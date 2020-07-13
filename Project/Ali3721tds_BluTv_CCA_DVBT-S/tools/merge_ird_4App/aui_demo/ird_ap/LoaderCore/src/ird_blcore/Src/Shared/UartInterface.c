/*****************************************************************************
*                  COPYRIGHT (C) 2011 IRDETO B.V.                            *
******************************************************************************
*          File : UartInterface.c
*                                                                            *
*   Description : Temu is a PC hosted serial communication tool for          *
*                 delivering a download to a single IRD. This module         *
*                 will provide all relevant communication functions          *
*                 between Temu and IRD, according to the communication       *
*                 protocal prepared by Irdeto Loader.                        *
*                                                                            *
*****************************************************************************/

#include "LoaderCorePrivate.h"
#include <sys_config.h>
#include <api/libfs2/lib_stdio.h>
#include <aui_fs.h>
#include <api/libfs2/fs_main.h>

#define MAX_BYTES_PER_READ  (0x0000ffff)    /* maximum 16 bits long */
#define UART_INTERFACE_DEBUG  libc_printf
//#define UART_INTERFACE_DEBUG(...)
//#define USB_FS_READ
// #ifdef USB_FS_READ
#if 0
#define udisk_plug_dbg libc_printf
#else
#define udisk_plug_dbg(...)
#endif
#define BREAKPOINT()  asm volatile(".word 0x1000ffff; nop;");

#define UPG_USB_MODE "0"
#define UPG_UART_MODE "1"
#define ONCE_WRITE  (1024*64)
#define LC_USB_TIMEOUT  (30*1000)

#define UPG_DIR "/mnt/uda1/"
#define UPG_USB_FILE "/mnt/uda1/ALi_update.cd5"


typedef enum _lc_upg_type
{
    LC_UPG_USB = 0,
    LC_UPG_UART = 1,
    LC_UPG_INVALID = 2
}LC_UPG_TYPE;


static volatile aui_f_hdl opt_file = NULL;
static aui_f_hdl dump_file = NULL;
static LC_UPG_TYPE ird_upgrade_flag = LC_UPG_INVALID;

volatile aui_fs_event LC_FS_FLAG = AUI_FS_EVENT_READY;
volatile lc_uint32 usb_plugout_time = 0;


void fs_evt_cb(aui_fs_event type, unsigned int device_id, const void *pv_event_data, void *pv_usercb_data)
{
    udisk_plug_dbg("fs_evt_cb -> %d, %u, %p, %p\n", type, device_id, pv_event_data, pv_usercb_data);
    if (type) {
        switch (type) {
            case AUI_FS_EVENT_READY:
            {
                udisk_plug_dbg("%s -> disk ready r/w \n", __func__);
                LC_FS_FLAG = type;
                break;
            }
            case AUI_FS_EVENT_PLUGOUT:
            {
                udisk_plug_dbg("%s -> disk plugout \n", __func__);
                LC_FS_FLAG = type;
                //opt_file = NULL;
                usb_plugout_time = osal_get_tick();
                break;
            }
            default:
            {
                udisk_plug_dbg("%s -> evt: %d\n", __func__, type);
                break;
            }
        }
    }
    return 0;
}

lc_result LC_fs_init(void)
{
    if(AUI_RTN_SUCCESS != aui_fs_init())
    {
        UART_INTERFACE_DEBUG("-------aui_fs_init fail--------\n");
        return LC_FAILURE;
    } 
	if(AUI_RTN_SUCCESS != aui_fs_addcallback(fs_evt_cb, NULL))
	{
        UART_INTERFACE_DEBUG("-------aui_fs_addcallback fail--------\n");
        return LC_FAILURE;
	}
    usb_init();
    return LC_SUCCESS;
}

