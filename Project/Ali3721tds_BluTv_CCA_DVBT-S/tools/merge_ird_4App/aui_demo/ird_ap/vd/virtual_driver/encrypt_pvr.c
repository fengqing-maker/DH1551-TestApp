#ifdef linux
#define LINUX_MUXTE
#else
#endif

#include <stdio.h>
#include <stdlib.h>

#ifdef LINUX_MUXTE
#include <pthread.h>
#else
#endif

#include "aui_common.h"
#include "aui_dmx.h"
#include "aui_kl.h"
#include "aui_dsc.h"
#include "aui_otp.h"
#include "aui_pvr.h"

#include "encrypt_pvr.h"


#define INVALID_FD       (-1)
#define INVALID_DEV_IDX       (-1)
#define GEN_CA_TS_PACKAGE_SIZE           	188 //bytes
#define INVALID_PID     0x1fff	//refer to hld


#define PVR_ENC_ERR(...) do{printf("ERROR: %s, %d, %s\r\n", __FILE__, __LINE__, __func__); printf(__VA_ARGS__);}while(0)
#define PVR_ENC_WARN(...) do{printf("WARN: %s, %d, %s\r\n", __FILE__, __LINE__, __func__); printf(__VA_ARGS__);}while(0)


struct pvr_encrypt_status
{
	
#ifdef LINUX_MUXTE
	pthread_mutex_t mutex;
#else
	//ID mutex;
#endif
	
	int is_working;
	
	int is_encrypt;

	int is_key_valid;
	struct pvr_crypto_key key;

	aui_hdl h_dsc;
	int dsc_dev_idx;
	int enable_close_dsc;

	aui_hdl h_kl;
	int kl_dev_idx;
	int enable_close_kl;

	aui_hdl h_dmx;
	int dmx_dev_idx;

	int pid_count;
	unsigned short int* p_pids;
};

#define PVR_ENCRYPT_MAX_COUNT 1
static struct pvr_encrypt_status g_pvr_encrypt_status[PVR_ENCRYPT_MAX_COUNT];
static int g_is_pvr_encrypt_status_inited = false;

static unsigned char g_default_iv[32 * 2] =
{
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};


static void init_pvr_encrypt_status(struct pvr_encrypt_status* p_status)
{
	memset(p_status, 0, sizeof(*p_status));
	
	p_status->dsc_dev_idx = INVALID_DEV_IDX;
	p_status->kl_dev_idx = INVALID_DEV_IDX;
	p_status->dmx_dev_idx = INVALID_DEV_IDX;	

	//p_status->pvr_de_enconfig.decrypt_fd = INVALID_FD;
	//p_status->pvr_de_enconfig.encrypt_fd = INVALID_FD;
	
	p_status->key.kl_level = 0;

	p_status->enable_close_dsc = false;
	p_status->enable_close_kl = false;
	//p_status->enable_kl = false;
	
	p_status->is_working = false;
	p_status->is_encrypt = false;
	p_status->is_key_valid = false;
	
}



static int init_pvr_encrypt_status_lock(struct pvr_encrypt_status* p_status)
{
#ifdef LINUX_MUXTE
	int ret = pthread_mutex_init(&p_status->mutex, NULL);
	if (0 != ret)
	{
		PVR_ENC_ERR("pthread_mutex_init fail %d.\n", ret);
		return false;
	}

	return true;
#else
//p_status->mutex = osal_mutex_create();
//if (OSAL_INVALID_ID == p_status->mutex)
//{
//	PVR_ENC_ERR("osal_mutex_create fail(%p).\n", p_status);
//	return false;
//}
#endif

}

static void close_pvr_encrypt_status_lock(struct pvr_encrypt_status* p_status)
{
#ifdef LINUX_MUXTE
		int ret = pthread_mutex_destroy(&p_status->mutex);
		if (0 != ret)
		{
			PVR_ENC_ERR("pthread_mutex_destroy fail %d.\n", ret);
		}
#else
	//osal_mutex_delete(p_status->mutex);
	//p_status->mutex = OSAL_INVALID_ID;
#endif

}

static inline int lock(struct pvr_encrypt_status* p_status)
{
#ifdef LINUX_MUXTE
	//int pthread_mutex_trylock(pthread_mutex_t *mutex)
	int ret = pthread_mutex_lock(&p_status->mutex);
	if (0 != ret)
	{
		PVR_ENC_ERR("pthread_mutex_lock fail %d.\n", ret);
		return false;
	}

	return true;
#else
//ER ret = osal_mutex_lock(p_status->mutex, TMO_FEVR);
//if (E_OK != ret)
//{
//	PVR_ENC_ERR("osal_mutex_lock fail %d(%p).\n", ret, p_status);
//	return false;
//}
//return true;
#endif
}

static inline void unlock(struct pvr_encrypt_status* p_status)
{
#ifdef LINUX_MUXTE
	int ret = pthread_mutex_unlock(&p_status->mutex);
	if (0 != ret)
	{
		PVR_ENC_ERR("pthread_mutex_unlock fail %d.\n", ret);
	}
#else
	//osal_mutex_unlock(p_status->mutex);
#endif
}


static int init_pvr_encrypt_status_array()
{
	int i = 0;

	for (i = 0; i < PVR_ENCRYPT_MAX_COUNT; i++)
	{
		init_pvr_encrypt_status(&g_pvr_encrypt_status[i]);
	}

	for (i = 0; i < PVR_ENCRYPT_MAX_COUNT; i++)
	{
		if (true != init_pvr_encrypt_status_lock(&g_pvr_encrypt_status[i]))
		{
			goto init_pvr_encrypt_status_array_fail;
		}
	}

	return true;

init_pvr_encrypt_status_array_fail:
	for (i = 0; i < PVR_ENCRYPT_MAX_COUNT; i++)
	{
		close_pvr_encrypt_status_lock(&g_pvr_encrypt_status[i]);
	}
	
	return false;
}






static void clr_pvr_crypto_key(struct pvr_crypto_key* p_key)
{
	if (NULL != p_key->p_key)
	{
		free(p_key->p_key);
		p_key->p_key = NULL;
	}	
	
	if (NULL != p_key->p_iv)
	{
		free(p_key->p_iv);
		p_key->p_iv = NULL;
	}	

	memset(p_key, 0, sizeof(*p_key));
}


static void clr_pvr_encrypt_status(struct pvr_encrypt_status* p_status)
{
	if (NULL == p_status)
	{
		PVR_ENC_ERR("p_status NULL.\n");
		return;
	}

	if (NULL != p_status->p_pids)
	{
		free(p_status->p_pids);
		p_status->p_pids = NULL;
	}

	clr_pvr_crypto_key(&p_status->key);

	init_pvr_encrypt_status(p_status);
	
}


static struct pvr_encrypt_status* get_pvr_encrypt_status(int is_new)
{
	UNUSED(is_new);
	
	return &g_pvr_encrypt_status[0];
}


