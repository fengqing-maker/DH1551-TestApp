/**
 * @file LoaderCoreSPI_Module.h
 * Header for module methods. This file contains the prototypes for all module functions 
 * that are used by the Loader Core.
 *
 */

#ifndef LOADERCORESPI_MODULE_H__INCLUDED__
#define LOADERCORESPI_MODULE_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define IRD_MOD_MAGIC_NUM           (0xabcd9876)
#define IRD_MOD_HEADER_OFFSET       (sizeof(lc_module_base_info))
#define IRD_MOD_PAYLOAD_OFFSET      (sizeof(lc_module_base_info))
#define IRD_MOD_INFOFlAG_OFFSET     (sizeof(lc_module_base_info))

#define LC_MODULE_EXIT              (0x11)

//according to IRDETO SPEC, each module can't over 254M
#define MAX_MODULE_SIZE         (254*1024*1024)

#define LC_LOADER_PT_SIZE          (80)

#define NOT_UPDATE_INFO       (0)
#define UPDATE_INFO           (1)

#define READ 					(1)
#define WRITE 					(0)
#define PS_PARTITION_ID         (0) //NOR
#define PS_PARTITION_ID1        (1) //NAND

#define FAKE_LOADER_CORE_PAYLOAD    (0x31)

#define MAX_NAND_PAGESZIE		    (8*1024)
#define MAX_IRD_MOD_ID			    (0x1F)
#define MAX_ALI_MOD_ID			    (0x2F)
#define MAX_CUS_MOD_ID			    (0x3F)

#define MOD_LIST_HEADER_SIZE 	    (1536)
#define MOD_SIZE 				    (1000)
#define MAX_MOD_COUT			    (64)
#define MOD_LIST_TOTOAL_SIZE  	    ((MAX_MOD_COUT * MOD_SIZE)+MOD_LIST_HEADER_SIZE)// total 64 KB
#define LOADER_PT_OFFSET_IN_IRD     (MOD_LIST_TOTOAL_SIZE)
#define LOADER_PT_LEN               (1024)
#define LOADER_PS_OFFSET_IN_IRD     (LOADER_PT_OFFSET_IN_IRD + LOADER_PT_LEN)
#define LOADER_PS_LEN               (1*1024)

#define BBCB_OFFSET_IN_PT           (0)  
#define BBCB_LEN                    (1024)      //flash size(Real+Reserve)
#define BBCB_R_LEN                  (24)        //real size of this module

#define VARIANT_OFFSET_IN_PT        (BBCB_OFFSET_IN_PT + BBCB_LEN)
#define VARIANT_LEN                 (1024)      //flash size(Real+Reserve)

#define UK_OFFSET_IN_PT             (VARIANT_OFFSET_IN_PT + VARIANT_LEN)
#define UK_LEN                      (1024*3)    //flash size(Real+Reserve)

typedef enum _module_type
{
    IRD_MODULE = 0,
        
    CSTM_MODULE = 1,

    INVAILD_MODULE = 2
        
}lc_module_type;

typedef struct partition_info{
	char name[256];  // partition name in fdt
	unsigned int start_addr;    // Flash offset
	unsigned int load_addr;     // Sdram address to be load
	unsigned int len;           // partition size length
	unsigned char flash_type;   // 0--norflash, 1--nandflash
}PARTITION_INFO;

//in ALi's soluction the loaderCore can not be read out and CRC check
//the data which is full of  MAGIC NUMBER(0x31) will be return for LOADER CORE
//the len of Loader Core is 0x100
#define LOADERCORE_LEN                  (0x100)
#define BBCB_INFO_OUI (0x5A0100)
#define BBCB_INFO_BOOTCHECK (0x2)
#define BBCB_INFO_LOADER_MAJOR_VERSION (0x5)
#define BBCB_INFO_LOADER_MIN_VERSION (0x1)
#define BBCB_INFO_MANUFACTURE_ID (0xD6)
#define BBCB_INFO_HARDWARE_ID (0x3)


#define LC_UINT16_SIZE   sizeof(lc_uint16)
#define LC_CHAR_SIZE     sizeof(lc_char)
#define MODULE_HEADER_RSV  (MOD_LIST_HEADER_SIZE - LC_CHAR_SIZE*MAX_MOD_COUT - LC_UINT16_SIZE*MAX_MOD_COUT*2 - LC_UINT16_SIZE)


/*
 * module_list which is stored in NVRAM partition(loader_pt section)
 */
