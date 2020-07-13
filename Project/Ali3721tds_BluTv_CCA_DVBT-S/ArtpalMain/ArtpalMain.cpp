
#include "MSWindows.h"
#include "Aura.h"
#include "adi_os.h"
#include "adi_osg.h"
#include "AuraMain.h"
#include "adi_debug.h"
#include "adi_irdeto_bl_v5.h"
#include "adi_flash.h"
#include "adi_toolset.h"
#include "adi_panel.h"
#include "FactoryTestInit.h"
#include "STBDataInterface.h"
#include "adi_uart.h"
#include "ADI_CA_Comon.h"
#include "adi_ir.h"
#include "RemoteKey.h"
#include "ArtpalMain.h"
#include "../HardWareConfig/FlashMapConfig.h"
#include "adi_scart.h"
#include "adi_screen.h"
#include "adi_hdmi.h"
#include "adi_fs.h"
#include "adi_secure.h"


#define SPECIAL_RAMADDR_4DUMP (0x83000000)	//对应booter加密接口Encrypt_Maincode() 中ENC_MAIN_CODE_ADDR
#define DUMPED_IMAGE_MAXSIZE (0x800000)
static char  g_acUSBDumpFile[]="dumped_appenc_image.bin";

#define SW_ENCRYPT_STRING 	"ENCCASTPAL4DEC_"
#define SW_ENCRYPT_HEADLEN 	(0x10)
#define USB_DEVICES_MAX_CNT (32)
#define USB_ATTEMPT_MAX  (3)

extern void InitUSBBackDoor(unsigned int unByteFlag, unsigned int unFlashSize, char *pBacDoorFile);

static unsigned int BLInit( void );
void Dump_EncryptedImage_Test(unsigned int unDumpAddr, unsigned int unDumpSize);

int TestAppDetectUSBFile(char *pUSBFileName, int nNameLen, char *pFilepath, int nPathLen)
{
	int ii = 0;
	int nIDCountt = 0;
	int nLen = 0;
	unsigned int unRet = 0;
	ADIFSDeviceInfo_S sDeviceInfo;
	unsigned int adwId[32];
	char acMountPath[256] = {0};
	char acCompletePath[512] = {0};

	ADIOSThreadSleep(2000); /* 等待USB挂载 */
	for(ii=0; ii<5; ii++)
	{
		unRet = ADIFSGetAllDeviceId((int*)adwId, 32, &nIDCountt);
		printf("[%s %d]unRet=%d,nIDCountt=%d\r\n", __FUNCTION__, __LINE__, unRet, nIDCountt);
		if (0 != unRet)
		{
			return -1;
		}

		if(nIDCountt > 0 )
		{			
			break;
		}
		ADIOSThreadSleep(1000);
	}

	for (ii = 0; ii < nIDCountt; ii++)
	{
		unRet = ADIFSGetDeviceInfo(adwId[ii], &sDeviceInfo);
		printf("[%s %d]unRet=%d,MountPoint:%s\r\n", __FUNCTION__, __LINE__, unRet,sDeviceInfo.m_szMountPoint);
		if ( 0 != unRet)
		{
			continue;
		}

		snprintf(acMountPath, sizeof(acMountPath), "%s", sDeviceInfo.m_szMountPoint);
		nLen = strlen(acMountPath);		
		if ((nLen <= 0) || (nLen >= ADI_MAX_FILE_NAME_LEN))
		{
			continue;
		}
		if (acMountPath[nLen - 1] != '/')
		{
			acMountPath[nLen] = '/';
			acMountPath[nLen + 1] = '\0';
			nLen++;
		}

		snprintf(acCompletePath, sizeof(acCompletePath), "%s%s", acMountPath, pUSBFileName);
		printf("[%s %d]pFilepath=%s\r\n", __FUNCTION__, __LINE__, acCompletePath);
		ADI_HANDLE hEcosFile = ADIFSOpen((const char *)acCompletePath, (const char *)"rb");
		if (hEcosFile != 0)
		{
			unsigned char aucStr[512] = {0};
			int Readlen = ADIFSRead(hEcosFile, aucStr, sizeof(aucStr));
			printf("[%s %d]Readlen=%d\r\n", __FUNCTION__, __LINE__, Readlen);
			ADIFSClose(hEcosFile);
			memcpy(pFilepath, acCompletePath, strlen(acCompletePath));
			
			return 0;
		}
	}			

	return -2;
}

