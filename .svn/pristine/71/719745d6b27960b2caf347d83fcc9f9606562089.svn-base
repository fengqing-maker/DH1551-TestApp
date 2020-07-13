#include "../../chip/m3505/chip_m3505.h"
#include "../board_cfg.h"
#include "tve_hd_setting_half_mode.h"

#if defined(DUAL_VIDEO_OUTPUT_USE_VCAP)
#include "tve_old_cfg_setting_m3606.h"
#endif

#include <sys_config.h>
#include <hld/nim/nim_tuner.h>
#include <hld/nim/nim.h>
#include <bus/i2c/i2c.h>
/*********************************************************************************************************/

#if (SYS_DEM_MODULE == COFDM_S3811)
    extern INT32 nim_s3811_attach_ext(struct COFDM_TUNER_CONFIG_API *ptr_cofdm_tuner);
#endif

#define M3100_REV_ID        4
extern INT32 nim_m3101_dev_attach_ext(char *name, PCOFDM_TUNER_CONFIG_API p_config);

extern INT32 i2c_scb_write(UINT32 id, UINT8 slv_addr, UINT8 *data, int len);
extern INT32 i2c_scb_read(UINT32 id,UINT8 slv_addr, UINT8 *data, int len);
extern INT32 i2c_scb_write_read(UINT32 id, UINT8 slv_addr, UINT8 *data, int wlen, int rlen);

extern INT32 i2c_gpio_read(UINT32 id, UINT8 slv_addr, UINT8 *data, int len);
extern INT32 i2c_gpio_write(UINT32 id, UINT8 slv_addr, UINT8 *data, int len);
extern INT32 i2c_gpio_write_read(UINT32 id, UINT8 slv_addr, UINT8 *data, int wlen, int rlen);
extern void board_ddr_priority_init(void);
extern INT32 tun_mxl5007_init_isdbt_mode(UINT32 *tuner_id, struct COFDM_TUNER_CONFIG_EXT * ptr_tuner_config);

board_cfg board_config;
/*********************************************************************************************************/
#define SYS_BOARD_IS_M3606_01V02


#ifdef _M3702_
#define RXPLL_C_REG 		0xB8080108
#define MODE_C_REG  		0xB8083040
#define QAM_MARK    		0xFFFFFFFC	// [1:0]
#define QAM_J83AC_BIT		0x01		//bit 1=1
#define I2C_1_SDA_PINMUX_REG 		0xB808BC70
#define I2C_1_CLK_PINMUX_REG 		0xB808BC74
#define QAM_PINMUX_REG 			0xB808BC78

#else
#define RXPLL_C_REG 		0xB8000604
#define MODE_C_REG  		0xB800006c
#define QAM_MARK 			0xFFE7FFFF  // [20:19]
#define QAM_J83AC_BIT		0x00080000 //bit 19=1

#endif


static const struct ir_key_map_t    g_itou_key_tab[] =
{
	/*ali 60 key remote controller.*/
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df926d)}, V_KEY_0},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfc837)}, V_KEY_1},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df08f7)}, V_KEY_2},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df8877)}, V_KEY_3},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dff00f)}, V_KEY_4},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df30cf)}, V_KEY_5},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfb04f)}, V_KEY_6},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfd02f)}, V_KEY_7},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df10ef)}, V_KEY_8},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df906f)}, V_KEY_9},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df38c7)}, V_KEY_LEFT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df12ed)}, V_KEY_RIGHT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df22dd)}, V_KEY_UP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfb847)}, V_KEY_DOWN},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df50af)}, V_KEY_MP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df3ac5)}, V_KEY_ENTER},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfd22d)}, V_KEY_P_UP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfe01f)}, V_KEY_P_DOWN},
	//{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f28d7)}, V_KEY_BOOKMARK},
	//{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fa857)}, V_KEY_JUMPMARK},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df827d)}, V_KEY_TEXT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df708f)}, V_KEY_POWER},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df20df)}, V_KEY_PREV},//20
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df0af5)}, V_KEY_NEXT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df629d)}, V_KEY_AUDIO},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df807f)}, V_KEY_SUBTITLE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df9867)}, V_KEY_SLEEP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfe21d)}, V_KEY_FIND},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfa05f)}, V_KEY_MUTE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df7a85)}, V_KEY_PAUSE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfa25d)}, V_KEY_VIDEO_FORMAT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df6897)}, V_KEY_INFOR},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df42bd)}, V_KEY_EXIT},//30
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df52ad)}, V_KEY_TVSAT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df02fd)}, V_KEY_TVRADIO},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfc23d)}, V_KEY_FAV},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfa857)}, V_KEY_RECORD},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df18e7)}, V_KEY_PLAY},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df58a7)}, V_KEY_FB},//red
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfd827)}, V_KEY_FF},//green
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df4ab5)}, V_KEY_B_SLOW},//yellow
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfaa55)}, V_KEY_SLOW},//blue
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfe817)}, V_KEY_STOP},//40
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df40bf)}, V_KEY_ZOOM},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df00ff)}, V_KEY_EPG},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df2ad5)}, V_KEY_MENU},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfc03f)}, V_KEY_RECALL},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df609f)}, V_KEY_RED},//red
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df7887)}, V_KEY_GREEN},//green
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dff807)}, V_KEY_YELLOW},//yellow
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfba45)}, V_KEY_BLUE},//blue

	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfca35)}, V_KEY_PVR_INFO},//49
#ifndef SUPPORT_CAS9
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfb24d)}, V_KEY_FILELIST},
#endif
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df8a75)}, V_KEY_DVRLIST},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df1ae5)}, V_KEY_USBREMOVE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df6a95)}, V_KEY_PIP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df9a65)}, V_KEY_PIP_LIST},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df5aa5)}, V_KEY_SWAP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfda25)}, V_KEY_MOVE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60dfea15)}, V_KEY_REPEATAB},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df28d7)}, V_KEY_F_UP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x60df48b7)}, V_KEY_F_DOWN},

	/*ali 48 key remote controller.*/
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fb24d)}, V_KEY_0},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f22dd)}, V_KEY_1},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fa25d)}, V_KEY_2},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f629d)}, V_KEY_3},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fe21d)}, V_KEY_4},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f12ed)}, V_KEY_5},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f926d)}, V_KEY_6},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f52ad)}, V_KEY_7},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fd22d)}, V_KEY_8},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f32cd)}, V_KEY_9},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f9867)}, V_KEY_LEFT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f58a7)}, V_KEY_RIGHT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f18e7)}, V_KEY_UP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fd827)}, V_KEY_DOWN},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f906f)}, V_KEY_MP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807ff20d)}, V_KEY_ENTER},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f28d7)}, V_KEY_P_UP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fa857)}, V_KEY_P_DOWN},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f28d7)}, V_KEY_BOOKMARK},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fa857)}, V_KEY_JUMPMARK},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fc837)}, V_KEY_TEXT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fc03f)}, V_KEY_POWER},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f6897)}, V_KEY_PREV},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fe817)}, V_KEY_NEXT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f40bf)}, V_KEY_AUDIO},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fd02f)}, V_KEY_TIMER},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f50af)}, V_KEY_SUBTITLE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fb04f)}, V_KEY_LIST},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807ff00f)}, V_KEY_SLEEP},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f609f)}, V_KEY_FIND},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f30cf)}, V_KEY_MUTE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fb847)}, V_KEY_PAUSE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x00000156)}, V_KEY_SUBTITLE},
#ifdef HDTV_SUPPORT
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fa05f)}, V_KEY_VIDEO_FORMAT},
#else
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fa05f)}, V_KEY_HELP},
#endif
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f20df)}, V_KEY_INFOR},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f48b7)}, V_KEY_EXIT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f00ff)}, V_KEY_TVSAT},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f807f)}, V_KEY_TVRADIO},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f10ef)}, V_KEY_FAV},
#ifdef DVR_PVR_SUPPORT
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f38c7)}, V_KEY_RECORD},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f7887)}, V_KEY_PLAY},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f02fd)}, V_KEY_FB},//red
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f827d)}, V_KEY_FF},//green
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f42bd)}, V_KEY_B_SLOW},//yellow
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fc23d)}, V_KEY_SLOW},//blue
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807ff807)}, V_KEY_STOP},
#endif
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fe01f)}, V_KEY_LANGUAGE},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f708f)}, V_KEY_ZOOM},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f08f7)}, V_KEY_EPG},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f8877)}, V_KEY_MENU},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f728d)}, V_KEY_RECALL},
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f02fd)}, V_KEY_RED},//red
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f827d)}, V_KEY_GREEN},//green
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807f42bd)}, V_KEY_YELLOW},//yellow
	{{PAN_KEY_TYPE_REMOTE, PAN_KEY_PRESSED, 0, SET_IRCODE(0x807fc23d)}, V_KEY_BLUE},//blue

    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF0074)}, V_KEY_MENU },// V_KEY_POWER
    //{{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF0056)}, V_KEY_ENTER },
    //{{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF0074)}, V_KEY_VIDEO_FORMAT},
    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF004C)}, V_KEY_ENTER},
    //{{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF006e)}, V_KEY_MENU },
    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF0064)}, V_KEY_LEFT },
    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF0044)}, V_KEY_POWER},
    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF0054)}, V_KEY_UP },
    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF005c)}, V_KEY_DOWN },
    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF006c)}, V_KEY_RIGHT },
    {{PAN_KEY_TYPE_PANEL, PAN_KEY_PRESSED, 0, SET_IRCODE(0xFFFF0045)}, V_KEY_EXIT},
};

