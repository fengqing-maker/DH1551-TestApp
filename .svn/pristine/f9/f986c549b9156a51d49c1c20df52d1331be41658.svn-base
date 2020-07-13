#include "chip_m3505.h"
#include "../chip.h"
#include <hld/sec_boot/sec_boot.h>


typedef struct
{
    chip_init_param param;
    //...
}chip_priv;

extern UINT32 sys_ic_seerom_is_enabled();
extern void check_see_clock();




static void gpio_enable_pos(INT32 pos, BOOL enable_flag)
{
    UINT32 gpio_enable_reg = GPIO_REG;
    UINT32 reg_idx;
    UINT32 data;

    if (pos >= 160)
        return;

	if(pos < 0)
	{
		return;
	}
    reg_idx = pos >> 5;
    gpio_enable_reg += reg_idx * 4;

    pos &= 0x1f;

    data = *((volatile UINT32 *)gpio_enable_reg);

    if (enable_flag)
        data |= (1 << pos);
    else
        data &= ~(1 << pos);

    *((volatile UINT32 *)gpio_enable_reg) = data;
}

static void gpio_enable_group(UINT32 grp_idx, UINT32 pos_mask, BOOL enable_flag)
{
    UINT32 gpio_enable_reg = GPIO_REG;
    UINT32 data;

    if (grp_idx >= 5)
        return;

    gpio_enable_reg += grp_idx * 4;

    data = *((volatile UINT32 *)gpio_enable_reg);

    if (enable_flag)
        data |= pos_mask;
    else
        data &= ~pos_mask;

    *((volatile UINT32 *)gpio_enable_reg) = data;
}


static void m3505_pin_mux_set(chip* thiz, pin_mux_info* pin_mux_info)
{
    UINT32 data;
    UINT32 pin_mux_sel = pin_mux_info->pin_mux_sel;
    UINT32 val = pin_mux_info->value;
    UINT32 pin_addr = PIM_MUX_BASE + ((pin_mux_sel & PIN_MUX_REG_MASK) >> PIN_MUX_REG_SHIFT);
    UINT32 bit_height = (pin_mux_sel & PIN_BIT_HEIGHT_MASK) >> PIN_BIT_HEIGHT_SHIFT;
    UINT32 bit_low = (pin_mux_sel & PIN_BIT_LOW_MASK) >> PIN_BIT_LOW_SHIFT;
    UINT32 i=0;

    if(bit_height==0x00)
    bit_height=bit_low;
    if(bit_low > bit_height)
    {
        data=bit_low;
        bit_low=bit_height;
        bit_height=data;
    }
    data = *(volatile UINT32 *)pin_addr;
    for(i=bit_low;i<=bit_height;i++)
    {
        data &= ~(1 << i);
        data |= (val << i);
    }
    *(volatile UINT32*)(pin_addr) = data;

#ifdef SMC2_SUPPORT
    //set SCR2 GPIO
    unsigned long scr2_gpio;
    if (!( ((*(volatile UINT32 *)0xb8000070) >>19) & 0x1))
        {
            scr2_gpio= *(volatile unsigned long*)(0xb8000430);//disable GPIO[10]~[14]
            *(volatile unsigned long*)(0xb8000430) = scr2_gpio &(~0x7C00);
        }
#endif
}


static void m3505_pin_mux_set_ext(chip* thiz, pin_mux_info pin_mux_info[], UINT8 count)
{
    UINT8 i;
    for(i=0; i<count; i++)
    {
         m3505_pin_mux_set(thiz, &pin_mux_info[i]);
    }
}


static void m3505_gpio_dir_set(chip* thiz, gpio_info_t* gpio_info)
{
    HAL_GPIO_BIT_DIR_SET(gpio_info->position, gpio_info->io);
}


static void m3505_gpio_dir_set_ext(chip* thiz, gpio_info_t gpio_info[], UINT8 count)
{
    UINT32 j;
    gpio_info_t* gpio = NULL;
    for(j=0; j<count; j++)
    {
         gpio = &gpio_info[j];
		 if(gpio->position < 0)
		 {
		 		;
		 }
		 else
		 	HAL_GPIO_BIT_DIR_SET(gpio->position, gpio->io);
    }
}

static void m3505_gpio_pin_init(chip* thiz, gpio_info_t* gpio_info, BOOL enabled)
{
     gpio_enable_pos(gpio_info->position, enabled);
     if(enabled)
        HAL_GPIO_BIT_DIR_SET(gpio_info->position, gpio_info->io);
}


