
#ifndef __SYS_MEM_MAP_H
#define __SYS_MEM_MAP_H

#if ( SYS_SDRAM_SIZE == 2 )

#elif ( SYS_SDRAM_SIZE == 4 )

#elif (SYS_SDRAM_SIZE == 16)

#elif (SYS_SDRAM_SIZE == 32)

#elif (SYS_SDRAM_SIZE == 64)

#define SYS_DEM_MODULE          COFDM_S3811
#define SYS_TUN_MODULE          ANY_TUNER //MXL136 MXL5007 IX2410 NM120 RT820T

#undef AUDIO_DESCRIPTION_SUPPORT
//#undef ATSC_SUBTITLE_SUPPORT

#ifdef MP_PREVIEW_SWITCH_SMOOTHLY
#undef MP_PREVIEW_SWITCH_SMOOTHLY
#endif

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#undef DYNAMIC_RESOLUTION_SUPPORT
#endif

#define AVC_MEM_LEN		0x15bb000//0x1898400

#define __MM_VOID_BUFFER_LEN    0x00000000
#define __MM_FB_LEN_DEVIDED        0X32A000//(HD:1920X1152X1.5)
#ifdef VIDEO_DEBLOCKING_SUPPORT
#define __MM_FB_LEN                0x10CF200//0x19c6200
#else
#define __MM_FB_LEN                0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
#endif
#define __MM_MAF_LEN            0x198C00//0xd0000//0X3000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#define __MM_DVW_LEN            0
#define __MM_VBV_LEN            0x12C000//(HD = 8*SD > 4*SD)

//#define SD_PVR //to support 64M with SD pvr

#define __MM_HIGHEST_ADDR          0xa4000000        //64
#define __MM_VOID_BUFFER_ADDR    (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)
#define __MM_FB_TOP_ADDR        __MM_VOID_BUFFER_ADDR    //64MB
#define __MM_VBV_START_ADDR        ((__MM_FB_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define __MM_FB_START_ADDR            ((__MM_MAF_START_ADDR - __MM_FB_LEN)&0XFFFFFF00)


//#define __MM_VBV_START_ADDR            ((__MM_GE_START_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
//#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)

// for satcodx memmap
#define __MM_DVW_START_ADDR            ((__MM_FB_START_ADDR)&0XFFFFFFF0)

// end: mpeg2 decoder

// begin: h264 decoder
#define MAX_EXTRA_FB_NUM 3
#ifndef SYSCFG_SD_VIDEO
    #define MAX_MB_WIDTH 120 //(1920/16)
    #define MAX_MB_HEIGHT 68 //(1088/16)
#else
    #define MAX_MB_WIDTH 46//45 //(720/16)
    #define MAX_MB_HEIGHT 36//36 //(576/16)
#endif

#ifdef H264_SUPPORT_MULTI_BANK
    #ifndef SYSCFG_SD_VIDEO
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
    #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
    #endif
#define EXTRA_FB_SIZE 0x2000
#define ONE_FB_SIZE (((MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2+EXTRA_FB_SIZE-1)&0xffffe000)+EXTRA_FB_SIZE)
#else
    #ifndef SYSCFG_SD_VIDEO
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
    #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
    #endif

    #ifdef SYSCFG_SD_VIDEO
        #define one_frm_y_size         (MAX_MB_STRIDE*((MAX_MB_HEIGHT+1)/2)*512)
        #define one_frm_c_size   (MAX_MB_STRIDE*((((MAX_MB_HEIGHT+1)/2)+1)/2)*512)
        #define ONE_FB_SIZE (one_frm_y_size + one_frm_c_size)
    #else
        #define ONE_FB_SIZE (MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2)
    #endif

#endif

#define ONE_DV_FB_SIZE ((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifndef SYSCFG_SD_VIDEO
#define AVC_FB_LEN        ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN        ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#else
#define const_frm_num   5
#define AVC_FB_LEN        ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN        ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#endif

#define AVC_MB_COL_LEN        0x22000 //0x11000
#define AVC_MB_NEI_LEN        0x20000
#define AVC_CMD_QUEUE_LEN   0x10000 //In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
#undef  AVC_LAF_RW_BUF_LEN
//#define AVC_LAF_RW_BUF_LEN ((MAX_MB_WIDTH*MAX_MB_HEIGHT)*32*2*2)
#define AVC_LAF_RW_BUF_LEN (((((MAX_MB_WIDTH*MAX_MB_HEIGHT)*48*2)+1023)&0x0ffffc00)*2)

//#define AVC_LAF_FLAG_BUF_LEN (0xc00*21)
#define AVC_LAF_FLAG_BUF_LEN (0xc00*22) //when enable dual output, we need 1 more laf buffer

#ifdef AVC_VBV_LEN
#undef AVC_VBV_LEN
#endif

#ifndef SYSCFG_SD_VIDEO
    #define AVC_VBV_LEN        0x300000 //for CI+, must use 4MB. if this size is set to 0x200000, vbv buffer overflow could happen in 20061007d_0.ts
#else
    #define AVC_VBV_LEN        0x180000
#endif

// end: h264 decoder

#define AVC_SUPPORT_UNIFY_MEM

#ifndef AVC_SUPPORT_UNIFY_MEM
/*AVC buffer allocation*/
#define AVC_VBV_ADDR         (__MM_FB_TOP_ADDR - AVC_VBV_LEN)     //256 bytes alignment
#define AVC_FB_ADDR         ((AVC_VBV_ADDR -  AVC_FB_LEN )&0xfffffe00)           //512 bytes alignment
#define AVC_DVIEW_ADDR         ((AVC_FB_ADDR -  AVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define AVC_CMD_QUEUE_ADDR          ((AVC_DVIEW_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
#define AVC_MV_ADDR         ((AVC_CMD_QUEUE_ADDR - AVC_MV_LEN)&0xffffff00)          //256 bytes alignment
#define AVC_MB_COL_ADDR     ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR     ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_LAF_FLAG_BUF_ADDR         ((AVC_MB_NEI_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define AVC_LAF_RW_BUF_ADDR   ((AVC_LAF_FLAG_BUF_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#else

#define AVC_VBV_ADDR                 ((__MM_FB_TOP_ADDR - AVC_VBV_LEN )&0xffffff00)     //256 bytes alignment
#define AVC_CMD_QUEUE_ADDR          ((AVC_VBV_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
#define AVC_MB_COL_ADDR             ((AVC_CMD_QUEUE_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR             ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_MEM_ADDR                 ((AVC_MB_NEI_ADDR - AVC_MEM_LEN)&0xffffff00)

#define AVC_DVIEW_ADDR                 0
#define AVC_MV_ADDR                 0
#define AVC_LAF_RW_BUF_ADDR           0
#define AVC_LAF_FLAG_BUF_ADDR         0
#define AVC_FB_ADDR                    0
#endif


#if 1 //ifdef FPGA_TEST
#define __MM_GMA1_LEN            0 // 0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN            0 // 0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN        0 // 0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0 // 0x6DB0 // command buffer
#else
#define __MM_GMA1_LEN            0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN            0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN        0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0x6DB0 // command buffer
#endif
#define __MM_GE_LEN                (__MM_GMA1_LEN+__MM_GMA2_LEN+__MM_TEMP_BUF_LEN+__MM_CMD_LEN) //0xBE45B0
#define __MM_OSD_LEN            0x65400 // 720*576
#define __MM_OSD1_LEN           (1280*720*4) //(1280*720*2 + 256)//(1008 * 640 * 2  + 256)//(1280*720*2 + 256)
#ifdef HD_SUBTITLE_SUPPORT
#define __MM_OSD2_LEN            (720 * 576)//(1920*1080)
#else
#define __MM_OSD2_LEN            (720 * 576)
#endif

#define OSD_VSRC_MEM_MAX_SIZE     0x200000    //note.the size is not meaning,vscr is not exist,only for code compatibility. the vscr is the same as display size.


#define __MM_DMX_SI_LEN            (32*188)//(16*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define EXTRA_VIDEO_NUM 3
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*(92-EXTRA_VIDEO_NUM)) //by Xu.Liu
#else
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*92)    //by Xu.Liu
#endif

#define __MM_SI_VBV_OFFSET        __MM_DMX_SI_TOTAL_LEN
#define __MM_DMX_DATA_LEN        (30*188)
#define __MM_DMX_PCR_LEN        (10*188)
#define __MM_DMX_AUDIO_LEN        (256*188)//(32*188)
#define __MM_DMX_VIDEO_LEN        (12*512*188)//(8*512*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define __MM_DMX_EXTRA_VIDEO_LEN (960*188)
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_EXTRA_VIDEO_LEN*EXTRA_VIDEO_NUM+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#else
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#endif
#define __MM_DMX_BLK_BUF_LEN    0xbc000

#define __MM_SUB_BS_LEN            0xA000 //0X2800

#ifdef HD_SUBTITLE_SUPPORT
    #define __MM_SUB_PB_LEN            0xA0000//0x50000//0X19000
#else
    #define __MM_SUB_PB_LEN            0X19000
#endif

#ifdef SUPPORT_HW_SUBT_DECODE
#define __MM_SUB_HW_DATA_LEN 0xC000
#else
#define __MM_SUB_HW_DATA_LEN 0
#endif

