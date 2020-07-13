#ifndef NET_WORK_CONN_H_
#define NET_WORK_CONN_H_

#include "ConnInterface.h"
#include "APLock.h"

class NetworkConn : public ConnInterface
{
public:
	NetworkConn(char *pIP, int nLen, unsigned short usPort);
	~NetworkConn();

public:
	int StartConn(void);
	int SendDataTo(unsigned char *pBuffer, unsigned int unLen);
	int RecvDataFrom(unsigned char *pBuffer, unsigned int unLen);
	int IsConnON(void);

private:
	int IsConnectWithNet(void);
	void CloseNetSocket(void);

private:
	int m_nSocket;
	char m_acIP[32];
	unsigned short m_usPort;
	
	APLock m_ConnectLock;
};

#endif/*NET_WORK_CONN_H_*/
