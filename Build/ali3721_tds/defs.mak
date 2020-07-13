CC = $(ARTPAL_CROSS_COMPILE)gcc
CPP = $(ARTPAL_CROSS_COMPILE)g++
AR = $(ARTPAL_CROSS_COMPILE)ar
LD = $(ARTPAL_CROSS_COMPILE)ld
STRIP = $(ARTPAL_CROSS_COMPILE)strip

##CFLAGS = -EL -mips32 -mhard-float 
##CFLAGS += -Wall -Wpointer-arith  -Winline -Wundef  
##CFLAGS += -fno-strict-aliasing -fno-optimize-sibling-calls -fno-exceptions
##CFLAGS += -c -G0 
##CFLAGS += -D'IMAGE_TYPE=adi' -D'adi=1' -D'demo=2' -D'lite=3' -D'normal=4'

CFLAGS = -c  -EL -mips2  -msoft-float -fsigned-char -W 
#CFLAGS = -Werror

CC_OPTS  += -fno-builtin -Wstrict-prototypes

CPP_OPTS  += -Wno-sign-compare -Wno-reorder -fpermissive

ifeq ($(BUILD_TYPE),debug)
CFLAGS    += -O1 -g -D_ADI_DEBUG_
else
CFLAGS    += -O1
endif
