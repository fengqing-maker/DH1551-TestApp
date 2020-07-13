#ifndef _WIN_COM_H_
#define _WIN_COM_H_

#ifdef _INVW_JUICE
#include <sys_config.h>
#endif
#ifndef NEW_DEMO_FRAME
#include <api/libpub29/lib_pub27.h>
//modify bomur 2011 09 19
#include <api/libpub29/lib_hde.h>
#include <api/libpub29/lib_as.h>
#include <api/libpub29/lib_nim_manage.h>
//modify end
#else
#include <api/libpub/lib_pub.h>
//modify bomur 2011 09 19
#include <bus/tsi/tsi.h>
#include <api/libpub/lib_as.h>
#include <api/libpub/lib_hde.h>
//modify end
#include <api/libpub/lib_device_manage.h>
#include <api/libpub/lib_frontend.h>
#endif
#include <api/libosd/osd_lib.h>
#include <api/libsi/sie_monitor.h>

#include "copper_common/dev_handle.h"
#include "copper_common/com_api.h"
#include "copper_common/menu_api.h"
#include "copper_common/com_epg.h"
#include "copper_common/system_data.h"
//#include "pvr_control.h"
#include "vkey.h"

#include <bus/dog/dog.h>

#if defined(_VMX_CA_STD_ENABLE_) || defined(_VMX_CA_ENABLE_)
#ifdef SD_UI
//win_light_chan_list.c
#define	W_LCL_L	14     
#define	W_LCL_T	20
#define	W_LCL_W     255
#define	W_LCL_H      425
#endif
#endif

#define GET_MID_L(w)	((OSD_MAX_WIDTH-(w))/2)
#define GET_MID_T(h)	((OSD_MAX_HEIGHT-(h))/2)

/* Menu Open type & parameter mask */
#define MENU_OPEN_TYPE_MASK		0xFF000000
#define MENU_OPEN_PARAM_MASK		0x000000FF

#define MENU_OPEN_TYPE_KEY 	0xFF000000		/* PARAM : vkey			*/
#define MENU_OPEN_TYPE_MENU 	0xFE000000		/* PARAM : menu item ID */
#define MENU_OPEN_TYPE_STACK	0xFD000000		/* PARAM : null */
#define MENU_OPEN_TYPE_OTHER	0xFC000000		/* PARAM : null */

#define MENU_FOR_ISDBT 0x0000ff00

#define INVALID_SIM_ID (UINT32)(~0)

extern UINT8 cur_tuner_idx;
extern UINT8 g_ci_num;
extern UINT8 g_tuner_num;

#ifdef SEARCH_DEFAULT_FTAONLY
#define FATONLY_DEFAULT SEARCH_DEFAULT_FTAONLY
#else
#define FATONLY_DEFAULT 1
#endif

typedef struct win_scanch_channel_info_tag
{
	UINT32  VHF_Current_Ch_No;
	UINT32  VHF_Start_Ch_No;
	UINT32  VHF_End_Ch_No;
	UINT32  UHF_Start_Ch_No;
	UINT32  UHF_End_Ch_No;
	UINT32  UHF_Current_Ch_No;
}win_scanch_channel_info_t;


struct help_item_resource
{
	UINT16	bmp_id;
	UINT16	str_id;
};

void wincom_open_title(POBJECT_HEAD rootwin,UINT16 title_strid,UINT16 title_bmpid);
void wincom_close_title(void);

void wincom_open_help(POBJECT_HEAD rootwin,struct help_item_resource *helpinfo,UINT8 item_count);
void wincom_close_help(void);

/* For tuner index : see TUNER_TYPE_T*/
UINT16 get_tuner_strid(UINT32 tuner_idx);
UINT32 get_tuner_cnt(void);
UINT16 get_tuner_sat_cnt(UINT16 tuner_idx);
void   get_tuner_sat(UINT32 tuner_idx, UINT32 sat_idx, S_NODE* snode);
void   get_tuner_sat_name(UINT32 tuner_idx, UINT32 sat_idx, UINT16* unistr);

