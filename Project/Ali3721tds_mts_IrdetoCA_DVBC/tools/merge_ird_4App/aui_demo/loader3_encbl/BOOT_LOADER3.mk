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
ROOT_PRJ = ../prj/app/demo/combo/sabbat_dual

# output file name
OUT = bloader3
SEE_OUT = see_bloader3

all :
	${MAKE} release
	${MAKE} -f Makefile.cmd all
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h

rebuild_3281 :	
	${MAKE} see
	${MAKE} config_3281
	${MAKE} sdk
	${MAKE} new
	${MAKE} all
		
rebuild_3281_32M :	
	${MAKE} see
	${MAKE} config_3281
	${MAKE} config_32M
	${MAKE} sdk
	${MAKE} new
	${MAKE} all		
	
rebuild_3281_encbl :	
	${MAKE} see
	${MAKE} config_3281
	${MAKE} config_encbl
	${MAKE} sdk
	${MAKE} new
	${MAKE} all			

rebuild_3281_encbl_32M :	
	${MAKE} see
	${MAKE} config_3281
	${MAKE} config_encbl
	${MAKE} config_32M
	${MAKE} sdk
	${MAKE} new
	${MAKE} all		

rebuild_3281_demo :	
	${MAKE} see
	${MAKE} config_3281_demo
	${MAKE} sdk
	${MAKE} new
	${MAKE} all
		
rebuild_3281_32M_demo :	
	${MAKE} see
	${MAKE} config_3281_demo
	${MAKE} config_32M
	${MAKE} sdk
	${MAKE} new
	${MAKE} all		
	
rebuild_3281_encbl_demo :	
	${MAKE} see
	${MAKE} config_3281_demo
	${MAKE} config_encbl
	${MAKE} sdk
	${MAKE} new
	${MAKE} all			

rebuild_3281_encbl_32M_demo :	
	${MAKE} see
	${MAKE} config_3281_demo
	${MAKE} config_encbl
	${MAKE} config_32M
	${MAKE} sdk
	${MAKE} new
	${MAKE} all		

rebuild_3281_32M_demo_logo:
	${MAKE} see_with_logo
	${MAKE} config_3281_demo_logo
	${MAKE} config_32M
	${MAKE} sdk
	${MAKE} new
	${MAKE} all	
	
rebuild_3281_vsc_demo_logo:
	${MAKE} see_with_logo
	${MAKE} config_3281_demo_logo
	${MAKE} config_vsc
	${MAKE} sdk
	${MAKE} new
	${MAKE} all	
	
rebuild_3281_32M_vsc_demo_logo:
	${MAKE} see_with_logo
	${MAKE} config_3281_demo_logo
	${MAKE} config_32M
	${MAKE} config_vsc
	${MAKE} sdk
	${MAKE} new
	${MAKE} all		
		
rebuild_3281_32M_demo_solution3 :	
	${MAKE} see
	${MAKE} config_3281_demo
	${MAKE} config_32M
	${MAKE} config_solution3
	${MAKE} sdk
	${MAKE} new
	${MAKE} all		

rebuild_3281_encbl_32M_demo_solution3 :	
	${MAKE} see
	${MAKE} config_3281_demo
	${MAKE} config_encbl
	${MAKE} config_32M
	${MAKE} config_solution3
	${MAKE} sdk
	${MAKE} new
	${MAKE} all		
	
path:	
	./getpath.sh
	

config: sys_config_3281.h compiler_3281.def 
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f modules.h ${ROOT}/inc
	cp -f sys_config_3281.h ${ROOT}/inc/sys_config.h   
	cp -f sys_parameters.h ${ROOT}/inc
	cp -f compiler_3281.def ${ROOT}/src/compiler.def
	
config_3281: config  
	echo -e "\n_BOARD_DB_M3281_01V01_ = 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D_BOARD_DB_M3281_01V01_" >> ${ROOT}/src/compiler.def		

config_32M: 
	echo -e "\n_USE_32M_MEM_ = 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D_USE_32M_MEM_" >> ${ROOT}/src/compiler.def
	
config_vsc: 
	echo -e "\n_CAS9_VSC_ENABLE_= 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D_CAS9_VSC_ENABLE_" >> ${ROOT}/src/compiler.def

config_solution3: 
	echo -e "\n_M3281_SOLUTION3_SUPPORT_ = 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D_M3281_SOLUTION3_SUPPORT_" >> ${ROOT}/src/compiler.def

config_encbl:
	echo -e "\n_ENABLE_BL_ENCRYPTED_ = 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D_ENABLE_BL_ENCRYPTED_" >> ${ROOT}/src/compiler.def
	
config_3281_demo: config
	echo -e "\n_BOARD_DEMO_M3281_01V01_ = 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D_BOARD_DEMO_M3281_01V01_" >> ${ROOT}/src/compiler.def	

config_3281_demo_logo:sys_config_3281.h compiler_3281_logo.def
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cp -f ./modules_logo.h	${ROOT}/inc/modules.h
	cp -f ./sys_config_3281.h ${ROOT}/inc/sys_config.h   
	cp -f ./sys_parameters.h ${ROOT}/inc
	cp -f ./compiler_3281_logo.def ${ROOT}/src/compiler.def
	echo -e "\n_BOARD_DEMO_M3281_01V01_ = 1" >> ${ROOT}/src/compiler.def
	echo "DEFS += -D_BOARD_DEMO_M3281_01V01_" >> ${ROOT}/src/compiler.def	

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
	mv ${OUT}.abs ${OUT}.bak
	cd ../prj/tools; \
	./code_build.exe ../../obj/${OUT}.map ../../obj/${OUT}.bak ../../obj/${OUT}.abs;
	./bmerger.exe ${OUT}.abs boot.cfg 128 384
	${OBJDUMP} -D ${OUT}.out > ${OUT}.dis
  
