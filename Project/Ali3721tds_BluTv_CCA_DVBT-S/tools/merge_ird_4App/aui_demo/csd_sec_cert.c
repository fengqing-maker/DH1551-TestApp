
#include <sys_config.h>
#include <basic_types.h>
#include <mediatypes.h>
#include <api/libc/alloc.h>
#include <api/libc/printf.h>
#include <api/libc/string.h>
#include <osal/osal.h>
#include <hld/hld_dev.h>

#include "csd_sec_cert.h"

static int csd_clear_key(int debug_en)
{
	int ret = -1;
	int cert_akl_sess = -1;
	int cert_akl_key_pos = -1;
	int cert_asa_sess = -1;
	int i = 0;
	CE_FOUND_FREE_POS_PARAM pos_param;
	unsigned char output[128];

	debug_printf("...Start...\n");
	
	ret = csdDecryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							aes_test_key, sizeof(aes_test_key), 
							NULL, 0, 0, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdDecryptDataWithClearTextHostKey aes ecb return error\n");

	if(memcmp(output,aes_ecb_de_result,sizeof(aes_ecb_de_result))) {
		out_printf("csdDecryptDataWithClearTextHostKey aes ecb decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithClearTextHostKey aes ecb decrypt result PASS\n");
	}

	ret = csdEncryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							aes_test_key, sizeof(aes_test_key), 
							NULL, 0, 0, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdEncryptDataWithClearTextHostKey aes ecb return error\n");

	if(memcmp(output,aes_ecb_en_result,sizeof(aes_ecb_en_result))) {
		out_printf("csdEncryptDataWithClearTextHostKey aes ecb encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithClearTextHostKey aes ecb encrypt result PASS\n");
	}

	ret = csdEncryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							aes_test_key, sizeof(aes_test_key), 
							aes_test_iv, sizeof(aes_test_iv), 
							1, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdEncryptDataWithClearTextHostKey aes cbc return error\n");

	if(memcmp(output,aes_cbc_en_result,sizeof(aes_cbc_en_result))) {
		out_printf("csdEncryptDataWithClearTextHostKey aes cbc encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithClearTextHostKey aes cbc encrypt result PASS\n");
	}

	ret = csdDecryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							aes_test_key, sizeof(aes_test_key), 
							aes_test_iv, sizeof(aes_test_iv), 
							1, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdDecryptDataWithClearTextHostKey aes cbc return error\n");

	if(memcmp(output,aes_cbc_de_result,sizeof(aes_cbc_de_result))) {
		out_printf("csdDecryptDataWithClearTextHostKey aes cbc decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithClearTextHostKey aes cbc decrypt result PASS\n");
	}

	ret = csdDecryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							des_test_key, sizeof(des_test_key), 
							NULL, 0, 0, NULL, des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdDecryptDataWithClearTextHostKey tdes ecb return error\n");

	if(memcmp(output,tdes_ecb_de_result,sizeof(tdes_ecb_de_result))) {
		out_printf("csdDecryptDataWithClearTextHostKey tdes ecb decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithClearTextHostKey tdes ecb decrypt result PASS\n");
	}

	ret = csdEncryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							des_test_key, sizeof(des_test_key), 
							NULL, 0, 0, NULL, des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdEncryptDataWithClearTextHostKey tdes ecb return error\n");

	if(memcmp(output,tdes_ecb_en_result,sizeof(tdes_ecb_en_result))) {
		out_printf("csdEncryptDataWithClearTextHostKey tdes ecb encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithClearTextHostKey tdes ecb encrypt result PASS\n");
	}

	ret = csdEncryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							des_test_key, sizeof(des_test_key), 
							des_test_iv, sizeof(des_test_iv), 
							1, NULL, des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdEncryptDataWithClearTextHostKey tdes cbc return error\n");

	if(memcmp(output,tdes_cbc_en_result,sizeof(tdes_cbc_en_result))) {
		out_printf("csdEncryptDataWithClearTextHostKey tdes cbc encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithClearTextHostKey tdes cbc encrypt result PASS\n");
	}

	ret = csdDecryptDataWithClearTextHostKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							des_test_key, sizeof(des_test_key), 
							des_test_iv, sizeof(des_test_iv), 
							1, NULL, des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdDecryptDataWithClearTextHostKey tdes cbc return error\n");

	if(memcmp(output,tdes_cbc_de_result,sizeof(tdes_cbc_de_result))) {
		out_printf("csdDecryptDataWithClearTextHostKey tdes cbc decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithClearTextHostKey tdes cbc decrypt result PASS\n");
	}

	debug_printf("...End...\n");
out:
	return ret;
}