// TTX
#define __MM_TTX_BS_LEN            0x5000//0X2800
#ifdef TTX_SUB_PAGE
#define __MM_TTX_PB_LEN                0xCB200 //+80*1040 //0XCA800
#define __MM_TTX_SUB_PAGE_LEN       0x14500 //80*1040
#else
#define __MM_TTX_PB_LEN                0xCA800 //+80*1040 //
#define __MM_TTX_SUB_PAGE_LEN       0 //80*1040
#endif
#ifdef SUPPORT_PACKET_26
#define __MM_TTX_P26_NATION_LEN     0x61A80 //25*40*400
#define __MM_TTX_P26_DATA_LEN       0x3E8 //25*40
#else
#define __MM_TTX_P26_NATION_LEN     0
#define __MM_TTX_P26_DATA_LEN       0
#endif

//modify for TTX and EPG share buffer 2011 10 10
#ifdef TTX_EPG_SHARE_MEM
#define __MM_EPG_BUFFER_LEN     (__MM_TTX_BS_LEN+__MM_TTX_PB_LEN+__MM_TTX_SUB_PAGE_LEN+__MM_TTX_P26_NATION_LEN+__MM_TTX_P26_DATA_LEN)
#else
#define __MM_EPG_BUFFER_LEN     0x100000//0x96000 // (at least 585K, please reference lib_epg.c)
//#define SCHEDULE_TABLE_ID_NUM     2 /*(0x50, 0x51 or 0x60, 0x61)*/
#endif
//#define __MM_EPG_BUFFER_LEN             0x100000
//modify end

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#define __MM_VCAP_FB_SIZE               (736*576*2*3)
#else
#define __MM_VCAP_FB_SIZE               0
#endif

#ifdef DVR_PVR_SUPPORT
#ifdef _MHEG5_V20_ENABLE_ //MHEG5 enable, reserve 8MB
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(180*3)+0x1000 -__MM_VCAP_FB_SIZE)//// modify for MP and EPG share buffer 10 12
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE        0X800000
#else
    //#define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(240*3)+0x1000)
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(80*2)+0x1000 + 0x200000 - __MM_VCAP_FB_SIZE)// modify for MP and EPG share buffer 10 12
    //#define __MM_PVR_VOB_BUFFER_LEN        (0x1000)
#endif
#else
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(80+75 * 2)+0x1000)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE 0
#endif
    #define __MM_DMX_REC_LEN            (__MM_DMX_VIDEO_LEN)

#define __MM_USB_DMA_LEN                0    // 0x10FFFF currently not use
//#define __MM_EPG_BUFFER_LEN             0x100000
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0x100000

#ifdef NETWORK_SUPPORT
#define STO_PROTECT_BY_MUTEX
#define __MM_LWIP_MEM_LEN               0x10000
#define __MM_LWIP_MEMP_LEN              0xce200
#define __MM_XML_MEMP_LEN                0x100000 // 5M
#else
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN                0
#endif

#define __MM_DBG_MEM_LEN   0 // 0x4000

#ifdef AVC_SUPPORT_UNIFY_MEM
    #if (__MM_FB_START_ADDR < AVC_MEM_ADDR)
    #define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR

    #undef  AVC_MEM_ADDR
    #undef  AVC_MEM_LEN
    #define AVC_MEM_ADDR                __MM_FB_BOTTOM_ADDR
    #define AVC_MEM_LEN                 ((AVC_MB_NEI_ADDR - AVC_MEM_ADDR)&0xffffff00)

    #else
    #define __MM_FB_BOTTOM_ADDR         AVC_MEM_ADDR
    #endif
#else
    #if (__MM_FB_START_ADDR < AVC_LAF_RW_BUF_ADDR)
    #define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR
    #else
    #define __MM_FB_BOTTOM_ADDR         AVC_LAF_RW_BUF_ADDR
    #endif
#endif

// begin: buffer could be shared by media player
#define __MM_BUF_PVR_TOP_ADDR       __MM_FB_BOTTOM_ADDR
#define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)

#ifdef _MHEG5_V20_ENABLE_
#define __MM_MHEG5_BUFFER_ADDR      (__MM_PVR_VOB_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
#define __MM_DMX_AVP_START_ADDR        ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
#else
#define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
#endif

#define __MM_DMX_REC_START_ADDR        (__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)
#define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_DMX_SEE_BLK_ADDR        ((__MM_DMX_CPU_BLK_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - __MM_TTX_SUB_PAGE_LEN)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
#define __MM_TTX_BS_START_ADDR    ((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)
// modify for TTX and EPG share buffer 2011 10 10
#ifdef TTX_EPG_SHARE_MEM
#define __MM_EPG_BUFFER_START       (__MM_TTX_PB_START_ADDR)//(__MM_TTX_P26_DATA_BUF_ADDR)
#else
//#define __MM_EPG_BUFFER_START       (__MM_TTX_P26_DATA_BUF_ADDR - __MM_EPG_BUFFER_LEN)
#define __MM_EPG_BUFFER_START       (__MM_TTX_PB_START_ADDR-__MM_EPG_BUFFER_LEN)
#endif
//modify end

// end: buffer could be shared by media player

#define __MM_GE_START_ADDR            ((__MM_EPG_BUFFER_START - __MM_GE_LEN)&0XFFFFFFE0)//modify memerymap 10 12
#define __MM_OSD_BK_ADDR2       ((__MM_EPG_BUFFER_START - __MM_OSD2_LEN)&0XFFFFFFF0)
#define __MM_OSD_BK_ADDR1              ((__MM_OSD_BK_ADDR2 - __MM_OSD1_LEN)&0XFFFFFFF0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#ifdef OSD_VSRC_SUPPORT
#define __MM_OSD_VSRC_MEM_ADDR        ((__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFF0)
#define __MM_SUB_BS_START_ADDR    ((__MM_OSD_VSRC_MEM_ADDR  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#else
#define __MM_SUB_BS_START_ADDR    ((__MM_VCAP_FB_ADDR  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#endif
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - __MM_SUB_HW_DATA_LEN)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR    ((__MM_SUB_HW_DATA_ADDR - __MM_SUB_PB_LEN)&0XFFFFFFFC)


#define __MM_LWIP_MEM_ADDR          (__MM_SUB_PB_START_ADDR - __MM_LWIP_MEM_LEN)
#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR            ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)
#ifdef ATSC_SUBTITLE_SUPPORT
#define __MM_DCII_SUB_BS_START_ADDR (__MM_USB_START_ADDR - __MM_DCII_SUB_BS_LEN)
#define __MM_SUBT_ATSC_SEC_ADDR (__MM_DCII_SUB_BS_START_ADDR - __MM_SUBT_ATSC_SEC_LEN)
#define __MM_CPU_DBG_MEM_ADDR          (__MM_SUBT_ATSC_SEC_ADDR - __MM_DBG_MEM_LEN)
#else
#define __MM_CPU_DBG_MEM_ADDR          (__MM_USB_START_ADDR - __MM_DBG_MEM_LEN)
#endif
#define __MM_DBG_MEM_ADDR           __MM_CPU_DBG_MEM_ADDR

#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR

//end of main mem map



// for jpeg decoder memmap
#define __MM_FB0_Y_LEN            (1920*1088+1024)//(736*576+512)    //for high definition jpg decode
#define __MM_FB1_Y_LEN            __MM_FB0_Y_LEN
#define __MM_FB2_Y_LEN            __MM_FB0_Y_LEN

#define __MM_FB0_C_LEN            (__MM_FB0_Y_LEN/2)
#define __MM_FB1_C_LEN            __MM_FB0_C_LEN
#define __MM_FB2_C_LEN            __MM_FB0_C_LEN

#define __MM_FB3_Y_LEN            (736*576+1024)
#define __MM_FB3_C_LEN            (__MM_FB3_Y_LEN/2)
#define __MM_FB4_Y_LEN            __MM_FB3_Y_LEN
#define __MM_FB4_C_LEN            __MM_FB3_C_LEN
#define __MM_FB5_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB5_C_LEN          __MM_FB3_C_LEN
#define __MM_FB6_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB6_C_LEN          __MM_FB3_C_LEN

#define __MM_FB0_Y_START_ADDR   (__MM_FB_START_ADDR)
#define __MM_FB0_C_START_ADDR   (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

#define __MM_FB1_Y_START_ADDR   ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
#define __MM_FB1_C_START_ADDR   ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

#define __MM_FB2_Y_START_ADDR   ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
#define __MM_FB2_C_START_ADDR   ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

#define __MM_FB3_Y_START_ADDR   ((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
#define __MM_FB3_C_START_ADDR   ((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
#define __MM_FB4_Y_START_ADDR    ((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
#define __MM_FB4_C_START_ADDR   ((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
#define __MM_FB5_Y_START_ADDR    ((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
#define __MM_FB5_C_START_ADDR   ((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
#define __MM_FB6_Y_START_ADDR    ((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
#define __MM_FB6_C_START_ADDR   ((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)

#ifdef DVR_PVR_SUPPORT
//64M memory need share subtitle/epg buffer
//#define __MM_MP_BUFFER_LEN            __MM_PVR_VOB_BUFFER_LEN
//#define __MM_MP_BUFFER_ADDR            __MM_PVR_VOB_BUFFER_ADDR
#define __MM_MP_BUFFER_ADDR             ((__MM_EPG_BUFFER_START + 0x1FF)&0XFFFFFE00)
#define __MM_MP_BUFFER_LEN              (__MM_FB_BOTTOM_ADDR - __MM_MP_BUFFER_ADDR)
#else
#define __MM_MP_BUFFER_LEN            0x1000000
#define __MM_MP_BUFFER_ADDR            ((__MM_FB2_C_START_ADDR - __MM_MP_BUFFER_LEN)&0XFFFFFFF0)
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR


#elif (SYS_SDRAM_SIZE == 128)
#ifndef DRAM_SPLIT
//#define __MM_FB_LEN_DEVIDED        0X32A000//(HD:1920X1152X1.5)
//#define __MM_DVW_LEN            0
//#define __MM_VBV_START_ADDR            ((__MM_GE_START_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
//#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)

//#define AVC_SUPPORT_UNIFY_MEM
#ifdef SD_PVR
#ifdef AVC_SUPPORT_UNIFY_MEM
#undef AVC_SUPPORT_UNIFY_MEM
#endif
#endif

#ifdef AVC_SUPPORT_UNIFY_MEM
#ifdef MP_PREVIEW_SWITCH_SMOOTHLY
#undef MP_PREVIEW_SWITCH_SMOOTHLY
#endif

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#undef DYNAMIC_RESOLUTION_SUPPORT
#endif

#define AVC_MEM_LEN		0x15bb000//0x1898400
#endif

#define __MM_VOID_BUFFER_LEN    0x00000000
#define __MM_VBV_LEN            0x500000//(HD = 8*SD > 4*SD)
#define __MM_MAF_LEN            0x198C00//0xd0000//0X3000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#ifdef VIDEO_DEBLOCKING_SUPPORT
#define __MM_FB_LEN                0x10CF200//0x19c6200
#else
#define __MM_FB_LEN                0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
#endif
/********************************************
* SD PVR
*********************************************/
//#define SD_PVR //to support 64M with SD pvr
#define MAX_EXTRA_FB_NUM 3
#ifndef SD_PVR
    #define MAX_MB_WIDTH 120 //(1920/16)
    #define MAX_MB_HEIGHT 68 //(1088/16)
#else
    #define MAX_MB_WIDTH 46//45 //(720/16)
    #define MAX_MB_HEIGHT 36//36 //(576/16)
#endif

#ifdef H264_SUPPORT_MULTI_BANK
        #ifndef SD_PVR
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
        #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
        #endif
    #define EXTRA_FB_SIZE 0x2000
    #define ONE_FB_SIZE (((MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2+EXTRA_FB_SIZE-1)&0xffffe000)+EXTRA_FB_SIZE)
#else
        #ifndef SD_PVR
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
        #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
        #endif

        #ifdef SD_PVR
        #define one_frm_y_size         (MAX_MB_STRIDE*((MAX_MB_HEIGHT+1)/2)*512)
        #define one_frm_c_size   (MAX_MB_STRIDE*((((MAX_MB_HEIGHT+1)/2)+1)/2)*512)
        #define ONE_FB_SIZE (one_frm_y_size + one_frm_c_size)
        #else
        #define ONE_FB_SIZE (MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2)
        #endif
#endif

#define ONE_DV_FB_SIZE ((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#ifndef SD_PVR
#define AVC_FB_LEN		ONE_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0x1700000
#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN    0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0xb00000
#endif
#define AVC_MV_LEN		ONE_MV_SIZE*(5+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#else
#define const_frm_num   5
#define AVC_FB_LEN		ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN		ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#endif

#define AVC_MB_COL_LEN		0x18000 //0x11000
#else
#ifndef SD_PVR
#define AVC_FB_LEN		ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000
#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN    0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#endif
#define AVC_MV_LEN        ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN        0x15000 //0x11000
#else
#define const_frm_num   5
#define AVC_FB_LEN        ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN        ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN        0x18000 //0x11000
#endif
#endif

#define AVC_MB_NEI_LEN        0x20000
#define AVC_CMD_QUEUE_LEN   0x10000 //In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
#undef  AVC_LAF_RW_BUF_LEN
//#define AVC_LAF_RW_BUF_LEN ((MAX_MB_WIDTH*MAX_MB_HEIGHT)*32*2*2)
#define AVC_LAF_RW_BUF_LEN (((((MAX_MB_WIDTH*MAX_MB_HEIGHT)*48*2)+1023)&0x0ffffc00)*2)

//#define AVC_LAF_FLAG_BUF_LEN (0xc00*21)
#define AVC_LAF_FLAG_BUF_LEN (0xc00*22) //when enable dual output, we need 1 more laf buffer

#ifdef AVC_VBV_LEN
#undef AVC_VBV_LEN
#endif

#ifndef SD_PVR
    #define AVC_VBV_LEN        0x400000 //for CI+, must use 4MB. if this size is set to 0x200000, vbv buffer overflow could happen in 20061007d_0.ts
#else
    #define AVC_VBV_LEN        0x180000
#endif

/*************************************************
* OSD lib
**************************************************/
#if 1 //ifdef FPGA_TEST
#define __MM_GMA1_LEN            0 // 0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN            0 // 0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN        0 // 0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0 // 0x6DB0 // command buffer
#else
#define __MM_GMA1_LEN            0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN            0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN        0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0x6DB0 // command buffer
#endif
#define __MM_GE_LEN                (__MM_GMA1_LEN+__MM_GMA2_LEN+__MM_TEMP_BUF_LEN+__MM_CMD_LEN) //0xBE45B0
#define __MM_OSD_LEN            0x65400 // 720*576
#define __MM_OSD1_LEN           (1280*720*2 + 256) //(1280*720*4)
#define __MM_OSD2_LEN            (720 * 576 )//(1920*1080)

#define OSD_VSRC_MEM_MAX_SIZE     0x400000    //note.the size is not meaning,vscr is not exist,only for code compatibility. the vscr is the same as display size.

/*************************************************
* DMX, Subtitle, TTX
**************************************************/
#define __MM_DMX_SI_LEN            (32*188)//(16*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define EXTRA_VIDEO_NUM 3
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*(92-EXTRA_VIDEO_NUM))
#else
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*92)
#endif

#define __MM_SI_VBV_OFFSET        __MM_DMX_SI_TOTAL_LEN
#define __MM_DMX_DATA_LEN        (30*188)
#define __MM_DMX_PCR_LEN        (10*188)
#define __MM_DMX_AUDIO_LEN        (256*188)//(32*188)
#define __MM_DMX_VIDEO_LEN        (12*512*188)//(8*512*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define __MM_DMX_EXTRA_VIDEO_LEN (960*188)
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_EXTRA_VIDEO_LEN*EXTRA_VIDEO_NUM+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#else
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#endif
#define __MM_DMX_BLK_BUF_LEN    0xbc000

#define __MM_SUB_BS_LEN            0xA000 //0X2800

#ifdef HD_SUBTITLE_SUPPORT
    #define __MM_SUB_PB_LEN            0xA0000//0x50000//0X19000
#else
    #define __MM_SUB_PB_LEN            0X19000
#endif

#ifdef SUPPORT_HW_SUBT_DECODE
#define __MM_SUB_HW_DATA_LEN 0xC000
#else
#define __MM_SUB_HW_DATA_LEN 0
#endif

#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_LEN        0x8FC0
#define __MM_ISDBTCC_PB_LEN        0x7E900
#endif

#if (CC_ON==1)
#define OSD_CC_WIDTH   	  576//480//480//704//480//(CC_CHAR_W*40+16)//560//704(16bytes aligned)
#define OSD_CC_HEIGHT  	  390//360//300//360//300//450//(CC_CHAR_H*15)//500//570
#define CC_CHAR_HEIGHT		26

#define __MM_ATSC_CC_PB_RECT_LEN (OSD_CC_WIDTH*OSD_CC_HEIGHT)
#define __MM_ATSC_CC_PB_LEN  (__MM_ATSC_CC_PB_RECT_LEN+OSD_CC_WIDTH*4*CC_CHAR_HEIGHT)
#define __MM_ATSC_CC_BS_LEN  0x1c00 // 1K Word CC Data, 1K Byte CC Field, 2K Word DTVCC Data
//#define __MM_SUBT_ATSC_SEC_LEN	0x400	// 1KB  

#else
#undef __MM_ATSC_CC_PB_LEN
#undef __MM_ATSC_CC_BS_LEN
#define __MM_ATSC_CC_PB_LEN	0
#define __MM_ATSC_CC_BS_LEN	0
#endif

// TTX
#define __MM_TTX_BS_LEN            0x5000//0X2800
#ifdef TTX_SUB_PAGE
#define __MM_TTX_PB_LEN                0xCB200 //+80*1040 //0XCA800
#define __MM_TTX_SUB_PAGE_LEN       0x14500 //80*1040
#else
#define __MM_TTX_PB_LEN                0xCA800 //+80*1040 //
#define __MM_TTX_SUB_PAGE_LEN       0 //80*1040
#endif
#ifdef SUPPORT_PACKET_26
#define __MM_TTX_P26_NATION_LEN     0x61A80 //25*40*400
#define __MM_TTX_P26_DATA_LEN       0x3E8 //25*40
#else
#define __MM_TTX_P26_NATION_LEN     0
#define __MM_TTX_P26_DATA_LEN       0
#endif

/*************************************************
* Demod, Tuner
**************************************************/
//#define SYS_DEM_MODULE          COFDM_S3811
//#define SYS_TUN_MODULE          ANY_TUNER //MXL136 MXL5007 IX2410 NM120 RT820T
#ifdef ISDBT_SUPPORT
    #if (SYS_DEM_MODULE == COFDM_S3811)
        #define __MM_COFDM_S3811_ISDBT_BUF_LEN  0x741600 // ((7607808+0xF)&0xFFFFFFF0)) //for S3811 ISDBT mode only. (4560*16/2 + 96)*13 -> 7607808 Bytes.
    #else
        #define __MM_COFDM_S3811_ISDBT_BUF_LEN  0
    #endif
