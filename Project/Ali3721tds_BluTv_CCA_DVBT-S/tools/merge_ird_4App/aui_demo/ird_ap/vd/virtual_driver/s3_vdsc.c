/**@file
 *  (c) Copyright 2013-2999  ALi Corp. ZHA Linux SDK Team (alitech.com)
 *  All rights reserved
 *
 *  @file               Y:\Irdeto\ird_vd\virtual_driver\s3_vdsc.c
 *  @brief              
 *
 *  @version            1.0
 *  @date               7/26/2016 15:16:40
 *  @revision           none
 *
 *  @author              <>
 */


/**
 * This file is part of the 'smartcard virtual driver'.
 * It contains all definitions for the smartcard virtual driver.
 **/



#include <s3_portable_types.h>
#include <s3_vd.h>
#include <s3_vdsc.h>
#include <s3_osdrv.h>
#include <signal.h>
#include <time.h>
//#include <sys/time.h>
#include <stdlib.h>
#include <aui_common.h>
#include <aui_smc.h>
#include "ali_vd_drv.h"

#define SMC_V1 1
#define SMC_V2 2
#define SMC_V3 3
#define SMC_V4 4
#define SMC_V5 5

#define SMC_RES_NR 1

#ifdef BOARD_CFG_M3733
#define ID (1)
#else
#define ID (0)
#endif
#define IRD_T14_TX_ACK_RSP_EXP {0xff}
#define IRD_T14_TX_DAT_RSP_EXP {0xff, 0xff}
#define IRD_T14_RX_ACK_RSP_EXP {0xff}
#define IRD_T14_RX_DAT_RSP_EXP {0xff, 0xff}
#define IRD_T0_TX_ACK_RSP_EXP {0x04}
#define IRD_T0_TX_DAT_RSP_EXP {0x90, 0x19}
#define IRD_T0_RX_ACK_RSP_EXP {0xFE}
#define IRD_T0_RX_DAT_RSP_EXP {0x90, 0x00}

#define MAX_ATR_LN (33)
#define MAX_RESP_LEN (100)
typedef struct smc_ref{
	vd_rsc_id						rsc_id;
	vd_ref_id						ref_id;
	aui_hdl 						smc_hld;
	aui_smc_attr 					smc_attr;
	vd_sc_open_st					smc_st;
	unsigned char 					atr[MAX_ATR_LN];
	unsigned short 					atr_len;
	unsigned char					protocol;
	struct aui_list_head 			node;
} smc_ref;

static ia_word32 ref_cnt = 0;
static unsigned char t14_tx_ack_exp[] = IRD_T14_TX_ACK_RSP_EXP;
static unsigned char t14_tx_dat_exp[] = IRD_T14_TX_DAT_RSP_EXP;
static unsigned char t14_rx_ack_exp[] = IRD_T14_RX_ACK_RSP_EXP;
static unsigned char t14_rx_dat_exp[] = IRD_T14_RX_DAT_RSP_EXP;
static unsigned char t0_tx_ack_exp[]  = IRD_T0_TX_ACK_RSP_EXP;
static unsigned char t0_tx_dat_exp[]  = IRD_T0_TX_DAT_RSP_EXP;
static unsigned char t0_rx_ack_exp[]  = IRD_T0_RX_ACK_RSP_EXP;
static unsigned char t0_rx_dat_exp[]  = IRD_T0_RX_DAT_RSP_EXP;

static AUI_LIST_HEAD(smc_ref_head);                         
static ia_word16 vd_smc_get_drv_version();
static ia_result vd_smc_get_resources(void **ppvList, ia_word16 *pwCount);
static vd_ref_id vd_smc_open (vd_rsc_id wResourceID, void *pvData);
static ia_result vd_smc_close (vd_ref_id wRefId);
static ia_result vd_smc_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead);

static AUI_RTN_CODE *smc_init_cb(void *para);
static void fun_cb(int x, unsigned int status);

static ia_result vdsc_io_com(smc_ref *pref, ia_word32 wDataWriteSize, void *pin, ia_word32 *pwDataReadSize, vd_sc_read_error_st *pout);

