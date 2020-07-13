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
echo "Unify Rel: delete ddk_release_m32 directory"

rm -rf ../../../../../../ddk_release_m32
rm -rf ../../../../../../ddk_release
mkdir ../../../../../../ddk_release

#combo 3281 library & sdk_rel
cd ../../../../../
cd src/see/m36f
pwd
dos2unix *.sh
echo "Unify Rel: generate libcore(SEE) for combo(make path config_3281 new make)"
make path
make config_3281
make new
make

ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"
	exit 1
fi

echo "Unify Rel: generate libcore(SEE) for combo(make path config_3281_32M new make)"
make config_3281_32M
make new
make

ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"
	exit 1
fi

#echo "Unify Rel: generate libcore(SEE) for combo(make path config_3281_ota new make)"
#make path
#make config_3281_ota
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
echo "Unify Rel: build bootloader in Combo"
cd loader3_encbl
dos2unix *.sh
make rebuild_3281_demo_32M

ret=$?
if [ $ret != 0 ]; then
	echo "$0 compile bootloader with error[$ret]"
	exit 1
fi

#echo "Unify Rel: release loader3_encbl"
#cd ..
#make config_3281
#cd ./loader3_encbl
#make sdk_rel
cd ..

#echo "Unify Rel: generate libcore(CPU) for combo 3281(make path config_3281_ota new sdk_clean sdk)"
#make path
#make config_3281_ota
#make new 
#make sdk_clean
#make sdk

#ret=$?
#if [ $ret != 0 ]; then
	#echo "$0 compile libcore ota with error[$ret]"
	#exit 1
#fi

echo "Unify Rel: generate libcore(CPU) for combo 3281(make path config_3281 new sdk_clean sdk)"
make path
make config_3281
make new 
make sdk_clean
make sdk

ret=$?
if [ $ret != 0 ]; then
	echo "$0 compile libcore with error[$ret]"
	exit 1
fi

echo "Unify Rel: release for combo (make -f MakefileAS.cmd sdk_rel_m32)"
make -f MakefileAS.cmd sdk_rel_m32

mv ../../../../../../ddk_release ../../../../../../ddk_release_m32
echo "Unify Rel: ddk_release_m32 finished"

#if [ -d "../../../../../../cas9_release_combo" ]; then
	#if [ -d "../../../../../../cas9_release_combo" ]; then
		#rm -Rf ../../../../../../cas9_release_combo
	#fi
#fi
#if [ -d "../../../../../../cas9_release_m32" ]; then
	#if [ -d "../../../../../../cas9_release_m32" ]; then
		#rm -Rf ../../../../../../cas9_release_m32
	#fi
#fi
#echo "Unify Rel: release cas9_release_m32"
#make -f MakefileAS.cmd cas9_rel_m32
#mv ../../../../../../cas9_release_combo ../../../../../../cas9_release_m32

#if [ -d "../../../../../../cas9_vsc_release_combo" ]; then
	#echo "rm cas9_vsc_release_combo"
	#rm -Rf ../../../../../../cas9_vsc_release_combo
#fi
#if [ -d "../../../../../../cas9_vsc_release_m32" ]; then
	#echo "rm cas9_vsc_release_m32"
	#rm -Rf ../../../../../../cas9_vsc_release_m32
#fi

#echo "Unify Rel: release cas9_vsc_release_m32"
#make -f MakefileAS.cmd cas9_vsc_rel_m32
#mv ../../../../../../cas9_vsc_release_combo ../../../../../../cas9_vsc_release_m32

#if [ -d "../../../../../../cas9_release_m32" ]; then
	#rm -f ../../../../../../cas9_release_m32/prj/app/demo/combo/sabbat_dual/conax_ap/vsc_see_se*
	
	#if [ -d "../../../../../../cas9_vsc_release_m32" ]; then
		#echo "copy cas9 to vsc"
		#cp -rf ../../../../../../cas9_release_m32/*  ../../../../../../cas9_vsc_release_m32/		
		
		#rm -f ../../../../../../cas9_vsc_release_m32/prj/app/demo/combo/sabbat_dual/conax_ap/vsc_see_se*
		#rm -f ../../../../../../cas9_vsc_release_m32/prj/app/demo/combo/sabbat_dual/conax_ap/libconax_m32.a
		#rm -f ../../../../../../cas9_vsc_release_m32/prj/app/demo/combo/sabbat_dual/conax_ap/libconax.a
				
		#echo "copy cas9 to vsc done"
	#fi
#fi


echo "Unify Rel: plug in release"
make -f MakefileAS.cmd plugin_rel_m32

rm -rf ../../../../../../plugin_combo_M32
mv ../../../../../../plugin_combo ../../../../../../plugin_combo_M32