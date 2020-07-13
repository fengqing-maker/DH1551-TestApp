#ifndef CONN_INTERFACE_H_
#define CONN_INTERFACE_H_

class ConnInterface
{
public:
	ConnInterface();
	virtual ~ConnInterface();

public:
	virtual int StartConn(void) = 0;
	virtual int SendDataTo(unsigned char *pBuffer, unsigned int unLen) = 0;
	virtual int RecvDataFrom(unsigned char *pBuffer, unsigned int unLen) = 0;
	virtual int IsConnON(void);
};

#endif/*CONN_INTERFACE_H_*/
