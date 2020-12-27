//PA5
//RCC->AHB1ENR
//GPIOA->MODER
//GPIOA->BSRR

#include "stm32f4xx.h"                  // Device header

void delayMs(int delay)
{
	int i;
	for(;delay>0;delay--)
		for(i=0;i<3195;i++);
}
int main(void)
{
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;				 // 0000 0000 0000 0000 0000 0100 0000 0000
	
	while(1)
	{
		GPIOA->BSRR = 0x20;					 // 0000 0000 0000 0000 0000 0000 0010 0000
		delayMs(100);
		GPIOA->BSRR = 0x200000;      // 0000 0000 0010 0000 0000 0000 0000 0000
		delayMs(100);
	}
}
