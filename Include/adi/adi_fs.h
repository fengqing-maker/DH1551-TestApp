

#ifndef _ADI_FS_H_
#define _ADI_FS_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ADIFS_CP_DEFAULT		(0)           // 默认编码方式,当移植层不确定文件系统使用的编码方式时使用该模式,这种情况下可能会产生乱码
#define ADIFS_CP_GB2312	        (936)         // GB2312编码
#define ADIFS_CP_BIG5			(950)         // big5编码
#define ADIFS_CP_UTF8			(65001)       // UTF8

#define ADIFS_ENCODE_BIG_ENDIAN     (0x10000)     // bigendian,即高位在前
#define ADIFS_ENCODE_LITTLE_ENDIAN  (0)           // littelendian,即低位在前

#define ADIFS_SEEK_SET 	(0)	        // 从文件开头处seek
#define ADIFS_SEEK_CUR 	(1)	        // 从文件当前位置seek
#define ADIFS_SEEK_END  (2) 		// 从文件结尾处seek

#define ADIFS_MODE_REG 	(0x1)		// 普通文件，见ADIFSFileStat_S结构的m_lMode域
#define ADIFS_MODE_DIR	(0x1 << 1) 	// 文件夹，ADIFSFileStat_S结构的m_lMode域

#define ADIFS_ISREG(m)  (((m) & ADIFS_MODE_REG) == ADIFS_MODE_REG)	// 判断是否为普通文件,用于ADIFSFileStat_S结构的m_lMode域
#define ADIFS_ISDIR(m)  (((m) & ADIFS_MODE_DIR) == ADIFS_MODE_DIR)	// 判断是否为文件夹,用于ADIFSFileStat_S结构的m_lMode域

/*可移动设备主设备号掩码，所有可移动设备的设备号与该值相与得到其主设备号，主设备号即代表了该设备的类型，可移动设备的主设备号具体由设备操作模块定义，其值从0x00010000开始，即所有大于0x00010000的设备号都表示可移动设备。*/
#define ADI_FS_MAJOR_DEVICEID_MASK		(0xFFFF0000)

/*可移动设备从设备号掩码，所有可移动设备的设备号与该值相与得到其从设备号，从设备号即代表了该类型设备的一个具体设备。 具体类型的可移动设备的从设备号均从0开始，单个设备每次插入拔出，从设备号都会发生变化。*/
#define ADI_FS_MINOR_DEVICEID_MASK		(0x0000FFFF)



enum
{
	ADIFS_ERROR_BAD_PARAMETER = ADI_FS_ERROR_BASE,
	ADIFS_ERROR_FEATURE_NOT_SUPPORTED,
	ADIFS_ERROR_UNKNOWN_ERROR,
	ADIFS_ERROR_NO_MEMORY,
	ADIFS_ERROR_INVALID_DEVICE_ID,
	ADIFS_ERROR_DEVICE_BUSY,
	ADIFS_ERROR_NO_CALLBACK,
	ADIFS_ERROR_ALREADY_ADDED
};

/*分卷的类型*/
typedef enum 
{
	EM_ADIFS_PARTITION_AUTO = 0,    	    // 自动类型,由平台决定使用支持的最好的类型，从底层获取的文件系统类型不得为该值
	
	EM_ADIFS_PARTITION_READONLY_START,      // 只读文件系统边界
	EM_ADIFS_PARTITION_CRAMFS,			    // CRAMFS类分区
	EM_ADIFS_PARTITION_ROMFS,			    // ROMFS类分区
	EM_ADIFS_PARTITION_READONLY_END = 0x100,// 只读文件系统边界
	
	EM_ADIFS_PARTITION_RW_START,		   // 可读写文件系统边界
	EM_ADIFS_PARTITION_FAT32 ,             // FAT32类型分区
	EM_ADIFS_PARTITION_EXT2,               // E2FS类型分区
	EM_ADIFS_PARTITION_EXT3,			   // EXT3类型分区
	EM_ADIFS_PARTITION_JFFS2,			   // JFFS2类型分区
	EM_ADIFS_PARTITION_NTFS,               // NTFS类型分区
	EM_ADIFS_PARTITION_UBIFS,              // UBIFS类型分区
	EM_ADIFS_PARTITION_YAFFS2,             // YAFFS2类型分区
	EM_ADIFS_PARTITION_UNKNOW,
	EM_ADIFS_PARTITION_RW_END = 0x200      // 可读写文件系统边界
}ADIFSPartitionType_E;

