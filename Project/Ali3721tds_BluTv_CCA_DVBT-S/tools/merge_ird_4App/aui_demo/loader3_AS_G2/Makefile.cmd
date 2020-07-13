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
DDK_PRJ_DIR=prj/app/demo/combo/aui_demo
DDK_REL_DIR=${BASE_DIR}/../ddk_release
DDK_BLSDK_DIR = ${ROOT}/ddk/blsdk
include ${ROOT}/src/compiler.def
include ${ROOT}/src/path.def

SIG_TOOL_DIR=${ROOT}/prj/app/demo/combo/aui_demo/conax_ap

# Module Name
MOD = BOOT_LOADER3
OUT = bloader3
USEE_OUT = usee_bloader3

## bl cpu model
ifdef DUAL_ENABLE
	ifdef _BOOT_LOGO_
		SDKLIB = libboot_m35_logo
	else
		SDKLIB = libboot_m35
	endif

	ifndef _STANDBY_C_CODE_
		BOOT = boot35
	else
		BOOT = boot35_stby_c
	endif
else
	SDKLIB = libboot_m35_single
	ifndef _STANDBY_C_CODE_
		BOOT = boot35_single
	else
		BOOT = boot35_stby_c_single
	endif
endif

ifndef _STANDBY_C_CODE_
SLOT_MOD = BOOT_SLOTHD_CH455
SLOT = libslothd_ch455
STANDBYLIB = libstandby36
else
SLOT_MOD = BOOT_SLOT_C
SLOT = libslot_c
STANDBYLIB = libstandby36_c
endif
## bl see model


ifdef _HW_SECURITY_ENABLE_ 
ifdef _M3515_SECURE_BOOT_ENABLE_
UBOOT_SEE = boot_see_sec_m35_logo
USEELIB = libblsee_sec_m35_logo
BOOT_SEE = boot_see_sec_m35_nologo
SEELIB = libblsee_sec_m35_nologo
else
UBOOT_SEE = boot_see_sec_nologo
USEELIB = libblsee_sec_nologo
BOOT_SEE = boot_see_sec_nologo
SEELIB = libblsee_sec_nologo
endif
else
UBOOT_SEE = boot_see_nosec_logo
USEELIB = libblsee_nosec_logo
BOOT_SEE = boot_see_nosec_logo
SEELIB = libblsee_nosec_logo
endif

ifdef _CAS9_VSC_ENABLE_
	SEE_LSCR = see_ldscript_vsc.ld
else
SEE_LSCR = see_ldscript.ld
endif
USEE_LSCR = usee_ldscript.ld
SEE_LINKER = see_link
USEE_LINKER = usee_link
ifndef _HW_SECURITY_ENABLE_
ifndef _BOARD_DB_M3822_01V01_
BOOTCONFIG = boot_m35_128M
else
BOOTCONFIG = boot_m3821_128M
endif
else
BOOTCONFIG = boot_m35_128M_sec
endif


ifdef _BOARD_DB_M3822_01V01_
CHIP = 3821
else
CHIP = 3503
endif

ifdef DUAL_CPU
CPUNUM = dual
else
CPUNUM = single
endif

ifdef _BOOT_LOGO_
OUTPUTABS = bloader3_$(CHIP)_$(CPUNUM)_logo
else
OUTPUTABS = bloader3_$(CHIP)_$(CPUNUM)
endif

ifndef DUAL_ENABLE
	LSCR = ldscript.ld
else
ifndef _HW_SECURITY_ENABLE_
LSCR = ldscript_logo.ld
else
ifndef _ENABLE_BL_ENCRYPTED_
	LSCR = ldscript_security.ld
else
	LSCR = ldscript_security_encbl.ld
endif
endif
endif

VSC_NAME=
ifdef _CAS9_VSC_ENABLE_
	VSC_NAME = _vsc
endif
ifdef _M3515_SECURE_BOOT_ENABLE_
	ifdef _ENABLE_BL_ENCRYPTED_
		ifdef _LINUX_BOOTLOADER_
			ifdef _NAND_BOOT_E_
				OUTPUTABS = bloader3_m3715_dual_encbl_nandonly
			else
				OUTPUTABS = bloader3_m3715_dual_encbl
			endif
		else
			OUTPUTABS = bloader3_3503_encbl$(VSC_NAME)
		endif
	else
		ifdef _LINUX_BOOTLOADER_
			OUTPUTABS = bloader3_m3715_dual
		else
			OUTPUTABS = bloader3_3503_sec$(VSC_NAME)
		endif
	endif
else
	ifdef _LINUX_BOOTLOADER_
		ifdef _NAND_BOOT_E_
			OUTPUTABS = bloader3_m3516_nandonly
		else	
			OUTPUTABS = bloader3_m3516
		endif
	endif
endif

ifdef _STANDBY_C_CODE_
OUTPUTABS = bloader3_3503_dual_stby_c
endif
ifndef DUAL_ENABLE
BOOT_LIBS = ${BOOT}.o ${SDKLIB}.a liblog.a ${STANDBYLIB}.a
else
BOOT_LIBS = ${BOOT}.o ${BOOT_SEE}.o ${SEELIB}.a ${SDKLIB}.a liblog.a ${STANDBYLIB}.a
endif
COMM_LIBS = lib7zip.a libmlzo.a
BOOT_BIN = boot_enc.o glue.o
TOOLS = bmerger code_build.exe

