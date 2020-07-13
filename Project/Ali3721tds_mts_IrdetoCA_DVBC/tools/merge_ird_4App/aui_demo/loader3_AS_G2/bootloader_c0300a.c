/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2013 Copyright (C)
*
*    File:    bootloader_c0300a.c
*
*    Description:    This file contains all globe micros and functions declare
*                    of Flash boot loader for C0300A.
*    History:
*           Date            Athor        Version          Reason
*       ============    =============   =========   =================
*   1.  July.16.2013     Ryan.Chen       Ver 0.1    Create file.
*****************************************************************************/

#include "bootloader.h"
#include <bus/i2c/i2c.h>
#include <api/libcas/c0300a/bc_types.h>

#ifdef BL_C0300A_AS
static RET_CODE verify_block(UINT32 block_id, UINT8 *block_buf, UINT32 block_len, UINT32 data_len)
{
    UINT8 mode = 0;
    UINT8 errcode = 0;
    UINT32 len = 0;
    UINT32 maxlen = 0;
    UINT32 signature = 0;
    UINT32 header_crc = 0;
    UINT8 *tmp_buf = NULL;
    UINT8 *decrypted_buf = NULL;
    RET_CODE ret = RET_SUCCESS;

    FIXED_PRINTF("verify chunk(0x08%x)\n", block_id);

    decrypted_buf = block_buf + CHUNK_HEADER_SIZE;

    tmp_buf = (UINT8 *)((0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf)) );
    len = data_len-(CHUNK_HEADER_SIZE-CHUNK_NAME)-SIGNATURE_SIZE;
    signature = decrypted_buf + len;
    maxlen = len;
    mode = 0;     //from flash
    ret = verify_signature(signature, decrypted_buf, tmp_buf, len, maxlen, mode, &errcode);
    FREE(tmp_buf);
    tmp_buf = NULL;

    if ((CHUNKID_MAINCODE == block_id) || \
        (CHUNKID_SEECODE == block_id))
    {
        if (ERR_2 == errcode)    //store app to flash and reboot later
        {
            //calculate crc value for chunk header
            header_crc = mg_table_driven_crc(0xFFFFFFFF, block_buf+CHUNK_NAME, block_len);
            *(block_buf + CHUNK_CRC) = (UINT8)(header_crc >> 24);
            *(block_buf + CHUNK_CRC + 1) = (UINT8)(header_crc >> 16);
            *(block_buf + CHUNK_CRC + 2) = (UINT8)(header_crc >> 8);
            *(block_buf + CHUNK_CRC + 3) = (UINT8)(header_crc);
            //memcpy(main_block+CHUNK_CRC,&header_crc,4);
            FIXED_PRINTF("block header_crc=0x%x first byte=0x%x\n",header_crc,*(block_buf+CHUNK_CRC));
            update_flash_data(block_addr, block_len, block_buf);

            FIXED_PRINTF("verify ok and re-encrypt\n");
        }
        else if(ERR_1 == errcode)
        {
            FIXED_PRINTF("verify failed\n");
        }
    }

    return ret;
}

