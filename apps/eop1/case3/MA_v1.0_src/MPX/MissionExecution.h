#pragma once
#ifndef MISSION_EXECUTION_H
#define MISSION_EXECUTION_H
#include "Store.h";
#include "tsl\ordered_hash.h"
#include "missions\ProgressMatric.h"
#include "missions\Mission.h"

using namespace uas;
class MissionExecution
{
public:
	MissionExecution() {};
	~MissionExecution() {};

	//Receive current status data from MPU 
	static void onReceivingMsnProgressMsg(const std::string& msg)
	{
		//convert msg to mission 
		//executeMission(mission);
	}

	void executeMission(const uas::Mission & msn)
	{
		switch (msn.progress.kill_chain_state) {
		case uas::INGRESS:
			moveToNextWpt();
			break;
		case uas::FIND:
			collectDetects(msn);
			break;
		case uas::FIX:
			classifyObjects(msn);
			break;
		case uas::TRACK:
			tracking(msn);
			break;
		case uas::TARGET:
			targetting(msn);
			break;
		case uas::ENGRESS:
			moveToNextWpt();
			break;
		default:
			break;
		}
	}
	   	 

	//build collect detects command, send to ISRM
	void collectDetects(const Mission& mission)
	{
	}

	//build fix command, send to ISRM
	void classifyObjects(const Mission& mission)
	{
	}

	//build tracking command, send to ISRM
	void tracking(const Mission& mission)
	{
	}

	//build target command, send command to ISRM
	void targetting(const Mission& mission)
	{
	}

	//send command to VMS 
	void moveToNextWpt()
	{
	}


};
#endif