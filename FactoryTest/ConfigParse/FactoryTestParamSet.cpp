#include "FactoryTestParamSet.h"
#include "FactoryTestKey.h"

FactoryTestParamSet::FactoryTestParamSet()
{
	memset(&m_BaseTestItem, 0, sizeof(BaseTestItem));
	memset(&m_AVConfig, 0, sizeof(AVConfig));
	memset(&m_SNConfig, 0, sizeof(SNConfig));
	memset(&m_OTAConfig, 0, sizeof(OTAConfig));
}

FactoryTestParamSet::~FactoryTestParamSet()
{
}

void FactoryTestParamSet::SetDefaultConfig(void)
{
	m_BaseTestItem.SetDefaultConfig();
	m_AVConfig.SetDefaultConfig();
	m_USBConfig.SetDefaultConfig();
	m_NetConfig.SetDefaultConfig();
	m_SMCConfig.SetDefaultConfig();
	m_FPConfig.SetDefaultConfig();
	m_SNConfig.SetDefaultConfig();
	m_OTAConfig.SetDefaultConfig();
}

int FactoryTestParamSet::GetBaseConfig(BaseTestItem *pBaseTestItem)
{
	memcpy(pBaseTestItem, &m_BaseTestItem, sizeof(BaseTestItem));

	return 1;
}

int FactoryTestParamSet::GetAVConfig(AVConfig *pAVConfig)
{
	memcpy(pAVConfig, &m_AVConfig, sizeof(AVConfig));

	return 1;
}

int FactoryTestParamSet::GetUSBConfig(USBConfig *pUSBConfig)
{
	memcpy(pUSBConfig, &m_USBConfig, sizeof(USBConfig));

	return 1;
}

int FactoryTestParamSet::GetNETConfig(NetConfig *pNetConfig)
{
	memcpy(pNetConfig, &m_NetConfig, sizeof(NetConfig));

	return 1;
}

int FactoryTestParamSet::GetSMCConfig(SMCConfig *pSMCConfig)
{
	memcpy(pSMCConfig, &m_SMCConfig, sizeof(SMCConfig));

	return 1;
}

int FactoryTestParamSet::GetFPConfig(FPConfig *pFPConfig)
{
	memcpy(pFPConfig, &m_FPConfig, sizeof(FPConfig));

	return 1;
}

int FactoryTestParamSet::GetSNConfig(SNConfig *pSNConfig)
{
	memcpy(pSNConfig, &m_SNConfig, sizeof(SNConfig));

	return 1;
}

int FactoryTestParamSet::GetOTAConfig(OTAConfig *pOTAConfig)
{
	memcpy(pOTAConfig, &m_OTAConfig, sizeof(OTAConfig));

	return 1;
}

int FactoryTestParamSet::SetAllConfig(XMLNode *pXMLNode)
{
	int nRet = 1;

	if (pXMLNode->IsSameTag("FACTORYTEST", strlen("FACTORYTEST")))
	{
		nRet &= SetBaseConfig(pXMLNode);
		nRet &= SetAVConfig(pXMLNode, m_BaseTestItem.m_nAV);
		nRet &= SetUSBConfig(pXMLNode, m_BaseTestItem.m_nUSB);
		nRet &= SetNETConfig(pXMLNode, m_BaseTestItem.m_nNet);
		nRet &= SetSMCConfig(pXMLNode, m_BaseTestItem.m_nSMC);
		nRet &= SetFPConfig(pXMLNode, m_BaseTestItem.m_nFP);
		nRet &= SetSNConfig(pXMLNode, m_BaseTestItem.m_nSN);
		nRet &= SetOTAConfig(pXMLNode, m_BaseTestItem.m_nOTA);
	}
	else
	{
		nRet = 0;
	}

	return nRet;
}

