/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: bootloader.c
*
*    Description:    This file contains Application functions declare
*                    of ALi boot loader.
*
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
     KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
     IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
     PARTICULAR PURPOSE.
*****************************************************************************/
#include "bootloader.h"
#ifdef BL_BC_AS //aaron
#include <api/libcas/bc/bc_types.h>
#endif

#ifdef US_TICKS
#undef US_TICKS
#endif
#ifdef WAIT_300MS
#undef WAIT_300MS
#endif

#define MAIN_OK                     0x1
#define SEE_OK                      0x2
#define OTA_LOADER_OK               0x4

#define US_TICKS       (sys_ic_get_cpu_clock()*1000000 / 2000000)
#define WAIT_100MS          (100000 * US_TICKS)
#define WAIT_300MS          (300000 * US_TICKS)
#define WAIT_500MS            (500000 * US_TICKS)
#define WAIT_5MS            (5000 * US_TICKS)
#define MS_TICKS        (1000*US_TICKS)

UINT8  g_crc_bad = 0;

static void nosdelay(UINT32 timeout)
{
    UINT32 stamp;
    stamp = read_tsc();
    while(read_tsc() - stamp < timeout*MS_TICKS);
}

static BOOL check_sw_upgrade()
{
    BOOL ret = FALSE;
    UINT32 dwtick;
    UINT8  ch;

    dwtick = read_tsc();
    do
    {
        if (sci_read_tm(SCI_FOR_RS232, &ch, 5) == SUCCESS && ch == 'c')
        {
            ret=TRUE;
            break;
        }
        else
            ch = 0;
    }
    while (read_tsc() - dwtick < WAIT_300MS);

    return ret;
}

static INT32 update_flash_data(UINT32 offset, INT32 len, UINT8 * data)
{
    UINT8 *app_flash_buffer = NULL;
    INT32 ret=0;
    FIXED_PRINTF("%s-offset(0x%x),len(0x%x),data(0x %2x %2x %2x %2x)\n",__FUNCTION__,offset,len,data[0],data[1],data[2],data[3]);
    struct sto_device *flash_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);

    app_flash_buffer = MALLOC(64*1024);
    if(app_flash_buffer==NULL)
    {
        FIXED_PRINTF("update_flash_data: allocate buffer failed\n");
        return -1;
    }

    sto_io_control(flash_dev, STO_DRIVER_SECTOR_BUFFER, (UINT32)app_flash_buffer);
    sto_io_control(flash_dev, STO_DRIVER_SET_FLAG, STO_FLAG_AUTO_ERASE|STO_FLAG_SAVE_REST);
    ret=sto_put_data(flash_dev, (UINT32)offset, data, (INT32)len);

    FREE(app_flash_buffer);
    app_flash_buffer = NULL;
    sto_io_control(flash_dev, STO_DRIVER_SECTOR_BUFFER, 0);
    sto_io_control(flash_dev, STO_DRIVER_SET_FLAG, 0);

    return ret;
}

#ifdef BL_BC_AS

#define FAKE_VERITY_SIGNATURE //Aaron Test

#ifdef FAKE_VERITY_SIGNATURE
/****************************************************************************
 *  ViewRight Functions
 ****************************************************************************/
//typedef unsigned long long uint64_t;

static uint8_t magic[8] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };

uint32_t crc32(uint8_t *data, uint32_t len)
{
    return mg_table_driven_crc(0xFFFFFFFF, data, len);
}

uint64_t getNumber( uint8_t* ptr )
{
    uint64_t tmpVal = 0;
    int i;
    // data in the signature is big-endian
    for( i = 0; i < 8; i++ )
    {
        tmpVal = (tmpVal<<8) | ptr[i];
    }
    return tmpVal;
}

uint8_t checkTheDataAndHash(uint8_t *data, uint32_t len, uint8_t* signature)
{
    // this function verifies the hash values and determines whether a
    // re-encryption is needed
    uint32_t tmpCrc = crc32( data, len );

    /* we only have put 32-bits into the signature therefore we type-cast and correct the offset by 4 */
    if( ( (uint32_t)getNumber( signature + 48 - 4 ) ) == tmpCrc )
    {
#if 1    // here we "decrypt" by using xor
        int j;
        FIXED_PRINTF("checkTheDataAndHash: tmpCrc=0x%x match, decrypt the source\n",tmpCrc);
        for( j = 0; j < len; j++ )
        data[j] ^= 0xff;
#endif
        return 0;
    }
    else
    {
        // here we can already "re-encrypt" by using xor
        int i;
        for( i = 0; i < len; i++ )
        data[i] ^= 0xff;
        tmpCrc = crc32( data, len );
        /* we only have put 32-bits into the signature therefore we type-cast and
        correct the offset by 4 */
        if( ( (uint32_t)getNumber( signature + 48 - 4 ) ) != tmpCrc )
        {
            // the crc does not match therefore there it is an error
            FIXED_PRINTF("checkTheDataAndHash: crc error tmpCrc=0x%x\n",tmpCrc);
            return 2;
        }
        return 1;
    }
}

