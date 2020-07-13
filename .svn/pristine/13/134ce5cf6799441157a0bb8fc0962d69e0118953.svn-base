#include "NetworkConn.h"
#include "adi_error.h"
#include "adi_socket.h"
#include "adi_net.h"
#include "string.h"
#include "stdio.h"
#include "adi_os.h"


NetworkConn::NetworkConn(char *pIP, int nLen, unsigned short usPort)
{
	m_nSocket = -1;

	memset(m_acIP, 0, sizeof(m_acIP));

	if(pIP != NULL && nLen < sizeof(m_acIP))
	{
		memcpy(m_acIP, pIP, nLen);
	}

	m_usPort = usPort;
}

NetworkConn::~NetworkConn()
{
	if(m_nSocket != -1)
	{
		ADISOCKShutDown(m_nSocket, 2);
	}
}

int NetworkConn::StartConn(void)
{
	int nRet = 0;

	m_ConnectLock.Lock();

	do
	{
		if(m_nSocket != -1)
		{
			nRet = 1;
			break;
		}
		
		m_nSocket = ADISOCKSocket(ADI_AF_INET, ADI_SOCK_STREAM, 0);
		if(m_nSocket == -1)
		{
			break;
		}
			
		ADISockAddr_IN_S  servaddr;
		memset(&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = ADI_AF_INET;
		servaddr.sin_port = ADISOCKHtons(m_usPort);
		servaddr.sin_addr.s_addr = ADISOCKInet_addr(m_acIP);

		printf("---[%s] [%d] m_usPort:%u,sin_port = 0x%x\n", __FUNCTION__, __LINE__, m_usPort, servaddr.sin_port);
		printf("---[%s] [%d] m_acIP:%s,s_addr = 0x%x\n", __FUNCTION__, __LINE__, m_acIP,servaddr.sin_addr.s_addr);
		
		if(ADISOCKConnect(m_nSocket, (ADISockAddr_S* )&servaddr, sizeof(ADISockAddr_S)) != ADI_SUCCESS)
		{
			CloseNetSocket();
			ADIOSThreadSleep(2000);
			break;
		}

		nRet = 1;
	}while(0);

	m_ConnectLock.UnLock();

	return nRet;
}

int NetworkConn::SendDataTo(unsigned char *pBuffer, unsigned int unLen)
{
	int nRet = 0;

	m_ConnectLock.Lock();
	
	if(pBuffer != NULL && unLen > 0 && m_nSocket != -1)
	{
		nRet = ADISOCKSend(m_nSocket, pBuffer, unLen, 0);
		if( nRet <= 0 )
		{
			CloseNetSocket();
			
			nRet = 0;
		}
	}

	m_ConnectLock.UnLock();

	return nRet;
}

int NetworkConn::RecvDataFrom(unsigned char *pBuffer, unsigned int unLen)
{
	int nRet = 0;

	if(pBuffer != NULL && unLen > 0)
	{
		nRet = ADISOCKRecv(m_nSocket, pBuffer, unLen, 0);
		if( nRet <= 0 )
		{
			CloseNetSocket();
			
			nRet = 0;
		}
	}

	return nRet;
}

int NetworkConn::IsConnectWithNet(void)
{
	int nRet = 0;

	if(m_nSocket == -1)
	{
		if(ADINetPing("eth0", m_acIP) == ADI_SUCCESS)
		{
			if(StartConn() > 0)
			{
				nRet = 1;
			}
		}
		else
		{
			printf("--[%s][%d]---ADINetPing fail:%s----\n", __FUNCTION__, __LINE__, m_acIP);
		}
	}
	else
	{
		nRet = 1;
	}
	
	return nRet;
}

void NetworkConn::CloseNetSocket(void)
{
	if(m_nSocket != -1)
	{
		ADISOCKClose(m_nSocket);

		m_nSocket = -1;
	}
}

int NetworkConn::IsConnON(void)
{
	return IsConnectWithNet();
}

