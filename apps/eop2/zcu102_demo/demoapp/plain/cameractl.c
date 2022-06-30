#include "cameractl.h"
#include "klvparser.h"

#include "OrionPublicPacket.h"
#include "OrionComm.h"
#include "Constants.h"
#include "fielddecode.h"
#include "earthposition.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/mathematics.h"
#include "libavutil/opt.h"
#include "libavutil/rational.h"
#include "libavutil/avstring.h"
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,28,1)
#error "libavcodec version >= 55.28.1 required"
#endif

// Comment out to suppress OrionComm, e.g., for tcpreplay 
// #define ORION_COMM_ 1

// Incoming and outgoing packet structures. 
OrionPkt_t PktOut;

AVFormatContext *pInputContext = NULL;
AVCodecContext  *pDecodeContext = NULL;
AVCodecContext  *pEncodeContext = NULL;
AVFrame *pFrame = NULL;
AVPacket Packet;
AVPacket OutPacket;
int VideoStream = 0;
int DataStream = 0;

void StreamClose(void)
{
    // Free the AVFrames
    av_frame_free(&pFrame);

    // If we allocated a decode context
    if (pDecodeContext)
    {
        // Close it then free it
        avcodec_close(pDecodeContext);
        av_free(pDecodeContext);
    }

    // If we allocated an encode context
    if (pEncodeContext)
    {
        // Close it then free it
        avcodec_close(pEncodeContext);
        av_free(pEncodeContext);
    }

    // If we allocated a format context
    if (pInputContext)
    {
        // Pause, close and free it
        av_read_pause(pInputContext);
        avformat_close_input(&pInputContext);
        avformat_free_context(pInputContext);
    }

    // Nullify all the pointers we just messed with
    pDecodeContext  = NULL;
    pEncodeContext  = NULL;
    pFrame         = NULL;
    pInputContext = NULL;

}// StreamClose

int StreamOpen(const char *pUrl)
{
    AVCodec *pDeCodec;
    AVCodec *pEnCodec;

    // FFmpeg startup stuff
    avcodec_register_all();
    av_register_all();
    avformat_network_init();
    av_log_set_level(AV_LOG_QUIET);

    // Allocate a new format context
    pInputContext = avformat_alloc_context();

    // Have avformat_open_input timeout after 5s
    AVDictionary *pOptions = 0;
    av_dict_set(&pOptions, "timeout", "5000000", 0);

    // If the stream doesn't open
    if (avformat_open_input(&pInputContext, pUrl, NULL, &pOptions) < 0)
    {
        // Clean up the allocated resources (if any...) and exit with a failure code
        StreamClose();
        return 0;
    }

    // If there don't appear to be an valid streams in the transport stream
    if (pInputContext->nb_streams == 0)
    {
        // Clean up the allocated resources (if any...) and exit with a failure code
        StreamClose();
        return 0;
    }

    // Get the stream indices for video and metadata
    VideoStream = av_find_best_stream(pInputContext, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0);
    DataStream  = av_find_best_stream(pInputContext, AVMEDIA_TYPE_DATA,  -1, -1, NULL, 0);

    // Set the format context to playing
    av_read_play(pInputContext);

    // Get a codec pointer based on the video stream's codec ID and allocate a context
    pDeCodec = avcodec_find_decoder(pInputContext->streams[VideoStream]->codec->codec_id);
    pDecodeContext = avcodec_alloc_context3(pDeCodec);

    // Open the newly allocated decoder codec context
    avcodec_open2(pDecodeContext, pDeCodec, NULL);

    // Get a codec pointer for encoding format and allocate a context
    pEnCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
    pEncodeContext = avcodec_alloc_context3(pEnCodec);

    // Set encoding parameters
    pEncodeContext->bit_rate = 400000;
    pEncodeContext->width = 320;
    pEncodeContext->height = 180;
    pEncodeContext->time_base = (AVRational){1, 25};
    pEncodeContext->framerate = (AVRational){25, 1};
    pEncodeContext->gop_size = 10;
    pEncodeContext->max_b_frames = 1;
    pEncodeContext->pix_fmt = AV_PIX_FMT_YUV420P;
    if (pEnCodec->id == AV_CODEC_ID_H264)
        av_opt_set(pEncodeContext->priv_data, "preset", "slow", 0);

    // Open the newly allocated encoder codec context
    avcodec_open2(pEncodeContext, pEnCodec, NULL);

    // Allocate the decode frame structure
    pFrame = av_frame_alloc();

    // Finally, initialize the AVPacket structure
    av_init_packet(&Packet);
    Packet.data = NULL;
    Packet.size = 0;

    av_init_packet(&OutPacket);
    OutPacket.data = NULL;
    OutPacket.size = 0;

    // Done - return 1 to indicate success
    return 1;

}// StreamOpen

