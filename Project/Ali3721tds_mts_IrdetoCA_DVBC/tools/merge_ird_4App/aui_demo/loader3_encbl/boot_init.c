/*****************************************************************************
*    Copyright (c) 2013 ALi Corp. All Rights Reserved
*    This source is confidential and is ALi's proprietary information.
*    This source is subject to ALi License Agreement, and shall not be
     disclosed to unauthorized individual.
*    File: boot_init.c
*
*    Description:    This file contains HLD functions and device initialize function
*                     declare of ALi boot loader.
*
*    THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
     KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
     IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
     PARTICULAR PURPOSE.
*****************************************************************************/
#include <sys_config.h>
#include <sys_parameters.h>
#include <api/libc/printf.h>
#include <api/libc/string.h>
#include <api/libchunk/chunk.h>
#include <bus/sci/sci.h>
#include <bus/flash/flash.h>
#include <hal/hal_gpio.h>
#include <hal/hal_mem.h>
#include <hld/pan/pan_dev.h>
#include <hld/smc/smc.h>
#include <hld/pan/pan.h>
#include <bus/i2c/i2c.h>
#include <bus/otp/otp.h>
#include <api/libloader/ld_boot_info.h>
#include <api/librsa/flash_cipher.h>
#include <api/librsa/rsa_verify.h>

#include "bootloader.h"

#if(SYS_MAIN_BOARD == BOARD_DEMO_M3281_01V01)
static gpio_info_t bl_gpio_array[] =
{
        {1, HAL_GPIO_O_DIR, 45},        //SYS_I2C_SDA //panel data
        {1, HAL_GPIO_O_DIR, 44},        //SYS_I2C_SCL  //panel clock
        {1, HAL_GPIO_O_DIR, 49}, //panel lock
        {1, HAL_GPIO_O_DIR, 54}, //panel com1
        {1, HAL_GPIO_O_DIR, 55}, //panel com2
        {1, HAL_GPIO_O_DIR, 51}, //panel com3
        {1, HAL_GPIO_O_DIR, 60}, //panel com4
        {1, HAL_GPIO_O_DIR, 58}, //panel key1
        {1, HAL_GPIO_O_DIR, 59}, //panel key2
        {0, HAL_GPIO_O_DIR, 20}, //SMC 5V/3.3V switch

};
#elif(SYS_MAIN_BOARD == BOARD_DB_M3281_01V01)
static gpio_info_t bl_gpio_array[] =
{
        {1, HAL_GPIO_O_DIR, 45},        //SYS_I2C_SDA
        {1, HAL_GPIO_O_DIR, 44},        //SYS_I2C_SCL
        {0, HAL_GPIO_O_DIR, 20}, //SMC 5V/3.3V switch

};
static UINT32 g_panel_id = I2C_TYPE_GPIO0;
#endif

static i2c_cfg i2c_config[4] =
{
        {I2C_TYPE_SCB0, 100000, 1, NULL, NULL},
        {I2C_TYPE_SCB1, 100000, 1, NULL, NULL},
        {I2C_TYPE_GPIO0, 40000, 1, &bl_gpio_array[0], &bl_gpio_array[1]},
        {I2C_TYPE_GPIO1, 100000, 1, &bl_gpio_array[0], &bl_gpio_array[1]},
};

static UINT32 g_gpio_count = ARRAY_SIZE ( bl_gpio_array );

