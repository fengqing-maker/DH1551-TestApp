/*****************************************************************************
*This file contains the memory map of C3702, if need modify the memory space 
after NIM_BUFFER, should also sync the modification to sys_config_3702.h in see
*****************************************************************************/
#ifndef __SYS_MEM_MAP_H
#define __SYS_MEM_MAP_H

#if ( SYS_SDRAM_SIZE == 2 )

#elif ( SYS_SDRAM_SIZE == 4 )

#elif (SYS_SDRAM_SIZE == 16)

#elif (SYS_SDRAM_SIZE == 32)

#elif (SYS_SDRAM_SIZE == 64)

#elif (SYS_SDRAM_SIZE >= 128)
#ifndef DRAM_SPLIT
//not support
#else //#ifndef DRAM_SPLIT
#ifndef VFB_SUPPORT
//not support
#else// VFB_SUPPORT
//AS or ACS
/* memory mapping

== limitations
1. AVC and MPEG2 decoder both use about 30MB memory, MPEG2 requires one 32MB segment,
    so we put decoder buffer between [64MB, 96MB], start from 96MB and go down.
2. DMX dma buffer should under same 8M segment.
    __MM_DMX_AVP_START_ADDR, and __MM_DMX_REC_START_ADDR, must under same 8M segment,
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

#define __MM_SHARED_MEM_LEN      1024

#define __MM_SEE_MP_BUF_LEN      0//0x00900000    //9M
#ifdef SD_PVR
	#define __MM_PRIVATE_SHARE_LEN	0x01700000  //24M
	#define __MM_TTXSUBT_S_LEN      0x00300000
#else
	#define __MM_PRIVATE_SHARE_LEN	0x01200000//0x01100000//0x01700000//0x02000000//0x01e00000	//30M
	#define __MM_TTXSUBT_S_LEN      0
#endif
#define __MM_VOID_BUFFER_LEN	0//0x00200000	//2M
	
#define __MM_PRIVATE_LEN        (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

/*******************************************************NIM BUFFER LEN************************************************************/
#ifdef DVBC_SUPPORT
#ifdef J83B_QAM_BUFFER_DISABLE
#define __MM_NIM_DVBC_BUFFER_LEN         0x0 //Paul 20180802  removed 
#else
#define __MM_NIM_DVBC_BUFFER_LEN         0x200000//2M  
#endif
#else
#define __MM_NIM_DVBC_BUFFER_LEN         0x0
#endif

#ifdef DVBT2_SUPPORT
#define __MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN         0x400000//4M
#define __MM_NIM_DVBT2_DJB_BUFFER_LEN                0x96000//600K
#else 
#define __MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN         0x0
#define __MM_NIM_DVBT2_DJB_BUFFER_LEN                0x0
#endif
#define __MM_NIM_DVBT2_BUFFER_LEN (__MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN + __MM_NIM_DVBT2_DJB_BUFFER_LEN)

#define __MM_NIM_BUFFER_LEN  (__MM_NIM_DVBT2_BUFFER_LEN + __MM_NIM_DVBC_BUFFER_LEN)


/*************************FSC BUFFER*******************/
#ifdef FSC_SUPPORT
    #ifdef FSC_SHARE_WITH_PVR            
    #define __MM_DMX_MAIN_BLK_LEN     ((47*1024)*87)// should align with 188*16//(0x400000)
    #else
    #define __MM_DMX_MAIN_BLK_LEN     ((47*1024)*60)
    #endif 

    #ifdef FSC_DMA_BUFFER_CACHE
    #define FSC_CACHE_BUFFER_PART1_LEN     (__MM_DMX_MAIN_BLK_LEN*2) 
    #else
    #define FSC_CACHE_BUFFER_PART1_LEN     (__MM_DMX_MAIN_BLK_LEN*1)
    #endif
#else
    #define __MM_DMX_MAIN_BLK_LEN       0
    #define FSC_CACHE_BUFFER_PART1_LEN  0
#endif

#ifndef SD_PVR
    #define AVC_VBV_LEN        0x400000 //for CI+, must use 4MB. if this size is set to 0x200000, vbv buffer overflow could happen in 20061007d_0.ts
#else
    #define AVC_VBV_LEN        0x180000
#endif

#define HEVC_VBV_LEN            0x400000

#ifndef SD_PVR
#define __MM_VBV_LEN            0x400000
#else
#define __MM_VBV_LEN            0x12C000//(HD = 8*SD > 4*SD)
#endif

#if (HEVC_VBV_LEN <= __MM_VBV_LEN && AVC_VBV_LEN<=__MM_VBV_LEN)
#define VBV_MAX_LEN     __MM_VBV_LEN
#elif (HEVC_VBV_LEN<=__MM_VBV_LEN)
#define VBV_MAX_LEN     AVC_VBV_LEN
#else
#define VBV_MAX_LEN     HEVC_VBV_LEN
#endif

#define SND_DMA_BUFFER_LEN 0xF0000//1M
/************************************************************PVR BUFFER LEN*********************************************************/
#ifdef SD_PVR
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(75*2)+0x1000- __MM_NIM_BUFFER_LEN)//0x88a800//0x6fb000
#else
    #ifdef SAT2IP_SUPPORT
        #define __MM_MEDIA_PROV_BUFFER_LEN     0x400000
    #else
        #define __MM_MEDIA_PROV_BUFFER_LEN     0
    #endif
    #ifdef _AUI_
        /*As the MP module is sharing memory with PVR module, and the memory of 
        MP module will allocate 10M to SBM which is used to cache data of video file 
        in driver, and as the memory size of SBM can just use 6M to ensure the video 
        file play success, so the memory size of MP module can be reduced by 4M, 
        that is, the memory size of PVR module can be reduced by 4M.The heap space 
        of aui version will increase 4M.*/
                    
        /*the DMX module share its memory with media player module, 
        which can increase 3.23M memory size of MP module. As the MP module 
        needs a lot of memory, the PVR module is also share its memory with MP 
        module. As the DMX module dedicates 3.23M to MP module, the PVR module 
        can reduce the dedication of 3.23M. The heap space of aui version will increase 3.23M*/

#ifdef PVR_SIZE_REDUCE    //Reduct to 0x930000
           #define    __MM_PVR_VOB_BUFFER_LEN (((47*1024)*(200)+0x2000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_NIM_BUFFER_LEN - __MM_DMX_MAIN_BLK_LEN)
#else
            // AUI demo default size: 0x00d6a4a0
			#define __MM_PVR_VOB_BUFFER_LEN ((47*1024)*(220)+0x2000)
#endif                                                                                 
	#else
		//#define __MM_PVR_VOB_BUFFER_LEN (((47*1024)*(150*3)+0x1000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_NIM_BUFFER_LEN - FSC_CACHE_BUFFER_PART1_LEN)
        #define __MM_PVR_VOB_BUFFER_LEN (((47*1024)*(200*3)+0x1000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_NIM_BUFFER_LEN - FSC_CACHE_BUFFER_PART1_LEN - SND_DMA_BUFFER_LEN - VBV_MAX_LEN)	

	#endif
#endif

/************************************************************DECODER BUFFER*************************************************************/
#define __MM_FB_LEN_DEVIDED        0X32A000//(HD:1920X1152X1.5)
#ifndef SD_PVR
    #ifdef VIDEO_DEBLOCKING_SUPPORT
	#define __MM_FB_LEN			    0x10D8800//0x10CF200//0x19c6200
    #else
	#define __MM_FB_LEN			    0xddb800//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
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

#define EXTRA_DV_FB_SIZE 0x3C00
#define ONE_DV_FB_SIZE (((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4) + EXTRA_DV_FB_SIZE)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#ifndef SD_PVR
#define AVC_FB_LEN		ONE_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0x1700000

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN   0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0xb00000
#endif

#define AVC_MV_LEN		ONE_MV_SIZE*(5+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#else
#define const_frm_num   5
#define AVC_FB_LEN		ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN		ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#endif //end of SD_PVR
#define AVC_MB_COL_LEN		0x18000 //0x11000
#else
#ifndef SD_PVR
#define AVC_FB_LEN      ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN   0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#endif

#define AVC_MV_LEN      ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x15000
#else
#define const_frm_num   5
#define AVC_FB_LEN      ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN      ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x18000 // 0x11000 will cause overflow
#endif //end of SD_PVR
#endif // end of DYNAMIC_RESOLUTION_SUPPORT

#define AVC_MB_NEI_LEN        0xf000
#define AVC_CMD_QUEUE_LEN   0x10000 //In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
#undef  AVC_LAF_RW_BUF_LEN
//#define AVC_LAF_RW_BUF_LEN ((MAX_MB_WIDTH*MAX_MB_HEIGHT)*32*2*2)
#define AVC_LAF_RW_BUF_LEN (((((MAX_MB_WIDTH*MAX_MB_HEIGHT)*48*2)+1023)&0x0ffffc00)*2)

//#define AVC_LAF_FLAG_BUF_LEN (0xc00*21)
#define AVC_LAF_FLAG_BUF_LEN (0xc00*22) //when enable dual output, we need 1 more laf buffer

#define HEVC_CMD_QUEUE_LEN      0x20000
#define HEVC_EP_QUEUE_LEN       0x20000
#define HEVC_PICTURE_SYNTAX_LEN 0x5000

#define HEVC_FB_LEN             0x2020000//0x1820000//0x1B24000//0x1807E00
#ifdef  HEVC_8BIT_MODE
#undef HEVC_FB_LEN
#define HEVC_FB_LEN             0x1820000      //8bit hevc!
#endif

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define HEVC_DVIEW_LEN          0
#else
#define HEVC_DVIEW_LEN          0x53ac00
#endif

#define HEVC_MV_LEN             0x100000
#define HEVC_MB_NEI_LEN         0xB000
#define HEVC_LAF_LEN            0//0x18F000
#define HEVC_INNER_ES_LEN       0x300000 //max:0x733334
#define HEVC_INNER_AUX_LEN      0x39000 

#ifdef HEVC_DISABLE
#undef HEVC_VBV_LEN           
#undef HEVC_CMD_QUEUE_LEN     
#undef HEVC_EP_QUEUE_LEN      
#undef HEVC_PICTURE_SYNTAX_LEN
#undef HEVC_FB_LEN            
#undef HEVC_DVIEW_LEN         
#undef HEVC_MV_LEN            
#undef HEVC_MB_NEI_LEN        
#undef HEVC_LAF_LEN           
#undef HEVC_INNER_ES_LEN      
#undef HEVC_INNER_AUX_LEN   

#define HEVC_VBV_LEN            0
#define HEVC_CMD_QUEUE_LEN      0
#define HEVC_EP_QUEUE_LEN       0
#define HEVC_PICTURE_SYNTAX_LEN 0
#define HEVC_FB_LEN             0
#define HEVC_DVIEW_LEN          0
#define HEVC_MV_LEN             0
#define HEVC_MB_NEI_LEN         0
#define HEVC_LAF_LEN            0
#define HEVC_INNER_ES_LEN       0
#define HEVC_INNER_AUX_LEN      0
#endif //#ifdef HEVC_DISABLE
/*****************************************OSD ,DMX,TTX,*********************************************************************************/

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
#ifndef SD_PVR
#ifdef _AUI_
#define __MM_OSD1_LEN           (1280*720*4)//(1280*720*2)//(1280*720*4)

#else
#define __MM_OSD1_LEN           (1280*720*2)//(1280*720*4)
#endif
#define __MM_OSD2_LEN            (1920*1080)
#define __MM_OSD_SEE_LEN         (1920*1080)
#else
#ifdef _AUI_
#define __MM_OSD1_LEN           (1280*720*4)//(1008 * 640 * 2 + 256)
#else
#define __MM_OSD1_LEN           (1008 * 640 * 2 + 256)
#endif
#define __MM_OSD2_LEN            (720*576)
#define __MM_OSD_SEE_LEN         (720*576)
#endif

#ifdef OSD2_DISABLE
#undef __MM_OSD2_LEN
#define __MM_OSD2_LEN   0
#endif

// CNX
#if 1//def _AUI_
//AUI project share buffer with __MM_OSD_BK_ADDR2 which configured for SEE TTX/SUBT,
// But now it is no used anymore
#define AD_SEE_OSD2_SHARE_BUFFER
#endif

#ifdef AD_SEE_OSD2_SHARE_BUFFER
#define __MM_AD_DECA_MEM_LEN 0xF0000
#define __MM_AD_SND_MEM_LEN  0x34200
#else
#define __MM_AD_DECA_MEM_LEN 0
#define __MM_AD_SND_MEM_LEN 0
#endif


//#define OSD_VSRC_MEM_MAX_SIZE     0x400000    //300*1024
/*Close the macro, __MM_OSD_VSRC_MEM_ADDR, which is used to auxiliary drawing in OSD
 layer. As the aui do not use this but the GE to auxiliary drawing, closing this macro
 in aui version has no effect for aui, and the heap space of aui will increase 1.25M*/
