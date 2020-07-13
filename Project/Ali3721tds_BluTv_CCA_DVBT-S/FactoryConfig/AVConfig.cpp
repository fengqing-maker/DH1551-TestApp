#include "AVConfig.h"
#include "string.h"

void AVConfig::SetDefaultConfig(void)
{	
	m_nTunerCount = 1;

	TunerInfo_S *pTuner = new TunerInfo_S();
	ServiceInfo_S *pServiceList = new ServiceInfo_S();
	memset(pTuner, 0, sizeof(TunerInfo_S));
	memset(pServiceList, 0, sizeof(ServiceInfo_S));
	m_vTuner_List.push_back(pTuner);
	m_vServiceList.push_back(pServiceList);
}