uint8_t decryptSignature( uint8_t* decSignature, uint8_t* signature )
{
    // here we do signature decryption
    // we only copy here as the signature is not encrypted at all
    memcpy( decSignature, signature, 256 );
    return 1;
}

int verifySignature( uint8_t* signature, uint8_t* src, uint8_t* tmp,uint32_t len, uint32_t maxLen, uint8_t mode,uint8_t *errorCode )
{
    uint8_t decSignature[256];

    FIXED_PRINTF("verifySignature: len=0x%x, maxLen=0x%x, mode=%d\n",len, maxLen, mode);
    FIXED_PRINTF("verifySignature: signature crc=0x%x 0x%x 0x%x 0x%x\n",signature[48],signature[49],signature[50],signature[51]);
    FIXED_PRINTF("verifySignature: signature len=0x%x 0x%x 0x%x 0x%x\n",signature[36],signature[37],signature[38],signature[39]);
    FIXED_PRINTF("verifySignature: signature maxlen=0x%x 0x%x 0x%x 0x%x\n",signature[44],signature[45],signature[46],signature[47]);
    // we decrypt the signature, which you do not have to do here
    if( decryptSignature( decSignature, signature ) )
    {
        if( memcmp( decSignature, magic, 8 ) )
        {
            // error magic value is wrong, therefore signature is bad
            FIXED_PRINTF("verifySignature: magic value wrong:0x%x 0x%x\n",decSignature[0], decSignature[1]);
            *errorCode = 1;
            return 0;
        }
        else
        {
            int i;
            for( i = 9; i < 24; i++ )
            {
                if( decSignature[i] )
                {
                    // error verifier is not 0, therefore signature is bad
                    FIXED_PRINTF("verifySignature: zero value wrong:decSignature[%d]= 0x%x\n",i,decSignature[i]);
                    *errorCode = 1;
                    return 0;
                }
            }
            // the signature has been decrypted correctly, now we check the
            // length values
            if( ( getNumber( decSignature+32 ) == len ) &&( getNumber( decSignature+40 ) == maxLen ) )
            {
                // now we do some additional checks for hash-value
                // and from this check we determine whether a
                // re-encryption is needed
                uint8_t re_encryption_needed = checkTheDataAndHash( src, len, decSignature );
                FIXED_PRINTF("verifySignature: re_encryption_needed=%d\n",re_encryption_needed);
                if( re_encryption_needed == 2 )
                {
                    // error the hash value is not correct,
                    // therefore signature is bad
                    *errorCode = 1;
                    return 0;
                }
                // if re-encryption is needed we check, for the mode value.
                if( re_encryption_needed && ( decSignature[8] == 1 ) &&( mode == 0 ) )
                {
                    // error re-encryption when starting from flash must not occur
                    // for loaded image, therefore signature is bad
                    FIXED_PRINTF("verifySignature: mode not match error\n");
                    *errorCode = 1;
                    return 0;
                }

                if( re_encryption_needed )
                {
                    // do the re-encryption
                    // we have already done it
                    *errorCode = 2;
                    return 0;
                }
                else
                {
                    if( mode == 1 )
                    {
                        // error there should be no re-encrypted image directly loaded
                        FIXED_PRINTF("verifySignature: error mode should be 0\n");
                        * errorCode = 1;
                        return 0;
                    }
                    else
                    {
                        // everything is fine
                        *errorCode = 0;
                        return 1;
                    }
                }
            }
            else
            {
                // error one of the length values does not match,
                // therefore signature is bad
                FIXED_PRINTF("verifySignature: len wrong: len=0x%x 0x%x 0x%x 0x%x\n",decSignature[32+4], decSignature[32+5],decSignature[32+6], decSignature[32+7]);
                FIXED_PRINTF("verifySignature: maxlen wrong: maxlen=0x%x 0x%x 0x%x 0x%x\n",decSignature[40+4], decSignature[40+5],decSignature[40+6], decSignature[40+7]);
                *errorCode = 1;
                return 0;
            }
        }
    }
    else
    {
        // error decryption failed, therefore signature is bad
        FIXED_PRINTF("verifySignature: decryption failed\n");
        *errorCode = 1;
        return 0;
    }
}
#endif //FAKE_VERITY_SIGNATURE

