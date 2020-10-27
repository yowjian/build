#include "amqlib.h"
#include <stdlib.h>
#include <list>
#include <iostream>
#include <amqm/AMQManager.h>
#include <nlohmann/json.hpp>

using namespace std;
using namespace std::placeholders;
using namespace amqm;
using json = nlohmann::json;

class FPC {
public:
    amqlib_fptr_t fun;
    FPC(amqlib_fptr_t f) { this->fun = f; }
    void apply(json j) { return (this->fun)(j.dump().c_str()); }
};

amqlib_t *amq() { 
    static amqlib_t *a = NULL; 
    if (a == NULL) { a = amqlib_create(); } 
    return a; 
}

amqlib_t *amqlib_create() {
    amqlib_t *m = (typeof(m))malloc(sizeof(*m));
    m->obj      = new AMQManager();
    m->fpl      = new std::list<FPC *>();
    return m;
}

void amqlib_destroy(amqlib_t *m) {
    if (m == NULL) return;
    delete static_cast<AMQManager *>(m->obj);
    std::list<FPC *> *fpl = static_cast<std::list<FPC *> *>(m->fpl);
    for (std::list<FPC *>::iterator it=fpl->begin(); it != fpl->end(); ++it) delete *it;
    fpl->clear();
    delete fpl;
    free(m);
}

void amqlib_publish(amqlib_t *m, const char *dst, const char *msg, int isTopic){
    if (m == NULL) return;
    AMQManager *obj = static_cast<AMQManager *>(m->obj);
    string t = string(dst);
    string v = string(msg);
    json   j = json::parse(v);
    obj->publish(t, j, isTopic==0?false:true);
}

void amqlib_listen (amqlib_t *m, const char *dst, amqlib_fptr_t f, int isTopic) {
    if (m == NULL) return;
    AMQManager *obj       = static_cast<AMQManager *>(m->obj);
    std::list<FPC *> *fpl = static_cast<std::list<FPC *> *>(m->fpl);
    FPC *fpc              = new FPC(f);
    obj->listen(string(dst), std::bind(&FPC::apply,fpc,_1), isTopic==0?false:true);
    fpl->push_back(fpc);
    return;
}

