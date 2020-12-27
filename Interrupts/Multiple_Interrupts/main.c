#include "stm32f4xx.h"                  // Device header

void sysTickDelayMs(int n);

int main(void)
{
	__disable_irq();											// disable all interrupts
	
	RCC->AHB1ENR |= 1; 										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA
	GPIOA->MODER |= 0x400;								// 0000 0000 0000 0000 0000 0100 0000 0000 set PA5 as output
	
	RCC->AHB1ENR |= 2;										// 0000 0000 0000 0000 0000 0000 0000 0010 enable clock for PB
	GPIOB->MODER |= 0;										// 0000 0000 0000 0000 0000 0000 0000 0000 set PB10 as input
	GPIOB->PUPDR |= 0x100000;							// 0000 0000 0001 0000 0000 0000 0000 0000 enable pull up resistor for PB10
	
	RCC->AHB1ENR |= 4; 										// 0000 0000 0000 0000 0000 0000 0000 0100 enable clock for PC
	GPIOC->MODER |= 0;										// 0000 0000 0000 0000 0000 0000 0000 0000 set PC13 as input
	
	RCC->APB2ENR |= 0x4000;								// 0000 0000 0000 0000 0100 0000 0000 0000 enable clock for SYSCFG
	SYSCFG->EXTICR[2] |= 0x100;						// 0000 0000 0000 0000 0000 0001 0000 0000 EXTI10 as PB10
	SYSCFG->EXTICR[3] |= 0x20;						// 0000 0000 0000 0000 0000 0000 0010 0000 EXTI13 as PC13
	
	EXTI->IMR |= 0x400; 									// 0000 0000 0000 0000 0000 0100 0000 0000 unmask PB10
	EXTI->IMR |= 0x2000;									// 0000 0000 0000 0000 0010 0000 0000 0000 unmask PC13
	
	EXTI->FTSR |= 0x400;									// 0000 0000 0000 0000 0000 0100 0000 0000 falling edge detector at PB10
	EXTI->FTSR |= 0x2000;									// 0000 0000 0000 0000 0010 0000 0000 0000 falling edge detector at PC13
	
	NVIC_EnableIRQ(EXTI15_10_IRQn);				// enable external interrupts 10 to 15
	
	__enable_irq();												// enable all global interrupts
	
	while(1)
	{
	}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & 0x400)									// if interrupt occurs at PB10
	{
		GPIOA->BSRR = 0x20;									// LED on
		sysTickDelayMs(200);
		GPIOA->BSRR = 0x200000;							// LED off
		sysTickDelayMs(200);
		
		EXTI->PR = 0x400;										// clear interrupt flag
	}
	
	else if(EXTI->PR & 0x2000)						// if interrupt occurs at PC13
	{
		GPIOA->BSRR = 0x20;									// LED on
		sysTickDelayMs(200);
		GPIOA->BSRR = 0x200000;							// LED off
		sysTickDelayMs(200);
		GPIOA->BSRR = 0x20;									// LED on
		sysTickDelayMs(200);
		GPIOA->BSRR = 0x200000;							// LED off
		sysTickDelayMs(200);
		
		EXTI->PR = 0x2000;									// clear interrupt flag
	}
}

void sysTickDelayMs(int n)
{
	SysTick->LOAD = 16000; 								// no. of clock cycles in 1ms at 16MHz
	SysTick->VAL = 0;    								  // Clear current value register
	SysTick->CTRL = 0x5;   								// Enable SysTick
	
	for(int i=0; i<n; i++)
	{
		while((SysTick->CTRL & 0x10000) == 0);     // Wait until the COUNT flag is set
	}
	
	SysTick->CTRL = 0;
}
 