# List of source files
	ASMS = 
	SRCS = expand.c boot_system_data.c boot_init.c
ifdef _C0300A_CA_ENABLE_ 
	SRCS += bootloader_c0300a.c 
else 
	ifdef _C0300A_CA_STD_ENABLE_ 
		SRCS += bootloader_c0300a.c 
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
	  HLD_STO BUS_SCI_UART LLD_IRC_M63 HLD_BASE \
	  HLD_PAN LIB_BOOTUPG3 LLD_PAN_CH455 ${SLOT_MOD} BOOT_PUB
LMOD = 
SMOD =

ifdef _HW_SECURITY_ENABLE_
RMOD += HLD_SMC LLD_SMARTCARD HLD_DSC HLD_CRYPTO
endif

ifdef _M3515_SECURE_BOOT_ENABLE_
RMOD += HLD_SEC_BOOT
endif

ifdef _BOOT_LOGO_
RMOD += BUS_DMA_M36F HLD_DECV HLD_VP HLD_VENC
endif

ifdef _NAND_BOOT_E_
RMOD += LLD_STO_RAM
else
RMOD += LLD_STO_FLASH_SQI
endif

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
ifdef DUAL_ENABLE
	cp ${DDK_BLSDK_DIR}/$(SEELIB).a ${LIB_DIR}/libblsee.a
	cp ${DDK_BLSDK_DIR}/$(BOOT_SEE).o ${LIB_DIR}/boot_see.o
endif
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
	sde-objdump -d ${LIB_DIR}/see_bloader3.out > ${LIB_DIR}/see_bloader3.dis
endif	
	cd ${LIB_DIR}; \
	  ${MAKE} -f ${MOD}.lk link
ifdef  _M3515_SECURE_BOOT_ENABLE_	  
ifndef _C0300A_CA_ENABLE_	
ifndef _C0300A_CA_STD_ENABLE_	  
	cd ${ROOT}
	cp -f ${LIB_DIR}/see_bloader3.abs ${SIG_TOOL_DIR}/see_bloader3.abs
	${MAKE} see_sig
	cp -f ${SIG_TOOL_DIR}/see_bloader3_s.abs see_bloader3_3503_s.abs
	cp -f see_bloader3_3503_s.abs ${ROOT}/prj/app/demo/combo/aui_demo/
endif	
endif
	cp -f ${LIB_DIR}/${OUT}.abs ${ROOT}/prj/app/demo/combo/aui_demo/bloader3_m3515_dual.abs   
endif	
	cp -f ${LIB_DIR}/${OUT}.abs ${OUTPUTABS}.abs
	cp -f ${LIB_DIR}/${OUT}.abs ${ROOT}/prj/app/demo/combo/aui_demo/${OUTPUTABS}.abs   
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h


		
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
	${CC} ${CFLAGS} -M ${ASMS} ${SRCS} > dep.txt
	${DDK_DIR}/genlist dep.txt "${BASE_DIR}" "${DDK_REL_DIR}" "${DDK_REL_DIR}" "${DDK_REL_DIR}" 1>file.txt 2>dir.txt
	sh dir.txt
	sh file.txt
	rm -f dep.txt
	rm -f dir.txt
	rm -f file.txt
	mkdir -p ${DDK_REL_DIR}/obj
	mkdir -p ${DDK_REL_DIR}/ddk
	mkdir -p ${DDK_REL_DIR}/ddk/blsdk
	mkdir -p ${DDK_REL_DIR}/${DDK_PRJ_DIR}/loader3_AS_G2
	mkdir -p ${DDK_REL_DIR}/prj/tools	
	mkdir -p ${DDK_REL_DIR}/src

	cd ${DDK_DIR}/blsdk/; \
	cp -f ${BOOT_LIBS} ${DDK_REL_DIR}/ddk/blsdk/
	cd ${DDK_DIR};\
	cp -f ${COMM_LIBS} ${DDK_REL_DIR}/ddk/
	cp -r ../loader3_AS_G2 ${DDK_REL_DIR}/${DDK_PRJ_DIR}/ ;echo
	
	cp -f $(BASE_DIR)/src/Makefile  ${DDK_REL_DIR}/src/
	cp -rf $(BASE_DIR)/inc/modules.h  ${DDK_REL_DIR}/inc/modules.h
	cd ${BASE_DIR}/prj/tools; \
	cp -f $(TOOLS)    $(DDK_REL_DIR)/prj/tools/
	cd $(BASE_DIR)/obj; \
	
	cd ${BASE_DIR}/src; \
	  ${MAKE} ${RMOD__}

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

usee_all:
	cp ${DDK_BLSDK_DIR}/$(USEELIB).a ${LIB_DIR}/libblsee.a
	cp ${DDK_BLSDK_DIR}/$(UBOOT_SEE).o ${LIB_DIR}/boot_see.o
	cp -f ${USEE_LSCR} ${LIB_DIR}/see_ldscript.ld
	cat Makefile >> ${LIB_DIR}/${MOD}.lk
	cd ${LIB_DIR}; \
  	  ${MAKE} -f ${MOD}.lk ${USEE_LINKER}
	sde-objdump -d ${LIB_DIR}/usee_bloader3.out > ${LIB_DIR}/usee_bloader3.dis
	cp -f ${LIB_DIR}/${USEE_OUT}.o ${USEE_OUT}.lib

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