#ifdef _AUI_
    #ifdef _C1800A_DVT_TEST_
    #define OSD_VSRC_MEM_MAX_SIZE     0x140000    //300*1024
    #else
    #define OSD_VSRC_MEM_MAX_SIZE     0//0x140000    //300*1024
    #endif
#else
#define OSD_VSRC_MEM_MAX_SIZE     0x140000    //300*1024
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
#define __MM_DMX_REC_LEN            (__MM_DMX_VIDEO_LEN)

#ifdef FSC_SUPPORT
#ifdef FSC_DMA_BUFFER_CACHE
//Case 1) use dma buffer to cache fsc data
#define __MM_DMX_BLK_BUF_LEN        0xbc000
#define __MM_DMX_SEE_BLK_BUF_LEN    0xbc000

#define DMX_DMA_BUFFER_LEN          __MM_DMX_MAIN_BLK_LEN
#if(DMX_DMA_BUFFER_LEN < __MM_DMX_AVP_LEN)
    #error "DMX_DMA_BUFFER_LEN too small"
#endif
#undef __MM_DMX_REC_LEN
#undef __MM_DMX_AVP_LEN
#define __MM_DMX_REC_LEN            DMX_DMA_BUFFER_LEN
#define __MM_DMX_AVP_LEN            DMX_DMA_BUFFER_LEN

#define __MM_FSC_BUFFER_LEN         (__MM_DMX_REC_LEN*1+1024)
#else
//Case 2) Use the SW (DMX task)to cache
#define __MM_DMX_BLK_BUF_LEN        __MM_DMX_MAIN_BLK_LEN
#define __MM_DMX_SEE_BLK_BUF_LEN    0xbc000

#define DMX_DMA_BUFFER_LEN          __MM_DMX_AVP_LEN
#define __MM_DMX_REC_LEN		    (__MM_DMX_AVP_LEN)
#define __MM_FSC_BUFFER_LEN         (__MM_DMX_MAIN_BLK_LEN*2 + __MM_DMX_REC_LEN*1+1024)
#endif
#else
//Case 3) Normal, and NO FSC.
#define __MM_DMX_BLK_BUF_LEN        0xbc000
#define __MM_DMX_SEE_BLK_BUF_LEN    __MM_DMX_BLK_BUF_LEN
#define __MM_FSC_BUFFER_LEN         0
#endif


/*The macros, __MM_SUB_BS_START_ADDR, __MM_SUB_HW_DATA_ADDR, 
__MM_SUB_PB_START_ADDR, __MM_DCII_SUB_BS_START_ADDR,
__MM_SUBT_ATSC_SEC_ADDR, of SUBTITLE are not used by aui, so cloing 
these macros in aui has no eddect for aui, and the heap space of aui will increase 0.697M*/
#ifdef _AUI_
#define __MM_SUB_BS_LEN            0//0xA000 //0X2800
#else
#define __MM_SUB_BS_LEN            0xA000
#endif

#ifdef HD_SUBTITLE_SUPPORT
/*The macros, __MM_SUB_BS_START_ADDR, __MM_SUB_HW_DATA_ADDR, 
__MM_SUB_PB_START_ADDR, __MM_DCII_SUB_BS_START_ADDR,
__MM_SUBT_ATSC_SEC_ADDR, of SUBTITLE are not used by aui, so closing 
these macros in aui has no eddect for aui, and the heap space of aui will increase 0.697M*/
	#ifdef _AUI_
    #define __MM_SUB_PB_LEN            0//0xA0000 //0x50000//0X19000(1920X340 for hd subt)
	#else
	#define __MM_SUB_PB_LEN            0xA0000 //0x50000//0X19000(1920X340 for hd subt)
	#endif
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
    /*The macros, _MM_TTX_SUB_PAGE_BUF_ADDR, __MM_TTX_P26_NATION_BUF_ADDR, __MM_TTX_P26_DATA_BUF_ADDR, 
	__MM_TTX_BS_START_ADDR, __MM_TTX_PB_START_ADDR of TTX module are not used by aui, so closing these macros
    in aui has no effect for aui. And the heap space of aui will increase 1.28M*/
    #ifdef _AUI_
    #define __MM_TTX_PB_LEN                0//0xCB200 //+80*1040 //0XCA800
    #define __MM_TTX_SUB_PAGE_LEN      0// 0x14500 //80*1040
    #else
    #define __MM_TTX_PB_LEN                0xCB200 //+80*1040 //0XCA800
    #define __MM_TTX_SUB_PAGE_LEN          0x14500 //80*1040
    #endif
    #else
    #define __MM_TTX_PB_LEN                0xCA800 //+80*1040 //
    #define __MM_TTX_SUB_PAGE_LEN       0 //80*1040
    #endif
    #ifdef SUPPORT_PACKET_26
    /*The macros, _MM_TTX_SUB_PAGE_BUF_ADDR, __MM_TTX_P26_NATION_BUF_ADDR, __MM_TTX_P26_DATA_BUF_ADDR, 
	__MM_TTX_BS_START_ADDR, __MM_TTX_PB_START_ADDR of TTX module are not used by aui, so closing these macros
    in aui has no effect for aui. And the heap space of aui will increase 1.28M*/
    #ifdef _AUI_
    #define __MM_TTX_P26_NATION_LEN     0//0x61A80 //25*40*400
    #define __MM_TTX_P26_DATA_LEN       0//0x3E8 //25*40
    #else
    #define __MM_TTX_P26_NATION_LEN     0x61A80 //25*40*400
    #define __MM_TTX_P26_DATA_LEN       0x3E8 //25*40
    #endif
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
#ifdef _AUI_
#define __MM_ATSC_CC_PB_LEN  0//(__MM_ATSC_CC_PB_RECT_LEN+OSD_CC_WIDTH*4*CC_CHAR_HEIGHT)
#define __MM_ATSC_CC_BS_LEN  0//0x1c00 // 1K Word CC Data, 1K Byte CC Field, 2K Word DTVCC Data
#else
#define __MM_ATSC_CC_PB_LEN  (__MM_ATSC_CC_PB_RECT_LEN+OSD_CC_WIDTH*4*CC_CHAR_HEIGHT)
#define __MM_ATSC_CC_BS_LEN  0x1c00 // 1K Word CC Data, 1K Byte CC Field, 2K Word DTVCC Data
#endif
#else
#undef __MM_ATSC_CC_PB_LEN
#undef __MM_ATSC_CC_BS_LEN
#define __MM_ATSC_CC_PB_LEN	0
#define __MM_ATSC_CC_BS_LEN	0
#endif

#define __MM_USB_DMA_LEN                0    // 0x10FFFF currently not use
#ifdef AUI
// AUI project don't use this buffer
#define __MM_EPG_BUFFER_LEN             0
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0
#else
#define __MM_EPG_BUFFER_LEN             0x100000
#define __MM_AUTOSCAN_DB_BUFFER_LEN     0x100000
#endif

#ifdef NETWORK_SUPPORT
#define STO_PROTECT_BY_MUTEX
#define __MM_LWIP_MEM_LEN               0x10000
#define __MM_LWIP_MEMP_LEN              0xd1f00//0xce200
#define __MM_XML_MEMP_LEN                0x100000 // 5M
#else
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN                0
#endif

#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_LEN        0x8FC0
#define __MM_ISDBTCC_PB_LEN        0x7E900
#else
#define __MM_ISDBTCC_BS_LEN         0
#define __MM_ISDBTCC_PB_LEN         0
#endif

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#define __MM_VCAP_FB_SIZE               (736*576*2*4)
#else
#define __MM_VCAP_FB_SIZE               0
#endif

#ifndef HEVC_DISABLE
#define __MM_FRAME_BACKUP_LEN 0x408000
#else
#define __MM_FRAME_BACKUP_LEN 0x308000
#endif

#define __MM_DBG_MEM_LEN   0x4000

/*************************************************MEMORY MAP ADDR*************************************************************/

#ifdef SD_PVR
    #define __MM_HIGHEST_ADDR   0xa4000000        //64M    
#else
    #define __MM_HIGHEST_ADDR   0xa8000000        //128M
#endif


#define __MM_TTXSUB_S_TOP_ADDR    (__MM_HIGHEST_ADDR)
#define __MM_TTXSUB_S_START_ADDR  (__MM_TTXSUB_S_TOP_ADDR - __MM_TTXSUBT_S_LEN)
#define __MM_VOID_BUFFER_ADDR    (__MM_TTXSUB_S_START_ADDR - __MM_VOID_BUFFER_LEN)    //126M or 114M


#define __MM_SHARE_BASE_ADDR     (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)

#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR        (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)     //96M

#if (defined _CAS9_VSC_ENABLE_ || defined _C0700A_VSC_ENABLE_)
	#define __MM_VSC_CODE_START_ADDR	__MM_PRIVATE_ADDR
	#define __MM_VSC_DATA_START_ADDR (__MM_VSC_CODE_START_ADDR+__MM_VSC_CODE_LEN)
#endif

#ifdef SD_PVR
    #define __MM_MAIN_TOP_ADDR        0xa2600000//0xa2000000        //36MB

    #define __MM_OSD_VSRC_MEM_ADDR    (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE) 
    #define __MM_NIM_BUFFER_ADDR            (__MM_OSD_VSRC_MEM_ADDR - __MM_NIM_BUFFER_LEN)

    #ifdef _MHEG5_V20_ENABLE_
        #define __MM_MHEG5_BUFFER_ADDR      (__MM_NIM_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
        #define __MM_DMX_AVP_START_ADDR     ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
    #else
        #define __MM_DMX_AVP_START_ADDR     ((__MM_NIM_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
    #endif
    #define __MM_DMX_REC_START_ADDR        ((__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN) & 0XFFFFFFF0)
    #define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)

    #define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)
    #define __MM_BUF_PVR_TOP_ADDR       __MM_EPG_BUFFER_START
    #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    
    #define __MM_FB_TOP_ADDR        (__MM_PVR_VOB_BUFFER_ADDR&0XFFFFFC00)     //32MB align
#else
    #define __MM_MAIN_TOP_ADDR      0xa6E00000//0xa6F00000//0xa6900000//0xa6000000        //96MB
    #define __MM_SND_DMA_BUFFER_ADDR ((__MM_MAIN_TOP_ADDR - SND_DMA_BUFFER_LEN)&0XFFFF0000)//64k align

    //add
    #define __MM_VBV_START_ADDR         ((__MM_SND_DMA_BUFFER_ADDR - __MM_VBV_LEN)&0XFFFF0000)
    #define AVC_VBV_ADDR                ((__MM_SND_DMA_BUFFER_ADDR - AVC_VBV_LEN)&0XFFFF0000)   //64k bytes alignment
    #define HEVC_VBV_ADDR               ((__MM_SND_DMA_BUFFER_ADDR - HEVC_VBV_LEN)&0XFFFF0000) //64k bytes alignment
    
    #if (AVC_VBV_ADDR <= __MM_VBV_START_ADDR && AVC_VBV_ADDR<=HEVC_VBV_ADDR)
    #define VDEC_PRIVATE_START_ADDR     AVC_VBV_ADDR
    #elif (HEVC_VBV_ADDR<=__MM_VBV_START_ADDR)
    #define VDEC_PRIVATE_START_ADDR     HEVC_VBV_ADDR
    #else
    #define VDEC_PRIVATE_START_ADDR     __MM_VBV_START_ADDR
    #endif

    #define __MM_VCAP_FB_ADDR       ((VDEC_PRIVATE_START_ADDR - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    //#define __MM_VCAP_FB_ADDR       ((__MM_MAIN_TOP_ADDR - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment


    #define __MM_FB_TOP_ADDR        __MM_VCAP_FB_ADDR//0xa6000000        //96MB
#endif

#ifdef SD_PVR
    #if(__MM_MAIN_TOP_ADDR != __MM_PRIVATE_ADDR)
    #error "__MM_PRIVATE_ADDR address error"
    #endif
#endif

// for satcodx memmap
#define __MM_DVW_START_ADDR         ((__MM_FB2_C_START_ADDR - 0X25FA0)&0XFFFFFFF0)

// MPEG2
#define __MM_MAF_START_ADDR         ((__MM_FB_TOP_ADDR - __MM_MAF_LEN) & 0xFFFFFC00)
#define MPEG2_BUF_START_ADDR        ((__MM_MAF_START_ADDR - __MM_FB_LEN) & 0xFFFFFc00)

