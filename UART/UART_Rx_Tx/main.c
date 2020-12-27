
#include "stm32f4xx.h"                  // Device header
#include <stdio.h>

void USART_Init(void)
{
	RCC->APB1ENR |= 0x20000; 							// 0000 0000 0000 0010 0000 0000 0000 0000   enable USART2 port
  RCC->AHB1ENR |= 1;      							// 0000 0000 0000 0000 0000 0000 0000 0001   enable port A

	GPIOA->AFR[0] |= 0x7700;
	GPIOA->MODER	|= 0x00A0;              // 0000 0000 0000 0000 0000 0000 1010 0000   enable alternate function for PA2 and PA3
	
	USART2->BRR |= 0x0683;								// 9600 baud rate 
	USART2->CR1 |= 0x000C;								// 0000 0000 0000 0000 0000 0000 0000 1100   enable rx and tx
	USART2->CR1 |= 0x2000;  							// 0000 0000 0000 0010 0000 0000 0000 0000   enable USART
}

int USART_write(int ch)
{
	while(!(USART2->SR & 0x0080))    			// wait for tx buffer to be empty
	{
		USART2->DR = (ch & 0xFF);
		return ch;
	}
}

int USART_read(void)
{
	while(!(USART2->SR & 0x0020))					// wait for rx buffer to be empty
	{
		return USART2->DR;
	}
}

struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout = {1};
FILE __stderr = {2};

int fgetc(FILE *f)
{
	int c;
	c = USART_read();
	if (c == '\r')
	{
			USART_write(c);
		c= '\n';
	}
	USART_write(c);
	return c;
}

int fputc(int c, FILE *f)
{
	return USART_write(c);
}

int main(void)
{
	int n;
	char str[100];
	
	printf("Hello from the other side\n");
	fprintf(stdout, "test for stdout\r\n");
	fprintf(stderr, "test for stderr\r\n");
	
	while(1)
	{
		printf("How old are you?");
		scanf("%d",&n);
		printf("Your age is : %d\r\n",n);
		printf("Enter your first name");
		gets(str);
		printf("I like your style: ");
		puts(str);
		printf("\r\n");
	}
}


	