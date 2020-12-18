#ifndef __AMQLIB_H__
#define __AMQLIB_H__
#ifdef __cplusplus
extern "C" {
#endif

struct __amqlib { 
  void *obj; 
  void *fpl;
}; 

typedef struct __amqlib amqlib_t;
typedef void (*amqlib_fptr_t)(const char *s);

amqlib_t *amq();
amqlib_t *amqlib_create();
void     amqlib_destroy(amqlib_t *m);
void     amqlib_publish(amqlib_t *m, const char *dst, const char *msg, int isTopic);
void     amqlib_listen (amqlib_t *m, const char *dst, amqlib_fptr_t f, int isTopic);

#ifdef __cplusplus
}
#endif
#endif /* __AMQLIB_H__ */