static int csd_kl_key(int debug_en)
{
	int ret = -1;
	int cert_akl_sess = -1;
	int cert_akl_key_pos = -1;
	int cert_asa_sess = -1;
	int i = 0;
	CE_FOUND_FREE_POS_PARAM pos_param;
	unsigned char output[128];

	debug_printf("...Start...\n");
	
	ret = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							aesProtectingKey,
							aesCipheredContentKey,
							sizeof(aesCipheredContentKey),
							NULL, 0, 0, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdEncryptDataWithSecretContentKey aes ecb return error\n");

	if(memcmp(output,aes_ecb_en_result,sizeof(aes_ecb_en_result))) {
		out_printf("csdEncryptDataWithSecretContentKey aes ecb encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithSecretContentKey aes ecb encrypt result PASS\n");
	}

	ret = csdDecryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							aesProtectingKey,
							aesCipheredContentKey,
							sizeof(aesCipheredContentKey),
							NULL, 0, 0, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdDecryptDataWithSecretContentKey aes ecb return error\n");

	if(memcmp(output,aes_ecb_de_result,sizeof(aes_ecb_de_result))) {
		out_printf("csdDecryptDataWithSecretContentKey aes ecb decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithSecretContentKey aes ecb decrypt result PASS\n");
	}

	ret = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							aesProtectingKey,
							aesCipheredContentKey,
							sizeof(aesCipheredContentKey),
							aes_test_iv, sizeof(aes_test_iv),
							1, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdEncryptDataWithSecretContentKey aes cbc return error\n");

	if(memcmp(output,aes_cbc_en_result,sizeof(aes_cbc_en_result))) {
		out_printf("csdEncryptDataWithSecretContentKey aes cbc encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithSecretContentKey aes cbc encrypt result PASS\n");
	}

	ret = csdDecryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_AES_128,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							aesProtectingKey,
							aesCipheredContentKey,
							sizeof(aesCipheredContentKey),
							aes_test_iv, sizeof(aes_test_iv),
							1, NULL, aes_test_in, output, sizeof(aes_test_in));
	if (ret)
		out_printf("csdDecryptDataWithSecretContentKey aes cbc return error\n");

	if(memcmp(output,aes_cbc_de_result,sizeof(aes_cbc_de_result))) {
		out_printf("csdDecryptDataWithSecretContentKey aes cbc decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithSecretContentKey aes cbc decrypt result PASS\n");
	}

	ret = csdDecryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							tdesProtectingKey,
							tdesCipheredContentKey,
							sizeof(tdesCipheredContentKey),
							NULL, 0, 0, NULL,
							des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdDecryptDataWithSecretContentKey tdes ecb return error\n");

	if(memcmp(output,tdes_ecb_de_result,sizeof(tdes_ecb_de_result))) {
		out_printf("csdDecryptDataWithSecretContentKey tdes ecb decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithSecretContentKey tdes ecb decrypt result PASS\n");
	}

	ret = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_ECB,
							tdesProtectingKey,
							tdesCipheredContentKey,
							sizeof(tdesCipheredContentKey),
							NULL, 0, 0, NULL,
							des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdEncryptDataWithSecretContentKey tdes ecb return error\n");

	if(memcmp(output,tdes_ecb_en_result,sizeof(tdes_ecb_en_result))) {
		out_printf("csdEncryptDataWithSecretContentKey tdes ecb encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithSecretContentKey tdes ecb encrypt result PASS\n");
	}

	ret = csdEncryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							tdesProtectingKey,
							tdesCipheredContentKey,
							sizeof(tdesCipheredContentKey),
							des_test_iv, sizeof(des_test_iv), 1, NULL,
							des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdEncryptDataWithSecretContentKey tdes cbc return error\n");

	if(memcmp(output,tdes_cbc_en_result,sizeof(tdes_cbc_en_result))) {
		out_printf("csdEncryptDataWithSecretContentKey tdes cbc encrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdEncryptDataWithSecretContentKey tdes cbc encrypt result PASS\n");
	}

	ret = csdDecryptDataWithSecretContentKey(CSD_R2R_ALGORITHM_TDES_K1K2K1,
							CSD_R2R_CRYPTO_OPERATION_MODE_CBC,
							tdesProtectingKey,
							tdesCipheredContentKey,
							sizeof(tdesCipheredContentKey),
							des_test_iv, sizeof(des_test_iv), 1, NULL,
							des_test_in, output, sizeof(des_test_in));
	if (ret)
		out_printf("csdDecryptDataWithSecretContentKey tdes cbc return error\n");

	if(memcmp(output,tdes_cbc_de_result,sizeof(tdes_cbc_de_result))) {
		out_printf("csdDecryptDataWithSecretContentKey tdes cbc decrypt result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("csdDecryptDataWithSecretContentKey tdes cbc decrypt result PASS\n");
	}

	debug_printf("...End...\n");
out:
	return ret;
}


