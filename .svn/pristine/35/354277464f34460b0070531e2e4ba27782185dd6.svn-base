/**
 * @file LoaderCoreSPI.h
 * Header for Service Provider Interfaces (SPIs). This file contains the headers for the common Service Provider 
 * Interfaces that must be implemented on a platform. 
 *
 * \note It is the integrator's responsibility to implement these interfaces for a particular platform.
 */
 
#include "LoaderCoreSPI.h"
#include <osal/osal.h>

#define UC_SPI_DEBUG  LoaderCoreSPI_Stdlib_printf

#define WRITE 0
#define READ 1

#define ModifyFlagLen       (1)

#define ResetFlagLen        (1)

#define RebootTypeLen        (1)

#define RebootTypeReadLen        (1)

#define UpgradeResultLen   (1)

static lc_uint32 ModifyFlagOffset = 0;
static lc_uint32 ResetFlagOffset  = 1;
static lc_uint32 RebootTypeOffset = 2;
static lc_uint32 RebootTypeReadOffset = 3;
static lc_uint32 PSUpgradeOffset = 4;


#define ModifyFlagLen       (1)
#define TuningDataLen       (128)
#define TuningDataCount     (2)

/**nor flash*/
#define FLASH_TYPE_NOR (0)
/**nand flash*/
#define FLASH_TYPE_NAND (1)

#define SLEEP_BEFORE_REBOOT (30000)

//static lc_uchar RType = COLD_BOOT;
static lc_uchar MFlag = 0x00;
static executecode_func func = {0};

#ifdef ALI_IRD_DEBUG
void lc_data_dump(lc_uchar *data, lc_uint32 len)
{
    lc_uint32 i;
    for(i=0; i<len; i++)
    {
        UC_SPI_DEBUG("0x%02x, ", *(data+i));
        if((i+1)%16==0)
            UC_SPI_DEBUG("\n");
    }
    if(i%16!=0)
        UC_SPI_DEBUG("\n");
}
#endif



void LoaderCoreSPI_SetExecuteCodeFunc (executecode_func *pfunc)
{
	func.Strapup = pfunc->Strapup;
	func.Bootloader= pfunc->Bootloader;
	func.Application= pfunc->Application;
	func.Updateinfo = pfunc->Updateinfo;
	return;
}

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
lc_result LoaderCoreSPI_ReportErrorCode(lc_uint32  errorCode, lc_uint16 moduleId)
{
    int info_type =0;
    int info_size=0;
    lc_uint32 info_array[2] ={0};

	UC_SPI_DEBUG ("LoaderCoreSPI_ReportErrorCode<<<<<<==== 0x%03x ===>>>>>>>\n", errorCode);
    
    /* display error and moduleId in the OSD */
    if(0xffff != moduleId)
    {
        info_type = UI_INFO_TYPE_ERROR_CODE;
        info_size = SPI_DIS_ERR_WITH_MODID;
        info_array[0]= errorCode;
        info_array[1]= moduleId;
        LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(info_array));
    }
    else
    {
        info_type = UI_INFO_TYPE_ERROR_CODE;
        info_size = sizeof(errorCode);
        LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&errorCode));
    }

    if(0 == errorCode)
    {
        /*
          * update UI stage info
          */
        LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_FINAL_SUCCESS);

        //snprintf(info_long_message,64,"Download completed successfully!");
        //LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_STAGE,0,info_long_message);
    }
    else
    {
        /*
          * update UI stage info
          */
        LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_FINAL_FAILED);
        //snprintf(info_long_message,64,"Download failed, please try again!");
        //LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_STAGE,0,info_long_message);
    }
	return LC_SUCCESS;
}

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

lc_result LoaderCoreSPI_SetResetType(lc_uchar resetType)
{

    lc_uint32 chunk_addr;
    lc_result lc_ret= LC_SUCCESS;    
  
    lc_ret = loadercorespi_flash_init();
    if(LC_SUCCESS != lc_ret)
    {
       UC_SPI_DEBUG("%s() in line(%d) loadercorespi_flash_init failed!\n:", __FUNCTION__, __LINE__);
       goto EXIT;
    }
    if( LC_SUCCESS != getPsFlagChunkAddr(&chunk_addr))
    {
        UC_SPI_DEBUG("%s() in line(%d) getPsFlagPrtAddr failed!\n:", __FUNCTION__, __LINE__);
		lc_ret = LC_FAILURE;
        goto EXIT;
    }
    UC_SPI_DEBUG("%s in %d line: start_addr = 0x%x.\n",  __FUNCTION__, __LINE__,chunk_addr);
	if ( 0 != ps_data_read_write(WRITE, chunk_addr, ResetFlagLen, (void *)&resetType, 0, LC_FALSE))
	{
        UC_SPI_DEBUG("%s() in line(%d) ps_data_read_write failed!\n:", __FUNCTION__, __LINE__);
		lc_ret = LC_FAILURE;
        goto EXIT;
	}

EXIT:
	return lc_ret;
    
}

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
lc_result LoaderCoreSPI_GetResetType(lc_uchar *pResetType)
{

    lc_uint32 chunk_addr;
    lc_result lc_ret= LC_SUCCESS;    

    lc_ret = loadercorespi_flash_init();
    if(LC_SUCCESS != lc_ret)
    {
       UC_SPI_DEBUG("%s() in line(%d) loadercorespi_flash_init failed!\n:", __FUNCTION__, __LINE__);
       goto EXIT;
    }
    if( LC_SUCCESS != getPsFlagChunkAddr(&chunk_addr))
    {
        UC_SPI_DEBUG("%s() in line(%d) getPsFlagPrtAddr failed!\n:", __FUNCTION__, __LINE__);
		lc_ret = LC_FAILURE;
        goto EXIT;
    }
    UC_SPI_DEBUG("%s in %d line: start_addr = 0x%x.\n",  __FUNCTION__, __LINE__,chunk_addr);
	if ( 0 != ps_data_read_write(READ, chunk_addr+ ResetFlagOffset, ResetFlagLen,(void *)pResetType,0, LC_FALSE))
	{
        UC_SPI_DEBUG("%s() in line(%d) ps_data_read_write failed!\n:", __FUNCTION__, __LINE__);
		lc_ret = LC_FAILURE;
        goto EXIT;
	}

EXIT:
	return lc_ret;

}

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


