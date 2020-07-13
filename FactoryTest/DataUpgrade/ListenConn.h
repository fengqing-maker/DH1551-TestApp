#ifndef LISTEN_CONN_H_
#define LISTEN_CONN_H_

#include "APSafeThread.h"
#include "APLock.h"
#include "CommandData.h"
#include "TransportProtocol.h"
#include "../LinkInterface/NetworkConn.h"
#include "../LinkInterface/SerialConn.h"
#include "SerialBuf.h"
#include "SNConfig.h"

#define MAX_BUF_LEN		(16*1024)

class ListenConn : public APSafeThread
{
public:
	ListenConn();
	~ListenConn();

public:
	void OnceProcess(void);
	int Init(int Type, char *pBuffer, int nLen, unsigned short usPort);
	int GetCommandData(CommandData *pCommandData);
	int SendDataTo(unsigned char *pBuffer, unsigned int unLen, unsigned int unCommand);
	void CleanReadBuf(void);
	int IsConnect(void);
	void SetRecvFlag(unsigned int unFlag);
	void SetRunStatus(unsigned int unFlag);
	unsigned int GetRunStatus(void);
	int RecvDataFrom();

private:
	int PraseCommandData(void);

private:
	unsigned int m_unRunStatus;
	unsigned int m_unRecvFlag;
	CommandData m_CommandData;
	TransportProtocol m_TransportProtocol;

	ConnInterface *m_pConnInterface;

	BYTE m_pReadBuffer[MAX_BUF_LEN];
	unsigned int m_unReadLen;
	BYTE m_pWriteBuffer[MAX_BUF_LEN];

	APLock m_ReadBufLock;
};

#endif/*LISTEN_CONN_H_*/
