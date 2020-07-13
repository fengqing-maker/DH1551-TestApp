
#ifndef _IRD_APP_F_H_847528345_V5___
#define _IRD_APP_F_H_847528345_V5___

#include "adi_tuner.h"
#include "adi_bootloader_common.h"

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Max space size for manufacturer to save private data.
 *
 * Loader Partition module will reserve the space so that manufacturer can save some private data into the space, for example, tuner info.
 */
#define LC_MANUFACTURER_PRIVATE_INFO_LENGTH /*(48)*/ 128/*---ADITunerSRCDeliver_U--*/

/*Irdeto v5 bbcb结构体*/
typedef struct
{
    unsigned char OUI[3]; /**< (3 bytes) - contains an IEEE OUI */
    unsigned short manufacturer_id; /**< (2 bytes) - variable */ 
    unsigned short hardware_version; /**< (2 bytes) - variable */
    unsigned char loader_major_version; /**< (1 byte) - must be 0x05 */
    unsigned char loader_minor_version; /**< (1 byte) - variable */
    unsigned short loader_version_buildnumber; /**< (2 bytes) - variable */ 
    unsigned char boot_check_algorithm; /**< (1 byte) - 0x00 refers to CRC32; 
                                                  0x01 refers to MAC
                                                  0x02 refers to RSASSA-PKCS1-v1_5
                                                  0x03~0xff reserved  */
    unsigned char serial_number[4]; /**< (4 bytes) - variable */
    unsigned char random_number[4]; /**< (4 bytes) - variable */
    unsigned int crc32; /**< (4 bytes) - the checksum of the entire boot block (except itself). */
    
} ADIIrdetoBBCBV5_S;

/*Irdeto v5 flash配置枚举*/
typedef enum
{
	E_FLASH_BOOTER_V5 = 0,
	E_FLASH_LOADER_V5 = 1,
	E_FLASH_BBCB_V5 = 2,
	E_FLASH_UK_V5 = 3,
	E_FLASH_VARIANT_V5 = 4,
	E_FLASH_LOADER_PT_V5 = 5,
	E_FLASH_RESET_MODIFIED_V5 = 6,
	E_FLASH_SYSSETTING_V5 = 7,
	E_FLASH_LOGO_V5 = 8,
	E_FLASH_APP_V5 = 9,
	E_FLASH_MAX
}ADIIrdetoBLFlashTypeV5_E;

/*+++++++++++++++4字节对齐+++++++++++*/
/*由于项目的bbcb和flash配置都是固定的,所以将bbcb+flashcfg(以下结构体)作为一个block*/
typedef struct
{
	ADIBLFlashBlock_S m_stFshBooterv5;/*booter 12bytes*/
	ADIBLFlashBlock_S m_stFshLoaderv5;/*loader 12bytes*/
	ADIBLFlashBlock_S m_stFshBBCBv5;/*bbcb 12bytes*/
	ADIBLFlashBlock_S m_stFshUKv5;/*key 12bytes*/
	ADIBLFlashBlock_S m_stFshVariantv5;/*key 12bytes*/
	ADIBLFlashBlock_S m_stFshLoaderPTv5;/*loader pt 12bytes*/
	ADIBLFlashBlock_S m_stFshResetModifiedFlagv5;/*loader pt 12bytes*/
	ADIBLFlashBlock_S m_stFshSYSSettingv5;/*sys set 12bytes*/
	ADIBLFlashBlock_S m_stFshLogov5; /*logo 12bytes*/
	ADIBLFlashBlock_S m_stFshAppv5;/*app 12bytes*/
	unsigned int m_unVirEEpromAddrv5; /*vir eeprom起始地址 4bytes*/
	unsigned int m_unVirEEpromTotalSizev5; /*vir eeprom使用flash的总大小 4bytes*/
	unsigned int m_unVirEEpromUnitSizev5; /*vir eeprom一个最小单元的大小 4bytes*/
	unsigned int m_unCrc32;/*crc32 4bytes*/
}ADIIrdetoBLFlashCfgInfoV5_S;

typedef struct
{
    /**
     * This 8-bit field indicates whether we have found a valid migration EMM.
     */
    ADI_BOOL validMigrationEmm;

    /** variant value obtained from the IRD EMM. */
    unsigned short variant;

    /** sub-variant value obtained from the IRD EMM. */
    unsigned short subVariant;
    
} ADIBLIrdetoEmmParamforMigrationV5_S;


/**
 * DVB-SSU parameters obtained from NIT table
 *
 * This structure is used to obtain the key parameters for DVB-SSU from NIT table.
 * 
 */
