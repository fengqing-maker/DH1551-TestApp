/**
 * @file LoaderCoreSPI.h
 * Header for Service Provider Interfaces (SPIs). This file contains the headers for the common Service Provider 
 * Interfaces that must be implemented on a platform. 
 *
 * \note It is the integrator's responsibility to implement these interfaces for a particular platform.
 */

#ifndef LOADERCORESPI_H__INCLUDED__
#define LOADERCORESPI_H__INCLUDED__

#include "LoaderCore_Types.h"
#include "LoaderCoreSPI_Stdlib.h"
#include "LoaderCoreSPI_Module.h"
#include "LoaderCoreSPI_FrontPanel.h"
#include "LoaderCoreSPI_OS.h"
#include "LoaderCoreSPI_UART.h"
#include "LoaderCoreSPI_DEMUX.h"
#include "LoaderCoreSPI_Device.h"
#include "LoaderCoreSPI_Timer.h"
#include "LoaderCoreSPI_Bit.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LC_HIGHEST_MEM_ADDR (0x10000000)
#define LC_CSTM_VDL

#define INC_DEBUG_PRINT

#define SPI_DIS_ERR_WITH_MODID 8


/** @defgroup errorcodes Loader Core Error Codes
 *  Loader Core Error Codes
 *
 *  Error codes that indicate the execution result. The result code will be shared by both Boot Strap and Boot Loader.
 *  
 *  @{
 */

#define ALI_IRD_DEBUG

#ifdef ALI_IRD_DEBUG
void lc_data_dump(lc_uchar *data, lc_uint32 len);
#undef SDBBP()
#define SDBBP()        asm volatile(".word    0x1000ffff; \
                                  nop;");
#else
#define lc_data_dump() do{}while(0)

#define SDBBP() do{}while(0)
#endif

// #define LC_NAND_ONLY

//#define LC_NOR_ONLY


/**
 * 0x00000000
 * 
 * SUCCESS. No error is detected.
 * This result code is used to indicate that everything is fine.
 */

#define  ERROR_CODE_SUCCESS                                     0       

/**
 * \note Error codes from 1 to 0xF are shared by boot strap and boot loader.
 */


/**
 * 
 * This error code is reported when boot strap has detected an error on Boot-check.
 */
#define ERROR_CODE_BOOT_CHECK_FAILED                            0x01            

/**
 * 
 * This error code is reported when boot strap has detected an invalid Loader Core module.
 */
#define ERROR_CODE_INVALID_LOADERPT                             0x02       

/**
 * 
 * This error code is reported when boot strap has detected an error 
 * during decompression of the loader.
 */
#define ERROR_CODE_BL_DECOMPRESS_FAILED                         0x03          

/**
 * 
 * CRC error of the decompressed Boot loader in RAM.
 */
#define ERROR_CODE_BL_CRC                                       0x04      

/**
 * 
 * This error code is reported when boot strap has detected an error of invalid BBCB module,
 * that the CRC_32 field of the boot block control block has failed.
 */
#define ERROR_CODE_INVALID_BBCB                                 0x05            




/**
 * \note Error codes from 0x10 to 0xFF are only used by boot loader.
 */

/******************************************************************************
 * Module errors
 */

/**
 * The module list cannot be obtained or incomplete 
 * (i.e. the module list should at least include BBCB, Loader Core and NVRAM).
 */

#define ERROR_CODE_INVALID_MODULE_LIST                          0x10     

/**
 * 
 * The module info header is incorrect. 
 * (e.g., has a mismatched module id, or a wrong module size.).
 */

#define ERROR_CODE_INCORRECT_MODULE_INFO_HEADER                 0x11      

/**
 * 
 * The CRC32 of Module Info Header verify failed.
 */

#define ERROR_CODE_INVALID_MODULE_INFO_HEADER_CRC               0x12    

/**
 * 
 * The module did not update due to the version is not within the
 * valid window for this STB version (either too low or too high).
 */

#define ERROR_CODE_INCORRECT_MODULE_VERSION                     0x13        

/**
 * 
 * The module did not update due to a same version.
 */

#define ERROR_CODE_SAME_MODULE_VERSION                          0x14       

/**
 * 
 * The memory_type field of the module info header is not correct or a recognized value.
 */

