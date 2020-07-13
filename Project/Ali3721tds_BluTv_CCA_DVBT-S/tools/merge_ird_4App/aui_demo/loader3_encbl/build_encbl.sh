#!/bin/bash

make path
#build bloader3_3281_security_demoboard_64M.abs
make rebuild_3281_demo
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_security_demoboard_32M.abs
make rebuild_3281_32M_demo
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_bl_encrypted_demoboard_64M.abs
make rebuild_3281_encbl_demo
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi

#build bloader3_3281_bl_encrypted_demoboard_32M.abs
make rebuild_3281_encbl_32M_demo
ret=$?
if [ $ret != 0 ]; then
	echo "$0 with error[$ret]"		
	exit 1
fi