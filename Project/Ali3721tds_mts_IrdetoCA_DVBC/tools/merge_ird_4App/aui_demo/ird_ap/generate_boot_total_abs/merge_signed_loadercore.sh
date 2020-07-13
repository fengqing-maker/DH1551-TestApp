#!/bin/bash

#if [ "$BR2_IRDETO_LEGAL_FLOW" = "y" ]; then

	curdir="$(dirname $0)"
	
	function message()
	{
		echo -e "\033[47;30m$*\033[0m"
		echo ""
		return 0
	}
	loader_core_sig=$curdir/of_signed/3721L_ouc_loader_signed.bin
	loader_core_enc=$curdir/of_signed/3721L_ouc_loader_for_enc.bin.ecf

	for file in $loader_core_sig $loader_core_enc
	do
		[ ! -f $file ] && message "($BASH_SOURCE:$FUNCNAME:$LINENO) Error!:$file is not exist" && exit 1;
	done

	cp -f $loader_core_sig $curdir/of_signed/loader_core.sign.mergeok
	dd if=$loader_core_enc of=$curdir/of_signed/loader_core.sign.mergeok conv=notrunc
#	dd if=$loader_core_sig of=$curdir/of_signed/loader_core.signed.bin.header bs=1 count=128
#	cat $curdir/of_signed/loader_core.signed.bin.header $curdir/of_signed/3721L_ouc_loader_for_enc_payload.bin.ecf > loader_core.sign.mergetemp
#	dd if=loader_core.sign.mergetemp of=$curdir/of_signed/loader_core.sign.mergeok conv=notrunc
#	cp $TEMPDIR/loader_core.sign.clear $curdir/../../3721L_ouc_loader.bin

	message "Success : merge signed image successfully"
#fi

exit 0
