
#ifndef _ADI_PLAYER_H_
#define _ADI_PLAYER_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_record.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif


/*播放相关错误代码值*/
enum
{
	ADIPLAYER_ERROR_BAD_PARAMETER = ADI_PLAYER_ERROR_BASE,
	ADIPLAYER_ERROR_FEATURE_NOT_SUPPORTED,
	ADIPLAYER_ERROR_UNKNOWN_ERROR,
	ADIPLAYER_ERROR_NO_MEMORY,
	ADIPLAYER_ERROR_INVALID_DEVICE_ID,
	ADIPLAYER_ERROR_INVALID_HANDLE,
	ADIPLAYER_ERROR_INVALID_STATUS,
	ADIPLAYER_ERROR_DEVICE_BUSY,
	ADIPLAYER_ERROR_DEVICE_DISORDER,
	ADIPLAYER_ERROR_CALLBACK_FULL,
	ADIPLAYER_ERROR_CALLBACK_EXIST,
	ADIPLAYER_ERROR_CALLBACK_NOT_EXIST,
	ADIPLAYER_ERROR_STREAMTYPE_DISORDER,
	ADIPLAYER_ERROR_TRICKMODE_STATE_ERROR
};

/*播放速率枚举定义*/
typedef enum 
{
	EM_ADIPLAYER_SPEED_NORMAL= 0,          	// 1
	EM_ADIPLAYER_SPEED_FASTREWIND_32,	   	// -32		
	EM_ADIPLAYER_SPEED_FASTREWIND_16,		// -16	
	EM_ADIPLAYER_SPEED_FASTREWIND_8,		// -8
	EM_ADIPLAYER_SPEED_FASTREWIND_4,		// -4 	
	EM_ADIPLAYER_SPEED_FASTREWIND_2,		// -2	
	EM_ADIPLAYER_SPEED_SLOWREWIND_2,	   	// -1/2		
	EM_ADIPLAYER_SPEED_SLOWREWIND_4,	   	// -1/4		
  	EM_ADIPLAYER_SPEED_SLOWREWIND_8,	   	// -1/8		
  	EM_ADIPLAYER_SPEED_SLOWFORWARD_2,		// 1/2
  	EM_ADIPLAYER_SPEED_SLOWFORWARD_4,		// 1/4
  	EM_ADIPLAYER_SPEED_SLOWFORWARD_8,	 	// 1/8
	EM_ADIPLAYER_SPEED_FASTFORWARD_2, 		// 2
	EM_ADIPLAYER_SPEED_FASTFORWARD_4,     	// 4
	EM_ADIPLAYER_SPEED_FASTFORWARD_8,		// 8
	EM_ADIPLAYER_SPEED_FASTFORWARD_16, 	  	// 16	
  	EM_ADIPLAYER_SPEED_FASTFORWARD_32,		// 32	
  	EM_ADIPLAYER_SPEED_SLOWREWIND_16,	   	// -1/16
  	EM_ADIPLAYER_SPEED_SLOWREWIND_32,	   	// -1/32
  	EM_ADIPLAYER_SPEED_SLOWFORWARD_16,	 	// 1/16
  	EM_ADIPLAYER_SPEED_SLOWFORWARD_32,	 	// 1/32
	EM_ADIPLAYER_SPEED_MAX
}ADIPlayerSpeed_E;	

#define ADI_PLAYER_MAX_FILE_NAME_LEN         (512)  //文件名称长度
#define ADI_PLAYER_TITLE_MAX_LEN             (512)  //文件标题、作者等最大字符数
#define ADI_PLAYER_TIME_LEN                  (8)    //年份字节数
#define ADI_PLAYER_MAX_PROGRAM_NUM           (5)    //最大节目个数，如ts媒体文件，节目个数如果超过5个，则播放器最多只能存储其中某5个节目信息，并播放其中的某一个
#define ADI_PLAYER_MAX_STREAM_NUM            (5)    // 流个数 
#define ADI_PLAYER_MAX_LANG_NUM              (10)    //支持的最多语言种类个数
#define ADI_PLAYER_LANG_LEN                  (4)    //语言字符数
#define ADI_PLAYER_SUB_TITLE_LEN             (8)    //字幕标题长度