lc_result LoaderCoreSPI_SetPSModifyFlag(lc_uchar modifyFlag)
{

	lc_uint32 chunk_addr;
    lc_result lc_ret= LC_SUCCESS;    
    lc_uchar data = 0;  
	 
    lc_ret = loadercorespi_flash_init();
    if(LC_SUCCESS != lc_ret)
    {
       UC_SPI_DEBUG("%s() in line(%d) loadercorespi_flash_init failed!\n:", __FUNCTION__, __LINE__);
       goto EXIT;
    }
    if( LC_SUCCESS != getPsFlagChunkAddr(&chunk_addr))
    {
        UC_SPI_DEBUG("%s() in line(%d) getPsFlagPrtAddr failed!\n:", __FUNCTION__, __LINE__);
		lc_ret = LC_FAILURE;
        goto EXIT;
    }
    UC_SPI_DEBUG("%s in %d line: start_addr = 0x%x.\n",  __FUNCTION__, __LINE__,chunk_addr);
	if ( 0 != ps_data_read_write(WRITE, chunk_addr + ModifyFlagOffset , ModifyFlagLen,(void *)&modifyFlag,0, LC_FALSE))
	{
        UC_SPI_DEBUG("%s() in line(%d) ps_data_read_write failed!\n:", __FUNCTION__, __LINE__);
		lc_ret = LC_FAILURE;
        goto EXIT;
	}
	MFlag = modifyFlag;
    
EXIT:    
    return lc_ret;
	
}

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
lc_result LoaderCoreSPI_GetPSModifyFlag(lc_uchar *pModifyFlag)
{
    lc_uint32 chunk_addr;
    lc_result lc_ret= LC_SUCCESS;    
	if (0 == MFlag)
	{
	    lc_ret = loadercorespi_flash_init();
	    if(LC_SUCCESS != lc_ret)
	    {
	       UC_SPI_DEBUG("%s() in line(%d) loadercorespi_flash_init failed!\n:", __FUNCTION__, __LINE__);
	       goto EXIT;
	    }
	    if( LC_SUCCESS != getPsFlagChunkAddr(&chunk_addr))
	    {
	        UC_SPI_DEBUG("%s() in line(%d) getPsFlagPrtAddr failed!\n:", __FUNCTION__, __LINE__);
			lc_ret = LC_FAILURE;
	        goto EXIT;
	    }
	    UC_SPI_DEBUG("%s in %d line: start_addr = 0x%x.\n",  __FUNCTION__, __LINE__,chunk_addr);
		if ( 0 != ps_data_read_write(READ, chunk_addr + ModifyFlagOffset, ModifyFlagLen,(void *)pModifyFlag,0,LC_FALSE))
		{
	        UC_SPI_DEBUG("%s() in line(%d) ps_data_read_write failed!\n:", __FUNCTION__, __LINE__);
			lc_ret = LC_FAILURE;
	        goto EXIT;
		}
	}
	else
	{
	  *pModifyFlag = MFlag;
	}

EXIT:
    return lc_ret;
}

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
lc_result LoaderCoreSPI_ExecuteCode( lc_code_id codeID )
{
	lc_result ret = LC_SUCCESS;
	
	switch (codeID)
	{
		case CODE_ID_BOOT_STRAP:
		{
			UC_SPI_DEBUG ("CODE_ID_BOOT_STRAP\n");
			if (0 == func.Strapup)
			{
    			aui_sys_reboot(0);
				ret = LC_FAILURE;
				break;
			}
			UC_SPI_DEBUG ("CODE_ID_BOOT_STRAP: reboot\n");
			aui_sys_reboot(0);//func.Strapup();
			break;
		}
			
		case CODE_ID_BOOT_LOADER:
		{
			UC_SPI_DEBUG ("CODE_ID_BOOT_LOADER\n");
			if (0 == func.Bootloader)
			{
				ret = LC_FAILURE;
			    break;
			}
			func.Bootloader();
			break;
		}

		case CODE_ID_HIGH_LEVEL_APPLICATION:
		{
			UC_SPI_DEBUG ("CODE_ID_HIGH_LEVEL_APPLICATION\n");
			if (0 == func.Application)
			{
                //after upgrade the stb need to be reboot in 30 seconds
    			osal_task_sleep(SLEEP_BEFORE_REBOOT);
    			aui_sys_reboot(0);
			    ret = LC_FAILURE;
				break;
			}

			func.Application();


			break;
		}

		default:
		{
			LoaderCoreSPI_Stdlib_printf ("unknow execute code!!!\n");
			break;
		}
	}
	
	return ret;
}