static int nocs_csd_test(int debug_en)
{
	int ret = -1;
	TCsd8BytesVector xNUID;
	TCsd4BytesVector xNUIDCheckNumber;
	TCsd4BytesVector xSTBCASN;
	TCsd4BytesVector xMarketSegmentId;
	TCsd4BytesVector xSCS_PV_VERSIONING_REF;
	TCsd4BytesVector xCSCDCheckNumber;
	TCsdDebugInterfaceAccessMode xDebugInterfaceProtectionLevel;
	char *xDebugInterfaceStatus[] = {"OPEN", "PASSWORD", "CLOSED"};
	TCsdActivationFlag xScramblingActivationFlagState;
	char *xScramblingActivationStatus[] = {"ACTIVATED", "DEACTIVATED"};
	TCsdActivationFlag xScsActivationFlagState;
	char *xScsActivationStatus[] = {"ACTIVATED", "DEACTIVATED"};
	TCsdActivationFlag xFlashProtectionActivationFlagState;
	char *xFlashProtectionActivationStatus[] = {"ACTIVATED", "DEACTIVATED"};

	csdInitialize(NULL);

	ret = csdGetNuid64(xNUID);

	ret |= csdGetNUIDCheckNumber(xNUIDCheckNumber);
	ret |= csdGetDebugInterfaceProtectionLevel(&xDebugInterfaceProtectionLevel);
	ret |= csdGetStbCaSn(xSTBCASN);
	ret |= csdGetMarketSegmentId(xMarketSegmentId);
	ret |= csdGetScsPv(CSD_SCS_PV_VERSIONING_REF, NULL, 4, xSCS_PV_VERSIONING_REF);
	ret |= csdGetScramblingActivationFlag(&xScramblingActivationFlagState);
	ret |= csdGetScsActivationFlag(&xScsActivationFlagState);
	ret |= csdGetCSCDCheckNumber(csc_data, xCSCDCheckNumber);
	ret |= csdGetFlashProtectionActivationFlag(&xFlashProtectionActivationFlagState);

	if (ret) {
		out_printf("\nGet OTP items error...\n\n");
		csdTerminate(NULL);
		return ret;
	}

	CSD_SEC_DUMP("NUID", xNUID, 8);
	CSD_SEC_DUMP("NUIDCheckNumber", xNUIDCheckNumber, 4);
	out_printf("DebugInterfaceProtectionLevel: %s\n",
		xDebugInterfaceStatus[xDebugInterfaceProtectionLevel]);
	CSD_SEC_DUMP("STBCASN", xSTBCASN, 4);
	CSD_SEC_DUMP("MarketSegmentId", xMarketSegmentId, 4);
	CSD_SEC_DUMP("SCS_PV_VERSIONING_REF", xSCS_PV_VERSIONING_REF, 4);
	out_printf("ScramblingActivationFlagState: %s\n",
			xScramblingActivationStatus[xScramblingActivationFlagState]);
	out_printf("ScsActivationFlagState: %s\n",
			xScsActivationStatus[xScsActivationFlagState]);
	CSD_SEC_DUMP("CSCCheckNumber", xCSCDCheckNumber, 4);
	if (memcmp(xCSCDCheckNumber, csc_result, 4))
		out_printf("\nxCSCDCheckNumber is wrong...\n\n");

	out_printf("FlashProtectionActivationFlagState: %s\n",
			xFlashProtectionActivationStatus[xFlashProtectionActivationFlagState]);

	ret = csd_clear_key(debug_en);
	ret |= csd_kl_key(debug_en);

	csdTerminate(NULL);
	return ret;
}

