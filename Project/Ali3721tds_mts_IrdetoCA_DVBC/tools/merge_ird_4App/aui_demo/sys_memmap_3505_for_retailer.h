
#ifndef __SYS_MEM_MAP_H
#define __SYS_MEM_MAP_H

#if (SYS_SDRAM_SIZE == 128)

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

#ifdef _MHEG5_V20_ENABLE_ //MHEG5 enable, reserve 8MB
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(120*3)+0x1000- __MM_NIM_BUFFER_LEN)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE        0X800000
#else
    #ifdef SAT2IP_SUPPORT
        #define __MM_MEDIA_PROV_BUFFER_LEN     0x800000
    #else
        #define __MM_MEDIA_PROV_BUFFER_LEN     0
    #endif
    #ifdef SAT2IP_PVR_SHARE_BUFFER
        #undef __MM_MEDIA_PROV_BUFFER_LEN
        #define __MM_MEDIA_PROV_BUFFER_LEN     0
    #endif
    #if(defined(WIFI_DIRECT_SUPPORT)||defined(_WIFI_ENABLE_))
        #define __WIFI_DIRECT_BUFFER_LEN     0x400000
    #else
        #define __WIFI_DIRECT_BUFFER_LEN     0x0
    #endif
	#ifdef DLNA_SUPPORT
        #define __MM_DLNA_BUFFER_LEN     0x800000
    #else
        #define __MM_DLNA_BUFFER_LEN     0
    #endif
	#define __MM_PVR_VOB_BUFFER_LEN (((47*1024)*(240*3)+0x1000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_DLNA_BUFFER_LEN - __MM_NIM_BUFFER_LEN)
#endif


#define __MM_SHARED_MEM_LEN      256
#define __MM_SEE_MP_BUF_LEN      0
#define __MM_PRIVATE_SHARE_LEN	0x02000000//0x01e00000	//30M
#define __MM_VOID_BUFFER_LEN	0//0x00200000	//2M
#define __MM_PRIVATE_LEN        (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)
#define __MM_HIGHEST_ADDR   0xa8000000        //128M
#define __MM_VOID_BUFFER_ADDR    (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)    //126M or 114M
#define __MM_SHARE_BASE_ADDR     (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)
#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR        (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)     //96M

#define __MM_FB_TOP_ADDR        0xa6000000        //96MB

#if(__MM_FB_TOP_ADDR != __MM_PRIVATE_ADDR)
	#error "__MM_PRIVATE_ADDR address error"
#endif

#define __MM_FB_LEN_DEVIDED        0X32A000//(HD:1920X1152X1.5)
    #ifdef VIDEO_DEBLOCKING_SUPPORT
    #define __MM_FB_LEN                0x10CF200//0x19c6200
    #else
    #define __MM_FB_LEN                0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
    #endif
    #define __MM_MAF_LEN            0x198C00//0xd0000//0X3000//((FLAG==4*4*3K) + VALUE ==120*72*32 *2(Y+C)>46*36*32 *2(Y+C) *4 )
#define __MM_DVW_LEN            0
#define __MM_FB_START_ADDR		((__MM_FB_TOP_ADDR - __MM_FB_LEN)&0XFFFFFF00)

// for satcodx memmap
#define __MM_DVW_START_ADDR            ((__MM_FB2_C_START_ADDR - 0X25FA0)&0XFFFFFFF0)

#define MAX_EXTRA_FB_NUM 3
    #define MAX_MB_WIDTH 120 //(1920/16)
    #define MAX_MB_HEIGHT 68 //(1088/16)

#ifdef H264_SUPPORT_MULTI_BANK
    #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
	#define EXTRA_FB_SIZE 0x2000
	#define ONE_FB_SIZE (((MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2+EXTRA_FB_SIZE-1)&0xffffe000)+EXTRA_FB_SIZE)
#else
    #define MAX_MB_STRIDE 120 //120 MB alignment to improve AVC performance
    #define ONE_FB_SIZE (MAX_MB_STRIDE*MAX_MB_HEIGHT*256*3/2)
#endif

#define ONE_DV_FB_SIZE ((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240


#define AVC_FB_LEN		ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN		ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x15000

