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

static UINT8 g_key_pos =0;

/*Bootloader OTA flow*/
static RET_CODE bl_ota_app(void)
{

    RET_CODE ret  = RET_FAILURE ;
    UINT32 block_len =0 ,
            block_addr = 0 ,
            ota_len = 0;
    UINT8 *ota_decrypted = NULL;

    mg_setup_crc_table();
    if ( 0 != find_second_loader() )
    {
        block_addr = g_ota_offset + CHUNK_HEADER_SIZE;
        block_len = sto_fetch_long ( g_ota_offset + CHUNK_LENGTH );
        if((block_len!=0)&&(block_len<0xffffffff))
        {
            ota_decrypted = ( UINT8 * ) MALLOC ( block_len + 0xf );
            if(NULL == ota_decrypted)
                return RET_FAILURE;
            ota_decrypted = ( UINT8 * ) ( ( 0xFFFFFFF8 & ( UINT32 ) (ota_decrypted )) );

            ret = bl_prepare_otaloader(ota_decrypted,g_key_pos, block_addr, block_len, (UINT8 *)(&ota_len));
            if(ret!=RET_SUCCESS)
            {
                FIXED_PRINTF("prepare otaloader fail\n");
                FREE(ota_decrypted);
                ota_decrypted = NULL;
                return RET_FAILURE;
            }
        }
        else
        {
            goto ota_err;
        }
    }
    else
    {
        FIXED_PRINTF("Don't found second loader\n");
        ret = pan_display ( panel_dev, "ERR", 4 );
        goto ota_err;
    }

    /*if ota flow successful, goto ota but do not return,
    * otherwise ,reboot.
    */
    ret = bl_enter_ota_loader(ota_decrypted, ota_len);
    FIXED_PRINTF("Enter ota loader fail\n");
    return RET_SUCCESS;
ota_err:
    return RET_FAILURE;

}

void app_init ( void )
{

    UINT32 cpu_mc_len = 0,
       see_mc_len = 0;
    UINT32 block_addr = 0,
        block_len = 0;
    UINT8 *temp_buffer = NULL;
    UINT8 *main_decrypted = NULL;
    UINT8 *see_decrypted = NULL;
    unsigned long vsc_see_run_addr = 0;
    RET_CODE ret=RET_SUCCESS;
    UINT8 sys_sw_wrong = SYS_SW_PASS;
    UINT8 *f_temp = NULL;
    UINT32 ret_len=0;


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


#ifdef ENABLE_UART_UPG
    if( TRUE == check_sw_upgrade() ) /* force download */
    {
        serial_upgrade();
    }
#endif


     ret = bl_prepare_key(&g_key_pos);

    if(ret!=RET_SUCCESS)
    {
        FIXED_PRINTF("prepare key fail!\n");
        goto bl_reboot;
    }

    if(RET_SUCCESS != set_parameter_from_bl(0, NULL))
    {
        FIXED_PRINTF("prepare key fail!\n");
        goto bl_reboot;
    }

    if ( SYS_SW_PASS == sys_sw_wrong )
    {
        #ifdef BL_VSC_ENABLE
        FIXED_PRINTF("vsc_see_run_addr=0x%08x\n",vsc_see_run_addr);
        block_len = 0 ;
        if ( RET_FAILURE == sto_get_chunk_len ( CHUNKID_VSC_CODE, &block_addr, &block_len ) )
        {
            FIXED_PRINTF ( "Can't find chunk id 0x%08x.\n", CHUNKID_VSC_CODE );
            sys_sw_wrong = SYS_SW_FAIL;
        }
        else if ( RET_SUCCESS == bl_len_check(block_len))
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
            if(ret_len!=block_len)
            {
                FIXED_PRINTF("Get VSC from flash Failed!\n");
                goto bl_reboot;
            }
            //check VSC signature
            ret = test_vsc_rsa_ram ((UINT32)temp_buffer, block_len);
           if(RET_SUCCESS != ret)
           {
               FIXED_PRINTF ("VSC signature failed\n");
               goto bl_reboot;
           }

           if(SYS_SW_FAIL != sys_sw_wrong)
           {
               if (RET_SUCCESS != aes_cbc_decrypt_vsc(temp_buffer, block_len-VSC_SIGNATURE_LEN-VSC_VERSION_LEN))
                {
                FIXED_PRINTF ("VSC decrypt failed\n");
                goto bl_reboot;
                }
           }

           FREE(f_temp);
        }
        else
        {
            FIXED_PRINTF("Code length out of range\n");
            sys_sw_wrong = SYS_SW_FAIL ;
        }
     #endif
        /*decrypt and verfiy main code*/
        block_len = 0;
        if ( RET_FAILURE == sto_get_chunk_len ( CHUNKID_MAINCODE, &block_addr, &block_len ) )
        {
            FIXED_PRINTF ( "Can't find chunk id 0x%08x.\n", CHUNKID_MAINCODE );
            sys_sw_wrong = SYS_SW_FAIL;
        }
        else if ( RET_SUCCESS == bl_len_check(block_len) )
        {
            main_decrypted = ( UINT8* ) (( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( block_len + 0xf ) ) );
            if( NULL == main_decrypted)
            {
                FIXED_PRINTF ("%s: out of main memory \n",__FUNCTION__);
                sys_sw_wrong = SYS_SW_FAIL;
                goto bl_reboot ;
            }
            ret = aes_cbc_decrypt_chunk ( g_key_pos, CHUNKID_MAINCODE, main_decrypted, &cpu_mc_len );
            if( RET_SUCCESS != ret)
            {
                FIXED_PRINTF ( "%s: main code decrypt fail\n",__FUNCTION__ );
                sys_sw_wrong = SYS_SW_FAIL;   
            }
            //decrypt CPU Main code
            FIXED_PRINTF ( "\ndecrypt CPU Main code,%x,%x,%x.\n", g_key_pos, CHUNKID_MAINCODE, cpu_mc_len );
            FIXED_PRINTF ( "verify CPU main.\n" );
        }
        else
        {
            FIXED_PRINTF("Code length out of range\n");
            sys_sw_wrong = SYS_SW_FAIL ;
        }

        if((SYS_SW_PASS == sys_sw_wrong ) && ( cpu_mc_len != 0 ))
        {
            ret = test_rsa_ram ( ( UINT32 ) main_decrypted, cpu_mc_len );
            if(RET_SUCCESS != ret )
            {
                FIXED_PRINTF ( "main signautre error\n" );
                sys_sw_wrong = SYS_SW_FAIL;
            }
        }

    }

    /*see decrypt and verify*/
