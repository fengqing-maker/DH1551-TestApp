include ../../../../../../src/path.def
include ../../../../../../src/compiler.def
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
ROOT = ../../../../../..
DDK_PRJ_DIR=prj/app/demo/combo/sabbat_dual
CA_AP_DIR = conax_ap

# output file name
OUT = bloader3
SEE_OUT = see_bloader3
USEE_OUT = usee_bloader3

all :
	${MAKE} release
	${MAKE} -f Makefile.cmd all
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h		

rebuild_3503:
	${MAKE} path
	${MAKE} config_3503
	${MAKE} sdk
	${MAKE} new
	${MAKE} all

rebuild_3503_logo:
	${MAKE} path
	${MAKE} see_3503
	${MAKE} config_3503_logo
	${MAKE} sdk_S
	${MAKE} new
	${MAKE} all

rebuild_3503_single:
	${MAKE} path
	${MAKE} config_3503_single
	${MAKE} sdk
	${MAKE} new
	${MAKE} all

rebuild_3821:
	${MAKE} path
	${MAKE} config_3821
	${MAKE} sdk
	${MAKE} new
	${MAKE} all

rebuild_3821_logo:
	${MAKE} path
	${MAKE} see_3503
	${MAKE} config_3821_logo
	${MAKE} sdk_S
	${MAKE} new
	${MAKE} all

rebuild_3821_single:
	${MAKE} path
	${MAKE} config_3821_single
	${MAKE} sdk
	${MAKE} new
	${MAKE} all

rebuild_3503_stby_c:
	${MAKE} path
	${MAKE} config_3503_stby_c
	${MAKE} sdk
	${MAKE} new
	${MAKE} all	

rebuild_3503_S:
	${MAKE} path
	${MAKE} see_3503
	${MAKE} config_3503_S
	${MAKE} sdk_S
	${MAKE} new
	${MAKE} all

rebuild_m3516:
	${MAKE} path
	${MAKE} usee_3503
	${MAKE} config_m3516
	${MAKE} sdk
	${MAKE} new
	${MAKE} all

rebuild_m3516_nandonly:
	${MAKE} path
	${MAKE} usee_3503		
	${MAKE} config_m3516_nandonly
	${MAKE} sdk
	${MAKE} new
	${MAKE} all
	
rebuild_m3516_nandonly_mp:
	${MAKE} path
	${MAKE} config_m3516_nandonly_mp
	${MAKE} sdk
	${MAKE} new
	${MAKE} all
	
rebuild_m3515:
	${MAKE} path
	${MAKE} see_m3515
	${MAKE} config_m3515
	${MAKE} sdk_S
	${MAKE} new
	${MAKE} all	
	
rebuild_m3715:
	${MAKE} path
	${MAKE} usee_3715
	${MAKE} see_m3715
	${MAKE} config_m3715
	${MAKE} sdk_S
	${MAKE} new
	${MAKE} all

rebuild_m3715_nandonly:
	${MAKE} path
	${MAKE} usee_3715
	${MAKE} see_m3715
	${MAKE} config_m3715_nandonly
	${MAKE} sdk_S
	${MAKE} new
	${MAKE} all

path:	
	./getpath.sh

config_3503: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
	sed -e 's/#_BOARD_DB_M3511_01V01_ = 1/_BOARD_DB_M3511_01V01_ = 1/' \
		> ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_3503_logo: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
	sed -e 's/#_BOARD_DB_M3511_01V01_ = 1/_BOARD_DB_M3511_01V01_ = 1/' | \
	sed -e 's/#BOOT_OS = 1/BOOT_OS = 1/' | \
	sed -e 's/#_BOOT_LOGO_ = 1/_BOOT_LOGO_ = 1/' \
		> ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_3503_single: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
	sed -e 's/#_BOARD_DB_M3511_01V01_ = 1/_BOARD_DB_M3511_01V01_ = 1/' | \
	sed -e 's/DUAL_CPU = 1/#DUAL_CPU = 1/' \
		> ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_3821: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
	sed -e 's/#_BOARD_DB_M3822_01V01_ = 1/_BOARD_DB_M3822_01V01_ = 1/' \
		> ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_3821_logo: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
	sed -e 's/#_BOARD_DB_M3822_01V01_ = 1/_BOARD_DB_M3822_01V01_ = 1/' | \
	sed -e 's/#BOOT_OS = 1/BOOT_OS = 1/' | \
	sed -e 's/#_BOOT_LOGO_ = 1/_BOOT_LOGO_ = 1/' \
		> ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_3821_single: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
	sed -e 's/#_BOARD_DB_M3822_01V01_ = 1/_BOARD_DB_M3822_01V01_ = 1/' | \
	sed -e 's/DUAL_CPU = 1/#DUAL_CPU = 1/' \
		> ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def
	
