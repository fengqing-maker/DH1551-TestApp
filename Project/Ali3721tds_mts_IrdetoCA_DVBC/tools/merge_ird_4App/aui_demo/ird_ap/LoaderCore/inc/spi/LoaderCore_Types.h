/**
 * @file LoaderCore_Types.h
 *
 * Loader Core types.  This file contains common types that are platform specific.
 */
#ifndef LOADERCORE_TYPES_H__INCLUDED__
#define LOADERCORE_TYPES_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * LC_NULL typedef. 
 */
#define LC_NULL 0

/**
 * Boolean type enumeration
 */
typedef enum _lc_bool
{
    /** 0 False.
     * 
     * False.
     */
    LC_FALSE = 0,

    /** 1 True.
     * 
     * True.
     */

    LC_TRUE = 1
}lc_bool;


/** @defgroup result Result Code List
 *  List of all possible values of ::lc_result codes. 
 *
 *  Except where noted, applications and implementations should 
 *  not expect particular failure codes to always be returned from functions, other than ::LC_SUCCESS.
 *  This is because over time and across different implementations the error codes returned from different error situations
 *  may change.
 *  @{
 */

/**
 * Result code enumerator type. 
 */
typedef enum _lc_result
{
    /** (0) The operation was successful. */
    LC_SUCCESS                                          = 0,

    /** (1) The operation has failed for unknown reasons. */
    LC_FAILURE                                          = 1,

    /** (2) One or more required parameters were NULL. */
    LC_ERROR_NULL_PARAM                                 = 2, 

    /** (3) The buffer passed in is too small. */
    LC_ERROR_INSUFFICIENT_BUFFER                        = 3,

    /** (4) An invalid message was found. */
    LC_ERROR_INVALID_DATA                               = 4,

    /** (5) Some required internal data is missing. */
    LC_ERROR_MISSING_DATA                               = 5,

    /** (6) At least one of function parameters is invalid. */
    LC_ERROR_INVALID_PARAMETER                          = 6,

    /** (7) Handle is invalid. */
    LC_ERROR_INVALID_HANDLE                             = 7,

    /** (8) Timeout. */
    LC_ERROR_TIMEOUT                                    = 8,

    /** (9) An invalid SSU section was received. */
    LC_ERROR_WRONG_SECTION                              = 9,

    /** (10) An SSU section with incorrect message ID was received. */
    LC_ERROR_WRONG_MESSAGE_ID                           = 10,

    /** (11) An SSU section with incorrect transaction ID was received. */
    LC_ERROR_WRONG_TRANSACTION_ID                       = 11,

    /** (12) An SSU section with incorrect service ID was received. */
    LC_ERROR_WRONG_SERVICE_ID                           = 12,

    /** (13) The module list was invalid. */
    LC_ERROR_INVALID_MODULE_LIST                        = 13,

    /** (14) The module has not been found. */
    LC_ERROR_MODULE_NOT_FOUND                           = 14,

    /** (15) The module was not supported. */
    LC_ERROR_MODULE_NOT_SUPPORTED                       = 15,

    /** (16) Failed to access a module. */
    LC_ERROR_MODULE_ACCESS_ERROR                        = 16,

    /** (17) A module is illegal. */
    LC_ERROR_ILLEGAL_MODULE_CONTENT                     = 17,

    /** (18) A module is strictly forbidden to be updated. */
    LC_ERROR_MODULE_UPDATE_DISALLOWED                   = 18,

    /** (19) Invalid Variant value. */
    LC_ERROR_INVALID_VARIANT_VALUE                      = 19,

    /** (20) Invalid Sub-Variant value. */
    LC_ERROR_INVALID_SUBVARIANT_VALUE                   = 20,

    /** (21) An invalid key was found. */
    LC_ERROR_INVALID_KEY                                = 21,

    /** (22) Incorrect DDB module version*/
    LC_ERROR_DDB_WRONG_MODULE_VERSION                   = 22,

    /** (23) Incorrect download sequence number */
    LC_ERROR_INCORRECT_DOWNLOAD_SEQUENCE_NUMBER         = 23,

    /** (24) Same download sequence number*/
    LC_ERROR_SAME_DOWNLOAD_SEQUENCE_NUMBER              = 24,

    /** (25) Incorrect module version */
    LC_ERROR_INCORRECT_MODULE_VERSION                   = 25,

    /** (26) Same module version */
    LC_ERROR_SAME_MODULE_VERSION                        = 26,

    /** (27) Incorrect signature length */
    LC_ERROR_INCORRECT_SIGNATURE_LENGTH                 = 27,

    /** (28) Incorrect CRC32 for SSU section */
    LC_ERROR_INCORRECT_SECTION_CRC32                    = 28,

    /** (29) Incorrect module Id for SSU DDB block */
    LC_ERROR_WRONG_MODULE_ID                            = 29,

    /** (29) without Application moudle (ID >= MIN_MODULE_ID_APP)  */
    LC_ERROR_MISSING_APP_MODULE                         = 30
}lc_result;


/** @} */

typedef unsigned int    lc_uint32;   /**< Unsigned 32-bit integer */
typedef int             lc_sint32;   /**< Signed 32-bit integer */
typedef unsigned short  lc_uint16;   /**< Unsigned 16-bit integer */
typedef unsigned char   lc_uchar;    /**< Unsigned 8-bit byte */
typedef char            lc_char;     /**< Single character */
typedef char *          lc_string;   /**< Null-terminated string */
typedef void *          lc_handle;   /**< Virtual handle to all kinds of instance. #LC_INVALID_HANDLE is not a valid filter handle. */

/**
 * Invalid handle value.  This is equivalent to a void* with all bits set (i.e., 0xFFFFFFFF)
 */
#define LC_INVALID_HANDLE ((lc_handle)-1)


/**
 * Byte buffer structure
 *
 * This structure is used to hold arbitrary blocks of memory.
 * 
 * The caller sets the \a bytes member to point to a 
 * buffer, and sets the \a length member to be the length of the buffer.
 * 
 * When used as an output parameter, the function being called will copy data up to
 * the length of the buffer into the memory specified by \a bytes. When used as an
 * input parameter, the function leaves the contents of the buffer alone. 
 */
typedef struct _lc_buffer_st
{
    /**
     * Pointer to a valid region of memory. Depending on the operation, this
     * may be a block of memory to write into or to read from.
     */
    lc_uchar *bytes;

    /**
     * Length of the buffer. Depending on the operation, the number of bytes to 
     * read to or write from the \a bytes member.
     */
    lc_uint32 length;
} lc_buffer_st;

#ifdef __cplusplus
}
#endif

#endif /* !LOADERCORE_TYPES_H__INCLUDED__ */
