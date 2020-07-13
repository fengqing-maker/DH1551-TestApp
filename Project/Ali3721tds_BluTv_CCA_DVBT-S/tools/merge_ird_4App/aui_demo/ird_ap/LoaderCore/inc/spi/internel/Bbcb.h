
#ifndef BBCB_H__INCLUDED__
#define BBCB_H__INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

/** Public Function Prototypes **********************************************/

/**
 *  Boot Check Algorithm. 
 */

/** 0x00 refers to CRC32 */
#define LC_BOOTCHECK_CRC32              (0x00)

/** 0x01 refers to MAC */
#define LC_BOOTCHECK_MAC                (0x01)
    
/** 0x02 refers to Digital Signature Verification  */
#define LC_BOOTCHECK_DIGITAL_SIGNATURE_VERIFICATION  (0x02)

/** 0x03 reserved */
#define LC_BOOTCHECK_MIN_RESERVED       (0x03)
    


/** 
 * Get and parse BBCB.
 * \note: Set pIsCrcCorrect to LC_NULL to ignore the CRC32 check.
 */
lc_result BBCB_GetBBCB(lc_bbcb_st *pBBCB, lc_bool *pIsCrcCorrect);

/** 
 * Update BBCB.
 * \note: Set updateCRC to LC_TRUE to update the CRC32 field.
 */
lc_result BBCB_SetBBCB(lc_bool updateCRC, const lc_bbcb_st *pBBCB);


#ifdef __cplusplus
}
#endif

#endif  /* BBCB_H__INCLUDED__ */


