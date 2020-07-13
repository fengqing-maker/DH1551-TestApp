/*****************************************************************************
*    Ali Corp. All Rights Reserved. 2002 Copyright (C)
*
*    File:    bootloader.c
*
*    Description:    This file contains all globe micros and functions declare
*                    of Flash boot loader.
*    History:
*           Date            Athor        Version          Reason
*       ============    =============   =========   =================
*   1.  Oct.28.2003     Justin Wu       Ver 0.1    Create file.
 *  2.  2006.5.16       Justin Wu       Ver 0.2    STO chunk support & clean up.
*****************************************************************************/
#include "bootloader.h"

UINT32 g_boot_type = 0;             /* 0--Nor, 1--Nand, 2--SDIO, 3--EMMC, 9--Unknow */



static void bl_dump_data(UINT8 *data, UINT32 len)
{
    UINT32 i = 0;

    if (NULL == data)
    {
        FIXED_PRINTF("Error : %s, invalid parameter, data is NULL\n", __FUNCTION__);
        return ;
    }

    for (i = 0; i < len; i++)
    {
        FIXED_PRINTF("0x%02x, ", *(data + i));
        if (0 == ((i + 1) % 16))
        {
            FIXED_PRINTF("\n");
        }
    }

    if (0 != (i % 16))
    {
        FIXED_PRINTF("\n");
    }
}

#ifdef _HW_SECURITY_ENABLE_
/*
* Parameter:
*     flag =1  main/see chunk head is wrong
*
*/
#ifndef LINUX_BOOTLOADER
static RET_CODE app_init_ota(struct UKEY_INFO ukey)
{
    UINT32 chid = 0;
    UINT32 cpu_mc_len = 0;
    UINT32 block_addr = 0;
    UINT32 block_len = 0;
    UINT8 *main_decrypted = NULL;
    UINT8 *see_decrypted = NULL;
    UINT8 *main_entry = NULL;
    UINT32 g_key_pos = 0;

    g_key_pos = ukey.kl_key_pos;
    mg_setup_crc_table();
    if (1 != find_second_loader())
    {
        FIXED_PRINTF("Error : %s, can't find second loader!\n", __FUNCTION__);
        return RET_FAILURE;
    }

    FIXED_PRINTF("second loader code g_ota_offset=0x%x, flash_dev->totol_size=0x%x\n",
                                    g_ota_offset, flash_dev->totol_size);
    sto_chunk_init(g_ota_offset, flash_dev->totol_size - g_ota_offset);

    FIXED_PRINTF("Run second loader main chunk id 0x%08x.\n", chid);
    chid = CHUNKID_SECLOADER;
    block_len = 0;

    if (RET_SUCCESS != bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, can't find second loader chunk id 0x%08x.\n", __FUNCTION__, chid);
        return RET_FAILURE;
    }

    if(0 == block_len)
    {
        FIXED_PRINTF("Error : %s, can't find chunk id length 0x%08x.\n", __FUNCTION__, chid);
        return RET_FAILURE;
    }

    main_decrypted = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf));
    if (NULL == main_decrypted)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
        return RET_FAILURE;
    }

    if (RET_SUCCESS != aes_cbc_decrypt_chunk(g_key_pos, chid, main_decrypted, &cpu_mc_len))
    {
        FIXED_PRINTF("Error : %s, second loader decrypt failed\n", __FUNCTION__);
        return RET_FAILURE;
    }

    FIXED_PRINTF("Run second loader see chunk id 0x%08x.\n", chid);
    chid = CHUNKID_SECSEECODE;
    block_len = 0;

    if (RET_SUCCESS != bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, can't find second see loader chunk id 0x%08x.\n", __FUNCTION__, chid);
        return RET_FAILURE;
    }

    if (0 == block_len)
    {
        FIXED_PRINTF("Error : %s, can't find chunk id length 0x%08x.\n", __FUNCTION__, chid);
        return RET_FAILURE;
    }

    see_decrypted = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf));
    if (NULL == see_decrypted)
    {
        FIXED_PRINTF("Error : %s, allocate buffer failed\n", __FUNCTION__);
        return RET_FAILURE;
    }

    if ((INT32)block_len != sto_get_data(flash_dev, see_decrypted, block_addr, block_len))
    {
        FIXED_PRINTF("Error : %s, second loader see code load failed\n", __FUNCTION__);
        return RET_FAILURE;
    }
    set_see_code_info((UINT32)see_decrypted, block_len, SEE_ENTRY);
    set_see_sig_info((UINT32)see_decrypted + block_len - SIG_LEN, SIG_LEN, RSASSA_PKCS1_V1_5);
    set_see_key_info(&ukey);

    if (RET_SUCCESS != bl_verify_sw_see(DUVS_SEE))
    {
        FIXED_PRINTF("Error : %s, second loader see software trig failed\n", __FUNCTION__);
        return RET_FAILURE;
    }

    if ((0 == cpu_mc_len) || \
        (0 == bl_unzip_sw(main_decrypted, cpu_mc_len, MAIN_CODE)))
    {
        FIXED_PRINTF("Error : %s, main code decrypt error,goto reboot...\n", __FUNCTION__);
        return RET_FAILURE;
    }

    if(RET_SUCCESS != bl_run_sw_see_later(0))
    {
        FIXED_PRINTF("Error : %s, see software run failed, sys will goto reboot ...\n", __FUNCTION__);
        return RET_FAILURE;
    }

    main_entry = (UINT8 *)MAIN_ENTRY;
    if( RET_SUCCESS != bl_enter_sys_sw(main_entry, unzip_length))
    {
        FIXED_PRINTF("Error : %s, bl enter sys_sw failed , goto reboot...\n", __FUNCTION__);
        return RET_FAILURE;
    }

    return RET_SUCCESS;
}
#endif

