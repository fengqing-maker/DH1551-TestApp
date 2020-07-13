#
# -= Makefile for application compile =-
#
# Note:
# . This is the second part of two makefile components;
#   Please refer "Makefile" for the other part.
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
ROOT = ../../../../../..
DDK_BLSDK_DIR = ${ROOT}/ddk/blsdk
include ${ROOT}/src/compiler.def
include ${ROOT}/src/path.def

# Module Name
MOD = BOOT_LOADER3
OUT = bloader3

ifdef _HW_SECURITY_ENABLE_
	SEC = sec
else
	SEC = nosec
endif

ifdef M3281_BOOT_WITH_LOGO
	LOGO = logo3281
else
	ifdef _BOOT_LOGO_
		LOGO = logo
	else
		LOGO = nologo
	endif
endif

ifdef _MIPS2_ENABLE_
	BOOT = boot_encbl_m32
	SDKLIB = libboot_encbl_m32
	STANDBYLIB = libstandby36_m32

	SEELIB = libblsee_m32_$(SEC)_$(LOGO)
	BOOT_SEE = boot_see_m32_$(SEC)_$(LOGO)
else
	BOOT = boot_encbl
	SDKLIB = libboot_encbl
	STANDBYLIB = libstandby36

	SEELIB = libblsee_$(SEC)_$(LOGO)
	BOOT_SEE = boot_see_$(SEC)_$(LOGO)
endif

ifndef _ENABLE_BL_ENCRYPTED_
	ifdef _BOARD_DB_M3281_01V01_
		SLOT_MOD = BOOT_SLOT3602F
		SLOT = libslot3602f
	else
	##demo board
		SLOT_MOD = BOOT_SLOT36F
		SLOT = libslot36f
	endif
else
	ifdef _BOARD_DB_M3281_01V01_
		SLOT_MOD = BOOT_SLOT3602F
		SLOT = libslot3602f
	else
	##demo board
		SLOT_MOD = BOOT_SLOT36F
		SLOT = libslot36f
	endif
endif

ifdef _USE_32M_MEM_
	ifdef _M3281_SOLUTION3_SUPPORT_
		SEE_LSCR = see_ldscript_32M_solution3.ld
		BOOTCONFIG = boot_m3281_32M_solution3
	else
		ifdef _CAS9_VSC_ENABLE_
			SEE_LSCR = see_ldscript_VSC_32M.ld
		else
			SEE_LSCR = see_ldscript_32M.ld
		endif
	BOOTCONFIG = boot_m3281_32M
	endif
else
	ifdef _CAS9_VSC_ENABLE_
		SEE_LSCR = see_ldscript_VSC.ld
	else
		SEE_LSCR = see_ldscript.ld
	endif
	BOOTCONFIG = boot_m3281_64M
endif
SEE_LINKER = see_link

ifndef _ENABLE_BL_ENCRYPTED_
OUTPUTABS = bloader3_3281_security
LSCR = ldscript_security.ld
else
OUTPUTABS = bloader3_3281_bl_encrypted
LSCR = ldscript_security_encbl.ld
endif


VSC_NAME=
ifdef _CAS9_VSC_ENABLE_
	VSC_NAME = _vsc
endif

ifdef _USE_32M_MEM_
	ifdef _ENABLE_BL_ENCRYPTED_
		ifdef _BOARD_DB_M3281_01V01_
			OUTPUTABS1 = bloader3_3281_bl_encrypted_debugboard_32M$(VSC_NAME)
		else
			OUTPUTABS1 = bloader3_3281_bl_encrypted_demoboard_32M$(VSC_NAME)
		endif
	else
		ifdef _BOARD_DB_M3281_01V01_
			OUTPUTABS1 = bloader3_3281_security_debugboard_32M$(VSC_NAME)
		else
			OUTPUTABS1 = bloader3_3281_security_demoboard_32M$(VSC_NAME)
		endif
	endif
else
	ifdef _ENABLE_BL_ENCRYPTED_
		ifdef _BOARD_DB_M3281_01V01_
			OUTPUTABS1 = bloader3_3281_bl_encrypted_debugboard_64M$(VSC_NAME)
		else
			OUTPUTABS1 = bloader3_3281_bl_encrypted_demoboard_64M$(VSC_NAME)
		endif
	else
		ifdef _BOARD_DB_M3281_01V01_
			OUTPUTABS1 = bloader3_3281_security_debugboard_64M$(VSC_NAME)
		else
			OUTPUTABS1 = bloader3_3281_security_demoboard_64M$(VSC_NAME)
		endif
	endif
