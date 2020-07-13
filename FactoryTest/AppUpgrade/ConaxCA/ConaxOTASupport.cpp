#include "ConaxOTASupport.h"
#include "AuraTypedef.h"
#include "adi_os.h"
#include "adi_toolset.h"
#include "APMemory.h"
#include "adi_flash.h"
#include "adi_uart.h"
#include "../../DataUpgrade/SerialBuf.h"

#define libc_printf printf


ConaxOTASupport::ConaxOTASupport()
{
}

ConaxOTASupport::~ConaxOTASupport()
{
}

unsigned int ConaxOTASupport::OpenHLType(int nOption1, int nOption2, int nOption3)
{
	unsigned int unRet = 0;

	if(GetHLType() != 1)
	{
		SetOTACurSteps(OTP_STEP1);
		
		return 1;
	}

	unsigned int unStep = GetOTACurSteps();

	if((unStep & OTP_STEP1) != OTP_STEP1)
	{
		if(Burn_OTP_Step1() == 1)
		{
			SetOTACurSteps(OTP_STEP1);

			printf("--[%s][%d]--\n", __FUNCTION__, __LINE__);
			
			unRet = 2;
		}
	}
	else if ((unStep & OTP_STEP2) != OTP_STEP2 && OTP_STEP1 != nOption1)
	{
		if(Burn_OTP_Step2() == 1)
		{
			SetOTACurSteps(OTP_STEP2);
			
			printf("--[%s][%d]--\n", __FUNCTION__, __LINE__);
			
			unRet = 1;
		}
	}
	else
	{
		unRet = 1;
	}

	return unRet;
}

void ConaxOTASupport::OTP_Read_Test(unsigned int unOTPAddr)
{
	int nRet = 0;
	unsigned int unOTPValue = 0;
	unsigned char ucOTPData[4] = {0};

	nRet = TS_OTP_Read( unOTPAddr*4, &unOTPValue, 4);
	if(nRet <= 0)
	{
		libc_printf(" 0x%x: otp_read uint failed with nRet 0x%x!\n",unOTPAddr, nRet);
	}
	ADIOSThreadSleep(100);
	nRet = ADIOTPRead( unOTPAddr*4, ucOTPData, 4);
	if(nRet != 0)
	{
		libc_printf(" 0x%x: otp_read char failed with nRet 0x%x!\n",unOTPAddr, nRet);
	}
	libc_printf(" 0x%x: uint 0x%02x, char 0x%02x 0x%02x 0x%02x 0x%02x\n",unOTPAddr,unOTPValue,ucOTPData[0],ucOTPData[1],ucOTPData[2],ucOTPData[3]);	
	ADIOSThreadSleep(100);

	return;
}

void ConaxOTASupport::OTP_Write_Test(unsigned int unOTPAddr, unsigned int unOTPData, unsigned int unOTPLen)
{
	int nRet = 0;
	unsigned char ucOTPData[4] = {0};

	do
	{
		if(0x4 != unOTPLen)
		{
			libc_printf(" Write Failed with Bad Param: 0x%x\n",unOTPLen);
			break;
		}
		
		nRet = ADIOTPRead( unOTPAddr*4, ucOTPData, 4);
		if(nRet != 0)
		{
			libc_printf(" 0x%x: read failed with nRet 0x%x!\n",unOTPAddr, nRet);
			break;
		}
		libc_printf(" 0x%x: before write 0x%02x 0x%02x 0x%02x 0x%02x\n",unOTPAddr,ucOTPData[0],ucOTPData[1],ucOTPData[2],ucOTPData[3]);	
		ADIOSThreadSleep(100);
		
		ucOTPData[0] = (unOTPData&0x000000FF);
		ucOTPData[1] = (unOTPData&0x0000FF00)>>8;
		ucOTPData[2] = (unOTPData&0x00FF0000)>>16;
		ucOTPData[3] = (unOTPData&0xFF000000)>>24;
#if 1  /*-------- This line '#if 0/1 #endif' condition is inserted as a debug test! --------*/
		nRet = ADIOTPWrite( unOTPAddr*4, ucOTPData, 4);
		if(nRet != 0)
		{
			libc_printf(" 0x%x: write failed with nRet 0x%x!\n",unOTPAddr, nRet);
			break;
		}
#endif
		libc_printf(" 0x%x: write success 0x%02x 0x%02x 0x%02x 0x%02x\n",unOTPAddr,ucOTPData[0],ucOTPData[1],ucOTPData[2],ucOTPData[3]);	
		ADIOSThreadSleep(100);
		
		nRet = ADIOTPRead( unOTPAddr*4, ucOTPData, 4);
		if(nRet != 0)
		{
			libc_printf(" 0x%x: read failed with nRet 0x%x!\n",unOTPAddr, nRet);
			break;
		}
		libc_printf(" 0x%x: after write 0x%02x 0x%02x 0x%02x 0x%02x\n",unOTPAddr,ucOTPData[0],ucOTPData[1],ucOTPData[2],ucOTPData[3]);	
		ADIOSThreadSleep(100);
	}while(0);

	return;
}


