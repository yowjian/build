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
    const char *st)
{
    json js;
    js["fromRemote"] = 1;
    js["ss"] = string(ss);
    js["st"] = string(st);

    AMQManager *amq = static_cast<AMQManager *>(__amqlib->obj);
    amq->publish("component_heartbeats", js, __is_topic==0?false:true);
}

void unmarshal_component_heartbeats(
    const char *s,
    int *fromRemote, 
    char *ss, 
    char *st)
{
    json js = json::parse(s);
    int fromRemote_cpp = js.contains("fromRemote")?js["fromRemote"].get<int>():0;
    string ss_cpp = js["ss"].get<string>();
    string st_cpp = js["st"].get<string>();

    *fromRemote = fromRemote_cpp;
    strncpy(ss, ss_cpp.c_str(),MAXSTR_SIZE);
    strncpy(st, st_cpp.c_str(),MAXSTR_SIZE);
}

} /* extern "C" */
