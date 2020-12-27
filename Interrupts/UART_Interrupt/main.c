#include "stm32f4xx.h"                  // Device header

void UART_Init_Recieve(void)
{
	RCC->AHB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA
	RCC->APB1ENR |= 0x20000;							// 0000 0000 0000 0010 0000 0000 0000 0000 enable clock for USART2
	
	GPIOA->MODER |= 0x80;									// 0000 0000 0000 0000 0000 0000 0010 0000 set PA3 as alternate function
	GPIOA->AFR[0] |= 0x7000;							// 0000 0000 0000 0000 0000 0111 0000 0000 set PA3 as AF7
	
	USART2->BRR = 0x08B;									// set baud rate as 115200
	USART2->CR1 = 4;											// 0000 0000 0000 0000 0000 0000 0000 0100 enable reciever

	USART2->CR1 = 0x2000;									// 0000 0000 0000 0000 0010 0000 0000 0000 enable UART2
	
}

void delayMs(int n)
{
	SysTick->LOAD = 16000; 								// no. of clock cycles in 1ms at 16MHz
	SysTick->VAL = 0;      								// Clear current value register
	SysTick->CTRL = 0x5;   								// Enable SysTick
	
	for(int i=0; i<n; i++)
	{
		while((SysTick->CTRL & 0x10000) == 0);     // Wait until the COUNT flag is set
	}
	
	SysTick->CTRL = 0;
}


void LED_play(int value)
{
	value %=16;
	
	for (;value>0;value--)
	{
		GPIOA->BSRR = 0x20;                // Turn on LED
		delayMs(100);
		GPIOA->BSRR = 0x200000;            // Turn off LED
		delayMs(100);
	}
}

void USART2_IRQHandler(void)
{
	char c;
	if (USART2->SR & 0x0020)							// when USART is recieved
	{
		c = USART2->DR;
		LED_play(c);
	}
}

int main(void)
{
	__disable_irq();											// disable global interrupt
	
	RCC->AHB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA
	GPIOA->MODER |= 0x400;								// 0000 0000 0000 0000 0000 0100 0000 0000 set PA5 as output
	
	UART_Init_Recieve();
	USART2->CR1 |= 0x20;									// 0000 0000 0000 0000 0000 0000 0010 0000 enable RX interrupt
	
	NVIC_EnableIRQ(USART2_IRQn);					// enable USART2 interrupt handler
	
	__enable_irq();												// enable global interrupts
	
	while(1)
	{
	}
}