static INT32 handle_chunk_data(UINT8 *data, UINT32 length)
{
    int ret;
    uint8_t* signature;
    uint8_t* tmp_buffer;
    uint8_t *source = NULL;
    uint32_t len, maxLen;
    uint8_t mode, errorCode;
    uint32_t chunk_id, block_len, code_len=0;
    unsigned int header_crc=0;
    INT32 ret_val = 0;

    chunk_id = fetch_long(data + CHUNK_ID);
    block_len = fetch_long(data + CHUNK_OFFSET);
    code_len = fetch_long(data + CHUNK_LENGTH);
    #define SIGNATURE_SIZE 256
    len = code_len - (CHUNK_HEADER_SIZE-CHUNK_NAME)-SIGNATURE_SIZE;
    source = data + CHUNK_HEADER_SIZE;
    signature = source + len;

    mode = 1;
    tmp_buffer = (UINT8*)((0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)));
    maxLen = len;

    ret = verifySignature(signature, source, tmp_buffer, len, maxLen, mode,&errorCode);

    if(ret == 1)
    {
        //FIXED_PRINTF("code verify ok, but should not enter this case in force donwload...\n");
    }
    else
    {
        if(errorCode==2)
        {
            UINT32 block_addr = 0;

            switch(chunk_id)
            {
                case CHUNKID_MAINCODE:
                    block_addr = sto_chunk_goto(&chunk_id, CHUNKID_MAINCODE_MASK, 1);

                    if(ERR_FAILUE == block_addr)
                    {
                        uint32_t pre_chunk_id = CHUNKID_STBINFO;
                        uint32_t pre_chunk_offset;

                        block_addr = sto_chunk_goto(&pre_chunk_id, CHUNKID_STBINFO_MASK, 1);
                        pre_chunk_offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

                        if(ERR_FAILUE == block_addr)
                            ret_val = -1;
                        else
                            block_addr += pre_chunk_offset;
                    }
                    break;

                case CHUNKID_SEECODE:
                    block_addr = sto_chunk_goto(&chunk_id, CHUNKID_SEECODE_MASK, 1);

                    if(ERR_FAILUE == block_addr)
                    {
                        uint32_t pre_chunk_id = CHUNKID_MAINCODE;
                        uint32_t pre_chunk_offset;

                        block_addr = sto_chunk_goto(&pre_chunk_id, CHUNKID_MAINCODE_MASK, 1);
                        pre_chunk_offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

                        if(ERR_FAILUE == block_addr)
                            ret_val = -1;
                        else
                            block_addr += pre_chunk_offset;
                    }
                    break;

                default:
                    //not supported chunk id in force download
                    ret_val = -1;
                    break;
            }

            if( ret_val == 0 )
            {
                //calculate crc value for chunk header
                header_crc=mg_table_driven_crc(0xFFFFFFFF, data+CHUNK_NAME, code_len);
                *(data+CHUNK_CRC)=(UINT8)(header_crc>>24);
                *(data+CHUNK_CRC+1)=(UINT8)(header_crc>>16);
                *(data+CHUNK_CRC+2)=(UINT8)(header_crc>>8);
                *(data+CHUNK_CRC+3)=(UINT8)(header_crc);
                pan_display(panel_dev, "BURN", 4);
                update_flash_data(block_addr, block_len, data);
            }
            else
            {
                pan_display(panel_dev, "fail", 4);
                while(1);
            }
        }
        else if(errorCode==1)
        {
            ret_val = -1;
        }
    }

    FREE(tmp_buffer);

    return ret_val;
}
#endif

//Apply bc std boot flow
#ifdef BL_BC_STD
int verifySignature_std( UINT8* src, UINT8* dest, CHUNK_HEADER hdr,UINT8 *errorCode)
{
    FIXED_PRINTF("Verify chunk (0x%x)!\n",hdr.id);
    int ret=0,val=0;
    *errorCode=1;
    UINT8 kid=0;
    if(NO_CRC!=hdr.crc)
    {
        kid=1;    //common key
        FIXED_PRINTF("Use Common Key!\n");
    }
    else
    {
        FIXED_PRINTF("Use AES Key!\n");
    }
    ret=aes_cbc_std(0,kid,src,dest);
    FIXED_PRINTF("%s-run aes_cbc_std , ret: %d.\n",__FUNCTION__,ret);
    fetch_sys_pub_key(1);
    val=Test_RSA_Ram((UINT32)dest+CHUNK_HEADER_SIZE,hdr.len-CHUNK_HEADER_SIZE + CHUNK_NAME);
    FIXED_PRINTF("%s-run Test_RSA_Ram , ret: %d.\n",__FUNCTION__,val);
    if(0!=val)        //case of no valid signature
    {
        if(-2==val)    //Special case during MP (No RSA Key)
        {
            FIXED_PRINTF("Skip RSA Check, due to Zero RSA Key!\n");
            ret=1;
            *errorCode=0;
        }
        else
        {
            FIXED_PRINTF("No valid signature!\n");
            if(1==kid)
            {
                *errorCode = 3;    //Need hang up, since check fail with common key
            }
            else
            {
                *errorCode = 1;
            }
            return ret;
        }
    }
    //valid signature
    if(0==kid)
    {
        ret=1;
        *errorCode=0;
        FIXED_PRINTF("Success to check chunk.\n");
    }
    else if(1==kid)
    {
        MEMSET(src,0xFF,hdr.offset);
        val=aes_cbc_std(1,0,dest,src);
        if(0==val)
        {
            *errorCode=2;    //case of need to store reEnc code to flash
            FIXED_PRINTF("Need to store data to flash!\n");
        }
        else if(-2==val)    //special case during MP Flow (No AES Key)
        {
            *errorCode=0;
            ret=1;
            FIXED_PRINTF("Spcial case during MP !\n");
        }
    }
    return ret;
}

