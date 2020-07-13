/*
 * SmartCardTest.cpp
 *
 *  Created on: 2015-8-14
 *      Author: timothy.liao
 */

#include "string.h"
#include "APAssert.h"
#include "SmartCardTest.h"
#include "ADI_CA_Comon.h"
#include "CI_Interface.h"

SmartCardTest* g_pSmartCardTest = NULL;
static unsigned int g_unCardIN = 0;

static void ScEventStatusCallBack(unsigned int unCardNumber, int nStatus);
void CASupportCallback(unsigned int dwType, unsigned int dwParm1, unsigned int dwParm2, unsigned int dwParm3);

SmartCardTest::SmartCardTest(unsigned int unIndex, ADISMCProtocol_E eProtocol, SmartCardNotify* pNotify) :
m_pSmartCardNotify(pNotify), m_unSmartCardIndex(unIndex), m_unSmartCardStatus(0), m_eSmcProtocol(eProtocol)
{
	APAssert(pNotify != NULL);

	g_pSmartCardTest = this;
}

SmartCardTest::~SmartCardTest()
{

}

void SmartCardTest::Init(SMCConfig csSMCConfig)
{
	memcpy(&m_SMCConfig, &csSMCConfig, sizeof(SMCConfig));
	
	switch( m_SMCConfig.m_nCAType )
	{
		case CLOAKED_CARD:
			break;
			
		case CIPLUS_CARD:
			break;
			
		case IRDETO_B_CARD:
		case IRDETO_S_CARD:
		case TONGFANG_CARD:
		{
			CardConfig(m_unSmartCardIndex, m_eSmcProtocol);
		}
			break;
			
		case ALI_CARD:
			break;
			
		default:
			break;
	}
}

unsigned int SmartCardTest::Start()
{
	unsigned int unRet = 0;

	switch( m_SMCConfig.m_nCAType )
	{
		case CLOAKED_CARD:
			break;
			
		case CIPLUS_CARD:
		{
			if( g_unCardIN == 1 )
			{
				unRet = 1;
				m_pSmartCardNotify->SmartCardResetNotify(m_unSmartCardIndex, unRet);
			}
			else
			{
				m_pSmartCardNotify->NoSmartCardNotify();
			}
		}
			break;
			
		case IRDETO_B_CARD:
		case IRDETO_S_CARD:
		case TONGFANG_CARD:
		{
			m_unSmartCardStatus = ADISMCDetectCardStatus(m_unSmartCardIndex);

			if (m_unSmartCardStatus == ADISMC_ERROR_IN ||
				m_unSmartCardStatus == ADISMC_ERROR_READY)
			{
				ResetCard(m_unSmartCardIndex);
			}
			else if (m_unSmartCardStatus == ADISMC_ERROR_OUT)
			{
				if(g_unCardIN == 0)
				{
					m_pSmartCardNotify->NoSmartCardNotify();
					unRet = 1;
				}
				else
				{
					m_pSmartCardNotify->SmartCardOutNotify(m_unSmartCardIndex);
				}
			}
		}
			break;
			
		case ALI_CARD:
			break;
			
		default:
			break;
	}

	return unRet;
}

unsigned int SmartCardTest::Stop()
{
	return 1;
}

unsigned int SmartCardTest::CardIn(unsigned int unIndex)
{
	unsigned int unRet = 0;

	if (unIndex == m_unSmartCardIndex)
	{
		m_pSmartCardNotify->SmartCardInNotify(m_unSmartCardIndex);

		ResetCard(m_unSmartCardIndex);

		unRet = 1;
	}

	return unRet;
}

unsigned int SmartCardTest::CardOut(unsigned int unIndex)
{
	unsigned int unRet = 0;

	if (unIndex == m_unSmartCardIndex)
	{
		m_pSmartCardNotify->SmartCardOutNotify(m_unSmartCardIndex);
		unRet = 1;
	}

	return unRet;
}