void re_encode(AVCodecContext *ectx, AVFrame *frame, AVPacket *pkt, char *buf, int *sz, int maxbytes)
{
    int ret;
    int idx;
    ret = avcodec_send_frame(ectx, frame);
    if (ret < 0) {
        fprintf(stderr, "Error sending a frame for encoding:%s\n",av_err2str(ret));
        *sz = 0;
        return;
    }
    idx = 0;
    *sz = 0;
    while (ret >= 0) {
        ret = avcodec_receive_packet(ectx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF) {
            return;
        }
        else if (ret < 0) {
            fprintf(stderr, "Error during encoding:%s\n", av_err2str(ret));
            exit(1);
        }
        // fprintf(stderr, "Write packet %3"PRId64" (size=%5d)\n", pkt->pts, pkt->size);
        if (idx + pkt->size <= maxbytes) {
            memcpy(&buf[idx], pkt->data, pkt->size);
            idx += pkt->size;
            *sz = idx;
        }
        else {
            fprintf(stderr, "Compressed frame larger than buffer\n");
            *sz = 0;
        }
    }
}

void pull_md(char *mbuf, int msz, struct llat_st *md) {
    int Result;
    md->lat = 0.0;
    md->lon = 0.0;
    md->alt = 0.0;
    md->ts  = 0;

    // Send the new metadata to the KLV parser
    KlvNewData(mbuf, msz);

    // Grab the gimbal's LLA and TS out of the KLV data
    md->lat = KlvGetValueDouble(KLV_UAS_SENSOR_LAT, &Result);
    md->lon = KlvGetValueDouble(KLV_UAS_SENSOR_LON, &Result);
    md->alt = KlvGetValueDouble(KLV_UAS_SENSOR_LON, &Result);
    md->ts  = KlvGetValueUInt(KLV_UAS_TIME_STAMP,   &Result);

    //fprintf(stderr, "\nImage LLAT: %11.6lf %11.6lf %7.1lf %ld", degrees(md->lat), degrees(md->lon), md->alt, md->ts);
}

int extract_metadata(char *buf, int *sz, int maxbytes) {
    static uint8_t *pMetaData = NULL;
    static uint64_t MetaDataBufferSize = 0;
    static uint64_t MetaDataSize = 0;
    static uint64_t MetaDataBytes = 0;

    // If we have a full metadata packet in memory, zero out the size and index
    if (MetaDataBytes == MetaDataSize)
        MetaDataBytes = MetaDataSize = 0;

    // If we don't have any metadata buffered up yet and this packet is big enough for a US key and size
    if ((MetaDataBytes == 0) && (Packet.size > 17))
    {
        // UAS LS universal key
        static const uint8_t KlvHeader[16] = {
            0x06, 0x0E, 0x2B, 0x34, 0x02, 0x0B, 0x01, 0x01,
            0x0E, 0x01, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00
        };

        // Try finding the KLV header in this packet
        const uint8_t *pStart = memmem(Packet.data, Packet.size, KlvHeader, 16);
        const uint8_t *pSize = pStart + 16;

        // If we found the header and the size tag is contained in this packet
        if ((pStart != 0) && ((pSize - Packet.data) < Packet.size))
        {
            // Initialize the header size to US key + 1 size byte and zero KLV tag bytes
            uint64_t KlvSize = 0, HeaderSize = 17;

            // If the size is a multi-byte BER-OID size
            if (pSize[0] & 0x80)
            {
                // Get the size of the size (up to )
                int Bytes = pSize[0] & 0x07, i;

                // If the entire size field is contained in this packet
                if (&pSize[Bytes] < &Packet.data[Packet.size])
                {
                    // Build the size up from the individual bytes
                    for (i = 0; i < Bytes; i++)
                        KlvSize = (KlvSize << 8) | pSize[i + 1];
                }

                // Add the additional size bytes to the header size
                HeaderSize += Bytes;
            }
            // Otherwise, just read the size byte straight out of byte 16
            else
                KlvSize = pSize[0];

            // If we got a valid local set size
            if (KlvSize > 0)
            {
                // Compute the maximum bytes to copy out of the packet
                int MaxBytes = Packet.size - (pStart - Packet.data);
                int TotalSize = HeaderSize + KlvSize;
                int BytesToCopy = MIN(MaxBytes, TotalSize);

                // If our local buffer is too small for the incoming data
                if (MetaDataBufferSize < TotalSize)
                {
                    // Reallocate enough space and store the new buffer size
                    pMetaData = (uint8_t *)realloc(pMetaData, TotalSize);
                    MetaDataBufferSize = TotalSize;
                }

                // Now copy the new data into the start of the local buffer
                memcpy(pMetaData, pStart, BytesToCopy);
                MetaDataSize = TotalSize;
                MetaDataBytes = BytesToCopy;
            }
        }
    }
    // Otherwise, if we're mid-packet
    else if (MetaDataBytes < MetaDataSize)
    {
        // Figure out the number of bytes to copy out of this particular packet
        int BytesToCopy = MIN(Packet.size, MetaDataSize - MetaDataBytes);

        // Copy into the local buffer in the right spot and increment the index
        memcpy(&pMetaData[MetaDataBytes], Packet.data, BytesToCopy);
        MetaDataBytes += BytesToCopy;
    }

    // There's new metadata if the size is non-zero and equal to the number of bytes read in
    if ((MetaDataSize != 0) && (MetaDataBytes == MetaDataSize)) {
        struct llat_st md;
        int mdsize = sizeof(struct llat_st);
        // If there's a valid metadata buffer and we're not going to overrun pData
        //if ((pMetaData != 0) && (MetaDataBytes <= maxbytes)) {
        //    // Copy the buffered KLV data into pData and send out the buffer size
        //    memcpy(buf, pMetaData, MetaDataBytes);
        //    *sz = MetaDataBytes;
        //    return 1;
        //}
        if ((pMetaData != 0) && (mdsize <= maxbytes)) {
            pull_md(pMetaData, MetaDataBytes, &md);
            memcpy(buf, &md, mdsize);
            *sz = mdsize;
        }
        else {
            *sz = 0;
            return 0;
        }
    }
}