ir_key_map_t ir_key_maps[] =
{
	{ROCK00, IRP_NEC, 0x807f},
};

static struct pan_hw_info pan_hw_info =
{
    0,                /* type_kb : 2; Key board (array) type */
    1,                /* type_scan : 1; 0: Slot scan, 1: Shadow scan */
    1,                /* type_key: 1; Key exit or not */
    1,                /* type_irp: 3; 0: not IRP, 1: NEC, 2: LAB */
    0,                /* type_mcu: 1; MCU exit or not */
    4,                /* num_com: 4; Number of com PIN, 0 to 8 */
    1,                /* Position of colon flag, 0 to 7 */
    1,                /* num_scan: 2; Number of scan PIN, 0 to 2 */
    0,                /* rsvd_bits:6; Reserved bits */
    0,              /* rsvd byte for align pan_info */
    {0, HAL_GPIO_O_DIR, 127},        /* LATCH PIN */
    {0, HAL_GPIO_O_DIR,     127},        /* CLOCK PIN */
    {1, HAL_GPIO_O_DIR,     127},        /* DATA PIN */
    {{0, HAL_GPIO_I_DIR,     127},        /* SCAN1 PIN */
    {0, HAL_GPIO_I_DIR, 127}},        /* SCAN2 PIN */
    {{0, HAL_GPIO_O_DIR,     127},        /* COM1 PIN */
    {0, HAL_GPIO_O_DIR,     127},        /* COM2 PIN */
    {0, HAL_GPIO_O_DIR,     127},        /* COM3 PIN */
    {0, HAL_GPIO_O_DIR,     127},        /* COM4 PIN */
    {0, HAL_GPIO_O_DIR, 127},        /* COM5 PIN */
    {0, HAL_GPIO_O_DIR, 127},        /* COM6 PIN */
    {0, HAL_GPIO_O_DIR, 127},        /* COM7 PIN */
    {0, HAL_GPIO_O_DIR, 127}},        /* COM8 PIN */
    {{0, HAL_GPIO_O_DIR,     127},        /* POWER PIN */
    {1, HAL_GPIO_O_DIR,     127},        /* LOCK PIN */
    {0, HAL_GPIO_O_DIR, 127},        /* Extend function LBD */
    {0, HAL_GPIO_O_DIR, 127}},        /* Extend function LBD */
    {0, HAL_GPIO_O_DIR, 127},       /* rsvd extend function LBD */   
    300,                            /* Intv repeat first */
    250,                            /* Intv repeat */
    350,                                /* Intv release, 0: disable release key */
    NULL,                                  /* hook_scan() callback */
    NULL,                                  /* hook_show() callback */
    0,                                  /* p_seg */
};
#define bitmap_list                NULL
#define bitmap_list_num        0
struct pan_configuration pan_config = {&pan_hw_info, bitmap_list_num, bitmap_list};


/*
**This pinmux setting array is maintained by every module pic.
*/
static pin_mux_info pin_mux_array[] =
{
#ifndef _M3702_
    { EPHY_LED1_SEL				    ,0},
    { XNF_DQS_SEL			        ,0},
    { XDISEQC_IN_SEL2				,0},
    { XSC_SEL3				        ,0},
    { XSC_SEL2				        ,0},
    { XI2C2_SEL				        ,1},
#ifdef DVBC_SUPPORT
    { XIF_AGC_QAM_SEL				,1},
#else
	{ XIF_AGC_QAM_SEL			  	,0},
#endif
    { XI2C_SEL4				        ,1},
    { XTUN_AGC_QAM_SEL		        ,0},//useless
    { XDISEQC_IN_SEL		        ,0},
    { XDISEQC_HV_SEL2				,0},
    { XDISEQC_HV_SEL1			    ,0},
    { XDISEQC_OUT_SEL				,1},
#ifdef DVBS_SUPPORT//conflict with QAM AGC
    { XIF_AGC_S2_SEL				,1},
#else
	{ XIF_AGC_S2_SEL				,0},
#endif
    { XUART2_RX_SEL				    ,1},
    { XUART2_TX_SEL				    ,1},
    { XI2C_SEL					    ,1},
    { XHDMI_HTPG_SEL				,1},
    { XSC_SEL                       ,1},
#if (defined(NETWORK_SUPPORT) && defined(GPIO_CONTROL_NET_LED))
    { XUART_TX_SEL				    ,0}, // UART_TX(GPIO1) share with Network LED1, default close uart
    { XUART_RX_SEL				    ,0}, // UART_RX(GPIO0) share with Network LED2, default close uart
#else
    { XUART_TX_SEL				    ,1},
    { XUART_RX_SEL				    ,1},
#endif

    { XSPDIF_SEL				    ,1},
    { ASSI3_SEL2				    ,0},
    { NF_SMREJ_TST_SEL			    ,0},
    { EPHY_LED0_SEL	                ,0},
    { XDISEQC_HV_BGA_SEL			,0},
    { XDISEQC_IN_BGA_SEL			,0},
#ifdef DVBC_SUPPORT
    { XIF_AGC_QAM2_SEL			    ,1},
#else
	{ XIF_AGC_QAM2_SEL			    ,0},
#endif
    { XPMU_UART_SEL				    ,0},
    { ASSI4_SEL2			        ,0},
    { ASSI4_DATA1_SEL			    ,0},
    { SSO_SEL			            ,0},
    { SSO_ERR_SEL					,0},
    { ASSI4_SEL					    ,0},
    { ASSI3_DATA1_SEL				,0},
    { ASSI3_SEL					    ,0},
    { ASSI3_ERR_SEL				    ,0},
    { ASS2_DATA1_SEL				,0},
    { ASSI2_SEL					    ,0},
    { ASSI2_ERR_SEL			        ,0},
    { ASSI_DATA1_SEL		        ,0},
    { ASSI_SEL			            ,0},
    { ASSI_ERR_SEL			        ,0},
    { SPI_SEL					    ,0},
    { SPI_ERR_SEL					,0},

    { SFLASH_NANDFLASH_PINMUX_SEL	,0},
    { XNF_SEL					    ,0},
    { XSF_BGA_SEL					,0},
    { XCI_SEL			            ,0},
    { XNF_WPJ_SEL		            ,1},
    { XSF_HOLDJ_SEL			        ,1},
    { XSF_WJ_SEL			        ,1},
    { XSF_CS1_BGA_SEL				,0},
    { XSF_CS0_BGA_SEL				,1},

    { TEST_IP_SEL				    ,0},
    { XI2SO_DATA3_SEL2			    ,0},
    { XI2SO_DATA2_SEL2			    ,0},
    { XI2SO_DATA1_SEL2			    ,0},
    { HDMI_TEST_FUNTION_SEL		    ,0},
    { XI2S1_SEL				        ,0},
    { XI2S_SEL			            ,0},
    { XI2SO_DATA1_SEL	            ,0},
    { XI2SO_SEL				        ,0},
    { XI2SO_DATA3_SEL				,0},
    { XI2SO_DATA2_SEL				,0},
    { XPMU_DOCD_SEL				    ,0},
    { TVENC_SYNC_SEL				,0},
    { XSPDIF_IN_SEL				    ,0},
    { XSPDIF_TEXT_SEL				,0},
    { VIN_SE				    ,0},
    { USB_TEST_SEL				    ,0},
    { TEST_OUT_SEL				    ,0},
#endif
};