#define ERROR_CODE_INCORRECT_MEMORY_TYPE                        0x15    

/**
 * 
 * Loader Core could not modify (write, delete) a module.
 */
#define ERROR_CODE_MODIFY_MODULE                                0x16   

/**
 * 
 * A module is not allowed to update, e.g. BBCB, Loader Core, NVRAM; or UK, variant by OTA. 
 */
#define ERROR_CODE_NOTUPDATEABLE_MODULE                         0x17     

/**
 * 
 * Error occurred on updating module signature in module info header.
 */

#define ERROR_CODE_UPDATE_MODULE_SIGNATURE                      0x18

/**
 * 
 * Error occurred on updating module that is not supported by this device.
 */

#define ERROR_CODE_UNSUPPORTED_MODULE                           0x19



/******************************************************************************
 * STB resident key validation errors
 */

/**
 * 
 * STB resident key is corrupt, e.g., not authenticated.
 */

#define ERROR_CODE_RESIDENT_KEY_CORRUPT                         0x20     

/**
 * 
 * This error code indicates there is something wrong with the content of resident key. 
 * E.g, lost.
 */

#define ERROR_CODE_RESIDENT_KEY_INVALID                         0x21     


/******************************************************************************
 * Signature verification errors
 */

/**
 * 
 * Signature verification has failed.
 */

#define ERROR_CODE_VERIFY_SIGNATURE                             0x26    

/**
 * 
 * The length of the signature is not as expected.
 */

#define ERROR_CODE_INVALID_SIG_LENGTH                           0x27   


/******************************************************************************
 * Module Header errors
 */

/**
 * 
 * The CRC_16 field of the module header does not match computed value.
 */

#define ERROR_CODE_INVALID_MH_CRC                               0x30      

/**
 * 
 * There is something wrong with the module header's content (e.g., both encrypted and obscured.).
 */

#define ERROR_CODE_INVALID_MH_CONTENT                           0x31        


/**
 * 
 * The data_id field of the serial module header does not equal 0x22.
 */

#define ERROR_CODE_INVALID_MH_ID                                0x32        

/**
 * 
 * The length field of the serial module header specifies an invalid
 * module header size.
 */

#define ERROR_CODE_INVALID_MH_SIZE                              0x33        


/**
 * 
 * The module size calculated by block_count * block_size derived from the 
 * module header is either zero or too big.
 */

#define ERROR_CODE_MH_MODULE_SIZE                               0x34    

/**
 * 
 * The C_CRC_32 field of the module header does not match computed value.
 * Failure occurred during processing of partition pq.
 */

#define ERROR_CODE_INVALID_MH_COMP_CRC                          0x35      


/******************************************************************************
 * Key update errors
 */

/**
 * 
 * The system ID of the key message does not match the STB resident key.
 */

#define ERROR_CODE_DL_KEY_INCORRECT_SYS_ID                      0x40   

/**
 * 
 * The key version of the download signature does not match the STB resident
 * key.
 */

#define ERROR_CODE_DL_KEY_INCORRECT_KEY_VER                     0x41  

/**
 * 
 * The download key has a lower or equal version (only applicable for same key type update, 
 * e.g., Dev-Key -> Dev-Key).
 */

#define ERROR_CODE_DL_KEY_OLD_KEY_VER                           0x42        

/**
 * 
 * The downloaded key is corrupted, e.g., wrong size or not authenticated.
 */

#define ERROR_CODE_DL_KEY_CORRUPTED                             0x43         




/******************************************************************************
 * Download header errors
 */

/**
 * 
 * The download is not for Loader V5.
 */

#define ERROR_CODE_INVALID_DLH_NOT_GTE_V5                       0x50    

/**
 * 
 * The data_id field of the serial download header does not equal 0x11.
 */

#define ERROR_CODE_INVALID_DLH_ID                               0x51    

/**
 * 
 * The CRC_16 field of the download header does not match the computed value.
 */

#define ERROR_CODE_INVALID_DLH_CRC                              0x52    

/**
 * 
 * The length field of the serial download header specifies an invalid
 * download header size.
 */

#define ERROR_CODE_INVALID_DLH_SIZE                             0x53   