static INT32 handle_chunk_data_std(UINT8 *data, UINT32 length)
{
    int ret;
    UINT8* tmp_buffer;
    UINT32 len;
    UINT8 errorCode;
    UINT32 chunk_id, block_len;
    unsigned int header_crc=0;
    INT32 ret_val = 0;
    UINT32 pre_chunk_id =0;
    UINT32 pre_chunk_offset=0;


    CHUNK_HEADER tchunk_hdr;
    tchunk_hdr.id = fetch_long(data + CHUNK_ID);
    tchunk_hdr.len= fetch_long(data + CHUNK_LENGTH);
    tchunk_hdr.offset=fetch_long(data + CHUNK_OFFSET);
    tchunk_hdr.crc=fetch_long(data + CHUNK_CRC);

    chunk_id=tchunk_hdr.id;
    block_len=tchunk_hdr.offset;
    tmp_buffer = (UINT8*)((0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)));
    ret = verifySignature_std(data, tmp_buffer, tchunk_hdr,&errorCode);
    FIXED_PRINTF("%s:chkret(%d),errorcode(%d)\n",__FILE__,ret,errorCode);
    if(ret == 1)
    {
        //FIXED_PRINTF("code verify ok, but should not enter this case in force donwload...\n");
    }
    else
    {
        if(errorCode==3)
        {
            pan_display(panel_dev, "ERRC", 4);
            do{} while(1);
        }
        else if(errorCode==2)
        {
            UINT32 block_addr = 0;

            switch(chunk_id)
            {
                case CHUNKID_MAINCODE:
                    block_addr = sto_chunk_goto(&chunk_id, CHUNKID_MAINCODE_MASK, 1);
                    if(ERR_FAILUE == block_addr)
                    {
                        pre_chunk_id = CHUNKID_STBINFO;
                        pre_chunk_offset=0;

                        block_addr = sto_chunk_goto(&pre_chunk_id, CHUNKID_STBINFO_MASK, 1);
                        pre_chunk_offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

                        if(ERR_FAILUE == block_addr)
                            ret_val = -1;
                        else
                            block_addr += pre_chunk_offset;
                    }
                    break;

                case CHUNKID_SEECODE:
                    block_addr = sto_chunk_goto(&chunk_id, CHUNKID_SEECODE_MASK, 1);
                    if(ERR_FAILUE == block_addr)
                    {
                        pre_chunk_id = CHUNKID_MAINCODE;
                        pre_chunk_offset=0;

                        block_addr = sto_chunk_goto(&pre_chunk_id, CHUNKID_MAINCODE_MASK, 1);
                        pre_chunk_offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

                        if(ERR_FAILUE == block_addr)
                            ret_val = -1;
                        else
                            block_addr += pre_chunk_offset;
                    }
                    break;

                default:
                    //not supported chunk id in force download
                    ret_val = -1;
                    break;
            }
            if( ret_val == 0 )
            {
                pan_display(panel_dev, "BURN", 4);
                update_flash_data(block_addr, block_len, data);
            }
            else
            {
                pan_display(panel_dev, "FAIL", 4);
                do{} while(1);
            }
        }
        else if(errorCode==1)
        {
            ret_val = -1;
        }
    }

    FREE(tmp_buffer);

    return ret_val;
}
#endif

static void serial_upgrade(void)
{
    hw_watchdog_stop();
#ifdef BL_BC_STD
    lib_ash_set_data_callback(handle_chunk_data_std);
#elif defined BL_BC_AS
    lib_ash_set_data_callback(handle_chunk_data);
#endif
    lib_ash_shell();
}

void app_init ( void )
{
    UINT32 pos;
    UINT32 chid, offset;
    UINT8 *main_entry, *see_entry;
    UINT32 decrypt_flag = 0xff;
    UINT32 cpu_mc_len = 0, see_mc_len = 0, ota_len = 0;
    UINT32 ziped_len = 0;
    UINT8 *p=NULL;
    UINT32 block_addr = 0, block_len = 0;
    static UINT8 *temp_buffer = NULL;
    static UINT8 *main_decrypted = NULL;
    static UINT8 *see_decrypted = NULL;
    static UINT8 *ota_decrypted = NULL;
    CHUNK_HEADER chunk_hdr;
    UINT32 i=0 ;
    RET_CODE ret=RET_SUCCESS;
    UINT8 sys_sw_wrong = 0;

#ifdef BL_BC_AS //aaron
    uint8_t* signature;
    uint8_t* tmp_buffer;
    uint32_t len, maxLen;
    uint8_t mode, errorCode;
    UINT8 *main_block, *see_block;
    unsigned int header_crc=0;
    UINT8 verify_result=0;
#endif //BL_BC_AS

#ifdef BL_BC_STD
    struct sto_device *test_flash_dev = NULL;
    UINT8 *temp1,*temp2,*temp3,*temp4,*temp5,*temp6,errorCode,chkret=0;
    UINT32 mpos=0,spos=0;
#endif

    ret = bl_init_dev();
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF("bootloader init fail!\n");
        goto bl_reboot;
    }

    /* Initiaize and boot bootloader SEE*/
    temp_buffer = ( UINT8* ) (  ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( __SEE_ROM_END - __SEE_ROM_START + 0xf ) ) );
    if(NULL == temp_buffer )
    {
        FIXED_PRINTF("out of memory\n");
        goto bl_reboot;
    }

    MEMCPY ( ( UINT8 * ) ( temp_buffer ), __SEE_ROM_START, ( __SEE_ROM_END - __SEE_ROM_START ) );
    osal_cache_flush ( temp_buffer, ( __SEE_ROM_END - __SEE_ROM_START ) );
    self_boot ( SEE_ENTRY, (UINT32)(temp_buffer), ( __SEE_ROM_END - __SEE_ROM_START ), SEE_ENTRY );
    FREE ( temp_buffer );

#ifdef M3281_BOOT_WITH_LOGO
    ret = bl_show_logo_init();
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF("%s: logo_init fail!\n",__FUNCTION__);
        goto bl_reboot;
    }
#endif
    dsc_api_attach();
    ce_api_attach();
    see_step1();

    //Apply bc std boot flow
#ifdef BL_BC_STD
    test_flash_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);
#endif

    FIXED_PRINTF ( "Check firmware chunklist.\n" );
#if defined(BL_BC_STD) || defined(BL_BC_AS)
    mg_setup_crc_table();
    if(sto_chunk_check())
    {
        FIXED_PRINTF("firmware chunklist error.\n");
        sys_sw_wrong = 1;
    }
#endif

#ifdef ENABLE_UART_UPG
    if( TRUE == check_sw_upgrade() ) /* force download */
    {
        serial_upgrade();
    }
#endif

#if (!defined(BL_DISABLE_SE))||(defined(BL_BC_AS))
    ret = bl_prepare_key(&pos);
    if(ret!=RET_SUCCESS)
    {
        FIXED_PRINTF("prepare key fail!\n");
        goto bl_reboot;
    }
#endif
#if (!defined(BL_BC_AS) && !defined(BL_BC_STD))
    if(RET_SUCCESS != set_parameter_from_bl())
    {
        FIXED_PRINTF("prepare key from BL fail!\n");
        goto bl_reboot;
    }