#else
    #define __MM_COFDM_S3811_ISDBT_BUF_LEN  0
#endif

/*************************************************
* DVR PVR
**************************************************/
#ifdef DVR_PVR_SUPPORT
  #ifdef _MHEG5_V20_ENABLE_ //MHEG5 enable, reserve 8MB
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(180*3)+0x1000)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE        0X800000
  #else
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(240*3)+0x1000 - __MM_COFDM_S3811_ISDBT_BUF_LEN)
    //#define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(90*2)+0x1000)
  #endif
#else
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(80+75 * 2)+0x1000)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE 0
#endif
    #define __MM_DMX_REC_LEN            (__MM_DMX_VIDEO_LEN)

#define __MM_USB_DMA_LEN                0    // 0x10FFFF currently not use
#define __MM_EPG_BUFFER_LEN             0x100000

/************************************************
* Autoscan
*************************************************/
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0x100000

/*************************************************
* Network
**************************************************/
#ifdef NETWORK_SUPPORT
#define STO_PROTECT_BY_MUTEX
#define __MM_LWIP_MEM_LEN               0x10000
#define __MM_LWIP_MEMP_LEN              0xce200
#define __MM_XML_MEMP_LEN                0x100000 // 5M
#else
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN                0
#endif

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#define __MM_VCAP_FB_SIZE               (736*576*2*5)
#else
#define __MM_VCAP_FB_SIZE               0
#endif

/*************************************************
* Debug
**************************************************/
#define __MM_DBG_MEM_LEN   0x4000

/*^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
^ Memory space addr define
^
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^*/

/*************************************************
* Define Top
**************************************************/
#define __MM_HIGHEST_ADDR              0xa8000000        //128
#define __MM_VOID_BUFFER_ADDR        (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)
#define __MM_FB_TOP_ADDR            __MM_VOID_BUFFER_ADDR    //64MB

/*************************************************
* VDEC Addr
**************************************************/
#define __MM_VBV_START_ADDR        ((__MM_FB_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR        ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define __MM_FB_START_ADDR            ((__MM_MAF_START_ADDR - __MM_FB_LEN)&0XFFFFFF00)
// for satcodx memmap
#define __MM_DVW_START_ADDR            ((__MM_FB_START_ADDR)&0XFFFFFFF0)

/**************************************************
* AVC Addr
**************************************************/
//#define AVC_SUPPORT_UNIFY_MEM
#ifndef AVC_SUPPORT_UNIFY_MEM
/*AVC buffer allocation*/
#define AVC_VBV_ADDR         (__MM_FB_TOP_ADDR - AVC_VBV_LEN)     //256 bytes alignment
#define AVC_FB_ADDR         ((AVC_VBV_ADDR -  AVC_FB_LEN )&0xfffffe00)           //512 bytes alignment
#define AVC_DVIEW_ADDR         ((AVC_FB_ADDR -  AVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define AVC_CMD_QUEUE_ADDR          ((AVC_DVIEW_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
#define AVC_MV_ADDR         ((AVC_CMD_QUEUE_ADDR - AVC_MV_LEN)&0xffffff00)          //256 bytes alignment
#define AVC_MB_COL_ADDR     ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR     ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_LAF_FLAG_BUF_ADDR         ((AVC_MB_NEI_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define AVC_LAF_RW_BUF_ADDR   ((AVC_LAF_FLAG_BUF_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#else

#define AVC_VBV_ADDR                 ((__MM_FB_TOP_ADDR - AVC_VBV_LEN )&0xffffff00)     //256 bytes alignment
#define AVC_CMD_QUEUE_ADDR          ((AVC_VBV_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
#define AVC_MB_COL_ADDR             ((AVC_CMD_QUEUE_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR             ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_MEM_ADDR                 ((AVC_MB_NEI_ADDR - AVC_MEM_LEN)&0xffffff00)

#define AVC_DVIEW_ADDR                 0
#define AVC_MV_ADDR                 0
#define AVC_LAF_RW_BUF_ADDR           0
#define AVC_LAF_FLAG_BUF_ADDR         0
#define AVC_FB_ADDR                    0
#endif

/***************************************************
* Align to lower
****************************************************/
#ifdef AVC_SUPPORT_UNIFY_MEM
    #if (__MM_FB_START_ADDR < AVC_MEM_ADDR)
    #define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR

    #undef  AVC_MEM_ADDR
    #undef  AVC_MEM_LEN
    #define AVC_MEM_ADDR                __MM_FB_BOTTOM_ADDR
    #define AVC_MEM_LEN                 ((AVC_MB_NEI_ADDR - AVC_MEM_ADDR)&0xffffff00)

    #else
    #define __MM_FB_BOTTOM_ADDR         AVC_MEM_ADDR
    #endif
#else
    #if (__MM_FB_START_ADDR < AVC_LAF_RW_BUF_ADDR)
    #define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR
    #else
    #define __MM_FB_BOTTOM_ADDR         AVC_LAF_RW_BUF_ADDR
    #endif
#endif

/***************************************************
* PVR addr
* error: Lenth < Autoscan Length
****************************************************/
// begin: buffer could shared by media player
#define __MM_BUF_PVR_TOP_ADDR       __MM_FB_BOTTOM_ADDR
#define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)

/***************************************************
* Autoscan (Share to PVR)
* error: Lenth > PVR-length
****************************************************/
#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR

/***************************************************
* DMX addr
****************************************************/
#define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)

#define __MM_DMX_REC_START_ADDR        (__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)

#define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_DMX_SEE_BLK_ADDR        ((__MM_DMX_CPU_BLK_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
//#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - __MM_TTX_SUB_PAGE_LEN)
//#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
//#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
//#define __MM_TTX_BS_START_ADDR    ((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
//#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)

//#define __MM_ATSC_CC_PB_START_ADDR  ((__MM_TTX_PB_START_ADDR - __MM_ATSC_CC_PB_LEN)&0XFFFFFFFC)
//#define __MM_ATSC_CC_BS_START_ADDR  ((__MM_ATSC_CC_PB_START_ADDR - __MM_ATSC_CC_BS_LEN)&0XFFFFFFFC)

#define __MM_EPG_BUFFER_START       (__MM_DMX_SEE_BLK_ADDR -__MM_EPG_BUFFER_LEN)
// end: buffer could shared by media player

/***********************************************************
* GE,  SUBTITLE
***********************************************************/
#define __MM_GE_START_ADDR            ((__MM_EPG_BUFFER_START - __MM_GE_LEN)&0XFFFFFFE0)
#define __MM_OSD_BK_ADDR2       ((__MM_GE_START_ADDR - __MM_OSD2_LEN)&0XFFFFFFF0)
#define __MM_OSD_BK_ADDR1              ((__MM_OSD_BK_ADDR2 - __MM_OSD1_LEN)&0XFFFFFFF0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#define __MM_OSD_VSRC_MEM_ADDR        ((__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFF0)

#define __MM_SUB_BS_START_ADDR    ((__MM_OSD_VSRC_MEM_ADDR  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - __MM_SUB_HW_DATA_LEN)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR    ((__MM_SUB_HW_DATA_ADDR - __MM_SUB_PB_LEN)&0XFFFFFFFC)

/**********************************************************
* NIM
**********************************************************/
#define __MM_COFDM_S3811_ISDBT_ADDR ((__MM_SUB_PB_START_ADDR - __MM_COFDM_S3811_ISDBT_BUF_LEN)&0XFFFFFFE0)

/**********************************************************
* ISDBT CC
**********************************************************/
#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_COFDM_S3811_ISDBT_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
#define __MM_LWIP_MEM_ADDR      (__MM_ISDBTCC_PB_START_ADDR - __MM_LWIP_MEM_LEN)
#else
    #define __MM_LWIP_MEM_ADDR          (__MM_COFDM_S3811_ISDBT_ADDR - __MM_LWIP_MEM_LEN)
#endif
/*********************************************************
* Wifi, USB, CPU-DBG
**********************************************************/
#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR            ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)

//add for TTX_TO_MAIN
#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_USB_START_ADDR - __MM_TTX_SUB_PAGE_LEN)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
#define __MM_TTX_BS_START_ADDR    ((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)
//add for ATSC_CC_TO_MAIN
#define __MM_ATSC_CC_PB_START_ADDR  ((__MM_TTX_PB_START_ADDR - __MM_ATSC_CC_PB_LEN)&0XFFFFFFFC)
#define __MM_ATSC_CC_BS_START_ADDR  ((__MM_ATSC_CC_PB_START_ADDR - __MM_ATSC_CC_BS_LEN)&0XFFFFFFFC)


#define __MM_CPU_DBG_MEM_ADDR          (__MM_ATSC_CC_BS_START_ADDR - __MM_DBG_MEM_LEN)
#define __MM_DBG_MEM_ADDR           __MM_CPU_DBG_MEM_ADDR

/*********************************************************
* Media player( Share to DMX,PVR)
*********************************************************/
#ifdef DVR_PVR_SUPPORT
//media player need share other buffers
//#define __MM_MP_BUFFER_LEN            __MM_PVR_VOB_BUFFER_LEN
//#define __MM_MP_BUFFER_ADDR            __MM_PVR_VOB_BUFFER_ADDR
#define __MM_MP_BUFFER_ADDR             ((__MM_EPG_BUFFER_START + 0x1FF)&0XFFFFFE00)
#define __MM_MP_BUFFER_LEN              (__MM_FB_BOTTOM_ADDR - __MM_MP_BUFFER_ADDR)
#else
#define __MM_MP_BUFFER_LEN            0x1000000
#define __MM_MP_BUFFER_ADDR            ((__MM_FB2_C_START_ADDR - __MM_MP_BUFFER_LEN)&0XFFFFFFF0)
#endif
//end of main mem map

