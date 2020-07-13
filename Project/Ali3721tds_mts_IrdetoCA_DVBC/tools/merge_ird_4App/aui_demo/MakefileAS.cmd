#
# -= Makefile for application compile =-
#
# Note:
# . This is the 1st part of two makefile components;
#   Please refer "Makefile.lin" for the other part.
#
# Usage:
# . Name this file as "Makefile";
#   Put it in the same directory as application's source code.
# . Change the ROOT definition, if necessary;
#   Make it point to the root of the software tree.
# . Take application as a module, define the name in MOD;
#   There should be NO duplicated module names in the whole project.
# . List all files want to be compiled in ASMS and/or SRCS;
#   Including files, such as header files, must NOT be listed here.
# . List all library files this module may depends on in LIBS.
# . Give a new name in SMOD, if want to include sub-directories;
#   Write the linkage information at the end of file.
#

# Destination to the root of software tree
ROOT = ../../../../..

include ${ROOT}/src/path.def
include ${ROOT}/src/compiler.def

CA_AP_DIR =
ifdef _CAS9_CA_ENABLE_
CA_AP_DIR = conax_ap
endif

ifdef _BC_CA_STD_ENABLE_	
BC_AP_DIR = bc_ap_std
BC_DIR=bc_std
endif

ifdef _BC_CA_ENABLE_
BC_AP_DIR = bc_ap
endif

ifdef _FTA_ONLY_
CA_AP_DIR = fta_ap
endif

# Module Name
MOD = SABBAT_DEMO
BL_RMOD = LIB_BOOTUPG BOOT_SLOT3602

# Link Script File
LSCR = ldscript.ld
ifdef _M3383_SABBAT_
SEE_LSCR = see_ldscript_M3383_sabbat.ld
else
	ifdef _S3281_
		ifdef _USE_32M_MEM_
			ifdef _M3281_SOLUTION3_SUPPORT_
				SEE_LSCR = see_ldscript_M3281_32M_solution3.ld
			else
				ifdef _CAS9_VSC_ENABLE_
					SEE_LSCR = see_ldscript_M3281_VSC_32M.ld
				else
					SEE_LSCR = see_ldscript_M3281_32M.ld
				endif
			endif	
		else
			ifdef _CAS9_VSC_ENABLE_
				SEE_LSCR = see_ldscript_M3281_VSC_64M.ld
			else
				SEE_LSCR = see_ldscript_M3281_64M.ld
			endif
		endif
	else
		SEE_LSCR = see_ldscript.ld
	endif	
endif

# List of source files
ASMS =
ifdef _AUI_TEST_
SRCS += aui_root.c
else
SRCS = control.c ctrl_task_init.c ctrl_util.c ap_dynamic_pid.c ctrl_pip.c ctrl_debug.c ctrl_network.c \
       ctrl_play_channel.c ctrl_cas_ap.c ap_ctrl_mheg5.c ap_ctrl_ci.c ctrl_key_proc.c \
       ap_ctrl_ttx.c ap_ctrl_dtg.c ap_ctrl_display.c ap_ctrl_time.c ctrl_msg_proc.c \
       ap_ctrl_dual_ci.c ap_ctrl_ci_plus.c ctrl_popup_msg.c ctrl_play_si_proc.c ctrl_preplay_channel.c \
       cec_link.c game_othello.c game_sudoku.c key.c lib_ash.c menus_root.c \
       mobile_input.c osd_rsc.c ota_ctrl.c power.c \
       pvr_ctrl_basic.c pvr_ctrl_cnx9_v6.c pvr_ctrl_parent_lock.c pvr_ctrl_ca.c pvr_ctrl_timer.c \
       pvr_ctrl_record_internal.c pvr_ctrl_record.c pvr_ctrl_play.c pvr_ctrl_tms.c pvr_ctrl_ts_route.c pvr_control.c\
       system_init.c root.c hdcp_des.c \
       si_auto_update_tp.c time_zone_name.c win_ali_demo.c \
       win_audio.c win_chan_list_internal.c win_chan_list.c \
       win_chan_rename.c win_chunk_info.c win_ci_common.c win_ci_dlg.c \
       win_ci_info.c win_ci_slots.c win_com_list_callback.c win_com_parental.c win_com_frontend.c \
       win_com.c win_com_list.c \
       win_com_popup_inner.c win_com_popup_cas.c win_com_popup.c win_diag_i2c.c win_diag_register.c win_diagnosis.c \
       win_display_set.c epg_time.c epg_function.c win_epg.c win_epg_detail.c win_factory_set.c win_factory_test.c \
       win_favgroup_list.c win_filelist_inner.c win_filelist_display.c win_filelist_act_proc.c win_filelist_api.c win_filelist.c \
       win_find.c win_game_com.c win_game_othello.c \
       win_game_sudoku.c win_hdmi_factory.c win_hdtv_mode.c \
       win_imagepreview.c win_imageslide.c win_language.c \
       win_light_chan_list.c win_mainmenu.c win_mainmenu_submenu.c \
       win_misc_setting.c win_mpeg_player_audio_track.c win_mp_subtitle.c \
       win_mpeg_player.c win_mpspectrum.c win_mpvolume.c win_mpzoom.c \
       win_mute.c win_net_local_seting.c win_net_upg.c \
       win_osd_set.c win_ota_set.c win_otaupg.c win_otaupg_private.c \
       win_password.c win_pause.c \
       win_playlist.c win_playlist_setup.c \
       win_prog_detail.c win_prog_input.c win_prog_name.c \
       win_pvr_ctrl_bar_basic.c win_pvr_ctrl_bar_key.c win_pvr_ctrl_bar_draw.c win_pvr_ctrl_bar.c \
       win_pvr_hdd_format.c win_pvr_hint.c \
       win_pvr_jumpstep.c Win_pvr_record_manager.c win_pvr_tms.c \
       Win_rs232upg.c win_search.c win_search_ext_function.c win_signal.c \
       win_signalstatus.c win_sleeptimer.c win_submenu.c win_subtitle.c \
       win_time.c win_time_ciplus.c win_timer_list.c win_timer_msg.c win_timer_set.c \
       win_tvsys.c win_sat_fav.c \
       win_usbupg.c win_volume.c win_mp_move_file.c win_pvr_setting.c \
       win_storage_setting.c media_control_es.c media_control.c win_no_menu.c \
       win_disk_info.c win_disk_operate.c win_copying.c win_zoom.c \
       win_automatic_standby.c win_multifeed.c win_hdmi_certification.c mp_subtitle_osd.c \
       disk_manager.c win_audio_description.c win_mheg5_v20.c \
       win_usblogo.c win_diag_energy.c win_chapter.c win_security_upg.c \
       win_ci_authinfo.c ad_pic_gif.c win_av_delay.c win_PALNTSC.c  win_combo_ota.c win_adc.c win_nimreg.c \
       win_welcom.c win_closedcaption.c win_calen_time.c win_com_popup_smsg.c  win_subtitle_setting.c \
       win_mainmenu_submenu_data.c win_prog_name_extra.c beep_mp2.c

ifdef _DVBS_ENABLE_
SRCS += win_antenna_connect.c win_antenna_set_fixed.c win_unicable_setting.c \
       win_antenna_set_motor.c win_motor_limitsetup.c win_motor_setting.c \
       win_sat_edit.c win_sat_list.c win_satsearch_set.c satcodx.c\
       win_tp_edit.c win_ascan_edit.c win_tp_list.c win_tpsearch_set.c win_parental_old.c 
else
SRCS += win_parental.c
endif

ifdef _DVBC_ENABLE_
SRCS += win_quickscan.c win_country_net.c win_countryband.c 
endif
ifdef _DVBT_ENABLE_
SRCS +=  win_auto_scan.c win_chan_scan.c win_countryband_t.c win_lcn.c
endif
ifdef _ISDBT_ENABLE_
SRCS +=  win_auto_scan.c win_chan_scan.c win_countryband_t.c win_lcn.c win_cc.c
endif
ifdef _WIFI_ENABLE_
SRCS += win_wifi_manager.c win_wifi_ap_select.c win_wifi_input_password.c
endif
ifdef _MAC_TEST
	SRCS +=iol_test_mainmenu.c iol_test_mainmenu_submenu.c iol_test_submenu.c iol_test_submenu_system.c\
	win_mac_rx_config.c win_mac_rxtx_state.c win_mac_submenu.c win_mac_test.c win_mac_tx_config.c
endif
ifdef _SFU_TEST_SUPPORT
	SRCS += sfu_test.c
endif
ifdef _RD_DEBUG_
	SRCS += ui_debug.c
endif
endif
# List of library files
LIBS =

# List of sub-modules
# Note: Can NOT be the same name as sub-directories.

# ==================================================

SMOD =
export SMOD_LIB =
NIM_S2_MOD =
NIM_S2_LIB =
NIM_T_MOD =
NIM_T_LIB =

#S3281 only DVB-S, no S2 
ifndef _S3281_
NIM_S2_MOD = LLD_NIM_S2
NIM_S2_LIB = libnim_s2.a
SMOD += ${NIM_S2_MOD}
ifdef _DVBS_ENABLE_
SMOD_LIB += ${NIM_S2_LIB}
endif
endif

NIM_T_MOD = LLD_NIM_M3101
NIM_T_LIB = libnim_t.a
SMOD += ${NIM_T_MOD}
ifdef _DVBT_ENABLE_
SMOD_LIB += ${NIM_T_LIB}
endif

# S3281 supports _DVBC_ENABLE_ and _DVBS_ENABLE_
NIM_S3281_C_MOD = LLD_NIM_S3281_C
NIM_S3281_C_LIB = libnim_s3281_c.a

NIM_S3281_S_MOD = LLD_NIM_S3281_S
NIM_S3281_S_LIB = libnim_s3281_s.a
ifdef _S3281_
SMOD += ${NIM_S3281_C_MOD}
SMOD += ${NIM_S3281_S_MOD}
ifdef _DVBC_ENABLE_
SMOD_LIB += ${NIM_S3281_C_LIB}
endif
ifdef _DVBS_ENABLE_
SMOD_LIB += ${NIM_S3281_S_LIB}
endif
SECLIB_MAIN = libmsec_m32
else
SECLIB_MAIN = libmsec
endif
# ==================================================


# List of dependent modules

DMOD = 

# Libplus pvr+fs modules
PMOD = LIB_DOSFS LIB_VFS LIB_PVR3_ENG \
       VERSION_INFO_PLUS LIB_STDIO LIB_MP

PPMOD = PLUGIN_ALL

ifdef DUAL_ENABLE
	_M36F_MODULE_DEF = 1
endif
ifdef _M36F_SINGLE_CPU
	_M36F_MODULE_DEF = 1
endif

ifdef _M36F_MODULE_DEF
PMOD += LIB_PVR3_CRYPTO
endif

ifdef _WIFI_ENABLE_
  export LMOD_BUS_USB_MODULE = BUS_USB_HC_M36F BUS_USB_USBD_M36F BUS_USB_DEV_STOR_M36F BUS_USB_HUB_M36F 
  export LIB_WIFI_MODULE = HLD_WIFI LIB_WIFI
