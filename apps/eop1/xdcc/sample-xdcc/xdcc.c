#include <stdlib.h>
#include <unistd.h>
#include "amqlib.h"
#include "xdcc_echo.h"
#include "map.h"

/* XXX: Need to create CLE-JSON definitions here */

/* XXX: Move to amqlib.c, define signature in amqlib.h */
/* amqlib_t *amq() { static amqlib_t *a = NULL; if (a == NULL) { a = amqlib_create(); } return a; } */

/* Messages in system */
#define ALL_MSGS_LIST \
    component_heartbeats

/* _local_X is 1 if X is local, else 0 */
#define _local_component_heartbeats 0

/* _topic_X is 1 if X is a topic, else 0 */
#define _topic_component_heartbeats 1

/* XXX: annotate and bless function */
void echo_component_heartbeats(
    const char *ss,
    const char *st,
    int k
)
{
    /* XXX: cues here to guide GEDL for size inference */
    echo_component_heartbeats_cpp(
        amq(),
        _topic_component_heartbeats,
        ss,
        st,
        k
    );
}

void egress_component_heartbeats(const char *s)
{
    /* XXX: annotate vars below */  
    char ss[MAXSTR_SIZE];  /* XXX: size should come from schema */
    char st[MAXSTR_SIZE];  /* XXX: size should come from schema */
    int k;
    if (_local_component_heartbeats) return;
    unmarshal_component_heartbeats(s,ss,st,&k);
    echo_component_heartbeats(ss, st, k);
}

/* MAK: added, did not see a main routine in Ta's XDCC */
#define XDCCLISTEN(X) amqlib_listen(amq(), #X, egress_##X, _topic_##X); 
int main() { 
  amq();
  MAP(XDCCLISTEN, ALL_MSGS_LIST)
  while(1) { sleep(100); }
  amqlib_destroy(amq());
  return 0; 
}
