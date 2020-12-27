#include "stm32f4xx.h"                  // Device header

void sysTickDelayMs(int n);
void EXTI15_10_IRQHandler(void);	

int main(void)
{
	__disable_irq();											// disable interrupts
	RCC->AHB1ENR |= 1; 										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA
	GPIOA->MODER |= 0x400; 								// 0000 0000 0000 0000 0000 0000 0100 0000 set PA5 as output
	
	RCC->AHB1ENR |= 4;										// 0000 0000 0000 0000 0000 0000 0000 0100 enable clock for PC
	GPIOC->MODER |= 0;										// 0000 0000 0000 0000 0000 0000 0000 0000 set PC13 as input
	
	RCC->APB2ENR |= 0x4000; 							// 0000 0000 0000 0000 0100 0000 0000 0000 enable clock for system config
	
	SYSCFG->EXTICR[3] = 0x0020;						// 0000 0000 0000 0000 0000 0000 0010 0000 select port C for EXTI13
	
	EXTI->IMR |= 0x2000;									// 0000 0000 0000 0000 0010 0000 0000 0000 unmask EXTI13
	EXTI->FTSR |= 0x2000;									// 0000 0000 0000 0000 0010 0000 0000 0000 falling edge trigger enabled for EXTI13
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);       // enable external interrupts from EXTI10 to EXTI15
	
	__enable_irq();												// enable interrupts
	
	while(1)
	{
	}
}

void EXTI15_10_IRQHandler(void)					// occurs when falling edge is detected
{
	GPIOA->BSRR = 0x20;										// turn on LED
	sysTickDelayMs(100);
	GPIOA->BSRR = 0x200000;								// turn off LED
	sysTickDelayMs(100);
	
	EXTI->PR = 0x2000;										// 0000 0000 0000 0000 0010 0000 0000 0000 clear interrupt flag
}

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