#define EM_ADIFILEPLAYER_ERR_BASE        (1<<16) ///<文件播放错误类型基本值
#define EM_ADIFILEPLAYER_STATE_BASE    (2<<16)	///<文件播放状态类型基本值


/*文件流类型，播放的文件类型 */
typedef enum
{
	 EM_ADIFILEPLAYER_STREAM_ES = 0x0,	 // es流文件
	 EM_ADIFILEPLAYER_STREAM_TS, 		 // ts流文件
	 EM_ADIFILEPLAYER_STREAM_NORMAL, 	 // 普通文件，如idx,lrc,srt等字幕文件
	 EM_ADIFILEPLAYER_STREAM_NET,		 // 网络流文件
	 EM_ADIFILEPLAYER_STREAM_END
} ADIPlayerStreamType_E;


/*播放模式枚举定义*/
typedef enum
{
	EM_ADIPLAYER_LIVE,			// 直播模式
	EM_ADIPLAYER_FILE,			// 文件播放模式，包括本地文件和网络文件
	EM_ADIPLAYER_TSHIFT,		// PVR录制时移播放模式
	EM_ADIPLAYER_INJECT,		// 数据注入播放模式
	EM_ADIPLAYER_PVR,			// PVR录制播放模式
	EM_ADIPLAYER_MAXPLAYERTYPE  // 类型最大值，不可设置为该类型
}ADIPLAYERType_E;

/*切台播放模式定义*/
typedef enum
{
    EM_ADIPLAYER_DISPMODE_UNTIL_SYNC = 0,    //黑屏至音视频同步
    EM_ADIPLAYER_DISPMODE_SLOW_MOTION,       //慢同步
    EM_ADIPLAYER_DISPMODE_FIRST_FRAME		 //显示第一帧
} ADIPlayerDispMode_E;


/*回放播放模式(EM_ADIPLAYER_FILE、EM_ADIPLAYER_PVR和EM_ADIPLAYER_TSHIFT)下的参数数据结构*/
typedef struct 
{
	int                         m_nSecondPos;    // 回放的起始位置
	ADIPlayerSpeed_E 			m_eSpeed;        // 回放的速度
	char                        m_szFileName[ADI_MAX_URL_LEN];     	// 回放的流文件夹路径,只支持ASCII编码格式
    ADIStreamEncryptParam_S     m_stEncryptParam; 
}ADIPlaybackParam_S;

/*播放通道设备资源数据结构定义*/
typedef struct 
{
	int m_nDemux;			// Demux设备的Index，ADI_INVALID_INDEX代表不存在Demux设备
	int m_nVideoDecoder;	// 视频解码器的设备Index，ADI_INVALID_INDEX代表不存在视频解码器
	int m_nAudioDecoder;	// 音频解码器的设备Index，ADI_INVALID_INDEX代表不存在音频解码器
}ADIPlayerChnl_S;

/*回放偏移起始位置枚举定义*/
typedef enum
{
	EM_ADIPLAYER_POSITION_FROM_HEAD = 0,  	// 从文件头开始计算偏移
	EM_ADIPLAYER_POSITION_FROM_CURRENT,		// 从当前位置计算偏移
	EM_ADIPLAYER_POSITION_FROM_END			// 从文件尾计算偏移
}ADIPlayPosition_E;

