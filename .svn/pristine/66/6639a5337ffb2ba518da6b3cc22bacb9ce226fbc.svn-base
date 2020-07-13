/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : Bootloader.c                                               *
*                                                                            *
*   Description : The Boot Loader will acquire and process the headers and   *
*              present within the download to correctly obtain and transform *
*              data the download content such that the original data image   *
*              is reconstructed. This image is cryptographically checked to  *
*              ensure delivery before being written to target destination.   *
*                                                                            *
*****************************************************************************/
 


/******************************** Header Files ********************************/
#include "../Shared/LoaderCorePrivate.h"
#include "Decompression.h"
#include "Aes.h"
#include "DemuxManager.h"
#include "Utilization.h"
#include <sys_config.h>
#include <osal/osal.h>

#include "Dvb/Carousel.h"

/* Maximum size of download header. */
#define DOWNLOADE_HEADER_MAX_SIZE (30 + 4 * 0xFFFF + 2 * SIGNATURE_LENGTH)
/******************************* Local Variables ******************************/

/* Offset for download file. */
static lc_uint32 gSdlOffset;

/* This is used to verify the download */
static lc_sha_controller gGlobalSignatureController;

/* Found a new download? */
static lc_bool gFoundAcceptableUpdate;

/* Key download, variant download or code download? */
lc_dl_class gDownloadClass;

/* Migration? */
static lc_bool gMigrationMode;

/* Key for AES decompression */
#define AES_KEY_LEN   (32)
#define AES_BLOCK_LEN (16)
static const lc_uchar gAesKey[AES_KEY_LEN] = {
    0xEB, 0x89, 0xD9, 0xD2, 0xA8, 0x02, 0xA0, 0x0F, 0x25, 0xCB, 0x62, 0x28,
    0xE3, 0xA5, 0x89, 0xE5, 0xA2, 0xC3, 0x05, 0x53, 0x47, 0x6B, 0xE2, 0x7D,
    0x05, 0xC2, 0x49, 0x38, 0x29, 0xAD, 0xFC, 0x1D
};


/************************* Local Function Declarations ************************/

/** 
 * Initialization for Boot Loader.
 */
static lc_result LC_InitialiseBootLoader( void );

/** 
 * Error handling for Boot Loader.
 */
static void LC_BootLoaderErrHandler(void);

/** 
 * Main process of download and update.
 */
static lc_result LC_DownloadProcess( void );

/** 
 * Download download header.
 */
static lc_result LC_AcquireDownloadHeader(lc_module_dlh_st *pDownloadHeader);

/** 
 * Download module header.
 */
static lc_result LC_AcquireModuleHeader(lc_uint16 moduleId, lc_module_mh_st *pDPModuleHeader);

/** 
 * Download datagrams.
 */
static lc_result 
LC_AcquireDatagrams(
    lc_uint16 moduleId, 
    const lc_module_mh_st *pModuleHeader, 
    lc_uchar *pModuleDataByte);

/** 
 * Request update data via UART from TEMU.
 */
static lc_result 
LC_AcquireUartPackage(lc_uart_packet_type enData_id, lc_uint32 *pSdlOffset, lc_buffer_st* pbBuf);

/** 
 * Download process starting from downloading module header.
 */
static lc_result 
LC_DownloadAndUpdateModule(lc_uint16 moduleId,lc_buffer_st * dataBuffer);

/** 
 * Check if TEMU has been connected via UART.
 */
static lc_result 
LC_CheckUartConnection(lc_bool setError);

/** 
 * Conduct routine check on download header.
 */
static lc_result 
LC_ProcessDownloadHeader(const lc_module_dlh_st *pDownloadHeaderSt);



/** 
 * Check to see if we already have the newest version of a particular module.
 */
static lc_result 
LC_CheckModuleVersion(lc_uint16 moduleId, lc_uint32 newVersion);

static lc_result LC_UpdateModule(const lc_buffer_st *pModuleByte,lc_bool isAMankeyUpdate);
static lc_result LC_CheckModule(const lc_buffer_st *pModuleByte,lc_bool *isMankeyDownload);
static lc_result LC_GetKeyStatus(lc_bool *must_update_key);

lc_result LoaderCoreAPI_StartBootLoader( nim_setup func)
{
    lc_uint32 errorCode = ERROR_CODE_SUCCESS;
    lc_result result = LC_SUCCESS;
	lc_result serial_result = LC_SUCCESS;
    lc_uchar downloadType = NONE_DOWNLOAD;
    lc_uchar psModifyFlag = PS_UNMODIFIED;
    lc_uint16 info_type =0;
    lc_uint16 info_size =0;
    lc_uint16 info_value =0;
    lc_bool need_update_key = LC_FALSE;
    lc_bool UartConnect = LC_FALSE;
    int ui_error = 0xbbb;
    lc_uint16 lastDSN = 0xffff;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint16 moduleId = 0xFFFF;

	
    TRACE_LOG0(TRACE_INFO, ("**********************************************\n"));
    TRACE_LOG0(TRACE_INFO, ("*              V5.0 BOOT LOADER              *\n"));
    TRACE_LOG0(TRACE_INFO, ("**********************************************\n"));
	TRACE_LOG0(TRACE_INFO, ("* REV & DATE : v1.60  2016-05-10             *\n"));
	TRACE_LOG0(TRACE_INFO, ("* COPYRIGHT (C) 2002-2016 IRDETO B.V.        *\n"));
    TRACE_LOG0(TRACE_INFO, ("**********************************************\n"));

    /* Reset error code to ERROR_CODE_SUCCESS at the very beginning of BLOADER by default. */
    ERR_REPORT_Initialize();
    if(LC_SUCCESS == result)
    {
        result = LC_InitialiseBootLoader();
    }
    if(LC_SUCCESS != result)
    TRACE_LOG0(TRACE_INFO,"LC_InitialiseBootLoader failed\n");

    if(LC_SUCCESS == result)
    {
        /**
         * init the DSN of Loader OSD
         */
        result = LC_UtilGetDownloadSequence(&lastDSN);   
        if(LC_SUCCESS == result)
        {
            LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_DSN,sizeof(lc_uint16),(void*)(&lastDSN));
        }
    }

    //process to 10%
    info_type = UI_INFO_TYPE_PROCESS;
    info_size = sizeof(lc_uint16);
    info_value = 10;
    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));
    LoaderCoreSPI_set_ui_update_rate(400);

    if(LC_SUCCESS == result)
    {
        /* Get and Check download flag & type. */

		//result = LC_CheckUartConnection(LC_TRUE);
		serial_result = LC_CheckUartConnection(LC_FAILURE);
        if(LC_SUCCESS == serial_result)
        {
           LC_UtilSetDownloadType(SERIAL_DOWNLOAD);
           UartConnect = LC_TRUE;
        }
		else
		{
           ERR_REPORT_GetErrorCode(&errCode, &moduleId);
		   if(ERROR_CODE_UART_TIMEOUT == errCode)
		   {
			  errorCode = ERROR_CODE_SUCCESS;	
			  ERR_REPORT_Initialize();
		   }
						
		    LC_UtilSetDownloadType(OTA_DOWNLOAD);
            UartConnect = LC_FALSE; 
		}

	    downloadType = LC_UtilGetDownloadType();       
		  
		TRACE_LOG1(TRACE_INFO, "#[BLOADER] downloadType = %d\n",downloadType); 
        
        if (/*LC_TRUE != LC_UtilGetDownloadFlag() ||*/     
            NONE_DOWNLOAD == downloadType)
        {
            TRACE_LOG0(TRACE_ERROR, ("#[BLOADER] No download required.\n"));
            ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_DL_TYPE);
            result = LC_FAILURE;
        }

        //LC_GetKeyStatus(&need_update_key);                    
        TRACE_LOG1(TRACE_INFO, "#[BLOADER] need_update_key = %d\n", need_update_key);  

        //process to 20%
        info_type = UI_INFO_TYPE_PROCESS;
        info_size = sizeof(lc_uint16);
        info_value = 20;
        LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));      //

        LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_ERROR_CODE,sizeof(int),(void*)(&ui_error));
        
        if (LC_SUCCESS == result)
        {
            /* Set download available flag to FALSE. */
            result = LC_UtilSetDownloadFlag(LC_FALSE);          //201803

            /* Update Loader Prt to flash first  */
            if (LC_SUCCESS != LC_UtilFlushLoaderPartition())    //201803
            {
                ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_LOADERPT);
            }

            if( LC_SUCCESS == result )
            {
                //result = LC_CheckUartConnection(LC_TRUE);
               // if(LC_SUCCESS == result)
               // {
                //    UartConnect = LC_TRUE;
               // }

                if(LC_FALSE == UartConnect && LC_TRUE == need_update_key && SERIAL_DOWNLOAD == downloadType)
                {
                     TRACE_LOG0(TRACE_INFO, ("#[BLOADER] STB key is broken,please upgrade key files via uart or USB!\n"));
                     ERR_REPORT_SetErrorCode(ERROR_CODE_UART_DETECTED);
                     result = LC_FAILURE;
                }
                if(OTA_DOWNLOAD == downloadType)
                {
                    /* Migration mode? */
                    if (LC_SUCCESS == result)
                    {
                        gMigrationMode = LC_UtilCheckMigrationMode();
                    }
                    
                    /*Initialize the demux manager.*/
                    if (LC_SUCCESS == result)
                    {
                        result = LC_InitializeDemuxManager();
                    }

                    if(LC_SUCCESS == result)
                    {
                        switch (downloadType)
                        {
                            case OTA_DOWNLOAD:
                            {                                    
                                TRACE_LOG0(TRACE_INFO, ("#[BLOADER] OTA downloadType detected, setup carousel now...!\n"));
                                result= LC_SetupCarousel(func);
                                if (LC_SUCCESS == result)
                                {
                                    result = LC_ProcessCarousel();
                                }
                                break;                                               
                            }
                            default:
                            {
                                /* No OTA download type specified! */
                                TRACE_LOG0(TRACE_FATAL, ("#[BLOADER] No download type specified!\n"));
                                break;
                            }
                        }
                    }

                }

                if(LC_SUCCESS == result)
                {
                    TRACE_LOG0(TRACE_INFO, ("#[BLOADER] Bootloader start download process. \n"));
                    
                    //process to 30%
                    info_type = UI_INFO_TYPE_PROCESS;
                    info_size = sizeof(lc_uint16);
                    info_value = 30;
                    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));

                   /*
                      * update UI stage info
                      */
                    if (OTA_DOWNLOAD == downloadType)
                    {
                        LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_LOADER_READY);
                    }
                   
                    result = LC_DownloadProcess();
                }

                if (OTA_DOWNLOAD == downloadType)
                {  
                    LC_FinalizeCarousel();
                    /*Finalize demux.*/
                    LC_FinalizedDemuxManager();
                }


            }

            /* If no module has been updated, reset migration variant and sub-variant to default. */
            LoaderCoreSPI_GetPSModifyFlag(&psModifyFlag);
            if ((LC_SUCCESS == result) || 
                ((LC_SUCCESS != result) && (PS_MODIFIED != psModifyFlag)))
            {
                LC_UtilResetMigrationVariant();
            }

            /* Update Loader Partition. */
            if (LC_SUCCESS != LC_UtilFlushLoaderPartition())
            {
                ERR_REPORT_SetErrorCode(ERROR_CODE_INVALID_LOADERPT);
            }

        }
       
    }

    /* Finalize Persisitant Storage variable. */
    LC_FinalizePSVariable();
    //process to 100%
    info_type = UI_INFO_TYPE_PROCESS;
    info_size = sizeof(lc_uint16);
    info_value = 100;
    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));
    /**
     * If the update failed, Loader Core will not reset PS modify flag 
     * to PS_UNMODIFIED so as to launch another OTA download next time reboot. 
     */
    if (LC_DL_CLASS_CODE == gDownloadClass)
    {
        if(LC_SUCCESS == result)
        {
            /* Set PS modify flag to "unmodified" status. */
            LoaderCoreSPI_SetPSModifyFlag(PS_UNMODIFIED);
        }
    }

    
    /* Error handling. */
    
    ERR_REPORT_GetErrorCode(&errorCode, LC_NULL);
    /* Attention!!!!! Ensure the error code and result code are consistent with each other! */

    downloadType = LC_UtilGetDownloadType();
	if(OTA_DOWNLOAD == downloadType)
	{
        if( ERROR_CODE_UART_TIMEOUT == errorCode)
        {
          errorCode = ERROR_CODE_SUCCESS;
        }
	}
	
	libc_printf(" <%s:%d>  result = %d,errorCode = %d !!\n", __func__, __LINE__,result,errorCode);
	
    LC_ASSERT(!((LC_SUCCESS == result) && 
                    (ERROR_CODE_SUCCESS != errorCode && 
                    ERROR_CODE_SAME_MODULE_VERSION != errorCode)));
                    
    /* Unknown error occured. */
    if (LC_SUCCESS != result)
    {
        if (ERROR_CODE_SUCCESS == errorCode)
        {
            ERR_REPORT_SetErrorCode(ERROR_CODE_UNDEFINED_ERROR);
        }
    }
    
    /* Error code handling. */
    LC_BootLoaderErrHandler();

    /* Unify result code. */
    return LC_SUCCESS;

} /* LoaderCoreAPI_StartBootLoader */


