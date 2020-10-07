#include "amqlib.h"
#include "map.h"
#include <stdlib.h>
#include <unistd.h>

/* XXX: Need to create CLE-JSON definitions here */

amqlib_t *amq() { static amqlib_t *a = NULL; if (a == NULL) { a = amqlib_create(); } return a; }

/* Messages in system */
#define ALL_MSGS_LIST \
  component_heartbeats, \
  updateMissionPlan, \
  updateNewTasking, \
  requestISRMDetections,\
  recieveISRMDetections, \
  groundMovers, \
  pnt

/* _local_X is 1 if X is local, else 0 */
#define _local_component_heartbeats 1
#define _local_updateMissionPlan 1
#define _local_updateNewTasking 1
#define _local_requestISRMDetections 1
#define _local_recieveISRMDetections 1
#define _local_groundMovers 1
#define _local_pnt 1

/* _topic_X is 1 if X is a topic, else 0 */
#define _topic_component_heartbeats 1
#define _topic_updateMissionPlan 1
#define _topic_updateNewTasking 1
#define _topic_requestISRMDetections 1
#define _topic_recieveISRMDetections 1
#define _topic_groundMovers 0
#define _topic_pnt 1

/* XXX: Some of these echo_functions will need to be blessed using CLE for RPC wrapping */
void echo_component_heartbeats(const char *s) {
  amqlib_publish(amq(), "component_heartbeats", s, _topic_component_heartbeats);
}
void echo_updateMissionPlan(const char *s) {
  amqlib_publish(amq(), "updateMissionPlan", s, _topic_updateMissionPlan);
}
void echo_updateNewTasking(const char *s) {
  amqlib_publish(amq(), "updateNewTasking", s, _topic_updateNewTasking);
}
void echo_requestISRMDetections(const char *s) {
  amqlib_publish(amq(), "requestISRMDetections", s, _topic_requestISRMDetections);
}
void echo_recieveISRMDetections(const char *s) {
  amqlib_publish(amq(), "recieveISRMDetections", s, _topic_recieveISRMDetections);
}
void echo_groundMovers(const char *s) {
  amqlib_publish(amq(), "groundMovers", s, _topic_groundMovers);
}
void echo_pnt(const char *s) {
  amqlib_publish(amq(), "pnt", s, _topic_pnt);
}

/* XXX: Some echo_ functions will be moved to remote enclave, and corresponding _rpc_echo_ functions created and called below */
void egress_component_heartbeats(const char *s) {
  if(!_local_component_heartbeats) echo_component_heartbeats(s);
}
void egress_updateMissionPlan(const char *s) {
  if(!_local_updateMissionPlan) echo_updateMissionPlan(s);
}
void egress_updateNewTasking(const char *s) {
  if(!_local_updateNewTasking) echo_updateNewTasking(s);
}
void egress_requestISRMDetections(const char *s) {
  if(!_local_requestISRMDetections) echo_requestISRMDetections(s);
}
void egress_recieveISRMDetections(const char *s) {
  if(!_local_recieveISRMDetections) echo_recieveISRMDetections(s);
}
void egress_groundMovers(const char *s) {
  if(!_local_groundMovers) echo_groundMovers(s);
}
void egress_pnt(const char *s) {
  if(!_local_pnt) echo_pnt(s);
}

#define XDCCLISTEN(X) amqlib_listen(amq(), #X, egress_##X, _topic_##X); 
int main() { 
  amq();
  MAP(XDCCLISTEN, ALL_MSGS_LIST)
  while(1) { sleep(100); }
  amqlib_destroy(amq());
  return 0; 
}

