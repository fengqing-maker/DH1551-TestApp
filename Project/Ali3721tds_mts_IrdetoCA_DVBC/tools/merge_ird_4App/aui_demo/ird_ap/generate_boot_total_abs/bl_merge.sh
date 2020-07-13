#!/bin/bash

curdir="$(dirname $0)"

. $curdir/../common/do_common.sh

function message()
	{
		echo -e "\033[47;30m$*\033[0m"
		echo ""
		return 0
	}

	#merge signed boot image
	ext_pub_key=$curdir/../of_signed/ext_public_key_area_signature.abs
	boot_param_area=$curdir/../of_signed/boot_param_area.abs.signature
	boot_aux_code=$curdir/../of_signed/AUX_Code_Enc_demo.abs
	boot_aux_code_hash_sig=$curdir/../of_signed/AUX_Code_hash_value_signature.abs
	boot_uncheck_area=$curdir/../of_signed/boot_unchecked_area.bin
	boot_code_sig=$curdir/../of_signed/boot_code_area.abs.signature
	boot_code_enc=$curdir/../of_signed/boot_code_area.abs.enc
	
	for file in $ext_pub_key $boot_param_area $boot_aux_code \
	            $boot_aux_code_hash_sig $boot_uncheck_area \
	            $boot_code_sig $boot_code_enc
	do
		[ ! -f $file ] && message "($BASH_SOURCE:$FUNCNAME:$LINENO) Error!:$file is not exist" && exit 1;
	done
	
	cat $ext_pub_key $boot_param_area $boot_aux_code \
	    $boot_aux_code_hash_sig $boot_uncheck_area \
	    $boot_code_sig > $curdir/boot_total_area.abs.clear
	
	boot_code_area_offset=0x5800
	cd $curdir && cp -f boot_total_area.abs.clear boot_total_area.abs.enc
	dd if=$boot_code_enc of=$curdir/boot_total_area.abs.enc bs=1 seek=$(($boot_code_area_offset)) conv=notrunc
	
	cp -vpf $curdir/boot_total_area.abs.enc $curdir/boot_total_area_mergeok.abs

	cp -vpf $curdir/boot_total_area_mergeok.abs ./boot_total_area.abs

	message "Success : merge signed image successfully"

	


