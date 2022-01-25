#ifndef COMMUNICATION_CLIENT_H
#define COMMUNICATION_CLIENT_H

#include <memory>
#include <string>
#include <functional>
#include<CommunicationMessage.h>


class CommunicationClient
{
public:
	virtual bool IsConnected() = 0;
	virtual void Send(const CommunicationMessageHandle& message) = 0;
	virtual bool Start(const std::string& ip, const uint32_t port) = 0;
	virtual void Stop() = 0;
	virtual void Update() = 0;
	virtual void onDisconnected(const std::function<void()>& callback) = 0;
	virtual void onData(const std::function<void(const CommunicationMessageHandle&)>& callback) = 0;
	virtual ~CommunicationClient() = default;
};
using CommunicationClientHandle = std::shared_ptr<CommunicationClient>;
#endif