/* run once on one IC */
static int nocs_csd_otp_test(int debug_en)
{
	int ret = -1;
	TCsd4BytesVector xSTBCASN = {0x55,0x00,0x00,0x55};
	TCsd4BytesVector xMarketSegmentId = {0x55,0x00,0x00,0x55};
	TCsd4BytesVector xSCS_PV_VERSIONING_REF = {0,0,0,3};

	csdInitialize(NULL);

	ret = csdEnableRamScrambling();

	ret |= csdEnableFlashProtection();
	ret |= csdEnableScs();
	ret |= csdSetScsPv(CSD_SCS_PV_VERSIONING_REF, NULL, 4, xSCS_PV_VERSIONING_REF);

	ret |= csdSetStbCaSn(xSTBCASN);
	ret |= csdSetMarketSegmentId(xMarketSegmentId);
	ret |= csdSelectDebugInterfaceProtectionLevel(CSD_DEBUG_INTERFACE_ACCESS_MODE_OPEN);

	if (ret)
		out_printf("\nSomething wrong...\n\n");

	csdTerminate(NULL);
	return ret;
}

static int sec_clear_key(int debug_en)
{
	int ret = -1;
	TSecCipherSession xSession = NULL;
	TSecFunctionTable *sec = NULL;
	unsigned char output[128];

	debug_printf("...Start...\n");

	sec = secGetFunctionTable();
	out_printf("secGetFunctionTable: 0x%x\n", sec);

	ret = sec->secOpenRam2RamEncryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamEncryptSession, ret: 0x%x\n", ret);
		goto out;
	}

	ret = sec->secSetClearTextKey(xSession, 0x4021, 0, NULL,
					sizeof(aes_test_key), aes_test_key);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSetClearTextKey, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSessionEncrypt(xSession, aes_test_in, output,
				sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_ecb_en_result,sizeof(aes_ecb_en_result))) {
		out_printf("secSessionEncrypt aes ecb result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionEncrypt aes ecb result PASS\n");
	}

	sec->secCloseSession(xSession);

	ret = sec->secOpenRam2RamDecryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamDecryptSession, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSetClearTextKey(xSession, 0x4021, 0, NULL,
					sizeof(aes_test_key), aes_test_key);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSetClearTextKey, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSessionDecrypt(xSession, aes_test_in, output,
				sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_ecb_de_result,sizeof(aes_ecb_de_result))) {
		out_printf("secSessionDecrypt aes ecb result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionDecrypt aes ecb result PASS\n");
	}

	sec->secCloseSession(xSession);

	/* cbc */
	ret = sec->secOpenRam2RamDecryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamDecryptSession, ret: 0x%x\n", ret);
		goto out;
	}

	ret = sec->secSetClearTextKey(xSession, 0x4022, 0, NULL,
					sizeof(aes_test_key), aes_test_key);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSetClearTextKey, ret: 0x%x\n", ret);
		goto out;
	}

	ret = sec->secSessionDecrypt(xSession, aes_test_in, output,
			sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_cbc_de_result,sizeof(aes_cbc_de_result))) {
		out_printf("secSessionDecrypt aes cbc result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionDecrypt aes cbc result PASS\n");
	}

	sec->secCloseSession(xSession);

	ret = sec->secOpenRam2RamEncryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamEncryptSession, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSetClearTextKey(xSession, 0x4022, 0, NULL,
					sizeof(aes_test_key), aes_test_key);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSetClearTextKey, ret: 0x%x\n", ret);
		goto out;
	}

	ret = sec->secSessionEncrypt(xSession, aes_test_in, output,
			sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_cbc_en_result,sizeof(aes_cbc_en_result))) {
		out_printf("secSessionEncrypt aes cbc result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionEncrypt aes cbc result PASS\n");
	}

	/* ctr */
	ret = sec->secSetClearTextKey(xSession, 0x4024, 0, NULL,
					sizeof(aes_test_key), aes_test_key);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSetClearTextKey, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSessionEncrypt(xSession, aes_test_in, output,
			sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_ctr_result,sizeof(aes_ctr_result))) {
		out_printf("secSessionEncrypt aes ctr result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionEncrypt aes ctr result PASS\n");
	}

	sec->secCloseSession(xSession);

	debug_printf("...End...\n");

