/**
 * @file LoaderCoreAPI_ApplicationHelper.h
 * Loader Core API for High Level Application as helper functions.
 */
#ifndef LOADERCOREAPI_APPLICATIONHELPER_H__INCLUDED__
#define LOADERCOREAPI_APPLICATIONHELPER_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup loadercoreapis Loader Core APIs
 *  Loader Core APIs
 *
 *  These APIs provide their interfaces to start Loader Core and to read/write all necessary information from/to Loader Core.
 *  
 *  @{
 */


/** @defgroup ApplicationHelperAPIs Application Helper APIs
 *  Application Helper APIs
 *
 *  These API methods provide helper functions to high level application for convenience. 
 *
 *  @{
 */

/** 
 *  Download Types
 *  List of all possible values of ::lc_download_type codes. 
 *
 */
typedef enum _lc_download_type
{

    /** (0x00) No download required. */
    NONE_DOWNLOAD           = 0x00,

    /** (0x01) Serial download (e.g. UART, USB Serial, Flash Disk) */
    SERIAL_DOWNLOAD         = 0x01,

    /** (0x02) OTA download */
    OTA_DOWNLOAD            = 0x02
    
} lc_download_type;


/** 
 *  Boot Check algorithm.
 */
typedef enum _lc_bootcheck_algorithm
{

    /** 0x00 refers to CRC32 */
    LC_BOOTCHECK_CRC32 = 0x00,

    /** 0x01 refers to MAC */
    LC_BOOTCHECK_MAC = 0x01,
    
    /** 0x02 refers to Digital Signature Verification  */
    LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION = 0x02
    
} lc_bootcheck_algorithm;


/**
 * Boot Block Control Block parameters structure
 *
 * This structure is used to save Boot Block Control Block parameters.
 * The parameters can be serialized into or de-serialized from flash.
 * 
 */
typedef struct _lc_bbcb_parameters
{

    /**
     * This 24-bit field contains the IEEE OUI assigned to this manufacturer.
     */ 
    lc_uchar OUI[3];

    /**
     * This 16-bit field contains the manufacturer code assigned to this client device.
     */ 
    lc_uint16 manufacturer_id;

    /**
     * This 16-bit field contains the hardware version code assigned to this client device. 
     */
    lc_uint16 hardware_version; 

    /**
     * This 8-bit field contains the major version number of the loader software. 
     * 3 for loader v3.x and 5 for loader v5.x.
     */
    lc_uchar loader_major_version; 

    /**
     * This 8-bit field contains the minor version number of the loader software.  
     */
    lc_uchar loader_minor_version; 

    /**
     * This 16-bit field contains the build version number of the loader software.  
     */
    lc_uint16 loader_version_buildnumber; 

    /**
     * This 8-bit field contains the boot check algorithm of the loader software.  
     * The value can be: 
     * 0x00, refers to CRC32;
     * 0x01, refers to MAC;
     * 0x02, refers to RSASSA-PKCS1-v1_5;
     * 0x03~0xff are reserved
     */
    lc_uchar boot_check_algorithm; 

    /**
     * These 32-bit fields are specified by the manufacturer.  
     */
    lc_uchar serial_number[4]; 

    /**
     * These 32-bit fields are specified by the manufacturer.  
     */
    lc_uchar random_number[4]; 

    /**
     * This 32-bit field contains the CRC of the entire boot block, including boot block control block, boot strap and boot loader,
     * excluding the two bytes CRC_32 field itself.
     */
    lc_uint32 crc32; 

} lc_bbcb_parameters;    


/**
 * DVB-SSU parameters structure
 *
 * This structure is used to save DVB-SSU parameters into NVRAM Loader Partition.
 * 
 */
typedef struct _lc_dvb_ssu_parameters
{
    /**
     * This 13-bit field contains the PID of DSM-SC sections.
     */
    lc_uint16 pid;
    
} lc_dvb_ssu_parameters;


/**
 * Init application module.
 *
 * This function shall be called before other functions are called.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_InitApplicationModule(void);

/**
 * Write parameters to Boot Block Control Block.
 *
 * This function can be called to write the Boot Block Control Block parameters into flash. 
 *
 * @param[in] updateCRC Whether or not to recalculate a CRC value.
 *     If set to LC_TRUE, this function will recalculate a CRC value before writing the byte array into the flash.
 *     If set to LC_FALSE, this function will use the crc value contained in pBBCBParameters.
 *
 * @param[in] pBBCBParameters Saves the parameters to be written into flash.
 *     Parameters in this structure will be serialized into Boot Block Control Block whose format is defined in the loader spec.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_WriteBBCB(lc_bool updateCRC, const lc_bbcb_parameters *pBBCBParameters);


/**
 * Read parameters from Boot Block Control Block.
 *
 * This function can be called to read the BBCB parameters from flash. 
 * When called, this function will de-serialize the byte array from Boot Block Control Block to output all parameters.
 *
 * @param[out] pBBCBParameters Saves the parameters that have been read from flash.
 *     Parameters in this structure are got from Boot Block Control Block whose format is defined in the loader spec.
 * @param[out] pUpdateCRC Returns whether the CRC16 in Boot Block Control Block is correct.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_ReadBBCB(lc_bbcb_parameters *pBBCBParameters, lc_bool *pUpdateCRC);

/**
 * Write flag for enable/disable Loader Core download as well as download type into NVRAM Loader Partition.
 *
 * This function can be called to write flag for enable/disable Loader Core download as well as download type into NVRAM Loader Partition 
 * when high level wants to launch an OTA download.
 * When called, it will update the download type stored in the NVRAM Loader Partition.
 *
 * @param[in] enableDownload indicates the flag for enable/disable OTA download to be set into NVRAM Loader Partition.
 *     LC_TRUE for enable while LC_FALSE for disable.
 * @param[in] downloadType indicates type of download. See \ref lc_download_type "Download Types"
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_SetDownloadFlag( lc_bool enableDownload, lc_download_type downloadType);

/**
 * Read UK information.
 *
 * This function can be called to read system ID and key version of UK from local storage. 
 *
 * @param[out] pSystemId returns the key system id.
 * @param[out] pKeyVersion returns the key version.
 * @param[out] pSignatureVersion returns the signature version.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_GetUKInfo(lc_uint16* pSystemId, lc_uint16* pKeyVersion, lc_uint16* pSignatureVersion);

/**
 * Read download sequence number (download version).
 *
 * This function can be called to read DVB-SSU parameters from local storage. 
 *
 * @param[out] pDownloadSequenceNumber returns the value of download sequence number (download version).
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_GetDownloadSequenceNumber(lc_uint16 *pDownloadSequenceNumber);

/**
 * Read variant data.
 *
 * This function can be called to read current variant and sub-variant from local storage. 
 *
 * @param[out] pVariant returns the value of variant.
 * @param[out] pSubVariant returns the value of sub-variant.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_GetVariant(lc_uint16 *pVariant, lc_uint16 *pSubVariant);

/**
 * Read ISIGN information from the latest download information.
 *
 * This function can be called to read ISIGN's version and serial number from the latest 
 * download information. 
 *
 * @param[out] iSignVersion returns the version of ISIGN.
 * @param[out] iSignSN returns the serial number of ISIGN.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_GetISignInfo(lc_char iSignVersion[4], lc_char iSignSN[4]);

/** @} */


/** @defgroup MigrationAPIs Migration helper APIs
 *  Migration helper APIs
 *
 *  These API methods provide helper functions to high level application for migration. 
 *
 *  @{
 */


/**
 * migration parameters structure
 *
 * This structure is used to obtain the result for parsing IRD EMM for migration.
 * \note The lc_emm_parameters_for_migration::variant and lc_emm_parameters_for_migration::subVariant can only be 
 * used when the lc_emm_parameters_for_migration::validMigrationEmm equals to ::LC_TRUE.
 * 
 */
typedef struct _lc_emm_parameters_for_migration
{
    /**
     * This 8-bit field indicates whether we have found a valid migration EMM.
     */
    lc_bool validMigrationEmm;

    /** variant value obtained from the IRD EMM. */
    lc_uint16 variant;

    /** sub-variant value obtained from the IRD EMM. */
    lc_uint16 subVariant;
    
} lc_emm_parameters_for_migration;


/**
 * Parse IRD EMM (clear) for migration and determine it is necessary for the STB client to trigger a migration.
 *
 * This function can be called to parse and process IRD EMM (clear) for migration, if a valid migration is found, 
 * the function will set a pair of temporary variant and sub-variant for further download detection, the temporary
 * value will be reset to default when starting to process another IRD EMM or after being used for download detection
 * by ::LoaderCoreAPI_SearchValidUpdateInNIT or ::LoaderCoreAPI_SearchValidUpdateInBAT.
 *
 * @param[in] pBuffer saves an entire IRD EMM.
 * @param[out] pMigrationParameters returns the migration information obtained from the IRD EMM.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result 
LoaderCoreAPI_SearchValidMigrationInIrdEmm(
    const lc_buffer_st *pBuffer, 
    lc_emm_parameters_for_migration *pMigrationParameters);

/**
 * Read  variant and sub-variant for migration from Loader Partition.
 *
 * This function can be called to read variant and sub-variant for migration from Loader Partition. 
 *
 * @param[out] pMigrationVariant saves the variant that have been read from Loader Pt.
 * @param[out] pMigrationSubVariant saves the sub-variant that have been read from Loader Pt.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_ReadMigrationVariant( lc_uint16 *pMigrationVariant, lc_uint16 *pMigrationSubVariant);


/**
 * Write migration variant into NVRAM Loader Partition.
 *
 * This function can be called to write migration variant into NVRAM Loader Partition. 
 *
 * @param[in] migrationVariant saves the parameters that will be saved into NVRAM Loader Pt.
 * When called, it will serialize the input parameters in the byte order of NVRAM Loader Pt and write them into NVRAM.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_WriteMigrationVariant(lc_uint16 migrationVariant);

/**
 * Write migration sub-variant into NVRAM Loader Partition.
 *
 * This function can be called to write migration sub-variant into NVRAM Loader Partition. 
 *
 * @param[in] migrationSubVariant saves the parameters that will be saved into NVRAM Loader Pt.
 * When called, it will serialize the input parameters in the byte order of NVRAM Loader Pt and write them into NVRAM.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_WriteMigrationSubVariant(lc_uint16 migrationSubVariant);

/** @} */

/** @defgroup DVBDownloadAPIs DVB Download helper APIs
 *  DVB Download helper APIs
 *
 *  These API methods provide helper functions to high level application for DVB Download. 
 *
 *  @{
 */


/**
 * DVB-SSU parameters obtained from NIT table
 *
 * This structure is used to obtain the key parameters for DVB-SSU from NIT table.
 * 
 */
typedef struct _lc_parameters_from_nit
{
    /**
     * This 16-bit field indicates the Service ID of the SSU service.
     */
    lc_uint16 serviceId;
            
    struct
    {
        /**
          * This 8-bit field indicates the download mode of the SSU service.
          */
        lc_uchar downloadMode;

        /**
          * This 8-bit field indicates the trigger control mode of the SSU service.
          */
        lc_uchar triggerControlMode;
                
    } selectorByte;
            
} lc_parameters_from_nit;

/**
 * DVB-SSU parameters obtained from PMT table
 *
 * This structure is used to obtain the key parameters for DVB-SSU from PMT table.
 * 
 */
typedef struct _lc_parameters_from_pmt
{
    /**
     * This 16-bit field indicates the PID of the SSU service.
     */
    lc_uint16 ssuPid;

    /**
     * This 48-byte field indicates the private data the SSU service requires usually containing 
     * necessary tuner information, which has a user-defined format. 
     * \note Loader Core does not parse or utilize the data in this field and just supply it 
     * as an argument in the SPI function call ::LoaderCoreSPI_DEMUX_OpenChannel.
     * 
     */
    lc_uchar manufacturerPrivateData[48];
            
} lc_parameters_from_pmt;


/**
 * DVB-SSU parameters from SI or PSI
 *
 * This structure is used to obtain the key parameters for DVB-SSU from SI/PSI tables.
 * 
 */
typedef union _lc_parameters_from_si_psi
{
    /** Parameters from NIT table */
    lc_parameters_from_nit nitSpec;

    /** Parameters from PMT table */
    lc_parameters_from_pmt pmtSpec;
    
} lc_parameters_from_si_psi;


/**
 * DVB-SSU parameters structure
 *
 * This structure is used to obtain the result for detecting valid SSU and 
 * key parameters of DVB-SSU from SI/PSI tables.
 * 
 */
typedef struct _lc_si_parameters_for_dvb_ssu
{
    /**
     * This 8-bit field indicates whether we have found a valid update in SI/PSI.
     */
    lc_bool validUpdate;

    /** Parameters from SI/PSI table */
    lc_parameters_from_si_psi data;
    
} lc_si_parameters_for_dvb_ssu;


/**
 * Search valid software update information in NIT.
 *
 * This function can be called to parse NIT table and search valid software update information. 
 *
 * @param[in] pSection saves the parameters containing the raw contents of the NIT table. 
 *     The lc_buffer_st::bytes member must point to a buffer containing the PMT, and
 *     the lc_buffer_st::length must be set to the number of bytes in the buffer.
 * @param[out] pParameters returns the key parameters obtained from the NIT (and the descriptors), 
 *     containing a valid service for software update.
 * 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result 
LoaderCoreAPI_SearchValidUpdateInNIT(
    const lc_buffer_st *pSection, 
    lc_si_parameters_for_dvb_ssu *pParameters);

/**
 * Search valid software update information in BAT.
 *
 * This function can be called to parse BAT table and search valid software update information. 
 *
 * @param[in] pSection saves the parameters containing the raw contents of the BAT table. 
 *     The lc_buffer_st::bytes member must point to a buffer containing the BAT, and
 *     the lc_buffer_st::length must be set to the number of bytes in the buffer.
 * @param[out] pParameters returns the key parameters obtained from the BAT (and the descriptors), 
 *     containing a valid service for software update.
 * 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */ 
lc_result 
LoaderCoreAPI_SearchValidUpdateInBAT(
    const lc_buffer_st *pSection, 
    lc_si_parameters_for_dvb_ssu *pParameters);

/**
 * Search valid software update information in PMT.
 *
 * This function can be called to parse PMT table and search valid software update information 
 * of a specific service. 
 *
 * @param[in] pSection saves the parameters containing the raw contents of the PMT table. 
 *     The lc_buffer_st::bytes member must point to a buffer containing the PMT, and
 *     the lc_buffer_st::length must be set to the number of bytes in the buffer.
 * @param[in] serviceId indicates the service ID of a specific software update service. 
 * @param[out] pParameters returns the key parameters obtained from the PMT (and the descriptors), 
 *     containing the PID and other information (e.g., tuned parameters) of a valid software update 
 *     service.
 * 
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */    
lc_result 
LoaderCoreAPI_SearchValidUpdateInPMT(
    const lc_buffer_st *pSection, 
    lc_uint16 serviceId, 
    lc_si_parameters_for_dvb_ssu *pParameters);



/**
 * Write DVB-SSU parameters into NVRAM Loader Partition.
 *
 * This function can be called to write DVB-SSU parameters into NVRAM Loader Partition. 
 *
 * @param[in] pDvbssuParameters saves the parameters for DVB-SSU.
 *      Parameters in this structure will be serialized into Loader Partition whose format is defined in the loader spec.
 * @param[in] pPrivateData This field contains the manufacturer's private info for download.
 *      When called, the input data will be saved into Loader Partition in byte order without any change.
 * \note: the maximum size of private data should not be more than 48 bytes.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_WriteDVBSSUParameters( 
    const lc_dvb_ssu_parameters *pDvbssuParameters, 
    const lc_buffer_st *pPrivateData);

/**
 * Read DVB-SSU parameters from NVRAM Loader Partition.
 *
 * This function can be called to read DVB-SSU parameters from NVRAM Loader Partition. 
 *
 * @param[out] pDvbssuParameters saves the parameters that have been read from NVRAM Loader Pt.
 *     When called, this function will de-serialize the byte array from Loader Partition to output all parameters.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *    ::LC_FAILURE
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_ReadDVBSSUParameters( lc_dvb_ssu_parameters *pDvbssuParameters);


/** @} */

/** @} */


#ifdef __cplusplus
}
#endif


#endif

