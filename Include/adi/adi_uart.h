
#ifndef _ADI_UART_H_
#define _ADI_UART_H_

#include "adi_typedef.h"
#include "adi_error.h"

#ifdef  __cplusplus
extern "C" {
#endif

/*UART��ش������ֵ*/
enum
{
	ADIUART_ERROR_BAD_PARAMETER = ADI_UART_ERROR_BASE,	// ��������
	ADIUART_ERROR_FEATURE_NOT_SUPPORTED,				// ������֧�� 
	ADIUART_ERROR_TIMEOUT                               // ��ʱ
};

/*��żУ������ö��ֵ */
typedef enum {
	EM_UDIURART_PARITY_NONE,		// ��У��
	EM_UDIURART_PARITY_EVEN,		// ż��У��
	EM_UDIURART_PARITY_ODD,			// ����У��
	EM_UDIURART_PARITY_NUM
} ADIUartParity_E;

//reference termios.h
typedef struct ADIUartTermios  
{  
	unsigned long c_iflag;  // ����ģʽ��־  
	unsigned long c_oflag;  // ���ģʽ��־  
	unsigned long c_cflag;  // ����ģʽ��־  
	unsigned long c_lflag;  // ����ģʽ��־  
	unsigned char c_line;   // ��·��̣����ʣ�  
	unsigned char c_cc[17];  // �����ַ�����  NCCS 17
}ADIUartTermios_S;  


/*�������Խṹ*/
typedef struct
{
	int m_nBaudrate;		        // ������,��������115200,38400 ��
	int m_nDataBits;		        // ����λ,������5,6,7,8 �������
	int m_nStopBits;		        // ֹͣλ,������1, 1.5,2 �������
	ADIUartParity_E m_eParity;		// ��żУ��,���ADIUartParity_E����
	ADI_BOOL m_bCmdMode;             // ����������ģʽ���������������
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

