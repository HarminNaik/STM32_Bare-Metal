#include "stm32f4xx.h"                 		 // Device header
		
int main(void)
{
	int last_value=0;
	int current_value=0;
	int period=0;
	float freq=0;
	
	RCC->AHB1ENR |= 1;												// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA5
	GPIOA->MODER |= 0x800; 										// 0000 0000 0000 0000 0000 1000 0000 0000 set PA5 as alternate function
	GPIOA->AFR[0] = 0x100000;									// 0000 0000 0001 0000 0000 0000 0000 0000 set PA5 to AF1

	RCC->APB1ENR = 1;													// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for TIM2
	TIM2->PSC = 1600-1; 											// divide the clock frequency by 1600
	TIM2->ARR = 10000-1;											// divide the clock frequency by 10000
	TIM2->CCMR1 = 0x30;												// set timer to toggle channel when TIM2_CNT = TIM2_CCR1
	TIM2->CCR1 = 0;														// match value is set to 0
	TIM2->CNT = 0;														// counter cleared
	TIM2->CR1 = 1;														// timer enabled
	
	//PA6 as input
	
	RCC->AHB1ENR |= 1;		
	GPIOA->MODER |= 0x2000;										// 0000 0000 0000 0000 0010 0000 0000 0000 set PA6 as alternate function
	GPIOA->AFR[0] |= 0x020000000; 						// 0000 0010 0000 0000 0000 0000 0000 0000 set PA6 to AF2
	
	// Read the toggle rate using TIM3
	RCC->APB1ENR |=2;													// 0000 0000 0000 0000 0000 00000 0000 0010 enable clock for TIM3
	TIM3->PSC = 16000-1; 											// divide the clock frequency by 16000
	TIM3->CCMR1 = 0x41;												// 0000 0000 0000 0000 0000 0000 0100 0001 
	TIM3->CCER = 0x0B;												// 0000 0000 0000 0000 0000 0000 0000 1011
	TIM3->CR1 = 1;		
	
	while(1)
	{
		while(!(TIM3->SR & 2))									// wait until edge is captured
		{
			current_value = TIM3->CCR1;
			period = current_value - last_value;
			last_value = current_value;
			freq= 1000.0f/period;
		}
	}
}
