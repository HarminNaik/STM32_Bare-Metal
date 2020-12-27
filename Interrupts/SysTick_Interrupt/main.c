#include "stm32f4xx.h"                  // Device header
// toggle LED whe SysTick timercompletes counting
int main(void)
{
	__disable_irq();											// disable all global interrupts
	
	RCC->AHB1ENR |= 1; 										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA
	GPIOA->MODER |= 0x400;								// 0000 0000 0000 0000 0000 0100 0000 0000 set PA5 as output
	
	SysTick->LOAD |= 16000000-1;					// 1 Hz at 16MHz
	SysTick->VAL |= 0;						
	SysTick->CTRL |= 7;										// enable SysTick
	
	__enable_irq();
	
	while(1)
	{
	}
}

void SysTick_Handler(void)
{
	GPIOA->ODR ^= 0x20;										// toggle LED
}
