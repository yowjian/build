#pragma once
#ifndef MPU_H
#define MPU_H
#include <Store.h>
#include <missions/MissionPlan.h>
#include <nlohmann/json.hpp>
#include <amqm/AMQManager.h>
/**
* @brief – Class responsible for loading plans, recieving plans, generating new plans based on actions,
* 
*
* @author – Original Author - Mases Krikorian
* @author – Last Edited By - Frederick Santiago
* @date – 9/15/2020
*
* @details – When all the systems are ready, MPU will load it's default plan and send it to other systems
* This triggers the start signal for all the systems. Additionally, MPU listens to the UI for updated plans,
* and listens to MPX and/or ISRM for actions to generate new plans
*
* 
* @todo implement MPX/ISRM communications with MPU
*/
class MPU {
public:
	/**
	 * @brief Construct a new MPU object and listen for update tasking/plan
	 * 
	 */
	MPU();
	/**
	 * @brief Destroy the MPU object and clear all plan storage
	 * 
	 */
	~MPU();
	/**
	 * @brief load plan
	 * 
	 * @param VOID
	 *
	 * @return VOID
	 */
	void run();
private:
	/**
	 * @brief Send the plan to all the systems
	 * 
	 * @param j - refer to MPU/missionplans/MP-001.json for a sample
	 *
	 * @return VOID
	 */
	void sendPlan(const nlohmann::json &j);
	/**
	 * @brief New plan recieved from UI through ActiveMQ
	 * and a copy is stored in the plan manager
	 * 
	 * @param j - refer to MPU/missionplans/MP-001.json for a sample
	 *
	 * @return VOID
	 */
	void updateNewTasking(nlohmann::json j);
	/**
	 * @brief Loads the default configuration
	 *
	 * @param VOID
	 *
	 * @return VOID
	 */
	void loadDefaultConfig();
	void handleUpdateConfig(json j);
	/**
	 * @brief Loads a local mission plan json file, stores a copy of it, and
	 * sends it to all the systems.
	 *
	 * @param j - refer to MPU/missionplans/MP-001.json for a sample
	 * 
	 * @return VOID
	 */
	void loadPlan(json j);
	/**
     * @brief ActiveMQ Manager instance to listen and publish messages
     * 
    */
	amqm::AMQManager amq;
	/**
	 * @brief Pointer to the processing plan.
	 * 
	 */
	MissionPlan *plan;
	/**
	 * @brief Storage for all mission plans recieved from MPU
	 * 
	 */
	Store<MissionPlan*> planManager;
};
#endif
