#ifndef IP_ADDRESS_H
#define IP_ADDRESS_H
#include<cinttypes>
#include<string>
#include<sstream>
class IPAddress
{
private:
	uint8_t data[4]={ 0,0,0,0 };
public:
	IPAddress() 
	{
	}

	IPAddress(const std::string& ip)
	{
		int index = 0;
		std::istringstream stream(ip);
		std::string current;
		while (std::getline(stream, current, '.'))
		{
			data[index++] = atoi(current.c_str());
		}
	}

	IPAddress(const char* ip)
	{
		int index = 0;
		std::istringstream stream(ip);
		std::string current;
		while (std::getline(stream, current, '.'))
		{
			data[index++] = atoi(current.c_str());
		}
	}

	IPAddress(const uint8_t ip[4])
	{
		data[0] = ip[0];
		data[1] = ip[1];
		data[2] = ip[2];
		data[3] = ip[3];
	}

	IPAddress(const uint8_t ip1,const uint8_t ip2, const uint8_t ip3, const uint8_t ip4)
	{
		data[0] = ip1;
		data[1] = ip2;
		data[2] = ip3;
		data[3] = ip4;
	}

	const std::string toString()
	{
		return std::to_string(data[0]) + "." + std::to_string(data[1]) + "." + std::to_string(data[2]) + "." + std::to_string(data[3]);
	}
	const uint8_t* getData() const
	{
		return data;
	}

	static IPAddress Encode(const char* mac)
	{
		uint32_t value = 0;

		value |= mac[2] << 24;
		value |= mac[3] << 16;
		value |= mac[4] << 8;
		value |= mac[5];

		return IPAddress(10, (value & 0xFF00) >> 8, value & 0xFF, 1);

	}
};

#endif