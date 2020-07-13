/*****************************************************************************
*    Copyrights(C) 2003 Acer Laboratries Inc. All Rights Reserved.
*
*    FILE NAME:        root.c
*
*    DESCRIPTION:     This file contains application's root function - AppInit().
*                 It inits all modules used in the application and creates all the tasks
*                used. It also send a command to play the current tv program.
*
*
*    HISTORY:
*        Date         Author         Version     Notes
*        =========    =========    =========    =========
*        2003-04-19    Xianyu Nie    Ver 0.1        Create File
*        ..............    ......    .        ....            .....
*        2004-11-11     Xionghua        Ver 0.2        modify for m3327
*****************************************************************************/
#include <stddef.h>
#include <version/ver.h>
#include "head_file.h"
#include "./platform/board.h"
#include "./platform/board_cfg/board_cfg.h"
#include "ali_pmu_bin.h"
//#include "win_com.h"
//#include "copper_common/com_api.h"
#include <bus/rtc/rtc.h>
#include <bus/dog/dog.h>
#include <hld/pmu/pmu.h>

#include <api/libdbc/lib_dbc.h>
#include <api/libfs2/fs_main.h>
#ifdef SUPPORT_CAS_A
#include <api/libcas/abel/abel_mcas.h>
#include <api/libcas/abel/NN.h>
#endif
//#include <api/libdbc/lib_dbc.h>
//#include "nocs_test_app.h"
#include "aui_common.h"
#include <aui_os.h>
#include <aui_deca.h>
#include <aui_snd.h>
#include <aui_tsg.h>
#include <aui_dsc.h>
#include <aui_kl.h>
#include <aui_dog.h>
#include <aui_rtc.h>
#include <aui_dmx.h>
#include <aui_nim.h>
#include <aui_vbi.h>
#include <aui_decv.h>
#include <aui_dis.h>
#include <aui_av.h>
#include <aui_osd.h>
#include <aui_tsi.h>
#include <aui_hdmi.h>
#include <aui_pvr.h>
#include <aui_fs.h>
#include <aui_misc.h>
#ifdef _NAND_ENABLE_
#include <bus/nand/ali_nand_dev.h>
#endif
#include <hld/avsync/avsync.h>
#include "copper_common/system_type.h"
#include <boot/boot_common.h>


#ifdef NETWORK_SUPPORT
#include <hld/net/ethtool.h>
#include <api/libnet/libnet.h>

#define MEMORY_CACHE_CONVERT 0x8fffffff

#define MAC_ADDR_ARRAY(a,b,c,d,e,f) {0x##a, 0x##b, 0x##c, 0x##d, 0x##e, 0x##f}
#define IP2UINT32(a,b,c,d) ((a)|((b)<<8)|((c)<<16)|((d)<<24))

/////////////////////////////////////////////////////////////////////////////////////////////////
//#define NETWORK_USE_HARDCODE_MAC   // RD debug use, define to Use MAC address in following defined
#define MAC_ADDR  MAC_ADDR_ARRAY(00,1E,90,22,53,59)
//#define NETWORK_USE_STATIC_IP      // RD debug use, define to use following static IP config
#define STATIC_IP 		IP2UINT32(10,8,5,147)
#define STATIC_SUBMASK 	IP2UINT32(255,255,255,0)
#define STATIC_GATEWAY 	IP2UINT32(10,8,5,254)
#define STATIC_DNS 		IP2UINT32(10,8,1,11)
#define STATIC_DNS2 	IP2UINT32(10,8,1,12)

#ifdef _NESTOR_SUPPORT_
extern int aui_ci_dut_get_ip_cfg(UINT8 *mac, struct ip_local_cfg *cfg);
#endif
extern RET_CODE eth_mac_attach(MAC_CONFIG *cfg);

static int changed_mac(unsigned char * mac_addr);

/* This API will be used by LIB_NIC, to get IP address which was stored in Flash chunk.
 Customer can implement this API.
*/
void get_local_ip_cfg(PIP_LOC_CFG pcfg)
{
//    MEMCPY(pcfg, &system_config.ip_cfg.local_cfg, sizeof(IP_LOC_CFG));
}

static void print_ip_config(struct ip_local_cfg *cfg)
{
	libc_printf("IP:       %d.%d.%d.%d\n", \
		(cfg->ip_addr		) & 0xFF,
		(cfg->ip_addr >>  8) & 0xFF,
		(cfg->ip_addr >> 16) & 0xFF,
		(cfg->ip_addr >> 24) & 0xFF
	);
	libc_printf("Gateway:  %d.%d.%d.%d\n", \
		(cfg->gateway		) & 0xFF,
		(cfg->gateway >>  8) & 0xFF,
		(cfg->gateway >> 16) & 0xFF,
		(cfg->gateway >> 24) & 0xFF
	);
	libc_printf("MASK:     %d.%d.%d.%d\n", \
		(cfg->subnet_mask		) & 0xFF,
		(cfg->subnet_mask >>  8) & 0xFF,
		(cfg->subnet_mask >> 16) & 0xFF,
		(cfg->subnet_mask >> 24) & 0xFF
	);
	libc_printf("DNS:      %d.%d.%d.%d\n", \
		(cfg->dns		) & 0xFF,
		(cfg->dns >>  8) & 0xFF,
		(cfg->dns >> 16) & 0xFF,
		(cfg->dns >> 24) & 0xFF
	);
	libc_printf("DNS2:     %d.%d.%d.%d\n", \
		(cfg->dns2 	 ) & 0xFF,
		(cfg->dns2 >>	8) & 0xFF,
		(cfg->dns2 >> 16) & 0xFF,
		(cfg->dns2 >> 24) & 0xFF
	);
}

void network_callback(UINT32 event_type, UINT32 param) {
    if(NET_MSG_DHCP == event_type && NET_ERR_DHCP_SUCCESS == param) {
        struct ip_local_cfg net_local_cfg;
        libnet_get_ipconfig(&net_local_cfg);

        libc_printf("DHCP get IP success\n");
		print_ip_config(&net_local_cfg);
    }
}

int network_attach() {
    int result = 0;
    UINT8 mac_addr[] = MAC_ADDR;//{ 0x00, 0x1E, 0x90, 0x22, 0x53, 0x59 };

#if (defined(IDE_SUPPORT) || defined(SDIO_SUPPORT) || \
 (defined(NETWORK_SUPPORT) && (SYS_NETWORK_MODULE == SMSC9220)))
    if (sys_ic_get_chip_id() < ALI_S3602F)
    {
        //ATA share pins with flash, disable flash.
        *((volatile UINT32 *)0xb8000090) = (*((volatile UINT32 *)0xb8000090) & 0xf0) | 0x02;
        //Set Pin Mux.
        *((volatile UINT32 *)0xb8000088) |= 0x000000a1;
    }
#endif
#if (SYS_NETWORK_MODULE == SMSC9220)
// GPIO for SMSC9220
#define SMSC9220_A6_GPIO_NUM        31
#define SMSC9220_A7_GPIO_NUM        32
#define SMSC9220_CS_GPIO_NUM        33
#define SMSC9220_FIFO_SEL_GPIO_NUM    34
#define SMSC9220_INT_GPIO_NUM        35
    //Set Pin Mux.
    *((volatile UINT32 *)0xb8000088) |= 0x1000; /* select GPIO[31-35] */
    *((volatile UINT8  *)0xb800008c) &= (~0x04);
//    HAL_GPIO_BIT_DIR_SET(25, HAL_GPIO_O_DIR);
//    HAL_GPIO_BIT_SET(25, 1); /* de-select SD Card */
//    HAL_GPIO_BIT_DIR_SET(SMSC9220_CS_GPIO_NUM, HAL_GPIO_O_DIR); /* LAN_nCS */
//    HAL_GPIO_BIT_SET(SMSC9220_CS_GPIO_NUM, 0);
    SMSC_CONFIG smsc_cfg;
    MEMSET(&smsc_cfg, 0, sizeof(SMSC_CONFIG));

    smsc_cfg.en_gpio_setting = 1;
    smsc_cfg.a6_gpio_position = SMSC9220_A6_GPIO_NUM;
    smsc_cfg.a7_gpio_position = SMSC9220_A7_GPIO_NUM;
    smsc_cfg.cs_gpio_position = SMSC9220_CS_GPIO_NUM;
    smsc_cfg.sel_gpio_position = SMSC9220_FIFO_SEL_GPIO_NUM;
    smsc_cfg.int_gpio_position = SMSC9220_INT_GPIO_NUM;
    smsc_cfg.int_gpio_polar = 0;

    smsc_cfg.en_ata_setting = 1;
    smsc_cfg.ata_timing = 0x02190900; // ATA timing for PIO transfer mode
    // 0: system get MAC address from erom; 1: SW config MAC address
    smsc_cfg.en_mac_setting = 0;
    MEMCPY(smsc_cfg.mac_addr, mac_addr, sizeof(mac_addr));
    result = smsc9220_attach(&smsc_cfg);
#elif (SYS_NETWORK_MODULE == NET_ENC28J60)
    ENC_CONFIG enc_cfg;
    MEMSET(&enc_cfg, 0, sizeof(ENC_CONFIG));
    enc_cfg.init_mac_addr = 1;
    MEMCPY(enc_cfg.mac_addr, mac_addr, sizeof(mac_addr));
/*
    enc_cfg.int_by_gpio = 1; // use interrupt
    enc_cfg.int_position = 54; // depends on board design
    enc_cfg.int_io = HAL_GPIO_I_DIR;
    enc_cfg.int_polar = 0; // depends on board design
    // If the net environment is half-duplex, then don't set this field.
    enc_cfg.link_mode = NET_LINK_FULL;
*/
    result = net_enc28j60_attach(&enc_cfg);
#elif (SYS_NETWORK_MODULE == NET_ALIETHMAC)

#ifdef _NESTOR_SUPPORT_
#if defined(NETWORK_USE_HARDCODE_MAC)
	libc_printf("Use hardcode MAC:  %02X:%02X:%02X:%02X:%02X:%02X\n",
		mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
#else
	changed_mac(mac_addr);
#endif
	board_cfg* cfg = get_board_cfg();
	// reset PHY, it may not work correctly after PMU wakeup
	if (cfg->rmii_rst) {
        	libc_printf("PHY reset\n");
        	chip_gpio_set(cfg->rmii_rst, 0);
	        osal_task_sleep(100);
        	chip_gpio_set(cfg->rmii_rst, 1);
	} else {
        	libc_printf("PHY not reset\n");
	}
#endif

    MAC_CONFIG mac_cfg;
    MEMSET(&mac_cfg, 0, sizeof(MAC_CONFIG));
    MEMCPY(mac_cfg.mac_addr, mac_addr, sizeof(mac_addr));
    //Set phy address
    mac_cfg.phy_addr = 0x05;
    //Set phy mode to RMII
    mac_cfg.phy_mode = NET_PHY_RMII;
    result = eth_mac_attach(&mac_cfg);
#endif
    return result;
}

int changed_mac(unsigned char * mac_addr)
{
	int i = 0;
	long ret = 0;
	struct sto_device *test_flash_dev = NULL;
	UINT8 mac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

	test_flash_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);
	if (test_flash_dev == NULL) {
		libc_printf("Get sto_device fail!\n");
		return 1;
	}
	ret = sto_lseek(test_flash_dev, -5, STO_LSEEK_END);
	if (ret >= 0) {
		ret = sto_read(test_flash_dev, mac, sizeof(mac));
	}
	if (ret != sizeof(mac)) {
		libc_printf("sto_read mac fail, readed %#ld bytes.\n", ret);
		return 1;
	}

	if (!(mac[0] == 0xFF && mac[1] == 0xFF && mac[2] == 0xFF
		&& mac[3] == 0xFF && mac[4] == 0xFF && mac[5] == 0xFF)) {
		libc_printf("\nDefault MAC: ");
		for (i = 0; i < sizeof(mac); i++) {
			libc_printf("%02X ", mac_addr[i]);
		}
		libc_printf(" will covered by ");
		MEMCPY(mac_addr, mac, sizeof(mac));
	}
	libc_printf("MAC: ");
	for (i = 0; i < sizeof(mac); i++) {
		libc_printf("%02X ", mac_addr[i]);
	}
	libc_printf("\n");
	return 0;
}

