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

MAKEFILE = Makefile3821

CONAX_AP_DIR =
ifdef _CAS7_CA_ENABLE_
CONAX_AP_DIR = conax_ap7
endif
ifdef _CAS9_CA_ENABLE_
CA_AP_DIR=conax_ap
endif
ifdef _BC_CA_ENABLE_
CA_AP_DIR=bc_ap
endif

# Module Name
MOD = SABBAT_DEMO
BL_RMOD = LIB_BOOTUPG

# Link Script File
LSCR = ldscript.ld
SEE_LSCR = see_ldscript.ld

# List of source files
ifdef _AUI_TEST_
SRCS += aui_root.c hdcp_des.c
else
ASMS =
SRCS = control.c ctrl_task_init.c ctrl_util.c ap_dynamic_pid.c ctrl_pip.c ctrl_debug.c ctrl_network.c \
       ctrl_play_channel.c ctrl_cas_ap.c ap_ctrl_mheg5.c ap_ctrl_ci.c ctrl_key_proc.c \
       ap_ctrl_ttx.c ap_ctrl_dtg.c ap_ctrl_display.c ap_ctrl_time.c ctrl_msg_proc.c \
       ap_ctrl_dual_ci.c ap_ctrl_ci_plus.c ctrl_popup_msg.c ctrl_play_si_proc.c ctrl_preplay_channel.c \
       cec_link.c game_othello.c game_sudoku.c key.c lib_ash.c menus_root.c \
       mobile_input.c osd_rsc.c ota_ctrl.c power.c \
       pvr_ctrl_basic.c pvr_ctrl_cnx9_v6.c pvr_ctrl_parent_lock.c pvr_ctrl_ca.c pvr_ctrl_timer.c \
       pvr_ctrl_record_internal.c pvr_ctrl_record.c pvr_ctrl_play.c pvr_ctrl_tms.c pvr_ctrl_ts_route.c pvr_control.c\
       system_init.c root.c hdcp_des.c \
       sfu_test.c si_auto_update_tp.c time_zone_name.c win_ali_demo.c ui_debug.c \
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
       win_multiview.c win_multiview_ext.c win_multiviewset.c win_multiview_password.c\
       win_mpeg_player.c win_mpspectrum.c win_mpvolume.c win_mpzoom.c \
       win_mute.c win_net_local_seting.c win_net_upg.c \
       win_osd_set.c win_ota_set.c win_otaupg.c win_otaupg_private.c \
       win_password.c win_pause.c \
       win_playlist.c win_playlist_setup.c \
       win_prog_detail.c win_prog_input.c win_prog_name.c \
       win_pvr_ctrl_bar_basic.c win_pvr_ctrl_bar_key.c win_pvr_ctrl_bar_draw.c win_pvr_ctrl_bar.c \
       win_pvr_hdd_format.c win_pvr_hint.c \
       win_pvr_jumpstep.c Win_pvr_record_manager.c win_pvr_tms.c \
       Win_rs232upg.c win_search.c win_signal.c win_search_ext_function.c \
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
       win_welcom.c win_closedcaption.c win_calen_time.c win_com_popup_smsg.c  win_subtitle_setting.c  nit_info.c \
       win_mainmenu_submenu_data.c win_prog_name_extra.c beep_mp2.c
ifdef _DVBS_ENABLE_
SRCS += win_antenna_connect.c win_antenna_set_fixed.c win_unicable_setting.c \
       win_antenna_set_motor.c win_motor_limitsetup.c win_motor_setting.c \
       win_sat_edit.c win_sat_list.c win_satsearch_set.c \
       win_tp_edit.c win_ascan_edit.c win_tp_list.c win_tpsearch_set.c win_parental_old.c
else
SRCS += win_parental.c
endif

ifdef _DVBC_ENABLE_
SRCS += win_quickscan.c win_country_net.c win_countryband.c
ifdef _RD_DEBUG_
SRCS += win_dvbc_nim_debug.c
endif
endif
ifdef _DVBT_ENABLE_
SRCS +=  win_auto_scan.c win_chan_scan.c win_countryband_t.c win_lcn.c   prog_find.c  t2malloc.c \
		 win_automatic_upgrade_setting.c
endif
ifdef _ISDBT_ENABLE_
SRCS +=  win_auto_scan.c win_chan_scan.c win_countryband_t.c win_lcn.c win_cc.c
endif
ifdef _WIFI_ENABLE_
SRCS += win_wifi_manager.c win_wifi_ap_select.c win_wifi_input_password.c
endif
ifdef _USB3G_SUPPORT_
SRCS += win_usb3g_dongle.c win_usb3g_dongle_dial.c
export LIB_USB3G_MODULE = LIB_USB3G
endif
ifdef _MAC_TEST
	SRCS +=iol_test_mainmenu.c iol_test_mainmenu_submenu.c iol_test_submenu.c iol_test_submenu_system.c\
	win_mac_rx_config.c win_mac_rxtx_state.c win_mac_submenu.c win_mac_test.c win_mac_tx_config.c
endif

ifdef _IMG_2D_TO_3D_
SRCS += win_imagesetting.c
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
NIM_S3811_MOD =
NIM_S3811_LIB =
NIM_S3821_MOD =
NIM_S3821_LIB =

NIM_S2_MOD = LLD_NIM_S2
NIM_S2_LIB = libnim_s2.a
SMOD += ${NIM_S2_MOD}
ifdef _DVBS_ENABLE_
SMOD_LIB += ${NIM_S2_LIB}
endif
SMOD_LIB += libnand.a

