
include $(TRUNK_HOME)/Build/$(PLATFORM)/defs.mak
include $(TRUNK_HOME)/Build/$(PLATFORM)/inc.mak
#CC_OPTS += -D$(PLATFORM)
module_name := FactoryTest

module_lib := lib$(module_name).a

CURRENT_PATH = $(shell pwd)
CFLAGS += -D$(PLATFORM)
#Component   
INC_LOCAL += -I$(TRUNK_HOME)/Include/Common      \
			 -I$(TRUNK_HOME)/Include/CA  \
			 -I$(TRUNK_HOME)/Include/CA/CI  \
			 -I$(TRUNK_HOME)/Include/CA/Conax  \
			 -I$(TRUNK_HOME)/Include/Aura  \
			 -I$(TRUNK_HOME)/Include/bootloader  \
			 -I$(TRUNK_HOME)/Include/FactoryTest \
			 -I$(TRUNK_HOME)/Include/FactoryTest/FactoryConfig \
			 -I$(TRUNK_HOME)/Include/STBData \
			 -I$(TRUNK_HOME)/Include/adi    \
			 -I$(TRUNK_HOME)/UI/include   \
			 -I$(TRUNK_HOME)/UI/include/Notify  \
			 -I$(TRUNK_HOME)/UI/include/MainInterface   \
			 -I$(CURRENT_PATH)   		 
			 
SRCDIR +=  $(CURRENT_PATH)     \
		   $(CURRENT_PATH)/AVPlay     \
		   $(CURRENT_PATH)/USB     \
		   $(CURRENT_PATH)/FrontPanel     \
		   $(CURRENT_PATH)/SmartCard     \
		   $(CURRENT_PATH)/Ethernet     \
		   $(CURRENT_PATH)/DataUpgrade      \
		   $(CURRENT_PATH)/AppUpgrade  \
		   $(CURRENT_PATH)/LinkInterface  \
		   $(CURRENT_PATH)/ConfigParse  \
		   $(CURRENT_PATH)/FlashCheck  \
		   $(CURRENT_PATH)/AppUpgrade/$(ARTPAL_CA)
		   
VPATH  := $(SRCDIR)

SOURCES_C := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.c))

SOURCES_CPP := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.cpp))

include $(TRUNK_HOME)/Build/$(PLATFORM)/compile.mak


