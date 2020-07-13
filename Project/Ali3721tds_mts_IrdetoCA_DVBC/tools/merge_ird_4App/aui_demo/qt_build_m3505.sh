#!/bin/bash

FILE_COMPILE_3505="compiler_3505.def"

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

Clean_TMP()
{	
	rm -f ${FILE_COMPILE_3505}.tmp
}
M3527_Conax_Compiler()
{
	echo "enter m3527 conax compiler"
}

M3527_Conax_VSC_Compiler()
{
	## MACRO ENABLE
	RM_CH="#"
	echo ">>> enable designated macro ..."
	ENABLE_COMPILE_3505_128M=("_BOARD_M3527_01V01_" "_CAS9_CA_ENABLE_"  "_CAS9_VSC_ENABLE_" "_CAS9_VSC_API_ENABLE_" "_ENABLE_BL_ENCRYPTED_" "_DD_SUPPORT" "_USE_SIGNED_BL_SEE")
	Enable_Macro_Func "${FILE_COMPILE_3505}" "${ENABLE_COMPILE_3505_128M[*]}" "${RM_CH}"
	## PRE COMPILE
	echo ">>> build M3527 conax vsc fw ..."
	make path config_3505 new ddk aui product_7z
	## clean tempoary file
	Clean_TMP
}

RELEASE_DATE=$(date +%Y-%m-%d)
echo "Build AUI Sample Code On" $RELEASE_DATE
echo "############################################################"
echo "choose your sampe code type to build :"
echo -e "1 : M3527 CONAX\n2 : M3527 CONAX VSC(cardless)"
echo "############################################################"
read -p "input your type : " BUILD_TYPE

if [ $BUILD_TYPE == 1 ]; then
	echo ">>> ready to build M3527 conax ..."
	M3527_Conax_Compiler
elif [ $BUILD_TYPE == 2 ]; then
	echo ">>> ready to build M3527 conax vsc ..."
	M3527_Conax_VSC_Compiler
else
	echo "[error] invalid type input, please check again !"
fi

echo "############################################################"
echo "all finished"

