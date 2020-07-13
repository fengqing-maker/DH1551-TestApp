/**
 * @file LoaderCoreSPI_Module.h
 * Header for module methods. This file contains the prototypes for all module functions 
 * that are used by the Loader Core.
 *
 */
#include "LoaderCoreSPI.h"
#include <aui_flash.h>
//#include <udi/spi/internel/LoaderCorePrivate.h>
#include <aui_dsc.h>

// #define UC_SPI_MODULE_DEBUG(...)
#define UC_SPI_MODULE_DEBUG(format,arg...) libc_printf(format, ##arg)

/*
 *  3529 no need to align 4 bytes, but 3733 still need to 4 bytes align
 */
//#define LC_SHA_ALIGN
#define LC_HW_SHA_ALIGN_BYTES  (0x4)
#define HASH_LEN        (32)

#define MODULE_HEADER_NONE       (0)
#define MODULE_HEADER_IRD        (0x11)
#define MODULE_HEADER_APP        (0x22)
#define NOR_ONE_BLOCK_SIZE       (64*1024)
#define EACH_MOD_HADER_RAW_LEN   (1024)
#define MOD_HEADER_INFO_LENGTH  sizeof(lc_module_info_header)

#define CHUNK_ID     0
#define CHUNK_LENGTH    4
#define CHUNK_OFFSET    8
#define CHUNK_CRC       12
#define CHUNK_HEADER_SIZE       128
#define SHORT_MODULE_INFO_HEADER_SIZE 12

static unsigned long chunk_start = 0;
static unsigned long chunk_end =  0x800000;
static unsigned long chunk_maxlen = 0x800000;

static lc_bool b_fdt_init= LC_FALSE;
static lc_bool flash_inited = LC_FALSE;
static aui_hdl nor_flash_handle = LC_NULL;
static unsigned long nor_block_size = 0;
static unsigned long nor_flash_size = 0;
aui_flash_partition_table aui_part_table; 

static lc_module_base_info *g_lc_module_list = LC_NULL;

static lc_uchar *g_lc_module_uk = LC_NULL;
static lc_uchar *g_lc_module_variant = LC_NULL;
static lc_uchar *g_lc_module_loaderPt = LC_NULL;

static lc_uchar *g_lc_module_bbcb = LC_NULL;
static lc_bool g_lc_ird_module_get = LC_FALSE;

static lc_uint32 psFlag_base_addr = 0;
static lc_uint32 tuning_info_base_addr= 0;

/* Minimum module ID  size for High level App */
#define MIN_MODULE_ID_APP   (0x20)

#define MAX_HL_MODULE_NUM   (0x20)

#define MAX_PARTITION_NAME_LENGTH 64

static lc_result lc_module_list_init();
static lc_result LoaderCoreSPI_Module_GetPrtAddr(void);

static lc_result get_sha_value(void *buffer,unsigned long len,void* hash_value);
static lc_result UpdateIrdetoModuleInfoHeader(lc_uint16 moduleId);
static lc_result UpdateHLModuleInfoHeader(void);
static lc_result LC_CheckModuleHeader(lc_module_base_info *module_base_info, lc_uint32 count);
static lc_uint16 get_index_in_HL_module_list(lc_uint16 moduleId);
unsigned long aui_flash_fetch_long(unsigned long offset);
unsigned long aui_flash_chunk_goto(unsigned long *chid, unsigned long mask, unsigned int n);


/*
 * this function is check the module is vaild or not.
 * in case of the module list contains a module, but not update the module header
 *
 */
static lc_bool CheckExistModuleVaild(lc_uint16 moduleId,lc_module_info_header *header_info )
{
    lc_bool b_result = LC_TRUE;

    //module size should less than 254M, and the Loader PT module size is fixed
    if( (header_info->module_size> MAX_MODULE_SIZE) || 
    ((MODULE_DRV_ID_LOADER_PT == moduleId) &&(header_info->module_size!= LC_LOADER_PT_SIZE ) ) ||
    header_info->header_length == 0xffff || header_info->header_signature_length == 0xffff ||
    header_info->module_signature_length == 0xffff)
    {
        b_result = LC_FALSE;
    }
    
    return b_result;  
}

/*
 * check module id is out of range or not
 * NOW we support 64 modules
 */
static lc_module_type CheckModuleId(lc_uint16 moduleId)
{
    if(moduleId < 0)
        return INVAILD_MODULE;
    else if(moduleId <= MAX_IRD_MOD_ID)
        return IRD_MODULE;
    else
        return CSTM_MODULE;
}

static lc_bool checkModuleExist(lc_uint16 moduleId, lc_uint32 *index)     //
{
    lc_result result = LC_SUCCESS;
    lc_module_base_info *pModule_base_info = LC_NULL;
    lc_uint32 i = 0xff;

    if(MIN_MODULE_ID_APP > moduleId)
    {
        switch(moduleId)
        {
            case MODULE_DRV_ID_UK:
    		{
                pModule_base_info = (lc_module_base_info *)g_lc_module_uk;    //201803
                break;
    		}
            case MODULE_DRV_ID_LOADER_PT:
    		{
                pModule_base_info = (lc_module_base_info *)g_lc_module_loaderPt;
                break;

    		}
            case MODULE_DRV_ID_VARIANT:
    		{
                pModule_base_info = (lc_module_base_info *)g_lc_module_variant;
                break;
    		} 
            default:
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
                break;
            }
        }
        /* the index is 0 */
        if(( 1 == pModule_base_info->module_count )&&
            (LC_MODULE_EXIT == pModule_base_info->is_exist[0]) &&
            (moduleId == pModule_base_info->module_id[0]))
        {
            /* check module header */
            result = LC_CheckModuleHeader(pModule_base_info, 1);
            if(LC_SUCCESS == result)
            {
                return LC_TRUE;
            }
            else
            {
                return LC_FALSE;
            }
        }
        else
        {
            return LC_FALSE;
        }
    }
    else
    {
        i = get_index_in_HL_module_list(moduleId);
        if(i < MAX_HL_MODULE_NUM )
        {
            *index = i;
            return LC_TRUE;
        }
        else
        {
            return LC_FALSE;
        }
    }
    
}




lc_result LC_GetChunkFromMouldID (lc_module_id moduleId, lc_uint32 * pckid, lc_uint32 *pBakckid)
{

    lc_result result = LC_SUCCESS;
	
    switch(moduleId)
    {
        case MODULE_DRV_ID_UK:
         {
                *pckid = IRD_UK_MODULE_CKID;
                break;
    	 }
        case MODULE_DRV_ID_LOADER_PT:
    	 {
                *pckid = IRD_LDPT_MODULE_CKID;
                break;

    	 }
        case MODULE_DRV_ID_VARIANT:
    	 {
                *pckid = IRD_VAR_MODULE_CKID;
                break;
    	 } 
		case MODULE_DRV_ID_BBCB:
    	 {
                *pckid = IRD_BBCB_MODULE_CKID;
                break;
    	 } 
		case MODULE_DRV_ID_MAIN:
    	 {
                *pckid = HL_MODULE_MAINCODE;
                break;
    	 } 
		case MODULE_DRV_ID_SEE:
    	 {
                *pckid = HL_MODULE_SEECODE;
                break;
    	 } 
		case MODULE_DRV_ID_HEADIFO:
    	 {
                *pckid = IRD_IMAGE_MODULE_HEADER_CKID;
                break;
    	 } 
		case MODULE_DRV_ID_USERFS1:
    	 {
                *pckid = IRD_USERFS1_MODULE_CKID;
                break;
    	 } 
         default:
         {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
				result = LC_FAILURE;
                break;
         }
    }
  	return result;
}

//
static lc_result lc_get_offset_from_NVRAM(lc_uint16 moduleId, lc_uint32 *orig_offset, lc_uint32 *bak_offset, lc_uint32 *module_len,lc_uint32 *bak_module_len)
{
    
    lc_result result = LC_SUCCESS;
    lc_uint32 chunk_id = 0;
	lc_uint32 chunk_id_bak = 0;
	lc_uint32 data_len = 0;
    lc_uchar  *data_addr = NULL;

	if(!orig_offset || !module_len)
	 {
	   UC_SPI_MODULE_DEBUG("%s() in line(%d) INVAILD paramter!\n", __FUNCTION__, __LINE__);
	   return  LC_FAILURE;
	 }
	
	switch(moduleId)
    {
        case MODULE_DRV_ID_UK:
         {
                chunk_id = IRD_UK_MODULE_CKID;
				chunk_id_bak = IRD_UK_BAK_MODULE_CKID;
                break;
    	 }
        case MODULE_DRV_ID_LOADER_PT:
    	 {
                chunk_id = IRD_LDPT_MODULE_CKID;
				chunk_id_bak = IRD_LDPT_BAK_MODULE_CKID;
                break;

    	 }
        case MODULE_DRV_ID_VARIANT:
    	 {
                chunk_id = IRD_VAR_MODULE_CKID;
				chunk_id_bak = IRD_VAR_BAK_MODULE_CKID;
                break;
    	 } 
		case MODULE_DRV_ID_BBCB:
    	 {
                chunk_id = IRD_BBCB_MODULE_CKID;
                break;
    	 } 
         default:
         {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
                break;
         }
     }
    data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1);
	if(LC_FAILURE!=data_addr)
	{
	   data_len = aui_flash_fetch_long(data_addr + CHUNK_OFFSET) - CHUNK_HEADER_SIZE;
	   data_addr += CHUNK_HEADER_SIZE;
	   *orig_offset = (lc_uint32)data_addr;
	   *module_len = data_len;
	    UC_SPI_MODULE_DEBUG("%s() in line(%d) moduleId = 0x%x,chunk_id = 0x%x: orig_offset = 0x%x,module_len = 0x%x!\n", __FUNCTION__, __LINE__,moduleId,chunk_id,*orig_offset,*module_len);
	}
	else
	{
	   UC_SPI_MODULE_DEBUG("%s() in line(%d) chunk_goto fail!\n", __FUNCTION__, __LINE__);
	   return  LC_FAILURE;
	}

	if((moduleId == MODULE_DRV_ID_UK)||(moduleId == MODULE_DRV_ID_LOADER_PT)||(moduleId == MODULE_DRV_ID_VARIANT))
	{
	    data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id_bak, 0xFFFFFFFF, 1);
		if(LC_FAILURE!=data_addr)
		{
		   data_len = aui_flash_fetch_long(data_addr + CHUNK_OFFSET) - CHUNK_HEADER_SIZE;
		   data_addr += CHUNK_HEADER_SIZE;
		   *bak_offset = (lc_uint32)data_addr;
		   *bak_module_len = data_len;
		    UC_SPI_MODULE_DEBUG("%s() in line(%d) moduleId = 0x%x,chunk_id_bak = 0x%x: bak_offset = 0x%x,bak_module_len = 0x%x!\n", __FUNCTION__, __LINE__,moduleId,chunk_id_bak,*bak_offset,*bak_module_len);
		}
		else
		{
		   UC_SPI_MODULE_DEBUG("%s() in line(%d) chunk_goto fail!\n", __FUNCTION__, __LINE__);
		   //return  LC_FAILURE;
		   *bak_offset = *orig_offset + NOR_ONE_BLOCK_SIZE;
		   *bak_module_len = *module_len;
           UC_SPI_MODULE_DEBUG("line(%d),force get chunk info: moduleId = 0x%x,chunk_id_bak = 0x%x: bak_offset = 0x%x,bak_module_len = 0x%x!\n", __LINE__,moduleId,chunk_id_bak,*bak_offset,*bak_module_len);
		}
	}
	 return  LC_SUCCESS; 
}


/**
 * input:moduleId
 * output:payload info(include flash type and address),
 */
lc_result LC_GetPayloadInfoFromMouldID (lc_module_id moduleId, lc_uint32 *pPayLoadAddress,
                                                lc_uint32 *pPayLoaderAddress_bak, lc_uchar *flash_type, lc_uint32 *pPrtLen,
                                                lc_uchar *flash_type_bak, lc_uint32 *bak_module_len)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_uint32 module_len = 0;
    lc_uint32 bak_md_len = 0;
	lc_uint32 chunk_id = 0;
	lc_uint32 chunk_id_bak = 0;
	lc_uint32 data_len = 0;
    lc_uchar  *data_addr = NULL;
	
	
    if(LC_NULL == pPayLoadAddress || LC_NULL == flash_type || LC_NULL == pPayLoaderAddress_bak)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) input paramter invalid:", __FUNCTION__, __LINE__);
        lc_ret = LC_FAILURE;
        goto EXIT;
    }
    if(INVAILD_MODULE == CheckModuleId(moduleId))
    {
         UC_SPI_MODULE_DEBUG("%s() in line(%d) invalid moduleId:", __FUNCTION__, __LINE__);
         lc_ret = LC_FAILURE;
         goto EXIT;
    }

    lc_ret = LC_GetChunkFromMouldID(moduleId, &chunk_id, &chunk_id_bak);
    if(LC_SUCCESS == lc_ret)
    {		
        /*  UK,Variant and Loader PT module are in the NVRAM partition */
        if( moduleId == MODULE_DRV_ID_UK || moduleId == MODULE_DRV_ID_VARIANT || moduleId == MODULE_DRV_ID_LOADER_PT )
        {
            lc_ret = lc_get_offset_from_NVRAM(moduleId, pPayLoadAddress, pPayLoaderAddress_bak, pPrtLen,&bak_md_len);
			*bak_module_len = bak_md_len;
        }
        else
        {
            if (IRD_IMAGE_MODULE_HEADER_CKID  == chunk_id)
			{
			    if (0x220000 == chunk_start)
				{
					  data_addr = IRD_IMAGE_MODULE_HEADER_CKID_ADDR_LOGO;
				}
				else
				{
					  data_addr = IRD_IMAGE_MODULE_HEADER_CKID_ADDR;
				}
			} 
			else
			    if (IRD_PSFLAG_MODULE_HEADER_CKID  == chunk_id)
				{
				    if (0x220000 == chunk_start)
					{
						  data_addr = IRD_PSFLAG_MODULE_HEADER_CKID_ADDR_LOGO;
					}
					else
					{
						  data_addr = IRD_PSFLAG_MODULE_HEADER_CKID_ADDR;
					}
				}	
		        else	
				{
				  data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1); 
				}
				   
            //data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1);
			if(LC_FAILURE!=data_addr)
		
			{
			   data_len = aui_flash_fetch_long(data_addr + CHUNK_OFFSET) - CHUNK_HEADER_SIZE;
			   data_addr += CHUNK_HEADER_SIZE;
			   UC_SPI_MODULE_DEBUG("%s() in line(%d) data_addr = 0x%x,data_len = %d !\n", __FUNCTION__, __LINE__,data_addr,data_len);
			   *pPayLoadAddress = (lc_uint32)data_addr;
			   *pPrtLen = data_len;
			   lc_ret = LC_SUCCESS;
			}
			else
			{
			   UC_SPI_MODULE_DEBUG("%s() in line(%d) chunk_goto fail!\n", __FUNCTION__, __LINE__);
			   lc_ret = LC_FAILURE;
			}
        }
    }
 
EXIT:    
    return lc_ret;
}