static void m3505_gpio_pin_init_ext(chip* thiz,  gpio_info_t gpio_info[], UINT8 count)
{
    UINT32 reg_addr[] =
    {
         GPIO_REG, GPIOA_REG, GPIOB_REG, GPIOC_REG, GPIOD_REG,
    };
    UINT32 i, j;
    UINT32 value;
    gpio_info_t* gpio = NULL;

    // disable all GPIO
    for(i=0; i<ARRAY_SIZE(reg_addr); i++)
    {
        value = 0;
        for(j=0; j<count; j++)
        {
            gpio = &gpio_info[j];
			if(gpio->position < 0)
			{
				;
			}
			else
			{
            	if(gpio->position >= (i*32) && gpio->position < ((i+1)*32))
                	value |= 1 << (gpio->position - (i*32));
			}
        }
        *((volatile unsigned long *)reg_addr[i]) = value;
    }

    m3505_gpio_dir_set_ext(thiz, gpio_info, count);
}


static void m3505_gpio_set(chip* thiz, gpio_info_t* gpio_info, UINT8 value)
{
    UINT8 val;
    if(gpio_info->io != HAL_GPIO_O_DIR)
        return;
    val = gpio_info->polar ? value : !value;
    HAL_GPIO_BIT_SET(gpio_info->position, val);
}


static UINT32 m3505_gpio_get(chip* thiz, gpio_info_t* gpio_info)
{
    UINT32 val = HAL_GPIO_BIT_GET(gpio_info->position);
    return gpio_info->polar ? val : !val;
}


static void m3505_tsi_pin_cfg(chip* thiz, UINT8 tsi_id, BOOL clear)
{

    return;

    static UINT32 config_array[][2] =
    {
        {TSI_SPI_1, (1<<22)}, {TSI_SSI_0, (1<<23)},
        {TSI_SSI_1, (1<<24)}, {TSI_SSI2B_0, (1<<25)},
        {TSI_SSI2B_1, (1<<26)},
    };

    UINT32 i;
    UINT32 data = *((volatile unsigned long *)0xb8000088);

    if(clear)
        data &= 0xf83fffff;
    for(i=0; i<ARRAY_SIZE(config_array); i++)
    {
        if(tsi_id == config_array[i][0])
        {
            data |= config_array[i][1];
            *((volatile unsigned long *)0xb8000088) = data;
            break;
        }
    }
}


static void m3505_ci_power(chip* thiz, BOOL power_on)
{
    //chip_priv* priv = (chip_priv*)thiz->priv;
    //UINT32 data;

}

extern void phy_chip_setting(void);
static void phy_chip_enable()
{
    //unsigned long        chip_id;
    //unsigned long        chip_version;
    //unsigned long        temp;
#ifndef _BUILD_USB_LOADER_RET2GAC	
    phy_chip_setting();
#endif

#if 0    //waitting dbg!!!
    temp = (*(unsigned long*) 0xb8000000);
    chip_id = temp >> 16;
    chip_version = temp & 0xC00;
    if (chip_id == 0x3603)
    {
        // M3603 chip series
        // Config SOC pin mux registers to assign pin to phy
        temp = (*(unsigned long*) 0xb8000430);
        temp &= 0x01FFFFFF;
        *((volatile UINT32 *)0xb8000430) = temp;

        temp = (*(unsigned long*) 0xb8000434);
        temp &= 0xFFFFFFF0;
        *((volatile UINT32 *)0xb8000434) = temp;

#if 1
        //Select RMII Mode
        // NO.1 Select RMII Mode 0xb800006c Bit 31 0:MII 1:RMII
        *((volatile UINT32 *)0xb800006c) |= (1<<31);
        // NO.2 Select RMII Pins 0xb8000088 Bit 30 Function Select PIN296~PIN308 XRMII Interface 0:GPIO[] 1:RMII Select
        *((volatile UINT32 *)0xb8000088) |= (1<<30);
        // NO.3 Select RMII Pins 0xb8000088 Bit 31 Function 1: RMII Interupt
        *((volatile UINT32 *)0xb8000088) |= (1<<31);
        //NO.4 RMII Clock Select, 0xb800008c Bit 25  1:external clock, 0:PL clock
        //*((volatile UINT32 *)0xb800008c) |= 0x02000000;
        *((volatile UINT32 *)0xb800008c) &= 0xFDFFFFFF;
        //NO.4 Test Mux Select
        //*((volatile UINT32 *)0xb80000a8) |= 0x00000109;

#else
        //Select MII Mode for test
        //NO.1 MII Test Select 0xb800008c Bit 24 1:MII Select
        *((volatile UINT32 *)0xb800008c) |= 0x01000000;
        //NO.2 Test Mux Select
        *((volatile UINT32 *)0xb80000a8) |= 0x00000109;
        // NO.3 Select MII Mode 0xb800006c Bit 31 0:MII 1:RMII
        *((volatile UINT32 *)0xb800006c) &= 0x7FFFFFFF;
#endif
/*
        if (chip_version != 0xC00)
        {
            //We need Power off to reset phy
            // Change pad driving ability
            *((volatile UINT32 *)0xb8001288) |= 0x00044000;
            //Reset Phy for first use
            *((volatile UINT32 *)0xb80012a4) |= 0x40;
            *((volatile UINT32 *)0xb800043c) |= 0x40;
            *((volatile UINT32 *)0xb8000358) |= 0x40;

            *((volatile UINT32 *)0xb8000354) |= 0x40;
            osal_task_sleep(1000);
            *((volatile UINT32 *)0xb8000354) &= 0xFFFFFFBF;
            osal_task_sleep(100);
            //Other QFP
            // 256/216 pin MDIO Enable
            // *((volatile UINT32 *)0xb80012a4) = 0x0003ffff;
            // MDIO Test MUX Select
            // *((volatile UINT32 *)0xb80000a8) = 0x00002109;
        }
*/
    }
#endif
}

