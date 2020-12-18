#ifndef __XDCC_ECHO_H__
#define __XDCC_ECHO_H__

#include "amqlib.h"

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus */

#define MAXSTR_SIZE 16 /* XXX: should not be hardcoded, use per-field size from schema */

void echo_component_heartbeats_cpp(
    amqlib_t *__amqlib,
    int __is_topic,
    const char *ss,
    const char *st);
void unmarshal_component_heartbeats(
    const char *s, 
    int *fromRemote,
    char *ss, 
    char *st);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __XDCC_ECHO_H__ */
