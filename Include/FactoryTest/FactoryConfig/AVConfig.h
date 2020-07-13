#ifndef AV_CONFIG_H_
#define AV_CONFIG_H_

#include "adi_tuner.h"
#include <vector>

using namespace std;

typedef struct{
	int m_nVideoPid;
	int m_nAudioPid;
	int m_nPCRPid;
	int m_nVideoType;
	int m_nAudioType; 
}ServiceInfo_S;
typedef struct{
	unsigned int m_nTunerType;
	int m_nDeliveryCount;
	vector<ADITunerSRCDeliver_U*> m_vDeliveryList;
}TunerInfo_S;

class AVConfig
{
public:
	void SetDefaultConfig(void);
	
public:
	int m_nTunerCount;

	vector<TunerInfo_S*> m_vTuner_List;

	vector<ServiceInfo_S*> m_vServiceList;

};

#endif/*AV_CONFIG_H_*/