static lc_result LC_InitialiseBootLoader( void )
{
   
    lc_result result  = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    
    /* Initialise CRC tables if required */
#ifdef USE_DYNAMIC_LOOKUP_TABLES
    CRC_CreateTables();
#endif

    /* New Download flag. */
    gFoundAcceptableUpdate = LC_FALSE;

    /* Download class: key, variant or code. */
    gDownloadClass = LC_DL_CLASS_CODE;

    /* Hash controller for global signature */
	gGlobalSignatureController.mode = PKCS_SHA256_MODE;

    /* Migration On/Off */
    gMigrationMode = LC_FALSE;

    /* SDL offset */
    gSdlOffset = 0; /* init value */


    /* Check Master Key of the device. */
    if( LC_SUCCESS == result )
    {
        result = LC_CheckMasterKey();     
        if (LC_SUCCESS != result)
        {
            TRACE_LOG0(TRACE_ERROR, ("#[BLOADER] Error checking Master Key!\n"));
            errCode = ERROR_CODE_INVALID_MASTER_KEY;
        }
    }
         
    /* Initialize Persisitant Storage variable. */
    if( LC_SUCCESS == result )
    {
        result = LC_InitializePSVariable();
    }


    ERR_REPORT_SetErrorCode(errCode);
    
    if( LC_SUCCESS != result )
    {
        TRACE_LOG0(TRACE_ERROR, ("#[BLOADER] System init failed!\n"));
    }
    if( LC_SUCCESS == result )
    {
        TRACE_LOG0(TRACE_INFO, ("#[BLOADER] System init is done!\n"));
    }
    return result;

} 

#define SLEEP_BEFORE_REBOOT (30000)
static void LC_BootLoaderErrHandler(void)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint32 ledDispLoopCnt = 0;
    lc_uint32 otaWaitCnt = 16;
    lc_uchar downloadType = NONE_DOWNLOAD;
    lc_uint16 moduleId = 0xFFFF;
    lc_front_panel_key_event keyEvent = KEY_NONE;
    lc_uchar ledDispSeq[2][3] = {{CHAR_BLNK, CHAR_BLNK, CHAR_BLNK}, {CHAR_BLNK, CHAR_BLNK, CHAR_BLNK}};
    lc_uint16 count = 0;
    lc_uchar downloadStatus = 0;

    ERR_REPORT_GetErrorCode(&errCode, &moduleId);
	
    downloadType = LC_UtilGetDownloadType();
	if(OTA_DOWNLOAD == downloadType)
	{
        if( ERROR_CODE_UART_TIMEOUT == errCode)
        {
          errCode = ERROR_CODE_SUCCESS;
        }
	}
	
    TRACE_LOG1(TRACE_INFO, "[BLOADER] Error code = 0x%8x\n", errCode);
    
    /* save update success to ps_flag */
    if (ERROR_CODE_SUCCESS != errCode)
	{
        downloadStatus = 1;
    }
    
    /*Report the error code to the client device no matter success or not.*/
    LoaderCoreSPI_ReportErrorCode(errCode, moduleId);

	/*Following a successful Key Download or Variant Download, the error code 0x00 shall be displayed*/
    if(( ERROR_CODE_SUCCESS == errCode) && (LC_DL_CLASS_KEY != gDownloadClass) && 
            (LC_DL_CLASS_VARIANT != gDownloadClass)  ) 
    {
        //after upgrade the stb need to be reboot in 30 seconds
        while(1)
        {
            /*Try to get a key.*/
            LoaderCoreSPI_FrontPanel_GetKey(&keyEvent, 500);
            
            /* until STANDBY front panel key pressed. */
            if( KEY_STANDBY == keyEvent)
            {
                TRACE_LOG0(TRACE_INFO, "[BLOADER] detected a standby button, reboot now...\n");
                break;
            }
            
    		osal_task_sleep(100);
            count += 1;
            if(100 == count)
            {
                break;
            }
        }
        osal_task_sleep(3000);

    }
    else
    {
        /* any other error, go through ErrHandler() */
       
        /* acquire four displaying segments of Error Code (probably module ID). */
        ledDispSeq[0][0] = (lc_uchar)CHAR_E;
        ledDispSeq[0][1] = LC_LedDisplayGetHexDigit(((lc_uchar)(errCode) >> 4) & 0x0F);
        ledDispSeq[0][2] = LC_LedDisplayGetHexDigit(((lc_uchar)(errCode) >> 0) & 0x0F);
        
        if (0xffff != moduleId)
        {
            /* 2 times per cycle required to display the entire error code, 
            looks like error_code 8 bits -> module ID Low 12 bits */
            ledDispSeq[1][0] = LC_LedDisplayGetHexDigit(((lc_uchar)(moduleId >> 8) >> 0) & 0x0F);
            ledDispSeq[1][1] = LC_LedDisplayGetHexDigit(((lc_uchar)(moduleId >> 0) >> 4) & 0x0F);
            ledDispSeq[1][2] = LC_LedDisplayGetHexDigit(((lc_uchar)(moduleId >> 0) >> 0) & 0x0F);
        }

        /* Get download type, it will be used to decide the handling method later. */
        if(SERIAL_DOWNLOAD == downloadType)
        {
            TRACE_LOG0(TRACE_INFO, ("#[BLOADER] Waiting for STANDBY pressed to reset the IRD...\n"));
        }
        else
        {
            TRACE_LOG0(TRACE_INFO, ("#[BLOADER] Waiting for 4s to reset the IRD...\n"));
        }

        /*We will NOT quit unless STANDBY key is pressed.*/
        while(1)
        {
       
            /* Display error code. */
            LC_LedDisplay(
                LED_CHAR_NONE, 
                (lc_front_panel_char)ledDispSeq[ledDispLoopCnt][0], 
                (lc_front_panel_char)ledDispSeq[ledDispLoopCnt][1], 
                (lc_front_panel_char)ledDispSeq[ledDispLoopCnt][2]);

            /* Spark counter handling. */
            if (0xffff != moduleId)
            {
                ledDispLoopCnt = ((ledDispLoopCnt + 1) % 2);
            }
       
            /* For serial download, wait for a key press of STANDBY to trigger the reboot. */
            if(SERIAL_DOWNLOAD == downloadType)
            {
           
                /*Clear it before continue since we are in a while loop.*/
                keyEvent = KEY_NONE;

                /*Try to get a key.*/
                LoaderCoreSPI_FrontPanel_GetKey(&keyEvent, 500);

                /* until STANDBY front panel key pressed. */
                if( KEY_STANDBY == keyEvent)
                {
                    TRACE_LOG0(TRACE_INFO, "[BLOADER] detected a standby button, reboot now...\n");
                    break;
                }
                LoaderCoreSPI_Thread_Sleep(500);
            }
            /* For OTA download, wait for a fixed time to trigger the reboot. */
            else
            {   
             
                /* Error display period: 4 secs suggested. */
                if( 0 == (otaWaitCnt--) )  
                { 
                    break;
                }
                
                LoaderCoreSPI_Thread_Sleep(500);
            }
        }
       
        /* IRD post-reboot behaviour */
        LoaderCoreSPI_SetResetType(IRD_COLD_BOOT);

    }

    /*No matter success or not, Boot Loader can only transit to Boot Strap.*/
    result = LoaderCoreSPI_ExecuteCode( CODE_ID_BOOT_STRAP ); /* reset Boot Strap */
   
} 


