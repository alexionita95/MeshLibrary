#ifndef MESH_H
#define MESH_H
#include<functional>
#include<NetworkStation.h>
#include<NetworkAccessPoint.h>
#include<CommunicationMessage.h>
#include<CommunicationClient.h>
#include<CommunicationServer.h>

#include<Node.h>


enum MeshState
{
	Unconfigured,
	Disconnected,
	Connected
};

class Mesh
{
public:
	Mesh(const NetworkStationHandle& sta, const NetworkAccessPointHandle& ap, const CommunicationServerHandle& srv, const CommunicationClientHandle& clt);
	void Initialize(const char* meshN, const char* meshPw, const uint32_t port, bool iAmRoot);
	void Update();
	void Send(const CommunicationMessageHandle& message);
	void onMessage(const std::function<void(const CommunicationMessageHandle&)>& callback);

private:
	bool root;
	NetworkStationHandle station;
	NetworkAccessPointHandle accessPoint;
	CommunicationServerHandle server;
	CommunicationClientHandle client;
	NodeHandle node;
	std::string meshName;
	std::string meshPassword;
	uint32_t meshPort;
	std::function<void(const CommunicationMessageHandle&)> messageCallback;
	void Connect();
};

#endif