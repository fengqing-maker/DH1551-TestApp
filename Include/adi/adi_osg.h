
#ifndef _ADI_OSG_H_
#define _ADI_OSG_H_


#include "adi_typedef.h"
#include "adi_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*���ش������ö�ٶ��塣*/
enum {
	ADIOSG_ERROR_BAD_PARAMETER = ADI_OSG_ERROR_BASE,
    ADIOSG_ERROR_FEATURE_NOT_SUPPORTED,
    ADIOSG_ERROR_UNKNOWN_ERROR,
    ADIOSG_ERROR_NO_MEMORY,
    ADIOSG_ERROR_DEVICE_BUSY
};

/*��ɫģʽö�ٶ���*/
typedef enum {
    EM_ADIOSG_PIXEL_FORMAT_RGB_565,      //  16-bit, no per-pixel alpha 
    EM_ADIOSG_PIXEL_FORMAT_ARGB_1555,    //  16-bit 
    EM_ADIOSG_PIXEL_FORMAT_RGBA_5551,    //  16-bit 
    EM_ADIOSG_PIXEL_FORMAT_ARGB_4444,    //  16-bit 
    EM_ADIOSG_PIXEL_FORMAT_RGBA_4444,    //  16-bit 

    EM_ADIOSG_PIXEL_FORMAT_RGB_888,      //  24-bit 
    EM_ADIOSG_PIXEL_FORMAT_ARGB_8888,    //  32-bit 
    EM_ADIOSG_PIXEL_FORMAT_PALETTE8,     //  8-bit Palette index��Ŀǰû�е�ɫ���Surface����ɫ��ĽṹԤ����

    EM_ADIOSG_PIXEL_FORMAT_YCBCR888_444, // Y, Cb, Cr signed components with 8 bit precision in a 4:4:4 sampling model
    EM_ADIOSG_PIXEL_FORMAT_YCBCR888_422, // Y, Cb, Cr signed components with 8 bit precision in a 4:2:2 sampling model
	EM_ADIOSG_PIXEL_FORMAT_YCBCR888_420, // Y, Cb, Cr signed components with 8 bit precision in a 4:2:0 sampling model
    EM_ADIOSG_PIXEL_FORMAT_YCBCR888_411, // Y, Cb, Cr signed components with 8 bit precision in a 4:1:1 sampling model
    EM_ADIOSG_PIXEL_FORMAT_NUM           // ���ظ�ʽ������
} ADIOSGPixelFormat_E;


/*���ģʽö�ٶ��� */
typedef enum {
    EM_ADIOSG_OPMODE_COPY,               //  src 
    EM_ADIOSG_OPMODE_XOR,                //  src ^ dst 
    EM_ADIOSG_OPMODE_OR,                 //  src | dst 
    EM_ADIOSG_OPMODE_AND,                //  src & dst 
    EM_ADIOSG_OPMODE_CLEAR,              //  0 
    EM_ADIOSG_OPMODE_SET,                //  11111111 
    EM_ADIOSG_OPMODE_EQUIV,              //  ~(src ^ dst) 
    EM_ADIOSG_OPMODE_NOR,	             //  ~(src | dst) 
    EM_ADIOSG_OPMODE_NAND,               //  ~(src & dst) 
    EM_ADIOSG_OPMODE_INVERT,             //  ~dst 
    EM_ADIOSG_OPMODE_COPYINVERTED,       //  ~src 
    EM_ADIOSG_OPMODE_ORINVERTED,         //  ~src | dst 
    EM_ADIOSG_OPMODE_ANDINVERTED,        //  ~src & dst 
    EM_ADIOSG_OPMODE_ORREVERSE,          //  src | ~dst 
    EM_ADIOSG_OPMODE_ANDREVERSE,         //  src & ~dst 
    EM_ADIOSG_OPMODE_NOOP,               //  dst 
    EM_ADIOSG_OPMODE_ALPHA,              //  Alpha mode  from DST
    EM_ADIOSG_OPMODE_ALPHA_SRC           //  Alpha mode   from SRC
} ADIOSGOpMode_E;


