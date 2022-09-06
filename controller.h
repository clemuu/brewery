/*
 * controller.h
 *
 * Created: 04.09.2022 21:15:48
 *  Author: Clem
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdlib.h>
#include <avr/io.h>
#include "sens/ds18b20.h"
#include <stdbool.h>

#define C_WATER 4190
#define TIME_CONSTANT_SENSOR 4
#define KP 560
#define KD 0
#define UPSCALING 100
#define CDDR DDRD
#define CPORT PORTD
#define CPIN PD2


uint16_t powerHeater;				//In watt 
uint16_t volumeHeater;				//In deci litres

uint16_t timeConstantSystem;

volatile uint16_t power;

void controllerInit();	
uint16_t controller(int16_t input, int16_t measured);		//call every second, returns requested heating power
uint8_t powerToPwm(uint16_t power);		//returns pwm duty cycle in percent	
void pwm(uint8_t duty, bool powerOn);				//call every 33ms, fpwm = 0.3Hz

#endif /* CONTROLLER_H_ */