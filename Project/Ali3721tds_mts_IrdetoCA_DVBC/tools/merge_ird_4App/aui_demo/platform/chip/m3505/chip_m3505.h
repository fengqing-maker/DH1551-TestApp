#ifndef _CHIP_S3505_H_
#define _CHIP_S3505_H_

#define GPIO_REG                    0xb8000430  //gpio0 ~ gpio31
#define GPIOA_REG                   0xb8000434  //gpio32 ~ gpio63
#define GPIOB_REG                   0xb8000438  //gpio64 ~ gpio95
#define GPIOC_REG                   0xb800043c  //gpio96 ~ gpio127
#define GPIOD_REG                   0xb8000440  //gpio128 ~ gpio136

#define PIM_MUX_BASE                0xb8000000
#define PIN_MUX_REG_MASK            0xfff00000
#define PIN_MUX_REG_SHIFT           20
#define PIN_BIT_HEIGHT_MASK         0x0000ff00
#define PIN_BIT_LOW_MASK            0x000000ff
#define PIN_BIT_HEIGHT_SHIFT        8
#define PIN_BIT_LOW_SHIFT           0

#define PIN_MUX_CTRL                (0x488 << PIN_MUX_REG_SHIFT)
#define PIN_MUX_CTRL1               (0x48C << PIN_MUX_REG_SHIFT)
#define PIN_MUX_CTRL2               (0x490 << PIN_MUX_REG_SHIFT)
#define PIN_MUX_CTRL3               (0x494 << PIN_MUX_REG_SHIFT)

//#define PIN_MUX_CTRL                (0xa8 << PIN_MUX_REG_SHIFT)
//#define PIN_MUX_CTRL1               (0xac << PIN_MUX_REG_SHIFT)

// Reg addr | reserved | end bit:bit_num<<8(bit8~15) | start bit:bit_num<<0(bit0~7)

#define EPHY_LED1_SEL				(PIN_MUX_CTRL | 29)
#define XNF_DQS_SEL			        (PIN_MUX_CTRL | 24)
#define XDISEQC_IN_SEL2				(PIN_MUX_CTRL | 21)
#define XSC_SEL3				    (PIN_MUX_CTRL | 20)
#define XSC_SEL2				    (PIN_MUX_CTRL | 19)
#define XI2C2_SEL				    (PIN_MUX_CTRL | 18)
#define XIF_AGC_QAM_SEL				(PIN_MUX_CTRL | 17)
#define XI2C_SEL4				    (PIN_MUX_CTRL | 16)
#define XTUN_AGC_QAM_SEL		    (PIN_MUX_CTRL | 15)
#define XDISEQC_IN_SEL		        (PIN_MUX_CTRL | 14)
#define XDISEQC_HV_SEL2				(PIN_MUX_CTRL | 12)
#define XDISEQC_HV_SEL1			    (PIN_MUX_CTRL | 11)
#define XDISEQC_OUT_SEL				(PIN_MUX_CTRL | 10)
#define XIF_AGC_S2_SEL				(PIN_MUX_CTRL | 9)
#define XUART2_RX_SEL				(PIN_MUX_CTRL | 7)
#define XUART2_TX_SEL				(PIN_MUX_CTRL | 6)
#define	XI2C_SEL					(PIN_MUX_CTRL | 5)
#define XHDMI_HTPG_SEL				(PIN_MUX_CTRL | 4)
#define XSC_SEL					    (PIN_MUX_CTRL | 3)
#define XUART_TX_SEL				(PIN_MUX_CTRL | 2)
#define XUART_RX_SEL				(PIN_MUX_CTRL | 1)
#define XSPDIF_SEL				    (PIN_MUX_CTRL | 0)