#endif
    if ( sys_sw_wrong != 1 )
    {
#ifdef BL_BC_STD    //decrypt Main code
        //    1. get flash dev
        if (test_flash_dev == NULL)
        {
            FIXED_PRINTF("Fail to find flash device!\n");
            sys_sw_wrong =1;
        }
        // 2. [Main chunk]get Chunk Hdr, malloc buf, and get chunk data
        chid = CHUNKID_MAINCODE;
        if(0==sto_get_chunk_header(CHUNKID_MAINCODE, &chunk_hdr))
        {
            FIXED_PRINTF("Fail to get Chunk Header of ID(0x%x)!\n",CHUNKID_MAINCODE);
            sys_sw_wrong =1;
        }
        mpos=(UINT32)sto_chunk_goto(&chid, CHUNKID_MAINCODE_MASK, 1);
        temp1 = ( UINT8* ) (  0xFFFFFFF8 & ( UINT32 ) MALLOC ( chunk_hdr.offset+ 0xf ) );
        if(NULL!=temp1)
        {
            MEMSET(temp1,0xFF,chunk_hdr.offset+ 0xf);
        }
        temp2 = ( UINT8* ) (  0xFFFFFFF8 & ( UINT32 ) MALLOC ( chunk_hdr.offset+ 0xf ) );

        if(NULL!=temp2)
        {
            MEMSET(temp2,0xFF,chunk_hdr.offset+ 0xf);
        }
        sto_get_data(test_flash_dev, temp1, mpos, chunk_hdr.offset);

        // 3. call verifySignature_std
        chkret=verifySignature_std(temp1, temp2, chunk_hdr, &errorCode);
        FIXED_PRINTF("%s-%d:chkret(%d),errorcode(%d)\n",__FILE__,__LINE__,chkret,errorCode);
        if(0==chkret)
        {
            switch(errorCode)
            {
                case 0:
                    break;
                case 1:
                    sys_sw_wrong =1;
                    break;
                case 2:
                    update_flash_data(mpos, chunk_hdr.offset, temp1);
                    FIXED_PRINTF("Finish write back to Main Chunk!");
                    break;
                case 3:
                    do{}while(1);
                    break;
                default:
                    break;
            }
        }
        else if(1==chkret)
        {
            main_decrypted=temp2+CHUNK_HEADER_SIZE;
            cpu_mc_len=chunk_hdr.len-CHUNK_HEADER_SIZE + CHUNK_NAME;
        }
        else
        {
            sys_sw_wrong=1;
        }
#elif defined(BL_BC_AS)
        chid=CHUNKID_MAINCODE;
        block_addr=sto_chunk_goto(&chid, CHUNKID_MAINCODE_MASK, 1);
        if(ERR_FAILUE == block_addr)
        {
            FIXED_PRINTF("FTA: Can't find chunk id 0x%08x.\n", CHUNKID_MAINCODE);
            sys_sw_wrong = 1;    //can not find main, enter ota loader
        }
        else
        {
            block_len=sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);
            main_block = (UINT8*)( (0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)) );
            cpu_mc_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
            FIXED_PRINTF("Main code block_addr=0x%x,block_len=0x%x,cpu_mc_len=0x%x\n", block_addr,block_len,cpu_mc_len);
            sto_get_data(flash_dev, (void *)main_block, block_addr, block_len);

            main_decrypted=main_block+CHUNK_HEADER_SIZE;

            tmp_buffer = (UINT8*)( (0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)) );
            len=cpu_mc_len-(CHUNK_HEADER_SIZE-CHUNK_NAME)-SIGNATURE_SIZE;
            signature=main_decrypted+len;
            maxLen=len;
            mode=0;        //from flash
            ret=verifySignature(signature, main_decrypted, tmp_buffer, len, maxLen, mode,&errorCode);
            FREE(tmp_buffer);
            tmp_buffer=NULL;
            if(ret==1)    //app can be started
            {
                verify_result|=MAIN_OK;
                FIXED_PRINTF("Main code verify ok\n");
            }
            else    // don't start app
            {
                if(errorCode==2)    //store app to flash and reboot later
                {
                    //calculate crc value for chunk header
                    header_crc=mg_table_driven_crc(0xFFFFFFFF, main_block+CHUNK_NAME, cpu_mc_len);
                    *(main_block+CHUNK_CRC)=(UINT8)(header_crc>>24);
                    *(main_block+CHUNK_CRC+1)=(UINT8)(header_crc>>16);
                    *(main_block+CHUNK_CRC+2)=(UINT8)(header_crc>>8);
                    *(main_block+CHUNK_CRC+3)=(UINT8)(header_crc);
                    //memcpy(main_block+CHUNK_CRC,&header_crc,4);
                    FIXED_PRINTF("Main block header_crc=0x%x first byte=0x%x\n",header_crc,*(main_block+CHUNK_CRC));
                    update_flash_data(block_addr, block_len, main_block);

                    FIXED_PRINTF("Main code verify ok and re-encrypt\n");
                }
                else if(errorCode==1)
                {
                    FIXED_PRINTF("Main code verify failed\n");
                }
            }
        }
#else    //FTA
        chid=CHUNKID_MAINCODE;
        block_addr=sto_chunk_goto(&chid, CHUNKID_MAINCODE_MASK, 1);
        if(ERR_FAILUE == block_addr)
        {
            FIXED_PRINTF("FTA: Can't find chunk id 0x%08x.\n", CHUNKID_MAINCODE);
            sys_sw_wrong = 1;    //can not find main, enter ota loader
        }
        block_len=sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);
        main_decrypted = (UINT8*)(0xa0000000|(0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)));
        cpu_mc_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
        FIXED_PRINTF("Main code block_addr=0x%x,block_len=0x%x,cpu_mc_len=0x%x\n", block_addr,block_len,cpu_mc_len);
        sto_get_data(flash_dev, (void *)main_decrypted, block_addr + CHUNK_HEADER_SIZE, cpu_mc_len);
