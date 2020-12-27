#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |=1;
	GPIOA->MODER |=0x400;
	
	//configuring sysTick to generate 200ms delay
	
	SysTick->LOAD = 3200000 - 1;         // Loads the value
	SysTick->VAL = 0;                    // Initial value
	SysTick->CTRL = 5;                   // Timer on
	
	while(1)
	{
		if(SysTick->CTRL & 0x10000)         //Check the control flag. Turs 1 when timer ends
		{
			GPIOA->ODR ^= 0x20; 
		}
	}
}