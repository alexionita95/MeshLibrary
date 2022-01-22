#ifndef NODE_H
#define NODE_H

#include<memory>
#include<vector>
#include<cinttypes>
#include<functional>
#include<CommunicationMessage.h>
#include<CommunicationClient.h>
#include<CommunicationServer.h>
class Node
{
public:
	Node();
	Node(const CommunicationClientHandle& conn);
	void AddClient(const std::shared_ptr<Node>& client);
	bool Connected()
	{
		if (connection == nullptr)
			return false;
		return connection->IsConnected();
	}
	uint32_t GetId()
	{
		return id;
	}
	bool HasClient(const std::shared_ptr<Node>& client)
	{
		for (const auto& c : clients)
		{
			if (c->id == client->id)
				return true;
		}
		return false;
	}

	void Broadcast(const CommunicationMessageHandle& message)
	{
		connection->Send(message);

		for (const auto& client : clients)
		{
			if (client->GetId() != message->GetSender())
			{
				client->Broadcast(message);
			}
		}

	}

	void StartServer(const CommunicationServerHandle& srv);

	void onNewConnection(const std::function<void(const std::shared_ptr<Node>&)>& callback);
	void onClientDisconnected(const std::function<void(const std::shared_ptr<Node>&)>& callback);
	void onClientData(std::function<void(const std::shared_ptr<Node>&, const CommunicationMessageHandle&)>& callback);
	void onData(const std::function<void(const CommunicationMessageHandle&)>& callback);
	void onDisconnected(const std::function<void()>& callback);
	

private:
	CommunicationClientHandle connection;
	CommunicationServerHandle server;
	uint32_t id;
	std::shared_ptr<Node> parent;
	std::vector<std::shared_ptr<Node>> clients;
	bool isServer;
	bool isRoot;

	std::function<void(const std::shared_ptr<Node>&)> connectedCallback;
	std::function<void()> disconnectedCallback;
	std::function<void(const std::shared_ptr<Node>&)> clientDsconnectedCallback;
	std::function<void(const CommunicationMessageHandle&)> dataCallback;
	std::function<void(const std::shared_ptr<Node>&, const CommunicationMessageHandle&)> clientDataCallback;
};
using NodeHandle = std::shared_ptr<Node>;
#endif