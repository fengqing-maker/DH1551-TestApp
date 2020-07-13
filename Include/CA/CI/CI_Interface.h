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
	EM_CI_ALARM_MSG, // ALARM��Ϣ
	EM_CI_MMI_MSG, // ����MMI��ʾ
	EM_CI_STATUS_MSG, // ��ǰCAM��״̬
	EM_CI_MSG_MAX	
}CIMSGType_E;

typedef enum
{
	EM_CI_ALARM_MSG_CAM_OUT, // ��ʾ"Please insert CAM"
	EM_CI_ALARM_MSG_CLEAR,  //��������ALARM
	EM_CI_ALARM_MSG_OTHERCA, // ��ʾ"Can not descramble this CA system"
	EM_CI_ALARM_MSG__MAX
}CIMSGTypeAlarm_E;

typedef enum
{
	EM_CI_MMI_MSG_CLOSE, // CICAM����--�ر����е�MMI
	EM_CI_MMI_MSG_LIST, // CICAM����--����MMI list��Ϣ��ʾ(CIMMIEvent_S�ṹ���ַ), ��ʾ����Ϣ
	EM_CI_MMI_MSG_MENU, // CICAM����--����MMI Menu��Ϣ��ʾ(CIMMIEvent_S�ṹ���ַ), ��Ҫ����ADICIEnterSubMenuItem��Ӧ
	EM_CI_MMI_MSG_ENQ, //  CICAM����--����MMI Enq��Ϣ��ʾ(CIEnq_S�ṹ���ַ), ��Ҫ����ADICIEnterSubMenuItem��Ӧ
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
	unsigned char blind_answer; // 1:���벻�ɼ�(pin��), 0:����ɼ�
	unsigned char answer_text_length; // ��Ҫ�û������ַ��ĳ���
	unsigned char info_text_char[MAX_MAX_TEXT_LEN+1]; // ��ʾ����ʾ��Ϣ
	unsigned int  info_text_char_len;
}CIEnq_S;

typedef struct
{
	unsigned char answ_id; // 0:ȡ��  1:ȷ��
	unsigned char answ_text_char[MAX_TEXT_LEN+1]; // �û�������
	unsigned int  answ_text_char_len;
}CIAnsw_S;


#define CI_ITEM_MAX_NO (24)

typedef struct 
{
	unsigned char ucItem_NB; // aacMessage��Ŀ�ĸ���
	unsigned int nTag_Value; // app���Դ�ֵ
	char acTitle[MAX_TEXT_LEN+1]; // ������ 
	char acSubtitle[MAX_TEXT_LEN+1]; // ���������� 
	char acBottom[MAX_TEXT_LEN+1]; // �ױ��� 
	char aacMessage[CI_ITEM_MAX_NO][MAX_TEXT_LEN+1]; // ��ucItem_NB����Ϣ,���֧��CI_ITEM_MAX_NO��
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
 * Description:�鿴CI���˵�
 *
 * Note:�ɹ���, App���յ���Ϣ EM_CI_MMI_MSG_MENU, ��Ϣ���ṹ��CIMMIEvent_S��ַ,
 *        ����ucItem_NB�����Ӳ˵��ĸ���, aacMessage[0]Ϊ��һ���Ӳ˵�, aacMessage[1]Ϊ�ڶ����Ӳ˵�......
 *        acTitle Ϊ�˵�����,acSubtitleΪ�˵��ӱ���, acBottomΪ�˵��ײ���ʾ
 *
 * Parameters : 
 *				�������
 *					��
 *
 *				�������
 *					��
 *
 * Returns	  :  0: �ɹ�
 *				 ����: ʧ�� 
 */
int ADICIEnterMainMenu(void);

/*
 * Description: ����CI����Ӳ˵�
 *
 * Parameters : 
 *				�������
 *					ucChoice_ref: ��Ϊ0x00��ʾ�˳��˵�
 *                                ��Ϊ0x01��ʾѡ�� ��һ��item-->aacMessage[0]�µ��Ӳ˵�
 *                                ��Ϊ0x02��ʾѡ�� �ڶ���item-->aacMessage[1]�µ��Ӳ˵�
 *                                ��Ϊ0x03��ʾѡ�� ������item-->aacMessage[2]�µ��Ӳ˵�
 *                                ��������......
 *
 *				�������
 *					��
 *
 * Returns	  :  0: �ɹ�
 *				 ����: ʧ�� 
 */
int ADICIEnterSubMenuItem(unsigned char ucChoice_ref);

/*
 * Description: ��MMI_ENQ��Ϣ�Ļ�Ӧ
 *
 * Parameters : 
 *				�������
 *					Answ: user input
 *
 *				�������
 *					��
 *
 * Returns	  :  0: �ɹ�
 *				 ����: ʧ�� 
 */
int ADICIAnswEnq(CIAnsw_S *pAnsw);


/*
 * Description: ��ȡCI Application��Ϣ
 *
 * Parameters : 
 *				�������
 *					pInfo: app info
 *
 *				�������
 *					��
 *
 * Returns	  : VOID
 *
 */
void ADICIGetApplicationInfo(CIAppInfo_S *pInfo);

/*
 * Description: �û������ر����е�MMI�ػ�
 *
 * Parameters : 
 *				�������
 *					��
 *
 *				�������
 *					��
 *
 * Returns	  : VOID
 *
 */
void ADICICloseMMI(void);

/*
 * Description: ������¼�õ�֤���ַ��CC����ʹ�õĴ洢���Key�ĵ�ַ
 *
 * Parameters : 
 *				�������
 *					unCredentialsAddr: ֤���ַ
 *                  unCCRelatedKeyAddr: CC����ʹ�õ�����Ҫ�����key�ĵ�ַ
 *
 *				�������
 *					��
 *
 * Returns	  : VOID
 *
 */
void ADICISetFlashAddress(unsigned int unCredentialsAddr, unsigned int unCCRelatedKeyAddr);

#ifdef  __cplusplus
}
#endif

#endif 