void app_init(void)
{
    UINT32 chid = 0;
    UINT32 cpu_mc_len = 0;
    UINT32 block_addr = 0;
    UINT32 block_len = 0;
    UINT8 *main_entry = NULL;
    UINT8 *main_decrypted = NULL;
    UINT32 flag=0;
    UINT32 *param=NULL;
    struct UKEY_INFO ukey;
	UINT8 *f_temp = NULL;
	UINT8 *temp_buffer = NULL;
	UINT32 ret_len = 0;
	RET_CODE ret=RET_SUCCESS;

#ifdef LINUX_BOOTLOADER
    UINT8 *main_encrypted = NULL;

#else
    UINT8 *see_decrypted = NULL;

#endif

    sys_uart_init();
    otp_init(NULL);
#ifndef LINUX_BOOTLOADER
    bl_trig_bl_see((UINT32)__SEE_ROM_START, (__SEE_ROM_END - __SEE_ROM_START), SEE_ENTRY + 0x1000000);
#else
    bl_trig_bl_see((UINT32)__SEE_ROM_START, (__SEE_ROM_END - __SEE_ROM_START), SEE_ENTRY);
#endif

    g_boot_type = sys_ic_get_boot_type();
    FIXED_PRINTF("g_boot_type = %d\n", g_boot_type);
    boot_enter_standby();
#ifndef _LINUX_BOOTLOADER_
    sys_gpio_init();
    sys_panel_init();
    panel_dev = (struct pan_device *)dev_get_by_id(HLD_DEV_TYPE_PAN, 0);
    pan_display(panel_dev, " ON ", 4);
#endif
    bl_init_flash();
    dsc_api_attach();
    ce_api_attach();
    see_step1();

    MEMSET(&ukey, 0x0, sizeof(UKEY_INFO));
    if(RET_SUCCESS != bl_prepare_key(&ukey))
    {
        FIXED_PRINTF("Error : %s, prepare key failed!\n", __FUNCTION__);
        goto bl_reboot;
    }

#ifndef LINUX_BOOTLOADER
    if(RET_SUCCESS != set_parameter_from_bl(flag,param))
    {
        FIXED_PRINTF("Error : %s, set parameter failed!\n");
        goto bl_ota;
    }

#ifdef BL_VSC_ENABLE
	chid = CHUNKID_VSC_CODE;
	block_len = 0;
    if (RET_SUCCESS != bl_get_chunk_len (chid, &block_addr, &block_len))
    {
        FIXED_PRINTF ("Can't find chunk id 0x%08x.\n", CHUNKID_VSC_CODE);
        goto bl_ota;
    }
    else if (0 != block_len)
    {
        FIXED_PRINTF("VSC code block_addr=0x%x,block_len=0x%x\n", block_addr,block_len);
        f_temp = (UINT8 *)MALLOC(block_len + 0xf);
        if (NULL == f_temp)
        {
            FIXED_PRINTF("MALLOC Failed!\n");
            goto bl_reboot;
        }
        temp_buffer = (UINT8 *)((0xFFFFFFF8 & (UINT32)f_temp));
        ret_len=sto_get_data(flash_dev, (UINT8 *)temp_buffer, block_addr, block_len);
        if (ret_len != block_len)
        {
            FIXED_PRINTF("Get VSC from flash Failed!\n");
            goto bl_reboot;
        }
        ret = test_vsc_rsa_ram ((UINT32)temp_buffer, block_len);
        if(RET_SUCCESS != ret)
        {
            FIXED_PRINTF ("VSC signature 2 failed\n");
            goto bl_reboot;
        }
        else
        {
            aes_cbc_decrypt_vsc(temp_buffer, block_len - VSC_SIGNATURE_LEN - VSC_VERSION_LEN);
        }
        FREE(f_temp);
	}
    else
    {
        FIXED_PRINTF("Code length out of range\n");
        goto bl_ota;            
    }
#endif
    chid = CHUNKID_MAINCODE;
    block_len = 0;
    if (RET_SUCCESS != bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
        goto bl_ota;
    }
    else if (0 == block_len)
    {
        FIXED_PRINTF("Error : %s, the length of chunk 0x%08x is 0.\n", __FUNCTION__, chid);
        goto bl_ota;
    }

    main_decrypted = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf));
    if (RET_SUCCESS != aes_cbc_decrypt_chunk(ukey.kl_key_pos, chid, main_decrypted, &cpu_mc_len))
    {
        FIXED_PRINTF("Error : %s, main code decrypt failed\n", __FUNCTION__);
        goto bl_ota;
    }

