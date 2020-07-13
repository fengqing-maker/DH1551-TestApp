#!/bin/bash

if [ "$#" -le "1" ]; then
	if [ "$1" = "sdk" ] ; then
		BUILD_CMD="SDK"
	elif [ "$1" = "linux" ];  then
		BUILD_CMD="LINUX"
	elif [ "$1" = "as_linux" ];  then
		BUILD_CMD="AS_LINUX"
	fi
else 	
	echo "Error input parameter!!!"
fi
BUILD_CMD=${BUILD_CMD:="ALL"}

rm -rf *.abs
#build M3511/M3512 bootloader
BLOADER="M3511/M3512 Bootloader"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_3503
elif [ "$BUILD_CMD" = "SDK" ] ; then
	make config_3503 && make new && all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3503/
mv *.abs ./m3503/
echo "Compiler ${BLOADER} done !"

#build M3511/M3512 single bootloader
BLOADER="M3511/M3512 single Bootloader"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_3503_single
elif [ "$BUILD_CMD" = "SDK" ] ; then
	make config_3503_single && make new && all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3503_single/
mv *.abs ./m3503_single/
echo "Compiler ${BLOADER} done !"


#build M3511/M3512 bootloader with logo
BLOADER="M3511/M3512 Bootloader with logo"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_3503_logo
elif [ "$BUILD_CMD" = "SDK" ] ; then
	make config_3503_logo && make new && all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3503_logo/
mv *.abs ./m3503_logo/
echo "Compiler ${BLOADER} done !"

#build M3821 bootloader
BLOADER="M3821 Bootloader"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_3821
elif [ "$BUILD_CMD" = "SDK" ] ; then
	make config_3821 && make new && all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3821/
mv *.abs ./m3821/
echo "Compiler ${BLOADER} done !"

#build M3821 single bootloader
BLOADER="M3821 single Bootloader"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_3821_single
elif [ "$BUILD_CMD" = "SDK" ] ; then
	make config_3821_single && make new && all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3821_single/
mv *.abs ./m3821_single/
echo "Compiler ${BLOADER} done !"


#build M3821 bootloader with logo
BLOADER="M3821 Bootloader with logo"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_3821_logo
elif [ "$BUILD_CMD" = "SDK" ] ; then
	make config_3821_logo && make new && all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3821_logo/
mv *.abs ./m3821_logo/
echo "Compiler ${BLOADER} done !"


#build M3516 Linux bootloader
if [ "$BUILD_CMD" = "ALL" ] || [ "$BUILD_CMD" = "LINUX" ] ; then
	BLOADER="M3516 Linux Nor Flash Bootloader"
	echo "Begin to compiler ${BLOADER}"
	make rebuild_m3516
	if [ $? != 0 ]; then
		echo "$0 with error[$?]"		
		exit 1
	fi
	mkdir	./m3516_nor/
	mv *.abs ./m3516_nor/
	mv usee_bloader3.lib ./m3516_nor/
	echo "Compiler ${BLOADER} done !"
fi

if [ "$BUILD_CMD" = "ALL" ] || [ "$BUILD_CMD" = "LINUX" ] ; then
	BLOADER="M3516 Linux Nandonly Bootloader"
	echo "Begin to compiler ${BLOADER}"
	make rebuild_m3516_nandonly
	if [ $? != 0 ]; then
		echo "$0 with error[$?]"		
		exit 1
	fi
	mkdir	./m3516_nand/
	mv *.abs ./m3516_nand/
	mv usee_bloader3.lib ./m3516_nand/
	echo "Compiler ${BLOADER} done !"
fi

if [ "$BUILD_CMD" = "ALL" ] || [ "$BUILD_CMD" = "LINUX" ] ; then
	BLOADER="M3516 Linu Nandonly MP Bootloader"
	echo "Begin to compiler ${BLOADER}"
	make rebuild_m3516_nandonly_mp
	if [ $? != 0 ]; then
		echo "$0 with error[$?]"		
		exit 1
	fi
	mkdir	./m3516_mp/
	mv *.abs ./m3516_mp/
	echo "Compiler ${BLOADER} done !"
fi

#build M3515 TDS bootloader
BLOADER="M3515 TDS Clear Bootloader"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_m3515
elif [ "$BUILD_CMD" = "SDK" ] ; then	
	make config_m3515 && make new && make all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3515_clear/
mv *.abs ./m3515_clear/
echo "Compiler ${BLOADER} done !"

BLOADER="M3515 TDS Cipher Bootloader"
echo "Begin to compiler ${BLOADER}"
cp compiler_security.def compiler_security.def.old
gen_expression="sed -e 's/#_ENABLE_BL_ENCRYPTED_ = 1/_ENABLE_BL_ENCRYPTED_ = 1/' compiler_security.def.old"
eval ${gen_expression} > compiler_security.def.new
mv compiler_security.def.new compiler_security.def

if [ "$BUILD_CMD" = "ALL" ] ; then
	make rebuild_m3515
elif [ "$BUILD_CMD" = "SDK" ] ; then	
	make config_m3515 && make new && make all
fi
if [ $? != 0 ]; then
	echo "$0 with error[$?]"		
	exit 1
fi
mkdir	./m3515_cipher/
mv *.abs ./m3515_cipher/
cp compiler_security.def.old compiler_security.def
rm -f compiler_security.def.old compiler_security.def.new
echo "Compiler ${BLOADER} done !"


#build M3515/M3715 Linux bootloader
BLOADER="M3515/M3715 Linux Clear Nor flash Bootloader"
echo "Begin to compiler ${BLOADER}"
if [ "$BUILD_CMD" = "ALL" ] || [ "$BUILD_CMD" = "AS_LINUX" ] ; then
	make rebuild_m3715
	if [ $? != 0 ]; then
		echo "$0 with error[$?]"		
		exit 1
	fi
	echo "Compiler ${BLOADER} done !"	
fi
mkdir	./m3715_clear/
mv *.abs ./m3715_clear/
mv usee_bloader3.lib ./m3715_clear/

cp compiler_security.def compiler_security.def.old
gen_expression="sed -e 's/#_ENABLE_BL_ENCRYPTED_ = 1/_ENABLE_BL_ENCRYPTED_ = 1/' compiler_security.def.old"
eval ${gen_expression} > compiler_security.def.new
mv compiler_security.def.new compiler_security.def

BLOADER="M3515/M3715 Linux Nor flash Cipher Bootloader"
if [ "$BUILD_CMD" = "ALL" ] || [ "$BUILD_CMD" = "AS_LINUX" ] ; then
	make rebuild_m3715
	if [ $? != 0 ]; then
		echo "$0 with error[$?]"		
		exit 1
	fi
	echo "Compiler ${BLOADER} done !"	
fi
mkdir	./m3715_cipher_nor/
mv *.abs ./m3715_cipher_nor/
mv usee_bloader3.lib ./m3715_cipher_nor/

BLOADER="M3515/M3715 Linux Nandonly Cipher Bootloader"

if [ "$BUILD_CMD" = "ALL" ] || [ "$BUILD_CMD" = "AS_LINUX" ] ; then
	make rebuild_m3715_nandonly
	if [ $? != 0 ]; then
		echo "$0 with error[$?]"		
		exit 1
	fi
	echo "Compiler ${BLOADER} done !"
fi
mkdir	./m3715_cipher_nand/
mv *.abs ./m3715_cipher_nand/
mv usee_bloader3.lib ./m3715_cipher_nand/

cp compiler_security.def.old compiler_security.def
rm -f compiler_security.def.old compiler_security.def.new