lc_result loadercorespi_flash_init()
{
    lc_result lc_ret = LC_SUCCESS;
    lc_sint32 err = AUI_RTN_SUCCESS;
    int i = 0; 

    if(LC_FALSE == flash_inited)
    {
		aui_flash_open_param open_param;
		aui_flash_info flash_info;

		//flash init;
		err = aui_flash_init(LC_NULL, LC_NULL);
        if (err != AUI_RTN_SUCCESS)
        {
            UC_SPI_MODULE_DEBUG("flash init fail\n");
			lc_ret = LC_FAILURE;
			return lc_ret;
        }
		
		//open norflash handle.
    	LoaderCoreSPI_Stdlib_memset (&open_param, 0, sizeof(aui_flash_open_param));
    	open_param.flash_id = PS_PARTITION_ID;
    	open_param.flash_type = FLASH_TYPE_NOR;
    	err = aui_flash_open(&open_param, &nor_flash_handle);
    	if (err != AUI_RTN_SUCCESS)
        {
            UC_SPI_MODULE_DEBUG("NOR flash deinit fail\n");
            err = aui_flash_de_init (LC_NULL, LC_NULL);
            if(AUI_RTN_SUCCESS != err)
            {
                UC_SPI_MODULE_DEBUG ("flash deinit fail\n");
            }
            nor_flash_handle = LC_NULL;
			lc_ret = LC_FAILURE;
			return lc_ret;
    	}

		LoaderCoreSPI_Stdlib_memset (&flash_info, 0, sizeof(aui_flash_info));
		err = aui_flash_info_get(nor_flash_handle, &flash_info);
    	if (err != AUI_RTN_SUCCESS)
        {
            UC_SPI_MODULE_DEBUG("Nor flash info get failed\n");
    	}
		nor_block_size = flash_info.block_size;
		nor_flash_size = flash_info.flash_size;
		UC_SPI_MODULE_DEBUG("nor flash size = 0x%x,nor block size = 0x%x\n",nor_flash_size,nor_block_size);

        //lc_ret = LoaderCoreSPI_Module_GetPrtAddr();
        if (LC_SUCCESS != lc_ret)
        {
            UC_SPI_MODULE_DEBUG("LoaderCoreSPI_Module_GetPrtAddr failed\n");
            return lc_ret;
        }
		flash_inited = LC_TRUE;
    }

	return lc_ret;
}

void data2cklenth(lc_uint32 *data)
{
    lc_uchar *ptr = (lc_uchar *)data; 
    lc_uint32 ho = (((lc_uint32)ptr[0]) << 24) | (((lc_uint32)ptr[1]) << 16) | (((lc_uint32)ptr[2]) << 8) | ((lc_uint32)ptr[3]<<0);
    *data = ho;
}

void aui_flash_chunk_init(unsigned long start, unsigned int length)
{

	if(0xFFFFFFFF == start)
    {
        return ;
    }
    
    loadercorespi_flash_init();
    if (0 == length)
    {
        if(nor_flash_handle != NULL)
        {
            length = nor_flash_size;
        }
    }
    chunk_start = start;
    chunk_end = start + length;
    chunk_maxlen = length;
}

unsigned long aui_flash_fetch_long(unsigned long offset)
{
    unsigned char buf[4] = {0};
    lc_uint32 act_len = 0;
    loadercorespi_flash_init();

    if( offset > nor_flash_size)
    {
        return 0;
    }
	
    aui_flash_read(nor_flash_handle, offset, 4, (long unsigned int *)&act_len, (unsigned char *)buf);

    return (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
}

unsigned long aui_flash_chunk_goto(unsigned long *chid, unsigned long mask, unsigned int n)
{
	unsigned long id = 0;
	unsigned long offset = 0;
	unsigned long addr = chunk_start;
	const UINT32 invalid_chunk_id = 0xFFFFFFFF;

	if ((0 == n) || (NULL == chid))
	{
		return ((unsigned long)LC_FAILURE);
	}
	
	while (addr < chunk_end)
	{
		{
			id = aui_flash_fetch_long(addr + CHUNK_ID);
			if ((0 == id) || (id == invalid_chunk_id))
			{
				break;
			}

			if (!((id ^ *chid) & mask))
			{
				--n;
				if (0 == n)
				{
					*chid = id;
					return addr;
				}
			}

			offset = aui_flash_fetch_long(addr + CHUNK_OFFSET);
			if ((0 == offset) || (offset > chunk_maxlen))
			{
				return ((unsigned long)LC_FAILURE);
			}
		}
		addr += offset;
	}
	return ((unsigned long)LC_FAILURE);
}


/*make sure that addr & len are already block align when write*/
static lc_sint32 quick_nor_read_write (lc_bool is_read, lc_uint32 addr, lc_uint32 len, void *buffer)
{
    lc_sint32 err = 0;
    lc_uint32 act_len = 0;

    if((0 == len) || (LC_NULL == buffer))
    {
        UC_SPI_MODULE_DEBUG("nor flash has been inited!\n");
        err = -1;
        return err;
    }
    
    if(is_read)
    {
        err = aui_flash_read(nor_flash_handle, addr, len, (long unsigned int *)&act_len, (unsigned char *)buffer);
    }
    else
    {
		//erase
		err = aui_flash_erase (nor_flash_handle, addr, len);
		UC_SPI_MODULE_DEBUG ("erase err = %d\n", err);
		
		//write
        err = aui_flash_write (nor_flash_handle, addr, len, (long unsigned int *)&act_len, (unsigned char *)buffer);
		UC_SPI_MODULE_DEBUG ("real write length: 0x%x, err = %d\n", act_len, err);
    }
    
    if ((len != act_len) || (AUI_RTN_SUCCESS != err))
    {
       UC_SPI_MODULE_DEBUG("write/read failed\n");
       err = -1;
    }
    else
    {
       err = 0;
    }

    return err;
}



lc_result getPsFlagChunkAddr(lc_uint32 *chunk_addr)
{
	lc_result lc_ret = LC_SUCCESS;
    lc_uint32 chunk_id = IRD_PSFLAG_MODULE_HEADER_CKID;
	lc_uint32 data_len = 0;
    lc_uchar  *data_addr = NULL;

	if (0x220000 == chunk_start)
    {
	   data_addr = IRD_PSFLAG_MODULE_HEADER_CKID_ADDR_LOGO;
	}
	else
	{
	   data_addr = IRD_PSFLAG_MODULE_HEADER_CKID_ADDR;
	}

    //data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1);
	if(LC_FAILURE!=data_addr)
	{
	   data_len = aui_flash_fetch_long(data_addr + CHUNK_OFFSET) - CHUNK_HEADER_SIZE;
	   data_addr += CHUNK_HEADER_SIZE;
	   UC_SPI_MODULE_DEBUG("%s() in line(%d) data_addr = 0x%x,data_len = %d!\n", __FUNCTION__, __LINE__,data_addr,data_len);
	   *chunk_addr = (lc_uint32)data_addr;
	   lc_ret = LC_SUCCESS;
	}
	else
	{
	   UC_SPI_MODULE_DEBUG("%s() in line(%d) chunk_goto fail!\n", __FUNCTION__, __LINE__);
	   lc_ret = LC_FAILURE;
	}
    return lc_ret;	

}



static lc_result lc_ird_module_init(void)
{
    lc_result result = LC_SUCCESS;
    lc_sint32 ret = -1;
    lc_uchar *tmp_addr = LC_NULL;
    lc_uint32 bbcb_flash_aadr = 0;
    lc_uint32 uk_flash_aadr = 0;   
    lc_uint32 variant_flash_aadr = 0;    
    lc_uint32 loaderPt_flash_aadr = 0;
	lc_uint32 bak_aadr = 0;
    lc_uint32 prt_len = 0;
    lc_uint32 bak_module_len = 0;
    
    if(LC_FALSE == g_lc_ird_module_get)
    {

        result = lc_get_offset_from_NVRAM(MODULE_DRV_ID_UK,&uk_flash_aadr, &bak_aadr, &prt_len,&bak_module_len);
        if(LC_SUCCESS == result)
        {
           result = lc_get_offset_from_NVRAM(MODULE_DRV_ID_VARIANT,&variant_flash_aadr, &bak_aadr, &prt_len,&bak_module_len);
        }
        if(LC_SUCCESS == result)
        {
           result = lc_get_offset_from_NVRAM(MODULE_DRV_ID_LOADER_PT,&loaderPt_flash_aadr, &bak_aadr, &prt_len,&bak_module_len);
        }
        if(LC_SUCCESS == result)
        {
           result = lc_get_offset_from_NVRAM(MODULE_DRV_ID_BBCB,&bbcb_flash_aadr, &bak_aadr, &prt_len,&bak_module_len);
        }
        
        /* read the BBCB module */
        if(LC_NULL == g_lc_module_bbcb && LC_SUCCESS == result)
        {
            tmp_addr = (lc_uchar*)LoaderCoreSPI_Memory_Malloc(BBCB_R_LEN);
            if(!tmp_addr)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!!!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }

            if(LC_SUCCESS == result)
            {
                LoaderCoreSPI_Stdlib_memset(tmp_addr, 0xff, BBCB_R_LEN);
                
                ret = ps_data_read_write(READ, bbcb_flash_aadr, BBCB_R_LEN, tmp_addr, 0, LC_FALSE);
                if(ret)
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read bbcb from flash failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
                else
                {            
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read bbcb from flash success!\n", __FUNCTION__, __LINE__);
                    
                    g_lc_module_bbcb = tmp_addr;
                }
            }
        }
        /* read the UK module */
        if(LC_NULL == g_lc_module_uk && LC_SUCCESS == result)
        {
            tmp_addr = (lc_uchar*)LoaderCoreSPI_Memory_Malloc(NOR_ONE_BLOCK_SIZE);
            if(!tmp_addr)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!!!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }

            if(LC_SUCCESS == result)
            {
                LoaderCoreSPI_Stdlib_memset(tmp_addr, 0xff, NOR_ONE_BLOCK_SIZE);
                ret = ps_data_read_write(READ, uk_flash_aadr, NOR_ONE_BLOCK_SIZE, tmp_addr, 0, LC_FALSE);
                if(ret)
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read uk from flash failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
                else
                {            
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read uk from flash success!\n", __FUNCTION__, __LINE__);
                    
                    g_lc_module_uk = tmp_addr;
                }
            }
        }

        /* read the Variant module */
        if(LC_NULL == g_lc_module_variant && LC_SUCCESS == result)
        {
            tmp_addr = (lc_uchar*)LoaderCoreSPI_Memory_Malloc(NOR_ONE_BLOCK_SIZE);
            if(!tmp_addr)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!!!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }

            if(LC_SUCCESS == result)
            {
                LoaderCoreSPI_Stdlib_memset(tmp_addr, 0xff, NOR_ONE_BLOCK_SIZE);
                
                ret = ps_data_read_write(READ, variant_flash_aadr, NOR_ONE_BLOCK_SIZE, tmp_addr,0, LC_FALSE);
                if(ret)
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read variant from flash failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
                else
                {            
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read variant from flash success!\n", __FUNCTION__, __LINE__);
                    
                    g_lc_module_variant = tmp_addr;
                }
            }
        }

        /* read the LoaderPt module */
        if(LC_NULL == g_lc_module_loaderPt && LC_SUCCESS == result)
        {
            tmp_addr = (lc_uchar*)LoaderCoreSPI_Memory_Malloc(NOR_ONE_BLOCK_SIZE);
            if(!tmp_addr)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!!!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }

            if(LC_SUCCESS == result)
            {
                LoaderCoreSPI_Stdlib_memset(tmp_addr, 0xff, NOR_ONE_BLOCK_SIZE);
                ret = ps_data_read_write(READ, loaderPt_flash_aadr, NOR_ONE_BLOCK_SIZE, tmp_addr,0, LC_FALSE);
                if(ret)
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read loaderPT from flash failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
                else
                {            
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) read loaderPT from flash success!\n", __FUNCTION__, __LINE__);
                    
                    g_lc_module_loaderPt = tmp_addr;
                }
            }
        }

        if(g_lc_module_loaderPt && g_lc_module_variant && g_lc_module_uk && g_lc_module_bbcb )
        {
            g_lc_ird_module_get = LC_TRUE;
        }
    }

    return result;
}

static lc_result lc_HL_module_header_init(void)
{
    lc_result result = LC_SUCCESS;
    lc_sint32 ret = -1;

    lc_uchar *tmp_addr = LC_NULL;
    lc_uint32 moduleHeader_flash_aadr = 0;

    lc_uint32 chunk_id = IRD_IMAGE_MODULE_HEADER_CKID;
	lc_uint32 data_len = 0;
    lc_uchar *data_addr = NULL;
    
    if(LC_NULL == g_lc_module_list)
    {    
		//data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1);   // need fixed

		if (0x220000 == chunk_start)
		{
		  data_addr = IRD_IMAGE_MODULE_HEADER_CKID_ADDR_LOGO;
		}
		else
		{
		  data_addr = IRD_IMAGE_MODULE_HEADER_CKID_ADDR;
		}
		
		if(LC_FAILURE!=data_addr)
	
		{
            data_len = aui_flash_fetch_long(data_addr + CHUNK_OFFSET) - CHUNK_HEADER_SIZE;
			data_addr += CHUNK_HEADER_SIZE;
		    moduleHeader_flash_aadr = (lc_uint32)data_addr;
			UC_SPI_MODULE_DEBUG("%s() in line(%d) moduleHeader_flash_aadr = 0x%x,data_len = 0x%x!\n", __FUNCTION__, __LINE__,moduleHeader_flash_aadr,data_len);
		}
        else
        {
          result = LC_FAILURE;
        }
		
        tmp_addr = (lc_uchar*)LoaderCoreSPI_Memory_Malloc(data_len);
        if(!tmp_addr)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!!!\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }
    
        if(LC_SUCCESS == result)
        {
            LoaderCoreSPI_Stdlib_memset(tmp_addr, 0xff, data_len);
            ret = ps_data_read_write(READ, moduleHeader_flash_aadr, data_len, tmp_addr, 0, LC_FALSE);
            if(ret)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) read module header flash failed!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }
            else
            {            
                UC_SPI_MODULE_DEBUG("%s() in line(%d) read module header flash success!\n", __FUNCTION__, __LINE__);
                
                g_lc_module_list = (lc_module_base_info*)tmp_addr;
            }
        }

    }

    return result;
}


/**
 *  1.init the flash
 *  2.read BBCB, LoaderPt, UK and Variant to a static addr
 *  3.read HL module base info and HL module header to a static addr
 */
static lc_result lc_module_list_init(void)
{
    lc_result result = LC_SUCCESS;

    /* init the flash */
	result = loadercorespi_flash_init ();
	if (LC_SUCCESS != result)
	{
        UC_SPI_MODULE_DEBUG("%s() in line(%d) loadercorespi_flash_init failed!\n", __FUNCTION__, __LINE__);
		return result;
	}

    /* read the ird internal module from the flash */
    result = lc_ird_module_init();
	if (LC_SUCCESS != result)
	{
        UC_SPI_MODULE_DEBUG("%s() in line(%d) lc_ird_module_init failed!\n", __FUNCTION__, __LINE__);
		return result;
	}
    
    /* read HL module base info and header */
    result = lc_HL_module_header_init();
	if (LC_SUCCESS != result)
	{
        UC_SPI_MODULE_DEBUG("%s() in line(%d) lc_HL_module_header_init failed!\n", __FUNCTION__, __LINE__);
		return result;
	}
    
	return result;
}