out:
	return ret;
}

static int sec_kl_key(int debug_en)
{
	int ret = -1;
	TSecCipherSession xSession = NULL;
	TSecFunctionTable *sec = NULL;
	TUnsignedInt8 *output = NULL;

	debug_printf("...Start...\n");

	sec = secGetFunctionTable();
	out_printf("secGetFunctionTable: 0x%x\n", sec);
	if (!sec)
		return ret;

	output = sec->secAllocateBuffer(128);
	if (!output) {
		out_printf("secAllocateBuffer failed\n");
		return ret;
	}

	ret = sec->secOpenRam2RamEncryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamEncryptSession, ret: 0x%x\n", ret);
		goto out;
	}

	ret = sec->secSet2LevelProtectedKey(xSession, 0x4021, 0, NULL,
					sizeof(aesCipheredContentKey), aesCipheredContentKey,
					16, &aesProtectingKey[1], &aesProtectingKey[0]);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSet2LevelProtectedKey, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSessionEncrypt(xSession, aes_test_in, output,
				sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_ecb_en_result,sizeof(aes_ecb_en_result))) {
		out_printf("secSessionEncrypt aes ecb result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionEncrypt aes ecb result PASS\n");
	}

	sec->secCloseSession(xSession);

	ret = sec->secOpenRam2RamDecryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamDecryptSession, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSet2LevelProtectedKey(xSession, 0x4021, 0, NULL,
					sizeof(aesCipheredContentKey), aesCipheredContentKey,
					16, &aesProtectingKey[1], &aesProtectingKey[0]);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSet2LevelProtectedKey, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSessionDecrypt(xSession, aes_test_in, output,
				sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_ecb_de_result,sizeof(aes_ecb_de_result))) {
		out_printf("secSessionDecrypt aes ecb result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionDecrypt aes ecb result PASS\n");
	}

	sec->secCloseSession(xSession);

	/* cbc */
	ret = sec->secOpenRam2RamDecryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamDecryptSession, ret: 0x%x\n", ret);
		goto out;
	}

	ret = sec->secSet2LevelProtectedKey(xSession, 0x4022, 0, NULL,
					sizeof(aesCipheredContentKey), aesCipheredContentKey,
					16, &aesProtectingKey[1], &aesProtectingKey[0]);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSet2LevelProtectedKey, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSessionDecrypt(xSession, aes_test_in, output,
			sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_cbc_de_result,sizeof(aes_cbc_de_result))) {
		out_printf("secSessionDecrypt aes cbc result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionDecrypt aes cbc result PASS\n");
	}

	sec->secCloseSession(xSession);

	ret = sec->secOpenRam2RamEncryptSession(&xSession);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenRam2RamEncryptSession, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSet2LevelProtectedKey(xSession, 0x4022, 0, NULL,
					sizeof(aesCipheredContentKey), aesCipheredContentKey,
					16, &aesProtectingKey[1], &aesProtectingKey[0]);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSet2LevelProtectedKey, ret: 0x%x\n", ret);
		goto out;
	}

	ret = sec->secSessionEncrypt(xSession, aes_test_in, output,
			sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_cbc_en_result,sizeof(aes_cbc_en_result))) {
		out_printf("secSessionEncrypt aes cbc result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionEncrypt aes cbc result PASS\n");
	}

	/* ctr */
	ret = sec->secSet2LevelProtectedKey(xSession, 0x4024, 0, NULL,
					sizeof(aesCipheredContentKey), aesCipheredContentKey,
					16, &aesProtectingKey[1], &aesProtectingKey[0]);
	if (ret != SEC_NO_ERROR) {
		out_printf("error secSet2LevelProtectedKey, ret: 0x%x\n", ret);
		goto out;
	}
	ret = sec->secSessionEncrypt(xSession, aes_test_in, output,
			sizeof(aes_test_in), aes_test_iv, sizeof(aes_test_iv));
	if(memcmp(output,aes_ctr_result,sizeof(aes_ctr_result))) {
		out_printf("secSessionEncrypt aes ctr result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionEncrypt aes ctr result PASS\n");
	}

	sec->secCloseSession(xSession);

	debug_printf("...End...\n");