static int verify_pvr_crypto_key(const struct pvr_crypto_key* p_key)
{
	if (NULL == p_key)
	{
		PVR_ENC_ERR("p_key NULL.\n");
		return false;
	}

	if (!(0 <= p_key->kl_level && p_key->kl_level <= 5))
	{
		PVR_ENC_ERR("p_key->kl_level %d.\n", p_key->kl_level);
		return false;
	}

	if (PVR_KEY_PARITY_UNDEF != p_key->e_parity
		&& PVR_KEY_PARITY_EVEN != p_key->e_parity
		&& PVR_KEY_PARITY_ODD != p_key->e_parity
		&& PVR_KEY_PARITY_AUTO != p_key->e_parity)
	{
		PVR_ENC_ERR("p_key->e_parity %d.\n", p_key->e_parity);
		return false;
	}

	if (PVR_KEY_ALGO_AES != p_key->e_algo
		&& PVR_KEY_ALGO_DES != p_key->e_algo
		&& PVR_KEY_ALGO_TDES != p_key->e_algo)
	{
		PVR_ENC_ERR("p_key->e_algo %d.\n", p_key->e_algo);
		return false;
	}

	if (PVR_KEY_MODE_ECB != p_key->e_mode
		&& PVR_KEY_MODE_CBC != p_key->e_mode
		&& PVR_KEY_MODE_OFB != p_key->e_mode
		&& PVR_KEY_MODE_CFB != p_key->e_mode
		&& PVR_KEY_MODE_CTR != p_key->e_mode)
	{
		PVR_ENC_ERR("p_key->e_mode %d.\n", p_key->e_mode);
		return false;
	}

	if (8 != p_key->key_length
		&& 16 != p_key->key_length
		&& 24 != p_key->key_length
		&& 32 != p_key->key_length)
	{
		PVR_ENC_ERR("p_key->key_length %d.\n", p_key->key_length);
		return false;
	}

	return true;
}




static int save_pvr_crypto_key(struct pvr_crypto_key* p_dst_key, const struct pvr_crypto_key* p_key)
{
	int mem_size = 0;
	
	memcpy(p_dst_key, p_key, sizeof(*p_dst_key));
	p_dst_key->p_iv = NULL;
	p_dst_key->p_key = NULL;

	if (p_key->key_length <= 0)
	{
		PVR_ENC_ERR("p_key->key_length %d.\n", p_key->key_length);
		return false;
	}

	if (PVR_KEY_PARITY_AUTO == p_key->e_parity)
	{
		mem_size = p_key->key_length * 2;
	}
	else
	{
		mem_size = p_key->key_length;
	}
	
	if (NULL != p_key->p_iv)
	{
		p_dst_key->p_iv = malloc(mem_size);
		if (NULL == p_dst_key->p_iv)
		{
			PVR_ENC_ERR("p_dst_key->p_iv NULL.\n");
			goto save_pvr_crypto_key_fail;
		}
		
		memcpy(p_dst_key->p_iv, p_key->p_iv, mem_size);
	}

	if (NULL != p_key->p_key)
	{
		p_dst_key->p_key = malloc(mem_size);
		if (NULL == p_dst_key->p_key)
		{
			PVR_ENC_ERR("p_dst_key->p_key NULL.\n");
			goto save_pvr_crypto_key_fail;
		}
		
		memcpy(p_dst_key->p_key, p_key->p_key, mem_size);
	}

	return true;

save_pvr_crypto_key_fail:
	clr_pvr_crypto_key(p_dst_key);

	return false;
}

static int get_dsc_dev_index()
{
	return 0;
}

static int get_kl_dev_index()
{
	return 0;
}

static aui_kl_output_key_pattern single_pattern_pvr2kl(int length)
{
	if (8 == length)
	{
		return AUI_KL_OUTPUT_KEY_PATTERN_64_SINGLE;
	}
	else if(16 == length)
	{
		return AUI_KL_OUTPUT_KEY_PATTERN_128_SINGLE;
	}
	else
	{
		PVR_ENC_ERR("length %d\n", length);
		return AUI_KL_OUTPUT_KEY_PATTERN_NB;
	}
}

static aui_kl_output_key_pattern odd_even_pattern_pvr2kl(int length)
{
	if (8 == length)
	{
		return AUI_KL_OUTPUT_KEY_PATTERN_64_ODD_EVEN;
	}
	else if(16 == length)
	{
		return AUI_KL_OUTPUT_KEY_PATTERN_128_ODD_EVEN;
	}
	else
	{
		PVR_ENC_ERR("length %d\n", length);
		return AUI_KL_OUTPUT_KEY_PATTERN_NB;
	}
}

static aui_kl_output_key_pattern pattern_pvr2kl(const struct pvr_crypto_key* p_key)
{
	switch (p_key->e_parity)
	{
		case PVR_KEY_PARITY_EVEN:
		case PVR_KEY_PARITY_ODD:
			return single_pattern_pvr2kl(p_key->key_length);
			break;

		case PVR_KEY_PARITY_AUTO:
			return odd_even_pattern_pvr2kl(p_key->key_length);
			break;

		default:
			PVR_ENC_ERR("p_key->e_parity %d\n", p_key->e_parity);
			return AUI_KL_OUTPUT_KEY_PATTERN_NB;
	}

}

static unsigned long int get_dev_index(aui_hdl h_dev)
{
	UNUSED(h_dev);
	//aui_dev_priv_data *data = (aui_dev_priv_data *)h_dev;

	//return data->dev_idx;
	return -1;
}


#define KL_LEVEL_OTP_ADDR (0x3 * 4)
static aui_kl_crypt_key_level get_kl_enable_levl()
{
	unsigned int data;
	AUI_RTN_CODE ret = aui_otp_read(KL_LEVEL_OTP_ADDR, (unsigned char*)&data, sizeof(data));

	if (AUI_RTN_SUCCESS != ret)
	{
		PVR_ENC_ERR("aui_otp_read error %ld\n", ret);
		return AUI_KL_KEY_LEVEL_NB;
	}

	PVR_ENC_ERR("get_kl_enable_levl data 0x%04x\n", data);
	//[16:15]
	//0x: 1-level mode
	//10: 2-level mode
	//11: 3-level mode
	data >>= 15;
	data &= 0x03;
	PVR_ENC_ERR("get_kl_enable_levl data 0x%04x\n", data);
	if (0 == (data & 0x02))
	{
		return AUI_KL_KEY_ONE_LEVEL;
	}
	else if(0x02 == data)
	{
		return AUI_KL_KEY_TWO_LEVEL;
	}
	else //if(0x03 == data)
	{
		return AUI_KL_KEY_THREE_LEVEL;
	}
}


static aui_hdl open_kl_dev(struct pvr_encrypt_status* p_status)
{
	AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;
	struct aui_attr_kl kl_attr;
	memset(&kl_attr, 0, sizeof(kl_attr));
	
	struct pvr_crypto_key* p_key = &p_status->key;
	aui_hdl h_kl = NULL;
	
	kl_attr.uc_dev_idx = get_kl_dev_index();
	kl_attr.en_key_pattern = pattern_pvr2kl(p_key);
	kl_attr.en_level = get_kl_enable_levl();	//AUI_KL_KEY_THREE_LEVEL;
	kl_attr.en_root_key_idx = AUI_KL_ROOT_KEY_0_0;
	aui_ret = aui_kl_open(&kl_attr, &h_kl);
	if (AUI_RTN_SUCCESS != aui_ret) {
		PVR_ENC_ERR("aui_kl_open error %ld\n", aui_ret);
		return NULL;
	}
	p_status->h_kl = h_kl;
	p_status->kl_dev_idx = kl_attr.uc_dev_idx;
	p_status->enable_close_kl = true;

	return h_kl;
}