extern void nim_s3501_reset_tuner(void);
#ifdef DUAL_ENABLE

#if 0
#define MAX_SEE_LEN  1000000       //10M
static RET_CODE set_see_parameter(UINT32 run_addr, UINT32 code_addr,UINT32 len)
{
    *(volatile UINT32 *)(SEEROM_SEE_REAL_RUN_ADDR) = run_addr|0xa0000000 ;
    osal_cache_flush(code_addr,len);
    *(volatile UINT32 *)(SEEROM_SEE_CODE_LEN_ADDR) = len ;
    *(volatile UINT32 *)(SEEROM_SEE_CODE_LOCATION_ADDR) = code_addr|0xa0000000 ;
    return RET_SUCCESS;
}
#else
#define MAX_SEE_LEN  1000000       //10M
static RET_CODE set_see_parameter(UINT32 run_addr, UINT32 code_addr,UINT32 len)
{
	*(volatile UINT32 *)(SEEROM_SEE_REAL_RUN_ADDR) = run_addr|0xa0000000 ;
	osal_cache_flush((void *)code_addr,len);
    #ifndef _USE_64M_MEM_
      #ifdef _SUPPORT_256M_MEM
        *(volatile UINT32 *)(SEEROM_SEE_CODE_LEN_ADDR) = *(volatile UINT32 *)(0xaf0001f0) ;
        *(volatile UINT32 *)(SEEROM_SEE_CODE_LOCATION_ADDR) = code_addr|0xa0000000 ;      
    	*(volatile UINT32 *)(SEEROM_SEE_SIGN_LOCATION_ADDR) = 0xaf000200 ;
      #else
    	*(volatile UINT32 *)(SEEROM_SEE_CODE_LEN_ADDR) = *(volatile UINT32 *)(0xa70001f0) ;
        *(volatile UINT32 *)(SEEROM_SEE_CODE_LOCATION_ADDR) = code_addr|0xa0000000 ;      
    	*(volatile UINT32 *)(SEEROM_SEE_SIGN_LOCATION_ADDR) = 0xa7000200 ;
      #endif
    #else
    *(volatile UINT32 *)(SEEROM_SEE_CODE_LEN_ADDR) = *(volatile UINT32 *)(0xa3d001f0) ;
    *(volatile UINT32 *)(SEEROM_SEE_CODE_LOCATION_ADDR) = code_addr|0xa0000000 ;      
	*(volatile UINT32 *)(SEEROM_SEE_SIGN_LOCATION_ADDR) = 0xa3d00200 ;
    #endif
	
	return RET_SUCCESS;
}
#endif


#define IS_DOWNLOAD_DEBUG (((*(volatile UINT32 *)(0xb8000000+SYS_FIRST_BOOT_REG)&SYS_FIRST_BOOT_BIT)) == 0ul)
						   
static void see_boot(UINT32 addr)
{
    libc_printf("enter %s\n",__FUNCTION__);
    /*run from AS bl*/
    if(is_hw_ack_flag_true(SEE_ROM_RUN_BIT)){
          check_see_clock();
          return ;
      }

    if(*(volatile UINT32 *)(0xb8000200) != 0xb8000280)
    {
        //libc_printf("see_boot : return\n");
        return;
    }


    if( sys_ic_seerom_is_enabled())
    {
        *(volatile UINT32 *)(0xb8000220) &= ~(0x2);
		if(IS_DOWNLOAD_DEBUG)
		{
        	set_see_parameter(addr, addr,MAX_SEE_LEN);
		}
		*(volatile UINT32 *)(0xb8000220) |= 0x2;
        osal_task_sleep(400);
        *(volatile UINT32 *)(0xb8000200) = addr;
    }else{
		
		UINT32 i = 0;		
		*(volatile UINT32 *)(0xb8000220) &= ~(0x2); 
		addr = (addr & 0x0FFFFFFF) | 0xA0000000;		
		*(volatile UINT32 *)(0xb8000200) = addr; 
		
		while ( *(volatile UINT32 *)(0xb8000200) != addr )
			for(i=0;i<1000;i++);
        *(volatile UINT32 *)(0xb8000220) |= 0x2;
    }

    osal_task_sleep (1000);
    
    libc_printf("EXIT %s\n",__FUNCTION__);
}
#endif

