#include "stm32f4xx.h"                  // Device header

int main(void)
{
	RCC->AHB1ENR |= 1; 										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA5
	GPIOA->MODER |= 0x800;								// 0000 0000 0000 0000 0000 1000 0000 0000 set PA5 as alternate function
	GPIOA->AFR[0] |= 0x100000; 						// 0000 0000 0001 0000 0000 0000 0000 0000 set PA5 to AF1

	RCC->APB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for TIM2
	TIM2->PSC = 10 - 1;										// divide the clock frequency by 10
	TIM2->ARR = 26667 - 1;								// divide the clock frequency by 26667
	TIM2->CNT = 0;												// clear the count register
	TIM2->CCMR1 = 0x0060;									// 0000 0000 0000 0000 0000 0000 0110 0000 enable PWM mode
	TIM2->CCER = 1;												// enable PWM channel 1
	TIM2->CCR1 = 8889-1;									// set pulse width to 1/3rd period
	TIM2->CR1 = 1;												// enable timer
	
	while(1)
	{
	}
}
