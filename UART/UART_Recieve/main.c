//USART2 recieve pin is PA3

#include "stm32f4xx.h"                  // Device header

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
		for(i=0;i<3195;i++);
}

void USART_Init(void)
{
	RCC->APB1ENR |= 0x20000; 					  // 0000 0000 0000 0010 0000 0000 0000 0000
  RCC->AHB1ENR |= 1;        			  	// 0000 0000 0000 0000 0000 0000 0000 0001 clock enabled for port A
	
	GPIOA->AFR[0] |= 0x7000;   				  // 0000 0000 0000 0000 0111 0000 0000 0000 Call altenate function register
	GPIOA->MODER |= 0x0080;  				    // 0000 0000 0000 0000 0000 0000 1000 0000 Set PA3 to alternate
				
	USART2->BRR = 0x008B;     			   	// 115200 baud rate at 16MHz
	
	USART2->CR1 = 0x0004;    				    // 0000 0000 0000 0000 0000 0000 0000 0100 Enable Rx
	USART2->CR1 |= 0x2000;   				    // 0000 0000 0000 0000 0010 0000 0000 0000 Enable USART
}

char USART_Read(void)
{
	while(!(USART2->SR & 0x0020))       // Wait until character arrives. Read Data register isnt empty
	{
		return USART2->DR;
	}
}

void LED_play(int value)
{
	value %=16;
	
	for (;value>0;value--)
	{
		GPIOA->BSRR = 0x20;                // Turn on LED
		delayMs(100);
		GPIOA->BSRR = 0x200000;               // Turn off LED
		delayMs(100);
	}
}

int main(void)
{
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
	
	USART_Init();
	char ch;
	
	while(1)
	{
		ch = USART_Read();
		LED_play(ch);
	}
}
