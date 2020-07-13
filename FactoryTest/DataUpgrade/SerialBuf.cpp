/*
 * SerialBuf.cpp
 *
 *  Created on: 2015-8-17
 *      Author: linc
 */

#include "SerialBuf.h"
#include "stdio.h"
#include "string.h"
#include "stdarg.h"

#define CRC_FLAG (0xEDB88320) 

#define DEBUG_MODE
#ifdef DEBUG_MODE
#define MAX_LOG_COUNT 1024
BYTE g_LogInfo[MAX_LOG_COUNT][1024] = { 0 };
unsigned int g_unCount = 0;
#endif

SerialBuf::SerialBuf()
{
	m_nType = 0;
}

SerialBuf::~SerialBuf()
{
}

void SerialBuf::WriteLog(char * format, ...)
{
#ifdef DEBUG_MODE
	va_list args;

	if (g_unCount >= MAX_LOG_COUNT)
	{
		return;
	}

	va_start(args, format);
	vsprintf((char *)&g_LogInfo[g_unCount], format, args);
	va_end(args);

	g_unCount++;

	if(m_nType)
	{
		PrintAllLogInfo();
	}
#endif	
}

void SerialBuf::PrintAllLogInfo()
{
#ifdef DEBUG_MODE
	unsigned int ii = 0;

	printf("[%s][%d]g_unCount=%d\n", __FUNCTION__, __LINE__, g_unCount);
	for (ii = 0; ii < g_unCount; ii++)
	{
		printf("%s", &g_LogInfo[ii]);
		memset(&g_LogInfo[ii], 0, sizeof(g_LogInfo[ii]));
	}
	g_unCount = 0;
#endif
}

void SerialBuf::SetType(int nType)
{
	m_nType = nType;
}