void   get_tp_name(UINT32 sat_id, UINT32 tp_pos,UINT16* unistr);
UINT32 get_lnb_type_cnt(void);
UINT32 get_lnb_type_index(UINT32 lnb_type, UINT32 lnb_freq1, UINT32 lnb_freq2);
void   get_lnb_type_setting(UINT32 lnb_idx,UINT32* lnb_type, UINT32* lnb_freq1, UINT32* lnb_freq2);
void   get_lnb_name(UINT32 lnb_idx,UINT16* unistr);

UINT32 get_diseqc10_cnt(void);
void   get_diseqc10_name(UINT32 index,char* str, UINT16* unistr,UINT16* strID);

UINT32 get_diseqc11_cnt(void);
void   get_diseqc11_name(UINT32 val, UINT16* unistr);
UINT32 diseqc11_db_to_ui(UINT32 diseqc11_type, UINT32 diseqc11_port);
void   diseqc11_ui_to_db(UINT32 val, UINT8 *type, UINT8 *port);

UINT16 get_unicable_freq(UINT8 index);
UINT32 get_unicable_freq_index(UINT16 freq); 
UINT16 get_IF_channel_cnt(void);
UINT16 get_centre_freqs_cnt(void);
void get_IF_channel_name(UINT32 channel_idx,UINT16* unistr);
void get_centre_freqs_name(UINT32 freq_idx,UINT16* unistr);

void  get_chan_group_name(char* group_name,UINT8 group_idx,UINT8* group_type);
void  get_cur_group_name(char* group_name,UINT8* group_type);

#ifndef NEW_DEMO_FRAME
void sat2antenna_ext(S_NODE *sat, struct cc_antenna_info *antenna,UINT32 tuner_idx);
#endif

void remove_menu_item(CONTAINER* root,OBJECT_HEAD* item,UINT32 height);
UINT16 win_load_default_satidx();

UINT32 get_tv_mode_count(void);
UINT32 get_tv_mode_set(UINT32 index);
char *get_tv_mode_string(UINT32 index);
UINT32 get_tv_mode_panel_next(UINT32 index);
UINT32 tvmode_setting_to_osd(enum TV_SYS_TYPE set);
UINT32 tvmode_osd_to_setting(UINT32 osd);

void  get_dvbc_freq_str(UINT32 freq, void* str, BOOL Uni);

//modify bomur 2011 09 19
void increase_val_inuncode(UINT16 *ptr_base,UINT32 pos);
void decrease_val_inuncode(UINT16 *ptr_base,UINT32 pos);
//modify end

////////////////////////////////////////////////////////
// sub list (SAT / TP / LNB / DisEqC1.0 )

#ifdef PARENTAL_SUPPORT
BOOL rating_check(UINT16 cur_channel, BOOL all_check);
void UISetRatingLock(BOOL lock);
void clear_pre_ratinglock(void);
#endif

