#pragma once
#ifndef AMQ_H
#define AMQ_H
#include "MessageHandler.h"
#include <nlohmann/json.hpp>
#include <functional>
#include <unordered_map>
#include <thread>;
#include <Utils.h>
#include <mutex>
#include <atomic>
using namespace std;
using json = nlohmann::json;
namespace amqm {
	/**
	* @brief – Class responsible for handling the listen and publish functionality for each subsystem
	*
	* @author – Original Author - Mases Krikorian
	* @author – Last Edited By - Mases Krikorian
	* @date – 8/27/2020
	*
	* @details – AMQManager initializes the library in its constructor. When asked to listen on a certain channel name, it will create 
	* a thread and keep the thread running until it is told to stop listening on that thread. When data is recieved on the listened channel
	* the corresponding handler function (with a json input parameter) will be triggered, which is provided to the thread in the listen function. 
	* When asked to publish, it will create a new connection to the factory, and push the data through the given channel name.
	*/
	class AMQManager {
	public:
		/**
		 * @brief Construct a new AMQManager object and initialize the ActiveMQCPP library
		 * 
		 */
		AMQManager() {
			activemq::library::ActiveMQCPP::initializeLibrary();
		}
		/**
		 * @brief Construct a new AMQManager object and initialize the ActiveMQCPP library with a non-default broker uri
		 * 
		 */
		AMQManager(string uri) {
			this->brokerURI = uri;
			activemq::library::ActiveMQCPP::initializeLibrary();
		}
		/**
		 * @brief Construct a new AMQManager object and decide to initalize the library. Useful for 2 instances of AMQM
		 * @param init - if true, it will initialize. 
		 * 
		 */
		AMQManager(bool init) {
			if (init) {
				activemq::library::ActiveMQCPP::initializeLibrary();
			}
		}
		/**
		 * @brief Destroy the AMQManager object and stop all running listen threads.
		 * 
		 */
		~AMQManager() {
			stopAll();
		}
		/**
		 * @brief stop and kill all running listen threads
		 *
		 * @return VOID
		 */
		void stopAll() {
			for (const auto &it : running) {
				running[it.first] = false;
			}
			running.clear();
			Utils::sleep_for(100);
		}
		/**
		 * @brief listen to a specific channel (topic or queue) and trigger callback when data is recieved on that channel
		 * 
		 * @param channelName - string representation of topic or queue name 
		 * @param callback - a function referrence that takes a nlohmann::json instance as parameter
		 * @param topic - if true ActiveMQ's topic implementation will be used, otherwise ActiveMQ's queue implementation will be used
		 * 
		 * @return VOID
		*/
		void listen(string channelName, function< void(json j) > callback, bool topic) {
			const std::lock_guard<std::mutex> lock(mtx);
			if (running.find(channelName) == running.end()) {
				std::thread t1 =  std::thread(&AMQManager::startListening, this, channelName, callback, topic);
				t1.detach();
				running[channelName] = true;
			}
		}
		/**
		 * @brief stop listening to the given channel name and kill the listen thread for it
		 * 
		 * @param channelName - channel name in string (topic or queue) for the listen thread
		 *
		 * @return VOID
		 */
		void stopListening(const string& channelName) {
			const std::lock_guard<std::mutex> lock(mtx);
			const auto &it = running.find(channelName);
			if (running.find(channelName) != running.end()) {
				running[channelName] = false;
			}
		}
		/**
		 * @brief send string representation of nlohmann::json object through the provided topic or queue name
		 * 
		 * @param channelName - topic or queue name to send the data through
		 * @param data - nlohmann::json object of the data that will be sent
		 * @param topic - if true ActiveMQ's topic implementation will be used, otherwise ActiveMQ's queue implementation will be used
		 *
		 * @return VOID
		 */

		void publish(const string &channelName, json data, bool topic) {
			ActiveMQConnectionFactory *connectionFactory = new ActiveMQConnectionFactory(brokerURI);

			Connection *connection = connectionFactory->createConnection();

			connection->start();

			Session *session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
			Destination *destination;
			if (topic) {
				 destination = session->createTopic(channelName);
			}
			else {
				destination = session->createQueue(channelName);
			}
			MessageProducer *producer = producer = session->createProducer(destination);
			producer->setDeliveryMode(DeliveryMode::PERSISTENT);

			string text = (string)data.dump();
			TextMessage *message = session->createTextMessage(text);
			producer->send(message);

			delete message;
			delete destination;
			delete session;
			delete connection;
			delete connectionFactory;
			delete producer;
		}

	private:
		/**
		 * @brief if channel name does not exist in map, a new thread will be created alongside a MessageHandler instance
		 * and the process will be checked for termination every 100 ms
		 * 
		 * @param channelName - topic or queue name to send the data through 
		 * @param callback - a function referrence that takes a nlohmann::json instance as parameter 
		 * @param topic - if true ActiveMQ's topic implementation will be used, otherwise ActiveMQ's queue implementation will be used
		 *
		 * @return VOID
		 */
		void startListening(const string &channelName, function< void(json j) > callback, 
				const bool &topic) {
			MessageHandler consumer(brokerURI, channelName, callback, topic, false);
			consumer.runConsumer();
			while (running[channelName]) {
				Utils::sleep_for(100);
			}
			consumer.cleanup();
		}
		string brokerURI = "failover:(tcp://127.0.0.1:61616)";
		std::mutex mtx;
		unordered_map<string,  std::atomic<bool>>running;
	

	};
}
#endif
