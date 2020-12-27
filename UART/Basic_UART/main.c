//APB1 :USART 2
//RCC_APB1ENR bit 17 : for clock
//USART_CR1
//USART is on PA2
//USART_DR


#include "stm32f4xx.h"                  // Device header

void USART_Init(void);
void USART_Write(int ch);
void delayMs(int delay);

int main(void)
{
	USART_Init();
	
	while(1)
	{
		USART_Write('H');
		USART_Write('i');
		delayMs(10);
	}
}

void USART_Init(void)
{
	RCC->APB1ENR |= 0x20000; 					  // 0000 0000 0000 0010 0000 0000 0000 0000
  RCC->AHB1ENR |= 1;        			  	// clock enabled for port A
	
	GPIOA->AFR[0] = 0x0700;   				  // Call altenate function register
	GPIOA->MODER |= 0x0020;  				    // Set PA2 to alternate
				
	USART2->BRR = 0x0683;     			   	// 9600 baud rate at 16MHz
	
	USART2->CR1 = 0x0008;    				    // Enable Tx
	USART2->CR1 |= 0x2000;   				    // Enable USART
}

void USART_Write(int ch)
{
	while(!(USART2->SR & 0x0080))				//Checks TX Buffer. Code will stop if TX Buffer is empty  
		USART2->DR = (ch & 0xFF);         //Transmits the passed data
}

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
		for(i=0;i<3195;i++);
}
