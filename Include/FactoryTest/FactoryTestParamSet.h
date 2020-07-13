#ifndef FACTORY_TEST_PARAM_SET_H_
#define FACTORY_TEST_PARAM_SET_H_

#include "BaseTestItem.h"
#include "AVConfig.h"
#include "USBConfig.h"
#include "NetConfig.h"
#include "SMCConfig.h"
#include "FPConfig.h"
#include "SNConfig.h"
#include "OTAConfig.h"
#include "IndividualXMLParse.h"

class FactoryTestParamSet
{
public:
	FactoryTestParamSet();
	~FactoryTestParamSet();
	
public:
	int SetAllConfig(XMLNode *pXMLNode);
	int GetBaseConfig(BaseTestItem *pBaseTestItem);
	int GetAVConfig(AVConfig *pAVConfig);
	int GetUSBConfig(USBConfig *pUSBConfig);
	int GetNETConfig(NetConfig *pNetConfig);
	int GetSMCConfig(SMCConfig *pSMCConfig);
	int GetFPConfig(FPConfig *pFPConfig);
	int GetSNConfig(SNConfig *pSNConfig);
	int GetOTAConfig(OTAConfig *pOTAConfig);
	void SetDefaultConfig(void);

private:
	int SetBaseConfig(XMLNode *pXMLNode);
	int SetAVConfig(XMLNode *pXMLNode, int nFlag);
	int SetUSBConfig(XMLNode *pXMLNode, int nFlag);
	int SetNETConfig(XMLNode *pXMLNode, int nFlag);
	int SetSMCConfig(XMLNode *pXMLNode, int nFlag);
	int SetFPConfig(XMLNode *pXMLNode, int nFlag);
	int SetSNConfig(XMLNode *pXMLNode, int nFlag);
	int SetOTAConfig(XMLNode *pXMLNode, int nFlag);
	int SetDVBType(char *pBuffer, int nLen, unsigned int & unDeliveryType);
	int SetDeliveryParam(XMLNode *pXMLNode, ADITunerSRCDeliver_U *pDelivery, unsigned int unDVBType, int nIndex);
	int SetDVBCDelivery(XMLNode *pXMLNode, ADITunerSRCDeliver_U *pDelivery, int nIndex);
	int SetDVBSDelivery(XMLNode *pXMLNode, ADITunerSRCDeliver_U *pDelivery, int nIndex);
	int SetDVBTDelivery(XMLNode *pXMLNode, ADITunerSRCDeliver_U *pDelivery, int nIndex);
	int SetCACoreAddr(XMLNode *pXMLNode);
	int SetCAOneCoreAddr(XMLNode *pXMLNode, CoreDataInfo *pCoreDataInfo, int nIndex);
	int SetCAOneCoreSegAddr(XMLNode *pXMLNode, SegInfo *pSegInfo, int nIndex);
	int SetServiceListParam(XMLNode *pXMLNode);
	int SetTunerListPara(XMLNode *pXMLNode);
private:
	BaseTestItem m_BaseTestItem;
	AVConfig m_AVConfig;
	USBConfig m_USBConfig;
	NetConfig m_NetConfig;
	SMCConfig m_SMCConfig;
	FPConfig m_FPConfig;
	SNConfig m_SNConfig;
	OTAConfig m_OTAConfig;
};

#endif/*FACTORY_TEST_PARAM_SET_H_*/