static gpio_info_t gpio_array[] =
{
#ifdef _M3702_/*for M3712S.*/
	{1, HAL_GPIO_O_DIR, 193},/*PANEL__SDA.*/
	{1, HAL_GPIO_O_DIR, 192},/*PANEL_SCL.*/
#else/*for M3712L.*/
	{1, HAL_GPIO_O_DIR, 108},/*PANEL__SDA.*/
	{1, HAL_GPIO_O_DIR, 107},/*PANEL_SCL.*/
#endif
	{1, HAL_GPIO_O_DIR, 21},/*hdmi_SDA.*/
	{1, HAL_GPIO_O_DIR, 22},/*hdmi_SCL.*/
	{0, HAL_GPIO_O_DIR, 130},/*mute.*/

#if (defined(NETWORK_SUPPORT) && defined(GPIO_CONTROL_NET_LED))
	{1, HAL_GPIO_O_DIR,   0},/*PHY Yellow(LED2) -- Link/Act, share with UART_RX(GPIO0).*/
	{1, HAL_GPIO_O_DIR,   1},/*PHY Green(LED1) -- speed,    share with UART_TX(GPIO1).*/
#endif   
};

enum{
	GPIO_I2C0_SDA_INDEX = 0,
	GPIO_I2C0_SCL_INDEX,
	GPIO_I2C1_SDA_INDEX,
	GPIO_I2C1_SCL_INDEX,
	SYS_MUTE_INDEX,
};

#define MEM_GPIO_ENABLED (0)
front_end_cfg front_end[2];

#ifdef DVBS_SUPPORT
extern INT32 nim_s3501_attach(struct QPSK_TUNER_CONFIG_API *ptr_qpsk_tuner);
extern INT32 nim_s3503_attach(struct QPSK_TUNER_CONFIG_API *ptr_qpsk_tuner);
extern INT32 nim_c3505_attach(struct QPSK_TUNER_CONFIG_API *ptr_qpsk_tuner);

front_end_cfg* front_end_s_cfg(UINT8 tuner_id)
{
	struct QPSK_TUNER_CONFIG_API* qpsk_tuner;
	front_end_cfg* cfg;
	if(tuner_id > 1)
		return NULL;

	cfg = &front_end[tuner_id];
	MEMSET(cfg, 0, sizeof(front_end_cfg));
	cfg->front_end_type = FRONTEND_TYPE_S;
	cfg->sat_id = 2;
	cfg->lnb_power = NULL;//&gpio_array[GPIO_LNB_CUT_INDEX];
	cfg->lnb_short_det = NULL;

	if(tuner_id == 0)
		cfg->nim_name = "NIM_C3505_0";
	else
		cfg->nim_name = "NIM_S3501_1";

	if(tuner_id == 0)
	{
		cfg->tsi_cfg.tsi_select = TSI_DMX_0;
		cfg->tsi_cfg.tsi_id = TSI_SPI_3 ;
		cfg->tsi_cfg.tsi_attr = 0x8b;
		cfg->nim_config.s_cfg.attach = nim_c3505_attach;
		cfg->nim_reset = NULL;//&gpio_array[NIM_RESET_INDEX]; 
	}
	else
	{
		cfg->tsi_cfg.tsi_select = TSI_TS_B;
		cfg->tsi_cfg.tsi_id = TSI_SSI2B_3;
		cfg->tsi_cfg.tsi_attr = 0x9b;
		cfg->nim_config.s_cfg.attach = nim_s3501_attach;
		cfg->nim_reset = NULL;//&gpio_array[NIM_RESET_INDEX];
	}
	cfg->tsi_cfg.tsi_spi_tsg_attr = 0x83;
	cfg->nim_config.s_cfg.tsi_id_m3501a = TSI_SPI_0;
	cfg->nim_config.s_cfg.tsi_attr_m3501a = 0x8b;

	/*turner.*/
	qpsk_tuner = &cfg->nim_config.s_cfg.qpsk_tuner;
	if(tuner_id == 0)
	{
	#ifdef SUPPORT_TUNER_M3031
		qpsk_tuner->nim_tuner_init	 =	nim_m3031_init;
		qpsk_tuner->nim_tuner_control =	nim_m3031_control;
		qpsk_tuner->nim_tuner_status  =	nim_m3031_status;
		qpsk_tuner->nim_tuner_command =	nim_m3031b_command;
		qpsk_tuner->nim_tuner_gain	 =	nim_m3031_gain;
		qpsk_tuner->tuner_config.c_tuner_base_addr = 0x40; 
	#else 
		qpsk_tuner->nim_tuner_init = nim_av2011_init;
		qpsk_tuner->nim_tuner_control = nim_av2011_control;
		qpsk_tuner->nim_tuner_status    = nim_av2011_status;
		qpsk_tuner->tuner_config.c_tuner_base_addr = 0xc2;
	#endif
		qpsk_tuner->config_data.recv_freq_low = 900;
		qpsk_tuner->config_data.recv_freq_high = 2200;
		qpsk_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB1;
		qpsk_tuner->ext_dm_config.i2c_type_id = I2C_TYPE_SCB1;/*3501 i2c type id.*/
		qpsk_tuner->ext_dm_config.i2c_base_addr = 0xe6;/*3501 i2c base address.*/
		qpsk_tuner->config_data.qpsk_config = 0xe9;/*bit2 IQ Normal //0xed;//bit2 IQSWAP  //shi for 3606.*/
	}
	else
	{
	#ifdef SUPPORT_TUNER_M3031
		qpsk_tuner->nim_tuner_init	  =  nim_m3031_init;
		qpsk_tuner->nim_tuner_control =  nim_m3031_control;
		qpsk_tuner->nim_tuner_status  =  nim_m3031_status;
		qpsk_tuner->nim_tuner_command =  nim_m3031b_command;
		qpsk_tuner->nim_tuner_gain	  =  nim_m3031_gain;
		qpsk_tuner->tuner_config.c_tuner_base_addr = 0x42;
	#else 
		qpsk_tuner->nim_tuner_init = nim_av2011_init;//nim_hz6306_init;
		qpsk_tuner->nim_tuner_control = nim_av2011_control;//nim_hz6306_control;
		qpsk_tuner->nim_tuner_status    = nim_av2011_status;//nim_hz6306_status;
		qpsk_tuner->tuner_config.c_tuner_base_addr = 0xc2;		
	#endif
		qpsk_tuner->config_data.recv_freq_low = 900;
		qpsk_tuner->config_data.recv_freq_high = 2200;
		qpsk_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB3;
		qpsk_tuner->ext_dm_config.i2c_type_id = I2C_TYPE_SCB3;  // 3501 i2c type id
		qpsk_tuner->ext_dm_config.i2c_base_addr = 0x66;
		qpsk_tuner->config_data.qpsk_config=0x6d;//bit2 IQ Normal //0xed;//bit2 IQSWAP  //shi for 3606
	}

	return cfg;
}
#endif

