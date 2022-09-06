/*
 * tasking.c
 *
 * Created: 18.08.2022 18:07:00
 *  Author: Clem
 */ 
#include "tasking.h"


void taskingInit()
{	
		
	TCCR0 |= TIMER0_CONTROL;			//Set prescaler
	TIMSK |= (1<<TOIE0);				//Activate Timer0 overflow interrupt
	sei();								//set enable interrupts
	
}

void exec33ms()
{	
	static uint8_t count = 0;
	count ++;
	
	if(count % 15 == 0)						// 495ms
		{
			exec488ms();
		}
		
	if(count % 17 == 0)
		{			
			exec990ms();
		}
	
	if(count == 60)
		{
			count = 0;
			exec1980ms();
		}
	
	//**** Controller ****
	pwm(powerToPwm(power),true );	
		
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
		
		
		//**** Controller ****
		power = controller(getMenuTemp(), actTemp);	
		
		usartSendString("pwm: "); usartSendString(itoa(powerToPwm(power),buffer,10));
		usartSendString("Power: "); usartSendString(itoa(power,buffer,10));
		usartSendString("Temp act: "); usartSendString(itoa(actTemp,buffer,10));
		usartSendString("Temp men: "); usartSendString(itoa(getMenuTemp(),buffer,10));
		usartSendString("\n");
		
		
		
}

void exec1980ms()
{		

}


ISR (TIMER0_OVF_vect)
{
	exec33ms();
}

