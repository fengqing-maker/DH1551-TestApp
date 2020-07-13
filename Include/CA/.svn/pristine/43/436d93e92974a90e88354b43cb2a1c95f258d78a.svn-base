#ifndef _CI_INTERFACE_H_plus13__
#define _CI_INTERFACE_H_plus13__

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "float.h"
#include <ctype.h>
#include "adi_typedef.h"
#include "adi_os.h"
#include "adi_debug.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef int( *CIMsgCallback )(unsigned int param1, unsigned int param2, unsigned int param3, unsigned int param4);

typedef enum
{
	EM_CI_ALARM_MSG, // ALARM消息
	EM_CI_MMI_MSG, // 界面MMI提示
	EM_CI_STATUS_MSG, // 当前CAM的状态
	EM_CI_MSG_MAX	
}CIMSGType_E;

typedef enum
{
	EM_CI_ALARM_MSG_CAM_OUT, // 提示"Please insert CAM"
	EM_CI_ALARM_MSG_CLEAR,  //消除所有ALARM
	EM_CI_ALARM_MSG_OTHERCA, // 提示"Can not descramble this CA system"
	EM_CI_ALARM_MSG__MAX
}CIMSGTypeAlarm_E;

typedef enum
{
	EM_CI_MMI_MSG_CLOSE, // CICAM命令--关闭所有的MMI
	EM_CI_MMI_MSG_LIST, // CICAM命令--界面MMI list消息显示(CIMMIEvent_S结构体地址), 提示性消息
	EM_CI_MMI_MSG_MENU, // CICAM命令--界面MMI Menu消息显示(CIMMIEvent_S结构体地址), 需要调用ADICIEnterSubMenuItem回应
	EM_CI_MMI_MSG_ENQ, //  CICAM命令--界面MMI Enq消息显示(CIEnq_S结构体地址), 需要调用ADICIEnterSubMenuItem回应
	EM_CI_MMI_MSG_MAX
}CIMSGTypeMMI_E;

typedef enum
{
	EM_CI_STATUS_CAM_IN,
	EM_CI_STATUS_CAM_OUT,	
	EM_CI_STATUS_CAM_OK,
	EM_CI_STATUS_CAM_MAX
}CIMSGTypeStatus_E;

#define MAX_TEXT_LEN (128)
#define MAX_MAX_TEXT_LEN (256)

typedef struct
{
	unsigned char blind_answer; // 1:输入不可见(pin等), 0:输入可见
	unsigned char answer_text_length; // 需要用户输入字符的长度
	unsigned char info_text_char[MAX_MAX_TEXT_LEN+1]; // 显示的提示信息
	unsigned int  info_text_char_len;
}CIEnq_S;

typedef struct
{
	unsigned char answ_id; // 0:取消  1:确认
	unsigned char answ_text_char[MAX_TEXT_LEN+1]; // 用户的输入
	unsigned int  answ_text_char_len;
}CIAnsw_S;


#define CI_ITEM_MAX_NO (24)

typedef struct 
{
	unsigned char ucItem_NB; // aacMessage条目的个数
	unsigned int nTag_Value; // app忽略此值
	char acTitle[MAX_TEXT_LEN+1]; // 顶标题 
	char acSubtitle[MAX_TEXT_LEN+1]; // 二级顶标题 
	char acBottom[MAX_TEXT_LEN+1]; // 底标题 
	char aacMessage[CI_ITEM_MAX_NO][MAX_TEXT_LEN+1]; // 有ucItem_NB条消息,最大支持CI_ITEM_MAX_NO个
}CIMMIEvent_S;


typedef struct
{

	unsigned char application_type; // 0:Conditional_Access  1:Electronic_Programme_Guide
	unsigned short application_manufacturer;
	unsigned short manufacturer_code;
	unsigned char menu_string_length;
	unsigned char text_char[MAX_MAX_TEXT_LEN];
}CIAppInfo_S;

/*
 * Description:查看CI主菜单
 *
 * Note:成功后, App会收到消息 EM_CI_MMI_MSG_MENU, 消息带结构体CIMMIEvent_S地址,
 *        其中ucItem_NB代表子菜单的个数, aacMessage[0]为第一级子菜单, aacMessage[1]为第二级子菜单......
 *        acTitle 为菜单标题,acSubtitle为菜单子标题, acBottom为菜单底部提示
 *
 * Parameters : 
 *				输入参数
 *					无
 *
 *				输出参数
 *					无
 *
 * Returns	  :  0: 成功
 *				 其他: 失败 
 */
int ADICIEnterMainMenu(void);

/*
 * Description: 进入CI相关子菜单
 *
 * Parameters : 
 *				输入参数
 *					ucChoice_ref: 当为0x00表示退出菜单
 *                                当为0x01表示选择 第一个item-->aacMessage[0]下的子菜单
 *                                当为0x02表示选择 第二个item-->aacMessage[1]下的子菜单
 *                                当为0x03表示选择 第三个item-->aacMessage[2]下的子菜单
 *                                依次类推......
 *
 *				输出参数
 *					无
 *
 * Returns	  :  0: 成功
 *				 其他: 失败 
 */
int ADICIEnterSubMenuItem(unsigned char ucChoice_ref);

/*
 * Description: 对MMI_ENQ消息的回应
 *
 * Parameters : 
 *				输入参数
 *					Answ: user input
 *
 *				输出参数
 *					无
 *
 * Returns	  :  0: 成功
 *				 其他: 失败 
 */
int ADICIAnswEnq(CIAnsw_S *pAnsw);


/*
 * Description: 获取CI Application信息
 *
 * Parameters : 
 *				输入参数
 *					pInfo: app info
 *
 *				输出参数
 *					无
 *
 * Returns	  : VOID
 *
 */
void ADICIGetApplicationInfo(CIAppInfo_S *pInfo);

/*
 * Description: 用户主动关闭所有的MMI回话
 *
 * Parameters : 
 *				输入参数
 *					无
 *
 *				输出参数
 *					无
 *
 * Returns	  : VOID
 *
 */
void ADICICloseMMI(void);

/*
 * Description: 设置烧录好的证书地址和CC交互使用的存储相关Key的地址
 *
 * Parameters : 
 *				输入参数
 *					unCredentialsAddr: 证书地址
 *                  unCCRelatedKeyAddr: CC交互使用到的需要保存的key的地址
 *
 *				输出参数
 *					无
 *
 * Returns	  : VOID
 *
 */
void ADICISetFlashAddress(unsigned int unCredentialsAddr, unsigned int unCCRelatedKeyAddr);

#ifdef  __cplusplus
}
#endif

#endif 


