#ifndef FLASH_CHECK_INFO_H_
#define FLASH_CHECK_INFO_H_

#include <vector>

using namespace std;

typedef struct
{
	unsigned int m_unStartAddr;
	unsigned int m_unFlashSize;
	unsigned int m_unOriCrc;
}CheckInfo_s;


class FlashCheckInfo
{
public:
	FlashCheckInfo();
	~FlashCheckInfo();

public:
	void SetDefaultConfig();
	
public:
	int m_nCheckFlag;
	int m_nCheckCount;
	vector<CheckInfo_s> m_vtCheck;
};

#endif/*FLASH_CHECK_INFO_H_*/
