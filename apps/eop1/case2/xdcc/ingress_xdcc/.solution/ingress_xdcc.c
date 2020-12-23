#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "amqlib.h"
#include "xdcc_echo.h"
#include "map.h"

#pragma cle def GREEN {"level":"green"}

#pragma cle def GREEN_SHAREABLE {\
  "level": "green",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "egress", \
     "guarddirective": { "operation": "allow"}}\
 ] }

#pragma cle def XDLINKAGE_ECHO_COMPONENT_HEARTBEATS { \
   "cdf": [ \
     { \
       "argtaints": [ \
         [ \
           "TAG_REQUEST_ECHO_COMPONENT_HEARTBEATS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_COMPONENT_HEARTBEATS" \
         ] \
       ], \
       "codtaints": [], \
       "direction": "egress", \
       "guarddirective": { \
         "gapstag": [], \
         "oneway": true, \
         "operation": "allow" \
       }, \
       "remotelevel": "green", \
       "rettaints": [] \
     } \
   ], \
   "level": "orange" \
 }

#pragma cle def XDLINKAGE_ECHO_RECIEVEISRMDETECTIONS { \
   "cdf": [ \
     { \
       "argtaints": [ \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_RECIEVEISRMDETECTIONS" \
         ] \
       ], \
       "codtaints": [], \
       "direction": "egress", \
       "guarddirective": { \
         "gapstag": [], \
         "oneway": true, \
         "operation": "allow" \
       }, \
       "remotelevel": "green", \
       "rettaints": [] \
     } \
   ], \
   "level": "orange" \
 }

/* Messages in system */
#define ALL_MSGS_LIST \
    component_heartbeats, \
    groundMovers, \
    pnt, \
    recieveEOIRDetections, \
    recieveISRMDetections, \
    recieveRDRDetections, \
    requestEOIRDetections, \
    requestISRMDetections, \
    requestRDRDetections, \
    updateMissionPlan

/* _local_X is 1 if X is local, else 0 */
#define _local_component_heartbeats 0
#define _local_groundMovers 1
#define _local_pnt 1
#define _local_recieveEOIRDetections 1
#define _local_recieveISRMDetections 0
#define _local_recieveRDRDetections 1
#define _local_requestEOIRDetections 1
#define _local_requestISRMDetections 1
#define _local_requestRDRDetections 1
#define _local_updateMissionPlan 1

/* _topic_X is 1 if X is a msg_name, else 0 */
#define _topic_component_heartbeats 1
#define _topic_groundMovers 1
#define _topic_pnt 1
#define _topic_recieveEOIRDetections 1
#define _topic_recieveISRMDetections 1
#define _topic_recieveRDRDetections 1
#define _topic_requestEOIRDetections 1
#define _topic_requestISRMDetections 1
#define _topic_requestRDRDetections 1
#define _topic_updateMissionPlan 1

#pragma cle begin XDLINKAGE_ECHO_COMPONENT_HEARTBEATS
int echo_component_heartbeats(
    char *ss,
    char *st
)
{
#pragma cle end XDLINKAGE_ECHO_COMPONENT_HEARTBEATS
    char ss_cpp[32];
    memcpy(ss_cpp, ss, 32);

    char st_cpp[64];
    memcpy(st_cpp, st, 64);

    echo_component_heartbeats_cpp(
        amq(),
        _topic_component_heartbeats,
        ss_cpp,
        st_cpp
    );
    return 0;
}

int egress_component_heartbeats(char *jstr)
{
    int fromRemote;

#pragma cle begin GREEN_SHAREABLE
    char ss[32];
    char st[64];
#pragma cle end GREEN_SHAREABLE

    if (_local_component_heartbeats)
        return 0;

    unmarshal_component_heartbeats(
        jstr,
        &fromRemote,
        ss,
        st
    );
    if (fromRemote == 0) {
        echo_component_heartbeats(
            ss,
            st
        );
    }
    return 0;
}

int egress_groundMovers(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

int egress_pnt(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

int egress_recieveEOIRDetections(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

#pragma cle begin XDLINKAGE_ECHO_RECIEVEISRMDETECTIONS
int echo_recieveISRMDetections(
    int detectsActiveCnt,
    int detectsMaxCnt,
    char *TGT_ISRM_ID0,
    char *TGT_ISRM_ID1,
    char *TGT_ISRM_ID2,
    char *TGT_ISRM_ID3,
    char *TGT_ISRM_ID4,
    char *TGT_ISRM_ID5,
    char *TGT_ISRM_ID6,
    char *TGT_ISRM_ID7,
    double alt[],
    double bearing[],
    char *classification0,
    char *classification1,
    char *classification2,
    char *classification3,
    char *classification4,
    char *classification5,
    char *classification6,
    char *classification7,
    double confidence[],
    double lat[],
    double lon[],
    double speed[]
)
{
#pragma cle end XDLINKAGE_ECHO_RECIEVEISRMDETECTIONS
    char TGT_ISRM_ID0_cpp[32];
    memcpy(TGT_ISRM_ID0_cpp, TGT_ISRM_ID0, 32);

    char TGT_ISRM_ID1_cpp[32];
    memcpy(TGT_ISRM_ID1_cpp, TGT_ISRM_ID1, 32);

    char TGT_ISRM_ID2_cpp[32];
    memcpy(TGT_ISRM_ID2_cpp, TGT_ISRM_ID2, 32);

    char TGT_ISRM_ID3_cpp[32];
    memcpy(TGT_ISRM_ID3_cpp, TGT_ISRM_ID3, 32);

    char TGT_ISRM_ID4_cpp[32];
    memcpy(TGT_ISRM_ID4_cpp, TGT_ISRM_ID4, 32);

    char TGT_ISRM_ID5_cpp[32];
    memcpy(TGT_ISRM_ID5_cpp, TGT_ISRM_ID5, 32);

    char TGT_ISRM_ID6_cpp[32];
    memcpy(TGT_ISRM_ID6_cpp, TGT_ISRM_ID6, 32);

    char TGT_ISRM_ID7_cpp[32];
    memcpy(TGT_ISRM_ID7_cpp, TGT_ISRM_ID7, 32);

    double alt_cpp[8];
    memcpy((char *)alt_cpp, (char *)alt, 64);

    double bearing_cpp[8];
    memcpy((char *)bearing_cpp, (char *)bearing, 64);

    char classification0_cpp[64];
    memcpy(classification0_cpp, classification0, 64);

    char classification1_cpp[64];
    memcpy(classification1_cpp, classification1, 64);

    char classification2_cpp[64];
    memcpy(classification2_cpp, classification2, 64);

    char classification3_cpp[64];
    memcpy(classification3_cpp, classification3, 64);

    char classification4_cpp[64];
    memcpy(classification4_cpp, classification4, 64);

    char classification5_cpp[64];
    memcpy(classification5_cpp, classification5, 64);

    char classification6_cpp[64];
    memcpy(classification6_cpp, classification6, 64);

    char classification7_cpp[64];
    memcpy(classification7_cpp, classification7, 64);

    double confidence_cpp[8];
    memcpy((char *)confidence_cpp, (char *)confidence, 64);

    double lat_cpp[8];
    memcpy((char *)lat_cpp, (char *)lat, 64);

    double lon_cpp[8];
    memcpy((char *)lon_cpp, (char *)lon, 64);

    double speed_cpp[8];
    memcpy((char *)speed_cpp, (char *)speed, 64);

    echo_recieveISRMDetections_cpp(
        amq(),
        _topic_recieveISRMDetections,
        detectsActiveCnt,
        detectsMaxCnt,
        TGT_ISRM_ID0,
        TGT_ISRM_ID1,
        TGT_ISRM_ID2,
        TGT_ISRM_ID3,
        TGT_ISRM_ID4,
        TGT_ISRM_ID5,
        TGT_ISRM_ID6,
        TGT_ISRM_ID7,
        alt,
        bearing,
        classification0,
        classification1,
        classification2,
        classification3,
        classification4,
        classification5,
        classification6,
        classification7,
        confidence,
        lat,
        lon,
        speed
    );
    return 0;
}

int egress_recieveISRMDetections(char *jstr)
{
    int fromRemote;

#pragma cle begin GREEN_SHAREABLE
    int detectsActiveCnt;
    int detectsMaxCnt = 8; // numElements from schema
    char TGT_ISRM_ID0[32];
    char TGT_ISRM_ID1[32];
    char TGT_ISRM_ID2[32];
    char TGT_ISRM_ID3[32];
    char TGT_ISRM_ID4[32];
    char TGT_ISRM_ID5[32];
    char TGT_ISRM_ID6[32];
    char TGT_ISRM_ID7[32];
    double alt[detectsMaxCnt];
    double bearing[detectsMaxCnt];
    char classification0[64];
    char classification1[64];
    char classification2[64];
    char classification3[64];
    char classification4[64];
    char classification5[64];
    char classification6[64];
    char classification7[64];
    double confidence[detectsMaxCnt];
    double lat[detectsMaxCnt];
    double lon[detectsMaxCnt];
    double speed[detectsMaxCnt];
#pragma cle end GREEN_SHAREABLE

    if (_local_recieveISRMDetections)
        return 0;

    unmarshal_recieveISRMDetections(
        jstr,
        &fromRemote,
        &detectsActiveCnt,
        detectsMaxCnt,
        TGT_ISRM_ID0,
        TGT_ISRM_ID1,
        TGT_ISRM_ID2,
        TGT_ISRM_ID3,
        TGT_ISRM_ID4,
        TGT_ISRM_ID5,
        TGT_ISRM_ID6,
        TGT_ISRM_ID7,
        alt,
        bearing,
        classification0,
        classification1,
        classification2,
        classification3,
        classification4,
        classification5,
        classification6,
        classification7,
        confidence,
        lat,
        lon,
        speed
    );
    if (fromRemote == 0) {
        echo_recieveISRMDetections(
            detectsActiveCnt,
            detectsMaxCnt,
            TGT_ISRM_ID0,
            TGT_ISRM_ID1,
            TGT_ISRM_ID2,
            TGT_ISRM_ID3,
            TGT_ISRM_ID4,
            TGT_ISRM_ID5,
            TGT_ISRM_ID6,
            TGT_ISRM_ID7,
            alt,
            bearing,
            classification0,
            classification1,
            classification2,
            classification3,
            classification4,
            classification5,
            classification6,
            classification7,
            confidence,
            lat,
            lon,
            speed
        );
    }
    return 0;
}

int egress_recieveRDRDetections(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

int egress_requestEOIRDetections(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

int egress_requestISRMDetections(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

int egress_requestRDRDetections(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

int egress_updateMissionPlan(char *jstr)
{
#pragma cle begin GREEN_SHAREABLE
    int ret = 0;
#pragma cle end GREEN_SHAREABLE
    return ret;
}

#define XDCCLISTEN(X) amqlib_listen(amq(), #X, egress_##X, _topic_##X);
int main() {
#pragma cle begin GREEN_SHAREABLE
    int i = 100;
#pragma cle end GREEN_SHAREABLE
    amq();
    MAP(XDCCLISTEN, ALL_MSGS_LIST)

    while(1) {
        sleep(i);
    }

    amqlib_destroy(amq());
    return 0; 
}
