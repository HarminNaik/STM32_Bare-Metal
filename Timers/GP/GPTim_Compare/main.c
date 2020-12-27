#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |= 1; 										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for port A
	GPIOA->MODER |= 0x800;								// 0000 0000 0000 0000 0000 1000 0000 0000 configure PA5 as Alternate Function
	GPIOA->AFR[0]  |=	0x100000;						// 0000 0000 0001 0000 0000 0000 0000 0000 configure PA5 as AF1
	
	RCC->APB1ENR |= 1; 										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for TIM2
  TIM2->PSC = 1600-1;
	TIM2->ARR = 10000-1;
	TIM2->CCMR1 = 0x30; 									// Set output to toggle whel TIM2_CNT = TIM2_CCR1
	TIM2->CCR1 = 0;
	TIM2->CCER |= 1; 											// Set CH1 of TIM2 to compare mode
	
	TIM2->CNT = 0;												// Set counter to zero
	TIM2->CR1 = 1;												// Enable counter
	
	while(1)
	{
	}
}