unsigned int SmartCardTest::CardConfig(unsigned int unIndex, ADISMCProtocol_E eProtocol)
{
	unsigned int unRet = 0;

	ADI_Error_Code unUDIError = ADISMC_ERROR_FAILURE;

	ADISMCParam_S sTmpParams;
	sTmpParams.m_eCheckBit = EM_ADISMC_8BITS_NO_PARITY;
	sTmpParams.m_eStandard = EM_ADISMC_STANDARD_IRDETO;
	sTmpParams.m_eStopBit = EM_ADISMC_STOP_1;

	if (EM_ADISMC_PROTOCOL_T14 == eProtocol)
	{
		//Irdeto T14
		sTmpParams.m_nBaudRate = 9600;
		sTmpParams.m_nETU = 620;
		sTmpParams.m_nFrequency = 6000000;
	}
	else
	{	
		//Irdeto T0
		sTmpParams.m_nBaudRate = 12096;
		sTmpParams.m_nETU = 372;
		sTmpParams.m_nFrequency = 4500000;
	}

	ADISMCClose(m_unSmartCardIndex);

	sTmpParams.m_eProtocol = eProtocol;
	unUDIError = ADISMCSetParams((int)unIndex, &sTmpParams);
	
	ADISMCOpen(m_unSmartCardIndex, (ADISMCCallback)ScEventStatusCallBack);

	if (unUDIError == ADI_SUCCESS)
	{
		unRet = 1;
	}

	return unRet;
}

unsigned int SmartCardTest::ResetCard(unsigned int unIndex)
{
	unsigned int unRet = 0;

	if( m_SMCConfig.m_nCAType == IRDETO_B_CARD || m_SMCConfig.m_nCAType == IRDETO_S_CARD || m_SMCConfig.m_nCAType == TONGFANG_CARD )
	{
		m_unSmartCardStatus = ADISMCDetectCardStatus(m_unSmartCardIndex);
		if (m_unSmartCardStatus == ADISMC_ERROR_IN ||
			m_unSmartCardStatus == ADISMC_ERROR_READY)
		{
			for (int ii = 0; ii < 2; ii++)
			{
				int dwAtrLen = 0;
				unsigned char acAtrBuf[33] = { 0 };
				if (ADI_SUCCESS == ADISMCReset(0, acAtrBuf, &dwAtrLen, ADI_FALSE))
				{
					unRet = 1;
					break;
				}
				else
				{
					m_eSmcProtocol = m_eSmcProtocol == EM_ADISMC_PROTOCOL_T14 ? EM_ADISMC_PROTOCOL_T0 : EM_ADISMC_PROTOCOL_T14;
					CardConfig(m_unSmartCardIndex, m_eSmcProtocol);
				}
			}
		}
	}
	else
	{
		unRet = 1;
	}

	m_pSmartCardNotify->SmartCardResetNotify(m_unSmartCardIndex, unRet);

	return unRet;
}

static void ScEventStatusCallBack(unsigned int unCardNumber, int nStatus)
{
	if (g_pSmartCardTest != NULL)
	{
		switch (nStatus)
		{
		case ADISMC_ERROR_IN:
			g_pSmartCardTest->CardIn(unCardNumber);
			g_unCardIN = 1;
			break;
		case ADISMC_ERROR_OUT:
			g_pSmartCardTest->CardOut(unCardNumber);
			g_unCardIN = 0;
			break;

		default:
			break;
		}
	}
}

void CASupportCallback(unsigned int dwType, unsigned int dwParm1, unsigned int dwParm2, unsigned int dwParm3)
{
	switch( dwType )
	{
		case EM_CI_STATUS_MSG:
		{
			switch( dwParm1 )
			{
				case EM_CI_STATUS_CAM_IN:
					/*if( g_pSmartCardTest == NULL )
					{
						g_pSmartCardTest->CardIn(0);
					}
					g_unCardIN = 1;*/
					printf("[%s %d] ===============pcmcia_IN========\n",__FUNCTION__, __LINE__);
					break;
				
				case EM_CI_STATUS_CAM_OUT:
					if( g_pSmartCardTest != NULL )
					{
						g_pSmartCardTest->CardOut(0);
					}
					g_unCardIN = 0;
					printf("[%s %d] ===============pcmcia_OUT========\n",__FUNCTION__, __LINE__);
					break;

				case EM_CI_STATUS_CAM_OK:
					printf("[%s %d] ===============pcmcia_OK========\n",__FUNCTION__, __LINE__);
					break;

				case (EM_CI_STATUS_CAM_OK+3):
					printf("[%s %d] ===============pcmcia_CAM_OK========\n",__FUNCTION__, __LINE__);
					if( g_pSmartCardTest != NULL )
					{
						g_pSmartCardTest->CardIn(0);
					}
					g_unCardIN = 1;
					break;

				default:
					break;
			}
		}
			break;

		default:
			break;
	}
}
