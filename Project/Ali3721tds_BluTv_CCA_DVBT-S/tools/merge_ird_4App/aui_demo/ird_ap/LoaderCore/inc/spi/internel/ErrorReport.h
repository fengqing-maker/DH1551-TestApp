
#ifndef _ERROR_REPORT_H__INCLUDED__
#define _ERROR_REPORT_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif


/** Public Function Prototypes **********************************************/

/** 
 * Initialize. 
 * This function is used to reset error code to ERROR_CODE_SUCCESS, 
 * and shall be invoked at the very beginning of BSTRAP or BLOADER.
 * 
 * @param Void 
 * 
 * @return Void.
 */
void ERR_REPORT_Initialize(void);

/** 
 * Set Error Code.
 * 
 * @param errorCode The error code we are going to set 
 * 
 * @return Void.
 */
void ERR_REPORT_SetErrorCode(lc_uint32 errorCode);

/** 
 * Set Error Code With Module ID.
 * 
 * @param errorCode The error code we are going to set 
 * @param pModuleId The pointer points to the module ID value we are going to set 
 * 
 * @return Void.
 */
void ERR_REPORT_SetErrorCodeWithModuleId(lc_uint32 errorCode, const lc_uint16 *pModuleId);

/** 
 * Get current Error code and module ID (optional).
 * 
 * @param pErrorCode To save the error code
 * @param pModuleId To save the module ID, optional
 * 
 * @return Void.
 */
void ERR_REPORT_GetErrorCode(lc_uint32 *pErrorCode, lc_uint16 *pModuleId);


#ifdef __cplusplus
}
#endif

#endif  /* _ERROR_REPORT_H__INCLUDED__ */