config_3503_stby_c:config_3503
	echo -e "\n_STANDBY_C_CODE_ = 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D__STANDBY_C_CODE_" >> ${ROOT}/src/compiler.def   

config_m3516: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
		cat ${ROOT}/src/compiler_tmp.def | \
		sed -e 's/#_LINUX_BOOTLOADER_ = 1/_LINUX_BOOTLOADER_ = 1/' \
	    > ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_m3516_nandonly: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
		cat ${ROOT}/src/compiler_tmp.def | \
		sed -e 's/#_LINUX_BOOTLOADER_ = 1/_LINUX_BOOTLOADER_ = 1/' | \
		sed -e 's/#_NAND_BOOT_E_ = 1/_NAND_BOOT_E_ = 1/' \
	    > ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def
	
config_m3516_nandonly_mp: sys_config.h sys_memmap.h compiler.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler.def ${ROOT}/src/compiler_tmp.def
		cat ${ROOT}/src/compiler.def | \
		sed -e 's/#_LINUX_BOOTLOADER_ = 1/_LINUX_BOOTLOADER_ = 1/' | \
		sed -e 's/#_NAND_BOOT_E_ = 1/_NAND_BOOT_E_ = 1/' | \
		sed -e 's/#_MPLOADER_ENABLE_ = 1/_MPLOADER_ENABLE_ = 1/' \
	    > ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_3503_S: sys_config.h sys_memmap.h compiler_security.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler_security.def ${ROOT}/src/compiler.def

config_m3515: sys_config.h sys_memmap.h compiler_security.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler_security.def ${ROOT}/src/compiler.def	

config_m3715: sys_config.h sys_memmap.h compiler_security.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler_security.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
		sed -e 's/#_LINUX_BOOTLOADER_ = 1/_LINUX_BOOTLOADER_ = 1/' \
	    > ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

config_m3715_nandonly: sys_config.h sys_memmap.h compiler_security.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config.h ${ROOT}/inc/sys_config.h
	cp -f sys_memmap.h ${ROOT}/inc/sys_memmap.h
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler_security.def ${ROOT}/src/compiler_tmp.def
	cat ${ROOT}/src/compiler_tmp.def | \
		sed -e 's/#_LINUX_BOOTLOADER_ = 1/_LINUX_BOOTLOADER_ = 1/' | \
		sed -e 's/#_NAND_BOOT_E_ = 1/_NAND_BOOT_E_ = 1/' \
	    > ${ROOT}/src/compiler.def
	rm -f ${ROOT}/src/compiler_tmp.def

clean :
	${MAKE} -f Makefile.cmd clean

new :
	${MAKE} -f Makefile.cmd new

release :
	${MAKE} -f Makefile.cmd release

	
# Link file
link :
	${LD} ${LDFLAGS} ${NEED} -o ${OUT}.out -Map ${OUT}.map \
	  -T lscript.ld libslot.a  -lbl libboot.a -lbl ${LIB} libstandby.a lib7zip.a libmlzo.a liblog.a -lc -lgcc -le
	${OBJCOPY} -O binary ${OUT}.out ${OUT}.abs
ifdef _HW_SECURITY_ENABLE_		
ifndef _C0300A_CA_ENABLE_
ifndef _C0300A_CA_STD_ENABLE_
	mv ${OUT}.abs ${OUT}.bak
	cd ../prj/tools; \
	./code_build.exe ../../obj/${OUT}.map ../../obj/${OUT}.bak ../../obj/${OUT}.abs; 
endif	
endif	
endif	
	./bmerger.exe ${OUT}.abs boot.cfg 128 384
	${OBJDUMP} -D ${OUT}.out > ${OUT}.dis
  
# Link file
see_link :
	${LD} ${LDFLAGS} -o ${SEE_OUT}.out -Map ${SEE_OUT}.map \
	  -T see_ldscript.ld ${LIB} libblsee.a liblog.a\
	    -lm -lgcc -lc -le
	${OBJCOPY} -O binary ${SEE_OUT}.out ${SEE_OUT}.abs
ifdef _HW_SECURITY_ENABLE_	
ifndef _C0300A_CA_ENABLE_	
ifndef _C0300A_CA_STD_ENABLE_
	mv ${SEE_OUT}.abs ${SEE_OUT}.bak
	cd ../prj/tools; \
	./code_build.exe ../../obj/${SEE_OUT}.map ../../obj/${SEE_OUT}.bak ../../obj/${SEE_OUT}.abs;
endif
endif
endif
	${OBJCOPY} -I binary  -B mips -O elf32-tradlittlemips ${SEE_OUT}.abs ${SEE_OUT}.o	