NIM_T_MOD = LLD_NIM_M3101
NIM_T_LIB = libnim_t.a
SMOD += ${NIM_T_MOD}
ifdef _DVBT_ENABLE_
SMOD_LIB += ${NIM_T_LIB}
endif

NIM_S3281_C_MOD = LLD_NIM_S3281_C
NIM_S3281_C_LIB = libnim_s3281_c.a
SMOD += ${NIM_S3281_C_MOD}
ifdef _DVBC_ENABLE_
SMOD_LIB += ${NIM_S3281_C_LIB}
endif


# S3821 supports _DVBT2_ENABLE_
NIM_S3821_MOD = LLD_NIM_S3821
NIM_S3821_LIB = libnim_s3821.a
SMOD += ${NIM_S3821_MOD}
ifdef _DVBT2_ENABLE_
SMOD_LIB += ${NIM_S3821_LIB}
endif

# S3821 supports _ISDBT_ENABLE_
NIM_S3811_MOD = LLD_NIM_S3811
NIM_S3811_LIB = libnim_s3811.a
SMOD += ${NIM_S3821_MOD}
ifdef _ISDBT_ENABLE_
SMOD_LIB += ${NIM_S3821_LIB}
endif

SECLIB_MAIN = libmsec



# ==================================================


# List of dependent modules

# Libplus pvr+fs modules
PMOD = LIB_DOSFS LIB_VFS LIB_PVR3_ENG \
       VERSION_INFO_PLUS LIB_STDIO LIB_MP LIB_PVR3_CRYPTO

PPMOD = PLUGIN_ALL

ifdef _WIFI_ENABLE_
  export LMOD_BUS_USB_MODULE = BUS_USB_LINUX
  # BUS_USB_HC_M36F BUS_USB_USBD_M36F BUS_USB_DEV_STOR_M36F BUS_USB_HUB_M36F 
   export LIB_WIFI_MODULE = HLD_WIFI LIB_WIFI
else
  # export LMOD_BUS_USB_MODULE = BUS_USB_HC_M36F BUS_USB_USBD_M36F BUS_USB_DEV_STOR_M36F BUS_USB_HUB_M36F 
  export LIB_WIFI_MODULE = HLD_WIFI
  export LMOD_BUS_USB_MODULE = BUS_USB_LINUX
endif
ifndef _BUILD_OTA_E_
ifndef DUAL_ENABLE 
export CORE_MODULE = LLD_VP_M3921 LLD_TVE_M3921 LLD_SND_M36G LLD_DECA_M36F
else
export CORE_MODULE = LLD_VP_M3921 LLD_SND_M36G LLD_DECA_M36F
endif

else
ifndef DUAL_ENABLE
export CORE_MODULE = LLD_VP_M3921 LLD_TVE_M3921
else
export CORE_MODULE = LLD_VP_M3921 
endif
endif

ifdef _AVS_DECODER_ENABLE_
export VE_MODULE = LLD_DECV_M36 LLD_DECV_AVC LLD_DCEV_CFG LLD_DECV_AVS
else
export VE_MODULE = LLD_DECV_M36 LLD_DECV_AVC LLD_DCEV_CFG
endif

# Libcore library
ifndef _BUILD_OTA_E_
LMOD = 	ARCH_M63 OS_TDS3 LLD_PMU_M36 PDD_M38\
	${CORE_MODULE} \
        LLD_GE_M36F \
        HLD_GMA \
        LLD_GMA_M3921 \
        LLD_DMX_M36F \
        LLD_PAN_HWSCAN \
        LLD_CIC_M36 \
        LLD_STO_NAND \
        BUS_DMA_M36F \
        BUS_TSI_M36 \
        BUS_EROM_M36\
        BUS_TSG_M36 \
        BUS_DOG_M33 \
        $(LMOD_BUS_USB_MODULE) \
        BUS_OTP_M33 \
        BUS_DPLL \
        HLD_GE BUS_SD_M33 \
        VERSION_INFO \
        ${VE_MODULE} LLD_AVSYNC\
        LIB_LWIP140 LLD_NET_ETHTOE2 \
        BUS_PINMUX_M36 LLD_PAN_HWSCAN LIB_CIPLUS_CC \
        LIB_RSA LIB_NETCTL BUS_RTC_M36 LLD_SBM LLD_VSC

else


LMOD = 	ARCH_M63 OS_TDS3 LLD_PMU_M36 PDD_M38\
		${CORE_MODULE} \
         LLD_GE_M36F \
         HLD_GMA \
         LLD_GMA_M3921 \
         LLD_DMX_M36F \
         LLD_PAN_HWSCAN \
         LLD_STO_NAND \
         BUS_DMA_M36F \
         BUS_TSI_M36 \
         BUS_DOG_M33 \
         BUS_OTP_M33 \
         BUS_DPLL \
         HLD_GE \
         BUS_RTC_M36 \
         VERSION_INFO \
         LIB_RSA LLD_VSC
        
