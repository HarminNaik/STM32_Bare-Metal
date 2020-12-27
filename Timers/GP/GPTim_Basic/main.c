//TIM2 on APB1
//1Hz clock

#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |= 1; 										// 0000 0000 0000 0000 0000 0000 0000 0001 Enable clock for LED
	GPIOA->MODER |= 0x400;								// 0000 0000 0000 0000 0000 0100 0000 0000 PA5 as output
	
	//TIM2 configuration
	RCC->APB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 Enable clock for TIM2
	TIM2->PSC = 1600 - 1;                 // 16 000 000 divide by 1600 to get 10000 cycles
	TIM2->ARR = 10000 - 1;                // 10 000 divide by 10000 to get 1 Hz
	TIM2->CNT = 0; 												// Timer counter cleared
	TIM2->CR1 = 1; 												// Timer on
	
	while(1)
	{
		while(TIM2->SR & 1)
		{
			TIM2->SR &= ~1;                   // Clear Flag
			GPIOA->ODR ^= 0x20;
		}
	}
}