static lc_result LC_DownloadProcess( void )
{
    lc_result result = LC_SUCCESS;
    lc_uint32 uErrCode = ERROR_CODE_SUCCESS;
    lc_uchar hash[32];
    lc_uint32 cnt = 0;
    lc_module_dlh_st downloadHeaderSt;
    lc_last_download_info_st lastDownloadPara;
    lc_bool isAMankey = LC_FALSE;	
    lc_uint16 info_type =0;
    lc_uint16 info_size =0;
    lc_uint16 info_value =0;
    lc_uint16 info_array[3] ={0};
    lc_uchar downloadType = NONE_DOWNLOAD;
    
    LC_memset(hash, 0, sizeof(hash));
    LC_memset(&downloadHeaderSt, 0, sizeof(lc_module_dlh_st));
    LC_memset(&lastDownloadPara, 0, sizeof(lc_last_download_info_st));

    downloadType = LC_UtilGetDownloadType();
    TRACE_LOG1(TRACE_INFO, "#[BLOADER] Enter LC_DownloadProcess now, the downloadType = %d\n", downloadType);

    /* Get the download header */
    if (LC_SUCCESS == result)
    {
        result = LC_AcquireDownloadHeader(&downloadHeaderSt);
        if (LC_SUCCESS == result)
        {            
            lastDownloadPara.download_sequence_number = downloadHeaderSt.download_sequence_number;
            LC_memcpy(lastDownloadPara.isign_version, downloadHeaderSt.isign_version, sizeof(downloadHeaderSt.isign_version));
            LC_memcpy(lastDownloadPara.isign_serial_number, downloadHeaderSt.isign_serial_number, sizeof(downloadHeaderSt.isign_serial_number));
        }
    }
	
    //process to 50% 
    info_type = UI_INFO_TYPE_PROCESS;
    info_size = sizeof(lc_uint16);
    info_value = 50;
    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));
    
    /* Now it's time to download and check modules. */
    if (LC_TRUE == gFoundAcceptableUpdate)
    {
        if (LC_SUCCESS == result)
        {
            for(cnt = 0; cnt < downloadHeaderSt.number_of_modules; cnt++)
            {
            	downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer = LC_MALLOC(sizeof(lc_buffer_st));
				if (LC_NULL == downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer)
				{
					result = LC_ERROR_INSUFFICIENT_BUFFER;
					break; 
				}
                //Module UI update stage 1
                info_type = UI_INFO_TYPE_MODULE_INFO;
                info_size = sizeof(info_array);
                info_array[0]= UI_MODULE_DATA_DOWNLOAD;
                info_array[1]=cnt+1;
                info_array[2]=downloadHeaderSt.number_of_modules;
                LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(info_array));

                result = LC_DownloadAndUpdateModule(downloadHeaderSt.pModuleIdList[cnt].module_id,downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer);   
				if(LC_SUCCESS != result)
	            {
	                TRACE_LOG1(
	                    TRACE_ERROR, 
	                    "&[BLOADER] Download module #%u failed!\n",
	                    downloadHeaderSt.pModuleIdList[cnt].module_id);
	                       
	                break; /* break out to do some possible rollback */
	            }
            }

            LoaderCoreSPI_set_ui_update_rate(100);
            //process to 60%
            info_type = UI_INFO_TYPE_PROCESS;
            info_size = sizeof(lc_uint16);
            info_value = 60;
            LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));

            for(cnt = 0; cnt < downloadHeaderSt.number_of_modules; cnt++)
            {
                //Module UI update stage 2
                info_type = UI_INFO_TYPE_MODULE_INFO;
                info_size = sizeof(info_array);
                info_array[0]= UI_MODULE_DATA_CHECK;
                info_array[1]=cnt+1;
                info_array[2]=downloadHeaderSt.number_of_modules;
                LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(info_array));
                /* check this module. */
                if (LC_SUCCESS == result)
                {
                    result = LC_CheckModule(downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer,&isAMankey);
                    if(LC_SUCCESS == result)
                    {
                        TRACE_LOG1(
                            TRACE_INFO, 
                            "&[BLOADER] Module #%u was succesfully checked.\n",
                            downloadHeaderSt.pModuleIdList[cnt].module_id);
                    }
                    else
                    {
                        TRACE_LOG1(
                            TRACE_ERROR, 
                            "&[BLOADER] Error: Module #%u was not succesfully checked!\n",
                            downloadHeaderSt.pModuleIdList[cnt].module_id);
                    }
                }

				if(LC_SUCCESS != result)
	            {
	                /**
	                    * Download and update module failed
	                    * and if there is ONLY one module to be updated,
	                    * or
	                    * If there are more than one module to be updated, but we encountered an 
	                    * error (except LC_ERROR_SAME_MODULE_VERSION)when downloading the first module, 
	                    * then return out without going on checking global signature and subsequent 
	                    * rollback.
	                    * 
	                    */

	                if (LC_ERROR_SAME_MODULE_VERSION == result)
	                {
	                    TRACE_LOG1(
	                        TRACE_INFO, 
	                        "&[BLOADER] Same module version for module #%u encounterd, ignored!\n",
	                        downloadHeaderSt.pModuleIdList[cnt].module_id);
	                    result = LC_SUCCESS;
	                }
	                else
	                {
	                    TRACE_LOG1(
	                        TRACE_ERROR, 
	                        "&[BLOADER] Download and update module #%u failed!\n",
	                        downloadHeaderSt.pModuleIdList[cnt].module_id);
	                       
	                    break; /* break out to do some possible rollback */
	                }
	            }                
            }			
        }

        /* Check the global signature (SHA1), if failed, erase all modules! */
        if (LC_SUCCESS == result)
        {  
            result = LC_SHAFinal(&gGlobalSignatureController, hash);
        }
        //process to 70%
        info_type = UI_INFO_TYPE_PROCESS;
        info_size = sizeof(lc_uint16);
        info_value = 70;
        LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));
        if (LC_SUCCESS == result)
        {
            /** 
             * Make comparison between download_signature derived from download header and
             * the actual hash result on download data.
             */

            LC_LedDisplaySP0(CHAR_A);     //by keven
           
            /* Use hash to verify the download signature unconditionally. */
            result = LC_VerifySHASignature(
				(lc_uchar*)loaderEnhancedSecureKey,
                        gGlobalSignatureController.mode, 
                        downloadHeaderSt.download_signature, 
                        hash);
            if( LC_SUCCESS != result)
            {
                TRACE_LOG0(TRACE_ERROR, ("#[BLOADER] Error verifying Global signature!\n"));
                             
                uErrCode = ERROR_CODE_VERIFY_SIGNATURE;
            }
            else
            {
                TRACE_LOG0(TRACE_INFO, ("#[BLOADER] Global signature in download header verify OK!\n"));
            }
        }
    }
    //process to 80%
    info_type = UI_INFO_TYPE_PROCESS;
    info_size = sizeof(lc_uint16);
    info_value = 80;
    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));
    
	if (LC_TRUE == gFoundAcceptableUpdate)
	{
		if (LC_SUCCESS == result)
		{
			for(cnt = 0; cnt < downloadHeaderSt.number_of_modules; cnt++)
			{
                //Module UI update stage 3
                info_type = UI_INFO_TYPE_MODULE_INFO;
                info_size = sizeof(info_array);
                info_array[0]= UI_MODULE_DATA_UPDATE;
                info_array[1]= cnt+1;
                info_array[2]= downloadHeaderSt.number_of_modules;
                LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(info_array));
				/* Update this module. */
				if (LC_SUCCESS == result)
				{
					result = LC_CheckModuleVersion(
                            downloadHeaderSt.pModuleIdList[cnt].module_id,
                            downloadHeaderSt.pModuleIdList[cnt].module_version);  /* check the same module version to not update the module */
					if(LC_SUCCESS == result)  
					{
    					result = LC_UpdateModule(downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer,isAMankey);
    					if(LC_SUCCESS == result)
    					{
    						TRACE_LOG1(
    							TRACE_INFO, 
    							"&[BLOADER] Module #%u was succesfully updated.\n",
    							downloadHeaderSt.pModuleIdList[cnt].module_id);
    					}
    					else
    					{
    						TRACE_LOG1(
    							TRACE_ERROR, 
    							"&[BLOADER] Error: Module #%u was not succesfully updated!\n",
    							downloadHeaderSt.pModuleIdList[cnt].module_id);
    						break;
    					}
					}

#if 0
        			LC_Free_Memory((void **)&downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer->bytes);
        			LC_Free_Memory((void **)&downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer); 
#endif

					if(LC_ERROR_SAME_MODULE_VERSION == result)
					{
						result = LC_SUCCESS; /* the same modue version to continue next module update process */
					}
				}	
			}		
		}

#if 1
		for(cnt = 0; cnt < downloadHeaderSt.number_of_modules; cnt++)
		{
			LC_Free_Memory((void **)&downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer->bytes);
			LC_Free_Memory((void **)&downloadHeaderSt.pModuleIdList[cnt].moduleDataBuffer); 			
		}	
#endif
	}	

    /* Report Errorcode */        
    ERR_REPORT_SetErrorCode(uErrCode);

    /**
     * A special case, if the errcode is  "ERROR_CODE_SAME_SW_VERSION", we consider it a successful download 
     * and set result code to LC_SUCCESS. 
     */
    ERR_REPORT_GetErrorCode(&uErrCode, LC_NULL);
    
    /* For a successful migration, update variant module with the new one derived from Loader Partition. */
    if (LC_TRUE == gMigrationMode)
    {
        if (LC_SUCCESS == result) 
        {
            /* Update the existing variant module at the end of a successful migration.  */
            result = LC_UtilMigrationUpdateVariant();
            if (LC_SUCCESS == result)
            {     
                /* Ignore the error encountered. */
                ERR_REPORT_Initialize();
            }
            
        }
    }

    /* It is allowed for a Multi-module update that some (not all) of them have the same version as before. */
    if (ERROR_CODE_SAME_MODULE_VERSION == uErrCode)
    {
        if (LC_TRUE == gFoundAcceptableUpdate)
        {
            /* In the case of partial download, reset error code to ERROR_CODE_SUCCESS. */
            ERR_REPORT_Initialize();
        }

        /* Module(s) with same version can be regarded as a successful case. */
        result = LC_SUCCESS;
    }
    //process to 90%
    info_type = UI_INFO_TYPE_PROCESS;
    info_size = sizeof(lc_uint16);
    info_value = 90;
    LoaderCoreSPI_UPDATE_UI(info_type,info_size,(void*)(&info_value));

    /**
     * At last, save the download information into Loader Partition in case of 
     * detection on incomplete downloads next time.
     */
    if (LC_SUCCESS == result)
    {
        /* US 236855 download sequence number is not updated when key or Variant download */
        if (LC_DL_CLASS_KEY != gDownloadClass && 
            LC_DL_CLASS_VARIANT != gDownloadClass) 
        {
        	result = LC_StoreDownloadInformation(&lastDownloadPara);
        }
    }
    
    /* Free memory blocks. */
    MessageParser_FreeDPDownloadHeader(&downloadHeaderSt);    
   
    return result;
} 

