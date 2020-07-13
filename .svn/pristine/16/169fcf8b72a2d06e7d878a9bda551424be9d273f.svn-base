#ifndef OTA_CONFIG_H_
#define OTA_CONFIG_H_

#include "adi_tuner.h"

#define IRDETOCCA_CORE_AND_CFG_COUNT 11
#define MAXSEGINFOCOUNT     ( 5 )

typedef struct
{
	unsigned int unSegAddr;
	unsigned int unSegSize;
}SegInfo;

typedef struct
{
	unsigned int unDataSize;
	unsigned int unSegCount;

	SegInfo saSegInfo[MAXSEGINFOCOUNT];
}CoreDataInfo;

class OTAConfig
{
public:
	void SetDefaultConfig(void);
	
public:
	ADITunerSRCDeliver_U m_stOTADelivery;
	unsigned int m_unHLType;
	unsigned int m_unMarkIDFlag;
	unsigned int m_usOTAPid;
	unsigned int m_ucOTATableId;
	unsigned int m_unOTAType;

	int m_nBoot;
	int m_nCW;
	int m_nJTag;

	unsigned int m_unCAAddr;
	unsigned int m_unCASize;

	unsigned int m_unManuF;
	unsigned int m_unHW;
	unsigned int m_unVT;

	int m_CoreFlag;
	CoreDataInfo m_CoreDataInfo[IRDETOCCA_CORE_AND_CFG_COUNT];

	unsigned int m_unCoreFileAddr;
	unsigned int m_unCoreFileBackupAddr;
	unsigned int m_unCoreFileSize;

	unsigned int m_unCFGFileAddr;
	unsigned int m_unCFGFileBackAddr;
	unsigned int m_unCFGFileSize;
};

#endif/*OTA_CONFIG_H_*/