static int g_config_dhcp_on = 1;
static INT32 system_init_network(void) {
    struct libnet_config netcfg;
    int static_ip_flag = 0;
    struct ip_local_cfg cfg;
	UINT8 flash_mac[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

    if (network_attach()) {
        libc_printf("attach network fail.\n");
        return -1;
    }

    memset(&netcfg, 0, sizeof(struct libnet_config));
    netcfg.cb = network_callback;
    netcfg.lwip_cfg.mem.enable = TRUE;
    netcfg.lwip_cfg.mem.start = (UINT8 *)(__MM_LWIP_MEM_ADDR & MEMORY_CACHE_CONVERT);
    netcfg.lwip_cfg.mem.length = __MM_LWIP_MEM_LEN;

    netcfg.lwip_cfg.memp.enable = TRUE;
    netcfg.lwip_cfg.memp.start = (UINT8 *)(__MM_LWIP_MEMP_ADDR & MEMORY_CACHE_CONVERT);
    netcfg.lwip_cfg.memp.length = __MM_LWIP_MEMP_LEN;

    if (libnet_init(&netcfg)) {
        libc_printf("init libnet error.\n");
        return -1;
    }
#if defined(NETWORK_USE_STATIC_IP)
    g_config_dhcp_on = 0;
#endif

    if (g_config_dhcp_on)
    {
		#ifdef _NESTOR_SUPPORT_
		if (changed_mac(flash_mac)==0)
		{
	        if (aui_ci_dut_get_ip_cfg(flash_mac, &cfg) == 0)
	    	{
	    		// Yes, this is CI Daily test device, let's set Static IP
				libnet_set_ipconfig(&cfg);

				static_ip_flag = 1;
	    	}
		}
		#endif

        // if static_ip_flag == 0, this is normal case, just use DHCP to get IP.
    	if ((static_ip_flag == 0) && (libnet_dhcp_on()))
    	{
            libc_printf("open dhcp error.\n");
            return -1;
        }
    }
    else
    {
    	// This case: RD hard code static IP configure
        cfg.dhcp_on = FALSE;
        cfg.ip_addr = STATIC_IP;
        cfg.dns = STATIC_DNS;
        cfg.dns2 = STATIC_DNS2;
        cfg.gateway = STATIC_GATEWAY;
        cfg.subnet_mask = STATIC_SUBMASK;
        libnet_set_ipconfig(&cfg);
        static_ip_flag = 1;
    }
    if (static_ip_flag)
    {
        libc_printf("Set static IP success\n");
		print_ip_config(&cfg);
    }

    return 0;
}
#endif

aui_hdl g_pHdlNim[2]={NULL};
aui_hdl g_p_hdl_deca=NULL;
aui_hdl g_p_hdl_snd=NULL;
aui_hdl g_p_hdl_tsg=NULL;
aui_hdl g_p_hdl_dsc_aes=NULL;
aui_hdl g_p_hdl_dsc_des=NULL;
aui_hdl g_p_hdl_dog=NULL;
aui_hdl g_p_hdl_rtc=NULL;
aui_hdl g_p_hdl_dmx0=NULL;
aui_hdl g_p_hdl_dmx1=NULL;
aui_hdl g_p_hdl_dmx2=NULL;
aui_hdl g_p_hdl_vbi[2]={NULL};
aui_hdl g_p_handle_player = NULL;
aui_hdl g_p_handle_player_avc = NULL;
aui_hdl g_p_handle_disSD = NULL;
aui_hdl g_p_handle_disHD = NULL;
aui_hdl g_p_handle_decv = NULL;
aui_hdl g_p_handle_decv_avc = NULL;
aui_hdl g_p_hdl_gfx = NULL;
aui_hdl g_p_hdl_hdmi = NULL;

struct scart_device* g_scart_dev = NULL;
struct pan_device*   g_pan_dev = NULL;
struct nim_device*   g_nim_dev = NULL;
struct nim_device*   g_nim_dev2 = NULL;
struct sto_device*   g_sto_dev = NULL;
struct rfm_device*   g_rfm_dev = NULL;
struct ge_device*   g_ge_dev = NULL;
struct snd_device*   g_snd_dev = NULL;
struct ali_nand_device* g_sto_nand_dev = NULL;

#ifdef _BOARD_DB_M3823_02V01_

static UINT8 g_nestor_nim_flag = 0;
#endif

struct boot_vpo_info
{
    enum tvsystem tv_mode;
    UINT8 progressive;
    enum dac_type scart_out;
    enum tvmode tv_ratio;
    enum display_mode display_mode;
    UINT8 dual_output;
};

INT8 g_boot_vpo_active = -1;
static struct boot_vpo_info g_boot_vpo_info;

struct aui_app_tsi_init_para
{
    unsigned long ul_hw_init_val;
    unsigned long ul_tsi_id;
    unsigned long ul_input_src;
    unsigned long ul_tis_port_idx;
    unsigned long ul_dmx_idx;
};

struct aui_app_hdmi_init_para
{
    aui_attr_hdmi attr_hdmi;
    /** the  callback fucntion that hdmi edid is ready.*/
    void (*aui_hdmi_edid_ready_callback)();
    /** the  callback fucntion that hdmi plug out.*/
    void (*aui_hdmi_hot_plug_out_callback)();
    /** the  callback fucntion that hdmi plug out.*/
    void (*aui_hdmi_hot_plug_in_callback)();
    /** the  callback fucntion that hdmi plug out.*/
    void (*aui_hdmi_dbg_msg_callback)();
    /** the  callback fucntion that hdmi plug out.*/
    void (*aui_hdmi_cec_msg_callback)();
    /** the  callback fucntion that hdmi plug out.*/
    void (*aui_hdmi_hdcp_err_callback)();


};

#define ComStrCmp(cmp1, cmp2)   (!STRCMP((UINT8 *)(cmp1), (UINT8 *)(cmp2)))
#define ComStrCat    strcat
static void Ul2HexStr(DWORD Val, PCHAR Str, BOOL fIgnoreZero, BOOL fCapital)
{
    int i, j;
    char num, chr = 'A';
    BOOL fNonZero = FALSE;
    if(!fCapital)
        chr = 'a';
    for(i=0, j=0; i<8; i++)
    {
        num = (Val >> ((7-i)*4)) & 0x0F;
        if(!fNonZero && fIgnoreZero)
        {
            if(!num)
                continue;
            else
                fNonZero = TRUE;
        }
        if(num < 10)
            Str[j++] = '0' + num;
        else
            Str[j++] = chr + num - 0x0A;
    }
    if(!j)
        Str[j++] = (char)'0';
    Str[j] = 0;
}

static void print_buffer_range(DWORD Address, DWORD Size, char *name)
{
#define PRINT_NUM_ITEM  2
#define CONTENT_RESERVED_LEN    12
#define REPLACE_START_POS       (CONTENT_RESERVED_LEN-1)
    char *szTop     = "+------------------------------+";
    (void)szTop; //no use
    char *szContent = "          |                              |";
    char OutBuf[64], TempBuf[30], NumBuf[10];
    int i, j, len, output_len, start_pos;
    Size &= 0x0fffffff;
#ifdef _S3811_
    DWORD Number[PRINT_NUM_ITEM] = {Size, (Address)};
#else
    DWORD Number[PRINT_NUM_ITEM] = {Size, (Address+Size)};
#endif
    char *szPrefix[PRINT_NUM_ITEM] = {"Size=0x", "Next=0x"};
    if(NULL == name)
    {
        AUI_PRINTF("          %s\n", szTop);
        return;
    }
#ifdef _S3811_
    AUI_PRINTF("0x%08x", Address+Size);
#else
    AUI_PRINTF("0x%08x", Address);
#endif
    AUI_PRINTF("%s\n", szTop);
    output_len = STRLEN(szContent) - CONTENT_RESERVED_LEN;
    STRCPY(OutBuf, szContent);
    len = STRLEN(name);
    if(len > output_len)
        len = output_len;
    start_pos = REPLACE_START_POS + (output_len - len)/2;
    for(i=0; i<len; i++)
        OutBuf[i+start_pos] = name[i];
    AUI_PRINTF("%s\n", OutBuf);
    for(j=0; j<PRINT_NUM_ITEM; j++)
    {
        STRCPY(OutBuf, szContent);
        STRCPY(TempBuf, szPrefix[j]);
        Ul2HexStr(Number[j], NumBuf, FALSE, FALSE);
        ComStrCat(TempBuf, NumBuf);
        len = STRLEN(TempBuf);
        if(len > output_len)
            len = output_len;
        start_pos = REPLACE_START_POS + (output_len - len)/2;
        for(i=0; i<len; i++)
            OutBuf[i+start_pos] = TempBuf[i];
        AUI_PRINTF("%s\n", OutBuf);
    }
}

static void flash_remap(void)
{
       
    //the bit24 of the register 0x18000220(0xb8000220) is used to control the user of 
    //high 64M memory(0xAC000000~0xb000000). When bit24 set 1:the high 64M is used by dram,
    //and when bit24 set 0:the high 64M is used by flash. So when the bit24 set 1, the high
    //64M is used by dram, the SYS_FLASH_BASE_ADDR, which is the base address of flash, should be 
    //changed 0xAFC00000 from to 0xBFC000000.
#ifdef _M3702_
    *(volatile UINT32 *)(0xB80832A4) |= 0x1;
    *(volatile UINT32 *)(0xB8070000) |= 0x1;
#else    
    *(volatile UINT32 *)(0xb8000220) |= (0x01<<24);
    
    //The SW always use 0x0FC0_xxxx(0xAFC00000) to access FLASH, but it is for compatibility
    //that some SW may use 0x1FC0_xxxx(0xBFC00000) to access FLASH. When SW use 0x1FC0_xxxx(0xBFC00000)
    //to access FLASH, the register BOOTROM_SPACE_CHANGE(0xb8070000 or 0xb8000110) should be configed.   
    //When this bit0 of (0xb8070000 or 0xb8000110) is '0', access 0x1FC0_xxxx(0xBFC00000) will get boot
    //rom code. If boot rom is finished, SW will get dummy data.
    //When this bit0 of (0xb8070000 or 0xb8000110) is '1', access 0x1FC0_xxxx(0xBFC00000) will get FLASH data.
    #ifdef _M3505_
    *(volatile UINT32 *)(0xb8070000) |= 0x01;
    #else
    *(volatile UINT32 *)(0xb8000110) |= 0x01;
    #endif
#endif    

}

UINT8 lib_nimng_get_nim_play(void)
{
    return 1;
}

//void run_time_integrity_check(void)
//{
//}

#ifndef AUI_3281
void print_memory_layout_dual()
{
    extern UINT heap_start;
    //extern int _end;
    //AUI_PRINTF("\n======== Memory Layout ==========\n");
    AUI_PRINTF("\n\nmain memory mapping\n\n");
    print_buffer_range(0, heap_start, "Code");
    print_buffer_range(heap_start, (__MM_HEAP_TOP_ADDR&0x0fffffff)-(heap_start&0x0fffffff), "Heap");
    print_buffer_range(__MM_TTXSUB_S_TOP_ADDR, 0, "__MM_TTXSUB_S_TOP_ADDR");
    print_buffer_range(__MM_TTXSUB_S_START_ADDR, __MM_TTXSUBT_S_LEN, "__MM_TTXSUB_S_START_ADDR");
    print_buffer_range(__MM_VOID_BUFFER_ADDR, __MM_VOID_BUFFER_LEN, "__MM_VOID_BUFFER_ADDR");
    print_buffer_range(__MM_PRIVATE_TOP_ADDR, 0x0, "__MM_PRIVATE_TOP_ADDR");
    print_buffer_range(__MM_PRIVATE_ADDR, __MM_PRIVATE_LEN, "__MM_PRIVATE_ADDR");
    print_buffer_range(__MM_FB_TOP_ADDR, 0,"__MM_FB_TOP_ADDR");
    print_buffer_range(__MM_DVW_START_ADDR, 0X25FA0, "__MM_DVW_START_ADDR");
    print_buffer_range(MPEG2_BUF_START_ADDR, __MM_FB_LEN, "MPEG2_BUF_START_ADDR");
    print_buffer_range(AVC_MV_ADDR, AVC_MV_LEN, "AVC_MV_ADDR");
    print_buffer_range(AVC_MB_COL_ADDR, AVC_MB_COL_LEN, "AVC_MB_COL_ADDR");
    print_buffer_range(AVC_MB_NEI_ADDR, AVC_MB_NEI_LEN, "AVC_MB_NEI_ADDR");
    print_buffer_range(AVC_LAF_RW_BUF_ADDR, AVC_LAF_RW_BUF_LEN, "AVC_LAF_RW_BUF_ADDR");
    print_buffer_range(AVC_DVIEW_ADDR, AVC_DVIEW_LEN, "AVC_DVIEW_ADDR");
    print_buffer_range(AVC_BUF_START_ADDR,AVC_FB_LEN,"AVC_BUF_START_ADDR");
#if (defined(_M3702_))
    print_buffer_range(HEVC_MV_ADDR,HEVC_MV_LEN,"HEVC_MV_ADDR");
    print_buffer_range(HEVC_MB_NEI_ADDR, HEVC_MB_NEI_LEN, "HEVC_MB_NEI_ADDR");
    print_buffer_range(HEVC_LAF_ADDR, HEVC_LAF_LEN, "HEVC_LAF_ADDR");
    print_buffer_range(HEVC_INNER_ES_ADDR, HEVC_INNER_ES_LEN, "HEVC_INNER_ES_ADDR");
    print_buffer_range(HEVC_INNER_AUX_ADDR, HEVC_INNER_AUX_LEN, "HEVC_INNER_AUX_ADDR");
    print_buffer_range(HEVC_DVIEW_ADDR, HEVC_DVIEW_LEN, "HEVC_DVIEW_ADDR");
    print_buffer_range(HEVC_BUF_START_ADDR, HEVC_FB_LEN, "HEVC_BUF_START_ADDR");
    print_buffer_range(__MM_FB_BOTTOM_ADDR,__MM_FB_BOTTOM_ADDR - HEVC_BUF_START_ADDR, "__MM_FB_BOTTOM_ADDR");
    print_buffer_range(__MM_FB_START_ADDR, __MM_FB_START_ADDR - HEVC_BUF_START_ADDR, "__MM_FB_START_ADDR");
	print_buffer_range(AVC_FB_ADDR, AVC_FB_ADDR - __MM_FB_BOTTOM_ADDR, "AVC_FB_ADDR");
    print_buffer_range(HEVC_FB_ADDR, HEVC_FB_ADDR - __MM_FB_BOTTOM_ADDR, "HEVC_FB_ADDR");
#endif
    print_buffer_range(__MM_NIM_BUFFER_ADDR, __MM_NIM_BUFFER_LEN, "__MM_NIM_BUFFER_ADDR");
    print_buffer_range(__MM_BUF_PVR_TOP_ADDR, 0x0, "__MM_BUF_PVR_TOP_ADDR");
    print_buffer_range(__MM_PVR_VOB_BUFFER_ADDR, __MM_PVR_VOB_BUFFER_LEN, "__MM_PVR_VOB_BUFFER_ADDR");
    print_buffer_range(__MM_DMX_AVP_START_ADDR, __MM_SI_VBV_OFFSET + __MM_DMX_DATA_LEN + __MM_DMX_AVP_LEN, "__MM_DMX_AVP_START_ADDR");
    print_buffer_range(__MM_DMX_REC_START_ADDR, __MM_DMX_REC_LEN, "__MM_DMX_REC_START_ADDR");
    print_buffer_range(__MM_DMX_CPU_BLK_ADDR, __MM_DMX_BLK_BUF_LEN, "__MM_DMX_CPU_BLK_ADDR");
    print_buffer_range(__MM_EPG_BUFFER_START, __MM_EPG_BUFFER_LEN, "__MM_EPG_BUFFER_START");
    print_buffer_range(__MM_GE_START_ADDR, __MM_GE_LEN, "__MM_GE_START_ADDR");
    print_buffer_range(__MM_OSD_BK_ADDR1, __MM_OSD1_LEN, "__MM_OSD_BK_ADDR1");
    print_buffer_range(__MM_OSD_BK_ADDR2_MAIN, __MM_OSD2_LEN, "__MM_OSD_BK_ADDR2_MAIN");
    print_buffer_range(__MM_VCAP_FB_ADDR, __MM_VCAP_FB_SIZE, "__MM_VCAP_FB_ADDR");
    print_buffer_range(__MM_OSD_VSRC_MEM_ADDR, OSD_VSRC_MEM_MAX_SIZE, "__MM_OSD_VSRC_MEM_ADDR");
    print_buffer_range(__MM_LWIP_MEM_ADDR, __MM_LWIP_MEM_LEN, "__MM_LWIP_MEM_ADDR");
    print_buffer_range(__MM_NIM_DVBT2_BUFFER_ADDR, __MM_NIM_DVBT2_BUFFER_LEN, "__MM_NIM_DVBT2_BUFFER_ADDR");
    print_buffer_range(__MM_NIM_DVBC_BUFFER_ADDR,__MM_NIM_DVBC_BUFFER_LEN, "__MM_NIM_DVBC_BUFFER_ADDR");
    print_buffer_range(__MM_LWIP_MEMP_ADDR, __MM_LWIP_MEMP_LEN, "__MM_LWIP_MEMP_ADDR");
    print_buffer_range(__MM_USB_START_ADDR, __MM_USB_DMA_LEN, "__MM_USB_START_ADDR");
    print_buffer_range(__MM_TTX_SUB_PAGE_BUF_ADDR, __MM_TTX_SUB_PAGE_LEN, "__MM_TTX_SUB_PAGE_BUF_ADDR");
    print_buffer_range(__MM_TTX_P26_NATION_BUF_ADDR, __MM_TTX_P26_NATION_LEN, "__MM_TTX_P26_NATION_BUF_ADDR");
    print_buffer_range(__MM_TTX_P26_DATA_BUF_ADDR, __MM_TTX_P26_DATA_LEN, "__MM_TTX_P26_DATA_BUF_ADDR");
    print_buffer_range(__MM_TTX_BS_START_ADDR, __MM_TTX_BS_LEN, "__MM_TTX_BS_START_ADDR");
    print_buffer_range(__MM_TTX_PB_START_ADDR, __MM_TTX_PB_LEN, "__MM_TTX_PB_START_ADDR");
    print_buffer_range(__MM_ATSC_CC_PB_START_ADDR, __MM_ATSC_CC_PB_LEN, "__MM_ATSC_CC_PB_START_ADDR");
    print_buffer_range(__MM_ATSC_CC_BS_START_ADDR, __MM_ATSC_CC_BS_LEN, "__MM_ATSC_CC_BS_START_ADDR");
    print_buffer_range(__MM_SUB_BS_START_ADDR, __MM_SUB_BS_LEN, "__MM_SUB_BS_START_ADDR");
    print_buffer_range(__MM_SUB_HW_DATA_ADDR, __MM_SUB_HW_DATA_LEN, "__MM_SUB_HW_DATA_ADDR");
    print_buffer_range(__MM_SUB_PB_START_ADDR, __MM_SUB_PB_LEN, "__MM_SUB_PB_START_ADDR");
    print_buffer_range(__MM_DCII_SUB_BS_START_ADDR, __MM_DCII_SUB_BS_LEN, "__MM_DCII_SUB_BS_START_ADDR");
    print_buffer_range(__MM_SUBT_ATSC_SEC_ADDR, __MM_SUBT_ATSC_SEC_LEN, "__MM_SUBT_ATSC_SEC_ADDR");
    print_buffer_range(__MM_ISDBTCC_BS_START_ADDR, __MM_ISDBTCC_BS_LEN, "__MM_ISDBTCC_BS_START_ADDR");
    print_buffer_range(__MM_ISDBTCC_PB_START_ADDR, __MM_ISDBTCC_PB_LEN, "__MM_ISDBTCC_PB_START_ADDR");
    print_buffer_range(__MM_CPU_DBG_MEM_ADDR, __MM_DBG_MEM_LEN, "__MM_CPU_DBG_MEM_ADDR");
    print_buffer_range(__MM_AUTOSCAN_DB_BUFFER_ADDR, __MM_AUTOSCAN_DB_BUFFER_ADDR - __MM_PVR_VOB_BUFFER_ADDR, "__MM_AUTOSCAN_DB_BUFFER_ADDR");
    print_buffer_range(__MM_PRIV_DEC_ADDR, __MM_PRIV_DEC_LEN, "__MM_PRIV_DEC_ADDR");
    print_buffer_range(__MM_REAL_PRIVATE_TOP_ADDR, __MM_REAL_PRIVATE_TOP_ADDR - __MM_PRIV_DEC_ADDR, "__MM_REAL_PRIVATE_TOP_ADDR");
    print_buffer_range(__MM_VBV_START_ADDR,__MM_VBV_LEN, "__MM_VBV_START_ADDR");
    print_buffer_range(__MM_REAL_PRIVATE_TOP_ADDR, __MM_REAL_PRIVATE_TOP_ADDR - __MM_PRIV_DEC_ADDR, "__MM_REAL_PRIVATE_TOP_ADDR");
    print_buffer_range(__MM_VBV_START_ADDR, __MM_VBV_LEN, "__MM_VBV_START_ADDR");
    print_buffer_range(__MM_MAF_START_ADDR, __MM_MAF_LEN, "__MM_MAF_START_ADDR");
    print_buffer_range(AVC_VBV_ADDR, AVC_VBV_LEN, "AVC_VBV_ADDR");
#if (defined(_M3702_))
    print_buffer_range(HEVC_VBV_ADDR, HEVC_VBV_LEN, "HEVC_VBV_ADDR");
    print_buffer_range(HEVC_PICTURE_SYNTAX_BUF_ADDR, HEVC_PICTURE_SYNTAX_LEN, "HEVC_PICTURE_SYNTAX_BUF_ADDR");
    print_buffer_range(HEVC_EP_QUEUE_BUF_ADDR, HEVC_EP_QUEUE_LEN, "HEVC_EP_QUEUE_BUF_ADDR");
    print_buffer_range(HEVC_CMD_QUEUE_BUF_ADDR, HEVC_CMD_QUEUE_LEN, "HEVC_CMD_QUEUE_BUF_ADDR");
//IFCP function is just supported on 3702 chip
	print_buffer_range(__MM_IFCP_BUFF_ADDR, __MM_IFCP_BUFF_LEN, "__MM_IFCP_BUFF_ADDR");
#endif
	print_buffer_range(__MM_DMX_SEE_BLK_ADDR, __MM_DMX_SEE_BLK_BUF_LEN, "__MM_DMX_SEE_BLK_ADDR");
    print_buffer_range(__MM_DMX_SEE_BLK_START_ADDR, __MM_DMX_SEE_BLK_START_ADDR-__MM_DMX_SEE_BLK_ADDR, "__MM_DMX_SEE_BLK_START_ADDR");
    print_buffer_range(__MM_SEE_MP_BUF_ADDR, __MM_SEE_MP_BUF_LEN, "__MM_SEE_MP_BUF_ADDR");
//STILL_PICTURE function is just supported on 3702 chip
#if (defined(_M3702_))
	print_buffer_range(__MM_STILL_PICTURE_MEM_ADDR, __MM_STILL_PICTURE_MEM_LEN, "__MM_STILL_PICTURE_MEM_ADDR");
#endif
	print_buffer_range(AVC_CMD_QUEUE_ADDR, AVC_CMD_QUEUE_LEN, "AVC_CMD_QUEUE_ADDR");
    print_buffer_range(AVC_LAF_FLAG_BUF_ADDR, AVC_LAF_FLAG_BUF_LEN, "AVC_LAF_FLAG_BUF_ADDR");
    print_buffer_range(__MM_OSD_BK_ADDR2, __MM_OSD2_LEN, "__MM_OSD_BK_ADDR2");
    print_buffer_range(__MM_SEE_DBG_MEM_ADDR, __MM_DBG_MEM_LEN, "__MM_SEE_DBG_MEM_ADDR");
    print_buffer_range(__MM_FB0_Y_START_ADDR, __MM_FB0_Y_LEN, "__MM_FB0_Y_START_ADDR");
    print_buffer_range(__MM_FB0_C_START_ADDR, __MM_FB0_C_LEN, "__MM_FB0_C_START_ADDR");
    print_buffer_range(__MM_FB1_Y_START_ADDR,__MM_FB1_Y_LEN, "__MM_FB1_Y_START_ADDR");
    print_buffer_range(__MM_FB1_C_START_ADDR, __MM_FB1_C_LEN, "__MM_FB1_C_START_ADDR");
    print_buffer_range(__MM_FB2_Y_START_ADDR,__MM_FB2_Y_LEN,"__MM_FB2_Y_START_ADDR");
    print_buffer_range(__MM_FB2_C_START_ADDR, __MM_FB2_C_LEN, "__MM_FB2_C_START_ADDR");
    print_buffer_range(__MM_MP_BUFFER_ADDR, __MM_MP_BUFFER_LEN, "__MM_MP_BUFFER_ADDR");
    print_buffer_range(__MM_DBG_MEM_ADDR, __MM_DBG_MEM_ADDR - __MM_CPU_DBG_MEM_ADDR, "__MM_DBG_MEM_ADDR");
    print_buffer_range(__MM_HEAP_TOP_ADDR, __MM_HEAP_TOP_ADDR - __MM_DBG_MEM_ADDR, "__MM_HEAP_TOP_ADDR++++++++++++++++++++++++++++++++");
    print_buffer_range(__MM_CPU_DBG_MEM_ADDR, __MM_DBG_MEM_LEN, "CPU debug buffer ");
    print_buffer_range(__MM_EPG_BUFFER_START ,__MM_EPG_BUFFER_LEN, "EPG_BUFFER ");
    print_buffer_range(__MM_USB_START_ADDR, __MM_USB_DMA_LEN,"USB_START_");
    print_buffer_range(__MM_DMX_CPU_BLK_ADDR, __MM_DMX_BLK_BUF_LEN,"__MM_DMX_CPU_BLK_ADDR");
    print_buffer_range(__MM_LWIP_MEMP_ADDR, __MM_LWIP_MEMP_LEN,"__MM_LWIP_MEMP_ADDR");
    print_buffer_range(__MM_LWIP_MEM_ADDR, __MM_LWIP_MEM_LEN,"__MM_LWIP_MEM_ADDR");
    print_buffer_range(__MM_AUTOSCAN_DB_BUFFER_ADDR, __MM_AUTOSCAN_DB_BUFFER_LEN,"__MM_AUTOSCAN_DB_BUFFER_ADDR");
    print_buffer_range(__MM_OSD_VSRC_MEM_ADDR, OSD_VSRC_MEM_MAX_SIZE, "__MM_OSD_VSRC_MEM_ADDR ");
    print_buffer_range(__MM_VCAP_FB_ADDR, __MM_VCAP_FB_SIZE, "__MM_VCAP_FB_ADDR ");
    print_buffer_range(__MM_OSD_BK_ADDR1, __MM_OSD1_LEN, "__MM_OSD_BK_ADDR1 ");
    print_buffer_range(__MM_GE_START_ADDR, __MM_GE_LEN, "__MM_GE_START_ADDR ");
    print_buffer_range(__MM_PVR_VOB_BUFFER_ADDR,__MM_PVR_VOB_BUFFER_LEN , "VOB cache");
    print_buffer_range(__MM_DMX_REC_START_ADDR, __MM_DMX_REC_LEN,"__MM_DMX_REC_START_ADDR");
    print_buffer_range(__MM_DMX_AVP_START_ADDR,__MM_SI_VBV_OFFSET + __MM_DMX_DATA_LEN + __MM_DMX_AVP_LEN , "DMX AVP ");

    print_buffer_range(AVC_LAF_RW_BUF_ADDR,AVC_LAF_RW_BUF_LEN , "AVC_LAF_RW_BUF_ADDR ");
    print_buffer_range(AVC_MB_NEI_ADDR, AVC_MB_NEI_LEN, "AVC_MB_NEI_ADDR ");
    print_buffer_range(AVC_MB_COL_ADDR, AVC_MB_COL_LEN, " AVC_MB_COL_ADDR");
    print_buffer_range(AVC_MV_ADDR, AVC_MV_LEN, "AVC_MV_ADDR ");
    print_buffer_range(AVC_DVIEW_ADDR,AVC_DVIEW_LEN , "AVC_DVIEW_ADDR ");
    print_buffer_range(AVC_FB_ADDR, AVC_FB_LEN, "AVC_FB_ADDR ");
    print_buffer_range(__MM_FB_TOP_ADDR, 0, "Frame buffer top memory");
    print_buffer_range(__MM_VIDEO_FILE_BUF_ADDR, __MM_VIDEO_FILE_BUF_LEN, "Media buffer");
    AUI_PRINTF("\n\nprivate memory mapping\n\n");
#ifdef DUAL_ENABLE
    print_buffer_range(__MM_SEE_DBG_MEM_ADDR,__MM_DBG_MEM_LEN , "SEE debug");
#endif
    print_buffer_range(__MM_SUB_PB_START_ADDR,__MM_SUB_PB_LEN , "SUB_PB_START ");
    print_buffer_range(__MM_SUB_HW_DATA_ADDR,__MM_SUB_HW_DATA_LEN , "__MM_SUB_HW_DATA_ADDR ");
    print_buffer_range(__MM_SUB_BS_START_ADDR,__MM_SUB_BS_LEN , "SUB_BS_START_ ");
    print_buffer_range(__MM_OSD_BK_ADDR2, __MM_OSD2_LEN, "__MM_OSD_BK_ADDR2 ");
    print_buffer_range(AVC_LAF_FLAG_BUF_ADDR, AVC_LAF_FLAG_BUF_LEN, "AVC_LAF_FLAG_BUF_ADDR ");
    print_buffer_range(AVC_CMD_QUEUE_ADDR, AVC_CMD_QUEUE_LEN, "AVC_CMD_QUEUE_ADDR ");
#ifdef DUAL_ENABLE
    print_buffer_range(__MM_SEE_MP_BUF_ADDR,__MM_SEE_MP_BUF_LEN , " __MM_SEE_MP_BUF_ADDR");
#endif
    print_buffer_range(__MM_TTX_P26_DATA_BUF_ADDR, __MM_TTX_P26_DATA_LEN, "TTX_P26_DATA_ ");
    print_buffer_range(__MM_TTX_P26_NATION_BUF_ADDR,__MM_TTX_P26_NATION_LEN , " TTX_P26_NATION");
    print_buffer_range(__MM_TTX_SUB_PAGE_BUF_ADDR, __MM_TTX_SUB_PAGE_LEN, "TTX_SUB_PAGE ");
    print_buffer_range(__MM_TTX_PB_START_ADDR, __MM_TTX_PB_LEN, "TTX_PB_START ");
    print_buffer_range(__MM_TTX_BS_START_ADDR, __MM_TTX_BS_LEN, "TTX_BS_START ");
    print_buffer_range(__MM_DMX_SEE_BLK_ADDR,__MM_DMX_BLK_BUF_LEN , "__MM_DMX_SEE_BLK_ADDR ");
    print_buffer_range(AVC_VBV_ADDR,AVC_VBV_LEN , "AVC_VBV_ADDR ");
    print_buffer_range(__MM_VBV_START_ADDR,__MM_VBV_LEN , "__MM_VBV_START_ADDR ");
    AUI_PRINTF("\n\nshare memory mapping\n\n");
#ifdef DUAL_ENABLE
    print_buffer_range(__MM_SHARE_BASE_ADDR,__MM_SHARED_MEM_LEN , "__MM_SHARE_BASE_ADDR ");
    print_buffer_range(__MM_VOID_BUFFER_ADDR, __MM_VOID_BUFFER_LEN , "void buffer to customer");
#endif
    print_buffer_range(__MM_HIGHEST_ADDR, 0, "Total Memory");
    print_buffer_range(0, 0, NULL);

}
#endif

void pmu_notify(UINT32 param)
{
 #if 0
 //   pmu_m36_en();
  if((ALI_S3811==sys_ic_get_chip_id()) && (sys_ic_get_rev_id() >= IC_REV_1))
   {
         ap_send_msg(CTRL_MSG_SUBTYPE_KEY_UI, V_KEY_POWER, TRUE);
        #ifdef AUTO_OTA
        extern BOOL m_ForFakeStandby;
        if(m_ForFakeStandby )
         ota_power_flag=TRUE;
        #endif
      }
    if(((ALI_C3701==sys_ic_get_chip_id()) && (sys_ic_get_rev_id() >= IC_REV_1))||(ALI_S3503==sys_ic_get_chip_id()))
   {
         ap_send_msg(CTRL_MSG_SUBTYPE_KEY_UI, V_KEY_POWER, TRUE);
        #ifdef AUTO_OTA
        extern BOOL m_ForFakeStandby;
        if(m_ForFakeStandby )
         ota_power_flag=TRUE;
        #endif
      }
    if((ALI_S3811==sys_ic_get_chip_id()) && (sys_ic_get_rev_id() == IC_REV_0))
      {
        ap_send_msg(CTRL_MSG_SUBTYPE_KEY_UI, V_KEY_POWER, TRUE);
        #ifdef AUTO_OTA
        extern BOOL m_ForFakeStandby;
        if(m_ForFakeStandby )
         ota_power_flag=TRUE;
        #endif
    }
 #endif
    return ;
}

extern void pmu_gpio_disable(void);

extern INT32 vdec_s3601_de_release(void *pdev,struct release_info *pRelease_Info);//UINT8 utop_idx,UINT8 frm_array_idx)
    /** the  callback fucntion that hdmi edid is ready.*/
void hdmi_edid_ready_callback()
{
    AUI_PRINTF("\r\n func:[%s]",__FUNCTION__);
}

/** the  callback fucntion that hdmi plug out.*/
void hdmi_hot_plug_out_callback()
{
    AUI_PRINTF("\r\n func:[%s]",__FUNCTION__);
}

/** the  callback fucntion that hdmi plug out.*/
void hdmi_hot_plug_in_callback()
{
    AUI_PRINTF("\r\n func:[%s]",__FUNCTION__);
}

/** the  callback fucntion that hdmi plug out.*/
void hdmi_dbg_msg_callback()
{
    AUI_PRINTF("\r\n func:[%s]",__FUNCTION__);
}

/** the  callback fucntion that hdmi plug out.*/
void hdmi_cec_msg_callback()
{
    AUI_PRINTF("\r\n func:[%s]",__FUNCTION__);
}

/** the  callback fucntion that hdmi plug out.*/
void hdmi_hdcp_err_callback()
{
    //AUI_PRINTF("\r\n func:[%s]",__FUNCTION__);
}

static RET_CODE get_sysinfo_from_bl(UINT32 flag, UINT8 *param, UINT32 len)
{
    UINT32 magic_number = 0;
    struct TRANS_SYSINFO *p_trans = NULL;

    if (NULL == param) {
        return RET_FAILURE;
    }

    magic_number = GET_DWORD(STAGE_TRANSFER_ADDR2);
    p_trans = (struct TRANS_SYSINFO *)GET_DWORD(STAGE_TRANSFER_ADDR3);

    if (ALI_TRANSFER_MAGIC_NUM == magic_number) {
        if (TRANS_VDEC_TYPE == flag) {
            if (len > sizeof(struct TRANS_VDEC_INFO)) {
                return RET_FAILURE;
            }

            memcpy(param, (UINT8 *)&(p_trans->vdec_info), len);

            return RET_SUCCESS;
        }

        if (TRANS_VPO_TYPE == flag) {
            if (len > sizeof(struct TRANS_VPO_INFO)) {
                return RET_FAILURE;
            }

            memcpy(param, (UINT8 *)&(p_trans->vpo_info), len);
            return RET_SUCCESS;
        }
    }

    return RET_FAILURE;
}

static BOOL vpo_is_open()
{
    if ((((*(unsigned long *)0xb8006000) & 1)
            && (ALI_S3503 == sys_ic_get_chip_id() || ALI_C3702 == sys_ic_get_chip_id() || ALI_C3503D == sys_ic_get_chip_id() || ALI_C3711C == sys_ic_get_chip_id())) ||
       ((((*(unsigned long *)0xb8006010) & 1) && ALI_S3821 == sys_ic_get_chip_id())) ||
       ((((*(unsigned long *)0xb8006010) & 1) && ALI_C3505 == sys_ic_get_chip_id())) ||
	   (ALI_S3281 == sys_ic_get_chip_id())){
        return TRUE;
    } else {
        return FALSE;
    }
}

static BOOL bl_data_is_progressive(enum TV_SYS_TYPE tvmode)
{
    BOOL bprogressive =FALSE;

#ifdef HDTV_SUPPORT
    switch (tvmode)
    {
    case TV_MODE_576P:
    case TV_MODE_480P:
    case TV_MODE_720P_50:
    case TV_MODE_720P_60:
    case TV_MODE_1080P_25:
    case TV_MODE_1080P_30:
    case TV_MODE_1080P_24:
    case TV_MODE_1080P_50:
    case TV_MODE_1080P_60:
        bprogressive = TRUE;
        break;
    case TV_MODE_1080I_25:
    case TV_MODE_1080I_30:
        bprogressive = FALSE;
        break;
    default:
        break;
    }
#endif
    return bprogressive;
}

//this covertion is from boot loader, can not be chagned
static enum tvsystem bl_tvsys_hd_to_sd(enum tvsystem tvsys)
{
    if ((PAL_M == tvsys) || (PAL_N == tvsys)) {
        return tvsys;
    } else if ((NTSC == tvsys) || (LINE_720_30 == tvsys) || (LINE_1080_30 == tvsys) || (LINE_1080_60 == tvsys)) {
        return NTSC;
    } else {
        return PAL;
    }
}

static enum tvsystem bl_get_tvsys(UINT8 tv_mode)
{
    enum tvsystem tvsys;
    switch(tv_mode) {
    	case TV_MODE_PAL:
            tvsys = PAL;
            break;
    	case TV_MODE_PAL_N:
            tvsys  = PAL_N;
            break;
    	case TV_MODE_NTSC358:
            tvsys  = NTSC;
            break;
    	case TV_MODE_PAL_M:
            tvsys  = PAL_M;
            break;
    	case TV_MODE_NTSC443:
            tvsys  = NTSC_443;
            break;
    	case TV_MODE_SECAM:
            tvsys  = SECAM;
            break;
    	case TV_MODE_480P:
            tvsys  = NTSC;
            break;
    	case TV_MODE_576P:
            tvsys  = PAL;
            break;
    	case TV_MODE_720P_50:
            tvsys  = LINE_720_25;
            break;
    	case TV_MODE_720P_60:
            tvsys  = LINE_720_30;
            break;
    	case TV_MODE_1080I_25:
            tvsys  = LINE_1080_25;
            break;
    	case TV_MODE_1080I_30:
            tvsys  = LINE_1080_30;
            break;
    	case TV_MODE_1080P_25:
            tvsys  = LINE_1080_25;
            break;
    	case TV_MODE_1080P_30:
            tvsys  = LINE_1080_30;
            break;
    	case TV_MODE_1080P_24:
            tvsys  = LINE_1080_24;
            break;
    	case TV_MODE_1080P_50:
            tvsys  = LINE_1080_50;
            break;
    	case TV_MODE_1080P_60:
            tvsys  = LINE_1080_60;
            break;
        default:
    		tvsys  = LINE_1080_25;
            break;
    }
	return tvsys;
}

static enum display_mode bl_get_display_mode(UINT8 display_mode, UINT8 tv_ratio)
{
    enum display_mode e_display_mode;

    if(tv_ratio == TV_ASPECT_RATIO_AUTO) {
        e_display_mode = NORMAL_SCALE;
    } else if(display_mode == DISPLAY_MODE_LETTERBOX) {
        if (tv_ratio == TV_ASPECT_RATIO_43)
            e_display_mode = LETTERBOX;
        else
            e_display_mode = PILLBOX;
    } else if(display_mode == DISPLAY_MODE_PANSCAN) {
        if (tv_ratio == TV_ASPECT_RATIO_43)
            e_display_mode = PANSCAN;
        else
            e_display_mode = VERTICALCUT;
    } else {
        e_display_mode = NORMAL_SCALE;
    }
    return e_display_mode;
}


static RET_CODE get_default_vpoinfo( struct TRANS_VPO_INFO* vpo_info)
{

    if(sys_ic_hd_output_is_enabled()){
        vpo_info->tv_mode = TV_MODE_1080I_25;
    }else{//if chip only support SD output,tv mode should be set to PAL
        vpo_info->tv_mode = TV_MODE_PAL;
    }

    //you can set tv ration and display mode to change display different
    vpo_info->tv_ratio = TV_ASPECT_RATIO_AUTO;
    vpo_info->display_mode = DISPLAY_MODE_PANSCAN;
    vpo_info->scart_out = SCART_YUV;

    return RET_SUCCESS;

}

static BOOL is_bootloader_show_logo_keeping_solution()
{
#ifndef SD_PVR
    struct TRANS_VPO_INFO vpo_info;
    INT32 ret = 0;

    if (g_boot_vpo_active < 0) {
        MEMSET(&vpo_info, 0, sizeof(vpo_info));
                
        ret = get_default_vpoinfo(&vpo_info);        
        if (ret != RET_SUCCESS) {
            //get info from boot loader failed, just close vpo when init vpo, or there is a problem about display
            libc_printf("\n AppInit : get_default_vpoinfo fail \n");
            return FALSE;
        }

        g_boot_vpo_info.tv_mode = bl_get_tvsys(vpo_info.tv_mode);
        g_boot_vpo_info.progressive = bl_data_is_progressive(vpo_info.tv_mode);
        g_boot_vpo_info.tv_ratio = (vpo_info.tv_ratio == TV_ASPECT_RATIO_169) ? TV_16_9 : TV_4_3;
        g_boot_vpo_info.display_mode = bl_get_display_mode(vpo_info.display_mode, vpo_info.tv_ratio);
        g_boot_vpo_info.scart_out = (vpo_info.scart_out == SCART_YUV) ? YUV_1: RGB_1;

        //info get from bootloader, only affect YUV output
	    if (vpo_info.tv_mode == TV_MODE_PAL || vpo_info.tv_mode == TV_MODE_NTSC358) {
	        g_boot_vpo_info.dual_output = 0;
	    } else {
	        g_boot_vpo_info.dual_output = 1;
	    }

	    libc_printf("boot tv mode: %d(%d), tv ratio: %d, display_mode: %d, scart_out: %d\n",
	        g_boot_vpo_info.tv_mode, vpo_info.tv_mode, g_boot_vpo_info.tv_ratio,
	        g_boot_vpo_info.display_mode, g_boot_vpo_info.scart_out);

	    if( TRUE == vpo_is_open())
        {
            g_boot_vpo_active = 1;
        }
        else
        {
            g_boot_vpo_active = 0;
        }
    }
#endif

    if(g_boot_vpo_active == 1 &&
        (sys_ic_get_chip_id() == ALI_S3503 ||
        sys_ic_get_chip_id() == ALI_S3821 ||
        sys_ic_get_chip_id() == ALI_S3281 ||
        sys_ic_get_chip_id() == ALI_C3505 ||
		sys_ic_get_chip_id() == ALI_C3503D ||
		sys_ic_get_chip_id() == ALI_C3711C ||
        sys_ic_get_chip_id() == ALI_C3702)) {
        libc_printf("===Devin  keep showing logo ===\n");
        return TRUE;
    }
    return FALSE;
}

void InitVPPara(struct vp_init_info *pVPInitInfo)
{
    int i;
    //api set backgound color]
    pVPInitInfo->t_init_color.u_y = 0x10;
    pVPInitInfo->t_init_color.u_cb= 0x80;
    pVPInitInfo->t_init_color.u_cr = 0x80;
    //set advanced control
    pVPInitInfo->b_brightness_value = 0;
    pVPInitInfo->f_brightness_value_sign = TRUE;
    pVPInitInfo->w_contrast_value= 0;
    pVPInitInfo->f_contrast_sign= TRUE;
    pVPInitInfo->w_saturation_value= 0;
    pVPInitInfo->f_saturation_value_sign= TRUE;
    pVPInitInfo->w_sharpness= 0;
    pVPInitInfo->f_sharpness_sign= TRUE;
    pVPInitInfo->w_hue_sin= 0;
    pVPInitInfo->f_hue_sin_sign= TRUE;
    pVPInitInfo->w_hue_cos= 0;
    pVPInitInfo->f_hue_cos_sign= TRUE;
    pVPInitInfo->b_ccir656enable= FALSE;
    //VPO_Zoom
    pVPInitInfo->t_src_rect.u_start_x= 0;
    pVPInitInfo->t_src_rect.u_width= PICTURE_WIDTH;
    pVPInitInfo->t_src_rect.u_start_y= 0;
    pVPInitInfo->t_src_rect.u_height= PICTURE_HEIGHT;
    pVPInitInfo->dst_rect.u_start_x= 0;
    pVPInitInfo->dst_rect.u_width= SCREEN_WIDTH;
    pVPInitInfo->dst_rect.u_start_y= 0;
    pVPInitInfo->dst_rect.u_height= SCREEN_HEIGHT;
    //VPO_SetAspect
    if(g_boot_vpo_active == 1){
        pVPInitInfo->e_tvaspect= g_boot_vpo_info.tv_ratio;
        pVPInitInfo->e_display_mode= g_boot_vpo_info.display_mode;//LETTERBOX;
    }else{
        pVPInitInfo->e_tvaspect= TV_4_3;
        pVPInitInfo->e_display_mode= NORMAL_SCALE;//LETTERBOX;
    }
    pVPInitInfo->u_nonlinear_change_point= 111;
    pVPInitInfo->u_pan_scan_offset= 90;
    //VPO_SetOutput
    for(i=0;i<VP_DAC_TYPENUM;i++)
        pVPInitInfo->p_dac_config[i].b_enable= FALSE;
    /** here we just config yuv output to hd tv_encoder **/
    /** init of dac of cvbs,if you need cvbs output,config this **/
#ifdef _SD_ONLY_
    pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = TRUE;
#else
    if(g_boot_vpo_active == 1) {
        if (g_boot_vpo_info.scart_out == YUV_1 && g_boot_vpo_info.dual_output == 0)
            pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = TRUE;
        else
            pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = FALSE;
    } else {
        pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = FALSE;
    }
#endif
    pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].t_dac_index.u_dac_first= CVBS_DAC;
    pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].e_vgamode= VGA_NOT_USE;
    pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_progressive= FALSE;
    /** cvbs config end **/
    /** init of dac of yuv,if you have yuv output,config this **/
