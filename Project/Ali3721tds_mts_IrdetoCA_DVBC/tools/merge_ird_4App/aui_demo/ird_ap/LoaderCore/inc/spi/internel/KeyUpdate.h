
#ifndef KEYUPD_H__INCLUDED__
#define KEYUPD_H__INCLUDED__

/* Default maximum increment for Key version,  */
#define DEFAULT_MAX_INCREMENT_FOR_KEY_VERSION (99)

/* Typical UK value */
typedef enum _lc_typical_system_id
{
    SYS_ID_MANKEY = 0x0000,

    SYS_ID_DEVKEY = 0xFFFF
    
} lc_typical_system_id;


/* Key update message */
#define SIZE_LODER_INFO_CONTROL (4)    /* size of loader info control block */
#define SIZE_LODER_RESERVED_INFO_CONTROL   (8)   /* size of loader reserved info control block */

#define SIZE_PUBKEY       (256)  /* available space for public key */
#define SIZE_UK_DATA       (SIZE_LODER_INFO_CONTROL*2 + SIZE_LODER_RESERVED_INFO_CONTROL + SIZE_PUBKEY*2)

typedef struct _lc_key_update_message
{
   lc_uchar loaderRealInfoControl [SIZE_LODER_INFO_CONTROL];  /* 0~1,sysid; 2~3,keyver */
   lc_uchar loaderUpgradeInfoControl[SIZE_LODER_INFO_CONTROL];        /* 0~1,sysid; 2~3,keyver */
   lc_uchar loaderReservedInfoControl [SIZE_LODER_RESERVED_INFO_CONTROL];     /* reserved info*/
   lc_uchar loaderPubKey [SIZE_PUBKEY];              /* public modules data */
   lc_uchar loaderPubKeyAuthMsg [SIZE_PUBKEY];
} lc_key_update_message;



/** 
 * public key authentication.
 * This routine accepts the 1104 bit (138 byte) key message from
 * the head-end.  If the message is valid, the IRD code
 * download/verifier public key is updated.
 */
lc_result LC_AuthenticateUK(
    const lc_uchar* pabMsg, 
    lc_uint32 wMsgLen, 
    lc_bool *pIsAManKey);

/** 
 * Get public key from UK module.
 */
lc_result LC_RetrieveUK(lc_uchar** ppUkData, lc_uint32* pUkLength);

/** 
 * Check the validity of master key.
 */
lc_result LC_CheckMasterKey(void);

/** 
 * Get clear (decrypted) public key.
 */
lc_result LC_GetClearKeyData (lc_key_update_message* pClearKeyData);


#endif /* KEYUPD_H__INCLUDED__ */


