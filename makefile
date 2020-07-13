CC = $(ARTPAL_CROSS_COMPILE)gcc
CPP = $(ARTPAL_CROSS_COMPILE)g++
AR = $(ARTPAL_CROSS_COMPILE)ar
LD = $(ARTPAL_CROSS_COMPILE)ld
STRIP = $(ARTPAL_CROSS_COMPILE)strip
OBJCOPY = $(ARTPAL_CROSS_COMPILE)objcopy

CC_OPTS = -g -EL -mips32r2 -O1 -msoft-float -fsigned-char -fno-builtin-printf
CC_OPTS += -fno-inline-small-functions -fstack-protector -fstack-protector-all -Wstack-protector -Wall 
CPP_OPTS  += -Wno-sign-compare -Wno-reorder -fpermissive
CC_OPTS += -D$(PLATFORM)

# **********************************************
# Directories
# **********************************************
ROOT        = $(TRUNK_HOME)/Porting/Ali/$(PLATFORM)
BINDIR      = $(TRUNK_HOME)/release2test
BIN_PATH    = $(BINDIR)
OBJDIR      = $(PRO_INCLUDE)/obj
OBJ_PATH    = $(OBJDIR)
CASTPAL_DIR += $(PRO_INCLUDE)/ArtpalMain

IMAGENAME = Sabbat_s3702

SRCDIR     += $(PRO_INCLUDE)/HardWareConfig	\
			  $(PRO_INCLUDE)/FactoryConfig	\
			  $(PRO_INCLUDE)/ArtpalMain

INCDIR     += -I$(TRUNK_HOME)/Include/adi \
			  -I$(TRUNK_HOME)/Include/CA  \
			  -I$(TRUNK_HOME)/Include/Common  \
			  -I$(TRUNK_HOME)/Include/Aura    \
			  -I$(TRUNK_HOME)/Include/bootloader      \
			  -I$(TRUNK_HOME)/Include/CA/Conax    \
			  -I$(TRUNK_HOME)/Include/bootloader   \
			  -I$(TRUNK_HOME)/Include/FactoryTest \
			  -I$(TRUNK_HOME)/Include/FactoryTest/FactoryConfig \
			  -I$(TRUNK_HOME)/Include/STBData	\
			  -I$(TRUNK_HOME)/UI/include    \
			  -I$(TRUNK_HOME)/UI/include/DrawPub	\
			  -I$(TRUNK_HOME)/UI/include/Notify	\
			  -I$(TRUNK_HOME)/UI/include/MainInterface	\
			  -I$(TRUNK_HOME)/Common/Include	\
			  -I/opt/mips-sde-elf-4.7.3/lib/gcc/mips-sde-elf/4.7.3/include \
			  -I/opt/mips-sde-elf-4.7.3/mips-sde-elf/include	


# Search source file path
VPATH       = $(SRCDIR)