int StreamProcess(char *fbuf, int *fsz, int fmaxbytes, char *mbuf, int *msz, int mmaxbytes) {
    // New video/metadata flags - note that NewMetaData == 1 if it's not in the TS
    int NewVideo = 0, NewMetaData = (pInputContext->nb_streams < 2);

    // As long as we can keep reading packets from the UDP socket
    while (av_read_frame(pInputContext, &Packet) >= 0)
    {
        int Index = Packet.stream_index;

        // If this packet belongs to the video stream
        if (Index == VideoStream)
        {
            // Pass it to the h.264 decoder
            avcodec_decode_video2(pDecodeContext, pFrame, &NewVideo, &Packet);

            // If this packet finished a video frame
            if (NewVideo)
            {
                // Pass it to the h.264 transcoder
                re_encode(pEncodeContext, pFrame, &OutPacket, fbuf, fsz, fmaxbytes);
                // Unref the frame
                av_frame_unref(pFrame);
            }
        }
        // If this is the KLV stream data
        else if (Index == DataStream)
        {
            NewMetaData = extract_metadata(mbuf, msz, mmaxbytes);
        }

        // Free the packet data
        av_free_packet(&Packet);
        av_free_packet(&OutPacket);

        // Return 1 if both a video frame and KLV packet have been read in
        if (NewVideo && NewMetaData) return 1;
    }

    // No new data if we made it here
    *msz = 0;
    *fsz = 0;
    return 0;
}// StreamProcess

int cam_shut(void) {
        StreamClose();
#ifdef ORION_COMM_
        OrionCommClose();
#endif /* ORION_COMM_ */
        return(1);
}

int cam_open(char *ipaddr) {
    uint8_t VideoFrame[1280 * 720 * 3] = { 0 };
    OrionNetworkVideo_t Settings;
    char VideoUrl[32] = "";
    int argc = 2;
    char *argv[2];
    argv[0] =  "";
    argv[1] =  ipaddr;

    // Zero out the video settings packet to set everything to 'no change'
    memset(&Settings, 0, sizeof(Settings));

    // Video port will default to 15004
    Settings.Port = 15004;
    Settings.StreamType = STREAM_TYPE_H264;

    uint8_t Octets[4];
    if (sscanf(ipaddr, "%3hhu.%3hhu.%3hhu.%3hhu", &Octets[0], &Octets[1], &Octets[2], &Octets[3]))
    {
        int Index = 0;
        Settings.DestIp = uint32FromBeBytes(Octets, &Index);
        sprintf(VideoUrl, "udp://%s:%d", ipaddr, Settings.Port);
    }

    // Send the network video settings
    encodeOrionNetworkVideoPacketStructure(&PktOut, &Settings);

#ifdef ORION_COMM_
    // If we can't connect to a gimbal, kill the app right now
    if (OrionCommOpen(&argc, &argv) == FALSE) {
        fprintf(stderr, "Failed to connect to gimabal%s\n", VideoUrl);
        cam_shut();
        return(1);
    }
    OrionCommSend(&PktOut);
#endif /* ORION_COMM_ */

    // If we can't open the video stream
    if (StreamOpen(VideoUrl) == 0)
    {
        fprintf(stderr, "Failed to open video at %s\n", VideoUrl);
        cam_shut();
        return(1);
    }
    return 0;
}

int cam_next(char *fbuf, int *fsz, int fmaxbytes, char *mbuf, int *msz, int mmaxbytes) {
    while (StreamProcess(fbuf, fsz, fmaxbytes, mbuf, msz, mmaxbytes) == 0) continue;
    return 0;
}