// AVC
#ifndef AVC_SUPPORT_UNIFY_MEM
#define AVC_MV_ADDR                 ((__MM_FB_TOP_ADDR - AVC_MV_LEN)&0xffffff00)                //256 bytes alignment
#define AVC_MB_COL_ADDR             ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)                 //256 bytes alignment
#define AVC_MB_NEI_ADDR             ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)             //256 bytes alignment
#define AVC_LAF_RW_BUF_ADDR         ((AVC_MB_NEI_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)         //1024 bytes alignment
#define AVC_CMD_QUEUE_ADDR          ((AVC_LAF_RW_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
#define AVC_LAF_FLAG_BUF_ADDR       ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)    //1024 bytes alignment
#define AVC_DVIEW_ADDR              ((AVC_LAF_FLAG_BUF_ADDR -  AVC_DVIEW_LEN)&0xfffffe00)       //512 bytes alignment
#define AVC_BUF_START_ADDR          ((AVC_DVIEW_ADDR -  AVC_FB_LEN)&0xfffffe00)                 //512 bytes alignment
#else
#define AVC_MB_COL_ADDR 		    ((__MM_FB_TOP_ADDR - AVC_MB_COL_LEN - AVC_MV_LEN -AVC_CMD_QUEUE_LEN)&0xffffff00)  		//256 bytes alignment
#define AVC_MB_NEI_ADDR 			((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00) 	//256 bytes alignment
#define AVC_BUF_START_ADDR 			((AVC_MB_NEI_ADDR - AVC_MEM_LEN)&0xffffff00)
#define AVC_DVIEW_ADDR 				0
#define AVC_MV_ADDR 				0
#define AVC_LAF_RW_BUF_ADDR			0
#define AVC_LAF_FLAG_BUF_ADDR       0
#define AVC_FB_ADDR					0
#endif

// HEVC
#define HEVC_MV_ADDR                ((__MM_FB_TOP_ADDR - HEVC_MV_LEN)&0xffffff00)       //256 bytes alignment
#define HEVC_MB_NEI_ADDR            ((HEVC_MV_ADDR - HEVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define HEVC_LAF_ADDR               ((HEVC_MB_NEI_ADDR - HEVC_LAF_LEN)&0xfffffc00)    //1024 bytes alignment
#define HEVC_INNER_ES_ADDR          ((HEVC_LAF_ADDR - HEVC_INNER_ES_LEN)&0xfffffc00)
#define HEVC_INNER_AUX_ADDR         ((HEVC_INNER_ES_ADDR - HEVC_INNER_AUX_LEN)&0xfffffc00)
#define HEVC_PICTURE_SYNTAX_BUF_ADDR ((HEVC_INNER_AUX_ADDR - HEVC_PICTURE_SYNTAX_LEN)&0XFFFFFF00)
#define HEVC_EP_QUEUE_BUF_ADDR      ((HEVC_PICTURE_SYNTAX_BUF_ADDR - HEVC_EP_QUEUE_LEN)&0XFFFFFF00)
#define HEVC_CMD_QUEUE_BUF_ADDR     ((HEVC_EP_QUEUE_BUF_ADDR - HEVC_CMD_QUEUE_LEN) & 0XFFFFFC00)
#define HEVC_DVIEW_ADDR             ((HEVC_CMD_QUEUE_BUF_ADDR -  HEVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define HEVC_BUF_START_ADDR         ((HEVC_DVIEW_ADDR -  HEVC_FB_LEN )&0xffff4000)      //16k bytes alignment

#if (MPEG2_BUF_START_ADDR < AVC_BUF_START_ADDR && MPEG2_BUF_START_ADDR < HEVC_BUF_START_ADDR)
#define __MM_FB_BOTTOM_ADDR         MPEG2_BUF_START_ADDR
#elif (HEVC_BUF_START_ADDR < AVC_BUF_START_ADDR)
#define __MM_FB_BOTTOM_ADDR         HEVC_BUF_START_ADDR
#else
#define __MM_FB_BOTTOM_ADDR         AVC_BUF_START_ADDR
#endif

#define __MM_FB_START_ADDR          __MM_FB_BOTTOM_ADDR
#define __MM_FB_ACT_LEN             (__MM_MAF_START_ADDR-__MM_FB_START_ADDR)

#ifdef AVC_SUPPORT_UNIFY_MEM
#undef  AVC_MEM_ADDR
#undef  AVC_MEM_LEN
#define AVC_MEM_ADDR                __MM_FB_BOTTOM_ADDR
#define AVC_MEM_LEN                 ((AVC_MB_NEI_ADDR - AVC_MEM_ADDR)&0xffffff00)
#else /* AVC_SUPPORT_UNIFY_MEM */
#define AVC_FB_ADDR                 __MM_FB_BOTTOM_ADDR
#define AVC_FB_ACT_LEN              (AVC_DVIEW_ADDR-AVC_FB_ADDR)

#define AVC_MEM_LEN                 0   //for compile error
#endif /* AVC_SUPPORT_UNIFY_MEM */

#define HEVC_FB_ADDR                __MM_FB_BOTTOM_ADDR
#define HEVC_FB_ACT_LEN             (HEVC_DVIEW_ADDR-HEVC_FB_ADDR)

//#define __MM_SND_DMA_BUFFER_ADDR ((VDEC_PRIVATE_START_ADDR - SND_DMA_BUFFER_LEN)&0XFFFF0000)//64k align

#ifndef SD_PVR
    #define __MM_NIM_BUFFER_ADDR            (__MM_FB_BOTTOM_ADDR - __MM_NIM_BUFFER_LEN)
    //#define __MM_NIM_BUFFER_ADDR            (__MM_SND_DMA_BUFFER_ADDR - __MM_NIM_BUFFER_LEN)

    #ifdef FSC_SUPPORT
        #ifdef FSC_SHARE_WITH_PVR
            #define __MM_BUF_PVR_TOP_ADDR           __MM_NIM_BUFFER_ADDR
            #define __MM_FSC_BUFFER_TOP             ((__MM_BUF_PVR_TOP_ADDR)&0XFF800000)
        #else
            #define __MM_FSC_BUFFER_TOP             __MM_NIM_BUFFER_ADDR
            #define __MM_BUF_PVR_TOP_ADDR           (__MM_FSC_BUFFER_TOP - __MM_FSC_BUFFER_LEN)
        #endif
    #else
        #define __MM_BUF_PVR_TOP_ADDR           __MM_NIM_BUFFER_ADDR
    #endif
    
    #ifdef SAT2IP_SUPPORT//MEDIA_PROVIDER_USE_RING_BUFFER
        #define __MM_MEDIA_PROVIDER_BUFFER_ADDR (__MM_BUF_PVR_TOP_ADDR - __MM_MEDIA_PROV_BUFFER_LEN)
        #define __MM_PVR_VOB_BUFFER_ADDR        (__MM_MEDIA_PROVIDER_BUFFER_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #else
        #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #endif

	#define __MM_DMX_REC_START_ADDR			(__MM_PVR_VOB_BUFFER_ADDR - __MM_DMX_REC_LEN)
	#define __MM_DMX_CPU_BLK_ADDR 		 ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #define __MM_DMX_AVP_START_ADDR        ((__MM_DMX_CPU_BLK_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFFC)
	#define __MM_EPG_BUFFER_START       (__MM_DMX_AVP_START_ADDR - __MM_EPG_BUFFER_LEN)

    #define __MM_GE_START_ADDR          ((__MM_EPG_BUFFER_START - __MM_GE_LEN)&0XFFFFFFE0)
    #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFE0)
    #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFE0)
    //#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    #define __MM_OSD_VSRC_MEM_ADDR     ((__MM_OSD_BK_ADDR2_MAIN - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFE0)//((__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFE0)
    #define __MM_LWIP_MEM_ADDR          (__MM_OSD_VSRC_MEM_ADDR - __MM_LWIP_MEM_LEN)
   
#else
    #define __MM_GE_START_ADDR          ((__MM_FB_BOTTOM_ADDR - __MM_GE_LEN)&0XFFFFFFE0)
    #ifdef _M36F_SINGLE_CPU
        // for m36f single cpu mode(only test for ali internal)
        // move osd, vsrc, scap buffer to private buffer base.
        #define __MM_LWIP_MEM_ADDR      (__MM_GE_START_ADDR - __MM_LWIP_MEM_LEN)
    #else
        #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFE0)
        #if (defined(_CAS9_CA_ENABLE_) || defined(_C0200A_CA_ENABLE_) ||defined(_GEN_CA_ENABLE_) ||defined(_BC_CA_ENABLE_))
            #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFE0)
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        #else
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        #endif
        #define __MM_LWIP_MEM_ADDR          (__MM_VCAP_FB_ADDR - __MM_LWIP_MEM_LEN)
     #endif
#endif

#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR            ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)

#ifndef SD_PVR
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
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
#else
//add for TTX_TO_MAIN
#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_TTXSUB_S_TOP_ADDR - __MM_TTX_SUB_PAGE_LEN)
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
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)

#if ( __MM_ISDBTCC_PB_START_ADDR < __MM_TTXSUB_S_START_ADDR)
    #error "TTX ATSC len is bigger than __MM_TTXSUBT_S_LEN"
#endif
#endif

#ifndef SD_PVR
#define __MM_CPU_DBG_MEM_ADDR          (__MM_ISDBTCC_PB_START_ADDR - __MM_DBG_MEM_LEN)
#else
#define __MM_CPU_DBG_MEM_ADDR          (__MM_USB_START_ADDR - __MM_DBG_MEM_LEN)
#endif

#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR
#define __MM_NIM_BUFFER_TOP_ADDR		(__MM_NIM_BUFFER_ADDR + __MM_NIM_BUFFER_LEN)
#define __MM_NIM_DVBT2_BUFFER_ADDR        (__MM_NIM_BUFFER_TOP_ADDR - __MM_NIM_DVBT2_BUFFER_LEN)
#define __MM_NIM_DVBC_BUFFER_ADDR       (__MM_NIM_DVBT2_BUFFER_ADDR - __MM_NIM_DVBC_BUFFER_LEN)


//Allocate FSC buffer, share with PVR
#ifdef FSC_SUPPORT 
    #define __MM_FSC_BUFFER_ADDR    (__MM_FSC_BUFFER_TOP - __MM_FSC_BUFFER_LEN)

    #define __MM_DMX0_DMA_START_ADDR    (__MM_DMX_AVP_START_ADDR)
    #define __MM_DMX1_DMA_START_ADDR    (__MM_DMX_REC_START_ADDR)
    #define __MM_DMX2_DMA_START_ADDR    ((__MM_FSC_BUFFER_TOP - __MM_DMX_REC_LEN)&0XFFFFFFF0)
    //#define __MM_DMX3_DMA_START_ADDR	((__MM_DMX2_DMA_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)

    #define __MM_DMX0_MAIN_BLK_START_ADDR (__MM_DMX_CPU_BLK_ADDR )
    #ifdef FSC_DMA_BUFFER_CACHE
    #define __MM_DMX1_MAIN_BLK_START_ADDR   (__MM_DMX_CPU_BLK_ADDR )
    #define __MM_DMX2_MAIN_BLK_START_ADDR   (__MM_DMX_CPU_BLK_ADDR )
    #else
    #define __MM_DMX1_MAIN_BLK_START_ADDR	((__MM_DMX3_DMA_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #define __MM_DMX2_MAIN_BLK_START_ADDR   ((__MM_DMX1_MAIN_BLK_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #endif
    
#ifdef FSC_DMA_BUFFER_CACHE 
    #if(__MM_DMX2_DMA_START_ADDR < __MM_FSC_BUFFER_ADDR)
    #error "1) __MM_FSC_BUFFER_LEN too small for dmx2"
    #endif
    #if defined(__MM_DMX3_DMA_START_ADDR) && (__MM_DMX3_DMA_START_ADDR < __MM_FSC_BUFFER_ADDR)
    #error "2) __MM_FSC_BUFFER_LEN too small for dmx3"
    #endif
#else
#if(__MM_DMX2_MAIN_BLK_START_ADDR < __MM_FSC_BUFFER_ADDR)
    #error "__MM_FSC_BUFFER_ADDR too small"
#endif
#if(__MM_FSC_BUFFER_ADDR < __MM_PVR_VOB_BUFFER_ADDR)
    #error "PVR no enough buffer to share with fsc"
#endif
#endif
#endif


//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/

#ifdef _DD_SUPPORT
#define __MM_PRIV_DEC_LEN   0x20000
#define __MM_PRIV_DEC_ADDR (__MM_PRIVATE_TOP_ADDR- __MM_PRIV_DEC_LEN)
#else
#define __MM_PRIV_DEC_LEN   0
#define __MM_PRIV_DEC_ADDR (__MM_PRIVATE_TOP_ADDR- __MM_PRIV_DEC_LEN)
#endif

#define __MM_REAL_PRIVATE_TOP_ADDR  __MM_PRIV_DEC_ADDR

#if 0
#define __MM_VBV_START_ADDR         ((__MM_REAL_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define AVC_VBV_ADDR                ((__MM_REAL_PRIVATE_TOP_ADDR - AVC_VBV_LEN)&0XFFFFFF00)   //256 bytes alignment
#define HEVC_VBV_ADDR               ((__MM_REAL_PRIVATE_TOP_ADDR - HEVC_VBV_LEN)&0XFFFFFF00) //256 bytes alignment