static lc_result LC_DownloadAndUpdateModule(lc_uint16 moduleId,lc_buffer_st * dataBuffer)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_module_mh_st moduleHeaderSt;
    lc_uint32 cnt = 0;
    lc_uint32 crc32 = 0;
    lc_uint32 decryptLoopMax = 0;
    lc_uint32 actualModuleSize = 0;
    lc_sint32 decompStatus = 0;
    lc_uchar abBlock[AES_BLOCK_LEN];
    aes_key *pAesKey = LC_NULL;
    lc_uchar downloadType = NONE_DOWNLOAD;
    lc_buffer_st CompressedBufferbytes = {LC_NULL, 0};	
	
    downloadType = LC_UtilGetDownloadType();	
    LC_memset(&moduleHeaderSt, 0, sizeof(lc_module_mh_st));

    /* Try to read module_header */
    if (LC_SUCCESS == result)
    {
        result = LC_AcquireModuleHeader(moduleId, &moduleHeaderSt);
        if (LC_SUCCESS != result)
        {
            TRACE_LOG1(
                TRACE_ERROR, 
                "#[BLOADER] Error retrieving module header for module #%u\n",
                moduleId);
        }
        else
        {
            TRACE_LOG1(
                TRACE_INFO, 
                "#[BLOADER] Successfully retrieving module header for module #%u\n",
                moduleId);
        }
    }

    /* Check module size in module_header, if it exceeds the maximum memory size or equals ZERO, 
     * terminate this download and report failure */
    if (LC_SUCCESS == result)
    {
        if((moduleHeaderSt.block_size * moduleHeaderSt.block_count) == 0)
        {
            TRACE_LOG2(
                TRACE_ERROR, 
                "[BLOADER] Error: Module #%u is either too big or too small! module size = %u bytes\n",
                moduleId, moduleHeaderSt.block_size * moduleHeaderSt.block_count);
            errCode = ERROR_CODE_MH_MODULE_SIZE;
        }
    }

    /* Get the actual size of the module, depending on the compress field. */
    if (LC_SUCCESS == result)
    {
        if(moduleHeaderSt.compressed)   //
        {
            actualModuleSize = moduleHeaderSt.compressed_size + AES_BLOCK_LEN-
                (moduleHeaderSt.compressed_size % AES_BLOCK_LEN);

            /* Extra size for decompression */
            dataBuffer->length = moduleHeaderSt.original_size;
        }
        else
        {
            actualModuleSize = moduleHeaderSt.original_size + AES_BLOCK_LEN-
                (moduleHeaderSt.original_size % AES_BLOCK_LEN);

            dataBuffer->length = actualModuleSize;
        }
    }

    /* Allocate memory for one module data. */
    if (LC_SUCCESS == result)
    {
        dataBuffer->bytes = LC_MALLOC(dataBuffer->length + 1);
        if (LC_NULL == dataBuffer->bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    /* Try to read all the datagrams. */
    if (LC_SUCCESS == result)
    {
        result = LC_AcquireDatagrams(moduleId, &moduleHeaderSt, dataBuffer->bytes);
        if(LC_SUCCESS != result)
        {
            TRACE_LOG1(
                TRACE_ERROR, 
                "#[BLOADER] Error retrieving datagrams for module #%u\n",
                moduleId);
        }
    }
	
    /* Encryption and obscuration handling */
    if (LC_SUCCESS == result)
    {
        /* Assemble the datagrams, If neccesary decrypt and decompress */
        if(LC_TRUE == moduleHeaderSt.encrypted)
        {
            LC_LedDisplaySP0(CHAR_6);
                    
            TRACE_LOG1(
               TRACE_INFO, 
               "&[BLOADER] Decrypting encrypted module #%u\n",
               moduleId);

            pAesKey = LC_MALLOC(sizeof(aes_key));
            if (LC_NULL == pAesKey)
            {
                result = LC_ERROR_INSUFFICIENT_BUFFER;
            }

            if (LC_SUCCESS == result)
            {
                aes_setup(gAesKey, AES_KEY_LEN, 0, pAesKey);
                       
                decryptLoopMax = actualModuleSize / AES_BLOCK_LEN;
                for(cnt = 0; cnt < decryptLoopMax; cnt++)
                {
                    /* Decrypt a block */
                    aes_ecb_decrypt((lc_uchar*) dataBuffer->bytes + (AES_BLOCK_LEN * cnt), abBlock, pAesKey);
                           
                    /* Write the decrypted block back */
                    LC_memcpy((lc_uchar*) dataBuffer->bytes + (AES_BLOCK_LEN * cnt), abBlock, AES_BLOCK_LEN);
                    
                }
            }

            LC_Free_Memory((void **)&pAesKey);

            LC_LedDisplaySP0(CHAR_6);
			
        }
    }

    /* Compress handling */
    if (LC_SUCCESS == result)
    {
        if(moduleHeaderSt.compressed)
        {
            if (OTA_DOWNLOAD == downloadType)
            {
            	LC_GetSSUStreamData(&CompressedBufferbytes);  
                LC_memcpy(CompressedBufferbytes.bytes, (lc_uchar*)dataBuffer->bytes , actualModuleSize); 
            }
            if (SERIAL_DOWNLOAD == downloadType)
            {
                CompressedBufferbytes.bytes = LC_MALLOC(actualModuleSize + 1);
                if (LC_NULL == CompressedBufferbytes.bytes)
                {
                    result = LC_ERROR_INSUFFICIENT_BUFFER;
                }				

                LC_memcpy(CompressedBufferbytes.bytes, (lc_uchar*)dataBuffer->bytes, actualModuleSize);
            }
  			
            TRACE_LOG1(
                TRACE_INFO, 
                "&[BLOADER] Decompressing module #%u\n",
                moduleId);
        
            /* Check the CRC32 checksum of the compressed data first. */
            crc32 = CRC_Code32((void *)CompressedBufferbytes.bytes, moduleHeaderSt.compressed_size);   
			
            if(crc32 != moduleHeaderSt.crc32)
            {
                TRACE_LOG3(
                    TRACE_ERROR, 
                    "&[BLOADER] Error checking CRC32 on the compressed module #%u. Expected: 0x%08X; Actual: 0x%08X\n",
                    moduleId, crc32, moduleHeaderSt.crc32);
                errCode = ERROR_CODE_INVALID_MH_COMP_CRC;
                result = LC_ERROR_INVALID_DATA;
            }
			 
            /* If everything goes well, decompress the module data. */
            if (LC_SUCCESS == result)
            {
                LC_LedDisplaySP0(CHAR_7);
                
                decompStatus = DECOMP_Decompress(
                                    moduleHeaderSt.original_size,
                                    moduleHeaderSt.compressed_size,
                                    (lc_uchar*)CompressedBufferbytes.bytes,
                                    (lc_uchar*)dataBuffer->bytes);
				
                if(decompStatus != 0)
                {
                    TRACE_LOG2(
                        TRACE_ERROR, 
                        "&[BLOADER] ERROR: module #%u failed to decompress, %d\n",
                        moduleId, decompStatus);
                    errCode = ERROR_CODE_MODULE_DECOMP_FAIL;
                    result = LC_ERROR_INVALID_DATA;
                }

                LC_LedDisplaySP0(CHAR_7);
            }

        }
    }

    if (SERIAL_DOWNLOAD == downloadType && LC_TRUE == moduleHeaderSt.compressed)
    {
        LC_Free_Memory((void **)&CompressedBufferbytes.bytes);
    }
    /* Report Errorcode */
    ERR_REPORT_SetErrorCodeWithModuleId(errCode, &moduleId);
    return result;
}


static lc_result LC_AcquireDownloadHeader(lc_module_dlh_st *pDownloadHeader)
{

    lc_result result = LC_SUCCESS;
    lc_uint32 errCode =  ERROR_CODE_SUCCESS;
    lc_uint16 crc16 = 0;
    lc_buffer_st dlh = {LC_NULL, 0};
    lc_uint32 bitPos = 0;
    lc_sha_controller sha;  
    lc_uchar hashDLH[32];
    lc_uchar downloadType = NONE_DOWNLOAD;
    lc_uint32 cnt = 0;
    
    LC_memset(&sha, 0, sizeof(lc_sha_controller));
    LC_memset(hashDLH, 0, sizeof(hashDLH));
    

    LC_LedDisplay(LED_CHAR_NONE, CHAR_2, CHAR_BLNK, CHAR_BLNK );

    TRACE_LOG0(TRACE_INFO, ("#[BLOADER] Receiving Download Header...\n"));

    dlh.length = 0; /* Must be set by BLOADER_AcquireXXXPackage */
    dlh.bytes = (lc_uchar *)LC_MALLOC(DOWNLOADE_HEADER_MAX_SIZE);
    if (LC_NULL == dlh.bytes)
    {
        result = LC_ERROR_INSUFFICIENT_BUFFER;
    }

    if (LC_SUCCESS == result)
    {
        downloadType = LC_UtilGetDownloadType();
        TRACE_LOG1(TRACE_INFO, "#[BLOADER] downloadType = %d\n",downloadType );

        switch (downloadType)
        {
            case SERIAL_DOWNLOAD:
            {
                result = LC_AcquireUartPackage(UART_DLH_ID, &gSdlOffset, &dlh);
                break;
            }
            case OTA_DOWNLOAD:
            {
                result = LC_AcquireUpgradeDataFromSSUStream(UART_DLH_ID, &dlh);
                break;
            }
            default:
            {
                result = LC_FAILURE;
                errCode = ERROR_CODE_INVALID_LOADERPT;
                break;
            }
        }
    }
    
    /* Parse Download Header of Download Protocol */
    if (LC_SUCCESS == result)
    {
        TRACE_LOG0(TRACE_INFO, ("#[BLOADER] Parsing Download Header...\n"));
        result = MessageParser_ParseDPDownloadHeader(
                    &dlh,
                    &bitPos,
                    pDownloadHeader );
    }
    
    LoaderCoreSPI_UPDATE_UI(UI_INFO_TYPE_DSN,sizeof(lc_uint16),(void*)(&(pDownloadHeader->download_sequence_number)));

    /* Download header verification. */
    
    /* step 1: check CRC16 of download header */
    if (LC_SUCCESS == result)
    {                                                                  
        crc16 = CRC_16(
            &dlh.bytes[0], /* start from the beginning of Download_Header() */
            MODULE_DOWNLOAD_HEADER_STATIC_SIZE
            + (pDownloadHeader->number_of_modules * 4)
            + pDownloadHeader->header_signature_length
            + pDownloadHeader->download_signature_length );
    
        if(crc16 != pDownloadHeader->crc16)
        {
            errCode = ERROR_CODE_INVALID_DLH_CRC;
            result = LC_ERROR_INVALID_DATA;
        }
    }

    /* Go through module info list and check if this module type can be download */
    if (LC_SUCCESS == result)
    {
        for(cnt = 0; cnt < pDownloadHeader->number_of_modules; cnt++)
        {
            result = LC_UtilCheckModuleId(LC_UtilGetDownloadType(), pDownloadHeader->pModuleIdList[cnt].module_id);
            if (LC_SUCCESS != result)
            {
                ERR_REPORT_SetErrorCodeWithModuleId(ERROR_CODE_NOTUPDATEABLE_MODULE, &(pDownloadHeader->pModuleIdList[cnt].module_id));
                break;
            }

            /* Using RSA to verify signature or not depending on if this is a key download */
            if (MODULE_DRV_ID_UK == pDownloadHeader->pModuleIdList[cnt].module_id)
            {
               /*
                  * update UI stage info
                  */
                LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_UPDATING_KEY);
                gDownloadClass = LC_DL_CLASS_KEY;
            }

            /* variant update */
            if (MODULE_DRV_ID_VARIANT == pDownloadHeader->pModuleIdList[cnt].module_id)
            {
               /*
                  * update UI stage info
                  */
                LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_UPDATING_VARIANT);
                gDownloadClass = LC_DL_CLASS_VARIANT;
            }
        }
    }

    /**
     *  Step 2: Download header verification using header_signature (SHA1) 
     */  
    
    if(LC_SUCCESS == result)
    {
        result = LC_UtilCheckHashMode(
                        (LC_DL_CLASS_KEY == gDownloadClass)? LC_FALSE : LC_TRUE, 
                        pDownloadHeader->header_signature, 
                        &gGlobalSignatureController.mode);

        if (LC_SUCCESS != result || 
            PKCS_UNSUPPORT_MODE == gGlobalSignatureController.mode)
        {
            errCode = ERROR_CODE_VERIFY_SIGNATURE;
        }
	
    }

    /* Initialize controller for calculating global signature. */
    if (LC_SUCCESS == result)
    {
        result = LC_SHAInit(&gGlobalSignatureController);
    }

    /* Calculate download header signature. */
    if (LC_SUCCESS == result)
    {
        /* The hash mode used in every signature of a single download should be unique. */
        sha.mode = gGlobalSignatureController.mode;
        result = LC_SHAInit(&sha);
        
        if (LC_SUCCESS == result)
        {            
            /* calculate global hash (SHA1) */
            result = LC_SHAUpdate(
                            &sha,
                            dlh.bytes,
                            MODULE_DOWNLOAD_HEADER_STATIC_SIZE          /* start from manufacturer_id */
                            + (pDownloadHeader->number_of_modules * 4)  /* module_id and module_version */
                            - 2                                         /* header_signature_length */ 
                            - 2 );                                      /* download_signature_length */
        }
       
        if (LC_SUCCESS == result)
        {  
            result = LC_SHAFinal(&sha, hashDLH);
            if (LC_SUCCESS != result)
            {
                TRACE_LOG0(TRACE_ERROR, ("&[BLOADER] Error calculating hash for global signature!\n"));
            }
        }
        
    }
   
    if (LC_SUCCESS == result)
    {
		lc_uchar *pRsaKey = LC_NULL;
		lc_buffer_st uk = {LC_NULL, 0};
		if(LC_DL_CLASS_KEY != gDownloadClass)
		{
			result = LC_RetrieveUK(&uk.bytes, &uk.length);
			if (LC_SUCCESS == result)
			{
				pRsaKey = uk.bytes;
			}
		}
		else
		{
			pRsaKey = (lc_uchar*)loaderEnhancedSecureKey;
		}
        /**
         * Make comparison between header_signature derived from download header and
         * the actual hash result on download header.
         */
		if(LC_SUCCESS == result)
		{
        result = LC_VerifySHASignature(
				pRsaKey,
                    sha.mode, 
                    pDownloadHeader->header_signature, 
                    hashDLH);
		}
        if( LC_SUCCESS != result )
        {
            TRACE_LOG0(TRACE_ERROR, ("&[BLOADER] Error verifying global signature! Erasing all modules!!!\n"));               
            errCode = ERROR_CODE_VERIFY_SIGNATURE;
        }
        else
        {
            TRACE_LOG0(TRACE_INFO, ("&[BLOADER] Download header signature verify OK!\n"));
        }
		if(uk.bytes != LC_NULL)
		{
			LC_Free_Memory((void **)&uk.bytes);
    }
	}

    /* Process download header. */
    if (LC_SUCCESS == result)
    {
        result = LC_ProcessDownloadHeader(pDownloadHeader);
    }
  
   
    /** 
     * Calculate download signature, 
     * step 1:
     * Calculate hash value of Download_Header() [manufacutuer_id, header_signature]
     */
    if (LC_TRUE == gFoundAcceptableUpdate)
    {
        if (LC_SUCCESS == result)
        {
            result = LC_SHAUpdate(
                        &gGlobalSignatureController, 
                        dlh.bytes, 
                        MODULE_DOWNLOAD_HEADER_STATIC_SIZE              /* start from manufacturer_id */
                        + (pDownloadHeader->number_of_modules * 4)      /* module_id and module_version */
                        + (pDownloadHeader->header_signature_length)
                        - 2 );                                          /* download_signature_length */      
        }
    }

    LC_Free_Memory((void **)&dlh.bytes);

    /* Report Errorcode */
    ERR_REPORT_SetErrorCode(errCode);

    return result;   
} 