#ifdef _SD_ONLY_
    pVPInitInfo->p_dac_config[YUV_1].b_enable= FALSE;
#else
    pVPInitInfo->p_dac_config[YUV_1].b_enable= TRUE;
#endif
    pVPInitInfo->p_dac_config[YUV_1].t_dac_index.u_dac_first= YUV_DAC_Y;
    pVPInitInfo->p_dac_config[YUV_1].t_dac_index.u_dac_second= YUV_DAC_U;
    pVPInitInfo->p_dac_config[YUV_1].t_dac_index.u_dac_third= YUV_DAC_V;
    pVPInitInfo->p_dac_config[YUV_1].e_vgamode= VGA_NOT_USE;
    if(g_boot_vpo_active == 1) {
        pVPInitInfo->p_dac_config[YUV_1].b_progressive = g_boot_vpo_info.progressive;//boot loader default value
    } else {
        pVPInitInfo->p_dac_config[YUV_1].b_progressive = TRUE;//default value 720p60
    }
    /** yuv config end **/

    /** init of dac of rgb,if you have rgb output,config this **/
    if(g_boot_vpo_active == 1 && g_boot_vpo_info.scart_out == RGB_1) {
        pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].b_enable = TRUE;
        pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = TRUE;
        pVPInitInfo->p_dac_config[YUV_1].b_enable= FALSE;
    } else {
        pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].b_enable = FALSE;
    }
    pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].t_dac_index.u_dac_first = RGB_DAC_R;
    pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].t_dac_index.u_dac_second= RGB_DAC_G;
    pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].t_dac_index.u_dac_third= RGB_DAC_B;
    pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].e_vgamode= VGA_NOT_USE;
    pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].b_progressive= FALSE;
    /** yuv config end **/
    /** config others **/
