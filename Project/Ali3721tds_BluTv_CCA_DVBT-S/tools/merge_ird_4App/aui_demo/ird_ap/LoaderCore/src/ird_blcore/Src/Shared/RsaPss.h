//rsa 

#ifndef RSA_H_INCLUDED_
#define RSA_H_INCLUDED_


#ifdef __cplusplus
extern "C" {
#endif


/*
 * RSA KEY PAIR 
*/

typedef struct _LC_RSA_key
{
 /** 
     * modulus value of RSA operation.  This value is the same 
     * for encryption or decryption
     */
    pkcs_long_num n;

    /**
      * public or private key.  If encrypting this value is the 
     *          public key (e), if decrypting it is the private key (d)
     */
    pkcs_long_num d_or_e;

    /**
     * m' ( -(m^-1) mod b )
     */
    pkcs_long_num mp;

}LC_RSA_key;


//*******************************************************************************//

/*
 *  Basic OS2IP function
 */
 pkcs_result Rsa_OS2IP(
    const lc_uchar *pValue,
    lc_uint32 valueLen,
    pkcs_long_num *pLongNum);

/*
 * Basic I2OSP function
 */
 pkcs_result Rsa_I2OSP(
    const pkcs_long_num *pLongNum,
	lc_uchar *pValue,
    lc_uint32 valueLen);

/**
 * Simple helper function for calculating the MPrime at runtime
 */
void  Rsa_CalcMPrime( 
    const pkcs_long_num *n,
    pkcs_long_num *mp);

/*
 *signature verification function
 */
//
pkcs_result  Rsa_VerifyPssSha256(
    const lc_buffer_st *pHash,
    const lc_uchar signature[SIGNATURE_LENGTH],
    const LC_RSA_key *pRsaKey);



#ifdef __cplusplus
}
#endif

#endif  /*RSA_H_INCLUDED*/