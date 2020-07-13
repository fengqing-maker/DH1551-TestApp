
#ifndef _ADI_PLAYER_H_
#define _ADI_PLAYER_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_record.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif


/*������ش������ֵ*/
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

/*��������ö�ٶ���*/
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

#define ADI_PLAYER_MAX_FILE_NAME_LEN         (512)  //�ļ����Ƴ���
#define ADI_PLAYER_TITLE_MAX_LEN             (512)  //�ļ����⡢���ߵ�����ַ���
#define ADI_PLAYER_TIME_LEN                  (8)    //����ֽ���
#define ADI_PLAYER_MAX_PROGRAM_NUM           (5)    //����Ŀ��������tsý���ļ�����Ŀ�����������5�����򲥷������ֻ�ܴ洢����ĳ5����Ŀ��Ϣ�����������е�ĳһ��
#define ADI_PLAYER_MAX_STREAM_NUM            (5)    // ������ 
#define ADI_PLAYER_MAX_LANG_NUM              (10)    //֧�ֵ���������������
#define ADI_PLAYER_LANG_LEN                  (4)    //�����ַ���
#define ADI_PLAYER_SUB_TITLE_LEN             (8)    //��Ļ���ⳤ��

#define EM_ADIFILEPLAYER_ERR_BASE        (1<<16) ///<�ļ����Ŵ������ͻ���ֵ
#define EM_ADIFILEPLAYER_STATE_BASE    (2<<16)	///<�ļ�����״̬���ͻ���ֵ


/*�ļ������ͣ����ŵ��ļ����� */
typedef enum
{
	 EM_ADIFILEPLAYER_STREAM_ES = 0x0,	 // es���ļ�
	 EM_ADIFILEPLAYER_STREAM_TS, 		 // ts���ļ�
	 EM_ADIFILEPLAYER_STREAM_NORMAL, 	 // ��ͨ�ļ�����idx,lrc,srt����Ļ�ļ�
	 EM_ADIFILEPLAYER_STREAM_NET,		 // �������ļ�
	 EM_ADIFILEPLAYER_STREAM_END
} ADIPlayerStreamType_E;


/*����ģʽö�ٶ���*/
typedef enum
{
	EM_ADIPLAYER_LIVE,			// ֱ��ģʽ
	EM_ADIPLAYER_FILE,			// �ļ�����ģʽ�����������ļ��������ļ�
	EM_ADIPLAYER_TSHIFT,		// PVR¼��ʱ�Ʋ���ģʽ
	EM_ADIPLAYER_INJECT,		// ����ע�벥��ģʽ
	EM_ADIPLAYER_PVR,			// PVR¼�Ʋ���ģʽ
	EM_ADIPLAYER_MAXPLAYERTYPE  // �������ֵ����������Ϊ������
}ADIPLAYERType_E;

/*��̨����ģʽ����*/
typedef enum
{
    EM_ADIPLAYER_DISPMODE_UNTIL_SYNC = 0,    //����������Ƶͬ��
    EM_ADIPLAYER_DISPMODE_SLOW_MOTION,       //��ͬ��
    EM_ADIPLAYER_DISPMODE_FIRST_FRAME		 //��ʾ��һ֡
} ADIPlayerDispMode_E;


/*�طŲ���ģʽ(EM_ADIPLAYER_FILE��EM_ADIPLAYER_PVR��EM_ADIPLAYER_TSHIFT)�µĲ������ݽṹ*/
typedef struct 
{
	int                         m_nSecondPos;    // �طŵ���ʼλ��
	ADIPlayerSpeed_E 			m_eSpeed;        // �طŵ��ٶ�
	char                        m_szFileName[ADI_MAX_URL_LEN];     	// �طŵ����ļ���·��,ֻ֧��ASCII�����ʽ
    ADIStreamEncryptParam_S     m_stEncryptParam; 
}ADIPlaybackParam_S;

/*����ͨ���豸��Դ���ݽṹ����*/
typedef struct 
{
	int m_nDemux;			// Demux�豸��Index��ADI_INVALID_INDEX��������Demux�豸
	int m_nVideoDecoder;	// ��Ƶ���������豸Index��ADI_INVALID_INDEX����������Ƶ������
	int m_nAudioDecoder;	// ��Ƶ���������豸Index��ADI_INVALID_INDEX����������Ƶ������
}ADIPlayerChnl_S;

