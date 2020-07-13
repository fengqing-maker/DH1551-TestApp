;####################################################
;###################### BL4 #########################
;#################################################### 
[PARAMETER]
generation=GA4

#CA_Vendor=3
############# RSASSA_PKCS or RSASSA_PSS #############
sig_format=RSASSA_PKCS
#####################################################

############# AES_CBC for CNX or AES_ECB for NGR ####
aes_mode=AES_CBC
#####################################################


################## MKT_ID & VER_ID ##################
market_id=0x000000EC
market_mask=0xFFFFFFFF
version_id=0x00000000
version_mask=0xFFFFFFFF
#####################################################

##################### HW_MONITOR ####################
hw_monitor1=ffff0000
hw_monitor2=ffff0022
#####################################################

########## Default address is 0xa0000200 ############
loader_entry=0xa1000000
#####################################################
crypto_flag=1
#encrypt_format=IRD_KL_KEY
#encrypt_format=KEY7_ONLY
#################################### FlashProtectKey encrypt Boot code ##########################################
#FlashProtectKey=./keys/c3702_c1800a_keys_bck.bin
FlashProtectKey=./keys/BL_Encrypted.bin
#################################################################################################################
aux_code_enc=AUX_Code_Enc_demo.abs
aux_code_hash=AUX_Code_Hash_demo.abs

############ public key level is 1 or 2 #############
pub_key_level=2
#####################################################

##### external public key, X509 with DER format #####
ext_pub_key=./keys/public_2nd_level.key
#####################################################

######### Root Key pair, ALI or DER format ##########
root_key_format=DER
rsa_key=./keys/root_key_pair.der
#####################################################

####### External Pubic Key, ALI or DER format #######
ext_key_format=DER
ext_rsa_key=./keys/ext_key_pair.der
# the next stage software public key, if linux project, this key is used for uboot, if TDS, this key is used for system software
#####################################################

######### SYSTEM1 Pubic Key, ALI or DER format ######
sys1_key_format=ALI
sys1_rsa_key=./keys/sys_sw_pair.key
#####################################################

######### SYSTEM2 Pubic Key, ALI or DER format ######
#sys2_key_format=DER
#sys2_rsa_key=sys_sw_pair.der
#####################################################

#####################################################
#system software universal key, customer can change this key
#sys_uk=sw_uk.bin
#####################################################
bl_name=boot_total_area_origin.abs
bl_version=1
output=bl.in

#mem_init_file=C3702_SIP_BGA13X13_DDR3_1866Mbps_CL13xCWL9_256M.txt
mem_init_file=C3702_Memory_Init.txt
    
[NAND CONFIG]
############ MICRON #############
#block_perchip=0x800
#pages_perblock=0x100
#bytes_perpage=0x2000
#ecctype=40 
#nand_type=1

############ TOSHIBA #############
#block_perchip=0x800
#pages_perblock=0x100
#bytes_perpage=0x4000
#ecctype=40 
#nand_type=0

############ SK hyniux #############
#block_perchip=0x1000
#pages_perblock=0x40
#bytes_perpage=0x2000
#ecctype=40 
#nand_type=0

############ Default #############
block_perchip=0x800
pages_perblock=0x40
bytes_perpage=0x800
ecctype=16 
nand_type=0

#####################################################

read_timing=0x55 
write_timing=0x55
scramble_en=0
row_count=3

##eccsec_size=0x400
##eccredu_size=0x20
##rowaddr_cycle=0x3
##ecctype=0x0
##eccsec_perpage=0x2


############ SPI NAND #############
#block_perchip=0x0
#pages_perblock=0x40
#bytes_perpage=0x800
#ecctype=0xFFFFFFFF 
#nand_type=0
#read_timing=0x2 
[CMD]
ext_key_sign
params_sign
insert_len
insert_key
bl_version
#aux_inner_sign
#aux_sign
#aux_enc
aux_hash_enc
bl_sign
#bl_enc_payload
merge  