/********************************************************
* FB detail addr
*********************************************************/
// for jpeg decoder memmap
#define __MM_FB0_Y_LEN            (1920*1088+1024)//(736*576+512)    //for high definition jpg decode
#define __MM_FB1_Y_LEN            __MM_FB0_Y_LEN
#define __MM_FB2_Y_LEN            __MM_FB0_Y_LEN

#define __MM_FB0_C_LEN            (__MM_FB0_Y_LEN/2)
#define __MM_FB1_C_LEN            __MM_FB0_C_LEN
#define __MM_FB2_C_LEN            __MM_FB0_C_LEN

#define __MM_FB3_Y_LEN            (736*576+1024)
#define __MM_FB3_C_LEN            (__MM_FB3_Y_LEN/2)
#define __MM_FB4_Y_LEN            __MM_FB3_Y_LEN
#define __MM_FB4_C_LEN            __MM_FB3_C_LEN
#define __MM_FB5_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB5_C_LEN          __MM_FB3_C_LEN
#define __MM_FB6_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB6_C_LEN          __MM_FB3_C_LEN

#define __MM_FB0_Y_START_ADDR   (__MM_FB_START_ADDR)
#define __MM_FB0_C_START_ADDR   (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

#define __MM_FB1_Y_START_ADDR   ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
#define __MM_FB1_C_START_ADDR   ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

#define __MM_FB2_Y_START_ADDR   ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
#define __MM_FB2_C_START_ADDR   ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

#define __MM_FB3_Y_START_ADDR   ((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
#define __MM_FB3_C_START_ADDR   ((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
#define __MM_FB4_Y_START_ADDR    ((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
#define __MM_FB4_C_START_ADDR   ((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
#define __MM_FB5_Y_START_ADDR    ((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
#define __MM_FB5_C_START_ADDR   ((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
#define __MM_FB6_Y_START_ADDR    ((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
#define __MM_FB6_C_START_ADDR   ((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR

#else //#ifndef DRAM_SPLIT
/* memory mapping

== limitations
1. AVC and MPEG2 decoder both use about 30MB memory, MPEG2 requires one 32MB segment,
    so we put decoder buffer between [64MB, 96MB], start from 96MB and go down.
2. DMX dma buffer should under same 8M segment.
    __MM_DMX_AVP_START_ADDR, and __MM_DMX_REC_START_ADDR, must under same 8M segment,

    [126,128]  2MB -- cpu memory -- void memory, left to customer
    [96, 126] 30MB -- see memory -- private memory
    [64 , 96] 32MB -- cpu memory -- Video Decoder buffer
    [30 , 64] 34MB -- cpu memory -- PVR VOB buffer.
    [15 , 30] 15MB -- cpu memory -- Device Buffer: DMX, GE, OSD, VCAP, USB, EPG, DB, LWIP, etc.
    [0    , 15] 15MB -- cpu memory -- main code + heap

*/

//#define AVC_SUPPORT_UNIFY_MEM
#ifdef SD_PVR
#ifdef AVC_SUPPORT_UNIFY_MEM
#undef AVC_SUPPORT_UNIFY_MEM
#endif
#endif

#ifdef AVC_SUPPORT_UNIFY_MEM
#ifdef MP_PREVIEW_SWITCH_SMOOTHLY
#undef MP_PREVIEW_SWITCH_SMOOTHLY
#endif

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#undef DYNAMIC_RESOLUTION_SUPPORT
#endif

#define AVC_MEM_LEN		0x15bb000//0x1898400
#endif

#ifdef DVBC_SUPPORT
#define __MM_NIM_BUFFER_LEN         0x200000//2M
#else
#define __MM_NIM_BUFFER_LEN         0x0
#endif

#ifdef DVR_PVR_SUPPORT
#ifdef _MHEG5_V20_ENABLE_ //MHEG5 enable, reserve 8MB
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(180*3)+0x1000- __MM_NIM_BUFFER_LEN)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE        0X800000
#else
    #ifdef SD_PVR
        #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(75*2)+0x1000- __MM_NIM_BUFFER_LEN)//0x88a800//0x6fb000
    #else
        #ifdef SAT2IP_SUPPORT
            #define __MM_MEDIA_PROV_BUFFER_LEN     0x800000
        #else
            #define __MM_MEDIA_PROV_BUFFER_LEN     0
        #endif
    #ifdef DLNA_SUPPORT
            #define __MM_DLNA_BUFFER_LEN     0x800000
        #else
            #define __MM_DLNA_BUFFER_LEN     0
        #endif
		// About 12M for PVR, that's enough
		#define __MM_PVR_VOB_BUFFER_LEN (((47*1024)*(261)+0x1000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_DLNA_BUFFER_LEN - __MM_NIM_BUFFER_LEN)
	#endif
#endif
#else
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(80+75 * 2)+0x1000 - __MM_NIM_BUFFER_LEN)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE 0
#endif

#define __MM_SHARED_MEM_LEN      256
#ifdef HW_SECURE_ENABLE
    #define __MM_SEE_MP_BUF_LEN      0x00900000    //9M
    #ifdef SD_PVR
		#define __MM_PRIVATE_SHARE_LEN	0x01A00000//0x01A00000//0x01e00000	//26M
    #else
		#define __MM_PRIVATE_SHARE_LEN	0x02000000//0x01e00000	//30M
    #endif
	#define __MM_VOID_BUFFER_LEN	0//0x00200000	//2M
#else
#ifdef _C0200A_CA_ENABLE_//20140623 evan.wu for C0200A MemMap
	#define __MM_SEE_MP_BUF_LEN  	0
	#define __MM_PRIVATE_SHARE_LEN	0x01e00000	//30M
	#define __MM_VOID_BUFFER_LEN	0x00200000	//2M
#else
	#if(defined( _AUI_TEST_)&&defined(_M3503B_))
	#define __MM_SEE_MP_BUF_LEN  	0
	#define __MM_PRIVATE_SHARE_LEN	0x01e00000	//30M
	#define __MM_VOID_BUFFER_LEN	0x00200000	//2M
	#else
	#define __MM_SEE_MP_BUF_LEN      0
	#define __MM_PRIVATE_SHARE_LEN	0x02000000//0x01e00000	//30M
	#define __MM_VOID_BUFFER_LEN	0//0x00200000	//2M
	#endif
#endif

#endif
#define __MM_PRIVATE_LEN        (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

#ifdef SD_PVR
    #define __MM_HIGHEST_ADDR   0xa4000000        //64M
#else
    #define __MM_HIGHEST_ADDR   0xa8000000        //128M
#endif
#define __MM_VOID_BUFFER_ADDR    (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)    //126M or 114M
#define __MM_SHARE_BASE_ADDR     (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR        (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)     //96M
#ifdef SD_PVR
    #define __MM_MAIN_TOP_ADDR        0xa2600000//0xa2000000        //36MB
/*
    #ifdef _M3383_SABBAT_
    #define __MM_GE_START_ADDR            ((__MM_MAIN_TOP_ADDR - __MM_GE_LEN)&0XFFFFFFE0)
    #define __MM_OSD_BK_ADDR1              ((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)
    #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    #endif
*/
    #define __MM_OSD_VSRC_MEM_ADDR    (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE) 
    #define __MM_NIM_BUFFER_ADDR            (__MM_OSD_VSRC_MEM_ADDR - __MM_NIM_BUFFER_LEN)

    #ifdef _MHEG5_V20_ENABLE_
        #define __MM_MHEG5_BUFFER_ADDR      (__MM_NIM_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
        #define __MM_DMX_AVP_START_ADDR     ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
    #else
        #define __MM_DMX_AVP_START_ADDR     ((__MM_NIM_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
    #endif
    #define __MM_DMX_REC_START_ADDR        (__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)
    #define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)

    #define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)
    #define __MM_BUF_PVR_TOP_ADDR       __MM_EPG_BUFFER_START
    #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    
    #define __MM_FB_TOP_ADDR        (__MM_PVR_VOB_BUFFER_ADDR&0XFFFFFC00)     //32MB align
#else
    #define __MM_FB_TOP_ADDR        0xa6000000        //96MB
#endif
#ifdef _CAS9_VSC_ENABLE_
	#define __MM_VSC_CODE_START_ADDR	__MM_PRIVATE_ADDR
	#define __MM_VSC_DATA_START_ADDR (__MM_VSC_CODE_START_ADDR+__MM_VSC_CODE_LEN)
#endif

#ifdef SD_PVR
    #if(__MM_MAIN_TOP_ADDR != __MM_PRIVATE_ADDR)
    #error "__MM_PRIVATE_ADDR address error"
    #endif
#else
    #if(__MM_FB_TOP_ADDR != __MM_PRIVATE_ADDR)
    #error "__MM_PRIVATE_ADDR address error"
    #endif
#endif

#define __MM_FB_LEN_DEVIDED        0X32A000//(HD:1920X1152X1.5)
#ifndef SYSCFG_SD_VIDEO
    #ifdef VIDEO_DEBLOCKING_SUPPORT
    #define __MM_FB_LEN                0x10CF200//0x19c6200
    #else
    #define __MM_FB_LEN                0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
    #endif
    #define __MM_MAF_LEN            0x198C00//0xd0000//0X3000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#else
    #ifdef VIDEO_DEBLOCKING_SUPPORT
    #define __MM_FB_LEN                0x61BC00//0x10CF200//0x19c6200
    #else
    #define __MM_FB_LEN                0x308400//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
    #endif
    #define __MM_MAF_LEN            0X8C000//0x198C00//0xd0000//0X3000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#endif