/*非本地文件播放时，音视频播放事件枚举定义*/
typedef enum 
{
	
	EM_ADIPLAYER_VIDEO_FRAME_COMING,		// video新帧事件 此事件应该保证在视频正常解码的情况下一直可以监听到，并不是播放节目开始播放时只向上抛1次
	EM_ADIPLAYER_AUDIO_FRAME_COMING,		// audio新帧事件
	
	EM_ADIPLAYER_VIDEO_UNDERFLOW,		    // 视频解码器下溢事件
	EM_ADIPLAYER_AUDIO_UNDERFLOW,		    // 音频解码器下溢事件  
	
	EM_ADIPLAYER_VIDEO_OVERFLOW,		    // 视频解码器上溢事件
	EM_ADIPLAYER_AUDIO_OVERFLOW,		    // 音频解码器上溢事件

	EM_ADIPLAYER_VIDEO_SOURCE_CHANGE,		// 视频源改变事件，例如width,height,framerate参数改变
	EM_ADIPLAYER_AUDIO_SOURCE_CHANGE,		// 音频源改变事件，例如codec改变
	
	EM_ADIPLAYER_END_OF_STREAM,				// 播放至文件末尾，仅当播放模式为EM_ADIPLAYER_FILE、EM_ADIPLAYER_PVR或者EM_ADIPLAYER_TSHIFT时才会有该事件发生
	EM_ADIPLAYER_BEGIN_OF_STREAM,			// 播放至文件开头, 仅当播放模式为EM_ADIPLAYER_FILE、EM_ADIPLAYER_PVR或者EM_ADIPLAYER_TSHIFT且快退或慢退时才会有该事件发生

	EM_ADIPLAYER_VIDEO_DECODER_DECODING,
	EM_ADIPLAYER_VIDEO_DECODER_NODATA,
	EM_ADIPLAYER_AUDIO_DECODER_DECODING,
	EM_ADIPLAYER_AUDIO_DECODER_NODATA,
	EM_ADIPLAYER_VIDEO_DECODER_ERROR,
	EM_ADIPLAYER_MAXEVENTTYPE				// 边界值
}ADIPlayerEventType_E; 


/**本地文件播放，音视频播放事件枚举定义*/
typedef enum 
{
	
	EM_ADIFILEPLAYER_VIDEO_FRAME_COMING,	
	EM_ADIFILEPLAYER_AUDIO_FRAME_COMING,	
	
	EM_ADIFILEPLAYER_VIDEO_UNDERFLOW,	
	EM_ADIFILEPLAYER_AUDIO_UNDERFLOW,		
	
	EM_ADIFILEPLAYER_VIDEO_OVERFLOW,		 
	EM_ADIFILEPLAYER_AUDIO_OVERFLOW,		   

	EM_ADIFILEPLAYER_VIDEO_SOURCE_CHANGE,	
	EM_ADIFILEPLAYER_AUDIO_SOURCE_CHANGE,	
	
	EM_ADIFILEPLAYER_END_OF_STREAM,			
	EM_ADIFILEPLAYER_BEGIN_OF_STREAM,		

	EM_ADIFILEPLAYER_SHOW_SUBTITLE,         
	EM_ADIFILEPLAYER_CLEAR_SUBTITLE,      

	EM_ADIFILEPLAYER_ERR_ABORTED = EM_ADIFILEPLAYER_ERR_BASE,                    
	EM_ADIFILEPLAYER_ERR_DECODE,                               
	EM_ADIFILEPLAYER_ERR_FORMAT,                              
	EM_ADIFILEPLAYER_ERR_SEEK,                        
	EM_ADIFILEPLAYER_ERR_PAUSE,                     
	EM_ADIFILEPLAYER_ERR_RESUME,                
	EM_ADIFILEPLAYER_ERR_SETSPEED,               
	EM_ADIFILEPLAYER_ERR_NETWORK,                         
	EM_ADIFILEPLAYER_ERR_TIMEOUT,                   

	EM_ADIPFILELAYER_STATE_LOADING = EM_ADIFILEPLAYER_STATE_BASE, 
	EM_ADIPFILELAYER_STATE_LOADED,        
	EM_ADIPFILELAYER_STATE_HAVEMETADATA,      
	EM_ADIPFILELAYER_STATE_ENOUGHDATA_FORPLAY,       
	EM_ADIPFILELAYER_STATE_DURATIONCHANGE,          
	EM_ADIPFILELAYER_STATE_RATECHANGE,              

	EM_ADIFILEPLAYER_STATE_LOADING_PROGRESS,	
	EM_ADIFILEPLAYER_STATE_LOADING_DOWNLOADRATE,
	
	EM_ADIFILEPLAYER_STATE_STOP,                
	EM_ADIFILEPLAYER_STATE_START,               
	EM_ADIFILEPLAYER_STATE_PAUSE,             
	EM_ADIFILEPLAYER_SEEK_FINISH,             

	EM_ADIFILEPLAYER_MAXEVENTTYPE			
}ADIFilePlayerEventType_E; 