static lc_result LC_AcquireUartPackage(lc_uart_packet_type enData_id, lc_uint32 *pSdlOffset, lc_buffer_st* pbBuf)
{
    /* Delivery data format of serial dl:
        +----------------+----------------+----------------+
        |   S_DLH()      |   S_MH()       |   S_DG()       |
        |   {            |   {            |   {            |
        |     DataID;    |     DataID;    |     DataID;    |
        |     Length;    |     Length;    |     DG()       |
        |     DLH()      |     MH()       |     {          |
        |     {          |     {          |       Length;  |
        |       ...      |       ...      |       ...      |
        |     }          |     }          |     }          |
        |   }            |   }            |   }            |
        +----------------+----------------+----------------+ */

    lc_result result = LC_SUCCESS;
    lc_uint32 errCode =  ERROR_CODE_SUCCESS;
    lc_serial_download_packet sdp;
    lc_uint32 offset = *pSdlOffset;
    lc_uchar uartBuffer[4];


    LC_memset(&sdp, 0, sizeof(lc_serial_download_packet));
    LC_memset(uartBuffer, 0, sizeof(uartBuffer));
    /* Get Data ID. */
    result = LC_TemuDataRequest(&sdp.data_id, 1, offset, UART_DL_ATTEMPT_MAX);
    if (LC_SUCCESS == result)
    {
        offset += 1;

        if( sdp.data_id != enData_id )
        {
            result = LC_FAILURE;
            
            switch( enData_id )
            {
                case UART_DLH_ID: /* Download Header */
                    TRACE_LOG0(TRACE_ERROR, ("[BLOADER] Error: Download Header data_id error!\n"));
                    errCode = ERROR_CODE_INVALID_DLH_ID;
                    break;

                case UART_MH_ID: /* Module Header */
                    TRACE_LOG0(TRACE_ERROR, ("[BLOADER] ERROR: Module Header data_id error.\n"));
                    errCode = ERROR_CODE_INVALID_MH_ID;
                    break;

                case UART_DG_ID: /* Datagram */
                    TRACE_LOG0(TRACE_ERROR, ("[BLOADER] ERROR: Datagram data_id error.\n"));
                    errCode = ERROR_CODE_INVALID_DG_ID;
                    break;
            }
        }
    }

    /* Get length. */
    if (LC_SUCCESS == result)
    {
        if( enData_id != UART_DG_ID )
        {
            result = LC_TemuDataRequest(uartBuffer, 2, offset, UART_DL_ATTEMPT_MAX);
            if (LC_SUCCESS == result)
            {
                /* The length in Serial_Download_Header() and Serial_Module_Header()
                 * just indicates the length of "Download_header()/Module_header()".
                 */
                sdp.length  = (lc_uint32)((lc_uint32)uartBuffer[0] << 8);
                sdp.length |= (lc_uint32)uartBuffer[1];
               
                offset += 2;
            }
        }
        else
        {
            result = LC_TemuDataRequest( pbBuf->bytes, 4, offset, UART_DL_ATTEMPT_MAX);    //
            if (LC_SUCCESS == result)
            {
                /* 
                 * This data_length in datagram() just indicates the length of "data".
                 */
                sdp.length  = (lc_uint32)((lc_uint16)pbBuf->bytes[2] << 8);
                sdp.length |= (lc_uint32)pbBuf->bytes[3];

                offset += 4;

                TRACE_LOG1(TRACE_DEBUG, "[BLOADER] DG length = %u\n", sdp.length);
                sdp.length += 2;    /* length of CRC16 from datagram() */
            }
        }

        if( sdp.length == 0 )
        {
            result = LC_FAILURE;
            
            switch( enData_id )
            {
                case UART_DLH_ID: /* Download Header */
                    TRACE_LOG0(TRACE_DEBUG, ("[BLOADER] ERROR: DLH length error.\n"));
                    errCode = ERROR_CODE_INVALID_DLH_SIZE;
                    break;

                case UART_MH_ID: /* Module Header */
                    TRACE_LOG0(TRACE_DEBUG, ("[BLOADER] ERROR: PH length error.\n"));
                    errCode = ERROR_CODE_INVALID_MH_SIZE;
                    break;

                case UART_DG_ID: /* Datagram */
                    TRACE_LOG0(TRACE_DEBUG, ("[BLOADER] ERROR: DG length error.\n"));
                    errCode = ERROR_CODE_DATAGRAM_SIZE;
                    break;
            }
        }
    }

    /* Get payload. */
    if (LC_SUCCESS == result)
    {
        if( enData_id != UART_DG_ID )
        {
            result = LC_TemuDataRequest(pbBuf->bytes, sdp.length, offset, UART_DL_ATTEMPT_MAX);
            if (LC_SUCCESS == result)
            {
                offset += sdp.length;
            }
        }
        else
        {
            result = LC_TemuDataRequest((pbBuf->bytes + 4), sdp.length, offset, UART_DL_ATTEMPT_MAX);    // id -length -data
            if (LC_SUCCESS == result)
            {
                offset += sdp.length;
                sdp.length += 4;    /* sum size of module_id and data_length */
            }
           
        }
    }

    /** 
     * Return length of download protocol packet(payload of Serial_xxxx()).
     * for download header and module header, sdp.length = Download_header/Module_header();
     * for datagram, sdp.length = Datagram().
     */
    if (LC_SUCCESS == result)
    {
        pbBuf->length = sdp.length;
        *pSdlOffset = offset;
    }

    ERR_REPORT_SetErrorCode(errCode);
    
    return result;

} 


static lc_result LC_AcquireModuleHeader(lc_uint16 moduleId, lc_module_mh_st *pDPModuleHeader)
{

    lc_result result = LC_SUCCESS;
    lc_uint32 errCode =  ERROR_CODE_SUCCESS;
    lc_uint32 bitPos = 0;
    lc_buffer_st mh = {LC_NULL, 0};
    lc_uint16 crc16 = 0;
    lc_uchar downloadType = NONE_DOWNLOAD;
    lc_uchar moduleHeaderBuffer[32];

    mh.bytes = (lc_uchar *)moduleHeaderBuffer;
    LC_memset(moduleHeaderBuffer, 0, sizeof(moduleHeaderBuffer));

    LC_LedDisplay(LED_CHAR_NONE, CHAR_3, CHAR_BLNK, CHAR_BLNK );
    TRACE_LOG1(TRACE_INFO, "#[BLOADER] Receiving Module Header - #%u ...\n", moduleId);

    downloadType = LC_UtilGetDownloadType();
    if(SERIAL_DOWNLOAD == downloadType)
    {
        result = LC_AcquireUartPackage(UART_MH_ID, &gSdlOffset, &mh);
    }
    else if (OTA_DOWNLOAD == downloadType)
    { 
        result = LC_AcquireUpgradeDataFromSSUStream(UART_MH_ID, &mh);      
    }
    else
    {
        LC_ASSERT(0);
    }

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(TRACE_INFO, "#[BLOADER] Parsing Module Header - #%u ...\n", moduleId);
        
        result = MessageParser_ParseDPModuleHeader(
                                &mh,
                                &bitPos,
                                pDPModuleHeader);
    }
   

    /* Verification procedure start ---> */

    /* step x: check CRC16 of module header */
    if (LC_SUCCESS == result)
    {
        crc16 = CRC_16(
                    mh.bytes, /* start from the beginning of Download_Header() */
                    mh.length
                    - 2 );      /* crc16 (2 bytes) */

        if(crc16 != pDPModuleHeader->crc16)
        {
            TRACE_LOG1(TRACE_ERROR, "&[BLOADER] Error checking CRC16 for Module Header - #%u.\n", moduleId);
            errCode = ERROR_CODE_INVALID_MH_CRC;
            result = LC_ERROR_INVALID_DATA;
        }
    }

    /* Verification procedure end <--- */

    /* Report Errorcode */
    ERR_REPORT_SetErrorCodeWithModuleId(errCode, &pDPModuleHeader->module_id);

    return result;

} 

