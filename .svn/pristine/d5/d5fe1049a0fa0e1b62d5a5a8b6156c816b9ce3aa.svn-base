/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2013 Copyright (C)
*
*    File:    bootinit.c
*
*    Description:    This file contains HLD functions and device initialize function
*                     declare of ALi boot loader.
*
*
*****************************************************************************/
#include "bootloader.h"

UINT32 unzip_length = 0;
#if(defined(ENABLE_4M_FLASH))
UINT32 g_ota_offset = 0;
#endif

#ifdef FAKE_VERITY_SIGNATURE
static UINT8 magic[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};
#endif

#ifdef DUAL_CPU
static UINT32 see_unzip_length = 0;
#endif

#ifndef _LINUX_BOOTLOADER_
static UINT32 g_unzip_length = 0;
#endif

static UINT8 *g_see_unziped = NULL;
struct pan_device *panel_dev = NULL;
struct sto_device *flash_dev = NULL;

#ifdef BL_C0300A_AS
static INT32 handle_chunk_data(UINT8 *data, UINT32 length);
#endif

#ifdef ENABLE_UART_UPG
static INT32 update_flash_data(UINT32 offset, INT32 len, UINT8 *data)
{
    UINT8 *app_flash_buffer = NULL;
    INT32 ret = 0;
    struct sto_device *sto_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);

    if (NULL == data)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, data is NULL\n", __FUNCTION__);
        return RET_FAILURE;
    }

    FIXED_PRINTF("%s-offset(0x%x),len(0x%x),data(0x %2x %2x %2x %2x)\n",
    __FUNCTION__, offset, len, data[0], data[1], data[2], data[3]);
    app_flash_buffer = (UINT8 *)MALLOC(64 * 1024);
    if (NULL == app_flash_buffer)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
        return RET_FAILURE;
    }

    sto_io_control(sto_dev, STO_DRIVER_SECTOR_BUFFER, (UINT32)app_flash_buffer);
    sto_io_control(sto_dev, STO_DRIVER_SET_FLAG, STO_FLAG_AUTO_ERASE|STO_FLAG_SAVE_REST);

    ret = sto_put_data(sto_dev, (UINT32)offset, data, (INT32)len);

    sto_io_control(sto_dev, STO_DRIVER_SECTOR_BUFFER, 0);
    sto_io_control(sto_dev, STO_DRIVER_SET_FLAG, 0);

    FREE(app_flash_buffer);
    app_flash_buffer = NULL;
    return ret;
}
#endif

void boot_enter_standby(void)
{
    UINT32 boot_code = 0;
    UINT8  boot_type = 0;

    if (1 != g_boot_type)
    {
        boot_code = *(UINT32 *)(0xA0000110);
        /* Cold bootup */
        boot_type = *(UINT8 *)(SYS_FLASH_BASE_ADDR + HW_SET_BOOTTYPE);
        if ((boot_type & BOOT_TYPE_MASK) && \
            (DEAD3BEE == boot_code))
        {
            /* If cold bootup and enter standby enabled, enter standby */
            sys_ic_enter_standby(0, 0);
        }
    }
    else
    {
        /*transfer S5 and S7 to 220 for linux reboot get timer*/
        //if(boot_type == 0xdead1bee)
        {
            SET_DWORD(0xA0000220, GET_DWORD(0xA0000110));
            SET_DWORD(0xA0000224, GET_DWORD(0xA0000114));
            SET_DWORD(0xA0000228, GET_DWORD(0xA0000118));
        }
    }
}

//Apply c0300a std boot flow
#ifdef BL_C0300A_STD
static RET_CODE verify_signature_std(UINT8 *src, UINT8 *dest, CHUNK_HEADER hdr,UINT8 *errcode)
{
    RET_CODE ret = RET_FAILURE;
    INT32 val = 0;
    UINT8 kid = 0;

    if ((NULL == src) || \
        (NULL == dest) || \
        (NULL == errcode))
    {
        FIXED_PRINTF("Error : %s, invalid parameter\n", __FUNCTION__);
        return ret;
    }

    FIXED_PRINTF("Verify chunk (0x%x)!\n", hdr.id);
    *errcode = ERR_1;

    if (NO_CRC != hdr.crc)
    {
        kid = 1;    //common key
        FIXED_PRINTF("Use Common Key!\n");
    }
    else
    {
        FIXED_PRINTF("Use AES Key!\n");
    }

    ret = aes_cbc_std(0, kid, src, dest);
    FIXED_PRINTF("%s-run aes_cbc_std , ret: %d.\n", __FUNCTION__, ret);

    ret = fetch_sys_pub_key(1);
    if (RET_SUCCESS != ret)
    {
        RSA_PRINTF("Error : %s, fetch system software public key fail!(%x)\n", __FUNCTION__, ret);
        return ret;
    }

    val = test_rsa_ram((UINT32)dest + CHUNK_HEADER_SIZE, hdr.len - CHUNK_HEADER_SIZE + CHUNK_NAME);
    FIXED_PRINTF("%s-run Test_RSA_Ram , ret: %d.\n", __FUNCTION__, val);
    if (RET_SUCCESS != val)        //case of no valid signature
    {
        if(-2 == val)    //Special case during MP (No RSA Key)
        {
            FIXED_PRINTF("Skip RSA Check, due to Zero RSA Key!\n");
            *errcode = NO_ERR;
            ret = RET_SUCCESS;
        }
        else
        {
            FIXED_PRINTF("No valid signature!\n");
            if (1 == kid)
            {
                *errcode = ERR_3;    //Need hang up, since check fail with common key
            }
            else
            {
                *errcode = ERR_1;
            }
            return val;
        }
    }

    //valid signature
    if (0 == kid)
    {
        FIXED_PRINTF("Success to check chunk.\n");
        *errcode = NO_ERR;
        ret = RET_SUCCESS;
    }
    else if (1 == kid)
    {
        MEMSET(src, 0xFF, hdr.offset);
        val = aes_cbc_std(1, 0, dest, src);
        if (0 == val)
        {
            FIXED_PRINTF("Need to store data to flash!\n");
            *errcode = ERR_2;    //case of need to store reEnc code to flash
        }
        else if (-2 == val)    //special case during MP Flow (No AES Key)
        {
            FIXED_PRINTF("Spcial case during MP !\n");
            *errcode = NO_ERR;
            ret = RET_SUCCESS;
        }
    }

    return ret;
}

