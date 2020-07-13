#ifndef _ADI_HDICOMMON_H_
#define _ADI_HDICOMMON_H_


#ifdef __cplusplus
extern "C" {
#endif

#define ADI_HDI_TIMEOUT_INFINITY		(unsigned int)0xffffffff
#define ADI_HDI_TIMEOUT_IMMEDIATE	0


//ң������ǰ��尴��
#define ADI_VK_POWER					0xffff  // ������
#define ADI_VK_0						0x30	// ���ּ�0
#define ADI_VK_1						0x31	// ���ּ�1
#define ADI_VK_2						0x32	// ���ּ�2
#define ADI_VK_3						0x33	// ���ּ�3
#define ADI_VK_4						0x34	// ���ּ�4
#define ADI_VK_5						0x35	// ���ּ�5
#define ADI_VK_6						0x36	// ���ּ�6
#define ADI_VK_7						0x37	// ���ּ�7
#define ADI_VK_8						0x38	// ���ּ�8
#define ADI_VK_9						0x39	// ���ּ�9
#define ADI_VK_OK			       	 	0x0D    // ȷ�ϼ�
#define ADI_VK_TOGGLE                	0x0280  // ���ؼ�
#define ADI_VK_EXIT					    0x1B    // �˳���
#define ADI_VK_PAGE_UP				    0x21    // ���Ϸ�ҳ
#define ADI_VK_PAGE_DOWN			    0x22    // ���·�ҳ
#define ADI_VK_LEFT					    0x25    // ����� 
#define ADI_VK_UP						0x26    // ���ϼ�
#define ADI_VK_RIGHT					0x27    // ���Ҽ�
#define ADI_VK_DOWN					    0x28    // ���¼�
#define ADI_VK_CHANNEL_UP				0x01AB	// Ƶ�����Ӽ�
#define ADI_VK_CHANNEL_DOWN			    0x01AC  // Ƶ�����ټ�
#define ADI_VK_VOLUME_UP				0x01BF  // �������Ӽ�
#define ADI_VK_VOLUME_DOWN			    0x01C0	// �������ټ�
#define ADI_VK_MENU					    0X01D4  // �˵���
#define ADI_VK_MUTE					    0x01C1	// ������
#define ADI_VK_GUIDE					0x01CA	// ��Ŀָ�ϼ�
#define ADI_VK_AUDIO					0x0197  // ������
#define ADI_VK_COLORED_KEY_0	        0X0193  // ��ɫ��
#define ADI_VK_COLORED_KEY_1	        0X0194  // ��ɫ��
#define ADI_VK_COLORED_KEY_2	        0X0195  // ��ɫ��
#define ADI_VK_COLORED_KEY_3	        0X0196  // ��ɫ��

#define ADI_VK_PROG_LIST                0x0281  // Ƶ���б��
#define ADI_VK_TV_RADIO                 0x0282  // ����/��Ƶ�㲥��
#define ADI_VK_CARD_INFO             	0x0283  // ����Ϣ��
#define ADI_VK_MAIL_INFO             	0x0284  // �ʼ���
#define ADI_VK_VOD                   	0x0285  // �㲥��
#define ADI_VK_SYSSET					0x0286  // ϵͳ���ü�
#define ADI_VK_HELP						0x1E3   // ������
#define ADI_VK_SERV						0x01D0  // ��Ѷ��
#define ADI_VK_FAV						0x01E0	// ϲ����
#define ADI_VK_TV						0x01E1	// ���Ӽ�
#define ADI_VK_RADIO					0x01E2  // �㲥��
#define ADI_VK_INFO						0x01C9  // ��Ϣ��
#define ADI_VK_LANGUAGE					0x0198  // ��/Ӣ���л���
#define ADI_VK_INPUT                 	0x84	//  ���뷨����

#define ADI_VK_REFRESH              	0x80    //  ˢ����ҳ 
#define ADI_VK_FORWARD               	0x81	//  ǰ������ʷ��ҳ�� 
#define ADI_VK_BACK                  	0x82	//  ���ˣ���ʷ��ҳ�� 
#define ADI_VK_BROWSER                	0x83	//  ��������� 
#define ADI_VK_RECORD       	        0xf10	// ¼�Ƽ�
#define ADI_VK_PLAY 					0xf16	// ����
#define ADI_VK_STOP 					0xf17	// ֹͣ����
#define ADI_VK_PAUSE 					0xf18   // ��ͣ
#define ADI_VK_RW   					0xf21	// ����
#define ADI_VK_FF   					0xf22	// ���
#define ADI_VK_SF   					0xf23	// ����
#define ADI_VK_SB   					0xf24	// ����

#define ADI_VK_POUND					0x23	// "#"��
#define ADI_VK_ASTERISK			    	0x2A	// "*"��
#define ADI_VK_SEEK                  	0xf28   // ��λ��
#define ADI_VK_TAB						0x09	// Tab��

#define ADI_VK_END            			0x23	// END��
#define ADI_VK_HOME           			0x24 	// Home��
#define ADI_VK_INSERT         			0x9B	// Insert��
#define ADI_VK_DELETE        			0x7F	// Delete��

#define ADI_VK_TELETEXT					0x01CB	//��Ļ��
#define ADI_VK_SUBTITLE					0x01CC	//subtitle��

#define ADI_VK_RECALL					0xf24	//Recall��
#define ADI_VK_TIMER_REC				0xf25	//��ʾԤ���б�

#define ADI_VK_GAME						0xf29	//��Ϸ��ݼ�
#define ADI_VK_ADS						0xf2A	//����ݼ�
#define ADI_VK_NVOD						0xf2B	//NVOD��ݼ�
#define ADI_VK_STOCK					0xf2C	//��Ʊ��ݼ�
#define ADI_VK_PAYOUT					0xf2D	//֧����ݼ�
#define ADI_VK_PORTAL					0xf2E	//Portal��ݼ�
		
#define ADI_VK_LBUTTON					0x01	//������
#define ADI_VK_RBUTTON					0x02	//����Ҽ�
#define ADI_VK_CANCEL					0x03	//ȡ������Ctrl-Break��
#define ADI_VK_MBUTTON					0x04	//����м�
#define ADI_VK_CLEAR					0x0C	//Num Lock�ر�ʱ�����ּ���5
#define ADI_VK_SHIFT					0x10	//Shift��
#define ADI_VK_CONTROL					0x11	//Ctrl��
#define ADI_VK_ALT						0x12	//Alt��
#define ADI_VK_CAPITAL					0x14	//Caps lock��
#define ADI_VK_SPACE					0x20	//�ո��
#define ADI_VK_SELECT					0x29	//Select��
#define ADI_VK_PRINT					0x2A	//Print��
#define ADI_VK_EXECUTE					0x2B	//Execute��
#define ADI_VK_SNAPSHOT					0x2C	//Print Screen��
#define ADI_VK_A						0x41	//��ĸ��A
#define ADI_VK_B						0x42	//��ĸ��B
#define ADI_VK_C						0x43	//��ĸ��C
#define ADI_VK_D						0x44	//��ĸ��D
#define ADI_VK_E						0x45	//��ĸ��E
#define ADI_VK_F						0x46	//��ĸ��F
#define ADI_VK_G						0x47	//��ĸ��G
#define ADI_VK_H						0x48	//��ĸ��H
#define ADI_VK_I						0x49	//��ĸ��I
#define ADI_VK_J						0x4A	//��ĸ��J
#define ADI_VK_K						0x4B	//��ĸ��K
#define ADI_VK_L						0x4C	//��ĸ��L
#define ADI_VK_M						0x4D	//��ĸ��M
#define ADI_VK_N						0x4E	//��ĸ��N
#define ADI_VK_O						0x4F	//��ĸ��O
#define ADI_VK_P						0x50	//��ĸ��P
#define ADI_VK_Q						0x51	//��ĸ��Q
#define ADI_VK_R						0x52	//��ĸ��R
#define ADI_VK_S						0x53	//��ĸ��S
#define ADI_VK_T						0x54	//��ĸ��T
#define ADI_VK_U						0x55	//��ĸ��U
#define ADI_VK_V						0x56	//��ĸ��V
#define ADI_VK_W						0x57	//��ĸ��W
#define ADI_VK_X						0x58	//��ĸ��X
#define ADI_VK_Y						0x59	//��ĸ��Y
#define ADI_VK_Z						0x5A	//��ĸ��Z
#define ADI_VK_LWIN						0x6B	//�󴰿�
#define ADI_VK_RWIN						0x7C	//�Ҵ���
#define ADI_VK_NUMPAD0					0x60	//С����0��
#define ADI_VK_NUMPAD1					0x61	//С����1��
#define ADI_VK_NUMPAD2					0x62	//С����2��
#define ADI_VK_NUMPAD3					0x63	//С����3��
#define ADI_VK_NUMPAD4					0x64	//С����4��
#define ADI_VK_NUMPAD5					0x65	//С����5��
#define ADI_VK_NUMPAD6					0x66	//С����6��
#define ADI_VK_NUMPAD7					0x67	//С����7��
#define ADI_VK_NUMPAD8					0x68	//С����8��
#define ADI_VK_NUMPAD9					0x69	//С����9��
#define ADI_VK_MULTIPLY					0x6A	//С����*
#define ADI_VK_ADD						0x6B	//С����+
#define ADI_VK_SEPARATER				0x6C	//ENTER��
#define ADI_VK_SUBTRACT					0x6D	//С����-
#define ADI_VK_DECIMAL					0x6E	//С����.
#define ADI_VK_DIVIDE					0x6F	//С����/
#define ADI_VK_F1						0x70	//F1��
#define ADI_VK_F2						0x71	//F2��
#define ADI_VK_F3						0x72	//F3��
#define ADI_VK_F4						0x73	//F4��
#define ADI_VK_F5						0x74	//F5��
#define ADI_VK_F6						0x75	//F6��
#define ADI_VK_F7						0x76	//F7��
#define ADI_VK_F8						0x77	//F8��
#define ADI_VK_F9						0x78	//F9��
#define ADI_VK_F10						0x79	//F10��
#define ADI_VK_F11						0x7A	//F11��
#define ADI_VK_F12						0x7B	//F12��
#define ADI_VK_F13						0x7C	//F13��
#define ADI_VK_F14						0x7D	//F14��
#define ADI_VK_F15						0x7E	//F15��
#define ADI_VK_F16						0x7F	//F16��
#define ADI_VK_NUM_LOCK					0x90	//num lock��
#define ADI_VK_SCROLL_LOCK				0x91	//scroll lock��
#define ADI_VK_OEM_1					0xBA	//"��" or "��"
#define ADI_VK_OEM_PLUS					0xBB	//"=" or "+"
#define ADI_VK_OEM_COMMA				0xBC	//"," or "<"
#define ADI_VK_OEM_MINUS				0xBD	//"_" or "-"
#define ADI_VK_OEM_PERIOD				0xBE	//"." or ">"
#define ADI_VK_OEM_2					0xBF	//"/" or "?"
#define ADI_VK_OEM_3					0xC0	//"~" or "`"
#define ADI_VK_OEM_4					0xDB	//"[" or "{"
#define ADI_VK_OEM_5					0xDC	//"\" or "|"
#define ADI_VK_OEM_6					0xDD	//"]" or "}"
#define ADI_VK_OEM_7					0xDE	//"'" or """

#define ADI_VK_PRIOR					ADI_VK_PAGE_UP		//���Ϸ�ҳ��
#define ADI_VK_NEXT						ADI_VK_PAGE_DOWN	//���·�ҳ��
#define ADI_VK_RETURN					ADI_VK_OK			//�س���
#define ADI_VK_ESCAPE					ADI_VK_EXIT			//ESC��(����)

#define ADI_VK_HDD_LIST					0xf11	//Ӳ���ļ��б��
#define ADI_VK_PIP						0xf12	//PIP
#define ADI_VK_SWAP						0xf13	//��������
#define ADI_VK_ASSIST					0xf14	//��ݲ˵���/���ּ�/ħ��

#define ADI_VK_INSERT_WIN				0x2D	//Insert��,Ϊ�˲���awt�иð���ֵ�����ͻ��windows������İ��������±� _WIN ��־
#define ADI_VK_DELETE_WIN				0x2E	//Delete��,windows��ʹ�á�
#define ADI_VK_BACK_WIN					0x08	//back space��

#define ADI_VK_3D					    0xA01	// ����:3D������
#define ADI_VK_NORMAL			    	0xA02	// ����:���� 
#define ADI_VK_BASS                  	0xA03   // ����:����
#define ADI_VK_TREBLE					0xA04	// ����:����


typedef enum
{
	EM_ADI_KEY_CALLBACK_IR,			// callback from adi_ir
	EM_ADI_KEY_CALLBACK_PANEL		// callback from adi_panel
} ADIKeyCallbackType;

/* enum of key status */
typedef enum
{
	EM_ADI_KEY_PRESS,			// ��ʾ��������
	EM_ADI_KEY_REPEAT,		// ��ʾ�����ظ�
	EM_ADI_KEY_RELEASE		// ��ʾ��������
} ADIKeyStatus_E;


/* struct of the second parameter of KeySendCallback */
typedef struct
{
	ADIKeyStatus_E	m_eKeyStatus;	// ����״̬����ʾ�������»��� 
	unsigned int	m_uLogicValue;	// �����Ĺ����� 
	unsigned int	m_uHBBTVKeyValue;  //��HBBTV��Ŀʹ��
	
}ADIKeyParam_S;


/* Ir & Panel �����ص�����
��һ���������ذ���������
�ڶ�����������ADIKeyParam_S
*/
typedef  void ( *ADIKeyCallback_F )( ADIKeyCallbackType , void * );

#ifdef __cplusplus
}
#endif

#endif
