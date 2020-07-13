#include "APPFlashWrite.h"

#include <string.h>
#include "adi_flash.h"
#include "STBDataInterface.h"
APPFlashWrite::APPFlashWrite()
{
	m_ADDR = 0;
	m_pData = NULL;
	m_DataLen = 0;
	m_CurrentCount = 0;
	m_LastCount = 0;
}

APPFlashWrite::~APPFlashWrite()
{
	delete m_pData;
}
void APPFlashWrite::SetADDR(unsigned int unADDR)
{
	m_ADDR = unADDR;
}
void APPFlashWrite::SetAPPDataLength(unsigned int unAPPDataLength)
{
	m_APPDataLength = unAPPDataLength;
}
unsigned int APPFlashWrite::HandleTheReceiveData(unsigned char *pucCommandData, unsigned int unCommandDataLen)
{
	unsigned int CurrentCount = 0;
	unsigned int LastCount = 0;
	unsigned int unRcvDataLen = 0;
	unsigned char ucRcvBuffer[MAX_SERIAL_SIZE + 6] = { 0 };

	memcpy(ucRcvBuffer, pucCommandData, unCommandDataLen);
	CurrentCount = (ucRcvBuffer[0] << 8) | ucRcvBuffer[1];
	LastCount = (ucRcvBuffer[2] << 8) | ucRcvBuffer[3];
	unRcvDataLen = (ucRcvBuffer[4] << 8) | ucRcvBuffer[5];

	if (CurrentCount <= m_CurrentCount)
	{
		return 0;
	}
	m_CurrentCount = CurrentCount;
	m_LastCount = LastCount;

	return SetData(ucRcvBuffer + 6, unRcvDataLen);
}
void APPFlashWrite::SetCurrentCount(unsigned int unCurrenCount)
{
	m_CurrentCount = unCurrenCount;
}
unsigned int APPFlashWrite::GetCurrentCount(void)
{
	return m_CurrentCount;
}
void APPFlashWrite::SetLastCount(unsigned int unLastCount)
{
	m_LastCount = unLastCount;
}
unsigned int APPFlashWrite::GetLastCount(void)
{
	return m_LastCount;
}
unsigned int APPFlashWrite::SetData(unsigned char *pucData, unsigned int unDataLen)
{
	if (m_pData == NULL)
	{
		m_pData = new unsigned char[m_APPDataLength];
		if (m_pData == NULL)
		{
			return -1;
		}
	}
	memcpy(m_pData + m_DataLen, pucData, unDataLen);
	m_DataLen += unDataLen;

	return 1;
}
unsigned int APPFlashWrite::IsDataReceiveOver()
{
	return ((m_CurrentCount == m_LastCount) && (m_LastCount > 0))? 1 : 0;
}
unsigned int APPFlashWrite::WriteDataToFlash()
{
	return ADIFlashWrite(m_ADDR,m_pData,m_DataLen);
}