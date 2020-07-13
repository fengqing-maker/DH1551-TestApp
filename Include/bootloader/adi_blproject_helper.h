/*
 * adi_blproject_helper.h
 *
 * ��ͷ�ļ�ר�Ÿ�booter loader����ʹ��
 * Ӧ��app���̲��õ��ô�ͷ�ļ��еĽӿ�
 *
 */

#ifndef _ADI_BLPROJECT_HELPER_H_345___
#define _ADI_BLPROJECT_HELPER_H_345___

#include "adi_tuner.h"
#include "adi_panel.h"
#include "adi_bootloader_common.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef enum
{
	E_ADIBL_CHECKSUM_ALGORITHM_CRC32 = 0x00,/*non secure box*/
	E_ADIBL_CHECKSUM_ALGORITHM_MAC = 0x01,/*secure box*/
	E_ADIBL_CHECKSUM_ALGORITHM_SHA1 = 0x02, /*secure box*/
	E_ADIBL_CHECKSUM_ALGORITHM_SHA256 = 0x03,/*secure box*/
	E_ADIBL_CHECKSUM_ALGORITHM_MIN_RESERVED = 0x04
}ADIBLChecksumAlgorithm_E;

typedef enum
{
	E_ADIBL_CASTPAL_VRF= 0, /* Ĭ��Castpal ����*/
	E_ADIBL_VMX_VRF = 1,    /* VMX �ⲿע��У��*/
	E_ADIBL_CONAX_VRF = 2,  /* Conax �ⲿע��У�� */
	E_ADIBL_MAX_VRF = 0xF,  /* ��App ��RC �ϲ�Ϊһ��app �ļ�����ʱ����ΪMAX ����, ����У��*/
}ADIBLVerifyType_E;

/*
 * Description: castpalͨ�ù淶booter��ں���
 *
 * Note: ר��Ϊbooter���̵���, �������̽�ֹ����
 *
 * Parameters : ��
 *
 * Returns	  :   0  �ɹ�
 *			   ����  ʧ��
 */
int ADIBLBooterEnter(void);

/*
 * Description: castpalͨ�ù淶loader��ں���
 *
 * Note: ר��Ϊloader���̵���, �������̽�ֹ����
 *
 * Parameters : ��
 *
 * Returns	  :   0  �ɹ�
 *			   ����  ʧ��
 */
int ADIBLLoaderEnter(void);

/*
 * Description: Irdeto�淶booter��ں���
 *
 * Note:ר��Ϊbooter���̵���, �������̽�ֹ����
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoProcessBooter(void);

/*
 * Description: Irdetoͨ�ù淶loader��ں���, 
 *
 * ר��Ϊloader���̵���, �������̽�ֹ����
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLIrdetoProcessLoader(void);

/*
 * Description: ��ʼ��bl��Ҫʹ�õ�osg
 *
 * Note: booter/loader���̱�����ô˽ӿ�,����BLû�н��� 
 *
 * Parameters : pOsgInfo osg�����Ϣ,�ο�ADIBLOSGInfo_S����
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLOSGInit(const ADIBLOSGInfo_S *pOsgInfo);

/*
 * Description: enable Bcm boot osg
 *
 * Note: booter���̵���
 *
 * Parameters : 0:disable,  1:enable
 *
 * Returns	  :
 *		
 */
void ADIBLEnableBcmBootOsg(int enable);

/*
 * Description: ��ȡflash�е�logo����ʾ, ��Ҫ��ʾlogo������flash������,������Բ�����
 *
 * Note: booter��Ҫ��ʾlogo�͵��ô˽ӿ�,���򲻵���
 *
 * Parameters :  unLogoFlashAddress logo��flash��ַ(logoͷ+jpeglogo����)
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
int ADIBLShowJpegLogoFromFlash(unsigned int unLogoFlashAddress);

/*
 * Description: ��ȡBLĳһ��flash����
 *
 * Note: booter/loader/dvt������Ҫ��flashУ�� �ṩ��flash�ӿ�
 *
 * Parameters :  stBlock: ������ַ������Ϣ
 *               pucData: buffer�ռ�
 *               nLen: buffer����
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLReadFlash(ADIBLFlashBlock_S stBlock, unsigned char* pucData, unsigned int nLen);

/*
 * Description: дBLĳһ��flash����
 *
 * Note: booter/loader/dvt������Ҫ��flashУ�� �ṩдflash�ӿ�
 *
 * Parameters :  stBlock: ������ַ������Ϣ
 *               pucData: buffer�ռ�
 *               nLen: buffer����
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
int ADIBLWriteFlash(ADIBLFlashBlock_S stBlock, unsigned char* pucData, unsigned int nLen);

/*
 * Description: ��������CRC32
 *
 * Note: booter/loader/dvt������Ҫ��У������crc�ӿ�
 *
 * Parameters :  pvDataIn: ������ʼ��ַ
 *               unSizeInBytes: ���ݿռ䳤��
 *
 * Returns	  :    0 �ɹ�
 *              ���� ʧ��
 *			   
 */
unsigned int ADIBLCalculateCRC32(void* pvDataIn, unsigned int unSizeInBytes);

