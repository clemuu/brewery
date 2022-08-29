/*
 * serialComm.h
 *
 * Created: 27.08.2022 17:45:35
 *  Author: Clem
 */ 


#ifndef SERIALCOMM_H_
#define SERIALCOMM_H_

#include <stdlib.h>
#include <avr/io.h>

#define FOSC 8000000			//Clock
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void usartInit(uint8_t ubrr);						//init uart
void usartTransmit (unsigned char data);			//write byte
unsigned char usartReceive( void );					//receive byte
void usartWriteWord(int16_t data);					//write binary word
void usartSendString(const char *data);				//write ascii string
void usartSendNumberAsAscii(int16_t data);			//write int as ascii string

#endif /* SERIALCOMM_H_ */