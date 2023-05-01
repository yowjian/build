#ifndef _PURPLE_RPC_
#define _PURPLE_RPC_

#include "codec.h"
#include <limits.h>

#include "xdcomms.h"
#define INURI "ipc:///tmp/sock_subpurple"
#define OUTURI "ipc:///tmp/sock_pubpurple"

#define MUX_BASE 0
#define SEC_BASE 0
#define TYP_BASE 0

extern void _master_rpc_init();

#pragma cle def RPC_GET_EWMA {"level": "purple", \
    "cdf": [{"remotelevel":"purple", "direction": "bidirectional", \
            "guarddirective": {"operation": "allow"}, \
            "argtaints": [["TAG_REQUEST_GET_EWMA", "TAG_RESPONSE_GET_EWMA"]],\
            "codtaints": ["TAG_REQUEST_GET_EWMA", "TAG_RESPONSE_GET_EWMA"],\
            "rettaints": ["TAG_RESPONSE_GET_EWMA"]\
            }]}
#pragma cle def ERR_HANDLE_RPC_GET_EWMA {"level": "purple", \
    "cdf": [{"remotelevel":"purple", "direction": "bidirectional", \
            "guarddirective": {"operation": "allow"}, \
            "argtaints": [],\
            "codtaints": ["TAG_REQUEST_GET_EWMA", "TAG_RESPONSE_GET_EWMA"],\
            "rettaints": ["TAG_RESPONSE_GET_EWMA"]\
            }]}
#pragma cle def TAG_NEXTRPC {"level": "purple", \
    "cdf": [{"remotelevel": "orange", "direction": "egress", \
            "guarddirective": {"operation": "allow", "gapstag": [2,2,1]}}]}

#pragma cle def TAG_OKAY {"level": "purple", \
    "cdf": [{"remotelevel": "purple", "direction": "egress", \
            "guarddirective": {"operation": "allow", "gapstag": [1,1,2]}}]}

#pragma cle def TAG_REQUEST_GET_EWMA {"level": "purple", \
    "cdf": [{"remotelevel": "orange", "direction": "egress", \
            "guarddirective": {"operation": "allow", "gapstag": [2,2,3]}}]}

#pragma cle def TAG_RESPONSE_GET_EWMA {"level": "purple", \
    "cdf": [{"remotelevel": "purple", "direction": "egress", \
            "guarddirective": {"operation": "allow", "gapstag": [1,1,4]}}]}

#define MUX_NEXTRPC MUX_BASE + 2
#define SEC_NEXTRPC SEC_BASE + 2
#define MUX_OKAY MUX_BASE + 1
#define SEC_OKAY SEC_BASE + 1
#define MUX_REQUEST_GET_EWMA MUX_BASE + 2
#define SEC_REQUEST_GET_EWMA SEC_BASE + 2
#define MUX_RESPONSE_GET_EWMA MUX_BASE + 1
#define SEC_RESPONSE_GET_EWMA SEC_BASE + 1

extern double _err_handle_rpc_get_ewma(void);

#endif /* _PURPLE_RPC_ */
