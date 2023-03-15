// Source code under CC0 1.0
#include <stdint.h>
#include <stdio.h>

#define PC_ODR	(*(volatile uint8_t *)0x500a)
#define PC_DDR	(*(volatile uint8_t *)0x500c)
#define PC_CR1	(*(volatile uint8_t *)0x500d)

#define PD_ODR	(*(volatile uint8_t *)0x500f)
#define PD_DDR	(*(volatile uint8_t *)0x5011)
#define PD_CR1	(*(volatile uint8_t *)0x5012)

#define PE_ODR	(*(volatile uint8_t *)0x5014)
#define PE_DDR	(*(volatile uint8_t *)0x5016)
#define PE_CR1	(*(volatile uint8_t *)0x5017)

#define CLK_DIVR	(*(volatile uint8_t *)0x50c0)
#define CLK_PCKENR1	(*(volatile uint8_t *)0x50c3)
#define CLK_PCKENR2	(*(volatile uint8_t *)0x50c4)

#define TIM1_CR1	(*(volatile uint8_t *)0x52b0)
#define TIM1_PCNTRH	(*(volatile uint8_t *)0x52bf)
#define TIM1_PCNTRL	(*(volatile uint8_t *)0x52c0)
#define TIM1_PSCRH	(*(volatile uint8_t *)0x52c1)
#define TIM1_PSCRL	(*(volatile uint8_t *)0x52c2)

#define USART1_SR (*(volatile uint8_t *)0x5230) // USART1 status register
#define USART1_DR (*(volatile uint8_t *)0x5231) // USART1 data register
#define USART1_BRR1 (*(volatile uint8_t *)0x5232) // USART1 baud rate register 1
#define USART1_BRR2 (*(volatile uint8_t *)0x5233) // USART1 baud rate register 2
#define USART1_CR1 (*(volatile uint8_t *)0x5234) // USART1 control register 1
#define USART1_CR2 (*(volatile uint8_t *)0x5235) // USART1 control register 2
#define USART1_CR3 (*(volatile uint8_t *)0x5236) // USART1 control register 3
#define USART1_CR4 (*(volatile uint8_t *)0x5237) // USART1 control register 4
#define USART1_CR5 (*(volatile uint8_t *)0x5238) // USART1 control register 5
#define USART1_GTR (*(volatile uint8_t *)0x5239) // USART1 guard time register
#define USART1_PSCR (*(volatile uint8_t *)0x523A) // USART1 prescaler register

unsigned int clock(void)
{
	unsigned char h = TIM1_PCNTRH;
	unsigned char l = TIM1_PCNTRL;
	return((unsigned int)(h) << 8 | l);
}

int
putchar (int c)
{
	if (c == '\n') {
		while ((USART1_SR & 0x80) == 0) // TXE Transmit data empty
			;
		USART1_DR = '\r';
	}
	while ((USART1_SR & 0x80) == 0) // TXE Transmit data empty
		;
	USART1_DR = c;
	return (c);
}


void
delay(int count)
{
	unsigned int start, now, delta;

	start = clock();
	while (1) {
		now = clock();
		delta = now - start;
		if (delta >= count)
			break;
	}
}

void main(void)
{
	CLK_DIVR = 0x00; // Set the frequency to 16 MHz
	CLK_PCKENR2 |= 0x02; // Enable clock to timer

	// Configure timer
	// 1000 ticks per second
	TIM1_PSCRH = 0x3e;
	TIM1_PSCRL = 0x80;
	// Enable timer
	TIM1_CR1 = 0x01;

	/* 
	 * serial 
	 * incoming PC2, pin 27
	 * outgoing PC3, pin28
	 */
	CLK_PCKENR1 |= 0x20; // Enable clock to usart1

	/* adafruit: white is data to usb; green is data from usb */
	/* 16MHz, 9600 bit/s USART_DIV  0x0683 */
	USART1_BRR1 = 0x68;
	USART1_BRR2 = 0x3;

	USART1_CR2 |= 0x0c; // transmitter enable + receiver enable


	// Configure pins
	PD_DDR = 0x08;
	PD_CR1 = 0x08;

	int val = 0;
	for(;;)
	{
		PD_ODR &= 0xf7;
		delay (300);
		PD_ODR |= 0x08;
		delay (100);
		val++;
		printf ("hello %d\n", val);

	}
}
