/*
 * serialComm.c
 *
 * Created: 27.08.2022 17:45:47
 *  Author: Clem
 */ 

#include "serialComm.h"




void usartInit(uint8_t ubrr)
{
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL)|(1<<USBS)|(3<<UCSZ0);
}


void usartTransmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
		;
	/* Put data into buffer, sends the data */
	UDR = data;
}

unsigned char usartReceive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

void usartWriteWord(int16_t data)
{
	for (int i = 0; i < 2; i++)
	{
			while ( !( UCSRA & (1<<UDRE)) )
				;
			UDR = data >> (8 * i);			//no shifting in first iteration
	}
}

void usartSendString(const char *data)
{
	int i = 0;
	while(data[i] != '\0')
	{
		usartTransmit(data[i]);
		i++;
	}
	usartTransmit('\0');
}


void usartSendNumberAsAscii(int16_t data)
{
	char buffer[7];							//6 digits max with 16 bit number
	itoa(data,buffer,10);
	int i = 0;
	while(buffer[i] != '\0')
		{
			usartTransmit(buffer[i]);
			i++;
		}
	usartTransmit('\n');
}