#include "mongoose.h"
#include "cameractl.h"
#include <pthread.h>
#include <unistd.h>

#define FRAME_INTERVAL  20
#define POLL_INTERVAL   5
#define WSS_URL         "wss://0.0.0.0:8443"   
#define HTTPS_URL       "https://0.0.0.0:8443"
#define WWW_ROOT        "./www"

// ------------------------------------------------------------------------------------
// Video processing that will run on ARM
// ------------------------------------------------------------------------------------

struct framebuf_st * get_framebuf() {
  static struct framebuf_st wp;
  static int inited = 0;
  if (!inited) { inited  = 1; wp.newf = 0; wp.size = 0; }
  return &wp;
}

int getNextFrame(char buf[static MAX_FRAME_BUF]) {
  int sz;
  struct framebuf_st *wp;
  wp = get_framebuf();
  pthread_mutex_lock(&wp->flk);
  if (wp->newf == 1 && wp->size > 0) {
     memcpy(buf, wp->data, wp->size);
     wp->newf = 0;  // mark frame not new 
     sz = wp->size;
  } else {
     sz = 0;
  }
  pthread_mutex_unlock(&wp->flk);
  return sz;
}

int init_videoproc() {
  while (cam_open("192.1.100.192") != 0) {
    fprintf(stderr, "Unable to open camera, sleeping for 5 seconds\n");
    sleep(5);
  }
  return 0;
}

void *process_video(void *arg) {
  struct framebuf_st *wp = (struct framebuf_st *) arg;
  char fbuf[MAX_FRAME_BUF];
  int  fmaxbytes = MAX_FRAME_BUF;
  int  fsz;

  char mbuf[MAX_MDATA_BUF];
  int  mmaxbytes = MAX_MDATA_BUF;
  int  msz;

  init_videoproc();
  for(;;) {
    cam_next(fbuf, &fsz, fmaxbytes, mbuf, &msz, mmaxbytes);
    usleep(5000);
    pthread_mutex_lock(&wp->flk);
    memcpy(wp->data, fbuf, fsz);  // XXX: avoid copy by making StreamProcess do the locking
    wp->size = fsz;
    wp->newf = 1;
    pthread_mutex_unlock(&wp->flk);
  }
  return NULL;
}

void run_videoproc() {
  struct framebuf_st *wp;
  wp = get_framebuf();
  printf("Initializing video processing\n");
  pthread_t thread_id = (pthread_t) 0;
  pthread_attr_t attr;
  (void) pthread_attr_init(&attr);
  (void) pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
  pthread_create(&thread_id, &attr, (void *(*) (void *)) process_video, (void *) wp);
  pthread_attr_destroy(&attr);
}

// ------------------------------------------------------------------------------------
// Webserver that will run on MB
// ------------------------------------------------------------------------------------

void handle_camera_command(struct mg_connection *c, struct mg_http_message *hm) {
  if (hm != NULL) {
    // XXX: process h, send commands to remote camera, receive and return response to browser
    mg_http_reply(c, 200, "", "{\"result\": %d}\n", 123);
  }
}

void wsend_video(void *arg) {
  struct mg_mgr *mgr = (struct mg_mgr *) arg;
  static char buf[MAX_FRAME_BUF];
  int sz;
  sz = getNextFrame(buf);
  if (sz > 0) {
    for (struct mg_connection *c = mgr->conns; c != NULL; c = c->next) { // send next frame to each live stream
      if (c->label[0] == 'S') {
          mg_ws_send(c, buf, sz, WEBSOCKET_OP_BINARY);
          // fprintf(stderr, "Sent frame to websock\n");
      }
    }
  }
}

void webfn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
  static const char *s_web_root = WWW_ROOT;
  if (ev == MG_EV_ACCEPT && fn_data != NULL) {
    struct mg_tls_opts opts = {
      .cert = "./creds/server.pem",
      .certkey = "./creds/server.pem",
    };
    mg_tls_init(c, &opts);
  } else if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_http_match_uri(hm, "/ws/video"))   { // Upgrade to websocket and mark connection as live streamer
      fprintf(stderr, "Stream request reeived, upgrading to websocket\n");
      mg_ws_upgrade(c, hm, NULL);
      c->label[0] = 'S';  
    } else if (mg_http_match_uri(hm, "/api")) { // Handle camera API commands
      handle_camera_command(c, hm);
    } else {                                    // Serve files for webpages
      struct mg_http_serve_opts opts = {.root_dir = s_web_root};
      mg_http_serve_dir(c, ev_data, &opts);
    }
  } 
}

void run_webserver() {
  struct mg_mgr mgr;
  const char *s_listen_on  = WSS_URL;
  const char *s_https_addr = HTTPS_URL;
  mg_mgr_init(&mgr);
  printf("Starting HTTPS camera API endpoint on %s/api\n", s_https_addr);
  printf("Starting WSS video endpoint on %s/ws/video\n", s_listen_on);
  mg_http_listen(&mgr, s_https_addr, webfn, (void *) 1);
  mg_timer_add(&mgr, FRAME_INTERVAL, MG_TIMER_REPEAT, wsend_video, &mgr);
  for (;;) mg_mgr_poll(&mgr, POLL_INTERVAL);
  mg_mgr_free(&mgr);
}

int main(void) {
  run_videoproc();
  run_webserver();
  return 0;
}
