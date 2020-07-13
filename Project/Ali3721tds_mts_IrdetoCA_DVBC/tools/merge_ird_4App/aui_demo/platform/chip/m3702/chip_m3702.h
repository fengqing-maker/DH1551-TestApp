#ifndef _CHIP_M3702_H_
#define _CHIP_M3702_H_

/*Add for gpio setting.*/
#define GPIO_LA_REG (0xB808D000)
#define GPIO_BA_REG (0xB808D100)
#define GPIO_BB_REG (0xB808D120)
#define GPIO_BC_REG (0xB808D140)
#define GPIO_RA_REG (0xB808D200)
#define GPIO_TA_REG (0xB808D300)
#define GPIO_TB_REG (0xB808D320)

/*Add for pinmux setting.*/
#define PMX_IO_BASE		0xb8080000
#define PMX_GPIO_LA_BASE	0xb808b000
#define PMX_GPIO_BA_BASE	0xb808b400
#define PMX_GPIO_BB_BASE	0xb808b480
#define PMX_GPIO_BC_BASE	0xb808b500
#define PMX_GPIO_RA_BASE	0xb808b800
#define PMX_GPIO_TA_BASE	0xb808bc00
#define PMX_GPIO_TB_BASE	0xb808bc80

#define PMX_PIN_SET(base, number, value) 	(*(volatile long *)(((long)base) + sizeof (long) * number) = value)
#define PMX_PIN_GET(base, number) 		(*(volatile long *)(((long)base) + sizeof (long) * number))

#define PMX_PIN_SEL(base, number, sel) do {		\
		long value = PMX_PIN_GET(base, number);	\
		value = (value & (~((long)0xf))) | sel;	\
		PMX_PIN_SET(base, number, value);	\
	} while (0)

// Pinmux register low 4 bits
#define PMX_PIN_SEL_GPIO		0x0000
#define PMX_PIN_SEL_I2C			0x0001
#define PMX_PIN_SEL_RMII_TXD		0x0001
#define PMX_PIN_SEL_RMII_TX_EN		0x0001
#define PMX_PIN_SEL_ASSI2			0x0003
#define PMX_PIN_SEL_ASSI3			0x0003

// More Pin sel define here
#define PMX_PIN_SEL_ASSI1			0x0003
#define PMX_PIN_SEL_XSPI			0x0004
//...

#endif

