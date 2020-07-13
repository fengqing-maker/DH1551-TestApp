#
# -= Makefile for application =-
#
# Note:
# . "make config" must be done for initial routines.
#
# Usage:
# . Change the ROOT definition, if necessary;
#   Make it point to the root of the software tree.
#

# Destination to the root of software tree
ROOT = ../../../../..
ROOT_PRJ = ../prj/app/demo/combo/sabbat_dual

MAKEFILE = MakefileCommon


# The command which is for Customer use
	
all :
	${MAKE} -f ${MAKEFILE} all

path:
	# First step change sh to unix style, for win7 
	@dos2unix *.sh 2>/dev/null
	@dos2unix ${ROOT}/ddk/genlist* 2>/dev/null
ifdef LOGISCOPE_CMD_LINE
	dos2unix ${ROOT}/prj/tools/logiscope/*.sh
endif
	chmod +x getpath.sh
	./getpath.sh

config_cpu :
	${MAKE} -f ${MAKEFILE} config_cpu

config_3811 :
	${MAKE} -f ${MAKEFILE} config_3811

config_3281 :
	${MAKE} -f ${MAKEFILE} config_3281
	
config_3281_ota :
	${MAKE} -f ${MAKEFILE} config_3281_ota

config_3503 :
	${MAKE} -f ${MAKEFILE} config_3503
	
config_3503B :
	${MAKE} -f ${MAKEFILE} config_3503B

config_3503_ota :
	${MAKE} -f ${MAKEFILE} config_3503_ota
	
config_3503_usb :
	${MAKE} -f ${MAKEFILE} config_3503_usb
	
config_3503B_upg :
	${MAKE} -f ${MAKEFILE} config_3503B_upg
config_3505 :
	${MAKE} -f ${MAKEFILE} config_3505
config_3505_ota :
	${MAKE} -f ${MAKEFILE} config_3505_ota
config_3505_usb :
	${MAKE} -f ${MAKEFILE} config_3505_usb
config_3505_ouc :
	${MAKE} -f ${MAKEFILE} config_3505_ouc
	
config_3821 :
	${MAKE} -f ${MAKEFILE} config_3821

config_3821_ota :
	${MAKE} -f ${MAKEFILE} config_3821_ota	

config_3821_loader :
	${MAKE} -f ${MAKEFILE} config_3821_loader

config_3702 :
	${MAKE} -f ${MAKEFILE} config_3702

config_3702_ota :
	${MAKE} -f ${MAKEFILE} config_3702_ota

config_3702_usb :
	${MAKE} -f ${MAKEFILE} config_3702_usb

config_3702_ouc :
	${MAKE} -f ${MAKEFILE} config_3702_ouc

config_3702_loadercore :
	${MAKE} -f ${MAKEFILE} config_3702_loadercore
		
config_3702_mpclient :
	${MAKE} -f ${MAKEFILE} config_3702_mpclient
	
new :
	echo ${MAKEFILE}"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	${MAKE} -f ${MAKEFILE} new

ddk:	
	${MAKE} -f ${MAKEFILE} ddk

ui :
	${MAKE} -f ${MAKEFILE} ui
linkonly :
	${MAKE} -f ${MAKEFILE} linkonly
	
product_7z :
	${MAKE} -f ${MAKEFILE} product_7z


# The command which is Debug use

dis:
	${MAKE} -f ${MAKEFILE} dis
	
see_dis:
	${MAKE} -f ${MAKEFILE} see_dis

# The command which is for SDK use
bin:
	${MAKE} -f ${MAKEFILE} bin	

sync :
	${MAKE} -f ${MAKEFILE} sync

syncbl :
	${MAKE} -f ${MAKEFILE} syncbl

clean :
	${MAKE} -f ${MAKEFILE} clean

nim :
	${MAKE} -f ${MAKEFILE} nim

bc :
	${MAKE} -f ${MAKEFILE} bc

bc_clean :
	${MAKE} -f ${MAKEFILE} bc_clean

sat2ip_lib :
	${MAKE} -f ${MAKEFILE} sat2ip_lib

stdby_lib :
	${MAKE} -f ${MAKEFILE} stdby_lib

compress_7z :
	${MAKE} -f ${MAKEFILE} compress_7z

generate_7z :
	${MAKE} -f ${MAKEFILE} generate_7z

link :
	${MAKE} -f ${MAKEFILE} link

link_ota :
	${MAKE} -f ${MAKEFILE} link_ota

see_link : 
	${MAKE} -f ${MAKEFILE} see_link

see_link_ota :
	${MAKE} -f ${MAKEFILE} see_link_ota

cleanld :
	${MAKE} -f ${MAKEFILE} cleanld

label :
	${MAKE} -f ${MAKEFILE} label

label_core :
	${MAKE} -f ${MAKEFILE} label_core

label_sec :
	${MAKE} -f ${MAKEFILE} label_sec

sdk_os:
	${MAKE} -f ${MAKEFILE} sdk_os	

sdk_lib:
	${MAKE} -f ${MAKEFILE} sdk_lib
sdk:
	${MAKE} -f ${MAKEFILE} sdk	

ddk_clean :
	${MAKE} -f ${MAKEFILE} ddk_clean
	
sdk_clean :
	${MAKE} -f ${MAKEFILE} sdk_clean
sdk_lib_clean :
	${MAKE} -f ${MAKEFILE} sdk_lib_clean

plus_clean:
	${MAKE} -f ${MAKEFILE} plus_clean
	
plus_lib_clean:
	${MAKE} -f ${MAKEFILE} plus_lib_clean
	
sdk_rel:
	${MAKE} -f ${MAKEFILE} sdk_rel

plus:
	${MAKE} -f ${MAKEFILE} plus

plus_lib:
	${MAKE} -f ${MAKEFILE} plus_lib
	
plus_open:
	${MAKE} -f ${MAKEFILE} plus_open
	
plus_open_clean:
	${MAKE} -f ${MAKEFILE} plus_open_clean
	
pplus:
	${MAKE} -f ${MAKEFILE} pplus

pplus_clean:
	${MAKE} -f ${MAKEFILE} pplus_clean

mheg5_v20_all:
	${MAKE} -f ${MAKEFILE} mheg5_v20_all	
	
mheg5_v20_core:	
	${MAKE} -f ${MAKEFILE} mheg5_v20_core
	
mheg5_v20_app:	
	${MAKE} -f ${MAKEFILE} mheg5_v20_app

mheg5_v20_all_clean :
	${MAKE} -f ${MAKEFILE} mheg5_v20_all_clean

mheg5_v20_core_clean :
	${MAKE} -f ${MAKEFILE} mheg5_v20_core_clean

mheg5_v20_app_clean :
	${MAKE} -f ${MAKEFILE} mheg5_v20_app_clean

mheg5_v20_rel:
	${MAKE} -f ${MAKEFILE} mheg5_v20_rel

ciplus_rel:
	${MAKE} -f ${MAKEFILE} ciplus_rel

see_enc: 	
	${MAKE} -f ${MAKEFILE} see_enc
	
bakcp:
	${MAKE} -f ${MAKEFILE} bakcp	

pre_boot_code:
	${MAKE} -f ${MAKEFILE} pre_boot_code

pre_boot_total_area:
	${MAKE} -f ${MAKEFILE} pre_boot_total_area

ddkbin :
	${MAKE} -f ${MAKEFILE} ddkbin
	
aui :
	${MAKE} -f ${MAKEFILE} aui
	
alici :
	${MAKE} -f ${MAKEFILE} alici

alici_build_sym:
	${MAKE} -f ${MAKEFILE} alici_build_sym

aui_sync_3505:
	${MAKE} -f MakefileSync aui_sync_3505

aui_sync_3702:
	${MAKE} -f MakefileSync aui_sync_3702