static struct 
{
    lc_ui_stages stage_info;
    lc_uchar message[64];
}stage_info_table[] = 
    {
        {UI_STAGES_LOADER_READY,                "Loader is ready"},
        {UI_STAGES_TRANSPORT_STRAM,             "Start transport stream..."},
        {UI_STAGES_DOWNLOAD_DSI,                "Download DSI..."},
        {UI_STAGES_DOWNLOAD_DII,                "Download DII..."},
        {UI_STAGES_DOWNLOAD_DDB,                "Download DDB, it may take a while, please wait..."},
        {UI_STAGES_PROCESSING_DATA_DECRYPT,     "Decrypt module data..."},
        {UI_STAGES_PROCESSING_DATA_DECOMPRESS,  "Decompress module data..."},
        {UI_STAGES_VERIFYING_SIG,               "Verifying signature..."},
        {UI_STAGES_WRITING_DATA_TO_FLASH,       "Storing module data to flash..."},
        {UI_STAGES_UPDATING_VARIANT,            "Update Variant"},
        {UI_STAGES_UPDATING_KEY,                "Update Key"},
        {UI_STAGES_FINAL_SUCCESS,               "Download completed successfully!"},
        {UI_STAGES_FINAL_FAILED,                "Download failed, please try again!"}
    };

static lc_result LoaderCoreSPI_GetUIStringFromStageinfo(lc_ui_stages stage_info, const lc_uchar string[])
{
    lc_result result = LC_SUCCESS;
    lc_uint32 total_message_cnt = 0; 
    lc_uint32 i = 0;
    if(LC_NULL == string)
    {
        LoaderCoreSPI_Stdlib_printf("%s() in line(%d) input paramter invalid:", __FUNCTION__, __LINE__);
        result = LC_FAILURE;
    }

    if(LC_SUCCESS == result)
    {
        total_message_cnt = sizeof(stage_info_table)/sizeof(stage_info_table[0]);
            
        for (i = 0; i < total_message_cnt; i++) 
        {
            if (stage_info == stage_info_table[i].stage_info) 
            {
                snprintf(string, 64, stage_info_table[i].message);
                break;
            }
        }
        
        if(total_message_cnt == i)
        {
            snprintf(string,64,"Unknow stage info!");
        }
    }
    
    return result;
}

lc_result LoaderCoreSPI_UpdateUIStageInfo(lc_ui_stages stage_info)
{
    lc_result result = LC_SUCCESS;
    char info_long_message[64]={0};

    result = LoaderCoreSPI_GetUIStringFromStageinfo(stage_info, info_long_message);
    if(LC_SUCCESS == result)
    {
        result = LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_STAGE,0,info_long_message);
    }

    return result;
}


lc_result LoaderCoreSPI_Update_UI_Message(const lc_char *pFormat,...)
{
    return;
    char info_long_message[64]={0};
    snprintf(info_long_message,64,pFormat);
    return LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_ERROR_INFO,0,info_long_message);
}


lc_result LoaderCoreSPI_UPDATE_UI(int type,int size,void*buf)
{
   #if 0
   if(UI_INFO_TYPE_PROCESS== type)
    {
        libc_printf("%s() =========> percentage(%d) tick(%d)\n", __FUNCTION__, *((lc_uint16 *)buf), osal_get_tick());
    }
   
    LoaderCoreSPI_take_a_break();
	#endif
	
    if(LC_NULL != func.Updateinfo)
    {
        return func.Updateinfo(type,size,buf);
    }
    else
    {
        return LC_SUCCESS;
    }
}

//define the update rate of the UI.
//It's used to set the sleep time in UI task.
//While data is downloaded, the sleep time need to be less.
//While data is downloading, the sleep time need to be more.
static lc_uint32 g_ui_rate = 400;
static lc_uint32 g_a_break = 120;

void LoaderCoreSPI_set_ui_update_rate(lc_uint32 var)
{
//  printf("%s() ===> var is %d\n",__FUNCTION__,var);
    g_ui_rate = var;
}

lc_uint32 LoaderCoreSPI_get_ui_update_rate()
{
//  printf("%s() ===> var is %d\n",__FUNCTION__,g_ui_rate);
    return g_ui_rate;
}

void LoaderCoreSPI_take_a_break()
{  
    return;
//    libc_printf("%s() =========> tick(%d)\n", __FUNCTION__, osal_get_tick());
    osal_task_sleep(g_a_break);
}

