/*
 * simplestMenu.h
 *
 * Created: 18.08.2022 18:07:15
 *  Author: Clem
 */ 


#ifndef SIMPLESTMENU_H_
#define SIMPLESTMENU_H_



#include <stdint.h>
#include "lcd/lcd-routines.h"
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "rotary.h"
#include <stdlib.h>
#include "sens/ds18b20.h"

static volatile int16_t menuTemp;
volatile int16_t actTemp;

void menuInit();
void showMenu();
void showText(uint8_t col, uint8_t line, const char *text, bool blinking, bool *flag);		//flag is used to achieve alternating function behaviour when blinking, if blinking not needed, pass nullptr

int16_t getMenuTemp();
int16_t setMenuTemp(int8_t change);
char* showMenuTemp(uint16_t temp, char* buffer);												//convert fpa-int to decimal point-using string



#endif /* SIMPLESTMENU_H_ */