#if (AVC_VBV_ADDR <= __MM_VBV_START_ADDR && AVC_VBV_ADDR<=HEVC_VBV_ADDR)
#define VDEC_PRIVATE_START_ADDR     AVC_VBV_ADDR
#elif (HEVC_VBV_ADDR<=__MM_VBV_START_ADDR)
#define VDEC_PRIVATE_START_ADDR     HEVC_VBV_ADDR
#else
#define VDEC_PRIVATE_START_ADDR     __MM_VBV_START_ADDR
#endif
#endif

//add for M3721 ifcp
#define __MM_IFCP_BUFF_LEN    0x80000//0x100000 ///1M
#define __MM_IFCP_BUFF_ADDR   ((__MM_REAL_PRIVATE_TOP_ADDR-__MM_IFCP_BUFF_LEN)&0xFFF00000) // 1M align

//#define __MM_DMX_SEE_BLK_ADDR       ((__MM_REAL_PRIVATE_TOP_ADDR - __MM_DMX_SEE_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_DMX_SEE_BLK_ADDR       ((__MM_IFCP_BUFF_ADDR - __MM_DMX_SEE_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_DMX_SEE_BLK_START_ADDR (__MM_DMX_SEE_BLK_ADDR)

#define __MM_SEE_MP_BUF_ADDR    (__MM_DMX_SEE_BLK_ADDR -  __MM_SEE_MP_BUF_LEN)
#define __MM_FRAME_BACKUP_ADDR  (__MM_SEE_MP_BUF_ADDR - __MM_FRAME_BACKUP_LEN) 

//add
#define __MM_STILL_PICTURE_MEM_LEN    0x44A000
#define __MM_STILL_PICTURE_MEM_ADDR   ((__MM_SEE_MP_BUF_ADDR - __MM_STILL_PICTURE_MEM_LEN)&0xFFFFFFE0)

#define __MM_SEE_OSD2_LEN    (__MM_AD_DECA_MEM_LEN + __MM_AD_SND_MEM_LEN)
//move to main
//#define AVC_CMD_QUEUE_ADDR  ((__MM_SEE_MP_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
//#define AVC_LAF_FLAG_BUF_ADDR   ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
//#define __MM_OSD_BK_ADDR2       ((__MM_SEE_MP_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)//((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)
#define __MM_OSD_BK_ADDR2       ((__MM_FRAME_BACKUP_ADDR - __MM_OSD_SEE_LEN)&0XFFFFFFE0)//((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)


// AD buffer share with __MM_OSD_BK_ADDR2, because in 3505, no ttx/subt in see anymore
#define __MM_AD_DECA_MEM_ADDR            ((__MM_STILL_PICTURE_MEM_ADDR - __MM_AD_DECA_MEM_LEN)&0xFFFFFFE0)
#define __MM_AD_SND_MEM_ADDR            ((__MM_AD_DECA_MEM_ADDR - __MM_AD_SND_MEM_LEN)&0xFFFFFFE0)

#if (__MM_AD_SND_MEM_ADDR < __MM_OSD_BK_ADDR2)
#define __MM_SEE_DBG_MEM_ADDR      ( __MM_AD_SND_MEM_ADDR - __MM_DBG_MEM_LEN)
#else
#define __MM_SEE_DBG_MEM_ADDR      ( __MM_OSD_BK_ADDR2 - __MM_DBG_MEM_LEN)
#endif

// for jpeg decoder memmap
#ifdef SD_PVR
#define __MM_FB0_Y_LEN            (736*576 + 1024)
#define __MM_IMG_FB_Y_LEN        (736*576*2 + 1024)
#define __MM_IMG_FB_C_LEN        (__MM_IMG_FB_Y_LEN/2)
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

#ifdef SD_PVR   
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
    //#define __MM_MP_BUFFER_LEN        (__MM_FB_TOP_ADDR - __MM_TTX_P26_DATA_BUF_ADDR)//(__MM_SEE_MP_BUF_LEN - __MM_FB0_Y_LEN * 3 - __MM_FB0_C_LEN * 3)
    //#define __MM_MP_BUFFER_ADDR        __MM_TTX_P26_DATA_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
#endif

#ifdef SAT2IP_SUPPORT
    #define __MM_MP_BUFFER_LEN            (__MM_PVR_VOB_BUFFER_LEN+__MM_NIM_BUFFER_LEN+__MM_MEDIA_PROV_BUFFER_LEN)
#else
    /*the DMX module share its memory with media player module, 
    which can increase 3.23M memory size of MP module. As the MP module 
    needs a lot of memory, the PVR module is also share its memory with MP 
    module. As the DMX module dedicates 3.23M to MP module, the PVR module 
    can reduce the dedication of 3.23M. The heap space of aui version will increase 3.23M*/
	#ifdef _AUI_        
		#define __MM_MP_BUFFER_LEN			  (__MM_PVR_VOB_BUFFER_LEN+__MM_NIM_BUFFER_LEN + __MM_DMX_REC_LEN + __MM_DMX_BLK_BUF_LEN)        
    #else
		#define __MM_MP_BUFFER_LEN            (__MM_PVR_VOB_BUFFER_LEN+__MM_NIM_BUFFER_LEN)
	#endif
#endif
/*the DMX module share its memory with media player module, 
which can increase 3.23M memory size of MP module. As the MP module 
needs a lot of memory, the PVR module is also share its memory with MP 
module. As the DMX module dedicates 3.23M to MP module, the PVR module 
can reduce the dedication of 3.23M. The heap space of aui version will increase 3.23M*/
#ifdef _AUI_
    #define __MM_MP_BUFFER_ADDR          __MM_DMX_CPU_BLK_ADDR
#else
    #define __MM_MP_BUFFER_ADDR            __MM_PVR_VOB_BUFFER_ADDR
#endif


//end of Private mem map
#ifdef SEE_CPU
#define __MM_DBG_MEM_ADDR __MM_SEE_DBG_MEM_ADDR
#else
#define __MM_DBG_MEM_ADDR __MM_CPU_DBG_MEM_ADDR
#endif

#define __MM_HEAP_TOP_ADDR      __MM_DBG_MEM_ADDR

#endif //end of VFB_SUPPORT
#endif //end of DRAM_SPLIT

#elif (SYS_SDRAM_SIZE > 256)
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
#define __MM_FB_LEN			    0x10D8800//0x10CF200//0x19c6200
#else
#define __MM_FB_LEN			    0xddb800//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
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

#define EXTRA_DV_FB_SIZE 0x3C00
#define ONE_DV_FB_SIZE ((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4 + EXTRA_DV_FB_SIZE)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#ifndef SD_PVR
#define AVC_FB_LEN		ONE_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0xb00000
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
#define AVC_FB_LEN        ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
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

#define AVC_MB_NEI_LEN        0xf000
#define AVC_CMD_QUEUE_LEN     0x10000 //In allegro test stream, this length could be bigger than 128k, however, in realistic, 0x10000 should be enough
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
#define __MM_OSD2_LEN            (1920*1080)

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
#define __MM_LWIP_MEMP_LEN              0xd1f00//0xce200
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
#define __MM_HIGHEST_ADDR              0xb0000000//0xa8000000        //128
#define __MM_VOID_BUFFER_ADDR        (__MM_HIGHEST_ADDR - __MM_VOID_BUFFER_LEN)
#define __MM_FB_TOP_ADDR            __MM_VOID_BUFFER_ADDR    //64MB

#ifdef _DD_SUPPORT
#define __MM_PRIV_DEC_LEN   __MM_VOID_BUFFER_LEN
#define __MM_PRIV_DEC_ADDR  __MM_VOID_BUFFER_ADDR
#endif


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
#define AVC_MV_ADDR 		((AVC_DVIEW_ADDR - AVC_MV_LEN)&0xffffff00)  		//256 bytes alignment
#define AVC_MB_COL_ADDR     ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR     ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_CMD_QUEUE_ADDR  		((AVC_MB_NEI_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)  	//256 bytes alignment
#define AVC_LAF_FLAG_BUF_ADDR 		((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define AVC_LAF_RW_BUF_ADDR   ((AVC_LAF_FLAG_BUF_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#else

#define AVC_VBV_ADDR                 ((__MM_FB_TOP_ADDR - AVC_VBV_LEN )&0xffffff00)     //256 bytes alignment
#define AVC_CMD_QUEUE_ADDR          ((AVC_VBV_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
#define AVC_MB_COL_ADDR 		    ((AVC_CMD_QUEUE_ADDR - AVC_MB_COL_LEN - AVC_MV_LEN)&0xffffff00)  		//256 bytes alignment
//#define AVC_MB_COL_ADDR 			((AVC_CMD_QUEUE_ADDR - AVC_MB_COL_LEN)&0xffffff00) 		//256 bytes alignment
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
#define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)

#define __MM_DMX_REC_START_ADDR        ((__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)

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
#define __MM_OSD_BK_ADDR2       ((__MM_GE_START_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)
#define __MM_OSD_BK_ADDR1              ((__MM_OSD_BK_ADDR2 - __MM_OSD1_LEN)&0XFFFFFFE0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#define __MM_OSD_VSRC_MEM_ADDR        ((__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFE0)

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
#ifndef VFB_SUPPORT
//gen ca
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

/*************************************************SHARE MEMORY LEN********************************************************/
#define __MM_SHARED_MEM_LEN      1024

#ifdef HW_SECURE_ENABLE
    #define __MM_SEE_MP_BUF_LEN      0x0
    #ifdef SD_PVR
		#define __MM_PRIVATE_SHARE_LEN	0x01700000  //24M
		#define __MM_TTXSUBT_S_LEN      0x00300000
    #else
		#define __MM_PRIVATE_SHARE_LEN	0x02000000//0x01e00000	//30M
		#define __MM_TTXSUBT_S_LEN      0
    #endif
	#define __MM_VOID_BUFFER_LEN	0//0x00200000	//2M
	
#else
#ifdef _C0200A_CA_ENABLE_//20140623 evan.wu for C0200A MemMap
	#define __MM_SEE_MP_BUF_LEN  	0
	#define __MM_PRIVATE_SHARE_LEN	0x01e00000	//30M
	#define __MM_VOID_BUFFER_LEN	0x00200000	//2M
#else
	#define __MM_SEE_MP_BUF_LEN      0
#ifdef SD_PVR
	#define __MM_PRIVATE_SHARE_LEN	0x01700000
#else
	#define __MM_PRIVATE_SHARE_LEN	0x02000000//0x01e00000	//30M
#endif
	#define __MM_VOID_BUFFER_LEN	0//0x00200000	//2M
#endif
#ifdef SD_PVR
	#define __MM_TTXSUBT_S_LEN      0x00300000
#else
    #define __MM_TTXSUBT_S_LEN  0   //2M
#endif
#endif

#define __MM_PRIVATE_LEN        (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

/*******************************************************NIM BUFFER LEN************************************************************/
#ifdef DVBC_SUPPORT
#define __MM_NIM_DVBC_BUFFER_LEN         0x200000//2M
#else
#define __MM_NIM_DVBC_BUFFER_LEN         0x0
#endif


#ifdef DVBT2_SUPPORT
#define __MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN         0x400000//4M
#define __MM_NIM_DVBT2_DJB_BUFFER_LEN                0x96000//600K
#else 
#define __MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN         0x0
#define __MM_NIM_DVBT2_DJB_BUFFER_LEN                0x0
#endif
#define __MM_NIM_DVBT2_BUFFER_LEN (__MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN + __MM_NIM_DVBT2_DJB_BUFFER_LEN)

#define __MM_NIM_BUFFER_LEN  (__MM_NIM_DVBT2_BUFFER_LEN + __MM_NIM_DVBC_BUFFER_LEN)

/************************************************************PVR BUFFER LEN*********************************************************/
#ifdef DVR_PVR_SUPPORT
#ifdef _MHEG5_V20_ENABLE_ //MHEG5 enable, reserve 8MB
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(180*3)+0x1000- __MM_NIM_BUFFER_LEN)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE        0X800000
#else
    #ifdef SD_PVR
        #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(75*2)+0x1000- __MM_NIM_BUFFER_LEN)//0x88a800//0x6fb000
    #else
        #ifdef SAT2IP_SUPPORT
            #define __MM_MEDIA_PROV_BUFFER_LEN     0x400000
        #else
            #define __MM_MEDIA_PROV_BUFFER_LEN     0
        #endif
        
        #ifdef FSC_SUPPORT
            #define __MM_DMX_MAIN_BLK_LEN     ((47*1024)*87)// should align with 188*16//(0x400000) 
        #else
            #define __MM_DMX_MAIN_BLK_LEN     0
        #endif
        
		#ifdef _M3503B_
		#define __MM_PVR_VOB_BUFFER_LEN                (((47*1024)*(160*3)+0x1000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_DLNA_BUFFER_LEN - __MM_NIM_BUFFER_LEN) //
		#else
		#define __MM_PVR_VOB_BUFFER_LEN (((47*1024)*(160*3)+0x1000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_NIM_BUFFER_LEN - __MM_DMX_MAIN_BLK_LEN)
    	#endif
	#endif