#define AVC_MB_NEI_LEN        	0xf000
#define AVC_CMD_QUEUE_LEN   	0x10000 //In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
#undef  AVC_LAF_RW_BUF_LEN
#define AVC_LAF_RW_BUF_LEN 		(((((MAX_MB_WIDTH*MAX_MB_HEIGHT)*48*2)+1023)&0x0ffffc00)*2)

#define AVC_LAF_FLAG_BUF_LEN 	(0xc00*22) //when enable dual output, we need 1 more laf buffer

#define AVC_VBV_LEN        		0x400000 //for CI+, must use 4MB. if this size is set to 0x200000, vbv buffer overflow could happen in 20061007d_0.ts

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

#define __MM_GMA1_LEN           0 // 0x1FA400 // 1920*1080 osd layer1
#define __MM_GMA2_LEN           0 // 0x1FA400//1920*1080  osd layer2
#define __MM_TEMP_BUF_LEN       0 // 0x100 //1920*1080*4 temp resize buffer
#define __MM_CMD_LEN            0 // 0x6DB0 // command buffer
#define __MM_GE_LEN             (__MM_GMA1_LEN+__MM_GMA2_LEN+__MM_TEMP_BUF_LEN+__MM_CMD_LEN) //0xBE45B0
#define __MM_OSD_LEN            0x65400 // 720*576

#ifdef MULTIVIEW_SUPPORT
	#define __MM_OSD1_LEN           (1280*720*2 + 256) //(1280*720*4) 
#else
	#define __MM_OSD1_LEN           (1008 * 640 * 2  + 256)//(1280*720*2 + 256) //(1280*720*4) 
#endif

#define __MM_OSD2_LEN				(1920 * 1080)//(720 * 576) 
#define OSD_VSRC_MEM_MAX_SIZE     	0x140000    //300*1024
#define __MM_VBV_LEN            	0x500000
#define __MM_DMX_SI_LEN            	(32*188)//(16*188)

#ifdef SUPPORT_MULTI_SD_VIDEO
    #define EXTRA_VIDEO_NUM 3
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*(44-EXTRA_VIDEO_NUM))
#else
    #define __MM_DMX_SI_TOTAL_LEN    (__MM_DMX_SI_LEN*44)
#endif

#define __MM_SI_VBV_OFFSET        	__MM_DMX_SI_TOTAL_LEN
#define __MM_DMX_DATA_LEN        	(30*188)
#define __MM_DMX_PCR_LEN        	(10*188)
#define __MM_DMX_AUDIO_LEN        	(256*188)//(32*188)
#define __MM_DMX_VIDEO_LEN        	(12*512*188)//(8*512*188)
#define __MM_DMX_AVP_LEN        (__MM_DMX_VIDEO_LEN+__MM_DMX_AUDIO_LEN+__MM_DMX_PCR_LEN)
#define __MM_DMX_BLK_BUF_LEN    0x46800//0xbc000

#define __MM_SUB_BS_LEN			0x2d000
#define __MM_SUB_PB_LEN			0xA0000 //0x50000//0X19000(1920X340 for hd subt)

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
#define OSD_CC_WIDTH   	  576
#define OSD_CC_HEIGHT  	  390
#define CC_CHAR_HEIGHT		26
#define __MM_ATSC_CC_PB_RECT_LEN (OSD_CC_WIDTH*OSD_CC_HEIGHT)
#define __MM_ATSC_CC_PB_LEN  (__MM_ATSC_CC_PB_RECT_LEN+OSD_CC_WIDTH*4*CC_CHAR_HEIGHT)
#define __MM_ATSC_CC_BS_LEN  0x2c00 // 1K Word CC Data, 1K Byte CC Field, 2K Word DTVCC Data
#else
#undef __MM_ATSC_CC_PB_LEN
#undef __MM_ATSC_CC_BS_LEN
#define __MM_ATSC_CC_PB_LEN	0
#define __MM_ATSC_CC_BS_LEN	0
#endif

#define __MM_DMX_REC_LEN		    (__MM_DMX_AVP_LEN)

#define __MM_USB_DMA_LEN                0    // 0x10FFFF currently not use
#define __MM_EPG_BUFFER_LEN             0x100000
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0x100000

#ifdef NETWORK_SUPPORT
#define STO_PROTECT_BY_MUTEX
#define __MM_LWIP_MEM_LEN               0x40000
#define __MM_LWIP_MEMP_LEN              0xe0000//0xce200
#define __MM_XML_MEMP_LEN				0x100000 // 5M
#else
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN              	0
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

    #define __MM_NIM_BUFFER_ADDR            (__MM_FB_BOTTOM_ADDR - __MM_NIM_BUFFER_LEN)
    #define __MM_BUF_PVR_TOP_ADDR       __MM_NIM_BUFFER_ADDR
    #ifdef SAT2IP_SUPPORT//MEDIA_PROVIDER_USE_RING_BUFFER
        #define __MM_MEDIA_PROVIDER_BUFFER_ADDR (__MM_BUF_PVR_TOP_ADDR - __MM_MEDIA_PROV_BUFFER_LEN)
        #define __MM_PVR_VOB_BUFFER_ADDR        (__MM_MEDIA_PROVIDER_BUFFER_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #else
        #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #endif

	//OTA unpressed/pressed/swap data & swap share with PVR
	#define __MM_OTA_UNPRESSED_BOTTOM_ADDR    __MM_PVR_VOB_BUFFER_ADDR
	#define __MM_OTA_UNPRESSED_LEN          0x700000 //0x600000 //firmware may >5M + ota loader may >6M,should adjust this buffer
	#define __MM_OTA_UNPRESSED_TOP_ADDR         (__MM_OTA_UNPRESSED_BOTTOM_ADDR + __MM_OTA_UNPRESSED_LEN)

	#define __MM_OTA_PRESSED_BOTTOM_ADDR    __MM_OTA_UNPRESSED_TOP_ADDR
	#define __MM_OTA_PRESSED_LEN           0x400000
	#define __MM_OTA_PRESSED_TOP_ADDR    (__MM_OTA_PRESSED_BOTTOM_ADDR + __MM_OTA_PRESSED_LEN)

	#define __MM_OTA_SWAP_BOTTOM_ADDR   __MM_OTA_PRESSED_TOP_ADDR
	#define __MM_OTA_SWAP_LEN           (256*1024)
	#define __MM_OTA_SWAP_TOP_ADDR      (__MM_OTA_SWAP_BOTTOM_ADDR + __MM_OTA_SWAP_LEN)

    #ifdef _MHEG5_V20_ENABLE_
        #define __MM_MHEG5_BUFFER_ADDR      (__MM_PVR_VOB_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
		#define __MM_DMX_AVP_START_ADDR		((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
	#else
		#define __MM_DMX_AVP_START_ADDR		((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
    #endif

	#define __MM_DMX_REC_START_ADDR		((__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)
    #define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)

    #define __MM_GE_START_ADDR          ((__MM_EPG_BUFFER_START - __MM_GE_LEN)&0XFFFFFFE0)
    #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFF0)
    #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    #define __MM_OSD_VSRC_MEM_ADDR        (__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)
    #define __MM_LWIP_MEM_ADDR          (__MM_OSD_VSRC_MEM_ADDR - __MM_LWIP_MEM_LEN)

#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR			((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)
#define __MM_CPU_DBG_MEM_ADDR      	(__MM_USB_START_ADDR - __MM_DBG_MEM_LEN)

#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR

//end of main mem map

//Private mem map
#define __MM_VBV_START_ADDR            ((__MM_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define AVC_VBV_ADDR                 (__MM_PRIVATE_TOP_ADDR - AVC_VBV_LEN)     //256 bytes alignment

#if (AVC_VBV_ADDR <= __MM_MAF_START_ADDR)
	#define __MM_DMX_SEE_BLK_ADDR    ((AVC_VBV_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#else
	#define __MM_DMX_SEE_BLK_ADDR    ((__MM_MAF_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#endif

#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_DMX_SEE_BLK_ADDR - __MM_TTX_SUB_PAGE_LEN)
#define __MM_TTX_P26_NATION_BUF_ADDR (__MM_TTX_SUB_PAGE_BUF_ADDR - __MM_TTX_P26_NATION_LEN)
#define __MM_TTX_P26_DATA_BUF_ADDR  (__MM_TTX_P26_NATION_BUF_ADDR -  __MM_TTX_P26_DATA_LEN)
#define __MM_TTX_BS_START_ADDR	((__MM_TTX_P26_DATA_BUF_ADDR - __MM_TTX_BS_LEN)&0XFFFFFFFC)
#define __MM_TTX_PB_START_ADDR	((__MM_TTX_BS_START_ADDR - __MM_TTX_PB_LEN)&0XFFFFFFFC)

