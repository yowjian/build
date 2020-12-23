#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "amqlib.h"
#include "xdcc_echo.h"
#include "map.h"

#pragma cle def ORANGE {"level":"orange"}

#pragma cle def ORANGE_SHAREABLE {\
  "level": "orange",\
  "cdf": [\
    {"remotelevel":"green", \
     "direction": "egress", \
     "guarddirective": { "operation": "allow"}}\
 ] }

#pragma cle def XDLINKAGE_ECHO_COMPONENT_HEARTBEATS { \
   "cdf": [ \
     { \
       "argtaints": [ \
         [ \
           "TAG_REQUEST_ECHO_COMPONENT_HEARTBEATS" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_COMPONENT_HEARTBEATS" \
         ] \
       ], \
       "codtaints": [], \
       "direction": "egress", \
       "guarddirective": { \
         "gapstag": [], \
         "oneway": true, \
         "operation": "allow" \
       }, \
       "remotelevel": "orange", \
       "rettaints": [] \
     } \
   ], \
   "level": "green" \
 }

#pragma cle def XDLINKAGE_ECHO_PNT { \
   "cdf": [ \
     { \
       "argtaints": [ \
         [ \
           "TAG_REQUEST_ECHO_PNT" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_PNT" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_PNT" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_PNT" \
         ] \
       ], \
       "codtaints": [], \
       "direction": "egress", \
       "guarddirective": { \
         "gapstag": [], \
         "oneway": true, \
         "operation": "allow" \
       }, \
       "remotelevel": "orange", \
       "rettaints": [] \
     } \
   ], \
   "level": "green" \
 }

#pragma cle def XDLINKAGE_ECHO_REQUESTISRMDETECTIONS { \
   "cdf": [ \
     { \
       "argtaints": [ \
         [ \
           "TAG_REQUEST_ECHO_REQUESTISRMDETECTIONS" \
         ] \
       ], \
       "codtaints": [], \
       "direction": "egress", \
       "guarddirective": { \
         "gapstag": [], \
         "oneway": true, \
         "operation": "allow" \
       }, \
       "remotelevel": "orange", \
       "rettaints": [] \
     } \
   ], \
   "level": "green" \
 }

#pragma cle def XDLINKAGE_ECHO_UPDATEMISSIONPLAN { \
   "cdf": [ \
     { \
       "argtaints": [ \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ], \
         [ \
           "TAG_REQUEST_ECHO_UPDATEMISSIONPLAN" \
         ] \
       ], \
       "codtaints": [], \
       "direction": "egress", \
       "guarddirective": { \
         "gapstag": [], \
         "oneway": true, \
         "operation": "allow" \
       }, \
       "remotelevel": "orange", \
       "rettaints": [] \
     } \
   ], \
   "level": "green" \
 }

/* Messages in system */
#define ALL_MSGS_LIST \
    component_heartbeats, \
    groundMovers, \
    pnt, \
    recieveEOIRDetections, \
    recieveISRMDetections, \
    recieveRDRDetections, \
    requestEOIRDetections, \
    requestISRMDetections, \
    requestRDRDetections, \
    updateMissionPlan

/* _local_X is 1 if X is local, else 0 */
#define _local_component_heartbeats 0
#define _local_groundMovers 1
#define _local_pnt 0
#define _local_recieveEOIRDetections 1
#define _local_recieveISRMDetections 1
#define _local_recieveRDRDetections 1
#define _local_requestEOIRDetections 1
#define _local_requestISRMDetections 0
#define _local_requestRDRDetections 1
#define _local_updateMissionPlan 0

/* _topic_X is 1 if X is a msg_name, else 0 */
#define _topic_component_heartbeats 1
#define _topic_groundMovers 1
#define _topic_pnt 1
#define _topic_recieveEOIRDetections 1
#define _topic_recieveISRMDetections 1
#define _topic_recieveRDRDetections 1
#define _topic_requestEOIRDetections 1
#define _topic_requestISRMDetections 1
#define _topic_requestRDRDetections 1
#define _topic_updateMissionPlan 1

#pragma cle begin XDLINKAGE_ECHO_COMPONENT_HEARTBEATS
int echo_component_heartbeats(
    char *ss,
    char *st
)
{
#pragma cle end XDLINKAGE_ECHO_COMPONENT_HEARTBEATS
    char ss_cpp[32];
    memcpy(ss_cpp, ss, 32);

    char st_cpp[64];
    memcpy(st_cpp, st, 64);

    echo_component_heartbeats_cpp(
        amq(),
        _topic_component_heartbeats,
        ss_cpp,
        st_cpp
    );
    return 0;
}

int egress_component_heartbeats(char *jstr)
{
    int fromRemote;

#pragma cle begin ORANGE_SHAREABLE
    char ss[32];
    char st[64];
#pragma cle end ORANGE_SHAREABLE

    if (_local_component_heartbeats)
        return 0;

    unmarshal_component_heartbeats(
        jstr,
        &fromRemote,
        ss,
        st
    );
    if (fromRemote == 0) {
        echo_component_heartbeats(
            ss,
            st
        );
    }
    return 0;
}

int egress_groundMovers(char *jstr)
{
#pragma cle begin ORANGE_SHAREABLE
    int ret = 0;
#pragma cle end ORANGE_SHAREABLE
    return ret;
}

#pragma cle begin XDLINKAGE_ECHO_PNT
int echo_pnt(
    double alt,
    double lat,
    double lon,
    int time
)
{
#pragma cle end XDLINKAGE_ECHO_PNT
    echo_pnt_cpp(
        amq(),
        _topic_pnt,
        alt,
        lat,
        lon,
        time
    );
    return 0;
}

int egress_pnt(char *jstr)
{
    int fromRemote;

#pragma cle begin ORANGE_SHAREABLE
    double alt;
    double lat;
    double lon;
    int time;
#pragma cle end ORANGE_SHAREABLE

    if (_local_pnt)
        return 0;

    unmarshal_pnt(
        jstr,
        &fromRemote,
        &alt,
        &lat,
        &lon,
        &time
    );
    if (fromRemote == 0) {
        echo_pnt(
            alt,
            lat,
            lon,
            time
        );
    }
    return 0;
}

int egress_recieveEOIRDetections(char *jstr)
{
#pragma cle begin ORANGE_SHAREABLE
    int ret = 0;
#pragma cle end ORANGE_SHAREABLE
    return ret;
}

int egress_recieveISRMDetections(char *jstr)
{
#pragma cle begin ORANGE_SHAREABLE
    int ret = 0;
#pragma cle end ORANGE_SHAREABLE
    return ret;
}

int egress_recieveRDRDetections(char *jstr)
{
#pragma cle begin ORANGE_SHAREABLE
    int ret = 0;
#pragma cle end ORANGE_SHAREABLE
    return ret;
}

int egress_requestEOIRDetections(char *jstr)
{
#pragma cle begin ORANGE_SHAREABLE
    int ret = 0;
#pragma cle end ORANGE_SHAREABLE
    return ret;
}

#pragma cle begin XDLINKAGE_ECHO_REQUESTISRMDETECTIONS
int echo_requestISRMDetections(
    char *phase
)
{
#pragma cle end XDLINKAGE_ECHO_REQUESTISRMDETECTIONS
    char phase_cpp[32];
    memcpy(phase_cpp, phase, 32);

    echo_requestISRMDetections_cpp(
        amq(),
        _topic_requestISRMDetections,
        phase_cpp
    );
    return 0;
}

int egress_requestISRMDetections(char *jstr)
{
    int fromRemote;

#pragma cle begin ORANGE_SHAREABLE
    char phase[32];
#pragma cle end ORANGE_SHAREABLE

    if (_local_requestISRMDetections)
        return 0;

    unmarshal_requestISRMDetections(
        jstr,
        &fromRemote,
        phase
    );
    if (fromRemote == 0) {
        echo_requestISRMDetections(
            phase
        );
    }
    return 0;
}

int egress_requestRDRDetections(char *jstr)
{
#pragma cle begin ORANGE_SHAREABLE
    int ret = 0;
#pragma cle end ORANGE_SHAREABLE
    return ret;
}

#pragma cle begin XDLINKAGE_ECHO_UPDATEMISSIONPLAN
int echo_updateMissionPlan(
    char *missionPlanId,
    int actionsActiveCnt,
    int actionsMaxCnt,
    char *actionId0,
    char *actionId1,
    char *actionId2,
    char *actionType0,
    char *actionType1,
    char *actionType2,
    char *wayPointId0,
    char *wayPointId1,
    char *wayPointId2,
    int numberOfSensorWayPoints,
    char *sensorPlanId,
    char *vehiclePlanId,
    int numberOfWayPoints,
    char *vehiclePlanId1,
    int wayPointsActiveCnt,
    int wayPointsMaxCnt,
    char *wayPointId20,
    char *wayPointId21,
    char *wayPointId22,
    char *wayPointId23,
    char *wayPointId24,
    double x[],
    double y[],
    double z[]
)
{
#pragma cle end XDLINKAGE_ECHO_UPDATEMISSIONPLAN
    char missionPlanId_cpp[32];
    memcpy(missionPlanId_cpp, missionPlanId, 32);

    char actionId0_cpp[32];
    memcpy(actionId0_cpp, actionId0, 32);

    char actionId1_cpp[32];
    memcpy(actionId1_cpp, actionId1, 32);

    char actionId2_cpp[32];
    memcpy(actionId2_cpp, actionId2, 32);

    char actionType0_cpp[32];
    memcpy(actionType0_cpp, actionType0, 32);

    char actionType1_cpp[32];
    memcpy(actionType1_cpp, actionType1, 32);

    char actionType2_cpp[32];
    memcpy(actionType2_cpp, actionType2, 32);

    char wayPointId0_cpp[32];
    memcpy(wayPointId0_cpp, wayPointId0, 32);

    char wayPointId1_cpp[32];
    memcpy(wayPointId1_cpp, wayPointId1, 32);

    char wayPointId2_cpp[32];
    memcpy(wayPointId2_cpp, wayPointId2, 32);

    char sensorPlanId_cpp[32];
    memcpy(sensorPlanId_cpp, sensorPlanId, 32);

    char vehiclePlanId_cpp[32];
    memcpy(vehiclePlanId_cpp, vehiclePlanId, 32);

    char vehiclePlanId1_cpp[32];
    memcpy(vehiclePlanId1_cpp, vehiclePlanId1, 32);

    char wayPointId20_cpp[32];
    memcpy(wayPointId20_cpp, wayPointId20, 32);

    char wayPointId21_cpp[32];
    memcpy(wayPointId21_cpp, wayPointId21, 32);

    char wayPointId22_cpp[32];
    memcpy(wayPointId22_cpp, wayPointId22, 32);

    char wayPointId23_cpp[32];
    memcpy(wayPointId23_cpp, wayPointId23, 32);

    char wayPointId24_cpp[32];
    memcpy(wayPointId24_cpp, wayPointId24, 32);

    double x_cpp[5];
    memcpy((char *)x_cpp, (char *)x, 40);

    double y_cpp[5];
    memcpy((char *)y_cpp, (char *)y, 40);

    double z_cpp[5];
    memcpy((char *)z_cpp, (char *)z, 40);

    echo_updateMissionPlan_cpp(
        amq(),
        _topic_updateMissionPlan,
        missionPlanId_cpp,
        actionsActiveCnt,
        actionsMaxCnt,
        actionId0,
        actionId1,
        actionId2,
        actionType0,
        actionType1,
        actionType2,
        wayPointId0,
        wayPointId1,
        wayPointId2,
        numberOfSensorWayPoints,
        sensorPlanId_cpp,
        vehiclePlanId_cpp,
        numberOfWayPoints,
        vehiclePlanId1_cpp,
        wayPointsActiveCnt,
        wayPointsMaxCnt,
        wayPointId20,
        wayPointId21,
        wayPointId22,
        wayPointId23,
        wayPointId24,
        x,
        y,
        z
    );
    return 0;
}

int egress_updateMissionPlan(char *jstr)
{
    int fromRemote;

#pragma cle begin ORANGE_SHAREABLE
    char missionPlanId[32];
    int actionsActiveCnt;
    int actionsMaxCnt = 3; // numElements from schema
    char actionId0[32];
    char actionId1[32];
    char actionId2[32];
    char actionType0[32];
    char actionType1[32];
    char actionType2[32];
    char wayPointId0[32];
    char wayPointId1[32];
    char wayPointId2[32];
    int numberOfSensorWayPoints;
    char sensorPlanId[32];
    char vehiclePlanId[32];
    int numberOfWayPoints;
    char vehiclePlanId1[32];
    int wayPointsActiveCnt;
    int wayPointsMaxCnt = 5; // numElements from schema
    char wayPointId20[32];
    char wayPointId21[32];
    char wayPointId22[32];
    char wayPointId23[32];
    char wayPointId24[32];
    double x[wayPointsMaxCnt];
    double y[wayPointsMaxCnt];
    double z[wayPointsMaxCnt];
#pragma cle end ORANGE_SHAREABLE

    if (_local_updateMissionPlan)
        return 0;

    unmarshal_updateMissionPlan(
        jstr,
        &fromRemote,
        missionPlanId,
        &actionsActiveCnt,
        actionsMaxCnt,
        actionId0,
        actionId1,
        actionId2,
        actionType0,
        actionType1,
        actionType2,
        wayPointId0,
        wayPointId1,
        wayPointId2,
        &numberOfSensorWayPoints,
        sensorPlanId,
        vehiclePlanId,
        &numberOfWayPoints,
        vehiclePlanId1,
        &wayPointsActiveCnt,
        wayPointsMaxCnt,
        wayPointId20,
        wayPointId21,
        wayPointId22,
        wayPointId23,
        wayPointId24,
        x,
        y,
        z
    );
    if (fromRemote == 0) {
        echo_updateMissionPlan(
            missionPlanId,
            actionsActiveCnt,
            actionsMaxCnt,
            actionId0,
            actionId1,
            actionId2,
            actionType0,
            actionType1,
            actionType2,
            wayPointId0,
            wayPointId1,
            wayPointId2,
            numberOfSensorWayPoints,
            sensorPlanId,
            vehiclePlanId,
            numberOfWayPoints,
            vehiclePlanId1,
            wayPointsActiveCnt,
            wayPointsMaxCnt,
            wayPointId20,
            wayPointId21,
            wayPointId22,
            wayPointId23,
            wayPointId24,
            x,
            y,
            z
        );
    }
    return 0;
}

#define XDCCLISTEN(X) amqlib_listen(amq(), #X, egress_##X, _topic_##X);
int main() {
#pragma cle begin ORANGE_SHAREABLE
    int i = 100;
#pragma cle end ORANGE_SHAREABLE
    amq();
    MAP(XDCCLISTEN, ALL_MSGS_LIST)

    while(1) {
        sleep(i);
    }

    amqlib_destroy(amq());
    return 0; 
}
