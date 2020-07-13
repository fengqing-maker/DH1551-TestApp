#ifndef FLASH_CHECK_H_
#define FLASH_CHECK_H_

#include "FlashCheckInfo.h"
#include "IndividualXMLParse.h"

class FlashCheck
{
public:
	FlashCheck();
	~FlashCheck();

public:
	int Init(FlashCheckInfo *pFlashCheckInfo);
	int SetCrcCheckInfo(XMLNode *pXMLNode);
	int SetOneCheckBlock( XMLNode *pXMLNode, CheckInfo_s *pCheckInfo, int nIndex);
	int GetFlashConfig(FlashCheckInfo *pFlashCheckInfo);
	int StartCheck(void);

private:
	unsigned int CheckOneItem(unsigned int unStartAddr, unsigned int unSize, unsigned int unCrc);
	unsigned int CalculateCRC32(unsigned char *pbData, unsigned int unLength);

private:
	FlashCheckInfo m_FlashCheckInfo;
};

#endif/*FLASH_CHECK_H_*/
