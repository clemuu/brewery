/*
 * tasking.h
 *
 * Created: 18.08.2022 18:07:15
 *  Author: Clem
 *	ALWAYS EXECUTE INIT!!		
 */ 


#ifndef TASKING_H_
#define TASKING_H_

#define TIMER0_CONTROL 0x5		//Prescaler 1024 ->30.5 Hz at full range timer

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "comm/serialComm.h"


void taskingInit();				//init of timer, interrupt 

void exec33ms();
void exec488ms();
void exec990ms();
void exec1980ms();




#endif /* TASKING_H_ */