lc_sint32 ps_data_read_write(lc_bool is_read, lc_uint32 addr, lc_uint32 len, void *buffer, lc_uint32 type, lc_bool eraseAll)
{
    lc_sint32 ret = -1;
    lc_sint32 err = 0;
    lc_uint32 act_len = 0;
    aui_hdl flash_handle = LC_NULL;
    unsigned long block_size = 0;
    unsigned long block_start_addr = 0;
    unsigned char *tmp_buffer = LC_NULL;
    unsigned long write_size = 0;
    unsigned long read_size = 0 ;
    unsigned long page_size = MAX_NAND_PAGESZIE;
    lc_uint32 rw_addr = addr; // support nand partition, the addr need to translate to base on partition
    UC_SPI_MODULE_DEBUG("enter %s is_read? %d, addr: 0x%x, len: 0x%x, type:%d\n",
                        __func__, is_read, addr, len, type);

    lc_uint32 start_addr = 0, start_size = 0;
    lc_uint32 m_addr = rw_addr, m_size = len;
    lc_uint32 end_addr = 0, end_size = 0;
    lc_result lc_ret = LC_SUCCESS;
    aui_flash_info erase_flash_info;

    flash_handle = nor_flash_handle;
    block_size = nor_block_size;

    if(LC_NULL == flash_handle)
    {
        UC_SPI_MODULE_DEBUG("flash has not been inited!\n");
        return ret;
    }

    if((0 == len) || (LC_NULL == buffer))
    {
        UC_SPI_MODULE_DEBUG("invalid parameter\n");
        return ret;
    }

    /* just erase len bytes space from start_addr */
    LoaderCoreSPI_Stdlib_memset(&erase_flash_info, 0, sizeof(erase_flash_info));
    if( LC_TRUE == eraseAll)
    {
       // LoaderCoreSPI_take_a_break();
        err = aui_flash_info_get(flash_handle, &erase_flash_info );
       // LoaderCoreSPI_take_a_break();
    	if (err != AUI_RTN_SUCCESS) 
        {
            UC_SPI_MODULE_DEBUG("%s(%d):aui_flash_info_get fail\n",  __FUNCTION__, __LINE__);
    		return 1;
    	}
       // LoaderCoreSPI_take_a_break();
        
        err = aui_flash_erase(flash_handle, rw_addr, len);
    	if (err != AUI_RTN_SUCCESS) 
        {
            UC_SPI_MODULE_DEBUG("%s(%d):aui_flash_erase failed\n",  __FUNCTION__, __LINE__);
    		return 1;
    	}
        //LoaderCoreSPI_take_a_break();        
        UC_SPI_MODULE_DEBUG("%s(%d):erase err = %d\n", __FUNCTION__, __LINE__, err);
        ret = 0;
        goto EXIT;
    }

    if(is_read)
    {
      
        // LoaderCoreSPI_take_a_break();
         err = aui_flash_read(flash_handle, rw_addr, len,(long unsigned int *)&act_len,(unsigned char *)buffer);
        // LoaderCoreSPI_take_a_break();
         if((len != act_len) || (AUI_RTN_SUCCESS != err))
         {
            UC_SPI_MODULE_DEBUG("write/read failed\n");
            ret = -1;
         }
         else
         {
             ret = 0;
         }
    }
    else
    {
        // 1. start address is block align?
        if(rw_addr % block_size)
        {
            start_addr = rw_addr - (rw_addr % block_size);

            if((rw_addr + len) - start_addr <= block_size)
                start_size = len;
            else
                start_size = block_size - (rw_addr % block_size);

            m_addr = start_addr + block_size;
            m_size = len - start_size;
        }

        // 2. the end address is block align?
        if((m_size > 0) && ((rw_addr + len) % block_size))
        {
            end_addr = ((rw_addr + len) / block_size) * block_size;
            end_size = (rw_addr + len) - end_addr;
            m_size -= end_size;
        }

        UC_SPI_MODULE_DEBUG("write addr(0x%x) len(0x%x), adjust to: s(0x%x, 0x%x), m(0x%x, 0x%x), e(0x%x, 0x%x)\n",
                            rw_addr, len, (unsigned int)start_addr, (unsigned int)start_size, (unsigned int)m_addr, (unsigned int)m_size, (unsigned int)end_addr, (unsigned int)end_size);

        // 3. write start
        if(start_size > 0)
        {
            tmp_buffer = LoaderCoreSPI_Memory_Malloc(block_size);

            if(LC_NULL == tmp_buffer)
            {
                UC_SPI_MODULE_DEBUG("malloc tmp_buffer failed\n");
                return -1;
            }

            LoaderCoreSPI_Stdlib_memset(tmp_buffer, 0, block_size);
            UC_SPI_MODULE_DEBUG("[write start]read/erase/write at: 0x%x, len: 0x%x\n", start_addr, block_size);
            err = aui_flash_read(flash_handle, start_addr, block_size,
                                 (long unsigned int *)&act_len,
                                 (unsigned char *)tmp_buffer);
            // combine buffer to the end of tmp_buffer
            LoaderCoreSPI_Stdlib_memcpy(tmp_buffer + rw_addr % block_size, buffer, start_size);
           // LoaderCoreSPI_take_a_break();
            err = aui_flash_erase(flash_handle, start_addr, block_size);
	    if(err)
		    err = aui_flash_erase(flash_handle, start_addr, block_size);
           // LoaderCoreSPI_take_a_break();
            err = aui_flash_write(flash_handle, start_addr, block_size,
                                  (long unsigned int *)&act_len,
                                  (unsigned char *)tmp_buffer);
           // LoaderCoreSPI_take_a_break();
            UC_SPI_MODULE_DEBUG("[write start] real read/erase/write at: 0x%x, len: 0x%x\n", start_addr, act_len);
        }

        // 4. write middle
        if(m_size > 0)
        {
            UC_SPI_MODULE_DEBUG("[write m]erase/write at: 0x%x, len: 0x%x\n", m_addr, m_size);
           // LoaderCoreSPI_take_a_break();
            err = aui_flash_erase(flash_handle, m_addr, m_size);
	    if(err)
		    err = aui_flash_erase(flash_handle, start_addr, block_size);
           // LoaderCoreSPI_take_a_break();
            UC_SPI_MODULE_DEBUG("erase err = %d\n", err);
            err = aui_flash_write(flash_handle, m_addr, m_size,
                                  (long unsigned int *)&act_len,
                                  (unsigned char *)buffer + start_size);
           // LoaderCoreSPI_take_a_break();
            UC_SPI_MODULE_DEBUG("[write m]real write length: 0x%x, err = %d\n", act_len, err);
        }

        // 5. write tail
        if(end_size > 0)
        {
            UC_SPI_MODULE_DEBUG("[write end]read/erase/write at: 0x%x, len: 0x%x\n", end_addr, act_len);

            if(!tmp_buffer)
            {
                tmp_buffer = LoaderCoreSPI_Memory_Malloc(block_size);

                if(LC_NULL == tmp_buffer)
                {
                    UC_SPI_MODULE_DEBUG("malloc tmp_buffer failed\n");
                    return -1;
                }
            }

            LoaderCoreSPI_Stdlib_memset(tmp_buffer, 0, block_size);
           // LoaderCoreSPI_take_a_break();
            err = aui_flash_read(flash_handle, end_addr, block_size,
                                 (long unsigned int *)&act_len,
                                 (unsigned char *)tmp_buffer);
           // LoaderCoreSPI_take_a_break();
            LoaderCoreSPI_Stdlib_memcpy(tmp_buffer, buffer + len - end_size, end_size);
            err = aui_flash_erase(flash_handle, end_addr, block_size);
	    if(err)
		    err = aui_flash_erase(flash_handle, start_addr, block_size);
           // LoaderCoreSPI_take_a_break();
            err = aui_flash_write(flash_handle, end_addr, block_size,
                                  (long unsigned int *)&act_len,
                                  (unsigned char *)tmp_buffer);
           // LoaderCoreSPI_take_a_break();
            UC_SPI_MODULE_DEBUG("[write end]read/erase/write at: 0x%x, len: 0x%x\n", end_addr, act_len);
        }

        if(tmp_buffer)
        {
            LoaderCoreSPI_Memory_Free(tmp_buffer);
            tmp_buffer = LC_NULL;
        }

        write_size = start_size + m_size + end_size;

        if(/*(write_size != act_len) || */(AUI_RTN_SUCCESS != err))
        {
            UC_SPI_MODULE_DEBUG("write/read failed\n");
            ret = -1;
        }
        else
        {
            ret = 0;
        }
    }

EXIT:
    UC_SPI_MODULE_DEBUG("leave %s with ret: %d\n", __func__, ret);
    return ret;
}

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
 * @param pModuleIdCount   [OUT] Total number of modules in the module list
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

/**
 * this spi is just for get all HL module array, for ALi design, the max HL module num is 0x20
 *
 */
lc_result LoaderCoreSPI_Module_GetModuleIdList(lc_uint16 **ppModuleIdList, lc_uint32 *pModuleIdCount)
{
    lc_result result = LC_SUCCESS;
    int i = 0;
    lc_uint16 *node_id = LC_NULL;
    lc_uint16 *node = LC_NULL;;
    lc_uint16 module_count =0;
    
    if((LC_NULL == ppModuleIdList) || (LC_NULL == pModuleIdCount))
    {
        result = LC_ERROR_NULL_PARAM;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) input parameters invaild!\n", __FUNCTION__, __LINE__);
        return result;
    }
    result = lc_module_list_init();
    if(LC_SUCCESS != result || LC_NULL == g_lc_module_list)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) module list is NULL!\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_MODULE_NOT_FOUND;
    }

    if(LC_SUCCESS == result)
    {
        result = LC_CheckModuleHeader(g_lc_module_list, MAX_HL_MODULE_NUM);
        if(LC_SUCCESS == result)
        {
            /* malloc an lc_uint16 array of module ids */
    		node_id = LoaderCoreSPI_Memory_Malloc (sizeof (lc_uint16) * MAX_HL_MODULE_NUM);
    		if (LC_NULL == node_id)
    		{
                UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc size %d error\n", __FUNCTION__, __LINE__, sizeof (lc_uint16) * MAX_HL_MODULE_NUM);
    			return LC_FAILURE;
    		}
    		LoaderCoreSPI_Stdlib_memset (node_id, 0, sizeof (lc_uint16) * MAX_HL_MODULE_NUM);
    		node = node_id;
    		while (i < MAX_HL_MODULE_NUM)
    		{
    			if (LC_MODULE_EXIT == g_lc_module_list->is_exist[i]) //index i module is exist
    			{
    				*node = (lc_uint16)g_lc_module_list->module_id[i];
    				node++;
                    module_count++;
    			}
    			i++;
    		}
            *ppModuleIdList = node_id;
            *pModuleIdCount = module_count;
        }
        else
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) the HL module base info is invaild, can not get the module list!\n", __FUNCTION__, __LINE__);
        }
    }
	
	return result;
}

static lc_result DelModuleInModuleList(lc_uint16 moduleId, lc_uint32 index)
{
    lc_result lc_ret = LC_SUCCESS;
    lc_module_type module_type = INVAILD_MODULE;
    lc_uchar * header_addr = 0;
    lc_module_base_info *pModule_base_info = LC_NULL;
    lc_uint32 tmp_index = 0xff;
    
    if( LC_FALSE == checkModuleExist(moduleId, &tmp_index))
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) module is exist, no need to add modult info!\n", __FUNCTION__, __LINE__);
        goto EXIT;
    }
    if(MIN_MODULE_ID_APP > moduleId)
    {
        if(MODULE_DRV_ID_BBCB == moduleId || MODULE_DRV_ID_LOADER_CORE == moduleId)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module is exist, no need to add modult info!\n", __FUNCTION__, __LINE__);
        }
        switch(moduleId)
        {
            case MODULE_DRV_ID_UK:
    		{
                pModule_base_info = (lc_module_base_info *)g_lc_module_uk;
                break;
    		}
            case MODULE_DRV_ID_LOADER_PT:
    		{
                pModule_base_info = (lc_module_base_info *)g_lc_module_loaderPt;
                break;

    		}
            case MODULE_DRV_ID_VARIANT:
    		{
                pModule_base_info = (lc_module_base_info *)g_lc_module_variant;
                break;
    		} 
            default:
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
                lc_ret = LC_FAILURE;
                break;
            }

            if(pModule_base_info)
            {
                pModule_base_info->module_count = 0;
                pModule_base_info->is_exist[0] = 0;
                pModule_base_info->module_id[0]= -1;
            }
            else
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) del #%d module failed!\n", __FUNCTION__, __LINE__,moduleId);
                lc_ret = LC_FAILURE;
                goto EXIT;
            }
        }
    }
    else
    {
        /* del HL module in the module list */
        if(LC_NULL == g_lc_module_list)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d)module_list is NULL!\n", __FUNCTION__, __LINE__);
            lc_ret = LC_FAILURE;
            goto EXIT;
        }
        
        if(0 == g_lc_module_list->module_count)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module_list is empty!\n", __FUNCTION__, __LINE__);
            lc_ret = LC_FAILURE;
            goto EXIT;
        }
        header_addr = (lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index * EACH_MOD_HADER_RAW_LEN;
        
        /* del the module id in the module base info */
        g_lc_module_list->module_id[index]= -1;
        g_lc_module_list->is_exist[index] = 0;
        g_lc_module_list->module_count--;

        /* update module header */
        LoaderCoreSPI_Stdlib_memset(header_addr, 0xff, EACH_MOD_HADER_RAW_LEN);
        
    }
        
EXIT:
    if(LC_SUCCESS == lc_ret)
    {       
        UC_SPI_MODULE_DEBUG("%s() in line(%d) del #%d module success!\n", __FUNCTION__, __LINE__, moduleId);
    }
    else
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) del #%d module failed!\n", __FUNCTION__, __LINE__, moduleId);
    }
    return lc_ret;

}