#endif
#else
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(120+75 * 2)+0x1000 - __MM_NIM_BUFFER_LEN)
    #define MHEG5_MEMORY_ALLOC_REGION_SIZE 0
#endif

/************************************************************DECODER BUFFER*************************************************************/
#define __MM_FB_LEN_DEVIDED        0X32A000//(HD:1920X1152X1.5)
#ifndef SD_PVR
    #ifdef VIDEO_DEBLOCKING_SUPPORT
	#define __MM_FB_LEN			    0x10D8800//0x10CF200//0x19c6200
    #else
	#define __MM_FB_LEN			    0xddb800//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
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

#define EXTRA_DV_FB_SIZE 0x3C00
#define ONE_DV_FB_SIZE (((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4) + EXTRA_DV_FB_SIZE)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#ifndef SD_PVR
#define AVC_FB_LEN		ONE_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0x1700000

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN   0
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
#define AVC_FB_LEN        ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN   0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#endif

#define AVC_MV_LEN        ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x15000
#else
#define const_frm_num   5
#define AVC_FB_LEN        ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN        ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN    0x18000 // 0x11000 will cause overflow
#endif
#endif

#define AVC_MB_NEI_LEN        0xf000
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

#ifndef SD_PVR
#define HEVC_VBV_LEN            0x400000
#define HEVC_CMD_QUEUE_LEN      0x20000
#define HEVC_EP_QUEUE_LEN       0x20000
#define HEVC_PICTURE_SYNTAX_LEN 0x5000

#define HEVC_FB_LEN             0x2020000//0x1820000//0x1B24000//0x1807E00

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define HEVC_DVIEW_LEN          0
#else
#define HEVC_DVIEW_LEN          0x53ac00
#endif

#define HEVC_MV_LEN             0x100000
#define HEVC_MB_NEI_LEN         0xB000
#define HEVC_LAF_LEN            0//0x18F000
#define HEVC_INNER_ES_LEN       0x300000 //max:0x733334
#define HEVC_INNER_AUX_LEN      0x39000 
#else
#define HEVC_VBV_LEN            0
#define HEVC_CMD_QUEUE_LEN      0
#define HEVC_EP_QUEUE_LEN       0
#define HEVC_PICTURE_SYNTAX_LEN 0

#define HEVC_FB_LEN             0

#define HEVC_DVIEW_LEN          0

#define HEVC_MV_LEN             0
#define HEVC_MB_NEI_LEN         0
#define HEVC_LAF_LEN            0
#define HEVC_INNER_ES_LEN       0
#define HEVC_INNER_AUX_LEN      0
#endif


/*****************************************OSD ,DMX,TTX,*********************************************************************************/

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
#ifndef SD_PVR
#define __MM_OSD1_LEN           (1280*720*2)//(1280*720*4)
#define __MM_OSD2_LEN            (1920*1080)
#else
#define __MM_OSD1_LEN           (1008 * 640 * 2 + 256)
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

#ifdef FSC_SUPPORT
#define __MM_DMX_BLK_BUF_LEN        __MM_DMX_MAIN_BLK_LEN
#define __MM_DMX_SEE_BLK_BUF_LEN    0xbc000
#else
#define __MM_DMX_BLK_BUF_LEN        0xbc000
#define __MM_DMX_SEE_BLK_BUF_LEN    __MM_DMX_BLK_BUF_LEN
#endif

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
#define __MM_LWIP_MEMP_LEN              0xd1f00//0xce200
#define __MM_XML_MEMP_LEN                0x100000 // 5M
#else
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN                0
#endif

#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_LEN        0x8FC0
#define __MM_ISDBTCC_PB_LEN        0x7E900
#else
#define __MM_ISDBTCC_BS_LEN         0
#define __MM_ISDBTCC_PB_LEN         0
#endif

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#define __MM_VCAP_FB_SIZE               (736*576*2*4)
#else
#define __MM_VCAP_FB_SIZE               0
#endif
#define __MM_DBG_MEM_LEN   0x4000

/*************************************************MEMORY MAP ADDR*************************************************************/

//#ifdef SD_PVR
//    #define __MM_HIGHEST_ADDR   0xa4000000        //64M    
//#else
//    #define __MM_HIGHEST_ADDR   0xa8000000        //128M
//#endif
#define __MM_HIGHEST_ADDR           0xb0000000      // 256M

#define __MM_TTXSUB_S_TOP_ADDR    (__MM_HIGHEST_ADDR)
#define __MM_TTXSUB_S_START_ADDR  (__MM_TTXSUB_S_TOP_ADDR - __MM_TTXSUBT_S_LEN)
#define __MM_VOID_BUFFER_ADDR    (__MM_TTXSUB_S_START_ADDR - __MM_VOID_BUFFER_LEN)    //126M or 114M


#define __MM_SHARE_BASE_ADDR     (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)

#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR        (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)     //96M

#ifdef SD_PVR
    #define __MM_MAIN_TOP_ADDR        0xa2600000//0xa2000000        //36MB

    #define __MM_OSD_VSRC_MEM_ADDR    (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE) 
    //#define __MM_NIM_BUFFER_ADDR            (__MM_OSD_VSRC_MEM_ADDR - __MM_NIM_BUFFER_LEN)

    #define __MM_DMX_AVP_START_ADDR     ((__MM_OSD_VSRC_MEM_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)

    #define __MM_DMX_REC_START_ADDR        ((__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)
    #define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)

    #define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)

    #define __MM_NIM_BUFFER_ADDR            (__MM_EPG_BUFFER_START - __MM_NIM_BUFFER_LEN)
    #define __MM_BUF_PVR_TOP_ADDR           __MM_NIM_BUFFER_ADDR
    #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    
    #define __MM_FB_TOP_ADDR        (__MM_PVR_VOB_BUFFER_ADDR&0XFFFFFC00)     //32MB align
#else
    #define __MM_FB_TOP_ADDR        0xae000000//0xa6000000        //96MB
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



//#define SD_PVR //to support 64M with SD pvr

// for satcodx memmap
#define __MM_DVW_START_ADDR            ((__MM_FB2_C_START_ADDR - 0X25FA0)&0XFFFFFFF0)

// MPEG2
#define MPEG2_BUF_START_ADDR        ((__MM_FB_TOP_ADDR - __MM_FB_LEN)&0XFFFFFc00)

// AVC
#ifndef AVC_SUPPORT_UNIFY_MEM
/*AVC buffer allocation*/
#define AVC_MV_ADDR                 ((__MM_FB_TOP_ADDR - AVC_MV_LEN)&0xffffff00)          //256 bytes alignment
#define AVC_MB_COL_ADDR             ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)         //256 bytes alignment
#define AVC_MB_NEI_ADDR             ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define AVC_LAF_RW_BUF_ADDR         ((AVC_MB_NEI_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define AVC_DVIEW_ADDR              ((AVC_LAF_RW_BUF_ADDR - AVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define AVC_BUF_START_ADDR          ((AVC_DVIEW_ADDR - AVC_FB_LEN )&0xfffffe00)           //512 bytes alignment
#else
#define AVC_MB_COL_ADDR 		    ((__MM_FB_TOP_ADDR - AVC_MB_COL_LEN - AVC_MV_LEN)&0xffffff00)  		//256 bytes alignment
#define AVC_MB_NEI_ADDR 			((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00) 	//256 bytes alignment
#define AVC_BUF_START_ADDR 			((AVC_MB_NEI_ADDR - AVC_MEM_LEN)&0xffffff00)

#define AVC_DVIEW_ADDR 				0
#define AVC_MV_ADDR 				0
#define AVC_LAF_RW_BUF_ADDR			0
#define AVC_LAF_FLAG_BUF_ADDR       0
#define AVC_FB_ADDR					0
#endif

// HEVC
#define HEVC_MV_ADDR            ((__MM_FB_TOP_ADDR - HEVC_MV_LEN)&0xffffff00)          //256 bytes alignment
#define HEVC_MB_NEI_ADDR        ((HEVC_MV_ADDR - HEVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define HEVC_LAF_ADDR           ((HEVC_MB_NEI_ADDR - HEVC_LAF_LEN)&0xfffffc00)  //1024 bytes alignment
#define HEVC_INNER_ES_ADDR      ((HEVC_LAF_ADDR - HEVC_INNER_ES_LEN)&0xfffffc00)
#define HEVC_INNER_AUX_ADDR     ((HEVC_INNER_ES_ADDR - HEVC_INNER_AUX_LEN)&0xfffffc00)
#define HEVC_DVIEW_ADDR         ((HEVC_INNER_AUX_ADDR - HEVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define HEVC_BUF_START_ADDR     ((HEVC_DVIEW_ADDR - HEVC_FB_LEN )&0xfffffe00)           //512 bytes alignment

#if (MPEG2_BUF_START_ADDR < AVC_BUF_START_ADDR && MPEG2_BUF_START_ADDR < HEVC_BUF_START_ADDR)
#define __MM_FB_BOTTOM_ADDR         MPEG2_BUF_START_ADDR
#elif (HEVC_BUF_START_ADDR < AVC_BUF_START_ADDR)
#define __MM_FB_BOTTOM_ADDR         HEVC_BUF_START_ADDR
#else
#define __MM_FB_BOTTOM_ADDR         AVC_BUF_START_ADDR
#endif

//AVC redefine
#define __MM_FB_START_ADDR          __MM_FB_BOTTOM_ADDR
#define __MM_FB_ACT_LEN             (__MM_MAF_START_ADDR-__MM_FB_START_ADDR)

//AVC redefine
#ifdef AVC_SUPPORT_UNIFY_MEM
#undef  AVC_MEM_ADDR
#undef  AVC_MEM_LEN
#define AVC_MEM_ADDR                __MM_FB_BOTTOM_ADDR
#define AVC_MEM_LEN                 ((AVC_MB_NEI_ADDR - AVC_MEM_ADDR)&0xffffff00)
#else 
/* AVC_SUPPORT_UNIFY_MEM */
#define AVC_FB_ADDR                 __MM_FB_BOTTOM_ADDR
#define AVC_FB_ACT_LEN              (AVC_DVIEW_ADDR-AVC_FB_ADDR)
#define AVC_MEM_LEN                 0   //for compile error
#endif /* AVC_SUPPORT_UNIFY_MEM */

//HEVC redefine
#define HEVC_FB_ADDR                __MM_FB_BOTTOM_ADDR
#define HEVC_FB_ACT_LEN             (HEVC_DVIEW_ADDR-HEVC_FB_ADDR)


#define __MM_NIM_BUFFER_ADDR            (__MM_FB_BOTTOM_ADDR - __MM_NIM_BUFFER_LEN)
#define __MM_BUF_PVR_TOP_ADDR           __MM_NIM_BUFFER_ADDR
#ifdef SAT2IP_SUPPORT//MEDIA_PROVIDER_USE_RING_BUFFER
    #define __MM_MEDIA_PROVIDER_BUFFER_ADDR (__MM_BUF_PVR_TOP_ADDR - __MM_MEDIA_PROV_BUFFER_LEN)
    #define __MM_PVR_VOB_BUFFER_ADDR        (__MM_MEDIA_PROVIDER_BUFFER_ADDR - __MM_PVR_VOB_BUFFER_LEN)
#else
    #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
#endif

#ifdef _MHEG5_V20_ENABLE_
    #define __MM_MHEG5_BUFFER_ADDR      (__MM_PVR_VOB_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
    #define __MM_DMX_AVP_START_ADDR        ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
#else
    #define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
#endif

#define __MM_DMX_REC_START_ADDR        ((__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)
#define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)

#define __MM_GE_START_ADDR          ((__MM_EPG_BUFFER_START - __MM_GE_LEN)&0XFFFFFFE0)
#ifdef _M36F_SINGLE_CPU
    // for m36f single cpu mode(only test for ali internal)
    // move osd, vsrc, scap buffer to private buffer base.
    #define __MM_LWIP_MEM_ADDR      (__MM_GE_START_ADDR - __MM_LWIP_MEM_LEN)
#else
    #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFE0)
    #if (defined(_CAS9_CA_ENABLE_) || defined(_C0200A_CA_ENABLE_) ||defined(_GEN_CA_ENABLE_) ||defined(_BC_CA_ENABLE_) || defined (_C1800A_CA_ENABLE_))
        #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFE0)
        #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    #else
        #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    #endif
    #define __MM_OSD_VSRC_MEM_ADDR        ((__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFE0)
    #define __MM_LWIP_MEM_ADDR          (__MM_OSD_VSRC_MEM_ADDR - __MM_LWIP_MEM_LEN)
#endif


#define __MM_NIM_DVBT2_BUFFER_ADDR        (__MM_NIM_BUFFER_ADDR - __MM_NIM_DVBT2_BUFFER_LEN)
#define __MM_NIM_DVBC_BUFFER_ADDR         (__MM_NIM_DVBT2_BUFFER_ADDR - __MM_NIM_DVBC_BUFFER_LEN)

#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR            ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)

#ifndef SD_PVR
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
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
#else
//add for TTX_TO_MAIN
#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_TTXSUB_S_TOP_ADDR - __MM_TTX_SUB_PAGE_LEN)
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
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)

