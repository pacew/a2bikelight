/*
 * using stm8l151k4
 * "medium density"
 * 16k flash
 * 1k eeprom
 * 2k ram
 * 1 basic 8 bit timer
 * 2 general purpose 16 bit timers
 * 1 advanced control 16 bit timer
 * 1 spi
 * 1 i2c
 * 1 usart
 */



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

#define GPIO_BASE(port) (0x5000 + 5 * ((port) - 'A'))

#define GPIO_MASK(bitnum) (1 << (bitnum))

#define GPIO_ODR(port) (*(volatile uint8_t *)(GPIO_BASE(port) + 0))
#define GPIO_IDR(port) (*(volatile uint8_t *)(GPIO_BASE(port) + 1))
#define GPIO_DDR(port) (*(volatile uint8_t *)(GPIO_BASE(port) + 2))
#define GPIO_CR1(port) (*(volatile uint8_t *)(GPIO_BASE(port) + 3))
#define GPIO_CR2(port) (*(volatile uint8_t *)(GPIO_BASE(port) + 4))

#define GPIO_SET(port, bitnum) (GPIO_ODR(port) |= GPIO_MASK(bitnum))
#define GPIO_CLEAR(port, bitnum) (GPIO_ODR(port) &= ~GPIO_MASK(bitnum))


/*
 * STM8L151K4U6TR
 * UFQFPN-32(5x5)
 * use table 5, Medium density STM8L151x4/6, 2nd column "LQFP32/UFQFPN32"
 */

/* D3 on pin 12. functions: PD3/TIM1_ETR/LCD_SEG9/ADC1_IN19/COMP1_INP */
#define LIGHT_PORT 'D'
#define LIGHT_BITNUM 3

/* D4 on pin 21. functions: PD4/TIM1_CH2/LCD_SEG18/ADC1_IN10/COMP1_INP */
#define PWM_PORT 'D'
#define PWM_BITNUM 4

#define TIM1_CR1 (*(volatile uint8_t *)0x52b0)
#define TIM1_CR2 (*(volatile uint8_t *)0x52b1)
#define TIM1_SMCR (*(volatile uint8_t *)0x52b2)
#define TIM1_ETR (*(volatile uint8_t *)0x52b3)
#define TIM1_DER (*(volatile uint8_t *)0x52b4)
#define TIM1_IER (*(volatile uint8_t *)0x52b5)
#define TIM1_SR1 (*(volatile uint8_t *)0x52b6)
#define TIM1_SR2 (*(volatile uint8_t *)0x52b7)
#define TIM1_EGR (*(volatile uint8_t *)0x52b8)
#define TIM1_CCMR1 (*(volatile uint8_t *)0x52b9)
#define TIM1_CCMR2 (*(volatile uint8_t *)0x52ba)
#define TIM1_CCMR3 (*(volatile uint8_t *)0x52bb)
#define TIM1_CCMR4 (*(volatile uint8_t *)0x52bc)
#define TIM1_CCER1 (*(volatile uint8_t *)0x52bd)
#define TIM1_CCER2 (*(volatile uint8_t *)0x52be)
#define TIM1_CNTRH (*(volatile uint8_t *)0x52bf)
#define TIM1_CNTRL (*(volatile uint8_t *)0x52c0)
#define TIM1_PSCRH (*(volatile uint8_t *)0x52c1)
#define TIM1_PSCRL (*(volatile uint8_t *)0x52c2)
#define TIM1_ARRH (*(volatile uint8_t *)0x52c3)
#define TIM1_ARRL (*(volatile uint8_t *)0x52c4)
#define TIM1_RCR (*(volatile uint8_t *)0x52c5)
#define TIM1_CCR1H (*(volatile uint8_t *)0x52c6)
#define TIM1_CCR1L (*(volatile uint8_t *)0x52c7)
#define TIM1_CCR2H (*(volatile uint8_t *)0x52c8)
#define TIM1_CCR2L (*(volatile uint8_t *)0x52c9)
#define TIM1_CCR3H (*(volatile uint8_t *)0x52ca)
#define TIM1_CCR3L (*(volatile uint8_t *)0x52cb)
#define TIM1_CCR4H (*(volatile uint8_t *)0x52cc)
#define TIM1_CCR4L (*(volatile uint8_t *)0x52cd)
#define TIM1_BKR (*(volatile uint8_t *)0x52ce)
#define TIM1_DTR (*(volatile uint8_t *)0x52cf)
#define TIM1_OISR (*(volatile uint8_t *)0x52d0)
#define TIM_DCR1 (*(volatile uint8_t *)0x52d1)
#define TIM1_DCR2 (*(volatile uint8_t *)0x52d2)
#define TIM1_DMA1R (*(volatile uint8_t *)0x52d3)

void
gpio_init_output (uint8_t port, uint8_t bitnum)
{
	GPIO_DDR(port) |= GPIO_MASK(bitnum); // output
	GPIO_CR1(port) |= GPIO_MASK(bitnum); // push-pull
	GPIO_CR2(port) &= ~GPIO_MASK(bitnum); // low speed (up to 2 MHz)
}

unsigned int
clock(void)
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

void blink (void);
void pwm (void);

void
main(void)
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

	gpio_init_output (LIGHT_PORT, LIGHT_BITNUM);

	pwm ();
}

void
blink (void)
{
	int val = 0;
	while (1) {
		GPIO_CLEAR(LIGHT_PORT, LIGHT_BITNUM); // off
		GPIO_CLEAR(PWM_PORT, PWM_BITNUM); // off
		delay (400);
		GPIO_SET(LIGHT_PORT, LIGHT_BITNUM); // on
		GPIO_SET(PWM_PORT, PWM_BITNUM); // on
		delay (100);
		val++;
		printf ("hello %d\n", val);
	}
}

void
pwm (void)
{
	gpio_init_output (PWM_PORT, PWM_BITNUM);
	GPIO_SET(PWM_PORT, PWM_BITNUM); // on


/*
Up-counting is active when the DIR bit in the TIM1_CR1 register is
low.  Example This example uses PWM mode 1. The reference PWM signal,
OCiREF, is high as long as TIM1_CNT < TIM1_CCRi. Otherwise, it becomes
low. If the compare value in TIM1_CCRi is greater than the auto-reload
value (in TIM1_ARR) then OCiREF is held at 1. If the compare value is
0, OCiREF is held at 0. Figure 106 shows some edge-aligned PWM
waveforms in an example where TIM1_ARR = 8.
*/
	
	TIM1_CCMR2 = (TIM1_CCMR2 & ~0x70) | 0x60; /* OC2M: PWM mode 1 */
	TIM1_CCER2 |= 1; /* CC2E */
	// want MOE=1 CC1E=1 CC1NE=0

	int prescale = 60000;
	TIM1_PSCRH = prescale >> 8;
	TIM1_PSCRL = prescale & 0xff;

	int reload = 1000;
	TIM1_ARRH = reload >> 8;
	TIM1_ARRL = reload & 0xff;

	int compare = 20000;
	TIM1_CCR2H = compare >> 8;
	TIM1_CCR2L = compare & 0xff;

	TIM1_BKR |= 0x80; /* MOE = 1 */

	TIM1_CR1 |= 1; /* CEN counter enable */

	int val = 0;
	int last = 0;
	while (1) {
		val++;
		uint8_t hi = TIM1_CNTRH;
		uint8_t lo = TIM1_CNTRL;
		uint16_t count = (hi << 8) | lo;

		printf ("hello %d %5d %6d\n", val, count, count - last);
		last = count;
	}

}
