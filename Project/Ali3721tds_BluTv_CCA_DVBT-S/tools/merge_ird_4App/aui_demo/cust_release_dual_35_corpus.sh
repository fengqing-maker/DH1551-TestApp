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

SILIENT="-s"
RELEASE_DATE=$(date +%y%m%d)
echo "buid sdk at" $RELEASE_DATE

make ${SILIENT}  path
echo "Unify Rel:" ${PWD}
echo "Unify Rel: delete ddk_release_combo_35 directory"

rm -rf ../../../../../../ddk_release_nestor_M35
rm -rf ../../../../../../ddk_release

mkdir ../../../../../../ddk_release

cp -f compiler_3503.def compiler_3503_bak.def

cp -f ../../../../../ddk/genlist ../../../../../ddk/genlist.bak
cp -f ../../../../../ddk/genlistLinux ../../../../../ddk/genlist

#here should compile again
FILE_COMPILE_3503="compiler_3503.def"
RM_CH="#"
ENABLE_COMPILE=("_BOARD_M3515_01V01_")
Enable_Macro_Func "${FILE_COMPILE_3503}" "${ENABLE_COMPILE[*]}" "${RM_CH}"
DISABLE_COMPILE=("_CAS9_CA_ENABLE_" "_ENABLE_ALI_DEMO_SBPSIGN_DEBUG_" "_ENABLE_ALI_DEMO_KEY_DEBUG_")
Disable_Macro_Func "${FILE_COMPILE_3503}" "${DISABLE_COMPILE[*]}" "${RM_CH}"

echo "start compile: 3503"

#combo 3503 library & sdk_rel
cd ../../../../../
cd src/see/m36f
pwd
dos2unix *.sh
echo "Unify Rel: generate libcore(SEE) for combo M3503(make ${SILIENT}  path config new make ${SILIENT} )"
make ${SILIENT}  path 
make ${SILIENT}  config_3503 
make ${SILIENT}  new
make ${SILIENT} 

ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"
	exit 1
fi

cd ../../../
cd prj/app/demo/combo/aui_demo
pwd

echo "Unify Rel: generate libcore(CPU) for combo M3503(make ${SILIENT}  path config_3503 new sdk_clean sdk)"
make ${SILIENT}  path
make ${SILIENT}  config_3503
make ${SILIENT}  new 
make ${SILIENT}  sdk_clean
make ${SILIENT}  sdk

ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"
	exit 1
fi

#cp -f compiler_3503_bak.def compiler_3503.def

echo "Unify Rel: release for combo 3503 (make ${SILIENT}  -f Makefile35.cmd sdk_rel)"
make ${SILIENT}  -f Makefile35.cmd sdk_rel_35
make ${SILIENT}  -f Makefile35.cmd corpus_rel

echo "Unify Rel: 3503 plug in release"
make ${SILIENT}  -f Makefile35.cmd plugin_rel
mv ../../../../../../plugin_combo/ddk/plugin/* ../../../../../../ddk_release/ddk/plugin/
mv ../../../../../../plugin_combo/ddk/plugin_ext/* ../../../../../../ddk_release/ddk/plugin_ext/


mv ../../../../../../ddk_release ../../../../../../ddk_release_nestor_M35
echo "Unify Rel: ddk_release_nestor_M35 finished"

rm -rf ../../../../../../plugin_combo


cp -f ../../../../../ddk/genlist.bak ../../../../../ddk/genlist

echo "all finished"
