/*
 * main.c
 *
 *  Created on: Oct 11, 2020
 *      Author: Basel Ashraf
 */


#include "uart.h"
#define M1_READY 0x10

void Timer1_PWM(unsigned short dutyCycle)
{
	TCNT1 = 0;
	ICR1 = 39999;
	OCR1A = dutyCycle;

	TCCR1A = (1<<COM1A1) | (1<<WGM11);
	TCCR1B = (1<<WGM12)	 | (1<<WGM13) | (1<<CS11);

}


int main(void)
{
	DDRD |= (1<<PD2) | (1<<PD3);
	uint8 byteRecieved = 0;
	DDRB |= (1<<PB1);
	DDRD |= (1<<PD2) | (1<<PD3);
	_delay_ms(100);
	UART_init();
	while(1)
	{


		byteRecieved = UART_recieveByte();
		if(byteRecieved == 'R')
		{
			Timer1_PWM(4800);

			_delay_ms(50);

		}
		else if(byteRecieved == 'L')
		{
			Timer1_PWM(1000);
			_delay_ms(50);
		}
		else if(byteRecieved == 'S')
		{
			PORTD &= ~(1<<PD2);
			PORTD &= ~(1<<PD3);
			Timer1_PWM(2800);
			_delay_ms(50);
		}
		else if(byteRecieved == 'F')
		{
			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);

		}
		else if(byteRecieved == 'B')
		{
			PORTD &= ~(1<<PD2);
			PORTD |= (1<<PD3);

		}
		else if(byteRecieved == 'Q')
		{
			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);
			Timer1_PWM(1000);
			_delay_ms(50);

		}
		else if(byteRecieved == 'E')
		{
			PORTD |= (1<<PD2);
			PORTD &= ~(1<<PD3);
			Timer1_PWM(4800);

			_delay_ms(50);

		}

	}
}