static struct pan_hw_info pan_hw_info =
{
        0,                  /* type_kb : 2; Key board (array) type */
        1,                 /* type_scan : 1; 0: Slot scan, 1: Shadow scan */
        1,                 /* type_key: 1; Key exit or not */
        1,                  /* type_irp: 3; 0: not IRP, 1: NEC, 2: LAB */
        0,                  /* type_mcu: 1; MCU exit or not */
        4,                  /* num_com: 4; Number of com PIN, 0 to 8 */
        1,                  /* Position of colon flag, 0 to 7 */
        1,                  /* num_scan: 2; Number of scan PIN, 0 to 2 */
        0,                  /* rsvd_bits:6; Reserved bits */
        0,              /* rsvd byte for align pan_info */
        {0, HAL_GPIO_O_DIR, 127},               /* LATCH PIN */
        {0, HAL_GPIO_O_DIR, 127},           /* CLOCK PIN */
        {1, HAL_GPIO_O_DIR, 127},           /* DATA PIN */
        {       {0, HAL_GPIO_I_DIR, 127},           /* SCAN1 PIN */
                {0, HAL_GPIO_I_DIR, 127}
        },              /* SCAN2 PIN */
        {       {0, HAL_GPIO_O_DIR,    127},           /* COM1 PIN */
                {0, HAL_GPIO_O_DIR,     127},           /* COM2 PIN */
                {0, HAL_GPIO_O_DIR,     127},           /* COM3 PIN */
                {0, HAL_GPIO_O_DIR,     127},           /* COM4 PIN */
                {0, HAL_GPIO_O_DIR, 127},               /* COM5 PIN */
                {0, HAL_GPIO_O_DIR, 127},               /* COM6 PIN */
                {0, HAL_GPIO_O_DIR, 127},               /* COM7 PIN */
                {0, HAL_GPIO_O_DIR, 127}
        },              /* COM8 PIN */
        {       {0, HAL_GPIO_O_DIR,    127},           /* POWER PIN */
                {1, HAL_GPIO_O_DIR,     127},           /* LOCK PIN */
                {0, HAL_GPIO_O_DIR, 127},         /* Extend function LBD */
                {0, HAL_GPIO_O_DIR, 127}
        },              /* Extend function LBD */
        {0, HAL_GPIO_O_DIR, 127},       /* rsvd extend function LBD */
        300,                            /* Intv repeat first */
        250,                            /* Intv repeat */
        350,                     /* Intv release, 0: disable release key */
        NULL,                           /* hook_scan() callback */
        NULL,                            /* hook_show() callback */
        0
};

static struct pan_configuration pan_config = {
                    &pan_hw_info,
                    BITMAP_LIST_NUM,
                    BITMAP_LIST
                      };

static UINT32 unzip_length=0;
static UINT32 see_unzip_length=0;

struct pan_device *panel_dev = NULL;
struct sto_device *flash_dev = NULL;
UINT8 *g_see_unziped   = NULL;
UINT32 g_ota_offset = 0;

static void bl_gpio_dir_set_ext ( gpio_info_t gpio_info[], UINT8 count )
{
    UINT32 j =0 ;

    gpio_info_t *gpio =  NULL;

    for ( j = 0; j < count; j++ )
    {
        gpio = &gpio_info[j];
        HAL_GPIO_BIT_DIR_SET ( gpio->position, gpio->io );
    }
}

static void bl_gpio_set_ext ( gpio_info_t gpio_info[], UINT8 count )
{
    UINT32 j = 0;

    gpio_info_t *gpio = NULL ;

    for ( j = 0; j < count; j++ )
    {
        gpio = &gpio_info[j];
        HAL_GPIO_BIT_SET ( gpio->position, gpio->polar );
    }
}

static RET_CODE bl_gpio_init(void)
{
    UINT32 i2c_id = 0;
    UINT32 reg_addr[] =
    {
         GPIO_REG,
     GPIOA_REG,
     GPIOB_REG,
     GPIOC_REG,
    };
    UINT32 i=0,
            j =0;
    UINT32 value = 0;
    gpio_info_t *gpio = NULL;
    gpio_info_t *sda = NULL;
    gpio_info_t *scl = NULL;
    RET_CODE ret = -1 ;

    /* disable all GPIO firstly*/
    for ( i = 0; i < ARRAY_SIZE ( reg_addr ); i++ )
    {
        value = 0;
        for ( j = 0; j < g_gpio_count; j++ )
        {
                gpio = &bl_gpio_array[j];
                if ( gpio->position >= ( i * 32 ) && gpio->position < ( ( i + 1 ) * 32 ) )
        {
                        value |= 1 << ( gpio->position - ( i * 32 ) );
        }
        }
        *( ( volatile unsigned long *) reg_addr[i] ) = value;
    }
    bl_gpio_dir_set_ext ( bl_gpio_array, g_gpio_count );
    bl_gpio_set_ext ( bl_gpio_array, g_gpio_count );

    ret =i2c_scb_attach ( 2 );
    if(SUCCESS != ret)
    {
        FIXED_PRINTF ( "%s i2c_scb_attach fail!\n",__FUNCTION__ );
        return ret ;
    }

    ret = i2c_gpio_attach ( 3 );
    if(SUCCESS != ret)
    {
        FIXED_PRINTF ( "%s i2c_gpio_attach fail!\n",__FUNCTION__ );
        return ret ;
    }

    for ( i = 0; i < 4; i++ )
    {
        if ( NULL != ( &i2c_config[i] ) )
        {
            i2c_id = ( &i2c_config[i] )->i2c_id;
            sda = ( &i2c_config[i] )->sda;
            scl = ( &i2c_config[i] )->scl;
            if ( ( ( i2c_id & I2C_TYPE_MASK ) == I2C_TYPE_GPIO ) && ( NULL != sda ) && ( NULL != scl ) )
            {
                i2c_gpio_set ( i2c_id & I2C_ID_MASK, sda->position, scl->position );
            }

            if ( ( &i2c_config[i] )->bps != 0 )
                i2c_mode_set ( i2c_id, ( &i2c_config[i] )->bps, 1 );
        }
    }
    return RET_SUCCESS;
}

