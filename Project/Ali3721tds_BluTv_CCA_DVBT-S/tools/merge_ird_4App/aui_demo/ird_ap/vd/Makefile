#
# -= Makefile for module compile =-
#
# Usage:
# . Name this file as "Makefile";
#   Put it in the same directory as module's source code.
# . Change the ROOT definition, if necessary;
#   Make it point to the root of the software tree.
# . Define the Module Name in MOD as you like;
#   There should be NO duplicated module names in the whole project.
# . List all files want to be compiled in ASMS and/or SRCS;
#   Including files, such as header files, must NOT be listed here.
# . List all library files this module may depends on in LIBS.
# . Give a new name in SMOD, if want to include sub-directories;
#   Write the linkage information at the end of file.
#
                                                                                                                                                                         
# Destination of definition files
ROOT = ../../../../../../..
OBJ = obj/
# Module Name
MOD = IRD_VD

include ${ROOT}/src/path.def
include ${ROOT}/src/compiler.def
CFLAGS += -I${ROOT}/prj/app/demo/combo/aui_demo/ird_ap/vd/include
CFLAGS += -I${ROOT}/prj/app/demo/combo/aui_demo/ird_ap/LoaderCore/inc/spi
CFLAGS += -I${ROOT}/prj/app/demo/combo/aui_demo/ird_ap/LoaderCore/inc/spi/internel

# List of source files
SRCS = 					virtual_driver/s3_ansi_functions.c \
					virtual_driver/s3_vd.c  \
					virtual_driver/s3_vddf.c  \
					virtual_driver/s3_vd_external_storage.c  \
					virtual_driver/s3_vd_loader.c  \
					virtual_driver/s3_vdps.c  \
					virtual_driver/s3_vdsc.c  \
					virtual_driver/s3_vdtmr.c \
					virtual_driver/s3_osdrv.c \
					virtual_driver/s3_vddd.c  \
					virtual_driver/s3_cadrv.c  \
					virtual_driver/ali_vd_drv.c \
					virtual_driver/s3_vd_stream_crypto.c  \
					virtual_driver/encrypt_pvr.c  \
		
					
					
# List of library files
LIBS = ./obj
D_OUT = libird_vd.so
S_OUT = libird_vd.a


# Following lines are the common description for all projects.
# Do NOT modify anything, unless you know what you are doing.

OBJS =  ${SRCS:.c=.o}

SMOD_ = ${SMOD:=_}

all :${OBJS}
#	${CC} -fPIC ${CFLAGS} ${CFLAGS_EXT} ${LDFLAGS} -shared  ${OBJS}  -o ${D_OUT}
#	${AR} -crv ${S_OUT} ${OBJS}
#	${BUILD_TEST_CMD}
	${AR} -r ${S_OUT} ${OBJS}
	cp ${S_OUT} ${ROOT}/ddk -f
	cp ${S_OUT} ${ROOT}/obj -f

%.o:%.c
	${CC} ${CFLAGS} -o $@ -c $<
	
clean : ${SMOD_}
	  rm -f ${OBJS} ${MOD}.mk
	  rm -f ${D_OUT} ${S_OUT}
	  cd ${LIB_DIR}; \
	  echo rm -f \\ > rm.sh; \
	  cat ${MOD}.lst >> rm.sh; \
	  sh < rm.sh; \
	  rm -f rm.sh ${MOD}.lst
	  
rebuild: clean all
# End of common description.

# Construct of sub-modules

# Deconstruct of sub-modules