typedef enum
{

    EM_ADIPLAYER_TYPE_CLEAR_STREAM  = 0,
    EM_ADIPLAYER_TYPE_VID_TS_ENCRYPTED  = 0x01,
    EM_ADIPLAYER_TYPE_VID_PES_ENCRYPTED = 0x02,
    EM_ADIPLAYER_TYPE_AUD_TS_ENCRYPTED  = 0x04,
    EM_ADIPLAYER_TYPE_AUD_PES_ENCRYPTED = 0x08,
    EM_ADIPLAYER_TYPE_MAX
} ADIPlayerStreamEncryptType_E;


/*视频流信息 */
typedef struct
{
	 int            m_nStreamIndex;		   // 流索引，对于ts流，该值为流pid
	 unsigned int   m_uFormat;			   // 视频编码格式，值定义参考::ADIVIDStreamType_E ,驱动实现的时候要注意转换
	 unsigned int   m_uWidth;			   // 宽度，单位像素
	 unsigned int   m_uHeight;			   // 高度，单位像素
	 unsigned int   m_uFpsInteger;		   // 帧率，整数部分
	 unsigned int   m_uFpsDecimal;		   // 帧率，小数部分
	 unsigned int 	m_uBps; 			   // 视频码率，bits/s
	 unsigned int   m_uExtradataSize;	   // 扩展数据长度
	 unsigned char  *m_puExtradata;		   // 扩展数据
} ADIPlayerVidInfo_S;

/*音频流信息 */
typedef struct
{
	 int           m_nStreamIndex;				    // 流索引，对于ts流，该值为流pid，非法值为::HI_FORMAT_INVALID_STREAM_ID
	 unsigned int  m_uFormat;					    // 音频编码格式，值定义参考::ADIAUDStreamType_E ,驱动实现的时候要注意转换
	 unsigned int  m_uVersion; 					    // 音频编码版本，仅对wma编码，0x160(WMAV1), 0x161 (WMAV2)
	 unsigned int  m_uSampleRate;				    // 8000,11025,441000,...
	 unsigned int  m_uBitPerSample;				    // 音频每个采样点所占的比特数，8bit,16bit
	 unsigned int  m_uChannels;					    // 声道数, 1 or 2
	 unsigned int  m_uBlockAlign;				    // packet包含的字节数
	 unsigned int  m_uBps; 						    // 音频码率，bits/s
	 ADI_BOOL          m_bBigEndian;				    // 大小端，仅pcm格式有效
	 char          m_acAudLang[ADI_PLAYER_LANG_LEN];// 音频流语言
	 unsigned int  m_ExtradataSize;				    // 扩展数据长度
	 unsigned char  *m_pu8Extradata;				// 扩展数据
} ADIPlayerAudInfo_S;

/*字幕数据类型 */
typedef enum
{
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_TEXT = 0x0,	  // 字符串
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_BMP, 		  // bmp图片
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_ASS, 		  // ass字幕
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_HDMV_PGS,	  // pgs字幕
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_BMP_SUB, 	  // sub字幕
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_END
} ADIPlayerSubtitleDataType_E;