static aui_dsc_algo algo_pvr2dsc(enum pvr_key_algo e_algo)
{
	switch (e_algo)
	{
		case PVR_KEY_ALGO_AES:
			return AUI_DSC_ALGO_AES;
			break;

		case PVR_KEY_ALGO_DES:
			return AUI_DSC_ALGO_DES;
			break;

		case PVR_KEY_ALGO_TDES:
			return AUI_DSC_ALGO_TDES;
			break;

		default:
			PVR_ENC_WARN("e_algo %d\r\n", e_algo);
			return AUI_DSC_ALGO_NB;
	}
}

static aui_hdl open_dsc_dev(struct pvr_encrypt_status* p_status)
{
	AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;
	struct pvr_crypto_key* p_key = &p_status->key;
	aui_hdl h_dsc = NULL;

	aui_attr_dsc dsc_attr;
	memset(&dsc_attr, 0, sizeof(dsc_attr));
	
	dsc_attr.uc_dev_idx = get_dsc_dev_index();
	dsc_attr.uc_algo = algo_pvr2dsc(p_key->e_algo);
	dsc_attr.dsc_data_type = AUI_DSC_DATA_TS;

	aui_ret = aui_dsc_open(&dsc_attr, &h_dsc);
	if (AUI_RTN_SUCCESS != aui_ret)
	{
		PVR_ENC_ERR("aui_dsc_open failed %ld\n", aui_ret);
		return NULL;
	}
	p_status->h_dsc = h_dsc;
	p_status->dsc_dev_idx = dsc_attr.uc_dev_idx;
	p_status->enable_close_dsc = true;

	return h_dsc;

}

static int enable_kl(const struct pvr_encrypt_status* p_status)
{
	return (p_status->key.kl_level > 0) ? true : false;
}

static void close_pvr_encrypt(struct pvr_encrypt_status* p_status)
{
	AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;

	if (true == p_status->enable_close_dsc)
	{
		if (NULL != p_status->h_dsc)
		{
			aui_ret = aui_dsc_close(p_status->h_dsc);
			if (AUI_RTN_SUCCESS != aui_ret)
			{
				PVR_ENC_ERR("aui_dsc_close failed %ld\n", aui_ret);
			}
		}
	}
	p_status->h_dsc = NULL;
	p_status->dsc_dev_idx = INVALID_DEV_IDX;
	p_status->enable_close_dsc = false;


	if (true == p_status->enable_close_kl)
	{
		if (NULL != p_status->h_kl)
		{
			aui_ret = aui_kl_close(p_status->h_kl);
			if (AUI_RTN_SUCCESS != aui_ret)
			{
				PVR_ENC_ERR("aui_kl_close failed %ld\n", aui_ret);
			}
		}	
	}
	p_status->h_kl = NULL;
	p_status->kl_dev_idx = INVALID_DEV_IDX;
	p_status->enable_close_kl = false;

	clr_pvr_encrypt_status(p_status);
}


static AUI_RTN_CODE open_encrypt_dev(struct pvr_encrypt_status* p_status, struct pvr_set_crypto_key_hd* p_key_hd)
{
	if (NULL == p_key_hd)
	{
		return AUI_RTN_SUCCESS;
	}

	if (true == enable_kl(p_status))
	{
		if (NULL == p_key_hd->h_kl)
		{
			p_key_hd->h_kl = open_kl_dev(p_status);
			if (NULL == p_key_hd->h_kl)
			{
				PVR_ENC_ERR("p_key->h_kl NULL.\n");
				return AUI_RTN_FAIL;
			}
		}
		else
		{
			p_status->h_kl = p_key_hd->h_kl;
			p_status->kl_dev_idx = get_dev_index(p_status->h_kl);
			p_status->enable_close_kl= false;
		}
	}
	else
	{
		p_key_hd->h_kl = NULL;
	}


	if (NULL == p_key_hd->h_dsc)
	{
		p_key_hd->h_dsc = open_dsc_dev(p_status);
		if (NULL == p_key_hd->h_dsc)
		{
			PVR_ENC_ERR("p_key_hd->h_dsc NULL.\n");
			return AUI_RTN_FAIL;
		}
	}
	else
	{
		p_status->h_dsc = p_key_hd->h_dsc;
		p_status->dsc_dev_idx = get_dev_index(p_status->h_dsc);
		p_status->enable_close_dsc= false;
	}

	if (NULL != p_key_hd->h_dmx)
	{
		p_status->h_dmx = p_key_hd->h_dmx;
		p_status->dmx_dev_idx = get_dev_index(p_status->h_dmx);
	}
	
	return AUI_RTN_SUCCESS;
}


static int save_pid(struct pvr_encrypt_status* p_status, unsigned short int* p_pids, int count)
{
	int size = 0;
	
	if (count <= 0)
	{
		PVR_ENC_ERR("count %d\n", count);
		return false;
	}

	if (NULL == p_pids)
	{
		PVR_ENC_ERR("p_pids NULL\n");
		return false;
	}

	if (NULL != p_status->p_pids)
	{
		PVR_ENC_ERR("p_status->p_pids %p\n", p_status->p_pids);
		return false;
	}

	size = sizeof(*(p_status->p_pids)) * count;
	p_status->p_pids = malloc(size);
	if (NULL == p_status->p_pids)
	{
		PVR_ENC_ERR("p_status->p_pids %p\n", p_status->p_pids);
		return false;
	}

	
	memcpy(p_status->p_pids, p_pids, size);
	p_status->pid_count = count;

	return true;

}


static int verify_pids(struct pvr_encrypt_status* p_status, unsigned short int* p_pids, int count)
{
	if (count != p_status->pid_count)
	{
		PVR_ENC_ERR("count %d != %d\n", count, p_status->pid_count);
		return false;
	}

	if (NULL == p_pids)
	{
		PVR_ENC_ERR("p_pids NULL\n");
		return false;
	}

	if (NULL == p_status->p_pids)
	{
		PVR_ENC_ERR("p_status->p_pids NULL\n");
		return false;
	}

	if (0 != memcmp(p_pids, p_status->p_pids, sizeof(*p_pids) * count))
	{
		PVR_ENC_ERR("memcmp p_pids error\n");
		return false;
	}

	return true;
}


static AUI_RTN_CODE init_pvr_crypto_key(struct pvr_encrypt_status* p_status, const struct pvr_crypto_key* p_key,
	struct pvr_set_crypto_key_hd* p_key_hd, struct pvr_crypto_pids* p_pids)
{
	AUI_RTN_CODE ret = AUI_RTN_SUCCESS;
		
	if (true != verify_pvr_crypto_key(p_key))
	{
		PVR_ENC_ERR("p_key->key_length %d.\n", p_key->key_length);
		goto init_pvr_crypto_key_fail;
	}

	clr_pvr_encrypt_status(p_status);

	if (true != save_pvr_crypto_key(&p_status->key, p_key))
	{
		clr_pvr_encrypt_status(p_status);

		PVR_ENC_ERR("save_pvr_crypto_key fail.\n");
		goto init_pvr_crypto_key_fail;
	}
	p_status->is_key_valid = true;