/*�ط�ƫ����ʼλ��ö�ٶ���*/
typedef enum
{
	EM_ADIPLAYER_POSITION_FROM_HEAD = 0,  	// ���ļ�ͷ��ʼ����ƫ��
	EM_ADIPLAYER_POSITION_FROM_CURRENT,		// �ӵ�ǰλ�ü���ƫ��
	EM_ADIPLAYER_POSITION_FROM_END			// ���ļ�β����ƫ��
}ADIPlayPosition_E;

/*�Ǳ����ļ�����ʱ������Ƶ�����¼�ö�ٶ���*/
typedef enum 
{
	
	EM_ADIPLAYER_VIDEO_FRAME_COMING,		// video��֡�¼� ���¼�Ӧ�ñ�֤����Ƶ��������������һֱ���Լ������������ǲ��Ž�Ŀ��ʼ����ʱֻ������1��
	EM_ADIPLAYER_AUDIO_FRAME_COMING,		// audio��֡�¼�
	
	EM_ADIPLAYER_VIDEO_UNDERFLOW,		    // ��Ƶ�����������¼�
	EM_ADIPLAYER_AUDIO_UNDERFLOW,		    // ��Ƶ�����������¼�  
	
	EM_ADIPLAYER_VIDEO_OVERFLOW,		    // ��Ƶ�����������¼�
	EM_ADIPLAYER_AUDIO_OVERFLOW,		    // ��Ƶ�����������¼�

	EM_ADIPLAYER_VIDEO_SOURCE_CHANGE,		// ��ƵԴ�ı��¼�������width,height,framerate�����ı�
	EM_ADIPLAYER_AUDIO_SOURCE_CHANGE,		// ��ƵԴ�ı��¼�������codec�ı�
	
	EM_ADIPLAYER_END_OF_STREAM,				// �������ļ�ĩβ����������ģʽΪEM_ADIPLAYER_FILE��EM_ADIPLAYER_PVR����EM_ADIPLAYER_TSHIFTʱ�Ż��и��¼�����
	EM_ADIPLAYER_BEGIN_OF_STREAM,			// �������ļ���ͷ, ��������ģʽΪEM_ADIPLAYER_FILE��EM_ADIPLAYER_PVR����EM_ADIPLAYER_TSHIFT�ҿ��˻�����ʱ�Ż��и��¼�����

	EM_ADIPLAYER_VIDEO_DECODER_DECODING,
	EM_ADIPLAYER_VIDEO_DECODER_NODATA,
	EM_ADIPLAYER_AUDIO_DECODER_DECODING,
	EM_ADIPLAYER_AUDIO_DECODER_NODATA,
	EM_ADIPLAYER_VIDEO_DECODER_ERROR,
	EM_ADIPLAYER_MAXEVENTTYPE				// �߽�ֵ
}ADIPlayerEventType_E; 


/**�����ļ����ţ�����Ƶ�����¼�ö�ٶ���*/
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


/*��Ƶ����Ϣ */
typedef struct
{
	 int            m_nStreamIndex;		   // ������������ts������ֵΪ��pid
	 unsigned int   m_uFormat;			   // ��Ƶ�����ʽ��ֵ����ο�::ADIVIDStreamType_E ,����ʵ�ֵ�ʱ��Ҫע��ת��
	 unsigned int   m_uWidth;			   // ��ȣ���λ����
	 unsigned int   m_uHeight;			   // �߶ȣ���λ����
	 unsigned int   m_uFpsInteger;		   // ֡�ʣ���������
	 unsigned int   m_uFpsDecimal;		   // ֡�ʣ�С������
	 unsigned int 	m_uBps; 			   // ��Ƶ���ʣ�bits/s
	 unsigned int   m_uExtradataSize;	   // ��չ���ݳ���
	 unsigned char  *m_puExtradata;		   // ��չ����
} ADIPlayerVidInfo_S;

/*��Ƶ����Ϣ */
typedef struct
{
	 int           m_nStreamIndex;				    // ������������ts������ֵΪ��pid���Ƿ�ֵΪ::HI_FORMAT_INVALID_STREAM_ID
	 unsigned int  m_uFormat;					    // ��Ƶ�����ʽ��ֵ����ο�::ADIAUDStreamType_E ,����ʵ�ֵ�ʱ��Ҫע��ת��
	 unsigned int  m_uVersion; 					    // ��Ƶ����汾������wma���룬0x160(WMAV1), 0x161 (WMAV2)
	 unsigned int  m_uSampleRate;				    // 8000,11025,441000,...
	 unsigned int  m_uBitPerSample;				    // ��Ƶÿ����������ռ�ı�������8bit,16bit
	 unsigned int  m_uChannels;					    // ������, 1 or 2
	 unsigned int  m_uBlockAlign;				    // packet�������ֽ���
	 unsigned int  m_uBps; 						    // ��Ƶ���ʣ�bits/s
	 ADI_BOOL          m_bBigEndian;				    // ��С�ˣ���pcm��ʽ��Ч
	 char          m_acAudLang[ADI_PLAYER_LANG_LEN];// ��Ƶ������
	 unsigned int  m_ExtradataSize;				    // ��չ���ݳ���
	 unsigned char  *m_pu8Extradata;				// ��չ����
} ADIPlayerAudInfo_S;