#define ASSI3_SEL2				    (PIN_MUX_CTRL1 | 31)
#define NF_SMREJ_TST_SEL			(PIN_MUX_CTRL1 | 22)
#define EPHY_LED0_SEL	            (PIN_MUX_CTRL1 | 21)
#define XDISEQC_HV_BGA_SEL			(PIN_MUX_CTRL1 | 20)
#define XDISEQC_IN_BGA_SEL			(PIN_MUX_CTRL1 | 19)
#define XIF_AGC_QAM2_SEL			(PIN_MUX_CTRL1 | 18)
#define XPMU_UART_SEL				(PIN_MUX_CTRL1 | 17)
#define ASSI4_SEL2			        (PIN_MUX_CTRL1 | 16)
#define ASSI4_DATA1_SEL			    (PIN_MUX_CTRL1 | 15)
#define SSO_SEL			            (PIN_MUX_CTRL1 | 14)
#define SSO_ERR_SEL					(PIN_MUX_CTRL1 | 13)
#define ASSI4_SEL					(PIN_MUX_CTRL1 | 12)
#define ASSI3_DATA1_SEL				(PIN_MUX_CTRL1 | 10)
#define ASSI3_SEL					(PIN_MUX_CTRL1 | 9)
#define ASSI3_ERR_SEL				(PIN_MUX_CTRL1 | 8)
#define ASS2_DATA1_SEL				(PIN_MUX_CTRL1 | 7)
#define ASSI2_SEL					(PIN_MUX_CTRL1 | 6)
#define ASSI2_ERR_SEL			    (PIN_MUX_CTRL1 | 5)
#define ASSI_DATA1_SEL		        (PIN_MUX_CTRL1 | 4)
#define ASSI_SEL			        (PIN_MUX_CTRL1 | 3)
#define ASSI_ERR_SEL			    (PIN_MUX_CTRL1 | 2)
#define SPI_SEL					    (PIN_MUX_CTRL1 | 1)
#define SPI_ERR_SEL					(PIN_MUX_CTRL1 | 0)


#define SFLASH_NANDFLASH_PINMUX_SEL					(PIN_MUX_CTRL2 | 10)
#define XNF_SEL					                    (PIN_MUX_CTRL2 | 9)
#define XSF_BGA_SEL					                (PIN_MUX_CTRL2 | 8)
#define XCI_SEL			                            (PIN_MUX_CTRL2 | 5)
#define XNF_WPJ_SEL		                            (PIN_MUX_CTRL2 | 4)
#define XSF_HOLDJ_SEL			                    (PIN_MUX_CTRL2 | 3)
#define XSF_WJ_SEL			                        (PIN_MUX_CTRL2 | 2)
#define XSF_CS1_BGA_SEL					            (PIN_MUX_CTRL2 | 1)
#define XSF_CS0_BGA_SEL					            (PIN_MUX_CTRL2 | 0)



#define TEST_IP_SEL				    (PIN_MUX_CTRL3 | (31<<8) | 28)
#define XI2SO_DATA3_SEL2			(PIN_MUX_CTRL3 | 27)
#define XI2SO_DATA2_SEL2			(PIN_MUX_CTRL3 | 26)
#define XI2SO_DATA1_SEL2			(PIN_MUX_CTRL3 | 25)
#define HDMI_TEST_FUNTION_SEL		(PIN_MUX_CTRL3 | 24)
#define XI2S1_SEL				    (PIN_MUX_CTRL3 | 23)
#define XI2S_SEL			        (PIN_MUX_CTRL3 | 22)
#define XI2SO_DATA1_SEL	            (PIN_MUX_CTRL3 | 21)
#define XI2SO_SEL				    (PIN_MUX_CTRL3 | 20)
#define XI2SO_DATA3_SEL				(PIN_MUX_CTRL3 | 19)
#define XI2SO_DATA2_SEL				(PIN_MUX_CTRL3 | 18)
#define XPMU_DOCD_SEL				(PIN_MUX_CTRL3 | 17)
#define TVENC_SYNC_SEL				(PIN_MUX_CTRL3 | 13)
#define XSPDIF_IN_SEL				(PIN_MUX_CTRL3 | 12)
#define XSPDIF_TEXT_SEL				(PIN_MUX_CTRL3 | 11)
#define VIN_SE					    (PIN_MUX_CTRL3 | 8)
#define USB_TEST_SEL				(PIN_MUX_CTRL3 | 1)
#define TEST_OUT_SEL				(PIN_MUX_CTRL3 | 0)




#endif

