static RET_CODE bl_init_uart(void)
{
    OTP_CONFIG my_otp_cfg;
    UINT32 otp_check = 0;
    RET_CODE ret = RET_FAILURE ;

    //OTP Bus Driver Setting
    MEMSET ( ( void * ) ( &my_otp_cfg ), 0, sizeof ( OTP_CONFIG ) );
    ret = otp_init ( &my_otp_cfg );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%S:otp init fail !!\n", __FUNCTION__ );
        return ret ;
    }

    ret = otp_read ( 0x3 * 4, (UINT8 *)(&otp_check), sizeof(otp_check));
    if(ret <OTP_DW_LEN )
    {
        FIXED_PRINTF ( "%S:otp read fail !!\n", __FUNCTION__ );
        return ret ;
    }

    if ( 0 == ( ( 1 << 12 ) &otp_check ) )
    {
        libc_printf_uart_id_set ( SCI_FOR_RS232 );
        ret = sci_16550uart_attach ( 1 );     // Use just 1 UART for RS232
        if(ret != RET_SUCCESS)
        {
            FIXED_PRINTF ( "%S:uart_attach fail !!\n", __FUNCTION__ );
            return ret ;
        }
        sci_mode_set ( SCI_FOR_RS232, 115200, SCI_PARITY_EVEN );
    }
    FIXED_PRINTF ( "\nHW BootLoader APP  init!\n" );
    FIXED_PRINTF ( "OTP 0x03 = 0x%x!\n", otp_check );
    return RET_SUCCESS ;
}

static RET_CODE bl_init_flash(void)
{
    INT32 ret = RET_FAILURE;

    //init flash device
    *( ( unsigned long *) 0xb802e098 ) |=  0xc2000000; //for flash can read 4M

#ifndef ENABLE_SERIAL_FLASH
    #ifdef ENABLE_UART_UPG
    flash_info_pl_init();     
    #endif
    ret = sto_local_flash_attach ( NULL );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%s sto flash attach fail !\n", __FUNCTION__ );
        return ret :
    }
#else
    #ifdef ENABLE_UART_UPG
    flash_info_sl_init();
    #endif
    ret = sto_local_sflash_attach ( NULL );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%s sto flash attach fail !\n", __FUNCTION__ );
        return ret ;
    }
#endif
    flash_dev = ( struct sto_device * ) dev_get_by_type ( NULL, HLD_DEV_TYPE_STO );
    if ( flash_dev == NULL )
    {
        FIXED_PRINTF ( "Can't find FLASH device!\n" );
        return RET_FAILURE;
    }

    ret = sto_open ( flash_dev );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%s sto open fail!\n",__FUNCTION__);
        return ret ;
    }
    sto_chunk_init ( 0, flash_dev->totol_size );
    FIXED_PRINTF ( "flash init OK,flash size is:%x!\n", flash_info.flash_size );

    ret = get_sys_pub_key(PK_FROM_FLASH,NULL,0);
    if(RET_SUCCESS != ret)
    {
        FIXED_PRINTF ( "Get public key failed!\n" );
        return RET_FAILURE;
    }
    return RET_SUCCESS;
}

static RET_CODE bl_init_panel(void)
{
    UINT32 i = 0;
    UINT8 *t1 = NULL,
           *t2 = NULL;
    UINT32 boot_cfg = 0;
    RET_CODE ret = RET_FAILURE;

    boot_cfg = get_boot_cfg_addr() - 0x80;
    t2 =(UINT8 *)(boot_cfg + HW_SET_GPIO
);

#ifdef PANEL_DISPLAY

#if(SYS_MAIN_BOARD == BOARD_DB_M3281_01V01)
    ret = pan_ch455_attach ( &pan_config );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%s pan attach fail!\n",__FUNCTION__);
        return ret ;
    }

    panel_dev = ( struct pan_device * ) dev_get_by_id ( HLD_DEV_TYPE_PAN, 0 );
    pan_ch455_id_set ( panel_dev, g_panel_id );