/**
 * 
 * The manufacturer_id field of the download header does not match that of
 * the STB.
 */

#define ERROR_CODE_DLH_MAN_ID_NE                                0x54   

/**
 * 
 * The hardware_version field of the download header does not match that of the
 * STB.
 */

#define ERROR_CODE_DLH_HW_VER_NE                                0x55   

/**
 * 
 * The download_sequence_number field of the download header is equal to 0 or 65535 or
 * out of valid window for this STB (either too low or too high). Please refer to the 
 * Glossary for an explanation of the valid window for this value.
 */

#define ERROR_CODE_INCORRECT_DOWNLOAD_SEQUENCE_NUMBER           0x56     

/**
 * 
 * The download_sequence_number field of the download header is identical to that
 * currently resident in the STB.
 */

#define ERROR_CODE_SAME_DOWNLOAD_SEQUENCE_NUMBER                0x57     

/**
 * 
 * The resident download_sequence_number is unavailable!
 * 
 */

#define ERROR_CODE_RESIDENT_DOWNLOAD_SEQUENCE_NUMBER_INVALID    0x58 

/**
 * 
 * The isign_serial_number field of the download header contains non-printable
 * characters.
 */

#define ERROR_CODE_ISIGN_SN_NPCHARS                             0x59  

/**
 * 
 * The isign_version field of the download header contains non-printable
 * characters.
 */

#define ERROR_CODE_ISIGN_VER_NPCHARS                            0x60  

/**
 * 
 * Reserved for use by the Broadcast PC adapter.
 */

#define ERROR_CODE_DLH_PCI_VENDOR_ID_NE                         0x61   

/**
 * 
 * Reserved for use by the Broadcast PC adapter.
 */

#define ERROR_CODE_DLH_PCI_ADAPTER_ID_NE                        0x62   


/******************************************************************************
 * Variant errors
 */

/**
 * 
 * The variant field of the download header or module info header does not match 
 * that of the STB, or it has an invalid value.
 */

#define ERROR_CODE_INVALID_VARIANT                              0x65      

/**
 * 
 * The sub-variant field of the download header or module info header does not match 
 * that of the STB, or it has an invalid value.
 */

#define ERROR_CODE_INVALID_SUBVARIANT                           0x66   

/**
 * 
 * The resident variant is unavailable!
 * 
 */

#define ERROR_CODE_RESIDENT_VARIANT_INVALID                     0x67      


/******************************************************************************
 * Datagram errors
 */

/**
 * 
 * Decompression operation on compressed datagram payload failed. Failure
 * occurred during processing of module pq.
 */

#define ERROR_CODE_MODULE_DECOMP_FAIL                           0x70       

/**
 * 
 * The data_length field of the datagram is either zero or greater than the
 * block_size field of the corresponding partition header.
 */

#define ERROR_CODE_DATAGRAM_SIZE                                0x71   

/**
 * 
 * The CRC_16 field of the datagram does not match the computed value.
 */

#define ERROR_CODE_INVALID_DG_CRC                               0x72    

/**
 * 
 * The data_id field of the serial datagram does not equal 0x33.
 */

#define ERROR_CODE_INVALID_DG_ID                                0x73   

/**
 * 
 * The datagram content was incorrect. 
 */

#define ERROR_CODE_DATAGRAM_CONTENT                             0x74    


/******************************************************************************
 * Miscellaneous ex-manufacturer errors incorporated into this file
 */

/**
 * 
 * The loader code cannot identify the reason for the bootstrap code
 * initiating a download.
 */

#define ERROR_CODE_INVALID_DL_TYPE                              0x80    

/**
 * 
 * The Loader NVRAM partition does not contain valid parameters of transport stream (DVB)
 * or multicast (IP).
 */

#define ERROR_CODE_INVALID_OTA_PARA                             0x81    

/**
 * 
 * An attempt to write to the serial port has failed.
 */

#define ERROR_CODE_UART_TIMEOUT                                 0x82  

/**
 * 
 * A timeout occurred whilst attempting to acquire a download section.
 */

#define ERROR_CODE_TABLE_TIMEOUT                                0x83   

/**
 * 
 * Download service multicast address/port connection timeout.
 */

#define ERROR_CODE_MULTICAST_CONNECTION_TIMEOUT                 0x84   