#ifdef _SD_ONLY_
    pVPInitInfo->e_tvsys= PAL;
#else
    if(g_boot_vpo_active == 1)
        pVPInitInfo->e_tvsys= g_boot_vpo_info.tv_mode;//boot loader default value
    else
        pVPInitInfo->e_tvsys= LINE_720_30;
#endif
    pVPInitInfo->b_win_on_off= FALSE;
    pVPInitInfo->u_win_mode= VPO_MAINWIN;//|VPO_PIPWIN;
    pVPInitInfo->t_pipcall_back.request_callback= NULL;
    pVPInitInfo->t_pipcall_back.release_callback= NULL;
    //pVPInitInfo->tMPCallBack.RequestCallback = (T_MPRequest)vdec_s3601_de_request;
    //pVPInitInfo->tMPCallBack.ReleaseCallback = (T_MPRelease)vdec_s3601_de_release;
    pVPInitInfo->p_src_change_call_back=NULL;
}

void InitVPPara_sd(struct vp_init_info *pVPInitInfo)
{
    int i;
    MEMSET(pVPInitInfo, 0, sizeof(struct vp_init_info));
    pVPInitInfo->device_priority = VPO_AUTO_DUAL_OUTPUT;    // S3602F use VCAP
    //api set backgound color]
    pVPInitInfo->t_init_color.u_y= 0x10;
    pVPInitInfo->t_init_color.u_cb= 0x80;
    pVPInitInfo->t_init_color.u_cr= 0x80;
    //set advanced control
    pVPInitInfo->b_brightness_value= 0;
    pVPInitInfo->f_brightness_value_sign= TRUE;
    pVPInitInfo->w_contrast_value= 0;
    pVPInitInfo->f_contrast_sign= TRUE;
    pVPInitInfo->w_saturation_value= 0;
    pVPInitInfo->f_saturation_value_sign= TRUE;
    pVPInitInfo->w_sharpness= 0;
    pVPInitInfo->f_sharpness_sign= TRUE;
    pVPInitInfo->w_hue_sin= 0;
    pVPInitInfo->f_hue_sin_sign= TRUE;
    pVPInitInfo->w_hue_cos= 0;
    pVPInitInfo->f_hue_cos_sign= TRUE;
    //VPO_Zoom
    pVPInitInfo->t_src_rect.u_start_x= 0;
    pVPInitInfo->t_src_rect.u_width= PICTURE_WIDTH;
    pVPInitInfo->t_src_rect.u_start_y= 0;
    pVPInitInfo->t_src_rect.u_height= PICTURE_HEIGHT;
    pVPInitInfo->dst_rect.u_start_x= 0;
    pVPInitInfo->dst_rect.u_width= SCREEN_WIDTH;
    pVPInitInfo->dst_rect.u_start_y= 0;
    pVPInitInfo->dst_rect.u_height= SCREEN_HEIGHT;
    //VPO_SetAspect
    pVPInitInfo->e_tvaspect= TV_4_3;
    pVPInitInfo->e_display_mode= NORMAL_SCALE;//LETTERBOX;
    pVPInitInfo->u_nonlinear_change_point= 111;
    pVPInitInfo->u_pan_scan_offset= 90;
    //VPO_SetOutput
    for(i=0;i<VP_DAC_TYPENUM;i++)
        pVPInitInfo->p_dac_config[i].b_enable= FALSE;
    if(g_boot_vpo_active == 1) {
        if ((g_boot_vpo_info.scart_out == YUV_1 && g_boot_vpo_info.dual_output == 0)
            || g_boot_vpo_info.scart_out == RGB_1)
            pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = FALSE;
        else
            pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable = TRUE;
    } else {
       pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_enable= TRUE;
    }
    pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].t_dac_index.u_dac_first= CVBS_DAC;
    pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].e_vgamode= VGA_NOT_USE;
    pVPInitInfo->p_dac_config[VDAC_USE_CVBS_TYPE].b_progressive= FALSE;

    pVPInitInfo->p_dac_config[YUV_1].b_enable= FALSE;
    pVPInitInfo->p_dac_config[VDAC_USE_RGB_TYPE].b_enable= FALSE;
    if(g_boot_vpo_active == 1)
        pVPInitInfo->e_tvsys= bl_tvsys_hd_to_sd(g_boot_vpo_info.tv_mode);//boot loader default value
    else
        pVPInitInfo->e_tvsys= NTSC;//HD is 720p60
    pVPInitInfo->u_win_mode= VPO_MAINWIN;//|VPO_PIPWIN;
    pVPInitInfo->t_pipcall_back.request_callback= NULL;
    pVPInitInfo->t_pipcall_back.release_callback= NULL;
    //pVPInitInfo->tMPCallBack.RequestCallback = (T_MPRequest)vdec_s3601_de_request;
    //pVPInitInfo->tMPCallBack.ReleaseCallback = (T_MPRelease)vdec_s3601_de_release;
    pVPInitInfo->p_src_change_call_back=NULL;
}

#if defined(_NESTOR_SUPPORT_)
#ifdef _BOARD_DB_M3823_02V01_
extern front_end_cfg* front_end_isdbt_cfg(UINT8 tuner_id);
#endif
/*
 * This code is very special for AUI CI Test(M3823), Normal flow please skip it.
 * We need to test DVBT & ISDBT in the same firmware, so here check one flag
 * in Nor Flash, if it set to 1, change the first NIM in M3823 board to ISDBT, otherwise
 * keep the first NIM is DVBT.
 */
static int nestor_change_nim_cfg(board_cfg* cfg)
{
	int ret = 0;
#ifdef _BOARD_DB_M3823_02V01_
	struct sto_device *test_flash_dev = NULL;

	test_flash_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);
	if (test_flash_dev == NULL) {
		libc_printf("Get sto_device fail!\n");
		return 1;
	}
	ret = sto_lseek(test_flash_dev, -6, STO_LSEEK_END);
	if (ret >= 0) {
		ret = sto_read(test_flash_dev, &g_nestor_nim_flag, 1);
	}
	if (ret != 1) {
		libc_printf("sto_read nim_flag fail, readed %#ld bytes.\n", ret);
		return 1;
	}

	if (g_nestor_nim_flag == 1)
	{
		cfg->front_end_cfg[0] =  front_end_isdbt_cfg(0);
		libc_printf("####### Attach as ISDBT");
	}
	else
	{
		libc_printf("####### Attach as DVBT");
	}
