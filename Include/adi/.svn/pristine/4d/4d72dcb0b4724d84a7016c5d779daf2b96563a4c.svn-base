#ifndef _ADI_NET_H_
#define _ADI_NET_H_

#include "adi_error.h"

#ifdef   __cplusplus
extern "C" {
#endif

#define ADI_WLAN_MAX_AP_NUM		    (32)
#define ADI_WLAN_SSID_MAX_LEN		(32)
#define ADI_WLAN_MAC_MAX_LEN		(32)
#define ADI_WLAN_PASSWD_MAX_LEN		(40)
#define ADI_IP_MAX_LEN				(16)
#define	ADI_MASK_MAX_LEN			(16)
#define ADI_GATEWAY_MAX_LEN			(16)

enum
{
	ADINET_ERROR_BAD_PARAMETER = ADI_NET_ERROR_BASE, 
	ADINET_ERROR_NOT_SUPPORT,
	ADINET_ERROR_ALREADY_ADDED,
	ADINET_ERROR_UNKNOWN,
};

typedef enum
{
	EM_ADIWLAN_CONN_KEY_ERR, 									///< 密钥错误
	EM_ADIWLAN_CONN_TIMEOUT,									///< 连接超时
	EM_ADIWLAN_DOWN,											///< 网络断开
	EM_ADIWLAN_UP,												///< 网络连接成功
	EM_ADIWLAN_APLOST,											///< AP缺失
	EM_ADIWLAN_APCONNECT,										///< AP成功连接
	EM_ADIWLAN_DONGLE_IN,										///USB WIFI DONGLE PLUG IN
	EM_ADIWLAN_DONGLE_OUT,										///USB WIFI DONGLE PLUG OUT
	EM_ADIWLAN_DHCP_SUCCESS,                                    ///WLAN DHCP SUCCESS
	EM_ADIWLAN_DHCP_FAILED                                      ///WLAN DHCP FAILED
}ADIWLanMsgInfo_E;

/**@brief 网卡类型*/
typedef enum 
{
   EM_ADIETHER_TYPE_LAN 	= 1 << 0,  							///< 有线网卡
   EM_ADIETHER_TYPE_WLAN 	= 1 << 1,							///< 无线网卡
   EM_ADIEHTER_TYPE_PPPOE 	= 1 << 2,                           //pppoe
   EM_ADIEHTER_TYPE_AP 		= 1 << 3,							///无线AP
   EM_ADIEHTER_TYPE_UNKNOWN                                     ///未知类型网卡
}ADIEtherType_E;


/**@brief 无线网卡认证的加密类型*/
typedef enum 
{
   EM_ADIWLAN_ENC_NONE = 0,  									///< 无加密
   EM_ADIWLAN_ENC_WEPOPENAUTO,								///< WEPOpen加密
   EM_ADIWLAN_ENC_WEPSHARE,									///< shared共享模式来加密WEP信息
   EM_ADIWLAN_ENC_WPAPSK_TKIP,								///<WPAPSK 认证方式和TKIP加密算法
   EM_ADIWLAN_ENC_WPAPSK_AES,								///<WPAPSK 认证方式和AES加密算法
   EM_ADIWLAN_ENC_WPA2PSK_TKIP,								///<WPA2PSK 认证方式和TKIP加密算法
   EM_ADIWLAN_ENC_WPA2PSK_AES,								///<WPA2PSK 认证方式和AES加密算法
   EM_ADIWLAN_ENC_WPA2PSK_EAP,
   EM_ADIWLAN_ENC_UNKNOW
}ADIWLanEncType_E;


typedef enum
{
	EM_ADIRAWSENDTYPE_UNICAST = 0,//单播
	EM_ADIRAWSENDTYPE_BROADCAST,//广播
	EM_ADIRAWSENDTYPE_UNDEFINED
} ADIRawSendType_E;

typedef enum 
{
	EM_ADILAN_PHY_CONNECT,
	EM_ADILAN_PHY_DISCONNECT,
	EM_ADILAN_DHCP_SUCCESS,
	EM_ADILAN_DHCP_FAILED,
	EM_ADILAN_MAXEVENTTYPE
}ADINetLANEventType_E; 

/**@brief 网卡的芯片信息*/
typedef struct
{
    unsigned int      		uLanManuFactory;   					///< 生产厂家ID                   
    ADIEtherType_E    		eEtherType ;	          			///< 网卡类型
}ADIEtherInfo_S;


/**@brief 网卡的统计信息*/
typedef struct
{
    unsigned int uConnectTime;          ///< 连接持续时间
    unsigned int uTotalBytesSend;       ///< 发送包字节数
    unsigned int uTotalBytesReceived;   ///< 接收包字节数
    unsigned int uTotalPacketSend;      ///< 发送包个数
    unsigned int uTotalPacketReceived;  ///< 接发包个数
}ADIEtherStat_S;


typedef struct
{
    ADIWLanEncType_E eEncType;								//AP Security mode
    unsigned int unStrehgth; 								//AP Strength (0-100)
    unsigned int unQuality; 								//AP Quality (0-100)
    char acSSId[ADI_WLAN_SSID_MAX_LEN];						//AP SSID
    char acMac[ADI_WLAN_MAC_MAX_LEN];						//AP的 MAC
} ADIWLanApInfo_S;

typedef struct
{
	ADIWLanEncType_E eEncType;								//WLAN Security mode
	char acSSId[ADI_WLAN_SSID_MAX_LEN];						//WLAN SSID
	char acPassWord[ADI_WLAN_PASSWD_MAX_LEN];				//Password
} ADIWlanAPConnectInfo_S;


/**@brief 无线网卡回调函数
*/
typedef void (*ADIWlanCallback_F)(ADIWLanMsgInfo_E eMsgType,char * pcWlanName,void * pvUserData);

 /**@brief 有线网卡回调函数
 */
 typedef void (*ADILanCallback_F)(ADINetLANEventType_E eEventType,char * pcEthName,void * pvUserData);

 /**
@brief 注册无线网卡的回调函数

*/
ADI_Error_Code ADINetAddWlanCallback(ADIWlanCallback_F fnWlanCallback,void * pvUserData);


 /**
@brief 删除无线网卡的回调函数

*/
ADI_Error_Code ADINetDelWlanCallback(ADIWlanCallback_F fnWlanCallback,void * pvUserData);

/**
@brief 注册有线网卡的回调函数

*/
ADI_Error_Code ADINetAddLanCallback(ADILanCallback_F fnLanCallback,void * pvUserData);

 /**
@brief 删除有线网卡的回调函数

*/
ADI_Error_Code ADINetDelLanCallback(ADILanCallback_F fnLanCallback,void * pvUserData);


/**
@brief 获得网卡数，支持有线和无线网卡和pppoe。如果带有pppoe功能，数量应该是实际的网卡数加上ppp0
*/ 
ADI_Error_Code ADINetGetEtherCount(int* pnCount);



/**
@brief 获取网卡设备名，支持有线和无线网卡和pppoe。
*/
ADI_Error_Code ADINetGetEtherName(int nEthIndex,char * pcEthName,int nLen );



/**
@brief 获得网卡芯片的信息，包括制造商和类型等。
*/
ADI_Error_Code ADINetGetEtherChipInfo(char * pcEthName, ADIEtherInfo_S * psChipInfo);



/**
@brief 通过设备名称来设置网卡物理地址，支持有线和无线网卡。
*/
ADI_Error_Code ADINetSetMacByName(char * pcEthName,unsigned char * pucMacAddress);


/**
@brief 通过设备名称来获取网卡物理地址，支持有线和无线网卡。
*/

ADI_Error_Code ADINetGetMacByName(char * pcEthName,unsigned char * pucMacAddress);



/**
@brief 获取有线和无线网卡的连接状态。
*/
ADI_Error_Code ADINetGetEtherStatus(char * pcEthName, unsigned short * pushLinkState);



/**
@brief 搜索网络内存在的所有AP的信息，只用于无线网卡。
*/
ADI_Error_Code ADINetSearchAP(char * pcEthName,ADIWLanApInfo_S * psWlanApInfo, int * pnWlanApInfoNum);


/**
@brief 与AP建立连接，只用于无线网卡。
*/
ADI_Error_Code ADINetConnectAP(char * pcEthName,ADIWlanAPConnectInfo_S * psWLanAPConf);


/**
@brief 断开与AP的连接，只用于无线网卡。
*/
ADI_Error_Code ADINetDisconnectAP(char * pcEthName);


/**
@brief 设置DNS的地址。
*/
ADI_Error_Code ADINetSetDNSServer(char * pcEthName,char * pcDNS1, char * pcDNS2 );



/**  
@brief 获得DNS的地址。
*/
ADI_Error_Code ADINetGetDNSServer(char * pcEthName,char * pcDNS1, char * pcDNS2 );


/**
@brief 设置IP地址
*/
ADI_Error_Code ADINetSetIp(char * pcEthName,char *pcIP);


/**
@brief 获取IP地址
*/
ADI_Error_Code ADINetGetIp(char * pcEthName,char *pcIP);


/**
@brief设置子网掩码
*/
ADI_Error_Code ADINetSetNetMask(char * pcEthName,char *pcNetMask);


/**
@brief获取子网掩码
*/
ADI_Error_Code ADINetGetNetMask(char * pcEthName,char *pcNetMask);

/**
@brief设置网关
*/
ADI_Error_Code ADINetSetGateWay(char * pcEthName,char *pcGateWay);


/**
@brief获取网关
*/
ADI_Error_Code ADINetGetGateWay(char * pcEthName,char *pcGateWay);



/**
@brief 将应用层传下来的包经过处理交给网卡驱动层发送出去。

*/
int  ADINetRawSendPacket(char *pcEthName, int  *fd, const char *pcDhcpBuf, int nBufLen, int nFlag);


/**
@brief 将应用层传下来的包经过处理交给网卡驱动层发送出去,根据用户设置的参数eRawSendType决定发送的包是单播包还是广播包。
*/
int  ADINetRawSendPacketByMode(char *pcEthName, int  *fd, const char *pcDhcpBuf, int nBufLen, int nFlag, ADIRawSendType_E eRawSendMode);

/**
@brief 接收从网卡驱动传上来的包，交给应用层
*/
int ADINetRawRecvPacket (char *pcEthName, int  *fd, const char *pchBuf, int* pnBufLen, int nFlag);


/**
@brief 获取网卡统计信息
*/
ADI_Error_Code ADINetGetStatInfo(char *pcEthName,ADIEtherStat_S *psNetStatus);


/**
@brief 启用网卡
*/
ADI_Error_Code ADINetEtherUp(char *pcEthName);


/**
@brief 禁用网卡
*/
ADI_Error_Code ADINetEtherDown(char *pcEthName);

/*
@brief启动DHCP
*/
ADI_Error_Code ADINetDHCPON(char *pcEthName);


/*
@brief关闭DHCP
*/
ADI_Error_Code ADINetDHCPOFF(char *pcEthName);


ADI_Error_Code ADINetPing(char * pcEthName,char *pcIP);



#ifdef __cplusplus
}
#endif

#endif 


