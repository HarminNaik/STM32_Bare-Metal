#include "stm32f4xx.h"                  // Device header

void sysTickDelayMs(int n)
{
	SysTick->LOAD = 16000; // no. of clock cycles in 1ms at 16MHz
	SysTick->VAL = 0;      // Clear current value register
	SysTick->CTRL = 0x5;   // Enable SysTick
	
	for(int i=0; i<n; i++)
	{
		while((SysTick->CTRL & 0x10000) == 0);     // Wait until the COUNT flag is set
	}
	
	SysTick->CTRL = 0;
}

int main(void)
{
	RCC->AHB1ENR |= 1;
	GPIOA->MODER |= 0x400;
	
	while(1)
	{
		sysTickDelayMs(50);
		GPIOA->ODR ^= 0x20;
	}
}