endif
# Release library
ifndef _BUILD_OTA_E_
RMOD = BUS_I2C_SCB BUS_I2C_GPIO BUS_SCI_UART \
       BUS_IDE_M36_HD\
       HLD_BASE LIB_C \
       HLD_PAN  \
       HLD_SCART  \
       HLD_STO  \
       HLD_VP \
       HLD_OSD \
       HLD_DECV \
       HLD_AVSYNC \
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
       HLD_SEC_BOOT \
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
       LIB_OTA \
       LIB_DBC HLD_SMC LLD_SMARTCARD \
       LIB_USBUPG LIB_VFS2 \
       LIB_PVR3_MGR LIB_TSG LIB_PVR3_API36 \
       LLD_NET_ENC28J60 LLD_NET_SMSC9220 LIB_CURL_S LIB_NETUPG LIB_XML2 \
       HLD_DSC HLD_CRYPTO HLD_PVR \
       LIB_LISTS \
       LIB_PUB_ALL LIB_PUB_AS_ENGINE \
       VERSION_INFO_APP LIB_PE \
       LIB_CEC \
       LIB_NIC \
       $(LIB_WIFI_MODULE) \
       LIB_PE_EXTERNAL_SUBTITLE LIB_GE_OSD $(LIB_USB3G_MODULE)
ifdef _MHEG5_V20_ENABLE_
ifdef _CIPLUS_CC_ENABLE_
# Need to add this module in CI Plus project
RMOD += UDI_MHEG_V20_CIPLUS_APP
endif
endif

else

RMOD = BUS_I2C_SCB BUS_I2C_GPIO BUS_SCI_UART \
       BUS_IDE_M36_HD\
       HLD_BASE LIB_C \
       HLD_PAN  \
       HLD_SCART  \
       HLD_STO  \
       HLD_VP \
       HLD_OSD \
       HLD_DECV \
       HLD_AVSYNC \
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
       LIB_OTA \
       LIB_DBC HLD_SMC \
       HLD_DSC HLD_CRYPTO HLD_PVR \
       LIB_PUB_ALL LIB_PUB_AS_ENGINE \
       VERSION_INFO_APP \
       LIB_CEC \
       LIB_GE_OSD
       
endif
ifdef _DVBS_ENABLE_
RMOD += LLD_NIM_S2_TUNER LLD_NIM_S2_3501 LIB_PUB_AS_S LIB_DISEQC
endif

ifdef _DVBT2_ENABLE_
RMOD += LLD_NIM_DVBT2
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
SRCS = control.c ctrl_util.c ctrl_play_channel.c osd_rsc.c power.c hdcp_des.c root.c key.c win_com_popup.c \
         win_otaupg.c win_ota_set.c ota_ctrl.c win_signal.c win_signalstatus.c  win_mute.c win_pause.c win_tvsys.c win_com.c \
         win_com_list.c ota_link.c ctrl_key_proc.c  ctrl_task_init.c  ctrl_msg_proc.c  ctrl_popup_msg.c \
         system_init.c ap_dynamic_pid.c ap_ctrl_display.c ap_ctrl_time.c win_com_popup_inner.c win_otaupg_private.c win_com_frontend.c

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

ifndef _BUILD_OTA_E_
SEELIB = libsee_m382x
else
SEELIB = libsee_m382x_ota
endif
BOOT_SEE = boot_see
ifdef _M36F_SINGLE_CPU
  ifndef _BUILD_OTA_E_
	export DDKLIB = ${LIBCORE_NAME_EXT}
  else
    export DDKLIB = libcore_v40e_m382x_single_ota
  endif
	export PVR_PLUS=${LIBPLUG_NAME_EXT}
	BOOT_MOD = boot_v40b_single
else
  ifndef _BUILD_OTA_E_
	export DDKLIB = libcore_v40e_m382x
  else
  	export DDKLIB = libcore_v40e_m382x_ota
  endif
	export PVR_PLUS=libplus_v40b
	BOOT_MOD = boot_v40b
endif

ifdef _BUILD_OTA_E_
LWIP_LIB =
else
LWIP_LIB = liblwip_hd.a
endif

ifdef _NESTOR_SUPPORT_
LWIP_LIB = liblwip_hd.a
endif

ifdef _MHEG5_V20_ENABLE_
export MHEG5_V2_LIB = $(DDK_DIR)/libmheg5app.a $(DDK_DIR)/libdsmcc.a $(DDK_DIR)/libengcore.a $(DDK_DIR)/libclass.a $(DDK_DIR)/libfont.a $(DDK_DIR)/libasn.a $(DDK_DIR)/libmheg5app.a $(DDK_DIR)/libpng.a $(DDK_DIR)/libzlib.a
endif

ifdef _OPENSSL_ENABLE
export OPENSSL_LIB = libopenssl.a
export CIPLUSCC_LIB = 
ifdef _CIPLUS_CC_ENABLE_
export CIPLUSCC_LIB = libciplus_cc.a
endif
else
export OPENSSL_LIB = 
export CIPLUSCC_LIB = 
endif

export CA_LIB = 
export FONT_LIB =
ifdef _CAS7_CA_ENABLE_
	export CA_LIB = libconax7.a
	export FONT_LIB =  $(DDK_DIR)/libfreetype.a
endif
ifdef _CAS9_CA_ENABLE_
	ifdef _CAS9_ALI_CA_LIB_
		export CA_LIB = libconax.a libupg_rs232.a
		export FONT_LIB = $(DDK_DIR)/libfreetype.a
	endif
endif

ifdef _BC_CA_ENABLE_
	export CA_LIB = lib_bc.a lib_bc_nsc.a
	export FONT_LIB =
endif

ifdef DUAL_ENABLE
export ALL_LIBS = $(CIPLUSCC_LIB) $(OPENSSL_LIB) ${PVR_PLUS}.a ${DDKLIB}.a ALi_pic_2dto3d.a\
			liblog.a ${SMOD_LIB} ${LWIP_LIB} ${CA_LIB} ${FONT_LIB}