#if ( __MM_ISDBTCC_PB_START_ADDR < __MM_TTXSUB_S_START_ADDR)
    #error "TTX ATSC len is bigger than __MM_TTXSUBT_S_LEN"
#endif
#endif

#ifndef SD_PVR
#define __MM_CPU_DBG_MEM_ADDR          (__MM_ISDBTCC_PB_START_ADDR - __MM_DBG_MEM_LEN)
#else
#define __MM_CPU_DBG_MEM_ADDR          (__MM_USB_START_ADDR - __MM_DBG_MEM_LEN)
#endif

#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR

//Allocate FSC buffer, share with PVR
#ifdef FSC_SUPPORT
    #define __MM_FSC_BUFFER_LEN     (__MM_DMX_MAIN_BLK_LEN*2 + __MM_DMX_REC_LEN*2+1024)
    
    #define __MM_FSC_BUFFER_TOP     ((__MM_BUF_PVR_TOP_ADDR)&0XFF800000)
    #define __MM_FSC_BUFFER_ADDR    (__MM_FSC_BUFFER_TOP - __MM_FSC_BUFFER_LEN) 

    #define __MM_DMX0_DMA_START_ADDR    (__MM_DMX_AVP_START_ADDR)
    #define __MM_DMX1_DMA_START_ADDR    (__MM_DMX_REC_START_ADDR)
    #define __MM_DMX2_DMA_START_ADDR    ((__MM_FSC_BUFFER_TOP - __MM_DMX_REC_LEN)&0XFFFFFFF0)
    #define __MM_DMX3_DMA_START_ADDR	((__MM_DMX2_DMA_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)

    #define __MM_DMX0_MAIN_BLK_START_ADDR (__MM_DMX_CPU_BLK_ADDR )
    #define __MM_DMX1_MAIN_BLK_START_ADDR	((__MM_DMX3_DMA_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #define __MM_DMX2_MAIN_BLK_START_ADDR   ((__MM_DMX1_MAIN_BLK_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    
#if(__MM_DMX2_MAIN_BLK_START_ADDR < __MM_FSC_BUFFER_ADDR)
    #error "__MM_FSC_BUFFER_ADDR too small"
#endif
#if(__MM_FSC_BUFFER_ADDR < __MM_PVR_VOB_BUFFER_ADDR)
    #error "PVR no enough buffer to share with fsc"
#endif
#else
    #define __MM_FSC_BUFFER_LEN     0
#endif

//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/

#ifdef _DD_SUPPORT
#define __MM_PRIV_DEC_LEN   0x20000
#define __MM_PRIV_DEC_ADDR (__MM_PRIVATE_TOP_ADDR- __MM_PRIV_DEC_LEN)
#else
#define __MM_PRIV_DEC_LEN   0
#define __MM_PRIV_DEC_ADDR (__MM_PRIVATE_TOP_ADDR- __MM_PRIV_DEC_LEN)
#endif

#define __MM_REAL_PRIVATE_TOP_ADDR __MM_PRIV_DEC_ADDR

#define __MM_VBV_START_ADDR            ((__MM_REAL_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define __MM_MAF_START_ADDR            ((__MM_VBV_START_ADDR - __MM_MAF_LEN)&0XFFFFFC00)
#define AVC_VBV_ADDR                 (__MM_REAL_PRIVATE_TOP_ADDR - AVC_VBV_LEN)     //256 bytes alignment

#define HEVC_VBV_ADDR                  ((__MM_REAL_PRIVATE_TOP_ADDR - HEVC_VBV_LEN)&0XFFFFFF00)     //256 bytes alignment
#define HEVC_PICTURE_SYNTAX_BUF_ADDR   ((HEVC_VBV_ADDR - HEVC_PICTURE_SYNTAX_LEN)&0XFFFFFF00)
#define HEVC_EP_QUEUE_BUF_ADDR         ((HEVC_PICTURE_SYNTAX_BUF_ADDR - HEVC_EP_QUEUE_LEN)&0XFFFFFF00)
#ifndef SD_PVR
#define HEVC_CMD_QUEUE_BUF_ADDR        ((HEVC_EP_QUEUE_BUF_ADDR - HEVC_CMD_QUEUE_LEN)&0XFFFFFF00) 
#else
#define HEVC_CMD_QUEUE_BUF_ADDR        __MM_MAF_START_ADDR//for 64M not support HEVC
#endif


#if (AVC_VBV_ADDR <= __MM_MAF_START_ADDR && AVC_VBV_ADDR<=HEVC_CMD_QUEUE_BUF_ADDR)
#define __MM_DMX_SEE_BLK_ADDR    ((AVC_VBV_ADDR - __MM_DMX_SEE_BLK_BUF_LEN)&0XFFFFFFE0)
#elif (HEVC_CMD_QUEUE_BUF_ADDR<=__MM_MAF_START_ADDR)
#define __MM_DMX_SEE_BLK_ADDR    ((HEVC_CMD_QUEUE_BUF_ADDR - __MM_DMX_SEE_BLK_BUF_LEN)&0XFFFFFFE0)
#else
#define __MM_DMX_SEE_BLK_ADDR    ((__MM_MAF_START_ADDR - __MM_DMX_SEE_BLK_BUF_LEN)&0XFFFFFFE0)
#endif

#define __MM_DMX_SEE_BLK_START_ADDR (__MM_DMX_SEE_BLK_ADDR)


#define __MM_SEE_MP_BUF_ADDR    (__MM_DMX_SEE_BLK_ADDR -  __MM_SEE_MP_BUF_LEN)

#define AVC_CMD_QUEUE_ADDR  ((__MM_SEE_MP_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment

#ifndef AVC_SUPPORT_UNIFY_MEM
#define AVC_LAF_FLAG_BUF_ADDR   ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define __MM_OSD_BK_ADDR2       ((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)
#else
#define __MM_OSD_BK_ADDR2       ((AVC_CMD_QUEUE_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)
#endif


#ifdef _M36F_SINGLE_CPU
// for m3f single cpu(only test for ali internal)
// more osd, vsrc, scap buffer to private buffer base.
#define __MM_OSD_BK_ADDR1              ((__MM_SUB_PB_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFE0)
#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
#define __MM_OSD_VSRC_MEM_ADDR        ((__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFE0)
#define __MM_SEE_DBG_MEM_ADDR      (__MM_OSD_VSRC_MEM_ADDR - __MM_DBG_MEM_LEN)
    #if(__MM_SEE_DBG_MEM_ADDR < __MM_PRIVATE_ADDR)
        #error "__MM_SEE_DBG_MEM_ADDR address error"
    #endif
#else
#define __MM_SEE_DBG_MEM_ADDR      ( __MM_OSD_BK_ADDR2 - __MM_DBG_MEM_LEN)
#endif

// for jpeg decoder memmap
#ifdef SD_PVR
#define __MM_FB0_Y_LEN            (736*576 + 1024)
#define __MM_IMG_FB_Y_LEN        (736*576*2 + 1024)
#define __MM_IMG_FB_C_LEN        (__MM_IMG_FB_Y_LEN/2)
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
    #define __MM_FB3_Y_START_ADDR    0 //((__MM_FB2_C_START_ADDR+__MM_FB2_C_LEN)&0XFFFFFE00)
    #define __MM_FB3_C_START_ADDR    0 //((__MM_FB3_Y_START_ADDR+__MM_FB3_Y_LEN)&0XFFFFFE00)
    #define __MM_FB4_Y_START_ADDR    0 //((__MM_FB3_C_START_ADDR+__MM_FB3_C_LEN)&0XFFFFFE00)
    #define __MM_FB4_C_START_ADDR    0 //((__MM_FB4_Y_START_ADDR+__MM_FB4_Y_LEN)&0XFFFFFE00)
    #define __MM_FB5_Y_START_ADDR    0 //((__MM_FB4_C_START_ADDR+__MM_FB4_C_LEN)&0XFFFFFE00)
    #define __MM_FB5_C_START_ADDR    0 //((__MM_FB5_Y_START_ADDR+__MM_FB5_Y_LEN)&0XFFFFFE00)
    #define __MM_FB6_Y_START_ADDR    0 //((__MM_FB5_C_START_ADDR+__MM_FB5_C_LEN)&0XFFFFFE00)
    #define __MM_FB6_C_START_ADDR    0 //((__MM_FB6_Y_START_ADDR+__MM_FB6_Y_LEN)&0XFFFFFE00)
    //#define __MM_MP_BUFFER_LEN        (__MM_TTX_BS_START_ADDR - __MM_SEE_MP_BUF_ADDR)//(__MM_SEE_MP_BUF_LEN - __MM_FB0_Y_LEN * 3 - __MM_FB0_C_LEN * 3)
    //#define __MM_MP_BUFFER_ADDR        __MM_SEE_MP_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
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
    //#define __MM_MP_BUFFER_LEN        (__MM_FB_TOP_ADDR - __MM_TTX_P26_DATA_BUF_ADDR)//(__MM_SEE_MP_BUF_LEN - __MM_FB0_Y_LEN * 3 - __MM_FB0_C_LEN * 3)
    //#define __MM_MP_BUFFER_ADDR        __MM_TTX_P26_DATA_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
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
#endif


#ifdef SD_PVR
    #define __MM_MP_BUFFER_ADDR             ((__MM_EPG_BUFFER_START + 0x1FF)&0XFFFFFE00)
    #define __MM_MP_BUFFER_LEN              (__MM_FB_BOTTOM_ADDR - __MM_MP_BUFFER_ADDR)
#else
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
#else// VFB_SUPPORT
//cas9 or VFB enable
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

#define __MM_SHARED_MEM_LEN      1024

#define __MM_SEE_MP_BUF_LEN      0//0x00900000    //9M
#ifdef SD_PVR
	#define __MM_PRIVATE_SHARE_LEN	0x01700000  //24M
	#define __MM_TTXSUBT_S_LEN      0x00300000
#else
	#define __MM_PRIVATE_SHARE_LEN	0x02000000//0x01e00000	//30M
	#define __MM_TTXSUBT_S_LEN      0
#endif
#define __MM_VOID_BUFFER_LEN	0//0x00200000	//2M
	
#define __MM_PRIVATE_LEN        (__MM_PRIVATE_SHARE_LEN-__MM_SHARED_MEM_LEN)

/*******************************************************NIM BUFFER LEN************************************************************/
#ifdef DVBC_SUPPORT
#define __MM_NIM_DVBC_BUFFER_LEN         0x200000//2M
#else
#define __MM_NIM_DVBC_BUFFER_LEN         0x0
#endif

#ifdef DVBT2_SUPPORT
#define __MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN         0x400000//4M
#define __MM_NIM_DVBT2_DJB_BUFFER_LEN                0x96000//600K
#else 
#define __MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN         0x0
#define __MM_NIM_DVBT2_DJB_BUFFER_LEN                0x0
#endif
#define __MM_NIM_DVBT2_BUFFER_LEN (__MM_NIM_DVBT2_TIME_DEINT_BUFFER_LEN + __MM_NIM_DVBT2_DJB_BUFFER_LEN)

#define __MM_NIM_BUFFER_LEN  (__MM_NIM_DVBT2_BUFFER_LEN + __MM_NIM_DVBC_BUFFER_LEN)

/************************************************************PVR BUFFER LEN*********************************************************/
#ifdef SD_PVR
    #define __MM_PVR_VOB_BUFFER_LEN        ((47*1024)*(75*2)+0x1000- __MM_NIM_BUFFER_LEN)//0x88a800//0x6fb000
#else
    #ifdef SAT2IP_SUPPORT
        #define __MM_MEDIA_PROV_BUFFER_LEN     0x400000
    #else
        #define __MM_MEDIA_PROV_BUFFER_LEN     0
    #endif
    
    #ifdef FSC_SUPPORT
        #define __MM_DMX_MAIN_BLK_LEN     ((47*1024)*87)// should align with 188*16//(0x400000) 
    #else
        #define __MM_DMX_MAIN_BLK_LEN     0
    #endif
    
	#define __MM_PVR_VOB_BUFFER_LEN (((47*1024)*(160*3)+0x1000) - __MM_MEDIA_PROV_BUFFER_LEN - __MM_NIM_BUFFER_LEN - __MM_DMX_MAIN_BLK_LEN)	
#endif

/************************************************************DECODER BUFFER*************************************************************/
#define __MM_FB_LEN_DEVIDED        0X32A000//(HD:1920X1152X1.5)
#ifndef SD_PVR
    #ifdef VIDEO_DEBLOCKING_SUPPORT
	#define __MM_FB_LEN			    0x10D8800//0x10CF200//0x19c6200
    #else
	#define __MM_FB_LEN			    0xddb800//0xdd2200//0XCA8000//0X9B4000//0X26D000//(16*SD>3*HD)
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

