#pragma once
#ifndef MISSION_PLAN_STATUS_H
#define MISSION_PLAN_STATUS_H
#include "Mission.h"
#include "Product.h"

namespace uas {

	struct MissionPlanStatus {
		time_t time_stamp;
		Location uav_location; 
		Mission mission;
	};
}
#endif