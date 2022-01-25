#include <Mesh.h>
#include <memory>
#include<algorithm>


#include <IPAddress.h>
Mesh::Mesh(const NetworkStationHandle& sta, const NetworkAccessPointHandle& ap, const CommunicationServerHandle& srv, const CommunicationClientHandle& clt)
	:station{ sta }, accessPoint{ ap }, server{ srv }, client{ clt }, root{ false }, node{ std::make_shared<Node>()}
{

}
void Mesh::Initialize(const char* meshN, const char* meshPw, const uint32_t port, bool iAmRoot)
{
	meshName = meshN;
	meshPassword = meshPw;
	meshPort = port;
	node->onClientData([this](const std::shared_ptr<Node>& client, const CommunicationMessageHandle& message) {

		if (messageCallback)
		{
			messageCallback(message);
		}
		});

	node->onData([this](const CommunicationMessageHandle& message) 
		{
			if (messageCallback)
			{
				messageCallback(message);
			}
		});
	root = iAmRoot;
	node->StartServer(server);
	node->StartClient(client);
	station->onDisconnected([this]() {
		
		});
	if (accessPoint != nullptr)
	{
		const char* mac = accessPoint->GetMAC();
		IPAddress ip = IPAddress::Encode(mac);
		const char* ipStr = ip.toString().c_str();
		accessPoint->Config(ipStr, ipStr, "255.255.255.0");
		accessPoint->Begin(meshName.c_str(), meshPassword.c_str());
		if (accessPoint->IsConnected() && server!=nullptr)
		{
			server->Start(ipStr, port);
		}
	}

	if (station != nullptr && station->IsConnected())
	{
		if (client != nullptr)
		{
			client->Start(std::string(station->GetGatewayIP()), port);
		}
	}

}

void Mesh::Connect()
{
	NetworkList available = station->Scan();
	available.erase(std::remove_if(available.begin(), available.end(), [this](const NetworkInfo& info) {
		return info.SSID != meshName;
		}));
	if (available.empty())
		return;

	std::sort(available.begin(), available.end(), [](const NetworkInfo& lhs, const NetworkInfo& rhs)
		{
			return lhs.RSID < rhs.RSID;
		});

	NetworkInfo best = available[0];
	station->Connect(meshName.c_str(), meshPassword.c_str(), best.MAC.c_str());
}
void Mesh::Update()
{
	if(!root)
	if (!station->IsConnected())
	{
		Connect();
	}
	node->Update();
}