/*字幕信息 */
typedef struct
{
	 int                         m_nStreamIndex; 		// 流索引，对于ts流，该值为流pid
	 ADI_BOOL                        m_bExtSubTitle; 		// 是否为外挂字幕
	 ADIPlayerSubtitleDataType_E m_eSubtitileType;	    // 字幕格式，如bmp,string
	 char m_acSubTitleName[ADI_PLAYER_SUB_TITLE_LEN];   // 字幕标题
	 unsigned int                m_uOriginalFrameWidth; // 原始图像宽度
	 unsigned int                m_uOriginalFrameHeight;// 原始图像高度
	 unsigned int                m_uHorScale;			// 水平缩放比，0-100
	 unsigned int                m_uVerScale;			// 垂直缩放比，0-100
	 unsigned int                m_ExtradataSize;		// 扩展数据长度
	 unsigned short              m_pu8Extradata[256]; 		// 扩展数据
} ADIPlayerSubtitleInfo_S;

typedef struct
{
	 ADIPlayerVidInfo_S      m_stVidStream;								    // 视频流信息
	 unsigned int            m_AudStreamNum;								// 音频流个数
	 unsigned int 			 n_CurrentAudIndex;								//当前音频索引
	 ADIPlayerAudInfo_S      m_astAudStream[ADI_PLAYER_MAX_STREAM_NUM];		// 音频流信息
	 unsigned int            m_SubTitleNum; 								// 字幕个数
	 unsigned int 			 n_CurrentSubTitleIndex;						//当前字幕索引
	 ADIPlayerSubtitleInfo_S m_astSubTitle[ADI_PLAYER_MAX_LANG_NUM];	    // 字幕信息
} ADIPlayerProgramInfo_S;

/*媒体文件信息*/
typedef struct
{
	 ADIPlayerStreamType_E m_eStreamType; 			        // 文件流类型
	 ADI_INT64  m_n64FileSize;								// 文件大小，单位字节	
	 ADI_INT64  m_n64StartTime;						   // 文件播放起始时间，单位ms
	 ADI_INT64  m_n64Duration;							   // 文件总时长，单位ms	
	 unsigned int  m_unBps;									// 文件码率，bits/s
	 char m_acFileName[ADI_PLAYER_MAX_FILE_NAME_LEN];       // 文件名称
	 char m_acAlbum[ADI_PLAYER_TITLE_MAX_LEN];		        // 专辑
	 char m_aczTitle[ADI_PLAYER_TITLE_MAX_LEN];		        // 标题
	 char m_acArtist[ADI_PLAYER_TITLE_MAX_LEN];		        // 艺术家，作者
	 char m_acGenre[ADI_PLAYER_TITLE_MAX_LEN];		        // 风格
	 char m_acComments[ADI_PLAYER_TITLE_MAX_LEN]; 	        // 附注
	 char m_acTime[ADI_PLAYER_TIME_LEN];				    // 创建年份
	 unsigned int  m_ProgramNum; 							// 实际节目个数
	 ADIPlayerProgramInfo_S m_astProgramInfo[ADI_PLAYER_MAX_PROGRAM_NUM];	 // 节目信息
} ADIPlayerFileInfo_S;


typedef  void ( *ADIPLAYERCallback_F  )(ADI_HANDLE hPlayer,ADIPlayerEventType_E eEvent,void * pvUserData);

typedef  void ( *ADIFilePLAYERCallback_F  )(ADI_HANDLE hPlayer, ADIFilePlayerEventType_E ePlayerEvent, void *pvEventData, void * pvUserData);

ADI_Error_Code ADIPLAYERAddPlayerCallback(ADI_HANDLE hPlayer,ADIPLAYERCallback_F fnPlayerCallback,ADIPlayerEventType_E eEvent,void * pvUserData );