endif




# List of source files
	ASMS = 
	SRCS = expand.c boot_system_data.c boot_showlogo.c boot_init.c
ifdef _BC_CA_ENABLE_ 
	SRCS += bootloader_bc.c 
else 
	ifdef _BC_CA_STD_ENABLE_ 
		SRCS += bootloader_bc.c 
	else
		SRCS += bootloader.c 	
	endif	
endif

# List of library files
LIBS =

# List of dependent modules
DMOD =


_LIB_UI_CFG = 


# Release library
RMOD = LIB_C LIB_CHUNK LIB_LIB7ZIP BUS_I2C_SCB BUS_I2C_GPIO\
	  HLD_STO LLD_STO_FLASH_SQI BUS_SCI_UART HLD_SMC LLD_SMARTCARD\
	  LLD_IRC_M63 HLD_BASE HLD_PAN LIB_BOOTUPG3 LLD_PAN_CH455\
   	HLD_DSC HLD_CRYPTO ${SLOT_MOD}

ifdef M3281_BOOT_WITH_LOGO
	RMOD += HLD_VP HLD_DECV
endif

LMOD = 
SMOD =

CPU_RMOD = LLD_TRNG_M36F  LLD_DSC_M36F  LLD_CRYPTO_M36F HLD_DSC HLD_CRYPTO

ALL_RMOD = HLD_BASE ${CPU_RMOD}



RELPROJ = ${BASE_DIR}
RELLIB = libbl



# Following lines are the common description for all projects.
# Do NOT modify anything, unless you know what you are doing.


OBJS = ${ASMS:.S=.o} ${SRCS:.c=.o}
SMOD_ = ${SMOD:=_}
DMOD_ = ${DMOD:=_}
RMOD_ = ${RMOD:=_}
LMOD_ = ${LMOD:=_}
SMOD__ = ${SMOD:=__}
DMOD__ = ${DMOD:=__}
RMOD__ = ${RMOD:=__}
LMOD__ = ${LMOD:=__}


all : ${MOD}.mk
	cp ${DDK_BLSDK_DIR}/$(SEELIB).a ${LIB_DIR}/libblsee.a
	cp ${DDK_BLSDK_DIR}/$(BOOT_SEE).o ${LIB_DIR}/boot_see.o
	cp ${DDK_BLSDK_DIR}/$(BOOT).o ${LIB_DIR}/boot.o
	cp ${DDK_BLSDK_DIR}/$(STANDBYLIB).a ${LIB_DIR}/libstandby.a
	cp ${DDK_BLSDK_DIR}/$(SLOT).a ${LIB_DIR}/libslot.a
	cp ${DDK_BLSDK_DIR}/liblog.a ${LIB_DIR}/
	cp ${DDK_BLSDK_DIR}/$(SDKLIB).a ${LIB_DIR}/libboot.a
	cp ${ROOT}/ddk/lib7zip.a ${LIB_DIR}/
	cp ${ROOT}/ddk/libmlzo.a ${LIB_DIR}/
	cp ${BOOTCONFIG}.cfg ${LIB_DIR}/boot.cfg
	cp ${BOOTCONFIG}.cfg boot.cfg
	cp ${ROOT}/prj/tools/bmerger.exe ${LIB_DIR}/bmerger.exe
	${MAKE} -f ${MOD}.mk ${OBJS}
	cp -f ${OBJS} ${LIBS} ${LIB_DIR}
	echo ${OBJS} ${LIBS} \\ > ${LIB_DIR}/${MOD}.lst
	rm -f ${LIB_DIR}/list.mod
	cd ${ROOT}/src; \
	  ${MAKE} ${DMOD}
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
	cat Makefile >> ${LIB_DIR}/${MOD}.lk
ifdef DUAL_ENABLE
	cp -f ${SEE_LSCR} ${LIB_DIR}/see_ldscript.ld
	cd ${LIB_DIR}; \
  	  ${MAKE} -f ${MOD}.lk ${SEE_LINKER}
endif	
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk link
##cp -f ${LIB_DIR}/${OUT}.abs ${OUTPUTABS}.abs
	cp -f ${LIB_DIR}/${OUT}.abs ${OUTPUTABS1}.abs   