	if (NULL != p_pids)
	{
		if (true != save_pid(p_status, p_pids->p_pids, p_pids->count))
		{
			PVR_ENC_ERR("save_pid fail.\n");
			goto init_pvr_crypto_key_fail;
		}
	}
	
	ret = open_encrypt_dev(p_status, p_key_hd);
	if (AUI_RTN_SUCCESS != ret)
	{
		PVR_ENC_ERR("open_encrypt_dev fail %ld.\n", ret);
		goto init_pvr_crypto_key_fail;
	}

	return AUI_RTN_SUCCESS;
	
init_pvr_crypto_key_fail:
	close_pvr_encrypt(p_status);

	return AUI_RTN_FAIL;
}


static int enable_change_pvr_key(const struct pvr_crypto_key* p_dst_key, const struct pvr_crypto_key* p_key)
{
	if (p_key->kl_level != p_dst_key->kl_level)
	{
		PVR_ENC_ERR("p_key->kl_level %d != %d.\n", p_key->kl_level, p_dst_key->kl_level);
		return false;
	}

	if (PVR_KEY_PARITY_UNDEF == p_key->e_parity || PVR_KEY_PARITY_UNDEF == p_dst_key->e_parity)
	{
		if (p_key->e_parity != p_dst_key->e_parity)
		{
			PVR_ENC_ERR("p_key->e_parity %d != %d.\n", p_key->e_parity, p_dst_key->e_parity);
			return false;
		}
	}
	else
	{
		if (p_key->e_parity == p_dst_key->e_parity)
		{
			PVR_ENC_ERR("p_key->e_parity %d == %d.\n", p_key->e_parity, p_dst_key->e_parity);
			return false;
		}
	}

	if (p_key->e_algo != p_dst_key->e_algo)
	{
		PVR_ENC_ERR("p_key->e_algo %d != %d.\n", p_key->e_algo, p_dst_key->e_algo);
		return false;
	}

	if (p_key->e_mode != p_dst_key->e_mode)
	{
		PVR_ENC_ERR("p_key->e_mode %d != %d.\n", p_key->e_mode, p_dst_key->e_mode);
		return false;
	}

	return true;
}




#if 0
static aui_kl_algo algo_pvr2kl(enum pvr_key_algo e_algo)
{
	switch (e_algo)
	{
		case PVR_KEY_ALGO_AES:
			return AUI_KL_ALGO_AES;
			break;

		case PVR_KEY_ALGO_DES:
		case PVR_KEY_ALGO_TDES:
			return AUI_KL_ALGO_TDES;
			break;

		default:
			PVR_ENC_WARN("e_algo %d\r\n", e_algo);
			return AUI_KL_ALGO_AES;
	}
}

static aui_kl_run_level_mode kl_level_pvr2kl(int level)
{
	switch (level)
	{
		case 1:
			return AUI_KL_RUN_LEVEL_MODE_LEVEL_FIRST;
			break;

		case 2:
			return AUI_KL_RUN_LEVEL_MODE_LEVEL_SECOND;
			break;
			
		case 3:
			return AUI_KL_RUN_LEVEL_MODE_LEVEL_THIRD;
			break;

		case 5:
			return AUI_KL_RUN_LEVEL_MODE_LEVEL_ALL;
			break;

		default:
			PVR_ENC_WARN("level %d\r\n", level);
			return AUI_KL_RUN_LEVEL_MODE_LEVEL_NB;
	}

}
#endif


static aui_kl_cw_key_attr parity_pvr2kl(enum pvr_key_parity e_parity)
{
	switch (e_parity)
	{
		case PVR_KEY_PARITY_EVEN:
			return AUI_KL_CW_KEY_EVEN;
			break;

		case PVR_KEY_PARITY_ODD:
			return AUI_KL_CW_KEY_ODD;
			break;
			
		case PVR_KEY_PARITY_AUTO:
			return AUI_KL_CW_KEY_ODD_EVEN;
			break;

		default:
			PVR_ENC_WARN("e_parity %d\r\n", e_parity);
			return AUI_KL_CW_KEY_ODD_EVEN;
	}
	
}


static int cfg_kl(struct pvr_encrypt_status* p_status, unsigned long* p_key_dst_pos)
{
	struct pvr_crypto_key* p_key = &p_status->key;
	aui_hdl h_kl = NULL;
	int size = 0;
	
	struct aui_cfg_kl cfg;
	memset(&cfg, 0, sizeof(cfg));

	static unsigned char protected_keys[][16] = 
		{
			{ 0x18,0xb6,0x7d,0xe3,0x5d,0x1a,0x3b,0x31,
			  0xd8,0x46,0xd4,0xb3,0xe3,0x32,0x06,0x71 },
			{ 0x10,0xf6,0x97,0xf9,0xd6,0xf4,0xfd,0xef,
			  0xf5,0x70,0x16,0x7e,0x9f,0x1d,0x05,0x4f }
			//{ 0xf5,0x70,0x16,0x7e,0x9f,0x1d,0x05,0x4f,
			//  0x10,0xf6,0x97,0xf9,0xd6,0xf4,0xfd,0xef }
		};

	h_kl = p_status->h_kl;
	if (NULL == h_kl)
	{
		PVR_ENC_ERR("h_kl NULL\n");
		return false;
	}
	
	cfg.run_level_mode = AUI_KL_RUN_LEVEL_MODE_LEVEL_ALL;
	cfg.en_kl_algo = AUI_KL_ALGO_AES;	//algo_pvr2kl(p_key->algo);
	cfg.en_crypt_mode = AUI_KL_DECRYPT;
	cfg.en_cw_key_attr = parity_pvr2kl(p_key->e_parity);	//AUI_KL_CW_KEY_SINGLE;


	if (PVR_KEY_PARITY_EVEN == p_key->e_parity
		|| PVR_KEY_PARITY_ODD == p_key->e_parity)
	{
		size = p_key->key_length;
	}
	else if (PVR_KEY_PARITY_AUTO == p_key->e_parity)
	{
		size = p_key->key_length * 2;
	}
	else
	{
		PVR_ENC_ERR("p_key->e_parity %d\n", p_key->e_parity);
		return false;
	}
	MEMCPY(cfg.ac_key_val, protected_keys, sizeof(protected_keys));
	MEMCPY(&cfg.ac_key_val[sizeof(protected_keys)], p_key->p_key, size);

	if (aui_kl_gen_key_by_cfg(h_kl, &cfg, p_key_dst_pos)) {
		PVR_ENC_ERR("aui_kl_gen_key_by_cfg error\n");
		return false;
	}

	return true;

}




static aui_dsc_work_mode mode_pvr2dsc(enum pvr_key_mode e_mode)
{
	switch (e_mode)
	{
		case PVR_KEY_MODE_ECB:
			return AUI_DSC_WORK_MODE_IS_ECB;
			break;

		case PVR_KEY_MODE_CBC:
			return AUI_DSC_WORK_MODE_IS_CBC;
			break;

		case PVR_KEY_MODE_OFB:
			return AUI_DSC_WORK_MODE_IS_OFB;
			break;

		case PVR_KEY_MODE_CFB:
			return AUI_DSC_WORK_MODE_IS_CFB;
			break;

		case PVR_KEY_MODE_CTR:
			return AUI_DSC_WORK_MODE_IS_CTR;
			break;

		default:
			PVR_ENC_WARN("e_mode %d\r\n", e_mode);
			return AUI_DSC_WORK_MODE_NB;
	}
}