int FactoryTestParamSet::SetBaseConfig(XMLNode *pXMLNode)
{
	int nRet = 0;

	char acDVBType[32] = { 0 };

	XMLNode *pTemp = pXMLNode->GetXMLNode("BASEITEM", strlen("BASEITEM"));
	
	if (pTemp != NULL)
	{
		nRet = 1;
		nRet &= pTemp->GetValue("PRPJECT", strlen("PRPJECT"), m_BaseTestItem.m_acProjectName, sizeof(m_BaseTestItem.m_acProjectName));
		nRet &= pTemp->GetValue("STATUSADDR", strlen("STATUSADDR"), (int*)&m_BaseTestItem.m_unResultAddr);
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nS22K, "S_22K", strlen("S_22K"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nDis, "COLOR_MODE", strlen("COLOR_MODE"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nASP, "ASPECT_RATIO", strlen("ASPECT_RATIO"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nST, "TUNER_SV", strlen("TUNER_SV"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nTT, "TUNER_TV", strlen("TUNER_TV"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nCR, "READ_CARD", strlen("READ_CARD"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nIR, "EX_IR", strlen("EX_IR"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nAV, "AVTEST", strlen("AVTEST"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nUSB, "USBTEST", strlen("USBTEST"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nNet, "NETTEST", strlen("NETTEST"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nSMC, "SMCTEST", strlen("SMCTEST"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nFP, "FPTEST", strlen("FPTEST"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nSN, "WRITETEST", strlen("WRITETEST"));
		nRet &= pTemp->GetValue(&m_BaseTestItem.m_nOTA, "OTATEST", strlen("OTATEST"));
	}

	return nRet;
}

int FactoryTestParamSet::SetDVBType(char *pBuffer, int nLen, unsigned int & unDeliveryType)
{
	int nRet = 1;

	if (memcmp(pBuffer, "DVB-C", strlen("DVB-C")) == 0)
	{
		unDeliveryType = DELIVERY_C;
	}
	else if (memcmp(pBuffer, "DVB-S", strlen("DVB-S")) == 0)
	{
		unDeliveryType = DELIVERY_S;
	}
	else if (memcmp(pBuffer, "DVB-T", strlen("DVB-T")) == 0)
	{
		unDeliveryType = DELIVERY_T;
	}
	else
	{
		nRet = 0;
	}

	return nRet;
}

int FactoryTestParamSet::SetAVConfig(XMLNode *pXMLNode, int nFlag)
{
	int nRet = 1;

	if (nFlag != 0)
	{
		XMLNode *pTemp = pXMLNode->GetXMLNode("AV", strlen("AV"));

		if (pTemp != NULL)
		{
			nRet &= pTemp->GetValue("TUNERCOUNT", strlen("TUNERCOUNT"), &m_AVConfig.m_nTunerCount);
			nRet &= SetTunerListPara(pTemp);
			nRet &= SetServiceListParam(pTemp);
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetTunerListPara(XMLNode *pXMLNode)
{
	int nRet = 0;
	XMLNode *pTunerXML = NULL;
	nRet = 1;
	for (int i = 0; i < m_AVConfig.m_nTunerCount && nRet == 1; i++)
	{
		int nDeliveryCount = 0;
		char key[32] = { 0 };
		char acTunerType[32] = { 0 };
		TunerInfo_S *pTuner = new TunerInfo_S();

		pTunerXML = NULL;
		memset(pTuner, 0, sizeof(pTuner));
		memset(key, 0, sizeof(key));
		memset(acTunerType, 0, sizeof(acTunerType));
		//Tuner
		sprintf(key, "TUNER%d", i + 1);
		pTunerXML = pXMLNode->GetXMLNode(key, strlen(key));
		if(pTunerXML != NULL)
		{
			nRet &= pTunerXML->GetValue("TUNERTYPE", strlen("TUNERTYPE"), acTunerType, sizeof(acTunerType));
			nRet &= SetDVBType(acTunerType, strlen(acTunerType), pTuner->m_nTunerType);
			//Delivery
			pTunerXML->GetValue("DELIVERYCOUNT", strlen("DELIVERYCOUNT"), &nDeliveryCount);
			for (int i = 0; i < nDeliveryCount && nRet == 1; i++)
			{
				ADITunerSRCDeliver_U *pDelivery = new ADITunerSRCDeliver_U();
				memset(pDelivery, 0, sizeof(ADITunerSRCDeliver_U));
				nRet &= SetDeliveryParam(pTunerXML, pDelivery, pTuner->m_nTunerType, i);
				printf("freq = %d\n", pDelivery->m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFrequency);
				pTuner->m_vDeliveryList.push_back(pDelivery);
			}
			m_AVConfig.m_vTuner_List.push_back(pTuner);
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}
int FactoryTestParamSet::SetServiceListParam(XMLNode *pXMLNode)
{
	int nRet = 0;
	int nServiceCount = 0;
	XMLNode *pTemp = NULL;

	pTemp = pXMLNode->GetXMLNode("SERVICELIST", strlen("SERVICELIST"));
	if (pTemp != NULL)
	{
		nRet = 1;	
		char key[32] = { 0 };
		XMLNode *pServiceXML = NULL;
		nRet &= pXMLNode->GetValue("SERVICECOUNT", strlen("SERVICECOUNT"), &nServiceCount);
		printf("nServiceCount = %d\n", nServiceCount);
		for (int i = 0; i < nServiceCount && nRet == 1; i++)
		{
			pServiceXML = NULL;
			memset(key, 0, sizeof(key));
			sprintf(key, "SERVICE%d", i+1);
			pServiceXML = pTemp->GetXMLNode(key, strlen(key));
			if (pServiceXML == NULL)
			{
				printf("pServiceXML fail\n");
				break;
			}
			ServiceInfo_S *pService = new ServiceInfo_S();
			nRet &= pServiceXML->GetValue("VIDPID", strlen("VIDPID"), &(pService->m_nVideoPid));
			nRet &= pServiceXML->GetValue("AUDPID", strlen("AUDPID"), &(pService->m_nAudioPid));
			nRet &= pServiceXML->GetValue("PCRPID", strlen("PCRPID"), &(pService->m_nPCRPid));
			nRet &= pServiceXML->GetValue("VIDEO_TYPE", strlen("VIDEO_TYPE"), &(pService->m_nVideoType));
			nRet &= pServiceXML->GetValue("AUDIO_TYPE", strlen("AUDIO_TYPE"), &(pService->m_nAudioType));
			printf("m_nVideoPid = %d\n", pService->m_nVideoPid);
			m_AVConfig.m_vServiceList.push_back(pService);
		}
		printf("m_vServiceList.size = %d\n", m_AVConfig.m_vServiceList.size());
	}
	return nRet;
}
int FactoryTestParamSet::SetUSBConfig(XMLNode *pXMLNode, int nFlag)
{
	int nRet = 1;

	if (nFlag != 0)
	{
		XMLNode *pTemp = pXMLNode->GetXMLNode("USB", strlen("USB"));

		if (pTemp != NULL)
		{
			nRet &= pTemp->GetValue("COUNT", strlen("COUNT"), &m_USBConfig.m_nCount);
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetNETConfig(XMLNode *pXMLNode, int nFlag)
{
	int nRet = 1;

	return nRet;
}

int FactoryTestParamSet::SetSMCConfig(XMLNode *pXMLNode, int nFlag)
{
	int nRet = 1;

	if (nFlag != 0)
	{
		XMLNode *pTemp = pXMLNode->GetXMLNode("SMARTCARD", strlen("SMARTCARD"));

		if (pTemp != NULL)
		{
			nRet &= pTemp->GetValue("CATYPE", strlen("CATYPE"), &m_SMCConfig.m_nCAType);
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetFPConfig(XMLNode *pXMLNode, int nFlag)
{
	int nRet = 1;

	if (nFlag != 0)
	{
		XMLNode *pTemp = pXMLNode->GetXMLNode("FRONTPANEL", strlen("FRONTPANEL"));

		if (pTemp != NULL)
		{
			int nTemp = 0;
			
			m_FPConfig.m_unKeyCount = 0;
			nRet &= pTemp->GetValue(&nTemp, "POWER", strlen("POWER"));
			if(nTemp == 1)
			{
				m_FPConfig.m_aunKeyList[m_FPConfig.m_unKeyCount++] = FT_VK_FP_POWER;
			}
			nRet &= pTemp->GetValue(&nTemp, "OK", strlen("OK"));
			if(nTemp == 1)
			{
				m_FPConfig.m_aunKeyList[m_FPConfig.m_unKeyCount++] = FT_VK_FP_OK;
			}
			nRet &= pTemp->GetValue(&nTemp, "CH+", strlen("CH+"));
			if(nTemp == 1)
			{
				m_FPConfig.m_aunKeyList[m_FPConfig.m_unKeyCount++] = FT_VK_FP_UP;
			}
			nRet &= pTemp->GetValue(&nTemp, "CH-", strlen("CH-"));
			if(nTemp == 1)
			{
				m_FPConfig.m_aunKeyList[m_FPConfig.m_unKeyCount++] = FT_VK_FP_DOWN;
			}
			nRet &= pTemp->GetValue(&nTemp, "VOL+", strlen("VOL+"));
			if(nTemp == 1)
			{
				m_FPConfig.m_aunKeyList[m_FPConfig.m_unKeyCount++] = FT_VK_FP_LEFT;
			}
			nRet &= pTemp->GetValue(&nTemp, "VOL-", strlen("VOL-"));
			if(nTemp == 1)
			{
				m_FPConfig.m_aunKeyList[m_FPConfig.m_unKeyCount++] = FT_VK_FP_RIGHT;
			}
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetSNConfig(XMLNode *pXMLNode, int nFlag)
{
	int nRet = 1;

	if (nFlag != 0)
	{
		XMLNode *pTemp = pXMLNode->GetXMLNode("WRITE", strlen("WRITE"));

		if (pTemp != NULL)
		{
			nRet &= pTemp->GetValue("CONN", strlen("CONN"), (int*)&m_SNConfig.m_unConnType);
			nRet &= pTemp->GetValue("IP", strlen("IP"), m_SNConfig.m_acIP, sizeof(m_SNConfig.m_acIP));
			nRet &= pTemp->GetValue("PORT", strlen("PORT"), (int*)&m_SNConfig.m_usPort);
			nRet &= pTemp->GetValue(&m_SNConfig.m_nSN, "SN", strlen("SN"));
			nRet &= pTemp->GetValue(&m_SNConfig.m_nHDCP, "HDCP", strlen("HDCP"));
			nRet &= pTemp->GetValue(&m_SNConfig.m_nMAC, "MAC", strlen("MAC"));
			nRet &= pTemp->GetValue(&m_SNConfig.m_nPEF, "PEF", strlen("PEF"));
			nRet &= pTemp->GetValue(&m_SNConfig.m_nCxPerson, "CONAXP", strlen("CONAXP"));
			nRet &= pTemp->GetValue(&m_SNConfig.m_nCxPerson, "IFCP", strlen("IFCP"));
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetOTAConfig(XMLNode *pXMLNode, int nFlag)
{
	int nRet = 1;

	if (nFlag != 0)
	{

		char acDVBType[32] = { 0 };
		XMLNode *pTemp = pXMLNode->GetXMLNode("OTA", strlen("OTA"));

		if (pTemp != NULL)
		{
			nRet &= pTemp->GetValue("OTAType", strlen("OTAType"), acDVBType, sizeof(acDVBType));
			nRet &= SetDVBType(acDVBType, strlen(acDVBType), m_OTAConfig.m_unOTAType);
			nRet &= pTemp->GetValue("OTAPID", strlen("OTAPID"), (int*)&m_OTAConfig.m_usOTAPid);
			nRet &= pTemp->GetValue("TABLEID", strlen("TABLEID"), (int*)&m_OTAConfig.m_ucOTATableId);
			nRet &= SetDeliveryParam(pTemp, &m_OTAConfig.m_stOTADelivery, m_OTAConfig.m_unOTAType, 0);
			nRet &= pTemp->GetValue((int*)&m_OTAConfig.m_unHLType, "HLTEST", strlen("HLTEST"));
			nRet &= pTemp->GetValue((int*)&m_OTAConfig.m_unMarkIDFlag, "MARKETID", strlen("MARKETID"));
			nRet &= pTemp->GetValue(&m_OTAConfig.m_nBoot, "BOOT", strlen("BOOT"));
			nRet &= pTemp->GetValue(&m_OTAConfig.m_nCW, "CW", strlen("CW"));
			nRet &= pTemp->GetValue(&m_OTAConfig.m_nJTag, "JTAG", strlen("JTAG"));
			nRet &= pTemp->GetValue(&m_OTAConfig.m_CoreFlag, "COREWRITE", strlen("COREWRITE"));

			if (nRet == 1 && m_OTAConfig.m_CoreFlag == 1)
			{
				nRet &= pTemp->GetValue("MANF", strlen("MANF"), (int*)&m_OTAConfig.m_unManuF);
				nRet &= pTemp->GetValue("HARDWARE", strlen("HARDWARE"), (int*)&m_OTAConfig.m_unHW);
				nRet &= pTemp->GetValue("VAT", strlen("VAT"), (int*)&m_OTAConfig.m_unVT);
				nRet &= pTemp->GetValue("CAADDR", strlen("CAADDR"), (int*)&m_OTAConfig.m_unCAAddr);
				nRet &= pTemp->GetValue("CASIZE", strlen("CASIZE"), (int*)&m_OTAConfig.m_unCASize);
				nRet &= pTemp->GetValue("COREADDR", strlen("COREADDR"), (int*)&m_OTAConfig.m_unCoreFileAddr);
				nRet &= pTemp->GetValue("CORESIZE", strlen("CORESIZE"), (int*)&m_OTAConfig.m_unCoreFileSize);
				nRet &= pTemp->GetValue("CFGADDR", strlen("CFGADDR"), (int*)&m_OTAConfig.m_unCFGFileAddr);
				nRet &= pTemp->GetValue("CFGSIZE", strlen("CFGSIZE"), (int*)&m_OTAConfig.m_unCFGFileSize);
			
				if(nRet == 1)
				{
					nRet &= SetCACoreAddr(pTemp);
				}
			}
		}
		else
		{
			nRet = 0;
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetDeliveryParam(XMLNode *pXMLNode, ADITunerSRCDeliver_U *pDelivery, unsigned int unDVBType, int nIndex)
{
	int nRet = 1;

	if (unDVBType == DELIVERY_C)
	{
		nRet &= SetDVBCDelivery(pXMLNode, pDelivery, nIndex);
	}
	else if (unDVBType == DELIVERY_S)
	{
		nRet &= SetDVBSDelivery(pXMLNode, pDelivery, nIndex);
	}
	else if (unDVBType == DELIVERY_T)
	{
		nRet &= SetDVBTDelivery(pXMLNode, pDelivery, nIndex);
	}
	else
	{
		nRet = 0;
	}

	return nRet;
}

int FactoryTestParamSet::SetDVBCDelivery(XMLNode *pXMLNode, ADITunerSRCDeliver_U * pDelivery, int nIndex)
{
	int nRet = 1;
	XMLNode *pTemp = NULL;

	if(nIndex == 0)
	{
		pTemp = pXMLNode->GetXMLNode("DVBC", strlen("DVBC"));
	}
	else if(nIndex == 1)
	{
		pTemp = pXMLNode->GetXMLNode("DVBC2", strlen("DVBC2"));
	}

	if (pTemp != NULL)
	{
		int nTemp = 0;

		nRet = 1;
		nRet &= pTemp->GetValue("FREQUENCY_C", strlen("FREQUENCY_C"), &nTemp);
		pDelivery->m_sCableDeliver.m_uFrequency = nTemp;
		nRet &= pTemp->GetValue("SYMBOL", strlen("SYMBOL"), &nTemp);
		pDelivery->m_sCableDeliver.m_uSymbolRate_24 = nTemp;
		nRet &= pTemp->GetValue("MODUL", strlen("MODUL"), &nTemp);
		pDelivery->m_sCableDeliver.m_uModulation_8 = nTemp;
	}

	return nRet;
}

int FactoryTestParamSet::SetDVBSDelivery(XMLNode *pXMLNode, ADITunerSRCDeliver_U * pDelivery, int nIndex)
{
	int nRet = 0;
	XMLNode *pTemp = NULL;

	if(nIndex == 0)
	{
		pTemp = pXMLNode->GetXMLNode("DVBS", strlen("DVBS"));
	}
	else if(nIndex == 1)
	{
		pTemp = pXMLNode->GetXMLNode("DVBS2", strlen("DVBS2"));
	}

	if (pTemp != NULL)
	{
		int nTemp = 0;

		nRet = 1;
		pDelivery->m_sSourceSatelliteDeliver.m_sLNB.m_uHighFrequency = 5150000;
		pDelivery->m_sSourceSatelliteDeliver.m_sLNB.m_uLowFrequency = 5150000;
		pDelivery->m_sSourceSatelliteDeliver.m_sLNB.m_uLnbType = EM_ADITUNER_SINGLE;
		pDelivery->m_sSourceSatelliteDeliver.m_sLNB.m_uLnbPower = EM_ADITUNER_SWITCH_ON;
		pDelivery->m_sSourceSatelliteDeliver.m_sAntennaPar.m_uSwitch22k = EM_ADITUNER_SWITCH_ON;
		nRet &= pTemp->GetValue("FREQUENCY_S", strlen("FREQUENCY_S"), &nTemp);
		pDelivery->m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFrequency = pDelivery->m_sSourceSatelliteDeliver.m_sLNB.m_uHighFrequency - nTemp;
		nRet &= pTemp->GetValue("SYMBOL", strlen("SYMBOL"), &nTemp);
		pDelivery->m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uSymbolRate_24 = nTemp;
		nRet &= pTemp->GetValue("POLAR", strlen("POLAR"), &nTemp);
		pDelivery->m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uPolar_4 = nTemp;
		nRet &= pTemp->GetValue("TUNER", strlen("TUNER"), &nTemp);
		pDelivery->m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uStandards_2 = nTemp;
	}

	return nRet;
}

int FactoryTestParamSet::SetDVBTDelivery(XMLNode *pXMLNode, ADITunerSRCDeliver_U * pDelivery, int nIndex)
{
	int nRet = 0;
	XMLNode *pTemp = NULL;

	if(nIndex == 0)
	{
		pTemp = pXMLNode->GetXMLNode("DVBT", strlen("DVBT"));
	}
	else if(nIndex == 1)
	{
		pTemp = pXMLNode->GetXMLNode("DVBT2", strlen("DVBT2"));
	}
	printf("nIndex = %d\n", nIndex);
	if (pTemp != NULL)
	{
		int nTemp = 0;

		nRet = 1;
		nRet &= pTemp->GetValue("FREQUENCY_T", strlen("FREQUENCY_T"), &nTemp);
		pDelivery->m_sTerrestrialDeliver.m_uFrequency = nTemp;
		printf("FREQUENCY_T = %d  ", (pDelivery->m_sTerrestrialDeliver.m_uFrequency));
		nRet &= pTemp->GetValue("BAND", strlen("BAND"), &nTemp);
		pDelivery->m_sTerrestrialDeliver.m_uBanuidth_3 = nTemp;
		printf("BAND = %d  ", nTemp);
		nRet &= pTemp->GetValue("TUNER", strlen("TUNER"), &nTemp);
		pDelivery->m_sTerrestrialDeliver.m_uFlag_2 = nTemp;
		printf("TUNER = %d  \n", nTemp);
	}

	return  nRet;
}

int FactoryTestParamSet::SetCACoreAddr(XMLNode *pXMLNode)
{
	int nRet = 0;

	XMLNode *pTemp = pXMLNode->GetXMLNode("CORECFG", strlen("CORECFG"));

	if (pTemp != NULL)
	{
		int ii = 0;
		for (ii; ii < IRDETOCCA_CORE_AND_CFG_COUNT; ii++)
		{
			if (SetCAOneCoreAddr(pTemp, &m_OTAConfig.m_CoreDataInfo[ii], ii) == 0)
			{
				break;
			}
		}
		if (ii == IRDETOCCA_CORE_AND_CFG_COUNT)
		{
			nRet = 1;
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetCAOneCoreAddr(XMLNode *pXMLNode, CoreDataInfo *pCoreDataInfo, int nIndex)
{
	int nRet = 0;
	char acCoreName[32] = { 0 };

	sprintf(acCoreName, "CORE%d", nIndex);

	XMLNode *pTemp = pXMLNode->GetXMLNode(acCoreName, strlen(acCoreName));

	if (pTemp != NULL)
	{
		nRet = 1;
		nRet &= pTemp->GetValue("SIZE", strlen("SIZE"), (int*)&pCoreDataInfo->unDataSize);
		nRet &= pTemp->GetValue("SEGNUM", strlen("SEGNUM"), (int*)&pCoreDataInfo->unSegCount);
		if (nRet == 1 && pCoreDataInfo->unSegCount > 0)
		{
			for (int ii = 0; ii < pCoreDataInfo->unSegCount; ii++)
			{
				if (SetCAOneCoreSegAddr(pTemp, &pCoreDataInfo->saSegInfo[ii], ii) == 0)
				{
					nRet = 0;
					break;
				}
			}
		}
	}

	return nRet;
}

int FactoryTestParamSet::SetCAOneCoreSegAddr(XMLNode *pXMLNode, SegInfo *pSegInfo, int nIndex)
{
	int nRet = 0;
	char acSegName[32] = { 0 };

	sprintf(acSegName, "SEG%d", nIndex);

	XMLNode *pTemp = pXMLNode->GetXMLNode(acSegName, strlen(acSegName));

	if (pTemp != NULL)
	{
		nRet = 1;
		nRet &= pTemp->GetValue("SEGADDR", strlen("SEGADDR"), (int*)&pSegInfo->unSegAddr);
		nRet &= pTemp->GetValue("SEGSIZE", strlen("SEGSIZE"), (int*)&pSegInfo->unSegSize);
	}

	return nRet;
}
