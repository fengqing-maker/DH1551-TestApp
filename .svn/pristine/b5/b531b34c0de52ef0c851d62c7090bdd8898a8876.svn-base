
#include "APAssert.h"
#include "EthernetTest.h"
#include "adi_os.h"
#include "adi_net.h"
#include "adi_toolset.h"
#include "string.h"

static void NetCallBack(ADINetLANEventType_E eEventType,char * pcEthName,void * pvUserData);

EthernetTest::EthernetTest(EthernetNotify* pNotify) : m_pNotify(pNotify)
{
	m_DHCPStatus = 0;

	m_PhyConn = 0;

	memset(m_acEthName, 0, sizeof(m_acEthName));

	memcpy(m_acEthName, "eth0", strlen("eth0"));
}

EthernetTest::~EthernetTest()
{
	ADINetDelLanCallback( NetCallBack, this );
}

void EthernetTest::Init(NetConfig csNetConfig)
{
	memcpy(&m_NetConfig, &csNetConfig, sizeof(NetConfig));
	
	ADINetAddLanCallback( NetCallBack, this );

	ADINetDHCPON(m_acEthName);
}

unsigned int EthernetTest::Start()
{
	unsigned int unRet = 0;

	if(m_DHCPStatus == 0)
	{
		if(ADINetDHCPON(m_acEthName) == ADI_SUCCESS)
		{
			unRet = 1;
		}
	}
	else if(m_DHCPStatus == 1)
	{
		unRet = TestEthernet();
	}
	
	if(unRet == 0)
	{
		m_pNotify->EthernetNotReadyNotify();
	}
	
	printf("\n--End EthernetTest!-unRet:%d-\n", unRet);

	return unRet;
}

unsigned int EthernetTest::Stop()
{
	unsigned int unRet = 1;

	unRet = ADINetDelLanCallback( NetCallBack, this );

	return unRet;
}

unsigned int EthernetTest::TestEthernet()
{
	unsigned int unRet = 0;
	char acIP[32] = {0};
	int nCount = 0;
	ADI_Error_Code errCode = ADI_FAILURE;

	while (nCount < 3)
	{
		errCode = ADINetGetGateWay(m_acEthName, acIP);
		if(m_PhyConn == 1 && errCode == ADI_SUCCESS)
		{
			if(ADINetPing(m_acEthName, acIP) == ADI_SUCCESS)
			{
				unRet = 1;
				
				m_pNotify->EthernetReadyNotify();

				break;
			}
			else
			{
				printf("\n--Ping Gateway IP erorr:%s!--\n", acIP);
			}
		}
		else
		{
			printf("\n--Get Gateway IP erorr! m_PhyConn=%d errCode=%d--\n", m_PhyConn, errCode);
		}

		nCount++;

		ADIOSThreadSleep(500);
	}
	
	if(unRet == 0)
	{
		m_pNotify->EthernetNotReadyNotify();
	}

	return unRet;
}

unsigned int EthernetTest::GetIPName(char *pcIP, int nLen)
{
	unsigned int unRet = 1;
	
	if(pcIP != NULL && nLen > 0)
	{
		unRet = ADINetGetIp( m_acEthName, pcIP );
	}
	
	return unRet;
}

unsigned int EthernetTest::GetMacName(unsigned char *pucMacAddress, unsigned int unLen)
{
	unsigned int unRet = 1;

	if(pucMacAddress != NULL && unLen > 0)
	{
		unRet = ADINetGetMacByName( m_acEthName, pucMacAddress );
	}
	
	return unRet;
}

void EthernetTest::SetDHCPStatus(unsigned int unStatus)
{
	m_DHCPStatus = unStatus;
}

void EthernetTest::SetConnectStatus(unsigned int unStatus)
{
	m_PhyConn = unStatus;
}

static void NetCallBack(ADINetLANEventType_E eEventType,char * pcEthName,void * pvUserData)
{
	EthernetTest *pEthernetTest = (EthernetTest *)pvUserData;
	
	switch( eEventType )
	{
		case EM_ADILAN_DHCP_SUCCESS:
		{
			pEthernetTest->SetDHCPStatus(1);
			pEthernetTest->SetConnectStatus(1);
			pEthernetTest->TestEthernet();
			printf("--[%s][%d]---DHCP_SUCCESS---\n", __FUNCTION__, __LINE__);
		}
			break;

		case EM_ADILAN_DHCP_FAILED:
		{
			pEthernetTest->SetDHCPStatus(0);
			printf("--[%s][%d]---DHCP_FAILED---\n", __FUNCTION__, __LINE__);
		}
			break;

		case EM_ADILAN_PHY_CONNECT:
		{
			pEthernetTest->SetConnectStatus(1);
			pEthernetTest->Start();
			printf("--[%s][%d]---PHY_CONNECT---\n", __FUNCTION__, __LINE__);
		}
			break;

		case EM_ADILAN_PHY_DISCONNECT:
		{
			pEthernetTest->SetConnectStatus(0);
			pEthernetTest->SetDHCPStatus(0);
			printf("--[%s][%d]---PHY_DISCONNECT---\n", __FUNCTION__, __LINE__);
		}
			break;

		default:
			break;
	}
}

