#include "SerialConn.h"
#include "adi_uart.h"
#include "string.h"

SerialConn::SerialConn()
{
}

SerialConn::~SerialConn()
{
}

int SerialConn::StartConn(void)
{
	int nRet = 0;
	
	nRet = ADIUartInitial(0, NULL);

	return nRet;
}

int SerialConn::SendDataTo(unsigned char *pBuffer, unsigned int unLen)
{
	int nActualWrite = 0;
	nActualWrite = ADIUartWrite(0, pBuffer, unLen, 1000);
	return nActualWrite;
}

int SerialConn::RecvDataFrom(unsigned char *pBuffer, unsigned int unLen)
{
	int nActualRead = 0;
	
	nActualRead = ADIUartRead(0, pBuffer, unLen, 2000);

	return nActualRead;
}