#ifdef BL_VSC_ENABLE
    MEMSET(&ukey, 0x0, sizeof(UKEY_INFO));
    if(RET_SUCCESS != bl_prepare_key_see(&ukey))
    {
        FIXED_PRINTF("Error : %s, prepare key see failed!\n", __FUNCTION__);
        goto bl_reboot;
    }
#endif
    chid = CHUNKID_SEECODE;
    block_len = 0;
    if (RET_SUCCESS != bl_get_chunk_len(chid, &block_addr, &block_len))
    {
        FIXED_PRINTF("Error : %s, can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
        goto bl_ota;
    }
    else if(0 == block_len)
    {
        FIXED_PRINTF("Error : %s, the length of chunk 0x%08x is 0.\n", __FUNCTION__, chid);
        goto bl_ota;
    }

    see_decrypted = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf));
    if ((INT32)block_len != sto_get_data(flash_dev, see_decrypted, block_addr, block_len))
    {
        FIXED_PRINTF("Error : %s, SEE code load failed\n", __FUNCTION__);
        goto bl_ota;
    }
    set_see_code_info((UINT32)see_decrypted, block_len, SEE_ENTRY);
    set_see_sig_info((UINT32)see_decrypted + block_len - SIG_LEN, SIG_LEN, RSASSA_PKCS1_V1_5);
    set_see_key_info(&ukey);
    if (RET_SUCCESS != bl_verify_sw_see(DUVS_SEE))
    {
        FIXED_PRINTF("Error : %s, bootloader see software trig failed\n", __FUNCTION__);
        goto bl_ota;
    }

    if ((0 == cpu_mc_len) || \
        (0 == bl_unzip_sw(main_decrypted, cpu_mc_len, MAIN_CODE)))
    {
        FIXED_PRINTF("Main code decrypt error\n");
        goto bl_ota;
    }
    main_entry = (UINT8 *)MAIN_ENTRY;

    if (0 != version_check((UINT32)CHUNKID_FW, (UINT32)main_entry, unzip_length))
    {
        FIXED_PRINTF("Error : %s, main software version check failed\n", __FUNCTION__);
        goto bl_ota;
    }
#else
    if (RET_SUCCESS != bl_get_uboot_addr(g_boot_type, &chid))
    {
        FIXED_PRINTF("Error : %s, can't get uboot address.\n", __FUNCTION__);
        goto bl_reboot;
    }
    block_len = 0;

    if (1 != g_boot_type)
    {
        if (RET_SUCCESS != bl_get_chunk_len(chid, &block_addr, &block_len))
        {
            FIXED_PRINTF("Error : %s, can't find chunk id 0x%08x.\n", __FUNCTION__, chid);
            goto bl_reboot;
        }
        else if (0 == block_len)
        {
            FIXED_PRINTF("Error : %s, the length of chunk 0x%08x is 0.\n", __FUNCTION__, chid);
            goto bl_reboot;
        }

        main_decrypted = (UINT8 *)(0xFFFFFFF8 & (UINT32)MALLOC(block_len + 0xf));
        if (RET_SUCCESS != aes_cbc_decrypt_chunk(ukey.kl_key_pos, chid, main_decrypted, &cpu_mc_len))
        {
            FIXED_PRINTF("Error : %s, Main code decrypt failed\n", __FUNCTION__);
            goto bl_reboot;
        }
    }
    else
    {
        FIXED_PRINTF("Load uboot:\n");
        cpu_mc_len = g_nand_info.uboot_len;
        main_encrypted = (UINT8*)(0xFFFFFFF8 & (UINT32)MALLOC(cpu_mc_len + 0xf));
        if (0 != api_load_data_from_nandflash(chid, cpu_mc_len, main_encrypted))
        {
            FIXED_PRINTF("Error : %s, load uboot fail...\n", __FUNCTION__);
            goto bl_reboot;
        }
        main_decrypted = (UINT8*)(0xFFFFFFF8&(UINT32)MALLOC(cpu_mc_len+0xf));
        aes_cbc_decrypt_ram_chunk(ukey.kl_key_pos, main_decrypted, main_encrypted, cpu_mc_len);
        free(main_encrypted);
        main_encrypted = NULL;
    }
    main_entry = (UINT8 *)MAIN_ENTRY;
    MEMCPY((UINT8 *)MAIN_ENTRY, main_decrypted, cpu_mc_len);
    osal_cache_flush((UINT8 *)MAIN_ENTRY, cpu_mc_len);
    unzip_length = cpu_mc_len;
    if (0 != version_check((UINT32)CHUNKID_UBOOT, (UINT32)MAIN_ENTRY, unzip_length))
    {
        FIXED_PRINTF("Error : %s, main software version check failed\n", __FUNCTION__);
        goto bl_reboot;
    }