static void set_even_dsc_attr(struct pvr_crypto_key* p_key, aui_attr_dsc* p_dsc_attr)
{
	p_dsc_attr->en_parity = AUI_DSC_PARITY_MODE_EVEN_PARITY_MODE;
	p_dsc_attr->ul_key_pattern = AUI_DSC_KEY_PATTERN_EVEN;

	if (NULL != p_key->p_iv)
	{
		p_dsc_attr->puc_iv_ctr = p_key->p_iv;
	}
	else
	{
		p_dsc_attr->puc_iv_ctr = &g_default_iv[p_key->key_length];
	}
}


static void set_odd_dsc_attr(struct pvr_crypto_key* p_key, aui_attr_dsc* p_dsc_attr)
{
	p_dsc_attr->en_parity = AUI_DSC_PARITY_MODE_ODD_PARITY_MODE;
	p_dsc_attr->ul_key_pattern = AUI_DSC_KEY_PATTERN_ODD;

	if (NULL != p_key->p_iv)
	{
		p_dsc_attr->puc_iv_ctr = p_key->p_iv;
	}
	else
	{
		p_dsc_attr->puc_iv_ctr = g_default_iv;
	}
}


static void set_even_odd_dsc_attr(struct pvr_crypto_key* p_key, aui_attr_dsc* p_dsc_attr)
{
	p_dsc_attr->en_parity = AUI_DSC_PARITY_MODE_AUTO_PARITY_MODE0;
	p_dsc_attr->ul_key_pattern = AUI_DSC_KEY_PATTERN_ODD_EVEN;

	if (NULL != p_key->p_iv)
	{
		p_dsc_attr->puc_iv_ctr = p_key->p_iv;
	}
	else
	{
		p_dsc_attr->puc_iv_ctr = g_default_iv;
	}
}

static int set_dsc_common_attr(struct pvr_encrypt_status* p_status, aui_attr_dsc* p_dsc_attr)
{
	struct pvr_crypto_key* p_key = &p_status->key;
				
	p_dsc_attr->uc_dev_idx = p_status->dsc_dev_idx;
	p_dsc_attr->uc_algo = algo_pvr2dsc(p_key->e_algo);
	p_dsc_attr->dsc_data_type = AUI_DSC_DATA_TS;
	
	p_dsc_attr->uc_mode = mode_pvr2dsc(p_key->e_algo);
	p_dsc_attr->ul_key_len = p_key->key_length * 8;

	p_dsc_attr->en_residue = AUI_DSC_RESIDUE_BLOCK_IS_NO_HANDLE;
	p_dsc_attr->en_en_de_crypt = 0 != p_status->is_encrypt ? AUI_DSC_ENCRYPT : AUI_DSC_DECRYPT;
	//p_dsc_attr->csa_version = AUI_CSA1;
	p_dsc_attr->pus_pids = p_status->p_pids;
	p_dsc_attr->ul_pid_cnt = p_status->pid_count;

	switch (p_key->e_parity)
	{
		case PVR_KEY_PARITY_EVEN:
			set_even_dsc_attr(p_key, p_dsc_attr);
			break;

		case PVR_KEY_PARITY_ODD:
			set_odd_dsc_attr(p_key, p_dsc_attr);
			break;

		case PVR_KEY_PARITY_AUTO:
			set_even_odd_dsc_attr(p_key, p_dsc_attr);
			break;

		default:
			PVR_ENC_ERR("p_key->e_parity %d\r\n", p_key->e_parity);
			return false;
	}

	return true;
}



static int set_clear_dsc_attr(struct pvr_encrypt_status* p_status, aui_attr_dsc* p_dsc_attr)
{
	struct pvr_crypto_key* p_key = &p_status->key;

	if (true != set_dsc_common_attr(p_status, p_dsc_attr))
	{
		PVR_ENC_ERR("set_dsc_common_attr fail\r\n");
		return false;
	}

	p_dsc_attr->dsc_key_type = AUI_DSC_HOST_KEY_SRAM;
	p_dsc_attr->puc_key = p_key->p_key;

	return true;

}

static int set_kl_dsc_attr(struct pvr_encrypt_status* p_status, aui_attr_dsc* p_dsc_attr, unsigned long key_dst_pos)
{
	if (true != set_dsc_common_attr(p_status, p_dsc_attr))
	{
		PVR_ENC_ERR("set_dsc_common_attr fail\r\n");
		return false;
	}
	
	p_dsc_attr->dsc_key_type = AUI_DSC_CONTENT_KEY_KL;
	p_dsc_attr->ul_key_pos = key_dst_pos;
		
	return true;
}


static AUI_RTN_CODE set_dsc_cfg(struct pvr_encrypt_status* p_status, unsigned long key_dst_pos, int is_init_key)
{
	AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;
	int is_complete = false;
	aui_hdl h_dsc = p_status->h_dsc;

	UNUSED(is_init_key);

	if (NULL == h_dsc)
	{
		PVR_ENC_ERR("h_dsc NULL\n");
		return AUI_RTN_FAIL;
	}
	
	aui_attr_dsc dsc_attr;
	memset(&dsc_attr, 0, sizeof(dsc_attr));
			

	if (true == enable_kl(p_status))
	{
		is_complete = set_kl_dsc_attr(p_status, &dsc_attr, key_dst_pos);
	}
	else
	{
		is_complete = set_clear_dsc_attr(p_status, &dsc_attr);
	}
	if (true != is_complete)
	{
		PVR_ENC_ERR("is_complete %d\n", is_complete);
		return AUI_RTN_FAIL;
	}

	//if (true == is_init_key)
	{
		aui_ret = aui_dsc_attach_key_info2dsc(h_dsc, &dsc_attr);
		if (AUI_RTN_SUCCESS != aui_ret)
		{
			PVR_ENC_ERR("aui_gen_ca_pvr_rec_config_C1800A aui_dsc_attach_key_info2dsc failed %ld\n", aui_ret);
			return aui_ret;
		}	
	}
	//else
	//{
	//	aui_dsc_process_status dsc_process_status;
	//	memset(&dsc_process_status, 0, sizeof(dsc_process_status));

	//	aui_ret = aui_dsc_update_pvr_encrypt_key_info(h_dsc, &dsc_attr, NULL, &dsc_process_status);
	//	if (AUI_RTN_SUCCESS != aui_ret)
	//	{
	//		PVR_ENC_ERR("aui_gen_ca_pvr_rec_config_C1800A aui_dsc_attach_key_info2dsc failed %d\n", aui_ret);
	//		return aui_ret;
	//	}
	//}


	return AUI_RTN_SUCCESS;
}


static AUI_RTN_CODE do_change_pvr_key(struct pvr_encrypt_status* p_status)
{
	AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;
	unsigned long key_dst_pos = 0;

	if (true == enable_kl(p_status))
	{
		if (true != cfg_kl(p_status, &key_dst_pos))
		{
			PVR_ENC_ERR("cfg_kl fail.\n");
			return AUI_RTN_FAIL;
		}
	}

	aui_ret = set_dsc_cfg(p_status, key_dst_pos, 0);
	if (AUI_RTN_SUCCESS != aui_ret)
	{
		PVR_ENC_ERR("cfg_dsc set_dsc_cfg failed %ld\n", aui_ret);
		return AUI_RTN_FAIL;
	}

	return AUI_RTN_SUCCESS;
}

