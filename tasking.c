/*
 * tasking.c
 *
 * Created: 18.08.2022 18:07:00
 *  Author: Clem
 */ 
#include "tasking.h"
#include "simplestMenu.h"
#include "sens/ds18b20.h"
#include <stdbool.h>

void taskingInit()
{	
	DDRD |= (1<<PD5);
	
	TCCR0 |= TIMER0_CONTROL;			//Set prescaler
	TIMSK |= (1<<TOIE0);				//Activate Timer0 overflow interrupt
	sei();								//set enable interrupts

	// ***** temp sensor specific **********
	set_resolution(CONFIG10);
	
}

void exec33ms()
{	
	static uint8_t count = 0;
	count ++;
	
	if(count % 15 == 0)						// 495ms
		{
			exec488ms();
		}
		
	if(count % 30 == 0)
		{			
			exec990ms();
		}
	
	if(count % 60 == 0)
		{
			count = 0;
			exec1980ms();
		}
		
}

void exec488ms()
{	
	showMenu();
}


void exec990ms()
{	
		// ******** Temp sensor ********
		static bool flag = true;
		if(flag){						//request and get temperature alternating
			req_temperature();
		}
		
		else{
			actTemp = get_temperature(CORRECTION10,SHIFT10);
		}
		
		flag = !flag;
		
		if(actTemp >= 11000 || actTemp <= -500)
			actTemp = 2000;							
		
		char* buffer[6];
		usartSendString(itoa(actTemp,buffer,10));
}

void exec1980ms()
{		

}


ISR (TIMER0_OVF_vect)
{
	exec33ms();
}