static lc_result LC_AcquireDatagrams(
    lc_uint16 moduleId, 
    const lc_module_mh_st *pModuleHeader, 
    lc_uchar *pModuleDataByte)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint16 cnt = 0;
    lc_buffer_st dg = {LC_NULL, 0};
    lc_module_dg_st dg_st;
    lc_uint32 bitpos = 0;
    lc_uint16 crc16 = 0;
    lc_uchar downloadType = NONE_DOWNLOAD;
    const lc_front_panel_char dispDatagrams[2] = {CHAR_4dot, CHAR_4};

    LC_memset(&dg_st, 0, sizeof(lc_module_dg_st));

    /* Display module ID. */
    LC_LedDisplay(
        LED_CHAR_NONE, 
        (lc_uchar)(moduleId >> 12) & 0x0F, 
        (lc_uchar)(moduleId >> 8) & 0x0F, 
        CHAR_BLNK );

    LC_LedDisplay(
        LED_CHAR_NONE, 
        (lc_uchar)(moduleId >> 4) & 0x0F, 
        (lc_uchar)(moduleId >> 0) & 0x0F, 
        CHAR_BLNK );
        
    TRACE_LOG1(TRACE_INFO, "#[BLOADER] Acquiring datagrams for module #%u:\n", moduleId);
    

    downloadType = LC_UtilGetDownloadType();

    if (LC_SUCCESS == result)
    {
        dg.bytes = LC_MALLOC(DG_BUF_SIZE_MAX);
        if (LC_NULL == dg.bytes)
        {
            result = LC_ERROR_INSUFFICIENT_BUFFER;
        }
    }

    /* Get datagrams. */
    for( cnt = 0; (cnt < pModuleHeader->block_count) && (LC_SUCCESS == result); )
    {
        /* Display for odd/even datagram numbers. */
        LC_LedDisplay(LED_CHAR_NONE, dispDatagrams[cnt % 2], CHAR_BLNK, CHAR_BLNK );
        
        /* Get datagrams from specific transmission channels. */
        switch (downloadType)
        {
            
            case SERIAL_DOWNLOAD:
            {
                /* Get datagram. */
                result = LC_AcquireUartPackage(UART_DG_ID, &gSdlOffset, &dg);
                break;
            }

            case OTA_DOWNLOAD:
            {
            
                result = LC_AcquireUpgradeDataFromSSUStream(UART_DG_ID, &dg);

                break;
            }

            default:
            {
                result = LC_ERROR_INVALID_PARAMETER;
                break;
            }
        }

        /* Check datagram length, if it is larger than block size, it should invalid. */
        if (LC_SUCCESS == result)
        {
            if ((dg.length - 2 - 4) > (lc_uint32)(pModuleHeader->block_size))
            {
                errCode = ERROR_CODE_DATAGRAM_SIZE;
            }
        }

        /* Parse datagram */
        if (LC_SUCCESS == result)
        {
            bitpos = 0;
            result = MessageParser_ParseDPDatagram(&dg, &bitpos, &dg_st);
            if (LC_SUCCESS != result)
            {
                errCode = ERROR_CODE_DATAGRAM_CONTENT;
            }
        }

        /* Check crc16. */
        if (LC_SUCCESS == result)
        {
            /* calculate crc16 and perform checksum verification. [module_id, data] */
            crc16 = CRC_16(dg.bytes, (2 + 2 + dg_st.data_length));

            if (crc16 != dg_st.crc16)
            {
                result = LC_ERROR_INVALID_DATA;
                errCode = ERROR_CODE_INVALID_DG_CRC;
            }
        }

        /* Is this an datagram that belongs to us? ETHAN_NOTE: replaced by filter? */
        if (LC_SUCCESS == result)
        {
            if(dg_st.module_id != moduleId)
            {
                result = LC_ERROR_INVALID_DATA;
                errCode = ERROR_CODE_DATAGRAM_CONTENT;
            }
        }

        /* Copy datagram payload into a continuous fix-sized buffer one by one. */
        if (LC_SUCCESS == result)
        {
            LC_memcpy(
                ((lc_uchar*)pModuleDataByte) + (cnt * pModuleHeader->block_size),
                dg_st.data_byte,
                dg_st.data_length );
        }

        if (LC_SUCCESS == result)
        {
            cnt++;
        }
                  
    }

    LC_Free_Memory((void **)&dg.bytes);

    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(TRACE_DEBUG, "&[BLOADER] Acquired all DGs of Module #%u.\n", moduleId);
    }

    ERR_REPORT_SetErrorCode(errCode);
    
    return result;
   
} 


static lc_result LC_CheckUartConnection(lc_bool setError)
{
    lc_result result = LC_SUCCESS;

    result = LC_TemuStart();
    if(LC_TRUE == setError)
    {
        if (LC_SUCCESS != result)
        {
            ERR_REPORT_SetErrorCode(ERROR_CODE_UART_TIMEOUT);
        }
    }

    return result;
}


static lc_result LC_ProcessDownloadHeader(const lc_module_dlh_st *pDownloadHeaderSt)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_uint32 cnt = 0;
    lc_bool acceptableUpdate = LC_FALSE;
    lc_uint16 deviceDownloadSequence = 0;
    lc_uchar psModifyFlag = 0;

    /* step 1: check if manufacturer_id matched */
    if (LC_SUCCESS == result)
    {
        result = LC_UtilCheckManufacturerId(pDownloadHeaderSt->manufacturer_id);
        if (LC_SUCCESS != result)
        {
            errCode = ERROR_CODE_DLH_MAN_ID_NE;
        }
    }

    /* step 2: check if hardware_version matched */
    if (LC_SUCCESS == result)
    {
        result = LC_UtilCheckHardwareVersion(pDownloadHeaderSt->hardware_version);
        if (LC_SUCCESS != result)
        {
            errCode = ERROR_CODE_DLH_HW_VER_NE;
        }
    }

    /* ISIGN version and SN must be printable! */
    if (LC_SUCCESS == result)
    {
        if (LC_TRUE != LC_UtilIsStringPrintable(
                        pDownloadHeaderSt->isign_version, 
                        sizeof(pDownloadHeaderSt->isign_version)))
        {
            result = LC_ERROR_INVALID_DATA;
            errCode = ERROR_CODE_ISIGN_VER_NPCHARS;
        }
        
        if (LC_TRUE != LC_UtilIsStringPrintable(
                        pDownloadHeaderSt->isign_serial_number, 
                        sizeof(pDownloadHeaderSt->isign_serial_number)))
        {
            result = LC_ERROR_INVALID_DATA;
            errCode = ERROR_CODE_ISIGN_SN_NPCHARS;
        }
    }


    /* We need to check download sequence number, 
     * if the download one is NOT SMALLER than the local one, that is valid. */

    if (LC_SUCCESS == result)
    {
        if (LC_DL_CLASS_KEY != gDownloadClass && 
            LC_DL_CLASS_VARIANT != gDownloadClass && 
            LC_FALSE == gMigrationMode)
        {
            result = LC_UtilGetDownloadSequence(&deviceDownloadSequence);
            if (LC_SUCCESS == result)
            {
                result = LC_CheckDownloadSequence(
                            pDownloadHeaderSt->download_sequence_number, 
                            deviceDownloadSequence);
            }

            if (LC_ERROR_INCORRECT_DOWNLOAD_SEQUENCE_NUMBER == result)
            {
                TRACE_LOG0(TRACE_ERROR, ("&[BLOADER] Error: Old download, rejected!\n"));
                errCode = ERROR_CODE_INCORRECT_DOWNLOAD_SEQUENCE_NUMBER;
            }
            else if (LC_ERROR_SAME_DOWNLOAD_SEQUENCE_NUMBER == result)
            {
            	LoaderCoreSPI_GetPSModifyFlag(&psModifyFlag);
				if(PS_MODIFIED == psModifyFlag)    /*  Psmodify trigger loader and avoid the DSN same check*/
				{
                	result = LC_SUCCESS;
					errCode = ERROR_CODE_SUCCESS;					
				}
				else
            	{					
                	TRACE_LOG0(TRACE_ERROR, ("&[BLOADER] Error: Same download, rejected!\n"));
                	errCode = ERROR_CODE_SAME_DOWNLOAD_SEQUENCE_NUMBER;
                }					
            }
        }
       
    }

    /* Go through module info list and check module version. */
    if (LC_SUCCESS == result)
    {
        /* Not a key download and not in migration status, it is required to check module version. */
        if (LC_DL_CLASS_KEY != gDownloadClass && 
            LC_DL_CLASS_VARIANT != gDownloadClass && 
            LC_FALSE == gMigrationMode)
        {                    
            for(cnt = 0; cnt < pDownloadHeaderSt->number_of_modules; cnt++)
            {
                result = LC_CheckModuleVersion(
                            pDownloadHeaderSt->pModuleIdList[cnt].module_id,
                            pDownloadHeaderSt->pModuleIdList[cnt].module_version);
                                    
                if (LC_ERROR_SAME_MODULE_VERSION == result)
                {
					/**
					 * A special case, if the errcode is  "ERROR_CODE_SAME_SW_VERSION", and psmodify trigger the loader,  we ignore ERROR_CODE_SAME_SW_VERSION 
					 * and set result code to SUCCESS. 
					 */
					LoaderCoreSPI_GetPSModifyFlag(&psModifyFlag);  /* PS modify to recovery ignore the same error */
					if (PS_UNMODIFIED == psModifyFlag)
					{
						ERR_REPORT_SetErrorCodeWithModuleId(
							ERROR_CODE_SAME_MODULE_VERSION, 
							&pDownloadHeaderSt->pModuleIdList[cnt].module_id);
					}
                }
                else if (LC_ERROR_INCORRECT_MODULE_VERSION == result)
                {
                    ERR_REPORT_SetErrorCodeWithModuleId(
                        ERROR_CODE_INCORRECT_MODULE_VERSION, 
                        &pDownloadHeaderSt->pModuleIdList[cnt].module_id);
                                
                    break;
                }
                else
                {
                    /**
                     * A module needs to be updated in such cases below:
                     *      1. exist, need update to higher version.
                     *      2. not found, need update for totally new module.
                     *      3. exist but corrupted, need to be recovered.
                     */
                    acceptableUpdate = LC_TRUE;
                }
            }

            if (LC_ERROR_INCORRECT_MODULE_VERSION != result)
            {
                result = LC_SUCCESS;
            }
        }    
        else
        {
            acceptableUpdate = LC_TRUE;
        }

    }

    /* if not key download, loader should check if variant matched.
     * In other words, other modules except UK and variant should care
     * about variant at first.
     */
    if (LC_SUCCESS == result)
    {
        /* If this is an UART download allow the variant to be ignored, thus
         * make it posible to update it.
         */
        if(LC_DL_CLASS_KEY != gDownloadClass && 
           LC_DL_CLASS_VARIANT != gDownloadClass) /* pay attention!!! */
        { 
            result = LC_UtilCheckVariant(
                        gMigrationMode, 
                        &pDownloadHeaderSt->variant, 
                        &pDownloadHeaderSt->sub_variant);
            if (LC_ERROR_INVALID_VARIANT_VALUE == result)
            {
                errCode = ERROR_CODE_INVALID_VARIANT;
            }
            else if (LC_ERROR_INVALID_SUBVARIANT_VALUE == result)
            {
                errCode = ERROR_CODE_INVALID_SUBVARIANT;
            }
        }
    }

    if (LC_SUCCESS == result)
    {
        gFoundAcceptableUpdate = acceptableUpdate;
    }

    /* Report Errorcode */
    ERR_REPORT_SetErrorCode(errCode);

    return result;
}

