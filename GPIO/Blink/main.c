//PA5. LED is connected to PA5
//AHB1. PA5 is connected to AHB1
//RCC->AHB1ENR. To enable clock of ports on AHB1
//GPIOx_MODER
//GPIOx_ODR

#include "stm32f4xx.h"                  // Device header

void delayMs (int delay)
{
	int i;
	for(;delay>0;delay--)
		for(i=0;i<3195;i++);
}

int main(void)
{
	RCC->AHB1ENR |= 1;   						 //Clock enabled for GPIOA  0000 0000 0000 0000 0000 0000 0000 0001. | is for friendly programming
	
	GPIOA->MODER |= 0x400;  				 // 0000 0000 0000 0000 0000 0100 0000 0000
	
	while(1)
	{
		GPIOA->ODR = 0x20;						 // 0000 0000 0000 0000 0000 0000 0010 0000
		delayMs(100);
		GPIOA->ODR = 0x00;
		delayMs(100);
	}
}