out:
	if (output)
		sec->secFreeBuffer(output);
	return ret;
}

static int ca_sec_test(int debug_en)
{
	int ret = -1;
	TSecFunctionTable *sec = NULL;
	TUnsignedInt8 *output = NULL;

	sec = secGetFunctionTable();
	out_printf("secGetFunctionTable: 0x%x\n", sec);
	if (!sec)
		return ret;

	output = sec->secAllocateBuffer(128);
	if (!output) {
		out_printf("secAllocateBuffer failed\n");
		return ret;
	}

	ret = sec->secEncryptFlashProtKey(flash_pk, output, sizeof(flash_pk));
	if (ret != SEC_NO_ERROR) {
		out_printf("error secEncryptFlashProtKey, ret: 0x%x\n", ret);
		goto out;
	}
	CSD_SEC_DUMP("FlashPK", output, 16);
	if (memcmp(flash_pk_en_result, output, sizeof(flash_pk_en_result))) {
		ret = -1;
		out_printf("secEncryptFlashProtKey result mismatch\n");
		goto out;
	} else {
		out_printf("secEncryptFlashProtKey result PASS\n");
	}

	ret = sec_clear_key(debug_en);
	ret |= sec_kl_key(debug_en);

out:
	if (output)
		sec->secFreeBuffer(output);
	return ret;
}

static int ca_cert_test(int debug_en)
{
	int ret = -1;
	TCertFunctionTable *cert = NULL;
	TSecFunctionTable *sec = NULL;
	TUnsignedInt8 *output = NULL;
	TCertResourceHandle cert_hdl = NULL;
	int i = 0;
	TCertCommand param;
	TSecCipherSession xSession = NULL;

	cert = certGetFunctionTable();
	out_printf("certGetFunctionTable: 0x%x\n", cert);
	if (!cert)
		return ret;

	sec = secGetFunctionTable();
	out_printf("secGetFunctionTable: 0x%x\n", sec);
	if (!sec)
		return ret;

	output = sec->secAllocateBuffer(8192);
	if (!output) {
		out_printf("secAllocateBuffer failed\n");
		return ret;
	}

	ret = cert->certLock(&cert_hdl);
	if (ret != CERT_NO_ERROR) {
		out_printf("error certLock, ret: 0x%x\n", ret);
		goto out;
	}
	if (!cert_hdl) {
		out_printf("certLock failed, handle is NULL\n");
		goto out;
	}

	ret = sec->secOpenStreamDecryptSession(&xSession, 0);
	if ((ret != SEC_NO_ERROR) || !xSession) {
		out_printf("error secOpenStreamDecryptSession, ret: 0x%x\n", ret);
		goto out;
	}

	ret = cert->certExchange(cert_hdl,
			ARRAY_SIZE(akl_cmd_for_asa_even),
			&akl_cmd_for_asa_even, &i);
	if (ret != CERT_NO_ERROR) {
		out_printf("error certExchange even, ret: 0x%x, procceed cmd_nr: %d\n",
			ret, i);
		goto out;
	}
	i = 0;
	memcpy(xSession->xPidList, pids, sizeof(pids));
	xSession->xPidCount = ARRAY_SIZE(pids);
	ret = sec->secUseCertKey(xSession,
			0x0010, 1, &i);
	if (ret != CERT_NO_ERROR) {
		out_printf("error secUseCertKey even, ret: 0x%x\n", ret);
		goto out;
	}

	ret = cert->certExchange(cert_hdl,
			ARRAY_SIZE(akl_cmd_for_asa_odd),
			&akl_cmd_for_asa_odd, &i);
	if (ret != CERT_NO_ERROR) {
		out_printf("error certExchange odd, ret: 0x%x, procceed cmd_nr: %d\n",
			ret, i);
		goto out;
	}
	i = 1;
	ret = sec->secUseCertKey(xSession,
			0x0010, 1, &i);
	if (ret != CERT_NO_ERROR) {
		out_printf("error secUseCertKey odd, ret: 0x%x\n", ret);
		goto out;
	}

	ret = secSessionCrypto(xSession, asa_data_in,
				output, sizeof(asa_data_in));
	if (ret != 0) {
		out_printf("Error secSecCrypto, ret = 0x%x\n",ret);
		goto out;
	}

	if(memcmp(output,asa_data_ref,sizeof(asa_data_ref))) {
		out_printf("secSessionDecrypt asa result mismatch\n");
		ret = RET_FAILURE;
		goto out;
	} else {
		out_printf("secSessionDecrypt asa result PASS\n");
	}

out:
	sec->secCloseSession(xSession);
	if (output)
		sec->secFreeBuffer(output);
	return ret;
}