static void load_and_launch_code(UINT32 chunk_err)
{
    UINT32 chid = 0;
    UINT32 cpu_mc_len=0;
    UINT32 see_mc_len=0;
    UINT8 *main_decrypted = NULL;
    UINT8 *see_decrypted = NULL;
    UINT32 block_addr = 0;
    UINT32 block_len = 0;
    UINT8 sys_sw_wrong = 0;
    RET_CODE ret = RET_SUCCESS;
    UINT8 *main_block = NULL;
    UINT8 *see_block = NULL;

#ifdef _OTA_E_
    UINT32 ota_len = 0;
    UINT8 *ota_decrypted = NULL;
    UINT8 *ota_block = NULL;

#endif

    if (chunk_err != 0)
    {
        goto bl_ota;
    }

    /* main sw verify */
    chid = CHUNKID_MAINCODE;
    if(RET_FAILURE == bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, Can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
        sys_sw_wrong = 1;
        goto bl_ota;
    }
    else if(block_len != 0)
    {
        *(UINT32 *)(0xb8018500) = 0;    // reset watch dog timer

        main_block = (UINT8 *)( (0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf)) );
        cpu_mc_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
        FIXED_PRINTF("Main code block_addr=0x%x,block_len=0x%x,cpu_mc_len=0x%x\n", block_addr,block_len,cpu_mc_len);
        sto_get_data(flash_dev, (void *)main_block, block_addr, block_len);
        main_decrypted = main_block + CHUNK_HEADER_SIZE;

        ret = verify_block(chid, main_block, block_len, cpu_mc_len);
        if (RET_FAILURE == ret)    //app can be started
        {
            FIXED_PRINTF("Main code verify ok\n");
            goto bl_reboot;
        }
    }
    else
    {
        sys_sw_wrong = 1;
        FIXED_PRINTF("Error : %s, maincode len is zero.\n", __FUNCTION__);
        goto bl_ota;
    }

    /* see sw verify */
    chid = CHUNKID_SEECODE;
    if(RET_FAILURE == bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, Can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
        sys_sw_wrong = 1;
        goto bl_ota;
    }
    else if(block_len != 0)
    {
        see_block = (UINT8 *)((0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf)));
        see_mc_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
        FIXED_PRINTF("See code block_addr=0x%x, block_len=0x%x, see_mc_len=0x%x\n", \
                    block_addr, block_len, see_mc_len);
        sto_get_data(flash_dev, (void *)see_block, block_addr, block_len);
        see_decrypted = see_block + CHUNK_HEADER_SIZE;

        ret = verify_block(chid, see_block, block_len, see_mc_len);
        if (RET_SUCCESS == ret)    //app can be started
        {
            FIXED_PRINTF("See code verify ok\n");
            g_see_unziped = (UINT8 *)((0xFFFFFFF8 & (UINT32)MALLOC(block_len * 4)));
        }
        else
        {
            FIXED_PRINTF("verify see error\n");
            goto bl_reboot;
        }
    }
    else
    {
        sys_sw_wrong = 1;
        FIXED_PRINTF("Error : %s, see len is zero.\n", __FUNCTION__);
        goto bl_ota;
    }

bl_ota:
#ifdef _OTA_E_
    if( sys_sw_wrong)
    {
        if (find_second_loader())
        {
            block_addr = g_ota_offset;
            block_len = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

            ota_block = (UINT8 *)((0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf)));
            ota_len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
            FIXED_PRINTF("Ota loader block_addr=0x%x,block_len=0x%x,ota_len=0x%x\n", block_addr, block_len, ota_len);
            sto_get_data(flash_dev, (void *)ota_block, block_addr, block_len);
            ota_decrypted = ota_block + CHUNK_HEADER_SIZE;

            ret = verify_block(CHUNKID_SECLOADER, ota_block, block_len, ota_len);

            if (ret == RET_FAILURE)    //app can be started
            {
                FIXED_PRINTF("verify ota loder error\n");
                goto bl_reboot;
            }
        }
        else
        {
            FIXED_PRINTF("Cannot found ota loader\n");
            goto bl_reboot;
        }

        bl_enter_ota_loader(ota_decrypted, ota_len);  //if successful, never return
        FIXED_PRINTF("Enter ota loader fail\n");
        goto bl_reboot;
    }
#endif // _OTA_E_

    //enter system software and never return
    bl_enter_sys_zip_sw(see_decrypted, see_mc_len, main_decrypted, cpu_mc_len);

bl_reboot:
    FIXED_PRINTF("Bootloader reboot\n");
    hw_watchdog_reboot();
}

#elif defined(BL_C0300A_STD)

