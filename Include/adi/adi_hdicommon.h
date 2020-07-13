#ifndef _ADI_HDICOMMON_H_
#define _ADI_HDICOMMON_H_


#ifdef __cplusplus
extern "C" {
#endif

#define ADI_HDI_TIMEOUT_INFINITY		(unsigned int)0xffffffff
#define ADI_HDI_TIMEOUT_IMMEDIATE	0


//遥控器，前面板按键
#define ADI_VK_POWER					0xffff  // 待机键
#define ADI_VK_0						0x30	// 数字键0
#define ADI_VK_1						0x31	// 数字键1
#define ADI_VK_2						0x32	// 数字键2
#define ADI_VK_3						0x33	// 数字键3
#define ADI_VK_4						0x34	// 数字键4
#define ADI_VK_5						0x35	// 数字键5
#define ADI_VK_6						0x36	// 数字键6
#define ADI_VK_7						0x37	// 数字键7
#define ADI_VK_8						0x38	// 数字键8
#define ADI_VK_9						0x39	// 数字键9
#define ADI_VK_OK			       	 	0x0D    // 确认键
#define ADI_VK_TOGGLE                	0x0280  // 返回键
#define ADI_VK_EXIT					    0x1B    // 退出键
#define ADI_VK_PAGE_UP				    0x21    // 向上翻页
#define ADI_VK_PAGE_DOWN			    0x22    // 向下翻页
#define ADI_VK_LEFT					    0x25    // 向左键 
#define ADI_VK_UP						0x26    // 向上键
#define ADI_VK_RIGHT					0x27    // 向右键
#define ADI_VK_DOWN					    0x28    // 向下键
#define ADI_VK_CHANNEL_UP				0x01AB	// 频道增加键
#define ADI_VK_CHANNEL_DOWN			    0x01AC  // 频道减少键
#define ADI_VK_VOLUME_UP				0x01BF  // 音量增加键
#define ADI_VK_VOLUME_DOWN			    0x01C0	// 音量减少键
#define ADI_VK_MENU					    0X01D4  // 菜单键
#define ADI_VK_MUTE					    0x01C1	// 静音键
#define ADI_VK_GUIDE					0x01CA	// 节目指南键
#define ADI_VK_AUDIO					0x0197  // 声道键
#define ADI_VK_COLORED_KEY_0	        0X0193  // 红色键
#define ADI_VK_COLORED_KEY_1	        0X0194  // 绿色键
#define ADI_VK_COLORED_KEY_2	        0X0195  // 黄色键
#define ADI_VK_COLORED_KEY_3	        0X0196  // 蓝色键

#define ADI_VK_PROG_LIST                0x0281  // 频道列表键
#define ADI_VK_TV_RADIO                 0x0282  // 电视/音频广播键
#define ADI_VK_CARD_INFO             	0x0283  // 卡信息键
#define ADI_VK_MAIL_INFO             	0x0284  // 邮件键
#define ADI_VK_VOD                   	0x0285  // 点播键
#define ADI_VK_SYSSET					0x0286  // 系统设置键
#define ADI_VK_HELP						0x1E3   // 帮助键
#define ADI_VK_SERV						0x01D0  // 资讯键
#define ADI_VK_FAV						0x01E0	// 喜爱键
#define ADI_VK_TV						0x01E1	// 电视键
#define ADI_VK_RADIO					0x01E2  // 广播键
#define ADI_VK_INFO						0x01C9  // 信息键
#define ADI_VK_LANGUAGE					0x0198  // 中/英文切换键
#define ADI_VK_INPUT                 	0x84	//  输入法按键

#define ADI_VK_REFRESH              	0x80    //  刷新网页 
#define ADI_VK_FORWARD               	0x81	//  前进（历史网页） 
#define ADI_VK_BACK                  	0x82	//  后退（历史网页） 
#define ADI_VK_BROWSER                	0x83	//  启动浏览器 
#define ADI_VK_RECORD       	        0xf10	// 录制键
#define ADI_VK_PLAY 					0xf16	// 播放
#define ADI_VK_STOP 					0xf17	// 停止播放
#define ADI_VK_PAUSE 					0xf18   // 暂停
#define ADI_VK_RW   					0xf21	// 快退
#define ADI_VK_FF   					0xf22	// 快进
#define ADI_VK_SF   					0xf23	// 慢进
#define ADI_VK_SB   					0xf24	// 慢退

#define ADI_VK_POUND					0x23	// "#"键
#define ADI_VK_ASTERISK			    	0x2A	// "*"键
#define ADI_VK_SEEK                  	0xf28   // 定位键
#define ADI_VK_TAB						0x09	// Tab键

#define ADI_VK_END            			0x23	// END键
#define ADI_VK_HOME           			0x24 	// Home键
#define ADI_VK_INSERT         			0x9B	// Insert键
#define ADI_VK_DELETE        			0x7F	// Delete键

#define ADI_VK_TELETEXT					0x01CB	//字幕键
#define ADI_VK_SUBTITLE					0x01CC	//subtitle键

#define ADI_VK_RECALL					0xf24	//Recall键
#define ADI_VK_TIMER_REC				0xf25	//显示预订列表

#define ADI_VK_GAME						0xf29	//游戏快捷键
#define ADI_VK_ADS						0xf2A	//广告快捷键
#define ADI_VK_NVOD						0xf2B	//NVOD快捷键
#define ADI_VK_STOCK					0xf2C	//股票快捷键
#define ADI_VK_PAYOUT					0xf2D	//支付快捷键
#define ADI_VK_PORTAL					0xf2E	//Portal快捷键
		
#define ADI_VK_LBUTTON					0x01	//鼠标左键
#define ADI_VK_RBUTTON					0x02	//鼠标右键
#define ADI_VK_CANCEL					0x03	//取消键（Ctrl-Break）
#define ADI_VK_MBUTTON					0x04	//鼠标中键
#define ADI_VK_CLEAR					0x0C	//Num Lock关闭时的数字键盘5
#define ADI_VK_SHIFT					0x10	//Shift键
#define ADI_VK_CONTROL					0x11	//Ctrl键
#define ADI_VK_ALT						0x12	//Alt键
#define ADI_VK_CAPITAL					0x14	//Caps lock键
#define ADI_VK_SPACE					0x20	//空格键
#define ADI_VK_SELECT					0x29	//Select键
#define ADI_VK_PRINT					0x2A	//Print键
#define ADI_VK_EXECUTE					0x2B	//Execute键
#define ADI_VK_SNAPSHOT					0x2C	//Print Screen键
#define ADI_VK_A						0x41	//字母键A
#define ADI_VK_B						0x42	//字母键B
#define ADI_VK_C						0x43	//字母键C
#define ADI_VK_D						0x44	//字母键D
#define ADI_VK_E						0x45	//字母键E
#define ADI_VK_F						0x46	//字母键F
#define ADI_VK_G						0x47	//字母键G
#define ADI_VK_H						0x48	//字母键H
#define ADI_VK_I						0x49	//字母键I
#define ADI_VK_J						0x4A	//字母键J
#define ADI_VK_K						0x4B	//字母键K
#define ADI_VK_L						0x4C	//字母键L
#define ADI_VK_M						0x4D	//字母键M
#define ADI_VK_N						0x4E	//字母键N
#define ADI_VK_O						0x4F	//字母键O
#define ADI_VK_P						0x50	//字母键P
#define ADI_VK_Q						0x51	//字母键Q
#define ADI_VK_R						0x52	//字母键R
#define ADI_VK_S						0x53	//字母键S
#define ADI_VK_T						0x54	//字母键T
#define ADI_VK_U						0x55	//字母键U
#define ADI_VK_V						0x56	//字母键V
#define ADI_VK_W						0x57	//字母键W
#define ADI_VK_X						0x58	//字母键X
#define ADI_VK_Y						0x59	//字母键Y
#define ADI_VK_Z						0x5A	//字母键Z
#define ADI_VK_LWIN						0x6B	//左窗口
#define ADI_VK_RWIN						0x7C	//右窗口
#define ADI_VK_NUMPAD0					0x60	//小键盘0键
#define ADI_VK_NUMPAD1					0x61	//小键盘1键
#define ADI_VK_NUMPAD2					0x62	//小键盘2键
#define ADI_VK_NUMPAD3					0x63	//小键盘3键
#define ADI_VK_NUMPAD4					0x64	//小键盘4键
#define ADI_VK_NUMPAD5					0x65	//小键盘5键
#define ADI_VK_NUMPAD6					0x66	//小键盘6键
#define ADI_VK_NUMPAD7					0x67	//小键盘7键
#define ADI_VK_NUMPAD8					0x68	//小键盘8键
#define ADI_VK_NUMPAD9					0x69	//小键盘9键
#define ADI_VK_MULTIPLY					0x6A	//小键盘*
#define ADI_VK_ADD						0x6B	//小键盘+
#define ADI_VK_SEPARATER				0x6C	//ENTER键
#define ADI_VK_SUBTRACT					0x6D	//小键盘-
#define ADI_VK_DECIMAL					0x6E	//小键盘.
#define ADI_VK_DIVIDE					0x6F	//小键盘/
#define ADI_VK_F1						0x70	//F1键
#define ADI_VK_F2						0x71	//F2键
#define ADI_VK_F3						0x72	//F3键
#define ADI_VK_F4						0x73	//F4键
#define ADI_VK_F5						0x74	//F5键
#define ADI_VK_F6						0x75	//F6键
#define ADI_VK_F7						0x76	//F7键
#define ADI_VK_F8						0x77	//F8键
#define ADI_VK_F9						0x78	//F9键
#define ADI_VK_F10						0x79	//F10键
#define ADI_VK_F11						0x7A	//F11键
#define ADI_VK_F12						0x7B	//F12键
#define ADI_VK_F13						0x7C	//F13键
#define ADI_VK_F14						0x7D	//F14键
#define ADI_VK_F15						0x7E	//F15键
#define ADI_VK_F16						0x7F	//F16键
#define ADI_VK_NUM_LOCK					0x90	//num lock键
#define ADI_VK_SCROLL_LOCK				0x91	//scroll lock键
#define ADI_VK_OEM_1					0xBA	//"；" or "："
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

#define ADI_VK_PRIOR					ADI_VK_PAGE_UP		//向上翻页键
#define ADI_VK_NEXT						ADI_VK_PAGE_DOWN	//向下翻页键
#define ADI_VK_RETURN					ADI_VK_OK			//回车键
#define ADI_VK_ESCAPE					ADI_VK_EXIT			//ESC键(返回)

#define ADI_VK_HDD_LIST					0xf11	//硬盘文件列表键
#define ADI_VK_PIP						0xf12	//PIP
#define ADI_VK_SWAP						0xf13	//交换窗口
#define ADI_VK_ASSIST					0xf14	//快捷菜单键/助手键/魔键

#define ADI_VK_INSERT_WIN				0x2D	//Insert键,为了不与awt中该按键值定义冲突，windows中另定义的按键加上下标 _WIN 标志
#define ADI_VK_DELETE_WIN				0x2E	//Delete键,windows中使用。
#define ADI_VK_BACK_WIN					0x08	//back space键

#define ADI_VK_3D					    0xA01	// 音响:3D环绕声
#define ADI_VK_NORMAL			    	0xA02	// 音响:正常 
#define ADI_VK_BASS                  	0xA03   // 音响:低音
#define ADI_VK_TREBLE					0xA04	// 音响:高音


typedef enum
{
	EM_ADI_KEY_CALLBACK_IR,			// callback from adi_ir
	EM_ADI_KEY_CALLBACK_PANEL		// callback from adi_panel
} ADIKeyCallbackType;

/* enum of key status */
typedef enum
{
	EM_ADI_KEY_PRESS,			// 表示按键按下
	EM_ADI_KEY_REPEAT,		// 表示按键重复
	EM_ADI_KEY_RELEASE		// 表示按键弹起
} ADIKeyStatus_E;


/* struct of the second parameter of KeySendCallback */
typedef struct
{
	ADIKeyStatus_E	m_eKeyStatus;	// 按键状态，表示按键按下或弹起 
	unsigned int	m_uLogicValue;	// 按键的功能码 
	unsigned int	m_uHBBTVKeyValue;  //仅HBBTV项目使用
	
}ADIKeyParam_S;


/* Ir & Panel 按键回调函数
第一个参数返回按键的类型
第二个参数返回ADIKeyParam_S
*/
typedef  void ( *ADIKeyCallback_F )( ADIKeyCallbackType , void * );

#ifdef __cplusplus
}
#endif

#endif