#ifdef ISDBT_SUPPORT
front_end_cfg* front_end_isdbt_cfg(UINT8 tuner_id)
{
	struct COFDM_TUNER_CONFIG_API*  isdbt_tuner;
	front_end_cfg* cfg;
	if(tuner_id > 1)
		return NULL;

	cfg = &front_end[tuner_id];
	MEMSET(cfg, 0, sizeof(front_end_cfg));
	cfg->is_isdbt = 1;
	cfg->front_end_type = FRONTEND_TYPE_T;
	cfg->sat_id = 1;
	cfg->lnb_power = NULL;
	cfg->lnb_short_det = NULL;
	cfg->nim_reset = NULL;
	cfg->tsi_cfg.tsi_id = TSI_SPI_0;
	cfg->tsi_cfg.tsi_attr = 0x87;
	if(tuner_id == 0)
		cfg->tsi_cfg.tsi_select = TSI_TS_A;
	else
		cfg->tsi_cfg.tsi_select = TSI_TS_B;
	cfg->tsi_cfg.tsi_spi_tsg_attr = 0x83;
	isdbt_tuner = &cfg->nim_config.t_cfg.cofdm_tuner;

#if (SYS_DEM_MODULE == COFDM_S3811)

	isdbt_tuner->config_data.flag = 0;/*0:ISDBT mode, 1:DVBT mode.*/
	isdbt_tuner->config_data.memory_size = __MM_COFDM_S3811_ISDBT_BUF_LEN;
	isdbt_tuner->config_data.memory = __MM_COFDM_S3811_ISDBT_ADDR;/*for S3811 ISDBT mode only.*/
	cfg->nim_config.t_cfg.attach = nim_s3811_attach_ext;
	if(1)//tuner_id == 0
	{
		/*S3811 internal demodulator.*/
		cfg->nim_name = "NIM_S3811_0";
		isdbt_tuner->work_mode = NIM_COFDM_SOC_MODE;
	}
	else
	{
		/*S3811 be used as external demodulator.*/
		cfg->nim_name = "NIM_S3811_1";
		isdbt_tuner->work_mode = NIM_COFDM_ONLY_MODE;
		isdbt_tuner->ext_dm_config.i2c_type_id = I2C_TYPE_SCB0;
		isdbt_tuner->ext_dm_config.i2c_base_addr = 0x40;
	}
#else
	#error "SYS_DEM_MODULE had not been defined for ISDBT."
#endif

	isdbt_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
	isdbt_tuner->ts_mode = NIM_COFDM_TS_SPI_8B;

#if (SYS_TUN_MODULE == MXL136 || SYS_TUN_MODULE == ANY_TUNER)
	{
		isdbt_tuner->tuner_type = MXL136;
		isdbt_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
		isdbt_tuner->tuner_config.c_tuner_base_addr = 0xC0;
		isdbt_tuner->config_data.connection_config = 0x00;/*no I/Q swap.*/
		isdbt_tuner->config_data.cofdm_config = 0x03;/*low-if, dirct , if-enable.*/
		isdbt_tuner->config_data.IF_AGC_MAX = 0xff;
		isdbt_tuner->config_data.IF_AGC_MIN = 0x00;
		isdbt_tuner->nim_tuner_init = tun_mxl136_init;
		isdbt_tuner->nim_tuner_control = tun_mxl136_control;
		isdbt_tuner->nim_tuner_status = tun_mxl136_status;
		isdbt_tuner->nim_tuner_command = tun_mxl136_command;
		isdbt_tuner->tuner_config.c_tuner_crystal = 24000;//khz
		isdbt_tuner->tuner_config.c_tuner_ref_div_ratio = 128;
		isdbt_tuner->tuner_config.w_tuner_if_freq = 4000;
		isdbt_tuner->tuner_config.c_tuner_agc_top = 2;/* from 0~7 //can be setted by COFDM, ex.disable RF Auto-AGC.*/
		isdbt_tuner->tuner_config.c_tuner_step_freq = 125;
		isdbt_tuner->tuner_config.c_chip = tuner_chip_maxlinear;
	}
#elif (SYS_TUN_MODULE == MXL5007)
	isdbt_tuner->config_data.connection_config = 0x00;/*no I/Q swap.*/
	isdbt_tuner->config_data.cofdm_config = 0x03;/*low-if, dirct , if-enable.*/
	isdbt_tuner->config_data.AGC_REF = 0x63;
	isdbt_tuner->config_data.IF_AGC_MAX = 0xff;
	isdbt_tuner->config_data.IF_AGC_MIN = 0x00;
	isdbt_tuner->nim_tuner_init  =  tun_mxl5007_init_isdbt_mode;
	isdbt_tuner->nim_tuner_control  =  tun_mxl5007_control;
	isdbt_tuner->nim_tuner_status =  tun_mxl5007_status;
	isdbt_tuner->nim_tuner_command  =  tun_mxl5007_command;
	isdbt_tuner->tuner_config.c_tuner_crystal = 24000;/*28800;  //Unit: KHz.*/
	isdbt_tuner->tuner_config.w_tuner_if_freq = 4570;/*36170.*/
	isdbt_tuner->tuner_config.c_tuner_agc_top = 252;/*Special for MaxLiner.*/
	isdbt_tuner->tuner_config.c_chip = tuner_chip_maxlinear;
	isdbt_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
	isdbt_tuner->tuner_config.c_tuner_base_addr    = 0xC0;
	isdbt_tuner->tuner_type = MXL5007;

#else
	#error "SYS_TUN_MODULE had not been defined for ISDBT."
#endif

	if((isdbt_tuner->tuner_config.i2c_type_id & I2C_TYPE_MASK) == I2C_TYPE_GPIO)
	{
		isdbt_tuner->tuner_config.tuner_write = i2c_gpio_write;
		isdbt_tuner->tuner_config.tuner_read = i2c_gpio_read;
		isdbt_tuner->tuner_config.tuner_write_read = i2c_gpio_write_read;
	}
	else
	{
		isdbt_tuner->tuner_config.tuner_write = i2c_scb_write;
		isdbt_tuner->tuner_config.tuner_read = i2c_scb_read;
		isdbt_tuner->tuner_config.tuner_write_read = i2c_scb_write_read;
	}

	// Work around to Enable SSI1_2 data swap
	//*((volatile UINT8 *)(0xb801a00b)) = (*(volatile UINT8  *)(0xb801a00b)) | 0x10;
	return cfg;
}
#endif

#ifdef DVBT_SUPPORT