static RET_CODE handle_chunk_data_std(UINT8 *data, UINT32 length)
{
    RET_CODE ret = RET_FAILURE;
    UINT8 *tmp_buffer = NULL;
    UINT8 errcode = 0;
    UINT32 chunk_id = 0;
    UINT32 block_len = 0;
    UINT32 pre_chunk_id =0;
    UINT32 pre_chunk_offset = 0;
    INT32 ret_val = 0;
    CHUNK_HEADER tchunk_hdr = {0};
    UINT32 block_addr = 0;

    if (NULL == data)
    {
        FIXED_PRINTF("Error : %s, invalid parameter!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    tchunk_hdr.id = fetch_long(data + CHUNK_ID);
    tchunk_hdr.len = fetch_long(data + CHUNK_LENGTH);
    tchunk_hdr.offset = fetch_long(data + CHUNK_OFFSET);
    tchunk_hdr.crc = fetch_long(data + CHUNK_CRC);

    chunk_id = tchunk_hdr.id;
    block_len = tchunk_hdr.offset;
    tmp_buffer = (UINT8*)(0xa0000000|(0xFFFFFFF8&(UINT32)MALLOC(block_len + 0xf)));
    if (NULL == tmp_buffer)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
        return RET_FAILURE;
    }

    ret = verify_signature_std(data, tmp_buffer, tchunk_hdr, &errcode);
    FIXED_PRINTF("%s:chkret(%d),errorcode(%d)\n", __FILE__, ret, errcode);
    if (RET_SUCCESS != ret)
    {
        if (ERR_3 == errcode)
        {
            pan_display(panel_dev, "ERRC", 4);
            do
            {
                ;
            }
            while(1);
        }
        else if (ERR_2 == errcode)
        {
            switch (chunk_id)
            {
                case CHUNKID_MAINCODE:
                    block_addr = sto_chunk_goto(&chunk_id, CHUNKID_MAINCODE_MASK, 1);
                    if (ERR_FAILUE == block_addr)
                    {
                        pre_chunk_id = CHUNKID_STBINFO;
                        pre_chunk_offset=0;

                        block_addr = sto_chunk_goto(&pre_chunk_id, CHUNKID_STBINFO_MASK, 1);
                        pre_chunk_offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

                        if(ERR_FAILUE == block_addr)
                        {
                            ret_val = -1;
                        }
                        else
                        {
                            block_addr += pre_chunk_offset;
                        }
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
                        {
                            ret_val = -1;
                        }
                        else
                        {
                            block_addr += pre_chunk_offset;
                        }
                    }
                    break;

                default:
                //not supported chunk id in force download
                    ret_val = -1;
                    break;
            }

            if (0 == ret_val)
            {
                pan_display(panel_dev, "BURN", 4);
                update_flash_data(block_addr, block_len, data);
                ret = RET_SUCCESS;
            }
            else
            {
                pan_display(panel_dev, "FAIL", 4);
                ret = RET_FAILURE;
                do
                {
                    ;
                }
                while(1);
            }
        }
        else if (ERR_1 == errcode)
        {
            ret = RET_FAILURE;
        }
    }

    FREE(tmp_buffer);
    tmp_buffer = NULL;

    return ret;
}
#endif

#ifdef ENABLE_UART_UPG
static void nosdelay(UINT32 timeout)
{
    UINT32 stamp = 0;

    stamp = read_tsc();
    while(read_tsc() - stamp < timeout*MS_TICKS)
    {
        ;
    }
}

RET_CODE check_sw_upgrade(void)
{
    BOOL ret = RET_FAILURE;
    UINT32 dwtick = 0;
    UINT8  ch = 0;

    dwtick = read_tsc();
    do
    {
        if ((SUCCESS == sci_read_tm(SCI_FOR_RS232, &ch, 5)) && \
            ('c' == ch))
        {
            ret = RET_SUCCESS;
            break;
        }
        else
        {
            ch = 0;
        }
    }while (read_tsc() - dwtick < WAIT_300MS);

    return ret;
}

void serial_upgrade(void)
{
    hw_watchdog_stop();
#ifdef BL_C0300A_STD
    lib_ash_set_data_callback(handle_chunk_data_std);
#elif defined BL_C0300A_AS
    lib_ash_set_data_callback(handle_chunk_data);
#endif
    lib_ash_shell();
}
#endif

UINT8 *expand_ram(UINT32 addr, UINT32 len, int unzip(UINT8 *, UINT8 *, UINT8 *), UINT32 type)
{
    UINT8 *buffer = NULL;
    UINT8 *codeentry = NULL;

    if ((MAIN_CODE == type) || \
        (OTA_CPU_CODE == type))
    {
        codeentry = (UINT8 *)MAIN_ENTRY;
    }
    else if ((SEE_CODE == type) || \
             (OTA_SEE_CODE == type))
    {
        codeentry = g_see_unziped;
    }

    buffer = (UINT8 *)malloc(BUFFER_SIZE);

    if (NULL == buffer)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed!\n", __FUNCTION__);
        return 0;
    }

    if (0 != unzip((void *)(addr), codeentry, buffer))
    {
        codeentry = 0;
        FIXED_PRINTF("Error: error to decompress chunk(type %d)!\n", type);
    }
    else
    {
#if defined(BL_C0300A_STD) || defined(BL_C0300A_AS)
        if ((MAIN_CODE == type) || \
            (OTA_CPU_CODE == type))
        {
            unzip_length = GET_DWORD(buffer);
        }
        else if ((SEE_CODE == type) || \
                 (OTA_SEE_CODE == type))
        {
            see_unzip_length = GET_DWORD(buffer);
        }
#else
        unzip_length = GET_DWORD(buffer);
#endif
    }

    osal_cache_flush(codeentry, unzip_length);
    FREE(buffer);
    buffer = NULL;

    return codeentry;
}

void set_os_config(UINT16 task_num, UINT16 sema_num, UINT16 flg_num, UINT16 mbf_num, UINT16 mutex_num)
{
    struct os_config *ptr = (struct os_config *)0xa00001e0;

    ptr->task_num = task_num;
    ptr->sema_num = sema_num;
    ptr->flg_num = flg_num;
    ptr->mbf_num = mbf_num;
    ptr->mutex_num = mutex_num;
    ptr->parity_value = ptr->task_num + \
                        ptr->sema_num + \
                        ptr->flg_num + \
                        ptr->mbf_num + \
                        ptr->mutex_num;
}

#ifndef _LINUX_BOOTLOADER_
static void bl_enter_ota_loader(UINT8 *ota_decrypted, UINT32 ota_len)
{
    UINT32 chunk_head_length = 128;
    UINT32 ota_cpu_len = 0;
    UINT32 ota_see_addr = 0;
    UINT32 ota_see_len = 0;
    UINT32 ziped_len = 0;
    UINT8 *p = NULL;
    UINT8 *temp_buf = NULL;
    UINT8 *ota_entry = NULL;
    UINT8 *main_entry = NULL;
    UINT8 *see_entry = NULL;

    if (NULL == ota_decrypted)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, ota_decrypted is NULL\n", __FUNCTION__);
        return ;
    }

    FIXED_PRINTF("\nEnter OTA loader by sys_sw_wrong \n");
    p = ota_decrypted + (ota_len - 0x200);
    ziped_len = (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24));
    temp_buf = expand_ram((UINT32)ota_decrypted, ziped_len, un7zip, OTA_CPU_CODE);

    ota_entry = (UINT8 *)MALLOC(g_unzip_length + 0xf);
    if (NULL == ota_entry)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
        return ;
    }

    ota_entry = (UINT8 *)((0xFFFFFFF8 & (UINT32)(ota_entry)));
    FIXED_PRINTF("ota_entry: 0x%08x\n", ota_entry);
    MEMCPY(ota_entry, (UINT8 *)MAIN_ENTRY, g_unzip_length);

    p = ota_entry + 0x4;
    ota_cpu_len = (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24));
    p = ota_entry + 0x8;
    ota_see_addr = (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24));
    p = ota_entry + ota_see_addr + 0x4;
    ota_see_len = (p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24));
    FIXED_PRINTF("\n cpu:0x%x,see:0x%x,0x%x\n", ota_cpu_len, ota_see_len, ota_see_addr);

    //excute see ota code
    FIXED_PRINTF("expand ota see code, ziped len: %d\n", ota_see_len);
    //for decompress use.
    g_see_unziped = (UINT8 *)MALLOC(ota_see_len * 4 + 0xf);
    if (NULL == g_see_unziped)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
        return ;
    }

    osal_cache_invalidate(g_see_unziped, ota_see_len * 4 + 0xf);
    g_see_unziped = (UINT8 *)(0xa0000000 | (0xFFFFFFF8 & (UINT32)g_see_unziped));

    see_entry = expand_ram((UINT32)(ota_entry + ota_see_addr + chunk_head_length), ota_see_len, un7zip, OTA_SEE_CODE);
    if (see_entry)
    {
        osal_cache_flush(g_see_unziped, ota_see_len * 4);
        FIXED_PRINTF("success, unziped len: %d,g_see_unziped:0x%08x\n", g_unzip_length, g_see_unziped);
        self_boot(SEE_ENTRY, (UINT32)see_entry, g_unzip_length, 0);
    }
    //excute cpu ota code
    FIXED_PRINTF("expand ota cpu code, ziped len: %d\n", ota_cpu_len);
    main_entry = expand_ram((UINT32)(ota_entry + chunk_head_length), ota_cpu_len, un7zip, OTA_CPU_CODE);
    if (main_entry)
    {
        set_os_config(128, 64, 64, 64, 64);
        FIXED_PRINTF("success, unziped len: %d\n", g_unzip_length);
        hw_watchdog_stop();
        exec((UINT32)main_entry);
    }

    return ;
}

UINT8 *bl_unzip_sw(UINT8 *decrypted, UINT32 mc_len,UINT32 type)
{
    UINT32 ziped_len = 0;
    UINT8 *p = NULL;
    UINT8 *entry = NULL;

    if (NULL == decrypted)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, decrypted is NULL\n", __FUNCTION__);
        return 0;
    }

    p = decrypted + (mc_len - 0x200);
    ziped_len = p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24);
    FIXED_PRINTF("expand code, ziped len: 0x%x\n", ziped_len);
#ifdef LZO_COMPRESS_ENABLE
    entry = expand_ram((UINT32)decrypted, ziped_len, unlzo, type);
#else
    entry = expand_ram((UINT32)decrypted, ziped_len, un7zip, type);
#endif

    return entry;
}
#endif