static lc_result LC_CheckModule(const lc_buffer_st *pModuleByte,lc_bool *isMankeyDownload)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_buffer_st mihNew_byte = {LC_NULL, 0};
    lc_module_info_header mihNew_st;
    lc_buffer_st byteModulePayload = {LC_NULL, 0};
    lc_uint32 bitpos = 0;
    lc_uint32 crc32 = 0;
    lc_buffer_st uk = {LC_NULL, 0};
    lc_bool isAMankeyUpdate = LC_FALSE;
    lc_checksum_algorithm_status status = {LC_BOOTCHECK_MIN_RESERVED, LC_NULL};
    lc_uchar psModifyFlag = 0;

    mihNew_byte.bytes = pModuleByte->bytes;
    mihNew_byte.length = pModuleByte->length;
    LC_memset(&mihNew_st, 0, sizeof(lc_module_info_header));

    /* Start data verification. */
    LC_LedDisplay(LED_CHAR_NONE, CHAR_8, CHAR_BLNK, CHAR_BLNK );

    /** <Parse> */
    
    /* Parse new incoming module message */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ParseModuleInfoHeader(
                    LC_TRUE,
                    &mihNew_byte, 
                    &bitpos, 
                    &mihNew_st);
        if (LC_SUCCESS != result)
        {
            if (LC_ERROR_INCORRECT_SIGNATURE_LENGTH == result)
            {
                errCode = ERROR_CODE_INVALID_SIG_LENGTH;
            }
            else
            {
                errCode = ERROR_CODE_INCORRECT_MODULE_INFO_HEADER;
            }
        }
        else
        {
            /* Check module length */
            LC_ASSERT((mihNew_st.header_length + mihNew_st.module_size) <= mihNew_byte.length);
        }
    }

    /* Check crc32 */
    if (LC_SUCCESS == result)
    {
        if (0 == mihNew_st.crc32)
        {
            result = LC_ERROR_INVALID_DATA;
        }
        else
        {
            crc32 = CRC_Code32(mihNew_byte.bytes, (mihNew_st.header_length - 4));
            if ((crc32 != mihNew_st.crc32))
            {
                result = LC_ERROR_INVALID_DATA;
            }
			
        }

        if (LC_SUCCESS != result)
        {
            ERR_REPORT_SetErrorCodeWithModuleId(ERROR_CODE_INVALID_MODULE_INFO_HEADER_CRC, &mihNew_st.module_id);
        }
    }

    /** <Calculate Global Signature> */
    
    /** 
     * step 2
     * Calculate global hash of the entire module, include module_info_header and module payload.
     */
    if (LC_SUCCESS == result)
    {      
        result = LC_SHAUpdate(
                    &gGlobalSignatureController,
                    mihNew_byte.bytes,
                    mihNew_st.header_length + mihNew_st.module_size);
    }

    /** <Check> */

    /* Verify this new module. */
    
    if (LC_SUCCESS == result)
    {
        byteModulePayload.bytes = &mihNew_byte.bytes[mihNew_st.header_length];
        byteModulePayload.length = mihNew_st.module_size;
    }

    
    if (LC_SUCCESS == result)
    {
        /* PKCS1 */
        status.algorithm = LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION;
        
        if (LC_DL_CLASS_KEY != gDownloadClass)
        {
            /* Get UK for RSA authentication(not necessary for UK module itself) */
            result = LC_RetrieveUK(&uk.bytes, &uk.length);
            if (LC_SUCCESS != result)
            {
                TRACE_LOG1(
                    TRACE_ERROR, 
                    "&[BLOADER] Error loading UK on updating module #%u!\n", 
                    mihNew_st.module_id);
            }

            if (LC_SUCCESS == result)
            {
                /* Use RSASSA_PKCS1_V1_5 to verify signature signed by Irdeto's signing tool. */   
                status.pRsaKey = uk.bytes;
            }
#ifdef ALI_IRD_DEBUG
            TRACE_LOG0(TRACE_ERROR, ("&[BLOADER] DUMP the UK!\n"));
            lc_data_dump(uk.bytes,uk.length);
#endif
        }
        else
        {
			status.pRsaKey = (lc_uchar*)loaderEnhancedSecureKey;
        }

        
    }
    
    /*
      * update UI stage info
      */
    LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_VERIFYING_SIG);

    /* step 1. Verify the module header using module_header_signature */
    if (LC_SUCCESS == result)
    {
        result = LC_VerifyModuleInfoHeaderSignature(&status, &mihNew_byte, &mihNew_st);
        if (LC_SUCCESS != result)
        {
            errCode = ERROR_CODE_VERIFY_SIGNATURE;
        }
    }

    /* step 2. Verify the module payload using module_signature_data */
    if (LC_SUCCESS == result)
    {
        result = LC_VerifySignature(
                    &status,
                    byteModulePayload.bytes, 
                    byteModulePayload.length, 
                    mihNew_st.module_signature);
        if ( LC_SUCCESS != result )
        {
            TRACE_LOG1(
                TRACE_ERROR, 
                "&[BLOADER] Error verifying New module #%u's payload!\n", 
                mihNew_st.module_id);

            errCode = ERROR_CODE_VERIFY_SIGNATURE;
        }
    }

    /* None of BBCB, Loader Partition and Loader Core can be updated. */
    if (LC_SUCCESS == result)
    {
        result = LC_UtilCheckModuleId(LC_UtilGetDownloadType(), mihNew_st.module_id);
        if (LC_SUCCESS != result)
        {
            errCode = ERROR_CODE_NOTUPDATEABLE_MODULE;
        }

        if (LC_SUCCESS == result)
        {
            if (MODULE_DRV_ID_UK == mihNew_st.module_id)
            {
                if (LC_DL_CLASS_KEY != gDownloadClass)
                {
                    errCode = ERROR_CODE_INCORRECT_MODULE_INFO_HEADER;
                }
            }

            if (MODULE_DRV_ID_VARIANT == mihNew_st.module_id)
            {
                if (LC_DL_CLASS_VARIANT != gDownloadClass)
                {
                    errCode = ERROR_CODE_INCORRECT_MODULE_INFO_HEADER;
                }
            }
        }
    }

    /* Check memory type. */
    if (LC_SUCCESS == result)
    {
        /* UK and variant must be saved into NVRAM! */
        if (LC_DL_CLASS_KEY == gDownloadClass ||
            LC_DL_CLASS_VARIANT == gDownloadClass )
        {
            if (MOD_MEM_TYPE_NVRAM != mihNew_st.memory_type)
            {
                result = LC_ERROR_INVALID_DATA;
                errCode = ERROR_CODE_INCORRECT_MEMORY_TYPE;
            }
        }
    }
    

    /* Is this a key download, if yes, then this is a special case. And 
     * All modules stored that is validated using the old key need to 
     * be removed and updated, either in an later update or in this.
     */

    /* Not a key download and not in migration status, it is required to check module version. */
    if (LC_SUCCESS == result)
    {
        if (LC_DL_CLASS_KEY != gDownloadClass && 
            LC_DL_CLASS_VARIANT != gDownloadClass && 
            LC_FALSE == gMigrationMode)
        {
            result = LC_CheckModuleVersion(
                        mihNew_st.module_id, 
                        mihNew_st.module_version);
                            
            if (LC_SUCCESS != result)
            {
                if (LC_ERROR_INCORRECT_MODULE_VERSION == result)
                {
                    errCode= ERROR_CODE_INCORRECT_MODULE_VERSION;
                }
                else if (LC_ERROR_SAME_MODULE_VERSION == result)
                {
                    errCode = ERROR_CODE_SAME_MODULE_VERSION;
                }
                else
                {
                    /**
                     * A module needs to be updated in such cases below:
                     *      1. exist, need update to higher version.
                     *      2. not found, need update for totally new module.
                     *      3. exist but corrupted, need to be recovered.
                     */
                    result = LC_SUCCESS;
                }
            }
        }
 
    }

    /* For a UK module, it must be authenticated first! */
    if (LC_SUCCESS == result)
    {
        if(LC_DL_CLASS_KEY == gDownloadClass)
        {
            TRACE_LOG2(
                TRACE_DEBUG, 
                "[BLOADER] KEYUPD_useMg -- headerlen %u datalen %u\n", 
                mihNew_st.header_length , 
                mihNew_st.module_size);
                            
            /* UK authentication */
            result = LC_AuthenticateUK(
                            byteModulePayload.bytes, 
                            byteModulePayload.length, 
                            &isAMankeyUpdate);
			*isMankeyDownload = isAMankeyUpdate;
            if ( LC_SUCCESS != result)
            {
                TRACE_LOG0(TRACE_ERROR, ("&[BLOADER] Error updating Key module!\n"));
            }
        }
    }

    /**
     * For a non-Manufacturer Key update, we should check if the variant & sub-variant are matched with those in this device.
     * The variant refers to the one derived from module_info_header of UK module. 
     */ 
    if (LC_SUCCESS == result)
    {
        /* For development key download, customer key download, and data module download, 
         * variant & sub_variant should equal to the one stored in this device.
         */
        if ((LC_TRUE != isAMankeyUpdate) && (LC_DL_CLASS_VARIANT != gDownloadClass))
        {
            result = LC_UtilCheckVariant(gMigrationMode, &mihNew_st.variant, &mihNew_st.sub_variant);
            if (LC_ERROR_INVALID_VARIANT_VALUE == result)
            {
                errCode = ERROR_CODE_INVALID_VARIANT;
            }
            else if (LC_ERROR_INVALID_SUBVARIANT_VALUE == result)
            {
                errCode = ERROR_CODE_INVALID_SUBVARIANT;
            }
        }
    }    

    /* clear memory blocks */
    LC_Free_Memory((void **)&uk.bytes);
    MessageParser_FreeModuleInfoHeader(&mihNew_st);

    /**
    * A special case, if the errcode is  "ERROR_CODE_SAME_SW_VERSION", and psmodify trigger the loader,  we ignore ERROR_CODE_SAME_SW_VERSION 
    * and set result code to SUCCESS. 
    */
    LoaderCoreSPI_GetPSModifyFlag(&psModifyFlag);  /* PS modify to recovery ignore the same error */
    if (PS_MODIFIED == psModifyFlag) 
	{
		if(ERROR_CODE_SAME_MODULE_VERSION != errCode)
		{
    		ERR_REPORT_SetErrorCodeWithModuleId(errCode, &mihNew_st.module_id);
		}
	}
	else
	{
    	ERR_REPORT_SetErrorCodeWithModuleId(errCode, &mihNew_st.module_id);
	}

    return result;
}