front_end_cfg* front_end_t_cfg(UINT8 tuner_id)
{
	struct COFDM_TUNER_CONFIG_API*  t_tuner;
	front_end_cfg* cfg;
	if(tuner_id > 1)
		return NULL;

	cfg = &front_end[tuner_id];
	MEMSET(cfg, 0, sizeof(front_end_cfg));
	cfg->front_end_type = FRONTEND_TYPE_T;
	cfg->is_isdbt = 0;
	cfg->sat_id = 1;
	cfg->lnb_power = NULL;
	cfg->lnb_short_det = NULL;
	cfg->nim_reset = &gpio_array[2];
	cfg->nim_name = "NIM_COFDM_0";
	cfg->tsi_cfg.tsi_id = TSI_SPI_0;
	cfg->tsi_cfg.tsi_attr = 0x87;
	if(tuner_id == 0)
		cfg->tsi_cfg.tsi_select = TSI_TS_A;
	else
		cfg->tsi_cfg.tsi_select = TSI_TS_B;
	cfg->tsi_cfg.tsi_spi_tsg_attr = 0x83;
	t_tuner = &cfg->nim_config.t_cfg.cofdm_tuner;

#if (SYS_DEM_MODULE == COFDM_S3811)
	t_tuner->config_data.flag = 1; //0:ISDBT mode, 1:DVBT mode.
	cfg->nim_config.t_cfg.attach = nim_s3811_attach_ext;
	if(1)//tuner_id == 0
	{
		/*S3811 internal demodulator.*/
		cfg->nim_name = "NIM_S3811_0";
		t_tuner->work_mode = NIM_COFDM_SOC_MODE;
	}
	else
	{
		/*S3811 be used as external demodulator.*/
		cfg->nim_name = "NIM_S3811_1";
		t_tuner->work_mode = NIM_COFDM_ONLY_MODE;
		t_tuner->ext_dm_config.i2c_type_id = I2C_TYPE_SCB0;
		t_tuner->ext_dm_config.i2c_base_addr = 0x40;
	}

#elif (SYS_DEM_MODULE == COFDM_M3101)
	cfg->nim_config.t_cfg.attach_with_name = nim_m3101_dev_attach_ext;
	t_tuner->ext_dm_config.i2c_type_id = I2C_TYPE_SCB0;
	t_tuner->ext_dm_config.i2c_base_addr = 0x40;
	t_tuner->rev_id = M3100_REV_ID; // cofdm mode can't read ver id from register
	t_tuner->config_mode = 1;
	t_tuner->work_mode = NIM_COFDM_ONLY_MODE;

#else
	//#error "SYS_DEM_MODULE had not been defined for DVBT."
#endif

	t_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
	t_tuner->ts_mode = NIM_COFDM_TS_SPI_8B;

#if (SYS_TUN_MODULE == MXL5007 || SYS_TUN_MODULE == ANY_TUNER)
	t_tuner->config_data.connection_config = 0x00;/*no I/Q swap.*/
	t_tuner->config_data.cofdm_config = 0x03;/*low-if, dirct , if-enable.*/
	t_tuner->config_data.AGC_REF = 0x63;
	t_tuner->config_data.IF_AGC_MAX = 0xff;
	t_tuner->config_data.IF_AGC_MIN = 0x00;
	t_tuner->nim_tuner_init =  tun_mxl5007_init;
	t_tuner->nim_tuner_control  =  tun_mxl5007_control;
	t_tuner->nim_tuner_status =  tun_mxl5007_status;
	t_tuner->nim_tuner_command  =  tun_mxl5007_command;
	t_tuner->tuner_config.c_tuner_crystal = 24000; /*28800;  //Unit: KHz.*/
	t_tuner->tuner_config.w_tuner_if_freq = 4570;/*36170.*/
	t_tuner->tuner_config.c_tuner_agc_top = 252;/*Special for MaxLiner.*/
	t_tuner->tuner_config.c_chip = tuner_chip_maxlinear;
	t_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
	t_tuner->tuner_config.c_tuner_base_addr = 0xC0;
	t_tuner->tuner_type = MXL5007;

#elif (SYS_TUN_MODULE == TD1611ALF)
	t_tuner->config_data.connection_config = 0x00;/*no I/Q swap.*/
	t_tuner->config_data.cofdm_config = 0x03;/*low-if, dirct , if-enable.*/
	t_tuner->config_data.AGC_REF = 0x63;
	t_tuner->config_data.IF_AGC_MAX = 0xff;
	t_tuner->config_data.IF_AGC_MIN = 0x00;
	t_tuner->nim_tuner_init=tun_td1611alf_init;
	t_tuner->nim_tuner_control=tun_td1611alf_control;
	t_tuner->nim_tuner_status=tun_td1611alf_status;
	//  t_tuner->nim_Tuner_Cal_Agc=tun_td1611alf_cal_agc;
	static UINT8 mt352[]={0x28,0xA0,0x00,0x00,0xFF,0x00,0x00,0x00,0x40,0x00,0x3,0xFF,0x0,0x0};
	static UINT8 mt353[]={0x31,0x62,0xA1,0x03,0x52,0xFF,0x1A,0x0};
	t_tuner->config_data.pt_mt352=mt352;
	t_tuner->config_data.pt_mt353=mt353;
	t_tuner->tuner_config.c_tuner_crystal=4000;/*khz.*/
	t_tuner->tuner_config.c_tuner_base_addr=0xC0;
	t_tuner->tuner_config.c_chip=tuner_chip_infineon;
	t_tuner->tuner_config.c_tuner_ref_div_ratio=24;
	t_tuner->tuner_config.w_tuner_if_freq=36160;
	t_tuner->tuner_config.c_tuner_agc_top=2;/*from 0~7 , can be setted by COFDM, ex.disable RF Auto-AGC.*/
	t_tuner->tuner_config.c_tuner_step_freq=166;
	t_tuner->tuner_type = TD1611ALF;

#elif (SYS_TUN_MODULE == MXL5005)
	t_tuner->config_data.connection_config = 0x00;/*no I/Q swap.*/
	t_tuner->config_data.cofdm_config = 0x03;/*low-if, dirct , if-enable.*/
	t_tuner->config_data.AGC_REF = 0x53;
	t_tuner->config_data.IF_AGC_MAX = 0xff;
	t_tuner->config_data.IF_AGC_MIN = 0x00;
	t_tuner->nim_tuner_init = tun_mxl5005_init;
	t_tuner->nim_tuner_control = tun_mxl5005_control;
	t_tuner->nim_tuner_status =  tun_mxl5005_status;
	t_tuner->tuner_config.c_tuner_crystal = 16;/*Unit: MHz.*/
	t_tuner->tuner_config.w_tuner_if_freq = 4570;/*36170.*/
	t_tuner->tuner_config.c_tuner_agc_top = 252;/*Special for MaxLiner.*/
	t_tuner->tuner_config.c_chip = tuner_chip_maxlinear;/*Tuner_Chip_PHILIPS.*/
	t_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
	t_tuner->tuner_config.c_tuner_base_addr = 0xc6;
	//t_tuner->ts_mode = NIM_COFDM_TS_SSI;
	t_tuner->tuner_type = MXL5005;

#elif (SYS_TUN_MODULE == NM120)
	t_tuner->config_data.connection_config = 0x00;/*no I/Q swap.*/
	t_tuner->config_data.cofdm_config = 0x03;/*low-if, dirct , if-enable.*/
	t_tuner->config_data.AGC_REF = 0x63;
	t_tuner->config_data.IF_AGC_MAX = 0xff;
	t_tuner->config_data.IF_AGC_MIN = 0x00;
	t_tuner->nim_tuner_init=tun_nm120_init;
	t_tuner->nim_tuner_control=tun_nm120_control;
	t_tuner->nim_tuner_status=tun_nm120_status;
	t_tuner->tuner_config.c_tuner_crystal=24000;    //khz
	t_tuner->tuner_config.c_tuner_ref_div_ratio=24;
	t_tuner->tuner_config.w_tuner_if_freq=4570;
	t_tuner->tuner_config.c_tuner_agc_top=5;// 3'b101
	t_tuner->tuner_config.c_tuner_step_freq=166;
	t_tuner->tuner_config.c_chip=tuner_chip_maxlinear;
	t_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
	t_tuner->tuner_config.c_tuner_base_addr = 0xce;
	t_tuner->tuner_type = NM120;
#elif (SYS_TUN_MODULE == RT820T)

       t_tuner->config_data.connection_config = 0x00; //no I/Q swap.
    t_tuner->config_data.cofdm_config = 0x03;//low-if, dirct , if-enable.
    t_tuner->config_data.AGC_REF = 0x63;
    t_tuner->config_data.IF_AGC_MAX = 0xff;
    t_tuner->config_data.IF_AGC_MIN = 0x00;

    t_tuner->nim_tuner_init=tun_rt820_init;
    t_tuner->nim_tuner_control=tun_rt820_control;
    t_tuner->nim_tuner_status=tun_rt820_status;

    t_tuner->tuner_config.c_tuner_crystal=4000;    //khz
    t_tuner->tuner_config.c_tuner_ref_div_ratio=24;
    t_tuner->tuner_config.w_tuner_if_freq=3570;//3570 for 6M mode, 4570 for 8M/7M mmode;
    t_tuner->tuner_config.c_tuner_agc_top=5;// 3'b101
    t_tuner->tuner_config.c_tuner_step_freq=166;
    t_tuner->tuner_config.c_chip=tuner_chip_maxlinear;
    t_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
    t_tuner->tuner_type = RT820T;
#elif (SYS_TUN_MODULE == MXL603)
    t_tuner->config_data.connection_config = 0x00;  //no I/Q swap.
    t_tuner->config_data.cofdm_config = 0x03;        //low-if, dirct , if-enable.
    t_tuner->config_data.AGC_REF = 0x63;
    t_tuner->config_data.IF_AGC_MAX = 0xff;
    t_tuner->config_data.IF_AGC_MIN = 0x00;

    t_tuner->nim_tuner_init     =  tun_mxl603_init;
    t_tuner->nim_tuner_control  =  tun_mxl603_control;
    t_tuner->nim_tuner_status   =  tun_mxl603_status;
    t_tuner->nim_tuner_command  =  tun_mxl603_command;

    t_tuner->tuner_config.c_tuner_crystal      = 16; // Unit: MHz
    t_tuner->tuner_config.w_tuner_if_freq      = 4570;   //36170
    t_tuner->tuner_config.c_tuner_agc_top      = 252;    //Special for MaxLiner
    t_tuner->tuner_config.c_chip               = tuner_chip_maxlinear;

    t_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
    t_tuner->tuner_config.c_tuner_base_addr    = 0xC0;
    t_tuner->tuner_type = MXL603;
#elif (SYS_TUN_MODULE == AT810)
    t_tuner->nim_tuner_init=tun_at810_init;
    t_tuner->nim_tuner_control=tun_at810_control;
    t_tuner->nim_tuner_status=tun_at810_status;
    t_tuner->nim_tuner_command=tun_at810_command;

    t_tuner->config_data.cofdm_config = 0x13;         // BBAGC enabled, positive slope + 0IF modulation
    t_tuner->config_data.connection_config = 0x00; // no I/Q swap.
    t_tuner->config_data.AGC_REF = 0x63;                 // not used
    t_tuner->config_data.IF_AGC_MAX = 0xff;        // max DAC value
    t_tuner->config_data.IF_AGC_MIN = 0x01;        // why not 0?

    t_tuner->tuner_config.c_tuner_crystal=24000;     // khz
    t_tuner->tuner_config.c_tuner_base_addr=0x61<<1;   // to be checked!!!FFT
    t_tuner->tuner_config.c_tuner_ref_div_ratio=24;  // usual value (used?)
    t_tuner->tuner_config.w_tuner_if_freq=0;
    t_tuner->tuner_config.c_tuner_agc_top=2;        // usual value (used?)
    t_tuner->tuner_config.c_tuner_step_freq=125;
    t_tuner->tuner_config.c_chip=0;                 // not used
    t_tuner->tuner_type = AT810;

#elif (SYS_TUN_MODULE == DB5515)
    t_tuner->config_data.connection_config = 0x00;  //no I/Q swap.
    t_tuner->config_data.cofdm_config = 0x03;        //low-if, dirct , if-enable.
    t_tuner->config_data.AGC_REF = 0x63;
    t_tuner->config_data.IF_AGC_MAX = 0xff;
    t_tuner->config_data.IF_AGC_MIN = 0x00;

    t_tuner->nim_tuner_init     =  tun_db5515_init;
    t_tuner->nim_tuner_control  =  tun_db5515_control;
    t_tuner->nim_tuner_status   =  tun_db5515_status;
    t_tuner->nim_tuner_command  =  NULL;//tun_mxl5007_command;

    t_tuner->tuner_config.c_tuner_crystal      = 27000; //28800;  //Unit: KHz
    t_tuner->tuner_config.w_tuner_if_freq      = 4000;   //36170
    t_tuner->tuner_config.c_tuner_agc_top      = 252;    //Special for MaxLiner
    t_tuner->tuner_config.c_chip               = tuner_chip_infineon;

    t_tuner->tuner_config.i2c_type_id = I2C_TYPE_SCB0;
    t_tuner->tuner_config.c_tuner_base_addr    = 0xC2;
    t_tuner->tuner_type = DB5515;
#else
    #error "SYS_TUN_MODULE had not been defined for DVBT."
#endif

    if((t_tuner->tuner_config.i2c_type_id & I2C_TYPE_MASK) == I2C_TYPE_GPIO)
    {
        t_tuner->tuner_config.tuner_write = i2c_gpio_write;
        t_tuner->tuner_config.tuner_read = i2c_gpio_read;
        t_tuner->tuner_config.tuner_write_read = i2c_gpio_write_read;
    }
    else
    {
        t_tuner->tuner_config.tuner_write = i2c_scb_write;
        t_tuner->tuner_config.tuner_read = i2c_scb_read;
        t_tuner->tuner_config.tuner_write_read = i2c_scb_write_read;
    }

    return cfg;
}
#endif

