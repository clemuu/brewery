/*
* ds18b20.c
*
* Created: 24.07.2022 16:52:41
*  Author: Clemens Hauser
*/
#include <avr/io.h>
#include "ds18b20.h"
#include <util/delay.h>


void onewireInit()
{
	WIRE_DDR |= (1<<WIRE);						//set output
	WIRE_PORT &= (0<<WIRE);
	_delay_us(DELAY_RESET);
	WIRE_DDR &= (0<<WIRE);						//set input
	_delay_us(DELAY_RESET);
}

void bus_write_bit(char bit)
{
	WIRE_PORT &= (0<<WIRE);
	
	if(bit)
	{
		_delay_us(ONE_DUR);
		WIRE_PORT |= (1<<WIRE);
		_delay_us(ZERO_DUR);					//wait extra time to reach total timeslot duration
		
	}
	else
	{
		_delay_us(ZERO_DUR);
		WIRE_PORT |= (1<<WIRE);
	}
	
	
}

void bus_write_byte(char byte)
{
	WIRE_DDR |= (1<<WIRE);
	for(uint8_t i = 0; i<8; i++)
	{
		bus_write_bit(byte & (1<<i) );
	}
	WIRE_DDR &= (0<<WIRE);
}

uint8_t bus_read_bit()
{
	
	WIRE_DDR |= (1<<WIRE);
	WIRE_PORT &= (0<<WIRE); //initiate timeslot
	WIRE_DDR &= (0<<WIRE);
	
	_delay_us(ONE_DUR);
	
	return ((WIRE_PIN & (1<<WIRE))>>WIRE);		//read bit value on bus
}

uint8_t bus_read_byte()
{
	uint8_t ret=0x00;
	
	for(uint8_t i = 0; i<8; i++)
	{
		ret |= bus_read_bit() << i;				//lsb is transmitted first
		_delay_us(ZERO_DUR);
	}
	
	return ret;
}


void req_temperature()
{
	onewireInit();
	bus_write_byte(ROMSKIP);
	bus_write_byte(TCONVERT);
	onewireInit();
}

int16_t get_temperature(uint8_t correction, uint8_t shift)
{
	if(!bus_read_bit())							//check if sensor is still converting
	{
		return 0xFFFF;
	}
	
	int16_t ret=0x0000;
	

	
	bus_write_byte(ROMSKIP);
	bus_write_byte(SCRATCHPADREAD);
	
	ret |= bus_read_byte();
	ret |= bus_read_byte()<<8;					//read 2nd byte
	onewireInit();									//stop reading
	
	ret = ret >> shift;							//shift fpa
	
	return ret*correction;						//correction fpa

}


void set_resolution(uint8_t configuration)
{	
	onewireInit();
	bus_write_byte(ROMSKIP);
	bus_write_byte(SCRATCHPADWRITE);
	bus_write_byte(0x00);
	bus_write_byte(0x00);
	bus_write_byte(configuration);
	onewireInit();
}