#define __MM_DVW_LEN            0

//#define SD_PVR //to support 64M with SD pvr


//#define __MM_FB_START_ADDR        ((AVC_VBV_ADDR - __MM_FB_LEN)&0XFFFFFF00)
#define __MM_FB_START_ADDR        ((__MM_FB_TOP_ADDR - __MM_FB_LEN)&0XFFFFFc00)

// for satcodx memmap
#define __MM_DVW_START_ADDR            ((__MM_FB2_C_START_ADDR - 0X25FA0)&0XFFFFFFF0)

#define MAX_EXTRA_FB_NUM 3
#ifndef SYSCFG_SD_VIDEO
    #define MAX_MB_WIDTH 120 //(1920/16)
    #define MAX_MB_HEIGHT 68 //(1088/16)
#else
    #define MAX_MB_WIDTH 46//45 //(720/16)
    #define MAX_MB_HEIGHT 36//36 //(576/16)
#endif

#ifdef H264_SUPPORT_MULTI_BANK
    #ifndef SYSCFG_SD_VIDEO
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
    #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
    #endif
#define EXTRA_FB_SIZE 0x2000
#define ONE_FB_SIZE (((MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2+EXTRA_FB_SIZE-1)&0xffffe000)+EXTRA_FB_SIZE)
#else
    #ifndef SYSCFG_SD_VIDEO
        #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
    #else
        #define MAX_MB_STRIDE 46//46 //120 MB alignment to improve AVC performance
    #endif

    #ifdef SYSCFG_SD_VIDEO
        #define one_frm_y_size         (MAX_MB_STRIDE*((MAX_MB_HEIGHT+1)/2)*512)
        #define one_frm_c_size   (MAX_MB_STRIDE*((((MAX_MB_HEIGHT+1)/2)+1)/2)*512)
        #define ONE_FB_SIZE (one_frm_y_size + one_frm_c_size)
    #else
        #define ONE_FB_SIZE (MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2)
    #endif

#endif

#define ONE_DV_FB_SIZE ((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#ifndef SYSCFG_SD_VIDEO
#define AVC_FB_LEN		ONE_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0x1700000
#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN    0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0xb00000
#endif
#define AVC_MV_LEN		ONE_MV_SIZE*(5+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#else
#define const_frm_num   5
#define AVC_FB_LEN		ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN		ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#endif

#define AVC_MB_COL_LEN		0x18000 //0x11000
#else
#ifndef SYSCFG_SD_VIDEO
#define AVC_FB_LEN        ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000
#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN    0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#endif
#define AVC_MV_LEN        ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x22000
#else
#define const_frm_num   5
#define AVC_FB_LEN        ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN        ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN    0x12000 // 0x11000 will cause overflow
#endif
#endif

#define AVC_MB_NEI_LEN        0x20000
#define AVC_CMD_QUEUE_LEN   0x10000 //In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
#undef  AVC_LAF_RW_BUF_LEN
//#define AVC_LAF_RW_BUF_LEN ((MAX_MB_WIDTH*MAX_MB_HEIGHT)*32*2*2)
#define AVC_LAF_RW_BUF_LEN (((((MAX_MB_WIDTH*MAX_MB_HEIGHT)*48*2)+1023)&0x0ffffc00)*2)

//#define AVC_LAF_FLAG_BUF_LEN (0xc00*21)
#define AVC_LAF_FLAG_BUF_LEN (0xc00*22) //when enable dual output, we need 1 more laf buffer

#ifndef SD_PVR
    #define AVC_VBV_LEN        0x400000 //for CI+, must use 4MB. if this size is set to 0x200000, vbv buffer overflow could happen in 20061007d_0.ts
#else
    #define AVC_VBV_LEN        0x180000
#endif
#ifndef AVC_SUPPORT_UNIFY_MEM
/*AVC buffer allocation*/
#define AVC_FB_ADDR 		((__MM_FB_TOP_ADDR -  AVC_FB_LEN )&0xfffffe00)   		//512 bytes alignment
#define AVC_DVIEW_ADDR 		((AVC_FB_ADDR -  AVC_DVIEW_LEN)&0xfffffe00) 	//512 bytes alignment
#define AVC_MV_ADDR 		((AVC_DVIEW_ADDR - AVC_MV_LEN)&0xffffff00)  		//256 bytes alignment
#define AVC_MB_COL_ADDR 	((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00) 		//256 bytes alignment
#define AVC_MB_NEI_ADDR 	((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00) 	//256 bytes alignment
#define AVC_LAF_RW_BUF_ADDR ((AVC_MB_NEI_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#else
#define AVC_MB_COL_ADDR 		    ((__MM_FB_TOP_ADDR - AVC_MB_COL_LEN - AVC_MV_LEN)&0xffffff00)  		//256 bytes alignment
#define AVC_MB_NEI_ADDR 			((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00) 	//256 bytes alignment
#define AVC_MEM_ADDR 				((AVC_MB_NEI_ADDR - AVC_MEM_LEN)&0xffffff00)

#define AVC_DVIEW_ADDR 				0
#define AVC_MV_ADDR 				0
#define AVC_LAF_RW_BUF_ADDR			0
#define AVC_LAF_FLAG_BUF_ADDR       0
#define AVC_FB_ADDR					0
#endif

#if 1 //ifdef FPGA_TEST
#define __MM_GMA1_LEN            0 // 0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN            0 // 0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN        0 // 0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0 // 0x6DB0 // command buffer
#else
#define __MM_GMA1_LEN            0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN            0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN        0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0x6DB0 // command buffer
#endif
#define __MM_GE_LEN                (__MM_GMA1_LEN+__MM_GMA2_LEN+__MM_TEMP_BUF_LEN+__MM_CMD_LEN) //0xBE45B0
#define __MM_OSD_LEN            0x65400 // 720*576
#ifndef SYSCFG_SD_VIDEO
#define __MM_OSD1_LEN           (1280*720*4)//(1280*720*4)
#define __MM_OSD2_LEN            (1920*1080)
#else
#define __MM_OSD1_LEN           (720*576*4) //(1008 * 640 * 2 + 256)
#define __MM_OSD2_LEN            (720*576)
#endif

//#define OSD_VSRC_MEM_MAX_SIZE     0x400000    //300*1024
#define OSD_VSRC_MEM_MAX_SIZE     0x140000    //300*1024

#ifndef SD_PVR
#define __MM_VBV_LEN            0x500000
#else
#define __MM_VBV_LEN            0x12C000//(HD = 8*SD > 4*SD)
#endif

#define __MM_DMX_SI_LEN            (32*188)//(16*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define EXTRA_VIDEO_NUM 3
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*(44-EXTRA_VIDEO_NUM))
#else
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*44)
#endif

#define __MM_SI_VBV_OFFSET        __MM_DMX_SI_TOTAL_LEN
#define __MM_DMX_DATA_LEN        (30*188)
#define __MM_DMX_PCR_LEN        (10*188)
#define __MM_DMX_AUDIO_LEN        (256*188)//(32*188)
#define __MM_DMX_VIDEO_LEN        (12*512*188)//(8*512*188)
#ifdef SUPPORT_MULTI_SD_VIDEO
    #define __MM_DMX_EXTRA_VIDEO_LEN (960*188)
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_EXTRA_VIDEO_LEN*EXTRA_VIDEO_NUM+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#else
    #define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#endif
#define __MM_DMX_BLK_BUF_LEN    0xbc000

#define __MM_SUB_BS_LEN            0xA000 //0X2800

#ifdef HD_SUBTITLE_SUPPORT
    #define __MM_SUB_PB_LEN            0xA0000 //0x50000//0X19000(1920X340 for hd subt)
#else
    #define __MM_SUB_PB_LEN            0X19000
#endif

#ifdef SUPPORT_HW_SUBT_DECODE
#define __MM_SUB_HW_DATA_LEN 0xC000
#else
#define __MM_SUB_HW_DATA_LEN 0
#endif

// TTX
#if (TTX_ON==1)
#define __MM_TTX_BS_LEN            0x5000//0X2800
#ifdef TTX_SUB_PAGE
#define __MM_TTX_PB_LEN                0xCB200 //+80*1040 //0XCA800
#define __MM_TTX_SUB_PAGE_LEN       0x14500 //80*1040
#else
#define __MM_TTX_PB_LEN                0xCA800 //+80*1040 //
#define __MM_TTX_SUB_PAGE_LEN       0 //80*1040
#endif
#ifdef SUPPORT_PACKET_26
#define __MM_TTX_P26_NATION_LEN     0x61A80 //25*40*400
#define __MM_TTX_P26_DATA_LEN       0x3E8 //25*40
#else
#define __MM_TTX_P26_NATION_LEN     0
#define __MM_TTX_P26_DATA_LEN       0
    #endif
#else
    #define __MM_TTX_BS_LEN             0
    #define __MM_TTX_PB_LEN             0
    #define __MM_TTX_SUB_PAGE_LEN       0
    #define __MM_TTX_P26_NATION_LEN     0
    #define __MM_TTX_P26_DATA_LEN       0
#endif