# Link file
see_link :
	${LD} ${LDFLAGS} -o ${SEE_OUT}.out -Map ${SEE_OUT}.map \
	  -T see_ldscript.ld ${LIB} libblsee.a liblog.a\
	    -lm -lgcc -lc -le
	${OBJCOPY} -O binary ${SEE_OUT}.out ${SEE_OUT}.abs
	mv ${SEE_OUT}.abs ${SEE_OUT}.bak
	cd ../prj/tools; \
	./code_build.exe ../../obj/${SEE_OUT}.map ../../obj/${SEE_OUT}.bak ../../obj/${SEE_OUT}.abs;
	${OBJCOPY} -I binary  -B mips -O elf32-tradlittlemips ${SEE_OUT}.abs ${SEE_OUT}.o	
	

cleanld :
	rm -f ${OUT}.out ${OUT}.map ${OUT}.dis libbl.a

sdk:
	cd ${ROOT}/src/boot; \
	${MAKE} rebuild_encrypted_bl ;
	
see_with_logo:
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cd ${ROOT}/src/boot/see36f; \
	cp -fr ./compiler_3281.def ./compiler_3281_temp.def; \
	${MAKE} config_3281_logo; ${MAKE} see_new; ${MAKE} see; \
	cp -fr ./compiler_3281_temp.def ./compiler_3281.def
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h
see:
	cp -f ${ROOT}/inc/modules.h ${ROOT}/inc/modules_temp.h
	cp -f ${ROOT}/inc/sys_parameters.h ${ROOT}/inc/sys_parameters_temp.h
	cd ${ROOT}/src/boot/see36f; \
	${MAKE} config_3281; ${MAKE} see_new; ${MAKE} see 
	cp -f ${ROOT}/inc/modules_temp.h ${ROOT}/inc/modules.h
	cp -f ${ROOT}/inc/sys_parameters_temp.h ${ROOT}/inc/sys_parameters.h


dis:
	sde-objdump -D ${OUT}.out > ${OUT}.dis
expand.o: expand.c /cygdrive/f/Cstm_proj/qt_release/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/retcode.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/itron.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/alitypes.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/platform.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/asm/chip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/machine.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/erom/erom.h
boot_system_data.o: boot_system_data.c \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/retcode.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/itron.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/alitypes.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/platform.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/asm/chip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/machine.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/string.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/erom/erom.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/sci/sci.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/flash/flash.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_gpio.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_mem.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libloader/ld_boot_info.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libpub/lib_frontend.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/p_search.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libsi/si_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_pmt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_sdt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l_T.h \
  boot_system_data.h bootloader.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/fast_crc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/smc/smc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/i2c/i2c.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/otp/otp.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/flash_cipher.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/dsc/dsc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/rsa_verify.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libzip/gnuzip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/crypto/crypto.h
boot_showlogo.o: boot_showlogo.c \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/retcode.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/itron.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/alitypes.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/platform.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/asm/chip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/machine.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/string.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/erom/erom.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/sci/sci.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/flash/flash.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_gpio.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_mem.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/smc/smc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/i2c/i2c.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/otp/otp.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libloader/ld_boot_info.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libpub/lib_frontend.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/p_search.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libsi/si_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_pmt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_sdt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l_T.h bootloader.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/fast_crc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/flash_cipher.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/dsc/dsc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/rsa_verify.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libzip/gnuzip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/crypto/crypto.h
boot_init.o: boot_init.c \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/retcode.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/itron.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/alitypes.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/platform.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/asm/chip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/machine.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/string.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/erom/erom.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/sci/sci.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/flash/flash.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_gpio.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_mem.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/smc/smc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/i2c/i2c.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/otp/otp.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libloader/ld_boot_info.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libpub/lib_frontend.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/p_search.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libsi/si_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_pmt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_sdt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l_T.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/flash_cipher.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/dsc/dsc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/rsa_verify.h \
  bootloader.h /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/fast_crc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libzip/gnuzip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/crypto/crypto.h
bootloader.o: bootloader.c bootloader.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_define.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/sys_parameters.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/retcode.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/basic_types.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_base.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/itron.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/alitypes.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/platform.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/os/tds2/config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/asm/chip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/alloc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_task.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_int.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_timer.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_msgq.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_sema.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_flag.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mm.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_cache.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_mutex.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/osal/osal_dual.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/machine.h \
  /mips-sde/bin/../lib/gcc/sde/3.4.4/include/stdarg.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/debug_printf.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/string.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libc/fast_crc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libchunk/chunk.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/sto/sto_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/hld_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/erom/erom.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/sci/sci.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/flash/flash.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_gpio.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hal/hal_mem.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan_dev.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/smc/smc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/pan/pan.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/i2c/i2c.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/bus/otp/otp.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libloader/ld_boot_info.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libpub/lib_frontend.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/p_search.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libsi/si_config.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_pmt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/sec_sdt.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libtsi/db_3l_T.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/flash_cipher.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/dsc/dsc.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/librsa/rsa_verify.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/api/libzip/gnuzip.h \
  /cygdrive/f/Cstm_proj/qt_release/inc/hld/crypto/crypto.h
