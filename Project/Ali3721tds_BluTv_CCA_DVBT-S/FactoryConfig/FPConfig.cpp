#include "FPConfig.h"
#include "string.h"
#include "FactoryTestKey.h"

void FPConfig::SetDefaultConfig(void)
{
	unsigned int aunPanelKeys[] = { FT_VK_FP_POWER, FT_VK_FP_UP, FT_VK_FP_DOWN };

	m_unKeyCount = sizeof(aunPanelKeys) / sizeof(unsigned int);

	memcpy(m_aunKeyList, aunPanelKeys, sizeof(aunPanelKeys));
}