##cp -f ${LIB_DIR}/${OUT}.abs ../../../../../../../../../S3281/Elephant/prj/app/demo/combo/aui_demo/${OUTPUTABS1}.abs   

		
${MOD}.mk : ${ASMS} ${SRCS}
	echo include ${ROOT}/src/path.def > $@
	echo include ${ROOT}/src/compiler.def >> $@
	cat Makefile >> $@
	${CC} ${CFLAGS} -M ${ASMS} ${SRCS} >> $@

clean :
	rm -f ${OBJS} ${MOD}.mk
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk cleanld; \
	  rm -f lscript.ld list.mod ${MOD}.lk; \
	  echo rm -f \\ > rm.sh; \
	  cat ${MOD}.lst >> rm.sh; \
	  sh < rm.sh; \
	  rm -f rm.sh ${MOD}.lst boot.o liblog.a libboot.a libstandby.a libslot.a boot.cfg bmerger.exe

new : clean
	cd ${ROOT}/src; \
	  ${MAKE} ${DMOD_} ${RMOD_}

rebuild: clean all

sdk_rel :
	rm -f ${LIB_DIR}/list.ddk
	cd ${ROOT}/src; \
	  ${MAKE} ${RMOD__}
	cd ${LIB_DIR}; \
	  echo NEED = \\ > ${SDKLIB}.mak; \
	  echo cat \\ > cat.sh; \
	  cat list.mod >> cat.sh; \
	  echo \>\> ${SDKLIB}.mak >> cat.sh; \
	  sh < cat.sh; \
	  rm -f cat.sh
	echo "#" >> ${LIB_DIR}/${SDKLIB}.mak
	echo all: >> ${LIB_DIR}/${SDKLIB}.mak
	echo "	${AR} -r ${SDKLIB}.a \$${NEED}" >> ${LIB_DIR}/${SDKLIB}.mak
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${SDKLIB}.mak
	cp -f ${LIB_DIR}/${SDKLIB}.a ${DDK_BLSDK_DIR}/
	rm -f ${LIB_DIR}/${SDKLIB}.mak

module_config:
#add "enum REMOTE_MODULES" into inc/modules.h
	cp modules.h $(ROOT)/inc; \
	cd $(ROOT)/inc; \
  echo	${ALL_RMOD} | sed -e "s/[! ] *\$$//" | sed -e "s/ *[! ]/_MODULE,\n/g" | sed -e "\$${s/\$$/_MODULE,/}" >tmp.mod; \
	sed -e ':begin; /REMOTE_MODULES/,/\}/ {/\}/! { {N; b begin};};s/MODULES.*\}/MODULES\{\n\}/;};' modules.h | sed -e '/REMOTE_MODULES/r tmp.mod' > modules_tmp.h; \
	cp modules_tmp.h modules.h; rm -f tmp.mod; rm -f modules_tmp.h 
	
#generate g_remote_callee in modules_see.c based on modules.c
	echo	${ALL_RMOD}| sed -e 's/.*/\L&/' | sed -e "s/[! ] *\$$//" | sed -e "s/ *[! ]/_callee(UINT8 *);\n/g" | sed -e "\$${s/\$$/_callee(UINT8 *);/}" |sed -e "s/^/extern void /" > tmp1; 
	echo	${ALL_RMOD}| sed -e 's/.*/\L&/' | sed -e "s/[! ] *\$$//" | sed -e "s/ *[! ]/_callee,\n/g" | sed -e "\$${s/\$$/_callee,/}" | sed -e "s/^/\(UINT32\)/" >tmp2;
	sed -e ':begin; /g_remote_callee/,/\}/ {/\}/! { {N; b begin};};s/callee.*\}/callee[] = \{\n\}/;};' modules.c | sed -e '/<modules.h>/r tmp1' | sed -e '/g_remote_callee/r tmp2' > modules_see.c; \
	rm -f tmp3.sh; rm -f tmp3; rm -f tmp2; rm -f tmp1
	