#endif
	return ret;
}
#endif


#define WDT_REBOOT_FLAG_SAVE_ADDR                                                          (0xB8053FAC)
#define WDT_REBOOT_FLAG_READ_ADDR                                                          (0xB8053FA8)
#define ALI_WDT_REBOOT (0x52454254)/*0x52-'R', 0x45-'E', 0x42-'B', 0x54-'T'.*/


static void system_pmu_init(void)
{
 #ifdef PMU_ENABLE
 	/*
 	**According to IC team's new design, C3702/C3922 MAIN cpu
 	**have not authority to access PMU module.
 	*/
	if((ALI_C3702 != sys_ic_get_chip_id()) && (ALI_C3922 != sys_ic_get_chip_id()))
 	{
		/*pmu sw/hw init.*/
		unsigned int __MAYBE_UNUSED__ nec_ir_key = STANDBY_IR_KEY;
		unsigned char ir_type = 0;
		unsigned char pmu_pan_type = 0x0;
		UINT64 nec_ir_key_first  = 0x60DF708F;
		UINT64 nec_ir_key_second = 0;

		/*
		**PAN_TYPE_CH455 = 0.
		**PAN_TYPE_FD650K =1.
		*/
		pmu_m36_attach(pmu_notify, (UINT32)NULL);
		pmu_panel_type(pmu_pan_type);
		pmu_m36_ir_init();
		pmu_key_transfrom_extend(nec_ir_key_first, ir_type, nec_ir_key_second, ir_type, NULL);
		rtc_s3811_set_tick_msk();

	#ifdef PMU_RETENTION_SUPPORT
		DDR_Parameter_Backup_Before_Standby();
	#endif
	}
	else if(ALI_C3702 == sys_ic_get_chip_id())
	{
        //corresponding to sabbat_dual @2017.12.29 by steven.zhang
		/*Init PMU RPC params.*/
        pmu_rpc_para = (struct pmu_smc_call_para *)malloc(sizeof(struct pmu_smc_call_para));

        /*Init PMU RPC params.*/
        pmu_rpc_para->reserved_flag1 = 1;
        pmu_rpc_para->reserved_flag2 = 2;
        pmu_rpc_para->reserved_flag3 = 3;
        pmu_rpc_para->reserved_flag4 = 4;
        pmu_rpc_para->reserved_flag5 = 5;
        pmu_rpc_para->reserved_flag6 = 6;
        pmu_rpc_para->reserved_flag7 = 7;
        pmu_rpc_para->reserved_flag8 = 8;
        pmu_rpc_para->reserved_flag9 = 9;
        pmu_rpc_para->reserved_flag10 = 10;
        pmu_rpc_para->reserved_flag11 = 11;
        pmu_rpc_para->reserved_flag12 = 12;
        pmu_rpc_para->reserved_flag13 = 13;
        pmu_rpc_para->reserved_flag14 = 14;
        pmu_rpc_para->reserved_flag15 = 15;
        pmu_rpc_para->reserved_flag16 = 16;
        pmu_rpc_para->reserved_flag17 = 17;
        pmu_rpc_para->reserved_flag18 = 18;
        pmu_rpc_para->reserved_flag19 = 19;

        /*IR power key is default inited as ALi IR power key.*/
        pmu_rpc_para->ir_power_key1 = STANDBY_IR_KEY;
        pmu_rpc_para->show_panel_type = 0;//Show OFF default

#ifdef PMU_STANDBY_DEBUG_EN
        /*Dump all PMU RPC params.*/
        libc_printf("\npmu_rpc_para->reserved_flag1: 0x%08X", pmu_rpc_para->reserved_flag1);
        libc_printf("\npmu_rpc_para->reserved_flag2: 0x%08X", pmu_rpc_para->reserved_flag2);
        libc_printf("\npmu_rpc_para->reserved_flag3: 0x%08X", pmu_rpc_para->reserved_flag3);
        libc_printf("\npmu_rpc_para->reserved_flag4: 0x%08X", pmu_rpc_para->reserved_flag4);
        libc_printf("\npmu_rpc_para->reserved_flag5: 0x%08X", pmu_rpc_para->reserved_flag5);
        libc_printf("\npmu_rpc_para->reserved_flag6: 0x%08X", pmu_rpc_para->reserved_flag6);
        libc_printf("\npmu_rpc_para->reserved_flag7: 0x%08X", pmu_rpc_para->reserved_flag7);
        libc_printf("\npmu_rpc_para->reserved_flag8: 0x%08X", pmu_rpc_para->reserved_flag8);
        libc_printf("\npmu_rpc_para->reserved_flag9: 0x%08X", pmu_rpc_para->reserved_flag9);
        libc_printf("\npmu_rpc_para->reserved_flag10: 0x%08X", pmu_rpc_para->reserved_flag10);
        libc_printf("\npmu_rpc_para->reserved_flag11: 0x%08X", pmu_rpc_para->reserved_flag11);
        libc_printf("\npmu_rpc_para->reserved_flag12: 0x%08X", pmu_rpc_para->reserved_flag12);
        libc_printf("\npmu_rpc_para->reserved_flag13: 0x%08X", pmu_rpc_para->reserved_flag13);
        libc_printf("\npmu_rpc_para->reserved_flag14: 0x%08X", pmu_rpc_para->reserved_flag14);
        libc_printf("\npmu_rpc_para->reserved_flag15: 0x%08X", pmu_rpc_para->reserved_flag15);
        libc_printf("\npmu_rpc_para->reserved_flag16: 0x%08X", pmu_rpc_para->reserved_flag16);
        libc_printf("\npmu_rpc_para->reserved_flag17: 0x%08X", pmu_rpc_para->reserved_flag17);
        libc_printf("\npmu_rpc_para->reserved_flag18: 0x%08X", pmu_rpc_para->reserved_flag18);
        libc_printf("\npmu_rpc_para->reserved_flag19: 0x%08X", pmu_rpc_para->reserved_flag19);
#endif

        /*when system boot,PMU will run 2 steps, as follows:
        1: copy boot reason from boot_reason_write to boot_reason_read.
        2: write ALI_WDT_REBOOT(boot reason) to boot_reason_write,in case system stuck unexpected(WDT reboot).
        Up layer read boot reason only from boot_reason_read.*/
        pmu_rpc_para->mcu_rw_offset = WDT_REBOOT_FLAG_SAVE_ADDR & 0xFFFF;
        hld_pmu_remote_call(0, 0, RPC_MCU_READ32, pmu_rpc_para);

        pmu_rpc_para->mcu_rw_offset = WDT_REBOOT_FLAG_READ_ADDR & 0xFFFF;
        pmu_rpc_para->mcu_write_data = pmu_rpc_para->mcu_read_data;
        hld_pmu_remote_call(0, 0, RPC_MCU_WRITE32, pmu_rpc_para);

        pmu_rpc_para->mcu_rw_offset = WDT_REBOOT_FLAG_SAVE_ADDR & 0xFFFF;
        pmu_rpc_para->mcu_write_data = ALI_WDT_REBOOT;
        hld_pmu_remote_call(0, 0, RPC_MCU_WRITE32, pmu_rpc_para);

        hld_pmu_remote_call(0, 0, GET_PMU_MCU_TIME, pmu_rpc_para);
        main_cpu_read_time_init(pmu_rpc_para);
        hld_pmu_remote_call(0, 0, SUSPEND_MCU, pmu_rpc_para);
	}
#endif

#ifdef RTC_TIME_SUPPORT
	if( (ALI_C3701 == sys_ic_get_chip_id()) || (ALI_S3503 == sys_ic_get_chip_id()) \
		|| (ALI_S3821 == sys_ic_get_chip_id()) || (ALI_C3505 == sys_ic_get_chip_id()) \
		|| (ALI_C3702 == sys_ic_get_chip_id()) || (ALI_C3711C == sys_ic_get_chip_id()))
	{
		south_rtc_init(0);
	}
#endif

#ifndef PMU_ENABLE
	if((ALI_S3811==sys_ic_get_chip_id()) \
		&& (sys_ic_get_rev_id() >= IC_REV_1))
	{
		rtc_s3811_set_tick_msk();
	}
#endif
	pmu_gpio_disable();
	PRINTF("%s : function end !\n", __FUNCTION__);
}

void system_hw_init(board_cfg* cfg)
{
	UINT32		boot_total_area_len = 0;

    set_board_cfg(cfg);

    //init chip
    global_chip_set(chip_create());
    chip_init(&(cfg->chip_param));

    //config gpio
    chip_gpio_pin_init_ext(cfg->all_gpio_array, cfg->all_gpio_count);
    if((NULL != cfg->front_end_cfg[0] && cfg->front_end_cfg[0]->front_end_type == FRONTEND_TYPE_S)
        || (NULL != cfg->front_end_cfg[1] && cfg->front_end_cfg[1]->front_end_type == FRONTEND_TYPE_S))
    {
        // power off 1000ms to work around IC bug
        chip_gpio_set(cfg->sys_power, 0);
        osal_task_sleep(1000);
    }

    //DDR_256M_SUPPORT
    #ifdef _SUPPORT_256M_MEM
    flash_remap(); 
    #endif
    
    //config pinmux
    chip_pin_mux_set_ext(cfg->pin_mux_array, cfg->pin_mux_count);
    //power on
    board_power(TRUE);
#ifdef DUAL_ENABLE
    hld_dev_see_init((void*)__MM_SEE_DBG_MEM_ADDR);
#endif
    //sci
    UINT32 port_disbale = 0;
#ifdef _CAS9_CA_ENABLE_
    otp_init(NULL);
    otp_read(0x3*4, &port_disbale, 4);
    if(port_disbale&(1<<12))
        port_disbale = 1;
    else
        port_disbale = 0;
#endif
#ifdef _BC_CA_ENABLE_
    // VMX KDF vender id
    #ifdef _SMI_CF_ENABLE_
    UINT64 vendor_id = 0x564d000000010328;// VMX SMI vender id
    #else
    UINT64 vendor_id = 0x564d78463401f6df;// VMX vender id
    #endif
    otp_etsi_kdf_trigger(0, vendor_id);
    otp_etsi_kdf_trigger(1, vendor_id);
    otp_etsi_kdf_trigger(2, vendor_id);
    otp_init(NULL);
#endif
    if(port_disbale == 0)
    {
            board_sci_init();
    }
    FIXED_PRINTF("MC: APP  init ok\r\n");
    FIXED_PRINTF("%s\r\n", get_sdk_ver());
    FIXED_PRINTF("%s\r\n", get_core_ver());
    FIXED_PRINTF("%s\r\n", get_app_ver());

    //pmu
    system_pmu_init();

    //i2c
    board_i2c_init();
    //scart
    if((NULL != cfg->scart_attach) && (NULL != cfg->scart_param))
    {
        cfg->scart_attach(cfg->scart_param);
        g_scart_dev = (struct scart_device *)dev_get_by_id(HLD_DEV_TYPE_SCART, 0);
    }
    //front panel
    if(NULL != cfg->pan_attach && NULL != cfg->pan_config)
    {
        cfg->pan_attach(cfg->pan_config);
        g_pan_dev = (struct pan_device *)dev_get_by_id(HLD_DEV_TYPE_PAN, 0);
        if(NULL != cfg->pan_i2c_id_set)
            cfg->pan_i2c_id_set(g_pan_dev, cfg->pan_i2c_id);
         pan_open(g_pan_dev);
        pan_display(g_pan_dev, " on ", 4);
    }
#if !(defined _BOARD_DB_M3716L_01V01_) && !(defined _BOARD_DB_M3526_01V01_)
// Maybe Demoboard no NAND flash
#ifdef _NAND_ENABLE_
    //NAND flash
       ali_nand_attach();
       g_sto_nand_dev = (struct ali_nand_device *)dev_get_by_name("ALI_NAND");
       if(RET_FAILURE == ali_nand_open(g_sto_nand_dev))
               FIXED_PRINTF("Nand Init Fail... other operations are not guarantied...\n");
#endif
#endif
    /*nor flash.*/
#ifndef _M3702_     
	if(1 == cfg->flash_type)
	{
		sto_local_flash_attach(NULL);
	}
	else     
	{
		sto_local_sflash_attach(NULL);
	}
#else
//3702 new BL/FW use SPI flash driver to support 128/256M DDR
	libc_printf("!!new spi flash init!!\n");
	spi_bus_init();        
	sto_local_sflash_attach(NULL);
#endif

    g_sto_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);
    sto_open(g_sto_dev);
	get_boot_total_area_len(&boot_total_area_len);
	if(boot_total_area_len > (UINT32)g_sto_dev->totol_size)
	{
		PRINTF("%s() %d err:bootloader size is larger than the flash size!!!\n",\
		__FUNCTION__,__LINE__);
	}
	if(g_sto_dev)
	{
		sto_chunk_init(boot_total_area_len, g_sto_dev->totol_size - boot_total_area_len);
	}
	//sto_eeprom_init();

#if defined(_NESTOR_SUPPORT_)
	// This code is very special for AUI CI Test(M3823), Normal flow please skip it
	nestor_change_nim_cfg(cfg);
#endif
    //rfm
    if(NULL != cfg->rfm_attach)
    {
        cfg->rfm_attach();
        g_rfm_dev = (struct rfm_device*)dev_get_by_id(HLD_DEV_TYPE_RFM, 0);
        if(NULL != g_rfm_dev)
        {
            g_rfm_dev->i2c_type_id_cfg = 1;
            g_rfm_dev->i2c_type_id = cfg->rfm_i2c_id;
        }
        //rfm_open(g_rfm_dev);
    }

#ifdef MULTI_CAS
#ifdef _C0200A_CA_ENABLE_
    cfg->adv_cfg_para.class_select = board_class_select;
#endif
#endif
    cfg->adv_cfg_para.scart_aspect_change = NULL;//api_scart_aspect_callback;

    if(TRUE == is_bootloader_show_logo_keeping_solution()) {
        cfg->adv_cfg_para.vpo_active = TRUE;//DE will not close VPO when opening
    } else {
        cfg->adv_cfg_para.vpo_active = FALSE;
    }

    board_frontend_init();
    aui_board_advance_init(&(cfg->adv_cfg_para));
    g_ge_dev = (struct ge_device*)dev_get_by_type(NULL,HLD_DEV_TYPE_GE);
    g_nim_dev = (struct nim_device*)dev_get_by_id(HLD_DEV_TYPE_NIM, 0);
    g_nim_dev2 = (struct nim_device*)dev_get_by_id(HLD_DEV_TYPE_NIM, 1);

    if(NULL == g_nim_dev && NULL == g_nim_dev2)
    {
        ASSERT(0);
    }
    else if(NULL == g_nim_dev2)
        cfg->adv_cfg_para.front_end_num = 1;
    else
        cfg->adv_cfg_para.front_end_num = 2;
}

void osal_delay_ms(UINT32 ms)
{
    UINT32 i;
    for (i = 0; i < ms; i++)
        osal_delay(1000);
}

/*------------------------------------------------------------
    GPIO related functions : LNB and Scart control
------------------------------------------------------------*/
/*
    sw ---- 0   off
            1   on
*/
static void api_Scart_Power_OnOff(unsigned int sw)          // 0: off 1: on
{
    board_cfg* cfg = get_board_cfg();
    if(NULL == cfg)
        return;
    if(NULL != cfg->scart_power)
    {
        chip_gpio_set(cfg->scart_power, sw);
    }
    else if(NULL != g_scart_dev && sw == 0)
    {
        scart_io_control(g_scart_dev,SCART_ENTRY_STADNBY,0);
    }
}

static unsigned int api_Scart_VCR_Detect(void)
{
    board_cfg* cfg = get_board_cfg();
    if(NULL == cfg)
        return 0;
    if(NULL != cfg->scart_vcr_detech)
    {
        return chip_gpio_get(cfg->scart_vcr_detech);
    }
    else if (g_scart_dev)
    {
        UINT32 vcr_detect = 0;

        scart_io_control(g_scart_dev,SCART_CHK_STATE,(UINT32)&vcr_detect);
        if(vcr_detect & SCART_STATE_VCR_IN)
            return 1;
        else
            return 0;
    }
    return 0;
}

#ifdef POS_SCART_VCR_DETECT