SRC_C      += $(foreach dir, $(SRCDIR),       $(wildcard $(dir)/*.c))
SRC         = $(SRC_C)

SRC_CPP      += $(foreach dir, $(SRCDIR),       $(wildcard $(dir)/*.cpp))

OBJ_C_0     = $(notdir $(patsubst %.c, %.o,   $(SRC_C)))
OBJ_C       = $(foreach file, $(OBJ_C_0),     $(OBJ_PATH)/$(file))
OBJ         = $(OBJ_C)

OBJ_CPP_0     = $(notdir $(patsubst %.cpp, %.o,   $(SRC_CPP)))
OBJ_CPP       = $(foreach file, $(OBJ_CPP_0),     $(OBJ_PATH)/$(file))



# **********************************************
# Image file names
# **********************************************
IMAGE_BIN   = $(BIN_PATH)/$(IMAGENAME).abs
IMAGE_ELF   = $(BIN_PATH)/$(IMAGENAME).out
IMAGE_MAP   = $(BIN_PATH)/$(IMAGENAME).map

PLUGIN_PATH = $(PRO_INCLUDE)/lib/linux/$(BUILD_TYPE)/plugin_ext

BSP_LIBS    =  -L$(PRO_INCLUDE)/lib/linux/$(BUILD_TYPE) \
			   $(PRO_INCLUDE)/lib/linux/$(BUILD_TYPE)/libporting.a \
			   $(PRO_INCLUDE)/lib/linux/libCommon.a \
			   $(PRO_INCLUDE)/lib/linux/libUI.a  \
			   $(PRO_INCLUDE)/lib/linux/libthirdparty.a \
			   $(PRO_INCLUDE)/lib/linux/libIrdetoBooterLoaderV51app.a  \
			   $(PRO_INCLUDE)/lib/linux/libSTBData.a \
			   $(PRO_INCLUDE)/lib/linux/libFactoryTest.a \
			   $(PRO_INCLUDE)/lib/linux/libTestCommon.a \
			   $(PRO_INCLUDE)/lib/linux/libaura.a




# **********************************************
# Compiler and linker options
# **********************************************


LD_SCRIPT   = $(PRO_INCLUDE)/lib/linux/$(BUILD_TYPE)/lscript.ld

LD_LIBS     = -L/opt/mips-sde-elf-4.7.3/lib/gcc/mips-sde-elf/4.7.3/el/sof \
			  -L/opt/mips-sde-elf-4.7.3/mips-sde-elf/lib/el/sof 
			  

LD_OPTS     = -g -EL -O1 -defsym __BOOT_FROM_FLASH=0 -defsym __BOOT_LOADER=0

# **********************************************
# Rules
# **********************************************
.PHONY : all clean

all:copylib setup makeImg

copylib:
	cp $(TRUNK_HOME)/FactoryTest/objs/libFactoryTest.a $(PRO_INCLUDE)/lib/linux/ -rf;\
	cp $(TRUNK_HOME)/UI/objs/libUI.a $(PRO_INCLUDE)/lib/linux/ -rf;\
	cd STBData/;make clean;make;\
	cp $(TRUNK_HOME)/STBData/objs/libSTBData.a $(PRO_INCLUDE)/lib/linux/ -rf;\
	cd ../Common/;make clean;make;\
	cp $(TRUNK_HOME)/Common/objs/libTestCommon.a $(PRO_INCLUDE)/lib/linux/ -rf;\
	cd ..;
	
version:
	exportSvnInfo $(TRUNK_HOME) $(CASTPAL_DIR)
	
makeImg : $(IMAGE_ELF) $(IMAGE_BIN)

flash:
	rm -rf $(PRODUCT_HOME)/tools/0_all_flash_for_burn/ali_NoEnc_app.bin
	
	make -C $(PRODUCT_HOME)/tools/merge_ird_4App clean;
	cp $(BIN_PATH)/Sabbat_s3702.map $(PRODUCT_HOME)/tools/merge_ird_4App -rf;
	cp $(BIN_PATH)/Sabbat_s3702.out $(PRODUCT_HOME)/tools/merge_ird_4App -rf;
	make -C $(PRODUCT_HOME)/tools/merge_ird_4App;
	
	cp $(PRODUCT_HOME)/tools/merge_ird_4App/ali_NoEnc_app.bin $(PRODUCT_HOME)/tools/0_all_flash_for_burn/ali_NoEnc_app.bin -rf;
	
	cd $(PRODUCT_HOME)/tools/0_all_flash_for_burn;\
	./MERGE flashmap.ini
	
	cp $(PRODUCT_HOME)/tools/0_all_flash_for_burn/flashwr_c3702.abs $(BIN_PATH)
	cp $(PRODUCT_HOME)/tools/0_all_flash_for_burn/product_sabbat_dual.abs $(BIN_PATH)
	cp $(PRODUCT_HOME)/tools/0_all_flash_for_burn/s3702_sf_burn_sabbat_8m.ini $(BIN_PATH)
	cp $(PRODUCT_HOME)/tools/0_all_flash_for_burn/ali_NoEnc_app.bin $(BIN_PATH)

	cp $(PRODUCT_HOME)/tools/0_all_flash_for_burn/product_sabbat_dual.abs $(PRODUCT_HOME)/tools/4_backdoor/
	cp $(PRODUCT_HOME)/tools/0_all_flash_for_burn/ali_NoEnc_app.bin $(PRODUCT_HOME)/tools/4_backdoor/

	echo $(shell pwd)
	
merge_app_rc:
	cd $(PRODUCT_HOME)/tools/merge/0_all_flash_for_burn;\
	./MERGE merge_app_rc.ini
	echo $(shell pwd)
	cp $(PRODUCT_HOME)/tools/merge/0_all_flash_for_burn/app_rc.bin $(BIN_PATH) -rf;
	
# Project Image Build
$(IMAGE_BIN) : $(IMAGE_ELF)
	$(OBJCOPY) -O binary $(IMAGE_ELF) $(IMAGE_BIN);
	cp -f $(IMAGE_ELF) $(PRODUCT_HOME)/tools/merge_ird_4App/

$(IMAGE_ELF) : $(OBJ_C)  $(OBJ_CPP)
	@echo '  [LD] $@'
	@$(LD) $(LD_OPTS)  $(OBJ_C) $(OBJ_CPP) $(shell ls $(PLUGIN_PATH)/*.o ) -o $(IMAGE_ELF)   -Map $(IMAGE_MAP) -T ${LD_SCRIPT} \
	$(LD_LIBS) 	--start-group  $(BSP_LIBS) -lstdc++ --end-group -lm -lstdc++ -lgcc -lc

# Project Source Build
$(OBJ_C) : $(OBJ_PATH)/%.o : %.c
	@echo '  [CC] $@'
	@$(CC) $(CC_OPTS) $(INCDIR) -c -o $@ $<;

$(OBJ_CPP) : $(OBJ_PATH)/%.o : %.cpp
	@echo '  [CPP] $@'
	@$(CPP) $(CC_OPTS) $(CPP_OPTS) $(INCDIR) -c -o $@ $<;
	
setup:
	@if [ ! -d $(OBJ_PATH) ]; then \
	mkdir $(OBJ_PATH); fi
	@if [ ! -d $(BIN_PATH) ]; then \
	mkdir $(BIN_PATH); fi
	
# Project Clean
clean :
	@echo "Clean $(CHIP) $(PROJNAME) project..."
	@rm -f -r $(OBJ_PATH)
	@rm -f -r $(BIN_PATH)