static lc_result DelModuleHeader(lc_uint16 moduleId)
{
    lc_result result = LC_SUCCESS;
    lc_module_type module_type = INVAILD_MODULE;

    lc_uchar *mem_start = LC_NULL;
    lc_module_info_header header_info={0};
    lc_uchar * tmp = LC_NULL;
    lc_uint32 index = 0xff;
    lc_uint32 module_header_addr = 0;

    if((MODULE_DRV_ID_BBCB == moduleId) || (MODULE_DRV_ID_LOADER_CORE == moduleId))
    {
        UC_SPI_MODULE_DEBUG("%s %d:Parametors invaild\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_NULL_PARAM;
    }

    if(LC_SUCCESS == result)
    {
        result = lc_module_list_init();
    }
    if(LC_SUCCESS == result)
    {    
        if( LC_FALSE == checkModuleExist(moduleId, &index))
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist, no need to delete!\n", __FUNCTION__, __LINE__);
            return LC_SUCCESS;
        }

        if(MIN_MODULE_ID_APP > moduleId)
        {
            switch(moduleId)
            {
                case MODULE_DRV_ID_UK:
            	{
                    module_header_addr = (lc_uint32)g_lc_module_uk + IRD_MOD_HEADER_OFFSET;
                    break;
            	}
                case MODULE_DRV_ID_LOADER_PT:
            	{
                    module_header_addr = (lc_uint32)g_lc_module_loaderPt + IRD_MOD_HEADER_OFFSET;
                    break;

            	}
                case MODULE_DRV_ID_VARIANT:
            	{
                    module_header_addr = (lc_uint32)g_lc_module_variant + IRD_MOD_HEADER_OFFSET;
                    break;
            	} 
                default:
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                    break;
                }
            }
                
        }
        else
        {
            if(g_lc_module_list)
            {
                module_header_addr = (lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index*EACH_MOD_HADER_RAW_LEN;
            }
        }

        if( LC_SUCCESS == result)
        {                
            tmp = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(EACH_MOD_HADER_RAW_LEN);
            if(!tmp)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) LoaderCoreSPI_Memory_Malloc failed!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }
            else
            {
                LoaderCoreSPI_Stdlib_memset(tmp , 0xff, EACH_MOD_HADER_RAW_LEN);
                LoaderCoreSPI_Stdlib_memcpy(module_header_addr, tmp, EACH_MOD_HADER_RAW_LEN);
            }
        }
        
    }
    
    if(!tmp)
    {
        LoaderCoreSPI_Memory_Free(tmp);
        tmp = LC_NULL;
    }
    return result;

}

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
lc_result LoaderCoreSPI_Module_ReadModuleHeader(lc_uint16 moduleId, lc_buffer_st *pModuleHeader)
{   
    lc_result result = LC_SUCCESS;
    lc_result lc_ret = LC_SUCCESS;
    lc_uint32 index = 0xff;
    lc_buffer_st header = {LC_NULL, 0};
    lc_module_info_header header_info;
    lc_uchar *mem_start = LC_NULL;
    lc_uint32 BitPos = 0;
    
    if(LC_NULL == pModuleHeader )
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) input parameter invaild!\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_NULL_PARAM;
    }

    if(moduleId == MODULE_DRV_ID_LOADER_CORE || moduleId == MODULE_DRV_ID_BBCB)
    {
        result = LC_ERROR_NULL_PARAM;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) Header of Module 1~2 is not used!\n", __FUNCTION__, __LINE__);
    }

	UC_SPI_MODULE_DEBUG ("read header of moduleId = %d\n", moduleId);

    if(LC_SUCCESS == result)
    {
        result = lc_module_list_init();
    }
    
    if(LC_SUCCESS == result)
    {
        if(LC_FALSE == checkModuleExist(moduleId, &index))
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module #%d is not exist!\n", __FUNCTION__, __LINE__, moduleId);
            result = LC_FAILURE;
        }

        if(LC_SUCCESS == result)
        {
            if(MIN_MODULE_ID_APP > moduleId)
            {
                switch(moduleId)
                {
                    case MODULE_DRV_ID_UK:
            		{
                        header.bytes = (lc_uint32)g_lc_module_uk + IRD_MOD_HEADER_OFFSET;
                        break;
            		}
                    case MODULE_DRV_ID_LOADER_PT:
            		{
                        header.bytes = (lc_uint32)g_lc_module_loaderPt + IRD_MOD_HEADER_OFFSET;
                        break;

            		}
                    case MODULE_DRV_ID_VARIANT:
            		{
                        header.bytes = (lc_uint32)g_lc_module_variant + IRD_MOD_HEADER_OFFSET;
                        break;
            		} 
                    default:
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
                        break;
                    }
                }
            }
            else
            {
                header.bytes = (lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index*EACH_MOD_HADER_RAW_LEN;
            }
            
    		header.length = EACH_MOD_HADER_RAW_LEN;
        }
        
        if(LC_SUCCESS == result)
        {
#if 1
    		/* parse out the module header info */
    		LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
    		result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
    		if (LC_SUCCESS != result)
    		{
                UC_SPI_MODULE_DEBUG("%s() in line(%d) MessageParser_ParseModuleInfoHeader parse module #%d header failed!\n", __FUNCTION__, __LINE__, moduleId);
                result = LC_FAILURE;
    		}

            if(LC_SUCCESS == result)
            {
        		pModuleHeader->length = header_info.header_length;
        		pModuleHeader->bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(header_info.header_length);
            
#else

        		pModuleHeader->length = sizeof(lc_module_info_header);
        		pModuleHeader->bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(pModuleHeader->length);
#endif       
        	    if(LC_NULL == pModuleHeader->bytes)
        	    {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!\n", __FUNCTION__, __LINE__);
        	        result = LC_FAILURE;
        	    }
            }
        }
        
        if(LC_SUCCESS == result)
        {
    		LoaderCoreSPI_Stdlib_memset(pModuleHeader->bytes, 0, pModuleHeader->length);
    		LoaderCoreSPI_Stdlib_memcpy(pModuleHeader->bytes, header.bytes, pModuleHeader->length);
        }
    }

    return result;
}

static lc_result LC_ReadIrdInternalModulePayload(lc_uint16 moduleId, lc_buffer_st *pModulePayload)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 index = 0xff;
    lc_buffer_st header = {LC_NULL, 0};
    lc_module_info_header header_info;
    lc_uint32 BitPos = 0;
    lc_uint32 module_start_addr = 0;
    
    if(LC_NULL == pModulePayload || MIN_MODULE_ID_APP <= moduleId )
    {        
        UC_SPI_MODULE_DEBUG("%s() in line(%d) Parameters invaild!\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_NULL_PARAM;
    }
    if( LC_SUCCESS == result)
    {
       /**
        * special process for LOADER_CORE module
        */
        if (MODULE_DRV_ID_LOADER_CORE == moduleId)
        {
            pModulePayload->length = LOADERCORE_LEN;
            pModulePayload->bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(pModulePayload->length);
            if(LC_NULL == pModulePayload->bytes)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!!!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }

            if(LC_SUCCESS == result)
            {
                LoaderCoreSPI_Stdlib_memset(pModulePayload->bytes, FAKE_LOADER_CORE_PAYLOAD, pModulePayload->length);
                return result;
            }
        }
       /**
        * special process for BBCB module
        */
        else if(MODULE_DRV_ID_BBCB == moduleId)
        {
            pModulePayload->length = BBCB_R_LEN;
            pModulePayload->bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(pModulePayload->length);
            if(LC_NULL == pModulePayload->bytes)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!!!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }
            if(LC_SUCCESS == result)
            {
                LoaderCoreSPI_Stdlib_memcpy(pModulePayload->bytes, g_lc_module_bbcb, pModulePayload->length);

               /**
                  * BBCB is invalid?
                  */
                if((pModulePayload->bytes[0] == 0xff) &&(pModulePayload->bytes[1] == 0xff) && \
                    (pModulePayload->bytes[2] == 0xff) && (pModulePayload->bytes[3] == 0xff))
                {
                    /* NEVER should go here */
                    result = LC_FAILURE;
                }
                return result;
            }
        }
        else
        {
            if(LC_FALSE == checkModuleExist(moduleId, &index))
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) module #%d is not exist!\n", __FUNCTION__, __LINE__,moduleId);
                result = LC_FAILURE;
            }

            if(LC_SUCCESS == result)
            {
                switch(moduleId)
                {
                    case MODULE_DRV_ID_UK:
            		{
                        module_start_addr = (lc_uint32)g_lc_module_uk ;
                        break;
            		}
                    case MODULE_DRV_ID_LOADER_PT:
            		{
                        module_start_addr = (lc_uint32)g_lc_module_loaderPt ;
                        break;

            		}
                    case MODULE_DRV_ID_VARIANT:
            		{
                        module_start_addr = (lc_uint32)g_lc_module_variant ;
                        break;
            		} 
                    default:
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module\n", __FUNCTION__, __LINE__);
                        break;
                    }
                }
            }

            if(LC_SUCCESS == result && module_start_addr)
            {
                header.bytes = (lc_uint32)module_start_addr + IRD_MOD_HEADER_OFFSET;    //
                header.length = EACH_MOD_HADER_RAW_LEN;                                 //
                
            	LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
        		result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
                if(LC_SUCCESS == result)
                {
                    /* check the module is invaild? */
                    if(LC_FALSE == CheckExistModuleVaild(moduleId, &header_info))
                    {
                        UC_SPI_MODULE_DEBUG("module list contains #%u module, but the module header is invaild!\n", moduleId);
                        if( LC_SUCCESS != DelModuleInModuleList(moduleId, index))
                        {                
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) delete #%u module failed!!!\n", __FUNCTION__, __LINE__, moduleId);
                        }

                        if( LC_SUCCESS != UpdateIrdetoModuleInfoHeader(moduleId))     //from bak to resume
                        {                
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) UpdateHLModuleInfoHeader failed!!!\n", __FUNCTION__, __LINE__);
                        }
                        result = LC_FAILURE;
                    }
                    else
                    {
                		pModulePayload->length = header_info.module_size;
                		pModulePayload->bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(pModulePayload->length);
                        if(LC_NULL == pModulePayload->bytes)
                	    {
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed\n", __FUNCTION__, __LINE__);
                	        result = LC_FAILURE;
                	    }
                        else
                        {
                        	LoaderCoreSPI_Stdlib_memset (pModulePayload->bytes, 0, pModulePayload->length);
                            /* copy the ird module payload to target addr */
                        	LoaderCoreSPI_Stdlib_memcpy (pModulePayload->bytes, module_start_addr + IRD_MOD_PAYLOAD_OFFSET + header_info.header_length, pModulePayload->length);
                        }
                    }
               }
               else
               {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) MessageParser_ParseModuleInfoHeader failed!\n", __FUNCTION__, __LINE__);
               }
            }
            else
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) module_start_addr is NULL, unexpect error!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }
        }
    }

    return result;
}

static lc_result LC_ReadHLModulePayload(lc_uint16 moduleId, lc_buffer_st *pModulePayload, lc_bool readBakHLMod)
{
    lc_result result =LC_SUCCESS;
    lc_uint32 index = 0xff;
    lc_module_base_info *module_base_info;
    lc_buffer_st header = {LC_NULL, 0};
    lc_module_info_header header_info;
    lc_uint32 BitPos = 0;
    lc_uint32 module_start_addr = 0;
    lc_sint32 ret = -1;
    lc_uint32 payload_read_addr = 0;
    lc_uint32 payload_read_addr_bak = 0;
    lc_uint32 prtLen = 0;
    lc_uchar flash_type=0xff;
    lc_uint32 prtLen_bak = 0;
    lc_uchar flash_type_bak =0xff;
    
    if(LC_NULL == pModulePayload || MIN_MODULE_ID_APP > moduleId )
    {        
        UC_SPI_MODULE_DEBUG("%s() in line(%d) Parameters invaild!\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_NULL_PARAM;
    }

    /* check module is exist or not */
    if(LC_FALSE == checkModuleExist(moduleId, &index))
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }

    if(LC_SUCCESS == result)
    {
        header.bytes = (lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index* EACH_MOD_HADER_RAW_LEN;
        header.length = EACH_MOD_HADER_RAW_LEN;
        
    	LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
		result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
        if(LC_SUCCESS == result)
        {
            /* check the module is invaild? */
            if(LC_FALSE == CheckExistModuleVaild(moduleId, &header_info))
            {
                UC_SPI_MODULE_DEBUG("module list contains #%u module, but the module header is invaild!\n", moduleId);
                if( LC_SUCCESS != DelModuleInModuleList(moduleId, index))
                {                
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) delete #%u module failed!!!\n", __FUNCTION__, __LINE__, moduleId);
                }

                if( LC_SUCCESS != UpdateHLModuleInfoHeader())
                {                
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) UpdateHLModuleInfoHeader failed!!!\n", __FUNCTION__, __LINE__);
                }
                result = LC_FAILURE;
            }
            else
            {
        		pModulePayload->length = header_info.module_size;
        		pModulePayload->bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(pModulePayload->length);
                if(LC_NULL == pModulePayload->bytes)
        	    {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!\n", __FUNCTION__, __LINE__);
        	        result = LC_FAILURE;
        	    }
                
                if(LC_SUCCESS == result)
                {
                    result = LC_GetPayloadInfoFromMouldID(moduleId, &payload_read_addr, &payload_read_addr_bak, &flash_type, &prtLen, 
                                                            &flash_type_bak, &prtLen_bak);
				    if((MODULE_DRV_ID_MAIN == moduleId)|| (MODULE_DRV_ID_SEE == moduleId))
				    {
				       payload_read_addr -= CHUNK_HEADER_SIZE;
					   payload_read_addr_bak -= CHUNK_HEADER_SIZE;
				    }
				
                    if(LC_SUCCESS == result)
                    {
                        /* read HL module payload from flash to target addr */
                        if(LC_FALSE == readBakHLMod)
                        {
                            ret = ps_data_read_write(READ, payload_read_addr, pModulePayload->length, pModulePayload->bytes, flash_type, LC_FALSE);
                        }
                        else
                        {
                            if(payload_read_addr_bak)
                            {
                                ret = ps_data_read_write(READ, payload_read_addr_bak, pModulePayload->length, pModulePayload->bytes, flash_type_bak, LC_FALSE);
                            }
                            else
                            {
                                 UC_SPI_MODULE_DEBUG("%s() in line(%d) payload_read_addr_bak is invaild!\n", __FUNCTION__, __LINE__);
                                 ret = -1;
                            }
                        }
                        
                        if(ret)
                        {
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write failed!\n", __FUNCTION__, __LINE__);
                            result = LC_ERROR_MODULE_ACCESS_ERROR;      
                        }
                        else
                        {
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write success!\n", __FUNCTION__, __LINE__);
                        }
                    }
                    else
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) LC_GetPayloadInfoFromMouldID failed!\n", __FUNCTION__, __LINE__);
                        result = LC_FAILURE;
                    }
                }
            }
        }
        else
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) MessageParser_ParseModuleInfoHeader failed!\n", __FUNCTION__, __LINE__);
        }
    }

    if(LC_SUCCESS == result)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) LC_ReadHLModulePayload success!\n", __FUNCTION__, __LINE__);
    }
    else
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) LC_ReadHLModulePayload failed!\n", __FUNCTION__, __LINE__);
    }

    return result;
}


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
lc_result LoaderCoreSPI_Module_ReadModulePayload(lc_uint16 moduleId, lc_buffer_st *pModulePayload)
{
    lc_result result = LC_SUCCESS;
    lc_result lc_ret = LC_SUCCESS;
    lc_uchar *mem_start = LC_NULL;
    lc_module_info_header header_info={0};
    lc_buffer_st header={0};
    lc_uint32 BitPos = 0;
    lc_uint32 payload_read_addr = 0;
    lc_uint32 payload_read_addr_bak = 0;
    lc_uchar flash_type=0;
    lc_uint32 index = 0xff;
    
    if(LC_NULL == pModulePayload)
    {        
        UC_SPI_MODULE_DEBUG("%s() in line(%d) Parameters invaild!\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_NULL_PARAM;
    }
    UC_SPI_MODULE_DEBUG("%s() in line(%d) read payload of moduleId = #%d\n", __FUNCTION__, __LINE__, moduleId);

    if(LC_SUCCESS == result)
    {
        result = lc_module_list_init();
    }
    
    if(LC_SUCCESS == result)
    {
        if(MIN_MODULE_ID_APP > moduleId)
        {
            result = LC_ReadIrdInternalModulePayload(moduleId, pModulePayload);
        }
        else
        {
            result = LC_ReadHLModulePayload(moduleId, pModulePayload, LC_FALSE);
        }
    }
    
    if(LC_SUCCESS == result)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) read payload of moduleId = #%d success!\n", __FUNCTION__, __LINE__, moduleId);
    }
    else
    {    
        UC_SPI_MODULE_DEBUG("%s() in line(%d) read payload of moduleId = #%d failed!\n", __FUNCTION__, __LINE__, moduleId);
    }

    return result;
}

