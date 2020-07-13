
#ifndef  __ADIHDMI_H_
#define  __ADIHDMI_H_

#include "adi_typedef.h"
#include "adi_public.h"
#include "adi_error.h"
#include "adi_screen.h"

#ifdef  __cplusplus
extern "C" {
#endif


enum
{
	ADIHDMI_ERROR_BAD_PARAMETER = ADI_HDMI_ERROR_BASE,
	ADIHDMI_ERROR_FEATURE_NOT_SUPPORTED, 			
	ADIHDMI_ERROR_UNKNOWN_ERROR, 
	ADIHDMI_ERROR_NO_MEMORY,
	ADIHDMI_ERROR_INVALID_DEVICE_ID,
	ADIHDMI_ERROR_ALREADY_ADDED,
	ADIHDMI_ERROR_NO_CALLBACK
};


typedef enum _ADIHDMISinkAudioMode_E
{
	EM_ADIHDMI_SINK_AUDIO_MODE_INVALID,
	EM_ADIHDMI_SINK_AUDIO_MODE_PCM,
	EM_ADIHDMI_SINK_AUDIO_MODE_PCM_2CH=EM_ADIHDMI_SINK_AUDIO_MODE_PCM,
	EM_ADIHDMI_SINK_AUDIO_MODE_COMPRESSED,
	EM_ADIHDMI_SINK_AUDIO_MODE_PCM_6CH,
	EM_ADIHDMI_SINK_AUDIO_MODE_AC3PLUS,
	EM_ADIHDMI_SINK_AUDIO_MODE_COUNT
}ADIHDMISinkAudioMode_E;

typedef struct ADIHDMISinkCapabilities_S
{
	ADISCREENResolution_E m_ePreferVideoResolution;
	ADISCREENResolution_E m_eSupportedVideoMode[EM_ADISCREEN_RESOLUTION_NUM];
	ADIHDMISinkAudioMode_E m_ePreferAudioMode;
	ADIHDMISinkAudioMode_E m_eSupportedAudioMode[EM_ADIHDMI_SINK_AUDIO_MODE_COUNT];
}ADIHDMISinkCapabilities_S;

typedef enum 
{
	EM_ADIHDMI_SINK_AUDIO_FORMAT_RESERVED_0,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_LPCM = 1,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_AC3,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_MPEG1,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_MP3,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_MPEG2,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_AAC,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_DTS,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_ATRAC,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_SACD,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_DDPLUS,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_DTS_HD,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_MLP_Dolby_TrueHD,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_DST,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_WMA_Pro,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_RESERVED_15,
	EM_ADIHDMI_SINK_AUDIO_FORMAT_MAX,
}ADIHDMISinkAudioFormat_E;

typedef struct
{
	ADI_BOOL bSupport;
	unsigned int unMaxChannels;
}ADIHDMISinkAudio_S;

typedef enum 
{
	EM_ADIHDMI_SINK_VIDEO_FORMAT_0,         //Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_1_DMT0659, //	1 DMT0659	 4:3				  640x480p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_2_480p,    //	2 480p		 4:3	 8:9		  720x480p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_3_480pH,   //   3 480pH	   16:9    32:37		 720x480p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_4_720p,    //	4 720p		16:9	 1:1		 1280x720p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_5_1080i,   //	5 1080i 	16:9	 1:1		1920x1080i @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_6_480i,    //	6 480i		 4:3	 8:9	720(1440)x480i @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_7_480iH,   //	7 480iH 	16:9	32:37	720(1440)x480i @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_8_240p,    //	8 240p		 4:3	 8:9	720(1440)x240p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_9_240pH,   //	9 240pH 	16:9	32:37	720(1440)x240p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_10_480i4x, // 10 480i4x	 4:3	 8:9	   (2880)x480i @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_11_480i4xH,// 11 480i4xH	16:9	32:37	   (2880)x480i @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_12_240p4x, // 12 240p4x	 4:3	 8:9	   (2880)x240p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_13_240p4xH,// 13 240p4xH	16:9	32:37	   (2880)x240p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_14_480p2x, // 14 480p2x	 4:3	 8:9		 1440x480p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_15_480p2xH,// 15 480p2xH	16:9	32:37		 1440x480p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_16_1080p,  // 16 1080p 	16:9	 1:1		1920x1080p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_17_576p,   // 17 576p		 4:3	16:15		  720x576p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_18_576pH,  // 18 576pH 	16:9	64:45		  720x576p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_19_720p50, // 19 720p50	16:9	 1:1		 1280x720p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_20_1080i25,// 20 1080i25	16:9	 1:1		1920x1080i @ 50 Hz*
	EM_ADIHDMI_SINK_VIDEO_FORMAT_21_576i,   // 21 576i		 4:3	16:15	720(1440)x576i @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_22_576iH,  // 22 576iH 	16:9	64:45	720(1440)x576i @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_23_288p,   // 23 288p		 4:3	16:15	720(1440)x288p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_24_288pH,  // 24 288pH 	16:9	64:45	720(1440)x288p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_25_576i4x, //25 576i4x	 4:3	16:15	   (2880)x576i @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_26_576i4xH,//26 576i4xH	16:9	64:45	   (2880)x576i @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_27_288p4x, //27 288p4x	 4:3	16:15	   (2880)x288p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_28_288p4xH,//28 288p4xH	16:9	64:45	   (2880)x288p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_29_576p2x, //29 576p2x	 4:3	16:15		 1440x576p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_30_576p2xH,//30 576p2xH	16:9	64:45		 1440x576p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_31_1080p50,//31 1080p50	16:9	 1:1		1920x1080p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_32_1080p24,//32 1080p24	16:9	 1:1		1920x1080p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_33_1080p25,//33 1080p25	16:9	 1:1		1920x1080p @ 25 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_34_1080p30,//34 1080p30	16:9	 1:1		1920x1080p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_35_480p4x, //35 480p4x	 4:3	 8:9	   (2880)x480p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_36_480p4xH,//36 480p4xH	16:9	32:37	   (2880)x480p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_37_576p4x, //37 576p4x	4:3 	16:15	   (2880)x576p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_38_576p4xH,//38 576p4xH   16:9	  64:45 	 (2880)x576p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_39_1080i25,//39 1080i25   16:9	   1:1		  1920x1080i @ 50 Hz* (1250 Total)
	EM_ADIHDMI_SINK_VIDEO_FORMAT_40_1080i50,//40 1080i50   16:9	   1:1		  1920x1080i @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_41_720p100,//41 720p100   16:9	   1:1		   1280x720p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_42_576p100,//42 576p100    4:3	   8:9			720x576p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_43_576p100H,//43 576p100H  16:9	  32:37 		720x576p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_44_576i50, //44 576i50	   4:3	  16:15   720(1440)x576i @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_45_576i50H,//45 576i50H   16:9	  64:45   720(1440)x576i @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_46_1080i60,//46 1080i60   16:9	   1:1		  1920x1080i @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_47_720p120,//47 720p120   16:9	   1:1		   1280x720p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_48_480p119,//48 480p119    4:3	  16:15 		720x480p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_49_480p119H,//49 480p119H  16:9	  64:45 		720x480p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_50_480i59, //50 480i59	   4:3	   8:9	  720(1440)x480i @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_51_480i59H,//51 480i59H   16:9	  32:37   720(1440)x480i @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_52_576p200,//52 576p200    4:3	  16:15 		720x576p @ 200 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_53_576p200H,//53 576p200H  16:9	  64:45 		720x576p @ 200 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_54_576i100, //54 576i100    4:3	  16:15   720(1440)x576i @ 200 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_55_576i100H,//55 576i100H  16:9	  64:45   720(1440)x576i @ 200 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_56_480p239, //56 480p239    4:3	   8:9			720x480p @ 239.76/240 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_57_480p239H,//57 480p239H  16:9	  32:37 		720x480p @ 239.76/240 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_58_480i119, //58 480i119    4:3	   8:9	  720(1440)x480i @ 239.76/240 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_59_480i119H,//59 480i119H  16:9	  32:37   720(1440)x480i @ 239.76/240 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_60_720p24,  //60 720p24	  16:9	   1:1		   1280x720p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_61_720p25,  //61 720p25	  16:9	   1:1		   1280x720p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_62_720p30,  //62 720p30	  16:9	   1:1		   1280x720p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_63_1080p120,//63 1080p120  16:9	   1:1		  1920x1080p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_64_1080p100,//64 1080p100  16:9	   1:1		  1920x1080p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_65_720p24,  //65 720p24	  64:27    4:3		   1280x720p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_66_720p25,  //66 720p25	  64:27    4:3		   1280x720p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_67_720p30,  //67 720p30	  64:27    4:3		   1280x720p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_68_720p50,  //68 720p50	  64:27    4:3		   1280x720p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_69_720p,    //69 720p	  64:27    4:3		   1280x720p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_70_720p100, //70 720p100   64:27    4:3		   1280x720p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_71_720p120, //71 720p120   64:27    4:3		   1280x720p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_72_1080p24, //72 1080p24   64:27    4:3		  1920x1080p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_73_1080p25, //73 1080p25   64:27    4:3		  1920x1080p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_74_1080p30, //74 1080p30   64:27    4:3		  1920x1080p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_75_1080p50, //75 1080p50   64:27    4:3		  1920x1080p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_76_1080p,   //76 1080p	  64:27    4:3		  1920x1080p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_77_1080p100,//77 1080p100  64:27    4:3		  1920x1080p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_78_1080p120,//78 1080p120  64:27    4:3		  1920x1080p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_79_720p24,  //79  720p24   64:27   64:63 	   1680x720p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_80_720p25,  //80  720p25   64:27   64:63 	   1680x720p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_81_720p30,  //81  720p30   64:27   64:63 	   1680x720p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_82_720p50,  //82  720p50   64:27   64:63 	   1680x720p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_83_720p,    //83  720p	  64:27   64:63 	   1680x720p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_84_720p100,//84  720p100  64:27   64:63 	   1680x720p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_85_720p120,//85  720p120  64:27   64:63 	   1680x720p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_86_1080p24,//86 1080p24   64:27    1:1		  2560x1080p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_87_1080p25,//87 1080p25   64:27    1:1		  2560x1080p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_88_1080p30,//88 1080p30   64:27    1:1		  2560x1080p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_89_1080p50,//89 1080p50   64:27    1:1		  2560x1080p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_90_1080p,  //90 1080p	  64:27    1:1		  2560x1080p @ 59.94/60 Hz 
	EM_ADIHDMI_SINK_VIDEO_FORMAT_91_1080p100,//91 1080p100  64:27    1:1		  2560x1080p @ 100 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_92_1080p120,//92 1080p120  64:27    1:1		  2560x1080p @ 119.88/120 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_93_2160p24,//93 2160p24   16:9	   1:1		  3840x2160p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_94_2160p25,//94 2160p25   16:9	   1:1		  3840x2160p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_95_2160p30,//95 2160p30   16:9	   1:1		  3840x2160p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_96_2160p50,//96 2160p50   16:9	   1:1		  3840x2160p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_97_2160p,  //97 2160p	  16:9	   1:1		  3840x2160p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_98_2160p24,//98 2160p24  256:135   1:1		  4096x2160p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_99_2160p25,//99 2160p25  256:135   1:1		  4096x2160p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_100_2160p30,//100 2160p30  256:135   1:1		  4096x2160p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_101_2160p50,//101 2160p50  256:135   1:1		  4096x2160p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_102_2160p, //102 2160p	 256:135   1:1		  4096x2160p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_103_2160p24,//103 2160p24   64:27    4:3		  3840x2160p @ 23.98/24 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_104_2160p25,//104 2160p25   64:27    4:3		  3840x2160p @ 25Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_105_2160p30,//105 2160p30   64:27    4:3		  3840x2160p @ 29.97/30 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_106_2160p50,//106 2160p50   64:27    4:3		  3840x2160p @ 50 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_107_2160p, //107 2160p	  64:27    4:3		  3840x2160p @ 59.94/60 Hz
	EM_ADIHDMI_SINK_VIDEO_FORMAT_108,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_109,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_110,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_111,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_112,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_113,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_114,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_115,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_116,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_117,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_118,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_119,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_120,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_121,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_122,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_123,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_124,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_125,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_126,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_127,//Reserved
	EM_ADIHDMI_SINK_VIDEO_FORMAT_MAX,
}ADIHDMISinkVideoFormat_E;


typedef struct
{
	ADIHDMISinkAudio_S sSinkAudio[EM_ADIHDMI_SINK_AUDIO_FORMAT_MAX];
	ADI_BOOL bSinkVideoSupport[EM_ADIHDMI_SINK_VIDEO_FORMAT_MAX];
}ADIHDMISinkInfo_S;



typedef enum _ADIHDMIPropertyType_E
{
	EM_ADIHDMI_SPD_VENDOR_NAME,         //eight 7-bit ASCII characters, must be less than 8byte
	EM_ADIHDMI_SPD_PRODUCT_DESCRIPTION, //sixteen 7-bit ASCII characters,mute be less than 16 byte
	EM_ADIHDMI_HDCP_KEY_INFO,
	EM_ADIHDMI_LINK_STATUS,
	EM_ADIHDMI_PROPERT_COUNT		
}ADIHDMIPropertyType_E;

typedef enum
{
    EM_ADIHDMI_RECEIVER_PLUGIN,
    EM_ADIHDMI_RECEIVER_PLUGOUT
}ADIHDMIEvent_E;


typedef enum
{
	EM_ADIHDMI_STATUS_UNLINK,
    EM_ADIHDMI_STATUS_LINK_HDCP_SUCCESSED,
	EM_ADIHDMI_STATUS_LINK_HDCP_FAILED,
	EM_ADIHDMI_STATUS_LINK_HDCP_IGNORED,
	EM_ADIHDMI_STATUS_MAX
}ADIHDMILinkStatus_E;


typedef struct
{
	unsigned char ucInEncryptKey[512];
	unsigned char ucOutEncryptKey[512];
}ADIHDMIEncryptHdcpKey_S;


typedef void (*ADIHDMICallback_F)(ADIHDMIEvent_E eEvt, int nHdmiIndex, void* pvEventData, void * pvUserData);



ADI_Error_Code ADIHDMIGetCount(int * pnHdmiDeviceCount);


ADI_Error_Code ADIHDMIGetSinkCapabilities(int nHdmiIndex, ADIHDMISinkCapabilities_S *pCaps);

ADI_Error_Code ADIHDMIGetSinkInfo(int nHdmiIndex, ADIHDMISinkInfo_S *pSinkInfo);

ADI_Error_Code ADIHDMISetProperty(int nHdmiIndex, ADIHDMIPropertyType_E ePropetyType, void* pvData);


ADI_Error_Code ADIHDMIAddCallback(int nHdmiIndex, ADIHDMICallback_F fnHdmiCallback,void * pvUserData );


ADI_Error_Code ADIHDMIDelCallback(int nHdmiIndex, ADIHDMICallback_F fnHdmiCallback, void * pvUserData );


ADI_Error_Code ADIHDMIGetProperty(int nHdmiIndex, ADIHDMIPropertyType_E ePropetyType, void* pvData, int* pnLen);


ADI_Error_Code ADIHDMIEncryptHdcpKey(ADIHDMIEncryptHdcpKey_S *psHdmiEncryptHdcpKey);


ADI_Error_Code ADIHDMIHDCPEnable(int nHdmiIndex, ADI_BOOL bEnable);


#ifdef  __cplusplus
}
#endif


#endif


