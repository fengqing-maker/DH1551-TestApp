
#ifndef __SYS_MEM_MAP_H
#define __SYS_MEM_MAP_H

#ifdef _SUPPORT_64M_MEM
    #define SYS_SDRAM_SIZE 64
#elif defined _SUPPORT_128M_MEM
    #define SYS_SDRAM_SIZE 128
#else
    #define SYS_SDRAM_SIZE 256
#endif

#ifdef _CAS9_VSC_ENABLE_
#define __MM_VSC_CODE_LEN	0x20000
#define __MM_VSC_DATA_LEN 0x10000
#define __MM_VSC_TOTAL_LEN (__MM_VSC_CODE_LEN+__MM_VSC_DATA_LEN)
#endif
/*******Memory Mapping*******/
#if (SYS_SDRAM_SIZE == 64)
#define __MM_BUF_TOP_ADDR        0XA4000000
#define __MM_FB0_Y_LEN            0X65400
#define __MM_FB0_C_LEN            0X32C00
#define __MM_FB1_Y_LEN            0
#define __MM_FB1_C_LEN            0
#define __MM_FB2_Y_LEN            0
#define __MM_FB2_C_LEN            0

#define __MM_VCAP_FB_SIZE       (736*576*2*3)
#define __MM_FB_LEN                0x10CF200
#define __MM_MAF_LEN            0x198C00
#define __MM_DVW_LEN            0
#define __MM_OSD_LEN            0
#define __MM_VBV_LEN            0x12C000
#define __MM_DMX_SI_LEN            0
#define __MM_DMX_SI_TOTAL_LEN   0
#define __MM_SI_VBV_OFFSET        0
#define __MM_DMX_DATA_LEN        0
#define __MM_DMX_PCR_LEN        0
#define __MM_DMX_AUDIO_LEN        0
#define __MM_DMX_VIDEO_LEN        0
#define __MM_DMX_AVP_LEN        0
#define __MM_TTX_BS_LEN            0
#define __MM_TTX_PB_LEN            0
#define __MM_SUB_BS_LEN            0
#define __MM_SUB_PB_LEN            0

#define __MM_FB0_Y_START_ADDR    ((__MM_BUF_TOP_ADDR - __MM_FB0_Y_LEN)&0XFFFFFF00)
#define __MM_FB0_C_START_ADDR    ((__MM_FB0_Y_START_ADDR - __MM_FB0_C_LEN)&0XFFFFFF00)
#define __MM_FB1_Y_START_ADDR    ((__MM_FB0_C_START_ADDR - __MM_FB1_Y_LEN)&0XFFFFFF00)
#define __MM_FB1_C_START_ADDR    ((__MM_FB1_Y_START_ADDR - __MM_FB1_C_LEN)&0XFFFFFF00)
#define __MM_FB2_Y_START_ADDR    ((__MM_FB1_C_START_ADDR - __MM_FB2_Y_LEN)&0XFFFFFF00)
#define __MM_FB2_C_START_ADDR    ((__MM_FB2_Y_START_ADDR - __MM_FB2_C_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR        ((__MM_FB2_C_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define __MM_DVW_START_ADDR        ((__MM_MAF_START_ADDR - __MM_DVW_LEN)&0XFFFFFFF0)
#define __MM_OSD_START_ADDR        ((__MM_DVW_START_ADDR - __MM_OSD_LEN)&0XFFFFFFF0)
#define __MM_VBV_START_ADDR        ((__MM_OSD_START_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_DMX_AVP_START_ADDR    ((__MM_VBV_START_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)

#define __MM_TTX_BS_START_ADDR    ((__MM_DMX_AVP_START_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)
#define __MM_SUB_BS_START_ADDR    __MM_TTX_PB_START_ADDR
#define __MM_SUB_PB_START_ADDR    (__MM_SUB_BS_START_ADDR+__MM_SUB_BS_LEN)
#define __MM_FB_START_ADDR      ((__MM_SUB_PB_START_ADDR - __MM_FB_LEN)&0XFFFFFF00)
#define __MM_VCAP_FB_ADDR       ((__MM_FB_START_ADDR - __MM_VCAP_FB_SIZE)&0XFFFFFF00)
//#define __MM_HEAP_TOP_ADDR         __MM_VCAP_FB_ADDR

#elif(SYS_SDRAM_SIZE >= 128)

