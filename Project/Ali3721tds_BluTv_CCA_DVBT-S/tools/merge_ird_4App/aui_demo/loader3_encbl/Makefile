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
ROOT_PRJ = ../prj/app/demo/combo/aui_demo

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