static AUI_RTN_CODE change_pvr_crypto_key(struct pvr_encrypt_status* p_status, const struct pvr_crypto_key* p_key)
{
	AUI_RTN_CODE ret = AUI_RTN_SUCCESS;
	
	if (true != verify_pvr_crypto_key(p_key))
	{
		PVR_ENC_ERR("p_key->key_length %d.\n", p_key->key_length);
		return AUI_RTN_FAIL;
	}

	if (true != enable_change_pvr_key(&p_status->key, p_key))
	{
		PVR_ENC_ERR("enable_change_pvr_key false\n");
		return AUI_RTN_FAIL;
	}

	clr_pvr_crypto_key(&p_status->key);
	if (true != save_pvr_crypto_key(&p_status->key, p_key))
	{
		PVR_ENC_ERR("save_pvr_crypto_key false\n");
		return AUI_RTN_FAIL;
	}

	ret = do_change_pvr_key(p_status);
	if (AUI_RTN_SUCCESS != ret)
	{
		PVR_ENC_ERR("do_change_pvr_key failure %ld\n", ret);
		return ret;
	}

	return AUI_RTN_SUCCESS;
}


static aui_hdl cfg_dsc(struct pvr_encrypt_status* p_status)
{
	aui_hdl h_dsc = NULL;
	aui_hdl h_kl = NULL;

	AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;
	unsigned long key_dst_pos = 0;

	aui_attr_dsc dsc_attr;
	memset(&dsc_attr, 0, sizeof(dsc_attr));

	struct aui_attr_kl kl_attr;
	memset(&kl_attr, 0, sizeof(kl_attr));

	if (true == enable_kl(p_status))
	{
		if (NULL == p_status->h_kl)
		{
			h_kl = open_kl_dev(p_status);
			if (NULL ==  h_kl)
			{
				PVR_ENC_ERR("h_kl NULL\n");
				return NULL;
			}
		}
		else
		{
			h_kl = p_status->h_kl;
		}


		if (true != cfg_kl(p_status, &key_dst_pos))
		{
			PVR_ENC_ERR("cfg_kl failed\n");
			return NULL;
		}
	}

	if (NULL == p_status->h_dsc)
	{
		h_dsc = open_dsc_dev(p_status);
		if (NULL == h_dsc)
		{
			PVR_ENC_ERR("open_dsc_dev failed\n");
			return NULL;
		}
	}
	else
	{
		h_dsc = p_status->h_dsc;
	}

	aui_dsc_process_attr dsc_process_attr;
	memset(&dsc_process_attr, 0, sizeof(dsc_process_attr));
	dsc_process_attr.process_mode = 0 != p_status->is_encrypt ? AUI_DSC_PROCESS_MODE_TS_ENCRYPT : AUI_DSC_PROCESS_MODE_TS_DECRYPT;
	dsc_process_attr.ul_block_size = 64 * GEN_CA_TS_PACKAGE_SIZE;
	aui_ret = aui_dsc_process_attr_set(h_dsc, &dsc_process_attr);
	if (AUI_RTN_SUCCESS != aui_ret)
	{
		PVR_ENC_ERR("aui_dsc_process_attr_set failed %ld\n", aui_ret);
		return NULL;
	}

	aui_ret = set_dsc_cfg(p_status, key_dst_pos, 1);
	if (AUI_RTN_SUCCESS != aui_ret)
	{
		PVR_ENC_ERR("cfg_dsc set_dsc_cfg failed %ld\n", aui_ret);
		return NULL;
	}

	return h_dsc;
}



#define ONLY_AUI_API

#ifdef ONLY_AUI_API
#else
tatic int get_dsc_fd(aui_hdl h_dsc)
{
	struct algo_info algo_info;
	AUI_RTN_CODE ret = AUI_RTN_SUCCESS;

	ret = aui_dsc_get_fd(h_dsc, &algo_info);
    if (AUI_RTN_SUCCESS != ret)
	{
		PVR_ENC_ERR("aui_dsc_get_fd fail %d.\n", ret);
		return INVALID_FD;
	}

	return algo_info.dsc_fd;
}
#endif

AUI_RTN_CODE start_pvr_encrypt(aui_pvr_crypto_general_param *p_param)
{
	AUI_RTN_CODE aui_ret = AUI_RTN_SUCCESS;
	struct pvr_encrypt_status* p_status = NULL;

	if (true != g_is_pvr_encrypt_status_inited)
	{
		PVR_ENC_ERR("g_is_pvr_encrypt_status_inited %d.\n", g_is_pvr_encrypt_status_inited);
		return AUI_RTN_FAIL;
	}

	p_status = get_pvr_encrypt_status(0);
	if (NULL == p_status)
	{
		PVR_ENC_ERR("get_pvr_encrypt_status fail.\n");
		return AUI_RTN_FAIL;
	}

	if (true != lock(p_status))
	{
		PVR_ENC_ERR("lock fail.\n");
		return AUI_RTN_FAIL;
	}
	
	if (true != p_status->is_key_valid)
	{
		PVR_ENC_ERR("p_status->is_key_valid %d\n", p_status->is_key_valid);
		goto start_pvr_encrypt_fail;
	}
	
	if (true == p_status->is_working)
	{
		PVR_ENC_ERR("p_status->is_working %d\n", p_status->is_working);
		goto start_pvr_encrypt_fail;
	}
	p_status->is_encrypt = true;

	if (0 == p_status->pid_count)
	{
		if (true != save_pid(p_status, p_param->pid_list, p_param->pid_num))
		{
			PVR_ENC_ERR("save_pid failed\n");
			goto start_pvr_encrypt_fail1;
		}
	}
	else
	{
		if (true != verify_pids(p_status, p_param->pid_list, p_param->pid_num))
		{
			PVR_ENC_ERR("verify_pids failed\n");
			goto start_pvr_encrypt_fail1;
		}
	}
	
	aui_hdl h_dsc = cfg_dsc(p_status);
	if (NULL == h_dsc)
	{
		PVR_ENC_ERR("cfg_dsc failed\n");
		goto start_pvr_encrypt_fail1;
	}

#if 0
	{
		//WARNING: struct dmx_device is defined in hld, it`s different from struct dmx_device in aui
		struct dmx_device *dmx = NULL; 
		dmx = (struct dmx_device *)dev_get_by_id(HLD_DEV_TYPE_DMX, p_param->dmx_id);
		p_status->pvr_de_enconfig.decrypt_fd = INVALID_FD;
		p_status->pvr_de_enconfig.encrypt_fd = get_dsc_fd(h_dsc);
		dmx_io_control(dmx, IO_SET_DEC_CONFIG, (UINT32)&p_status->pvr_de_enconfig);
	}
#endif

	if (NULL == p_status->h_dmx)
	{
		PVR_ENC_ERR("p_status->h_dmx NULL\n");
		goto start_pvr_encrypt_fail1;
	}

	aui_dmx_data_path dmx_data_path;
	memset(&dmx_data_path, 0, sizeof(dmx_data_path));
	dmx_data_path.data_path_type = AUI_DMX_DATA_PATH_EN_REC;
	dmx_data_path.dsc_type = AUI_DMX_DATA_PATH_DSC_TYPE_HANDLE;
	dmx_data_path.p_hdl_de_dev = NULL;
	dmx_data_path.p_hdl_en_dev = h_dsc;
	//dmx_data_path.p_dsc_id;

	aui_ret = aui_dmx_data_path_set(p_status->h_dmx, &dmx_data_path);
	if (AUI_RTN_SUCCESS != aui_ret)
	{
		PVR_ENC_ERR("aui_dmx_data_path_set failed %ld\n", aui_ret);
		goto start_pvr_encrypt_fail1;
	}


#if 1
		aui_dmx_dsc_id dmx_dsc_id;
		aui_dmx_dsc_id_get(p_status->h_dmx, &dmx_dsc_id);
	
		MEMSET(&dmx_data_path, 0, sizeof(dmx_data_path));
		dmx_data_path.data_path_type = AUI_DMX_DATA_PATH_EN_REC;
		dmx_data_path.dsc_type = AUI_DMX_DATA_PATH_DSC_TYPE_ID;
		dmx_data_path.p_dsc_id = &dmx_dsc_id;
		if (aui_dmx_data_path_set(p_status->h_dmx, &dmx_data_path))
		{
			PVR_ENC_ERR("\r\n aui_dmx_data_path_set failed\n");
		}
#endif	

	p_status->is_working = true;

	unlock(p_status);
    return AUI_RTN_SUCCESS;


start_pvr_encrypt_fail1:
	close_pvr_encrypt(p_status);

start_pvr_encrypt_fail:

	unlock(p_status);
	return AUI_RTN_FAIL;

}