/**
 * 
 * Master Key is invalid.
 */

#define ERROR_CODE_INVALID_MASTER_KEY                           0x85   



/* Error codes for SSU download */

/**
 * The size for received DSI section mismatches the size indicated by section length fields. 
 */
#define ERROR_CODE_WRONG_DSI_SECTION_SIZE                       0xA1

/**
 * The size for received DII section mismatches the size indicated by section length fields. 
 */
#define ERROR_CODE_WRONG_DII_SECTION_SIZE                       0xA2

/**
 * The size for received DDB section mismatches the size indicated by section length fields. 
 */
#define ERROR_CODE_WRONG_DDB_SECTION_SIZE                       0xA3

/**
 * Incorrect CRC32 for received DSI section.
 */
#define ERROR_CODE_INVALID_DSI_CRC                              0xA4

/**
 * Incorrect CRC32 for received DII section.
 */
#define ERROR_CODE_INVALID_DII_CRC                              0xA5

/**
 * Incorrect CRC32 for received DDB section.
 */
#define ERROR_CODE_INVALID_DDB_CRC                              0xA6

/**
 * Incorrect DSI section: wrong TID, wrong section number or last section number.
 * TID for DSI should be 0x3B. Section number and last section number should be 0 for DSI.
 */
#define ERROR_CODE_DSI_WRONG_SECTION                            0xB6

/**
 * Incorrect message Id for DSI section.
 * Message Id should be 0x1006, protocolDiscrimitor should be 0x11, dsmccType should be 0x03 for DSI.
 */
#define ERROR_CODE_DSI_WRONG_MESSAGE_ID                         0xB7

/**
 * Incorrect transaction Id for DSI section.
 * The least two bytes for transaction Id in DSI must be 0x0000 or 0x0001 according to SSU spec.
 */
#define ERROR_CODE_DSI_WRONG_TRANSACTION_ID                     0xB8

/**
 * Incorrect service Id for DSI section.
 * The service Id should be filled 0xFF, length 20.
 */
#define ERROR_CODE_DSI_WRONG_SERVICE_ID                         0xB9

/**
 * Incorrect DII section: wrong TID, wrong section number or last section number.
 * TID for DII should be 0x3B. Section number and last section number should be 0 for DII.
 */
#define ERROR_CODE_DII_WRONG_SECTION                            0xBA

/**
 * Incorrect message Id for DII section.
 * Message Id should be 0x1002, protocolDiscrimitor should be 0x11, dsmccType should be 0x03 for DII.
 */
#define ERROR_CODE_DII_WRONG_MESSAGE_ID                         0xBB

/**
 * Incorrect transaction Id for DII section.
 * The least two bytes for transaction Id in DSI must be higher than 0x0001. And it should be equal to groupId defined in DSI.
 */
#define ERROR_CODE_DII_WRONG_TRANSACTION_ID                     0xBC

/**
 * No valid module information found in DII. Number of module is equal to 0.
 */
#define ERROR_CODE_DII_NO_VALID_MODULE_INFO                     0xBD

/**
 * Incorrect DDB section: wrong TID, wrong section number or last section number.
 * TID for DII should be 0x3C. Section number should less or equal to (<=) last section number.
 */
#define ERROR_CODE_DDB_WRONG_SECTION                            0xBE

/**
 * Incorrect message Id for DDB section.
 * Message Id should be 0x1003, protocolDiscrimitor should be 0x11, dsmccType should be 0x03 for DDB.
 */
#define ERROR_CODE_DDB_WRONG_MESSAGE_ID                         0xBF

/**
 * The module version in DDB is not equal to the one defined in DII.
 */
#define ERROR_CODE_DDB_WRONG_MODULE_VERSION                     0xC0

/**
 * The module Id in DDB is not equal to the one defined in DII.
 */
#define ERROR_CODE_DDB_WRONG_MODULE_ID                          0xC1

/**
 * No valid download be found in compatibility descriptor
 */
#define ERROR_CODE_NO_VALID_DOWNLOAD_IN_COMP_DESC               0xC2

/* Error codes for IP Multicasting download */

/**
 * 
 * The CRC_32 field of the datagram section is incorrect.
 */

#define ERROR_CODE_MULTICAST_CRC_ERROR                          0xD1     

