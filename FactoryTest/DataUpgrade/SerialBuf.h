/*
 * SerialBuf.h
 *
 *  Created on: 2015-8-17
 *      Author: linc
 */

#ifndef SERIALBUF_H_
#define SERIALBUF_H_

#include "AuraTypedef.h"

class SerialBuf
{
public:
	SerialBuf();
	virtual ~SerialBuf();

public:
	void WriteLog(char * format, ...);
	void PrintAllLogInfo();
	void SetType(int nType);

private:
	int m_nType;
};

#endif /* SERIALBUF_H_ */
