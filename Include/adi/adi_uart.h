
#ifndef _ADI_UART_H_
#define _ADI_UART_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*UART相关错误代码值*/
enum
{
	ADIUART_ERROR_BAD_PARAMETER = ADI_UART_ERROR_BASE,	// 参数错误
	ADIUART_ERROR_FEATURE_NOT_SUPPORTED,				// 操作不支持 
	ADIUART_ERROR_TIMEOUT                               // 超时
};

/*奇偶校验属性枚举值 */
typedef enum {
	EM_UDIURART_PARITY_NONE,		// 不校验
	EM_UDIURART_PARITY_EVEN,		// 偶数校验
	EM_UDIURART_PARITY_ODD,			// 奇数校验
	EM_UDIURART_PARITY_NUM
} ADIUartParity_E;

//reference termios.h
typedef struct ADIUartTermios  
{  
	unsigned long c_iflag;  // 输入模式标志  
	unsigned long c_oflag;  // 输出模式标志  
	unsigned long c_cflag;  // 控制模式标志  
	unsigned long c_lflag;  // 本地模式标志  
	unsigned char c_line;   // 线路规程（速率）  
	unsigned char c_cc[17];  // 控制字符数组  NCCS 17
}ADIUartTermios_S;  


/*串口属性结构*/
typedef struct
{
	int m_nBaudrate;		        // 波特率,常见的有115200,38400 等
	int m_nDataBits;		        // 数据位,常见的5,6,7,8 四种情况
	int m_nStopBits;		        // 停止位,常见的1, 1.5,2 三种情况
	ADIUartParity_E m_eParity;		// 奇偶校验,详见ADIUartParity_E定义
	ADI_BOOL m_bCmdMode;             // 类似命令行模式，输入输出被处理
	ADIUartTermios_S m_sTermios;    // not used, for extern 
}ADIUartAttribute_S;

ADI_Error_Code ADIUartGetCount(unsigned int* pdwUartDeviceCount);

ADI_Error_Code ADIUartInitial  ( int  nUartIndex, ADIUartAttribute_S *psUartAttribute);

ADI_Error_Code ADIUartSetAttribute(int nUartIndex, ADIUartAttribute_S *psUartAttribute);

int ADIUartRead(int nUartIndex ,unsigned char* pucBuffer, unsigned int uLength, int nTimeout);

int ADIUartWrite(int nUartIndex ,unsigned char* pucBuffer, unsigned int uLength, int nTimeout);

ADI_Error_Code ADIUartClear(int nUartIndex);


ADI_Error_Code ADIUartDisable(int nUartIndex, ADI_BOOL bDisable);



#ifdef  __cplusplus
}
#endif

#endif

