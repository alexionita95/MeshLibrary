#include<Node.h>

Node::Node() :connection{ nullptr }, server{ nullptr }, id{ 0 }, isRoot{ false }
{

}


void Node::StartClient(const CommunicationClientHandle& conn)
{
	connection->onData([this](const CommunicationMessageHandle& message)
		{
			if (dataCallback)
			{
				dataCallback(message);
			}
		});

	connection->onDisconnected([this]() {
		if (disconnectedCallback) {
			disconnectedCallback();
		}
		});


}

bool Node::HasClient(const std::shared_ptr<Node>& client)
{
	for (const auto& c : clients)
	{
		if (c->id == client->id)
			return true;
	}
	return false;
}

void Node::Broadcast(const CommunicationMessageHandle& message)
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

void Node::AddClient(const NodeHandle& client)
{
	if (!HasClient(client))
	{
		clients.push_back(client);
	}
}

void Node::StartServer(const CommunicationServerHandle& srv)
{
	server->onNewConnection([this](const CommunicationClientHandle& c) {
		NodeHandle newNode = std::make_shared<Node>();
		newNode->StartClient(c);
		AddClient(newNode);
		newNode->onDisconnected([this,newNode]() {

			clients.erase(std::remove_if(clients.begin(), clients.end(), [newNode]
			(const NodeHandle& client) {
					return client->GetId() == newNode->GetId();
				}));

			if (clientDsconnectedCallback)
			{

				clientDsconnectedCallback(newNode);
			}
			});

		newNode->onData([this, newNode](const CommunicationMessageHandle& message) {

			if (clientDataCallback)
			{
				clientDataCallback(newNode, message);
			}

			});
		if (connectedCallback)
		{
			connectedCallback(newNode);
		}
		});
}

void Node::Update()
{
	if (server != nullptr)
	{
		server->Update();
	}
	if (connection != nullptr)
	{
		connection->Update();
	}
	for (const auto& client : clients)
	{
		client->Update();
	}
}


void Node::onNewConnection(const std::function<void(const std::shared_ptr<Node>&)>& callback)
{
	connectedCallback = callback;
}
void Node::onClientDisconnected(const std::function<void(const std::shared_ptr<Node>&)>& callback)
{
	clientDsconnectedCallback = callback;
}
void Node::onDisconnected(const std::function<void()>& callback)
{
	disconnectedCallback = callback;
}
void Node::onClientData(const std::function<void(const std::shared_ptr<Node>&, const CommunicationMessageHandle&)>& callback)
{
	clientDataCallback = callback;
}
void Node::onData(const std::function<void(const CommunicationMessageHandle&)>& callback)
{
	dataCallback = callback;
}