#if (CC_ON==1)
#define OSD_CC_WIDTH   	  576//480//480//704//480//(CC_CHAR_W*40+16)//560//704(16bytes aligned)
#define OSD_CC_HEIGHT  	  390//360//300//360//300//450//(CC_CHAR_H*15)//500//570
#define CC_CHAR_HEIGHT		26

#define __MM_ATSC_CC_PB_RECT_LEN (OSD_CC_WIDTH*OSD_CC_HEIGHT)
#define __MM_ATSC_CC_PB_LEN  (__MM_ATSC_CC_PB_RECT_LEN+OSD_CC_WIDTH*4*CC_CHAR_HEIGHT)
#define __MM_ATSC_CC_BS_LEN  0x1c00 // 1K Word CC Data, 1K Byte CC Field, 2K Word DTVCC Data
#else
#undef __MM_ATSC_CC_PB_LEN
#undef __MM_ATSC_CC_BS_LEN
#define __MM_ATSC_CC_PB_LEN	0
#define __MM_ATSC_CC_BS_LEN	0
#endif
#define __MM_DMX_REC_LEN            (__MM_DMX_VIDEO_LEN)

#define __MM_USB_DMA_LEN                0    // 0x10FFFF currently not use
#define __MM_EPG_BUFFER_LEN             0x100000
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0x100000

#ifdef NETWORK_SUPPORT
#define STO_PROTECT_BY_MUTEX
#define __MM_LWIP_MEM_LEN               0x10000
#define __MM_LWIP_MEMP_LEN              0xce200
#define __MM_XML_MEMP_LEN                0x100000 // 5M
#else
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN                0
#endif
#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_LEN        0x8FC0
#define __MM_ISDBTCC_PB_LEN        0x7E900
#endif

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#define __MM_VCAP_FB_SIZE               (736*576*2*4)
#else
#define __MM_VCAP_FB_SIZE               0
#endif
#define __MM_DBG_MEM_LEN   0x4000

#ifdef AVC_SUPPORT_UNIFY_MEM
#if (__MM_FB_START_ADDR < AVC_MEM_ADDR)
#define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR

#undef  AVC_MEM_ADDR
#undef  AVC_MEM_LEN
#define AVC_MEM_ADDR                __MM_FB_BOTTOM_ADDR
#define AVC_MEM_LEN                 ((AVC_MB_NEI_ADDR - AVC_MEM_ADDR)&0xffffff00)

#else
#define __MM_FB_BOTTOM_ADDR         AVC_MEM_ADDR
#endif
#else
#if (__MM_FB_START_ADDR < AVC_LAF_RW_BUF_ADDR)
#define __MM_FB_BOTTOM_ADDR         __MM_FB_START_ADDR
#else
#define __MM_FB_BOTTOM_ADDR         AVC_LAF_RW_BUF_ADDR
#endif
#endif

#ifndef AVC_SUPPORT_UNIFY_MEM
#define AVC_MEM_LEN 0   //for compile error
#endif

//#ifdef _M3383_SABBAT_

//#define __MM_DMX_REC_START_ADDR        (__MM_FB_BOTTOM_ADDR - __MM_DMX_REC_LEN)
//#define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
//#define __MM_BUF_PVR_TOP_ADDR       __MM_DMX_CPU_BLK_ADDR
//#define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)

//#ifdef _MHEG5_V20_ENABLE_
//#define __MM_MHEG5_BUFFER_ADDR      (__MM_PVR_VOB_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
//#define __MM_DMX_AVP_START_ADDR        ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
//#else
//#define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
//#endif

//#define __MM_EPG_BUFFER_START       (__MM_DMX_AVP_START_ADDR - __MM_EPG_BUFFER_LEN)
//#define __MM_LWIP_MEM_ADDR          (__MM_EPG_BUFFER_START - __MM_LWIP_MEM_LEN)

//#else /* #ifdef _M3383_SABBAT*/

#ifndef SD_PVR
    #define __MM_NIM_BUFFER_ADDR            (__MM_FB_BOTTOM_ADDR - __MM_NIM_BUFFER_LEN)
    #define __MM_BUF_PVR_TOP_ADDR       __MM_NIM_BUFFER_ADDR
    #ifdef SAT2IP_SUPPORT//MEDIA_PROVIDER_USE_RING_BUFFER
        #define __MM_MEDIA_PROVIDER_BUFFER_ADDR (__MM_BUF_PVR_TOP_ADDR - __MM_MEDIA_PROV_BUFFER_LEN)
        #define __MM_PVR_VOB_BUFFER_ADDR        (__MM_MEDIA_PROVIDER_BUFFER_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #else
        #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #endif

    #ifdef _MHEG5_V20_ENABLE_
        #define __MM_MHEG5_BUFFER_ADDR      (__MM_PVR_VOB_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
        #define __MM_DMX_AVP_START_ADDR        ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
    #else
        #define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
    #endif

    #define __MM_DMX_REC_START_ADDR        (__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)
    #define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)

    #define __MM_GE_START_ADDR          ((__MM_EPG_BUFFER_START - __MM_GE_LEN)&0XFFFFFFE0)
    #ifdef _M36F_SINGLE_CPU
        // for m36f single cpu mode(only test for ali internal)
        // move osd, vsrc, scap buffer to private buffer base.
        #define __MM_LWIP_MEM_ADDR      (__MM_GE_START_ADDR - __MM_LWIP_MEM_LEN)
    #else
        #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)
        #if (defined(_CAS9_CA_ENABLE_) || defined(_C0200A_CA_ENABLE_))
            #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFF0)
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        #else
        		#if (defined(_M3503B_)&&(defined(_AUI_TEST_)))
        		#define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFF0)
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        		#else
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
            #endif
        #endif
        #define __MM_OSD_VSRC_MEM_ADDR        (__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)
        #define __MM_LWIP_MEM_ADDR          (__MM_OSD_VSRC_MEM_ADDR - __MM_LWIP_MEM_LEN)
    #endif
#else
    #define __MM_GE_START_ADDR          ((__MM_FB_BOTTOM_ADDR - __MM_GE_LEN)&0XFFFFFFE0)
    #ifdef _M36F_SINGLE_CPU
        // for m36f single cpu mode(only test for ali internal)
        // move osd, vsrc, scap buffer to private buffer base.
        #define __MM_LWIP_MEM_ADDR      (__MM_GE_START_ADDR - __MM_LWIP_MEM_LEN)
    #else
        #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)
        #if (defined(_CAS9_CA_ENABLE_) || defined(_C0200A_CA_ENABLE_))
            #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFF0)
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        #else
        	#if (defined(_M3503B_)&&(defined(_AUI_TEST_)))
        		 #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFF0)
             #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        	#else
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
          #endif
        #endif
        #define __MM_LWIP_MEM_ADDR          (__MM_VCAP_FB_ADDR - __MM_LWIP_MEM_LEN)
     #endif
#endif


//#endif /* #ifdef _M3383_SABBAT*/

#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR            ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)

//add for TTX_TO_MAIN
#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_USB_START_ADDR - __MM_TTX_SUB_PAGE_LEN)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
#define __MM_TTX_BS_START_ADDR    ((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)

//add for ATSC_CC_TO_MAIN
#define __MM_ATSC_CC_PB_START_ADDR  ((__MM_TTX_PB_START_ADDR - __MM_ATSC_CC_PB_LEN)&0XFFFFFFFC)
#define __MM_ATSC_CC_BS_START_ADDR  ((__MM_ATSC_CC_PB_START_ADDR - __MM_ATSC_CC_BS_LEN)&0XFFFFFFFC)

#define __MM_SUB_BS_START_ADDR    ((__MM_ATSC_CC_BS_START_ADDR  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - __MM_SUB_HW_DATA_LEN)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR    ((__MM_SUB_HW_DATA_ADDR - __MM_SUB_PB_LEN)&0XFFFFFFFC)
//modify atsc subtitle on main cpu
#define __MM_DCII_SUB_BS_START_ADDR     (__MM_SUB_PB_START_ADDR - __MM_DCII_SUB_BS_LEN)
#define __MM_SUBT_ATSC_SEC_ADDR     (__MM_DCII_SUB_BS_START_ADDR - __MM_SUBT_ATSC_SEC_LEN)
//modify isdbt closed caption on main cpu
#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
#define __MM_CPU_DBG_MEM_ADDR          (__MM_ISDBTCC_PB_START_ADDR - __MM_DBG_MEM_LEN)
#else
#define __MM_CPU_DBG_MEM_ADDR          (__MM_SUBT_ATSC_SEC_ADDR - __MM_DBG_MEM_LEN)

#endif

#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR

//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/
#define __MM_VBV_START_ADDR            ((__MM_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define AVC_VBV_ADDR                 (__MM_PRIVATE_TOP_ADDR - AVC_VBV_LEN)     //256 bytes alignment

#if (AVC_VBV_ADDR <= __MM_MAF_START_ADDR)
#define __MM_DMX_SEE_BLK_ADDR    ((AVC_VBV_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#else
#define __MM_DMX_SEE_BLK_ADDR    ((__MM_MAF_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#endif

//#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - __MM_TTX_SUB_PAGE_LEN)
//#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
//#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
//#define __MM_TTX_BS_START_ADDR    ((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
//#define __MM_TTX_PB_START_ADDR    ((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)
//#define __MM_ATSC_CC_PB_START_ADDR  ((__MM_TTX_BS_START_ADDR - __MM_ATSC_CC_PB_LEN)&0XFFFFFFFC)
//#define __MM_ATSC_CC_BS_START_ADDR  ((__MM_ATSC_CC_PB_START_ADDR - __MM_ATSC_CC_BS_LEN)&0XFFFFFFFC)