else
  export LMOD_BUS_USB_MODULE = BUS_USB_HC_M36F BUS_USB_USBD_M36F BUS_USB_DEV_STOR_M36F BUS_USB_HUB_M36F 
  export LIB_WIFI_MODULE = HLD_WIFI
endif

ifdef _S3281_
  ifndef _BUILD_OTA_E_
  export CORE_MODULE = LLD_VP_M33 LLD_OSD_M31 LLD_SND_M31 LLD_DECA_M31
  else
  export CORE_MODULE = LLD_VP_M33 LLD_OSD_M31
  endif
else
  export CORE_MODULE = LLD_VP_M36F LLD_VP_M36G LLD_SND_M36F LLD_DECA_M36F 
endif

# Libcore library
ifdef _M36F_MODULE_DEF
LMOD = 	ARCH_M63 OS_TDS3 LLD_PMU_M36 \
	${CORE_MODULE} \
        LLD_DMX_M36F \
        LLD_PAN_HWSCAN \
        LLD_CIC_M36 \
        BUS_DMA_M36F \
        BUS_TSI_M36 \
        BUS_EROM_M36\
        BUS_TSG_M36 \
        BUS_DOG_M33 \
        $(LMOD_BUS_USB_MODULE) \
        BUS_SATA_M36F \
        BUS_OTP_M33 \
        HLD_GE \
        VERSION_INFO \
        LLD_DECV_M36 LLD_DECV_AVC LLD_DCEV_CFG \
        BUS_PINMUX_M36 LLD_PAN_HWSCAN LIB_CIPLUS_CC \
        LIB_RSA LIB_NETCTL BUS_RTC_M36 PDD_M33 LLD_SBM LLD_VSC

else

LMOD = 	ARCH_M63 OS_TDS3 LLD_PMU_M36\
        LLD_DECV_M36 LLD_DECV_AVC LLD_DCEV_CFG \
        LLD_VP_M36 \
        LLD_GE_M36 \
        LLD_OSD_M36_HD LLD_OSD_M3C\
        LLD_DMX_M36 \
        LLD_SND_M36 \
        LLD_DECA_M36 \
        LLD_PAN_HWSCAN \
        LLD_CIC_M36 \
        BUS_DMA_M36 \
        BUS_TSI_M36 \
        BUS_EROM_M36\
        BUS_TSG_M36 \
        BUS_DOG_M33 \
        BUS_USB_HC_M36 BUS_USB_USBD_M36 BUS_USB_DEV_STOR_M36 \
        BUS_OTP_M33 \
        HLD_GE BUS_SD_M33 \
        VERSION_INFO \
        LIB_LWIP

endif

ifdef _S3281_
ifdef _BUILD_OTA_E_
ifndef _BUILD_USB_LOADER_
	LMOD = 	ARCH_M63 OS_TDS3 LLD_PMU_M36 \
		${CORE_MODULE} \
         LLD_DMX_M36F \
         LLD_PAN_HWSCAN \
         BUS_DMA_M36F \
         BUS_TSI_M36 \
         BUS_DOG_M33 \
         BUS_OTP_M33 \
         HLD_GE \
         VERSION_INFO \
         LIB_RSA
endif         
endif
endif

# Release library
RMOD = BUS_I2C_SCB BUS_I2C_GPIO BUS_SCI_UART \
       HLD_BASE LIB_C \
       HLD_PAN  \
       HLD_SCART  \
       HLD_STO  \
       HLD_VP \
       HLD_OSD \
       HLD_DECV \
       HLD_VENC \
       HLD_VBI \
       HLD_DMX \
       HLD_SND \
       HLD_DECA \
       HLD_SDEC \
       HLD_CIC  \
       HLD_RFM  \
       HLD_NIM   \
       HLD_SCART \
       HLD_NET \
       LLD_IRC_M63 \
       LLD_SCART_AK4707 \
       LLD_SCART_MX9671 \
       LLD_PAN_CH455 \
       LLD_STO_FLASH_SQI \
       LIB_SUBT LLD_SDEC_SW \
       LIB_TTX LLD_VBI_M33 \
       LLD_RFM_MCBS373\
       LIB_NIM LIB_CIPLUS \
       LIB_TSI3_CON_PSI LIB_TSI3_DESCRIPTOR LIB_TSI3_PARSER LIB_TSI3_PLUGIN_EIT \
       LIB_TSI3_ENGINE \
       LIB_TSI3_PLUGIN_SEARCH LIB_TSI3_PLUGIN_MONITOR LIB_TSI3_PLUGIN_TDT LIB_TSI3_UTILITY \
       LIB_EPG LIB_CLOSE_CAPTION LIB_CHUNK LIB_DB4 LIB_UPG3 LIB_LIB7ZIP \
       LIB_CHAR LIB_OSDO \
       LIB_DBC LIB_OTA HLD_SMC LLD_SMARTCARD \
       LIB_USBUPG LIB_VFS2 \
       LIB_PVR3_MGR LIB_PVR3_API36 \
       LIB_NETUPG \
       HLD_DSC HLD_CRYPTO HLD_PVR \
       LIB_LISTS \
       LIB_PUB_ALL LIB_PUB_AS_ENGINE \
       VERSION_INFO_APP LIB_PE \
       LIB_CEC \
       $(LIB_WIFI_MODULE) \
       LIB_PE_MUSIC_ENGINE_INPUT_OGG LIB_PE_SUBTITLE LIB_GE_OSD

ifdef _S3281_
ifdef _BUILD_OTA_E_
ifndef _BUILD_USB_LOADER_
RMOD = BUS_I2C_SCB BUS_I2C_GPIO BUS_SCI_UART \
       HLD_BASE LIB_C \
       HLD_PAN  \
       HLD_SCART  \
       HLD_STO  \
       HLD_VP \
       HLD_OSD \
       HLD_DECV \
       HLD_VENC \
       HLD_DMX \
       HLD_SND \
       HLD_DECA \
       HLD_CIC  \
       HLD_RFM  \
       HLD_NIM   \
       HLD_SCART \
       HLD_NET \
       LLD_IRC_M63 \
       LLD_SCART_AK4707 \
       LLD_SCART_MX9671 \
       LLD_PAN_CH455 \
       LLD_STO_FLASH_SQI \
       LLD_RFM_MCBS373\
       LIB_NIM \
       LIB_TSI3_CON_PSI LIB_TSI3_DESCRIPTOR LIB_TSI3_PARSER LIB_TSI3_PLUGIN_EIT \
       LIB_TSI3_ENGINE \
       LIB_TSI3_PLUGIN_SEARCH LIB_TSI3_PLUGIN_MONITOR LIB_TSI3_PLUGIN_TDT LIB_TSI3_UTILITY \
       LIB_CHUNK LIB_UPG3 LIB_LIB7ZIP \
       LIB_CHAR LIB_OSDO \
       LIB_DBC LIB_OTA HLD_SMC \
       HLD_DSC HLD_CRYPTO HLD_PVR \
       LIB_PUB_ALL LIB_PUB_AS_ENGINE \
       VERSION_INFO_APP \
       LIB_CEC \
       LIB_GE_OSD
endif       
endif
endif

ifdef _DVBS_ENABLE_
ifdef _S3281_
RMOD += LLD_NIM_S LIB_PUB_AS_S LIB_DISEQC
else
RMOD += LLD_NIM_S2_TUNER LLD_NIM_S2_3501 LIB_PUB_AS_S LIB_DISEQC
endif
endif

ifdef _DVBT2_ENABLE_
RMOD += LLD_NIM_DVBT2 LIB_PUB_AS_T
endif
ifdef _DVBT_ENABLE_
RMOD += LLD_NIM_DVBT LIB_PUB_AS_T
endif

ifdef _DVBC_ENABLE_
RMOD += LLD_NIM_C LIB_PUB_AS_C LLD_NIM_TUN_TDA18250
endif
ifdef _ISDBT_ENABLE_
RMOD += LLD_NIM_ISDBT LLD_ISDBTCC LIB_ISDBTCC
#RMOD += LLD_NIM_ISDBT LLD_ISDBTCC LIB_ISDBTCC
endif

RMOD += LLD_NIM_COMBO

ifdef DUAL_ENABLE
RMOD += DUAL_MODULES
endif
LINKER=link
SEE_LINKER=see_link

###############################################################
ifdef _BUILD_OTA_E_

SRCS = control.c ctrl_task_init.c ctrl_util.c ap_dynamic_pid.c ctrl_play_channel.c ctrl_key_proc.c \
	   ap_ctrl_display.c ap_ctrl_time.c ctrl_msg_proc.c ctrl_popup_msg.c \
	   osd_rsc.c power.c hdcp_des.c system_init.c root.c key.c \
       win_com_popup_inner.c win_com_popup.c \
       win_otaupg.c  win_otaupg_private.c win_ota_set.c ota_ctrl.c win_signal.c \
	   win_signalstatus.c  win_mute.c win_pause.c win_tvsys.c win_com_frontend.c win_com.c \
	   win_com_list.c ota_link.c

ifdef _BUILD_USB_LOADER_
SRCS += win_usbupg.c Disk_manager.c
endif
ifdef _DVBT_ENABLE_
SRCS += win_countryband_t.c
endif
ifdef _ISDBT_ENABLE_
SRCS += win_countryband_t.c
endif
ifdef _DVBC_ENABLE_
SRCS += win_countryband.c
endif

LINKER=link_ota
SEE_LINKER=see_link_ota
endif
###############################################################

RELPROJ = ${BASE_DIR}
RELLIB = libstb

ifdef _S3281_
ifndef _BUILD_OTA_E_
	ifdef _USE_32M_MEM_
		ifdef _H264_SUPPORT_
			SEELIB = libsee_m32
		else
			SEELIB = libsee_m32_32M
		endif
	else
		SEELIB = libsee_m32
	endif
else
	ifdef _BUILD_USB_LOADER_
	SEELIB = libsee_m32
	else
	SEELIB = libsee_m32_ota
	endif
endif
BOOT_SEE = boot_see_m32
else
SEELIB = libsee
BOOT_SEE = boot_see
endif

ifdef DUAL_ENABLE
	ifdef _S3281_
		ifndef _BUILD_OTA_E_
			export DDKLIB = libcore_v40b_m32
		else
			ifdef _BUILD_USB_LOADER_
			export DDKLIB = libcore_v40b_m32
			else
			export DDKLIB = libcore_v40b_m32_ota
			endif
		endif
		export PVR_PLUS=libplus_v40b_m32
		BOOT_MOD = boot_v40b_m32
	else
		export DDKLIB = libcore_v40b
		export PVR_PLUS=libplus_v40b
		BOOT_MOD = boot_v40b
	endif
endif


ifdef _S3281_
LWIP_LIB =
else
LWIP_LIB = liblwip_hd.a
endif

ifdef _NESTOR_SUPPORT_
LWIP_LIB = liblwip_hd.a
endif

export OPENSSL_LIB = 
export CIPLUSCC_LIB = 