ADI_Error_Code ADIPLAYERDelPlayerCallback(ADI_HANDLE hPlayer,ADIPLAYERCallback_F fnPlayerCallback,ADIPlayerEventType_E eEvent, void * pvUserData );

ADI_Error_Code ADIPLAYERAddFilePlayerCallback(ADI_HANDLE hPlayer, ADIFilePLAYERCallback_F fnPlayerCallback, void * pvUserData );

ADI_Error_Code ADIPLAYERDelFilePlayerCallback(ADI_HANDLE hPlayer, ADIFilePLAYERCallback_F fnPlayerCallback, void * pvUserData );

ADI_Error_Code ADIPLAYERGetFileInfo(ADI_HANDLE hPlayer, ADIPlayerFileInfo_S * pstFileInfo);

ADI_Error_Code ADIPLAYEROpen(ADIPLAYERType_E ePlayerType, ADI_HANDLE * phPlayer);

ADI_Error_Code ADIPLAYERClose(ADI_HANDLE hPlayer);

ADI_Error_Code ADIPLAYERSetStream(ADI_HANDLE hPlayer, const ADIStreamInfo_S * psStreamInfo, int nStreamCnt,const ADIPlaybackParam_S * psPlaybackParam);

ADI_Error_Code ADIPLAYERGetStream(ADI_HANDLE hPlayer, ADIStreamInfo_S * psStreamInfo,int * pnStreamCnt);

ADI_Error_Code ADIPLAYERGetPlaybackParam(ADI_HANDLE hPlayer, ADIPlaybackParam_S * psPlaybackParam);

ADI_Error_Code ADIPLAYERStart(ADI_HANDLE hPlayer);

ADI_Error_Code ADIPLAYERStop(ADI_HANDLE hPlayer);

ADI_Error_Code ADIPLAYERPause(ADI_HANDLE hPlayer);

ADI_Error_Code ADIPLAYERResume(ADI_HANDLE hPlayer);

ADI_Error_Code ADIPLAYERClear(ADI_HANDLE hPlayer);

ADI_Error_Code ADIPLAYERSetSpeed(ADI_HANDLE  hPlayer, ADIPlayerSpeed_E eSpeed);

ADI_Error_Code ADIPLAYERGetSpeed(ADI_HANDLE  hPlayer, ADIPlayerSpeed_E *peSpeed);

ADI_Error_Code ADIPLAYERSeek(ADI_HANDLE  hPlayer,const int nPosInSec, const ADIPlayPosition_E ePlayPosFlag);

ADI_Error_Code ADIPLAYERGetCurPosInSec(ADI_HANDLE  hPlayer, int * pnPosInSec);

ADI_Error_Code ADIPLAYERGetDuration(ADI_HANDLE  hPlayer, int *pnSeconds);

ADI_Error_Code ADIPLAYERGetCurPTS(ADI_HANDLE  hPlayer, ADIContentType_E eContentType, ADI_UINT64 *psPTS);

ADI_Error_Code ADIPLAYERCheckStreamType(ADIVIDStreamType_E nStreamType, ADI_BOOL bIsSourceHD);

ADI_Error_Code ADIPLAYERSetFileSubtitleTrack(ADI_HANDLE hPlayer, ADI_BOOL bEnableSubtitle,unsigned int nSubtitleIndex);

ADI_Error_Code ADIPLAYERSetFileAudioTrack(ADI_HANDLE hPlayer, unsigned int nAudIndex);

ADI_Error_Code ADIPLAYERSetDispMode(ADIPlayerDispMode_E eSyncMode);

ADI_Error_Code ADIPLAYERGetStreamEncryptInfo(ADI_HANDLE hPlayer, unsigned short nPID, ADIPlayerStreamEncryptType_E *eEncryptType);

ADI_Error_Code ADIPLAYERGetFileInfoExt(const char * pcFileName, ADIPlayerFileInfo_S * pstFileInfo);

#ifdef  __cplusplus
}
#endif

#endif

