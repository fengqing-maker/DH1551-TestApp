#ifndef CONAX_OTA_SUPPORT_H_
#define CONAX_OTA_SUPPORT_H_

#include "OTASupport.h"

class ConaxOTASupport : public OTASupport
{
public:
	ConaxOTASupport();
	~ConaxOTASupport();

public:
	unsigned int OpenHLType(int nOption1, int nOption2, int nOption3);

private:
	void OTP_Read_Test(unsigned int unOTPAddr);
	void OTP_Write_Test(unsigned int unOTPAddr, unsigned int unOTPData, unsigned int unOTPLen);
	int Get_OTP_Info(void);
	void bit_print_test(unsigned int unValue);
	int Burn_OTP_Step1(void);
	int Burn_OTP_Step2(void);
	int TS_OTP_Read(unsigned int addr, unsigned int *punValue, unsigned int unSize);
	int WriteBootFile(void);
};

#endif/*CONAX_OTA_SUPPORT_H_*/