#define __MM_ATSC_CC_PB_START_ADDR	((__MM_TTX_PB_START_ADDR - __MM_ATSC_CC_PB_LEN)&0XFFFFFFFC)
#define __MM_ATSC_CC_BS_START_ADDR	((__MM_ATSC_CC_PB_START_ADDR - __MM_ATSC_CC_BS_LEN)&0XFFFFFFFC)

#define __MM_SEE_MP_BUF_ADDR    (__MM_ATSC_CC_BS_START_ADDR -  __MM_SEE_MP_BUF_LEN)
#define AVC_CMD_QUEUE_ADDR  ((__MM_SEE_MP_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)  	//256 bytes alignment

#ifndef AVC_SUPPORT_UNIFY_MEM
#define AVC_LAF_FLAG_BUF_ADDR   ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define __MM_OSD_BK_ADDR2       ((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFF0)
#else
#define __MM_OSD_BK_ADDR2       ((AVC_CMD_QUEUE_ADDR - __MM_OSD2_LEN)&0XFFFFFFF0)
#endif

#define __MM_SUB_BS_START_ADDR    	((__MM_OSD_BK_ADDR2  - __MM_SUB_BS_LEN)&0XFFFFFFFC)
#define __MM_SUB_HW_DATA_ADDR 		((__MM_SUB_BS_START_ADDR - __MM_SUB_HW_DATA_LEN)&0XFFFFFFF0)
#define __MM_SUB_PB_START_ADDR    	((__MM_SUB_HW_DATA_ADDR - __MM_SUB_PB_LEN)&0XFFFFFFFC)
#define __MM_DCII_SUB_BS_START_ADDR (__MM_SUB_PB_START_ADDR - __MM_DCII_SUB_BS_LEN)
#define __MM_SUBT_ATSC_SEC_ADDR     (__MM_DCII_SUB_BS_START_ADDR - __MM_SUBT_ATSC_SEC_LEN)
#define __MM_SEE_DBG_MEM_ADDR      ( __MM_SUBT_ATSC_SEC_ADDR - __MM_DBG_MEM_LEN)

// for jpeg decoder memmap
#define __MM_FB0_Y_LEN          (1920*1088+1024)//(736*576+512)    //for high definition jpg decode
#define __MM_FB1_Y_LEN          __MM_FB0_Y_LEN
#define __MM_FB2_Y_LEN          __MM_FB0_Y_LEN

#define __MM_FB0_C_LEN          (__MM_FB0_Y_LEN/2)
#define __MM_FB1_C_LEN          __MM_FB0_C_LEN
#define __MM_FB2_C_LEN          __MM_FB0_C_LEN

#define __MM_FB3_Y_LEN          (736*576+1024)
#define __MM_FB3_C_LEN          (__MM_FB3_Y_LEN/2)
#define __MM_FB4_Y_LEN           __MM_FB3_Y_LEN
#define __MM_FB4_C_LEN			__MM_FB3_C_LEN
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

#ifdef SAT2IP_SUPPORT
    #define __MM_MP_BUFFER_LEN            (__MM_PVR_VOB_BUFFER_LEN+__MM_NIM_BUFFER_LEN+__MM_MEDIA_PROV_BUFFER_LEN)
#else
	#define __MM_MP_BUFFER_LEN            (__MM_PVR_VOB_BUFFER_LEN+__MM_NIM_BUFFER_LEN)
#endif
#define __MM_MP_BUFFER_ADDR            __MM_PVR_VOB_BUFFER_ADDR


//end of Private mem map

#ifdef SEE_CPU
#define __MM_DBG_MEM_ADDR __MM_SEE_DBG_MEM_ADDR
#else
#define __MM_DBG_MEM_ADDR __MM_CPU_DBG_MEM_ADDR
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR



#endif //end of 128M config

#define __MM_VIDEO_FILE_BUF_ADDR    __MM_MP_BUFFER_ADDR
#define __MM_VIDEO_FILE_BUF_LEN     __MM_MP_BUFFER_LEN

#endif