#elif((SYS_MAIN_BOARD == BOARD_DEMO_M3281_01V01))
    FIXED_PRINTF ( "bl pan hwscan attach,0x%x\n", t2 );
    t1 = ( UINT8* ) ( &pan_hw_info );
    for ( i = 0; i < sizeof ( struct pan_hw_info ); i++ )
    {
            *( t1 + i ) = *( t2 + i );
    }
    ret = pan_hwscan_l_attach ( &pan_config );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%s hwsacn attach fail!\n",__FUNCTION__);
        return ret ;
    }
    panel_dev = ( struct pan_device * ) dev_get_by_id ( HLD_DEV_TYPE_PAN, 0 );
#endif
    if ( panel_dev == NULL )
    {
        FIXED_PRINTF ( "panel attach fail!\n" );
        return RET_FAILURE;
    }
    ret = pan_open ( panel_dev );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%s pan open fail!\n",__FUNCTION__);
        return ret ;
    }

    ret = pan_display ( panel_dev, " ON ", 4 );
    if(ret != RET_SUCCESS)
    {
        FIXED_PRINTF ( "%s pan display fail!\n",__FUNCTION__);
        return ret ;
    }

#endif
    FIXED_PRINTF ( "panel init OK!\n" );
    return RET_SUCCESS;
}

/*initialize the peripheral device which shall be used in bootloader
*/
RET_CODE bl_init_dev(void)
{
    RET_CODE ret  = RET_FAILURE ;

     dev_en_remote ( 0 );
     ret = bl_gpio_init();
    if(RET_SUCCESS!= ret )
    {
        FIXED_PRINTF("%s: gpio_init fail!\n",__FUNCTION__);
        goto init_err;
    }
    ret = bl_init_uart();
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF("%s: uart_init fail!\n",__FUNCTION__);
        goto init_err;
    }
    ret =bl_init_panel();
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF("%s: panel_init fail!\n",__FUNCTION__);
        goto init_err;
    }

    ret = bl_init_flash();
    if( RET_SUCCESS != ret)
    {
        FIXED_PRINTF("%s: flash_init fail!\n",__FUNCTION__);
        goto init_err;
    }
    dev_en_remote ( 1 );

    return RET_SUCCESS ;
init_err:
    return RET_FAILURE ;

}


#ifdef ENABLE_UART_UPG
INT32 update_flash_data(UINT32 offset, INT32 len, UINT8 * data)
{
    UINT8 *app_flash_buffer = NULL;
    INT32 ret=0;

    FIXED_PRINTF("%s-offset(0x%x),len(0x%x),data(0x %2x %2x %2x %2x)\n", \
                      __FUNCTION__,offset,len,data[0],data[1],data[2],data[3]);

    app_flash_buffer = MALLOC(64*1024);
    if(app_flash_buffer==NULL)
    {
        FIXED_PRINTF("update_flash_data: allocate buffer failed\n");
        return -1;
    }

    sto_io_control(flash_dev, STO_DRIVER_SECTOR_BUFFER, (UINT32)app_flash_buffer);

    sto_io_control(flash_dev, STO_DRIVER_SET_FLAG, \
                        STO_FLAG_AUTO_ERASE|STO_FLAG_SAVE_REST);

    ret=sto_put_data(flash_dev, (UINT32)offset, data, (INT32)len);

    FREE(app_flash_buffer);
    app_flash_buffer = NULL;
    sto_io_control(flash_dev, STO_DRIVER_SECTOR_BUFFER, 0);
    sto_io_control(flash_dev, STO_DRIVER_SET_FLAG, 0);

    return ret;
}
#endif

#ifdef ENABLE_UART_UPG
BOOL check_sw_upgrade()
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
void serial_upgrade(void)
{
    hw_watchdog_stop();
    lib_ash_shell();
}
#endif

