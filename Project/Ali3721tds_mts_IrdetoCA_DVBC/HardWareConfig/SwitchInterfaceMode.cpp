#include "SwitchInterfaceMode.h"
#include "string.h"

SwitchInterfaceMode::SwitchInterfaceMode()
{
	m_en22K = EM_ADITUNER_SWITCH_ON;
	m_enPolar = EM_ADITUNER_POLARISATION_H;
	m_enColor = EM_ADISCART_COLOR_CVBS;
	m_enDisplay = EM_ADISCART_DISPLAY_16_9;
	m_bPower = ADI_TRUE;
}

SwitchInterfaceMode::~SwitchInterfaceMode()
{
}

int SwitchInterfaceMode::Init(void)
{
	int nRet = 0;
	
	nRet |= ADITunerSetPolar(0, m_enPolar);
	
	nRet |= ADIScartColorModeSwitch(EM_ADISCART_INDEX_VCR, m_enColor);
	
	nRet |= ADIScartSetAspectRatio(EM_ADISCART_INDEX_VCR, m_enDisplay);
	
	nRet |= ADITunerSetAntennaPowerEnable(0, m_bPower);

	return nRet;
}

ADITunerSwitchStatus_E SwitchInterfaceMode::Get22KMode(void)
{
	return m_en22K;
}

ADITunerChannelPolar_E SwitchInterfaceMode::GetPolarMode(void)
{
	return m_enPolar;
}

ADIScartColorMod_E SwitchInterfaceMode::GetColorMode(void)
{
	return m_enColor;
}

ADIScartDisplayMod_E SwitchInterfaceMode::GetDisplayMode(void)
{
	return m_enDisplay;
}

ADI_BOOL SwitchInterfaceMode::GetPowerEnable(void)
{
	return m_bPower;
}

int SwitchInterfaceMode::Switch22KMode(void)
{
	m_en22K = (m_en22K == EM_ADITUNER_SWITCH_ON) ? EM_ADITUNER_SWITCH_OFF : EM_ADITUNER_SWITCH_ON;
	
	return StartTuner(m_en22K, m_enPolar);	
}

int SwitchInterfaceMode::SwitchPolarMode(void)
{
	m_enPolar = (m_enPolar == EM_ADITUNER_POLARISATION_H) ? EM_ADITUNER_POLARISATION_V : EM_ADITUNER_POLARISATION_H;

	return ADITunerSetPolar (0, m_enPolar);	
}

int SwitchInterfaceMode::SwitchColorMode(void)
{	
	m_enColor = (m_enColor == EM_ADISCART_COLOR_CVBS) ? EM_ADISCART_COLOR_RGB : EM_ADISCART_COLOR_CVBS;

	return ADIScartColorModeSwitch(EM_ADISCART_INDEX_VCR, m_enColor);	
}

int SwitchInterfaceMode::SwitchDisplayMode(void)
{
	m_enDisplay = (m_enDisplay == EM_ADISCART_DISPLAY_16_9) ? EM_ADISCART_DISPLAY_4_3 : EM_ADISCART_DISPLAY_16_9;

	return ADIScartSetAspectRatio(EM_ADISCART_INDEX_VCR, m_enDisplay);
}

int SwitchInterfaceMode::SwitchPowerEnable(void)
{
	m_bPower = (m_bPower == ADI_TRUE) ? ADI_FALSE : ADI_TRUE;

	return ADITunerSetAntennaPowerEnable( 0, m_bPower );	
}

int SwitchInterfaceMode::StartTuner(ADITunerSwitchStatus_E enTuner22k, ADITunerChannelPolar_E enPolar)
{	
	ADITunerSRCDeliver_U stAVDelivery;
	
	memset(&stAVDelivery, 0, sizeof(ADITunerSRCDeliver_U));
	
	stAVDelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uHighFrequency = 5150000 ;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uLowFrequency = 5150000 ;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uLnbType = EM_ADITUNER_SINGLE ;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uLnbPower = EM_ADITUNER_SWITCH_ON ;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sAntennaPar.m_uSwitch22k = enTuner22k;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFrequency = 4200000;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uSymbolRate_24 = 27500;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uPolar_4 = enPolar ;
	stAVDelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uStandards_2 = EM_ADITUNER_DVBS_STANDARD ;

	return ADITunerConnect(0 , &stAVDelivery);
}