typedef struct _lc_module_list_
{
    lc_uint16 	count;					//the totoal count of modules which has recorde on flashes. we will wite/get it to/from flash.
    lc_uchar	is_exist[MAX_MOD_COUT];	//base offest of per module. if nodes[i] == 0, module i is not exist.
    lc_uint16	module_id[MAX_MOD_COUT];	//base offest of per module. if nodes[i] == 0, module i is not exist.
    lc_uint16   module_header_prtinfo[MAX_MOD_COUT];  // module header is in module_header_ird partition or module_header_app partition
                                                      //#define MODULE_HEADER_NONE   (0)  for bbcb and loadercore, there is no header
                                                      //#define MODULE_HEADER_IRD    (0x11)  for UK and Variant
                                                       //#define MODULE_HEADER_APP    (0x22) for CSTM module
    lc_char     rev[MODULE_HEADER_RSV];
}lc_module_list;//size of MOD_LIST_HEADER_SIZE


typedef struct _lc_module_base_info
{
    /**
     *  0xabcd9876
     */
    lc_uint32 magic_num;

    lc_uint32 module_count;

    lc_uint16 is_exist[32];

    lc_uint16 module_id[32];                

    lc_uchar reserved[32];  
    
    lc_uint32 crc32;
    
}lc_module_base_info;


/*loader partition
 *  |--------------------------------------------------|-----|---------------------------------------------|
 *  |Loader¡¯s parameters + Tuning parameters(80 bytes)| rsv | lc_module_list(offset = 1024, length =1536 )|
 *  |--------------------------------------------------|-----|---------------------------------------------|
 */
#define MODULE_LIST_OFFSET_IN_LOADER_PT  (1024)
#define LOADER_PT_OFFSET_IN_NVRAM  (2*64*1024)


/** @defgroup loadercorespis Loader Core SPIs
 *  Loader Core SPIs
 *
 *  
 *  @{
 */

lc_result loadercorespi_flash_init();
lc_sint32 ps_data_read_write(lc_bool is_read, lc_uint32 addr, lc_uint32 len, void *buffer, lc_uint32 flash_type, lc_bool eraseAll);

/** @defgroup loadercoremodulespis Loader Core Module SPIs
 *  Loader Core Module SPIs
 *
 *  Methods to read/write module.
 *  
 *  @{
 */


/** 
 *  Pre-defined Module IDs
 *
 *  Error codes that indicate the execution result. The result code will be shared by both Boot Strap and Boot Loader.
 */
typedef enum _lc_module_id
{
    /*******************************************************************************************
     * Irdeto Internal Module ID:0x00 - 0x1F                                                                           
     *******************************************************************************************/
    /**
     * 0x0000
     * 
     * Module ID for Unique Key.
     * This module ID is used to indicate unique key.
     */
    MODULE_DRV_ID_UK = 0x0000,

    /**
     * 0x0001
     * 
     * Module ID for Loader Core Software.
     * This module ID is used to indicate loader software, including Boot Strap and Boot Loader.
     */
    MODULE_DRV_ID_LOADER_CORE = 0x0001,

    /**
     * 0x0002
     * 
     * Module ID for Boot Block Control Block.
     * This module ID is used to indicate Boot Block Control Block whose format is defined in the loader spec.
     */
    MODULE_DRV_ID_BBCB = 0x0002,

    /**
     * 0x0003
     * 
     * Module ID for Loader Partition.
     * This module ID is used to indicate Loader Partition which mainly contains download parameters.
     */
    MODULE_DRV_ID_LOADER_PT = 0x0003,

    /**
     * 0x0004
     * 
     * Module ID for variant.
     * This module ID is used to indicate variant module which mainly contains variant parameters.
     */
    MODULE_DRV_ID_VARIANT = 0x0004,

    /*******************************************************************************************
     * CSTM HL Module ID:0x20 - 0x3F                                                                               
     *******************************************************************************************/

    /**
     * 0x0020
     * 
     * Module ID for DTS.
     * This module ID is used for DTS.
     */
   // MODULE_DRV_ID_DTS = 0x0020,
    MODULE_DRV_ID_MAIN = 0x0020,
      

    /**
     * 0x0021
     * 
     * Module ID for BOOT_LOGO.
     * This module ID is used for BOOT_LOGO.
     */
   // MODULE_DRV_ID_BOOT_LOGO = 0x0021,
	MODULE_DRV_ID_SEE = 0x0021,

    /**
     * 0x0022
     * 
     * Module ID for BOOT_MEDIA.
     * This module ID is used for BOOT_MEDIA.
     */
    MODULE_DRV_ID_BOOT_MEDIA = 0x0022,
    
    /**
     * 0x0031
     * 
     * Module ID for SEE_SW.
     * This module ID is used for SEE_SW.
     */
   // MODULE_DRV_ID_SEE = 0x0031,
   MODULE_DRV_ID_HEADIFO = 0x0031,
    /**
     * 0x0032
     * 
     * Module ID for KERNEL.
     * This module ID is used for KERNEL.
     */
    MODULE_DRV_ID_KERNEL = 0x0032,

    /**
     * 0x0033
     * 
     * Module ID for ROOTFS.
     * This module ID is used for ROOTFS.
     */
    MODULE_DRV_ID_ROOTFS = 0x0033,

    /**
     * 0x0034
     * 
     * Module ID for USERFS.
     * This module ID is used for USERFS.
     */
    MODULE_DRV_ID_USERFS1 = 0x0034,

    /**
     * 0x0035
     * 
     * Module ID for USERFS2.
     * This module ID is used for USERFS2.
     */
    MODULE_DRV_ID_USERFS2 = 0x0035


} lc_module_id;