#endif

    if ((0 == unzip_length) || \
        (0 != test_rsa_ram((UINT32)main_entry, unzip_length)))
    {
        FIXED_PRINTF("Error : %s, main software verify failed, sys will goto reboot ...\n", __FUNCTION__);
        goto bl_ota;
    }

#ifndef LINUX_BOOTLOADER
    if (RET_SUCCESS != bl_run_sw_see_later(0))
    {
        FIXED_PRINTF("see software run failed, sys will goto reboot ...\n");
        goto bl_ota;
    }
#else
    set_uboot_config((UINT32)main_entry);
#endif

    if (RET_SUCCESS != bl_enter_sys_sw(main_entry, unzip_length))
    {
        goto bl_ota;
    }

bl_ota:
#if ((!defined LINUX_BOOTLOADER) && (defined _OTA_E_))
#ifdef BL_VSC_ENABLE
    MEMSET(&ukey, 0x0, sizeof(UKEY_INFO));
    if(RET_SUCCESS != bl_prepare_key(&ukey))
    {
        FIXED_PRINTF("Error : %s, prepare key failed!\n", __FUNCTION__);
        goto bl_reboot;
    }
#endif
    if (RET_SUCCESS != app_init_ota(ukey))
    {
        goto bl_reboot;
    }
#endif

bl_reboot:
    FIXED_PRINTF("Bootloader reboot...\n");
    hw_watchdog_reboot();
    while (1)
    {
        ;
    }
}
#else
/*retailer or sw CA flow*/
void app_init(void)
{
    UINT8 crc_bad = 0;

#ifdef DUAL_ENABLE
    bl_init_see(SEE_ENTRY + 0x01000000);
#endif
    /************       Initialize      ***********************/
    sys_uart_init();
    FIXED_PRINTF("HW BootLoader APP  init!\n");
#ifndef _LINUX_BOOTLOADER_
    sys_gpio_init();
    sys_panel_init();
    panel_dev = (struct pan_device *)dev_get_by_id(HLD_DEV_TYPE_PAN, 0);
    if (NULL == panel_dev)
    {
        FIXED_PRINTF("Error : %s, Can't get panel device!\n", __FUNCTION__);
        goto bl_reboot;
    }
    pan_display(panel_dev, " ON ", 4);
#endif

#ifdef _MPLOADER_ENABLE_
    FIXED_PRINTF("Mp loader begin to run\n");
    if( RET_SUCCESS != mp_app())
    {
        FIXED_PRINTF("Error : %s, Mp Application run failed\n", __FUNCTION__);
        goto bl_reboot;
    }
#endif

    g_boot_type = sys_ic_get_boot_type();
    FIXED_PRINTF("g_boot_type = %d\n", g_boot_type);
    boot_enter_standby();

    bl_init_flash();
    mg_setup_crc_table();
    FIXED_PRINTF("MG_Setup_CRC_Table finish.\n");
    crc_bad = check_program();
    FIXED_PRINTF("check_program finish.\n");

    if (NO_ERR == crc_bad)
    {
#ifdef _BOOT_LOGO_
        if (RET_FAILURE == bl_init_logo())
        {
            FIXED_PRINTF("Error : %s, Show logo error.\n", __FUNCTION__);
            goto bl_reboot;
        }
#endif

#ifdef ENABLE_UART_UPG
        if( TRUE == check_sw_upgrade() ) /* force download */
        {
            serial_upgrade();
        }
#endif

        bl_load_and_launch_sw();
    }
    else
    {
        bl_load_and_launch_ota();
    }

bl_reboot:
    FIXED_PRINTF("Error : %s, Bootloader fail\n", __FUNCTION__);
    SDBBP();
}
#endif

