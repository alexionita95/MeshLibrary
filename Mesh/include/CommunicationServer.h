#ifndef COMMUNICATION_SERVER_H
#define COMMUNICATION_SERVER_H

#include <memory>
#include <string>
#include <functional>
#include<CommunicationMessage.h>
#include <CommunicationClient.h>

class CommunicationServer
{
public:
	virtual bool IsConnected() = 0;
	virtual void Send(const CommunicationMessageHandle& message) = 0;
	virtual bool IsServer() = 0;
	virtual bool Start(const std::string& ip, const uint32_t port) = 0;
	virtual void Stop() = 0;
	virtual void onNewConnection(const std::function<void(const CommunicationClientHandle&)>& callback) = 0;
};
using CommunicationServerHandle = std::shared_ptr<CommunicationServer>;


#endif // !COMMUNICATION_SERVER_H