static UINT8 *expand_ram ( UINT32 addr,
                        UINT32 len,
                        int unzip ( UINT8 *, UINT8 *, UINT8 * ),
                        UINT32 type )
{
        UINT8 *buffer = NULL;
        UINT8 *codeentry = NULL;

        if ( (type == MAIN_CODE) || \
        (type == OTA_CPU_CODE ))
    {
                codeentry = ( UINT8 * ) MAIN_ENTRY;
    }
        else if ( (type == SEE_CODE) || \
        (type == OTA_SEE_CODE) )
    {
                codeentry = g_see_unziped;
    }
        if((BUFFER_SIZE!=0)&&(BUFFER_SIZE<0xffffffff))
            buffer = MALLOC ( BUFFER_SIZE );
        if ( buffer == NULL )
        {
                FIXED_PRINTF ( "Boot loader: No decompress buffer!\n" );
                return NULL;
        }

        if ( unzip ( ( void * ) ( addr ), codeentry, buffer ) != 0 )
        {
                codeentry = 0;
                FIXED_PRINTF ( "Boot loader: error to decompress chunk(type %d)!\n", type );
                return NULL ;
        }
        else
        {
               // unzip_length = * ( UINT32* ) buffer;
              if ( (type == MAIN_CODE) || (type == OTA_CPU_CODE) )
          {
                unzip_length = *( UINT32 *)buffer;
           }
              else if ( (type == SEE_CODE) || (type == OTA_SEE_CODE) )
          {
                see_unzip_length = *( UINT32 *)buffer;
          }
        }

        FREE ( buffer );
        return codeentry;
}

static void set_os_config ( UINT16 task_num, UINT16 sema_num, UINT16 flg_num, UINT16 mbf_num, UINT16 mutex_num )
{
        struct os_config *ptr = ( struct os_config *) 0xa00001e0;

        ptr->task_num = task_num;
        ptr->sema_num = sema_num;
        ptr->flg_num = flg_num;
        ptr->mbf_num = mbf_num;
        ptr->mutex_num = mutex_num;
        ptr->parity_value = ptr->task_num + ptr->sema_num + ptr->flg_num + ptr->mbf_num + ptr->mutex_num;
}

RET_CODE bl_enter_ota_loader(UINT8 *ota_decrypted, UINT32 ota_len)
{
    UINT32 chunk_head_length = 128;
    UINT32 ota_cpu_len = 0;
    UINT32 ota_see_addr = 0;
    UINT32 ota_see_len = 0;
    UINT32 ziped_len = 0;
    UINT8 *p=NULL;
    UINT8 *main_entry=NULL,
          *see_entry=NULL;

    UINT8 *ret_val = NULL ;

    FIXED_PRINTF ( "\nEnter OTA loader by sys_sw_wrong \n");
    p = ota_decrypted + ( ota_len - 0x200 );
    ziped_len = ( p[3] | ( p[2] << 8 ) | ( p[1] << 16 ) | ( p[0] << 24 ) );
    ret_val = expand_ram ( (UINT32)ota_decrypted, ziped_len, un7zip, OTA_CPU_CODE );
    if(ret_val == NULL)
    {
        FIXED_PRINTF ( "OTA_CPU_CODE uzip fail !!!\n"  );
        return RET_FAILURE ;
    }

    if((unzip_length!=0)&&(unzip_length<0xffffffff))
        ota_decrypted = ( UINT8 *) MALLOC ( unzip_length + 0xf );
    if(!ota_decrypted)
    {
       FIXED_PRINTF ( "OTA_malloc fail 1 !!!\n"  );
        return RET_FAILURE ;
    }
    ota_decrypted = ( UINT8 * ) ( ( 0xFFFFFFF8 & ( UINT32 ) (ota_decrypted )) );
    FIXED_PRINTF ( "ota_decrypted: 0x%08x\n", ota_decrypted );
    MEMCPY ( ota_decrypted, ( UINT8 * ) MAIN_ENTRY, unzip_length );

    p = ota_decrypted + 0x4;
    ota_cpu_len = ( p[3] | ( p[2] << 8 ) | ( p[1] << 16 ) | ( p[0] << 24 ) );
    p = ota_decrypted + 0x8;
    ota_see_addr = ( p[3] | ( p[2] << 8 ) | ( p[1] << 16 ) | ( p[0] << 24 ) );
    p = ota_decrypted + ota_see_addr + 0x4;
    ota_see_len = ( p[3] | ( p[2] << 8 ) | ( p[1] << 16 ) | ( p[0] << 24 ) );
    FIXED_PRINTF ( "\n cpu:0x%x,see:0x%x,0x%x\n", ota_cpu_len, ota_see_len, ota_see_addr );

    //excute see ota code
    FIXED_PRINTF ( "expand ota see code, ziped len: %d\n", ota_see_len );
    //for decompress use.
    g_see_unziped = ( UINT8 *) MALLOC ( ota_see_len * 4 + 0xf );
    if(NULL ==g_see_unziped)
    {
        FIXED_PRINTF ( "OTA_malloc fail 2 !!!\n"  );
        return RET_FAILURE ;
    }
  //  osal_cache_invalidate ( g_see_unziped, ota_see_len * 4 + 0xf );
    g_see_unziped = ( UINT8* ) ( ( 0xFFFFFFF8 & ( UINT32 ) g_see_unziped ) );

    see_entry = expand_ram ( (UINT32)ota_decrypted + ota_see_addr + chunk_head_length, ota_see_len, un7zip, OTA_SEE_CODE );
    if ( see_entry )
    {
        osal_cache_flush ( see_entry, see_unzip_length );
        FIXED_PRINTF ( "success, see_unzip_length len: %d,g_see_unziped:0x%08x\n", see_unzip_length,g_see_unziped );
        self_boot ( SEE_ENTRY, (UINT32)see_entry, see_unzip_length, 0 );
    }
    else
    {
        FIXED_PRINTF ( "see software uzip fail !!!\n"  );
        return RET_FAILURE ;
    }
    //excute cpu ota code
    FIXED_PRINTF ( "expand ota cpu code, ziped len: %d\n", ota_cpu_len );
    main_entry = expand_ram ( (UINT32)ota_decrypted + chunk_head_length, ota_cpu_len, un7zip, OTA_CPU_CODE );
    if ( main_entry )
    {
        set_os_config ( 128, 64, 64, 64, 64 );
        FIXED_PRINTF ( "success, unziped len: %d\n", unzip_length );
        hw_watchdog_stop();
        osal_cache_flush ( main_entry, unzip_length );
        exec ( (UINT32)main_entry );
    }
    FREE(ota_decrypted);

    return RET_FAILURE;
}

