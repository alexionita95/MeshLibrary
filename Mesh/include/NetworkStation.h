#ifndef NETWORK_STATION_H
#define NETWORK_STATION_H

#include<memory>
#include<functional>

#include <NetworkInfo.h>



class NetworkStation
{
public:
	virtual bool IsConnected() = 0;
	virtual void Connect(const char* ssid, const char* password,const char* mac=nullptr) = 0;
	virtual const char* GetGatewayIP() = 0;
	virtual NetworkList Scan()=0;
	virtual void onDisconnected(const std::function<void()>& callback) = 0;
	virtual ~NetworkStation() = default;
};
using NetworkStationHandle = std::shared_ptr<NetworkStation>;
#endif