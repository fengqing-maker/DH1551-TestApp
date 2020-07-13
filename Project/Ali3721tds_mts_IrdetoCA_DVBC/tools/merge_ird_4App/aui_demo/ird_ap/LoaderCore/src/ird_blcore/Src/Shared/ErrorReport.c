/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : ErrorReport.c                                              *
*                                                                            *
*   Description : Error code handling.                                       *
*                                                                            *
*****************************************************************************/


#include "LoaderCorePrivate.h"



/* Global variable saving Error Code used by BSTRP and BLOADER */
static lc_uint32 gErrorCode;

/* Module ID required by some error code related to module. */
static lc_uint16 gModuleId;

/* Count the total time(s) setting error code. */
static lc_uint32 gSetCounter;

//#define SUPPORT_LED_BLINK
#ifdef SUPPORT_LED_BLINK
typedef enum blink_mode {
    RED_ON,
    BLUE_ON,
    BOTH_ON,
    RED_BLINK
}blink_mode;
extern blink_mode next_blink_mode;

void blink_red(void)
{
    next_blink_mode = 3; //RED_BLINK;
}
#endif




static lc_result ERR_REPORT_ErrCodeFilterAndSet(lc_uint32 errorCode, const lc_uint16 *pModuleId)
{
    lc_result result = LC_SUCCESS;
    
    /* Occur SAMEVERSION save the moduleId*/
    gErrorCode = errorCode;

    if (LC_NULL != pModuleId)
    {
        gModuleId = *pModuleId;
    }

    return result;
}

void ERR_REPORT_Initialize(void)
{
    gErrorCode = ERROR_CODE_SUCCESS;
    gSetCounter = 0;
    gModuleId = 0xffff;
}

void ERR_REPORT_SetErrorCodeWithModuleId(lc_uint32 errorCode, const lc_uint16 *pModuleId)
{

    /* Disallowed to set ERROR_CODE_SUCCESS. */
    if (ERROR_CODE_SUCCESS != errorCode)
    {
#ifdef SUPPORT_LED_BLINK
        blink_red();    
#endif
        /* It is regarded as an ERROR to set it more than once or to set it as ERROR_CODE_SUCCESS! */
        if (0 == gSetCounter)
        {
            ERR_REPORT_ErrCodeFilterAndSet(errorCode, pModuleId);

            /* Only ERROR_CODE_SAME_MODULE_VERSION can be covered by other error codes!!! */
            if (ERROR_CODE_SAME_MODULE_VERSION != errorCode)
            {
                gSetCounter++;
            }
        }
        else
        {
            /* Print error message!!!!!!  */
            TRACE_LOG2(
                TRACE_DEBUG, 
                "[ERR_REPORT] Error setting error code more than once! %u times in all by now! Current = 0x%x, New = 0x%x.\n",
                gErrorCode, errorCode);       
        }
    }
    else
    {
        if (ERROR_CODE_SUCCESS != gErrorCode)
        {
#ifdef SUPPORT_LED_BLINK
            blink_red();    
#endif

            /* Print error message!!!!!!  */
            TRACE_LOG0(TRACE_DEBUG, "[ERR_REPORT] Error setting ERROR_CODE_SUCCESS by ERR_REPORT_SetErrorCode!\n");
        }
    }
    
}

void ERR_REPORT_SetErrorCode(lc_uint32 errorCode)
{
    ERR_REPORT_SetErrorCodeWithModuleId(errorCode, LC_NULL);

#ifdef SUPPORT_LED_BLINK
    if(errorCode != ERROR_CODE_SUCCESS) {
        blink_red();    
    }
#endif
}

void ERR_REPORT_GetErrorCode(lc_uint32 *pErrorCode, lc_uint16 *pModuleId)
{ 
    /* Error code is mandatory. */
    *pErrorCode = gErrorCode;
    
    /* Module ID is optional. */
    if (LC_NULL != pModuleId)
    {
        *pModuleId = gModuleId;
    }
}