#ifdef DVBC_SUPPORT
//3202 fullnim(alps)
INT32 nim_s3281_dvbc_attach(struct QAM_TUNER_CONFIG_API * ptr_qam_tuner);
enum DVBC_MODE_TYPE
{
    DVBC_MODE_J83AC = 0,
    DVBC_MODE_J83B = 1,

};

extern void m35_pin_mux_set_qam_select(UINT8 dvbc_mode);
void front_end_c_get_qam_config(UINT8 dvbc_mode,UINT32 nim_clk,struct DEMOD_CONFIG_ADVANCED* p_demod_config)
{
	UINT32 data_long=0x00;
	
    if(dvbc_mode == DVBC_MODE_J83B)
    {
        p_demod_config->qam_buffer_len= __MM_NIM_BUFFER_LEN;
        p_demod_config->qam_buffer_addr=__MM_NIM_BUFFER_ADDR;
		p_demod_config->qam_config_advanced &= ~((1<<0) | (1<<1));//clear bit0/bit1 first		
        p_demod_config->qam_config_advanced |= NIM_DVBC_J83B_MODE | nim_clk;  // j83ac, 54m sampleclk/dspclk
    }
    else if(dvbc_mode == DVBC_MODE_J83AC)
    {
        p_demod_config->qam_buffer_len= 0x00;
        p_demod_config->qam_buffer_addr=0x00;
		p_demod_config->qam_config_advanced &= ~((1<<0) | (1<<1));//clear bit0/bit1 first		
        p_demod_config->qam_config_advanced |= NIM_DVBC_J83AC_MODE |nim_clk;  // j83ac, 54m sampleclk/dspclk
    }

	//set sample clock (B4H[12]: 1 for 27M, 0 for 54M)
    if((NIM_SAMPLE_CLK_54M & p_demod_config->qam_config_advanced) ==NIM_SAMPLE_CLK_54M)
    { //54M, double cyrstal clock for sample clock        
		data_long=(*(volatile UINT32 *)(RXPLL_C_REG));
		data_long = data_long | 0x00000001;//changed by robin, 20161011
		*(volatile UINT32 *)(RXPLL_C_REG) = data_long;
    }
    else
    { //27M, same as crystal clock
		data_long=(*(volatile UINT32 *)(RXPLL_C_REG));		 
		data_long = data_long & 0xFFFFFFFE;//changed by robin, 20161011
		*(volatile UINT32 *)(RXPLL_C_REG) = data_long;
	}
#ifdef _M3702_
	data_long=(*(volatile UINT32 *)(I2C_1_SDA_PINMUX_REG));
	data_long = data_long | 0x00000001;//i2c  sda pinmux set
	*(volatile UINT32 *)(I2C_1_SDA_PINMUX_REG) = data_long;

	data_long=(*(volatile UINT32 *)(I2C_1_CLK_PINMUX_REG));
	data_long = data_long | 0x00000001;//i2c  clk pinmux set
	*(volatile UINT32 *)(I2C_1_CLK_PINMUX_REG) = data_long;

	data_long=(*(volatile UINT32 *)(QAM_PINMUX_REG));
	data_long = data_long | 0x00000001;////QAM pinmux set
	*(volatile UINT32 *)(QAM_PINMUX_REG) = data_long;
#endif
    m35_pin_mux_set_qam_select(dvbc_mode);
}