/*
    sw ---- 0   VCR master ( VCR can pass through)
            1   Recevie master  (VCR can't pass through)
*/
static void api_scart_output_switch(unsigned int sw)
{
    board_cfg* cfg = get_board_cfg();
    if(NULL == cfg)
        return;
    if(NULL != cfg->scart_vcr_switch)
    {
        chip_gpio_set(cfg->scart_vcr_switch, sw);
    }
    else if (g_scart_dev)
    {
        if(sw == 0)
        {
            scart_io_control(g_scart_dev,SCART_TV_SOURCE,SOURCE_VCR_IN);
            scart_io_control(g_scart_dev,SCART_VCR_SOURCE,SOURCE_VCR_IN);
        }
        else
        {
            scart_io_control(g_scart_dev,SCART_TV_SOURCE,SOURCE_STB_IN);
            scart_io_control(g_scart_dev,SCART_VCR_SOURCE,SOURCE_STB_IN);
        }
    }
    snd_io_control(g_snd_dev, SND_BYPASS_VCR, !sw);
}
#endif
static void api_scart_tvsat_switch(unsigned int sw,unsigned long aspect)         // 0: TV  1: SAT
{
    board_cfg* cfg = get_board_cfg();
    if(NULL == cfg)
        return;

    if(NULL != cfg->scart_tvsat_switch)
    {
        chip_gpio_set(cfg->scart_tvsat_switch, sw);
    }
    else if(g_scart_dev)
    {
        UINT32 tvsta_param;
        if(sw == 1)
            tvsta_param =aspect;//(pSys->avset.tv_ratio == TV_ASPECT_RATIO_43)? ASPECT_4_3 : ASPECT_16_9;
        else
            tvsta_param = ASPECT_INTERNAL;//TV
        scart_io_control(g_scart_dev,SCART_TV_ASPECT,tvsta_param);
    }
}

static void api_Scart_RGB_OnOff(unsigned int sw)
{
    board_cfg* cfg = get_board_cfg();
    if(NULL == cfg)
        return;
    if(NULL != cfg->scart_tv_fb)
    {
        chip_gpio_set(cfg->scart_tv_fb, sw);
    }
    else if (g_scart_dev)
    {
        UINT32 tv_mode;
        if(sw == 1)
            tv_mode = TV_MODE_RGB;
        else
            tv_mode = TV_MODE_CVBS;

        if(!api_Scart_VCR_Detect())
        {
            scart_io_control(g_scart_dev,SCART_TV_MODE,tv_mode);
        }
     }
#if 0//ndef GPIO_RGB_YUV_SWITCH
#ifdef VDAC_USE_RGB_TYPE
if(sw == 0)
    {
        vpo_ioctl(g_vpo_dev,VPO_IO_UNREG_DAC,VDAC_USE_RGB_TYPE);
    }
    else
    {
#ifdef VDAC_USE_SVIDEO_TYPE
        vpo_ioctl(g_vpo_dev,VPO_IO_UNREG_DAC,VDAC_USE_SVIDEO_TYPE);
#endif
        dac_reg_para.eDacType = VDAC_USE_RGB_TYPE;
        dac_reg_para.DacInfo.bEnable = 1;
        dac_reg_para.DacInfo.tDacIndex.uDacFirst    = RGB_DAC_R;
        dac_reg_para.DacInfo.tDacIndex.uDacSecond   = RGB_DAC_G;
        dac_reg_para.DacInfo.tDacIndex.uDacThird    = RGB_DAC_B;
        dac_reg_para.DacInfo.eVGAMode = VGA_NOT_USE;
        dac_reg_para.DacInfo.bProgressive = FALSE;
        vpo_ioctl(g_vpo_dev,VPO_IO_REG_DAC,(UINT32)&dac_reg_para);
    }
#endif
#endif
}

