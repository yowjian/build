#ifndef MISSION_H
#define MISSION_H
#include "CommonUAS.h"
#include "Objective.h"
#include "Resource.h"
#include "ProgressMatric.h"
#include <vector>
namespace uas {


	enum MissionType {
		ISR,
		CAS,
		STRIKE
	};

	struct Mission {
		UID mission_id;
		MissionType msn_type;
		Area battle_field;
		ProgressMatric progress;
		std::vector<Objective> objects;
		std::vector<Resource>  resources;
	};

}
#endif