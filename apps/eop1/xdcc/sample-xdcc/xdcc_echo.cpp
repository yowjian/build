#include <amqm/AMQManager.h>
#include <nlohmann/json.hpp>
#include <string.h>
#include "xdcc_echo.h"

using namespace std;
using namespace amqm;
using json = nlohmann::json;

extern "C" {

void echo_component_heartbeats_cpp(
    amqlib_t *__amqlib,
    int __is_topic,
    const char *ss,
    const char *st,
    int k
)
{
    json js;
    js["ss"] = string(ss);
    js["st"] = string(st);
    js["k"]  = k;

    AMQManager *amq = static_cast<AMQManager *>(__amqlib->obj);
    amq->publish("component_heartbeats", js.dump(), __is_topic==0?false:true);
}

void unmarshal_component_heartbeats(
    const char *s, 
    char *ss, 
    char *st, 
    int *k)
{
    json js = json::parse(s);

    string ss_cpp = js["ss"].get<string>();
    string st_cpp = js["st"].get<string>();
    int k_cpp     = js["k"].get<int>();

    strncpy(ss, ss_cpp.c_str(),MAXSTR_SIZE);
    strncpy(st, st_cpp.c_str(),MAXSTR_SIZE);
    *k = k_cpp;
}

} /* extern "C" */
