/*
 * main.c
 *
 *  Created on: Oct 11, 2020
 *      Author: Basel Ashraf
 */


#include "uart.h"
#include "adc.h"
#define M1_READY 0x10
int main(void)
{
	ADC_init();
	DDRB |= (1<<PB1);
	DDRD |= (1<<PD2) | (1<<PD3);
	uint16 x = 0;
	uint16 y = 0;
	UART_init();
	while(1)
	{

		x = ADC_readChannel(0);
		y = ADC_readChannel(1);
		if(x<100 && x>=0 && y>250 && y<700 )
		{

			UART_sendByte('R');


		}
		else if(x>900 && x<1024 && y>250 && y<700 )
		{
			UART_sendByte('L');

		}
		else if(y<1024 && y>=900 && x<700 && x>=250 )
		{

			UART_sendByte('F');


		}
		else if(y>=0 && y<100 && x<700 && x>250)
		{
			UART_sendByte('B');

		}
		else if(y>400 && y<600 && x>400 && x<600)
		{

			UART_sendByte('S');
		}
		else if(x>=1000 && x<1024 && y>=1000 && y<1024)
		{
			UART_sendByte('Q');
		}
		else if(y>=950 && y<1024 && x<200 && x>=0)
		{
			UART_sendByte('E');
		}
		_delay_ms(150);





	}
}
