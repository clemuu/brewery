/*
 * simplestMenu.c
 *
 * Created: 18.08.2022 18:07:00
 *  Author: Clem
 */ 
#include "simplestMenu.h"

void menuInit()
{
	menuTemp = 2000;				//equivalent to 20.0 Deg
	actTemp = menuTemp;
}

void showText(uint8_t col, uint8_t line, const char *text, bool blinking, bool *flag)
{
	if(blinking)
	{					
		if(*flag)
		{
			lcd_setcursor(col, line);
			for(int i = 0; i < strlen(text); i++)
			{
				lcd_data(' ');
			}
		}		
		else
		{
			lcd_setcursor(col, line);
			lcd_string(text);		
		}
		
	*flag = !(*flag);
	}
	
	else
	{
		lcd_setcursor(col, line);
		lcd_string(text);
	}
}


int16_t getMenuTemp()
{
	return menuTemp;
}

int16_t setMenuTemp(int8_t change)										//increment in 5 digits
{
	return menuTemp = menuTemp + 50 * change;
}

char* showMenuTemp(uint16_t temp, char* buffer)
{	
	char* returnbuffer = buffer;
	itoa(temp/100,buffer,10);					//convert number without decimal part
	int i = 0;								
	while(buffer[i] != '\0')					//search for string terminator
	{
		i++;		
	}
	buffer[i]='.';								//add decimal point
	i++;
	buffer = buffer + i;						//set buffer pointing to terminator again
	itoa((temp - (temp / 100 * 100)),buffer,10);

	return returnbuffer;						//return pointer to string start
}

void showMenu()
{	
	lcd_clear();

	static bool controllerActive = false;
	static bool blinkFlag, blinkFlag2;
	char buffer[5];
	
	showText(0,1,"Tsoll: ", false, NULL);
	
	if(rotaryGetSwitch())												//switch turned on
	{	
		setMenuTemp(rotaryGetChangeWhileSwitch());						//only change temp when switch turned on
		showText(12,1,showMenuTemp(getMenuTemp(),buffer), true, &blinkFlag);
		showText(12,2,"off", true, &blinkFlag2);

		controllerActive = false;
	}
	
	if(!rotaryGetSwitch())												//turned off
	{
		showText(12,1,showMenuTemp(getMenuTemp(),buffer), false, NULL);
		showText(12,2,"on", false, NULL);

		controllerActive = true;
	}

	showText(0,2,"Tist:",false, NULL);
	showText(5,2,showMenuTemp(actTemp,buffer),false,NULL);
}