AUI_RTN_CODE aui_app_scart_init(UINT32 scart_out)
{
    api_Scart_Power_OnOff(1);

    if (g_scart_dev)
    {
        if(scart_open(g_scart_dev) != RET_SUCCESS)
        {
            PRINTF("scart_open failed!!\n");
            //ASSERT(0);
            //scart_io_control(g_scart_dev,SCART_DETACH_DEV,0);//detach may cause dev list link see pointer
            g_scart_dev = NULL;
        }
    }
    api_scart_tvsat_switch(0,ASPECT_4_3);
    #ifdef POS_SCART_VCR_DETECT
        if(api_Scart_VCR_Detect())
        {
            //api_Scart_RGB_OnOff(0);
            api_scart_output_switch(0);
        }
        else
        {
            api_Scart_RGB_OnOff((scart_out == SCART_RGB) ? 1 : 0);
            #ifdef VDAC_USE_SVIDEO_TYPE
                api_Svideo_OnOff((scart_out == SCART_SVIDEO) ? 1 : 0);
            #endif
            api_scart_output_switch(1);
        }
    #else
        api_Scart_RGB_OnOff( (scart_out == SCART_RGB) ? 1 : 0);
        #ifdef VDAC_USE_SVIDEO_TYPE
            api_Svideo_OnOff((scart_out == SCART_SVIDEO) ? 1 : 0);
        #endif
    #endif
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_nim_init()
{
    aui_nim_attr attr_nim;

#ifndef AUI_NIM0_INVALID_CASE_FOR_TWO_TUNER_SOLUTION
    MEMSET(&attr_nim,0,sizeof(aui_nim_attr));
#ifdef AUI_3503
    attr_nim.en_dmod_type = AUI_NIM_QPSK;
#endif
#ifdef AUI_3281
    attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef AUI_3821
    attr_nim.en_ter_std = AUI_STD_DVBT2_COMBO;
    if (g_nestor_nim_flag) {
        attr_nim.en_ter_std = AUI_STD_ISDBT;
    }
    attr_nim.en_dmod_type = AUI_NIM_OFDM;
#endif
#ifdef AUI_3715B
    attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef AUI_3505
	attr_nim.en_dmod_type = AUI_NIM_QPSK;
#ifdef _BOARD_DB_M3727_02V01_
	attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3728_01V01_
    attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3712_01V01_
	attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3712L_01V01_
	attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3716L_01V01_
	attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3721L_01V01_
    #ifdef DVBS_SUPPORT
			attr_nim.en_dmod_type = AUI_NIM_QPSK;
	#else
	        attr_nim.en_dmod_type = AUI_NIM_QAM;
	#endif
#endif
#ifdef _BOARD_DB_M3721_02V01_
    attr_nim.en_dmod_type = AUI_NIM_QPSK;
#endif
#ifdef _BOARD_DB_M3626_01V01_
	attr_nim.en_ter_std = AUI_STD_DVBT2_COMBO;
	attr_nim.en_dmod_type = AUI_NIM_OFDM;
#endif
#ifdef _BOARD_DB_M3627_02V01_
	attr_nim.en_ter_std = AUI_STD_DVBT2_COMBO;
	attr_nim.en_dmod_type = AUI_NIM_OFDM;
#endif
#endif

#ifdef _BOARD_DB_M3711B_01V01_
	attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif

#ifdef _BOARD_DB_M3711C_01V01_
	attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif

    if (aui_nim_open(&attr_nim,&g_pHdlNim[0]))
    {
        AUI_PRINTF("\n aui_nim_open failed\n");
        return AUI_RTN_FAIL;
    }
#endif

#ifdef SUPPORT_TWO_TUNER
    MEMSET(&attr_nim,0,sizeof(aui_nim_attr));
#ifdef AUI_3505
    attr_nim.en_ter_std = AUI_STD_DVBT2_COMBO;
	attr_nim.en_dmod_type = AUI_NIM_OFDM;
#ifdef _BOARD_DB_M3727_02V01_
	attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3527_01V01_
	attr_nim.en_dmod_type = AUI_NIM_QPSK;
#endif
#ifdef _BOARD_DB_M3712_01V01_
    attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3712L_01V01_
    attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3716L_01V01_
    attr_nim.en_dmod_type = AUI_NIM_QAM;
#endif
#ifdef _BOARD_DB_M3526_01V01_
	attr_nim.en_dmod_type = AUI_NIM_QPSK;
#endif
#ifdef _BOARD_DB_M3528_01V01_
        attr_nim.en_dmod_type = AUI_NIM_QPSK;
#endif
#ifdef _BOARD_DB_M3721L_01V01_
	#ifdef DVBS_SUPPORT
		attr_nim.en_dmod_type = AUI_NIM_QPSK;
	#else
		attr_nim.en_ter_std = AUI_STD_DVBT2_COMBO;
		attr_nim.en_dmod_type = AUI_NIM_OFDM;
	#endif
#endif
#ifdef _BOARD_DB_M3721_02V01_
    attr_nim.en_dmod_type = AUI_NIM_QPSK;
#endif
#endif

    attr_nim.ul_nim_id  = 1;
    if (aui_nim_open(&attr_nim,&g_pHdlNim[1]))
    {
        AUI_PRINTF("\n aui_nim_open 1 failed\n");
        return AUI_RTN_FAIL;
    }
#endif

    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_os_init(aui_attr_os *p_os_mod_attr)
{
    return aui_os_init(p_os_mod_attr);
}

AUI_RTN_CODE aui_app_tsi_init(struct aui_app_tsi_init_para *para)
{
    aui_hdl hdl_tsi=NULL;
    aui_attr_tsi attr_tsi;
    //if(1==s_ul_nim_type) return 0;
    MEMSET(&attr_tsi, 0, sizeof(aui_attr_tsi));
    attr_tsi.ul_init_param = para->ul_hw_init_val;
    if(aui_tsi_open(&hdl_tsi))
    {
        AUI_PRINTF("\r\n aui_tsi_open error \n");
        return AUI_RTN_FAIL;
    }
    if(aui_tsi_src_init(hdl_tsi, para->ul_input_src, &attr_tsi))
    {
        AUI_PRINTF("\r\n aui_tsi_src_init error \n");
        return AUI_RTN_FAIL;
    }

    if(aui_tsi_route_cfg(hdl_tsi, para->ul_input_src,
                             para->ul_tis_port_idx,
                             para->ul_dmx_idx))
    {
        AUI_PRINTF("\r\n aui_tsi_route_cfg error \n");
        return AUI_RTN_FAIL;
    }
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_dmx_init(unsigned long ul_dev_cnt, aui_dmx_dev_type *pdev_type)
{
    unsigned int i=0;
    aui_hdl hdl_dmx=NULL;
    aui_attr_dmx attr_dmx;
    MEMSET(&attr_dmx,0,sizeof(aui_attr_dmx));

    for(i=0;i<ul_dev_cnt;i++)
    {
        if(AUI_DMX_DEV_TYPE_HARDWARE==pdev_type[i])
        {
            if(AUI_RTN_SUCCESS!=aui_find_dev_by_idx(AUI_MODULE_DMX, i, &hdl_dmx))
            {
                attr_dmx.uc_dev_idx=i;
                if(AUI_RTN_SUCCESS!=aui_dmx_open(&attr_dmx,&hdl_dmx))
                {
                    AUI_PRINTF("\r\n aui_dmx_open failed.");
                    return AUI_RTN_FAIL;
                }
                /*
                if(AUI_RTN_SUCCESS!=aui_dmx_start(hdl_dmx,&attr_dmx))
                {
                    AUI_PRINTF("\r\n aui_dmx_start failed.");
                    return AUI_RTN_FAIL;
                }
                */
            }
        }
    }
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_deca_init(aui_attr_deca attr_deca)
{
    #ifndef _BUILD_OTA_E_
    aui_hdl hdl_deca=NULL;

    if(AUI_RTN_SUCCESS!=aui_deca_open(&attr_deca, &hdl_deca))
    {
        AUI_PRINTF("deca_open failed!\n");
        return AUI_RTN_FAIL;
    }
    #endif
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_snd_init(aui_attr_snd attr_snd)
{
    #ifndef _BUILD_OTA_E_
    aui_hdl hdl_snd=NULL;

    if(AUI_RTN_SUCCESS!=aui_snd_open(&attr_snd, &hdl_snd))
    {
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS!=aui_snd_mute_set(hdl_snd, 0))
    {
        return AUI_RTN_FAIL;
    }
    aui_snd_vol_set(hdl_snd,50);

    #endif
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_gfx_init(osd_layer_e attr_gfx)
{
    aui_hdl hdl_gfx=NULL;

    if(AUI_RTN_SUCCESS!=aui_gfx_layer_open(attr_gfx, &hdl_gfx))
    {
        return AUI_RTN_FAIL;
    }
    return AUI_RTN_SUCCESS;
}
AUI_RTN_CODE aui_app_dis_init(aui_attr_dis attr_dis)
{
    aui_hdl hdl_dis = NULL;
    aui_hdl hdl_dis_sd = NULL;
 #ifdef _BUILD_OTA_E_
    static struct vpo_device*   g_vpo_dev = NULL;
 #endif
       MEMSET(&attr_dis, 0,sizeof(aui_attr_dis));

    attr_dis.uc_dev_idx = 0;
    attr_dis.get_param = (aui_dis_open_param_callback)InitVPPara;
    aui_dis_open(&attr_dis, &hdl_dis);
#ifndef AUI_3281
#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
    attr_dis.uc_dev_idx = 1;
    attr_dis.get_param = (aui_dis_open_param_callback)InitVPPara_sd;
    aui_dis_open(&attr_dis, &hdl_dis_sd);
#endif
#endif
#ifdef _BUILD_OTA_E_
    struct mpsource_call_back vMPCallBack;
	struct pipsource_call_back vPIPCallBack;
    MEMSET(&vMPCallBack, 0, sizeof(vMPCallBack));
    MEMSET(&vPIPCallBack, 0, sizeof(vPIPCallBack));
    g_vpo_dev = ( struct vpo_device * ) dev_get_by_id ( HLD_DEV_TYPE_DIS, 0 );
    vpo_win_mode ( g_vpo_dev, VPO_MAINWIN, &vMPCallBack, &vPIPCallBack );
#endif
    vpo_ioctl((struct vpo_device *) dev_get_by_id(HLD_DEV_TYPE_DIS, 0), VPO_IO_ALWAYS_OPEN_CGMS_INFO,1);
#ifndef AUI_3281
#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
    vpo_ioctl((struct vpo_device *) dev_get_by_id(HLD_DEV_TYPE_DIS, 1), VPO_IO_ALWAYS_OPEN_CGMS_INFO,1);
#endif
#endif
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_decv_init(aui_attr_decv attr_decv)
{
    #ifndef _BUILD_OTA_E_
    aui_hdl hdl_decv = NULL;

    if(AUI_RTN_SUCCESS != aui_decv_open(&attr_decv, &hdl_decv))
    {
        AUI_PRINTF("-------decv open fail--------\n");
        return AUI_RTN_FAIL;
    }
    /** select mpeg2 to register callback in display engine **/
    if(AUI_RTN_SUCCESS != aui_decv_decode_format_set(hdl_decv, AUI_DECV_FORMAT_MPEG))
    {
        AUI_PRINTF("-------decv callback register fail--------\n");
        return AUI_RTN_FAIL;
    }
    /** set video sync mode here **/
    AUI_PRINTF("\ndecv sync mode set AUI_STC_AVSYNC_PCR\n");
    if(AUI_RTN_SUCCESS != aui_decv_sync_mode(hdl_decv, AUI_STC_AVSYNC_PCR))
    {
        AUI_PRINTF("-------decv sync mode set fail--------\n");
        return AUI_RTN_FAIL;
    }
    #endif
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_tsg_init(aui_attr_tsg attr_tsg)
{
    #ifndef _BUILD_OTA_E_
    aui_hdl hdl_tsg = NULL;
    if(AUI_RTN_SUCCESS != aui_tsg_open(&attr_tsg, &hdl_tsg))
    {
        AUI_PRINTF("\n-------aui_tsg_open--------\n");
        return AUI_RTN_FAIL;
    }
    #endif
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_av_init(aui_attrAV attr_av)
{
    #ifndef _BUILD_OTA_E_
    aui_hdl hdl_av = NULL;
    if(AUI_RTN_SUCCESS != aui_av_open(&attr_av, &hdl_av))
    {
        AUI_PRINTF("-------aui_av_open fail--------\n");
        return AUI_RTN_FAIL;
    }
    #endif
    return AUI_RTN_SUCCESS;
}
AUI_RTN_CODE aui_app_fs_init()
{
    #ifndef _BUILD_OTA_E_
    if(AUI_RTN_SUCCESS != aui_fs_init())
    {
        AUI_PRINTF("-------aui_fs_init fail--------\n");
        return AUI_RTN_FAIL;
    }
    //usb_init must be placed behind aui_fs_init to receive usb disk plug_in/plug_out event.
    AUI_PRINTF("\n%s:%d: call usb_init\n", __func__, __LINE__);
    usb_init();
    #endif
    return AUI_RTN_SUCCESS;
}

AUI_RTN_CODE aui_app_avsync_init(void)
{
#if !defined( _BUILD_OTA_E_)
	struct avsync_device *avsync_dev = NULL;
	avsync_adv_param_t adv_params;

	avsync_attach();
	avsync_dev = (struct avsync_device *)dev_get_by_id(HLD_DEV_TYPE_AVSYNC, 0);
	if(RET_SUCCESS != avsync_open(avsync_dev))
		ASSERT(0);

	MEMSET(&adv_params, 0, sizeof(adv_params));
	avsync_get_advance_params(avsync_dev, &adv_params);
	adv_params.pts_adjust_threshold = 5000;
	avsync_config_advance_params(avsync_dev, &adv_params);
#endif
	return 0;
}

AUI_RTN_CODE aui_app_pvr_init()
{
    AUI_RTN_CODE ret= AUI_RTN_SUCCESS;

    #ifndef _BUILD_OTA_E_
    aui_pvr_init_param ini_param;
    unsigned char *pvr_buffer = (unsigned char *)__MM_PVR_VOB_BUFFER_ADDR;
    int pvr_buffer_len = __MM_PVR_VOB_BUFFER_LEN;
    if(pvr_buffer == NULL){
        AUI_PRINTF("pvr_buffer is %p\n",pvr_buffer);
        return 1;
    }else{
        AUI_PRINTF("pvr_buffer is %p\n",pvr_buffer);
    }
    memset(&ini_param,0,sizeof(ini_param));
    ini_param.max_rec_number = 2;     // max recorder number
    ini_param.max_play_number =1;
    //ini_param.max_rec_number=init_cfg.max_rec_number;
    ini_param.ac3_decode_support = 1;
    ini_param.continuous_tms_en = 0;
    ini_param.debug_level   = AUI_PVR_DEBUG_NONE | AUI_PVR_DEBUG_RECORDER |AUI_PVR_DEBUG_DATA | AUI_PVR_DEBUG_PLAYER;
    STRCPY(ini_param.dvr_path_prefix,"PVR");
    //STRCPY(ini_param.dvr_path_prefix,init_cfg.dvr_path_prefix);

    STRCPY(ini_param.info_file_name,"info.dvr");
    //STRCPY(ini_param.info_file_name,init_cfg.info_file_name);

    STRCPY(ini_param.info_file_name_new,"info3.dvr");
    //STRCPY(ini_param.info_file_name_new,init_cfg.info_file_name_new);
    STRCPY(ini_param.ts_file_format,"dvr");
    //STRCPY(ini_param.ts_file_format,ini_param.ts_file_format);

    STRCPY(ini_param.ts_file_format_new, "ts");
    //STRCPY(ini_param.ts_file_format_new, "ts");

    STRCPY(ini_param.ps_file_format,"mpg");
    //STRCPY(ini_param.ps_file_format,init_cfg.ps_file_format);

    STRCPY(ini_param.test_file1,"test_write1.dvr");
    //STRCPY(ini_param.test_file1,init_cfg.test_file1);
    STRCPY(ini_param.test_file2,"test_write2.dvr");
    //STRCPY(ini_param.test_file2,init_cfg.test_file2);
    STRCPY(ini_param.storeinfo_file_name,"storeinfo.dvr");
    //ini_param.h264_vobu_time_len = init_cfg.h264_vobu_time_len;    // in ms, scope: 500-2000ms, recommend to 600ms
    //ini_param.scramble_vobu_time_len = init_cfg.scramble_vobu_time_len;    //in ms, scope: 500-2000ms,    recommend to 600ms
    //ini_param.file_header_save_dur = init_cfg.file_header_save_dur;// in seconds, recomment to 30s, file head save cycle, min duration is 15s.
    ini_param.record_min_len = 3;        // in seconds, recomment to 15s, the record will be deleted if shorter that this limit
    //ini_param.record_min_len = init_cfg.record_min_len;        // in seconds, recomment to 15s, the record will be deleted if shorter that this limit
    ini_param.tms_time_max_len = 7200;    // in seconds, recomment to 2h(7200);
    //ini_param.tms_time_max_len = init_cfg.tms_time_max_len;    // in seconds, recomment to 2h(7200);
    ini_param.tms_file_min_size = 2;    // in MBytes,  recomment to 10M
    //ini_param.tms_file_min_size = init_cfg.tms_file_min_size;    // in MBytes,  recomment to 10M
    ini_param.prj_mode  = AUI_PVR_DVBS2;  //8.why is PVR_DVBS
    ini_param.cache_addr = (unsigned int)pvr_buffer;
    ini_param.cache_size = pvr_buffer_len;
    ret=aui_pvr_init(&ini_param);
    if(ret != AUI_RTN_SUCCESS){
        return 1;
    }
    #endif
    return ret;
}

#ifndef _SD_ONLY_
AUI_RTN_CODE aui_app_hdmi_init(struct aui_app_hdmi_init_para init_paras_hdmi)
{
    aui_hdl hdl_hdmi = NULL;

    if(AUI_RTN_SUCCESS != aui_hdmi_open(&(init_paras_hdmi.attr_hdmi), &hdl_hdmi))
    {
        AUI_PRINTF("-------HDMI open fail--------\n");
        return AUI_RTN_FAIL;
    }

    if(AUI_RTN_SUCCESS != aui_hdmi_callback_reg(hdl_hdmi,AUI_HDMI_CB_EDID_READY, init_paras_hdmi.aui_hdmi_edid_ready_callback,NULL ))
    {
        AUI_PRINTF("-------HDMI reg EDIE callback fail--------\n");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS != aui_hdmi_callback_reg(hdl_hdmi,AUI_HDMI_CB_HOT_PLUG_OUT, init_paras_hdmi.aui_hdmi_hot_plug_out_callback,NULL ))
    {
        AUI_PRINTF("-------HDMI reg hot plug out callback fail--------\n");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS != aui_hdmi_callback_reg(hdl_hdmi,AUI_HDMI_CB_HOT_PLUG_IN, init_paras_hdmi.aui_hdmi_hot_plug_in_callback,NULL ))
    {
        AUI_PRINTF("-------HDMI reg hot plug in callback fail--------\n");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS != aui_hdmi_callback_reg(hdl_hdmi,AUI_HDMI_CB_DBG_MSG, init_paras_hdmi.aui_hdmi_dbg_msg_callback,NULL ))
    {
        AUI_PRINTF("-------HDMI reg debug callback fail--------\n");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS != aui_hdmi_callback_reg(hdl_hdmi,AUI_HDMI_CB_CEC_MESSAGE, init_paras_hdmi.aui_hdmi_cec_msg_callback,NULL ))
    {
        AUI_PRINTF("-------HDMI reg CEC MSG callback fail--------\n");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS != aui_hdmi_callback_reg(hdl_hdmi,AUI_HDMI_CB_HDCP_FAIL, init_paras_hdmi.aui_hdmi_hdcp_err_callback,NULL ))
    {
        AUI_PRINTF("-------HDMI reg HDCP ERR callback fail--------\n");
        return AUI_RTN_FAIL;
    }
    return AUI_RTN_SUCCESS;
}
#endif

#ifdef _AUI_CASTPAL_

void aui_platform_init_hdmi(void)
{
   struct aui_app_hdmi_init_para attr_hdmi;

   MEMSET(&attr_hdmi,0,sizeof(struct aui_app_hdmi_init_para));

   /** add by vedic,for test hdcp nestor, the hdmi can't init first**/
   attr_hdmi.aui_hdmi_edid_ready_callback=hdmi_edid_ready_callback;
   attr_hdmi.aui_hdmi_hot_plug_out_callback=hdmi_hot_plug_out_callback;
   attr_hdmi.aui_hdmi_hot_plug_in_callback=hdmi_hot_plug_in_callback;
   attr_hdmi.aui_hdmi_dbg_msg_callback=hdmi_dbg_msg_callback;
   attr_hdmi.aui_hdmi_cec_msg_callback=hdmi_cec_msg_callback;
   attr_hdmi.aui_hdmi_hdcp_err_callback=hdmi_hdcp_err_callback;
   if(AUI_RTN_SUCCESS!=aui_app_hdmi_init(attr_hdmi))
   {
	   AUI_PRINTF("\r\n aui_app_hdmi_init failed.");
	   return AUI_RTN_FAIL;
   }
}
#endif

AUI_RTN_CODE aui_platform_init()
{
    aui_attr_os attr_os;
    MEMSET(&attr_os,0,sizeof(aui_attr_os));
    attr_os.task_rtn_mode=AUI_TASK_RTN_MODE_MANUAL_FREE;
    attr_os.event_num=256;
    if(0!=aui_app_os_init(&attr_os))
    {
        AUI_PRINTF("\r\n aui_app_os_init failed.");
        return AUI_RTN_FAIL;
    }

#ifndef _AUI_CI_MINI_SUPPORT_
#ifdef DVR_PVR_SUPPORT
    unsigned long ul_dmx_dev_cnt=3; // 2 hw dmx + 1 sw dmx(for pvr)
    aui_dmx_dev_type dmx_dev_types[AUI_DMX_DEV_CNT_MAX]={AUI_DMX_DEV_TYPE_HARDWARE,AUI_DMX_DEV_TYPE_HARDWARE,
                                                         AUI_DMX_DEV_TYPE_SOFTWARE};
#else
    unsigned long ul_dmx_dev_cnt=2; // 2 hw dmx
    aui_dmx_dev_type dmx_dev_types[AUI_DMX_DEV_CNT_MAX]={AUI_DMX_DEV_TYPE_HARDWARE,AUI_DMX_DEV_TYPE_HARDWARE};
#endif
    struct aui_app_tsi_init_para attr_tsi;
    aui_attr_deca attr_deca;
    aui_attr_snd attr_snd;
    aui_attr_decv attr_decv;
    aui_attr_dis attr_dis;
    #ifndef _SD_ONLY_
    // SD project no HDMI
    struct aui_app_hdmi_init_para attr_hdmi;
    #endif
    aui_hdl hdl_dis=NULL;
    aui_hdl hdl_dis_sd=NULL;
    aui_attr_tsg attr_tsg;
    aui_attr_kl attr_kl;
    aui_attr_dsc attr_dsc;
    aui_attrAV attr_av;
    //aui_attrAV attr_av;
    aui_hdl hdl_deca=NULL;
    aui_hdl hdl_snd=NULL;
    aui_hdl hdl_decv=NULL;
    aui_hdl hdl_dmx=NULL;

    MEMSET(&attr_tsi,0,sizeof(struct aui_app_tsi_init_para));
    MEMSET(&attr_snd,0,sizeof(aui_attr_snd));
    MEMSET(&attr_dis,0,sizeof(aui_attr_dis));
    MEMSET(&attr_decv,0,sizeof(aui_attr_decv));
    #ifndef _SD_ONLY_
    MEMSET(&attr_hdmi,0,sizeof(struct aui_app_hdmi_init_para));
    #endif
    MEMSET(&attr_tsg,0,sizeof(aui_attr_tsg));
    MEMSET(&attr_kl,0,sizeof(aui_attr_kl));
    MEMSET(&attr_dsc,0,sizeof(aui_attr_dsc));
    MEMSET(&attr_av,0,sizeof(aui_attrAV));
    //MEMSET(&attr_pvr,0,sizeof(aui_attr_dsc));



    if(AUI_RTN_SUCCESS!=aui_app_nim_init())
    {
        AUI_PRINTF("\r\n aui_app_nim_init failed.");
        return AUI_RTN_FAIL;
    }


#ifdef DVBC_SUPPORT
	attr_tsi.ul_hw_init_val = AUI_TSI_IN_CONF_SPI_ENABLE
            | AUI_TSI_IN_CONF_SSI_BIT_ORDER
            | AUI_TSI_IN_CONF_SYNC_SIG_POL
            | AUI_TSI_IN_CONF_VALID_SIG_POL;
    attr_tsi.ul_tsi_id = 0;

    #if (defined AUI_3281) || (defined AUI_3715B)
    attr_tsi.ul_input_src = AUI_TSI_INPUT_SPI_0;
    #else
    attr_tsi.ul_input_src = AUI_TSI_INPUT_SPI_0;
    #endif
    attr_tsi.ul_tis_port_idx = AUI_TSI_CHANNEL_0;
    if(AUI_RTN_SUCCESS!=aui_app_tsi_init(&attr_tsi))
    {
        AUI_PRINTF("\r\n aui_app_tsi_init failed.");
        return AUI_RTN_FAIL;
    }

#else

	attr_tsi.ul_hw_init_val = 0x5f;

    attr_tsi.ul_tsi_id = 0;

    #if (defined AUI_3281) || (defined AUI_3715B)
    attr_tsi.ul_input_src = AUI_TSI_INPUT_SPI_0;
    #else
    attr_tsi.ul_input_src = AUI_TSI_INPUT_SSI2B_1;
    #endif
    attr_tsi.ul_tis_port_idx = AUI_TSI_CHANNEL_0;
    if(AUI_RTN_SUCCESS!=aui_app_tsi_init(&attr_tsi))
    {
        AUI_PRINTF("\r\n aui_app_tsi_init failed.");
        return AUI_RTN_FAIL;
    }
#endif


    if(AUI_RTN_SUCCESS!=aui_app_dmx_init(ul_dmx_dev_cnt,dmx_dev_types))
    {
        AUI_PRINTF("\r\n aui_app_dmx_init failed.");
        return AUI_RTN_FAIL;
    }
    attr_deca.uc_dev_idx=0;
	attr_deca.en_stream_aud_type=AUI_DECA_STREAM_TYPE_MPEG2;
	attr_deca.en_sample_rate=AUI_DECA_STREAM_SAMPLE_RATE_48;
	attr_deca.en_quan=AUI_DECA_AUDIO_QWLEN_24;
	attr_deca.uc_channel_num=2;
	attr_deca.ul_pts=0;
	attr_deca.ul_deca_stop_mode=AUI_DECA_STOP_IMM;

    if(AUI_RTN_SUCCESS!=aui_app_deca_init(attr_deca))
    {
        AUI_PRINTF("\r\n aui_app_deca_init failed.");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS!=aui_app_snd_init(attr_snd))
    {
        AUI_PRINTF("\r\n aui_app_snd_init failed.");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS!=aui_app_scart_init(SCART_RGB))
    {
        AUI_PRINTF("\r\n aui_app_scart_init failed.");
        return AUI_RTN_FAIL;
    }

    if(AUI_RTN_SUCCESS!=aui_app_gfx_init(eAUI_OSD_LAYER_GMA1))
    {
        AUI_PRINTF("\r\n aui_app_gfx_init failed.");
        return AUI_RTN_FAIL;
    }

    /** The display module must be initialized before the decv module **/
    if(AUI_RTN_SUCCESS!=aui_app_dis_init(attr_dis))
    {
        AUI_PRINTF("\r\n aui_app_dis_init failed.");
        return AUI_RTN_FAIL;
    }

    /** avsync must be initialized before decv, because aui_decv_sync_mode need avsync_dev **/
    if(AUI_RTN_SUCCESS!=aui_app_avsync_init())
    {
        AUI_PRINTF("\r\n aui_app_avsync_init failed.");
        return AUI_RTN_FAIL;
    }

    attr_decv.uc_dev_idx = 0;
    attr_decv.en_chg_mode = AUI_CHG_BLACK;

    if(AUI_RTN_SUCCESS!=aui_app_decv_init(attr_decv))
    {
        AUI_PRINTF("\r\n aui_app_decv_init failed.");
        return AUI_RTN_FAIL;
    }
#ifndef _SD_ONLY_
/** add by vedic,for test hdcp nestor, the hdmi can't init first**/
    attr_hdmi.aui_hdmi_edid_ready_callback=hdmi_edid_ready_callback;
    attr_hdmi.aui_hdmi_hot_plug_out_callback=hdmi_hot_plug_out_callback;
    attr_hdmi.aui_hdmi_hot_plug_in_callback=hdmi_hot_plug_in_callback;
    attr_hdmi.aui_hdmi_dbg_msg_callback=hdmi_dbg_msg_callback;
    attr_hdmi.aui_hdmi_cec_msg_callback=hdmi_cec_msg_callback;
    attr_hdmi.aui_hdmi_hdcp_err_callback=hdmi_hdcp_err_callback;
    if(AUI_RTN_SUCCESS!=aui_app_hdmi_init(attr_hdmi))
    {
        AUI_PRINTF("\r\n aui_app_hdmi_init failed.");
        return AUI_RTN_FAIL;
    }

#endif

    if (g_boot_vpo_active == 1) {
        vpo_ioctl((struct vpo_device *) dev_get_by_id(HLD_DEV_TYPE_DIS, 0), VPO_IO_BOOT_UP_DONE, 1);
	}
#ifndef _SD_ONLY_
    if (ALI_C3702 == sys_ic_get_chip_id() || ALI_C3503D == sys_ic_get_chip_id()) {
		api_set_hdmi_color_space(HDMI_YCBCR_444);
    } else {
        vpo_ioctl((struct vpo_device *)dev_get_by_id(HLD_DEV_TYPE_DIS, 0), VPO_IO_HDMI_OUT_PIC_FMT, YCBCR_444);
    }
#endif


#ifndef AUI_3281
    if(g_boot_vpo_active != 1) {
		if(AUI_RTN_SUCCESS!=aui_find_dev_by_idx(AUI_MODULE_DIS,AUI_DIS_HD,&hdl_dis))
		{
			AUI_PRINTF("\r\n  get hd dis handle fail.");
			return AUI_RTN_FAIL;
		}
#ifndef _SD_ONLY_
		if(AUI_RTN_SUCCESS!=aui_dis_tv_system_set(hdl_dis,AUI_DIS_TVSYS_LINE_1080_25,FALSE))
		{
			AUI_PRINTF("\r\n aui_dis_tv_system_set AUI_DIS_TVSYS_LINE_1080_25 failed.");
			return AUI_RTN_FAIL;
		}
#else
		if(AUI_RTN_SUCCESS!=aui_dis_tv_system_set(hdl_dis,AUI_DIS_TVSYS_PAL,FALSE))
		{
			AUI_PRINTF("\r\n aui_dis_tv_system_set AUI_DIS_TVSYS_LINE_1080_25 failed.");
			return AUI_RTN_FAIL;
		}
#endif

#ifdef DUAL_VIDEO_OUTPUT_USE_VCAP
        if(AUI_RTN_SUCCESS!=aui_find_dev_by_idx(AUI_MODULE_DIS,AUI_DIS_SD,&hdl_dis_sd))
        {
            AUI_PRINTF("\r\n get sd dis handle fail.");
            return AUI_RTN_FAIL;
        }

        if(AUI_RTN_SUCCESS!=aui_dis_tv_system_set(hdl_dis_sd,AUI_DIS_TVSYS_PAL,FALSE))
        {
            AUI_PRINTF("\r\n aui_dis_tv_system_set AUI_DIS_TVSYS_PAL failed.");
            return AUI_RTN_FAIL;
        }
#endif
    }

#endif

    if(AUI_RTN_SUCCESS!=aui_find_dev_by_idx(AUI_MODULE_DECA,0,&hdl_deca))
    {
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS!=aui_find_dev_by_idx(AUI_MODULE_SND,0,&hdl_snd))
    {
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS!=aui_find_dev_by_idx(AUI_MODULE_DECV,0,&hdl_decv))
    {
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS!=aui_find_dev_by_idx(AUI_MODULE_DMX,0,&hdl_dmx))
    {
        return AUI_RTN_FAIL;
    }

    attr_av.pv_hdl_deca=hdl_deca;
    attr_av.pv_hdl_snd=hdl_snd;
    attr_av.pv_hdl_decv=hdl_decv;
    attr_av.pv_hdl_dmx=hdl_dmx;
    if(AUI_RTN_SUCCESS!=aui_app_av_init(attr_av))
    {
        AUI_PRINTF("\r\n aui_app_av_init failed.");
        return AUI_RTN_FAIL;
    }
    if(AUI_RTN_SUCCESS!=aui_app_fs_init())
    {
        AUI_PRINTF("\r\n aui_app_av_init failed.");
        return AUI_RTN_FAIL;
    }

#if 1
    T_CTSK tsk_param;
    tsk_param.task = (FP)aui_app_pvr_init;
    tsk_param.name[0] = 'P';
    tsk_param.name[1] = 'V';
    tsk_param.name[2] = 'R';
    tsk_param.quantum = 10;
    tsk_param.itskpri = OSAL_PRI_NORMAL;
    tsk_param.stksz = 0x4000*4;
    tsk_param.para1 = 0;
    osal_task_create(&tsk_param);
#else
    if(AUI_RTN_SUCCESS!=aui_app_pvr_init())
    {
        AUI_PRINTF("\r\n aui_app_pvr_init failed.");
        return AUI_RTN_FAIL;
    }
#endif

#endif //_AUI_CI_MINI_SUPPORT_

    aui_reg_pmu_bin(g_ali_pmu_bin, sizeof(g_ali_pmu_bin)/sizeof(unsigned char));

#ifndef _AUI_CI_MINI_SUPPORT_
    if(g_boot_vpo_active == 1) {
        #ifndef _BUILD_OTA_E_
        AUI_PRINTF("--------- backup logo --------\n");
        aui_decv_chg_mode_set(hdl_decv, AUI_DECV_CHG_STILL);
        if (AUI_RTN_SUCCESS != aui_decv_stop(hdl_decv)) {
            AUI_PRINTF("-------backup logo fail--------\n");
        }
        //restore default value
        aui_decv_chg_mode_set(hdl_decv, AUI_DECV_CHG_BLACK);
        #endif
    }
#endif //_AUI_CI_MINI_SUPPORT_

    return AUI_RTN_SUCCESS;
}

#if 0
static void connect_dvb(void)
{
    aui_hdl nim_hdl;
    aui_nim_attr nim_attr;
    nim_attr.en_dmod_type = AUI_NIM_OFDM;
    nim_attr.ul_nim_id = 0;
    aui_nim_open(&nim_attr,&nim_hdl);
    if(!nim_hdl)
    {
        //asm("sdbbp;nop");
        SDBBP();
    }
    aui_nim_connect_param param;
    memset(&param,0x00,sizeof(aui_nim_connect_param));
    param.ul_freq = 618000;
    param.connect_param.ter.bandwidth = 8;

    aui_nim_connect(nim_hdl,&param);
    int lock = 0;
    while(1)
    {
        aui_nim_is_lock(nim_hdl,&lock);
        libc_printf("%s line %d,lock = %d\n",__func__,__LINE__,lock);
        if(lock)
            break;
        osal_task_sleep(20);
    }
    return;
}
#endif

int init_time()
{
	int ret = 0;
#ifndef _BUILD_OTA_E_
	aui_hdl rtc_handler;
	aui_clock clock;

	struct tm time;
	ret |= aui_standby_init();
	ret |= aui_standby_get_current_timer(&time);

	ret |= aui_rtc_init();
	ret |= aui_rtc_open(&rtc_handler);
	if (ret != AUI_RTN_SUCCESS) {
		AUI_PRINTF("Init RTC time failed.\n");
		ret = 1;
	} else {
		clock.year= time.tm_year + 1900;
		clock.month = time.tm_mon + 1;
		clock.date= time.tm_mday;
		clock.day= time.tm_wday;
		clock.hour = time.tm_hour;
		clock.min = time.tm_min;
		clock.sec = time.tm_sec;
		AUI_PRINTF("Current time: %04d-%02d-%02d %02d:%02d:%02d\n",
				clock.year,clock.month, clock.date,
				clock.hour, clock.min, clock.sec);
		ret = aui_rtc_set_time(rtc_handler, &clock);
	}
#endif
	return ret;
}

#if defined(_AUI_NESTOR_) && defined(_TEST_OLD_CI_)
extern void run_nestor_in_task(int argc, const char *argv[]);
#else
#ifdef _AUI_NESTOR_
    extern int tds_aui_nestor_entry(int argc, const char *argv[]);
#endif
#endif

// This function currently use in NESTOR test, to ensure system can reboot
// when sytem HANG during initialization platform
void tds_app_watchdog_protect(BOOL enable)
{
    if (enable) {
        // Attach watchdog, to ensure system can reboot when HANG during platform init.
        // It is useful in NESTOR test
        dog_m3327e_attach(1);
        // Set 20 seconds reboot
        dog_mode_set(0, DOG_MODE_WATCHDOG, 20000000, NULL);
    } else {
        // only can use HLD API, because AUI module still not initialized.
        dog_stop(0);
    }
}

#if defined(_AUI_TEST_) && !defined(_BUILD_OTA_E_)
extern int tds_aui_test_entry();

static void tds_aui_test_task(UINT32 param1, UINT32 param2)
{
	// dive into aui sample code loop.
	(void)tds_aui_test_entry();
}

static void run_aui_test_in_task(void)
{
	T_CTSK  task_param;
	OSAL_ID task_id;

    task_param.task = tds_aui_test_task;
    task_param.name[0] = 'A';
    task_param.name[1] = 'U';
    task_param.name[2] = 'I';
    task_param.quantum = 10;
    task_param.itskpri = OSAL_PRI_NORMAL;
    task_param.stksz = 0x8000;
    task_param.para1 = 0;
    task_param.para2 = 0;

    task_id = osal_task_create(&task_param);
    libc_printf("Run AUI sample code task in ID %d\n", task_id);
}
#endif


#ifdef HDCP_FROM_CE
RET_CODE ce_generate_hdcp(void)
{
    //UINT16 i = 0;
    UINT32 id = HDCPKEY_CHUNK_ID;
    INT32 hdcp_chunk = -1;
    UINT8 *hdcp_internal_keys = NULL;

    p_ce_device ce_dev = (p_ce_device)dev_get_by_type(NULL, HLD_DEV_TYPE_CE);
#ifdef _C0200A_CA_ENABLE_
    TBlockParam     xBlkParam;
#endif

    hdcp_internal_keys = (UINT8 *)MALLOC(sizeof(UINT8)*288);

#ifdef _C0200A_CA_ENABLE_
    BlkParamGet(SCS_UNCHECKED_AREA_HDCP_KEY, &xBlkParam);
    hdcp_chunk = xBlkParam.xFlashOffset;
    sto_get_data( (struct sto_device *)dev_get_by_id(HLD_DEV_TYPE_STO, 0), hdcp_internal_keys,
        hdcp_chunk, 288);
#else
    hdcp_chunk = (INT32)sto_chunk_goto(&id,0xFFFFFFFF,1);
    if ((hdcp_chunk < 0) ||(-1 == hdcp_chunk ))
    {
        libc_printf("%s : function return value is ERR ! \n ", __FUNCTION__);
        FREE(hdcp_internal_keys);
        hdcp_internal_keys = NULL;
        return (!RET_SUCCESS);
    }
    sto_get_data( (struct sto_device *)dev_get_by_id(HLD_DEV_TYPE_STO, 0), hdcp_internal_keys,
        hdcp_chunk+ CHUNK_HEADER_SIZE, 288);
#endif

    ce_generate_hdcp_key(ce_dev, hdcp_internal_keys, 288);

    FREE(hdcp_internal_keys);
    hdcp_internal_keys = NULL;
    return RET_SUCCESS;
}
#endif

#ifdef PMU_ENABLE
#define AP_PMU_WRITE8(i, d)        (*(volatile UINT8 *)(i)) = (d)

// PMU set a panel key as standby key.
// Refer to Elephant\prj\app\demo\combo\sabbat_dual\power.c
void PMU_Set_Panel_Key(void)
{
#if ((defined _M3821_) || (defined _M3503_) || (defined _M3505_))
    libc_printf("%d %s PMU set panel power key OK!\n", __LINE__, __FUNCTION__);
    AP_PMU_WRITE8(STANDBY_PAN_KEY_ADDR, STANDBY_PAN_KEY);
#endif
}
#endif

#ifdef _AUI_NESTOR_
#ifdef _AUI_NESTOR_UART_MODE_
    static const char *nestor_argv[] = {"nestor", "--uart"};
#else
	static const char *nestor_argv[] = {"nestor"};
#endif

#endif


#ifdef _AUI_CASTPAL_
static unsigned long adi_main_task (void *pv_para1,void *pv_para2)
{
	artpal_main();
	while(1) osal_task_sleep(10000000);


}
#endif

void tds_app_init()
{
#if 0 // for download debug
		asm("b .");              //while loop
		asm("nop");
#endif
#ifdef _NESTOR_SUPPORT_
    tds_app_watchdog_protect(TRUE);
#endif
#ifdef _RD_DEBUG_
    if(ALI_S3503==sys_ic_get_chip_id())
    {
        ali_debug_enable();
    }
#endif

    system_hw_init(get_board_config());
#ifdef HDCP_FROM_CE
	ce_generate_hdcp();
#endif
    print_memory_layout_dual();

#ifdef _NOCS3_CSD_SEC_TEST_
	csd_sec_cert_entry();
#endif

#ifdef NETWORK_SUPPORT
    system_init_network();
#endif
    aui_platform_init();
    //connect_dvb();

// Get time form MCU
    init_time();

#ifdef PMU_ENABLE
    // Set panel power key
    PMU_Set_Panel_Key();
#endif
#ifdef _NESTOR_SUPPORT_
    tds_app_watchdog_protect(FALSE);
#endif

#if defined(_AUI_NESTOR_) && defined(_TEST_OLD_CI_)
    // Old nestor in AUI.git
     run_nestor_in_task(1, "nestor");
#else
#ifdef _AUI_NESTOR_
    // New nestor in ci.git
#ifdef _AUI_NESTOR_UART_MODE_
        tds_aui_nestor_entry(2, nestor_argv);
#else
        tds_aui_nestor_entry(1, nestor_argv);
#endif
#endif
#endif

#if defined(_AUI_TEST_) && !defined(_BUILD_OTA_E_) && !defined(_AUI_NESTOR_UART_MODE_)&& !defined(_AUI_CASTPAL_)
    // we should run aui sample test in normal task
#ifndef _C1800A_DVT_TEST_
    run_aui_test_in_task();
#else
    libc_printf("for test, not run test task, start ap task!!\n");

    INT32 len =0;
    get_boot_total_area_len(&len);
    aui_flash_chunk_init(len, 0x800000-len);
    libc_printf("boot total len 0x%x\n", len);

    INT32 ret = 0;
    ret = ap_task_init();
    if(FALSE == ret)
    {
    	PRINTF("ap_task_init Init failed\n");
    	ASSERT(0);
    }

    ret = key_init();
    if(FALSE == ret)
    {
    	PRINTF("key_init Init failed\n");
    	ASSERT(0);
    }
#endif
#else
#ifdef _C1800A_LOADERCORE_ENABLE_
  //Ird_Loader_UI_init();
#endif
#endif

	
	
#ifdef _AUI_CASTPAL_
	aui_hdl 		 hTunerTask  = NULL;
	aui_attr_task		 attr_task;


	memset(&attr_task,0,sizeof(aui_attr_task));

	attr_task.ul_priority = 20;
	attr_task.p_fun_task_entry = adi_main_task;
	attr_task.ul_quantum = 10;
	attr_task.ul_stack_size = 512*1024;
	strcpy(attr_task.sz_name,"adi_mian_task");
	if (AUI_RTN_SUCCESS != aui_os_task_create(&attr_task, &hTunerTask))
	{
		AUI_PRINTF("[%s][%d]aui_os_task_create fail!\n",__FUNCTION__,__LINE__);
	}
    
#endif

}

//add stubs for open macro _CAS9_CA_ENABLE_ in aui
#ifdef _CAS9_CA_ENABLE_
INT8 api_mcas_get_prog_record_flag(UINT32 prog_id)
{

}
INT32 api_mcas_start_transponder_multi_des(UINT8 dmx_id)
{

}
INT32 api_mcas_stop_transponder_multi_des(UINT8 dmx_id)
{

}
INT32 api_mcas_stop_service_multi_des(UINT32 prog_id,UINT32 mon_id)
{

}
void ca_set_prog_info()
{

}
INT32 api_mcas_start_service_multi_des(UINT32 channel_index, UINT32 mon_id, UINT8 dmx)
{

}
#endif

void get_local_time(date_time *dt)
{
    aui_hdl hdl_rtc=NULL;

    aui_clock time_now;

    MEMSET(&time_now,0,sizeof(time_now));

    aui_rtc_open(&hdl_rtc);

    if(NULL==hdl_rtc)
    {
        return;
    }

    if(AUI_RTN_SUCCESS!=aui_rtc_get_time(hdl_rtc,&time_now))
    {
        return;
    }
    dt->year=time_now.year;
    dt->month=time_now.month;
    dt->day=time_now.date;
    dt->weekday=time_now.day;
    dt->hour=time_now.hour;
    dt->min=time_now.min;
    dt->sec=time_now.sec;

}



#ifdef _AUI_CASTPAL_
void * __dso_handle = 0 ;

void puts(const char *s)
{
	if(s)
		libc_printf("%s \n", s);
}

void exit(int status)
{
    if(status != 0)
    {
		SDBBP();
    }
}

int unlink(const char *path)
{
	return fs_remove(path);
}

#endif



