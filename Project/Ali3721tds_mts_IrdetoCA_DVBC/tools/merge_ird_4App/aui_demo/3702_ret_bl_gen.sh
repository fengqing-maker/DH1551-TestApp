bl_tool=$1
bl_in=$2
mem_init=$3
bl_out=$4

# Copy linux or window bl_tool as name bl_tool.exe
cp ${bl_tool} ./bloader_cmd/c3702/bl_tool.exe

if [ -z ${bl_in}  ]; then
	bl_out="bloader3_3702_dual.abs"
fi

if [ -z ${bl_out} ]; then
	bl_out="bloader3_3702_rt_gen.abs"
fi

echo "BL: ${bl_in}"
mem_init2=$(echo "${mem_init}" | sed 's:\\::g')
echo "mem_init_file:${mem_init2}"

cp -rf ${bl_in} ./bloader_cmd/c3702/
cd ./bloader_cmd/c3702/
sed "s/bloader3_3702_dual.abs/${bl_in}/" C3702_Ret_BL_Generate.cmd > M3702_Ret_DB_BL_Generate_Merge.cmd

sed -i "s/bloader3_3702_rt_unified.abs/${bl_out}/" M3702_Ret_DB_BL_Generate_Merge.cmd

merge_init="C3702_Memory_Init_Merge.txt"
if [ -f "${mem_init2}" ]; then
	cp -f "${mem_init2}" "${merge_init}"
	sed -i "s/C3702_Memory_Init.txt/${merge_init}/" M3702_Ret_DB_BL_Generate_Merge.cmd
else
	pwd
	echo "Cannot find ${mem_init2}"
	echo " "
	exit 1
fi

echo "Merge ${mem_init2} to  ${bl_in}"
./bl_tool.exe M3702_Ret_DB_BL_Generate_Merge.cmd

rm -f M3702_Ret_DB_BL_Generate_Merge.cmd
rm -f "${merge_init}"