static lc_result UpdateIrdetoModuleInfoHeader(lc_uint16 moduleId)
{   
    lc_result result = LC_SUCCESS;
    lc_module_base_info *module_base_info = LC_NULL;
    lc_sint32 ret = -1;
    lc_uint32 PayLoadAddress = 0;
    lc_uchar  flash_type = 0xff;
    lc_uint32 PayLoaderAddress_bak = 0;
    lc_uint32 prtLen = 0;
    lc_uchar  flash_type_bak = 0xff;
    lc_uint32 prtLen_bak = 0;

    if(moduleId >= MIN_MODULE_ID_APP)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) input parameter invaild!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }
    if(MODULE_DRV_ID_LOADER_CORE == moduleId || MODULE_DRV_ID_BBCB == moduleId)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) BBCB or LOADER_CORE no need module header!\n", __FUNCTION__, __LINE__);
        return result;
    }

    if(LC_SUCCESS == result)
    {
        switch(moduleId)
        {
            case MODULE_DRV_ID_UK:
        	{
                module_base_info = (lc_module_base_info *)g_lc_module_uk;
                break;
        	}
            case MODULE_DRV_ID_LOADER_PT:
        	{
                module_base_info = (lc_module_base_info *)g_lc_module_loaderPt;
                break;

        	}
            case MODULE_DRV_ID_VARIANT:
        	{
                module_base_info = (lc_module_base_info *)g_lc_module_variant;
                break;
        	} 
            default:
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
                break;
            }
        }

        if(module_base_info)  
        {
            result = LC_GetPayloadInfoFromMouldID(moduleId, &PayLoadAddress, &PayLoaderAddress_bak, &flash_type, &prtLen, &flash_type_bak,&prtLen_bak);

            if(LC_SUCCESS == result)
            {
                /* update orig partition */
                ret =  ps_data_read_write(WRITE, PayLoadAddress, IRD_MOD_INFOFlAG_OFFSET, (void *)module_base_info, flash_type, LC_FALSE );

                if( ret)
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) update orig partition failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
                else
                {
                    UC_SPI_MODULE_DEBUG ("%s() in line(%d) update orig partition success!\n", __FUNCTION__, __LINE__);
                    
                    /* update bak partition */
                    ret =  ps_data_read_write(WRITE, PayLoaderAddress_bak, IRD_MOD_INFOFlAG_OFFSET, (void *)module_base_info, flash_type, LC_FALSE );
                    if( ret)
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) update bak partition failed!\n", __FUNCTION__, __LINE__);
                        result = LC_FAILURE;
                    }
                    else
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) update bak partition success!\n", __FUNCTION__, __LINE__);
                    }
                }
            }
        }

    }
    
    return result;
}

/**
 * update Irdeto internal moduel info header, which is stored in module_header_app partition
 *      note:no need to backup HL module info header
 */
static lc_result UpdateHLModuleInfoHeader(void)
{ 
	lc_result result = LC_SUCCESS;
    lc_uchar *tmp = LC_NULL;
    lc_sint32 ret = -1;
	lc_uint32 PayLoadAddress = 0;
    lc_uchar  flash_type = 0xff;
    lc_uint32 PayLoaderAddress_bak = 0;
    lc_uint32 prtLen = 0;
    lc_uchar  flash_type_bak = 0xff;
    lc_uint32 prtLen_bak = 0;
	
    tmp = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(NOR_ONE_BLOCK_SIZE);
    if(!tmp)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) malloc failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }
	
    LoaderCoreSPI_Stdlib_memset (tmp, 0xff, NOR_ONE_BLOCK_SIZE);
        
    LoaderCoreSPI_Stdlib_memcpy(tmp, (lc_uchar *)g_lc_module_list, IRD_MOD_HEADER_OFFSET + MAX_HL_MODULE_NUM*EACH_MOD_HADER_RAW_LEN);
   
    result = LC_GetPayloadInfoFromMouldID(MODULE_DRV_ID_HEADIFO, &PayLoadAddress, &PayLoaderAddress_bak, &flash_type, &prtLen, &flash_type_bak,&prtLen_bak);

    if( LC_SUCCESS ==  result)
    {
	    ret =  ps_data_read_write(WRITE,PayLoadAddress,IRD_MOD_HEADER_OFFSET + MAX_HL_MODULE_NUM*EACH_MOD_HADER_RAW_LEN, tmp, 0, LC_FALSE );
	    if(ret)
	    {
	        UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write failed!\n", __FUNCTION__, __LINE__);
	        UC_SPI_MODULE_DEBUG("%s() in line(%d)update CSTM Module header info failed\n", __FUNCTION__, __LINE__);
	        result = LC_FAILURE;
	    }
	    else
	    {
	        UC_SPI_MODULE_DEBUG("%s() in line(%d)update CSTM Module header info successed\n", __FUNCTION__, __LINE__);
	    }
    }
	else
	{
	  result = LC_FAILURE;
	}

EXIT:
    if( LC_NULL != tmp)
    {
        LoaderCoreSPI_Memory_Free((void*)tmp);
    }
    return result;
    
}

static lc_result get_sha_value(void *buffer,unsigned long len,void* hash_value)
{
    
    lc_result lc_ret = LC_SUCCESS;
    lc_sint32 ret = -1;
    lc_uchar * align_addr = LC_NULL;
    
    if((LC_NULL == buffer) || (LC_NULL == hash_value) || (0 == len))
    {
        UC_SPI_MODULE_DEBUG("%s() in Line(%d) input parametor invalid\n",__FUNCTION__,__LINE__);
        lc_ret = LC_FAILURE;
        return lc_ret;
    }

    /*
      * check buffer is 4 bytes align?
      */
#ifdef LC_SHA_ALIGN
    if((lc_uint32)buffer & (LC_HW_SHA_ALIGN_BYTES - 1))
    {
        align_addr = (lc_uchar*)LoaderCoreSPI_Memory_AlignedMalloc(len, LC_HW_SHA_ALIGN_BYTES);
        if(LC_NULL == align_addr)
        {                
            UC_SPI_MODULE_DEBUG("%s() in line(%d) LoaderCoreSPI_Memory_AlignedMalloc failed!!!\n", __FUNCTION__, __LINE__);
            lc_ret = LC_FAILURE;
            goto EXIT;
        }
        LoaderCoreSPI_Stdlib_memcpy(align_addr, buffer, len);
       
        ret = aui_dsc_sha_digest(AUI_SHA_SRC_FROM_DRAM, align_addr, len, AUI_SHA_256, (lc_uchar*)hash_value);
        
    }
    else
#endif
    {
        ret = aui_dsc_sha_digest(AUI_SHA_SRC_FROM_DRAM, buffer, len, AUI_SHA_256, (lc_uchar*)hash_value);
    }

    if (AUI_RTN_SUCCESS != ret)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) aui_dsc_sha_digest failed!!!\n", __FUNCTION__, __LINE__);
        lc_ret = LC_FAILURE;
        goto EXIT;
    }

EXIT:   
    if(LC_NULL != align_addr)
    {
        LoaderCoreSPI_Memory_AlignedFree(align_addr);
        align_addr = LC_NULL;
    }
    return lc_ret;

}

void LC_InitModuleBaseInfo(lc_module_base_info *module_base_info)
{
    LoaderCoreSPI_Stdlib_memset((void *)module_base_info, 0, sizeof(lc_module_base_info));
    module_base_info->magic_num = IRD_MOD_MAGIC_NUM;
    return ;
}

static lc_result LoaderCoreSPI_Module_WriteIrdInternalModule(lc_uint16 moduleId, lc_buffer_st *pHeader, lc_buffer_st *pPayload, 
                                                                        lc_uint32 flash_type, lc_uint32 modulePrtAddr, lc_uint32 modulePrtAddrBak)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 orig_addr;
    lc_uint32 bak_addr;
    lc_module_base_info module_base_info;
    lc_uchar hash[32] = {0};
    lc_uint32 ret = -1;
    lc_uint32 ret_ck = -1;
    lc_uchar *tmp_addr = LC_NULL;
    lc_uint32 g_module_start_addr = 0;

    lc_uint32 uk_flash_aadr = 0;   
	lc_uint32 bak_aadr = 0; 
    lc_uint32 prt_len = 0;
    lc_uint32 bak_module_len = 0;
    lc_uint32 crc32 = 0;
	lc_uint32 data_len = 0;
    lc_uint32 chunk_length = 0;
    if(MIN_MODULE_ID_APP <= moduleId || LC_NULL == pHeader 
        || LC_NULL == pPayload )
    {
        UC_SPI_MODULE_DEBUG("%s %d:input paramter invaild\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }

    /* LOADER_CORE module is readonly */
    if(MODULE_DRV_ID_LOADER_CORE == moduleId)
    {
        UC_SPI_MODULE_DEBUG("%s %d:LAODER_CORE module can not write!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }
    
    if(LC_SUCCESS == result)
    {
        switch(moduleId)
        {
            case MODULE_DRV_ID_BBCB:
     		{
                g_module_start_addr = (lc_uint32)g_lc_module_bbcb;
                break;
    		}   
            case MODULE_DRV_ID_UK:
    		{
                g_module_start_addr = (lc_uint32)g_lc_module_uk;
                break;
    		}
            case MODULE_DRV_ID_LOADER_PT:
    		{
                g_module_start_addr = (lc_uint32)g_lc_module_loaderPt;
                break;

    		}
            case MODULE_DRV_ID_VARIANT:
    		{
                g_module_start_addr = (lc_uint32 )g_lc_module_variant;
                break;
    		} 
            default:
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) unsupport this module", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
                break;
            } 
        }
    }


    if(LC_SUCCESS == result)
    {
        /**
          * BBCB don't need module header, need special process
          */
        if( MODULE_DRV_ID_BBCB == moduleId )
        {
            /* write payload to the flash */
            ret = ps_data_read_write(WRITE, modulePrtAddr,pPayload->length, pPayload->bytes, flash_type, LC_FALSE );
            if(ret)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) update BBCB to flash failed\n", __FUNCTION__, __LINE__);
                result = LC_ERROR_MODULE_ACCESS_ERROR;       
            }
            else
            {
                /* update to the mem buf */
                LoaderCoreSPI_Stdlib_memcpy((void *)g_module_start_addr,(void *)pPayload->bytes, pPayload->length);
            }
        }
        else
        {   
            /**
               * for UK VARIANT or LoaderPt module, those module need to backup
               */

			lc_get_offset_from_NVRAM(moduleId,&uk_flash_aadr, &bak_aadr, &prt_len,&bak_module_len);
            /* init the module base info */
            LC_InitModuleBaseInfo(&module_base_info);
            module_base_info.module_count = 1;
            module_base_info.module_id[0] = moduleId;
            module_base_info.is_exist[0] = LC_MODULE_EXIT;

            tmp_addr = (lc_uchar*)LoaderCoreSPI_Memory_Malloc(prt_len);
			UC_SPI_MODULE_DEBUG("%s() in line(%d) prt_len = 0x%x,tmp_addr = 0x%x!\n", __FUNCTION__, __LINE__,prt_len,tmp_addr);
			
            if(LC_NULL == tmp_addr)
            {
                UC_SPI_MODULE_DEBUG("%s %d:malloc failed!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }
            LoaderCoreSPI_Stdlib_memset(tmp_addr , 0xff , prt_len);

			UC_SPI_MODULE_DEBUG("%s() in line(%d) Header->length = 0x%x,Payload->length = 0x%x!\n", __FUNCTION__, __LINE__,pHeader->length,pPayload->length);
            if(LC_SUCCESS == result)
            {
                /* combine module base info, module header and module payload */
                LoaderCoreSPI_Stdlib_memcpy((void *)tmp_addr, (void *)&module_base_info, sizeof(lc_module_base_info));
                LoaderCoreSPI_Stdlib_memcpy((lc_uchar *)tmp_addr + IRD_MOD_HEADER_OFFSET, (lc_uchar *)pHeader->bytes, pHeader->length);
                LoaderCoreSPI_Stdlib_memcpy((lc_uchar *)tmp_addr + IRD_MOD_HEADER_OFFSET+pHeader->length, (lc_uchar *)pPayload->bytes, pPayload->length);
 
                data_len = IRD_MOD_HEADER_OFFSET + pHeader->length + pPayload->length;
                /* calc the hash value */
                result = get_sha_value(tmp_addr,prt_len - HASH_LEN,hash);     //
              
                if(LC_SUCCESS == result)
                {
                    /* copy hash value to the end of module parition */
                    LoaderCoreSPI_Stdlib_memcpy((void *)tmp_addr + prt_len - HASH_LEN, hash, HASH_LEN);
                  

                    /* update the orig parition */
                    //ret = ps_data_read_write(WRITE, modulePrtAddr,data_len+HASH_LEN, tmp_addr, 0, LC_FALSE );
                    ret = ps_data_read_write(WRITE, modulePrtAddr,prt_len, tmp_addr, 0, LC_FALSE );

				    chunk_length = data_len;
			        data2cklenth(&chunk_length);
					
					ret_ck = ps_data_read_write(WRITE, modulePrtAddr - CHUNK_HEADER_SIZE + CHUNK_LENGTH,4, &chunk_length, 0, LC_FALSE );   
                    if(ret || ret_ck)
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) update orig parition failed\n", __FUNCTION__, __LINE__);
                        result = LC_ERROR_MODULE_ACCESS_ERROR;       
                    }
                    if(LC_SUCCESS == result)
                    {
                        if(g_module_start_addr)
                        {
                            /* update module info to mem buffer */
                            LoaderCoreSPI_Stdlib_memcpy(g_module_start_addr, tmp_addr, prt_len);
                        }
                        else
                        {
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) g_module_start_addr failed\n", __FUNCTION__, __LINE__);
                            result = LC_FAILURE;
                        }
                    }
                    
                    if(LC_SUCCESS == result)
                    {
                        /* update the bak parition */
						UC_SPI_MODULE_DEBUG("%s() in line(%d) modulePrtAddrBak = 0x%x,tmp_addr = 0x%x!\n", __FUNCTION__, __LINE__,modulePrtAddrBak,tmp_addr);
                        //ret = ps_data_read_write(WRITE, modulePrtAddrBak,data_len+HASH_LEN, tmp_addr, flash_type, LC_FALSE );
                        ret = ps_data_read_write(WRITE, modulePrtAddrBak,prt_len, tmp_addr, flash_type, LC_FALSE );
                        chunk_length = data_len;
			            data2cklenth(&chunk_length);
						ret_ck = ps_data_read_write(WRITE, modulePrtAddrBak - CHUNK_HEADER_SIZE + CHUNK_LENGTH,4, &chunk_length, 0, LC_FALSE );   
                        if(ret || ret_ck)
                        {
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) update bak partition failed\n", __FUNCTION__, __LINE__);
                            result = LC_ERROR_MODULE_ACCESS_ERROR;     
                        }
                    }
                }
            }
        }
    }

    if(tmp_addr)
    {
        LoaderCoreSPI_Memory_Free(tmp_addr);
    }
    
    if(LC_SUCCESS == result )
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) update IrdInternalModule #%d success\n", __FUNCTION__, __LINE__, moduleId);
    }
    else
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) update IrdInternalModule #%d failed\n", __FUNCTION__, __LINE__, moduleId);
    }
    
    return result;
}

