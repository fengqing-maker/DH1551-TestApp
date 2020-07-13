
#ifndef MODULE_MANAGER__INCLUDED__
#define MODULE_MANAGER__INCLUDED__

#include "Sha1.h"
/* Typical size for module_info_header */
#define TYPICAL_MODULE_INFO_HEADER_SIZE (26)

/* Short size for module_info_header, applicable for BBCB, Loader Core, and Loader Partition. */
#define SHORT_MODULE_INFO_HEADER_SIZE (12)


typedef struct _lc_checksum_algorithm_status
{
    /** Algorithm */
    lc_uchar algorithm;

    /** Now only applicable when algorithm is LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION 
     *  as well as RSA is being used. 
     */
    lc_uchar* pRsaKey;
    
}lc_checksum_algorithm_status;



typedef struct _lc_sha_controller
{
    /** Hash mode */
    pkcs_hash_mode mode;

    /** Hash state. */
    union
    {
        /** SHA1 */
        sha1_state sha1;

        /** SHA256 */
        sha256_state sha256;
        
    } state;
    
} lc_sha_controller;



/**
 * Read and verifies a specified module with a given key.
 */
lc_result LC_ReadAndVerifyExistingModule(
    lc_uint16 moduleId, 
    lc_bool bootcheck,
    lc_uchar bootcheckAlgorithm,
    lc_uchar *pKey,
    lc_module_info_header *pStModuleHeader,
    lc_buffer_st *pByteModuleHeader, 
    lc_buffer_st *pByteModulePayload);

/** 
 * Retrieve the Variant 
 */
lc_result LC_GetVariant(lc_uint16 *pVariant, lc_uint16 *pSubVariant);


/** 
 * Update Variant and Sub-variant
 */
lc_result LC_SetVariant(lc_bool createNew, const lc_uint16 *pVariant, const lc_uint16 *pSubVariant);

/** 
 * Check if the given signature (clear, decrypted) matches the hash value.
 */
lc_result 
LC_VerifySHASignature(
	lc_uchar* pRsaKey,
    pkcs_hash_mode hashMode, 
    const lc_uchar signatureClear[SIGNATURE_LENGTH], 
    lc_uchar* hash);

/** 
 * Obtain and check the existing module list.
 * 
 * @param ppModuleIdList The module list.
 * @param pModuleIdCount The total number of module in this list.
 * 
 * @return LC_SUCCESS if successfully retrieving module list.
 */
lc_result LC_GetAndCheckExistingModuleList(lc_uint16 **ppModuleIdList, lc_uint32 *pModuleIdCount);

/** 
 * Obtain and parse the module info header.
 */
lc_result LC_ReadAndParseModuleInfoHeader(
    lc_uint16 moduleId, 
    lc_module_info_header *pStModuleInfoHeader,
    lc_buffer_st *pByteModuleInfoHeader);

/** 
 * Verify header signature for module info header.
 */
lc_result LC_VerifyModuleInfoHeaderSignature(
    const lc_checksum_algorithm_status *pStatus,
    const lc_buffer_st *pByteModuleInfoHeader, 
    const lc_module_info_header *pStModuleInfoHeader);

/** 
 * Verify signature.
 */
lc_result LC_VerifySignature(
    const lc_checksum_algorithm_status *pStatus,
    lc_uchar* pBuffer, 
    lc_uint32 length, 
    lc_uchar* pSignature);    

/** 
 * Update signature.
 * This function is used to recalculate and update signature 
 * for module info header and module payload.
 */
lc_result LC_UpdateModuleSignature(
    lc_uchar targetAlgorithm,
    lc_buffer_st *pByte,
    lc_module_info_header *pMih);




/** 
 * Encrypt/Decrypt module.
 * This function is used to encrypt/decrypt module payload data.
 */
lc_result LC_CryptModule(lc_bool encrypt, lc_uchar *pOut, const lc_uchar *pIn, lc_uint32 size);


/** 
 * Check the value of Variant and Sub-variant.
 * 
 * @param pVariant A pointer to an word where the variant will be
 *                stored.
 * @param pSubVariant A pointer to an word where the sub-variant will be
 *                stored.
 * 
 * @return LC_TRUE if all ok
 */
lc_bool LC_IsVariantValid(const lc_uint16 *pVariant, const lc_uint16 *pSubVariant);


/** 
 * SHA calculating initialization.
 * This function is used to initialize SHA algorithm.
 */
lc_result LC_SHAInit(lc_sha_controller *pSHAController);

/** 
 * SHA calculating process.
 * This function is used to calculate SHA and update the SHA state controller. 
 * \note: It supports a multi-part HASH operation.
 */
lc_result 
LC_SHAUpdate(
    lc_sha_controller *pSHAController, 
    const lc_uchar *pData,
    lc_uint32 length);

/** 
 * SHA calculating finalization.
 * This function is used to finalize a SHA calculation and output the final result. 
 */
lc_result 
LC_SHAFinal(
    lc_sha_controller *pSHAController, 
    lc_uchar *pHashResult);

/** 
 * Check variant or sub_variant.
 * This function is used to determine if the download module is allowed for update 
 * by checking the value of variant (or sub_variant). 
 */
lc_bool LC_CheckVariant(lc_bool isSubVariant, lc_uint16 newValue, lc_uint16 oldValue);



#endif  /* MODULE_MANAGER__INCLUDED__ */