RET_CODE bl_enter_sys_zip_sw(UINT8 *zip_see, UINT32 see_mc_len,UINT8 *zip_main, UINT32 cpu_mc_len)
{
    UINT32 ziped_len = 0;
    UINT8 *p = NULL;
    UINT8 *main_entry = NULL;

#ifdef DUAL_CPU
    UINT8 *see_entry = NULL;
    UINT8 *see_ram_address = NULL;

#endif

    if ((NULL == zip_main) || \
        (0 == cpu_mc_len))
    {
        return RET_FAILURE;
    }

#ifdef DUAL_CPU
    if ((NULL == zip_see) || \
        (0 == see_mc_len))
    {
        return RET_FAILURE;
    }

    see_ram_address = (UINT8 *)bl_config_memory(NULL, NULL);

    p = zip_see + ( see_mc_len - 0x200 );
    ziped_len = p[3] | (p[2] << 8) | (p[1] << 16) | (p[0] << 24);
    //enter Maincode
    FIXED_PRINTF("expand see main code, ziped len: %d\n", ziped_len);
#ifdef LZO_COMPRESS_ENABLE
    see_entry = expand_ram((UINT32)zip_see, ziped_len, unlzo, SEE_CODE);
#else
    see_entry = expand_ram((UINT32)zip_see, ziped_len, un7zip, SEE_CODE);
#endif
    see_unzip_length = unzip_length;
    FIXED_PRINTF("expand see, unzip_length = 0x%x\n", unzip_length);
#endif

    p = zip_main + ( cpu_mc_len - 0x200 );
    ziped_len = p[3] | ( p[2] << 8 ) | ( p[1] << 16 ) | ( p[0] << 24 );
    FIXED_PRINTF("expand cpu main code, ziped len: %d\n", ziped_len);
#ifdef LZO_COMPRESS_ENABLE
    main_entry = expand_ram((UINT32)zip_main, ziped_len, unlzo, MAIN_CODE);
#else
    main_entry = expand_ram((UINT32)zip_main, ziped_len, un7zip, MAIN_CODE);
#endif

#if (defined DUAL_CPU)
    if (see_entry)
    {
        FIXED_PRINTF("success, unziped len: %d,see entry = 0x%x,\n", see_unzip_length, see_entry);
        osal_cache_flush(see_entry, see_unzip_length);
#ifndef DUAL_ENABLE
        FIXED_PRINTF("run see, see_entry = 0x%x!\n", see_entry);
        see_boot_init(see_entry, see_unzip_length, see_ram_address);
        see_boot_ex();
        //wait for see copy finish
        wait_see_done();
        bl_see_boot(see_ram_address);
#else
        self_boot(SEE_ENTRY, (UINT32)see_entry, see_unzip_length, 0);
#endif
        set_see_boot_flag();
    }
    else
    {
        return RET_FAILURE;
    }
#endif

    if (main_entry)
    {
        FIXED_PRINTF("success, unziped len: %d.\n", unzip_length);
        set_os_config(128, 64, 64, 64, 64);
        FIXED_PRINTF("jump to fw entry=%x\n", main_entry);
        hw_watchdog_stop();
        osal_cache_flush(main_entry, unzip_length);
        exec((UINT32)main_entry);

        return RET_SUCCESS; // never return
    }
    else
    {
        return RET_FAILURE;
    }
}

RET_CODE bl_enter_sys_sw(UINT8 *main_entry, UINT32 cpu_mc_len)
{
    if ((NULL == main_entry) || \
        (0 == cpu_mc_len))
    {
        return RET_FAILURE;
    }

    FIXED_PRINTF("success, cpu len: %d.\n", cpu_mc_len);
    set_os_config(128, 64, 64, 64, 64);
    FIXED_PRINTF("jump to fw entry=%x\n", main_entry);
    hw_watchdog_stop();
    osal_cache_flush(main_entry, cpu_mc_len);
    exec((UINT32)main_entry);

    return RET_SUCCESS;
}