void ReadConfigFile( char *pFilepath, int nPathLen )
{
	if(pFilepath != NULL && nPathLen > 0)
	{
		if(TestAppDetectUSBFile((char*)"Factory.xml", sizeof("Factory.xml"), pFilepath, nPathLen) != 0)
		{
			printf("Can not find file Factory.xml\n");
		}
	}
}

void artpal_main ( void )
{
	ADIUartDisable ( 0, ADI_FALSE ); //ADI_TRUE关掉所有串口打印,ADI_FALSE 打开打印

	ADISYSSetCfg ( ADICFG_PANEL_TYPE, 0, EM_ADIPANEL_TYPE_GPIO, 0 );

	ADISYSSetCfg(ADICFG_TUNER_TYPE, 0, EM_ADITUNER_TYPE_QPSK, EM_ADITUNER_TYPE_COFDM);

	//ADISYSSetCfg ( ADICFG_AVSYNC_MOD, 0, EM_ADISYS_AVSYNC_AUDIO, 0 );

	ConfigSTBDataInfo ( MAC_SN_HDCP_KEY_FLASH_ADDR, MAC_SN_HDCP_KEY_FLASH_SIZE, STB_DATA_DEBUG_LEVEL );

	SetIFCPAddress(CCA_IFCP1, CCA_IFCP1_SIZE);

	ADISYSInit ( );

	ADIPlatformInit ( );

	ADIPlatformInitDelay ( );

	BLInit();
	
	MSAppIrInit();
	
	char acConfig[512] = { 0 };

	ReadConfigFile(acConfig,  sizeof(acConfig));
	
	if(FactoryTestInit1( EM_ADISMC_PROTOCOL_T14, acConfig, strlen(acConfig) ) == 0)
	{
		FactoryTestInit(EM_ADISMC_PROTOCOL_T14, FACTORY_TEST_CFG_ADDR, FACTORY_TEST_CFG_SIZE);
	}

	InitUSBBackDoor(0, 0x1600000, "TestApp_usb4227up.bin");

	AuraMain();

	//Dump_EncryptedImage_Test(SPECIAL_RAMADDR_4DUMP, 0x400000);
}

static unsigned int BLInit( void )
{
	ADIIrdetoBLFlashCfgInfoV5_S IrdflashCfg;
	int nRet = 0;

	ADIFlashRead ( FLASH_MAP_CFG, ( unsigned char* ) &IrdflashCfg, sizeof( IrdflashCfg ) );

	ADIIrdetoBLFlashInfoConfigV5 ( FLASH_MAP_CFG );

	nRet = ADIBLVirEEPROMRegister ( IrdflashCfg.m_stFshUKv5.m_unStartAddress, IrdflashCfg.m_stFshUKv5.m_unTotalSize, 4096, 0 );
	ADIASSERT ( nRet != 0 );

	nRet = ADIBLVirEEPROMRegister ( IrdflashCfg.m_stFshVariantv5.m_unStartAddress, IrdflashCfg.m_stFshVariantv5.m_unTotalSize, 4096, 0 );
	ADIASSERT ( nRet != 0 );

	ADIBLInitVirEEPROM ( IrdflashCfg.m_unVirEEpromAddrv5, IrdflashCfg.m_unVirEEpromTotalSizev5, IrdflashCfg.m_unVirEEpromUnitSizev5 );

	ADIBLIrdetoAppInitV5 ( );
	
	return 1;
}

static ADI_BOOL is_castpal_sw_enc(unsigned char *maincode_head)
{		
	if(NULL == maincode_head)	
	{		
		printf("[is_castpal_sw_enc] bad param maincode_head 0x%x!!\n",maincode_head);
		return ADI_FALSE;
	}
	if(0 != strncmp(maincode_head, SW_ENCRYPT_STRING, sizeof(SW_ENCRYPT_STRING) -1))
	{		
		return ADI_FALSE;
	}	
	else
	{		
		return ADI_TRUE;
	}
}

