#!/bin/bash

make path
#build bloader3_3281_security_demoboard_64M.abs
make config_3281_demo
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_security_demoboard_32M.abs
make config_3281_demo
make config_32M
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_bl_encrypted_demoboard_64M.abs
make config_3281_demo
make config_encbl
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_bl_encrypted_demoboard_32M.abs
make config_3281_demo
make config_encbl
make config_32M
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_security_demoboard_64M_vsc.abs
make config_3281_demo
make config_vsc
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_security_demoboard_32M_vsc.abs
make config_3281_demo
make config_32M
make config_vsc
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_bl_encrypted_demoboard_64M_vsc.abs
make config_3281_demo
make config_encbl
make config_vsc
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_bl_encrypted_demoboard_32M_vsc.abs
make config_3281_demo
make config_encbl
make config_32M
make config_vsc
make new
make all
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi
