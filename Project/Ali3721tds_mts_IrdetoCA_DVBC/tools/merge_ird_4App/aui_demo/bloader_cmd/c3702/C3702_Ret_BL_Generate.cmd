;####################################################
;###################### BL1 #########################
;#################################################### 
[PARAMETER]
generation=GR1
output=../../bloader3_3702_rt_unified.abs

########## Default address is 0xa0000200 ############
loader_entry=0xa1000000
#####################################################

######### Root Key pair, ALI or DER format ##########
rsa_key_format=ALI
rsa_key=root_key_pair.key
#####################################################
bl_name=bloader3_3702_dual.abs
aux_code=aux_code.abs
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

read_timing=0x22 
write_timing=0x22
scramble_en=0
row_count=3

##eccsec_size=0x400
##eccredu_size=0x20
##rowaddr_cycle=0x3
##ecctype=0x0
##eccsec_perpage=0x2

[CMD]
aux_sign
bl_sign
merge      
       