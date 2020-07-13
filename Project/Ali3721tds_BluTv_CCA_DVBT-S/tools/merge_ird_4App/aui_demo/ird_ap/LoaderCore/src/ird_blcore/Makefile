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
ROOT = ../../../../../../../../../
OBJ = obj/
# Module Name
BS_MOD = IRD_LOADERCORE_BS
BL_MOD = IRD_LOADERCORE_BL
APP_MOD = IRD_LOADERCORE_APP

include ${ROOT}/src/path.def
include ${ROOT}/src/compiler.def
CFLAGS += -I${ROOT}/prj/app/demo/combo/aui_demo/ird_ap/LoaderCore/inc/spi
CFLAGS += -I ./Src/BootLoader
CFLAGS += -I ./Src/Shared

BS_HEADER = Include/ExportAPI/LoaderCoreAPI_ApplicationHelper.h \
						Include/ExportAPI/LoaderCoreAPI.h \
						Include/LoaderCore_Types.h
						
# List of source files
BS_SRCS =  	Src/Shared/Bbcb.c \
			Src/Shared/Bit.c \
			Src/Shared/Crc.c \
			Src/Shared/ErrorReport.c \
			Src/Shared/KeyUpdate.c \
			Src/Shared/LedDisplay.c	 \
			Src/Shared/LoaderPartition.c \
			Src/Shared/ModuleManager.c \
			Src/Shared/Pkcs.c \
			Src/Shared/RsaPss.c \
			Src/Shared/Sha1.c \
			Src/Shared/Sha256.c \
			Src/Shared/UartInterface.c \
			Src/Shared/VbCipher.c \

BL_SRCS = 	Src/Shared/Bbcb.c \
			Src/Shared/Bit.c \
			Src/Shared/Crc.c \
			Src/Shared/ErrorReport.c \
			Src/Shared/KeyUpdate.c \
			Src/Shared/LedDisplay.c \
			Src/Shared/LoaderPartition.c \
			Src/Shared/ModuleManager.c \
			Src/Shared/Pkcs.c \
			Src/Shared/RsaPss.c \
			Src/Shared/Sha1.c \
			Src/Shared/Sha256.c \
			Src/Shared/UartInterface.c \
			Src/Shared/VbCipher.c \
			Src/BootLoader/Aes.c \
			Src/BootLoader/AesTable.c \
			Src/BootLoader/Bootloader.c \
			Src/BootLoader/Decompression.c \
			Src/BootLoader/DemuxManager.c \
			Src/BootLoader/Dvb/Carousel.c \
			Src/BootLoader/List.c \
			Src/BootLoader/Utilization.c

APP_SRCS =      Src/Shared/Bbcb.c \
			Src/Shared/Bit.c \
			Src/Shared/Crc.c \
			Src/Shared/ErrorReport.c \
			Src/Shared/KeyUpdate.c \
			Src/Shared/LedDisplay.c \
			Src/Shared/LoaderPartition.c \
			Src/Shared/ModuleManager.c \
			Src/Shared/Pkcs.c \
			Src/Shared/RsaPss.c \
			Src/Shared/Sha1.c \
			Src/Shared/Sha256.c \
			Src/Shared/UartInterface.c \
			Src/Shared/VbCipher.c \
			Src/Application/CommonApi.c \
			Src/Application/IrdEmm.c \
			Src/Application/Psi.c
										
# List of library files
LIBS = ./obj
D_BS_OUT = libird_blcore_bs.so
S_BS_OUT = libird_blcore_bs.a
D_BL_OUT = libird_blcore_bl.so
S_BL_OUT = libird_blcore_bl.a
D_APP_OUT = libird_blcore_app.so
S_APP_OUT = libird_blcore_app.a

# Following lines are the common description for all projects.
# Do NOT modify anything, unless you know what you are doing.

BS_OBJS =  ${BS_SRCS:.c=.o}
BL_OBJS =  ${BL_SRCS:.c=.o}
APP_OBJS =  ${APP_SRCS:.c=.o}
SMOD_ = ${SMOD:=_}

all :${BS_OBJS} ${BL_OBJS} ${APP_OBJS}
#	${CC} -fPIC ${CFLAGS} -laui -ludi_spi -shared  ${BS_OBJS} -o ${D_BS_OUT}
	${AR} -r ${S_BS_OUT} ${BS_OBJS}
	cp ${S_BS_OUT} ${ROOT}ddk -f
	cp ${S_BS_OUT} ${ROOT}obj -f
# ${CC} -fPIC ${CFLAGS} -laui -ludi_spi -shared  ${BL_OBJS} -o ${D_BL_OUT}
	${AR} -r ${S_BL_OUT} ${BL_OBJS}
	cp ${S_BL_OUT} ${ROOT}ddk -f
	cp ${S_BL_OUT} ${ROOT}obj -f
#	cp ./Include/ExportAPI/*.h ${ROOT}/inc/ird/spi/ -f
	${AR} -r ${S_APP_OUT} ${APP_OBJS}
	cp ${S_APP_OUT} ${ROOT}ddk -f
	cp ${S_APP_OUT} ${ROOT}obj -f
%.o:%.c
	$(CC)  ${CFLAGS} -o $@ -c $<
	
clean : ${SMOD_}
	  rm -f ${BL_OBJS} ${BL_MOD}.mk ${BS_OBJS} ${BS_MOD}.mk ${APP_OBJS} ${APP_MOD}.mk
	  cd ${LIB_DIR}; \
	  echo rm -f \\ > rm.sh; \
	  cat ${BS_MOD}.lst ${BL_MOD}.lst ${APP_MOD}.lst>> rm.sh; \
	  sh < rm.sh; \
	  rm -f rm.sh ${BS_MOD}.lst
	  
ddk_rel :
	${CC} ${CFLAGS} -M ${ASMS} ${BL_SRCS} ${BS_SRCS} ${BS_HEADER}> dep.txt
	${DDK_DIR}/genlist dep.txt "${BASE_DIR}" "${BASE_DIR}/../ddk_release" "${BASE_DIR}/../ddk_release" "${BASE_DIR}/../ddk_release" 1>file.txt 2>dir.txt
	mkdir -p ${BASE_DIR}/../ddk_release/src/udi/ird/ird_blcore/Src/Shared
	mkdir -p ${BASE_DIR}/../ddk_release/src/udi/ird/ird_blcore/Src/Application
	mkdir -p ${BASE_DIR}/../ddk_release/src/udi/ird/ird_blcore/Src/BootLoader/Dvb
#	mkdir -p ${BASE_DIR}/../ddk_release/src/udi/ird/ird_blcore/Include/ExportAPI
	sh dir.txt
	sh file.txt
	rm -f dep.txt
	rm -f dir.txt
	rm -f file.txt			  
	
rebuild: clean all
# End of common description.

# Construct of sub-modules

# Deconstruct of sub-modules