void m35_pin_mux_set_qam_select(UINT8 dvbc_mode)
{    
	UINT32 data_long=0x00;
#if 1
	//QAM
    if(dvbc_mode == DVBC_MODE_J83B)
    {   
        data_long=(*(volatile UINT32 *)(MODE_C_REG));
        data_long = data_long & QAM_MARK;
        *(volatile UINT32 *)(MODE_C_REG) = data_long;
    }
    else //(dvbc_mode == DVBC_MODE_J83AC)
    {   
        data_long=(*(volatile UINT32 *)(MODE_C_REG));
        data_long = data_long & QAM_MARK;
        *(volatile UINT32 *)(MODE_C_REG) = data_long | QAM_J83AC_BIT;
    }
#else
	 //QAM2
	 if(dvbc_mode == DVBC_MODE_J83B)
	 {	 // for J83B mode  (6CH[22:21]=2b'00;)
		 data_long=(*(volatile UINT32 *)(0xB800006c));
		 data_long = data_long & 0xFF9FFFFF;
		 *(volatile UINT32 *)(0xB800006c) = data_long | 0x00800000;//bit23=1
	 }
	 else //(dvbc_mode == DVBC_MODE_J83AC)
	 {	 // for J83AC mode (6CH[22:21]=2b'01;)
		 data_long=(*(volatile UINT32 *)(0xB800006c));
		 data_long = data_long & 0xFF9FFFFF;
		 *(volatile UINT32 *)(0xB800006c) = data_long | 0x00A00000;//bit23=1,bit21=1
	 }
#endif
}
extern INT32 tun_r858_init(UINT32* tuner_id, struct COFDM_TUNER_CONFIG_EXT * ptrTuner_Config);
extern INT32 tun_r858_control(UINT32 tuner_id, UINT32 freq, UINT8 bandwidth,UINT8 AGC_Time_Const,UINT8 *data,UINT8 cmd);
extern INT32 tun_r858_status(UINT32 tuner_id, UINT8 *lock);
extern INT32 tun_r858_command(UINT32 tuner_id, INT32 cmd, UINT32 param);
extern INT32 nim_s3281_dvbc_attach(struct QAM_TUNER_CONFIG_API * ptrQAM_Tuner);
front_end_cfg* front_end_c_cfg(UINT8 tuner_id)
{
    struct QAM_TUNER_CONFIG_API* c_tuner = NULL;
    front_end_cfg* cfg;
    __MAYBE_UNUSED__ UINT32 data_long=0x00;
    UINT32 mode_value = DVBC_MODE_J83AC;
    if(tuner_id > 1)
     	return NULL;
    cfg = &front_end[tuner_id];
    MEMSET(cfg, 0, sizeof(front_end_cfg));
    cfg->front_end_type = FRONTEND_TYPE_C;
    cfg->sat_id = 1;
    cfg->lnb_power = NULL;
    cfg->lnb_short_det = NULL;
    cfg->is_isdbt = 0;
    if(tuner_id == 0)
    {//QAM1
        cfg->nim_name             = "NIM_S3281_0";
        cfg->nim_reset = NULL;//&gpio_array[NIM_RESET_IO];
		cfg->tsi_cfg.tsi_select = TSI_DMX_1;
		cfg->tsi_cfg.tsi_id = TSI_SPI_0;
		cfg->tsi_cfg.tsi_attr = 0x8b;	


        cfg->nim_config.c_cfg.attach = nim_s3281_dvbc_attach;
        c_tuner = &cfg->nim_config.c_cfg.qam_tuner;

        c_tuner->tuner_config_data.RF_AGC_MAX         = 0xBA;
        c_tuner->tuner_config_data.RF_AGC_MIN         = 0x2A;
        c_tuner->tuner_config_data.IF_AGC_MAX         = 0xFE;
        c_tuner->tuner_config_data.IF_AGC_MIN         = 0x01;
        c_tuner->tuner_config_data.AGC_REF             = 0x80;

        c_tuner->tuner_config_ext.c_tuner_special_config=0x01;

        c_tuner->tuner_config_ext.c_chip             = TUNER_CHIP_NXP;
        c_tuner->tuner_config_ext.c_tuner_agc_top     = 1;//7; /*1 for single AGC, 7 for dual AGC */

        c_tuner->tuner_config_ext.i2c_type_id = I2C_TYPE_SCB1;
        c_tuner->tuner_config_ext.c_tuner_base_addr    =  0xD4;
        c_tuner->tuner_config_ext.c_tuner_crystal    = 16;
        c_tuner->tuner_config_ext.c_tuner_ref_div_ratio = 64;
        c_tuner->tuner_config_ext.c_tuner_step_freq    = 62.5;

        c_tuner->tuner_config_ext.w_tuner_if_freq_j83a=5000;
        c_tuner->tuner_config_ext.w_tuner_if_freq_j83b=4000;//5000;
        c_tuner->tuner_config_ext.w_tuner_if_freq_j83c=5380;

        //c_tuner->tuner_config_ext.c_tuner_reopen=0x00;
        c_tuner->tuner_config_data.c_tuner_tsi_setting = NIM_0_SPI_0;
        //c_tuner->tuner_config_ext.w_tuner_if_j83ac_type = 0x01;
        c_tuner->tuner_config_ext.w_tuner_if_freq = c_tuner->tuner_config_ext.w_tuner_if_freq_j83a; // 5000, for 8M; 5380 for 6M.
        
        c_tuner->tuner_config_ext.c_tuner_special_config = 0x01;
        c_tuner->nim_tuner_init = (void *)tun_r858_init;
        c_tuner->nim_tuner_control = (void *)tun_r858_control;
        c_tuner->nim_tuner_status = (void *)tun_r858_status;
		c_tuner->nim_tuner_command = (void *)tun_r858_command;
    }
    else if(tuner_id == 1)
    {//QAM2
        cfg->nim_name             = "NIM_S3281_1";
        cfg->nim_reset = NULL;//&gpio_array[NIM_RESET_IO];
		cfg->tsi_cfg.tsi_select = TSI_DMX_0;
		cfg->tsi_cfg.tsi_id = TSI_SPI_3 ;
		cfg->tsi_cfg.tsi_attr = 0x8b;

        cfg->nim_config.c_cfg.attach = nim_s3281_dvbc_attach;
        c_tuner = &cfg->nim_config.c_cfg.qam_tuner;

        c_tuner->tuner_config_data.RF_AGC_MAX         = 0xBA;
        c_tuner->tuner_config_data.RF_AGC_MIN         = 0x2A;
        c_tuner->tuner_config_data.IF_AGC_MAX         = 0xFE;
        c_tuner->tuner_config_data.IF_AGC_MIN         = 0x01;
        c_tuner->tuner_config_data.AGC_REF             = 0x80;

        c_tuner->tuner_config_ext.c_tuner_special_config=0x01;

        c_tuner->tuner_config_ext.c_chip             = TUNER_CHIP_NXP;
        c_tuner->tuner_config_ext.c_tuner_agc_top     = 1;//7; /*1 for single AGC, 7 for dual AGC */

        c_tuner->tuner_config_ext.c_tuner_base_addr    =  0xF4;//
        c_tuner->tuner_config_ext.c_tuner_crystal    = 16;
        c_tuner->tuner_config_ext.c_tuner_ref_div_ratio = 64;
        c_tuner->tuner_config_ext.c_tuner_step_freq    = 62.5;

        c_tuner->tuner_config_ext.w_tuner_if_freq_j83a=5500;//5000;
        c_tuner->tuner_config_ext.w_tuner_if_freq_j83b=4300;//5500;
        c_tuner->tuner_config_ext.w_tuner_if_freq_j83c=5380;

        //c_tuner->tuner_config_ext.c_tuner_reopen=0x00;
        c_tuner->tuner_config_data.c_tuner_tsi_setting = NIM_0_SPI_0;
        //c_tuner->tuner_config_ext.w_tuner_if_j83ac_type = 0x01;
        c_tuner->tuner_config_ext.w_tuner_if_freq = c_tuner->tuner_config_ext.w_tuner_if_freq_j83a; // 5000, for 8M; 5380 for 6M.
        c_tuner->tuner_config_ext.i2c_type_id = I2C_TYPE_SCB1;

        c_tuner->tuner_config_ext.c_tuner_special_config = 0x01;
		c_tuner->dem_config_advanced.qam_config_advanced |= NIM_RX_ADC_SWAP;
		
        c_tuner->nim_tuner_init = (void *)tun_r858_init;
        c_tuner->nim_tuner_control = (void *)tun_r858_control;
        c_tuner->nim_tuner_status = (void *)tun_r858_status;
		c_tuner->nim_tuner_command = (void *)tun_r858_command;
    }
    //power down s2
    //*(volatile UINT32 *)(0xB804E000) |= (1<<1);
    //*(volatile UINT32 *)(0xB80000A8) |= (3<<28);

    front_end_c_get_qam_config(mode_value,NIM_SAMPLE_CLK_27M,&(c_tuner->dem_config_advanced));
    
    return cfg;
}
#endif

struct scart_init_param scart_param =
{
	(UINT32)NULL,/*UINT32 i2c_type_id;.*/
	0,/*UINT32 vcr_plug_pos;.*/
	(UINT32)NULL,/*UINT32 vcr_callback;.*/
	0,/*UINT16 scart_volume; 0~7.  =0: Mute; =1: -6dB; =2: -3dB; =3: 0dB, =4: 3dB; =5: 6dB; =6: 9dB; =7: 12dB.*/
	0x94,/*reserved3.*/
};

sci_cfg sci_config[] =
{
	{SCI_FOR_RS232, 115200, SCI_PARITY_EVEN},
	{SCI_FOR_MDM, 115200, SCI_PARITY_EVEN},
};

i2c_cfg i2c_config[6] =
{
	{I2C_TYPE_SCB0, 100000, 1, NULL, NULL},/*hdmi.*/
	{I2C_TYPE_SCB1, 100000, 1, NULL, NULL},/*nim.*/
	{I2C_TYPE_SCB2, 100000, 1, NULL, NULL},/*nim.*/
	{I2C_TYPE_SCB3, 100000, 1, NULL, NULL},/*QAM I2C.*/
	{I2C_TYPE_GPIO0, 40000, 1, &gpio_array[GPIO_I2C0_SDA_INDEX], &gpio_array[GPIO_I2C0_SCL_INDEX]},/*for panel CH455 panel.*/
	{I2C_TYPE_GPIO1, 100000, 1, &gpio_array[GPIO_I2C1_SDA_INDEX], &gpio_array[GPIO_I2C1_SCL_INDEX]},/*for hdmi.*/
};

#define SYS_I2C_SDA2 (64)
#define SYS_I2C_SCL2 (65)