typedef struct
{
    /**
     * This 16-bit field indicates the Service ID of the SSU service.
     */
    unsigned short serviceId;
	unsigned short transportId; /*transportId*/
	unsigned short originalNetworkId;  /*originalNetworkId*/
            
    struct
    {
        /**
          * This 8-bit field indicates the download mode of the SSU service.
          */
        unsigned char downloadMode;

        /**
          * This 8-bit field indicates the trigger control mode of the SSU service.
          */
        unsigned char triggerControlMode;
                
    } selectorByte_s;
            
}ADIBLIrdetoParamFromNITV5_S;

/**
 * DVB-SSU parameters obtained from PMT table
 *
 * This structure is used to obtain the key parameters for DVB-SSU from PMT table.
 * 
 */
typedef struct
{
    /**
     * This 16-bit field indicates the PID of the SSU service.
     */
    unsigned short ssuPid;

    /**
     * This 48-byte field indicates the private data the SSU service requires usually containing 
     * necessary tuner information, which has a user-defined format. 
     * \note Loader Core does not parse or utilize the data in this field and just supply it 
     * as an argument in the SPI function call ::LoaderCoreSPI_DEMUX_OpenChannel.
     * 
     */
    unsigned char manufacturerPrivateData[LC_MANUFACTURER_PRIVATE_INFO_LENGTH];
            
} ADIBLIrdetoParamFromPMTV5_S;


/**
 * DVB-SSU parameters from SI or PSI
 *
 * This structure is used to obtain the key parameters for DVB-SSU from SI/PSI tables.
 * 
 */
typedef union
{
    /** Parameters from NIT table */
    ADIBLIrdetoParamFromNITV5_S nitSpec;

    /** Parameters from PMT table */
    ADIBLIrdetoParamFromPMTV5_S pmtSpec;
    
} ADIBLIrdetoParamFromSiPsiV5_U;


/**
 * DVB-SSU parameters structure
 *
 * This structure is used to obtain the result for detecting valid SSU and 
 * key parameters of DVB-SSU from SI/PSI tables.
 * 
 */
typedef struct
{
    /**
     * This 8-bit field indicates whether we have found a valid update in SI/PSI.
     */
    ADI_BOOL validUpdate;

    /** Parameters from SI/PSI table */
    ADIBLIrdetoParamFromSiPsiV5_U data;
    
}ADIBLIrdetoSIParamFordvbssuV5_S;

/*
 * Description: 初始化irdeto项目flashmap, booter loader app工程都必须要调用此接口配置整个flash分区信息
 *
 * Parameters : unAddress-配置分区表在flash中的位置<紧跟bbcb之后>
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIIrdetoBLFlashInfoConfigV5(unsigned int unAddress);

int ADIBLIrdetoGetSYSSettingV5(ADIBLSYSSetting_S * pstSysSetting);

int ADIBLIrdetoSetSYSSettingV5(ADIBLSYSSetting_S stSysSetting);

int ADIBLIrdetoSaveOTALoaderPtV5(ADIBLOtaLoaderPt_S*  pstOtaLoaderPt, ADI_BOOL bEnableOTAFlag);

int ADIBLIrdetoGetKeyInfoV5(unsigned short* pSystemId,  unsigned short* pKeyVersion, unsigned short* pSignatureVersion);

int ADIBLIrdetoGetDownloadSequenceNumberV5(unsigned short *pDownloadSequenceNumber);

int ADIBLIrdetoGetVariantV5(unsigned short *pVariant, unsigned short *pSubVariant);

unsigned short ADIBLIrdetoGetManufacturerCodeV5(void);

unsigned short ADIBLIrdetoGetHardwareVersionV5(void);

int ADIBLIrdetoGetBBCBV5(ADIIrdetoBBCBV5_S * pstBBCBV5);


/**
 * Init the Irdeto V5 loader
 *
 * This function can be called to Init the Irdeto V5 loader
 *
 * @note If not call this function, the read/write operate of loaderpt will failed
 *
 * @param void
 * 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */ 
int ADIBLIrdetoAppInitV5(void);

/**
 * Read app module version
 *
 * This function can be called to get the module version of application   
 *
 * @param[in/out] pAppModuleVersion: the module version of application. 
 * 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */ 
int ADIBLIrdetoGetAppModuleVersionV5(unsigned short *pAppModuleVersion);

/**
 * Read app flash end address
 *
 * This function can be called to get the end address of application, IF RC addto LzmaApp with no space, It can get RC Flash start address. 
 *
 * @param[in/out] punAddress: app flash end address. 
 * 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */ 
int ADIBLIrdetoGetAppEndFlashAddressV5(unsigned int *punAddress);

//设置OTA下载缺省的超时时间,单位毫秒, 如果0xFFFFFFFF永远不超时
int ADIBLIrdetoSetOTADefaultTimeoutV5(unsigned int unTimeoutMS);

#ifdef	__cplusplus
}
#endif


#endif


