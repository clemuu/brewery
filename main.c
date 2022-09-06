/*
 * simplestMenu.c
 *
 * Created: 19.08.2022 15:00:56
 * Author : Clem
 */ 

#include <avr/io.h>
#include "rotary.h"
#include "lcd/lcd-routines.h"
#include "tasking.h"
#include "simplestMenu.h"
#include "sens/ds18b20.h"
#include "comm/serialComm.h"


int main(void)
{	
		lcd_init();
		taskingInit();
		rotaryInit();
		menuInit();
		onewireInit();
		set_resolution(CONFIG10);
		
		usartInit(MYUBRR);
				
		controllerInit();
		
	
    while (1) 
    {

    }
}