#define EXTRA_DV_FB_SIZE 0x3C00
#define ONE_DV_FB_SIZE (((MAX_MB_WIDTH*MAX_MB_HEIGHT*256*3/2)/4) + EXTRA_DV_FB_SIZE)
#define ONE_MV_SIZE 32*(MAX_MB_WIDTH*MAX_MB_HEIGHT) //522240

#ifdef DYNAMIC_RESOLUTION_SUPPORT
#ifndef SD_PVR
#define AVC_FB_LEN		ONE_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0x1700000

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN   0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(5+MAX_EXTRA_FB_NUM) //0xb00000
#endif

#define AVC_MV_LEN		ONE_MV_SIZE*(5+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#else
#define const_frm_num   5
#define AVC_FB_LEN		ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN		ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#endif //end of SD_PVR
#define AVC_MB_COL_LEN		0x18000 //0x11000
#else
#ifndef SD_PVR
#define AVC_FB_LEN      ONE_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0x1700000

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define AVC_DVIEW_LEN   0
#else
#define AVC_DVIEW_LEN   ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#endif

#define AVC_MV_LEN      ONE_MV_SIZE*(4+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x15000
#else
#define const_frm_num   5
#define AVC_FB_LEN      ONE_FB_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x1700000
#define AVC_DVIEW_LEN   0//  ONE_DV_FB_SIZE*(4+MAX_EXTRA_FB_NUM) //0xb00000
#define AVC_MV_LEN      ONE_MV_SIZE*(const_frm_num+MAX_EXTRA_FB_NUM) //0x37c800//0x2FD000
#define AVC_MB_COL_LEN  0x18000 // 0x11000 will cause overflow
#endif //end of SD_PVR
#endif // end of DYNAMIC_RESOLUTION_SUPPORT

#define AVC_MB_NEI_LEN        0xf000
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

#define HEVC_VBV_LEN            0x400000
#define HEVC_CMD_QUEUE_LEN      0x20000
#define HEVC_EP_QUEUE_LEN       0x20000
#define HEVC_PICTURE_SYNTAX_LEN 0x5000

#define HEVC_FB_LEN             0x2020000//0x1820000//0x1B24000//0x1807E00

#ifndef MP_PREVIEW_SWITCH_SMOOTHLY
#define HEVC_DVIEW_LEN          0
#else
#define HEVC_DVIEW_LEN          0x53ac00
#endif

#define HEVC_MV_LEN             0x100000
#define HEVC_MB_NEI_LEN         0xB000
#define HEVC_LAF_LEN            0//0x18F000
#define HEVC_INNER_ES_LEN       0x300000 //max:0x733334
#define HEVC_INNER_AUX_LEN      0x39000 

/*****************************************OSD ,DMX,TTX,*********************************************************************************/

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
#ifndef SD_PVR
#define __MM_OSD1_LEN           (1280*720*2)//(1280*720*4)
#define __MM_OSD2_LEN            (1920*1080)
#else
#define __MM_OSD1_LEN           (1008 * 640 * 2 + 256)
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

#ifdef FSC_SUPPORT
#define __MM_DMX_BLK_BUF_LEN        __MM_DMX_MAIN_BLK_LEN
#define __MM_DMX_SEE_BLK_BUF_LEN    0xbc000
#else
#define __MM_DMX_BLK_BUF_LEN        0xbc000
#define __MM_DMX_SEE_BLK_BUF_LEN    __MM_DMX_BLK_BUF_LEN
#endif


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
#define __MM_LWIP_MEMP_LEN              0xd1f00//0xce200
#define __MM_XML_MEMP_LEN                0x100000 // 5M
#else
#define __MM_LWIP_MEM_LEN               0
#define __MM_LWIP_MEMP_LEN              0
#define __MM_XML_MEMP_LEN                0
#endif

#ifdef ISDBT_CC
#define __MM_ISDBTCC_BS_LEN        0x8FC0
#define __MM_ISDBTCC_PB_LEN        0x7E900
#else
#define __MM_ISDBTCC_BS_LEN         0
#define __MM_ISDBTCC_PB_LEN         0
#endif

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
#define __MM_VCAP_FB_SIZE               (736*576*2*4)
#else
#define __MM_VCAP_FB_SIZE               0
#endif
#define __MM_DBG_MEM_LEN   0x4000

/*************************************************MEMORY MAP ADDR*************************************************************/

#ifdef SD_PVR
    #define __MM_HIGHEST_ADDR   0xa4000000        //64M    
#else
    #define __MM_HIGHEST_ADDR   0xb0000000//0xa8000000        //128M
#endif


#define __MM_TTXSUB_S_TOP_ADDR    (__MM_HIGHEST_ADDR)
#define __MM_TTXSUB_S_START_ADDR  (__MM_TTXSUB_S_TOP_ADDR - __MM_TTXSUBT_S_LEN)
#define __MM_VOID_BUFFER_ADDR    (__MM_TTXSUB_S_START_ADDR - __MM_VOID_BUFFER_LEN)    //126M or 114M


#define __MM_SHARE_BASE_ADDR     (__MM_VOID_BUFFER_ADDR-__MM_SHARED_MEM_LEN)

#define __MM_PRIVATE_TOP_ADDR     (__MM_SHARE_BASE_ADDR)
#define __MM_PRIVATE_ADDR        (__MM_PRIVATE_TOP_ADDR-__MM_PRIVATE_LEN)     //96M

#ifdef _CAS9_VSC_ENABLE_
	#define __MM_VSC_CODE_START_ADDR	__MM_PRIVATE_ADDR
	#define __MM_VSC_DATA_START_ADDR (__MM_VSC_CODE_START_ADDR+__MM_VSC_CODE_LEN)
#endif

#ifdef SD_PVR
    #define __MM_MAIN_TOP_ADDR        0xa2600000//0xa2000000        //36MB

    #define __MM_OSD_VSRC_MEM_ADDR    (__MM_MAIN_TOP_ADDR - OSD_VSRC_MEM_MAX_SIZE) 
    #define __MM_NIM_BUFFER_ADDR            (__MM_OSD_VSRC_MEM_ADDR - __MM_NIM_BUFFER_LEN)

    #ifdef _MHEG5_V20_ENABLE_
        #define __MM_MHEG5_BUFFER_ADDR      (__MM_NIM_BUFFER_ADDR - MHEG5_MEMORY_ALLOC_REGION_SIZE)
        #define __MM_DMX_AVP_START_ADDR     ((__MM_MHEG5_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
    #else
        #define __MM_DMX_AVP_START_ADDR     ((__MM_NIM_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
    #endif
    #define __MM_DMX_REC_START_ADDR        ((__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)
    #define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)

    #define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)
    #define __MM_BUF_PVR_TOP_ADDR       __MM_EPG_BUFFER_START
    #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    
    #define __MM_FB_TOP_ADDR        (__MM_PVR_VOB_BUFFER_ADDR&0XFFFFFC00)     //32MB align
#else
    #define __MM_MAIN_TOP_ADDR      0xae000000//0xa6000000        //96MB
    #define __MM_VCAP_FB_ADDR       ((__MM_MAIN_TOP_ADDR - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment

    #define __MM_FB_TOP_ADDR        __MM_VCAP_FB_ADDR//0xa6000000        //96MB
#endif

#ifdef SD_PVR
    #if(__MM_MAIN_TOP_ADDR != __MM_PRIVATE_ADDR)
    #error "__MM_PRIVATE_ADDR address error"
    #endif
#endif

// for satcodx memmap
#define __MM_DVW_START_ADDR         ((__MM_FB2_C_START_ADDR - 0X25FA0)&0XFFFFFFF0)

// MPEG2
#define __MM_MAF_START_ADDR         ((__MM_FB_TOP_ADDR - __MM_MAF_LEN) & 0xFFFFFC00)
#define MPEG2_BUF_START_ADDR        ((__MM_MAF_START_ADDR - __MM_FB_LEN) & 0xFFFFFc00)

// AVC
#ifndef AVC_SUPPORT_UNIFY_MEM
#define AVC_MV_ADDR                 ((__MM_FB_TOP_ADDR - AVC_MV_LEN)&0xffffff00)                //256 bytes alignment
#define AVC_MB_COL_ADDR             ((AVC_MV_ADDR - AVC_MB_COL_LEN)&0xffffff00)                 //256 bytes alignment
#define AVC_MB_NEI_ADDR             ((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00)             //256 bytes alignment
#define AVC_LAF_RW_BUF_ADDR         ((AVC_MB_NEI_ADDR - AVC_LAF_RW_BUF_LEN)&0xfffffc00)         //1024 bytes alignment
#define AVC_CMD_QUEUE_ADDR          ((AVC_LAF_RW_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
#define AVC_LAF_FLAG_BUF_ADDR       ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)    //1024 bytes alignment
#define AVC_DVIEW_ADDR              ((AVC_LAF_FLAG_BUF_ADDR -  AVC_DVIEW_LEN)&0xfffffe00)       //512 bytes alignment
#define AVC_BUF_START_ADDR          ((AVC_DVIEW_ADDR -  AVC_FB_LEN)&0xfffffe00)                 //512 bytes alignment
#else
#define AVC_MB_COL_ADDR 		    ((__MM_FB_TOP_ADDR - AVC_MB_COL_LEN - AVC_MV_LEN -AVC_CMD_QUEUE_LEN)&0xffffff00)  		//256 bytes alignment
#define AVC_MB_NEI_ADDR 			((AVC_MB_COL_ADDR - AVC_MB_NEI_LEN)&0xffffff00) 	//256 bytes alignment
#define AVC_BUF_START_ADDR 			((AVC_MB_NEI_ADDR - AVC_MEM_LEN)&0xffffff00)
#define AVC_DVIEW_ADDR 				0
#define AVC_MV_ADDR 				0
#define AVC_LAF_RW_BUF_ADDR			0
#define AVC_LAF_FLAG_BUF_ADDR       0
#define AVC_FB_ADDR					0
#endif

// HEVC
#define HEVC_MV_ADDR                ((__MM_FB_TOP_ADDR - HEVC_MV_LEN)&0xffffff00)       //256 bytes alignment
#define HEVC_MB_NEI_ADDR            ((HEVC_MV_ADDR - HEVC_MB_NEI_LEN)&0xffffff00)     //256 bytes alignment
#define HEVC_LAF_ADDR               ((HEVC_MB_NEI_ADDR - HEVC_LAF_LEN)&0xfffffc00)    //1024 bytes alignment
#define HEVC_INNER_ES_ADDR          ((HEVC_LAF_ADDR - HEVC_INNER_ES_LEN)&0xfffffc00)
#define HEVC_INNER_AUX_ADDR         ((HEVC_INNER_ES_ADDR - HEVC_INNER_AUX_LEN)&0xfffffc00)
#define HEVC_PICTURE_SYNTAX_BUF_ADDR ((HEVC_INNER_AUX_ADDR - HEVC_PICTURE_SYNTAX_LEN)&0XFFFFFF00)
#define HEVC_EP_QUEUE_BUF_ADDR      ((HEVC_PICTURE_SYNTAX_BUF_ADDR - HEVC_EP_QUEUE_LEN)&0XFFFFFF00)
#define HEVC_CMD_QUEUE_BUF_ADDR     ((HEVC_EP_QUEUE_BUF_ADDR - HEVC_CMD_QUEUE_LEN) & 0XFFFFFC00)
#define HEVC_DVIEW_ADDR             ((HEVC_CMD_QUEUE_BUF_ADDR -  HEVC_DVIEW_LEN)&0xfffffe00)     //512 bytes alignment
#define HEVC_BUF_START_ADDR         ((HEVC_DVIEW_ADDR -  HEVC_FB_LEN )&0xffff4000)      //16k bytes alignment

#if (MPEG2_BUF_START_ADDR < AVC_BUF_START_ADDR && MPEG2_BUF_START_ADDR < HEVC_BUF_START_ADDR)
#define __MM_FB_BOTTOM_ADDR         MPEG2_BUF_START_ADDR
#elif (HEVC_BUF_START_ADDR < AVC_BUF_START_ADDR)
#define __MM_FB_BOTTOM_ADDR         HEVC_BUF_START_ADDR
#else
#define __MM_FB_BOTTOM_ADDR         AVC_BUF_START_ADDR
#endif

#define __MM_FB_START_ADDR          __MM_FB_BOTTOM_ADDR
#define __MM_FB_ACT_LEN             (__MM_MAF_START_ADDR-__MM_FB_START_ADDR)

#ifdef AVC_SUPPORT_UNIFY_MEM
#undef  AVC_MEM_ADDR
#undef  AVC_MEM_LEN
#define AVC_MEM_ADDR                __MM_FB_BOTTOM_ADDR
#define AVC_MEM_LEN                 ((AVC_MB_NEI_ADDR - AVC_MEM_ADDR)&0xffffff00)
#else /* AVC_SUPPORT_UNIFY_MEM */
#define AVC_FB_ADDR                 __MM_FB_BOTTOM_ADDR
#define AVC_FB_ACT_LEN              (AVC_DVIEW_ADDR-AVC_FB_ADDR)