#endif
    }

    if ( sys_sw_wrong != 1 )
    {
#ifdef BL_BC_STD    //decrypt See code
        // 2. [See chunk]get Chunk Hdr, malloc buf, and get chunk data
        chid = CHUNKID_SEECODE;
        if(0==sto_get_chunk_header(CHUNKID_SEECODE, &chunk_hdr))
        {
            FIXED_PRINTF("Fail to get Chunk Header of ID(0x%x)!\n",CHUNKID_SEECODE);
            sys_sw_wrong =1;
        }
        spos=(UINT32)sto_chunk_goto(&chid, CHUNKID_SEECODE_MASK, 1);
        temp3 = ( UINT8* )  ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( chunk_hdr.offset+ 0xf ));

        if(NULL!=temp3)
        {
            MEMSET(temp3,0xFF,chunk_hdr.offset+ 0xf);
        }
        temp4 = ( UINT8* ) ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( chunk_hdr.offset+ 0xf ));

        if(NULL!=temp4)
        {
            MEMSET(temp4,0xFF,chunk_hdr.offset+ 0xf);
        }
        sto_get_data(test_flash_dev, temp3, spos, chunk_hdr.offset);
        FIXED_PRINTF("see: 0x%2x %2x %2x %2x",temp3[0],temp3[1],temp3[2],temp3[3]);
        // 3. call verifySignature_std
        chkret=verifySignature_std(temp3, temp4, chunk_hdr, &errorCode);
        FIXED_PRINTF("%s-%d:chkret(%d),errorcode(%d)\n",__FILE__,__LINE__,chkret,errorCode);
        if(0==chkret)
        {
            switch(errorCode)
            {
                case 0:
                    break;
                case 1:
                    sys_sw_wrong =1;
                    break;
                case 2:
                    update_flash_data(spos, chunk_hdr.offset, temp3);
                    FIXED_PRINTF("Finish write back to See Chunk!");
                    goto bl_reboot;
                    break;
                case 3:
                    goto bl_reboot;
                    break;
                default:
                    break;
            }
        }
    else if(1==chkret)
    {
        see_decrypted=temp4+CHUNK_HEADER_SIZE;
        see_mc_len=chunk_hdr.len-CHUNK_HEADER_SIZE + CHUNK_NAME;
        //for decompress use.
        g_see_unziped = ( UINT8* ) (  ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( see_mc_len * 4 ) ) );
    }
    else
    {
        sys_sw_wrong=1;
    }
#elif defined(BL_BC_AS)
    chid=CHUNKID_SEECODE;
    block_addr=sto_chunk_goto(&chid, CHUNKID_SEECODE_MASK, 1);
    if(ERR_FAILUE == block_addr)
    {
        FIXED_PRINTF("Can't find chunk id 0x%08x.\n", CHUNKID_SEECODE);
        sys_sw_wrong = 1;    //can not find see, enter ota loader
    }
    else
    {
        block_len=sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);
        see_block = (UINT8*)( (0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)) );
        see_mc_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
        FIXED_PRINTF("See code block_addr=0x%x,block_len=0x%x,see_mc_len=0x%x\n", block_addr,block_len,see_mc_len);
        sto_get_data(flash_dev, (void *)see_block, block_addr, block_len);

        see_decrypted=see_block+CHUNK_HEADER_SIZE;

        tmp_buffer = (UINT8*)( (0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)) );
        len=see_mc_len-(CHUNK_HEADER_SIZE-CHUNK_NAME)-SIGNATURE_SIZE;
        signature=see_decrypted+len;
        maxLen=len;
        mode=0;        //from flash
        ret=verifySignature(signature, see_decrypted, tmp_buffer, len, maxLen, mode,&errorCode);
        FREE(tmp_buffer);
        tmp_buffer=NULL;
        if(ret==1)    //app can be started
        {
            verify_result|=SEE_OK;
            FIXED_PRINTF("See code verify ok\n");
            g_see_unziped = ( UINT8* ) ( ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( block_len * 4 ) ) );
        }
        else    // don't start app
        {
            if(errorCode==2)    //store app to flash and reboot later
            {
                //calculate crc value for chunk header
                header_crc=mg_table_driven_crc(0xFFFFFFFF, see_block+CHUNK_NAME, see_mc_len);
                *(see_block+CHUNK_CRC)=(UINT8)(header_crc>>24);
                *(see_block+CHUNK_CRC+1)=(UINT8)(header_crc>>16);
                *(see_block+CHUNK_CRC+2)=(UINT8)(header_crc>>8);
                *(see_block+CHUNK_CRC+3)=(UINT8)(header_crc);
                //memcpy(see_block+CHUNK_CRC,&header_crc,4);
                FIXED_PRINTF("See block header_crc=0x%x first byte=0x%x\n",header_crc,*(see_block+CHUNK_CRC));
                update_flash_data(block_addr, block_len, see_block);

                FIXED_PRINTF("See code verify ok and re-encrypt\n");
            }
            else if(errorCode==1)
            {
                FIXED_PRINTF("See code verify failed\n");
            }
        }
    }
#else
    chid=CHUNKID_SEECODE;
    block_addr=sto_chunk_goto(&chid, CHUNKID_SEECODE_MASK, 1);
    if(ERR_FAILUE == block_addr)
    {
        FIXED_PRINTF("Can't find chunk id 0x%08x.\n", CHUNKID_SEECODE);
        sys_sw_wrong = 1;    //can not find see, enter ota loader
    }
    block_len=sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);
    see_decrypted = (UINT8*)(0xa0000000|(0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)));
    see_mc_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
    FIXED_PRINTF("See code block_addr=0x%x,block_len=0x%x,see_mc_len=0x%x\n", block_addr,block_len,see_mc_len);
    sto_get_data(flash_dev, (void *)see_decrypted, block_addr + CHUNK_HEADER_SIZE, see_mc_len);
    g_see_unziped = ( UINT8* ) ( 0xa0000000 | ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( block_len * 4 ) ) );
