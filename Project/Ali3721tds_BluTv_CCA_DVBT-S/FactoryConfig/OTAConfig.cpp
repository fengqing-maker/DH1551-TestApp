#include "OTAConfig.h"
#include "string.h"

void OTAConfig::SetDefaultConfig(void)
{	
	memset(&m_stOTADelivery, 0, sizeof(ADITunerSRCDeliver_U));
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uHighFrequency = 5150000 ;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uLowFrequency = 5150000 ;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uLnbType = EM_ADITUNER_SINGLE ;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sLNB.m_uLnbPower = EM_ADITUNER_SWITCH_ON ;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sAntennaPar.m_uSwitch22k = EM_ADITUNER_SWITCH_ON;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uFrequency = 4150000;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uSymbolRate_24 = 27500;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uPolar_4 = EM_ADITUNER_POLARISATION_V ;
	m_stOTADelivery.m_sSourceSatelliteDeliver.m_sSatelliteDeliver.m_uStandards_2 = EM_ADITUNER_DVBS_STANDARD ;
	
	m_unHLType = 0;
	m_unMarkIDFlag = 1;
	m_usOTAPid = 0x402;
	m_ucOTATableId = 0x80;
	
	m_unCAAddr = 0;
	m_unCASize = 0;

	m_nBoot = 1;
	m_nCW = 0;
	m_nJTag = 1;

	m_unManuF = 236;
	m_unHW = 8;
	m_unVT = 360;

	m_CoreFlag = 0;
}