int ConaxOTASupport::Get_OTP_Info(void)
{
	unsigned int nRet = ADI_SUCCESS;
	unsigned int unOTPAddr = 0;
	
	do
	{
		//0x00 ~ 0x03
		for(unOTPAddr=0x0;unOTPAddr<0x4;unOTPAddr++)
		{
			OTP_Read_Test(unOTPAddr);
		}

		//0x55 ~ 0xDD
		for(unOTPAddr=0x55;unOTPAddr<0xDE;unOTPAddr++)
		{
			OTP_Read_Test(unOTPAddr);
		}

		//more: BootCode version
		unOTPAddr = 0xDE;
		OTP_Read_Test(unOTPAddr);
		
		//0xE2 ~ 0xE7
		for(unOTPAddr=0xE2;unOTPAddr<0xE8;unOTPAddr++)
		{
			OTP_Read_Test(unOTPAddr);
		}

	}while(0);
	
	return nRet;
}

void ConaxOTASupport::bit_print_test(unsigned int unValue)
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
				libc_printf("1");
			}
			else
			{
				libc_printf("0");
			}
		}
		libc_printf(" ");
	}
	
	libc_printf("\n");
	return;
} 

int ConaxOTASupport::Burn_OTP_Step1(void)
{
	unsigned int nRet = 0;
	unsigned int unFinish = 0;
	unsigned int unOTPAddr = 0;
	unsigned int unOTPData = 0;

	libc_printf("\n[%s] @@@@@@@@ Test 111111 Start @@@@@@@@\n",__FUNCTION__);
	do
	{
		//开启所有Conax 要求的OTP位:注意JTAG 和所有保护位一定要留在最后一步开启!!!
		//即先开启内容，再开启写保护, 否则会导致写保护开启后对应位置无法再开启，影响功能!!
		
		//OTP Fuse Test: Step 1
		{
			//config 0x2
			unOTPAddr = 0x2;
			unsigned int customer_id = 0x35B60000;	//test marketid, 0x27100000 or 0x33330000, release marketid: 0x35B60000
			nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData =customer_id;
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		{
			//config 0x85
			unOTPAddr = 0x85;
			unsigned int bootsize_bit7 = 0x00<<7;	///boot size 3 bit 7~9: 110
			unsigned int bootsize_bit8 = 0x01<<8;
			unsigned int bootsize_bit9 = 0x01<<9;
			nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (bootsize_bit7|bootsize_bit8|bootsize_bit9);
			bit_print_test(unOTPData);

			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		{
			//config 0xE6			---> bit by bit write protection for OTP 0x85 addr
			unOTPAddr = 0xE6;
			unsigned int E6_zone_bit7 = 0x01<<7;	//conax confirmed: 0xE6[9:7] is set to 1.
			unsigned int E6_zone_bit8 = 0x01<<8;
			unsigned int E6_zone_bit9 = 0x01<<9;
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (E6_zone_bit7|E6_zone_bit8|E6_zone_bit9);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		{
			if(WriteBootFile() == 0)
			{
				break;
			}
			//config 0xDD
			unOTPAddr = 0xDD;
			unsigned int bootrom_sig_enable = 0x01<<1;	//OTP Fuse Test: Step 1.1
			unsigned int bl_encrypt_flow = 0x01<<13;	//OTP Fuse Test: Step 1.2
			//bl_encrypt_flow = 0x00<<13 <---只验证bootrom sig高安签字，不做_ENABLE_BL_ENCRYPTED_加解密处理时先不开启bl_encrypt_flow
			nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (bootrom_sig_enable|bl_encrypt_flow);
			bit_print_test(unOTPData);

			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}

		unFinish = 1;
		
	}while(0);
	
	libc_printf("\n[%s] @@@@@@@@ Test 111111 End @@@@@@@@unFinish=%d\n",__FUNCTION__, unFinish);
	
	return unFinish;
}

int ConaxOTASupport::Burn_OTP_Step2(void)
{
	unsigned int nRet = 0;
	unsigned int unFinish = 0;
	unsigned int unOTPAddr = 0;
	unsigned int unOTPData = 0;

	libc_printf("\n[%s] @@@@@@@@ Test 222222 Start @@@@@@@@\n",__FUNCTION__);

	ADIUartDisable ( 0, ADI_TRUE );
	
	do
	{
		//开启所有Conax 要求的OTP位:注意JTAG 和所有保护位一定要留在最后一步开启!!!
		//即先开启内容，再开启写保护, 否则会导致写保护开启后对应位置无法再开启，影响功能!!

		//OTP Fuse Test: Step 2 (保证step1开启成功并重启验证可以启动的情况下再进入step2)
		{
			//config 0x8C
			unOTPAddr = 0x8C;
			unsigned int clear_blprotectionkey_disable = 0x01<<5;
			nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (clear_blprotectionkey_disable);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		{
			//config 0x8D
			unOTPAddr = 0x8D;
			unsigned int zone_8D_bit5 = 0x01<<5;
			nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (zone_8D_bit5);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}

		{
			//config 0x82
			unOTPAddr = 0x82;
			unsigned int zone_82_bit4 = 0x00<<4;	//to 0x0
			unsigned int zone_82_bit5 = 0x01<<5;
			unsigned int zone_82_bit7 = 0x01<<7;
			unsigned int zone_82_bit8 = 0x00<<8;	//to 0x0
			unsigned int zone_82_bit22 = 0x01<<22;
			unsigned int zone_82_bit23 = 0x01<<23;
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (zone_82_bit4|zone_82_bit5|zone_82_bit7|zone_82_bit8|zone_82_bit22|zone_82_bit23);
			bit_print_test(unOTPData);

			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		{
			//config 0xE5			---> bit by bit write protection for OTP 0x82 addr
			unOTPAddr = 0xE5;
			unsigned int E5_zone_bit5 = 0x01<<5;	//conax confirmed: 0xE5[23, 22, 8, 7, 5] is set to 1.
			unsigned int E5_zone_bit7 = 0x01<<7;
			unsigned int E5_zone_bit8 = 0x01<<8;
			unsigned int E5_zone_bit22 = 0x01<<22;
			unsigned int E5_zone_bit23 = 0x01<<23;
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (E5_zone_bit5|E5_zone_bit7|E5_zone_bit8|E5_zone_bit22|E5_zone_bit23);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		
		{
			//config 0xDC
			unOTPAddr = 0xDC;
			unsigned int smc0_disable = 0x00<<0;
			unsigned int smc1_disable = 0x01<<1;
			unsigned int bootmode_bit2 = 0x01<<2;	///boot mode 3 bit 2~4 : 001
			unsigned int bootmode_bit3 = 0x00<<3;
			unsigned int bootmode_bit4 = 0x00<<4;
			unsigned int standby_fastresume_disable = 0x01<<29;
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (smc0_disable|smc1_disable|bootmode_bit2|bootmode_bit3|bootmode_bit4|standby_fastresume_disable);
			bit_print_test(unOTPData);

			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		{
			//config 0xE7			---> bit by bit write protection for OTP 0xDC addr
			unOTPAddr = 0xE7;
			unsigned int E7_zone_bit0 = 0x01<<0;	//conax confirmed: 0xE7[ 30, 29, 4, 3, 2, 1, 0] is set to 1.
			unsigned int E7_zone_bit1 = 0x01<<1;
			unsigned int E7_zone_bit2 = 0x01<<2;
			unsigned int E7_zone_bit3 = 0x01<<3;
			unsigned int E7_zone_bit4 = 0x01<<4;
			unsigned int E7_zone_bit29 = 0x01<<29;
			unsigned int E7_zone_bit30 = 0x01<<30;
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (E7_zone_bit0|E7_zone_bit1|E7_zone_bit2|E7_zone_bit3|E7_zone_bit4|E7_zone_bit29|E7_zone_bit30);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		
		{
			//config 0x5F ---OTP读写保护位,要放到JTAG关闭前、所有被保护区域写入成功后再开启
			unOTPAddr = 0x5F;
			unsigned int DD_zone_bit2 = 0x01<<2;		//Zone 2 write protect
			unsigned int DD_zone_bit7 = 0x01<<7;		//Zone 7 write protect
			unsigned int DD_zone_bit8 = 0x01<<8;		//Zone 8 write protect
			unsigned int DD_zone_bit11 = 0x01<<11;		//Zone 11 write protect
			unsigned int DD_zone_bit12 = 0x01<<12;		//Zone 12 write protect
			unsigned int DD_zone_bit15 = ~(0x00<<15);	//Zone 15 write protect
			unsigned int DD_zone_bit18 = ~(0x00<<18);		//Zone 7 read protect
			unsigned int DD_zone_bit19 = 0x01<<19;			//Zone 8 read protect
			unsigned int DD_zone_bit21 = ~(0x00<<21);		//Zone 11 read protect
			unsigned int DD_zone_bit22 = ~(0x00<<22);		//Zone 12 read protect
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}

			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (DD_zone_bit2|DD_zone_bit7|DD_zone_bit8|DD_zone_bit11|DD_zone_bit12|DD_zone_bit19);
			unOTPData &= (DD_zone_bit15|DD_zone_bit18|DD_zone_bit21|DD_zone_bit22);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}

		{
			//config 0x3 --protected by 0xE4
			unOTPAddr = 0x3;
			unsigned int close_uart = 0x01<<12;		//bootloader未关闭打印的话开启此项后booter无法启动
			unsigned int close_usb = 0x00<<20;
		    unsigned int close_ethmac = 0x01<<22;
		    unsigned int force_kl_key = 0x01<<23;	//OTP_FORCE_KL_KEY
		    unsigned int crystal_monitor_en = 0x01<<28;	//CRYSTAL_MONITOR_EN
		    nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}

			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |=(close_uart|close_usb|close_ethmac|force_kl_key|crystal_monitor_en);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
		{
			//config 0xE4		---> bit by bit write protection for OTP 0x3 addr
			unOTPAddr = 0xE4;
			unsigned int E4_zone_bit0 = 0x01<<0;	//conax confirmed: 0xE4[28, 23, 22, 20, 12, 0] is set to 1.
			unsigned int E4_zone_bit12 = 0x01<<12;	//0x3 bit12 中uart未关闭的情况下,此otp位不可开启, 否则写保护后不可修改
			unsigned int E4_zone_bit20 = 0x01<<20;
			unsigned int E4_zone_bit22 = 0x01<<22;
			unsigned int E4_zone_bit23 = 0x01<<23;
			unsigned int E4_zone_bit28 = 0x01<<28;
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (E4_zone_bit0|E4_zone_bit12|E4_zone_bit20|E4_zone_bit22|E4_zone_bit23|E4_zone_bit28);
			bit_print_test(unOTPData);
			
			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}

#if 1
		//JTAG disable !!!
		{
			//config 0xDD ------ JTAG的开启要放到最后!!
			unOTPAddr = 0xDD;
			unsigned int close_ejtag = 0x01<<2;
			unsigned int disable_etsi_kl = 0x01<<15;
		  	nRet = TS_OTP_Read(unOTPAddr*4, &unOTPData, 4);
			if(nRet != sizeof(unOTPData))
			{
				libc_printf(" 0x%x: otp_read failed before write, nRet 0x%x\n",unOTPAddr, nRet);
				break;
			}
			
			libc_printf("OTPAddr 0x%02x:  \n",unOTPAddr);
			bit_print_test(unOTPData);
			unOTPData |= (close_ejtag|disable_etsi_kl);
			bit_print_test(unOTPData);

			OTP_Write_Test(unOTPAddr, unOTPData, sizeof(unOTPData));
			ADIOSThreadSleep(100);
			libc_printf("\n");
		}
#endif
		unFinish = 1;
		
	}while(0);
	
	libc_printf("\n[%s] @@@@@@@@ Test 222222 End @@@@@@@@unFinish=%d\n",__FUNCTION__, unFinish);
	
	return unFinish;
}

int ConaxOTASupport::TS_OTP_Read(unsigned int addr, unsigned int *punValue, unsigned int unSize)
{
	int nRet = 0;
	unsigned char ucOTPData[4] = {0};

	if(ADIOTPRead( addr, ucOTPData, 4) == ADI_SUCCESS)
	{
		*punValue = (unsigned int)((ucOTPData[3] << 24)|(ucOTPData[2] << 16)|(ucOTPData[1] << 8)|ucOTPData[0]);
		
		nRet = 4;
	}
	
	return nRet;
}

int ConaxOTASupport::WriteBootFile(void)
{
	int nRet = 0;
	unsigned char *pTemp = NULL;
	unsigned int unDataLen = 0xA0000;
	unsigned int unActReadLen = 0;
	unsigned int unStartAddr[2] = { 0x650000, 0x700000 };
	SerialBuf tempSerialBuf;

	do
	{
		pTemp = (unsigned char*)APMalloc(unDataLen);
		if(pTemp == NULL)
		{
			tempSerialBuf.WriteLog("--[%s][%d]--APMalloc fail-\n", __FUNCTION__, __LINE__);
			break;
		}
		
		//read encrypt boot
		for(int ii = 0; ii < 2; ii++)
		{
			memset(pTemp , 0, unDataLen);
			
			if(ADI_SUCCESS != ADIFlashRead(unStartAddr[ii], pTemp, unDataLen))
			{
				tempSerialBuf.WriteLog("--[%s][%d]--ADIFlashRead fail-\n", __FUNCTION__, __LINE__);
				continue;
			}
			unActReadLen = (unsigned int)((unsigned int)(pTemp[0] << 24) | (unsigned int)(pTemp[1] << 16) | (unsigned int)(pTemp[2] << 8) | (unsigned int)pTemp[3]);
			if(unActReadLen > 0x90000)
			{
				tempSerialBuf.WriteLog("--[%s][%d]--Read fail unActReadLen:0x%x-\n", __FUNCTION__, __LINE__, unActReadLen);
				continue;
			}
			tempSerialBuf.WriteLog("--[%s][%d]--unActReadLen:0x%x-\n", __FUNCTION__, __LINE__, unActReadLen);
			tempSerialBuf.WriteLog("--[%s][%d]--%x %x %x %x-\n", __FUNCTION__, __LINE__, pTemp[4+unActReadLen], pTemp[5+unActReadLen], pTemp[6+unActReadLen], pTemp[7+unActReadLen]);
			if(CheckCRC32(&pTemp[4], unActReadLen+4) == 0)
			{
				tempSerialBuf.WriteLog("--[%s][%d]--CheckCRC32 fail-\n", __FUNCTION__, __LINE__);
				continue;
			}

			//write encrypt boot
			if(ADI_SUCCESS != ADIFlashWrite(0x0, &pTemp[4], unActReadLen))
			{
				tempSerialBuf.WriteLog("--[%s][%d]--ADIFlashWrite fail-\n", __FUNCTION__, __LINE__);
				continue;
			}
		
			nRet = 1;

			break;
		}
	}while(0);

	if(pTemp != NULL)
	{
		APFree(pTemp);
	}
	
	tempSerialBuf.WriteLog("--[%s][%d]--nRet:%d-\n", __FUNCTION__, __LINE__, nRet);

	return nRet;
}