lc_result ird_dump_data_to_usb(lc_char* addr, lc_uint32 length)
{
    aui_f_hdl fp = NULL;
    int fs_ret = 0;
    int i = 0;
    lc_uint32 done_length = 0;
    lc_uint32 needWrite = ONCE_WRITE;
    lc_uint32 left_length = 0;
    static int  wait_times = 0;
	unsigned int fs_dev = 0;
	unsigned int actual_num =0 ;
	
    UART_INTERFACE_DEBUG("%s line %d, addr = 0x%x, length = 0x%x\n", __func__, __LINE__, addr, length);

    wait_times = 0;
	while((AUI_RTN_SUCCESS == aui_fs_get_alldevid(&fs_dev,1,&actual_num) )&& (0 == fs_dev))
	{
		udisk_plug_dbg("Warning: filesystem not mounted,waiting@%d!\n", wait_times);
        wait_times += 1;
        if(30 == wait_times)
        {
            return -1;
        }
		AUI_SLEEP(500);
	}
	UART_INTERFACE_DEBUG("%s line %d,fs_dev = %d\n",__func__,__LINE__,fs_dev);

    UART_INTERFACE_DEBUG("=======================write data to usb start================\n");
    fp = aui_fs_open("/mnt/uda1/dump.out", "w+");
	if(!fp)
	{
		UART_INTERFACE_DEBUG("%s line %d,open(w+)file failed!\n",
			__func__,__LINE__);
		return LC_FAILURE;
	}

    fs_ret = aui_fs_seek(fp, 0, SEEK_SET);
	if(fs_ret != 0)
	{
		UART_INTERFACE_DEBUG("%s line %d,seek file failed!fs_ret = %d\n",
			__func__,__LINE__,fs_ret);
		return LC_FAILURE;
	}

    if(length < ONCE_WRITE)
    {
        fs_ret = aui_fs_write(fp, addr, length);
    	if(fs_ret != length)
    	{
    		UART_INTERFACE_DEBUG("%s line %d, write file failed!,fs_ret = %d\n",
    			__func__,__LINE__,fs_ret);
    		return LC_FAILURE;
    	}
    }
    else
    {
        left_length = length;
        for(; left_length != 0 ;)
        {
            UART_INTERFACE_DEBUG("%s line %d, left_length = 0x%x\n", __func__,__LINE__, left_length);
            if((left_length / ONCE_WRITE) > 0)
            {
                needWrite = ONCE_WRITE;
            }
            else
            {
                needWrite = left_length;
            }
            left_length = left_length - needWrite;
            fs_ret = aui_fs_write(fp, addr, needWrite);
            aui_fs_flush(fp);
        	if(fs_ret != needWrite)
        	{
        		UART_INTERFACE_DEBUG("%s line %d, write file failed!,fs_ret = %d\n",
        			__func__,__LINE__,fs_ret);
        		return LC_FAILURE;
        	}
            addr += needWrite;

            fs_ret = aui_fs_seek(fp, 0, SEEK_END);
            //fs_ret = aui_fs_seek(fp, needWrite, SEEK_CUR);
        	if(fs_ret != 0)
        	{
        		UART_INTERFACE_DEBUG("%s line %d,seek file failed!fs_ret = %d\n",
        			__func__,__LINE__,fs_ret);
        		return LC_FAILURE;
        	}
            done_length += needWrite;
        }
    }
    if(done_length != length)
        UART_INTERFACE_DEBUG("%s line %d, write not complete!\n", __func__,__LINE__);

    aui_fs_flush(fp);
	fs_ret = aui_fs_close(fp);
	if(fs_ret)
	{
		UART_INTERFACE_DEBUG("%s line %d, close file failed!,fs_ret = %d\n",
			__func__,__LINE__,fs_ret);
		return LC_FAILURE;
	}
    UART_INTERFACE_DEBUG("=======================write data to usb end================\n");
    return LC_SUCCESS;
}

