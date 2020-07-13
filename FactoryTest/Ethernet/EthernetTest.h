
#ifndef ETHERNETTEST_H_
#define ETHERNETTEST_H_

#include "EthernetNotify.h"
#include "NetConfig.h"

#define ETH_NAME_LEN (32)

class EthernetTest
{
public:
	EthernetTest(EthernetNotify* pNotify);
	virtual ~EthernetTest();

public:
	void Init(NetConfig csNetConfig);
	unsigned int Start();
	unsigned int Stop();
	unsigned int TestEthernet();
	unsigned int GetIPName(char *pcIP, int nLen);
	unsigned int GetMacName(unsigned char *pucMacAddress, unsigned int unLen);
	void SetDHCPStatus(unsigned int unStatus);
	void SetConnectStatus(unsigned int unStatus);

private:
	EthernetNotify* m_pNotify;

	char m_acEthName[ETH_NAME_LEN];

	unsigned int m_DHCPStatus;

	unsigned int m_PhyConn;

	NetConfig m_NetConfig;
};

#endif /* ETHERNETTEST_H_ */