/*设备类型*/
typedef enum
{
    EM_ADIFS_DEVTYPE_UNKNOWN,            
	EM_ADIFS_DEVTYPE_STORAGE,	         // 存储设备
    EM_ADIFS_DEVTYPE_VOLUME              // 分卷设备
}ADIFSDeviceType_E;


/*设备信息结构*/
typedef struct
{
    unsigned int    	m_nDeviceId;         // 设备Id,一次开机过程中设备Id唯一标识一个设备的一次插入,同一设备反复插入设备Id号发生变化	
	ADIFSDeviceType_E   m_eDeviceType;       // 设备类型,可移动设备的设备类型必须要设备Id保持一致，固定设备的设备类型从该值获取
    char      	        m_szDeviceName[128]; // 设备的唯一设备名称
    ADI_UINT64          m_dwDeviceSize;       // 设备大小(字节为单位)
    unsigned int    	m_nParentDeviceId;   // 父设备Id,存储设备该值无效,分卷设备为其所属的存储设备的Id
    char                m_szMountPoint[256]; // 如果是存储设备的该项为"";分卷设备表示该设备在ADIFS中的可访问路径,如果为""(不是为ADI_NULL，也不是为空格),表示这是一个不能识别的分卷
	unsigned int        m_nMountPort;
}ADIFSDeviceInfo_S;	

/*文件属性*/
typedef struct
{
	unsigned long   	 m_lMode;		// 文件类型，用于表示是文件还是文件夹等，请使用ADIFS_ISREG、ADIFS_ISDIR宏进行判断
	unsigned long  long  m_lSize;     	// 文件实际大小
	unsigned long   	 m_lBlkSize;  	// 块大小,单位byte
	unsigned long   	 m_lBlkCount;    // 块数量
	unsigned long   	 m_lAtime;    	// 访问时间,用1970年1月1日0时0分0秒至今的秒数表示
	unsigned long   	 m_lMtime;    	// 修改时间,用1970年1月1日0时0分0秒至今的秒数表示
	unsigned long   	 m_lCtime;    	// 创建时间,用1970年1月1日0时0分0秒至今的秒数表示
}ADIFSFileStat_S;

/*文件夹内容节点属性,一般代表一个文件夹或者文件*/
typedef struct 
{
	unsigned char	m_ucDirType;         // 节点类型0-非文件夹,1-文件夹
	char		    m_cDirName[512];     // 节点名称
}ADIFSDirent_S;

/*文件系统属性*/
typedef struct
{
    ADIFSPartitionType_E m_eFsType;       // 文件系统类型	        
    unsigned long        m_lBsize;        // optimal transfer block size, 单位byte
    unsigned long        m_lBlocks;       // total data blocks in file system
    unsigned long        m_lBfree;        // free blocks in fs
    unsigned long        m_lBavail;       // free blocks avail to non-superuser
    unsigned long        m_lFiles;        // total file nodes in file system
    unsigned long        m_lFfree;        // free file nodes in fs
    unsigned long        m_lNamelen;      // maximum length of filenames
}ADIFSStatFs_S;

typedef enum
{
    EM_ADIFS_EVENT_UNKNOWN,       // 未知设备事件,非法值
    EM_ADIFS_EVENT_FOUND,         // 发现设备已可获得设备信息,但尚不可访问访问,pEventData为CSUDI_NULL
    EM_ADIFS_EVENT_CHECKING,      // 进入就绪状态前，需进行设备自检、安装等耗时较长的准备工作，发此消息通知应用耐心等待，pEventData为int类型，表示自检进度，范围为0-100，-1表示进度未知但仍在正常进行，如果无法知道状态，则请赋值为-1，自检过程中该消息应约每秒钟1次的频率反复发生。 
    EM_ADIFS_EVENT_READY,         // 设备就绪,已可进行访问,pEventData为CSUDI_NULL
    EM_ADIFS_EVENT_ERROR,         // 设备不可恢复错误,设备将无法访问,pEventData为错误代码(具体错误代码由模块定义，若未定义则仅用于显示和错误排查，不用于后续处理的依据)
    EM_ADIFS_EVENT_PLUGOUT,        // 设备移除,pEventData为ADIFSPlugOutType_E，即拔除类型,该消息通知返回后将不可再通过该设备Id获取设备信息
    EM_ADIFS_EVENT_DEVICE_NO_PARTITION
}ADIFSEvent_E;

