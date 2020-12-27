#include "stm32f4xx.h"                  // Device header

//PA5 will be output, and PA6 will be input, to capture

int timeStamp = 0;
int main(void)
{
	RCC->AHB1ENR |= 1;  									// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for port A
	GPIOA->MODER |= 0x800;								// 0000 0000 0000 0000 0000 0100 0000 0000 set PA5 as alternate function
	GPIOA->AFR[0] |= 0x100000;            // 0000 0000 0001 0000 0000 0000 0000 0000 set PA5 to AF1
	
	//TIM2 to 1Hz
	RCC->APB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for TIM2
	TIM2->PSC = 1600-1; 									// divide frequency of clock by 1600
	TIM2->ARR = 10000-1;									// divide frequency of clock by 10000
	TIM2->CCMR1 = 0x30; 									// output toggles when match value is met
	TIM2->CCR1 = 0;												// match value is set to 0
	TIM2->CCER = 1; 											// enable CH1 compare mode
	
	TIM2->CNT = 0;												// counter cleared
	TIM2->CR1 = 1;												// enable TIM2
	
	//TIM3 configuration
	
	RCC->AHB1ENR |= 1;  									// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for port A
	GPIOA->MODER |= 0x2000;								// 0000 0000 0000 0000 0010 0000 0000 0000 set PA6 as alternate
	GPIOA->AFR[0] |= 0x02000000;					// 0000 0010 0000 0000 0000 0000 0000 0000 set PA6 to AF2
	
	RCC->APB1ENR |= 2;										// 0000 0000 0000 0000 0000 0000 0000 0010 enable clock for TIM3
	TIM3->PSC = 16000-1;										// divide frequency of clock by 16000
	TIM3->CCMR1 = 0x41;										// set CH1 to capture at every edge
	TIM3->CCER = 1; 											// enable capture
	
	while(1)
	{
		while((TIM3->SR & 2))               // wait to capture an edge
		timeStamp = TIM3->CCR1;							// stores captured value in timeStamp
	}
}