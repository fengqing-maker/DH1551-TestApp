������ӵ�DDR��ʼ���ļ����������š��������ַ���Ĭ�ϵ�cigwin�ڱ����ʱ��ᱨ��������makefile
�ű��������ЩDDR��ʼ���ļ���ʱ����Ҫ����Щ�����ַ�����ת�壬����ʹ�á�\������ת�塣���磺

�޸�Make3505,�������£�
ifdef _BOARD_DB_M3526_01V01_
	BOOTLOADER_MA_RT = bloader3_3526${CPU_EN}${LOGO_EN}.abs
	MEM_INIT_FILE = C3505_DB_LQFP_128_1866Mbps\(CL13\,\ CWL9\)_128M.txt
else
	ifdef _BOARD_DB_M3626_01V01_
		BOOTLOADER_MA_RT = bloader3_3626${CPU_EN}${LOGO_EN}.abs
		MEM_INIT_FILE = C3505_DB_LQFP_128_1866Mbps\(CL13\,\ CWL9\)_128M.txt
	else
			ifdef _BOARD_DB_M3527_01V01_
				BOOTLOADER_MA_RT = bloader3_3527${CPU_EN}${LOGO_EN}.abs
			else
			  ifdef _BOARD_DB_M3627_01V01_
			  	BOOTLOADER_MA_RT = bloader3_3627${CPU_EN}${LOGO_EN}.abs
			  	MEM_INIT_FILE = C3505_DB_BGA_DB_BGA_1866Mbps\(CL13\,\ CWL9\)_128M.txt
			  else			  
				  ifdef _BOARD_DB_M3727_01V01_
				  	BOOTLOADER_MA_RT = bloader3_3527${CPU_EN}${LOGO_EN}.abs
				  else
						ifdef _BOARD_SB_M3527_01V01_
							BOOTLOADER_MA_RT = bloader3_3527${CPU_EN}${LOGO_EN}.abs
							MEM_INIT_FILE = C3505_SB_BGA_SB_1066Mbps\(CL7\,\ CWL6\)_256M.txt
						else
							BOOTLOADER_MA_RT = bloader3_3526${CPU_EN}${LOGO_EN}.abs
							MEM_INIT_FILE = C3505_SB_SB_LQFP_128_800Mbps\(CL6\,\ CWL5\)_128M.txt
						endif	  
				  endif 
			  endif	
			endif
	endif
endif		

