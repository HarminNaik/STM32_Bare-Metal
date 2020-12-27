//LED at PA5
//PUSHBUTTON at PC13
//GPIOC_IDR has to be 0x 0010 0000 0000 0000, i.e 0x2000 when PC13 is high

#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |= 0x5;				 // 0000 0000 0000 0000 0000 0000 0000 0101
	GPIOA->MODER |= 0x400; 			 // 0000 0000 0000 0000 0000 0100 0000 0000
	
	while(1)
	{
		if(GPIOC->IDR & 0x2000)    //if PC13 is high, bitwise AND
		{
			GPIOA->ODR = 0x00;       // 0000 0000 0000 0000 0000 0000 0000 0000
		}
		else
		{
			GPIOA->ODR = 0x20;       // 0000 0000 0000 0000 0000 0000 0010 0000
		}
	}
}
 