#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "amqlib.h"
#include "xdcc_echo.h"
#include "map.h"

#pragma cle def ORANGE {"level":"orange"}

#pragma cle def PURPLE_SHAREABLE {"level":"purple",\
  "cdf": [\
    {"remotelevel":"orange", \
     "direction": "egress", \
     "guarddirective": { "operation": "allow"}}\
  ] }

#pragma cle def XDLINKAGE_ECHO_COMPONENT_HEARTBEATS {"level":"orange",\
  "cdf": [\
    {"remotelevel":"purple", \
     "direction": "ingress", \
     "guarddirective": { "operation": "allow", "oneway": true}, \
     "argtaints": [["TAG_REQUEST_ECHO_COMPONENT_HEARTBEATS"]], \
     "codtaints": ["ORANGE"], \
     "rettaints": [] \
    } \
  ] }

/* Messages in system */
#define ALL_MSGS_LIST \
    component_heartbeats

/* _local_X is 1 if X is local, else 0 */
#define _local_component_heartbeats 0

/* _topic_X is 1 if X is a topic, else 0 */
#define _topic_component_heartbeats 1

#pragma cle begin XDLINKAGE_ECHO_COMPONENT_HEARTBEATS
int echo_component_heartbeats(
    char *ss,
    char *st
  )
{
#pragma cle end XDLINKAGE_ECHO_COMPONENT_HEARTBEATS
    /* cues here guide GEDL for size inference */
    char ss_cpp[MAXSTR_SIZE];
    char st_cpp[MAXSTR_SIZE];
    
    memcpy(ss_cpp, ss, MAXSTR_SIZE); /* XXX: size should come from schema */
    memcpy(st_cpp, st, MAXSTR_SIZE); /* XXX: size should come from schema */

    echo_component_heartbeats_cpp(
        amq(),
        _topic_component_heartbeats,
        ss_cpp,
        st_cpp
    );
    return 0;
}

void egress_component_heartbeats(const char *s)
{
    int fromRemote;
    #pragma cle begin PURPLE_SHAREABLE
    char ss[MAXSTR_SIZE];  /* XXX: size should come from schema */
    char st[MAXSTR_SIZE];  /* XXX: size should come from schema */
    #pragma cle end PURPLE_SHAREABLE
    if (_local_component_heartbeats) return;
    unmarshal_component_heartbeats(s,&fromRemote,ss,st);
    /* XXX: do CLOSURE tools require wrappable function to return non-void value? */
    if (fromRemote==0) echo_component_heartbeats(ss, st);
}

#define XDCCLISTEN(X) amqlib_listen(amq(), #X, egress_##X, _topic_##X); 
int main() {
  #pragma cle begin PURPLE_SHAREABLE
  int i = 100;
  #pragma cle end PURPLE_SHAREABLE; 
  amq();
  MAP(XDCCLISTEN, ALL_MSGS_LIST)
  while(1) { sleep(i); }
  amqlib_destroy(amq());
  return 0; 
}