static lc_result LC_CheckModuleHeader(lc_module_base_info *module_base_info, lc_uint32 count)
{
    lc_result result = LC_SUCCESS;

    if(LC_NULL == module_base_info)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) input paramter invaild!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }

    if(LC_SUCCESS == result)
    {
        /* check the magic num */
        if(IRD_MOD_MAGIC_NUM != module_base_info->magic_num)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module base info magic number invaild!\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }

        if(LC_SUCCESS == result)
        {
            /* check other unique info */
        }
    }

    return result;
}

static lc_uint16 get_index_in_HL_module_list(lc_uint16 moduleId)
{
    lc_result result = LC_SUCCESS;
    
    lc_uint16 i =0xff;

    lc_module_base_info *module_base_info = LC_NULL;

    result = lc_module_list_init();
    
    if(LC_SUCCESS != result || LC_NULL == g_lc_module_list )
    {        
        UC_SPI_MODULE_DEBUG("%s() in line(%d) module_list is NULL\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }

    if(LC_SUCCESS == result)
    {
        module_base_info = g_lc_module_list;
        
        result = LC_CheckModuleHeader(module_base_info, MAX_HL_MODULE_NUM);

        if(LC_SUCCESS == result)
        {
            /* find module index */
            for(i=0;i< MAX_HL_MODULE_NUM; i++)
            {
                if((LC_MODULE_EXIT == module_base_info->is_exist[i]) &&  (moduleId == module_base_info->module_id[i]))
                {
                    return i;
                }
            }
        }
    }

    return i;
    
}

/**
 * return the module index in the module list
 */
static lc_uint16 LC_AddHLModuleInModuleList(lc_uint16 moduleId)
{
    lc_uint16 lc_ret =0xffff;
    lc_uint16 i = 0xff;

    i = get_index_in_HL_module_list(moduleId);
    if(i < MAX_HL_MODULE_NUM)
    {
        return i;
    }

    if(LC_NULL == g_lc_module_list)
    {
        UC_SPI_MODULE_DEBUG("module_list is NULL\n");
        return lc_ret;
    }

    /* the initial module header image is all 0xff */
    if( -1 == g_lc_module_list->module_count)
    {
        g_lc_module_list->module_count = 0;
    }

    for(i=0; i< MAX_HL_MODULE_NUM; i++)
    {
        if(LC_MODULE_EXIT != g_lc_module_list->is_exist[i])
        {
            g_lc_module_list->magic_num = IRD_MOD_MAGIC_NUM;
            g_lc_module_list->module_id[i] = moduleId;
            g_lc_module_list->is_exist[i] = LC_MODULE_EXIT;
            g_lc_module_list->module_count++;
			
            return i;
        }
    }
    return lc_ret;
    
}

static lc_result LoaderCoreSPI_Module_WriteHLModule(lc_uint16 moduleId, lc_buffer_st *pHeader, lc_buffer_st *pPayload, 
                                                             lc_uint32 header_flash_type, lc_uint32 modulePrtAddr, lc_uint32 payload_flash_type,
                                                             lc_uint32 modulePrtAddrBak, lc_uint32 payload_flash_type_bak, lc_uint32 prtLen)
{
    lc_result result = LC_SUCCESS;
    lc_uint16 index = 0xff;
    lc_uint32 module_header_addr = 0;
    lc_uint32 ret = -1;
	lc_uint32 ret_ck = -1;
	lc_uint32 ret_ck1 = -1;
    lc_uint32 payload_read_addr = 0;
    lc_uint32 payload_read_addr_bak = 0;
    lc_uint32 dataLen = 0;
    lc_uchar flash_type=0xff;
    lc_uint32 prtLen_bak = 0;
    lc_uchar flash_type_bak =0xff;
	lc_uint32 chunk_length = 0;
	lc_uint32 calCrc = 0;
	
    if(MIN_MODULE_ID_APP > moduleId || LC_NULL == pHeader || LC_NULL == pPayload )
    {
        UC_SPI_MODULE_DEBUG("%s %d:input paramter invaild\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }
    if(LC_NULL == g_lc_module_list)
    {
        UC_SPI_MODULE_DEBUG("%s %d:module_list is NULL\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }

    if(LC_SUCCESS == result)
    {
        /* if module is not exist, add it to the module list */
        if(LC_FALSE == checkModuleExist(moduleId, &index))
        {
            /* update module base info */
            index = LC_AddHLModuleInModuleList(moduleId);
            if(index >= MAX_HL_MODULE_NUM)
            {
                UC_SPI_MODULE_DEBUG("%s %d:the module index is invaild\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
            }
        }
        if(LC_SUCCESS == result)
        {
            module_header_addr = (lc_uint32)g_lc_module_list + IRD_MOD_INFOFlAG_OFFSET + index*EACH_MOD_HADER_RAW_LEN;
            /* update module header */
            LoaderCoreSPI_Stdlib_memcpy((void *)module_header_addr, pHeader->bytes, pHeader->length);

            /* 1.update HL module payload to flash */
            ret = ps_data_read_write(WRITE, modulePrtAddr, pPayload->length,pPayload->bytes, 0, LC_FALSE);
            #if 0
            chunk_length = pPayload->length;
			data2cklenth(&chunk_length);
			ret_ck = ps_data_read_write(WRITE, modulePrtAddr - CHUNK_HEADER_SIZE + CHUNK_LENGTH,4, &chunk_length, 0, LC_FALSE );     

		    calCrc = CRC_Code32(pPayload->bytes, pPayload->length);
			UC_SPI_MODULE_DEBUG("%s %d:the module id = 0x%x,payload crc = 0x%x\n", __FUNCTION__, __LINE__,moduleId,calCrc);
			data2cklenth(&calCrc);
			ret_ck1 = ps_data_read_write(WRITE, modulePrtAddr - CHUNK_HEADER_SIZE + CHUNK_CRC,4, &calCrc, 0, LC_FALSE );     
            if(ret || ret_ck || ret_ck1)
			#endif
			if(ret)
            {
                UC_SPI_MODULE_DEBUG("%s %d:update HL module payload failed\n", __FUNCTION__, __LINE__);
                result = LC_ERROR_MODULE_ACCESS_ERROR;
            }
            else
            {
                /* 2.update HL module base info and module header to flash */
				  
                result = LC_GetPayloadInfoFromMouldID(MODULE_DRV_ID_HEADIFO, &payload_read_addr, &payload_read_addr_bak, &flash_type, &dataLen, 
                                                            &flash_type_bak, &prtLen_bak);

				if( LC_SUCCESS ==  result)
				{
	                ret = ps_data_read_write(WRITE, payload_read_addr, dataLen,g_lc_module_list,0, LC_FALSE);
                    #if 0
					chunk_length = dataLen;
				    data2cklenth(&chunk_length);
					ret_ck = ps_data_read_write(WRITE, payload_read_addr - CHUNK_HEADER_SIZE + CHUNK_LENGTH,4, &chunk_length, 0, LC_FALSE );
					if(ret || ret_ck)
					#endif
	                if(ret)
	                {
	                    UC_SPI_MODULE_DEBUG("%s %d:update HL module header failed!\n", __FUNCTION__, __LINE__);
	                    result = LC_ERROR_MODULE_ACCESS_ERROR;
	                }
	                else
	                {
	                    UC_SPI_MODULE_DEBUG("%s %d:update HL module header success!\n", __FUNCTION__, __LINE__);
	                }
				}
				else
				{
				   result = LC_FAILURE;
				}
				
            }
        }
    }

    if(LC_SUCCESS == result )
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) update HL module #%d success\n", __FUNCTION__, __LINE__, moduleId);
    }
    else
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) update HL module #%d failed\n", __FUNCTION__, __LINE__, moduleId);
    }

    return result;
}


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
lc_result LoaderCoreSPI_Module_WriteModule(lc_uint16 moduleId, lc_buffer_st *pModule)
{
    lc_result result = LC_SUCCESS;
    lc_buffer_st header={0};
    lc_buffer_st payload={0};
    lc_uint32 BitPos = 0;
    lc_module_info_header header_info={0};
    lc_uint32 payload_addr=0;
    lc_uint32 payload_addr_bak = 0;
    lc_uint32 prtLen = 0;
    lc_uchar *module_virtual_mem_start = LC_NULL;
    lc_uchar *module_virtual_addrr = LC_NULL;
    lc_bool  is_need_header = LC_TRUE;
    lc_uint32 prtLen_bak = 0;
    lc_uchar  flash_type_bak=0xff;
    lc_uchar  flash_type;
    lc_sint32 ret = 0;

    lc_buffer_st mp_byte = {LC_NULL, 0};
    
    if((LC_NULL == pModule) || (MODULE_DRV_ID_LOADER_CORE == moduleId))
    {
        UC_SPI_MODULE_DEBUG("%s %d:Parametors invaild\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_NULL_PARAM;
    }

    if(LC_SUCCESS == result)
    {
        result = lc_module_list_init();
        if(LC_SUCCESS == result)
        {
            if(LC_NULL == g_lc_module_list)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) module_list is NULL!\n", __FUNCTION__, __LINE__);
                result = LC_ERROR_MODULE_NOT_FOUND;
            }
        }
    }

    if(LC_SUCCESS == result)
    {
        /* parse the module header */
        LoaderCoreSPI_Stdlib_memset(&header_info, 0, sizeof (header_info));
        result = MessageParser_ParseModuleInfoHeader(LC_FALSE, pModule, &BitPos, &header_info);
        if (LC_SUCCESS == result)
        {
            header.bytes = pModule->bytes;
            header.length = header_info.header_length;
            /*payload*/
            payload.bytes = &pModule->bytes[header_info.header_length];
    		payload.length = header_info.module_size;

            /*
	              * 1).for now, we get the chunk addr.
	              * 2).if user want set header_info.addressable to an absolute address, user need add 
	              *   behavior of locating the specific addr of each module in here
                    */
#if 1
            if (1 == header_info.addressable)
            {
                /* unimplemented:     */
				payload_addr = header_info.start_address;
                UC_SPI_MODULE_DEBUG("%s() in line(%d)->Get ADDR from TS: header_info.start_address = 0x%x!\n", __FUNCTION__, __LINE__,payload_addr);
				UC_SPI_MODULE_DEBUG("%s() in line(%d)->Get CHUNK ID:0x%2x%2x%2x%2x!\n", __FUNCTION__, __LINE__, payload.bytes[0],payload.bytes[1],payload.bytes[2],payload.bytes[3]);
				
            }
            else
#endif
            {
                result = LC_GetPayloadInfoFromMouldID(moduleId, &payload_addr, &payload_addr_bak, &flash_type, &prtLen,&flash_type_bak, &prtLen_bak);
            }

            if(LC_SUCCESS == result)
            {
                if(moduleId < MIN_MODULE_ID_APP)
                {
                    /* write irdeto internal module */
                    result = LoaderCoreSPI_Module_WriteIrdInternalModule(moduleId, &header, &payload,0,payload_addr, payload_addr_bak);
                    if(LC_SUCCESS != result)
                    {
                        result = LC_ERROR_MODULE_ACCESS_ERROR;
                    }
                }
                else
                {
                    /* write HL module */
                    result = LoaderCoreSPI_Module_WriteHLModule(moduleId, &header, &payload,0,payload_addr, flash_type,
                                                                payload_addr_bak, flash_type_bak, prtLen_bak);
                    if(LC_SUCCESS != result)
                    {
                        result = LC_ERROR_MODULE_ACCESS_ERROR;
                    }
                }
            }
        }
    }
		
	return result;
}

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
lc_result LoaderCoreSPI_Module_Delete(lc_uint16 moduleId)
{
    lc_result result = LC_SUCCESS;
    lc_uint32  index = 0xff;

    if((MODULE_DRV_ID_BBCB == moduleId) || (MODULE_DRV_ID_LOADER_CORE == moduleId))
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) BBCB and Loader_Core module can not be deleted!\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_MODULE_ACCESS_ERROR;
    }

    if(LC_SUCCESS == result)
    {
        result = lc_module_list_init();
        if(LC_SUCCESS == result)
        {
            if(LC_NULL == g_lc_module_list)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) module_list is NULL!\n", __FUNCTION__, __LINE__);
                result = LC_ERROR_MODULE_NOT_FOUND;
            }

            if(LC_SUCCESS == result)
            {
                if(LC_FALSE == checkModuleExist(moduleId, &index))
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist, return true!\n", __FUNCTION__, __LINE__);
                    return LC_SUCCESS;
                }
            }
        }
    }
    
    if(LC_SUCCESS == result)
    {
        /* delete a ird internal module */
        if( MIN_MODULE_ID_APP > moduleId )
        {
            result = DelModuleInModuleList(moduleId, index);
            if( LC_SUCCESS == result)
            {
                result = DelModuleHeader(moduleId);
                if(LC_SUCCESS == result)
                {
                    result = UpdateIrdetoModuleInfoHeader(moduleId);
                }
            }
        }
        else
        {
            /* delete a HL module */
            index = get_index_in_HL_module_list(moduleId);
            if(index < MAX_HL_MODULE_NUM)
            {
                if(LC_SUCCESS == result)
                {
                    /* erase module payload */
                    result = LoaderCoreSPI_Module_EarseModulePayload(moduleId);

                    if(LC_SUCCESS == result)
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) erase module #%d success!\n", __FUNCTION__, __LINE__, moduleId);
                    }
                    else
                    {
                        UC_SPI_MODULE_DEBUG("%s() in line(%d) erase module #%d failed!\n", __FUNCTION__, __LINE__, moduleId);
                        result = LC_ERROR_MODULE_ACCESS_ERROR;
                    }

                    /* del moduleId in the module list */
                    if(LC_SUCCESS == result)
                    {
                        result = DelModuleInModuleList(moduleId, index);
                        if( LC_SUCCESS == result)
                        {
                            result = DelModuleHeader(moduleId);
                            if(LC_SUCCESS == result)
                            {
                                result = UpdateHLModuleInfoHeader();
                            }
                        }
                    }
                }
            }
            else
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) index is out of range!\n", __FUNCTION__, __LINE__);
                result = LC_SUCCESS;
            }
        }
    }
    
    return result;
}

/**
 *  this api is for DVT_APP, modify the last bit of HL module
 *  
 */
