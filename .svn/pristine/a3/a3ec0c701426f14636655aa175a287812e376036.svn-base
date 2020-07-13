#!/bin/bash
#IN_FILE=bl_out.abs
IN_FILE=$1
IN_FILE_SIZE=`du -b $IN_FILE | awk '{print $1}'`
echo "bl_out size:" $IN_FILE_SIZE

curdir="$(dirname $0)"

. $curdir/../common/do_common.sh

function message()
	{
		echo -e "\033[47;30m$*\033[0m"
		echo ""
		return 0
	}

	
OUT_FILE1=boot_param_area.abs.for.sign
OUT_FILE2=boot_aux_code_area.bin
OUT_FILE3=boot_unchecked_area.bin
OUT_FILE4=boot_code_area.abs.for.sign
OUT_FILE5=boot_code_area.abs.for.enc

echo "1.extract boot_params_area data..."
./util.sh extract --output=$OUT_FILE1 --input_offset=592 $IN_FILE 1200
echo "2.extract boot_aux_code_area data..."
./util.sh extract --output=$OUT_FILE2 --input_offset=2048 $IN_FILE 12032
echo "3.extract boot_unchecked_area data..."
./util.sh extract --output=$OUT_FILE3 --input_offset=14336 $IN_FILE 8192
echo "4.extract boot_code_area_for_sign data..."
./util.sh extract --output=$OUT_FILE4 --input_offset=22528 $IN_FILE $(($IN_FILE_SIZE-22528-256))
echo "5.extract boot_code_area_for_enc data..."
./util.sh extract --output=$OUT_FILE5 --input_offset=22528 $IN_FILE $(($IN_FILE_SIZE-22528-256-16))


cp -vpf $curdir/../AUX_Code_Hash_demo.abs $curdir/../to_be_sign/AUX_Code_Hash_demo.abs
cp -vpf $curdir/../AUX_Code_Enc_demo.abs $curdir/../of_signed/AUX_Code_Enc_demo.abs
cp -vpf $curdir/boot_unchecked_area.bin $curdir/../of_signed/boot_unchecked_area.bin

message "Success : generate to be signed image successfully"
