#include "boot_system_data.h"
#include "bootloader.h"


static union BOOT_INFO boot_system_data;
static UINT32 boot_info_addr = 0;

static void boot_sys_data_init(void)
{
    UINT8 i = 0;

    boot_system_data.t_info.boot_display_mode = 1;
    boot_system_data.t_info.boot_tv_ratio = 0;
    boot_system_data.t_info.boot_display_mode = 2;
    boot_system_data.t_info.boot_scart_out = 2;//SCART_YUV;
    for(i=0;i<VDAC_NUM_MAX;i++)
    {
        boot_system_data.t_info.vdac_out[i] = 0;
    }

    boot_system_data.t_info.ota_flag = 0;

    boot_system_data.t_info.ota_frequency = OTA_FREQUENCY;
    boot_system_data.t_info.band_width = OTA_BANDWIDTH;
    boot_system_data.t_info.ota_pid = OTA_PID;

    boot_system_data.c_info.osd_lang = 0;//ENGLISH_ENV;
}

static RET_CODE boot_sys_data_load(union BOOT_INFO *boot_info)
{
    RET_CODE ret = RET_FAILURE;
    UINT32 userdb_chid = 0;
    UINT32 userdb_addr = 0;
    UINT32 userdb_len = 0;
    UINT32 tmpinfo_addr= 0;
    UINT32 tmpinfo_len = 0;
    UINT8 tmp_data[4] ={0,0,0,0};

    if (NULL == boot_info)
    {
        return ret;
    }

    MEMSET(boot_info, 0, sizeof(union BOOT_INFO));

    userdb_chid = 0x04FB0100;
    userdb_addr = sto_chunk_goto(&userdb_chid, 0xFFFFFFFF, 1);
    if(userdb_addr == (UINT32)ERR_FAILUE)
    {
        return ret;
    }
    userdb_len = sto_fetch_long((UINT32)userdb_addr + CHUNK_LENGTH) - 0x70;
    /* seek the last node for tmp info */
    tmpinfo_addr = userdb_addr+0x200 - (userdb_addr+0x200)%(64*1024) + userdb_len - 4;
    tmpinfo_len = 0x10000-4;

    while((0xFFFFFFFF == (sto_fetch_long(tmpinfo_addr))) && \
           tmpinfo_len > 0)
    {
        tmpinfo_len -= 4;
        tmpinfo_addr -= 4;
    }
    while(tmpinfo_len > 0)
    {
        ret = sto_get_data(flash_dev,tmp_data,tmpinfo_addr,1);
        if(ret < 0)
        {
            return RET_FAILURE;
        }
        ret = sto_get_data(flash_dev,tmp_data+1,tmpinfo_addr-1,1);
        if(ret < 0)
        {
            return RET_FAILURE;
        }
        ret = sto_get_data(flash_dev,tmp_data+2,tmpinfo_addr-2,1);
        if(ret < 0)
        {
            return RET_FAILURE;
        }
        ret = sto_get_data(flash_dev,tmp_data+3,tmpinfo_addr-3,1);
        if(ret < 0)
        {
            return RET_FAILURE;
        }
        if((0x12 == tmp_data[0]) && \
            (0x34 == tmp_data[1]) && \
            (0x56 == tmp_data[2]) && \
            (0x78 == tmp_data[3]))
        {
            break;
        }
        tmpinfo_len -= 1;
        tmpinfo_addr -= 1;
    }

    if(tmpinfo_len > 0)
    {
        boot_info_addr=tmpinfo_addr+1;
        if(sto_get_data(flash_dev, (UINT8*)boot_info, tmpinfo_addr+1, sizeof(union BOOT_INFO))==sizeof(union BOOT_INFO))
        {
            return RET_SUCCESS;
        }
    }

    return RET_FAILURE;
}

static INT32 boot_sys_data_save(union BOOT_INFO *boot_info)
{
    return sto_put_data(flash_dev, boot_info_addr, (UINT8*)boot_info, sizeof(union BOOT_INFO));
}

union BOOT_INFO *get_boot_info(void)
{
    return &boot_system_data;
}