#define AVC_MEM_LEN                 0   //for compile error
#endif /* AVC_SUPPORT_UNIFY_MEM */

#define HEVC_FB_ADDR                __MM_FB_BOTTOM_ADDR
#define HEVC_FB_ACT_LEN             (HEVC_DVIEW_ADDR-HEVC_FB_ADDR)


#ifndef SD_PVR
    #define __MM_NIM_BUFFER_ADDR            (__MM_FB_BOTTOM_ADDR - __MM_NIM_BUFFER_LEN)
    #define __MM_BUF_PVR_TOP_ADDR           __MM_NIM_BUFFER_ADDR
    #ifdef SAT2IP_SUPPORT//MEDIA_PROVIDER_USE_RING_BUFFER
        #define __MM_MEDIA_PROVIDER_BUFFER_ADDR (__MM_BUF_PVR_TOP_ADDR - __MM_MEDIA_PROV_BUFFER_LEN)
        #define __MM_PVR_VOB_BUFFER_ADDR        (__MM_MEDIA_PROVIDER_BUFFER_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #else
        #define __MM_PVR_VOB_BUFFER_ADDR    (__MM_BUF_PVR_TOP_ADDR - __MM_PVR_VOB_BUFFER_LEN)
    #endif

    #define __MM_DMX_AVP_START_ADDR        ((__MM_PVR_VOB_BUFFER_ADDR - __MM_SI_VBV_OFFSET - __MM_DMX_DATA_LEN - __MM_DMX_AVP_LEN)&0XFFFFFFF0)
    
    #define __MM_DMX_REC_START_ADDR        ((__MM_DMX_AVP_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)
    #define __MM_DMX_CPU_BLK_ADDR        ((__MM_DMX_REC_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #define __MM_EPG_BUFFER_START       (__MM_DMX_CPU_BLK_ADDR - __MM_EPG_BUFFER_LEN)

    #define __MM_GE_START_ADDR          ((__MM_EPG_BUFFER_START - __MM_GE_LEN)&0XFFFFFFE0)
    #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFE0)
    #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFE0)
    //#define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
    #define __MM_OSD_VSRC_MEM_ADDR     ((__MM_OSD_BK_ADDR2_MAIN - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFE0)//((__MM_VCAP_FB_ADDR - OSD_VSRC_MEM_MAX_SIZE)&0XFFFFFFE0)
    #define __MM_LWIP_MEM_ADDR          (__MM_OSD_VSRC_MEM_ADDR - __MM_LWIP_MEM_LEN)
   
#else
    #define __MM_GE_START_ADDR          ((__MM_FB_BOTTOM_ADDR - __MM_GE_LEN)&0XFFFFFFE0)
    #ifdef _M36F_SINGLE_CPU
        // for m36f single cpu mode(only test for ali internal)
        // move osd, vsrc, scap buffer to private buffer base.
        #define __MM_LWIP_MEM_ADDR      (__MM_GE_START_ADDR - __MM_LWIP_MEM_LEN)
    #else
        #define __MM_OSD_BK_ADDR1  		((__MM_GE_START_ADDR - __MM_OSD1_LEN)&0XFFFFFFE0)
        #if (defined(_CAS9_CA_ENABLE_) || defined(_C0200A_CA_ENABLE_) ||defined(_GEN_CA_ENABLE_) ||defined(_BC_CA_ENABLE_))
            #define __MM_OSD_BK_ADDR2_MAIN      ((__MM_OSD_BK_ADDR1 - __MM_OSD2_LEN)&0XFFFFFFE0)
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR2_MAIN - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        #else
            #define __MM_VCAP_FB_ADDR           ((__MM_OSD_BK_ADDR1 - __MM_VCAP_FB_SIZE)&0XFFFFFF00) // 256 bytes alignment
        #endif
        #define __MM_LWIP_MEM_ADDR          (__MM_VCAP_FB_ADDR - __MM_LWIP_MEM_LEN)
     #endif
#endif

#define __MM_LWIP_MEMP_ADDR         (__MM_LWIP_MEM_ADDR - __MM_LWIP_MEMP_LEN)
#define __MM_USB_START_ADDR            ((__MM_LWIP_MEMP_ADDR - __MM_USB_DMA_LEN)&0XFFFFFFE0)

#ifndef SD_PVR
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
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)
#else
//add for TTX_TO_MAIN
#define __MM_TTX_SUB_PAGE_BUF_ADDR  (__MM_TTXSUB_S_TOP_ADDR - __MM_TTX_SUB_PAGE_LEN)
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
#define __MM_ISDBTCC_BS_START_ADDR ((__MM_SUBT_ATSC_SEC_ADDR - __MM_ISDBTCC_BS_LEN)&0XFFFFFFE0)
#define __MM_ISDBTCC_PB_START_ADDR ((__MM_ISDBTCC_BS_START_ADDR - __MM_ISDBTCC_PB_LEN)&0XFFFFFFE0)

#if ( __MM_ISDBTCC_PB_START_ADDR < __MM_TTXSUB_S_START_ADDR)
    #error "TTX ATSC len is bigger than __MM_TTXSUBT_S_LEN"
#endif
#endif

#ifndef SD_PVR
#define __MM_CPU_DBG_MEM_ADDR          (__MM_ISDBTCC_PB_START_ADDR - __MM_DBG_MEM_LEN)
#else
#define __MM_CPU_DBG_MEM_ADDR          (__MM_USB_START_ADDR - __MM_DBG_MEM_LEN)
#endif

#define __MM_AUTOSCAN_DB_BUFFER_ADDR    __MM_PVR_VOB_BUFFER_ADDR
#define __MM_NIM_DVBT2_BUFFER_ADDR      (__MM_NIM_BUFFER_ADDR - __MM_NIM_DVBT2_BUFFER_LEN)
#define __MM_NIM_DVBC_BUFFER_ADDR       (__MM_NIM_DVBT2_BUFFER_ADDR - __MM_NIM_DVBC_BUFFER_LEN)


//Allocate FSC buffer, share with PVR
#ifdef FSC_SUPPORT
    #define __MM_FSC_BUFFER_LEN     (__MM_DMX_MAIN_BLK_LEN*2 + __MM_DMX_REC_LEN*2+1024)
    
    #define __MM_FSC_BUFFER_TOP     ((__MM_BUF_PVR_TOP_ADDR)&0XFF800000)
    #define __MM_FSC_BUFFER_ADDR    (__MM_FSC_BUFFER_TOP - __MM_FSC_BUFFER_LEN) 

    #define __MM_DMX0_DMA_START_ADDR    (__MM_DMX_AVP_START_ADDR)
    #define __MM_DMX1_DMA_START_ADDR    (__MM_DMX_REC_START_ADDR)
    #define __MM_DMX2_DMA_START_ADDR    ((__MM_FSC_BUFFER_TOP - __MM_DMX_REC_LEN)&0XFFFFFFF0)
    #define __MM_DMX3_DMA_START_ADDR	((__MM_DMX2_DMA_START_ADDR - __MM_DMX_REC_LEN)&0XFFFFFFF0)

    #define __MM_DMX0_MAIN_BLK_START_ADDR (__MM_DMX_CPU_BLK_ADDR )
    #define __MM_DMX1_MAIN_BLK_START_ADDR	((__MM_DMX3_DMA_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    #define __MM_DMX2_MAIN_BLK_START_ADDR   ((__MM_DMX1_MAIN_BLK_START_ADDR - __MM_DMX_BLK_BUF_LEN)&0XFFFFFFE0)
    
#if(__MM_DMX2_MAIN_BLK_START_ADDR < __MM_FSC_BUFFER_ADDR)
    #error "__MM_FSC_BUFFER_ADDR too small"
#endif
#if(__MM_FSC_BUFFER_ADDR < __MM_PVR_VOB_BUFFER_ADDR)
    #error "PVR no enough buffer to share with fsc"
#endif
#else
    #define __MM_FSC_BUFFER_LEN     0
#endif

//end of main mem map

//Private mem map
/*
    In HW security mode, some see buffer must be shared by media player,
    so put them together on the top:
    VBV, DMX, TTX
*/

#ifdef _DD_SUPPORT
#define __MM_PRIV_DEC_LEN   0x20000
#define __MM_PRIV_DEC_ADDR (__MM_PRIVATE_TOP_ADDR- __MM_PRIV_DEC_LEN)
#else
#define __MM_PRIV_DEC_LEN   0
#define __MM_PRIV_DEC_ADDR (__MM_PRIVATE_TOP_ADDR- __MM_PRIV_DEC_LEN)
#endif

#define __MM_REAL_PRIVATE_TOP_ADDR  __MM_PRIV_DEC_ADDR

#define __MM_VBV_START_ADDR         ((__MM_REAL_PRIVATE_TOP_ADDR - __MM_VBV_LEN)&0XFFFFFF00)
#define AVC_VBV_ADDR                ((__MM_REAL_PRIVATE_TOP_ADDR - AVC_VBV_LEN)&0XFFFFFF00)   //256 bytes alignment
#define HEVC_VBV_ADDR               ((__MM_REAL_PRIVATE_TOP_ADDR - HEVC_VBV_LEN)&0XFFFFFF00) //256 bytes alignment

#if (AVC_VBV_ADDR <= __MM_VBV_START_ADDR && AVC_VBV_ADDR<=HEVC_VBV_ADDR)
#define VDEC_PRIVATE_START_ADDR     AVC_VBV_ADDR
#elif (HEVC_VBV_ADDR<=__MM_VBV_START_ADDR)
#define VDEC_PRIVATE_START_ADDR     HEVC_VBV_ADDR
#else
#define VDEC_PRIVATE_START_ADDR     __MM_VBV_START_ADDR
#endif

#define __MM_DMX_SEE_BLK_ADDR       ((VDEC_PRIVATE_START_ADDR - __MM_DMX_SEE_BLK_BUF_LEN)&0XFFFFFFE0)
#define __MM_DMX_SEE_BLK_START_ADDR (__MM_DMX_SEE_BLK_ADDR)


#define __MM_SEE_MP_BUF_ADDR    (__MM_DMX_SEE_BLK_ADDR -  __MM_SEE_MP_BUF_LEN)

//move to main
//#define AVC_CMD_QUEUE_ADDR  ((__MM_SEE_MP_BUF_ADDR - AVC_CMD_QUEUE_LEN)&0xffffff00)      //256 bytes alignment
//#define AVC_LAF_FLAG_BUF_ADDR   ((AVC_CMD_QUEUE_ADDR - AVC_LAF_FLAG_BUF_LEN)&0xfffffc00)  //1024 bytes alignment
#define __MM_OSD_BK_ADDR2       ((__MM_SEE_MP_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)//((AVC_LAF_FLAG_BUF_ADDR - __MM_OSD2_LEN)&0XFFFFFFE0)

#define __MM_SEE_DBG_MEM_ADDR      ( __MM_OSD_BK_ADDR2 - __MM_DBG_MEM_LEN)

// for jpeg decoder memmap
#ifdef SD_PVR
#define __MM_FB0_Y_LEN            (736*576 + 1024)
#define __MM_IMG_FB_Y_LEN        (736*576*2 + 1024)
#define __MM_IMG_FB_C_LEN        (__MM_IMG_FB_Y_LEN/2)
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

#ifdef SD_PVR   
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
    //#define __MM_MP_BUFFER_LEN        (__MM_FB_TOP_ADDR - __MM_TTX_P26_DATA_BUF_ADDR)//(__MM_SEE_MP_BUF_LEN - __MM_FB0_Y_LEN * 3 - __MM_FB0_C_LEN * 3)
    //#define __MM_MP_BUFFER_ADDR        __MM_TTX_P26_DATA_BUF_ADDR//(__MM_FB2_C_START_ADDR + __MM_FB2_C_LEN)
#endif

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

#endif //end of VFB_SUPPORT
#endif //end of DRAM_SPLIT


#endif //end of 256M config

#define __MM_VIDEO_FILE_BUF_ADDR    __MM_MP_BUFFER_ADDR
#define __MM_VIDEO_FILE_BUF_LEN     __MM_MP_BUFFER_LEN

#ifdef PLSN_SUPPORT
#define __MM_TABLE_LEN		0x319A00
#define __MM_CAPTURE_LEN	0x400000
#if (defined(M36F_SINGLE_CPU) && defined(SUPPORT_64M_MEM))
#define __MM_CAPTURE_ADDR 	(__MM_PVR_VOB_BUFFER_ADDR & 0x8FFFFFFF)
#define __MM_TABLE_ADDR		((__MM_VBV_START_ADDR&0x8FFFFFFF))
#else
#define __MM_CAPTURE_ADDR 	((__MM_PVR_VOB_BUFFER_ADDR + __MM_AUTOSCAN_DB_BUFFER_LEN) & 0x8FFFFFFF)
#define __MM_TABLE_ADDR		((__MM_CAPTURE_ADDR + __MM_CAPTURE_LEN) & 0x8FFFFFFF)
#endif
#endif

#endif //end of __SYS_MEM_MAP_H

