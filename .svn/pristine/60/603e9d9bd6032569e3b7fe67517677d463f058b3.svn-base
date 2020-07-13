#ifndef SERIAL_CONN_H_
#define SERIAL_CONN_H_

#include "ConnInterface.h"

class SerialConn : public ConnInterface
{
public:
	SerialConn();
	~SerialConn();

public:
	int StartConn(void);
	int SendDataTo(unsigned char *pBuffer, unsigned int unLen);
	int RecvDataFrom(unsigned char *pBuffer, unsigned int unLen);	
};

#endif/*SERIAL_CONN_H_*/
