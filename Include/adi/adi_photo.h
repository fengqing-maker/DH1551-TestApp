#ifndef _ADI_PHOTO_H_
#define _ADI_PHOTO_H_

#include "adi_typedef.h"
#include "adi_osg.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef struct _ADIPhotoShowRect_S
{
    int m_nShowX;
    int m_nShowY;
    int m_nShowWidth;
    int m_nShowHeight;
} ADIPhotoShowRect_S;

typedef struct _ADIPhotoInfo_S
{
    int m_nWidth;
    int m_nHeight;
} ADIPhotoInfo_S;

typedef enum _ADIPhotoZoom_E
{
    EM_PHOTO_x1,    //图片显示区域不放大
    EM_PHOTO_x2,    //图片显示区域放大2倍
    EM_PHOTO_x4,    //图片显示区域放大4倍
    EM_PHOTO_x8,    //图片显示区域放大8倍
    EM_PHOTO_x16    //图片显示区域放大16倍
} ADIPhotoZoom_E;

typedef enum _ADIPhotoMoveDir_E
{
    EM_PHOTO_MOVE_UP,       //上移
    EM_PHOTO_MOVE_DOWN,     //下移
    EM_PHOTO_MOVE_LEFT,     //左移
    EM_PHOTO_MOVE_RIGHT     //右移
} ADIPhotoMoveDir_E;

typedef enum
{
    EM_PHOTO_ALONG_90 = 0,  //顺时针旋转90度
    EM_PHOTO_COUNTER_90     //逆时针旋转90度
} ADIPhotoRound_E;


typedef enum
{
    EM_PHOTO_DECODE_DONE,  
    EM_PHOTO_DECODE_FAILED,  
    EM_PHOTO_ERROR_FILE
} ADIPhotoEventType_E;

typedef enum
{
    EM_PHOTO_FILE_MODE,              //for local file
    EM_PHOTO_DIRECTMEM_MODE,         // for direct memory input
    EM_PHOTO_MODE_INVALID,
} ADIPhotoSourceMode_E;

typedef struct _ADIPhotoShowPar_S
{
    char *m_pcFileName;             //需要显示的图片带路径文件名
    ADIPhotoShowRect_S m_stRectSD;  //图片在标清上显示的区域
    ADIPhotoShowRect_S m_stRectHD;  //图片在高清上显示的区域,如果是标清平台直接忽略该参数
} ADIPhotoShowPar_S;

typedef struct _ADIPhotoOpenParams_S
{
	ADIPhotoSourceMode_E eSourceMode;
    unsigned char *pu8DirMemInputBuf;       /* Photo Direct Memory Input Buffer */
    unsigned long  u32DirMemInputBufLen;    /* Direct Memory Input Buffer Length */
    unsigned char *pu8FileName;
} ADIPhotoOpenParams_S;


typedef  void ( *ADIPhotoCallback_F  )(ADIPhotoEventType_E eEvent,void * pvUserData);

ADI_Error_Code ADIPhotoInit(void);

ADI_Error_Code ADIPhotoDeinit(void);

ADI_Error_Code ADIPhotoAddCallback(ADIPhotoCallback_F fnPhotoCallback, ADIPhotoEventType_E  eEvent, void * pvUserData);

ADI_Error_Code ADIPhotoDelCallback(ADIPhotoCallback_F fnPhotoCallback, ADIPhotoEventType_E eEvent, void * pvUserData);

ADI_Error_Code ADIPhotoOpen(const char* pcFileName);

ADI_Error_Code ADIPhotoOpenExt(ADIPhotoOpenParams_S *psOpenParams);

ADI_Error_Code ADIPhotoClose(void);

ADI_Error_Code ADIPhotoShow(ADI_HANDLE hSurface, const ADIOSGRect_S* psDstRect);

ADI_Error_Code ADIPhotoPreviewImage(ADIPhotoShowPar_S *pstPhoto);

ADI_Error_Code ADIPhotoFullViewImage(const char *pcFileName);

ADI_Error_Code ADIPhotoShowMutilImage(const ADIPhotoShowPar_S *pstPhotoList, int nCount);

ADI_Error_Code ADIPhotoZoom(ADIPhotoZoom_E enZoom);

ADI_Error_Code ADIPhotoSetMoveTotalStep(int nLeftRight, int nUpDown);

ADI_Error_Code ADIPhotoMove(ADIPhotoMoveDir_E enMoveDir, int nStepCount);

ADI_Error_Code ADIPhotoRotate(ADIPhotoRound_E enRotate);

ADI_Error_Code ADIPhotoGetImageInfo(ADIPhotoInfo_S* pstInfo);

#ifdef  __cplusplus
}
#endif

#endif