static int ca_akl_generate_key(int akl_sess, int key_pos,
	int algo, struct cert_akl_cmd *cmd,
	int nr_cmds, int parity)
{
	int i = 0;
	struct cert_akl_cmd param;
	struct cert_akl_savekey akl_key;
	int ret = -1;

	for (i=0;i<nr_cmds;i++) {
		memcpy(&param, &cmd[i], sizeof(param));
		ret = cert_akl_exchange(akl_sess, &param);	
		if (ret != 0) {
			out_printf("cert_akl_exchange - error, index = %d\n",i);

			if (CERT_ERROR_EXTIMEOUT == ret) {
				out_printf("Exchange timed out\n");  
				goto out;
			} else {
				out_printf("Exchange error, status=%02X%02X%02X%02X\n",
                                    param.status[0], param.status[1],
                                    param.status[2], param.status[3]);
				goto out;
			}
		}
	}

	memset(&akl_key, 0, sizeof(akl_key));
	akl_key.pos = key_pos;
	akl_key.algo = algo;
	akl_key.parity = parity;
	ret = cert_akl_save_key(akl_sess, &akl_key);    
	if (ret != 0) {
		out_printf("cert_akl_save_key, ret:0x%x\n",ret);
		goto out;
	}

out:
	cert_akl_ack(akl_sess);
	return ret;
}

static int ca_asa_configs(int algo, short *pids, 
	int nr_pids, int ltsid, int debug_en, int ts_fmt, int key_pos)
{
	int sess = -1;
	struct cert_asa_pid add_pid;
	int i = 0;
	int ret = -1;

	sess = cert_asa_open();
	if(sess < 0)
	{
		out_printf("Open sess failed, ret=0x%x\n", sess);
		goto out;
	}
	debug_printf("Open sess: 0x%x\n", sess);

	ret = cert_asa_set_format(sess, ts_fmt);
	if(ret != 0)
	{
		out_printf("setting format, ret:0x%x\n");
		goto out;
	}
	debug_printf("Set format: %d\n", ts_fmt);

	memset(&add_pid, 0, sizeof(add_pid));
	for (i=0;i<nr_pids;i++) {
		add_pid.pid = pids[i];
		debug_printf("Adding pid: 0x%x\n", add_pid.pid);
		add_pid.pos= key_pos;
		add_pid.ltsid = ltsid;
		ret = cert_asa_add_pid(sess, &add_pid);
		if(ret != 0) {
			out_printf("adding pid error, ret:0x%x\n", ret);
			goto out;
		}
	}

	ret = sess;
out:
	return ret;
}

