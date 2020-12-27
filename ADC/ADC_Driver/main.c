#include "stm32f4xx.h"                  // Device header

int analogValue;
int main(void)
{
	RCC->AHB1ENR |= 1;										// 0000 0000 0000 0000 0000 0000 0000 0001 enable clock for PA
	GPIOA->MODER |= 0xC;									// 0000 0000 0000 0000 0000 0000 0000 1100 set PA1 as analog
	
	RCC->APB2ENR |= 0x100;								// 0000 0000 0000 0000 0000 0001 0000 0000 enable clock for ADC1
	ADC1->CR2 = 0;												// 0000 0000 0000 0000 0000 0000 0000 0000 ADC1 is disabled
	ADC1->SQR3 = 1;
	ADC1->CR2 |= 1;												// 0000 0000 0000 0000 0000 0000 0000 0001 ADC1 is enabled
	
	while(1)
	{
		ADC1->CR2 |= 40000000;							// 0100 0000 0000 0000 0000 0000 0000 0000 start conversion
		while(!(ADC1->SR & 2))							// wait for conversion to be complete
		{
		}
		
		analogValue = ADC1->DR;							// value of ADC goes into analogValue
	}
}
