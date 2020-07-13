
#ifndef _ADI_PUBLIC_H_
#define _ADI_PUBLIC_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define ADI_MAX_FILE_NAME_LEN (256)       // �ļ������Ƶ���󳤶�

#define ADI_MAX_URL_LEN (1024)            // URL ��󳤶�

#define ADI_INVALID_PID (0xe000)          // �Ƿ�������ƵPIDֵ

#define ADI_INVALID_INDEX (-1)   	      // �Ƿ����豸id


/*��Ƶ�������ʽ����ע��������ʽ(TS��AVI��ASF������)*/
typedef enum 
{
	EM_ADI_AUD_STREAM_UNKNOWN,      // δ֪���ͣ���������£�����Ӧ����ʶ����Ҫ���ڽ�AVI�������е�����Ƶ
	EM_ADI_AUD_STREAM_AC3,			// Dolby Digital AC3 audio  
	EM_ADI_AUD_STREAM_DTS,			// Digital Surround sound 
	EM_ADI_AUD_STREAM_MPEG1,		// MPEG1/2, layer 1/2. This does not support layer 3 (mp3) 
	EM_ADI_AUD_STREAM_MPEG2,		// MPEG1/2, layer 1/2. This does not support layer 3 (mp3) 
	EM_ADI_AUD_STREAM_CDDA,			// 1979�꣬Philips��Sony��˾�������Ͽ���CD-DA Compact Disc-Digital Audio,���ܹ���������Ƶ����׼ 
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

/*��Ƶ�������ʽ����ע��������ʽ(TS��ES��AVI��ASF������)*/
typedef enum 
{
	EM_ADI_VID_STREAM_UNKNOWN,      // δ֪���ͣ���������£�����Ӧ����ʶ����Ҫ���ڽ�AVI�������е�����Ƶ
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


/*������*/
typedef enum 
{
	EM_ADI_CONTENT_VIDEO = 0,	// ��Ƶ����	 						
	EM_ADI_CONTENT_AUDIO,  	    // ��Ƶ����
	EM_ADI_CONTENT_SUBTITLE,    // ��Ļ����
	EM_ADI_CONTENT_TELTEXT, 	// ͼ�ĵ�������
	EM_ADI_CONTENT_PCR, 		// PCR����	
	EM_ADI_CONTENT_AUDIOAD,  	// Audio Description
	EM_ADI_CONTENT_PMT,  	// PMT��
	EM_ADI_CONTENT_MAX
}ADIContentType_E;

/*������Ϣ����*/
typedef struct
{
	int                         m_nPid;            // ��������PID.pidֵ�ķ�Χ��ѭ13818-1�����ǣ������stream������ע�벥��ģʽ��ʹ��ʱ���븳ֵm_nPid=-1
	ADIContentType_E       	    m_eContentType;    // �����ͣ���ADIContentType_E����
	union 
	{
		ADIVIDStreamType_E m_eVideoType; // ��Ƶ������
		ADIAUDStreamType_E m_eAudioType; // ��Ƶ������
	} m_uStreamType;   	// ���ݵ������ͣ����������֣����Ҹ���m_eContentType������ȷ��ʹ������������������-ADIVIDStreamType_E m_eVideoType����Ƶ�����͡�-ADIAUDStreamType_E m_eAudioType����Ƶ�����͡�
	int   						m_nDemux; //demux index
	
}ADIStreamInfo_S;

/* ��������ṹ���� */
typedef struct 
{
	int m_nX;                // �����������ϽǺ����� 
	int m_nY;                // �����������Ͻ������� 
	int m_nWidth;            // ���������� > 0
	int m_nHeight;           // ��������߶� > 0
} ADIWinRect_S;


#ifdef  __cplusplus
}
#endif

#endif