lc_result LoaderCoreSPI_Module_WriteLastBitToModule(lc_uint16 moduleId)
{
    lc_result result = LC_SUCCESS;
    lc_uchar *mem_start = LC_NULL;
    lc_module_info_header header_info={0};
    lc_buffer_st header={0};
    lc_uint32 BitPos = 0;
    lc_uint32 payload_read_addr=0;
    lc_uchar flash_type=0;
    lc_buffer_st pModulePayload = {0};
    lc_uint32 i=0;
    lc_module_type module_type = INVAILD_MODULE;
    lc_uint32 payloadAddr = 0;
    lc_uint32 payloadAddr_bak = 0;
    lc_uint32 prtLen =0 ;
    lc_uchar mtd_index = 0xff;
    lc_uint32 index = 0xff;
    lc_uint32 prtLen_bak = 0;
    lc_uchar flash_type_bak = 0xff;

    lc_sint32 ret = -1;

    module_type = CheckModuleId(moduleId);
    
    if( CSTM_MODULE != module_type )
    {
        result = LC_ERROR_NULL_PARAM;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) can't modify moudle #%d!\n", __FUNCTION__, __LINE__, moduleId);
    }

    if(LC_SUCCESS == result )
    {
        result = lc_module_list_init();
        if(LC_SUCCESS != result || LC_NULL == g_lc_module_list)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d)module list is NULL!\n", __FUNCTION__, __LINE__, moduleId);
            result = LC_ERROR_MODULE_NOT_FOUND;
        }
    }

    if(LC_SUCCESS == result)
    {
        if( LC_FALSE == checkModuleExist(moduleId, &index))
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist, can not write payload!\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }

        if(LC_SUCCESS == result)
        {
            header.bytes = (lc_uchar *)((lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index * EACH_MOD_HADER_RAW_LEN);
            header.length = EACH_MOD_HADER_RAW_LEN;
            
            /* parse module header info */
            LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
            result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
            if (LC_SUCCESS == result)
            {
                pModulePayload.length = header_info.module_size;
                pModulePayload.bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(pModulePayload.length);
                if(LC_NULL == pModulePayload.bytes)
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) LoaderCoreSPI_Memory_Malloc failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
                else
                {
                    LoaderCoreSPI_Stdlib_memset (pModulePayload.bytes, 0, pModulePayload.length);
                    result = LC_GetPayloadInfoFromMouldID(moduleId, &payloadAddr, &payloadAddr_bak, &flash_type, &prtLen, &flash_type_bak, &prtLen_bak);

                    if(LC_SUCCESS == result)
                    {
                        /* read module payload from flash */
                        ret = ps_data_read_write(READ, payloadAddr, pModulePayload.length, pModulePayload.bytes, 0, LC_FALSE);
                        if (ret)
                        {
                        	result = LC_ERROR_MODULE_ACCESS_ERROR;
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) read module payload failed!\n", __FUNCTION__, __LINE__);
                        }
                        else
                        {
                            /* modify the last bit of module payload */
                            if((MODULE_DRV_ID_MAIN == moduleId) || (MODULE_DRV_ID_SEE == moduleId))
                            {
                              pModulePayload.bytes[pModulePayload.length-CHUNK_HEADER_SIZE-1] ^= 0x1;
                            }
                            else
                            {
                              pModulePayload.bytes[pModulePayload.length-1] ^= 0x1;
                            }

                            /* update module payload to the flash */
                            ret = ps_data_read_write(WRITE, payloadAddr, pModulePayload.length, pModulePayload.bytes, 0, LC_FALSE);
                            if(ret)
                            {
                            	result = LC_ERROR_MODULE_ACCESS_ERROR;
                                UC_SPI_MODULE_DEBUG("%s() in line(%d) update module payload failed!\n", __FUNCTION__, __LINE__);
                            }
                        }
                    }
                }
            }
                    
        }
    }
    
    return result;

}

lc_uint32 calcPatternCount(void *startAddr, lc_uint32 count)
{
    #define PATTERN_LEN 256
    lc_char *addr = (lc_char *)startAddr;
    lc_uint32 i = 0, j = 0, ptn_cnt = 0;
    lc_char pattern[PATTERN_LEN];

    for (i = 0; i < PATTERN_LEN; i++)
        pattern[i] = (i % PATTERN_LEN);
    
    for(i = 0; i < count; i++)
    {
        for (j = 0; j < PATTERN_LEN; j++,i++) {
            if (pattern[j] != addr[i]) {
                break;
            }
            
        }
        if (j == PATTERN_LEN) {
            //printf("got pattern: %d, i: %d\n", ptn_cnt, i);
            ptn_cnt += 1;
            i -= 1;
        }
    }
    return ptn_cnt;
}

/**
 * this api is just for earse HL module payload, if module is not exist, return true
 */
lc_result LoaderCoreSPI_Module_EarseModulePayload(lc_uint16 moduleId)
{
    lc_result result = LC_SUCCESS;
    lc_uchar flash_type=0;

    lc_module_type module_type = INVAILD_MODULE;
    lc_uint32 payloadAddr = 0;
    lc_uint32 payloadAddr_bak = 0;
    lc_uint32 prtLen = 0;
    lc_uint32 fakeaddr = 0;
    lc_uchar flash_type_bak = 0xff;
    lc_uint32 prtLen_bak = 0;

    lc_uint32 index = 0xff;
    lc_sint32 ret = -1;

    module_type = CheckModuleId(moduleId);
    
    if( CSTM_MODULE != module_type )
    {
        result = LC_ERROR_NULL_PARAM;
        UC_SPI_MODULE_DEBUG("%s() in line(%d)Internel module can not be earse", __FUNCTION__, __LINE__);
    }

    UC_SPI_MODULE_DEBUG("%s() in line(%d) want to earse moduleId:%d\n", __FUNCTION__, __LINE__, moduleId);

    if((MODULE_DRV_ID_BBCB == moduleId) || (MODULE_DRV_ID_LOADER_CORE == moduleId))
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) BBCB and Loader_Core module can not be deleted!\n", __FUNCTION__, __LINE__);
        result = LC_ERROR_MODULE_ACCESS_ERROR;
    }

    if(LC_SUCCESS == result)
    {
        result = lc_module_list_init();
        if(LC_SUCCESS == result)
        {
            if(LC_NULL == g_lc_module_list)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) module_list is NULL!\n", __FUNCTION__, __LINE__);
                result = LC_ERROR_MODULE_NOT_FOUND;
            }

            if(LC_SUCCESS == result)
            {
                if(LC_FALSE == checkModuleExist(moduleId, &index))
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist, return true!\n", __FUNCTION__, __LINE__);
                    return LC_SUCCESS;
                }
            }
        }
    }
	
    if(LC_SUCCESS == result)
    {
        result = LC_GetPayloadInfoFromMouldID(moduleId, &payloadAddr, &payloadAddr_bak, &flash_type, &prtLen, &flash_type_bak, &prtLen_bak);
        if( LC_SUCCESS == result)
        {               
            /* 
              * NOTE:
              *     before update module, we just erase HL module orig payload partition,DO NOT touch HL module backup partition
              */
            ret = ps_data_read_write(WRITE, payloadAddr, prtLen, &fakeaddr, flash_type, LC_FALSE);
            if(ret)
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) erase module #%d orig payload failed!\n", __FUNCTION__, __LINE__, moduleId);
                result = LC_ERROR_MODULE_ACCESS_ERROR;
            }
            else
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) erase module #%d orig payload success!\n", __FUNCTION__, __LINE__, moduleId);
            }
        }
    }
	
    return result;
}

/**
 *  this api is for DVT_APP, get count patterns in module
 *  
 */
lc_uint32 LoaderCoreSPI_Module_GetModulePatternCnt(lc_uint16 moduleId)
{
    lc_module_info_header header_info={0};
    lc_buffer_st header={0};
    lc_uint32 BitPos = 0;
    lc_result result = LC_SUCCESS;

    /*
     * get module header
     */
    result = LoaderCoreSPI_Module_ReadModuleHeader(moduleId, &header);
    if(LC_SUCCESS != result)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) get module header failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }
    if(LC_SUCCESS == result)
    {
        /* parse out the module header info */
        LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
        result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
        if (LC_SUCCESS != result)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) MessageParser_ParseModuleInfoHeader parse module #%d header failed!\n", __FUNCTION__, __LINE__, moduleId);
            result = LC_FAILURE;
        }
    }

    printf("%s  boot_check: %d\n", __func__, header_info.boot_check);
    /* if the module is bootcheck */
    if( 1 == header_info.boot_check ){
        return 0;
    }
    /*the non-check module */

    lc_module_type module_type = INVAILD_MODULE;    
    lc_uint32 payload_size = 0, pattern_cnt = 0;
    lc_uint32 payloadAddr = 0;
    lc_uint32 payloadAddr_bak = 0;
    lc_uchar mtd_index = 0xff;
    lc_sint32 ret = -1;
    lc_uchar *buf = LC_NULL;
    lc_uchar flash_type = 0;
    lc_uint32 prtLen = 0;
    lc_uint32 prtLen_bak = 0;
    lc_uchar flash_type_bak = 0xff;
    
    result = LC_GetPayloadInfoFromMouldID(moduleId, &payloadAddr, &payloadAddr_bak, &flash_type, &prtLen, &flash_type_bak, &prtLen_bak);
    if(LC_SUCCESS != result) {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) LC_GetPayloadInfoFromMouldID failed!\n", __FUNCTION__, __LINE__);
        return 0;
    }
    

    payload_size = LoaderCoreSPI_Module_ReadModulePayloadSize(moduleId);
    if (payload_size <= 0) {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) invalid payload_size!\n", __FUNCTION__, __LINE__);
        return 0;
    }        
    
    buf = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(payload_size);
    if (buf == LC_NULL) {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) LoaderCoreSPI_Memory_Malloc failed!\n", __FUNCTION__, __LINE__);
        return 0;
    }
    
    ret = ps_data_read_write(READ, payloadAddr, payload_size, buf, 0, LC_FALSE);
    if(ret) {
        result = LC_ERROR_MODULE_ACCESS_ERROR;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) update module payload failed!\n", __FUNCTION__, __LINE__);
        LoaderCoreSPI_Memory_Free(buf);
        return 0;
    }
    pattern_cnt = calcPatternCount(buf, payload_size);
    LoaderCoreSPI_Memory_Free(buf);
    printf("pattern_cnt: %d\n", pattern_cnt);
    /*while(offset < payload_size) {
        if (PATTERN_LEN > payload_size - offset)
            break; // the last is not a whole pattern
        printf("read offset: %d\n", offset);
        ret = ps_data_read_write(READ, mtd_index, payloadAddr + offset, PATTERN_LEN, module_data, LC_FALSE);
        if(ret) {
            result = LC_ERROR_MODULE_ACCESS_ERROR;
            UC_SPI_MODULE_DEBUG("%s() in line(%d) update module payload failed!\n", __FUNCTION__, __LINE__);
            return 0;
        }

        for (i = 0; i < PATTERN_LEN; i++) {
            if (module_data[i] != pattern[i])
                break;
        }
        printf(" i ==== %d\n", i);
        if (i == PATTERN_LEN) {
            printf("update pattern_cnt: %d\n", pattern_cnt);
            pattern_cnt += 1;
        }
        offset += (i + 1); 
    }*/

    return pattern_cnt;
}

/**
 *  this api is for DVT_APP, write pattern data to the HL module payload
 *  
 */
lc_result LoaderCoreSPI_Module_WritePattenToModule(lc_uint16 moduleId)
{
    lc_result result = LC_SUCCESS;
    lc_uchar *mem_start = LC_NULL;
    lc_module_info_header header_info={0};
    lc_buffer_st header={0};
    lc_uint32 BitPos = 0;
    lc_uint32 payload_read_addr=0;
    lc_uchar flash_type=0;
    lc_buffer_st pModulePayload = {0};
    lc_uint32 i=0;
    lc_module_type module_type = INVAILD_MODULE;
    lc_uint32 payloadAddr = 0;
    lc_uint32 payloadAddr_bak = 0;
    lc_uint32 prtLen =0;
    lc_uchar mtd_index = 0xff;
    lc_uint32 index = 0xff;
    lc_uint32 prtLen_bak = 0;
    lc_uchar flash_type_bak = 0xff;

    lc_sint32 ret = -1;

    module_type = CheckModuleId(moduleId);
    
    if( CSTM_MODULE != module_type )
    {
        result = LC_ERROR_NULL_PARAM;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) can't modify moudle #%d!\n", __FUNCTION__, __LINE__, moduleId);
    }

    if(LC_SUCCESS == result )
    {
        result = lc_module_list_init();
        if(LC_SUCCESS != result || LC_NULL == g_lc_module_list)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d)module list is NULL!\n", __FUNCTION__, __LINE__, moduleId);
            result = LC_ERROR_MODULE_NOT_FOUND;
        }
    }

    if(LC_SUCCESS == result)
    {
        if( LC_FALSE == checkModuleExist(moduleId, &index))
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist, can not write payload!\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }

        if(LC_SUCCESS == result)
        {
            header.bytes = (lc_uchar *)((lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index * EACH_MOD_HADER_RAW_LEN);
            header.length = EACH_MOD_HADER_RAW_LEN;
            
            /* parse module header info */
            LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
            result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
            if (LC_SUCCESS == result)
            {
                pModulePayload.length = header_info.module_size;
                pModulePayload.bytes = (lc_uchar *) LoaderCoreSPI_Memory_Malloc(pModulePayload.length);
                if(LC_NULL == pModulePayload.bytes)
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) LoaderCoreSPI_Memory_Malloc failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
                else
                {
                    for(i=0 ; i< pModulePayload.length; i++)
                    {
                		pModulePayload.bytes[i]=(i%256);
                    }
                    result = LC_GetPayloadInfoFromMouldID(moduleId, &payloadAddr, &payloadAddr_bak, &flash_type, &prtLen, &flash_type_bak, &prtLen_bak);
                    if(LC_SUCCESS == result)
                    {
                        ret = ps_data_read_write(WRITE,payloadAddr, pModulePayload.length, pModulePayload.bytes, 0, LC_FALSE);
                        if(ret)
                        {
                        	result = LC_ERROR_MODULE_ACCESS_ERROR;
                            UC_SPI_MODULE_DEBUG("%s() in line(%d) update module payload failed!\n", __FUNCTION__, __LINE__);
                        }
                    }
                }
            }
        }
    }

    return result;
}

/**
 *  this api is for DVT_APP, read HL module payload size
 *  
 */
