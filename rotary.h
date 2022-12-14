/*
 * rotary.h
 *
 * Created: 07.08.22
 *  Author: Clemens Hauser
 *	Simple timer interrupt based algorithm to read out a gray code based rotary encoder. See readme!
 */ 


#ifndef ROTARY_H_
#define ROTARY_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdbool.h>


#define SIGNAL_DDR			DDRD
#define	SIGNAL_PIN			PIND 
#define SIGNAL_PORT			PORTD
#define SIGNAL_A			PD7
#define SIGNAL_B			PD6
#define SW					PD5

#define F_CPU		8000000

#define TIMER_CONTROL	0x0B					//Prescaler 64, clear timer on compare match active
#define TIMER_COMPARE	124

static volatile uint8_t status;						//working register to save current and old signal status
static volatile int8_t cnt;							//counter for rotary operation

static volatile uint8_t button_status;					//working register of push button
static volatile bool button_flag;							//working register of push button
static volatile bool button_switch;							

void rotaryInit();

int8_t rotaryGetCount();						//returns cnt 
int8_t rotaryGetChange();						//returns cnt change since last call
int8_t rotaryGetChangeWhileSwitch();			//returns cnt change since last call when switch turned on, otherwise returns 0
uint8_t rotaryGetButton();						//returns last button states
bool rotaryGetSwitch();							//returns switch status, true if turned on

#endif /* ROTARY_H_ */