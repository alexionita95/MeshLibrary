#ifndef NETWORK_INFO_H
#define NETWORK_INFO_H
#include<vector>
#include <string>
struct NetworkInfo
{
	std::string SSID;
	std::string RSID;
	std::string MAC;
};

using NetworkList = std::vector<NetworkInfo>;


#endif // !NETWORK_INFO_H