else
export ALL_LIBS = $(OPENSSL_LIB) ${PVR_PLUS}.a ${DDKLIB}.a libmpg2c.a ALi_pic_2dto3d.a\
			liblog.a ${SMOD_LIB} ${LWIP_LIB} ${CA_LIB} ${FONT_LIB}
endif			

ALL_TOOLS = LZMA.EXE ObjSize.exe binsert.exe bmerger.exe dumpmerge_7z.exe \
			fidmerger.exe fidmerger_ca.exe fmerge.exe gzip.exe module_dif.exe code_build.exe \
			lzox99.exe bin2headfile.exe bin2txt.exe HEX2BIN.EXE bl_tool.exe

BOOT_LIBS_3503 = liblog.a boot35*.o libslot3602f.a libstandby36.a libboot_m35*.a

export CHIP_CFG_PATH = platform/chip/m3821
export CHIP_AVDCFG_PATH = platform/advanced_cfg/m3821_board




ifdef _BOARD_SB_M3821_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_SB_M3821_01V01
endif

ifdef _BOARD_DB_M3821_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3821_01V01
endif

ifdef _BOARD_DB_M3821_02V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3821_02V01
endif

ifdef _BOARD_SB_M3822_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_SB_M3822_01V01
endif

ifdef _BOARD_DB_M3822_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3822_01V01
endif

ifdef _BOARD_SB_M3823_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_SB_M3823_01V01
endif

ifdef _BOARD_DB_M3823_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3823_01V01
endif

ifdef _BOARD_DB_M3823_02V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3823_02V01
endif

ifdef _BOARD_M3701F_01V01_	  
export BOARD_CFG_PATH = platform/board_cfg/BOARD_DB_M3701F_01V01
endif

# Following lines are the common description for all projects.
# Do NOT modify anything, unless you know what you are doing.

OBJS = ${ASMS:.S=.o} ${SRCS:.c=.o}
SMOD_ = ${SMOD:=_}
LMOD_ = ${LMOD:=_}
RMOD_ = ${RMOD:=_}
PMOD_ = ${PMOD:=_}
PPMOD_ = ${PPMOD:=_}
SMOD__ = ${SMOD:=__}
LMOD__ = ${LMOD:=__}
RMOD__ = ${RMOD:=__}
PMOD__ = ${PMOD:=__}
PPMOD__= ${PPMOD:=__}
BL_RMOD_= ${BL_RMOD:=_}
BL_RMOD__= ${BL_RMOD:=__}

all : ${MOD}.mk
	cp ${DDK_DIR}/ALi_pic_2dto3d.a ${LIB_DIR}/ALi_pic_2dto3d.a
	cp ${DDK_DIR}/${BOOT_MOD}.o ${LIB_DIR}/boot.o
	cp ${DDK_DIR}/lib7zip.a ${LIB_DIR}/
ifdef _OPENSSL_ENABLE
	cp ${DDK_DIR}/libopenssl.a ${LIB_DIR}/
