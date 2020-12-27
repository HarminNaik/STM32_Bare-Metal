#include "stm32f4xx.h"                  // Device header

// 1Hz 

int main(void)
{
	__disable_irq();
	RCC->AHB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA
	GPIOA->MODER |= 0x400;								// 0000 0000 0000 0000 0000 0100 0000 0000 set PA5 as output

	RCC->APB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for TIM2
	TIM2->PSC = 16000-1;
	TIM2->ARR = 1000-1;
	TIM2->CR1 = 1;
	
	TIM2->DIER |= 1;											// update interrupt enable
	
	NVIC_EnableIRQ(TIM2_IRQn);
	
	__enable_irq();
	
	while(1)
	{
	}
}

void TIM2_IRQHandler(void)
{
	TIM2->SR = 0;
	
	GPIOA->ODR ^= 0x20;										// toggle LED
}