/*��ͼƽ��ṹ���塣 */
typedef struct {
	ADIOSGPixelFormat_E m_ePixelFormat;     //  �û�ͼƽ��֧����ɫģʽ 
	int m_nWidth;                           //  �û�ͼƽ��Ŀ��  > 0
	int m_nHeight;                          //  �û�ͼƽ��ĸ߶� > 0

	int m_nPitch;                           //  �û�ͼƽ��ÿ���ֽ���,width*BytesPerPixel 
	int m_nColorKeyFlag;                    //  �ñ�־Ϊ 1 ʱ��ʾm_uColorKey �����ã���ʼ��Ϊ 0
	int m_nAlphaFlag;                       //  �ñ�־Ϊ 1 ʱ��ʾ��ƽ���ȫ��m_uAlpha�����ã���ʼ��Ϊ 0
    unsigned int m_uColorkey;               //  �û�ͼƽ���colorKey ,AGRB888ģʽ������ֵ��ָ������ɫ���ڸû�ͼƽ�治����ʾ Ĭ��0x00000000
    unsigned int m_uAlpha;                  //  �û�ͼƽ���͸���ȣ�[0x00,0xFF],0x00��ʾ��ȫ͸��;0xFF��ʾ��͸����Ĭ��Ϊ0xFF
    void * m_pvSurfaceMem;                  //  �û�ͼƽ����ڴ��ַ ,�����Surface����ֱ�ӻ��ƣ���������Դ�Surface��,�븳ADI_NULL
    int m_nMemSize;                         //  �û�ͼƽ����ڴ��С 
    void *m_pvPalette;                      //  m_ePixelFormat ΪEM_ADIOSG_PIXEL_FORMAT_PALETTE8ʱָ���ĵ�ɫ����������Ŀǰû�е�ɫ���Surface,��ɫ��ĽṹԤ��������void *
} ADIOSGSurfaceInfo_S;

/*��������ṹ���� */
typedef struct {
    int m_nX;                // �����������ϽǺ����� 
    int m_nY;                // �����������Ͻ������� 
	int m_nWidth;            // ���������� > 0
	int m_nHeight;           // ��������߶� > 0
} ADIOSGRect_S;


/*��������ṹ���� */
typedef struct {
	unsigned int m_unPixel;  //color
    int m_nX1;               // start X address  
    int m_nY1;               // start Y address  
	int m_nX2;               // end X address
	int m_nY2;               // end Y address
	int m_nLinewidth;        // Line width
} ADIOSGLine_S;


/*ͼƬ����ģʽö�ٶ��� */
typedef enum {
    EM_ADIOSG_SCALE_FULLSIZE,   // �����ţ���ԭʼ��С���
    EM_ADIOSG_SCALE_OPTIMUM,   	// ����ƥ�䣬��ģʽ��ͼƬ����ԭʼ���������������ռ�����������������
    EM_ADIOSG_SCALE_FIXSIZE     // �����������ţ��������߾�Ϊָ��ֵ�������������ʵ�����ݲ�һ�£����������
} ADIOSGScalingMode_E;


ADI_Error_Code ADIOSGCreateSurface(ADIOSGPixelFormat_E ePixelFormat, int nWidth, int nHeight, ADI_HANDLE * phSurface);

ADI_Error_Code ADIOSGDestroySurface(ADI_HANDLE hSurface);

ADI_Error_Code ADIOSGGetDisplaySurface(int nIndex, ADI_HANDLE * phSurface);

ADI_Error_Code ADIOSGGetSurfaceInfo(ADI_HANDLE hSurface, ADIOSGSurfaceInfo_S * psSurfaceInfo);

ADI_Error_Code ADIOSGSetSurfaceInfo(ADI_HANDLE hSurface, const ADIOSGSurfaceInfo_S * psSurfaceInfo);


ADI_Error_Code ADIOSGBlit(ADI_HANDLE hDstSurface, const ADIOSGRect_S * psDstRect,
                        ADI_HANDLE hSrcSurface, const ADIOSGRect_S * psSrcRect, ADIOSGOpMode_E eOpMode);

ADI_Error_Code ADIOSGFill(ADI_HANDLE hDstSurface, const ADIOSGRect_S * psDstRect, unsigned int uPixel);

ADI_Error_Code ADIOSGDrawLine(ADI_HANDLE hDstSurface, const ADIOSGLine_S * psDstLine);


ADI_Error_Code ADIOSGSync(void);

ADI_Error_Code ADIOSGDecodeImage(const char * pszImageType, const void * pvImageMem, int nMemSize,ADIOSGScalingMode_E eScalingMode,const ADIOSGRect_S * psDstRect,ADI_HANDLE * phSurface);

ADI_Error_Code ADIOSGDisableBootlogo(void);

//only for ali boot
ADI_Error_Code ADIOSGShowBootlogo(unsigned char *logoBuf, unsigned int logoLen);


#ifdef __cplusplus
}
#endif


#endif