static lc_result LC_UpdateModule(const lc_buffer_st *pModuleByte,lc_bool isAMankeyUpdate)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 errCode = ERROR_CODE_SUCCESS;
    lc_buffer_st mihNew_byte = {LC_NULL, 0};
    lc_module_info_header mihNew_st;
    lc_buffer_st byteModulePayload = {LC_NULL, 0};
    lc_uint32 bitpos = 0;
    lc_uint32 crc32 = 0;
    lc_buffer_st uk = {LC_NULL, 0};
    lc_checksum_algorithm_status status = {LC_BOOTCHECK_MIN_RESERVED, LC_NULL};

    mihNew_byte.bytes = pModuleByte->bytes;
    mihNew_byte.length = pModuleByte->length;
    LC_memset(&mihNew_st, 0, sizeof(lc_module_info_header));


    /** <Parse> */
    
    /* Parse new incoming module message */
    if (LC_SUCCESS == result)
    {
        result = MessageParser_ParseModuleInfoHeader(
                    LC_TRUE,
                    &mihNew_byte, 
                    &bitpos, 
                    &mihNew_st);
        if (LC_SUCCESS != result)
        {
            if (LC_ERROR_INCORRECT_SIGNATURE_LENGTH == result)
            {
                errCode = ERROR_CODE_INVALID_SIG_LENGTH;
            }
            else
            {
                errCode = ERROR_CODE_INCORRECT_MODULE_INFO_HEADER;
            }
        }
        else
        {
            /* Check module length */
            LC_ASSERT((mihNew_st.header_length + mihNew_st.module_size) <= mihNew_byte.length);
        }
    }

    if (LC_SUCCESS == result)
    {
        byteModulePayload.bytes = &mihNew_byte.bytes[mihNew_st.header_length];
        byteModulePayload.length = mihNew_st.module_size;
    }



    /** <Update> */
    
    /* For a variant module, it must be encrypted first! */
    if (LC_SUCCESS == result)
    {
        if(LC_DL_CLASS_VARIANT == gDownloadClass)
        {
            lc_uchar clearVariant[4];
            
            TRACE_LOG0(TRACE_DEBUG, ("#[BLOADER] Encrypt variant before saving.\n"));
            
            /* backup the original one (clear) */
            LC_memcpy(
                clearVariant, 
                byteModulePayload.bytes, 
                sizeof(clearVariant));
                
            /* encrypt and replace the field in variant module */
            result = LC_CryptModule(
                        LC_TRUE,
                        byteModulePayload.bytes, 
                        clearVariant, 
                        sizeof(clearVariant));
        }
    }

    /**
     * Signature replacement.
     * a. For variant update, the two signatures (also signature length) in 
     * variant module_info_header should be replaced by CRC32 UNCODITIONALLY! 
     * b. For other module's update the replacement may vary depending on the 
     * algorithm supported by this device. 
    */
    if (LC_SUCCESS == result)
    {
        result = LC_UpdateModuleSignature(LC_UtilGetBootcheckAlgorithm(), &mihNew_byte, &mihNew_st);
    }


    /** <Save> */

    /* Set PS modify flag to "modified" status. */
    if (LC_SUCCESS == result)
    {
        if(LC_DL_CLASS_CODE == gDownloadClass)
        {
            result = LoaderCoreSPI_SetPSModifyFlag(PS_MODIFIED);
        }
    }

    
    /* Erase old module(s) */
    if (LC_SUCCESS == result)
    {
        if (MOD_MEM_TYPE_FLASH == mihNew_st.memory_type)
        {
            LC_LedDisplay(LED_CHAR_NONE, CHAR_9, CHAR_BLNK, CHAR_BLNK );			
        }

        if(LC_SUCCESS == result)
		{
			result = LoaderCoreSPI_Module_Delete(mihNew_st.module_id);
		}
                
        if(LC_SUCCESS != result)
		{
        	TRACE_LOG1(
                    TRACE_ERROR, 
                    "&[BLOADER] Error erasing module(s) on updating module #%u\n", 
                    mihNew_st.module_id);
                    
	        errCode = ERROR_CODE_MODIFY_MODULE;
        }		
        
        /* If this is a key download, go through all modules, and erase them. */
        if(LC_DL_CLASS_KEY == gDownloadClass)
        {
            if( LC_SUCCESS != result)
            {
                TRACE_LOG1(
                    TRACE_ERROR, 
                    "&[BLOADER] Error erasing module(s) on updating module #%u\n", 
                    mihNew_st.module_id);
                    
                errCode = ERROR_CODE_MODIFY_MODULE;
            }
        }
    }

    /** 
     * For a Manufacturer Key update, we should also update variant & sub-variant at the same time,
     * Where the value comes from the module_info_header of UK module. 
     */
    if (LC_SUCCESS == result)
    {
        if((LC_DL_CLASS_KEY == gDownloadClass) && (LC_TRUE == isAMankeyUpdate))
        {
            /* Create default variant module. */
            result = LC_SetVariant(LC_TRUE, &mihNew_st.variant, &mihNew_st.sub_variant);
        }
    }
    
    /* Update module NOW! */
    if (LC_SUCCESS == result)
    {
        if (MOD_MEM_TYPE_FLASH == mihNew_st.memory_type)
        {
            LC_LedDisplaySP0(CHAR_F);
        }
        
        /*
          * update UI stage info
          */
        LoaderCoreSPI_UpdateUIStageInfo(UI_STAGES_WRITING_DATA_TO_FLASH);
        
        mihNew_byte.length = mihNew_st.header_length + mihNew_st.module_size;
        result = LoaderCoreSPI_Module_WriteModule(
                    mihNew_st.module_id, 
                    &mihNew_byte );
        if( LC_SUCCESS != result )
        {
            TRACE_LOG1(TRACE_ERROR, "&[BLOADER] Error writing module #%u\n", mihNew_st.module_id);
            if (LC_ERROR_MODULE_NOT_SUPPORTED == result)
            {
                errCode = ERROR_CODE_UNSUPPORTED_MODULE;
            }
            else
            {
                errCode = ERROR_CODE_MODIFY_MODULE;
            }
        }
    }
    
    if (LC_SUCCESS == result)
    {
        TRACE_LOG1(TRACE_DEBUG, "&[BLOADER] Module #%u updated.\n", mihNew_st.module_id);
    }

    /* clear memory blocks */
    LC_Free_Memory((void **)&uk.bytes);
    //LC_Free_Memory((void **)&pModuleByte.bytes);	
    MessageParser_FreeModuleInfoHeader(&mihNew_st);

    /* Report Errorcode */
    ERR_REPORT_SetErrorCodeWithModuleId(errCode, &mihNew_st.module_id);

    return result;

}


static lc_result LC_CheckModuleVersion(lc_uint16 moduleId, lc_uint32 newVersion)
{
    lc_result result = LC_SUCCESS;
    lc_uchar bootcheckalgo = LC_BOOTCHECK_MIN_RESERVED;
    lc_buffer_st uk = {LC_NULL, 0};
    lc_module_info_header mih_st;
    lc_result tmp_result = LC_FAILURE;

    LC_memset(&mih_st, 0, sizeof(lc_module_info_header));

    TRACE_LOG1(TRACE_DEBUG, "[BLOADER] Checking module version for module #%u\n", moduleId);

    if (MODULE_DRV_ID_UK != moduleId &&             /* UK module does not need to care about module_version. */
        MODULE_DRV_ID_VARIANT != moduleId &&        /* Variant module does not need to care about module_version. */
        MODULE_DRV_ID_LOADER_CORE != moduleId &&    /* Loader Core module does not have module_version. */
        MODULE_DRV_ID_BBCB != moduleId &&           /* BBCB module does not have module_version. */
        MODULE_DRV_ID_LOADER_PT != moduleId )       /* Loader Partition module does not have module_version. */
    {
    
        bootcheckalgo = LC_UtilGetBootcheckAlgorithm();

        if (LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION == bootcheckalgo)
        {
            /* Get UK for RSA authentication(not necessary for UK module itself) */
            result = LC_RetrieveUK(&uk.bytes, &uk.length);
            if (LC_SUCCESS != result)
            {
                TRACE_LOG1(
                    TRACE_ERROR, 
                    "&[BLOADER] Error loading UK on checking module version for module #%u!\n", 
                    moduleId);
            }
        }

        if (LC_SUCCESS == result)
        {
            /** 
             * If the existing module is valid, Loader Core will check the version;
             * otherwise, it needs to be recovered without version check;
             */
            tmp_result = LC_ReadAndVerifyExistingModule(
                                            moduleId, 
                                            LC_FALSE, 
                                            bootcheckalgo,
                                            uk.bytes, 
                                            &mih_st,
                                            LC_NULL,
                                            LC_NULL );
            if( (LC_SUCCESS == tmp_result) ||
                ((moduleId == MODULE_DRV_ID_USERFS1) && (0 != mih_st.module_version) && ( 0 != mih_st.module_size)) ||
		((moduleId == MODULE_DRV_ID_USERFS2) && (0 != mih_st.module_version) && ( 0 != mih_st.module_size)) )
            {
                /* Check version */
                
                if(newVersion > mih_st.module_version)
                {
                    if((newVersion - mih_st.module_version) > DEFAULT_MAX_INCREMENT_FOR_MODULE_VERSION)
                    {
                        result = LC_ERROR_INCORRECT_MODULE_VERSION;
                    }
                }
                else if(newVersion < mih_st.module_version)
                {
                    if((65535 - (mih_st.module_version - newVersion)) > DEFAULT_MAX_INCREMENT_FOR_MODULE_VERSION)
                    {
                        result = LC_ERROR_INCORRECT_MODULE_VERSION;
                    }
                }
                else
                {
                    result = LC_ERROR_SAME_MODULE_VERSION;
                }

                if (LC_SUCCESS != result)
                {
                    TRACE_LOG2(
                        TRACE_DEBUG, 
                        "[BLOADER] Error: Module is too old to update, new version: %u, current version: %u!\n",
                        newVersion, 
                        mih_st.module_version);
                }
            }

        }

        /* Clear memory blocks */
        MessageParser_FreeModuleInfoHeader(&mih_st);

    }

    return result;
}

/**
 *  if UK or variant is broken, bootstrap should set env ird_key_broken to yes
 */
static lc_result LC_GetKeyStatus(lc_bool *must_update_key)
{
#if 0
    lc_char *is_key_broken = LC_NULL;

    is_key_broken = getenv("ird_key_broken");
    if(LC_NULL != is_key_broken)
    {      
        if(!strcmp(is_key_broken, "yes"))
        {
            *must_update_key = LC_TRUE;
            TRACE_LOG0(TRACE_INFO, "[BLOADER] STB key is broken, must upgrade key\n");
        }
        else
        {
            *must_update_key = LC_FALSE;
            TRACE_LOG0(TRACE_INFO, "[BLOADER] STB key is ok, no need force to upgrade key\n");
        }
    }
    else
    {
        *must_update_key = LC_FALSE;
        TRACE_LOG0(TRACE_INFO, "there is no env named ird_key_broken, key status is ok!\n");
    }
#endif
    return LC_SUCCESS;
}