/*��Ļ�������� */
typedef enum
{
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_TEXT = 0x0,	  // �ַ���
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_BMP, 		  // bmpͼƬ
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_ASS, 		  // ass��Ļ
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_HDMV_PGS,	  // pgs��Ļ
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_BMP_SUB, 	  // sub��Ļ
	 EM_ADIFILEPLAYER_SUBTITLE_DATA_END
} ADIPlayerSubtitleDataType_E;


/*��Ļ��Ϣ */
typedef struct
{
	 int                         m_nStreamIndex; 		// ������������ts������ֵΪ��pid
	 ADI_BOOL                        m_bExtSubTitle; 		// �Ƿ�Ϊ�����Ļ
	 ADIPlayerSubtitleDataType_E m_eSubtitileType;	    // ��Ļ��ʽ����bmp,string
	 char m_acSubTitleName[ADI_PLAYER_SUB_TITLE_LEN];   // ��Ļ����
	 unsigned int                m_uOriginalFrameWidth; // ԭʼͼ����
	 unsigned int                m_uOriginalFrameHeight;// ԭʼͼ��߶�
	 unsigned int                m_uHorScale;			// ˮƽ���űȣ�0-100
	 unsigned int                m_uVerScale;			// ��ֱ���űȣ�0-100
	 unsigned int                m_ExtradataSize;		// ��չ���ݳ���
	 unsigned short              m_pu8Extradata[256]; 		// ��չ����
} ADIPlayerSubtitleInfo_S;

typedef struct
{
	 ADIPlayerVidInfo_S      m_stVidStream;								    // ��Ƶ����Ϣ
	 unsigned int            m_AudStreamNum;								// ��Ƶ������
	 unsigned int 			 n_CurrentAudIndex;								//��ǰ��Ƶ����
	 ADIPlayerAudInfo_S      m_astAudStream[ADI_PLAYER_MAX_STREAM_NUM];		// ��Ƶ����Ϣ
	 unsigned int            m_SubTitleNum; 								// ��Ļ����
	 unsigned int 			 n_CurrentSubTitleIndex;						//��ǰ��Ļ����
	 ADIPlayerSubtitleInfo_S m_astSubTitle[ADI_PLAYER_MAX_LANG_NUM];	    // ��Ļ��Ϣ
} ADIPlayerProgramInfo_S;

/*ý���ļ���Ϣ*/
typedef struct
{
	 ADIPlayerStreamType_E m_eStreamType; 			        // �ļ�������
	 ADI_INT64  m_n64FileSize;								// �ļ���С����λ�ֽ�	
	 ADI_INT64  m_n64StartTime;						   // �ļ�������ʼʱ�䣬��λms
	 ADI_INT64  m_n64Duration;							   // �ļ���ʱ������λms	
	 unsigned int  m_unBps;									// �ļ����ʣ�bits/s
	 char m_acFileName[ADI_PLAYER_MAX_FILE_NAME_LEN];       // �ļ�����
	 char m_acAlbum[ADI_PLAYER_TITLE_MAX_LEN];		        // ר��
	 char m_aczTitle[ADI_PLAYER_TITLE_MAX_LEN];		        // ����
	 char m_acArtist[ADI_PLAYER_TITLE_MAX_LEN];		        // �����ң�����
	 char m_acGenre[ADI_PLAYER_TITLE_MAX_LEN];		        // ���
	 char m_acComments[ADI_PLAYER_TITLE_MAX_LEN]; 	        // ��ע
	 char m_acTime[ADI_PLAYER_TIME_LEN];				    // �������
	 unsigned int  m_ProgramNum; 							// ʵ�ʽ�Ŀ����
	 ADIPlayerProgramInfo_S m_astProgramInfo[ADI_PLAYER_MAX_PROGRAM_NUM];	 // ��Ŀ��Ϣ
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