#define __MM_BUF_TOP_ADDR        0XA8000000
#define __MM_FB0_Y_LEN            0X65400
#define __MM_FB0_C_LEN            0X32C00
#define __MM_FB1_Y_LEN            0
#define __MM_FB1_C_LEN            0
#define __MM_FB2_Y_LEN            0
#define __MM_FB2_C_LEN            0

#define __MM_VCAP_FB_SIZE       (736*576*2*3)
#define __MM_FB_LEN                0xBF4000
#define __MM_MAF_LEN            0x147000
#define __MM_DVW_LEN            0
#define __MM_OSD_LEN            0
#define __MM_VBV_LEN            0x12C000
#define __MM_DMX_SI_LEN            0
#define __MM_DMX_SI_TOTAL_LEN   0
#define __MM_SI_VBV_OFFSET        0
#define __MM_DMX_DATA_LEN        0
#define __MM_DMX_PCR_LEN        0
#define __MM_DMX_AUDIO_LEN        0
#define __MM_DMX_VIDEO_LEN        0
#define __MM_DMX_AVP_LEN        0
#define __MM_TTX_BS_LEN            0
#define __MM_TTX_PB_LEN            0
#define __MM_SUB_BS_LEN            0
#define __MM_SUB_PB_LEN            0
#define __MM_SEE_RESV_LEN       0x800000  // Reserve 8M for Bootloader see running

#define __MM_FB0_Y_START_ADDR    ((__MM_BUF_TOP_ADDR - __MM_FB0_Y_LEN)&0XFFFFFF00)
#define __MM_FB0_C_START_ADDR    ((__MM_FB0_Y_START_ADDR - __MM_FB0_C_LEN)&0XFFFFFF00)
#define __MM_FB1_Y_START_ADDR    ((__MM_FB0_C_START_ADDR - __MM_FB1_Y_LEN)&0XFFFFFF00)
#define __MM_FB1_C_START_ADDR    ((__MM_FB1_Y_START_ADDR - __MM_FB1_C_LEN)&0XFFFFFF00)
#define __MM_FB2_Y_START_ADDR    ((__MM_FB1_C_START_ADDR - __MM_FB2_Y_LEN)&0XFFFFFF00)
#define __MM_FB2_C_START_ADDR    ((__MM_FB2_Y_START_ADDR - __MM_FB2_C_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR        ((__MM_FB2_C_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define __MM_DVW_START_ADDR        ((__MM_MAF_START_ADDR - __MM_DVW_LEN)&0XFFFFFFF0)
#define __MM_OSD_START_ADDR        ((__MM_DVW_START_ADDR - __MM_OSD_LEN)&0XFFFFFFF0)
#define __MM_VBV_START_ADDR        ((__MM_OSD_START_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_DMX_AVP_START_ADDR    ((__MM_VBV_START_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)

#define __MM_TTX_BS_START_ADDR    ((__MM_DMX_AVP_START_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)
#define __MM_SUB_BS_START_ADDR    __MM_TTX_PB_START_ADDR
#define __MM_SUB_PB_START_ADDR    (__MM_SUB_BS_START_ADDR+__MM_SUB_BS_LEN)
#define __MM_FB_START_ADDR      ((__MM_SUB_PB_START_ADDR - __MM_SEE_RESV_LEN - __MM_FB_LEN)&0XFFFFFF00)
#define __MM_VCAP_FB_ADDR       ((__MM_FB_START_ADDR - __MM_VCAP_FB_SIZE)&0XFFFFFF00)
//#define __MM_HEAP_TOP_ADDR         __MM_VCAP_FB_ADDR
#endif

#define __MM_VOID_BUFFER_LEN    0x00200000    //2M
#define __MM_PRIVATE_SHARE_LEN  0x02000000
#define __MM_SHARED_MEM_LEN      256

#define __MM_PRIVATE_LEN    (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)
#define __MM_SHARE_BASE_ADDR (__MM_BUF_TOP_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR        (__MM_PRIVATE_TOP_ADDR - __MM_PRIVATE_LEN)
#define __MM_HEAP_TOP_ADDR        __MM_PRIVATE_ADDR    //
#ifdef _CAS9_VSC_ENABLE_
	#define SEE_ENTRY (__MM_PRIVATE_ADDR + __MM_VSC_TOTAL_LEN + 0x200)
#else
#define SEE_ENTRY (__MM_PRIVATE_ADDR + 0x200)
#endif

#define BOOTLOADER_TEMP_ADDR    0xA0500000

#endif


