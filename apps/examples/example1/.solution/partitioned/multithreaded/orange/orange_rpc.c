#include "orange_rpc.h"
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

#pragma cle begin HANDLE_REQUEST_GET_A
#pragma clang attribute push (__attribute__((annotate("HANDLE_REQUEST_GET_A"))), apply_to = any(function,type_alias,record,enum,variable(unless(is_parameter)),field))
void _handle_request_get_a() {
#pragma clang attribute pop
#pragma cle end HANDLE_REQUEST_GET_A
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
    static int res_counter = 0;
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
#ifndef __LEGACY_XDCOMMS__
    codec_map  mycmap[DATA_TYP_MAX];
    for (int i=0; i < DATA_TYP_MAX; i++)  mycmap[i].valid=0;
    my_xdc_register(request_get_a_data_encode, request_get_a_data_decode, DATA_TYP_REQUEST_GET_A, mycmap);
    my_xdc_register(response_get_a_data_encode, response_get_a_data_decode, DATA_TYP_RESPONSE_GET_A, mycmap);
#endif /* __LEGACY_XDCOMMS__ */
#ifndef __LEGACY_XDCOMMS__
    void * ctx = zmq_ctx_new();
    psocket = my_xdc_pub_socket(ctx, (char *)OUTURI);
    ssocket = my_xdc_sub_socket(t_tag, ctx, (char*)INURI);
    sleep(1); /* zmq socket join delay */
#else
    if (!inited) {
        inited = 1;
        psocket = xdc_pub_socket();
        ssocket = xdc_sub_socket(t_tag);
        sleep(1); /* zmq socket join delay */
    }
#endif /* __LEGACY_XDCOMMS__ */
#ifndef __LEGACY_XDCOMMS__
    int proc_error = 1;
    while (proc_error == 1) {
        my_xdc_blocking_recv(ssocket, &request_get_a, &t_tag, mycmap);
        int req_counter = request_get_a.trailer.seq;
        if(req_counter > res_counter){
            proc_error = 0;
            res_counter = req_counter;
            last_processed_result = get_a();
            response_get_a.ret = last_processed_result;
            last_processed_error = proc_error;
        }
#ifndef __ONEWAY_RPC__
        response_get_a.trailer.seq = res_counter << 2 | last_processed_error << 1;
        my_xdc_asyn_send(psocket, &response_get_a, &o_tag, mycmap);
#else /* __ONEWAY_RPC__ */
        res_counter = req_counter;
#endif /* __ONEWAY_RPC__ */
    }
    zmq_close(psocket);
    zmq_close(ssocket);
    zmq_ctx_shutdown(ctx);
#else
    int proc_error = 1;
    while (proc_error == 1) {
        xdc_blocking_recv(ssocket, &request_get_a, &t_tag);
        int req_counter = request_get_a.trailer.seq;
        if(req_counter > res_counter){
            proc_error = 0;
            res_counter = req_counter;
            last_processed_result = get_a();
            response_get_a.ret = last_processed_result;
            last_processed_error = proc_error;
        }
#ifndef __ONEWAY_RPC__
        response_get_a.trailer.seq = res_counter << 2 | last_processed_error << 1;
        xdc_asyn_send(psocket, &response_get_a, &o_tag);
#else /* __ONEWAY_RPC__ */
        res_counter = req_counter;
#endif /* __ONEWAY_RPC__ */
    }
#endif /* __LEGACY_XDCOMMS__ */
}

WRAP(request_get_a)
#define NXDRPC 1

int _slave_rpc_loop() {
    _hal_init((char *)INURI, (char *)OUTURI);
    pthread_t tid[NXDRPC];
    pthread_create(&tid[0], NULL, _wrapper_request_get_a, NULL);
    for (int i = 0; i < NXDRPC; i++) pthread_join(tid[i], NULL);
    return 0;
}