RET_CODE bl_enter_sys_sw(UINT8 *see_decrypted, UINT32 see_mc_len,UINT8 *main_decrypted, UINT32 cpu_mc_len)
{
    UINT32 ziped_len = 0;
    UINT8 *p=NULL;
    UINT8 *main_entry=NULL,
          *see_entry=NULL;

    p = see_decrypted + ( see_mc_len - 0x200 );
    ziped_len = p[3] | ( p[2] << 8 ) | ( p[1] << 16 ) | ( p[0] << 24 );
    //enter Maincode
    FIXED_PRINTF ( "expand see main code, ziped len: %d\n", ziped_len );
#ifdef LZO_COMPRESS_ENABLE
    see_entry = expand_ram ( (UINT32)see_decrypted, ziped_len, unlzo, SEE_CODE );
#else
    see_entry = expand_ram ( (UINT32)see_decrypted, ziped_len, un7zip, SEE_CODE );
#endif
    if(NULL == see_entry )
    {
        FIXED_PRINTF ( "see software uzip fail !!!n" );
        return RET_FAILURE;
    }

    p = main_decrypted + ( cpu_mc_len - 0x200 );
    ziped_len = p[3] | ( p[2] << 8 ) | ( p[1] << 16 ) | ( p[0] << 24 );
    FIXED_PRINTF ( "expand cpu main code, ziped len: %d\n", ziped_len );
#ifdef LZO_COMPRESS_ENABLE
    main_entry = expand_ram ( (UINT32)main_decrypted, ziped_len, unlzo, MAIN_CODE );
#else
    main_entry = expand_ram ( (UINT32)main_decrypted, ziped_len, un7zip, MAIN_CODE );
#endif
    if(NULL == main_entry )
    {
        FIXED_PRINTF ( "main software uzip fail !!!n" );
        return RET_FAILURE;
    }

#ifdef M3281_BOOT_WITH_LOGO
    bl_show_logo_close();
#endif
    if ( see_entry )
    {
        FIXED_PRINTF ( "success, unziped len: %d,see entry = 0x%x,\n", see_unzip_length, see_entry );
        osal_cache_flush ( see_entry, see_unzip_length );
        self_boot ( SEE_ENTRY, (UINT32)see_entry, see_unzip_length, 0 );
    }

    FIXED_PRINTF ( "success, unziped len: %d.\n", unzip_length );
    set_os_config ( 128, 64, 64, 64, 64 );
    FIXED_PRINTF ( "jump to fw entry=%x\n", main_entry );
    hw_watchdog_stop();
    osal_cache_flush ( main_entry, unzip_length );
    exec ( (UINT32)main_entry );

    return RET_FAILURE;
}