int cert_drv_test(int debug_en, int ts_fmt)
{
	int ret = -1;
	int cert_akl_sess = -1;
	int cert_akl_key_pos = -1;
	int cert_asa_sess = -1;
	int i = 0;
	CE_FOUND_FREE_POS_PARAM pos_param;
	unsigned char *output = NULL;

	debug_printf("...Start...\n");
	
	cert_akl_sess = cert_akl_open();
	if (cert_akl_sess < 0) {
		out_printf("Error cert_akl_open\n"); 
		return cert_akl_sess;
	}
	debug_printf("Open akl: 0x%x\n", cert_akl_sess);

	memset(&pos_param, 0, sizeof(pos_param));
	pos_param.ce_key_level = THREE_LEVEL;
	pos_param.number = 2;
	pos_param.root = 5;
	ret = ce_ioctl(dev_get_by_id(HLD_DEV_TYPE_CE, 0),
			IO_CRYPT_FOUND_FREE_POS,&pos_param);
	if (ret != 0)
		goto out;

	cert_akl_key_pos = pos_param.pos;
	debug_printf("Got key_pos: 0x%x\n", pos_param.pos);

	ret = ca_akl_generate_key(cert_akl_sess, cert_akl_key_pos, CERT_AKL_FOR_ASA,
			akl_cmd_for_asa_even, ARRAY_SIZE(akl_cmd_for_asa_even),
			CERT_AKL_EVEN_PARITY);
	if (ret != 0)
		goto out;

	
	ret = ca_akl_generate_key(cert_akl_sess, cert_akl_key_pos, CERT_AKL_FOR_ASA,
			akl_cmd_for_asa_odd, ARRAY_SIZE(akl_cmd_for_asa_odd),
			CERT_AKL_ODD_PARITY);
	if (ret != 0)
		goto out;

	cert_akl_close(cert_akl_sess); /* close it asap */
	cert_akl_sess = -1;

	cert_asa_sess  = ca_asa_configs(CERT_AKL_FOR_ASA, pids, ARRAY_SIZE(pids),
				ltsid, debug_en, ts_fmt, cert_akl_key_pos);
	if (cert_asa_sess < 0) {
		ret = cert_asa_sess;
		goto out;
	}

	output = calloc(1, sizeof(asa_data_in));
	if (!output) {
		out_printf("calloc failed\n");
		ret = -1;
		goto out;
	}

	ret = cert_asa_decrypt(cert_asa_sess, asa_data_in, output, sizeof(asa_data_in));
	if (ret)
		out_printf("cert_asa_decrypt failed, ret=0x%x\n", ret);
	
	if (!memcmp(asa_data_ref, output, sizeof(asa_data_ref)))
		out_printf("Decrypted data is correct\n");
	else {
		ret = -1;
		out_printf("Decrypted data is wrong\n");
	}
	free(output);

	debug_printf("...End...\n");
out:

	if (cert_asa_sess >= 0)
		cert_asa_close(cert_asa_sess);
	if (cert_akl_key_pos >= 0)
		close(cert_akl_key_pos);
	if (cert_akl_sess >= 0)
		cert_akl_close(cert_akl_sess);

	if (cert_akl_key_pos > 0) {
		ce_ioctl(dev_get_by_id(HLD_DEV_TYPE_CE, 0),
			IO_CRYPT_POS_SET_IDLE, cert_akl_key_pos);
		ce_ioctl(dev_get_by_id(HLD_DEV_TYPE_CE, 0),
			IO_CRYPT_POS_SET_IDLE, cert_akl_key_pos + 1);
	}

	return ret;
}

void csd_sec_cert_entry(void)
{
	int ret = -1;

	otp_init();
	dsc_api_attach();
	ce_api_attach();
	cert_asa_attach();
	cert_akl_attach();

//	nocs_csd_otp_test(1);

	ret = nocs_csd_test(1);
	ret |= cert_drv_test(1, CERT_ASA_TS188);
	ret |= ca_sec_test(1);
	ret |= ca_cert_test(1);

	if (!ret) {
		out_printf("\n\nCSD_SEC_CERT TEST PASS\n\n");
	} else {
		out_printf("\n\nCSD_SEC_CERT TEST FAIL\n\n");
	}

	while(1);
}
