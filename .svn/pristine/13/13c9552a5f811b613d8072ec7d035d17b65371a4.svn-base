/**
 * @file LoaderCoreAPI.h
 * Loader Core API. This file contains all the APIs that are provided by Boot Strap and Boot Loader.
 */
#ifndef LOADERCOREAPI_H__INCLUDED__
#define LOADERCOREAPI_H__INCLUDED__

#include "LoaderCore_Types.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup loadercoreapis Loader Core APIs
 *  Loader Core APIs
 *
 *  These APIs provide ther interfaces to start Loader Core and to read/write all necessary informations from/to Loader Core.
 *  
 *  @{
 */

/** @defgroup loadercorebaseapis Loader Core Base APIs
 *  Loader Core Base APIs
 *
 *  These APIs provide ther interfaces to start Loader Core.
 *  
 *  @{
 */


/**
 * Start Boot Strap.
 *
 * This method is used to start Boot Strap. 
 * Boot Strap is the entry point for Loader Core.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_StartBootStrap(void);

/**
 * Start Boot Loader.
 *
 * This method is used to start Boot Strap. 
 * Boot Loader is main body to perform the download process.
 * \note It is up to the manufacturer to decide when and where to start up Boot Loader. Usually, Boot Loader is called indirectly by Boot Strap.
 *
 * @retval 
 *    ::LC_SUCCESS
 * @retval
 *     Other The method may return any other errors listed in \ref result "Result Code List". 
 */
lc_result LoaderCoreAPI_StartBootLoader( ExecuteCode func);

/** @} */

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* !LOADERCOREAPI_H__INCLUDED__ */
