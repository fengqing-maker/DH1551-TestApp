#include "BaseTestItem.h"
#include "string.h"

void BaseTestItem::SetDefaultConfig(void)
{
	memcpy(m_acProjectName, "Ali3721", sizeof("Ali3721"));
	m_unResultAddr = 0x7FFF00;

	m_nS22K = 0;
	m_nASP = 0;
	m_nDis = 0;
	m_nST = 0;
	m_nTT = 0;
	m_nCR = 0;
	m_nIR = 0;
	m_nAV = 1;
	m_nUSB = 1;
	m_nNet = 0;
	m_nSMC = 0;
	m_nFP = 1;
	m_nSN = 1;
	m_nOTA = 1;
}