endif
ifdef _CAS7_CA_ENABLE_
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CONAX_AP_DIR}/libconax7.a ${LIB_DIR}/
endif
ifdef _CAS9_ALI_CA_LIB_
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libconax*.a ${LIB_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libupg_rs232*.a ${LIB_DIR}/
endif
ifdef _BC_CA_ENABLE_
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/lib_bc*.a ${LIB_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/lib_bc_nsc*.a ${LIB_DIR}/
	cp -rf ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/script_3823/. ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/tool/padding.exe ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/padding.exe
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/tool/ftell.exe ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/ftell.exe
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/tool/create_signature.exe ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/create_signature.exe
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/tool/fmerge.exe ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/fmerge.exe 
endif
	${MAKE} -f ${MOD}.mk ${OBJS}
	cp -f ${OBJS} ${LIBS} ${LIB_DIR}
	echo ${OBJS} ${LIBS} \\ > ${LIB_DIR}/${MOD}.lst
	rm -f ${LIB_DIR}/list.mod
	#cd copper_common;
	  #${MAKE} all
	cd platform; \
	  ${MAKE} all
	cd platform/chip; \
	  ${MAKE} all
	cd ${CHIP_CFG_PATH}; \
	  ${MAKE} all
	cd ${CHIP_AVDCFG_PATH}; \
	  ${MAKE} all
	
	@echo Entering Board: ${BOARD_CFG_PATH}
	cd ${BOARD_CFG_PATH}; \
	 ${MAKE} all	
ifdef _MAC_TEST
	cd ethernetmac; \
	  ${MAKE} all
endif 
ifdef _CAS7_CA_ENABLE_
ifndef _BUILD_OTA_E_
	cd ${CONAX_AP_DIR}; \
  		${MAKE} all
endif
endif
ifdef _CAS9_ALI_CA_LIB_
ifndef _BUILD_OTA_E_
	cd ${CA_AP_DIR}; \
  		${MAKE} all
endif
endif
ifdef _BC_CA_ENABLE_
ifndef _BUILD_OTA_E_
	cd ${CA_AP_DIR}; \
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
	cat ${MAKEFILE} | sed '/^include/d' >> ${LIB_DIR}/${MOD}.lk
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk ${LINKER};

ifdef DUAL_ENABLE
	cp -f ${SEE_LSCR} ${LIB_DIR}
	cd ${LIB_DIR}; \
  	  ${MAKE} -f ${MOD}.lk ${SEE_LINKER}
endif	

ifdef _LINUX_COMPILER_ENVIRONMENT_
	sh < post-rename-s382x.sh
endif

${MOD}.mk : ${ASMS} ${SRCS}
	echo include ${ROOT}/src/path.def > $@
	echo include ${ROOT}/src/compiler.def >> $@
	cat ${MAKEFILE} >> $@
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
	  #cd copper_common; \
	  #${MAKE} clean
	  cd platform; \
	   ${MAKE} clean
	  cd platform/chip; \
	   ${MAKE} clean
	  cd ${CHIP_CFG_PATH}; \
	   ${MAKE} clean
	  cd ${CHIP_AVDCFG_PATH}; \
	   ${MAKE} clean

	  cd ${BOARD_CFG_PATH}; \
	  ${MAKE} clean
ifdef _CAS7_CA_ENABLE_	  
	  cd ${CONAX_AP_DIR}; \
	  ${MAKE} clean
endif
ifdef _CAS9_ALI_CA_LIB_	  
	  cd ${CA_AP_DIR}; \
	  ${MAKE} clean
endif 
ifdef _BC_CA_ENABLE_	  
	  cd ${CA_AP_DIR}; \
	  ${MAKE} clean
endif
ifdef _MAC_TEST
	cd ethernetmac; \
	  ${MAKE} clean
endif

new : clean
	cd ${ROOT}/src; \
	  ${MAKE} ${RMOD_}

rebuild: clean all

sync: 
	cd ../${ROOT}/see; pwd
#	cp -f ../${ROOT}/see/inc/modules.h ${ROOT}/inc/
#	cp -f ../${ROOT}/see/src/see/m36f/compiler_cpu.def ./
	cp -f ../${ROOT}/see/ddk/${SEELIB}.a ${ROOT}/ddk;
	cp -f ../${ROOT}/see/ddk/${BOOT_SEE}.o ${ROOT}/ddk/;
#	cp -f ../${ROOT}/see/ddk/plugin/* ${ROOT}/ddk/plugin/
#*/

syncbl:
	@if [ -d ../${ROOT}/ALi_Boot ];then \
		ls ../${ROOT}/ALi_Boot/img/*.abs;\
		cp -vf ../${ROOT}/ALi_Boot/img/*.abs ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/ ;\
	else\
		if [ -d ../${ROOT}/aliboot ];then \
			ls ../${ROOT}/aliboot/img/*.abs;\
			cp -vf ../${ROOT}/aliboot/img/*.abs ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/ ;\
		else \
			echo "1 ";\
			echo "cannot find aliboot or ALi_Boot directory ";\
			echo "2 ";\
		fi \
	fi

ddk:
ifdef _CAS7_CA_ENABLE_
#	for compile error
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CONAX_AP_DIR}/libconax7.a ${DDK_DIR}/
endif
ifdef _CAS9_ALI_CA_LIB_
#	for compile error
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libconax*.a ${DDK_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/aui_demo/${CA_AP_DIR}/libupg_rs232*.a ${DDK_DIR}/
endif
ifdef _BC_CA_ENABLE_
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/lib_bc*.a ${DDK_DIR}/
	cp -f ${BASE_DIR}/prj/app/demo/combo/sabbat_dual/${CA_AP_DIR}/lib_bc_nsc*.a ${DDK_DIR}/
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

# ifdef _ISDBT_ENABLE_
	 cd ${LIB_DIR}; \
	 echo NIM_S3821_MOD_OBJ = \\ >> ${DDKLIB}.mak; \
	 cat ${NIM_S3821_MOD}.lst >> ${DDKLIB}.mak; \
	 echo "#" >> ${LIB_DIR}/${DDKLIB}.mak
# endif

# ifdef _DVBT2_ENABLE_
	 cd ${LIB_DIR}; \
	 echo NIM_S3821_MOD_OBJ = \\ >> ${DDKLIB}.mak; \
	 cat ${NIM_S3821_MOD}.lst >> ${DDKLIB}.mak; \
	 echo "#" >> ${LIB_DIR}/${DDKLIB}.mak
# endif
	  
#ifdef _DVBC_ENABLE_
	 cd ${LIB_DIR}; \
	 echo NIM_S3281_C_MOD_OBJ = \\ >> ${DDKLIB}.mak; \
	 cat ${NIM_S3281_C_MOD}.lst >> ${DDKLIB}.mak; \
	 echo "#" >> ${LIB_DIR}/${DDKLIB}.mak
#endif

	echo all: >> ${LIB_DIR}/${DDKLIB}.mak

# ifdef _DVBS_ENABLE_
	echo "	${AR} -r ${NIM_S2_LIB} \$${NIM_S2_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
# endif	
# ifdef _DVBT_ENABLE_
	echo "	${AR} -r ${NIM_T_LIB} \$${NIM_T_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
# endif

# ifdef _ISDBT_ENABLE_
	echo "	${AR} -r ${NIM_S3821_LIB} \$${NIM_S3821_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
# endif

# ifdef _DVBT2_ENABLE_
	echo "	${AR} -r ${NIM_S3821_LIB} \$${NIM_S3821_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
# endif

# ifdef _DVBC_ENABLE_
	echo "	${AR} -r ${NIM_S3281_C_LIB} \$${NIM_S3281_C_MOD_OBJ}" >> ${LIB_DIR}/${DDKLIB}.mak
# endif


	cd ${LIB_DIR}; \
	  ${MAKE} -f ${DDKLIB}.mak
	  
# ifdef _DVBS_ENABLE_
	cp ${LIB_DIR}/${NIM_S2_LIB} ${DDK_DIR}
# endif	
# ifdef _DVBT_ENABLE_
	cp ${LIB_DIR}/${NIM_T_LIB} ${DDK_DIR}
# endif	

# ifdef _ISDBT_ENABLE_
	cp ${LIB_DIR}/${NIM_S3821_LIB} ${DDK_DIR}
# endif	

# ifdef _DVBT2_ENABLE_
	cp ${LIB_DIR}/${NIM_S3821_LIB} ${DDK_DIR}
# endif	

# ifdef _DVBC_ENABLE_
	cp ${LIB_DIR}/${NIM_S3281_C_LIB} ${DDK_DIR}
# endif	

	
sdk:
	rm -f ${LIB_DIR}/list.ddk
	rm -f ${LIB_DIR}/list.nmt
	
	${MAKE} nim; \
	cd ${ROOT}/src; \
	  ${MAKE} ${LMOD} ;\

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
ifndef _BUILD_OTA_E_
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
	cd ${PLUGINDDK_DIR}; \
		rm -f *.*;
	cd ${PLUGINEXT_DIR}; \
		rm -f *.*;
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
	./updatelabel_sec.bat Security_module > label_log.txt

# End of common description.

# Construct of sub-modules

# Deconstruct of sub-modules

DDK_PRJ_DIR=prj/app/demo/combo/sabbat_dual
DDK_REL_DIR=${BASE_DIR}/../ddk_release
CAS9_REL_DIR=${BASE_DIR}/../cas9_release_combo
CAS7_REL_DIR=${BASE_DIR}/../cas7_release_combo
CIPLUS_REL_DIR=${BASE_DIR}/../ciplus_release_combo
PLUGIN_REL_DIR=${BASE_DIR}/../plugin_combo
BC_REL_DIR=${BASE_DIR}/../bc_release_combo

sdk_root:
	rm -rf ${DDK_REL_DIR}
	mkdir ${DDK_REL_DIR}

sdk_rel_3821:
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
#	mkdir -p ${DDK_REL_DIR}/${DDK_PRJ_DIR}/loader3_AS_G2
#	mkdir -p ${DDK_REL_DIR}/${DDK_PRJ_DIR}/loader3_3503_logo
	mkdir -p ${DDK_REL_DIR}/src/app
	mkdir -p ${DDK_REL_DIR}/prj/tools
#	mkdir -p ${DDK_REL_DIR}/supplement
ifdef _WIFI_ENABLE_
	mkdir -p ${DDK_REL_DIR}/ddk/wifi
	cp ${DDK_DIR}/wifi/lib_*_gusb.a ${DDK_REL_DIR}/ddk/wifi/
endif
	mkdir -p ${DDK_REL_DIR}/ddk/ali_3g
	cp ${DDK_DIR}/ali_3g/*.* ${DDK_REL_DIR}/ddk/ali_3g/

	mkdir -p ${DDK_REL_DIR}/src/lld/pmu/mcu
	cp -rf ${BASE_DIR}/src/lld/pmu/mcu ${DDK_REL_DIR}/src/lld/pmu
	
	mkdir -p ${DDK_REL_DIR}/aui
	cp -rf ${BASE_DIR}/aui/* ${DDK_REL_DIR}/aui/
	rm -rf ${DDK_REL_DIR}/aui/nestor
	mkdir -p ${DDK_REL_DIR}/prj/app/demo/combo/aui_demo/
	cp -rf ${BASE_DIR}/prj/app/demo/combo/aui_demo/* ${DDK_REL_DIR}/prj/app/demo/combo/aui_demo/

	cd ${DDK_DIR}; \
	cp ${ALL_LIBS} ${DDK_REL_DIR}/ddk/ ;\
	cp lib7zip.a ${DDK_REL_DIR}/ddk/ ;\
	cp libmlzo.a ${DDK_REL_DIR}/ddk/ ;\

	cp ${DDK_DIR}/libmpg2c.a ${DDK_REL_DIR}/ddk/
ifdef DUAL_ENABLE
	cp ${DDK_DIR}/libsee_m382x*.a	${DDK_REL_DIR}/ddk/
endif
	cp ${DDK_DIR}/libcore_v40e_m382x*.a	${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/libmpg6c.a ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/plugin/lib_ogg.o ${DDK_REL_DIR}/ddk/plugin/
#	cp ${DDK_DIR}/plugin/*.* ${DDK_REL_DIR}/ddk/plugin/
#	cp ${DDK_DIR}/plugin_ext/*.* ${DDK_REL_DIR}/ddk/plugin_ext/
	cp ${DDK_DIR}/${BOOT_MOD}.o ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/boot_see.o ${DDK_REL_DIR}/ddk/
	cp ${DDK_DIR}/libHDMI.a ${DDK_REL_DIR}/ddk/
	
ifdef _DVBT_ENABLE_
	cp 	${DDK_DIR}/libnim_t.a ${DDK_REL_DIR}/ddk/libnim_t.a
endif
#   3821 bootloader releate *.a , need to add here
#	cd ${DDK_DIR}; \
#	cd blsdk ;\
#	cp -f ${BOOT_LIBS_3503} ${DDK_REL_DIR}/ddk/blsdk/
	
	cd ${BASE_DIR}/prj/tools; \
	cp ${ALL_TOOLS} ${DDK_REL_DIR}/prj/tools ;\

#	cp -r loader3_AS_G2 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/ ;echo
	cp -r ./rsc 	${DDK_REL_DIR}/${DDK_PRJ_DIR}

	cp -f ${BASE_DIR}/inc/unistd.h ${DDK_REL_DIR}/inc/unistd.h
	cp -f ${BASE_DIR}/inc/string.h ${DDK_REL_DIR}/inc/string.h
	cp -f ${BASE_DIR}/inc/stdlib.h ${DDK_REL_DIR}/inc/stdlib.h
	cp -f ${BASE_DIR}/inc/stdio.h ${DDK_REL_DIR}/inc/stdio.h

	cp -f ${BASE_DIR}/ddk/genlist.exe ${DDK_REL_DIR}/ddk/genlist.exe
	cp -f ${BASE_DIR}/ddk/mod_makefile.exe ${DDK_REL_DIR}/ddk/mod_makefile.exe
	cp -f ${BASE_DIR}/src/path.def ${DDK_REL_DIR}/src/
	cp -f ${BASE_DIR}/src/makefile ${DDK_REL_DIR}/src/
	cp -f ${BASE_DIR}/src/compiler.def ${DDK_REL_DIR}/src/
	cp -f ./tve_hd_setting_half_mode_M3603.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ldscript.ld ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./see_ldscript.ld ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./compiler_3821.def ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./sys_config_3821.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./sys_memmap_3821.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/	
	cp -f ./*.m2v ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./bloader3_3821*.abs ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./blocks_script_7z_*.txt ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ota_parameter.bin ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./factory_data_*.bin ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./empty_hdcp.key ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./getpath.sh	 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./build_ota*.sh	 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./universal_key_encrypt_M3823.sh ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ota_link.c ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./how_to_compile_3823*.txt ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_full_mode.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_half_mode.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./tve_hd_setting_half_mode_M3603.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./*.ddf ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -rf ./platform/* ${DDK_REL_DIR}/${DDK_PRJ_DIR}/platform
	cp -f ./layout.zip ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_ci_common.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./win_parental* ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./ad_*.* ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	cp -f ./test*.h ${DDK_REL_DIR}/${DDK_PRJ_DIR}/
	
	cd ${ROOT}/src; \
	  ${MAKE} ${DMOD__}; \
	  ${MAKE} ${RMOD__};\
	  ${MAKE} ${BL_RMOD__}
	cd copper_common; \
	  ${MAKE} ddk_rel

mheg5_v20_core:
	rm -f ${LIB_DIR}/list.mheg
	cd ${ROOT}/src; \
	  ${MAKE} UDI_MHEG_V20_CORE
	  
mheg5_v20_core_clean:
	cd ${ROOT}/src; \
	  ${MAKE} UDI_MHEG_V20_CORE_

mheg5_v20_app:
	cp ${BASE_DIR}/src/udi/lib_mheg5_v20/*.a ${DDK_DIR}/

	cd ${ROOT}/src; \
	  ${MAKE} UDI_MHEG_V20_CIPLUS_APP

	cd ${LIB_DIR}; \
	  echo MH5 = \\ > libmheg5app.mak; \
	  echo cat \\ > cat.sh; \
	  cat list.mheg >> cat.sh; \
	  echo \>\> libmheg5app.mak >> cat.sh; \
	  sh < cat.sh; \
	  rm -f cat.sh
	echo "#" >> ${LIB_DIR}/libmheg5app.mak
	echo all: >> ${LIB_DIR}/libmheg5app.mak
	echo "	${AR} -r libmheg5app.a \$${MH5}" >> ${LIB_DIR}/libmheg5app.mak
	cd ${LIB_DIR}; \
	  ${MAKE} -f libmheg5app.mak

	cp ${LIB_DIR}/libmheg5app.a ${DDK_DIR}/
	rm -f ${LIB_DIR}/libmheg5app.mak
	rm -f ${LIB_DIR}/libmheg5app.a
	  
mheg5_v20_app_clean:
	cd ${ROOT}/src; \
	  ${MAKE} UDI_MHEG_V20_CIPLUS_APP_

mheg5_v20_rel:
	rm -rf ${BASE_DIR}/../ddk_release
	mkdir ${BASE_DIR}/../ddk_release
	cd ${ROOT}/src; \
	  ${MAKE} UDI_MHEG_V20_APP__
	cp ${BASE_DIR}/src/udi/lib_mheg5_v20/*.a ${BASE_DIR}/../ddk_release/src/udi/lib_mheg5_v20/
	
cas7_rel:
	mkdir -p ${CAS7_REL_DIR}/ddk
	mkdir -p ${CAS7_REL_DIR}/inc
	mkdir -p ${CAS7_REL_DIR}/inc/api
	mkdir -p ${CAS7_REL_DIR}/inc/api/libtsi
	mkdir -p ${CAS7_REL_DIR}/inc/api/libcas
	mkdir -p ${CAS7_REL_DIR}/${DDK_PRJ_DIR}
	
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${CAS7_REL_DIR}/inc/api/libtsi/
	cp -r ${BASE_DIR}/inc/freetype2 ${CAS7_REL_DIR}/inc/
	cp -f ${BASE_DIR}/inc/api/libcas/conax_mmi.h ${CAS7_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas_ca_info.h ${CAS7_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas.h ${CAS7_REL_DIR}/inc/api/libcas/
	cp -r ${BASE_DIR}/inc/api/libge ${CAS7_REL_DIR}/inc/api/
	cp -f ${BASE_DIR}/ddk/libfreetype.a ${CAS7_REL_DIR}/ddk/
	cp -r conax_ap7 ${CAS7_REL_DIR}/${DDK_PRJ_DIR}/
cas9_rel:
	mkdir -p ${CAS9_REL_DIR}/ddk
	mkdir -p ${CAS9_REL_DIR}/ddk/blsdk
	mkdir -p ${CAS9_REL_DIR}/inc
	mkdir -p ${CAS9_REL_DIR}/inc/api
	mkdir -p ${CAS9_REL_DIR}/inc/api/libtsi
	mkdir -p ${CAS9_REL_DIR}/inc/api/libcas
	mkdir -p ${CAS9_REL_DIR}/inc/api/libcas/cas9
	mkdir -p ${CAS9_REL_DIR}/${DDK_PRJ_DIR}
	
#	cp -f ${DDK_DIR}/blsdk/boot35.o ${CAS9_REL_DIR}/ddk/blsdk
#	cp -f ${DDK_DIR}/blsdk/boot_see*.o ${CAS9_REL_DIR}/ddk/blsdk
#	cp -f ${DDK_DIR}/blsdk/libboot_m35.a ${CAS9_REL_DIR}/ddk/blsdk
#	cp -f ${DDK_DIR}/blsdk/libslot36f.a ${CAS9_REL_DIR}/ddk/blsdk
#	cp -f ${DDK_DIR}/blsdk/libslot3602f.a ${CAS9_REL_DIR}/ddk/blsdk
#	cp -f ${DDK_DIR}/blsdk/libslothd_ct1628.a ${CAS9_REL_DIR}/ddk/blsdk
#	cp -f ${DDK_DIR}/blsdk/libslothd_fd650.a ${CAS9_REL_DIR}/ddk/blsdk
#	cp -f ${DDK_DIR}/blsdk/libblsee*.a ${CAS9_REL_DIR}/ddk/blsdk
	cp -f ${BASE_DIR}/inc/api/libtsi/db_3l_T.h ${CAS9_REL_DIR}/inc/api/libtsi/
	cp -r ${BASE_DIR}/inc/freetype2 ${CAS9_REL_DIR}/inc/
	cp -f ${BASE_DIR}/inc/api/libcas/cas9/cas9.h ${CAS9_REL_DIR}/inc/api/libcas/cas9/
	cp -f ${BASE_DIR}/inc/api/libcas/conax_mmi.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas_ca_info.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -f ${BASE_DIR}/inc/api/libcas/mcas.h ${CAS9_REL_DIR}/inc/api/libcas/
	cp -r ${BASE_DIR}/inc/api/libge ${CAS9_REL_DIR}/inc/api/
	cp -f ${BASE_DIR}/ddk/libfreetype.a ${CAS9_REL_DIR}/ddk/
	cp -r conax_ap ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/
#	cp -r loader3_hw_security ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/	
	#remove keys in release DIR in order to force customer to modify it
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/decrypt_key.bin
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/sys_sw_pair.key
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/orig_bl_key.bin
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/see_test_pair.key
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libupg_rs232_m32*.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/libconax_m32*.a
	rm -f ${CAS9_REL_DIR}/${DDK_PRJ_DIR}/conax_ap/vsc_see_se*.bin

plugin_rel:
	mkdir -p ${PLUGIN_REL_DIR}/ddk
	mkdir -p ${PLUGIN_REL_DIR}/ddk/plugin
	mkdir -p ${PLUGIN_REL_DIR}/ddk/plugin_ext
	
	cp -f ${DDK_DIR}/plugin/*.* ${PLUGIN_REL_DIR}/ddk/plugin/
	cp -f ${DDK_DIR}/plugin_ext/*.* ${PLUGIN_REL_DIR}/ddk/plugin_ext/		
ifdef _WIFI_ENABLE_
	mkdir -p ${DDK_REL_DIR}/ddk/wifi
	cp ${DDK_DIR}/wifi/lib_rt5370_gusb.a ${DDK_REL_DIR}/ddk/wifi/
	cp ${DDK_DIR}/wifi/*.o ${DDK_REL_DIR}/ddk/wifi/
endif

bakcp:
	cp -f ${DDK_DIR}/plugin/lib_flv.o.bak ${DDK_DIR}/plugin/lib_flv.o
	cp -f ${DDK_DIR}/plugin/lib_con_amr.o.bak ${DDK_DIR}/plugin/lib_con_amr.o
ifdef _RD_DEBUG_
	cp -f ${DDK_DIR}/plugin/plugin_eac3.o.bak ${DDK_DIR}/plugin/plugin_eac3.o
	rm -f ${DDK_DIR}/plugin/plugin_ac32c.o
endif

#for model compile,add by kent 2013-6-21
KK_MOD:  
	rm -f ${LIB_DIR}/list.nmt
	cd ${ROOT}/src; \
	  ${MAKE} ${KK_MODEL}
	
	cd copper_common; \
	  ${MAKE} all
	cd platform; \
	  ${MAKE} all
	cd platform/chip; \
	  ${MAKE} all
	cd ${CHIP_CFG_PATH}; \
	  ${MAKE} all
	cd ${CHIP_AVDCFG_PATH}; \
	  ${MAKE} all
	
	@echo Entering Board: ${BOARD_CFG_PATH}
	cd ${BOARD_CFG_PATH}; \
	 ${MAKE} all	
	  
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk ${LINKER};
ifdef DUAL_ENABLE
	cp -f ${SEE_LSCR} ${LIB_DIR}
	cd ${LIB_DIR}; \
  	  ${MAKE} -f ${MOD}.lk ${SEE_LINKER}
endif	

pre_boot_total_area:
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk pre_boot_total_area_cas9

aui :
	cd ${ROOT}/aui; \
		${MAKE} aui_clean aui_test_clean aui aui_test
	
alici :
ifdef _TEST_OLD_CI_
	cd ${ROOT}/aui; \
		${MAKE} aui_nestor_clean aui_nestor
else
	cd ${ROOT}/alici; \
		${MAKE} clean all
endif
