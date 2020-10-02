#pragma once
#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include <string>
#include <fstream>
#include <decaf/lang/Thread.h>
#include <decaf/lang/Runnable.h>
#include <decaf/util/concurrent/CountDownLatch.h>
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/core/ActiveMQConnection.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/library/ActiveMQCPP.h>
#include <decaf/lang/Integer.h>
#include <activemq/util/Config.h>
#include <decaf/util/Date.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <cms/BytesMessage.h>
#include <cms/MapMessage.h>
#include <cms/ExceptionListener.h>
#include <cms/MessageListener.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <functional>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf::lang;
using namespace decaf::util;
using namespace decaf::util::concurrent;
using namespace cms;
using namespace std;
using json = nlohmann::json;
namespace amqm {
	class MessageHandler : public ExceptionListener,
		public MessageListener,
		public DefaultTransportListener {
	private:

		Connection* connection;
		Session* session;
		Destination* destination;
		MessageConsumer* consumer;
		bool useTopic;
		bool clientAck;
		std::string brokerURI;
		std::string destURI;
                std::string name;
		function< void(json j) > callback;

	public:

		MessageHandler(const std::string& brokerURI,
			const std::string& destURI, function< void(json j) > callback,
                               const std::string& name,
			bool useTopic = false,
                               bool clientAck = false) {
			this->connection = NULL;
			this->session = NULL;
			this->destination = NULL;
			this->consumer = NULL;
			this->useTopic = useTopic;
			this->brokerURI = brokerURI;
			this->destURI = destURI;
			this->clientAck = clientAck;
			this->callback = callback;
                        this->name = name;
		}

		virtual ~MessageHandler() {
			this->cleanup();
		}

		void close() {
			this->cleanup();
		}

		void runConsumer() {

			try {

				ActiveMQConnectionFactory* connectionFactory =
					new ActiveMQConnectionFactory(brokerURI);

				connection = connectionFactory->createConnection();
				delete connectionFactory;

				ActiveMQConnection* amqConnection = dynamic_cast<ActiveMQConnection*>(connection);
				if (amqConnection != NULL) {
					amqConnection->addTransportListener(this);
				}

				connection->start();

				connection->setExceptionListener(this);

				
				if (clientAck) {
					session = connection->createSession(Session::CLIENT_ACKNOWLEDGE);
				}
				else {
					session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
				}

				
				if (useTopic) {
					destination = session->createTopic(destURI);
				}
				else {
					destination = session->createQueue(destURI);
				}

				consumer = session->createConsumer(destination);
				consumer->setMessageListener(this);

			}
			catch (CMSException& e) {
				e.printStackTrace();
			}
		}

		virtual void onMessage(const Message* message) {
			static int count = 0;
			try
			{
				count++;
				const TextMessage* textMessage =
					dynamic_cast<const TextMessage*>(message);
				string text = "";

				if (textMessage != NULL) {
					text = textMessage->getText();
				}
				else {
					text = "NOT A TEXTMESSAGE!";
				}

				if (clientAck) {
					message->acknowledge();
				}

				json j = json::parse(text);
				callback(j);
			}
			catch (CMSException& e) {
				e.printStackTrace();
			}
		}

		virtual void onException(const CMSException& ex AMQCPP_UNUSED) {
		
			exit(1);
		}

		virtual void transportInterrupted() {
		}

		virtual void transportResumed() {
			
		}


		void cleanup() {
			try {
				if (destination != NULL) delete destination;
			}
			catch (CMSException& e) {}
			destination = NULL;

			try {
				if (consumer != NULL) delete consumer;
			}
			catch (CMSException& e) {}
			consumer = NULL;

			// Close open resources.
			try {
				if (session != NULL) session->close();
				if (connection != NULL) connection->close();
			}
			catch (CMSException& e) {}

			// Now Destroy them
			try {
				if (session != NULL) delete session;
			}
			catch (CMSException& e) {}
			session = NULL;

			try {
				if (connection != NULL) delete connection;
			}
			catch (CMSException& e) {}
			connection = NULL;
		}
	};
}

#endif