/**
 * 
 * Failed to get multicast session.
 */

#define ERROR_CODE_MULTICAST_SESSION_FAILED                     0xD2        /* Todo! */

/**
 * 
 * The CRC_16 field of the multicast packet is incorrect.
 */

#define ERROR_CODE_MULTICAST_PACKET                             0xD3        /* Todo! */


/**
 *
 * Need upgrade key, but no SERILA_DOWNLOAD detected
 */
#define ERROR_CODE_UART_DETECTED                                0xFE 


/**
 * Undefined error occurred.
 */
#define ERROR_CODE_UNDEFINED_ERROR                              0xFF 


/** @} */ /* End of errorcodes */


/**
 * define ui info type
 */
#define UI_INFO_TYPE_BBCB_INFO              (0)
#define UI_INFO_TYPE_MODULE_INFO            (1)
#define UI_INFO_TYPE_ERROR_CODE             (2) 
#define UI_INFO_TYPE_PROCESS                (3) 
#define UI_INFO_TYPE_TIME                   (4) 
#define UI_INFO_TYPE_ERROR_INFO             (5)
#define UI_INFO_TYPE_VAR                    (6)
#define UI_INFO_TYPE_MODULE_FINAL           (7)
#define UI_INFO_TYPE_STAGE                  (8)
#define UI_INFO_TYPE_DSN                    (9)

/**
 * define process module data stage for ui download process display
 */
#define UI_MODULE_DATA_DOWNLOAD             (0)
#define UI_MODULE_DATA_CHECK                (1)
#define UI_MODULE_DATA_UPDATE               (2)

/**
 * define process module data stage for ui topmost visual display
 */
typedef enum _lc_ui_stages
{

    UI_STAGES_LOADER_READY             = 0x0,
    UI_STAGES_TRANSPORT_STRAM               ,
    
    /**
     * download module data
     */
    UI_STAGES_DOWNLOAD_DSI                  ,     
    UI_STAGES_DOWNLOAD_DII                  , 
    UI_STAGES_DOWNLOAD_DDB                  ,
    UI_STAGES_PROCESSING_DATA_DECRYPT       ,  
    UI_STAGES_PROCESSING_DATA_DECOMPRESS    , 

    /**
      * check module
      */
    UI_STAGES_VERIFYING_SIG                 ,

    /**
      * update module:write module to flash
      */
    UI_STAGES_WRITING_DATA_TO_FLASH         ,   

    /**
     *  special download class
     */
    
    UI_STAGES_UPDATING_VARIANT              ,        
    UI_STAGES_UPDATING_KEY                  ,

    /**
     *  finally info
     */
    UI_STAGES_FINAL_SUCCESS                 ,        
    UI_STAGES_FINAL_FAILED                 

}lc_ui_stages;


/** @defgroup loadercorespis Loader Core SPIs
 *  Loader Core SPIs
 *
 *  
 *  @{
 */


/** @defgroup loadercoretoplevelspis Loader Core Top Level SPIs
 *  Loader Core Top Level SPIs
 *
 *  
 *  @{
 */

/** 
 *  Loader Core Reset Types
 *
 *  Reset types that indicate the boot type.
 *  
 */

typedef enum _lc_reset_type
{
    /**
     * 0x55
     * 
     * Warm boot.
     * In case of warm boot, Loader Core will request to execute High Level Application directly.
     * Loader Core will set reset type as ::WARM_BOOT after a successful download and set it back to ::COLD_BOOT after the first reset.
     */
    IRD_WARM_BOOT = 0x55,
    /**
     * 0xAA
     * 
     * Cold boot.
     * In case of cold boot, Loader Core will NOT request to execute High Level Application directly.
     */
    IRD_COLD_BOOT = 0xAA

} lc_reset_type;

typedef enum _lc_reboot_type
{
    /**
     * 0x11
     * 
     * First boot.
     * Loader Core will set reboot type as ::FIRST_BOOT after a successful download and set it back to ::OTHER_BOOT after the MW read it.
     */
    FIRST_BOOT = 0x11,

    /**
     * 0x22
     * 
     * OTHER_BOOT.
     */
    OTHER_BOOT = 0x22

} lc_reboot_type;