/**nor flash*/
//#define SPI_FLASH_TYPE_NOR (0)
/**nand flash*/
//#define SPI_FLASH_TYPE_NAND (1)

/**
 * define HL module image name
 */

#define HL_MODULE_MAINCODE            0x01FE0101
#define HL_MODULE_SEECODE             0x06F90101

// need fixed

#define IRD_BBCB_MODULE_CKID          0x00FF1001

#define IRD_UK_MODULE_CKID            0x00FF1003
#define IRD_UK_BAK_MODULE_CKID        0x00FF1013

#define IRD_VAR_MODULE_CKID           0x00FF1002
#define IRD_VAR_BAK_MODULE_CKID       0x00FF1012

#define IRD_LDPT_MODULE_CKID          0x00FF1004
#define IRD_LDPT_BAK_MODULE_CKID      0x00FF1014

#define IRD_IMAGE_MODULE_HEADER_CKID  0x00FF1005
#define IRD_PSFLAG_MODULE_HEADER_CKID 0x00FF1006

#define IRD_IMAGE_MODULE_HEADER_CKID_ADDR_LOGO  0x005BFF80
#define IRD_IMAGE_MODULE_HEADER_CKID_ADDR       (0x005BFF80 - 0x100000)

#define IRD_PSFLAG_MODULE_HEADER_CKID_ADDR_LOGO 0x005DFF80
#define IRD_PSFLAG_MODULE_HEADER_CKID_ADDR      (0x005DFF80 - 0x100000)


#define IRD_USERFS1_MODULE_CKID       0x00FF1007     // temp use prst to test no-check case


/* NVRAM MAPPING:
 *
    _________________________________________________________________
    | partition layout         |      partition len |     is backup? |
    -----------------------------------------------------------------
    |IRDETO PARTITION (UK Key) |             64KB   |     NO         |
    -----------------------------------------------------------------
    |IRDETO PARTITION (Variant)|            64KB    |       NO       |
    -----------------------------------------------------------------
    |LOADER PARTITION          |            64KB    |      NO        |
    -----------------------------------------------------------------
    |GENERAL PARTITION         |            64KB    |      NO        |
    ------------------------------------------------------------------
    |IRDETO PARTITION (UK Key) |           64KB     |       YES      |
    ------------------------------------------------------------------
    |IRDETO PARTITION (Variant |           64KB     |       YES      |
    ------------------------------------------------------------------
    |LOADER PARTITION          |           64KB     |       YES      |
    ------------------------------------------------------------------
*
*/

#define IRD_MODULE_UK_OFFSET           0
#define IRD_MODULE_VARIANT_OFFSET      (64*1024*1)
#define IRD_MODULE_LOADER_PT_OFFSET    (64*1024*2)
//#define IRD_MODULE_GENERAL_PT_OFFSET   (64*1024*3)

#define IRD_MODULE_UK_BAK_OFFSET          (64*1024*3)
#define IRD_MODULE_VARIANT_BAK_OFFSET     (64*1024*4)
#define IRD_MODULE_LOADER_PT_BAK_OFFSET   (64*1024*5)


