
#ifndef UTILIZATION_H__INCLUDED__
#define UTILIZATION_H__INCLUDED__


#ifdef __cplusplus
extern "C" {
#endif


/** Download class. */
typedef enum _lc_dl_class
{    
    /** 1: Key download */
    LC_DL_CLASS_KEY                = 1,

    /** 2: Variant download */
    LC_DL_CLASS_VARIANT            = 2,

    /** 3: Code download */
    LC_DL_CLASS_CODE               = 3
    
} lc_dl_class;


/** Initialize variables for Persistant Storage. */
lc_result LC_InitializePSVariable(void);

/** Finalize variables for Persistant Storage. */
lc_result LC_FinalizePSVariable(void);


/** Get download flag from Loader Partition. */
lc_bool LC_UtilGetDownloadFlag(void);

/** Set download flag from Loader Partition. */
lc_result LC_UtilSetDownloadFlag(lc_bool enable);

/** Get download type from Loader Partition. */
lc_uchar LC_UtilGetDownloadType(void);

lc_result LC_UtilGetDvbssuDownloadParameters(
    lc_dvbssu_dl_info_st *pDvbSsuParameters, 
    lc_uchar privateInfo[LC_MANUFACTURER_PRIVATE_INFO_LENGTH]);

/** 
 * Reset the value of variant and sub-variant for migration to default.
 */
void LC_UtilResetMigrationVariant(void);

/** 
 * Check if a migration session is required.
 */
lc_bool LC_UtilCheckMigrationMode(void);

/** 
 * Update data field of Loader Partition into persistent storage.
 */
lc_result LC_UtilFlushLoaderPartition(void);

/** 
 * Check OUI to see if this module can be updated.
 */
lc_result LC_UtilCheckOUI(lc_uchar oui[3]);

/** 
 * Check Manufacturer ID to see if this module can be updated.
 */
lc_result LC_UtilCheckManufacturerId(lc_uint16 manufacturerId);

/** 
 * Check Hardware Version to see if this module can be updated.
 */
lc_result LC_UtilCheckHardwareVersion(lc_uint16 hardwareVersion);

/** 
 * Get algorithm type for Boot check from BBCB.
 */
lc_uchar LC_UtilGetBootcheckAlgorithm(void);

/** 
 * Check if all the characters in one string is printable or not.
 */
lc_bool LC_UtilIsStringPrintable(const lc_char *pString, lc_uint32 size);

/** 
 * Get download sequence number from Loader Partition.
 */
lc_result LC_UtilGetDownloadSequence(lc_uint16 *pDownloadSequenceNumber);


/** 
 * Check if Variant and Sub-variant are valid.
 */
lc_result LC_UtilCheckVariant(lc_bool migration, const lc_uint16 *pVariant, const lc_uint16 *pSubVariant);

/** 
 * Update variant and sub-variant in migration mode.
 */
lc_result LC_UtilMigrationUpdateVariant(void);

/** 
 * Check module ID to see if this module can be updated.
 */
lc_result LC_UtilCheckModuleId(lc_uchar downloadType, lc_uint32 moduleId);

/** 
 * Check HASH mode on a specific signature.
 */
lc_result LC_UtilCheckHashMode(lc_bool rsaOn, lc_uchar signatureByte[SIGNATURE_LENGTH], pkcs_hash_mode *pPkcsHashMode);



#ifdef __cplusplus
}
#endif

#endif /* !UTILIZATION_H__INCLUDED__ */