typedef enum _lc_read_reboot_type
{
    /**
     * 0x11
     * 
     * ALREADY_READ.
     */
    ALREADY_READ = 0x00,

    /**
     * 0x22
     * 
     * NOT_READ.
     */
    NOT_READ = 0x01

} lc_read_reboot_type;




/** 
 *  Loader Core persistent storage modify flag
 *
 *  The flag that indicate the persistent storage has been modified by Loader Core.
 *  
 */
typedef enum _lc_ps_modify_flag
{
    /**
     * 0x5A
     * 
     * Persistent storage has been modified by Loader Core.
     */
    PS_MODIFIED = 0x5A,

    /**
     * 0xA5
     * 
     * Persistent storage has not been modified by Loader Core.
     */
    PS_UNMODIFIED = 0xA5

} lc_ps_modify_flag;


/** 
 *  Code IDs
 *  List of all possible values of ::lc_code_id codes. 
 *  Each ID is used to indicate a software module that Loader Core may request to run.
 *
 */
typedef enum _lc_code_id
{
    /** (0) Boot Strap code ID.*/
    CODE_ID_BOOT_STRAP              = 0,

    /** (1) Boot Loader code ID.*/
    CODE_ID_BOOT_LOADER             = 1,

    /** (2) High Level Application code ID.*/
    CODE_ID_HIGH_LEVEL_APPLICATION  = 2,

    /** (3) Application Helper Module code ID.
      * \note Loader Core will NOT request to execute this module. This module is to provide some helper functions to High Level Application.
      */
    CODE_ID_APPLICATION_HELPER      = 3,

    CODE_ID_UNITTEST_HELPER         = 4
    
} lc_code_id;

// char* is the nim private data,
// int is for the pid
typedef lc_result (* nim_setup) (char *, int );
typedef lc_result (* UpdateInfoFunc)(int,int,void*);
typedef lc_result (* ExecuteCode) (void);
typedef struct executecode_func_st
{
    ExecuteCode Strapup;
    ExecuteCode Bootloader;
    ExecuteCode Application;
    UpdateInfoFunc Updateinfo;
}executecode_func;

void LoaderCoreSPI_SetExecuteCodeFunc (executecode_func *pfunc);