ifdef _CAS9_CA_ENABLE_
	ifdef _S3281_
		ifdef _CAS9_VSC_ENABLE_
			ifdef _CAS9_VSC_RAP_ENABLE_
				export CA_LIB = libconax_m32_vsc.a
			else
				ifdef _CAS9_SC_UPG_
					export CA_LIB = libconax_m32_scu.a libupg_rs232_m32_vsc.a
				else
					export CA_LIB = libconax_m32_vsc.a libupg_rs232_m32_vsc.a
				endif
			endif
		else
			export CA_LIB = libconax_m32.a libupg_rs232_m32.a
		endif
		export FONT_LIB = $(DDK_DIR)/libfreetype_m32.a
	else
		export CA_LIB = libconax.a libupg_rs232.a
		export FONT_LIB = $(DDK_DIR)/libfreetype.a
	endif
else
	ifdef _BC_CA_ENABLE_
		ifdef _S3281_
			export CA_LIB = lib_bc_m32.a lib_bc_nsc_m32.a
			export FONT_LIB =
		else
			export CA_LIB = lib_bc.a libbc_nsc.a
			export FONT_LIB =
		endif
	else
            ifdef _BC_CA_STD_ENABLE_	
	          export CA_LIB = lib_bc_3281_std.a lib_bc_nsc_3281_std.a	
	          export FONT_LIB =
            else
		export CA_LIB = 
		export FONT_LIB =
	endif
endif
endif

ifdef DUAL_ENABLE
export ALL_LIBS = $(CIPLUSCC_LIB) $(OPENSSL_LIB) ${PVR_PLUS}.a ${DDKLIB}.a \
			liblog.a ${SMOD_LIB} ${LWIP_LIB} ${CA_LIB} ${FONT_LIB}
else
export ALL_LIBS = $(OPENSSL_LIB) ${PVR_PLUS}.a ${DDKLIB}.a libmpg2c.a \
			liblog.a ${SMOD_LIB} ${LWIP_LIB} ${CA_LIB} ${FONT_LIB}
endif			

ALL_TOOLS = LZMA.EXE ObjSize.exe binsert.exe bmerger.exe dumpmerge_7z.exe \
			fidmerger.exe fidmerger_ca.exe fmerge.exe gzip.exe module_dif.exe code_build.exe universal_key_encrypt.exe \
			lzox99.exe

BOOT_LIBS = libboot36f.a liblog.a libstandby36.a boot36.o boot36f.o boot36f_os.o \
			boot_see*.o libblsee*.a libboot3606os.a libslot36f.a libslot3602f.a \
			libslothd_ct1628.a libslothd_fd650.a libstandby36.a

ifdef _BOARD_DB_M3603_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3603_01V01
export CHIP_CFG_PATH = platform/chip/m36f
export CHIP_AVDCFG_PATH = platform/advanced_cfg/m36f_board
endif
ifdef _BOARD_DB_M3603_02V01_
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3603_02V01
export CHIP_CFG_PATH = platform/chip/m36f
export CHIP_AVDCFG_PATH = platform/advanced_cfg/m36f_board
endif
ifdef _BOARD_DB_M3281_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3281_01V01
export CHIP_CFG_PATH = platform/chip/m3281
export CHIP_AVDCFG_PATH = platform/advanced_cfg/m3281_board
endif
ifdef _BOARD_DEMO_M3281_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DEMO_M3281_01V01
export CHIP_CFG_PATH = platform/chip/m3281
export CHIP_AVDCFG_PATH = platform/advanced_cfg/m3281_board
endif
ifdef _BOARD_SB_M3281_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_SB_M3281_01V01
export CHIP_CFG_PATH = platform/chip/m3281
export CHIP_AVDCFG_PATH = platform/advanced_cfg/m3281_board
endif

# Following lines are the common description for all projects.
# Do NOT modify anything, unless you know what you are doing.

OBJS = ${ASMS:.S=.o} ${SRCS:.c=.o}
SMOD_ = ${SMOD:=_}
LMOD_ = ${LMOD:=_}
DMOD_ = ${DMOD:=_}
RMOD_ = ${RMOD:=_}
PMOD_ = ${PMOD:=_}
PPMOD_ = ${PPMOD:=_}
SMOD__ = ${SMOD:=__}
LMOD__ = ${LMOD:=__}
DMOD__ = ${DMOD:=__}
RMOD__ = ${RMOD:=__}
PMOD__ = ${PMOD:=__}
PPMOD__= ${PPMOD:=__}
BL_RMOD_= ${BL_RMOD:=_}
BL_RMOD__= ${BL_RMOD:=__}
all : ${MOD}.mk
	cp ${DDK_DIR}/${BOOT_MOD}.o ${LIB_DIR}/boot.o
	cp ${DDK_DIR}/lib7zip.a ${LIB_DIR}/
ifdef _OPENSSL_ENABLE
	cp ${DDK_DIR}/libopenssl.a ${LIB_DIR}/