RET_CODE bl_prepare_key(UINT8 *pos)
{
    UINT32 chid=CHUNKID_MEM_CFG;
    CHUNK_HEADER chunk_hdr;
    UINT32 offset = 0;
    UINT8 key_pos = 0;
    RET_CODE ret=RET_FAILURE;

    MEMSET(&chunk_hdr,0 , sizeof(CHUNK_HEADER));
    if ( ( is_bl_encrypted_enable() ) && \
            ( sto_get_chunk_header ( CHUNKID_MEM_CFG, &chunk_hdr ) != 0 ) )
    {
        ret = sto_chunk_goto ( &chid, CHUNKID_MEM_CFG_MASK, 1 );
        if ( ret <0 )
        {
             FIXED_PRINTF ( "%s failed!!! \n", __FUNCTION__ );
             return ret;
        }
        else
        {
            offset =(UINT32)ret ;
            if (is_key_encrypted(offset, BL_FLASH_KEY)==FALSE)
            {
                ret = encrypt_bl_universal_key ( CHUNKID_MEM_CFG&CHUNKID_MEM_CFG_MASK);
                if(ret!=RET_SUCCESS)
        {
                    return ret;
                }
            }
        }

    }

    chid = CHUNKID_KEY;
    if ( sto_get_chunk_header ( CHUNKID_KEY, &chunk_hdr ) != 0 )
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
            #ifdef BL_VSC_ENABLE
                ret = encrypt_universal_key ( CHUNKID_KEY&CHUNKID_KEY_MASK|FIRST_FLASH_KEY|FLASH_TRI_LADDER_MODE_KEY02);
            #else
               ret = encrypt_universal_key ( (CHUNKID_KEY&CHUNKID_KEY_MASK)|FIRST_FLASH_KEY);
            #endif
               if(ret!=RET_SUCCESS)
           {
                  return ret;
        }
            }
        #ifdef BL_VSC_ENABLE
            ret = decrypt_universal_key ( &key_pos, (CHUNKID_KEY&CHUNKID_KEY_MASK|FIRST_FLASH_KEY|FLASH_TRI_LADDER_MODE_KEY02) );
        #else
            ret = decrypt_universal_key ( &key_pos, ((CHUNKID_KEY&CHUNKID_KEY_MASK)|FIRST_FLASH_KEY) );
        #endif
            if(ret!=RET_SUCCESS)
        {
                  return ret;
            }
        }
    }
    *pos = key_pos;
    return (ret = RET_SUCCESS);
}


#ifdef BL_VSC_ENABLE
RET_CODE bl_prepare_key_see(UINT8 *pos)
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
            //ret = decrypt_universal_key_see( &key_pos, (CHUNKID_KEY_SEE&CHUNKID_KEY_MASK|FLASH_TRI_LADDER_MODE_KEY02|FLASH_TRI_LADDER_MODE_KEY02) ); //yuchun0317
            ret = decrypt_universal_key( &key_pos, (CHUNKID_KEY_SEE&CHUNKID_KEY_MASK|FIRST_FLASH_KEY|FLASH_TRI_LADDER_MODE_KEY02) ); //yuchun0317
            if(ret!=RET_SUCCESS)
        {
                  return ret;
            }
        }
    }
    *pos = key_pos;

    return (ret = RET_SUCCESS);
}
#endif