static void m3505_init(chip* thiz, chip_init_param* param)
{
    //UINT32 data;
    chip_priv* priv = (chip_priv*)thiz->priv;

    
    if(sys_ic_get_chip_id() != ALI_C3505)
    {
       ASSERT(0);
    }
#if _CAS9_CA_ENABLE_//temp code for 3505 AS
	#ifndef SEE_PRINTF_ON
    UINT32 temp = (*(unsigned long*)0xb8042074);
    temp |= 0x10000;//bit 16
    *((volatile UINT32 *)0xb8042074) = temp;
	#endif
#endif

    MEMCPY(&priv->param, param, sizeof(chip_init_param));
#ifdef DUAL_ENABLE
    #ifdef _CAS9_VSC_ENABLE_
    see_boot(osal_dual_get_see_run_address() + __MM_VSC_TOTAL_LEN);
    #else
    see_boot(osal_dual_get_see_run_address());
	#endif
#else
    // b8000220, byte = 0, disable SEE
    *((volatile UINT8 *)0xb8000220) = 0;
#endif

#if 0
    data = *(UINT32 *)0xb8001010;
    data &= ~(1<<18);   // DE
    data &= ~(1<<19);   // DE
    data &= ~(1<<20);   // VE
    data &= ~(1<<21);   // VE
    //data &= ~(1<<27); // GE
    *(UINT32 *)0xb8001010 = data;
    *(UINT32 *)0xb8000004 = 1;

    data = *(UINT32 *)0xb8001024;
    data |= 0xffff;
    *(UINT32 *)0xb8001024 = data;

    data = *(UINT32 *)0xb8001020;
    data &= 0xffff;
    data |= 0x01080000;
    *(UINT32 *)0xb8001020 = data;

    //data = *(UINT32 *)0xb8001070;
    //data |= 0xff000000;
    //*(UINT32 *)0xb8001070 = data;
#endif

#if (SYS_PROJECT_FE == PROJECT_FE_DVBS || SYS_PROJECT_FE == PROJECT_FE_DVBS2)
    *(UINT32 *)0xb8000004 = 1;
#else
    *(UINT32 *)0xb8000004 = 0;
#endif

    //disabled all gpio
    *((unsigned long *)GPIO_REG) = 0;    // GPIO 0~31
    *((unsigned long *)GPIOA_REG) = 0;    // GPIO 32~63
    *((unsigned long *)GPIOB_REG) = 0;    // GPIO 64~95
    *((unsigned long *)GPIOC_REG) = 0;    // GPIO 96~127
    *((unsigned long *)GPIOD_REG) = 0;

    if(param->ali_ethmac_enabled)
        phy_chip_enable();

    // reset SCB 0/1/2
    *((unsigned long *)0xb8000080) = 0x00040000 | (1<<25) | (1<<26);
    osal_delay(100);
    // clear reset
    *((unsigned long *)0xb8000080) = 0x00000000;
}

static void m3505_destory(chip* thiz)
{
    return FREE(thiz);
}

chip* chip_create(void)
{
    chip* thiz = NULL;
    //chip_priv *priv = NULL;
    thiz = (chip*)MALLOC(sizeof(chip) + sizeof(chip_priv));
    if(NULL != thiz)
    {
        MEMSET(thiz, 0, sizeof(chip) + sizeof(chip_priv));
        thiz->init = m3505_init;
        thiz->destory = m3505_destory;
        thiz->gpio_dir_set = m3505_gpio_dir_set;
        thiz->gpio_dir_set_ext = m3505_gpio_dir_set_ext;
        thiz->gpio_pin_init = m3505_gpio_pin_init;
        thiz->gpio_pin_init_ext = m3505_gpio_pin_init_ext;
        thiz->gpio_set = m3505_gpio_set;
        thiz->pin_mux_set = m3505_pin_mux_set;
        thiz->pin_mux_set_ext = m3505_pin_mux_set_ext;
        thiz->tsi_pin_cfg = m3505_tsi_pin_cfg;
        thiz->ci_power = m3505_ci_power;
        thiz->gpio_get = m3505_gpio_get;
    }
    return thiz;
}


