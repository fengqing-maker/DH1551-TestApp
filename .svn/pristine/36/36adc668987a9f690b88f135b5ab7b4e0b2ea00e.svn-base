
#!/bin/sh
rm -rf splitfile*
split -b 1924368 dumped_appenc_image.bin splitfile
cp -rf splitfileaa  ../image_encrypt/dumped_appenc_image_4App.bin
cd ../image_encrypt
source mk_alimerge_encrypted_image.sh
cp -rf ali_encrypted_app.bin  ../Merge_EncryptApp_RC
cp -rf ali_encrypted_app.bin  ../../4_backdoor
cp -rf ../RC.bin ../Merge_EncryptApp_RC
cd ../Merge_EncryptApp_RC
./MERGE merge_app_rc.ini