/*
 * Description: ����booter��ǰ���/ң���������ĳ�ʱʱ��
 *
 * Note: �˽ӿ�Ϊ������ӵļ��ݽӿڽ����Щƽ̨booter����Ӧ��ʱʱ��̫��, ���Բ����� 
 *
 * Parameters : unTimeout: �����õİ�����ʱʱ��, ��λms
 *
 * Returns	  : 
 *			   
 */
void ADIBLSetBootKeyTimeout(unsigned int unTimeout);

/*
 * Description: ����booter���Ƿ���Ҫ֧��ң����
 *
 * Note: ��������booter���̵���
 *
 * Parameters : bEnable �Ƿ�֧��ң��������
 *
 * Returns	  : 
 *			   
 */
void ADIBLSetBooterIREnable(ADI_BOOL bEnable);

/*
 * Description: ����booter��ǰ���ֻ֧��scanģʽ
 *
 * Note: ��������booter���̵���
 *
 * Parameters : bEnable 
 *
 * Returns	  : 
 *			   
 */
void ADIBLSetBooterOnlyPanelScan(ADI_BOOL bEnable);

/*
 * Description: ң�����ص�, booter/loader�л�ʹ��, ��Ҫ��Ӧ�ù�����ע��
 *
 * Note: booter/loader���̵���,����bl�о���ң�ػص���, ���Խ��а�������
 *
 * Parameters : �ص�����
 *
 * Returns	  : 
 *			   
 */
void ADIBLIRCallBack(ADIKeyCallbackType eCallbackType ,void * pvUserData);

/*
 * Description: ����ǰ����ֵ, ��Щƽ̨ǰ��尴����ȫ������Ӵ˽ӿڼ���
 *
 * Note: �ṩ��booter/loader���̵���
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
void ADIBLIRPanelSetKeyValue(ADIBLPanelKey_E nKeyType, unsigned int  unKey);

/*
 * Description: ��������ǰ����źŵ�(������powerҲ������signal��)
 *
 * Note: �ṩ��booter/loader���̵���
 *
 * Parameters : 
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
void ADIBLSetSignalLightFlag(ADIPanelLightName_E eSignalLightFlag);

/*
 * Description: Irdeto bl V5 ��Ŀʹ�� ��������У���㷨
 *
 * Note: v5 booter/loader ����ר��, �߰���Ŀ��������Ϊcrc32, ��Ҫ����Ϊ���Ӹ߼��㷨
 *
 * Parameters : eAlg: У���㷨
 *
 * Returns	  : 0  �ɹ�
 *			   -1  ʧ��
 */
void ADIBLSetChecksumAlgorithm(ADIBLChecksumAlgorithm_E eAlg);

/*
 * Description: booter�Ƿ���ʾ������
 *
 * Note: 
 *
 * Parameters : bEnable  ADI_TRUE:  ��ʾ������ 
 *						 ADI_FALSE: ����ʾ������
 *
 * Returns	  : 
 *			   
 */
void ADIBLDisplayBooterProgress(ADI_BOOL bEnable);

/*
 * Description: ����baseapp�µ�ң����
 *
 * Note: pequiplistΪlist����, listnumΪADIIREquipList_S�ĸ���
 *
 *
 * Returns	  : 
 *			   
 */
void ADIBLBaseappSetIREquipment(ADIIREquipList_S* pequiplist, int listnum);

/*
signature: is the data array stored as signature value for the image. It is not necessarily an encrypted signature

src: is the data array of size len. The decrypted image is available there after decryption

tmp: is the data array of size len (not overlapping with src array) only used temporarily src and tmp might be,
depending on some chipset features, restricted to some values,e.g. beginning of a long word address or something like that.

len: is the length of the data array, it must be a multiple of 16bytes (padded at the end)

maxLen: defines the max-size of application, it must be greater or equal to len. This length value must be equal to 
the size of the file that has been used for signing. In most cases this value will be equal to len, as the compile file will be signed.

mode: gives the mode the verification is done, for flash application (0), to be programmed into
the flash before the flash is mounted on the PCB in production or after re-encryption, or for loader (1) to be used by serial or OTA

errorCode: is a pointer to a value that tells the reason for not having a valid image
1 means no valid signature found - reboot
2 means store src part to flash and reboot after it

return value:
0 indicates do not start the application
1 indicates the application can be started
*/
typedef int  (* vmx_verify_Fn)( unsigned char * signature, unsigned char * src, unsigned char * tmp, unsigned int len, unsigned int  maxLen, unsigned char  mode,  unsigned char  *errorCode );

/*
 * Description: Enter Verimatrix bootstrap 
 *
 * Note: 
 *
 * Parameters : fn: Verimatrix verify function
 *
 * Returns	  : 
 *			   
 */
int ADIBLVMXBooterEnter(vmx_verify_Fn fn);


/*
 * Description: Enter Verimatrix upgradeloader
 *
 * Note: 
 *
 * Parameters : fn: Verimatrix verify function
 *
 * Returns	  : 
 *			   
 */
int ADIBLVMXLoaderEnter(vmx_verify_Fn fn);

typedef struct
{
	unsigned int m_unTunerCount; // tuner����
	unsigned int m_unTunerTypeList[3];  // ֧�ֵ�TunerType�б�ADITunerType_E
	unsigned int m_unTunerTypeListCount; // TunerType����
}ADIBLTunerCfg_S;

void ADIBLConfigTuner(ADIBLTunerCfg_S *pADIBLTunerCfg);

#ifdef	__cplusplus
}
#endif


#endif


