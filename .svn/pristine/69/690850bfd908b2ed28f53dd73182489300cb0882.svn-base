#include "ListenConn.h"
#include "adi_os.h"

ListenConn::ListenConn(): APSafeThread(7*17, 64*1024, "ListenConn", strlen("ListenConn"))
{
	CleanReadBuf();

	m_unRecvFlag = 0;

	m_unRunStatus = 0;

	memset(&m_CommandData, 0, sizeof(m_CommandData));
}

ListenConn::~ListenConn()
{
	Exit ( );

	if(m_pConnInterface != NULL)
	{
		delete m_pConnInterface;
	}
}

int ListenConn::Init(int Type, char *pBuffer, int nLen, unsigned short usPort)
{
	int nRet = 0;
	
	if(E_UART_CONN == Type)
	{
		m_pConnInterface = new SerialConn();
	}
	else
	{
		m_pConnInterface = new NetworkConn(pBuffer, nLen, usPort);
	}

	if(m_pConnInterface != NULL)
	{
		nRet = 1;
	}

	return nRet;
}

void ListenConn::OnceProcess(void)
{
	if( m_unRecvFlag > 0 )
	{
		if(m_pConnInterface->IsConnON())
		{
			int nRecvLen = 0;
			
			nRecvLen = m_pConnInterface->RecvDataFrom(&m_pReadBuffer[m_unReadLen], sizeof(m_pReadBuffer) - m_unReadLen);
			if (nRecvLen > 0)
			{
				m_unReadLen += nRecvLen;

				if(sizeof(m_pReadBuffer) <= m_unReadLen)
				{
					m_unReadLen = 0;
				}
				
				PraseCommandData();
			}
		}
	}
	
	ADIOSThreadSleep(500);
}

int ListenConn::GetCommandData(CommandData *pCommandData)
{
	int nRet = 0;
	
	m_ReadBufLock.Lock();

	if (m_CommandData.m_nCommand != 0)
	{
		memcpy(pCommandData, &m_CommandData, sizeof(CommandData));

		memset(&m_CommandData, 0, sizeof(CommandData));

		nRet = 1;
	}
	
	m_ReadBufLock.UnLock();	

	return nRet;
}

int ListenConn::SendDataTo(unsigned char *pBuffer, unsigned int unLen, unsigned int unCommand)
{
	int nRet = 0;
	unsigned int unSendLen = 0;

	memset(m_pWriteBuffer, 0, sizeof(m_pWriteBuffer));
	unSendLen = m_TransportProtocol.ConstructData(pBuffer, unLen, unCommand, m_pWriteBuffer, sizeof(m_pWriteBuffer));
	if(unSendLen > 0)
	{
		if(m_pConnInterface->SendDataTo(m_pWriteBuffer, unSendLen))
		{
			nRet = 1;
		}
	}

	return nRet;
}

int ListenConn::RecvDataFrom()
{
	int nRecvLen = 0;

	nRecvLen = m_pConnInterface->RecvDataFrom(&m_pReadBuffer[m_unReadLen], sizeof(m_pReadBuffer) - m_unReadLen);

	m_unReadLen += nRecvLen;

	if(sizeof(m_pReadBuffer) <= m_unReadLen)
	{
		m_unReadLen = 0;
	}

	return nRecvLen;
}

int ListenConn::PraseCommandData(void)
{
	int nRet = 0;
	int nIndex = 0;

	m_ReadBufLock.Lock();

	for(int ii = 0; ii < m_unReadLen; ii++)
	{
		nIndex = m_TransportProtocol.PraseData(&m_pReadBuffer[ii], m_unReadLen-ii) + ii;
		if( nIndex >= ii)
		{
			memset(&m_CommandData, 0, sizeof(m_CommandData));

			m_CommandData.m_nCommand = m_pReadBuffer[nIndex + 1];
			m_CommandData.m_nDataLen = (int)((m_pReadBuffer[nIndex + 2] << 8) | m_pReadBuffer[nIndex + 3]);
			memcpy(m_CommandData.m_aucData, &m_pReadBuffer[nIndex+4], m_CommandData.m_nDataLen);

			ii = nIndex + m_CommandData.m_nDataLen + MIN_FACTORY_LEN;

			nRet = 1;
		}
	}
	
	m_ReadBufLock.UnLock();
	
	if(nRet > 0 || m_unReadLen >= sizeof(m_pReadBuffer))
	{
		CleanReadBuf();
	}

	return nIndex;
}

void ListenConn::CleanReadBuf(void)
{
	memset(m_pReadBuffer, 0, sizeof(m_pReadBuffer));

	m_unReadLen = 0;
}

int ListenConn::IsConnect(void)
{
	int nRet = 0;

	if(m_pConnInterface != NULL)
	{
		nRet = m_pConnInterface->IsConnON();
	}

	return nRet;
}

void ListenConn::SetRecvFlag(unsigned int unFlag)
{
	m_unRecvFlag = unFlag;
}

void ListenConn::SetRunStatus(unsigned int unFlag)
{
	if( unFlag == 1 )
	{
		m_unRunStatus = unFlag;

		m_unRecvFlag = unFlag;
		
		StartRun();
	}
}

unsigned int ListenConn::GetRunStatus(void)
{
	return m_unRunStatus;
}