static int LC_USBTemuStart(void)
{
	int fs_ret = 0;
    int ret = 0;
	int ecode = SUCCESS;
	aui_f_hdl dir = NULL;
	char buf[600] = {0};
	aui_fs_dirent_t *dirent = NULL;
	aui_f_hdl fp = NULL;
	unsigned int fs_dev = 0;
	unsigned int actual_num =0 ;

    static int wait_times = 0;

    if(NULL != opt_file)
    {
        UART_INTERFACE_DEBUG("ALi_update.cd5 has been open\n");
        return 0;
    }
	wait_times = 0;
	while((AUI_RTN_SUCCESS == aui_fs_get_alldevid(&fs_dev,1,&actual_num) )&& (0 == fs_dev))
	{
		udisk_plug_dbg("Warning: filesystem not mounted,waiting@%d!\n", wait_times);
        wait_times += 1;
        if(30 == wait_times)
        {
            return -1;
        }
		AUI_SLEEP(500);
	}
	UART_INTERFACE_DEBUG("%s line %d,fs_dev = %d\n",__func__,__LINE__,fs_dev);
	
	memset(buf, 0, 600);
	
	dir = aui_fs_open_dir(UPG_DIR);
	if(!dir)
	{
		UART_INTERFACE_DEBUG("%s line %d,open dir failed,dir = %p\n",__func__,__LINE__,dir);
        return -1;
	}

	while(1)
	{
		if(NULL != (dirent = aui_fs_read_dir(dir)))
		{
			UART_INTERFACE_DEBUG("    dir content %s\n",dirent->m_c_dir_name);
            if(0 == memcmp("ALi_update.CD5" ,dirent->m_c_dir_name,sizeof("ALi_update.CD5")))
            {
                break;
            }
     
		}
		else
		{
			break;
		}
	}
	aui_fs_close_dir(dir);

    UART_INTERFACE_DEBUG("%s line %d,open file: %s!\n",__FUNCTION__,__LINE__, UPG_USB_FILE);
    fp = aui_fs_open(UPG_USB_FILE, "r");
	if(NULL == fp)
	{
		UART_INTERFACE_DEBUG("%s line %d,open(r)file failed!\n",__FUNCTION__,__LINE__);
        return -1;
	}
    else
    {
        UART_INTERFACE_DEBUG("%s line %d,open(r)file success fp(0x%08x)!\n",__FUNCTION__,__LINE__,fp);
        opt_file = fp;
    	fs_ret = aui_fs_seek(fp, 0, SEEK_SET);

    	if(fs_ret != 0)
    	{
    		UART_INTERFACE_DEBUG("error %s line %d,seek file failed!fs_ret = %d\n",__func__,__LINE__,fs_ret);
            return -2;
    	}
	    else
	    {
    		UART_INTERFACE_DEBUG("%s line %d,seek file success\n",__func__,__LINE__);
        }
    }
    return ret;
}

static lc_result LC_UartTemuStart(void)
{
    lc_result result = LC_SUCCESS;
    lc_buffer_st aUARTPacket;
    lc_uchar abCmdSeq[3] = { STX, CMD_STB_START, ETX };
    lc_uchar abTemuSeq[4];

    aUARTPacket.bytes = abCmdSeq;
    aUARTPacket.length = sizeof(abCmdSeq);

    if (LC_SUCCESS == result)
    {
        /* STB -> Temu */
        result = LoaderCoreSPI_UART_Write(&aUARTPacket);
    }

    if (LC_SUCCESS == result)
    {
        /* STB <- Temu { STX, CMD_TEMU_START, DATA_TEMU_START, ETX } */
        aUARTPacket.bytes = abTemuSeq;
        aUARTPacket.length = sizeof(abTemuSeq);
        result = LoaderCoreSPI_UART_Read( &aUARTPacket );
    }

    if (LC_SUCCESS == result)
    {
		UART_INTERFACE_DEBUG("[UART_IFC] Temu Start (STB <- Temu)\n");
        UART_INTERFACE_DEBUG("[UART_IFC] Byte number = %d\n", aUARTPacket.length);
        UART_INTERFACE_DEBUG("[UART_IFC] Byte sequence = 0x%02x 0x%02x 0x%02x 0x%02x\n",
                abTemuSeq[0],
                abTemuSeq[1],
                abTemuSeq[2],
                abTemuSeq[3]);
		
        if(!((aUARTPacket.length == 4) &&
                    (abTemuSeq[0] == STX) &&
                    (abTemuSeq[1] == CMD_TEMU_START) &&
                    (abTemuSeq[2] == DATA_TEMU_START) &&
                    (abTemuSeq[3] == ETX)) )
        {
            result = LC_FAILURE;
        }

        if (LC_SUCCESS == result)
        {
            UART_INTERFACE_DEBUG("Temu is present.\n");
        }
    }

    return result;
}