lc_uint32 LoaderCoreSPI_Module_ReadModulePayloadSize(lc_uint16 moduleId)
{
    lc_module_info_header header_info={0};
    lc_buffer_st header={0};
    lc_uint32 BitPos = 0;
    
    lc_module_type module_type = INVAILD_MODULE;
    lc_result result = LC_SUCCESS;
    lc_uint32 index = 0xff;
    lc_uint32 payload_size = 0;

    module_type = CheckModuleId(moduleId);
    
    if( CSTM_MODULE != module_type )
    {
        result = LC_ERROR_NULL_PARAM;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) can't modify moudle #%d!\n", __FUNCTION__, __LINE__, moduleId);
    }

    if(LC_SUCCESS == result )
    {
        result = lc_module_list_init();
        if(LC_SUCCESS != result ||  LC_NULL == g_lc_module_list)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d)module list is NULL!\n", __FUNCTION__, __LINE__, moduleId);
            result = LC_ERROR_MODULE_NOT_FOUND;
        }
    }

    if(LC_SUCCESS == result)
    {
        if( LC_FALSE == checkModuleExist(moduleId, &index))
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist!\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }

        if(LC_SUCCESS == result)
        {
            header.bytes = (lc_uchar *)((lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index * EACH_MOD_HADER_RAW_LEN);
            header.length = EACH_MOD_HADER_RAW_LEN;
            
            /* parse module header info */
            LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
            result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
            if (LC_SUCCESS == result)
            {
                 payload_size =  header_info.module_size;
            }
        }
    }

    if(payload_size)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) read module payload size success!\n", __FUNCTION__, __LINE__);
    }
    else
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) read module payload size failed!\n", __FUNCTION__, __LINE__);
    }

    return payload_size;
}

/**
 *  this api is for DVT_APP, read HL module version
 *  
 */
lc_uint32 LoaderCoreSPI_Module_ReadModuleVersion(lc_uint16 moduleId)
{
    lc_module_info_header header_info={0};
    lc_buffer_st header={0};
    lc_uint32 BitPos = 0;
    
    lc_module_type module_type = INVAILD_MODULE;
    lc_result result = LC_SUCCESS;
    lc_uint32 index = 0xff;
    lc_uint16 module_version = -1;

    module_type = CheckModuleId(moduleId);
    
    if( CSTM_MODULE != module_type )
    {
        result = LC_ERROR_NULL_PARAM;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) can't modify moudle #%d!\n", __FUNCTION__, __LINE__, moduleId);
    }

    if(LC_SUCCESS == result )
    {
        result = lc_module_list_init();
        if(LC_SUCCESS != result || LC_NULL == g_lc_module_list)
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d)module list is NULL!\n", __FUNCTION__, __LINE__, moduleId);
            result = LC_ERROR_MODULE_NOT_FOUND;
        }
    }

    if(LC_SUCCESS == result)
    {
        if( LC_FALSE == checkModuleExist(moduleId, &index))
        {
            UC_SPI_MODULE_DEBUG("%s() in line(%d) module is not exist, can not write payload!\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }

        if(LC_SUCCESS == result)
        {
            header.bytes = (lc_uchar *)((lc_uint32)g_lc_module_list + IRD_MOD_HEADER_OFFSET + index * EACH_MOD_HADER_RAW_LEN);
            header.length = EACH_MOD_HADER_RAW_LEN;
            
            /* parse module header info */
            LoaderCoreSPI_Stdlib_memset (&header_info, 0, sizeof (header_info));
            result = MessageParser_ParseModuleInfoHeader(LC_FALSE, &header, &BitPos, &header_info);
            if (LC_SUCCESS == result)
            {
                 module_version =  header_info.module_version;
            }
        }
    }

    if(-1 == module_version)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) read module payload version failed!\n", __FUNCTION__, __LINE__);
    }
    else
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) read module payload version success!\n", __FUNCTION__, __LINE__);
    }

    return module_version;
    
}

static lc_result LoaderCoreSPI_Module_EraseOneModuleNVRAMPartition(lc_uint16 moduleId)
{
    lc_result result = LC_SUCCESS;
    
    lc_char* addr = LC_NULL;

    //lc_uint32 mtd_index = 0xff;
    lc_uint32 payloadAddr = 0;
    lc_uint32 payloadAddrBak = 0;
    lc_uchar flash_type=0xff;
    lc_uchar flash_type_bak=0xff;
    lc_uint32 prtLen = 0;
    lc_uint32 prtLen_bak = 0;

    if(moduleId != MODULE_DRV_ID_UK && moduleId != MODULE_DRV_ID_VARIANT && moduleId != MODULE_DRV_ID_LOADER_PT)
    {
        UC_SPI_MODULE_DEBUG ("%s() in line(%d) invaild parameter.\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }
    else
    {
        result = lc_module_list_init();
    }
    
   /* step 1. malloc 64kb size, memset to all 0xff */
    if(LC_SUCCESS == result)
    {
        addr = (lc_char*)LoaderCoreSPI_Memory_Malloc(NOR_ONE_BLOCK_SIZE);
        if(!addr)
        {
            UC_SPI_MODULE_DEBUG ("%s() in line(%d) LoaderCoreSPI_Memory_Malloc fail\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }

        if(LC_SUCCESS == result)
        {
            LoaderCoreSPI_Stdlib_memset (addr, 0xff, NOR_ONE_BLOCK_SIZE);
        }
    }
    
    /* step 2. erase NVRAM one module partition, and also backup parition */
    if(LC_SUCCESS == result)
    {
        //result = lc_utils_get_moduleInfo(moduleId, prtActive_getPayloadInfo,
        //                                LC_NULL,
        //                                &mtd_index, &payloadAddr, &payloadAddrBak,
        //                                0xff, LC_NULL, LC_NULL);
        result = LC_GetPayloadInfoFromMouldID(moduleId, &payloadAddr, &payloadAddrBak, &flash_type, &prtLen, 
                                                            &flash_type_bak, &prtLen_bak);
		
        if(moduleId == MODULE_DRV_ID_LOADER_PT)
        {
           payloadAddr += SHORT_MODULE_INFO_HEADER_SIZE + IRD_MOD_INFOFlAG_OFFSET;
		   payloadAddrBak += SHORT_MODULE_INFO_HEADER_SIZE + IRD_MOD_INFOFlAG_OFFSET;
           prtLen -= SHORT_MODULE_INFO_HEADER_SIZE + IRD_MOD_INFOFlAG_OFFSET;
		   prtLen_bak -= SHORT_MODULE_INFO_HEADER_SIZE + IRD_MOD_INFOFlAG_OFFSET;
        }

        if(LC_SUCCESS == result)
        {
            if( 0 != ps_data_read_write(WRITE, payloadAddr, prtLen, addr, 0, LC_FALSE))
        	{
                UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write failed!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
        	}
            if(LC_SUCCESS == result)
            {
                if( 0 != ps_data_read_write(WRITE, payloadAddrBak, prtLen_bak, addr, 0, LC_FALSE))
                {
                    UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write failed!\n", __FUNCTION__, __LINE__);
                    result = LC_FAILURE;
                }
            }
        }

    }

    return result;
}

static void reset_nvram_irdetoPt(void)
{
    LoaderCoreSPI_Stdlib_memset(g_lc_module_variant, 0xff, NOR_ONE_BLOCK_SIZE);
    LoaderCoreSPI_Stdlib_memset(g_lc_module_uk, 0xff, NOR_ONE_BLOCK_SIZE);
}

static void reset_nvram_loaderPt(void)
{
   // LoaderCoreSPI_Stdlib_memset(g_lc_module_loaderPt, 0xff, NOR_ONE_BLOCK_SIZE);
   LoaderCoreSPI_Stdlib_memset(g_lc_module_loaderPt +SHORT_MODULE_INFO_HEADER_SIZE + IRD_MOD_INFOFlAG_OFFSET, 0xff,\
   NOR_ONE_BLOCK_SIZE - SHORT_MODULE_INFO_HEADER_SIZE - IRD_MOD_INFOFlAG_OFFSET);
 
}

lc_result LoaderCoreSPI_Module_EraseIrdetoNVRAMPartition()
{
    lc_result result = LC_SUCCESS;

    /* step 1. erase UK partition */
    result = LoaderCoreSPI_Module_EraseOneModuleNVRAMPartition(MODULE_DRV_ID_UK);

    if(LC_SUCCESS == result)
    {
        libc_printf("LoaderCoreSPI_Module_EraseIrdetoNVRAMPartition, MODULE_DRV_ID_UK erase OK\n");
        /* step 2. erase variant partition */
        result = LoaderCoreSPI_Module_EraseOneModuleNVRAMPartition(MODULE_DRV_ID_VARIANT);
    }

    if(LC_SUCCESS == result)
    {
        libc_printf("LoaderCoreSPI_Module_EraseIrdetoNVRAMPartition, MODULE_DRV_ID_VARIANT erase OK\n");
        // reset data in ram
        reset_nvram_irdetoPt();
    }
    return result;
}

lc_result LoaderCoreSPI_Module_EraseLoaderNVRAMPartition()
{
    lc_result result = LC_SUCCESS;
    
    result = LoaderCoreSPI_Module_EraseOneModuleNVRAMPartition(MODULE_DRV_ID_LOADER_PT);
    if(LC_SUCCESS == result)
    {
        // reset data in ram
        reset_nvram_loaderPt();
    }
    return result;
}

lc_result LoaderCoreSPI_Module_EraseCANVRAMPartition()
{
    lc_result result = LC_SUCCESS;
  
    lc_uchar* addr = LC_NULL;
    PARTITION_INFO part_info;
    lc_sint32 err = -1;
    
    result = lc_module_list_init();
    if(LC_SUCCESS != result)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) lc_module_list_init failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
        goto EXIT;
    }
    UC_SPI_MODULE_DEBUG("Start EraseCANVRAMPartition...\n");  
    if(0) //(0 != ps_data_read_write(WRITE, PRSTPrtInfo.start_addr, 0, 0, LC_NULL, LC_TRUE))
    {
        result = LC_ERROR_MODULE_ACCESS_ERROR;
        UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write failed!\n", __FUNCTION__, __LINE__);
        goto EXIT;
    }
    else
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write success!\n\n", __FUNCTION__, __LINE__);
    }

    UC_SPI_MODULE_DEBUG("%s() in line(%d) EraseCANVRAMPartition success!\n", __FUNCTION__, __LINE__);
EXIT:
    return result;

}

lc_result LoaderCoreSPI_Module_EraseEntireNVRAMPartition()
{
    lc_result result = LC_SUCCESS;
  
    PARTITION_INFO part_info;
    lc_sint32 err = -1;
    
    result = lc_module_list_init();
    if(LC_SUCCESS != result)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) lc_module_list_init failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
        goto EXIT;
    }
    UC_SPI_MODULE_DEBUG("Start EraseEntireNVRAMPartition...\n");  
	
    /* erase entire NVRAM partition */
    //if (0 != ps_data_read_write(WRITE, NVRAMPrtInfo.start_addr, 0, 0, LC_NULL, LC_TRUE))
    result = LoaderCoreSPI_Module_EraseIrdetoNVRAMPartition();
    if(result != LC_SUCCESS)
    {
        result = LC_FAILURE;
        goto EXIT;
    }

    result = LoaderCoreSPI_Module_EraseLoaderNVRAMPartition();
    if(result != LC_SUCCESS)
        result = LC_FAILURE;
    
    UC_SPI_MODULE_DEBUG("%s() in line(%d) erase entire NVRAM parition success!\n", __FUNCTION__, __LINE__);
    
EXIT:
    return result;

}

lc_result LoaderCoreSPI_Module_EraseHLModule(UINT32 chunk_id)
{
    UINT32 data_addr = 0;
    UINT32 data_len = 0;
    lc_result result = LC_FAILURE;
    lc_char *addr = NULL;

	if (IRD_IMAGE_MODULE_HEADER_CKID  == chunk_id)
	{
	    if (0x220000 == chunk_start)
		{
			  data_addr = IRD_IMAGE_MODULE_HEADER_CKID_ADDR_LOGO;
		}
		else
		{
			  data_addr = IRD_IMAGE_MODULE_HEADER_CKID_ADDR;
		}
	} 
	else
	    if (IRD_PSFLAG_MODULE_HEADER_CKID  == chunk_id)
		{
		    if (0x220000 == chunk_start)
			{
				  data_addr = IRD_PSFLAG_MODULE_HEADER_CKID_ADDR_LOGO;
			}
			else
			{
				  data_addr = IRD_PSFLAG_MODULE_HEADER_CKID_ADDR;
			}
		}	
        else	
		{
		  data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1); 
		}
    //data_addr = (UINT32)aui_flash_chunk_goto(&chunk_id, 0xFFFFFFFF, 1);
	if(LC_FAILURE!=data_addr)
	{
	    data_len = aui_flash_fetch_long(data_addr + CHUNK_OFFSET);

        if(chunk_id == IRD_IMAGE_MODULE_HEADER_CKID || chunk_id == IRD_PSFLAG_MODULE_HEADER_CKID \
			|| chunk_id == HL_MODULE_MAINCODE ||chunk_id == HL_MODULE_SEECODE )
        {//fix to one chunk, avoid erase chunk header

            data_len -= CHUNK_HEADER_SIZE;
            data_addr += CHUNK_HEADER_SIZE;
        }    
	    UC_SPI_MODULE_DEBUG("%s() in line(%d) data_addr = 0x%x,data_len = %d !\n", __FUNCTION__, __LINE__,data_addr,data_len);
	    
      
        addr = (lc_char*)LoaderCoreSPI_Memory_Malloc(data_len);
        if(!addr)
        {
            UC_SPI_MODULE_DEBUG ("%s() in line(%d) LoaderCoreSPI_Memory_Malloc fail\n", __FUNCTION__, __LINE__);
            result = LC_FAILURE;
        }
        else
            result = LC_SUCCESS;

        if(LC_SUCCESS == result)
        {
          
            LoaderCoreSPI_Stdlib_memset (addr, 0xff, data_len);
        
            if( 0 != ps_data_read_write(WRITE, data_addr, data_len, addr, 0, LC_FALSE))
        	{
                UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write failed!\n", __FUNCTION__, __LINE__);
                result = LC_FAILURE;
        	}
            else
            {
                UC_SPI_MODULE_DEBUG("%s() in line(%d) ps_data_read_write OK!\n", __FUNCTION__, __LINE__);
                result = LC_SUCCESS;
            }
        }
        
	}
	else
	{
	   UC_SPI_MODULE_DEBUG("%s() in line(%d) chunk_goto fail!\n", __FUNCTION__, __LINE__);
	   result = LC_FAILURE;
	}

    return result;
}

lc_result LoaderCoreSPI_Module_RetsetToDefault()
{
    lc_result result = LC_SUCCESS;
  
    lc_uint32 i = 0;
#if 1   
    result = LoaderCoreSPI_Module_EraseEntireNVRAMPartition();
    if(result!=LC_SUCCESS)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
        goto EXIT;
    }
#endif   
    //module info
    result = LoaderCoreSPI_Module_EraseHLModule(IRD_IMAGE_MODULE_HEADER_CKID);
    if(result!=LC_SUCCESS)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
        goto EXIT;
    }

    //ps flag
    result = LoaderCoreSPI_Module_EraseHLModule(IRD_PSFLAG_MODULE_HEADER_CKID);
    if(result!=LC_SUCCESS)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
        goto EXIT;
    }
    //main/see
    result = LoaderCoreSPI_Module_EraseHLModule(HL_MODULE_SEECODE);
    if(result!=LC_SUCCESS)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
        goto EXIT;
    }

    result = LoaderCoreSPI_Module_EraseHLModule(HL_MODULE_MAINCODE);
    if(result!=LC_SUCCESS)
    {
        UC_SPI_MODULE_DEBUG("%s() in line(%d) failed!\n", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
        goto EXIT;
    }
EXIT:
    return result;    
}

