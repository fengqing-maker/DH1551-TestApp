/*
 * adi_blproject_helper.h
 *
 * 此头文件专门给booter loader工程使用
 * 应用app工程不得调用此头文件中的接口
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
	E_ADIBL_CASTPAL_VRF= 0, /* 默认Castpal 类型*/
	E_ADIBL_VMX_VRF = 1,    /* VMX 外部注册校验*/
	E_ADIBL_CONAX_VRF = 2,  /* Conax 外部注册校验 */
	E_ADIBL_MAX_VRF = 0xF,  /* 当App 和RC 合并为一个app 文件升级时设置为MAX 类型, 不做校验*/
}ADIBLVerifyType_E;

/*
 * Description: castpal通用规范booter入口函数
 *
 * Note: 专门为booter工程调用, 其他工程禁止调用
 *
 * Parameters : 无
 *
 * Returns	  :   0  成功
 *			   其他  失败
 */
int ADIBLBooterEnter(void);

/*
 * Description: castpal通用规范loader入口函数
 *
 * Note: 专门为loader工程调用, 其他工程禁止调用
 *
 * Parameters : 无
 *
 * Returns	  :   0  成功
 *			   其他  失败
 */
int ADIBLLoaderEnter(void);

/*
 * Description: Irdeto规范booter入口函数
 *
 * Note:专门为booter工程调用, 其他工程禁止调用
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoProcessBooter(void);

/*
 * Description: Irdeto通用规范loader入口函数, 
 *
 * 专门为loader工程调用, 其他工程禁止调用
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLIrdetoProcessLoader(void);

/*
 * Description: 初始化bl需要使用的osg
 *
 * Note: booter/loader工程必须调用此接口,否则BL没有界面 
 *
 * Parameters : pOsgInfo osg相关信息,参考ADIBLOSGInfo_S定义
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLOSGInit(const ADIBLOSGInfo_S *pOsgInfo);

/*
 * Description: enable Bcm boot osg
 *
 * Note: booter工程调用
 *
 * Parameters : 0:disable,  1:enable
 *
 * Returns	  :
 *		
 */
void ADIBLEnableBcmBootOsg(int enable);

/*
 * Description: 读取flash中的logo并显示, 需要显示logo才配置flash并调用,否则可以不调用
 *
 * Note: booter需要显示logo就调用此接口,否则不调用
 *
 * Parameters :  unLogoFlashAddress logo的flash地址(logo头+jpeglogo数据)
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
int ADIBLShowJpegLogoFromFlash(unsigned int unLogoFlashAddress);

/*
 * Description: 读取BL某一个flash分区
 *
 * Note: booter/loader/dvt工程需要读flash校验 提供读flash接口
 *
 * Parameters :  stBlock: 分区地址长度信息
 *               pucData: buffer空间
 *               nLen: buffer长度
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLReadFlash(ADIBLFlashBlock_S stBlock, unsigned char* pucData, unsigned int nLen);

/*
 * Description: 写BL某一个flash分区
 *
 * Note: booter/loader/dvt工程需要读flash校验 提供写flash接口
 *
 * Parameters :  stBlock: 分区地址长度信息
 *               pucData: buffer空间
 *               nLen: buffer长度
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
int ADIBLWriteFlash(ADIBLFlashBlock_S stBlock, unsigned char* pucData, unsigned int nLen);

/*
 * Description: 计算数据CRC32
 *
 * Note: booter/loader/dvt工程需要读校验数据crc接口
 *
 * Parameters :  pvDataIn: 数据起始地址
 *               unSizeInBytes: 数据空间长度
 *
 * Returns	  :    0 成功
 *              其他 失败
 *			   
 */
unsigned int ADIBLCalculateCRC32(void* pvDataIn, unsigned int unSizeInBytes);

/*
 * Description: 设置booter中前面板/遥控器按键的超时时间
 *
 * Note: 此接口为额外添加的兼容接口解决有些平台booter中响应超时时间太长, 可以不调用 
 *
 * Parameters : unTimeout: 新配置的按键超时时间, 单位ms
 *
 * Returns	  : 
 *			   
 */
void ADIBLSetBootKeyTimeout(unsigned int unTimeout);

/*
 * Description: 设置booter中是否需要支持遥控器
 *
 * Note: 仅仅限于booter工程调用
 *
 * Parameters : bEnable 是否支持遥控器按键
 *
 * Returns	  : 
 *			   
 */
void ADIBLSetBooterIREnable(ADI_BOOL bEnable);

/*
 * Description: 设置booter中前面板只支持scan模式
 *
 * Note: 仅仅限于booter工程调用
 *
 * Parameters : bEnable 
 *
 * Returns	  : 
 *			   
 */
void ADIBLSetBooterOnlyPanelScan(ADI_BOOL bEnable);

/*
 * Description: 遥控器回调, booter/loader中会使用, 需要在应用工程中注册
 *
 * Note: booter/loader工程调用,这样bl中就有遥控回调了, 可以进行按键处理
 *
 * Parameters : 回调参数
 *
 * Returns	  : 
 *			   
 */
void ADIBLIRCallBack(ADIKeyCallbackType eCallbackType ,void * pvUserData);

/*
 * Description: 设置前面板键值, 有些平台前面板按键不全所以添加此接口兼容
 *
 * Note: 提供给booter/loader工程调用
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
void ADIBLIRPanelSetKeyValue(ADIBLPanelKey_E nKeyType, unsigned int  unKey);

/*
 * Description: 兼容设置前面板信号灯(可以是power也可以是signal灯)
 *
 * Note: 提供给booter/loader工程调用
 *
 * Parameters : 
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
void ADIBLSetSignalLightFlag(ADIPanelLightName_E eSignalLightFlag);

/*
 * Description: Irdeto bl V5 项目使用 设置数据校验算法
 *
 * Note: v5 booter/loader 工程专用, 高安项目不能设置为crc32, 需要设置为更加高级算法
 *
 * Parameters : eAlg: 校验算法
 *
 * Returns	  : 0  成功
 *			   -1  失败
 */
void ADIBLSetChecksumAlgorithm(ADIBLChecksumAlgorithm_E eAlg);

/*
 * Description: booter是否显示进度条
 *
 * Note: 
 *
 * Parameters : bEnable  ADI_TRUE:  显示进度条 
 *						 ADI_FALSE: 不显示进度条
 *
 * Returns	  : 
 *			   
 */
void ADIBLDisplayBooterProgress(ADI_BOOL bEnable);

/*
 * Description: 设置baseapp下的遥控器
 *
 * Note: pequiplist为list数组, listnum为ADIIREquipList_S的个数
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
	unsigned int m_unTunerCount; // tuner个数
	unsigned int m_unTunerTypeList[3];  // 支持的TunerType列表ADITunerType_E
	unsigned int m_unTunerTypeListCount; // TunerType个数
}ADIBLTunerCfg_S;

void ADIBLConfigTuner(ADIBLTunerCfg_S *pADIBLTunerCfg);

#ifdef	__cplusplus
}
#endif


#endif


