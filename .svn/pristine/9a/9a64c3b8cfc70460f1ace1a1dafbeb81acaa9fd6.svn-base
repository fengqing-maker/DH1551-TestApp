
all:
	cp -rf ./bloader3_3702_logo_sec_ird.abs ./aui_demo/bloader3_3702_logo_sec_ird_128M.abs;
	cp -rf ./orginal_boot_see.abs ./aui_demo/ird_ap/see_bl.ubo;
	cp -rf ./orginal_ifcp_bl.abs ./aui_demo/ird_ap/ifcp_bl.ubo;
	
	rm -rf ./aui_demo/ird_ap/see.ubo;
	cp -rf ./see.ubo ./aui_demo/ird_ap/see.ubo;
	
	rm -rf ../0_all_flash_for_burn/image_encrypt/signed_app_see_4merge.bin;
	cp -rf ./see.ubo ../0_all_flash_for_burn/image_encrypt/signed_app_see_4merge.bin;
	
	make -f SABBAT_DEMO.lk compress_7z;
	make -f SABBAT_DEMO.lk generate_7z;
	cp -rf aui_demo/app_orign.bin  ./app_4mergetool.bin;
	cp -rf aui_demo/appsee_orign.bin  ./appsee_4mergetool.bin;
	./mk_alimerge_image.sh;	
	##cp -rf ./aui_demo/product_sabbat_dual.abs ./all_flash/ali_booter.bin;
	cp -rf ali_NoEnc_app.bin  ../0_all_flash_for_burn/ali_NoEnc_app.bin;
	
clean:
	rm -rf Sabbat_s3702*
	rm -rf aui_demo/product_sabbat*
	rm -rf aui_demo/3702_ouc_loader*
	rm -rf aui_demo/factory_data_sabbat.bin
	rm -rf aui_demo/app.bin
	rm -rf aui_demo/app_see.bin
	rm -rf aui_demo/app_orign.bin
	rm -rf aui_demo/see.ubo

