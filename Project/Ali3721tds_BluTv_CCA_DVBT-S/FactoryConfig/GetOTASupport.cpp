#include "adi_secure.h"
#include "GetOTASupport.h"
#include "string.h"
#include "stdio.h"

#define MSID_OTP_ADDRESS			(0x2)
#define MSID_PROTECT_OTP_ADDRESS	(0x5F)
#define CASTPAL_MSID_VALUE			(0xEC)
#define BOOT_ENCRYPT_OTP_ADDRESS	(0x1B8)
#define OTP_PROTECTION_ADDRESS		(0x104)

static OTASupport *g_pOTASupport = NULL;

OTASupport* GetOTASupport(void)
{
	if(g_pOTASupport == NULL)
	{
		g_pOTASupport = new IrdetoOTASupport();
	}

	return g_pOTASupport;
}

void bit_print_test(unsigned int unValue)
{
	int k = 0;
	int i = 0;
	
	unsigned char *p = (unsigned char*)&unValue + 3; //从低位到高位
	for(k = 0; k <= 3; k++)
	{
		unsigned int unData = *(p-k);
		for(i = 7; i >= 0; i--)
		{
			if(unData & (1 << i))
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		printf(" ");
	}
	
	printf("\n");
	return;
} 


unsigned int TS_SetOptAndMarketID( int nFlag )
{
	int nRet = 0;
	
	if ( nFlag == 0 )
	{
		printf("[%s %d] no need write MarketID \r\n", __FUNCTION__, __LINE__);
		nRet = 1;
	}
	else
	{
		unsigned int unOTPAddr = 0;
		unsigned int unOTPData = 0;

		do
		{			
			unOTPAddr = MSID_PROTECT_OTP_ADDRESS;
			nRet = ADISecureReadOtp( unOTPAddr, &unOTPData);	
			if((0 != nRet) || (((unOTPData>>2)&0x1) == 1))
			{
				// write protection otp has been set to 1
				printf("[%s %d]Failed with MSID_PROTECT_OTP enabled! data 0x%x, nRet 0x%x\r\n", __FUNCTION__, __LINE__, unOTPData, nRet);
				bit_print_test(unOTPData);
				//break;
			}
			else
			{
				nRet = ADISecureGetMarketId(&unOTPData);
				printf("[%s %d] ADISecureGetMarketId unOTPData:0x%x\r\n", __FUNCTION__, __LINE__, unOTPData);
				if(0 != nRet)
				{
					printf("[%s %d]ADISecureGetMarketId Failed: nRet 0x%x\r\n", __FUNCTION__, __LINE__,nRet);			
					break;
				}
				else
				{
					bit_print_test(unOTPData);
				}

				if(unOTPData == CASTPAL_MSID_VALUE) // 之前已经设置MSID=236 OK
				{
					printf("[%s %d] CASTPAL_MSID_VALUE OK\r\n", __FUNCTION__, __LINE__);
					//return 0;
				}
				else
				{
					unOTPData = CASTPAL_MSID_VALUE;
					nRet = ADISecureSetMarketId(unOTPData);
					if(0 != nRet)
					{
						printf("[%s %d]ADISecureSetMarketId Failed: nRet 0x%x\r\n", __FUNCTION__, __LINE__,nRet);
						break;
					}
					
					unOTPData = 0;
					nRet = ADISecureGetMarketId(&unOTPData);
					printf("[%s %d]ADISecureGetMarketId unOTPData:0x%x\r\n", __FUNCTION__, __LINE__, (unsigned int)unOTPData);
					if(0 != nRet)
					{
						break;
					}
					bit_print_test(unOTPData);

					if(CASTPAL_MSID_VALUE != unOTPData) // 校验本次设置是否OK
					{
						printf("[%s %d] Warning: Set IRDETO_MSID Failed\r\n", __FUNCTION__, __LINE__);
						//break;
					}
					printf("[%s %d]Set IRDETO_MSID OK\r\n", __FUNCTION__, __LINE__);
				}
			}

			//0x5F: OTP 保护位
			unsigned int ZONE_Protect_bit2 = 0x01<<2;	//bit by bit write protection for OTP 0x2 addr
			unOTPAddr = MSID_PROTECT_OTP_ADDRESS;
			nRet = ADISecureReadOtp(unOTPAddr, &unOTPData);
			if(ADI_SUCCESS != nRet)
			{
				printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			bit_print_test(unOTPData);
			unOTPData |= ZONE_Protect_bit2;
			nRet = ADISecureWriteOtp(unOTPAddr, unOTPData);
			if(ADI_SUCCESS != nRet)
			{
				printf("Addr 0x%x: ADISecureWriteOtp failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			bit_print_test(unOTPData);
			nRet = 1;
		}while(0);
	}
	
	return nRet;
}

unsigned int TS_SetBootEncryptOTP( int nFlag )
{
	int nRet = 0;
	unsigned int unOTPAddr = 0;
	unsigned int unOTPData = 0;

	do
	{
		//0x1B8[23]: Image_Enc_Enforcement, for boot image decryption!
		unsigned int Enc_Enforcement_bit23 = 0x01<<23;
		unOTPAddr = BOOT_ENCRYPT_OTP_ADDRESS;//0x1B8;
		unOTPData = 0;
		nRet = ADISecureReadOtp(unOTPAddr, &unOTPData);
		if(ADI_SUCCESS != nRet)
		{
			printf("Addr 0x%x: ADISecureReadOtp failed before write, nRet 0x%x\n",unOTPAddr, nRet);
			break;
		}
		bit_print_test(unOTPData);
		if (!(unOTPData & Enc_Enforcement_bit23))
		{
			unOTPData |= Enc_Enforcement_bit23;
			nRet = ADISecureWriteOtp(unOTPAddr, unOTPData);
			if(ADI_SUCCESS != nRet)
			{
				printf("Addr 0x%x: ADISecureWriteOtp failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			bit_print_test(unOTPData);
		}

		//0x104[23]: bit to bit protection for Image_Enc_Enforcement!
		unsigned int X104_bit23 = 0x01<<23;
		unOTPAddr = OTP_PROTECTION_ADDRESS;//0x104;
		unOTPData = 0;
		nRet = ADISecureReadOtp(unOTPAddr, &unOTPData);
		if(ADI_SUCCESS != nRet)
		{
			printf("Addr 0x%x: ADISecureReadOtp failed before write, nRet 0x%x\n",unOTPAddr, nRet);
			break;
		}
		bit_print_test(unOTPData);
		if ( !(unOTPData & X104_bit23) )
		{
			unOTPData |= Enc_Enforcement_bit23;
			nRet = ADISecureWriteOtp(unOTPAddr, unOTPData);
			if(ADI_SUCCESS != nRet)
			{
				printf("Addr 0x%x: ADISecureWriteOtp failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			bit_print_test(unOTPData);
		}
		nRet = 1;
	}while(0);

	return nRet;

}