/**
 * Method to report a code which indicates download result.
 *
 * This method is called when Loader Core wants to report the final error code to client device.
 *
 * No matter success or failure, Boot Strap and Boot Loader will always report the error code to client device one time.
 * Different error code will have different meaning. See the list for all error codes \ref errorcodes "Error Code List".
 *
 * @param[in] errorCode To indicate result code. See the list for all error codes \ref errorcodes "Error Code List"
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_ReportErrorCode(lc_uint32  errorCode, lc_uint16 moduleId);

/**
 * Method to set reset type.
 *
 * This method is called when Loader Core wants to save the reset type.
 * 
 * Reset type can be ::WARM_BOOT or ::COLD_BOOT. Reset type can only be stored in volatile types of memory (e.g., RAM), 
 * so that the state of reset type can be reset (to Cold-Boot) when power is removed. 
 * In case of ::WARM_BOOT, Loader Core will request to execute High Level Application directly.
 *
 * \note Reset type will be set by Boot Strap and Boot Loader. 

 * @param[in] resetType To indicate reset type. See the list for all reset types \ref lc_reset_type "Reset Types"
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_SetResetType(lc_uchar resetType);


/**
 * Method to get reset type.
 *
 * This method is called when Loader Core wants to get the reset type.
 * 
 * Reset type can be ::WARM_BOOT or ::COLD_BOOT. Reset type can only be stored in volatile types of memory (e.g., RAM), 
 * so that the state of reset type can be reset (to Cold-Boot) when power is removed. 
 * In case of ::WARM_BOOT, Loader Core will request to execute High Level Application directly.
 *
 * \note Reset type will be read by Boot Strap. 

 * @param[out] pResetType SPI drivers must read the reset type from volatile memory and set the value to this parameter. 
 * See the list for all reset types \ref lc_reset_type "Reset Types"
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_GetResetType(lc_uchar *pResetType);


/**
 * Method to set persistent storage modify flag.
 *
 * This method is called when Loader Core wants to modify the persistent storage.
 * 
 * Persisitent storage modified flag can be ::PS_MODIFIED or ::PS_UNMODIFIED. Depending on the implementation, reset type can be saved in the NVRAM or other storage.
 * It is up to manufacturers to decide where to save the reset type in order to optimize the boot-up speed. In case of ::PS_MODIFIED, Loader Core will 
 * request to execute Boot Loader for another OTA download.
 *
 * \note PS modify flag will be set by Boot Loader to ::PS_MODIFIED when it is about to erase/write the persistent storage, and set to ::PS_UNMODIFIED 
 * after persistent storage has been successfully updated. 

 * @param[in] modifyFlag To indicate persisitent storage modified flag. See the list for all flags \ref lc_ps_modify_flag "PS Modified Flags"
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_SetPSModifyFlag(lc_uchar modifyFlag);


/**
 * Method to set reset type.
 *
 * This method is called when Loader Core wants to save the reset type.
 * 
 * PS modifiy flag can be ::PS_MODIFIED or ::PS_UNMODIFIED. Depending on the implementation, reset type can be saved in the NVRAM or other storage.
 * It is up to manufacturers to decide where to save the modify flag in order to optimize the boot-up speed. In the case of ::PS_MODIFIED, Loader Core will 
 * request to execute Boot Loader for an OTA download.
 *
 * \note PS modify flag will be read by Boot Strap. 

 * @param[out] pModifyFlag SPI drivers must read the persistent storage modified flag from storage and set the value to this parameter. 
 * See the list for all flags \ref lc_ps_modify_flag "PS Modified Flags".
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_GetPSModifyFlag(lc_uchar *pModifyFlag);

/**
 * Method to set upgrade status at ps_flag partition.
 *
 * @param[in] pDownloadType To indicate download type. See the list for all flags \ref lc_ps_modify_flag "PS Modified Flags"
 * @param[in] pDownloadStatus To indicate download status. See the list for all flags \ref lc_ps_modify_flag "PS Modified Flags"
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_SetPSUpgradeResult(lc_uchar pDownloadType, lc_uchar pDownloadStatus);


/**
 * Method to get upgrade status at ps_flag partition.
 *
 * @param[out] pDownloadType To indicate download type. See the list for all flags \ref lc_ps_modify_flag "PS Modified Flags"
 * @param[out] pDownloadStatus To indicate download status. See the list for all flags \ref lc_ps_modify_flag "PS Modified Flags"
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_GetPSUpgradeResult(lc_uchar *pDownloadType, lc_uchar *pDownloadStatus);


/**
 * Request to execute specific module.
 *
 * This method is called when Loader Core wants to run specific module.
 * 
 * Usually, Boot Loader only requests to run Boot Strap, but Boot Strap may request to run Boot Strap (i.e. reset), Boot Loader or High Level Application.est to execute High Level Application directly.
 * It is up to manufacturer to decide whether to make Boot Strap and Boot Loader execute separately, or to combine Boot Strap and Boot Loader into a single executable module. 
 *
 * @param[in] codeID ID of code that Loader Core requests to run. See the list for all reset types \ref lc_code_id "Code IDs"
 * \note Loader Core will NOT request to run ::CODE_ID_APPLICATION_HELPER.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result  LoaderCoreSPI_ExecuteCode( lc_code_id codeID );

/** @} */ /* End of Loader Core Top Level SPIs */

/** @} */ /* End of Loader Core SPIs */


lc_result LoaderCoreSPI_SetPSDefaultData(lc_char *data, lc_uint16 index);
lc_result LoaderCoreSPI_GetPSDefaultData(lc_char *data, lc_uint16 index);
lc_result LoaderCoreSPI_Update_UI_Message(const lc_char *pFormat,...);
lc_result LoaderCoreSPI_UPDATE_UI(int type,int size,void*buf);
lc_result LoaderCoreSPI_GetRebootType(lc_uchar *pRebootType);
lc_result LoaderCoreSPI_UpdateUIStageInfo(lc_ui_stages stage_info);
void LoaderCoreSPI_set_ui_update_rate(lc_uint32 var);
lc_uint32 LoaderCoreSPI_get_ui_update_rate();
void LoaderCoreSPI_take_a_break();
#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_H__INCLUDED__ */

