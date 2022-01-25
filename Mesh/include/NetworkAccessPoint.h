#ifndef NETWORK_ACCESS_POINT_H
#define NETWORK_ACCESS_POINT_H

#include<memory>

#include <NetworkInfo.h>



class NetworkAccessPoint
{
public:
	virtual bool IsConnected() = 0;
	virtual void Begin(const char* ssid, const char* password) = 0;
	virtual void Config(const char* ip, const char* gateway, const char* subnet) = 0;
	virtual NetworkList GetClients() = 0;
	virtual const char* GetMAC() = 0;
	virtual ~NetworkAccessPoint() = default;
};
using NetworkAccessPointHandle = std::shared_ptr<NetworkAccessPoint>;
#endif