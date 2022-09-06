/*
 * controller
 *
 * Created: 04.09.2022 21:15:53
 *  Author: Clem
 */ 

#include "controller.h"

void controllerInit()
{
	CDDR |= (1<<CPIN); //set output
	

	powerHeater = 1800; //In watt 
	
	timeConstantSystem = C_WATER * volumeHeater / powerHeater /10;	// /10 is correction for decilitres
	
	power = 0;
}
	
uint16_t controller(const int16_t input, const int16_t measured)				//call every second, returns requested heating power
{
	int32_t y;
	static int32_t eold = 0;
	static int32_t e = 0;
	e = input - measured;	
	
	y = (KP * e + KD * (e-eold)) / 100;	// divide by 100 due to temp-fpa
	
	eold = e;
	
	if(y < 0)
		return 0;
	if(y > powerHeater)
		return powerHeater;
	
	return y;
}

uint8_t powerToPwm(uint16_t power)
{	
	uint32_t buff = power;
	return (buff * 100) / powerHeater;
}

void pwm(uint8_t duty, bool powerOn)				//call every 33ms, fpwm = 0.3Hz
{	

	static int i = 0;
	
	if(powerOn && duty == 100)						//dirty solution
		CPORT |= (1<<CPIN);		//on	
		
	else if(powerOn && duty > 0)
	{	
		if(i < duty)
			CPORT |= (1<<CPIN);		//on		
			
		if(i >= duty)
			CPORT &= (0<<CPIN);		//off				
				
		i++;
		
		if(i > 100)
			i = 0;
	}		

}