typedef enum
{
	POP_LIST_TYPE_SAT,		// param :  id - > SAT_POP_LIST_PARAM_T, cur -> current selection or focus
	POP_LIST_TYPE_TP,		// param :  id -> S_NODE's ID			  
	POP_LIST_TYPE_LNB,		// param:  id -> S_NODE's ID, 
	POP_LIST_TYPE_DISEQC10,//NULL
	POP_LIST_TYPE_DISEQC11,//NULL
	POP_LIST_TYPE_CHGRPALL,
	POP_LIST_TYPE_CHGRPFAV,
	POP_LIST_TYPE_CHGRPSAT,
	POP_LIST_TYPE_FAVSET,
	POP_LIST_TYPE_SORTSET,
	POP_LIST_TYPE_RECORDLIST,
#ifdef MULTI_PARTITION_SUPPORT
	POP_LIST_TYPE_VOLUMELIST,
#endif
	POP_LIST_TYPE_CHANLIST,
	POP_LIST_MENU_LANGUAGE_OSD,
	POP_LIST_MENU_LANGUAGE_STREAM,
	POP_LIST_MENU_TVSYS,
	POP_LIST_MENU_OSDSET,
	POP_LIST_MENU_TIME,
	POP_LIST_MENU_KEYLIST,	
	POP_LIST_TYPE_IF_CHANNEL,
	POP_LIST_TYPE_CENTRE_FREQ,
	POP_LIST_TYPE_MPSORTSET,
	POP_LIST_TYPE_VIDEOSORTSET,
#ifdef DISPLAY_SETTING_SUPPORT
	POP_LIST_MENU_DISPLAY_SET,
#endif
	POP_LIST_DISK_MODE,
	POP_LIST_DVR_TYPE,
	POP_LIST_PARTITION,
#ifdef DISK_MANAGER_SUPPORT
	POP_LIST_REMOVABLE_DISK_INFO,
#endif

//#ifdef SHOW_WELCOME_SCREEN
	POP_LIST_MENU_COUNTRY_NETWORK,
//#endif
	POP_LIST_MENU_PARENTAL_MENU_LOCK,
	POP_LIST_MENU_PARENTAL_CHANNEL_LOCK,
	POP_LIST_MENU_PARENTAL_CONTENT_LOCK,	
#ifdef MP_SUBTITLE_SETTING_SUPPORT
	POP_LIST_SUBT_SET,
#endif
#ifdef IMG_2D_TO_3D
    POP_LIST_IMAGE_SET,
#endif
#ifdef MULTIVIEW_SUPPORT
    POP_LIST_MULTIVIEW_SET,
#endif
#ifdef SAT2IP_SERVER_SUPPORT
    POP_LIST_MENU_SATIP_SLOT_INSTALL,
#endif
#ifdef SAT2IP_CLIENT_SUPPORT
	POP_LIST_MENU_SATIP_SERVER,
#endif

}COM_POP_LIST_TYPE_T;

typedef enum
{
	TUNER_FIRST = 0,
	TUNER_SECOND,
	TUNER_EITHER,	//
	TUNER_EITHER_SELECT,
}TUNER_TYPE_T;

typedef enum
{
	POP_LIST_NOSELECT = 0,	
	POP_LIST_SINGLESELECT,
	POP_LIST_MULTISELECT	
}COM_POP_LIST_SELECT_TYPE_T;


typedef struct
{
	UINT32 id;			/* Tuner for satlist / sat ID for tplist */
	UINT32 cur;			/* Current selection / focus */
	UINT32 selecttype;		/* COM_POP_LIST_SELECT_TYPE_T for satlist only */
	UINT8* select_array;	
}COM_POP_LIST_PARAM_T;
	
UINT16 win_com_open_sub_list(COM_POP_LIST_TYPE_T type,OSD_RECT* pRect, COM_POP_LIST_PARAM_T* param);

#define HELP_TYPE_INFOR		1 // only exit
#define HELP_TYPE_FACTORY	2 // H, 3icon
#define HELP_TYPE_RS232		0
#define HELP_TYPE_OTA		0 // 4 icon
#define HELP_TYPE_OTHER		3 // no OK, 3Icon
#define HELP_TYPE_FAVGROUP	4 // V, 3Icon
#define HELP_TYPE_OSDSET	0 // 4 icon
#define HELP_TYPE_PARENT_LOCK		3 // no OK, 3Icon
#define HELP_TYPE_UPGRAGE	5 // 2icon exit, ok
#define HELP_TYPE_TPLIST	6 // 2icon exit, ok
#define HELP_TYPE_SATLIST	7 // 2icon exit, ok
#define HELP_TYPE_PREVIEW   8 // 4 icon
#define HELP_TYPE_EPG       9     
#define HELP_TYPE_MEDIA 10
#define HELP_TYPE_PVRLIST 11

#ifdef NETWORK_SUPPORT
typedef UINT32 (*lib_net_ui_callback)(UINT32 type, UINT32 code);
typedef UINT32 (*lib_net_user_stop)();

typedef struct
{
	IP_REMOTE_CFG rmt_cfg;	// remote config
	IP_LOC_CFG local_cfg;	// local config
	lib_net_ui_callback pfn_ui_connect;	// indicator msg to ap
	lib_net_user_stop pfn_user_stop;	// check user cancel net upgrade.
	UINT32 file_addr;					// get the upgrade file address
	UINT32 file_len;
}LIB_NUC, *PLIB_NUC; // lib net upgrade config
#endif

UINT16 AudioPid2Type(UINT16 audioPID);

extern const char *QamTable[];

#endif//_WIN_COM_H_

