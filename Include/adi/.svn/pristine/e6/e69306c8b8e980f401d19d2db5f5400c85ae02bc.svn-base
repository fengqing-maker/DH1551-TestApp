
#ifndef _ADI_PUBLIC_H_
#define _ADI_PUBLIC_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define ADI_MAX_FILE_NAME_LEN (256)       // 文件夹名称的最大长度

#define ADI_MAX_URL_LEN (1024)            // URL 最大长度

#define ADI_INVALID_PID (0xe000)          // 非法的音视频PID值

#define ADI_INVALID_INDEX (-1)   	      // 非法的设备id


/*音频流编码格式，需注意与打包格式(TS、AVI、ASF等区别)*/
typedef enum 
{
	EM_ADI_AUD_STREAM_UNKNOWN,      // 未知类型，这种情况下，驱动应尽量识别，主要用于解AVI等容器中的音视频
	EM_ADI_AUD_STREAM_AC3,			// Dolby Digital AC3 audio  
	EM_ADI_AUD_STREAM_DTS,			// Digital Surround sound 
	EM_ADI_AUD_STREAM_MPEG1,		// MPEG1/2, layer 1/2. This does not support layer 3 (mp3) 
	EM_ADI_AUD_STREAM_MPEG2,		// MPEG1/2, layer 1/2. This does not support layer 3 (mp3) 
	EM_ADI_AUD_STREAM_CDDA,			// 1979年，Philips和Sony公司结盟联合开发CD-DA Compact Disc-Digital Audio,精密光盘数字音频）标准 
	EM_ADI_AUD_STREAM_PCM,			// PCM data
	EM_ADI_AUD_STREAM_LPCM,		
  	EM_ADI_AUD_STREAM_MP3,			//  MPEG1/2, layer 3 
  	EM_ADI_AUD_STREAM_MPEG_AAC,		//  Advanced audio coding. Part of MPEG-4  
  	EM_ADI_AUD_STREAM_HE_AAC,		//  AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE)  
  	EM_ADI_AUD_STREAM_RAW_AAC,	    
	EM_ADI_AUD_STREAM_AAC_PLUS_ADTS, //   AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE), with ADTS (Audio Data Transport Format)  
	EM_ADI_AUD_STREAM_AAC_PLUS_LOAS, //  AAC plus SBR. aka MPEG-4 High Efficiency (AAC-HE), with LOAS (Low Overhead Audio Stream)  
	EM_ADI_AUD_STREAM_AC3_PLUS,		//   Dolby Digital Plus (AC3+ or DDP) audio 
	EM_ADI_AUD_STREAM_DTS_HD,		//   Digital Surround sound, HD 
  	EM_ADI_AUD_STREAM_WMA_STD,		//   WMA Standard  
  	EM_ADI_AUD_STREAM_WMA_PRO,		//   WMA Professional 
  	EM_ADI_AUD_STREAM_DRA,			// DRA1
  	EM_ADI_AUD_STREAMTYPE_NUM				
}ADIAUDStreamType_E;							

/*视频流编码格式，需注意与打包格式(TS、ES、AVI、ASF等区别)*/
typedef enum 
{
	EM_ADI_VID_STREAM_UNKNOWN,      // 未知类型，这种情况下，驱动应尽量识别，主要用于解AVI等容器中的音视频
	EM_ADI_VID_STREAM_MPEG1,		// MPEG-1 Video (ISO/IEC 11172-2) 
	EM_ADI_VID_STREAM_MPEG2,		// MPEG-2 Video (ISO/IEC 13818-2)  
	EM_ADI_VID_STREAM_MPEG4,		// MPEG-4 Part 2 Video  
	EM_ADI_VID_STREAM_H264,			// H.264 (ITU-T) or ISO/IEC 14496-10/MPEG-4 AVC 
	EM_ADI_VID_STREAM_H263,			// H.263 Video. The value of the enum is not based on PSI standards 
	EM_ADI_VID_STREAM_VC1,			// VC-1 Advanced Profile  
	EM_ADI_VID_STREAM_VC1_SM,		// VC-1 Simple&Main Profile 
	EM_ADI_VID_STREAM_DIVX_311,		// DivX 3.11 coded video 
	EM_ADI_VID_STREAM_HEVC,
  	EM_ADI_VID_STREAMTYPE_NUM
}ADIVIDStreamType_E;


/*流类型*/
typedef enum 
{
	EM_ADI_CONTENT_VIDEO = 0,	// 视频类型	 						
	EM_ADI_CONTENT_AUDIO,  	    // 音频类型
	EM_ADI_CONTENT_SUBTITLE,    // 字幕类型
	EM_ADI_CONTENT_TELTEXT, 	// 图文电视类型
	EM_ADI_CONTENT_PCR, 		// PCR类型	
	EM_ADI_CONTENT_AUDIOAD,  	// Audio Description
	EM_ADI_CONTENT_PMT,  	// PMT表
	EM_ADI_CONTENT_MAX
}ADIContentType_E;

/*播放信息类型*/
typedef struct
{
	int                         m_nPid;            // 数据所在PID.pid值的范围遵循13818-1。但是，如果此stream在数据注入播放模式中使用时，请赋值m_nPid=-1
	ADIContentType_E       	    m_eContentType;    // 流类型，见ADIContentType_E定义
	union 
	{
		ADIVIDStreamType_E m_eVideoType; // 视频流类型
		ADIAUDStreamType_E m_eAudioType; // 音频流类型
	} m_uStreamType;   	// 数据的流类型，有如下两种，并且根据m_eContentType的类型确定使用以下哪种数据流。-ADIVIDStreamType_E m_eVideoType：视频流类型。-ADIAUDStreamType_E m_eAudioType：音频流类型。
	int   						m_nDemux; //demux index
	
}ADIStreamInfo_S;

/* 矩形区域结构定义 */
typedef struct 
{
	int m_nX;                // 矩形区域左上角横坐标 
	int m_nY;                // 矩形区域左上角纵坐标 
	int m_nWidth;            // 矩形区域宽度 > 0
	int m_nHeight;           // 矩形区域高度 > 0
} ADIWinRect_S;


#ifdef  __cplusplus
}
#endif

#endif


