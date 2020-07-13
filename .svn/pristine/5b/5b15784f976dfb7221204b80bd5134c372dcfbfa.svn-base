
include $(TRUNK_HOME)/Build/$(PLATFORM)/defs.mak
include $(TRUNK_HOME)/Build/$(PLATFORM)/inc.mak

module_name := STBData

module_lib := lib$(module_name).a

CURRENT_PATH = $(shell pwd)


#Services
INC_LOCAL += -I$(CURRENT_PATH)  \
			-I$(TRUNK_HOME)/Include/Aura    \
			-I$(TRUNK_HOME)/Include/STBData    \
			-I$(TRUNK_HOME)/Include/Common    \
			-I$(TRUNK_HOME)/Common/ \
			-I$(TRUNK_HOME)/UI/include/MainInterface/ \
			-I$(TRUNK_HOME)/Include/STBData \
			-I$(TRUNK_HOME)/Include/adi  
 
			 
SRCDIR +=	$(CURRENT_PATH) 


		   
VPATH  := $(SRCDIR)

SOURCES_C := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.c))

SOURCES_CPP := $(foreach dir, $(SRCDIR), $(wildcard  $(dir)/*.cpp))

include $(TRUNK_HOME)/Build/$(PLATFORM)/compile.mak
