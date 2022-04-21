/*
 * usart.c
 *
 *  Created on: Jul 21, 2019
 *      Author: mohamed
 */
#include "../../utils/bit_math.h"
#include "../../utils/custom_types.h"
#include "../dio/mcal_dio.h"
#include "usart.h"
#include "usart_atmega328p_reg.h"
void init_usart(u32_t baud_rate)
{
	u16_t baud;
	/*async mode */
	/*Parity Mode Disabled*/
	CLR_BIT(UCSR0C , UPM1);
	CLR_BIT(UCSR0C , UPM0);
	/*conf stop bit 1 stop bit*/
	CLR_BIT(UCSR0C , USBS);
	/*conf data size*/
	CLR_BIT(UCSR0B,UCSZ02);
	SET_BIT(UCSR0C,UCSZ1);
	SET_BIT(UCSR0C,UCSZ0);
	// use normal speed
	CLR_BIT(UCSR0A , U2X0);
	baud = (16000000UL/(16UL*baud_rate))-1;
    UBRR0H = (u8_t)(baud>>8);
	UBRR0L = (u8_t)baud;
	/*enable transmitter and receiver*/
	SET_BIT(UCSR0B,RXEN0);
	SET_BIT(UCSR0B,TXEN0);
	dio_set_channel_direction(dio_channel_rb0 , output);
}
void usart_write_char(u8_t chr)
{

	dio_set_channel_state(dio_channel_rb0 , high);
	while (READ_BIT(UCSR0A , UDRE0) == 0 );
	/* Put data into buffer, sends the data */
	UDR0 = chr;
	dio_set_channel_state(dio_channel_rb0 , low);
}
void usart_write_text(u8_t* txt)
{
   u8_t i = 0;
   while(txt[i] != '\0')
   {
	   usart_write_char(txt[i]);
	   i++;
   }
}
u8_t usart_read_char(void)
{
	/* Wait for data to be received */
	while ( READ_BIT(UCSR0A , RXC0) == 0 );
	return UDR0;
}
bool_t usart_data_available(void)
{
   return READ_BIT(UCSR0A , RXC0);
}

