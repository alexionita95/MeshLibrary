#ifndef COMMUNICATION_MESSAGE_H
#define COMMUNICATION_MESSAGE_H

class CommunicationMessage
{
public:
	virtual uint32_t GetSender() = 0;
};
using CommunicationMessageHandle = std::shared_ptr<CommunicationMessage>;




#endif


