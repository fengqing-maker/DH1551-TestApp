#ifndef BASE_TEST_ITEM_H_
#define BASE_TEST_ITEM_H_

typedef enum
{
	DELIVERY_UNKNOWN = 0,
	DELIVERY_C,
	DELIVERY_S,
	DELIVERY_T
}DELIVERY_TYPE;

class BaseTestItem
{
public:
	void SetDefaultConfig(void);
	
public:
	char m_acProjectName[32];
	unsigned int m_unResultAddr;

	int m_nS22K;
	int m_nASP;
	int m_nDis;
	int m_nST;
	int m_nTT;
	int m_nCR;
	int m_nIR;
	int m_nAV;
	int m_nUSB;
	int m_nNet;
	int m_nSMC;
	int m_nFP;
	int m_nSN;
	int m_nOTA;
};

#endif/*BASE_TEST_ITEM_H_*/