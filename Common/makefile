
include $(TRUNK_HOME)/Build/$(PLATFORM)/defs.mak
include $(TRUNK_HOME)/Build/$(PLATFORM)/inc.mak

module_name := TestCommon

module_lib := lib$(module_name).a

CURRENT_PATH = $(shell pwd)

INC_LOCAL = -I$(TRUNK_HOME)/Include/adi   \
			-I$(TRUNK_HOME)/Include/Aura  \
			-I$(CURRENT_PATH)/Include


#resources

SRCDIR +=  $(CURRENT_PATH)	\
			$(CURRENT_PATH)/CRC	\
			$(CURRENT_PATH)/Decompress

		   
VPATH  := $(SRCDIR)

SOURCES_C := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.c))

SOURCES_CPP := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.cpp))

include $(TRUNK_HOME)/Build/$(PLATFORM)/compile.mak
