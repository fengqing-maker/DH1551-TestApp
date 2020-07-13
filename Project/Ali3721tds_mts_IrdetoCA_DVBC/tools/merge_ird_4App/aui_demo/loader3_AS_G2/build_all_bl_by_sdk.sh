#!/bin/bash
#build bloader3_m3515_dual.abs
make path
make config_m3515
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_m3515_dual_encbl.abs
cp compiler_security.def compiler_security.def.old
gen_expression="sed -e 's/#_ENABLE_BL_ENCRYPTED_ = 1/_ENABLE_BL_ENCRYPTED_ = 1/' compiler_security.def.old"
eval ${gen_expression} > compiler_security.def.new
mv compiler_security.def.new compiler_security.def
make path
make config_m3515
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi
cp compiler_security.def.old compiler_security.def
rm -f compiler_security.def.old compiler_security.def.new