#include "purple_rpc.h"
#define TAG_MATCH(X, Y) (X.mux == Y.mux && X.sec == Y.sec && X.typ == Y.typ)
#define WRAP(X) void *_wrapper_##X(void *tag) { while(1) { _handle_##X(); } }

void _hal_init(char *inuri, char *outuri) {
    xdc_log_level(2);
#ifdef __LEGACY_XDCOMMS__
    xdc_set_in(inuri);
    xdc_set_out(outuri);
    xdc_register(request_get_a_data_encode, request_get_a_data_decode, DATA_TYP_REQUEST_GET_A);
    xdc_register(response_get_a_data_encode, response_get_a_data_decode, DATA_TYP_RESPONSE_GET_A);
#endif /* __LEGACY_XDCOMMS__ */

}

#pragma cle begin RPC_GET_A
#pragma clang attribute push (__attribute__((annotate("RPC_GET_A"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
double _rpc_get_a(int *error) {
#pragma clang attribute pop
#pragma cle end RPC_GET_A
    gaps_tag t_tag;
    gaps_tag o_tag;
#ifndef __LEGACY_XDCOMMS__
    my_tag_write(&t_tag, MUX_REQUEST_GET_A, SEC_REQUEST_GET_A, DATA_TYP_REQUEST_GET_A);
#else
    tag_write(&t_tag, MUX_REQUEST_GET_A, SEC_REQUEST_GET_A, DATA_TYP_REQUEST_GET_A);
#endif /* __LEGACY_XDCOMMS__ */
#ifndef __LEGACY_XDCOMMS__
    my_tag_write(&o_tag, MUX_RESPONSE_GET_A, SEC_RESPONSE_GET_A, DATA_TYP_RESPONSE_GET_A);
#else
    tag_write(&o_tag, MUX_RESPONSE_GET_A, SEC_RESPONSE_GET_A, DATA_TYP_RESPONSE_GET_A);
#endif /* __LEGACY_XDCOMMS__ */
    static int req_counter = INT_MIN;
    static double last_processed_result = 0;
    static int last_processed_error = 0;
    static int inited = 0;
#ifndef __LEGACY_XDCOMMS__
    void *psocket;
    void *ssocket;
#else
    static void *psocket;
    static void *ssocket;
#endif /* __LEGACY_XDCOMMS__ */
    #pragma cle begin TAG_REQUEST_GET_A
#pragma clang attribute push (__attribute__((annotate("TAG_REQUEST_GET_A"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
    request_get_a_datatype request_get_a;
#pragma clang attribute pop
    #pragma cle end TAG_REQUEST_GET_A
    #pragma cle begin TAG_RESPONSE_GET_A
#pragma clang attribute push (__attribute__((annotate("TAG_RESPONSE_GET_A"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
    response_get_a_datatype response_get_a;
#pragma clang attribute pop
    #pragma cle end TAG_RESPONSE_GET_A
    double result;
#ifndef __LEGACY_XDCOMMS__
    codec_map  mycmap[DATA_TYP_MAX];
    for (int i=0; i < DATA_TYP_MAX; i++)  mycmap[i].valid=0;
    my_xdc_register(request_get_a_data_encode, request_get_a_data_decode, DATA_TYP_REQUEST_GET_A, mycmap);
    my_xdc_register(response_get_a_data_encode, response_get_a_data_decode, DATA_TYP_RESPONSE_GET_A, mycmap);
#endif /* __LEGACY_XDCOMMS__ */
#ifndef __LEGACY_XDCOMMS__
    void * ctx = zmq_ctx_new();
    psocket = my_xdc_pub_socket(ctx, (char *)OUTURI);
    ssocket = my_xdc_sub_socket_non_blocking(o_tag, ctx, 1000, (char*)INURI);
    sleep(1); /* zmq socket join delay */
#else
    if (!inited) {
        inited = 1;
        psocket = xdc_pub_socket();
        ssocket = xdc_sub_socket_non_blocking(o_tag, 1000);
        sleep(1); /* zmq socket join delay */
    }
#endif /* __LEGACY_XDCOMMS__ */
    request_get_a.dummy = 0;
    request_get_a.trailer.seq = req_counter;
#ifndef __LEGACY_XDCOMMS__
    if (req_counter == INT_MIN) {
        int tries_remaining = 30;
        while(tries_remaining != 0){
            my_xdc_asyn_send(psocket, &request_get_a, &t_tag , mycmap);
#ifndef __ONEWAY_RPC__
            *error = my_xdc_recv(ssocket, &response_get_a, &o_tag , mycmap);
            if (*error == -1){
                tries_remaining--;
                continue;
            }
#else
            *error = 0;
#endif /* __ONEWAY_RPC__ */
            break;  /* Reach here if received a response or __ONEWAY_RPC__ */
        }
#ifndef __ONEWAY_RPC__
        if (*error >= 0) req_counter = 1 + (response_get_a.trailer.seq >> 2);
#else
        req_counter++;
#endif /* __ONEWAY_RPC__ */
    }
#else /* __LEGACY_XDCOMMS__ */
    if (req_counter == INT_MIN) {
        int tries_remaining = 30;
        while(tries_remaining != 0){
            xdc_asyn_send(psocket, &request_get_a, &t_tag);
#ifndef __ONEWAY_RPC__
            *error = xdc_recv(ssocket, &response_get_a, &o_tag);
            if (*error == -1){
                tries_remaining--;
                continue;
            }
#else
            *error = 0;
#endif /* __ONEWAY_RPC__ */
            break;  /* Reach here if received a response or __ONEWAY_RPC__ */
        }
#ifndef __ONEWAY_RPC__
        if (*error >= 0) req_counter = 1 + (response_get_a.trailer.seq >> 2);
#else
        req_counter++;
#endif /* __ONEWAY_RPC__ */
    }
#endif /* __LEGACY_XDCOMMS__ */
    request_get_a.dummy = 0;
    request_get_a.trailer.seq = req_counter;
#ifndef __LEGACY_XDCOMMS__
    int tries_remaining = 30;
    while(tries_remaining != 0){
        my_xdc_asyn_send(psocket, &request_get_a, &t_tag , mycmap);
#ifndef __ONEWAY_RPC__
        *error = my_xdc_recv(ssocket, &response_get_a, &o_tag , mycmap);
        if (*error == -1){
            tries_remaining--;
            continue;
        }
#else
        *error = 0;
#endif /* __ONEWAY_RPC__ */
        break;  /* Reach here if received a response or __ONEWAY_RPC__ */
    }
    zmq_close(psocket);
    zmq_close(ssocket);
    zmq_ctx_shutdown(ctx);
#else /* __LEGACY_XDCOMMS__ */
    int tries_remaining = 30;
    while(tries_remaining != 0){
        xdc_asyn_send(psocket, &request_get_a, &t_tag);
#ifndef __ONEWAY_RPC__
        *error = xdc_recv(ssocket, &response_get_a, &o_tag);
        if (*error == -1){
            tries_remaining--;
            continue;
        }
#else
        *error = 0;
#endif /* __ONEWAY_RPC__ */
        break;  /* Reach here if received a response or __ONEWAY_RPC__ */
    }
#endif /* __LEGACY_XDCOMMS__ */
    req_counter++;
#ifndef __ONEWAY_RPC__
    result = response_get_a.ret;
    return (result);
#else
    return 0;
#endif /* __ONEWAY_RPC__ */
}

#pragma cle begin ERR_HANDLE_RPC_GET_A
#pragma clang attribute push (__attribute__((annotate("ERR_HANDLE_RPC_GET_A"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
double _err_handle_rpc_get_a(){
#pragma clang attribute pop
#pragma cle end ERR_HANDLE_RPC_GET_A
	int err_num;
	double res = _rpc_get_a(&err_num);
	// err handling code goes here
	return res;
}
void _master_rpc_init() {
    _hal_init((char*)INURI, (char *)OUTURI);
}