#endif
    }

    if ( sys_sw_wrong ) //enter OTA loader
    {
#ifdef BL_BC_STD
        mg_setup_crc_table();
        if ( 0 != find_second_loader() )
        {
            block_addr = g_ota_offset ;
            chunk_hdr.id= sto_fetch_long((UINT32)block_addr + CHUNK_ID);
            chunk_hdr.len= sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
            chunk_hdr.offset=sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);
            chunk_hdr.crc=sto_fetch_long((UINT32)block_addr + CHUNK_CRC);
            temp5 = (UINT8*)(0xFFFFFFF8&(UINT32)MALLOC(chunk_hdr.offset+0xf));
            temp6 = (UINT8*)(0xFFFFFFF8&(UINT32)MALLOC(chunk_hdr.offset+0xf));

            sto_get_data(flash_dev, (void *)temp5, block_addr , chunk_hdr.offset);
            FIXED_PRINTF ( "ota info(hex): id(%x),len(%x),offset(%x),crc(%x)\n",
            chunk_hdr.id,chunk_hdr.len,chunk_hdr.offset,chunk_hdr.crc);
            FIXED_PRINTF ( "Verify OTA data!\n" );
            ret=verifySignature_std(temp5,temp6, chunk_hdr, &errorCode);
            if(ret==1)    //app can be started
            {
                ota_decrypted=temp6+CHUNK_HEADER_SIZE;
                ota_len=chunk_hdr.len-CHUNK_HEADER_SIZE + CHUNK_NAME;
                FIXED_PRINTF("ota loader verify ok\n");
            }
            else    // don't start app
            {
                if(errorCode==2)
                {
                    FIXED_PRINTF("ota loader should not enter here\n");
                }
                else if(errorCode==1)
                {
                    FIXED_PRINTF("ota loader verify failed\n");
                }
                FIXED_PRINTF("verify ota loder error: ret=%d\n", ret);
                pan_display ( panel_dev, "ERR3", 4 );
                goto bl_reboot;
            }
        }
        else
        {
            FIXED_PRINTF("Cannot found ota loader\n");
            pan_display ( panel_dev, "ERR1", 4 );
            goto bl_reboot;
        }
#elif defined(BL_BC_AS) /* BL_BC_STD */
        if(0 != find_second_loader())
        {
            block_addr = g_ota_offset;
            block_len=sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

            ota_decrypted = (UINT8*)( (0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)) );
            ota_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
            FIXED_PRINTF("Ota loader block_addr=0x%x,block_len=0x%x,ota_len=0x%x\n", block_addr,block_len,ota_len);
            sto_get_data(flash_dev, (void *)ota_decrypted, block_addr + CHUNK_HEADER_SIZE, ota_len);

            tmp_buffer = (UINT8*)( (0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)) );
            len=ota_len-(CHUNK_HEADER_SIZE-CHUNK_NAME)-SIGNATURE_SIZE;
            signature=ota_decrypted+len;
            //maxLen=block_len; //Clarify 20120806
            maxLen=len;
            mode=0;        //from flash
            ret=verifySignature(signature, ota_decrypted, tmp_buffer, len, maxLen, mode,&errorCode);
            FREE(tmp_buffer);
            tmp_buffer=NULL;
            if(ret==1)    //app can be started
            {
                verify_result|=OTA_LOADER_OK;
                FIXED_PRINTF("ota loader verify ok\n");
            }
            else    // don't start app
            {
                if(errorCode==2)
                {
                    FIXED_PRINTF("ota loader should not enter here\n");
                }
                else if(errorCode==1)
                {
                    FIXED_PRINTF("ota loader verify failed\n");
                }
            }

            if((verify_result&OTA_LOADER_OK) != OTA_LOADER_OK)
            {
                FIXED_PRINTF("verify ota loder error: verify_result=%d\n", verify_result);
                goto bl_reboot;
            }
            }
            else
            {
                FIXED_PRINTF("Cannot found ota loader\n");
                pan_display(panel_dev, "Err ", 4);
                goto bl_reboot;
            }
#else /* NON BL_BC_STD or BL_BC_AS */
        // not yet implement for FTA version
#endif /* BL_BC_STD */

        bl_enter_ota_loader(ota_decrypted, ota_len);  //if successful, never return
        FIXED_PRINTF("Enter ota loader fail\n");
        goto bl_reboot;
    }

#ifdef BL_BC_AS
        if((verify_result&(MAIN_OK|SEE_OK)) != (MAIN_OK|SEE_OK))
        {
            FIXED_PRINTF("Main and See code verify_result=%d\n", verify_result);
            goto bl_reboot;
        }
#endif
        //enter system software and never return
        bl_enter_sys_sw(see_decrypted, see_mc_len,main_decrypted,cpu_mc_len);
bl_reboot:
        hw_watchdog_reboot(); //loader code error, enter hw reboot
}