enum
{
	ADI_FS_STORAGE_MAJOR_DEVICEID		=  1 << 16,		// 存储设备主设备号，由adi_fs模块进行控制
	ADI_FS_VOLUME_MAJOR_DEVICEID			=  2 << 16,		// 分卷设备主设备号，由adi_fs模块进行控制
	ADI_FS_TUNER_MAJOR_DEVICEID			=  3 << 16,		// 高频头设备主设备号，由adi_tuner模块进行控制
    ADI_FS_HID_MAJOR_DEVICEID            =  4 << 16      // HID设备主设备号，由adi_hid模块进行控制
};


typedef  void ( *ADIFSCallback_F )( ADIFSEvent_E eType, int dnDeviceId,const void * pvEventData, void * pvUserData);


ADI_Error_Code ADIFSAddCallback(ADIFSCallback_F fnCallback,const void * pvUserData);


ADI_Error_Code ADIFSRemoveCallback(ADIFSCallback_F fnCallback,const void * pvUserData);

ADI_Error_Code ADIFSRemoveDev(int nDeviceId);

ADI_Error_Code ADIFSGetAllDeviceId(int * pnIds, int nMaxIdCnt, int * pnActIdCnt);

ADI_Error_Code ADIFSGetDeviceInfo(int nDeviceId,ADIFSDeviceInfo_S * psDeviceInfo);

ADI_Error_Code ADIFSFormat(int nDeviceId,ADIFSPartitionType_E eType);

ADI_Error_Code ADIFSGetCodePage(int * pnCodePage); 

ADI_HANDLE ADIFSOpen(const char * pcFileName, const char * pcMode);

int ADIFSRead(ADI_HANDLE hFile,char * pcBuf, unsigned int uCount);

int ADIFSWrite(ADI_HANDLE hFile,char * pcBuf, unsigned int uCount);

int ADIFSClose(ADI_HANDLE hFile);

int ADIFSSeek(ADI_HANDLE hFile, long lOffset, unsigned int uOrigin);

int ADIFSLseek(ADI_HANDLE hFile,ADI_INT64 i64Offset,unsigned int uOrigin);

long ADIFSTell(ADI_HANDLE hFile);

ADI_INT64 ADIFSLtell(ADI_HANDLE hFile);

int ADIFSFlush(ADI_HANDLE hFile);

int ADIFSRemove(const char * pcFileName);

int ADIFSRename(const char * pcOldPath, const char * pcNewPath);

int ADIFSTruncate(const char * pcPathName, unsigned long ulLength);

int ADIFSFTruncate(ADI_HANDLE hFile, unsigned long ulLength);

int ADIFSLTruncate(const char * pcPathName,ADI_UINT64 u64Length);

int ADIFSLFTruncate(ADI_HANDLE hFile,ADI_UINT64 u64Length);

int ADIFSStat(const char * pcFileName, ADIFSFileStat_S * psFileStat);

int ADIFSFstat(ADI_HANDLE hFile, ADIFSFileStat_S * psFileStat);

int ADIFSMkdir(const char * pcPathName, int nReserved);

int ADIFSRmdir(const char * pcPathName);

ADI_HANDLE ADIFSOpenDir(const char * pcPathName);

int ADIFSCloseDir(ADI_HANDLE hDir);

ADIFSDirent_S *ADIFSReadDir(ADI_HANDLE hDir);

int ADIFSStatfs(const char * pcPathName, ADIFSStatFs_S * psFsStat);

int ADIFSFstatfs(ADI_HANDLE hFile, ADIFSStatFs_S * psFsStat);

//多分区优盘格式化前调用此接口设置各分区大小，mstar仅支持四个分区
ADI_Error_Code ADIFSSetPartitionSize(int nPartitionCount, unsigned long long *n64PartitionSize);



#ifdef __cplusplus
}
#endif

#endif