#define __MM_SEE_MP_BUF_ADDR    (__MM_DMX_SEE_BLK_ADDR -  __MM_SEE_MP_BUF_LEN)

#define AVC_CMD_QUEUE_ADDR  ((__MM_SEE_MP_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment

#ifndef AVC_SUPPORT_UNIFY_MEM
#define AVC_LAF_FLAG_BUF_ADDR   ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define __MM_OSD_BK_ADDR2       ((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFF0)
#else
#define __MM_OSD_BK_ADDR2       ((AVC_CMD_QUEUE_ADDR - __MM_OSD2_LEN)&0XFFFFFFF0)
#endif

#if 0
#define __MM_SUB_BS_START_ADDR    ((__MM_OSD_BK_ADDR2  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR ((__MM_SUB_BS_START_ADDR - __MM_SUB_HW_DATA_LEN)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR    ((__MM_SUB_HW_DATA_ADDR - __MM_SUB_PB_LEN)&0XFFFFFFFC)
#define __MM_DCII_SUB_BS_START_ADDR     (__MM_SUB_PB_START_ADDR - __MM_DCII_SUB_BS_LEN)
#define __MM_SUBT_ATSC_SEC_ADDR     (__MM_DCII_SUB_BS_START_ADDR - __MM_SUBT_ATSC_SEC_LEN)
#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
#endif
#endif

#ifdef _M36F_SINGLE_CPU
// for m3f single cpu(only test for ali internal)
// more osd, vsrc, scap buffer to private buffer base.
#define __MM_OSD_BK_ADDR1              ((__MM_SUB_PB_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#define __MM_OSD_VSRC_MEM_ADDR        (__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)
#define __MM_SEE_DBG_MEM_ADDR      (__MM_OSD_VSRC_MEM_ADDR - __MM_DBG_MEM_LEN)
    #if(__MM_SEE_DBG_MEM_ADDR < __MM_PRIVATE_ADDR)
        #error "__MM_SEE_DBG_MEM_ADDR address error"
    #endif
#else
#define __MM_SEE_DBG_MEM_ADDR      ( __MM_OSD_BK_ADDR2 - __MM_DBG_MEM_LEN)
#endif

// for jpeg decoder memmap
#ifdef SYSCFG_SD_VIDEO
#define __MM_FB0_Y_LEN            (736*576 + 1024)
#else
#define __MM_FB0_Y_LEN            (1920*1088+1024)//(736*576+512)    //for high definition jpg decode
#endif
#define __MM_FB1_Y_LEN            __MM_FB0_Y_LEN
#define __MM_FB2_Y_LEN            __MM_FB0_Y_LEN

#define __MM_FB0_C_LEN            (__MM_FB0_Y_LEN/2)
#define __MM_FB1_C_LEN            __MM_FB0_C_LEN
#define __MM_FB2_C_LEN            __MM_FB0_C_LEN

#define __MM_FB3_Y_LEN            (736*576+1024)
#define __MM_FB3_C_LEN            (__MM_FB3_Y_LEN/2)
#define __MM_FB4_Y_LEN            __MM_FB3_Y_LEN
#define __MM_FB4_C_LEN            __MM_FB3_C_LEN
#define __MM_FB5_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB5_C_LEN          __MM_FB3_C_LEN
#define __MM_FB6_Y_LEN          __MM_FB3_Y_LEN
#define __MM_FB6_C_LEN          __MM_FB3_C_LEN

#ifdef HW_SECURE_ENABLE
#ifdef SD_PVR
    #define __MM_FB0_Y_START_ADDR    (__MM_TTX_P26_DATA_BUF_ADDR & 0xFFFFFE00)
    #define __MM_FB0_C_START_ADDR    (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

    #define __MM_FB1_Y_START_ADDR    ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
    #define __MM_FB1_C_START_ADDR    ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

    #define __MM_FB2_Y_START_ADDR    ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
    #define __MM_FB2_C_START_ADDR    ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

    #if (__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN > __MM_PRIVATE_TOP_ADDR)
    #error "jpeg frame buffer overflow ! please check it"
    #endif

    #define __MM_FB3_Y_START_ADDR    0 //((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
    #define __MM_FB3_C_START_ADDR    0 //((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
    #define __MM_FB4_Y_START_ADDR    0 //((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
    #define __MM_FB4_C_START_ADDR    0 //((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
    #define __MM_FB5_Y_START_ADDR    0 //((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
    #define __MM_FB5_C_START_ADDR    0 //((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
    #define __MM_FB6_Y_START_ADDR    0 //((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
    #define __MM_FB6_C_START_ADDR    0 //((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)
    #define __MM_MP_BUFFER_LEN        (__MM_TTX_BS_START_ADDR - __MM_SEE_MP_BUF_ADDR)//(__MM_SEE_MP_BUF_LEN - __MM_FB0_Y_LEN * 3 - __MM_FB0_C_LEN * 3)
    #define __MM_MP_BUFFER_ADDR        __MM_SEE_MP_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
#else
    #define __MM_FB0_Y_START_ADDR    (__MM_SEE_MP_BUF_ADDR & 0xFFFFFE00)
    #define __MM_FB0_C_START_ADDR    (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

    #define __MM_FB1_Y_START_ADDR    ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
    #define __MM_FB1_C_START_ADDR    ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

    #define __MM_FB2_Y_START_ADDR    ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
    #define __MM_FB2_C_START_ADDR    ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

    #define __MM_FB3_Y_START_ADDR    0 //((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
    #define __MM_FB3_C_START_ADDR    0 //((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
    #define __MM_FB4_Y_START_ADDR    0 //((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
    #define __MM_FB4_C_START_ADDR    0 //((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
    #define __MM_FB5_Y_START_ADDR    0 //((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
    #define __MM_FB5_C_START_ADDR    0 //((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
    #define __MM_FB6_Y_START_ADDR    0 //((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
    #define __MM_FB6_C_START_ADDR    0 //((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)
    #define __MM_MP_BUFFER_LEN        (__MM_PRIVATE_TOP_ADDR - __MM_TTX_P26_DATA_BUF_ADDR)//(__MM_SEE_MP_BUF_LEN - __MM_FB0_Y_LEN * 3 - __MM_FB0_C_LEN * 3)
    #define __MM_MP_BUFFER_ADDR        __MM_TTX_P26_DATA_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
#endif
#else

    #define __MM_FB0_Y_START_ADDR   (__MM_FB_START_ADDR)
    #define __MM_FB0_C_START_ADDR   (__MM_FB0_Y_START_ADDR+__MM_FB0_Y_LEN)

    #define __MM_FB1_Y_START_ADDR   ((__MM_FB0_C_START_ADDR+__MM_FB0_C_LEN)&0XFFFFFE00)
    #define __MM_FB1_C_START_ADDR   ((__MM_FB1_Y_START_ADDR+__MM_FB1_Y_LEN)&0XFFFFFE00)

    #define __MM_FB2_Y_START_ADDR   ((__MM_FB1_C_START_ADDR+__MM_FB1_C_LEN)&0XFFFFFE00)
    #define __MM_FB2_C_START_ADDR   ((__MM_FB2_Y_START_ADDR+__MM_FB2_Y_LEN)&0XFFFFFE00)

    #define __MM_FB3_Y_START_ADDR   ((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
    #define __MM_FB3_C_START_ADDR   ((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
    #define __MM_FB4_Y_START_ADDR    ((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
    #define __MM_FB4_C_START_ADDR   ((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
    #define __MM_FB5_Y_START_ADDR    ((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
    #define __MM_FB5_C_START_ADDR   ((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
    #define __MM_FB6_Y_START_ADDR    ((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
    #define __MM_FB6_C_START_ADDR   ((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)
#ifdef DVR_PVR_SUPPORT
#ifdef SAT2IP_SUPPORT
    #define __MM_MP_BUFFER_LEN            (__MM_PVR_VOB_BUFFER_LEN+__MM_NIM_BUFFER_LEN+__MM_MEDIA_PROV_BUFFER_LEN)
#else
    #define __MM_MP_BUFFER_LEN            (__MM_PVR_VOB_BUFFER_LEN+__MM_NIM_BUFFER_LEN)
#endif
    #define __MM_MP_BUFFER_ADDR            __MM_PVR_VOB_BUFFER_ADDR
#else
    #define __MM_MP_BUFFER_LEN            0x1000000
    #define __MM_MP_BUFFER_ADDR            ((__MM_FB2_C_START_ADDR - __MM_MP_BUFFER_LEN)&0XFFFFFFF0)
#endif
#endif

//end of Private mem map

#ifdef SEE_CPU
#define __MM_DBG_MEM_ADDR __MM_SEE_DBG_MEM_ADDR
#else
#define __MM_DBG_MEM_ADDR __MM_CPU_DBG_MEM_ADDR
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR

#endif //#ifndef DRAM_SPLIT


#endif //end of 128M config

#if 1 //#ifdef HW_SECURE_ENABLE
#define __MM_VIDEO_FILE_BUF_ADDR    __MM_SEE_MP_BUF_ADDR
#define __MM_VIDEO_FILE_BUF_LEN     (__MM_PRIVATE_TOP_ADDR - __MM_SEE_MP_BUF_ADDR)
#else
#define __MM_VIDEO_FILE_BUF_ADDR    __MM_MP_BUFFER_ADDR
#define __MM_VIDEO_FILE_BUF_LEN     __MM_MP_BUFFER_LEN
#endif

#endif