#generate g_remote_callee in modules_cpu.c based on modules.c
	echo	${ALL_RMOD} | sed -e 's/.*/\L&/' | sed -e "s/[! ] *\$$//" | sed -e "s/ *[! ]/_callee(UINT8 *);\n/g" | sed -e "\$${s/\$$/_callee(UINT8 *);/}" |sed -e "s/^/extern void /" > tmp1; \
	echo	${ALL_RMOD} | sed -e 's/.*/\L&/' | sed -e "s/[! ] *\$$//" | sed -e "s/ *[! ]/_callee,\n/g" | sed -e "\$${s/\$$/_callee,/}" | sed -e "s/^/\(UINT32\)/" >tmp3; \
	echo	${CPU_RMOD} | sed -e "s/[! ] *\$$//" | sed -e "s/ *[! ]/\\\|/g" |sed -e "s/^/sed -e \"s\/\\\(/" | sed -e "s/\$$/\\\).*\/0,\/i\" tmp3/" > tmp3.sh; \
	chmod +x ./tmp3.sh; ./tmp3.sh > tmp2; \
	sed -e ':begin; /g_remote_callee/,/\}/ {/\}/! { {N; b begin};};s/callee.*\}/callee[] = \{\n\}/;};' modules.c | sed -e '/<modules.h>/r tmp1' | sed -e '/g_remote_callee/r tmp2' > modules_cpu.c; \
	rm -f tmp3.sh; rm -f tmp3; rm -f tmp2; rm -f tmp1

#generate compiler_see.def and compiler_cpu.def
	cat compiler.def > compiler_tmp.def
	echo	"DEFS += -D_DEBUG_VERSION_ -DDUAL_ENABLE -DSEE_CPU" >tmp; echo "DUAL_ENABLE = 1">>tmp;  echo "SEE_CPU = 1">>tmp;cat compiler_tmp.def tmp > compiler_see.def
	echo	${CPU_RMOD} | sed -e "s/[! ] *\$$//" | sed -e "s/ *[! ]/_REMOTE = 1\n/g" | sed -e "\$${s/\$$/_REMOTE = 1\n DEFS += -DDUAL_ENABLE -DMAIN_CPU\nDUAL_ENABLE = 1\nMAIN_CPU = 1/}" >tmp ; cat compiler_tmp.def tmp> compiler_cpu.def
	rm -f tmp;  rm -f compiler_tmp.def
	
see_release :
	rm -f ${LIB_DIR}/list.sdk
	rm -f ${LIB_DIR}/list.mod
	cd ${ROOT}/src; \
	  ${MAKE} ${SEE_CMOD} ${SEE_LMOD} ${SEE_RMOD} ${SEE_PPMOD}
	cd ${LIB_DIR}; \
	  echo NEED = \\ > ${SEELIB}.mak; \
	  echo cat \\ > cat.sh; \
	  cat list.mod >> cat.sh; \
	  echo \>\> ${SEELIB}.mak >> cat.sh; \
	  sh < cat.sh; \
	  rm -f cat.sh
	echo "#" >> ${LIB_DIR}/${SEELIB}.mak
	echo all: >> ${LIB_DIR}/${SEELIB}.mak
	echo "	${AR} -r ${SEELIB}.a \$${NEED}" >> ${LIB_DIR}/${SEELIB}.mak
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${SEELIB}.mak

see_all : see.mk
	${MAKE} -f see.mk ${SEE_OBJS}
	cp -f ${SEE_OBJS} ${LIBS} ${LIB_DIR}
	echo ${SEE_OBJS} ${LIBS} \\ > ${LIB_DIR}/${MOD}.lst
	rm -f ${LIB_DIR}/list.mod
	cp -f ${SEE_LSCR} ${LIB_DIR}/lscript.ld
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
	cat Makefile >> ${LIB_DIR}/${MOD}.lk
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk ${SEE_LINKER}


see_new :
	cd ${ROOT}/src; \
	  ${MAKE} ${SEE_CMOD_} ${SEE_LMOD_} ${SEE_RMOD_} ${SEE_PPMOD_};
	  
see.mk : ${SEE_ASMS} ${SEE_SRCS}
	echo include ${ROOT}/src/path.def > $@
	echo include ${ROOT}/src/compiler.def >> $@
	cat Makefile >> $@
	${CC} ${CFLAGS} -M ${SEE_ASMS} ${SEE_SRCS} >> $@
	
release :
	rm -f ${LIB_DIR}/list.mod
	rm -f ${LIB_DIR}/${RELLIB}.a
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
#	cp -f ${LIB_DIR}/${RELLIB}.a ${LIB_DIR}/liblog.a ${LIB_DIR}/boot.o \
#	  ${LIB_DIR}/glue.o ${REL_DIR}/prj/${RELPROJ}/lib
	rm -f ${LIB_DIR}/${RELLIB}.mak
