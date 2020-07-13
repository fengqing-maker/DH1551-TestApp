#ifndef _PVR_CONNTROL_H_
#define _PVR_CONNTROL_H_

#include <sys_config.h>

#ifdef DVR_PVR_SUPPORT
#include <api/libpvr/lib_pvr.h>
#include <api/libpvr/lib_pvr_crypto.h>

// debug macro define
#define CI_PATCH_TRACE_ENABLE				0
#define TS_ROUTE_DEBUG_ENABLE				0
#define PVR_CRYPTO_DEBUG_ENABLE				0

#ifdef _INVW_JUICE   
#define PRESULT UINT8
#endif

#if CI_PATCH_TRACE_ENABLE
	#define CI_PATCH_TRACE(fmt, arg...)		libc_printf(fmt, ##arg)
#else
	#define CI_PATCH_TRACE(...)				do{} while(0)
#endif

#if PVR_CRYPTO_DEBUG_ENABLE
	#define PVR_CRYPTO_DEBUG(fmt, arg...) 	libc_printf(fmt, ##arg)
	#define PVR_CRYPTO_ERROR(fmt, arg...) \
		do { \
			libc_printf("Error: %s line %d: "fmt, __FILE__, __LINE__, ##arg); \
		} while (0)
#else
	#define PVR_CRYPTO_DEBUG(...)			do{} while(0)
	#define PVR_CRYPTO_ERROR(...)			do{} while(0)
#endif

#define PVR_ROOT_DIR	"ALIDVRS2"
#define PVR_TIMER_WAIT_TIME_FREE_PROG 		10
#define PVR_TIMER_WAIT_TIME_SCRAMBLE_PROG 	60 // wait for CAM work ok!
#define PVR_SUBTTX_EN	1
#define PVR_REC_END_TIME					2 // record end time
#define PVR_END_TIMER_STOP_REC				0xff	

#define REC_IDX0							0
#define REC_IDX1							1
#define PVR_MAX_RECORDER					2
#define REC_MASK 							0x52454330		//"REC0"
#define PLY_MASK 							0x504C5930		//"PLY0"
#define HND_INDEX_OFFSET					24

#define IDE_MOUNT_NAME						"/d"
#define USB_MOUNT_NAME						"/c"
#define PVR_MOUNT_NAME 						"/r"

//#define PVR_SPEED_PRETEST_DISABLE /*added by doy,2011-3-24*/
//#define PVR_CRYPTO_TEST						// only define to test pvr crypto api

typedef enum
{
    PVR_STATE_IDEL = 0,
    PVR_STATE_TMS, 				// time-shifting
    PVR_STATE_TMS_PLAY, 		// play time-shifting prog
    PVR_STATE_REC, 				// recording
    PVR_STATE_REC_PLAY, 		// recording and play recording prog
    PVR_STATE_REC_PVR_PLAY, 	// recording and play HDD prog
    PVR_STATE_UNREC_PVR_PLAY, 	// play HDD prog
    PVR_STATE_REC_TMS,			// recording a prog, 
    							// time-shifting b prog within same tp without playing.

    PVR_STATE_REC_TMS_PLAY,		// recording a prog, 
    							// time-shifting b prog within same tp and playing.

    PVR_STATE_REC_TMS_PLAY_HDD,	// recording a prog, 
    							// time-shifting record b prog within same tp,
    							// playing another program C from HDD.
    PVR_STATE_REC_REC,			// recording two prog within same tp.
    PVR_STATE_REC_REC_PLAY,		// recording two prog within same tp and play one recording prog.    
    PVR_STATE_REC_REC_PVR_PLAY,	// recording two prog within same tp and play hdd prog.    
}PvrState_t;

typedef struct
{
	UINT32 		play_chan_id;			/* played channel's index. For PLAY_CHAN_SAT only  */
	PVR_HANDLE	play_handle;			/* play handle (for PLAY_CHAN_SAT&timeshift_chan_flag or PLAY_CHAN_RECORD)*/
	UINT32 		play_index;				// play the record index.
	UINT32		RL_A_time;
	UINT32		RL_mutex_ptm;
}pvr_play_t;


typedef struct
{
	UINT8 		record_chan_flag;	/* 0 - not recording, 1 - recording */
	UINT8		ca_mode;
	INT8		ci_id;
	BOOL		is_scrambled;
	BOOL		rec_descrambled;
	UINT32		record_chan_id;	/* Record channel ID  */
	UINT32		duraton;
	BOOL		rec_by_timer;
	UINT8		rec_timer_id;
	UINT32		ts_bitrate;
	date_time	record_start_time;
	date_time	record_end_time;
	PVR_HANDLE	record_handle;		/* recorder handle */
	UINT8       preset_pin; 
	UINT8 	    pin[PWD_LENGTH];
#if (defined SUPPORT_VMX) || (defined SUPPORT_VMX_STD)
	UINT8      nsc_preset_pin; 
	UINT8 	   nsc_pin[PWD_LENGTH];
#endif
}pvr_record_t;


typedef struct
{
	pvr_play_t 		play;
	pvr_record_t	rec[PVR_MAX_RECORDER];
	//pvr_record_t	rec; 
	UINT8			rec_last_idx;
	BOOL			tms_enable;
	BOOL			rec_enable;
	UINT8			stop_rec_idx;
	UINT8			rec_num;
	PVR_HANDLE		tms_r_handle;
	UINT32			tms_scrambled;
	UINT32			tms_ts_bitrate;
	UINT32			tms_chan_id;
	UINT8			hdd_valid;
	PvrState_t		pvr_state;
	UINT8			hdd_status;
	UINT8			hdd_num;
#ifdef PVR3_SUPPORT
	UINT8 			continue_tms;
#endif
}pvr_play_rec_t;

enum
{
	PVR_HND_IDX_REC0 = 0,
	PVR_HND_IDX_REC1 = 1,
	PVR_HND_IDX_PLY0 = 16,
	PVR_HND_REC0	 = 0x52454330,
	PVR_HND_REC1	 = 0x52454331,
	PVR_HND_PLY0	 = 0x504C5930,
};

extern struct dmx_device *g_dmx_dev, *g_dmx_dev2, *g_dmx_dev3;
extern BOOL api_operate_ci(UINT8 mode, UINT8 slot_mask, UINT32 sim_id, void *nim, void *dmx, UINT32 prog_id, UINT16 v_pid, UINT16 a_pid);
extern BOOL api_check_TS_by_dmx(UINT8 dmx_id, UINT8 ts_id, UINT32 tp_id, BOOL is_goal_dmx, BOOL scramble, BOOL start_ci_service);
char *pvr_get_root_dir_name(void);

PvrState_t ap_pvr_set_state(void);
PRESULT ap_pvr_message_proc(UINT32 msg_type,UINT32 msg_code,UINT16 call_mode);
PRESULT ap_pvr_timer_proc(UINT32 msg_code, TIMER_SET_CONTENT* timer);
void ap_pvr_moniter_proc(void);
BOOL api_pvr_record_proc(BOOL start, UINT8 rec_type, UINT32 rec_prog_id);
BOOL api_pvr_tms_proc(BOOL start);
void api_pvr_set_back2menu_flag(BOOL val);
PVR_HANDLE api_start_record(UINT32 channel_id, BOOL is_scrambled, UINT8 rec_type);
BOOL api_stop_record(PVR_HANDLE handle, UINT32 index);
void api_start_tms_record(UINT32 channel_id,BOOL is_scrambled);
void api_stop_tms_record(void);
BOOL api_start_play_record(UINT32 rl_idx,  PVR_STATE state,UINT32 speed, UINT32 start_time, BOOL preview_mode);
void api_stop_play_record(UINT32 bpause);

void api_pvr_change_record_mode(UINT32 prog_id);
void api_pvr_set_record_finish(UINT32 prog_id,UINT8 is_not_finish);
void api_pvr_change_tms_mode(UINT32 prog_id);
pvr_record_t *api_pvr_get_rec_by_prog_id(UINT32 prog_id, UINT8 *pos);
UINT8 api_pvr_get_rec_num_by_dmx(UINT8 dmx_id);
pvr_record_t *api_pvr_get_rec_by_dmx(UINT8 dmx_id, UINT8 pos);
BOOL api_pvr_check_dmx_canuseci(UINT8 ca_mode, UINT8 dmx_id);
BOOL api_pvr_is_recording();
BOOL api_pvr_is_playing();
BOOL api_pvr_is_playing_hdd_rec();
BOOL api_pvr_is_live_playing();
UINT32 api_pvr_gettotaltime_byhandle(PVR_HANDLE	play_handle);
UINT32 api_pvr_get_jumpstep();
UINT32 api_pvr_respond_key(UINT32 key, UINT32 vkey, UINT32 osd_msg_code);
void pvr_monitor_task(void);
INT8 pvr_evnt_callback(PVR_HANDLE handle, UINT8 msg);
void pvr_module_init();
PVR_HANDLE pvr_msg_idx2hnd(UINT8 index);
UINT8 pvr_msg_hnd2idx(PVR_HANDLE pvr_handle);
UINT32 pvr_rechnd2idx(PVR_HANDLE pvr_handle);
pvr_record_t *api_pvr_get_rec(UINT8 pos);
pvr_record_t *api_pvr_get_rec_by_handle(PVR_HANDLE hdl, UINT8 *pos);
pvr_record_t *api_pvr_get_rec_by_idx(UINT16 index, UINT8 *pos);
void api_pvr_set_stop_play_attr(UINT32 stop_attr);

#ifdef _INVW_JUICE   
BOOL api_pvr_is_rec_only_or_play_rec();
BOOL api_pvr_get_rec_ts_route(UINT32 channel_id, struct ts_route_info *p_ts_route);
#endif

extern pvr_play_rec_t  pvr_info;

#ifdef MULTI_PARTITION_SUPPORT
int pvr_change_tms_vol(char *new_vol);
#endif

#ifdef PARENTAL_SUPPORT
BOOL api_pvr_get_rating_lock_eit_flag(void);
UINT32 api_pvr_get_rating(PVR_HANDLE handle);
void api_pvr_set_rating(PVR_HANDLE handle, UINT32 rating);
void api_pvr_force_unlock_rating(void);
BOOL pvr_playback_preview_rating_check(PVR_HANDLE handle);
BOOL pvr_rating_check(UINT16 cur_channel);
void UISetPVRRatingLock(BOOL lock);
#endif


#ifdef CAS9_V6
//play_apply_uri
void api_pvr_set_rec_uri(conax6_URI_item_m *rec_uri, UINT8 sid);
void api_set_play_uri_cnt(UINT32 uricnt);
UINT32 api_get_play_uri_cnt(void);
void api_set_play_cur_step(UINT32 step);
UINT32 api_get_play_cur_step(void);
void api_set_play_cur_uri(conax6_URI_item_m* URI_sets);
void api_get_play_cur_uri(conax6_URI_item_m* URI_sets);
BOOL api_get_play_next_uri(PVR_HANDLE handle, conax6_URI_item_m* cur_uri, conax6_URI_item_m* next_uri);
void api_cnx_playback_convert_time(date_time *uri_dt, UINT32 day, UINT32 hour, UINT32 min);
BOOL api_cnx_playback_compare_time(date_time *uri_dt, date_time *utc_dt);
BOOL api_pvr_cnx_check_play(conax6_URI_item_m* URI_sets, BOOL check_rec_list);
void api_pvr_check_uri(void);
void api_cnx_check_rec_playlist(BOOL bg); //check_rec_list
#endif


#endif
#endif//_PVR_CONNTROL_H_

