#include<Node.h>

Node::Node() :connection{ nullptr }, server{ nullptr }, id{ 0 }, isServer{ false }, isRoot{ false }
{

}

Node::Node(const CommunicationClientHandle& conn) : connection{ conn }, server{ nullptr }, id{ 0 }, isServer{ false }, isRoot{ false }
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
		NodeHandle newNode = std::make_shared<Node>(c);
		AddClient(newNode);
		newNode->onDisconnected([this,newNode]() {

			std::remove_if(clients.begin(), clients.end(), [newNode]
			(const NodeHandle& client) {
					return client->GetId() == newNode->GetId();
				});

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
void Node::onClientData(std::function<void(const std::shared_ptr<Node>&, const CommunicationMessageHandle&)>& callback)
{
	clientDataCallback = callback;
}
void Node::onData(const std::function<void(const CommunicationMessageHandle&)>& callback)
{
	dataCallback = callback;
}