board_cfg* advance_cfg(board_cfg* cfg)
{
	if(NULL == cfg)
		return NULL;

	cfg->chip_param.mem_gpio_enabled = FALSE;
	cfg->chip_param.ci_power_ctl_enabled = FALSE;
#if (SYS_NETWORK_MODULE == NET_ALIETHMAC)
	cfg->chip_param.ali_ethmac_enabled = FALSE;
#endif

#if(defined SHOW_ALI_DEMO_ON_SCREEN)
	cfg->adv_cfg_para.hdcp_disable = TRUE;
#else
	cfg->adv_cfg_para.hdcp_disable = FALSE;
#endif

    cfg->adv_cfg_para.i2c_for_eddc = I2C_TYPE_SCB0;
	//cfg->adv_cfg_para.hdmi_cm_scl = SYS_I2C_SCL2;
	//cfg->adv_cfg_para.hdmi_cm_sda = SYS_I2C_SDA2;
#ifdef AUDIO_DESCRIPTION_SUPPORT
#if(SYS_SDRAM_SIZE >= 128) //if only support broastcast mixed mode,set 0,if support receive mixed mode,set 1
	cfg->adv_cfg_para.audio_description_support = TRUE;
#else
	cfg->adv_cfg_para.audio_description_support = FALSE;
#endif
#else
	cfg->adv_cfg_para.audio_description_support = FALSE;
#endif
#ifdef AUI
        // AUI Sample code test default enable AUDIO DESCRIPTION SUPPORT
    #if(SYS_SDRAM_SIZE >= 128) //if only support broastcast mixed mode,set 0,if support receive mixed mode,set 1
        cfg->adv_cfg_para.audio_description_support = TRUE;
    #endif
#endif

	cfg->adv_cfg_para.sys_mute_gpio = gpio_array[SYS_MUTE_INDEX].position;
	cfg->adv_cfg_para.sys_mute_polar = gpio_array[SYS_MUTE_INDEX].polar;
	cfg->adv_cfg_para.ext_mute_mode = MUTE_BY_GPIO;    
	cfg->adv_cfg_para.snd_output_chip_type =  1;

#ifdef HD_SUBTITLE_SUPPORT
	cfg->adv_cfg_para.hd_subtitle_support = TRUE;
#else
	cfg->adv_cfg_para.hd_subtitle_support = FALSE;
#endif

	cfg->adv_cfg_para.tve_full_current_mode = FALSE;
	cfg->adv_cfg_para.tve_tbl = tve_table_total;
#if defined(DUAL_VIDEO_OUTPUT_USE_VCAP)
	cfg->adv_cfg_para.tve_adjust = g_sd_tve_adjust_table;
	cfg->adv_cfg_para.tve_adjust_adv = tve_sd_adjust_table_adv;
#endif

#ifdef SUPPORT_PACKET_26
	cfg->adv_cfg_para.ttx_packet_26_support = TRUE;
#else
	cfg->adv_cfg_para.ttx_packet_26_support = FALSE;
#endif
#ifdef TTX_SUB_PAGE
	cfg->adv_cfg_para.ttx_sub_page = TRUE;
#else
	cfg->adv_cfg_para.ttx_sub_page = FALSE;
#endif

#ifdef MULTI_CAS
	cfg->adv_cfg_para.cas_type = CAS_TYPE;

#ifdef SUPPORT_CAS9
	cfg->adv_cfg_para.cas9_support = TRUE;
#else
	cfg->adv_cfg_para.cas9_support = FALSE;
#endif
	cfg->adv_cfg_para.invert_detect  = 1;
#endif

#ifdef SUPPORT_AFD_SCALE
	cfg->adv_cfg_para.afd_scale_support = TRUE;
#else
	cfg->adv_cfg_para.afd_scale_support = FALSE;
#endif

#ifdef H264_SUPPORT_MULTI_BANK
	cfg->adv_cfg_para.h264_support_mulit_bank = TRUE;
#else
	cfg->adv_cfg_para.h264_support_mulit_bank = FALSE;
#endif

#ifdef CHANCHG_VIDEOTYPE_SUPPORT
	cfg->adv_cfg_para.chanchg_video_type_support = TRUE;
#else
	cfg->adv_cfg_para.chanchg_video_type_support = FALSE;
#endif

#ifdef AVC_SUPPORT_UNIFY_MEM
	cfg->adv_cfg_para.avc_unify_mem_support = TRUE;
#else
	cfg->adv_cfg_para.avc_unify_mem_support = FALSE;
#endif
	cfg->adv_cfg_para.ce_api_enabled = TRUE;

	/*add for setting priority for IP access DDR.*/
	board_ddr_priority_init();

	return cfg;
}

//extern INT32 scart_mx9671_attach(struct scart_init_param * param);
extern void pan_ch455_id_set(struct pan_device *dev, UINT32 id);
extern INT32 pan_ch455_attach(struct pan_configuration *config);

board_cfg* get_board_config(void)
{
	UINT8 i = 0;

	MEMSET(&board_config, 0, sizeof(board_cfg));
	board_config.pin_mux_count          = ARRAY_SIZE(pin_mux_array);
	board_config.all_gpio_count         = ARRAY_SIZE(gpio_array);
	board_config.mem_gpio_enabled       = MEM_GPIO_ENABLED;
	board_config.pin_mux_array          = pin_mux_array;
	board_config.all_gpio_array         = gpio_array;

	board_config.ddr_power_ctl = NULL;
	//board_config.sys_power = &gpio_array[SYS_POWER_INDEX];
	board_config.sys_power = NULL;
	board_config.mute = &gpio_array[SYS_MUTE_INDEX];
	board_config.usb_power = NULL;
#ifdef PMU_ENABLE
	board_config.fp_standby = NULL;//&gpio_array[GPIO_POWER_LED];
#else
	//board_config.fp_standby = &gpio_array[GPIO_POWER_LED];
#endif

#ifdef DVBT_SUPPORT
	board_config.scart_tvsat_switch = &gpio_array[SCART_TV_SAT_SWITCH_INDEX];
	board_config.scart_aspect = &gpio_array[SCART_ASPECT_INDEX];
	board_config.scart_tv_fb = &gpio_array[SCART_TV_FB_INDEX];
#else
	board_config.scart_tvsat_switch = NULL;//&gpio_array[SCART_TV_SAT_SWITCH_INDEX];
	board_config.scart_aspect = NULL;//&gpio_array[SCART_ASPECT_INDEX];
	board_config.scart_tv_fb = NULL;//&gpio_array[SCART_TV_FB_INDEX];
#endif

	board_config.scart_power = NULL;
	board_config.scart_vcr_switch = NULL;
	board_config.scart_vcr_detech = NULL;
	board_config.smc_5v_ctl = NULL;
	board_config.ata2lan_cs = NULL;

#ifdef SDIO_SUPPORT
	board_config.sdio_detect = &gpio_array[SDIO_GPIO_DETECT_INDEX];
	board_config.sdio_lock = &gpio_array[SDIO_GPIO_LOCK_INDEX];
	board_config.sdio_cs = &gpio_array[SDIO_GPIO_CS_INDEX];
#endif

#ifdef DVBS_SUPPORT
	board_config.front_end_cfg[0] = front_end_s_cfg(0);
#ifdef SUPPORT_TWO_TUNER
	//board_config.front_end_cfg[1] = front_end_s_cfg(1);
#endif
#elif defined(ISDBT_SUPPORT)
	board_config.front_end_cfg[0] = front_end_isdbt_cfg(0);
#elif defined(DVBT_SUPPORT)
	board_config.front_end_cfg[0] = front_end_t_cfg(0);
#endif

#ifdef DVBC_SUPPORT
	board_config.front_end_cfg[0] = front_end_c_cfg(0);
#ifdef SUPPORT_TWO_TUNER
	board_config.front_end_cfg[1] = front_end_c_cfg(1);
#endif
#endif

	board_config.libc_printf_uart_id = SCI_FOR_RS232;
	board_config.sci_config[0] = &sci_config[0];
#ifndef DUAL_ENABLE
	board_config.sci_config[1] = NULL;//&sci_config[1];
#endif
	for(i=0;i<6;i++)
	{
		board_config.i2c_config[i] = &i2c_config[i];
	}
	board_config.i2c_gpio_num = 2;
	board_config.i2c_scb_num = 4;

	//M3811_DB_01V01 has no SCART IC
	//board_config.scart_param = &scart_param;
	//board_config.scart_attach = scart_mx9671_attach;
	board_config.scart_param = NULL;
	board_config.scart_attach = NULL;
	board_config.pan_config = &pan_config;
	board_config.pan_i2c_id_set = pan_ch455_id_set;
	board_config.pan_i2c_id = I2C_TYPE_GPIO0;
	board_config.pan_attach = pan_ch455_attach;
	board_config.flash_type = 0;
	board_config.rfm_attach = NULL;
	board_config.rfm_i2c_id = I2C_TYPE_SCB1;
	board_config.key_map = g_itou_key_tab;
	board_config.ir_key_maps = ir_key_maps;
	board_config.key_map_cnt = sizeof(g_itou_key_tab)/(sizeof(struct ir_key_map_t));

	return advance_cfg(&board_config);
}

unsigned long __G_ALI_BOARD_TYPE=0X3001;
#define ALI_HW_REG_R32(i)       (*(volatile unsigned int *)(i))
#define ALI_HW_REG_W32(i, d) do {(*(volatile unsigned int *)(i)) = (d);} while(0)

int ali_reg_set_bits32(unsigned int address, unsigned int start_bit_idx,/* From 0 to 31*/
	unsigned int end_bit_idx,/* From 0 to 31, should be bigger than StartBitIdx*/ unsigned int bits_value)
{
	unsigned int value;
	unsigned int mask;
	unsigned int idx;

	mask = 0;

	for (idx = start_bit_idx; idx <= end_bit_idx; idx++)
	{
		mask |= (1 << idx);
	}

	bits_value <<= start_bit_idx;
	bits_value &= mask;

	/*Clean Value conrresponding bits to 0.*/
	mask = (~mask);
	value = ALI_HW_REG_R32(address);
	value &= mask;

	/* Set BitsValue to Value. */
	value |= bits_value;

	/* Set Value to HW. */
	ALI_HW_REG_W32(address, value);

	return(0);
}

unsigned int ali_reg_get_bits32(unsigned int address, unsigned int start_bit_idx,/* From 0 to 31*/
	unsigned int end_bit_idx/* From 0 to 31, should be bigger than StartBitIdx*/)
{
	unsigned int value;
	unsigned int mask;
	unsigned int idx;

	mask = 0;
	for (idx = start_bit_idx; idx <= end_bit_idx; idx++)
	{
		mask |= (1 << idx);
	}

	value = ALI_HW_REG_R32(address);
	value &= mask;
	value >>= start_bit_idx;

	return(value);
}

void phy_chip_setting(void)
{
}