static void load_and_launch_code(UINT32 chunk_err)
{
    UINT32 chid = 0;
    UINT32 cpu_mc_len=0;
    UINT32 see_mc_len=0;
    UINT32 ota_len = 0;
    UINT8 *main_decrypted = NULL;
    UINT8 *see_decrypted = NULL;
    UINT8 *ota_decrypted = NULL;
    UINT32 block_addr = 0;
    UINT8 sys_sw_wrong = 0;
    RET_CODE ret = RET_SUCCESS;
    struct sto_device *test_flash_dev = NULL;
    CHUNK_HEADER chunk_hdr = {0};
    UINT8 *temp1 = NULL;
    UINT8 *temp2 = NULL;
    UINT8 *temp3 = NULL;
    UINT8 *temp4 = NULL;
    UINT8 *temp5 = NULL;
    UINT8 *temp6 = NULL;
    UINT8 errcode = 0;
    UINT32 mpos = 0;
    UINT32 spos = 0;

    if (chunk_err != 0)
    {
        goto bl_ota;
    }

    //    1. get flash dev
    test_flash_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);
    if (NULL == test_flash_dev)
    {
        FIXED_PRINTF("Fail to find flash device!\n");
        goto bl_reboot;
    }
    // 2. [Main chunk]get Chunk Hdr, malloc buf, and get chunk data
    chid = CHUNKID_MAINCODE;
    if(0==sto_get_chunk_header(CHUNKID_MAINCODE, &chunk_hdr))
    {
        FIXED_PRINTF("Fail to get Chunk Header of ID(0x%x)!\n",CHUNKID_MAINCODE);
        sys_sw_wrong =1;
        goto bl_ota;
    }

    // reset watch dog timer
    *(UINT32 *)(0xb8018500) = 0;

    mpos = (UINT32)sto_chunk_goto(&chid, CHUNKID_MAINCODE_MASK, 1);
    temp1 = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(chunk_hdr.offset + 0xf));
    if(NULL != temp1)
    {
        MEMSET(temp1, 0xFF, chunk_hdr.offset);
    }

    temp2 = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(chunk_hdr.offset + 0xf));
    if(NULL != temp2)
    {
        MEMSET(temp2, 0xFF, chunk_hdr.offset);
    }
    sto_get_data(test_flash_dev, temp1, mpos, chunk_hdr.offset);

    // 3. call verifySignature_std
    ret = verify_signature_std(temp1, temp2, chunk_hdr, &errcode);
    FIXED_PRINTF("%s-%d:chkret(%d),errorcode(%d)\n", __FILE__, __LINE__, ret, errcode);
    if (RET_FAILURE == ret)
    {
        if (ERR_1 == errcode)
        {
            sys_sw_wrong =1;
        }
        else if (ERR_2 == errcode)
        {
            update_flash_data(mpos, chunk_hdr.offset, temp1);
            FIXED_PRINTF("Finish write back to Main Chunk!");
        }
        else if (ERR_3 == errcode)
        {
           goto bl_reboot;
        }
    }
    else if(RET_SUCCESS == ret)
    {
        main_decrypted = temp2 + CHUNK_HEADER_SIZE;
        cpu_mc_len = chunk_hdr.len - CHUNK_HEADER_SIZE + CHUNK_NAME;
    }

   // 2. [See chunk]get Chunk Hdr, malloc buf, and get chunk data
    chid = CHUNKID_SEECODE;
    if (0 == sto_get_chunk_header(CHUNKID_SEECODE, &chunk_hdr))
    {
        FIXED_PRINTF("Fail to get Chunk Header of ID(0x%x)!\n",CHUNKID_SEECODE);
        sys_sw_wrong = 1;
        goto bl_ota;
    }
    spos= (UINT32)sto_chunk_goto(&chid, CHUNKID_SEECODE_MASK, 1);
    temp3 = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(chunk_hdr.offset + 0xf));

    if (NULL != temp3)
    {
        MEMSET(temp3, 0xFF, chunk_hdr.offset);
    }
    temp4 = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(chunk_hdr.offset + 0xf));

    if (NULL != temp4)
    {
        MEMSET(temp4,0xFF,chunk_hdr.offset);
    }
    sto_get_data(test_flash_dev, temp3, spos, chunk_hdr.offset);
    FIXED_PRINTF("see: 0x%2x %2x %2x %2x",temp3[0],temp3[1],temp3[2],temp3[3]);
    // 3. call verifySignature_std
    ret=verify_signature_std(temp3, temp4, chunk_hdr, &errcode);
    FIXED_PRINTF("%s-%d:chkret(%d),errorcode(%d)\n",__FILE__,__LINE__,ret,errcode);
    if (RET_FAILURE == ret)
    {
        if (ERR_1 == errcode)
        {
            sys_sw_wrong =1;
        }
        else if (ERR_2 == errcode)
        {
            update_flash_data(spos, chunk_hdr.offset, temp3);
            FIXED_PRINTF("Finish write back to See Chunk!");
        }
        else if (ERR_3 == errcode)
        {
            goto bl_reboot;
        }
    }
    else if(RET_SUCCESS == ret)
    {
        see_decrypted = temp4 + CHUNK_HEADER_SIZE;
        see_mc_len = chunk_hdr.len - CHUNK_HEADER_SIZE + CHUNK_NAME;
            //for decompress use.
        g_see_unziped = (UINT8 *)((0xFFFFFFF8 & (UINT32)MALLOC(see_mc_len * 4)));
    }

