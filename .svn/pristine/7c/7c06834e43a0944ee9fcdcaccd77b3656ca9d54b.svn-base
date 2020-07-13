
include $(TRUNK_HOME)/Build/$(PLATFORM)/defs.mak
include $(TRUNK_HOME)/Build/$(PLATFORM)/inc.mak

module_name := UI

module_lib := lib$(module_name).a

CURRENT_PATH = $(shell pwd)

CFLAGS += -D$(PLATFORM)

INC_LOCAL += -I$(TRUNK_HOME)/Include/Common      \
			 -I$(TRUNK_HOME)/Include/CA \
			 -I$(TRUNK_HOME)/Include/CA/Irdeto3  \
			 -I$(TRUNK_HOME)/Include/bootloader  \
			 -I$(TRUNK_HOME)/Include/DTV      \
			 -I$(TRUNK_HOME)/Include/DTV/EPG      \
			 -I$(TRUNK_HOME)/Include/DTV/DataBase      \
			 -I$(TRUNK_HOME)/Include/DTV/Player      \
			 -I$(TRUNK_HOME)/Include/DTV/Search      \
			 -I$(TRUNK_HOME)/Include/DTV/SIPSI	      \
			 -I$(TRUNK_HOME)/Include/DTV/NetworkTime   \
			 -I$(TRUNK_HOME)/Include/DTV/Demultiplexer  \
			 -I$(TRUNK_HOME)/Include/DTV/Tuner   \
			 -I$(TRUNK_HOME)/Include/DTV/SignalIndicator  \
			 -I$(TRUNK_HOME)/Include/DTV/FileListScan   \
			 -I$(TRUNK_HOME)/Include/DTV/PVR \
			 -I$(TRUNK_HOME)/Include/DTV/Timer \
			 -I$(TRUNK_HOME)/Include/FactoryTest \
			 -I$(TRUNK_HOME)/Include/FactoryTest/FactoryConfig \
			 -I$(TRUNK_HOME)/Include/Aura \
			 -I$(TRUNK_HOME)/Include/STBData \
			 -I$(TRUNK_HOME)/Include/Public    \
			 -I$(TRUNK_HOME)/Include/UI    \
			 -I$(TRUNK_HOME)/Include/DTVSupport    \
			 -I$(TRUNK_HOME)/Include/DrawPub    \
			 -I$(TRUNK_HOME)/Include/Decode  \
			 -I$(TRUNK_HOME)/Include/adi    \
			 -I$(CURRENT_PATH)/include/DrawPub	\
			 -I$(CURRENT_PATH)/include/Notify	\
			 -I$(CURRENT_PATH)/include/MainInterface	\
			 -I$(CURRENT_PATH)/include


#resources

ifeq ($(ARTPAL_UI),HD)
UIStyle := HDRC
else ifeq ($(ARTPAL_UI),SD)
UIStyle := SDRC
endif

SRCDIR +=  $(CURRENT_PATH) \
		   $(CURRENT_PATH)/DrawPub \
		   $(CURRENT_PATH)/Notify \
		   $(CURRENT_PATH)/$(UIStyle)
	  
		   
VPATH  := $(SRCDIR)

SOURCES_C := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.c))

SOURCES_CPP := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.cpp))

include $(TRUNK_HOME)/Build/$(PLATFORM)/compile.mak
