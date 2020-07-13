
#ifndef _ADI_OSG_H_
#define _ADI_OSG_H_


#include "adi_typedef.h"
#include "adi_error.h"

#ifdef __cplusplus
extern "C" {
#endif

/*返回错误代码枚举定义。*/
enum {
	ADIOSG_ERROR_BAD_PARAMETER = ADI_OSG_ERROR_BASE,
    ADIOSG_ERROR_FEATURE_NOT_SUPPORTED,
    ADIOSG_ERROR_UNKNOWN_ERROR,
    ADIOSG_ERROR_NO_MEMORY,
    ADIOSG_ERROR_DEVICE_BUSY
};

/*颜色模式枚举定义*/
typedef enum {
    EM_ADIOSG_PIXEL_FORMAT_RGB_565,      //  16-bit, no per-pixel alpha 
    EM_ADIOSG_PIXEL_FORMAT_ARGB_1555,    //  16-bit 
    EM_ADIOSG_PIXEL_FORMAT_RGBA_5551,    //  16-bit 
    EM_ADIOSG_PIXEL_FORMAT_ARGB_4444,    //  16-bit 
    EM_ADIOSG_PIXEL_FORMAT_RGBA_4444,    //  16-bit 

    EM_ADIOSG_PIXEL_FORMAT_RGB_888,      //  24-bit 
    EM_ADIOSG_PIXEL_FORMAT_ARGB_8888,    //  32-bit 
    EM_ADIOSG_PIXEL_FORMAT_PALETTE8,     //  8-bit Palette index，目前没有调色板的Surface，调色板的结构预留。

    EM_ADIOSG_PIXEL_FORMAT_YCBCR888_444, // Y, Cb, Cr signed components with 8 bit precision in a 4:4:4 sampling model
    EM_ADIOSG_PIXEL_FORMAT_YCBCR888_422, // Y, Cb, Cr signed components with 8 bit precision in a 4:2:2 sampling model
	EM_ADIOSG_PIXEL_FORMAT_YCBCR888_420, // Y, Cb, Cr signed components with 8 bit precision in a 4:2:0 sampling model
    EM_ADIOSG_PIXEL_FORMAT_YCBCR888_411, // Y, Cb, Cr signed components with 8 bit precision in a 4:1:1 sampling model
    EM_ADIOSG_PIXEL_FORMAT_NUM           // 像素格式的总数
} ADIOSGPixelFormat_E;


/*混合模式枚举定义 */
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


/*绘图平面结构定义。 */
typedef struct {
	ADIOSGPixelFormat_E m_ePixelFormat;     //  该绘图平面支持颜色模式 
	int m_nWidth;                           //  该绘图平面的宽度  > 0
	int m_nHeight;                          //  该绘图平面的高度 > 0

	int m_nPitch;                           //  该绘图平面每行字节数,width*BytesPerPixel 
	int m_nColorKeyFlag;                    //  该标志为 1 时表示m_uColorKey 起作用，初始化为 0
	int m_nAlphaFlag;                       //  该标志为 1 时表示该平面的全局m_uAlpha起作用，初始化为 0
    unsigned int m_uColorkey;               //  该绘图平面的colorKey ,AGRB888模式的像素值，指定该颜色对于该绘图平面不被显示 默认0x00000000
    unsigned int m_uAlpha;                  //  该绘图平面的透明度，[0x00,0xFF],0x00表示完全透明;0xFF表示不透明，默认为0xFF
    void * m_pvSurfaceMem;                  //  该绘图平面的内存地址 ,如果该Surface不能直接绘制（如特殊的显存Surface）,请赋ADI_NULL
    int m_nMemSize;                         //  该绘图平面的内存大小 
    void *m_pvPalette;                      //  m_ePixelFormat 为EM_ADIOSG_PIXEL_FORMAT_PALETTE8时指定的调色板数据区域，目前没有调色板的Surface,调色板的结构预留，故用void *
} ADIOSGSurfaceInfo_S;

/*矩形区域结构定义 */
typedef struct {
    int m_nX;                // 矩形区域左上角横坐标 
    int m_nY;                // 矩形区域左上角纵坐标 
	int m_nWidth;            // 矩形区域宽度 > 0
	int m_nHeight;           // 矩形区域高度 > 0
} ADIOSGRect_S;


/*矩形区域结构定义 */
typedef struct {
	unsigned int m_unPixel;  //color
    int m_nX1;               // start X address  
    int m_nY1;               // start Y address  
	int m_nX2;               // end X address
	int m_nY2;               // end Y address
	int m_nLinewidth;        // Line width
} ADIOSGLine_S;


/*图片缩放模式枚举定义 */
typedef enum {
    EM_ADIOSG_SCALE_FULLSIZE,   // 不缩放，按原始大小输出
    EM_ADIOSG_SCALE_OPTIMUM,   	// 最优匹配，此模式下图片保持原始比例，但尽量大的占满整个输入矩形区域
    EM_ADIOSG_SCALE_FIXSIZE     // 不按比例缩放，即输出宽高均为指定值，但输入比例与实际数据不一致，会产生变形
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