bl_ota:
#ifdef _OTA_E_
    if( sys_sw_wrong)
    {
        mg_setup_crc_table();
        if ( 0 != find_second_loader() )
        {
            block_addr = g_ota_offset ;
            chunk_hdr.id = sto_fetch_long((UINT32)block_addr + CHUNK_ID);
            chunk_hdr.len = sto_fetch_long((UINT32)block_addr + CHUNK_LENGTH);
            chunk_hdr.offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);
            chunk_hdr.crc = sto_fetch_long((UINT32)block_addr + CHUNK_CRC);
            temp5 = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(chunk_hdr.offset + 0xf));
            temp6 = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(chunk_hdr.offset + 0xf));

            sto_get_data(flash_dev, (void *)temp5, block_addr , chunk_hdr.offset);
            FIXED_PRINTF("ota info(hex): id(%x),len(%x),offset(%x),crc(%x)\n",
            chunk_hdr.id,chunk_hdr.len,chunk_hdr.offset,chunk_hdr.crc);
            FIXED_PRINTF("Verify OTA data!\n");
            ret = verify_signature_std(temp5, temp6, chunk_hdr, &errcode);
            if(ret == RET_SUCCESS)  //app can be started
            {
                ota_decrypted = temp6 + CHUNK_HEADER_SIZE;
                ota_len = chunk_hdr.len - CHUNK_HEADER_SIZE + CHUNK_NAME;
                FIXED_PRINTF("ota loader verify ok\n");
            }
            else     // don't start app
            {
                FIXED_PRINTF("verify ota loder error: ret=%d, errcode = %d\n", ret, errcode);
                goto bl_reboot;
            }
        }
        else
        {
            FIXED_PRINTF("Cannot found ota loader\n");
            goto bl_reboot;
        }
    }
#endif

    //enter system software and never return
    bl_enter_sys_zip_sw(see_decrypted, see_mc_len, main_decrypted, cpu_mc_len);

bl_reboot:
    FIXED_PRINTF("Bootloader reboot\n");
    hw_watchdog_reboot();
}
#endif

void app_init(void)
{
    UINT8 sys_sw_wrong = 0;
    UINT32 pos = 0;

    /* Init UART */
    sys_uart_init();
    /*bl_see boot*/
    bl_init_see(SEE_ENTRY + 0x01000000);

    g_boot_type = sys_ic_get_boot_type();
    FIXED_PRINTF("g_boot_type = %d\n", g_boot_type);

    boot_enter_standby();

    sys_gpio_init();
    sys_panel_init();
    panel_dev = (struct pan_device *)dev_get_by_id(HLD_DEV_TYPE_PAN, 0);
    pan_display(panel_dev, " ON ", 4);
    FIXED_PRINTF("sys_panel_init\n");
    bl_init_flash();
    FIXED_PRINTF("bl_init_flash\n");

    dsc_api_attach();
    ce_api_attach();
    see_step1();

#ifdef BL_C0300A_STD
    test_flash_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);
#endif

    mg_setup_crc_table();
    if(sto_chunk_check())
    {
        FIXED_PRINTF("firmware chunklist error.\n");
        sys_sw_wrong = 1;
    }

#ifdef ENABLE_UART_UPG
    if( TRUE == check_sw_upgrade() ) /* force download */
    {
        serial_upgrade();
    }
#endif

    if(RET_SUCCESS != bl_prepare_key(&pos))
    {
        FIXED_PRINTF("prepare key fail!\n");
        goto bl_reboot;
    }

    load_and_launch_code(sys_sw_wrong);

bl_reboot:
    FIXED_PRINTF("Bootloader reboot\n");
    hw_watchdog_reboot();
}