AUI_RTN_CODE stop_pvr_encrypt(aui_pvr_crypto_general_param *p_param)
{
	UNUSED(p_param);

	struct pvr_encrypt_status* p_status = NULL;

	if (true != g_is_pvr_encrypt_status_inited)
	{
		PVR_ENC_ERR("g_is_pvr_encrypt_status_inited %d.\n", g_is_pvr_encrypt_status_inited);
		return AUI_RTN_FAIL;
	}
	
	p_status = get_pvr_encrypt_status(0);
	if (NULL == p_status)
	{
		PVR_ENC_ERR("get_pvr_encrypt_status fail.\n");
		return AUI_RTN_FAIL;
	}
	if (true != lock(p_status))
	{
		PVR_ENC_ERR("lock fail.\n");
		return AUI_RTN_FAIL;
	}
	
	close_pvr_encrypt(p_status);
	
	unlock(p_status);
	return AUI_RTN_SUCCESS;
}



AUI_RTN_CODE start_pvr_decrypt(aui_pvr_crypto_general_param *p_param)
{
	struct pvr_encrypt_status* p_status = NULL;

	if (true != g_is_pvr_encrypt_status_inited)
	{
		PVR_ENC_ERR("g_is_pvr_encrypt_status_inited %d.\n", g_is_pvr_encrypt_status_inited);
		return AUI_RTN_FAIL;
	}
	
	p_status = get_pvr_encrypt_status(0);
	if (NULL == p_status)
	{
		PVR_ENC_ERR("get_pvr_encrypt_status fail.\n");
		return AUI_RTN_FAIL;
	}
	if (true != lock(p_status))
	{
		PVR_ENC_ERR("lock fail.\n");
		return AUI_RTN_FAIL;
	}

	if (true != p_status->is_key_valid)
	{
		PVR_ENC_ERR("p_status->is_key_valid %d\n", p_status->is_key_valid);
		goto start_pvr_decrypt_fail;
	}
	
	if (true == p_status->is_working)
	{
		PVR_ENC_ERR("p_status->is_working %d\n", p_status->is_working);
		goto start_pvr_decrypt_fail;
	}
	p_status->is_encrypt = false;

	if (0 == p_status->pid_count)
	{
		if (true != save_pid(p_status, p_param->pid_list, p_param->pid_num))
		{
			PVR_ENC_ERR("save_pid failed\n");
			goto start_pvr_decrypt_fail1;
		}
	}
	else
	{
		if (true != verify_pids(p_status, p_param->pid_list, p_param->pid_num))
		{
			PVR_ENC_ERR("verify_pids failed\n");
			goto start_pvr_decrypt_fail1;
		}
	}
	
	aui_hdl h_dsc = cfg_dsc(p_status);
	if (NULL == h_dsc)
	{
		PVR_ENC_ERR("cfg_dsc failed\n");
		goto start_pvr_decrypt_fail1;
	}

#ifdef ONLY_AUI_API
	if (NULL == p_status->h_dmx)
	{
		if (AUI_RTN_SUCCESS != aui_find_dev_by_idx(AUI_MODULE_DMX, p_param->dmx_id, &p_status->h_dmx))
		{
				aui_attr_dmx attr_dmx;
				memset(&attr_dmx, 0, sizeof(aui_attr_dmx));
				attr_dmx.uc_dev_idx = p_param->dmx_id;	//DMX_ID_SW_DEMUX0;
 
				if(aui_dmx_open(&attr_dmx, &p_status->h_dmx))
				{
					PVR_ENC_ERR("aui_find_dev_by_idx AUI_MODULE_DMX failed(dmx_id %d)\n", p_param->dmx_id);
					goto start_pvr_decrypt_fail1;
				}
				//aui_dmx_start(p_status->h_dmx, NULL);
		}
	}

	aui_dmx_data_path dmx_data_path;
	memset(&dmx_data_path, 0, sizeof(dmx_data_path));
	dmx_data_path.data_path_type = AUI_DMX_DATA_PATH_DE_PLAY;
	dmx_data_path.dsc_type = AUI_DMX_DATA_PATH_DSC_TYPE_HANDLE;
	dmx_data_path.p_hdl_de_dev = h_dsc;
	dmx_data_path.p_hdl_en_dev = NULL;
	//dmx_data_path.p_dsc_id;

	AUI_RTN_CODE aui_ret = aui_dmx_data_path_set(p_status->h_dmx, &dmx_data_path);
	if (AUI_RTN_SUCCESS != aui_ret)
	{
		PVR_ENC_ERR("aui_dmx_data_path_set failed %ld\n", aui_ret);
		goto start_pvr_decrypt_fail1;
	}

	aui_dmx_dsc_id dmx_dsc_id;
	aui_dmx_dsc_id_get(p_status->h_dmx, &dmx_dsc_id);

	aui_dmx_data_path data_path;
	memset(&data_path, 0, sizeof(data_path));
	data_path.data_path_type = AUI_DMX_DATA_PATH_DE_PLAY;
	data_path.dsc_type = AUI_DMX_DATA_PATH_DSC_TYPE_ID;
	data_path.p_dsc_id = &dmx_dsc_id;
	if(aui_dmx_data_path_set(p_status->h_dmx, &data_path))
	{
		PVR_ENC_ERR("aui_dmx_data_path_set failed\n");
		goto start_pvr_decrypt_fail1;
	}
#else
	{
		struct dmx_device *dmx =NULL;
		int dsc_fd = INVALID_FD;

		//WARNING: struct dmx_device is defined in hld, it`s different from struct dmx_device in aui
		dmx = (struct dmx_device *)dev_get_by_id(HLD_DEV_TYPE_DMX, p_param->dmx_id);
		if(dmx == NULL)
		{
			PVR_ENC_ERR("Error: get dmx handle error !! \n");		  
			goto start_pvr_decrypt_fail1;
		}
			dsc_fd = get_dsc_fd(h_dsc);
		dmx_io_control(dmx, DMX_IO_SET_DEC_FD_HANDLE, (UINT32)&dsc_fd);
		dmx_io_control(dmx, IO_SET_DEC_STATUS, 1);
	}
#endif

	p_status->is_working = true;

	unlock(p_status);
	return AUI_RTN_SUCCESS;   

start_pvr_decrypt_fail1:
	close_pvr_encrypt(p_status);
		
start_pvr_decrypt_fail:	
	unlock(p_status);
	return AUI_RTN_FAIL;
}


