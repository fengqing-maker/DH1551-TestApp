#!/bin/bash

#if [ "$BR2_IRDETO_LEGAL_FLOW" = "y" ]; then

	curdir="$(dirname $0)"
	
	function message()
	{
		echo -e "\033[47;30m$*\033[0m"
		echo ""
		return 0
	}
#	loader_core_sig=$curdir/of_signed/3721L_ouc_loader_signed.bin
	loader_core_for_enc=$curdir/to_be_sign/3721L_ouc_loader_for_enc.bin

	for file in $loader_core_enc
	do
		[ ! -f $file ] && message "($BASH_SOURCE:$FUNCNAME:$LINENO) Error!:$file is not exist" && exit 1;
	done

	cp -f $loader_core_for_enc $curdir/to_be_sign/3721L_ouc_loader_for_enc.bin.bak
#	dd if=$loader_core_for_enc of=$curdir/to_be_sign/3721L_ouc_loader_for_enc_payload.bin bs=1 skip=128
#	cp -f $curdir/to_be_sign/3721L_ouc_loader_for_enc_payload.bin $curdir/of_signed
	cp -f $curdir/to_be_sign/3721L_ouc_loader_for_enc.bin $curdir/of_signed

	message "Success : extract signed image successfully"
#fi

exit 0
