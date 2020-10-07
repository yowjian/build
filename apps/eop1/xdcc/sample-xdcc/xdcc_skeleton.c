#include "amqlib.h"
#include "map.h"
#include <stdlib.h>
#include <unistd.h>

/* XXX: Need to create CLE-JSON definitions here */

amqlib_t *amq() { static amqlib_t *a = NULL; if (a == NULL) { a = amqlib_create(); } return a; }

/* Messages in system */
#define ALL_AMQ_MSG_LST \
  component_heartbeats, \
  updateMissionPlan, \
  updateNewTasking, \
  requestISRMDetections, \
  recieveISRMDetections, \
  groundMovers, \
  pnt

/* Remote messages if any */
/* #define REMOTE_MSG_LST */

/* Messages destined not to topics, but to queues */
/* #define QUEUE_MSG_LST */

#define LOCAL(X)   int _local_##X = 1;
#define UNLOCAL(X) _local_##X = 0;
MAP(LOCAL,   ALL_AMQ_MSG_LST)
#ifdef REMOTE_MSG_LST
MAP(UNLOCAL, REMOTE_MSG_LST)
#endif

#define TOPIC(X)   int _topic_##X = 1;
#define UNTOPIC(X) _topic_##X = 0;
MAP(TOPIC,   ALL_AMQ_MSG_LST)
#ifdef QUEUE_MSG_LST
MAP(UNTOPIC, QUEUE_MSG_LST)
#endif

/* XXX: Need to add CLE annotations to the functions defined by this macro */
#define XDCCEGRESS(X) void egress_##X(const char *s) { if (!_local_##X) amqlib_publish(amq(), #X, s, _topic_##X); }
MAP(XDCCEGRESS, ALL_AMQ_MSG_LST)

#define XDCCLISTEN(X) amqlib_listen(amq(), #X, egress_##X, _topic_##X); 
  
int main() { 
  amq();
  MAP(XDCCLISTEN, ALL_AMQ_MSG_LST)
  while(1) { sleep(100); }
  amqlib_destroy(amq());
  return 0; 
}