#ifdef BL_VSC_ENABLE
     ret = bl_prepare_key_see(&g_key_pos);

    if(ret!=RET_SUCCESS)
    {
        FIXED_PRINTF("prepare key fail!\n");
        goto bl_reboot;
    }
#endif
    if ( SYS_SW_PASS == sys_sw_wrong )
    {
        /*decrypt and verify SEE Main code*/
        block_len = 0;
        ret = sto_get_chunk_len ( CHUNKID_SEECODE, &block_addr, &block_len );
        if ( RET_SUCCESS != ret )
        {
            FIXED_PRINTF ( "Can't find chunk id 0x%08x.\n", CHUNKID_MAINCODE );
            sys_sw_wrong = SYS_SW_FAIL;
        }
        else if ( RET_SUCCESS == bl_len_check(block_len) )
        {
            see_decrypted = ( UINT8* ) ( ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( block_len + 0xf ) ) );
            if(NULL == see_decrypted )
            {
                FIXED_PRINTF ("%s: out of see memory \n",__FUNCTION__);
                goto bl_reboot;
            }
            ret = aes_cbc_decrypt_chunk ( g_key_pos, CHUNKID_SEECODE, see_decrypted, &see_mc_len );
            if( RET_SUCCESS != ret)
            {
                FIXED_PRINTF ("%s: decrypt see fail \n",__FUNCTION__);
                sys_sw_wrong = SYS_SW_FAIL;
            }
            else
            {
                FIXED_PRINTF ( "\ndecrypt SEE Main code,%x,%x,%x.\n", g_key_pos, CHUNKID_SEECODE, see_mc_len );
                FIXED_PRINTF ( "verify see main.%x\n", see_mc_len );
                 /* decompress buffer*/
                g_see_unziped = ( UINT8* ) ( ( 0xFFFFFFF8 & ( UINT32 ) MALLOC ( block_len * 4 ) ) );
                if( NULL == g_see_unziped )
                {
                    FIXED_PRINTF ("%s: out of see unzip memory \n",__FUNCTION__);
                    sys_sw_wrong = SYS_SW_FAIL;
                }

                ret = test_rsa_ram ( ( UINT32 ) see_decrypted, see_mc_len );
                if(ret != RET_SUCCESS )
                {
                    FIXED_PRINTF ( "RSA verify error\n" );
                    sys_sw_wrong = SYS_SW_FAIL;
                }

            }
        }
        else
        {
            FIXED_PRINTF("Code length out of range\n");
            sys_sw_wrong = SYS_SW_FAIL ;
        }
    }

    if( SYS_SW_PASS == sys_sw_wrong )
    {
        ret = bl_enter_sys_sw(see_decrypted, see_mc_len,main_decrypted,cpu_mc_len);
        if( RET_SUCCESS != ret)
        {
            FIXED_PRINTF("%s:enter sys_sw fail",__FUNCTION__);
            goto bl_reboot ;
        }
    }
    else
    {
#ifdef BL_VSC_ENABLE
        ret = bl_prepare_key(&g_key_pos);
        if(ret!=RET_SUCCESS)
        {
            FIXED_PRINTF("prepare key fail!\n");
            goto bl_reboot;
        }
#endif  
        /*firmware verfiy fail, try ota flow*/
        ret = bl_ota_app();
        if( RET_SUCCESS != ret)
        {
            FIXED_PRINTF("%s:enter ota fail",__FUNCTION__);
            goto bl_reboot ;
        }
    }

bl_reboot:
    /*loader code error, reboot right now!*/
    hw_watchdog_reboot();
    do{}while(1);
}