AUI_RTN_CODE stop_pvr_decrypt(aui_pvr_crypto_general_param *p_param)
{
	struct pvr_encrypt_status* p_status = NULL;

	if (true != g_is_pvr_encrypt_status_inited)
	{
		PVR_ENC_ERR("g_is_pvr_encrypt_status_inited %d.\n", g_is_pvr_encrypt_status_inited);
		return AUI_RTN_FAIL;
	}
	
	p_status = get_pvr_encrypt_status(0);
	if (NULL == p_status)
	{
		PVR_ENC_ERR("get_pvr_encrypt_status fail.\n");
		return AUI_RTN_FAIL;
	}
	if (true != lock(p_status))
	{
		PVR_ENC_ERR("lock fail.\n");
		return AUI_RTN_FAIL;
	}

#ifdef ONLY_AUI_API
UNUSED(p_param);
#else
	f (NULL != p_status->h_dsc)
	{
		int dsc_fd = get_dsc_fd(p_status->h_dsc);
		struct dmx_device *dmx = NULL;
		dmx = (struct dmx_device *)dev_get_by_id(HLD_DEV_TYPE_DMX, p_param->dmx_id);
		if (NULL != dmx)
		{
			dmx_io_control(dmx, DMX_IO_SET_DEC_FD_HANDLE, (UINT32)(&dsc_fd));
			dmx_io_control(dmx, IO_SET_DEC_STATUS, 0);
		}
		else
		{
			PVR_ENC_ERR("get_pvr_encrypt_status fail.\n");
		}
	}
#endif


	close_pvr_encrypt(p_status);

	unlock(p_status);
	return AUI_RTN_SUCCESS;
}


AUI_RTN_CODE set_pvr_crypto_key(const struct pvr_crypto_key* p_key, 
	struct pvr_set_crypto_key_hd* p_key_hd, struct pvr_crypto_pids* p_pids)
{
	AUI_RTN_CODE ret = AUI_RTN_SUCCESS;
	struct pvr_encrypt_status* p_status = NULL;
	
	if (true != g_is_pvr_encrypt_status_inited)
	{
		if (true != init_pvr_encrypt_status_array())
		{
			return false;
		}
		g_is_pvr_encrypt_status_inited = true;
	}

	p_status = get_pvr_encrypt_status(0);
	if (NULL == p_status)
	{
		PVR_ENC_ERR("get_pvr_encrypt_status fail.\n");
		return AUI_RTN_FAIL;
	}
	if (true != lock(p_status))
	{
		PVR_ENC_ERR("lock fail.\n");
		return AUI_RTN_FAIL;
	}

	//PVR_ENC_ERR("$$$$$$$$$ %d, (%02x, %02x, %02x, %02x)\r\n", p_key->e_parity, p_key->p_key[0], p_key->p_key[1], p_key->p_key[2], p_key->p_key[3]);
	//change key
	if (true == p_status->is_working)
	{
		ret = change_pvr_crypto_key(p_status, p_key);
	}

	//init key
	else
	{
		ret = init_pvr_crypto_key(p_status, p_key, p_key_hd, p_pids);
	}

	unlock(p_status);
	
	return ret;

}


void free_pvr_crypto_key()
{
	struct pvr_encrypt_status* p_status = NULL;
		
	if (true != g_is_pvr_encrypt_status_inited)
	{
		return;
	}
		
	p_status = get_pvr_encrypt_status(0);
	if (NULL == p_status)
	{
		return;
	}
	if (true != lock(p_status))
	{
		PVR_ENC_ERR("lock fail.\n");
		return;
	}

	close_pvr_encrypt(p_status);

	unlock(p_status);
}


static unsigned short int pvr_crypto_check_pids(unsigned short int *pid_list, unsigned short int pid_num)
{
    unsigned short int valid_pid_num = 0;
    unsigned short int i, j;

    for (i = 0; i < pid_num; i++) {
        if ((0 == pid_list[i]) || ((pid_list[i] & INVALID_PID) == INVALID_PID)) {
            continue;
        }

        for (j = 0; j < valid_pid_num; j++) {
            if (pid_list[i] == pid_list[j]) {
                pid_list[i] = INVALID_PID;
                break;
            }
        }

        if (j >= valid_pid_num) {
            pid_list[valid_pid_num++] = pid_list[i];
        }
    }

    return valid_pid_num;
}


AUI_RTN_CODE pvr_crypto_set_pids(aui_pvr_crypto_pids_param *p_pids_param)
{
	struct aui_pvr_pid_info *pid_info = NULL;
	unsigned short int *pid_list;
	unsigned short int pid_list_size;
    unsigned short int pid_num = 0;
    unsigned short int i;

	if (NULL == p_pids_param)
	{
		PVR_ENC_ERR("p_pids_param NULL.\n");
		return AUI_RTN_FAIL;
	}
	
	pid_info = p_pids_param->pid_info;
	if (NULL == pid_info)
	{
		PVR_ENC_ERR("pid_info NULL.\n");
		return AUI_RTN_FAIL;
	}

	pid_list = p_pids_param->pid_list;
	if (NULL == pid_list)
	{
		PVR_ENC_ERR("pid_list NULL.\n");
		return AUI_RTN_FAIL;
	}
	
	pid_list_size = p_pids_param->pid_num;
	

    if ((pid_info->video_pid != INVALID_PID) && (pid_num < pid_list_size)) {
        pid_list[pid_num++] = pid_info->video_pid;
    }

    for (i = 0; (i < pid_info->audio_count) && (pid_num < pid_list_size); i++) {
        pid_list[pid_num++] = pid_info->audio_pid[i];
    }

    for (i = 0; (i < pid_info->ttx_pid_count) && (pid_num < pid_list_size); i++) {
        pid_list[pid_num++] = pid_info->ttx_pids[i];
    }

    for (i = 0; (i < pid_info->ttx_subt_pid_count) && (pid_num < pid_list_size); i++) {
        pid_list[pid_num++] = pid_info->ttx_subt_pids[i];
    }

    for (i = 0; (i < pid_info->subt_pid_count) && (pid_num < pid_list_size); i++) {
        pid_list[pid_num++] = pid_info->subt_pids[i];
    }
    
    p_pids_param->pid_num = pvr_crypto_check_pids(pid_list, pid_num);
	if (0 >= p_pids_param->pid_num)
	{
		PVR_ENC_ERR("pid_num %d.\n", p_pids_param->pid_num);
		return AUI_RTN_FAIL;
	}

	return AUI_RTN_SUCCESS;
	
}



