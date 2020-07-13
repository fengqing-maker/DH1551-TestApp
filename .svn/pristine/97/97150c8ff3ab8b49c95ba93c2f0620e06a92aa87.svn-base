#!/bin/bash
#####################################################################################
# 1. before run this shell. make sure the file 'compiler_3281.def' be the default one
# 2. especially you cut down when compiler going. restores the file by backup one
# 3. if run completely, forget step 2
# 4. generate firmware bin code
#
#####################################################################################
#==============
Enable_Macro_Func()
{
# $1 :FILE_CONFIG, the file(include path) needed to be modified
# $2 :ENABLE_MACROS, Macros array needed to be opened
# $3 :RM_CH, character need to be delete, e.g. '/', '#'
	FILE_CONFIG=$1
	LT_ENABLE_MACROS=$2
	echo $LT_ENABLE_MACROS  "enable - check"
	RM_CH=$3


	FILE_TMP=$FILE_CONFIG".tmp"
	rm -f $FILE_TMP
	awk -v FILE_NAME="$FILE_CONFIG" -v FTMP="$FILE_TMP" -v ch="$RM_CH" -v siz="$siz" -v LT_ENABLE_MACROS2="${LT_ENABLE_MACROS[*]}" \
			'BEGIN { \
				siz=split(LT_ENABLE_MACROS2, array_enable," "); \
				while(getline < FILE_NAME > 0) { \
					for (k=1; k<=siz; k++) { \
						if (index( $0, array_enable[k] ) > 0 ) { \
							if(index( $0, "=" ) > 0 && index( $0, "=" ) > 0 && index( $0, "1" ) > 0) { \
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
	LT_DISABLE_MACROS=$2
	echo $LT_DISABLE_MACROS  "disable -check"
	RM_CH=$3


	FILE_TMP=$FILE_CONFIG".tmp"
	rm -f $FILE_TMP
	awk -v FILE_NAME="$FILE_CONFIG" -v FTMP="$FILE_TMP" -v ch="$RM_CH" -v siz="$siz" -v LT_DISABLE_MACROS2="${LT_DISABLE_MACROS[*]}" \
			'BEGIN { \
				siz=split(LT_DISABLE_MACROS2, array_enable," "); \
				while(getline < FILE_NAME > 0) { \
					for (k=1; k<=siz; k++) { \
						if (index( $0, array_enable[k] ) > 0 ) { \
							if ( index( $0, "=") > 0 && index( $0, "=" ) > 0 && index( $0, "DEFS" ) <= 0) { \
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
}



Compiler_3721L_IRD_Loadercore()
{
	echo "<1-1>build 3721L Loadercore ABS"
	
	make path aui_sync_3702
	
	RM_CH="#"
	ENABLE_COMPILE_3702_128M=("_BOARD_M3721_02V01_"  "_C1800A_CA_ENABLE_" "_C1800A_LOADERCORE_ENABLE_" "_C1800A_DVT_TEST_" "_USE_SIGNED_BL_SEE")
	Enable_Macro_Func "${FILE_COMPILE_3702}" "${ENABLE_COMPILE_3702_128M[*]}" "${RM_CH}"
	
	DISABLE_COMPILE_3702_128M=("_BOARD_M3712L_01V01_" "_DD_SUPPORT" "_BOOT_LOGO_ENABLE_" "_GEN_CA_ENABLE_")
	Disable_Macro_Func "${FILE_COMPILE_3702}" "${DISABLE_COMPILE_3702_128M[*]}" "${RM_CH}"
	
	make path config_3702_loadercore new ddk aui product_7z
	ret=$?
	if [ $ret != 0 ]; then
		echo "$0 with error[$ret]"
		exit 1
	fi

	DISABLE_COMPILE_3702_128M=("_C1800A_DVT_TEST_")
	Disable_Macro_Func "${FILE_COMPILE_3702}" "${DISABLE_COMPILE_3702_128M[*]}" "${RM_CH}"
    
	BL_OFFSET=$(cat ${BLOCKS_SCRIPT_3702} | grep -m1 "offset")
	sed -i "/id=0/,/file=bloader3_3702_sec_wh.abs/s/$BL_OFFSET/offset=0x60000/" 	${BLOCKS_SCRIPT_3702}
	
	make path config_3702 new ddk aui product_7z
	ret=$?
	if [ $ret != 0 ]; then
		echo "$0 with error[$ret]"
		exit 1
	fi
}


MAIN()
{
	Compiler_3721L_IRD_Loadercore
}

#=============="
FILE_COMPILE_3702="compiler_3702.def"
BLOCKS_SCRIPT_3702="blocks_script_7z_sabbat_M3702_dual_ird_8m.txt"

RELEASE_DATE=$(date +%Y%m%d)
echo "build bin at" $RELEASE_DATE

make path
pwd

echo "CUR_DIR=${CUR_DIR}"
echo "ROOT_DIR=${ROOT_DIR}"

MAIN  2>&1 | tee log_com.txt

##################################
echo "All finished"${date}


