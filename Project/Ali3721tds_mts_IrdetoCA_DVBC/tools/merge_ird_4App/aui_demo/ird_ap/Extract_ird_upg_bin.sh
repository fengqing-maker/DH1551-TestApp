dd if=sw_main_code.chunk bs=128 count=1 skip=0  of=main_chunk.bin
cat main_chunk.bin app.bin > app_upg.bin

dd if=sw_see_code.chunk bs=128 count=1 skip=0  of=see_chunk.bin
cat see_chunk.bin see.ubo > see_upg.ubo

cat prst.bin > prst_upg.bin