#if(defined(ENABLE_4M_FLASH))
UINT8 find_second_loader ( void )
{
    UINT32 pointer = 0;
    UINT32 data_id = 0;
    UINT32 data_len = 0;
    UINT32 data_off = 0;
    UINT32 data_crc = 0;
    UINT8 *buffer = NULL;
    UINT32 crc = 0;
    UINT8 bsecond_ota = 0;

    FIXED_PRINTF ( "start find_second_loader()!\n" );
    while ( pointer < (UINT32)(flash_dev->totol_size) )
    {
        data_id = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_ID );
        data_len = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_LENGTH );
        data_off = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_OFFSET );
        data_crc = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_CRC );

        /*FIXED_PRINTF("@pointer[%08X] id[%08X] len[%08X] off[%08X] crc[%08X]\n", \
                              pointer, data_id, data_len, data_off, data_crc);
         */

        if ( ( 0 != data_len ) && ( data_len < data_off ) && ( data_crc != NO_CRC ) \
             && ( ( CHUNKID_SECLOADER == data_id ) ) )
        {
            buffer = ( UINT8 * ) MALLOC ( data_len );
            if(NULL == buffer)
            {
                FIXED_PRINTF ( "MALLOC fail!\n" );
                ASSERT ( 0 );
            }
            else
            {
                if( sto_get_data ( flash_dev, buffer, pointer + 16, data_len ) < 0)
                {
                    FIXED_PRINTF ( "flash data get fail!\n" );
                    ASSERT ( 0 );
                }
                crc = mg_table_driven_crc ( 0xFFFFFFFF, buffer, data_len );
                FREE ( buffer );
                if ( data_crc == crc )
                {
                    g_ota_offset = pointer;
                    bsecond_ota = 1;
                    FIXED_PRINTF ( "Find OTA LOADER!\n" );
                    break;
                }
                else
                {
                    FIXED_PRINTF ( "OTA CRC Check not pass!\n" );
                }
            }
      
            FREE(buffer);
        }
        pointer += C_SECTOR_SIZE;
    }

    // verify the second LOADER_OPK_SIZE

    if ( bsecond_ota )
    {
        pointer = g_ota_offset;
        do
        {

            data_id = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_ID );
            data_len = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_LENGTH );
            data_off = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_OFFSET );
            data_crc = sto_fetch_long ( ( UINT32 ) pointer + CHUNK_CRC );

            if ( !data_off )
            {
                break;
            }
            if ( ( (( data_id >> 16 ) & 0xFF) + (( data_id >> 24 ) & 0xFF) ) != 0xFF )
            {
                bsecond_ota = 0;
                break;
            }

            if ( data_off > (UINT32)(flash_dev->totol_size) )
            {
                /*FIXED_PRINTF("@pointer[%08X] id[%08X] data_off[%08X] > flash size\n", \
                      pointer, data_id, data_off);
                      */
                bsecond_ota = 0;
                break;
            }

            if ( NO_CRC != data_crc )
            {
                if ( NULL == ( buffer = ( UINT8 * ) MALLOC ( data_len ) ) )
                {
                    FIXED_PRINTF ( "MALLOC fail!\n" );
                    ASSERT ( 0 );
                }

                if (sto_get_data ( flash_dev, buffer, pointer + 16, data_len )<0)
                {
                    FIXED_PRINTF ( "flash data get fail!\n" );
                    ASSERT ( 0 );
                }
                crc = mg_table_driven_crc ( 0xFFFFFFFF, buffer, data_len );
                FREE ( buffer );
                FIXED_PRINTF ( "Read OTALOADER CRC!\n" );

                if ( data_crc != crc )
                {
                    FIXED_PRINTF ( "@pointer[%08X] id[%08X] crc[%08X] != data_crc[%08X]\n", \
                                   pointer, data_id, crc, data_crc );
                    bsecond_ota = 0;
                    break;
                }

            }
            pointer += data_off;

            if ( pointer + CHUNK_HEADER_SIZE > (UINT32)(flash_dev->totol_size) )
            {
                    FIXED_PRINTF ( "@pointer[%08X] no space for header\n", pointer );
                    bsecond_ota = 0;
                    break;
            }
        }
        while ( data_off );
    }

    if ( 0 == bsecond_ota )
    {
            FIXED_PRINTF ( "Second Loader not exist!\n" );
            g_ota_offset = 0;
    }
    FIXED_PRINTF ( "LEAVE find_second_loader\n" );
    return bsecond_ota;
}
#endif

RET_CODE bl_prepare_otaloader(UINT8 *ota_decrypted,UINT8 key_pos,
                            UINT32 block_addr, UINT32 block_len, UINT8 *len)
{
    RET_CODE ret = RET_FAILURE;
    UINT32 ota_len = 0;

    ret = aes_cbc_decrypt_flash_data ( key_pos,
                                       block_addr,
                                       block_len - CHUNK_HEADER_SIZE + CHUNK_NAME,
                                       ota_decrypted );
    if(RET_SUCCESS!=ret)
    {
        FIXED_PRINTF ( "%s decrypt flash fail!\n",__FUNCTION__ );
        return ret ;
    }
    FIXED_PRINTF ( "Verify OTA data!\n" );
    ota_len = block_len - CHUNK_HEADER_SIZE + CHUNK_NAME;
    *len = ota_len;
    FIXED_PRINTF ( "ota_len: %08X\n", ota_len );

    ret = test_rsa_ram ( ( UINT32 ) ota_decrypted, ota_len );
    if ( RET_SUCCESS != ret )
    {
        FIXED_PRINTF ( "OTA signature fail!\n" );
        ret= pan_display ( panel_dev, "ERR", 4 );
        return RET_FAILURE;
    }
    else
    {
        FIXED_PRINTF ( "OTA signature Pass!\n" );
        return RET_SUCCESS;
    }
}

RET_CODE bl_len_check(UINT32 len)
{
    return (len != 0) && ( len <= MAX_CODE_LEN) ? \
            RET_SUCCESS :\
            RET_FAILURE;
}
