#include "chip_m3702.h"
#include "../chip.h"
#include <hld/sec_boot/sec_boot.h>
/***********************************************************************************************************/

typedef struct
{
	chip_init_param param;
}chip_priv;

extern void check_see_clock(void);
/***********************************************************************************************************/

static void m3702_pin_mux_set(chip* thiz, pin_mux_info* pin_mux_info)
{
	/*Add for show panel.
	**If you want to show panel, you need to set XGPIO_TB_1_PINSEL and
	**XGPIO_TB_2_PINSEL as gpio function.
	*/
	PMX_PIN_SEL(PMX_GPIO_TB_BASE, 0, PMX_PIN_SEL_GPIO);
	PMX_PIN_SEL(PMX_GPIO_TB_BASE, 1, PMX_PIN_SEL_GPIO);
}

static void m3702_pin_mux_set_ext(chip* thiz, pin_mux_info pin_mux_info[], UINT8 count)
{
    UINT8 i;
    for(i=0; i<count; i++)
    {
         m3702_pin_mux_set(thiz, &pin_mux_info[i]);
    }
}

static void m3702_gpio_dir_set(chip* thiz, gpio_info_t* gpio_info)
{
	HAL_GPIO_BIT_DIR_SET(gpio_info->position, gpio_info->io);
}

static void m3702_gpio_dir_set_ext(chip* thiz, gpio_info_t gpio_info[], UINT8 count)
{
	UINT32 j = 0;

	gpio_info_t* gpio = NULL;
	for(j=0; j<count; j++)
	{
		gpio = &gpio_info[j];
		if(gpio->position < 0)
		{
			;
		}
		else
		{
			HAL_GPIO_BIT_DIR_SET(gpio->position, gpio->io);
		}
	}
}

static void m3702_gpio_pin_init(chip* thiz, gpio_info_t* gpio_info, BOOL enabled)
{
	if(enabled)
		HAL_GPIO_BIT_DIR_SET(gpio_info->position, gpio_info->io);
}

static void m3702_gpio_pin_init_ext(chip* thiz,  gpio_info_t gpio_info[], UINT8 count)
{
	m3702_gpio_dir_set_ext(thiz, gpio_info, count);
}

static void m3702_gpio_set(chip* thiz, gpio_info_t* gpio_info, UINT8 value)
{
	UINT8 temp_val;

	if(gpio_info->io != HAL_GPIO_O_DIR)
		return;
	temp_val = (gpio_info->polar) ? value : (!value);
	HAL_GPIO_BIT_SET(gpio_info->position, temp_val);
}

static UINT32 m3702_gpio_get(chip* thiz, gpio_info_t* gpio_info)
{
	UINT32 val = HAL_GPIO_BIT_GET(gpio_info->position);
	return gpio_info->polar ? val : !val;
}

static void m3702_tsi_pin_cfg(chip* thiz, UINT8 tsi_id, BOOL clear)
{
	return;
}

static void m3702_ci_power(chip* thiz, BOOL power_on)
{
}

static void phy_chip_enable(void)
{
}

#ifdef DUAL_ENABLE			   
static void see_boot(UINT32 addr)
{
	UINT32 i = 0;

	if(sys_ic_get_chip_id() == ALI_C3702)
	{
		/*3702 boot see test code.*/
		addr = (addr & 0x0FFFFFFF) | 0xA0000000;		
		if(*(volatile UINT32 *)(0xb8087030) != 0xb8087020)
		return;

		*(volatile UINT32 *)(0xb8082440) &= ~0x1;
		*(volatile UINT32 *)(0xb8087030) = addr;
		for(i=0;i<900000;i++){
		;
		}
		*(volatile UINT32 *)(0xb8082440) |= 0x1; 
		return;
	}

	/*run from AS bl.*/
	if(is_hw_ack_flag_true(SEE_ROM_RUN_BIT)){
		check_see_clock();
		return ;
	}

	osal_task_sleep (1000);
}
#endif

static void m3702_init(chip* thiz, chip_init_param* param)
{
	chip_priv* priv = (chip_priv*)thiz->priv;

	if(sys_ic_get_chip_id() != ALI_C3702)
	{
		ASSERT(0);
	}

#if _CAS9_CA_ENABLE_//temp code for 3702 AS
	#ifndef SEE_PRINTF_ON
	UINT32 temp = (*(unsigned long*)0xb8042074);
	temp |= 0x10000;//bit 16
	*((volatile UINT32 *)0xb8042074) = temp;
	#endif
#endif

	MEMCPY(&priv->param, param, sizeof(chip_init_param));
#ifdef DUAL_ENABLE
	#if(defined _CAS9_VSC_ENABLE_ || defined _C0700A_VSC_ENABLE_)
	see_boot(osal_dual_get_see_run_address() + __MM_VSC_TOTAL_LEN);
	#else
	see_boot(osal_dual_get_see_run_address());
	#endif
#endif

	if(param->ali_ethmac_enabled)
		phy_chip_enable();
}

static void m3702_destory(chip* thiz)
{
	return FREE(thiz);
}

chip* chip_create(void)
{
	chip* thiz = NULL;

	thiz = (chip*)MALLOC(sizeof(chip) + sizeof(chip_priv));
	if(NULL != thiz)
	{
		MEMSET(thiz, 0, sizeof(chip) + sizeof(chip_priv));
		thiz->init = m3702_init;
		thiz->destory = m3702_destory;
		thiz->gpio_dir_set = m3702_gpio_dir_set;
		thiz->gpio_dir_set_ext = m3702_gpio_dir_set_ext;
		thiz->gpio_pin_init = m3702_gpio_pin_init;
		thiz->gpio_pin_init_ext = m3702_gpio_pin_init_ext;
		thiz->gpio_set = m3702_gpio_set;
		thiz->pin_mux_set = m3702_pin_mux_set;
		thiz->pin_mux_set_ext = m3702_pin_mux_set_ext;
		thiz->tsi_pin_cfg = m3702_tsi_pin_cfg;
		thiz->ci_power = m3702_ci_power;
		thiz->gpio_get = m3702_gpio_get;
	}

	return thiz;
}