RET_CODE bl_get_chunk_len(UINT32 id, UINT32 *addr, UINT32 *len)
{
    INT32 ret = 0;
    CHUNK_HEADER chunk_hdr;

    if ((NULL == addr) || \
        (NULL == len))
    {
        FIXED_PRINTF("Error : %s, invalid parameter, addr is NULL!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    ret = sto_get_chunk_header(id, &chunk_hdr);
    if (0 == ret)
    {
        return RET_FAILURE;
    }

    *addr = sto_chunk_goto(&id, 0xFFFFFFFF, 1) + CHUNK_HEADER_SIZE;
    *len = chunk_hdr.len - CHUNK_HEADER_SIZE + CHUNK_NAME;

    return RET_SUCCESS;
}

void bl_init_flash(void)
{
#ifdef _LINUX_BOOTLOADER_
    UINT8 *aboot_buf = NULL;

#endif

    if (BOOT_TYPE_NAND != g_boot_type)
    {
        //init flash device
        SET_DWORD(0xb802e098, (GET_DWORD(0xb802e098) | 0xc2000000));

#ifndef ENABLE_SERIAL_FLASH
#ifndef _LINUX_BOOTLOADER_
        flash_info_pl_init();
#endif
        sto_local_flash_attach(NULL);
#else
#ifndef _LINUX_BOOTLOADER_
        flash_info_sl_init();
#endif
        sto_local_sflash_attach(NULL);
#endif
    }
    else
    { // Nand boot
#ifdef _LINUX_BOOTLOADER_
        if (0 != bl_init_nand())
        {
            FIXED_PRINTF("Nand Flash init fail.\n");
            hw_watchdog_reboot();
        }

        //Copy bootloader code from nandflash to ram address 0xA8000000
        FIXED_PRINTF("Load bootloader:\n");
        aboot_buf = (UINT8*)RAM_BASE_ADDR;
        // the loader_len of M3503 is just only the bootloader real size
        if (0 != api_load_data_from_nandflash(g_nand_info.loader_start, 0x200000, aboot_buf))
        {
            FIXED_PRINTF("Load aboot fail\n");
            hw_watchdog_reboot();
        }

        sto_local_sflash_attach(NULL);
#else
        FIXED_PRINTF("%s, Unsupported boot type.\n", __FUNCTION__);
        hw_watchdog_reboot();
#endif
    }

    flash_dev = (struct sto_device *)dev_get_by_type(NULL, HLD_DEV_TYPE_STO);
    if (NULL == flash_dev)
    {
        FIXED_PRINTF("Can't find FLASH device!\n");
    }
    sto_open(flash_dev);
    sto_chunk_init(0, flash_dev->totol_size);
}

RET_CODE bl_init_logo(void)
{
#ifdef _BOOT_LOGO_
    UINT32 chid = 0;
    UINT32 block_addr = 0;
    UINT32 block_len = 0;
    UINT8 *logo_buf = NULL;
    RET_CODE ret = RET_FAILURE;

    chid = CHUNKID_LOGO;
    block_len = 0;
    if(RET_FAILURE == bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, Can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
        return ret;
    }
    else if(0 != block_len)
    {
        logo_buf = (UINT8*)(0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf));
        if (NULL == logo_buf)
        {
            FIXED_PRINTF("Error : %s, allocate buffer for logo failed!\n", __FUNCTION__);
            return ret;
        }

        sto_get_data(flash_dev, logo_buf, block_addr, block_len);
        FIXED_PRINTF("load logo, %x, %x, %x.\n", logo_buf, block_len, chid);

        ret = bl_show_logo(logo_buf, block_len);
        return ret;
    }        
    else
    {
        FIXED_PRINTF("Error : %s, logo len is zero.\n", __FUNCTION__);
        return ret;
    }
#else
    return RET_SUCCESS;
#endif
}

#ifdef DUAL_ENABLE
RET_CODE bl_init_see(UINT32 see_entry)
{
    UINT8 *temp_buf = NULL;

    temp_buf = (UINT8*)(0xFFFFFFF8 & (UINT32)MALLOC(__SEE_ROM_END - __SEE_ROM_START + 0xf));
    if (NULL == temp_buf)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    /* Copy Mini See */
    MEMCPY((UINT8 *)(temp_buf), __SEE_ROM_START, (__SEE_ROM_END - __SEE_ROM_START));
    osal_cache_flush(temp_buf,(__SEE_ROM_END - __SEE_ROM_START));
    //See Self boot
    self_boot(see_entry, (UINT32)temp_buf, (__SEE_ROM_END - __SEE_ROM_START), see_entry);
    FREE(temp_buf);
    temp_buf = NULL;

    return RET_SUCCESS;
}
#endif

INT32 check_program(void)
{
    UINT8 *buffer = 0;
    UINT32 data_id = 0;
    UINT32 data_len = 0;
    UINT32 data_off = 0;
    UINT32 data_crc = 0;
    UINT32 crc = 0;
    UINT32 pointer = 0;

    do
    {
        data_id  = sto_fetch_long((UINT32)pointer + CHUNK_ID);
        data_len = sto_fetch_long((UINT32)pointer + CHUNK_LENGTH);
        data_off = sto_fetch_long((UINT32)pointer + CHUNK_OFFSET);
        data_crc = sto_fetch_long((UINT32)pointer + CHUNK_CRC);

        if (0 != pointer)
        {
            if (0xFF != (((data_id >> 16) & 0xFF) + ((data_id >> 24) & 0xFF)))
            {
                return ERR_1;
            }
        }
        if ((INT32)data_off > flash_dev->totol_size)
        {
            FIXED_PRINTF("@pointer[%08X] id[%08X] data_off[%08X] > flash size\n", \
                  pointer, data_id, data_off);
            return ERR_2;
        }
        if ((data_off != 0) && \
            (data_len > data_off))
        {
            FIXED_PRINTF("@pointer[%08X] id[%08X] data_len[%08X] > data_off[%08X]\n", \
                  pointer, data_id, data_len, data_off);
            return ERR_3;
        }
        if (data_crc != NO_CRC)
        {
            if (NULL == (buffer = (UINT8 *)MALLOC(data_len)))
            {
                ASSERT(0);
            }
            sto_get_data(flash_dev, buffer, pointer + 16, data_len);
            crc = mg_table_driven_crc(0xFFFFFFFF, buffer, data_len);
            FREE(buffer);
            if (data_crc != crc)
            {
                FIXED_PRINTF("@pointer[%08X] id[%08X] crc[%08X] != data_crc[%08X]\n", \
                    pointer, data_id, crc, data_crc);
                return ERR_4;
            }
        }
        pointer += data_off;
        if ((INT32)(pointer + CHUNK_HEADER_SIZE) > flash_dev->totol_size)
        {
            FIXED_PRINTF("@pointer[%08X] no space for header\n", pointer);
            return ERR_5;
        }

    }while (data_off);

    return NO_ERR;
}

#if (defined(ENABLE_4M_FLASH))
UINT8 find_second_loader(void)
{
    UINT32 pointer = 0;
    UINT32 data_id = 0;
    UINT32 data_len = 0;
    UINT32 data_off = 0;
    UINT32 data_crc = 0;
    UINT8 *buffer = NULL;
    UINT32 crc = 0;
    UINT8 b_secondota = 0;

    FIXED_PRINTF("start find_second_loader()!\n");
    while ((INT32)pointer < flash_dev->totol_size)
    {
        data_id  = sto_fetch_long((UINT32)pointer + CHUNK_ID);
        data_len = sto_fetch_long((UINT32)pointer + CHUNK_LENGTH);
        data_off = sto_fetch_long((UINT32)pointer + CHUNK_OFFSET);
        data_crc = sto_fetch_long((UINT32)pointer + CHUNK_CRC);

        //FIXED_PRINTF("@pointer[%08X] id[%08X] len[%08X] off[%08X] crc[%08X]\n", \
        //                      pointer, data_id, data_len, data_off, data_crc);

#ifdef BL_C0300A_STD
        if ((0 != data_len) && \
            (data_len < data_off) && \
            (CHUNKID_SECLOADER == data_id))
        {
            g_ota_offset = pointer;
            b_secondota = 1;
            FIXED_PRINTF("Find OTA LOADER at 0x%x!\n", g_ota_offset);
            break;
        }
#else
        if ((0 != data_len) && \
            (data_len < data_off) && \
            (NO_CRC != data_crc) &&\
            (CHUNKID_SECLOADER == data_id))
        {
            buffer = (UINT8 *)MALLOC(data_len);
            if (NULL == buffer)
            {
                FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
                ASSERT(0);
            }

            sto_get_data(flash_dev, buffer, pointer + 16, data_len);
            crc = mg_table_driven_crc(0xFFFFFFFF, buffer, data_len);
            FREE(buffer);
            buffer = NULL;

            if (data_crc == crc)
            {
                g_ota_offset = pointer;
                b_secondota = 1;
                FIXED_PRINTF("Find OTA LOADER!\n");
                break;
            }
            else
            {
                FIXED_PRINTF("OTA CRC Check not pass!\n");
            }
        }
#endif
        pointer += C_SECTOR_SIZE;
    }

    // verify the second LOADER_OPK_SIZE
    if (b_secondota)
    {
        pointer = g_ota_offset;
        do
        {
            data_id  = sto_fetch_long((UINT32)pointer + CHUNK_ID);
            data_len = sto_fetch_long((UINT32)pointer + CHUNK_LENGTH);
            data_off = sto_fetch_long((UINT32)pointer + CHUNK_OFFSET);
            data_crc = sto_fetch_long((UINT32)pointer + CHUNK_CRC);

            if (!data_off)
            {
                break;
            }
            if ((0xFF != (((data_id >> 16) & 0xFF) + (( data_id >> 24) & 0xFF))))
            {
                b_secondota = 0;
                break;
            }

            if ((INT32)data_off > flash_dev->totol_size)
            {
                //FIXED_PRINTF("@pointer[%08X] id[%08X] data_off[%08X] > flash size\n", \
                //      pointer, data_id, data_off);
                b_secondota = 0;
                break;
            }

            if (NO_CRC != data_crc)
            {
                if (NULL == (buffer = (UINT8 *)MALLOC(data_len)))
                {
                    FIXED_PRINTF("MALLOC fail!\n");
                    ASSERT(0);
                }

                sto_get_data(flash_dev, buffer, pointer + 16, data_len);
                crc = mg_table_driven_crc(0xFFFFFFFF, buffer, data_len);
                FREE(buffer);
                FIXED_PRINTF("Read OTALOADER CRC!\n");

                if (data_crc != crc)
                {
                    FIXED_PRINTF("@pointer[%08X] id[%08X] crc[%08X] != data_crc[%08X]\n", \
                                    pointer, data_id, crc, data_crc );
                    b_secondota = 0;
                    break;
                }
            }

            pointer += data_off;
            if ((INT32)(pointer + CHUNK_HEADER_SIZE) > flash_dev->totol_size)
            {
                FIXED_PRINTF("@pointer[%08X] no space for header\n", pointer);
                b_secondota = 0;
                break;
            }
        }
        while(data_off);
    }

    if (0 == b_secondota)
    {
        FIXED_PRINTF("Second Loader not exist!\n");
        g_ota_offset = 0;
    }

    FIXED_PRINTF ("LEAVE find_second_loader\n");
    return b_secondota;
}
#endif

#ifdef _HW_SECURITY_ENABLE_
static RET_CODE bl_prepare_otaloader(UINT8 *ota_decrypted, \
                                        UINT8 key_pos, \
                                        UINT32 block_addr, \
                                        UINT32 block_len, \
                                        UINT8 *len)
{
    UINT32 ota_len = 0;

    if ((NULL == ota_decrypted) || \
        (NULL == len))
    {
        FIXED_PRINTF("Error : %s, invalid parameter!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    aes_cbc_decrypt_flash_data(key_pos, block_addr, block_len - CHUNK_HEADER_SIZE + CHUNK_NAME, ota_decrypted);
    FIXED_PRINTF("Verify OTA data!\n");
    ota_len = block_len - CHUNK_HEADER_SIZE + CHUNK_NAME;
    *len = ota_len;
    FIXED_PRINTF("ota_len: %08X\n", ota_len);
    if (0 != test_rsa_ram((UINT32)ota_decrypted, ota_len))
    {
        FIXED_PRINTF("OTA signature fail!\n" );
        pan_display(panel_dev, "ERR", 4);
        return RET_FAILURE;
    }
    else
    {
        FIXED_PRINTF("OTA signature Pass!\n");
        return RET_SUCCESS;
    }
}
#endif

void bl_load_and_launch_ota(void)
{
#if (defined _OTA_E_)
    UINT32 block_len = 0;
    UINT32 cpu_mc_len = 0;
    UINT32 see_mc_len = 0;
    UINT8 *main_buff = NULL;
    UINT8 *see_buff = NULL;

#if (defined DUAL_CPU) && (!defined _LINUX_BOOTLOADER_)
    UINT32 block_addr = 0;

#endif


    if (find_second_loader()) /* ota.bin */
    {
        /* loader the main code */
        block_len = sto_fetch_long(g_ota_offset + CHUNK_LENGTH) - CHUNK_HEADER_SIZE + CHUNK_NAME;
        if (0 != block_len)
        {
            main_buff = (UINT8*)(0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf));
            if (NULL == main_buff)
            {
                FIXED_PRINTF("Error : %s, allocate buffer for OTA main code failed!\n", __FUNCTION__);
                goto bl_reboot;
            }
            cpu_mc_len = block_len;
            sto_get_data(flash_dev, main_buff, (g_ota_offset + CHUNK_HEADER_SIZE), block_len);
            FIXED_PRINTF("\nMain code, %x, %x, %x.\n", main_buff, block_len, CHUNKID_SECLOADER);
        }
        else
        {
            FIXED_PRINTF("Error : %s, maincode len is zero.\n", __FUNCTION__);
            goto bl_reboot;
        }

#if (defined DUAL_CPU) && (!defined _LINUX_BOOTLOADER_)
        /* loader the see code */
        sto_chunk_init(g_ota_offset, flash_dev->totol_size - g_ota_offset);

        block_len = 0;  //get the block_len
        if(RET_FAILURE == bl_get_chunk_len(CHUNKID_SECSEECODE, &block_addr, &block_len))
        {
            FIXED_PRINTF("Can't find chunk id 0x%08x.\n", CHUNKID_SECSEECODE);
            goto bl_reboot;
        }
        else if(0 != block_len)
        {
            see_buff = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf));
            if (NULL == see_buff)
            {
                FIXED_PRINTF("Error : %s, allocate buffer for see failed!\n", __FUNCTION__);
                goto bl_reboot;
            }
            see_mc_len = block_len;
            //aes_cbc_decrypt_chunk(pos, CHUNKID_SEECODE, see_decrypted, &see_mc_len);
            sto_get_data(flash_dev, see_buff, block_addr, block_len);
            FIXED_PRINTF("\nSEE Main code, %x, %x, %x, %x.\n", \
                            see_buff, block_len, CHUNKID_SECSEECODE, see_mc_len);

            //for decompress use.
            g_see_unziped = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(block_len * 4));
            if (NULL == g_see_unziped)
            {
                FIXED_PRINTF("Error : %s, allocate buffer for unzip see failed!\n", __FUNCTION__);
                goto bl_reboot;
            }
        }
        else
        {
            FIXED_PRINTF("Error : %s, seecode len is zero.\n", __FUNCTION__);
            goto bl_reboot;
        }

        sto_chunk_init(0, flash_dev->totol_size);
#endif
    }

    if (RET_FAILURE == bl_enter_sys_zip_sw(see_buff, see_mc_len, main_buff, cpu_mc_len))
    {
        goto bl_reboot;
    }

#endif

bl_reboot:
    FIXED_PRINTF("Error : %s, Bootloader fail\n", __FUNCTION__);
    SDBBP();
}

void bl_load_and_launch_sw(void)
{
    UINT32 chid = 0;
    UINT32 boot_code = 0;
    UINT32 offset = 0;

#if (defined _NAND_BOOT_E_) || (defined _LINUX_BOOTLOADER_)
    UINT8 *main_entry = NULL;

#endif
#if (!defined _NAND_BOOT_E_) || (!defined _LINUX_BOOTLOADER_)
    UINT32 block_addr = 0;
    UINT32 block_len = 0;
    UINT32 cpu_mc_len = 0;
    UINT32 see_mc_len = 0;
    UINT8 *main_buff = NULL;
    UINT8 *see_buff = NULL;

#endif

    boot_code = *(UINT32 *)(0xA0000110);

   /* If dynamic application load enable, try load this application */
    if (DEAD2BEE == boot_code)
    {
        chid = *((UINT32 *)0xA0000114);
        offset = sto_chunk_goto(&chid, *((UINT32 *)0xA0000118), 1);
    }
    else
    {
        /*load main software or uboot*/
#ifndef _LINUX_BOOTLOADER_
        chid = CHUNKID_MAINCODE;
#else
        if (RET_SUCCESS != bl_get_uboot_addr(g_boot_type, &chid))
        {
            FIXED_PRINTF("Error : %s, Can't get uboot address.\n", __FUNCTION__);
            goto bl_reboot;
        }
#endif

#ifndef    _NAND_BOOT_E_
        block_len = 0;
        if(RET_FAILURE == bl_get_chunk_len(chid, &block_addr, &block_len))
        {
            FIXED_PRINTF("Error : %s, Can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
            bl_load_and_launch_ota();  //never return
            goto bl_reboot;
        }
        else if (0 != block_len)
        {
            main_buff = (UINT8*)(0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf));
            if (NULL == main_buff)
            {
                FIXED_PRINTF("Error : %s, allocate buffer for main code failed!\n", __FUNCTION__);
                goto bl_reboot;
            }
            sto_get_data(flash_dev, main_buff, block_addr, block_len);
            cpu_mc_len = block_len;
            FIXED_PRINTF("CPU Main code, %x, %x, %x, %x.\n", main_buff, block_len, chid, cpu_mc_len);
            #ifdef _LINUX_BOOTLOADER_
                main_entry = (UINT8*)MAIN_ENTRY;
                MEMCPY(main_entry, main_buff, cpu_mc_len);
                osal_cache_flush(main_entry, cpu_mc_len);
            #endif
        }
        else
        {
            FIXED_PRINTF("Error : %s, maincode len is zero.\n", __FUNCTION__);
            bl_load_and_launch_ota();  //never return
            goto bl_reboot;
        }
#else
        FIXED_PRINTF("Load uboot:\n");
        main_entry = (UINT8*)MAIN_ENTRY;
        if (0 != api_load_data_from_nandflash(chid, g_nand_info.uboot_len, main_entry))
        {
            FIXED_PRINTF("Error: %s, Load uboot fail...\n", __FUNCTION__);
            goto bl_reboot;
        }
#endif
    }

#if (defined DUAL_CPU) && (!defined _LINUX_BOOTLOADER_)
    chid = CHUNKID_SEECODE;
    block_len = 0;

    if(RET_FAILURE == bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, Can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
        bl_load_and_launch_ota();  //never return
        goto bl_reboot;
    }
    else if (0 != block_len)
    {
        see_buff = (UINT8*)(0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf));
        if (NULL == see_buff)
        {
            FIXED_PRINTF("Error : %s, allocate buffer for see code failed!\n", __FUNCTION__);
            goto bl_reboot;
        }

        sto_get_data(flash_dev, see_buff, block_addr, block_len);
        see_mc_len = block_len;
        FIXED_PRINTF("SEE Main code, %x, %x, %x, %x.\n", see_buff, block_len, chid, see_mc_len);

        //for decompress use.
        g_see_unziped = (UINT8*)(0xFFFFFFF8 & (UINT32)MALLOC(block_len * 4));
        if (NULL == g_see_unziped)
        {
            FIXED_PRINTF("Error : %s, allocate buffer for decrypted see failed!\n", __FUNCTION__);
            goto bl_reboot;
        }
    }
    else
    {
        FIXED_PRINTF("Error : %s, seecode len is zero.\n", __FUNCTION__);
        bl_load_and_launch_ota();  //never return
        goto bl_reboot;
    }
#endif

#ifndef _LINUX_BOOTLOADER_
    if (RET_FAILURE == bl_enter_sys_zip_sw(see_buff, see_mc_len, main_buff, cpu_mc_len))
    {
        goto bl_reboot;
    }
#else
    if (RET_FAILURE == bl_enter_sys_sw(main_entry, 0x800000))
    {
        goto bl_reboot;
    }
#endif

bl_reboot:
    FIXED_PRINTF("Error : %s, Bootloader fail\n", __FUNCTION__);
    SDBBP();
}

#ifdef BL_C0300A_AS
#ifdef FAKE_VERITY_SIGNATURE
static UINT32 crc32(UINT8 *data, UINT32 len)
{
    if (NULL == data)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, data is NULL!\n", __FUNCTION__);
        return 0;
    }

    return mg_table_driven_crc(0xFFFFFFFF, data, len);
}

static UINT64 get_number(UINT8 *ptr)
{
    UINT64 tmp_val = 0;
    int i = 0;

    if (NULL == ptr)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, ptr is NULL!\n", __FUNCTION__);
        return 0;
    }

    // data in the signature is big-endian
    for (i = 0; i < 8; i++)
    {
        tmp_val = (tmp_val<<8) | ptr[i];
    }
    return tmp_val;
}

static UINT8 check_the_data_and_hash(UINT8 *data, UINT32 len, UINT8 *signature)
{
    // this function verifies the hash values and determines whether a
    // re-encryption is needed
    UINT32 tmp_crc = 0;
    UINT32 i = 0;
    UINT32 j = 0;

    if ((NULL == data) || \
        (NULL == signature))
    {
        FIXED_PRINTF("Error : %s, invalid parameter!\n", __FUNCTION__);
        return NO_ERR;
    }

    tmp_crc = crc32(data, len);
    /* we only have put 32-bits into the signature therefore we type-cast and correct the offset by 4 */
    if (((UINT32)get_number(signature + 48 - 4)) == tmp_crc)
    {
        // here we "decrypt" by using xor
        FIXED_PRINTF("checkTheDataAndHash: tmpCrc=0x%x match, decrypt the source\n", tmp_crc);
        for (j = 0; j < len; j++)
        {
            data[j] ^= 0xff;
        }

        return NO_ERR;
    }
    else
    {
        // here we can already "re-encrypt" by using xor
        for (i = 0; i < len; i++)
        {
            data[i] ^= 0xff;
        }
        tmp_crc = crc32(data, len);
        /* we only have put 32-bits into the signature therefore we type-cast and
        correct the offset by 4 */
        if (((UINT32)get_number(signature + 48 - 4)) != tmp_crc)
        {
            // the crc does not match therefore there it is an error
            FIXED_PRINTF("checkTheDataAndHash: crc error tmp_crcs=0x%x\n", tmp_crc);
            return ERR_2;
        }
        return ERR_1;
    }
}

static UINT8 decrypt_signature(UINT8 *dec_sign, UINT8 *signature)
{
    // here we do signature decryption
    // we only copy here as the signature is not encrypted at all
    if ((NULL == dec_sign) || \
        (NULL == signature))
    {
        FIXED_PRINTF("Error : %s, invalid parameter!\n", __FUNCTION__);
        return 0;
    }

    MEMCPY(dec_sign, signature, 256);
    return 1;
}

static RET_CODE verify_signature(UINT8 *signature, \
                       UINT8 *src, \
                       UINT8 *tmp, \
                       UINT32 len, \
                       UINT32 maxlen, \
                       UINT8 mode, \
                       UINT8 *errcode)
{
    UINT8 dec_sign[256] = {0};
    UINT32 i = 0;
    UINT8 re_encryption_needed = 0;

    if ((NULL == signature) || \
        (NULL == src) || \
        (NULL == tmp) || \
        (NULL == errcode))
    {
        FIXED_PRINTF("Error : %s, invalid parameter!\n", __FUNCTION__);
        return RET_SUCCESS;
    }

    FIXED_PRINTF("%s: len=0x%x, maxLen=0x%x, mode=%d\n", \
                __FUNCTION__, len, maxlen, mode);
    FIXED_PRINTF("%s: signature crc=0x%x 0x%x 0x%x 0x%x\n", \
                __FUNCTION__, signature[48], signature[49], signature[50], signature[51]);
    FIXED_PRINTF("%s: signature len=0x%x 0x%x 0x%x 0x%x\n", \
                __FUNCTION__, signature[36], signature[37], signature[38], signature[39]);
    FIXED_PRINTF("%s: signature maxlen=0x%x 0x%x 0x%x 0x%x\n", \
                __FUNCTION__, signature[44], signature[45], signature[46], signature[47]);
    // we decrypt the signature, which you do not have to do here
    if (decrypt_signature(dec_sign, signature))
    {
        if (MEMCMP(dec_sign, magic, sizeof(magic)))
        {
            // error magic value is wrong, therefore signature is bad
            FIXED_PRINTF("%s: magic value wrong:0x%x 0x%x\n", \
            __FUNCTION__, dec_sign[0], dec_sign[1]);
            *errcode = ERR_1;
            return RET_SUCCESS;
        }
        else
        {
            for (i = 9; i < 24; i++)
            {
                if (dec_sign[i])
                {
                    // error verifier is not 0, therefore signature is bad
                    FIXED_PRINTF("%s: zero value wrong:decSignature[%d]= 0x%x\n" \
                    __FUNCTION__, i, dec_sign[i]);
                    *errcode = ERR_1;
                    return RET_SUCCESS;
                }
            }
            // the signature has been decrypted correctly, now we check the
            // length values
            if ((get_number(dec_sign + 32) == len) && \
                (get_number(dec_sign + 40) == max_len))
            {
                // now we do some additional checks for hash-value
                // and from this check we determine whether a
                // re-encryption is needed
                re_encryption_needed = check_the_data_and_hash(src, len, dec_sign);
                FIXED_PRINTF("verifySignature: re_encryption_needed=%d\n", re_encryption_needed);
                if (re_encryption_needed == ERR_2)
                {
                    // error the hash value is not correct,
                    // therefore signature is bad
                    *errcode = ERR_1;
                    return RET_SUCCESS;
                }
                // if re-encryption is needed we check, for the mode value.
                if (re_encryption_needed && \
                    (dec_sign[8] == 1) && \
                    (MODE_0 == mode))
                {
                    // error re-encryption when starting from flash must not occur
                    // for loaded image, therefore signature is bad
                    FIXED_PRINTF("verifySignature: mode not match error\n");
                    *errcode = ERR_1;
                    return RET_SUCCESS;
                }

                if (re_encryption_needed)
                {
                    // do the re-encryption
                    // we have already done it
                    *errcode = ERR_2;
                    return RET_SUCCESS;
                }
                else
                {
                    if (MODE_1 == mode)
                    {
                        // error there should be no re-encrypted image directly loaded
                        FIXED_PRINTF("verifySignature: error mode should be 0\n");
                        *errcode = ERR_1;
                        return RET_SUCCESS;
                    }
                    else
                    {
                        // everything is fine
                        *errcode = NO_ERR;
                        return RET_FAILURE;
                    }
                }
            }
            else
            {
                // error one of the length values does not match,
                // therefore signature is bad
                FIXED_PRINTF("%s: len wrong: len=0x%x 0x%x 0x%x 0x%x\n", \
                            __FUNCTION__, \
                            dec_sign[32+4], \
                            dec_sign[32+5], \
                            dec_sign[32+6], \
                            dec_sign[32+7]);
                FIXED_PRINTF("%s: maxlen wrong: maxlen=0x%x 0x%x 0x%x 0x%x\n", \
                            __FUNCTION__, \
                            dec_sign[40+4], \
                            dec_sign[40+5], \
                            dec_sign[40+6], \
                            dec_sign[40+7]);
                *errcode = ERR_1;
                return RET_SUCCESS;
            }
        }
    }
    else
    {
        // error decryption failed, therefore signature is bad
        FIXED_PRINTF("verifySignature: decryption failed\n");
        *errcode = ERR_1;
        return RET_SUCCESS;
    }
}
#endif //FAKE_VERITY_SIGNATURE

static RET_CODE handle_chunk_data(UINT8 *data, UINT32 length)
{
    UINT8 *signature = NULL;
    UINT8 *tmp_buffer = NULL;
    UINT8 *source = NULL;
    UINT8 mode = MODE_0;
    UINT8 errorcode = NO_ERR;
    UINT32 len = 0;
    UINT32 maxlen = 0;
    UINT32 chunk_id = 0;
    UINT32 block_len = 0;
    UINT32 code_len = 0;
    UINT32 header_crc = 0;
    UINT32 block_addr = 0;
    UINT32 pre_chunk_id = CHUNKID_STBINFO;
    UINT32 pre_chunk_offset = 0;

    RET_CODE ret = RET_FAILURE;

    if (NULL == data)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, data is NULL!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    chunk_id = fetch_long(data + CHUNK_ID);
    block_len = fetch_long(data + CHUNK_OFFSET);
    code_len = fetch_long(data + CHUNK_LENGTH);
    len = code_len - (CHUNK_HEADER_SIZE - CHUNK_NAME) - SIGNATURE_SIZE;
    source = data + CHUNK_HEADER_SIZE;
    signature = source + len;

    mode = MODE_1;
    tmp_buffer = (UINT8*)(0xa0000000|(0xFFFFFFF8&(UINT32)MALLOC(block_len+0xf)));
    if (NULL == tmp_buffer)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
        return RET_FAILURE;
    }

    maxlen = len;
    ret = verify_signature(signature, source, tmp_buffer, len, maxlen, mode, &errorcode);
    if (RET_SUCCESS == ret)
    {
        if(ERR_2 == errorcode)
        {
            switch(chunk_id)
            {
                case CHUNKID_MAINCODE:
                    block_addr = sto_chunk_goto(&chunk_id, CHUNKID_MAINCODE_MASK, 1);

                    if(ERR_FAILUE == block_addr)
                    {
                        block_addr = sto_chunk_goto(&pre_chunk_id, CHUNKID_STBINFO_MASK, 1);
                        pre_chunk_offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

                        if(ERR_FAILUE == block_addr)
                        {
                            ret = RET_FAILURE;
                        }
                        else
                        {
                            block_addr += pre_chunk_offset;
                        }
                    }
                    break;

                case CHUNKID_SEECODE:
                    block_addr = sto_chunk_goto(&chunk_id, CHUNKID_SEECODE_MASK, 1);

                    if(ERR_FAILUE == block_addr)
                    {
                        block_addr = sto_chunk_goto(&pre_chunk_id, CHUNKID_MAINCODE_MASK, 1);
                        pre_chunk_offset = sto_fetch_long((UINT32)block_addr + CHUNK_OFFSET);

                        if(ERR_FAILUE == block_addr)
                        {
                            ret = RET_FAILURE;
                        }
                        else
                        {
                            block_addr += pre_chunk_offset;
                        }
                    }
                    break;

                default:
                    //not supported chunk id in force download
                    ret = RET_FAILURE;
                    break;
            }

            if (RET_SUCCESS == ret)
            {
                //calculate crc value for chunk header
                header_crc = mg_table_driven_crc(0xFFFFFFFF, data + CHUNK_NAME, code_len);
                *(data + CHUNK_CRC) = (UINT8)(header_crc>>24);
                *(data + CHUNK_CRC + 1) = (UINT8)(header_crc>>16);
                *(data + CHUNK_CRC + 2) = (UINT8)(header_crc>>8);
                *(data + CHUNK_CRC + 3) = (UINT8)(header_crc);
                pan_display(panel_dev, "BURN", 4);
                update_flash_data(block_addr, block_len, data);
            }
            else
            {
                pan_display(panel_dev, "fail", 4);
                while(1)
                {
                    ;
                }
            }
        }
        else if(ERR_1 == errorcode)
        {
            ret = RET_FAILURE;
        }
    }

    FREE(tmp_buffer);
    tmp_buffer = NULL;

    return ret;
}
#endif

static RET_CODE api_store_key_to_nandflash(UINT32 id)
{
#ifdef _LINUX_BOOTLOADER_
    UINT32 block_addr = 0;
    UINT32 block_len = 0;
    UINT32 addr = 0;
    UINT32 len = 0;
    loff_t flash_addr = 0;
    struct ali_nand_device *nand_dev = NULL;

    nand_dev = (struct ali_nand_device *)dev_get_by_name("ALI_NAND");
    if (NULL == nand_dev)
    {
        FIXED_PRINTF("Error : %s, can't get nand device\n");
        return RET_FAILURE;
    }

    if (RET_FAILURE == bl_get_chunk_len(id, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, can't get chunk 0x%x!\n", __FUNCTION__, id);
        return RET_FAILURE;
    }

    FIXED_PRINTF("[%s]block_addr = 0x%x, block_len = 0x%x\n", __FUNCTION__, block_addr, block_len);
    flash_addr = g_nand_info.loader_start + (loff_t)block_addr;
    addr = RAM_BASE_ADDR + block_addr;
    len = block_len;
    if (nf_save_loader(nand_dev, flash_addr, (UINT8 *)addr, len) < 0)
    {
        FIXED_PRINTF("Error : %s, write nand flash failed!\n", __FUNCTION__);
        return RET_FAILURE;
    }
#endif

    return RET_SUCCESS;
}

#ifdef _LINUX_BOOTLOADER_
RET_CODE api_load_data_from_nandflash(unsigned long addr, unsigned long len, UINT8 *buf)
{
    struct ali_nand_device *nand_dev = NULL;

    FIXED_PRINTF("load data from flash: addr = 0x%x, len = 0x%x, buf = 0x%x\n", addr, len, buf);

    if (NULL == buf)
    {
        FIXED_PRINTF("Error : %s, invalid parameter!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    nand_dev = (struct ali_nand_device *)dev_get_by_name("ALI_NAND");
    if(nf_load_loader(nand_dev, addr, buf, len))
    {
        FIXED_PRINTF("Load data from nandflash fail\n");
        return RET_FAILURE;
    }

    return RET_SUCCESS;
}

static RET_CODE bl_load_stmach(struct state_machine_t *stmach)
{
    UINT8 *buf_tmp = NULL;
    UINT32 bbsize = 0;
    UINT32 bbchecklen = 0;
    UINT64 offset = 0;
    struct ali_nand_device *nand_dev = NULL;

    if (NULL == stmach)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, stmach is NULL!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    buf_tmp = (UINT8 *)MALLOC(g_nand_info.blocksize);
    if (NULL == buf_tmp)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    nand_dev = (struct ali_nand_device *)dev_get_by_name("ALI_NAND");
    if (NULL == nand_dev)
    {
        FIXED_PRINTF("Error : %s, nand_dev is null\n", __FUNCTION__);
        return RET_FAILURE;
    }

    bbchecklen = 3 * g_nand_info.blocksize;
    check_skip_len(nand_dev, (loff_t)(g_nand_info.stmach_addr - bbchecklen), bbchecklen, &bbsize);
    offset = g_nand_info.stmach_addr + bbsize;

    FIXED_PRINTF("Load stmach: offset = 0x%x\n", offset);
    if (nf_load_loader(nand_dev, (loff_t)offset, buf_tmp, g_nand_info.blocksize))
    {
        FIXED_PRINTF("Load data from nandflash fail\n");
        return RET_FAILURE;
    }

    MEMCPY((UINT8 *)stmach, buf_tmp, sizeof(struct state_machine_t));

    FIXED_PRINTF("State Machine:\n");
    FIXED_PRINTF("b_boot_status = 0x%x;\n", stmach->b_boot_status);
    FIXED_PRINTF("b_lowlevel_status = 0x%x;\n", stmach->b_lowlevel_status);
    FIXED_PRINTF("b_application_status = 0x%x;\n", stmach->b_application_status);
    FIXED_PRINTF("b_bootloader_upgrade = 0x%x;\n", stmach->b_bootloader_upgrade);
    FIXED_PRINTF("b_lowlevel_upgrade = 0x%x;\n", stmach->b_lowlevel_upgrade);
    FIXED_PRINTF("b_application_upgrade = 0x%x;\n", stmach->b_application_upgrade);
    FIXED_PRINTF("b_bootloader_run_cnt = 0x%x;\n", stmach->b_bootloader_run_cnt);
    FIXED_PRINTF("b_lowlevel_run_cnt = 0x%x;\n", stmach->b_lowlevel_run_cnt);
    FIXED_PRINTF("b_application_run_cnt = 0x%x;\n", stmach->b_application_run_cnt);
    #if 0
    FIXED_PRINTF("b_need_upgrade = 0x%x;\n", stmach->b_need_upgrade);
    FIXED_PRINTF("b_backup_exist = 0x%x;\n", stmach->b_backup_exist);
    FIXED_PRINTF("b_lowlevel_backup_exist = 0x%x;\n", stmach->b_lowlevel_backup_exist);
    FIXED_PRINTF("b_boot_backup_exist = 0x%x;\n", stmach->b_boot_backup_exist);
    FIXED_PRINTF("b_nor_upgrade = 0x%x;\n", stmach->b_nor_upgrade);
    FIXED_PRINTF("b_nor_reserved = 0x%x;\n", stmach->b_nor_reserved);
    FIXED_PRINTF("b_nor_reserved_upgrade = 0x%x;\n", stmach->b_nor_reserved_upgrade);
    FIXED_PRINTF("b_nand_reserved = 0x%x;\n", stmach->b_nand_reserved);
    FIXED_PRINTF("b_nand_reserved_upgrade = 0x%x;\n", stmach->b_nand_reserved_upgrade);
    FIXED_PRINTF("b_nand_whole_upgrade = 0x%x;\n", stmach->b_nand_whole_upgrade);
    FIXED_PRINTF("\n");
    #endif
    FIXED_PRINTF("b_cur_uboot = 0x%x;\n", stmach->b_cur_uboot);

    FREE(buf_tmp);
    buf_tmp = NULL;

    return RET_SUCCESS;
}

static RET_CODE bl_save_stmach(struct state_machine_t *stmach)
{
    UINT32 bbsize = 0, bbchecklen = 0;
    UINT64 offset = 0;
    struct ali_nand_device *nand_dev = NULL;

    if (NULL == stmach)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, stmach is NULL!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    nand_dev = (struct ali_nand_device *)dev_get_by_name("ALI_NAND");
    if (NULL == nand_dev)
    {
        FIXED_PRINTF("nand_dev is null\n");
        return RET_FAILURE;
    }

    bbchecklen = 3 * g_nand_info.blocksize;
    check_skip_len(nand_dev, (loff_t)(g_nand_info.stmach_addr - bbchecklen), bbchecklen, &bbsize);
    offset = g_nand_info.stmach_addr + bbsize;

    FIXED_PRINTF("save stmach:offset = 0x%x\n", offset);
    if (nf_save_loader(nand_dev, (loff_t)offset, (UINT8 *)stmach, sizeof(struct state_machine_t)))
    {
        FIXED_PRINTF("[%s, %d]ali_nand_write\n", __FUNCTION__, __LINE__);
    }

    return RET_SUCCESS;
}

RET_CODE bl_get_uboot_addr(UINT32 boot_type, UINT32 *uboot_addr)
{
    UINT32 nor_uboot_addr = 0;
    UINT32 nand_uboot_addr = 0;
    struct state_machine_t stmach;

    if (NULL == uboot_addr)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, uboot_addr is NULL!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    if (0 == bl_init_nand())
    {
        MEMSET((UINT8 *)&stmach, 0x0, sizeof(struct state_machine_t));
        if (RET_SUCCESS != bl_load_stmach(&stmach))
        {
            FIXED_PRINTF("Load state machine failed\n");
            return RET_FAILURE;
        }

        if (UPG_DESC_BOOT_UPG_OVER == stmach.b_bootloader_upgrade)
        {
            if (UPG_DESC_UBOOT2 == stmach.b_cur_uboot)
            {
                nor_uboot_addr = CHUNKID_MAINCODE;
                nand_uboot_addr = g_nand_info.uboot_start;
            }
            else
            {
                nor_uboot_addr = CHUNKID_UBOOT_BAK;
                nand_uboot_addr = g_nand_info.uboot_backup_start;
            }
        }
        else
        {
            if (UPG_DESC_UBOOT2 == stmach.b_cur_uboot)
            {
                nor_uboot_addr = CHUNKID_UBOOT_BAK;
                nand_uboot_addr = g_nand_info.uboot_backup_start;
            }
            else
            {
                nor_uboot_addr = CHUNKID_MAINCODE;
                nand_uboot_addr = g_nand_info.uboot_start;
            }
        }

        if (stmach.b_bootloader_upgrade)
        {
            stmach.b_boot_status = UPG_DESC_BOOT_RUN_ENTER;

            if (UPG_DESC_BOOT_UPG_OVER == stmach.b_bootloader_upgrade)
            {//uboot upgrading complete,
                stmach.b_bootloader_upgrade = UPG_DESC_BOOT_UPG_RUN;
            }
            else if (UPG_DESC_BOOT_UPG_RUN == stmach.b_bootloader_upgrade)
            {// uboot upgrading complete, boot fail
                stmach.b_bootloader_upgrade = UPG_DESC_BOOT_UPG_NO;
            }

            if (RET_SUCCESS != bl_save_stmach(&stmach))
            {
                FIXED_PRINTF("Load state machine failed\n");
                return RET_FAILURE;
            }
        }
    }
    else
    {//nand flash is empty
        nor_uboot_addr = CHUNKID_MAINCODE;
        nand_uboot_addr = g_nand_info.uboot_start;
    }

    if (1 != boot_type)
    {
        *uboot_addr = nor_uboot_addr;
    }
    else
    {
        *uboot_addr = nand_uboot_addr;
    }

    return RET_SUCCESS;
}
#endif

#ifdef _HW_SECURITY_ENABLE_
void set_uboot_config(UINT32 uboot_entry)
{
    fetch_sys_kernel_pub_key(uboot_entry - CFG_KEY_LEN);
}

RET_CODE bl_prepare_key(struct UKEY_INFO *ukey)
{
    UINT32 offset = 0;
    UINT32 key_pos = 0;
    UINT32 chid = 0;
    RET_CODE ret = RET_FAILURE;
    CHUNK_HEADER chunk_hdr;

    if (NULL == ukey)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, ukey is NULL!\n", __FUNCTION__);
        return ret;
    }

    chid = CHUNKID_MEM_CFG;
    /*bl_uk*/
    if ((is_bl_encrypted_enable()) && \
        (sto_get_chunk_header(CHUNKID_MEM_CFG, &chunk_hdr) != 0))
    {
        offset = sto_chunk_goto(&chid, CHUNKID_MEM_CFG_MASK, 1);
        if (((UINT32)ERR_PARA == offset) || \
            ((UINT32)ERR_FAILUE == offset))
        {
            FIXED_PRINTF("Error : %s, can't get chunk 0x%x!\n", __FUNCTION__, chid);
            ret = RET_FAILURE;
            return ret;
        }

        if (FALSE == is_key_encrypted(offset, BL_FLASH_KEY))
        {
            ret = encrypt_bl_universal_key(CHUNKID_MEM_CFG & CHUNKID_MEM_CFG_MASK);
            if (RET_SUCCESS != ret)
            {
                return ret;
            }

            if (BOOT_TYPE_NAND == g_boot_type)
            {
                ret = api_store_key_to_nandflash(CHUNKID_MEM_CFG);
                if (RET_SUCCESS != ret)
                {
                    return ret;
                }
            }
        }
    }

    chid = CHUNKID_KEY;
    if (sto_get_chunk_header(CHUNKID_KEY, &chunk_hdr) != 0)
    {
        offset = sto_chunk_goto(&chid, CHUNKID_KEY_MASK, 1);
        if (((UINT32)ERR_PARA == offset) || \
            ((UINT32)ERR_FAILUE == offset))
        {
            FIXED_PRINTF("Error : %s, can't get chunk 0x%x!\n", __FUNCTION__, chid);
            ret = RET_FAILURE;
            return ret;
        }

        if (FALSE == is_key_encrypted(offset, FIRST_FLASH_KEY))
        {
			#ifdef BL_VSC_ENABLE
			ret = encrypt_universal_key((CHUNKID_KEY & CHUNKID_KEY_MASK) | FIRST_FLASH_KEY | FLASH_TRI_LADDER_MODE_KEY02);
			#else
            ret = encrypt_universal_key((CHUNKID_KEY & CHUNKID_KEY_MASK) | FIRST_FLASH_KEY);
			#endif
            if (RET_SUCCESS != ret)
            {
                return ret;
            }

            if (BOOT_TYPE_NAND == g_boot_type)
            {
                ret = api_store_key_to_nandflash(CHUNKID_KEY);
                if (RET_SUCCESS != ret)
                {
                    return ret;
                }
            }
        }

#ifdef _LINUX_BOOTLOADER_
        /*encrypt 2nd uk*/
        if (FALSE == is_key_encrypted(offset, SECOND_FLASH_KEY))
        {
            ret = encrypt_universal_key((CHUNKID_KEY&CHUNKID_KEY_MASK)|SECOND_FLASH_KEY);
            if (RET_SUCCESS != ret)
            {
                return ret;
            }

            if (BOOT_TYPE_NAND == g_boot_type)
            {
                ret = api_store_key_to_nandflash(CHUNKID_KEY);
                if (RET_SUCCESS != ret)
                {
                    return ret;
                }
            }
        }
#endif
		#ifdef BL_VSC_ENABLE
		ret = decrypt_universal_key((UINT8 *)&key_pos, (CHUNKID_KEY&CHUNKID_KEY_MASK|FIRST_FLASH_KEY|FLASH_TRI_LADDER_MODE_KEY02));
		#else
        ret = decrypt_universal_key((UINT8 *)&key_pos, (CHUNKID_KEY&CHUNKID_KEY_MASK|FIRST_FLASH_KEY));
		#endif
        if(RET_SUCCESS != ret)
        {
            return ret;
        }
    }

    ret = RET_SUCCESS;
    get_enc_uk_mode(&ukey->ukey_mode, ukey->enc_uk);
    ukey->kl_key_pos = key_pos;
    return ret;
}
#ifdef BL_VSC_ENABLE
RET_CODE bl_prepare_key_see(struct UKEY_INFO *ukey)
{
    UINT32 chid=CHUNKID_MEM_CFG;
    CHUNK_HEADER chunk_hdr;
    UINT32 offset = 0;
    UINT8 key_pos = 0;
    RET_CODE ret=RET_FAILURE;
    MEMSET(&chunk_hdr,0 , sizeof(CHUNK_HEADER));
    chid = CHUNKID_KEY_SEE;
    if ( sto_get_chunk_header ( CHUNKID_KEY_SEE, &chunk_hdr ) != 0 )
    {
        ret = sto_chunk_goto ( &chid, CHUNKID_KEY_MASK, 1 );
        if ( ret < 0 )
        {
             FIXED_PRINTF ( "%s failed!!! \n", __FUNCTION__ );
             return ret;           
        }
        else
        {
            offset = (UINT32)ret ;
            if ( is_key_encrypted(offset, FIRST_FLASH_KEY)==FALSE )
            {
				ret = encrypt_universal_key ( CHUNKID_KEY_SEE&CHUNKID_KEY_MASK|FIRST_FLASH_KEY|FLASH_TRI_LADDER_MODE_KEY02);
				if(ret!=RET_SUCCESS)
				{
					return ret;
				}
            }
			ret = decrypt_universal_key( &key_pos, (CHUNKID_KEY_SEE&CHUNKID_KEY_MASK|FIRST_FLASH_KEY|FLASH_TRI_LADDER_MODE_KEY02) ); //yuchun0317
            if(ret!=RET_SUCCESS)
			{
				return ret;
            }
        }
    }
    ret = RET_SUCCESS;
    get_enc_uk_mode(&ukey->ukey_mode, ukey->enc_uk);
    ukey->kl_key_pos = key_pos;
    return ret;
}
#endif
#endif