/** 
 * Retrieve a list containing all the modules of high level application already owned by this device .
 * 
 * The SPI gets all module IDs of high level application owned by this device. The module list 
 * has a variable number of modules and must be well managed, being updated immediately at any changes 
 * (i.e., at receiving a new module or after deleting a useless module).
 * The SPI must allocate the memory to hold all module IDs and set the module ID count correctly. 
 * Loader Core will free the memory after using it.
 *
 * @param ppModuleIdList    [OUT] Pointer to an lc_uint16 array of module ids
 * @param pModuleIdCount    [OUT] Total number of modules in the module list
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_MODULE_NOT_FOUND
 * @retval
 *     ::LC_ERROR_MODULE_NOT_SUPPORTED
 * @retval
 *     ::LC_ERROR_MODULE_ACCESS_ERROR
 * @retval
 *     ::LC_ERROR_ILLEGAL_MODULE_CONTENT
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Module_GetModuleIdList(lc_uint16 **ppModuleIdList, lc_uint32 *pModuleIdCount);

/** 
 * Retrieve a module's header.
 *
 * This SPI reads in the module header. Loader Core allocates the memory for pModuleHeader. SPI driver 
 * shall allocate the buffer pModuleHeader->bytes and set pModuleHeader->length correctly to indicate 
 * the length of the whole module header
 * Loader Core will free the memory after using it.
 * 
 * @param moduleId      [IN] ID of module to read.
 * @param pModuleHeader [IN, OUT] pData Buffer to read module header data into. 
 *     On input, the lc_buffer_st::bytes member points to a buffer in memory, and the lc_buffer_st::length member 
 *     to the length of the buffer, in bytes. The function will read lc_buffer_st::length bytes from the resource
 *     and store them in lc_buffer_st::bytes.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_MODULE_NOT_FOUND
 * @retval
 *     ::LC_ERROR_MODULE_NOT_SUPPORTED
 * @retval
 *     ::LC_ERROR_MODULE_ACCESS_ERROR
 * @retval
 *     ::LC_ERROR_ILLEGAL_MODULE_CONTENT
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Module_ReadModuleHeader(lc_uint16 moduleId, lc_buffer_st *pModuleHeader);

/** 
 * Retrieve a module's data, without the header.
 *
 * It is up to the user to free the memory used by the data.
 * 
 * @param moduleId       [IN] ID of module to read.
 * @param pModulePayload [IN, OUT] pData Buffer to read module payload data into. 
 *     On input, the lc_buffer_st::bytes member points to a buffer in memory, and the lc_buffer_st::length member 
 *     to the length of the buffer, in bytes. The function will read lc_buffer_st::length bytes from the resource
 *     and store them in lc_buffer_st::bytes.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_MODULE_NOT_FOUND
 * @retval
 *     ::LC_ERROR_MODULE_NOT_SUPPORTED
 * @retval
 *     ::LC_ERROR_MODULE_ACCESS_ERROR
 * @retval
 *     ::LC_ERROR_ILLEGAL_MODULE_CONTENT
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Module_ReadModulePayload(lc_uint16 moduleId, lc_buffer_st *pModulePayload);
/** 
 * Write the entire module. 
 *
 * This SPI writes the entire module to driver, including module header and module payload.
 *
 * @param moduleId  [IN] ID of module to write.
 * @param pModule   [IN] pData Buffer containing module data to write to the resource. The lc_buffer_st::bytes member 
 *     points to the start of the buffer, and the lc_buffer_st::length member contains the number of bytes in the buffer
 *     to write.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_MODULE_NOT_FOUND
 * @retval
 *     ::LC_ERROR_MODULE_NOT_SUPPORTED
 * @retval
 *     ::LC_ERROR_MODULE_ACCESS_ERROR
 * @retval
 *     ::LC_ERROR_ILLEGAL_MODULE_CONTENT
 * @retval
 *     ::LC_ERROR_MODULE_UPDATE_DISALLOWED
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Module_WriteModule(lc_uint16 moduleId, lc_buffer_st *pModule);

/** 
 * Delete a module completely.
 * 
 * @param moduleId [IN] ID of module to delete.
 * 
 * @retval
 *     ::LC_SUCCESS
 * @retval
 *     ::LC_ERROR_MODULE_NOT_FOUND
 * @retval
 *     ::LC_ERROR_MODULE_NOT_SUPPORTED
 * @retval
 *     ::LC_ERROR_MODULE_ACCESS_ERROR
 * @retval
 *     ::LC_ERROR_ILLEGAL_MODULE_CONTENT
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreSPI_Module_Delete(lc_uint16 moduleId);

/** @} */ /* End of Loader Core Module SPIs */

/** @} */ /* End of Loader Core SPIs */

lc_result getTuningInfoPrtAddr(PARTITION_INFO *pPrtInfo);
lc_result getPsFlagPrtAddr(PARTITION_INFO *pPrtInfo);

lc_result LoaderCoreSPI_Module_EarseModulePayload(lc_uint16 moduleId);
lc_uint32 LoaderCoreSPI_Module_ReadModulePayloadSize(lc_uint16 moduleId);
void aui_flash_chunk_init(unsigned long start, unsigned int length);

#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORESPI_MODULE_H__INCLUDED__ */