endif
ifdef _CAS9_CA_ENABLE_
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libconax*.a ${LIB_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libupg_rs232*.a ${LIB_DIR}/
endif
ifdef _BC_CA_ENABLE_
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc*.a ${LIB_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc_nsc*.a ${LIB_DIR}/
endif
ifdef _BC_CA_STD_ENABLE_	
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc*.a ${LIB_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc_nsc*.a ${LIB_DIR}/
endif
	${MAKE} -f ${MOD}.mk ${OBJS}
	cp -f ${OBJS} ${LIBS} ${LIB_DIR}
	echo ${OBJS} ${LIBS} \\ > ${LIB_DIR}/${MOD}.lst
	rm -f ${LIB_DIR}/list.mod
	cd ${ROOT}/src; \
	  ${MAKE} ${DMOD}
ifndef _AUI_
	cd copper_common; \
	  ${MAKE} all
endif
	cd platform; \
	  ${MAKE} all
	cd platform/chip; \
	  ${MAKE} all
	cd ${CHIP_CFG_PATH}; \
	  ${MAKE} all
	cd ${CHIP_AVDCFG_PATH}; \
	  ${MAKE} all
ifdef _CAS9_VSC_RAP_ENABLE_
	cd vsc_rap; \
	  ${MAKE} all	
endif
	@echo Entering Board: ${BOARD_CFG_PATH}
	cd ${BOARD_CFG_PATH}; \
	 ${MAKE} all	
ifdef _MAC_TEST
	cd ethernetmac; \
	  ${MAKE} all
endif
	 
ifdef _CAS9_CA_ENABLE_
ifndef _BUILD_OTA_E_
	cd ${CA_AP_DIR}; \
  		${MAKE} all
endif
endif

ifdef _BC_CA_ENABLE_
	cd ${BC_AP_DIR}; \
  		${MAKE} all
endif

ifdef _BC_CA_STD_ENABLE_	
ifndef _BUILD_OTA_E_
	cd ${BC_AP_DIR}; \
  		${MAKE} all
endif
endif

	cp -f ${LSCR} ${LIB_DIR}/lscript.ld
	cd ${LIB_DIR}; \
	  echo include ../src/path.def > ${MOD}.lk; \
	  echo include ../src/compiler.def >> ${MOD}.lk; \
	  echo NEED = \\ >> ${MOD}.lk; \
	    echo cat \\ > cat.sh; \
	    cat list.mod >> cat.sh; \
	    echo ${MOD}.lst \\ >> cat.sh; \
	    echo \>\> ${MOD}.lk >> cat.sh; \
	    sh < cat.sh; \
	    rm -f cat.sh
	cat MakefileAS >> ${LIB_DIR}/${MOD}.lk
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk ${LINKER};
ifdef DUAL_ENABLE
	cp -f ${SEE_LSCR} ${LIB_DIR}
ifndef _BUILD_OTA_E_
ifndef _LINUX_COMPILER_ENVIRONMENT_
ifdef _CAS9_VSC_ENABLE_
	cp $(DDK_DIR)/${SEELIB}_vsc_enc.a ${CA_AP_DIR}/seelib_temp.a
	cd ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}; \
	./decrypt_see.bat
	cp ${CA_AP_DIR}/seelib_temp2.bin $(DDK_DIR)/${SEELIB}_vsc.a
	cp $(DDK_DIR)/${SEELIB}_vsc.a $(DDK_DIR)/${SEELIB}.a
	rm -f ${CA_AP_DIR}/seelib_temp2.bin ${CA_AP_DIR}/seelib_temp.a
endif
endif
endif
	cd ${LIB_DIR}; \
  	  ${MAKE} -f ${MOD}.lk ${SEE_LINKER}
endif	

${MOD}.mk : ${ASMS} ${SRCS}
	echo include ${ROOT}/src/path.def > $@
	echo include ${ROOT}/src/compiler.def >> $@
	cat MakefileAS >> $@
	${CC} ${CFLAGS} -M ${ASMS} ${SRCS} >> $@

clean :
	rm -f ${OBJS} ${MOD}.mk
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk cleanld; \
	  rm -f lscript.ld list.mod ${MOD}.lk; \
	  echo rm -f \\ > rm.sh; \
	  cat ${MOD}.lst >> rm.sh; \
	  sh < rm.sh; \
	  rm -f rm.sh ${MOD}.lst
ifndef _AUI_
	  cd copper_common; \
	  ${MAKE} clean
endif
	  cd platform; \
	   ${MAKE} clean
	  cd platform/chip; \
	   ${MAKE} clean
	  cd ${CHIP_CFG_PATH}; \
	   ${MAKE} clean
	  cd ${CHIP_AVDCFG_PATH}; \
	   ${MAKE} clean
ifdef _CAS9_VSC_RAP_ENABLE_
	cd vsc_rap; \
	  ${MAKE} clean	
endif
	  cd ${BOARD_CFG_PATH}; \
	  ${MAKE} clean
	  
ifdef _CAS9_CA_ENABLE_	  
	  cd ${CA_AP_DIR}; \
	  ${MAKE} clean
endif  

ifdef _BC_CA_ENABLE_
	cd ${BC_AP_DIR}; \
  		${MAKE} clean
endif

ifdef _BC_CA_STD_ENABLE_	  
	  cd ${BC_AP_DIR}; \
	  ${MAKE} clean
endif

ifdef _MAC_TEST
	cd ethernetmac; \
	  ${MAKE} clean
endif

new : clean
	cd ${ROOT}/src; \
	  ${MAKE} ${DMOD_}; \
	  ${MAKE} ${RMOD_}

rebuild: clean all

ifdef LOGISCOPE_CMD_LINE
# gather all project compile define
logiscope_def:=$(foreach item, $(DEFS), $(subst -,,$(item)))

# gather all SDK include path, except compiler's default include path which will add alone
logiscope_inc:=$(filter -I/cygdrive%,${CFLAGS})
logiscope_inc:=$(foreach item, ${logiscope_inc}, $(subst -I/cygdrive/,,${item}))
logiscope_inc:=$(foreach item, ${logiscope_inc}, $(firstword $(subst /, ,${item})):\\$(subst $(firstword $(subst /, ,${item}))/,,${item}))
logiscope_inc:=$(subst /,\\,${logiscope_inc})

logiscope:
	@echo -n  > ${ROOT}/src/logiscope.def
	@for k in $(logiscope_inc); \
		do echo I$$k>> ${ROOT}/src/logiscope.def;\
	done
#	# add compiler's default include path alone(position must after SDK's include path)
	@echo "IC:\Cygwin\mips-sde\lib\gcc\sde\3.4.4\include" >> ${ROOT}/src/logiscope.def
	@echo "IC:\Cygwin\mips-sde\sde\include" >> ${ROOT}/src/logiscope.def
	@echo "D__GNUC__=1" >> ${ROOT}/src/logiscope.def
	@echo "D__STDC__=1" >>${ROOT}/src/logiscope.def
#	# for log_cc can not reconize our config is little endian
	@echo "D__IEEE_LITTLE_ENDIAN=1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_DECA_REMOTE=1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_SND_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_VP_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LIB_SUBT_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LIB_CLOSE_CAPTION_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LIB_TTX_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_SDEC_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_ISDBTCC_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LIB_ISDBTCC_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_VBI_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_DECA_M36F_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_DECA_M33_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_SND_M36F_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_SND_M33_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_VP_M36F_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_VP_M33_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_SDEC_SW_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_VBI_M33_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_DMX_M36F_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_DSC_M36F_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_CRYPTO_M36F_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_TRNG_M36F_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_DSC_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_CRYPTO_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_HLD_DECV_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_DECV_M36_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LLD_DECV_AVC_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LIB_PE_ADV_VIDEO_ENGINE_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LIB_PE_MUSIC_ENGINE_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@echo "D_LIB_PE_IMAGE_ENGINE_REMOTE = 1" >>${ROOT}/src/logiscope.def
	@for k in $(logiscope_def); \
		do echo $$k=1 >>${ROOT}/src/logiscope.def; \
	done		
else
logiscope:
	@echo "Done!"
endif


sync: 
	cd ../${ROOT}/see; pwd
#	cp -f ../${ROOT}/see/inc/modules.h ${ROOT}/inc/
#	cp -f ../${ROOT}/see/src/see/m36f/compiler_cpu.def ./
	cp -f ../${ROOT}/see/ddk/${SEELIB}.a ${ROOT}/ddk;
	cp -f ../${ROOT}/see/ddk/${BOOT_SEE}.o ${ROOT}/ddk/;
#	cp -f ../${ROOT}/see/ddk/plugin/* ${ROOT}/ddk/plugin/
#*/

ddk:
ifdef _CAS9_CA_ENABLE_
#	for compile error
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libconax*.a ${DDK_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libupg_rs232*.a ${DDK_DIR}/
endif
ifdef _BC_CA_ENABLE_
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc*.a ${DDK_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc_nsc*.a ${DDK_DIR}/
ifdef _S3281_
	cp -rf ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/script_3281/. ${BASE_DIR}/prj/app/demo/combo/aui_demo/
else
	cp -rf ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/script/. ${BASE_DIR}/prj/app/demo/combo/aui_demo/
endif
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/tool/padding.exe ${BASE_DIR}/prj/app/demo/combo/aui_demo/padding.exe
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/tool/ftell.exe ${BASE_DIR}/prj/app/demo/combo/aui_demo/ftell.exe
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/tool/create_signature.exe ${BASE_DIR}/prj/app/demo/combo/aui_demo/create_signature.exe
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/tool/fmerge.exe ${BASE_DIR}/prj/app/demo/combo/aui_demo/fmerge.exe	
endif

ifdef _BC_CA_STD_ENABLE_	
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc*.a ${DDK_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${BC_AP_DIR}/lib_bc_nsc*.a ${DDK_DIR}/
endif

	cd ${DDK_DIR}; \
	cp ${ALL_LIBS} ${LIB_DIR}/ ;\
	rm -f ${LIB_DIR}/${DDKLIB}.mak
	
nim:
	rm -f ${LIB_DIR}/${DDKLIB}.mak
	rm -f ${LIB_DIR}/list.nmt
	cd ${ROOT}/src; \
	  ${MAKE} ${SMOD}
	  
	echo "#" > ${LIB_DIR}/${DDKLIB}.mak	
# ifdef _DVBS_ENABLE_
	 cd ${LIB_DIR}; \
	 echo NIM_S2_MOD_OBJ = \\ >> ${DDKLIB}.mak; \
	 cat ${NIM_S2_MOD}.lst >> ${DDKLIB}.mak; \
	 echo "#" >> ${LIB_DIR}/${DDKLIB}.mak
# endif
	  
# ifdef _DVBT_ENABLE_
	 cd ${LIB_DIR}; \
	 echo NIM_T_MOD_OBJ = \\ >> ${DDKLIB}.mak; \
	 cat ${NIM_T_MOD}.lst >> ${DDKLIB}.mak; \
	 echo "#" >> ${LIB_DIR}/${DDKLIB}.mak
# endif
	  
ifdef _S3281_
	 cd ${LIB_DIR}; \
	 echo NIM_S3281_C_MOD_OBJ = \\ >> ${DDKLIB}.mak; \
	 cat ${NIM_S3281_C_MOD}.lst >> ${DDKLIB}.mak; \
	 echo "#" >> ${LIB_DIR}/${DDKLIB}.mak

	 cd ${LIB_DIR}; \
	 echo NIM_S3281_S_MOD_OBJ = \\ >> ${DDKLIB}.mak; \
	 cat ${NIM_S3281_S_MOD}.lst >> ${DDKLIB}.mak; \
	 echo "#" >> ${LIB_DIR}/${DDKLIB}.mak
endif

	echo all: >> ${LIB_DIR}/${DDKLIB}.mak
ifndef _S3281_	
# ifdef _DVBS_ENABLE_
	echo "	${AR} -r ${NIM_S2_LIB} \$${NIM_S2_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
# endif	
# ifdef _DVBT_ENABLE_
	echo "	${AR} -r ${NIM_T_LIB} \$${NIM_T_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
# endif
else
	echo "	${AR} -r ${NIM_S3281_C_LIB} \$${NIM_S3281_C_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
	echo "	${AR} -r ${NIM_S3281_S_LIB} \$${NIM_S3281_S_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
endif

	cd ${LIB_DIR}; \
	  ${MAKE} -f ${DDKLIB}.mak
	  
ifndef _S3281_	  
# ifdef _DVBS_ENABLE_
	cp ${LIB_DIR}/${NIM_S2_LIB} ${DDK_DIR}
# endif	
# ifdef _DVBT_ENABLE_
	cp ${LIB_DIR}/${NIM_T_LIB} ${DDK_DIR}
# endif	
else
	cp ${LIB_DIR}/${NIM_S3281_C_LIB} ${DDK_DIR}
	cp ${LIB_DIR}/${NIM_S3281_S_LIB} ${DDK_DIR}
endif
	
sdk:
	rm -f ${LIB_DIR}/list.ddk
	rm -f ${LIB_DIR}/list.nmt
	
	${MAKE} nim
	cd ${ROOT}/src; \
	  ${MAKE} ${LMOD};\

	cd ${LIB_DIR}; \
	  echo DDK = \\ > ${DDKLIB}.mak; \
	  echo cat \\ > cat.sh; \
	  cat list.ddk >> cat.sh; \
	  echo \>\> ${DDKLIB}.mak >> cat.sh; \
	  sh < cat.sh; \
	  rm -f cat.sh
	echo "#" >> ${LIB_DIR}/${DDKLIB}.mak	
	echo all: >> ${LIB_DIR}/${DDKLIB}.mak
	echo "	${AR} -r ${DDKLIB}.a \$${DDK}" >> ${LIB_DIR}/${DDKLIB}.mak
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${DDKLIB}.mak

	cp ${LIB_DIR}/${DDKLIB}.a ${DDK_DIR}/sec
ifndef _S3281_
	cp ${LIB_DIR}/${LWIP_LIB} ${DDK_DIR}/
endif	
	cp -f ${DDK_DIR}/boot.o ${DDK_DIR}/${BOOT_MOD}.o
ifdef DUAL_ENABLE
	cp -f ${ROOT}/src/lld/sec/m36f/${SECLIB_MAIN}.a ${DDK_DIR}/sec/${SECLIB_MAIN}.a
	cd ${ROOT}/ddk/sec; \
		rm -f *.o; \
		${AR} -x ${SECLIB_MAIN}.a; \
		${AR} -r ${DDKLIB}.a *.o; \
		rm -f *.o
else
	cp -f ${ROOT}/src/lld/sec/m36f/libsec_single.a ${DDK_DIR}/sec/libsec_single.a
	cd ${ROOT}/ddk/sec; \
		rm -f *.o; \
		${AR} -x libsec_single.a; \
		${AR} -r ${DDKLIB}.a *.o; \
		rm -f *.o
endif
	cp -f ${DDK_DIR}/sec/${DDKLIB}.a ${DDK_DIR}/  
	cp -f ${DDK_DIR}/${DDKLIB}.a ${LIB_DIR}/${DDKLIB}.a
	rm -f ${LIB_DIR}/${DDKLIB}.mak
	rm -f ${DDK_DIR}/boot.o

pplus:
	cd ${ROOT}/src; \
	  ${MAKE} ${PPMOD}

plus:
	rm -f ${LIB_DIR}/list.ddk
	rm -f ${LIB_DIR}/list.nmt
	cd ${ROOT}/src; \
	  ${MAKE} ${PMOD}
	cd ${LIB_DIR}; \
	  echo NEED = \\ > ${PVR_PLUS}.mak; \
	  echo cat \\ > cat.sh; \
	  cat list.ddk >> cat.sh; \
	  echo \>\> ${PVR_PLUS}.mak >> cat.sh; \
	  sh < cat.sh; \
	  rm -f cat.sh
	echo "#" >> ${LIB_DIR}/${PVR_PLUS}.mak	
	 cd ${LIB_DIR}; \
	 echo NIM = \\ >> ${PVR_PLUS}.mak; \
	 echo cat \\ > cat.sh; \
	 cat list.nmt >> cat.sh; \
	 echo \>\> ${PVR_PLUS}.mak >> cat.sh; \
	 sh < cat.sh; \
	 rm -f cat.sh
	echo "#" >> ${LIB_DIR}/${PVR_PLUS}.mak
	echo all: >> ${LIB_DIR}/${PVR_PLUS}.mak
	echo "	${AR} -r ${PVR_PLUS}.a \$${NEED}" >> ${LIB_DIR}/${PVR_PLUS}.mak
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${PVR_PLUS}.mak
	cp ${LIB_DIR}/${PVR_PLUS}.a ${DDK_DIR}/
	rm -f ${LIB_DIR}/${PVR_PLUS}.mak

ddk_clean:

sdk_clean:
#	cd ${DDK_DIR}; \
#	  rm -f ${ALL_LIBS} *.o
	cd ${LIB_DIR}; \
	  rm -f *.a *.o
	cd ${ROOT}/src; \
	  ${MAKE} ${LMOD_} ${SMOD_};

plus_clean:
	cd ${DDK_DIR}; \
	rm -f ${PVR_PLUS}.a
	cd ${LIB_DIR}; \
	rm -f ${PVR_PLUS}.a
	cd ${ROOT}/src; \
	  ${MAKE} ${PMOD_};
 
pplus_clean:
ifdef _S3281_
	cd ${PLUGINDDK_DIR}/m32; \
		rm -f *.*;
	cd ${PLUGINEXT_DIR}/m32; \
		rm -f *.*;
else
	cd ${PLUGINDDK_DIR}; \
		rm -f *.*;
	cd ${PLUGINEXT_DIR}; \
		rm -f *.*;
endif		
	cd ${ROOT}/src; \
	  ${MAKE} ${PPMOD_};
	  
release :
	rm -f ${LIB_DIR}/list.sdk
	rm -f ${LIB_DIR}/list.mod
	cd ${ROOT}/src; \
	  ${MAKE} ${RMOD}
	cd ${LIB_DIR}; \
	  echo NEED = \\ > ${RELLIB}.mak; \
	  echo cat \\ > cat.sh; \
	  cat list.mod >> cat.sh; \
	  echo \>\> ${RELLIB}.mak >> cat.sh; \
	  sh < cat.sh; \
	  rm -f cat.sh
	echo "#" >> ${LIB_DIR}/${RELLIB}.mak
	echo all: >> ${LIB_DIR}/${RELLIB}.mak
	echo "	${AR} -r ${RELLIB}.a \$${NEED}" >> ${LIB_DIR}/${RELLIB}.mak
#	sed -e "s/boot.o//" -e "s/glue.o//" ${LIB_DIR}/${RELLIB}.mak > ${LIB_DIR}/${RELLIB}.tmp
#	mv ${LIB_DIR}/${RELLIB}.tmp ${LIB_DIR}/${RELLIB}.mak
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${RELLIB}.mak
#	cp ${LIB_DIR}/${RELLIB}.a ${LIB_DIR}/boot.o \
#	  ${LIB_DIR}/glue.o ${RELPROJ}/lib
	rm -f ${LIB_DIR}/${RELLIB}.mak

compress :
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk compress

generate :
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk generate

compress_7z :
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk compress_7z

generate_7z :
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk generate_7z


label :
	./updatelabel.bat $(APPLABEL) > label_log.txt

label_core :
	./updatelabel.bat $(LIBCORELABEL) > label_log.txt

label_sec :
	./updatelabel_sec.bat Security_Module_`date +%Y%m%d` > label_log.txt

# End of common description.

# Construct of sub-modules

# Deconstruct of sub-modules

DDK_PRJ_DIR=prj/app/demo/combo/aui_demo
DDK_REL_DIR=${BASE_DIR}/../ddk_release
CAS9_REL_DIR=${BASE_DIR}/../cas9_release_combo
CAS9_VSC_REL_DIR=${BASE_DIR}/../cas9_vsc_release_combo
CAS7_REL_DIR=${BASE_DIR}/../cas7_release_combo
BC_REL_DIR=${BASE_DIR}/../bc_release_combo
BC_STD_REL_DIR=${BASE_DIR}/../bc_std_release_combo
FTA_REL_DIR=${BASE_DIR}/../fta_release_combo
CIPLUS_REL_DIR=${BASE_DIR}/../ciplus_release_combo
PLUGIN_REL_DIR=${BASE_DIR}/../plugin_combo
BL_REL_DIR=${BASE_DIR}/../bootloader_release_m32

sdk_root:
	rm -rf ${DDK_REL_DIR}
	mkdir ${DDK_REL_DIR}

sdk_rel:
	${CC} ${CFLAGS} -M ${ASMS} ${SRCS} > dep.txt
	${DDK_DIR}/genlist dep.txt "${BASE_DIR}" "${DDK_REL_DIR}" "${DDK_REL_DIR}" "${DDK_REL_DIR}" 1>file.txt 2>dir.txt
	sh dir.txt
	sh file.txt
	rm -f dep.txt
	rm -f dir.txt
	rm -f file.txt
	mkdir -p ${DDK_REL_DIR}/obj
	mkdir -p ${DDK_REL_DIR}/ddk
	mkdir -p ${DDK_REL_DIR}/ddk/plugin
	mkdir -p ${DDK_REL_DIR}/ddk/plugin_ext
	mkdir -p ${DDK_REL_DIR}/sdk
	mkdir -p ${DDK_REL_DIR}/ddk/blsdk
	mkdir -p ${DDK_REL_DIR}/${DDK_PRJ_DIR}/rsc
	mkdir -p ${DDK_REL_DIR}/${DDK_PRJ_DIR}/loader3_3606
	mkdir -p ${DDK_REL_DIR}/src/app
	mkdir -p ${DDK_REL_DIR}/prj/tools
ifdef _WIFI_ENABLE_
	mkdir -p ${DDK_REL_DIR}/ddk/wifi
	cp ${DDK_DIR}/wifi/lib_rt5370.a ${DDK_REL_DIR}/ddk/wifi/
endif

	cd ${DDK_DIR}; \
	cp ${ALL_LIBS} ${DDK_REL_DIR}/ddk/ ;\
	cp ${DDK_DIR}/libHDMI.a ${DDK_REL_DIR}/ddk/ ;\
	cp lib7zip.a ${DDK_REL_DIR}/ddk/ ;\
	cp libmlzo.a ${DDK_REL_DIR}/ddk/ ;\
#	cp ${DDK_DIR}/boot_hd.o ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/boot_see.o ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/boot_v40b.o ${DDK_REL_DIR}/ddk/
	
	cp ${DDK_DIR}/libsee.a ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/libmpg2c.a ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/libmpg6c.a ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/plugin/lib_ogg.o ${DDK_REL_DIR}/ddk/plugin/
	cp 	${DDK_DIR}/libnim_t.a ${DDK_REL_DIR}/ddk/libnim_t.a

	cd ${DDK_DIR}; \
	cd blsdk ;\
	cp -f ${BOOT_LIBS} ${DDK_REL_DIR}/ddk/blsdk/
	
	cd ${BASE_DIR}/prj/tools; \
	cp ${ALL_TOOLS} ${DDK_REL_DIR}/prj/tools ;\

	cp -r loader3_3602 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/ ;echo
	cp -r loader3_3606 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/ ;echo
	cp -r loader3_3606S ${DDK_REL_DIR}/${DDK_PRJ_DIR}/ ;echo
	cp -r ./rsc 	${DDK_REL_DIR}/${DDK_PRJ_DIR}
	cp -f ${BASE_DIR}/ddk/genlist.exe ${DDK_REL_DIR}/ddk/genlist.exe
	cp -f ${BASE_DIR}/ddk/mod_makefile.exe ${DDK_REL_DIR}/ddk/mod_makefile.exe
	cp -f ${BASE_DIR}/src/path.def ${DDK_REL_DIR}/src/
	cp -f ${BASE_DIR}/src/makefile ${DDK_REL_DIR}/src/
	cp -f ${BASE_DIR}/src/compiler.def ${DDK_REL_DIR}/src/
	cp -f ./tve_hd_setting_half_mode_M3603.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ldscript.ld ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./see_ldscript.ld ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./see_ldscript_M3383_sabbat.ld ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./compiler_cpu.def ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./sys_config_3602.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./*.m2v ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./bloader3.abs ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./bloader3_*.abs ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./blocks_script_7z_*.txt ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ota_parameter.bin ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./compiler_3602.def ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./factory_data_*.bin ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./getpath.sh	 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./build_ota*.sh	 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./how_to_compile.txt	 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./empty_hdcp.key ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ciplus_key_empty.bin ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_full_mode.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_half_mode.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_half_mode_M3603.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_parental.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/		
	cp -f ./*.ddf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -rf ./platform/* ${DDK_REL_DIR}/${DDK_PRJ_DIR}/platform
	cd ${ROOT}/src; \
	  ${MAKE} ${DMOD__}; \
	  ${MAKE} ${RMOD__};\
	  ${MAKE} ${BL_RMOD__}
ifndef _AUI_
	cd copper_common; \
	  ${MAKE} ddk_rel
endif

sdk_rel_m32:
	${CC} ${CFLAGS} -M ${ASMS} ${SRCS} > dep.txt
	${DDK_DIR}/genlist dep.txt "${BASE_DIR}" "${DDK_REL_DIR}" "${DDK_REL_DIR}" "${DDK_REL_DIR}" 1>file.txt 2>dir.txt
	sh dir.txt
	sh file.txt
	rm -f dep.txt
	rm -f dir.txt
	rm -f file.txt
	mkdir -p ${DDK_REL_DIR}/obj
	mkdir -p ${DDK_REL_DIR}/ddk
	mkdir -p ${DDK_REL_DIR}/ddk/plugin/m32
	mkdir -p ${DDK_REL_DIR}/ddk/plugin_ext/m32
	mkdir -p ${DDK_REL_DIR}/sdk
	mkdir -p ${DDK_REL_DIR}/supplement
	mkdir -p ${DDK_REL_DIR}/ddk/blsdk
	mkdir -p ${DDK_REL_DIR}/${DDK_PRJ_DIR}/rsc
	mkdir -p ${DDK_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	mkdir -p ${DDK_REL_DIR}/src/app
	mkdir -p ${DDK_REL_DIR}/prj/tools

	mkdir -p ${DDK_REL_DIR}/inc
	mkdir -p ${DDK_REL_DIR}/inc/api
	mkdir -p ${DDK_REL_DIR}/inc/api/libtsi	
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${DDK_REL_DIR}/inc/api/libtsi/
	cp -r ${BASE_DIR}/inc/api/libge ${DDK_REL_DIR}/inc/api/

	cd ${DDK_DIR}; \
	cp ${ALL_LIBS} ${DDK_REL_DIR}/ddk/ ;\
	cp lib7zip.a ${DDK_REL_DIR}/ddk/ ;\
	cp libmlzo.a ${DDK_REL_DIR}/ddk/ ;\
	cp ${DDK_DIR}/boot_see_m32.o ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/boot_v40b_m32.o ${DDK_REL_DIR}/ddk/
	
	cp ${DDK_DIR}/libsee_m32*.a ${DDK_REL_DIR}/ddk/
	cp -f ${DDK_DIR}/libcore_v40b_m32*.a ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/libmpg2c_m32.a ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/plugin/m32/lib_ogg.o ${DDK_REL_DIR}/ddk/plugin/m32
	rm -f ${DDK_REL_DIR}/ddk/libconax_m32.a
	rm -f ${DDK_REL_DIR}/ddk/libupg_rs232_m32.a
	rm -f ${DDK_REL_DIR}/ddk/libfreetype_m32.a
	rm -f ${DDK_REL_DIR}/ddk/lib_bc_3281_std.a
	rm -f ${DDK_REL_DIR}/ddk/lib_bc_nsc_3281_std.a
	rm -f ${DDK_REL_DIR}/ddk/lib_bc3281_as.a
	rm -f ${DDK_REL_DIR}/ddk/lib_bc_nsc_3281_as.a

#	cd ${DDK_DIR}; \
#	cd blsdk ;\
#	cp -f ${BOOT_LIBS} ${DDK_REL_DIR}/ddk/blsdk/
	
	cd ${BASE_DIR}/prj/tools; \
	cp ${ALL_TOOLS} ${DDK_REL_DIR}/prj/tools ;\

	cp -r ./rsc 	${DDK_REL_DIR}/${DDK_PRJ_DIR}
	cp -f ${DDK_DIR}/blsdk/boot_encbl_m32.o ${DDK_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/boot_see_m32*.o ${DDK_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/liblog.a ${DDK_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libboot_encbl_m32.a ${DDK_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libstandby36_m32.a ${DDK_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libblsee_m32*.a ${DDK_REL_DIR}/ddk/blsdk
	mkdir -p ${DDK_REL_DIR}/inc/hld/pdd
	cp -f ${BASE_DIR}/inc/hld/pdd/* ${DDK_REL_DIR}/inc/hld/pdd/
	mkdir -p ${DDK_REL_DIR}/src/lld/nim/dvbc
	cp -rf ${BASE_DIR}/src/lld/nim/dvbc/tun_mxl603 ${DDK_REL_DIR}/src/lld/nim/dvbc/
	mkdir -p ${DDK_REL_DIR}/src/lld/nim/dvbs
	mkdir -p ${DDK_REL_DIR}/src/lib/libapplet/libpub/as_dvbs
	cp -rf ${BASE_DIR}/src/lld/nim/dvbs/* ${DDK_REL_DIR}/src/lld/nim/dvbs/
	rm -rf ${DDK_REL_DIR}/src/lld/nim/dvbs/S3281	
	cp -f ${BASE_DIR}/src/lib/libapplet/libpub/as_dvbs/* ${DDK_REL_DIR}/src/lib/libapplet/libpub/as_dvbs/
	mkdir -p ${DDK_REL_DIR}/src/lib/libapplet/libbootupg3
	cp -f ${BASE_DIR}/src/lib/libapplet/libbootupg3/* ${DDK_REL_DIR}/src/lib/libapplet/libbootupg3/
	mkdir -p ${DDK_REL_DIR}/src/lib/libcommunicate/libdiseqc
	cp -rf ${BASE_DIR}/src/lib/libcommunicate/libdiseqc/* ${DDK_REL_DIR}/src/lib/libcommunicate/libdiseqc/
	rm -rf ${DDK_REL_DIR}/src/lib/libcommunicate/libdiseqc/libdiseqc_ext
	mkdir -p ${DDK_REL_DIR}/src/boot/slot/slot_3602f
	cp -f ${BASE_DIR}/src/boot/slot/slot_3602f/* ${DDK_REL_DIR}/src/boot/slot/slot_3602f/
	mkdir -p ${DDK_REL_DIR}/src/boot/slot/slot36f
	cp -f ${BASE_DIR}/src/boot/slot/slot36f/* ${DDK_REL_DIR}/src/boot/slot/slot36f/
	cp -f ${BASE_DIR}/ddk/libnim_s3281*.a ${DDK_REL_DIR}/ddk/
	cp -f ${BASE_DIR}/ddk/genlist.exe ${DDK_REL_DIR}/ddk/genlist.exe
	cp -f ${BASE_DIR}/ddk/mod_makefile.exe ${DDK_REL_DIR}/ddk/mod_makefile.exe
	cp -f ${BASE_DIR}/src/path.def ${DDK_REL_DIR}/src/
	cp -f ${BASE_DIR}/src/makefile ${DDK_REL_DIR}/src/
	cp -f ${BASE_DIR}/src/compiler.def ${DDK_REL_DIR}/src/
	cp -f ./tve_hd_setting_half_mode_M3603.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ldscript.ld ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./see_ldscript_M3281*.ld ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./compiler_3281.def ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./sys_config_3281.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./*.m2v ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./bloader3_3281*.abs ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./blocks_script_7z_*.txt ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ota_parameter.bin ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./factory_data_*.bin ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./getpath.sh	 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./build_ota*.sh	 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./universal_key_encrypt.sh ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./how_to_compile_dual_cpu_3281.txt ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./retrieve_bootloader_m32.sh ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./empty_hdcp.key ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_full_mode.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_half_mode.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_half_mode_M3603.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_parental*.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_antenna*.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_motor*.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_unicable_setting.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_sat*.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_tp*.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./satcodx.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./satcodx.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_ascan_edit.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./eromclient_*.abs ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ota_link.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./qt_build_m32_bin.sh ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./*.ddf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -rf ./platform/* ${DDK_REL_DIR}/${DDK_PRJ_DIR}/platform
	rm -rf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/conax_ap
	#rm -rf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	rm -rf ${DDK_REL_DIR}/inc/api/libcas	
	rm -rf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/bc_ap_std
	rm -rf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/bc_ap
	#rm -rf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/fta_ap
	cd ${ROOT}/src; \
	  ${MAKE} ${DMOD__}; \
	  ${MAKE} ${RMOD__};
#	  ${MAKE} ${BL_RMOD__}
ifndef _AUI_
	cd copper_common; \
	  ${MAKE} ddk_rel
endif
	cp ${DDK_REL_DIR}/ddk/libsee_m32.a ${DDK_REL_DIR}/ddk/libsee_m32_vsc.a 
	cp ${DDK_REL_DIR}/ddk/libsee_m32_32M.a ${DDK_REL_DIR}/ddk/libsee_m32_32M_vsc.a
	rm -f ${DDK_REL_DIR}/ddk/libsee_m32*_enc.a
	rm -rf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/conax_ap
	  
	  
cas9_rel:
	mkdir -p ${CAS9_REL_DIR}/ddk
	mkdir -p ${CAS9_REL_DIR}/ddk/blsdk
	mkdir -p ${CAS9_REL_DIR}/inc
	mkdir -p ${CAS9_REL_DIR}/inc/api
	mkdir -p ${CAS9_REL_DIR}/inc/api/libtsi
	mkdir -p ${CAS9_REL_DIR}/inc/api/libcas
	mkdir -p ${CAS9_REL_DIR}/inc/api/libcas/cas9
	mkdir -p ${CAS9_REL_DIR}/${DDK_PRJ_DIR}
	
#	cp -f ${DDK_DIR}/libblsee.a ${CAS9_REL_DIR}/ddk/
	cp -f ${DDK_DIR}/blsdk/boot36f_os.o ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/boot_see*.o ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libboot36os.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libboot36fos.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslot36f.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslot3602f.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslothd_ct1628.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslothd_fd650.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libblsee*.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${CAS9_REL_DIR}/inc/api/libtsi/
	cp -r ${BASE_DIR}/inc/freetype2 ${CAS9_REL_DIR}/inc/
	cp -f ${BASE_DIR}/inc/api/libcas/cas9/cas9.h ${CAS9_REL_DIR}/inc/api/libcas/cas9/
	cp -f ${BASE_DIR}/inc/api/libcas/conax_mmi.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas_ca_info.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -r ${BASE_DIR}/inc/api/libge ${CAS9_REL_DIR}/inc/api/
	cp -f ${BASE_DIR}/ddk/libfreetype.a ${CAS9_REL_DIR}/ddk/
	cp -r conax_ap ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/
	cp -r loader3_hw_security ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/
	#remove keys in release DIR in order to force customer to modify it
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/decrypt_key*.bin
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/sys_sw_pair.key
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/orig_bl_key.bin

cas9_vsc_rel_m32:
#	mkdir -p ${CAS9_VSC_REL_DIR}/src/vsc
	mkdir -p ${CAS9_VSC_REL_DIR}/obj
	mkdir -p ${CAS9_VSC_REL_DIR}/inc
	mkdir -p ${CAS9_VSC_REL_DIR}/inc/api
	mkdir -p ${CAS9_VSC_REL_DIR}/inc/bus
	mkdir -p ${CAS9_VSC_REL_DIR}/inc/hld
	mkdir -p ${CAS9_VSC_REL_DIR}/${DDK_PRJ_DIR}
	
#	cp -rf ${BASE_DIR}/src/vsc ${CAS9_VSC_REL_DIR}/src/
#	cp -rf ${BASE_DIR}/src/makefile ${CAS9_VSC_REL_DIR}/src/
	cp -rf ${BASE_DIR}/inc/vsc ${CAS9_VSC_REL_DIR}/inc/
	cp -rf ${BASE_DIR}/inc/hal ${CAS9_VSC_REL_DIR}/inc/
	cp -rf ${BASE_DIR}/inc/osal ${CAS9_VSC_REL_DIR}/inc/
	cp -rf ${BASE_DIR}/inc/hld/crypto ${CAS9_VSC_REL_DIR}/inc/hld/
	cp -rf ${BASE_DIR}/inc/hld/dsc ${CAS9_VSC_REL_DIR}/inc/hld/
	cp -rf ${BASE_DIR}/inc/hld/trng ${CAS9_VSC_REL_DIR}/inc/hld/
#	cp -rf ${BASE_DIR}/inc/hld/vsc ${CAS9_VSC_REL_DIR}/inc/hld/
	cp -f ${BASE_DIR}/inc/hld/hld_dev.h ${CAS9_VSC_REL_DIR}/inc/hld/
	cp -rf ${BASE_DIR}/inc/bus/otp ${CAS9_VSC_REL_DIR}/inc/bus/
	cp -rf ${BASE_DIR}/inc/api/libc ${CAS9_VSC_REL_DIR}/inc/api/
	cp -rf ${BASE_DIR}/inc/sys_define.h ${CAS9_VSC_REL_DIR}/inc/
	cp -rf ${BASE_DIR}/inc/basic_types.h ${CAS9_VSC_REL_DIR}/inc/
	cp -rf ${BASE_DIR}/inc/retcode.h ${CAS9_VSC_REL_DIR}/inc/
	cp -rf ${BASE_DIR}/inc/types.h ${CAS9_VSC_REL_DIR}/inc/	
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/vsc_rap ${CAS9_VSC_REL_DIR}/${DDK_PRJ_DIR}/
	rm -f ${CAS9_VSC_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/vsc_see_se*
	rm -f ${CAS9_VSC_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/see_test_pair.key
	rm -f ${CAS9_VSC_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libupg_rs232_burn_otp.a
	rm -f ${CAS9_VSC_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libconax_m32.a

cas9_rel_m32:
	mkdir -p ${CAS9_REL_DIR}/ddk
	mkdir -p ${CAS9_REL_DIR}/ddk/blsdk
	mkdir -p ${CAS9_REL_DIR}/inc
	mkdir -p ${CAS9_REL_DIR}/inc/api
	mkdir -p ${CAS9_REL_DIR}/inc/api/libtsi
	mkdir -p ${CAS9_REL_DIR}/inc/api/libcas
	mkdir -p ${CAS9_REL_DIR}/inc/api/libcas/cas9
	mkdir -p ${CAS9_REL_DIR}/${DDK_PRJ_DIR}
	
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${CAS9_REL_DIR}/inc/api/libtsi/
	cp -r ${BASE_DIR}/inc/freetype2 ${CAS9_REL_DIR}/inc/
	cp -f ${BASE_DIR}/inc/api/libcas/cas9/cas9.h ${CAS9_REL_DIR}/inc/api/libcas/cas9/
	cp -f ${BASE_DIR}/inc/api/libcas/conax_mmi.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas_ca_info.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -r ${BASE_DIR}/inc/api/libge ${CAS9_REL_DIR}/inc/api/
	cp -f ${BASE_DIR}/ddk/libfreetype_m32.a ${CAS9_REL_DIR}/ddk/
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/conax_ap ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/loader3_encbl ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libconax.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libconax_m32_scu.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libconax_m32_vsc.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libupg_rs232_burn_otp.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libupg_rs232_m32_vsc.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libupg_rs232.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/app*
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/M3603*
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/product*
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/otaloader_m3603*
	#remove keys in release DIR in order to force customer to modify it
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/decrypt_key.bin
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/sys_sw_pair.key
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/orig_bl_key.bin	
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/vsc_see_se*
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/decrypt_key_see.bin
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/see_test_pair.key


bc_std_rel_m32:
	mkdir -p ${BC_STD_REL_DIR}/ddk
	mkdir -p ${BC_STD_REL_DIR}/ddk/blsdk
	mkdir -p ${BC_STD_REL_DIR}/inc
	mkdir -p ${BC_STD_REL_DIR}/inc/api
	mkdir -p ${BC_STD_REL_DIR}/inc/api/libtsi
	mkdir -p ${BC_STD_REL_DIR}/inc/api/libcas
	mkdir -p ${BC_STD_REL_DIR}/inc/api/libcas/bc_std
	mkdir -p ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}
	
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${BC_STD_REL_DIR}/inc/api/libtsi/
	cp -f ${BASE_DIR}/inc/api/libtsi/si_monitor.h ${BC_STD_REL_DIR}/inc/api/libtsi/
	cp -f ${BASE_DIR}/inc/api/libcas/bc_std/bc_consts.h ${BC_STD_REL_DIR}/inc/api/libcas/bc_std/
	cp -f ${BASE_DIR}/inc/api/libcas/bc_std/bc_main.h ${BC_STD_REL_DIR}/inc/api/libcas/bc_std/
	cp -f ${BASE_DIR}/inc/api/libcas/bc_std/bc_types.h ${BC_STD_REL_DIR}/inc/api/libcas/bc_std/
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/bc_ap_std ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/bc_ap_std
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/loader3_encbl ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/bc_ap_std/lib_bc_*
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/bc_ap_std/app*
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/bc_ap_std/product*
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/bc_ap_std/otaloader_m3603_*

	cp -f ${BASE_DIR}/${DDK_PRJ_DIR}/compiler_3281.def ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/
	#cp -f ${BASE_DIR}/${DDK_PRJ_DIR}/loader3_encbl/sys_config_3281.h ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	sed -i 's/_CAS9_CA_ENABLE_ = 1/#_CAS9_CA_ENABLE_ = 1/' ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/compiler_3281.def
	sed -i 's/#_BC_CA_STD_ENABLE_ = 1/_BC_CA_STD_ENABLE_ = 1/' ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/compiler_3281.def
	sed -i 's/_USE_32M_MEM_ = 1/#_USE_32M_MEM_ = 1/' ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/compiler_3281.def
	sed -i 's/\/\/#define BC_CA_STD_ENABLE/#define BC_CA_STD_ENABLE/' ${BC_STD_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl/sys_config_3281.h
		
bc_rel:
	mkdir -p ${BC_REL_DIR}/ddk
	mkdir -p ${BC_REL_DIR}/ddk/blsdk
	mkdir -p ${BC_REL_DIR}/inc
	mkdir -p ${BC_REL_DIR}/inc/api
	mkdir -p ${BC_REL_DIR}/inc/api/libtsi
	mkdir -p ${BC_REL_DIR}/inc/api/libcas
	mkdir -p ${BC_REL_DIR}/inc/api/libcas/bc
	mkdir -p ${BC_REL_DIR}/inc/hld/trng
	mkdir -p ${BC_REL_DIR}/${DDK_PRJ_DIR}
	mkdir -p ${BC_REL_DIR}/src
	mkdir -p ${BC_REL_DIR}/src/boot
	mkdir -p ${BC_REL_DIR}/src/boot/slot
	
	cp -f ${DDK_DIR}/blsdk/boot36f_os.o ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/boot_see*.o ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libboot36os.a ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libboot36fos.a ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslot36f.a ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslot3602f.a ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslothd_ct1628.a ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libslothd_fd650.a ${BC_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libblsee*.a ${BC_REL_DIR}/ddk/blsdk
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${BC_REL_DIR}/inc/api/libtsi/
	cp -f ${BASE_DIR}/inc/api/libtsi/si_monitor.h ${BC_REL_DIR}/inc/api/libtsi/
	cp -f ${BASE_DIR}/inc/api/libcas/bc/bc_consts.h ${BC_REL_DIR}/inc/api/libcas/bc/
	cp -f ${BASE_DIR}/inc/api/libcas/bc/bc_main.h ${BC_REL_DIR}/inc/api/libcas/bc/
	cp -f ${BASE_DIR}/inc/api/libcas/bc/bc_types.h ${BC_REL_DIR}/inc/api/libcas/bc/
	cp -f ${BASE_DIR}/inc/hld/trng/trng.h ${BC_REL_DIR}/inc/hld/trng/
	cp -r bc_ap ${BC_REL_DIR}/${DDK_PRJ_DIR}/
	cp -r loader3_hw_security ${BC_REL_DIR}/${DDK_PRJ_DIR}/
	cp -r ${BASE_DIR}/src/boot/slot/slot36f ${BC_REL_DIR}/src/boot/slot/
	cp -r ${BC_REL_DIR}/${DDK_PRJ_DIR}/bc_ap/lib_bc_fake.a ${BC_REL_DIR}/${DDK_PRJ_DIR}/bc_ap/lib_bc.a
	rm -f ${BC_REL_DIR}/${DDK_PRJ_DIR}/bc_ap/lib_bc_fake.a		

bc_rel_m32:
	mkdir -p ${BC_REL_DIR}/ddk
	mkdir -p ${BC_REL_DIR}/ddk/blsdk
	mkdir -p ${BC_REL_DIR}/inc
	mkdir -p ${BC_REL_DIR}/inc/api
	mkdir -p ${BC_REL_DIR}/inc/api/libtsi
	mkdir -p ${BC_REL_DIR}/inc/api/libcas
	mkdir -p ${BC_REL_DIR}/inc/api/libcas/bc
	mkdir -p ${BC_REL_DIR}/inc/hld/trng
	mkdir -p ${BC_REL_DIR}/${DDK_PRJ_DIR}
	
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${BC_REL_DIR}/inc/api/libtsi/
	cp -f ${BASE_DIR}/inc/api/libtsi/si_monitor.h ${BC_REL_DIR}/inc/api/libtsi/
	cp -r ${BASE_DIR}/inc/freetype2 ${BC_REL_DIR}/inc/
	cp -f ${BASE_DIR}/inc/api/libcas/bc/bc_consts.h ${BC_REL_DIR}/inc/api/libcas/bc/
	cp -f ${BASE_DIR}/inc/api/libcas/bc/bc_main.h ${BC_REL_DIR}/inc/api/libcas/bc/
	cp -f ${BASE_DIR}/inc/api/libcas/bc/bc_types.h ${BC_REL_DIR}/inc/api/libcas/bc/
	cp -f ${BASE_DIR}/inc/hld/trng/trng.h ${BC_REL_DIR}/inc/hld/trng/
	cp -r ${BASE_DIR}/inc/api/libge ${BC_REL_DIR}/inc/api/
	cp -f ${BASE_DIR}/ddk/libfreetype_m32.a ${BC_REL_DIR}/ddk/
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/bc_ap ${BC_REL_DIR}/${DDK_PRJ_DIR}/bc_ap
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/loader3_encbl ${BC_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	cp -r ${BC_REL_DIR}/${DDK_PRJ_DIR}/bc_ap/lib_bc_fake.a ${BC_REL_DIR}/${DDK_PRJ_DIR}/bc_ap/lib_bc_m32.a
	rm -f ${BC_REL_DIR}/${DDK_PRJ_DIR}/bc_ap/lib_bc_fake.a	

	cp -f ${BASE_DIR}/${DDK_PRJ_DIR}/compiler_3281.def ${BC_REL_DIR}/${DDK_PRJ_DIR}/
	sed -i 's/_CAS9_CA_ENABLE_ = 1/#_CAS9_CA_ENABLE_ = 1/' ${BC_REL_DIR}/${DDK_PRJ_DIR}/compiler_3281.def
	sed -i 's/#_BC_CA_ENABLE_ = 1/_BC_CA_ENABLE_ = 1/' ${BC_REL_DIR}/${DDK_PRJ_DIR}/compiler_3281.def
	sed -i 's/_USE_32M_MEM_ = 1/#_USE_32M_MEM_ = 1/' ${BC_REL_DIR}/${DDK_PRJ_DIR}/compiler_3281.def
	sed -i 's/\/\/#define BC_CA_ENABLE/#define BC_CA_ENABLE/' ${BC_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl/sys_config_3281.h

fta_rel_m32:
	mkdir -p ${FTA_REL_DIR}/ddk
	mkdir -p ${FTA_REL_DIR}/ddk/blsdk
	mkdir -p ${FTA_REL_DIR}/inc
	mkdir -p ${FTA_REL_DIR}/inc/api
	mkdir -p ${FTA_REL_DIR}/inc/api/libtsi
	mkdir -p ${FTA_REL_DIR}/${DDK_PRJ_DIR}
	
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${FTA_REL_DIR}/inc/api/libtsi/
	cp -r ${BASE_DIR}/inc/api/libge ${FTA_REL_DIR}/inc/api/
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/fta_ap ${FTA_REL_DIR}/${DDK_PRJ_DIR}/fta_ap
	cp -r ${BASE_DIR}/${DDK_PRJ_DIR}/loader3_encbl ${FTA_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	rm -f ${FTA_REL_DIR}/${DDK_PRJ_DIR}/fta_ap/app*
	rm -f ${FTA_REL_DIR}/${DDK_PRJ_DIR}/fta_ap/M3603*
	rm -f ${FTA_REL_DIR}/${DDK_PRJ_DIR}/fta_ap/product*
	rm -f ${FTA_REL_DIR}/${DDK_PRJ_DIR}/fta_ap/otaloader_m3603_*
	
plugin_rel:
	mkdir -p ${PLUGIN_REL_DIR}/ddk
	mkdir -p ${PLUGIN_REL_DIR}/ddk/plugin
	mkdir -p ${PLUGIN_REL_DIR}/ddk/plugin_ext
	
	cp -f ${DDK_DIR}/plugin/*.* ${PLUGIN_REL_DIR}/ddk/plugin/
	cp -f ${DDK_DIR}/plugin_ext/*.* ${PLUGIN_REL_DIR}/ddk/plugin_ext/		
ifdef _WIFI_ENABLE_
	mkdir -p ${PLUGIN_REL_DIR}/ddk/wifi
	cp ${DDK_DIR}/wifi/*.* ${PLUGIN_REL_DIR}/ddk/wifi/
endif

plugin_rel_m32:
	mkdir -p ${PLUGIN_REL_DIR}/ddk
	mkdir -p ${PLUGIN_REL_DIR}/ddk/plugin/m32
	mkdir -p ${PLUGIN_REL_DIR}/ddk/plugin_ext/m32
	
	cp -f ${DDK_DIR}/plugin/m32/*.* ${PLUGIN_REL_DIR}/ddk/plugin/m32/
	cp -f ${DDK_DIR}/plugin_ext/m32/*.* ${PLUGIN_REL_DIR}/ddk/plugin_ext/m32/		
ifdef _WIFI_ENABLE_
	mkdir -p ${PLUGIN_REL_DIR}/ddk/wifi
	cp ${DDK_DIR}/wifi/*.* ${PLUGIN_REL_DIR}/ddk/wifi/
endif

see_enc:
	cp ${DDK_DIR}/${SEELIB}.a ${DDK_DIR}/${SEELIB}_vsc.a
	cp $(DDK_DIR)/${SEELIB}_vsc.a ${CA_AP_DIR}/seelib_temp.a
	cd ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}; \
	./encrypt_see.bat
	cp ${CA_AP_DIR}/seelib_temp2.bin $(DDK_DIR)/${SEELIB}_vsc_enc.a
	rm -f ${CA_AP_DIR}/seelib_temp2.bin ${CA_AP_DIR}/seelib_temp.a

bakcp:
ifdef _RD_DEBUG_
	cp -f ${DDK_DIR}/plugin/plugin_eac3.o.bak ${DDK_DIR}/plugin/plugin_eac3.o
	rm -f ${DDK_DIR}/plugin/plugin_eac3.o.bak
	rm -f ${DDK_DIR}/plugin/plugin_ac32c.o
endif

bl_rel_m32:
	rm -rf ../../../../../../bootloader_release_m32
	mkdir -p ../../../../../../bootloader_release_m32
	mkdir -p ${BL_REL_DIR}/ddk
	mkdir -p ${BL_REL_DIR}/ddk/blsdk
	mkdir -p ${BL_REL_DIR}/ddk/plugin/m32
	mkdir -p ${BL_REL_DIR}/ddk/plugin_ext/m32
	mkdir -p ${BL_REL_DIR}/inc
	mkdir -p ${BL_REL_DIR}/inc/api
	mkdir -p ${BL_REL_DIR}/inc/api/libtsi
	mkdir -p ${BL_REL_DIR}/obj
	mkdir -p ${BL_REL_DIR}/sdk
	mkdir -p ${BL_REL_DIR}/${DDK_PRJ_DIR}/loader3_encbl
	mkdir -p ${BL_REL_DIR}/src/app
	mkdir -p ${BL_REL_DIR}/prj/tools
	cp -f ${DDK_DIR}/blsdk/boot_encbl_m32.o ${BL_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/boot_see_m32*.o ${BL_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/liblog.a ${BL_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libboot_encbl_m32.a ${BL_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libstandby36_m32.a ${BL_REL_DIR}/ddk/blsdk
	cp -f ${DDK_DIR}/blsdk/libblsee_m32*.a ${BL_REL_DIR}/ddk/blsdk
	#cp -f ${DDK_DIR}/plugin/m32/lib_ogg.o ${BL_REL_DIR}/ddk/plugin/m32
	cp -f ${DDK_DIR}/boot_see_m32.o ${BL_REL_DIR}/ddk
	cp -f ${DDK_DIR}/boot_v40b_m32.o ${BL_REL_DIR}/ddk
	cp -f ${DDK_DIR}/lib7zip.a ${BL_REL_DIR}/ddk
	cp -f ${DDK_DIR}/libmlzo.a ${BL_REL_DIR}/ddk
	cp -rf ${BASE_DIR}/inc/api/libc ${BL_REL_DIR}/inc/api
	cp -rf ${BASE_DIR}/inc/api/libchunk ${BL_REL_DIR}/inc/api
	mkdir -p ${BL_REL_DIR}/inc/api/libfs2
	cp -f ${BASE_DIR}/inc/api/libfs2/stdio.h ${BL_REL_DIR}/inc/api/libfs2
	cp -f ${BASE_DIR}/inc/api/libfs2/types.h ${BL_REL_DIR}/inc/api/libfs2
	cp -f ${BASE_DIR}/inc/api/libfs2/unistd.h ${BL_REL_DIR}/inc/api/libfs2
	cp -rf ${BASE_DIR}/inc/api/libimagedec ${BL_REL_DIR}/inc/api
	cp -rf ${BASE_DIR}/inc/api/libloader ${BL_REL_DIR}/inc/api
	mkdir -p ${BL_REL_DIR}/inc/api/libmp
	cp -f ${BASE_DIR}/inc/api/libmp/pe.h ${BL_REL_DIR}/inc/api/libmp
	mkdir -p ${BL_REL_DIR}/inc/api/libpub
	cp -f ${BASE_DIR}/inc/api/libpub/lib_frontend.h ${BL_REL_DIR}/inc/api/libpub
	cp -rf ${BASE_DIR}/inc/api/librsa ${BL_REL_DIR}/inc/api
	mkdir -p ${BL_REL_DIR}/inc/api/libsi
	cp -f ${BASE_DIR}/inc/api/libsi/si_config.h ${BL_REL_DIR}/inc/api/libsi
	cp -rf ${BASE_DIR}/inc/api/libstbinfo ${BL_REL_DIR}/inc/api
	mkdir -p ${BL_REL_DIR}/inc/api/libtsi
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l.h ${BL_REL_DIR}/inc/api/libtsi
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${BL_REL_DIR}/inc/api/libtsi
	cp -f ${BASE_DIR}/inc/api/libtsi/p_search.h ${BL_REL_DIR}/inc/api/libtsi
	cp -f ${BASE_DIR}/inc/api/libtsi/psi_db.h ${BL_REL_DIR}/inc/api/libtsi
	cp -f ${BASE_DIR}/inc/api/libtsi/sec_pmt.h ${BL_REL_DIR}/inc/api/libtsi
	cp -f ${BASE_DIR}/inc/api/libtsi/sec_sdt.h ${BL_REL_DIR}/inc/api/libtsi
	cp -rf ${BASE_DIR}/inc/api/libzip ${BL_REL_DIR}/inc/api
	cp -rf ${BASE_DIR}/inc/asm ${BL_REL_DIR}/inc
	mkdir -p ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/aci ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/dma ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/dog ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/erom ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/flash ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/hdmi ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/i2c ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/otp ${BL_REL_DIR}/inc/bus
	cp -rf ${BASE_DIR}/inc/bus/sci ${BL_REL_DIR}/inc/bus
	mkdir -p ${BL_REL_DIR}/inc/hal
	cp -f ${BASE_DIR}/inc/hal/hal_gpio.h ${BL_REL_DIR}/inc/hal
	cp -f ${BASE_DIR}/inc/hal/hal_mem.h ${BL_REL_DIR}/inc/hal
	cp -f ${BASE_DIR}/inc/hal/machine.h ${BL_REL_DIR}/inc/hal
	cp -f ${BASE_DIR}/inc/hal/mips.h ${BL_REL_DIR}/inc/hal
	mkdir -p ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/crypto ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/deca ${BL_REL_DIR}/inc/hld
	mkdir -p ${BL_REL_DIR}/inc/hld/decv
	cp -f ${BASE_DIR}/inc/hld/decv/decv.h ${BL_REL_DIR}/inc/hld/decv
	cp -rf ${BASE_DIR}/inc/hld/dis ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/dsc ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/ge ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/pan ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/smc ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/snd ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/sto ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/hld/trng ${BL_REL_DIR}/inc/hld
	cp -f ${BASE_DIR}/inc/hld/hld_dev.h ${BL_REL_DIR}/inc/hld
	cp -rf ${BASE_DIR}/inc/os ${BL_REL_DIR}/inc
	cp -rf ${BASE_DIR}/inc/osal ${BL_REL_DIR}/inc
	cp -rf ${BASE_DIR}/inc/*.h ${BL_REL_DIR}/inc
	cp -rf ${BASE_DIR}/${DDK_PRJ_DIR}/loader3_encbl ${BL_REL_DIR}/${DDK_PRJ_DIR}/
	cd ${BASE_DIR}/prj/tools; \
	cp ${ALL_TOOLS} ${BL_REL_DIR}/prj/tools ;\

	cp -rf ${BASE_DIR}/src/app ${BL_REL_DIR}/src
	cp -rf ${BASE_DIR}/src/boot ${BL_REL_DIR}/src
	cp -rf ${BASE_DIR}/src/bus ${BL_REL_DIR}/src
	mkdir -p ${BL_REL_DIR}/src/hld
	cp -rf ${BASE_DIR}/src/hld/crypto ${BL_REL_DIR}/src/hld
	cp -rf ${BASE_DIR}/src/hld/dsc ${BL_REL_DIR}/src/hld
	cp -rf ${BASE_DIR}/src/hld/pan ${BL_REL_DIR}/src/hld
	cp -rf ${BASE_DIR}/src/hld/smc ${BL_REL_DIR}/src/hld
	cp -rf ${BASE_DIR}/src/hld/sto ${BL_REL_DIR}/src/hld
	cp -f ${BASE_DIR}/src/hld/*.c ${BL_REL_DIR}/src/hld
	cp -f ${BASE_DIR}/src/hld/Makefile ${BL_REL_DIR}/src/hld
	mkdir -p ${BL_REL_DIR}/src/lib/libapplet
	cp -rf ${BASE_DIR}/src/lib/libapplet/libbootupg3 ${BL_REL_DIR}/src/lib/libapplet
	mkdir -p ${BL_REL_DIR}/src/lib/libcommon
	cp -rf ${BASE_DIR}/src/lib/libcommon/libc ${BL_REL_DIR}/src/lib/libcommon
	cp -rf ${BASE_DIR}/src/lib/libcommon/libzip ${BL_REL_DIR}/src/lib/libcommon
	mkdir -p ${BL_REL_DIR}/src/lib/libstorage
	cp -rf ${BASE_DIR}/src/lib/libstorage/libchunk ${BL_REL_DIR}/src/lib/libstorage
	mkdir -p ${BL_REL_DIR}/src/lld
	#cp -rf ${BASE_DIR}/src/lld/nim ${BL_REL_DIR}/src/lld
	cp -rf ${BASE_DIR}/src/lld/pan ${BL_REL_DIR}/src/lld
	cp -rf ${BASE_DIR}/src/lld/smc ${BL_REL_DIR}/src/lld
	cp -rf ${BASE_DIR}/src/lld/sto ${BL_REL_DIR}/src/lld
	cp -rf ${BASE_DIR}/src/version ${BL_REL_DIR}/src
	cd ${BASE_DIR}/src; \
	cp -f compiler.def makefile path.def ${BL_REL_DIR}/src ;\
	