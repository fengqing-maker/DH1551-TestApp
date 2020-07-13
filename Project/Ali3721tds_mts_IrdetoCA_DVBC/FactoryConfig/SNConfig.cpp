#include "SNConfig.h"
#include "string.h"

void SNConfig::SetDefaultConfig(void)
{
	m_unConnType = E_UART_CONN;
	memcpy(m_acIP, "192.168.110.19", sizeof("192.168.110.19"));
	m_usPort = 6555;
	m_nSN = 1;
	m_nHDCP = 1;
	m_nMAC = 0;
	m_nPEF = 0;
	m_nCxPerson = 0;
}
