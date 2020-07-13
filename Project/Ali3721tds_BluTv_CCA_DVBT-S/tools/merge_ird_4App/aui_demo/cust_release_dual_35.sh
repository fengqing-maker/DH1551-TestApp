#!/bin/bash
####################################################################
# 1. delete old ddk_release package
# 2. build bootloader and generate bootloader code
# 3. generate firmware source code.
#
####################################################################
#==============
Enable_Macro_Func()
{
# $1 :FILE_CONFIG, the file(include path) needed to be modified
# $2 :ENABLE_MACROS, Macros array needed to be opened
# $3 :RM_CH, character need to be delete, e.g. '/', '#'
	FILE_CONFIG=$1
	ENABLE_MACROS=$2
	echo $ENABLE_MACROS  "check"
	RM_CH=$3


	FILE_TMP=$FILE_CONFIG".tmp"
	rm -f $FILE_TMP
	awk -v FILE_NAME="$FILE_CONFIG" -v FTMP="$FILE_TMP" -v ch="$RM_CH" -v siz="$siz" -v ENABLE_MACROS2="${ENABLE_MACROS[*]}" \
			'BEGIN { \
				siz=split(ENABLE_MACROS2, array_enable," "); \
				while(getline < FILE_NAME > 0) { \
					for (k=1; k<=siz; k++) { \
						if (index( $0, array_enable[k] ) > 0 && index( $0, "=" ) > 0 && index( $0, "1" ) > 0) { \
							if(index( $0, "1" ) > 0 ) { \
								gsub( ch, "", $0); \
								print $0 >>FTMP; \
								break; \
							} \
							if ( index( $0, "define" ) > 0) { \
								gsub( ch, "", $0); \
								print $0 >>FTMP; \
								break; \
							} \
						} \
					} \
					if (k==(siz+1))
						print $0 >>FTMP; \
				} \
			}'	
	cp -f $FILE_TMP $FILE_CONFIG
	unix2dos $FILE_CONFIG
}

Disable_Macro_Func()
{
# $1 :FILE_CONFIG, the file(include path) needed to be modified
# $2 :ENABLE_MACROS, Macros array needed to be opened
# $3 :RM_CH, character need to be delete, e.g. '/', '#'
	FILE_CONFIG=$1
	ENABLE_MACROS=$2
	RM_CH=$3


	FILE_TMP=$FILE_CONFIG".tmp"
	rm -f $FILE_TMP
	awk -v FILE_NAME="$FILE_CONFIG" -v FTMP="$FILE_TMP" -v ch="$RM_CH" -v siz="$siz" -v ENABLE_MACROS2="${ENABLE_MACROS[*]}" \
			'BEGIN { \
				siz=split(ENABLE_MACROS2, array_enable," "); \
				while(getline < FILE_NAME > 0) { \
					for (k=1; k<=siz; k++) { \
						if (index( $0, array_enable[k] ) > 0 && index( $0, "=" ) > 0 && index( $0, "DEFS" ) <= 0) { \
							if ( index( $0, "1" ) > 0) { \
								print ch $0 >>FTMP; \
								break; \
							} \
							if ( index( $0, "define" ) > 0) { \
								print ch ch $0 >>FTMP; \
								break; \
							} \
						} \
					} \
					if (k==(siz+1))
						print $0 >>FTMP; \
				} \
			}'	
	cp -f $FILE_TMP $FILE_CONFIG
	unix2dos $FILE_CONFIG
	rm $FILE_TMP
}
#==============


RELEASE_DATE=$(date +%y%m%d)
echo "buid sdk at" $RELEASE_DATE

make path
echo "Unify Rel:" ${PWD}
echo "Unify Rel: delete ddk_release_combo_35 directory"

rm -rf ../../../../../../ddk_release_combo_M35
rm -rf ../../../../../../ddk_release

mkdir ../../../../../../ddk_release

cp -f compiler_3503.def compiler_3503_bak.def

#here should compile again
FILE_COMPILE_3503="compiler_3503.def"
RM_CH="#"
ENABLE_COMPILE=("_BOARD_M3515_01V01_")
Enable_Macro_Func "${FILE_COMPILE_3503}" "${ENABLE_COMPILE[*]}" "${RM_CH}"
DISABLE_COMPILE=("_BOARD_M3511_01V01_")
Disable_Macro_Func "${FILE_COMPILE_3503}" "${DISABLE_COMPILE[*]}" "${RM_CH}"

echo "start compile: 3503"

#combo 3503 library & sdk_rel
cd ../../../../../
cd src/see/m36f
pwd
dos2unix *.sh
echo "Unify Rel: generate libcore(SEE) for combo M3503(make path config new make)"
make path
make config_3503
make new
make

ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"
	exit 1
fi

#echo "Unify Rel: generate libcore(SEE) for combo M3503(make path config_3503 new make)"
#make path
#make config_3503_ota
#make new
#make

#ret=$?
#if [ $ret != 0 ]; then
	#echo "$0 with error[$ret]"
	#exit 1
#fi
cd ../../../
cd prj/app/demo/combo/aui_demo
pwd

#build bootloader
echo "Unify Rel: 3515A FTA bootloader In combo"
cd ./loader3_AS_G2 
cp -f compiler_security.def compiler_security.def.bak

#here should compile again
FILE_COMPILE_3503="compiler_security.def"
RM_CH="#"

make rebuild_3503

ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"
	exit 1
fi

#echo "Unify Rel: release loader3_3515"
#make sdk_rel
#cp -f compiler_security.def.bak compiler_security.def
#rm -f compiler_security.def.bak
#cd ..

#ret=$?
#if [ $ret != 0 ]; then
	#echo "$0 with error[$ret]"
	#exit 1
#fi

#echo "Unify Rel: generate libcore(CPU) for combo M3503(make path config_3503_ota new sdk_clean sdk)"
#make path
#make config_3503_ota
#make new 
#make sdk_clean
#make sdk

#ret=$?
#if [ $ret != 0 ]; then
	#echo "$0 with error[$ret]"
	#exit 1
#fi
cd ..
echo "Unify Rel: generate libcore(CPU) for combo M3503(make path config_3503 new sdk_clean sdk)"
make path
make config_3503
make new 
make sdk_clean
make sdk

ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"
	exit 1
fi

#for dvbc release
#FILE_COMPILE_3503="compiler_3503.def"
#ENABLE_COMPILE=("_DVBC_ENABLE_")
#RM_CH="#"
#Enable_Macro_Func "${FILE_COMPILE_3503}" "${ENABLE_COMPILE[*]}" "${RM_CH}"
make config_3503

#cp -f compiler_3503_bak.def compiler_3503.def

echo "Unify Rel: release for combo 3503 (make -f Makefile35.cmd sdk_rel)"
make -f Makefile35.cmd sdk_rel_35

echo "Unify Rel: 3503 plug in release"
make -f Makefile35.cmd plugin_rel

#echo "Unify Rel: release 3503 cas9_release combo"
#make -f Makefile35.cmd cas9_rel

#echo "Unify Rel: release 3503 cas7_release combo"
#make -f Makefile35.cmd cas7_rel

mkdir -p ../../../../../../ddk_release/aui
cp -rf ../../../../../aui/* ../../../../../../ddk_release/aui
mv ../../../../../../ddk_release ../../../../../../ddk_release_combo_M35
echo "Unify Rel: ddk_release_combo_35 finished"

rm -rf ../../../../../../plugin_combo_M35
mv ../../../../../../plugin_combo ../../../../../../plugin_combo_M35

echo "all finished"