usee_link :
	${LD} ${LDFLAGS} -o ${USEE_OUT}.out -Map ${USEE_OUT}.map \
	  -T see_ldscript.ld ${LIB} libblsee.a liblog.a\
	    -lm -lgcc -lc -le
	${OBJCOPY} -O binary ${USEE_OUT}.out ${USEE_OUT}.abs
ifdef _HW_SECURITY_ENABLE_	
	mv ${USEE_OUT}.abs ${USEE_OUT}.bak
	cd ../prj/tools; \
	./code_build.exe ../../obj/${USEE_OUT}.map ../../obj/${USEE_OUT}.bak ../../obj/${USEE_OUT}.abs;				
	../${DDK_PRJ_DIR}/${CA_AP_DIR}/redemo.exe -S ${USEE_OUT}.abs ${USEE_OUT}_sig.abs ../${DDK_PRJ_DIR}/${CA_AP_DIR}/uboot_pair.key ../${DDK_PRJ_DIR}/${CA_AP_DIR}/ejtag.bin
	../${DDK_PRJ_DIR}/${CA_AP_DIR}/lo_tool.exe -MegSig ${USEE_OUT}.abs ${USEE_OUT}_sig.abs
endif	
	${OBJCOPY} -I binary  -B mips -O elf32-tradlittlemips ${USEE_OUT}.abs ${USEE_OUT}.o

see_sig:
	cd ../${CA_AP_DIR}; \
	./pre_build_sig_bl_see.bat
	
	
cleanld :
	rm -f ${OUT}.out ${OUT}.map ${OUT}.dis libbl.a

sdk:
	cd ${ROOT}/src/boot; \
	${MAKE} rebuild_35 ;

sdk_S:
	cd ${ROOT}/src/boot; \
	${MAKE} rebuild_35_security ;

sdk_rel:
	${MAKE} -f Makefile.cmd sdk_rel

see_3503:
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cd ${ROOT}/src/boot/see36f; \
	${MAKE} config_3503; ${MAKE} see_new; ${MAKE} see 
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h

usee_3503:
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cd ${ROOT}/src/boot/see36f; \
	${MAKE} config_3503; ${MAKE} see_new; ${MAKE} see 
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h
	${MAKE} -f Makefile.cmd usee_all

see_m3515:
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cd ${ROOT}/src/boot/see36f; \
	${MAKE} config_m3515; ${MAKE} see_new; ${MAKE} see 
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h

see_m3715:
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cd ${ROOT}/src/boot/see36f; \
	${MAKE} config_m3715; ${MAKE} see_new; ${MAKE} see 
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h

usee_3715:
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cd ${ROOT}/src/boot/see36f; \
	${MAKE} config_usee_m3715; ${MAKE} see_new; ${MAKE} see 
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h
	${MAKE} -f Makefile.cmd usee_all

dis:
	sde-objdump -D ${OUT}.out > ${OUT}.dis
expand.o: expand.c \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_memmap.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/retcode.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hal/machine.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/asm/chip.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/erom/erom.h
boot_system_data.o: boot_system_data.c boot_system_data.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_memmap.h \
  bootloader.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/retcode.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hal/machine.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/asm/chip.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/string.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/erom/erom.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/flash/flash.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/sci/sci.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hal/hal_mem.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/smc/smc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libloader/ld_boot_info.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libpub/lib_frontend.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/p_search.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libsi/si_config.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/sec_pmt.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/sec_sdt.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/db_3l.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/db_3l_T.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/dsc/dsc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/nand/ali_nand.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/pan/pan.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/pan/pan_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/boot/boot_common.h
boot_init.o: boot_init.c bootloader.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_memmap.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/retcode.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hal/machine.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/asm/chip.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/string.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/erom/erom.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/flash/flash.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/sci/sci.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hal/hal_mem.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/smc/smc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libloader/ld_boot_info.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libpub/lib_frontend.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/p_search.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libsi/si_config.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/sec_pmt.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/sec_sdt.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/db_3l.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/db_3l_T.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/dsc/dsc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/nand/ali_nand.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/pan/pan.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/pan/pan_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/boot/boot_common.h
bootloader.o: bootloader.c bootloader.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_memmap.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/retcode.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hal/machine.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/asm/chip.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libc/string.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/erom/erom.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/flash/flash.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/sci/sci.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hal/hal_mem.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/smc/smc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libloader/ld_boot_info.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libpub/lib_frontend.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/p_search.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libsi/si_config.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/sec_pmt.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/sec_sdt.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/db_3l.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/api/libtsi/db_3l_T.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/dsc/dsc.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/bus/nand/ali_nand.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/pan/pan.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/hld/pan/pan_dev.h \
  /cygdrive/f/Cstm_proj/se-tree/se-tree0625/Elephant/inc/boot/boot_common.h