static ia_result vdsc_io_reset(smc_ref *pref, vd_sc_reset_code_e *pin);

static ia_result vdsc_io_get_card_form(smc_ref *pref, ia_word32 *pwDataReadSize, vd_sc_get_card_form_st *pout);
static int checkseq(unsigned char *a, int a_len, unsigned char *b, int b_len);

static vd_drv vdsmc_drv = {
		.drv_typ 			= VD_DRIVER_SMARTCARD,
		.priv				= NULL,
		.get_drv_version 	= vd_smc_get_drv_version,
		.get_resources		= vd_smc_get_resources,
		.drv_open			= vd_smc_open,
		.drv_close			= vd_smc_close,
		.drv_ioctl			= vd_smc_ioctl,
		.destroy			= NULL,
};

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_word16 vd_smc_get_drv_version()
{
	ia_word16 ver = VD_NOT_IMPLEMENTED;

	ver = SMC_V5;
	return ver;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/7/2016, Created
 *
 *  @note
 */
static ia_result vd_smc_get_resources(void **ppvList, ia_word16 *pwCount)
{
	ia_result ret = IA_INVALID_PARAMETER;
	vd_rsc_id i = 0;
	vd_rsc_id *rsc_arr = NULL;
	
	*pwCount = SMC_RES_NR;
	rsc_arr = OS_DRV_AllocateMemory(sizeof(vd_rsc_id) * SMC_RES_NR);
	for(i = 0; i < SMC_RES_NR; i++)
	{
		rsc_arr[i] = i ;
	}
	*ppvList = rsc_arr;
	ret = IA_SUCCESS;
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static vd_ref_id vd_smc_open (vd_rsc_id wResourceID, void *pvData)
{
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	aui_hdl smc_hld = NULL;
	struct smc_ref *pref = NULL;
	vd_sc_open_st *smc_st = (vd_sc_open_st *) pvData;
	int scratch = 0;
	aui_smc_attr smc_attr;

	if((wResourceID >= SMC_RES_NR) || (NULL == pvData))
	{
		return VD_REF_ID_ERROR;
	}

	smc_attr.p_fn_smc_cb = fun_cb;
	smc_attr.ul_smc_id = ID;
	aui_rtn = aui_smc_init((p_fun_cb)smc_init_cb);
	if (aui_rtn != AUI_RTN_SUCCESS) 
	{
		DEBUG_S3_VD_PRINTF("aui_smc_init fail\n");
		return VD_REF_ID_ERROR;
	}
	aui_rtn = aui_smc_open(&smc_attr, &smc_hld);
	if (aui_rtn != AUI_RTN_SUCCESS) 
	{
		DEBUG_S3_VD_PRINTF("aui_smc_open fail\n");
		goto error;
	}
	aui_rtn = aui_smc_active(smc_hld);
	if (aui_rtn != AUI_RTN_SUCCESS) {
		DEBUG_S3_VD_PRINTF("aui_smc_active fail\n");
		goto error;
	}
	pref = OS_DRV_AllocateMemory(sizeof(struct smc_ref));
	if(NULL == pref)
	{
		DEBUG_S3_VD_PRINTF("No mem to alloc\n");
		aui_smc_close(smc_hld);
		return VD_REF_ID_ERROR;
	}
	pref->rsc_id = wResourceID;
	pref->smc_hld = smc_hld;
	ansi_memcpy(&pref->smc_attr, &smc_attr, sizeof(aui_smc_attr));
	ansi_memcpy(&pref->smc_st, smc_st, sizeof(vd_sc_open_st));
	pref->atr_len = 0;
	ansi_memset(pref->atr, 0x00, sizeof(pref->atr));
	pref->ref_id = ref_cnt++;
	aui_list_add_tail(&pref->node, &smc_ref_head);
	
	return pref->ref_id;
error:
	aui_smc_close(smc_hld);
	return VD_REF_ID_ERROR;
	
}
/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_result vd_smc_close (vd_ref_id wRefId)
{
	ia_result ret = IA_SUCCESS;
	struct smc_ref *pref = NULL;
	int find_flag = 0;
		
	aui_list_for_each_entry(pref, &smc_ref_head, node)
	{
		if(wRefId == pref->ref_id)
		{
			
			aui_list_del(&pref->node);
			find_flag = 1;
			break;
		}
	}
	if(0 == find_flag)
	{
		return IA_INVALID_PARAMETER;

	}
	aui_smc_close(pref->smc_hld);
	OS_DRV_FreeMemory(pref);
	pref = NULL;
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
static ia_result vd_smc_ioctl (vd_ref_id wRefId, ia_word16 wOpCode, 
		ia_word32 wDataWriteSize, void *pvDataWrite, 
		ia_word32 *pwDataReadSize, void *pvDataRead)
{
	ia_result ret = IA_SUCCESS;
	struct smc_ref *pref = NULL;
	int find_flag = 0;

	aui_list_for_each_entry(pref, &smc_ref_head, node)
	{
		if(wRefId == pref->ref_id)
		{
			find_flag = 1;
			break;
		}

	}
	if(0 == find_flag)
	{
		return IA_INVALID_PARAMETER;

	}
	switch(wOpCode)
	{
		case VD_SC_COMMUNICATE:
			ret = vdsc_io_com(pref, wDataWriteSize, pvDataWrite, pwDataReadSize, pvDataRead);
			break;
		case VD_SC_RESET:
			ret = vdsc_io_reset(pref, pvDataWrite);
			break;
		
		case VD_SC_SOFTCLIENT_EVENT:
			ret = IA_INVALID_PARAMETER;
			break;
		
		case VD_SC_GET_CARD_FORM:
			ret = vdsc_io_get_card_form(pref, pwDataReadSize, pvDataRead);
			break;
			
		default:
			ret = IA_INVALID_PARAMETER;
			break;
	}
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               7/29/2016, Created
 *
 *  @note
 */
ia_result init_s3_vd_smc()
{
	ia_result ret = IA_SUCCESS;

	/*here implement your own module init code*/
	
	ret = register_vd_drv(&vdsmc_drv);
	return ret;
}

static AUI_RTN_CODE *smc_init_cb(void *para)
{
	aui_smc_device_cfg_t *pconfig = (aui_smc_device_cfg_t *)para;

	DEBUG_S3_VD_PRINTF("M3529_01V01 running smc_init_cb\n");
	pconfig->init_clk_trigger = 1;
	pconfig->init_clk_number = 1;
	pconfig->apd_disable_trigger = 1;
	pconfig->def_etu_trigger = 1;
	pconfig->default_etu = 372;
	pconfig->warm_reset_trigger = 1;
	pconfig->init_clk_array[0] = 3600000;
	pconfig->invert_detect = 1;
	pconfig->force_tx_rx_trigger = 1;
	pconfig->force_tx_rx_cmd = 0xdd;
	pconfig->force_tx_rx_cmd_len = 5;
	return AUI_RTN_SUCCESS;
}

static void fun_cb(int x, unsigned int status)
{
	struct smc_ref *pref = NULL;
	int find_flag = 0;
	vd_sc_status_notify_fn ntf_cb = NULL;
	vd_sc_atr_st art_st;
	ia_byte *buf = NULL;
	void *dat_pos = NULL;

	DEBUG_S3_VD_PRINTF("smart card %d %s (status = %u)\n",
						x, status ? "detected" : "missing",  status);		
	aui_list_for_each_entry(pref, &smc_ref_head, node)
	{
		if(x == pref->smc_attr.ul_smc_id)
		{
			
			aui_list_del(&pref->node);
			find_flag = 1;
			break;
		}
	}
	if(0 == find_flag)
	{
		return ;

	}
	ntf_cb = pref->smc_st.pfnStatusNotify;
	if(NULL != ntf_cb)
	{
		switch(pref->protocol)
		{
			case 0:
				art_st.wAtrLength = 2;
				buf = OS_DRV_AllocateMemory(sizeof(vd_sc_atr_st) + (art_st.wAtrLength * sizeof(ia_byte)));
				dat_pos = buf;
				ansi_memcpy(dat_pos, &art_st, sizeof(vd_sc_atr_st));
				dat_pos += sizeof(vd_sc_atr_st);
				ansi_memcpy(dat_pos, t0_rx_dat_exp, art_st.wAtrLength * sizeof(ia_byte));
				break;

			case 14:
				art_st.wAtrLength = 9;
				buf = OS_DRV_AllocateMemory(sizeof(vd_sc_atr_st) + (art_st.wAtrLength * sizeof(ia_byte)));
				dat_pos = buf;
				ansi_memcpy(dat_pos, &art_st, sizeof(vd_sc_atr_st));
				dat_pos += sizeof(vd_sc_atr_st);
				ansi_memcpy(dat_pos, t14_rx_dat_exp, art_st.wAtrLength * sizeof(ia_byte));
				break;
			default:
				buf = NULL;
				break;
		}
		ntf_cb(pref->ref_id, pref->smc_st.wSoftCellVal, status ? VD_SC_CARD_IN : VD_SC_CARD_OUT, buf);
	}
}
/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/7/2016, Created
 *
 *  @note
 */
static ia_result vdsc_io_com(smc_ref *pref, ia_word32 wDataWriteSize, void *pin, ia_word32 *pwDataReadSize, vd_sc_read_error_st *pout)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;
	vd_sc_write_st com_st;
	void *dat_pos = NULL;
	ia_byte *abScHeader;
	ia_byte *abScPayload;
	unsigned char resp[MAX_RESP_LEN];
	int resp_len;
	
	if((NULL == pref) || (0 == wDataWriteSize) || (NULL == pin))
    {
		ret = IA_FAIL;
		return ret;
    }
    ansi_memcpy(&com_st, pin, sizeof(vd_sc_write_st));
    dat_pos = pin + sizeof(vd_sc_write_st);
    abScHeader = OS_DRV_AllocateMemory(com_st.bScHeaderLen * sizeof(ia_byte));
    abScPayload = OS_DRV_AllocateMemory(com_st.bScPayloadLen * sizeof(ia_byte));
    ansi_memset(abScHeader, 0x00, com_st.bScHeaderLen * sizeof(ia_byte));
    ansi_memset(abScPayload, 0x00, com_st.bScPayloadLen * sizeof(ia_byte));
	ansi_memcpy(abScHeader, dat_pos, com_st.bScHeaderLen * sizeof(ia_byte));
	dat_pos += com_st.bScHeaderLen;
	ansi_memcpy(abScPayload, dat_pos, com_st.bScPayloadLen * sizeof(ia_byte));
	aui_rtn = aui_smc_transfer(pref->smc_hld, abScHeader, 
								com_st.bScHeaderLen / sizeof(ia_byte),
								resp, &resp_len);
	if (aui_rtn != AUI_RTN_SUCCESS)
	{
		DEBUG_S3_VD_PRINTF("aui_smc_transfer FAIL %d\n", aui_rtn);
		pout->eError = VD_SC_TIME_OUT;
		goto error;
	}
	else
	{
		switch(pref->protocol)
		{
			case 0:
				if(0 != checkseq(resp, resp_len, t0_tx_ack_exp, sizeof(t0_tx_ack_exp)))
				{
					DEBUG_S3_VD_PRINTF("aui_smc_transfer FAIL %d\n", aui_rtn);
					pout->eError = VD_SC_COMM_ERROR;
					goto error;
				}

				break;
			case 14:
				if(0 != checkseq(resp, resp_len, t14_tx_ack_exp, sizeof(t14_tx_ack_exp)))
				{
					DEBUG_S3_VD_PRINTF("aui_smc_transfer FAIL %d\n", aui_rtn);
					pout->eError = VD_SC_COMM_ERROR;
					goto error;
				}
				break;

			default:
				pout->eError = VD_SC_COMM_ERROR;
				goto error;
				break;
		}
	}
	aui_rtn = aui_smc_transfer(pref->smc_hld, abScPayload, 
								com_st.bScPayloadLen / sizeof(ia_byte),
								resp, &resp_len);
	if (aui_rtn != AUI_RTN_SUCCESS)
	{
		DEBUG_S3_VD_PRINTF("aui_smc_transfer FAIL %d\n", aui_rtn);
		pout->eError = VD_SC_TIME_OUT;
		goto error;
	}
	else
	{
		switch(pref->protocol)
		{
			case 0:
				if(0 != checkseq(resp, resp_len, t0_tx_dat_exp, sizeof(t0_tx_dat_exp)))
				{
					DEBUG_S3_VD_PRINTF("aui_smc_transfer FAIL %d\n", aui_rtn);
					pout->eError = VD_SC_COMM_ERROR;
					goto error;
				}
				break;
				
			case 14:
				if(0 != checkseq(resp, resp_len, t14_tx_dat_exp, sizeof(t14_tx_dat_exp)))
				{
					DEBUG_S3_VD_PRINTF("aui_smc_transfer FAIL %d\n", aui_rtn);
					pout->eError = VD_SC_COMM_ERROR;
					goto error;
				}
				break;

			default:
				goto error;
				pout->eError = VD_SC_COMM_ERROR;
				break;
		}
	}
	*pwDataReadSize = 0;
	ret = IA_SUCCESS;
	return ret;
error:
	*pwDataReadSize = sizeof(vd_sc_read_error_st);
	aui_smc_close(pref->smc_hld);
	ret = IA_FAIL;
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/7/2016, Created
 *
 *  @note
 */
static ia_result vdsc_io_reset(smc_ref *pref, vd_sc_reset_code_e *pin)
{
	ia_result ret = IA_SUCCESS;
	AUI_RTN_CODE aui_rtn = AUI_RTN_SUCCESS;

	if((NULL == pref) || (NULL == pin))
	{
		ret = IA_FAIL;
		return ret;
	}
	aui_rtn = aui_smc_reset(pref->smc_hld, pref->atr, &pref->atr_len, 0);	
	if (aui_rtn != AUI_RTN_SUCCESS) 
	{
		DEBUG_S3_VD_PRINTF("aui_smc_reset fail\n");
		goto error;
	}
	if(pref->atr_len > 3)
	{
		pref->protocol = pref->atr[3] & 0x0F;
	}
	else
	{
		pref->protocol = 0;
	}
	OS_DRV_DelayTask(100);
	aui_rtn = aui_smc_isexist(pref->smc_hld);
	if (aui_rtn != AUI_RTN_SUCCESS) 
	{
		DEBUG_S3_VD_PRINTF("aui_smc_isexist fail.\n");
		goto error;
	}
	aui_rtn = aui_smc_detect(pref->smc_hld);
	DEBUG_S3_VD_PRINTF("detect status = %i\n", aui_rtn);
	if (aui_rtn != AUISMC_ERROR_READY) {
		DEBUG_S3_VD_PRINTF("aui_smc_detect fail\n");
		goto error;
	}
	ret = IA_SUCCESS;
	return ret;
error:
	aui_smc_close(pref->smc_hld);
	ret = IA_FAIL;
	return ret;
}

/**
 *  Function Name:      
 *  @brief              
 *
 *  @param
 *  @param
 *
 *  @return
 *
 *  @author              <>
 *  @date               9/7/2016, Created
 *
 *  @note
 */
static ia_result vdsc_io_get_card_form(smc_ref *pref, ia_word32 *pwDataReadSize, vd_sc_get_card_form_st *pout)
{
	ia_result ret = IA_SUCCESS;

	if((NULL == pwDataReadSize) || (NULL == pwDataReadSize))
	{
		ret = IA_FAIL;
		return ret;
	}
	*pwDataReadSize = sizeof(vd_sc_get_card_form_st);
	pout->eScForm = VD_SC_CARD_FORM_NORMAL;
	return ret;
}

static int checkseq(unsigned char *a, int a_len, unsigned char *b, int b_len)
{
	int i = 0;;

	if(a_len != b_len)
		return -1;
	for (i = 0; i < a_len; i++)
		if (a[i] != b[i])
			return -1;
	return 0;
}