lc_result LC_TemuStart( void )
{

	 if(LC_SUCCESS == LC_USBTemuStart())	
	 {
		ird_upgrade_flag = LC_UPG_USB;
	 }
	 else
	 {
		if(LC_SUCCESS== LC_UartTemuStart())
		{
		   ird_upgrade_flag = LC_UPG_UART; 
		}
		else
		{
		   UART_INTERFACE_DEBUG("%s    %s get ird_boostrap_flag invalid\n", __FILE__ ,__FUNCTION__); 
		   return LC_FAILURE;
		}
	 }
	return LC_SUCCESS;
  
}

lc_result LC_TemuDataRequest(
    lc_uchar *pData,
    lc_uint32 length,
    lc_uint32 offset,
    lc_uint32 maxRetry)
{
    lc_result result = LC_SUCCESS;
    lc_uint32 bytesToRead = length;
    lc_uchar *pRead = pData;
    lc_uint32 off = offset;
    lc_uint32 bytesPerRead = 0;
    lc_uint32 retry = maxRetry;
    lc_uchar abCmdSeq[9];
    lc_buffer_st aUARTPacket = {0};
    lc_uint32 waittime =0;

    int fs_ret = 0;
    int ret = 0;
    aui_fs_dirent_t *dirent = NULL;
    aui_f_hdl fp = NULL;

    if(LC_UPG_USB == ird_upgrade_flag)
    {

        if( 0 == bytesToRead)
        {
            return LC_FAILURE;
        }

RETRY:
        result = LC_SUCCESS;
        if (NULL == opt_file)
        {
            // scan USB disk
            if(0 == LC_USBTemuStart())
            {
                udisk_plug_dbg("%s@%d, ok\n", __func__, __LINE__);
            }
            else
            {
                result = LC_FAILURE;
                udisk_plug_dbg("%s@%d, fail\n", __func__, __LINE__);
                if (AUI_FS_EVENT_READY == LC_FS_FLAG) 
                {
                    udisk_plug_dbg("%s line %d, sleep 3s to verify plug_out event\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
                    osal_task_sleep(3000);
                }
                udisk_plug_dbg("%s line %d,LC_USBTemuStart file failed!fs_ret = %d, %d\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
                if (AUI_FS_EVENT_READY == LC_FS_FLAG)
                {
                    udisk_plug_dbg("%s@%d -> really call LC_USBTemuStart fail\n", __func__, __LINE__);
                    return LC_FAILURE;
                }
                else if (AUI_FS_EVENT_PLUGOUT == LC_FS_FLAG)
                {
                    udisk_plug_dbg("%s@%d -> detect plugout evt during call LC_USBTemuStart, offset: %u, off: %u\n", __func__, __LINE__, offset, off);
                    goto FS_API_ERR;
                }
				
            }
        }

        fp = opt_file;
        UART_INTERFACE_DEBUG("aui_fs_seek is calling , fp(0x%08x), off(0x%08x)\n ",fp, off);
        fs_ret = aui_fs_seek(fp, off, SEEK_SET);
        if (fs_ret != 0)
        {
            UART_INTERFACE_DEBUG("error %s line %d,seek file failed!fs_ret = %d off(0x08x)\n",__func__,__LINE__,fs_ret,off);
            result = LC_FAILURE;

            udisk_plug_dbg("%s line %d,seek file failed!fs_ret = %d, %d\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
            if (AUI_FS_EVENT_READY == LC_FS_FLAG) {
               udisk_plug_dbg("%s line %d, sleep 3s to verify plug_out event\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
               osal_task_sleep(3000);
            }
            udisk_plug_dbg("%s line %d,seek file failed!fs_ret = %d, %d\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
            if (AUI_FS_EVENT_READY == LC_FS_FLAG)
            {
                udisk_plug_dbg("%s@%d -> really seek fail\n", __func__, __LINE__);
                return LC_FAILURE;
            }
            else if (AUI_FS_EVENT_PLUGOUT == LC_FS_FLAG)
            {
                udisk_plug_dbg("%s@%d -> detect plugout evt while seek, offset: %u, off: %u\n", __func__, __LINE__, offset, off);
                goto FS_API_ERR;
            }
			
        }
        else
        {
            UART_INTERFACE_DEBUG("%s line %d,seek file success\n",__func__,__LINE__);
        }

        for (retry = maxRetry; retry > 0; )
        {
            do
            {
                bytesPerRead = MAX_BYTES_PER_READ;
                if (bytesToRead < MAX_BYTES_PER_READ)
                {
                    bytesPerRead = bytesToRead;
                }

                UART_INTERFACE_DEBUG("aui_fs_read is calling fp(0x%08x), pRead(0x%08x), bytesPerRead(0x%08x)\n ",fp, pRead, bytesPerRead);
                fs_ret = aui_fs_read(fp, pRead, bytesPerRead);
                if (fs_ret <=0)
                {
                   result = LC_FAILURE;
				   udisk_plug_dbg("%s line %d,read file failed!fs_ret = %d\n", __func__,__LINE__, fs_ret);
                   udisk_plug_dbg("%s line %d,read file failed!fs_ret = %d, %d\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
                   if ((0 == fs_ret) && (AUI_FS_EVENT_READY == LC_FS_FLAG)) {
                       udisk_plug_dbg("%s line %d, sleep 3s to verify plug_out event\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
                       osal_task_sleep(3000);
                   }
                   result = LC_FAILURE;
                   udisk_plug_dbg("%s line %d,read file failed!fs_ret = %d, %d\n", __func__,__LINE__, fs_ret, LC_FS_FLAG);
                   if ((0 == fs_ret) && (AUI_FS_EVENT_READY == LC_FS_FLAG))
                   {
                        udisk_plug_dbg("%s@%d -> read eof \n", __func__, __LINE__);
                        result = LC_SUCCESS;
                   }
                   else if ((0 == fs_ret) && (AUI_FS_EVENT_PLUGOUT == LC_FS_FLAG))
                   {
                        udisk_plug_dbg("%s@%d -> detect plugout evt while reading, offset: %u, off: %u\n", __func__, __LINE__, offset, off);
                        goto FS_API_ERR;
                   }
                }

                if (LC_SUCCESS == result)
                {
                    if( fs_ret != bytesPerRead )
                    {
                        UART_INTERFACE_DEBUG("error The read bytes is not the same as wanted one fs_ret(%d),bytesPerRead(%d)\n",fs_ret,bytesPerRead);
                        result = LC_FAILURE;
                    }
                }

                if (LC_SUCCESS == result)
                {
                    pRead += bytesPerRead;
                    bytesToRead -= bytesPerRead;
                    off += bytesPerRead;
                }

            } while ((bytesToRead > 0) && (LC_SUCCESS == result));

            if (LC_SUCCESS == result)
            {
                break;
            }
            else
            {
                retry--;
            }

        }


        if (0 == retry)
        {
            result = LC_FAILURE;
           // ERR_REPORT_SetErrorCode(ERROR_CODE_UART_TIMEOUT);
        }

FS_API_ERR:
        UART_INTERFACE_DEBUG("%s@%d, %p, %d, %d\n", __FUNCTION__, __LINE__, opt_file, result, LC_FS_FLAG);
        if ((AUI_FS_EVENT_PLUGOUT == LC_FS_FLAG) &&(LC_FAILURE == result) )
        {
            if (opt_file) {
                udisk_plug_dbg("%s@%d close file\n", __func__, __LINE__);
                aui_fs_close(opt_file);
                udisk_plug_dbg("%s@%d close file success\n", __func__, __LINE__);
                opt_file = NULL;
            }
            do
            {
                if(AUI_FS_EVENT_READY == LC_FS_FLAG)
                {
                    udisk_plug_dbg("%s@%d -> plug in 30s, continue read\n", __FUNCTION__, __LINE__);
                    usb_plugout_time = 0;
                    goto RETRY;
                }
                else
                {
                    if((osal_get_tick() - usb_plugout_time ) < LC_USB_TIMEOUT)
                    {
                        osal_task_sleep(1000);
                        udisk_plug_dbg("%s@%d -> wait one more 1s\n", __FUNCTION__, __LINE__);
                        continue;
                    }
                    else
                    {
                        udisk_plug_dbg("%s@%d -> timeout 30s\n", __FUNCTION__, __LINE__);
                        ERR_REPORT_SetErrorCode(ERROR_CODE_UART_TIMEOUT);
                        return LC_SUCCESS; //return success and let upper level to return timeout.
                    }
                }
            }while(1);
        }
        return result;
    }
    else if(LC_UPG_UART == ird_upgrade_flag)
    {
        if (0 == bytesToRead)
        {
            result = LC_FAILURE;
        }

        if (LC_SUCCESS == result)
        {
            for (retry = maxRetry; retry > 0; )
            {
                do
                {
                    bytesPerRead = MAX_BYTES_PER_READ;
                    if (bytesToRead < MAX_BYTES_PER_READ)
                    {
                        bytesPerRead = bytesToRead;
                    }

                    abCmdSeq[0] = STX;
                    abCmdSeq[1] = CMD_STB_DATA_REQUEST;
                    abCmdSeq[2] = (lc_uchar)(bytesPerRead & 0xFF);         /* LSB of length */
                    abCmdSeq[3] = (lc_uchar)((bytesPerRead >> 8) & 0xFF);  /* MSB of length */
                    abCmdSeq[4] = (lc_uchar)(off & 0xFF);         /* LSB of offset */
                    abCmdSeq[5] = (lc_uchar)((off >>  8) & 0xFF);
                    abCmdSeq[6] = (lc_uchar)((off >> 16) & 0xFF);
                    abCmdSeq[7] = (lc_uchar)((off >> 24) & 0xFF); /* MSB of offset */
                    abCmdSeq[8] = ETX;

                    aUARTPacket.bytes = abCmdSeq;
                    aUARTPacket.length = sizeof(abCmdSeq);

                    /* STB -> Temu */
                    result = LoaderCoreSPI_UART_Write(&aUARTPacket);

                    /* STB <- Temu { data[wLength] }
                        Data sent from Temu to the STB in response to a STB_DATA_REQUEST
                        cmd is transmitted as raw data with no STX/ETX framing.
                     */
                    if (LC_SUCCESS == result)
                    {
                        aUARTPacket.bytes = pRead;
                        aUARTPacket.length = bytesPerRead;
                        result = LoaderCoreSPI_UART_Read(&aUARTPacket);
                        /*DBG(LC_printf("[UART_IFC] lReadByte = 0x%x\n", lReadByte));*/

                        if( aUARTPacket.length != bytesPerRead )
                        {
                            /* read error */
                            result = LC_FAILURE;
                        }
                    }

                    if (LC_SUCCESS == result)
                    {
                        pRead += bytesPerRead;
                        bytesToRead -= bytesPerRead;
                        off += bytesPerRead;
                    }

                } while ((bytesToRead > 0) && (LC_SUCCESS == result));

                if (LC_SUCCESS == result)
                {
                    break;
                }
                else
                {
                    retry--;
                }

            }

            if (0 == retry)
            {
                result = LC_FAILURE;
               // ERR_REPORT_SetErrorCode(ERROR_CODE_UART_TIMEOUT);
            }
        }

        return result;
    }
    else
    {
        UART_INTERFACE_DEBUG("%s    %s get ird_boostrap_flag invalid\n", __FILE__ ,__FUNCTION__);
        return LC_FAILURE;
    }
}

static lc_result LC_CheckUartConnection(void)
{
    lc_result result = LC_SUCCESS;

    result = LC_TemuStart();
    return result;
}