void Dump_EncryptedImage_Test(unsigned int unDumpAddr, unsigned int unDumpSize)
{	 
	int ret = 0;

	do
	{
		printf("[%s %d] ====> start\n",__FUNCTION__,__LINE__);		
		unsigned char *pDumpBuf = 0;
		ADI_HANDLE hFileHandle = 0;
		char acName[256] = {'\0'};
		
		//当前设置为最大支持16 M Flash
		if((SPECIAL_RAMADDR_4DUMP == unDumpAddr) && (DUMPED_IMAGE_MAXSIZE >= unDumpSize))
		{
			printf("[%s %d]read image from special RAM addr unDumpAddr: 0x%x\n", __FUNCTION__, __LINE__, unDumpAddr);
			pDumpBuf = SPECIAL_RAMADDR_4DUMP;
			if(ADI_TRUE != is_castpal_sw_enc(pDumpBuf))
			{
				printf("[%s %d] return with is_castpal_sw_enc: \n",__FUNCTION__,__LINE__);
				unsigned int ii = 0;
				for(ii=0; ii<0x20; ii++)
				{
					printf(" %02x ",pDumpBuf[ii]);
				}
				printf("\n");
				break;
			}
		}
		else if((0 == unDumpAddr) || (0 == unDumpSize) || (DUMPED_IMAGE_MAXSIZE < unDumpSize) || (0x1000000 < (unDumpAddr+unDumpSize)))
		{			
			printf("[%s %d] param error: unDumpAddr 0x%x，unDumpSize 0x%x\n",__FUNCTION__,__LINE__, unDumpAddr,unDumpSize);
			break;
		}
	
		//find usb first
		{
			int i = 0;
			int nIDCountt = 0;
			int nLen = 0;
			unsigned int adwId[USB_DEVICES_MAX_CNT];
			ADIFSDeviceInfo_S sDeviceInfo;
			unsigned int unRet = 0;

			for(i=0; i<USB_ATTEMPT_MAX; i++)
			{
				unRet = ADIFSGetAllDeviceId((int*)adwId, 32, &nIDCountt);
				printf("[%s %d]ADIFSGetAllDeviceId i:%d dwRet:%d, nIdCnt:%d\n", __FUNCTION__, __LINE__,i,unRet, nIDCountt);

				if((nIDCountt > 0) && (0 == unRet)) // OK
				{			
					break;
				}
				else
				{
					ADIOSThreadSleep(2000);
					continue;
				}
			}

			for (i = 0; i < nIDCountt; i++)
			{
				printf("[%s %d]adwId[%d]:0x%x\n", __FUNCTION__, __LINE__,i, adwId[i]);
				unRet = ADIFSGetDeviceInfo(adwId[i], &sDeviceInfo);
				
				printf("[%s %d]ADIFSGetDeviceInfo, dwRet:%d\n", __FUNCTION__, __LINE__,unRet);
				if ( 0!= unRet)
				{
					continue;
				}

				nLen = strlen(sDeviceInfo.m_szMountPoint);
				if ((nLen <= 0) || (nLen >= ADI_MAX_FILE_NAME_LEN))
				{
					printf("[%s %d]nLen:%d ERROR\n", __FUNCTION__, __LINE__, nLen);
					continue;
				}
				if (sDeviceInfo.m_szMountPoint[nLen - 1] != '/')
				{
					sDeviceInfo.m_szMountPoint[nLen] = '/';
					sDeviceInfo.m_szMountPoint[nLen + 1] = '\0';
					nLen++;
				}

				snprintf(acName, sizeof(acName)-1, "%s%s", sDeviceInfo.m_szMountPoint, g_acUSBDumpFile);
				//g_hSDLFile = ADIFSOpen((const char *)acName, (const char *)"r");
			}

			if(0 == strlen(acName))
			{
				printf("[%s %d]Failed with no usb inserted for dump!!\n", __FUNCTION__, __LINE__);
				break;
			}
		}
		printf("[%s %d]ADIFSOpen acName:%s\n", __FUNCTION__, __LINE__, acName);
		hFileHandle = ADIFSOpen((const char *)acName, "wb");
		printf("[%s %d]ADIFSOpen hFileHandle: 0x%x\n", __FUNCTION__, __LINE__, hFileHandle);
		if(0 == hFileHandle)
		{
			printf("[%s %d] ADIFSOpen dumped_image.bin failed!!\n");
			break;
		}
		else
		{
			if(SPECIAL_RAMADDR_4DUMP != unDumpAddr)
			{
				pDumpBuf = (unsigned char *)ADIOSMalloc(unDumpSize);
				printf("[%s %d]ADIOSMalloc pDumpBuf: 0x%x\n", __FUNCTION__, __LINE__, pDumpBuf);
				if(0 == pDumpBuf)
				{
					printf("[%s %d]malloc unDumpSize(0x%x) failed...\n", __FUNCTION__, __LINE__, unDumpSize); 
					break;
				}
				printf("[%s]read flash for unDumpAddr 0x%x , unDumpSize 0x%x\n", __FUNCTION__, unDumpAddr, unDumpSize);
				ret = ADIFlashRead(unDumpAddr, pDumpBuf, unDumpSize);
				if(0 != ret)
				{
					printf("[%s] ADIFlashRead failed with ret 0x%x\n", __FUNCTION__, ret);
					break;
				}
			}
			else
			{
				pDumpBuf = SPECIAL_RAMADDR_4DUMP;
			}

			if(unDumpSize >= 0x20)
			{
				
				printf("\n[decrypted data] pDumpBuf 0x%x, unDumpSize 0x%x\n",pDumpBuf, unDumpSize);
				unsigned int ii = 0;
				for(ii=0; ii<0x20; ii++)
				{
					printf(" %02x ",pDumpBuf[ii]);
				}
				printf("\n");
				for(ii=0x20; ii>0; ii--)
				{
					printf(" %02x ",pDumpBuf[unDumpSize-ii]);
				}
				printf("\n");
			}
		
			printf("[%s %d]ADIFSWrite hFileHandle 0x%x from pDumpBuf 0x%x\n", __FUNCTION__, __LINE__, hFileHandle, pDumpBuf);
			ret = ADIFSWrite(hFileHandle, (char*)pDumpBuf, unDumpSize);
			printf("[%s %d]ADIFSWrite unDumpSize 0x%x with ret: 0x%x\n", __FUNCTION__, __LINE__,unDumpSize, ret);
			if(unDumpSize != ret)
			{
				printf("[dump key]write flash dumped_image.bin failed, ret:0x%x...\n", ret);
			}
			else
			{
				printf("[dump key]write flash dumped_image.bin OK...\n");
			}
			/* 注意: 写文件操作之后必须再刷新一下才起作用!!!*/
			ret = ADIFSFlush(hFileHandle);
			printf("[%s %d]ADIFSFlush ret: 0x%x\n", __FUNCTION__, __LINE__, ret);
			ADIOSThreadSleep(3000);
		}

		if((0 != pDumpBuf)&&(SPECIAL_RAMADDR_4DUMP != pDumpBuf))
		{
			printf("[%s %d]ADIOSFree pDumpBuf: 0x%x\n", __FUNCTION__, __LINE__, pDumpBuf);
			ADIOSFree((void * )pDumpBuf);
			printf("[%s %d]ADIOSFree pDumpBuf: 0x%x\n", __FUNCTION__, __LINE__, pDumpBuf);
		}
		if(0 != hFileHandle)
		{			
			printf("[%s %d]ADIFSClose hFileHandle: 0x%x\n", __FUNCTION__, __LINE__, hFileHandle);
			ADIFSClose(hFileHandle);
			printf("[%s %d]ADIFSClose hFileHandle: 0x%x\n", __FUNCTION__, __LINE__, hFileHandle);
		}
	}while(0);

	return;
}

ADI_Error_Code ADIScartColorModeSwitch( ADIScartIndex_E Scart, ADIScartColorMod_E ColorMode)
{
	return 0;
}

ADI_Error_Code ADIScartSetAspectRatio( ADIScartIndex_E Scart,  ADIScartDisplayMod_E DisplayMode)
{
	return 0;
}

ADI_Error_Code ADIToolsetLoadMainCode(unsigned char *maincode_buf,unsigned int maincode_len)
{
	return 0;
}

ADI_Error_Code ADIToolsetLoadSeeCode(unsigned char *see_code_buf,unsigned int see_code_len)
{
	return 0;
}
