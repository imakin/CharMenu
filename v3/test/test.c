/*
 * To test compilation of CharMenu using gcc for linux 
 */
#include "CharMenu.h"
#include <stdio.h>

uint8_t bit_is_clear(uint8_t reg, uint8_t bit)
{
	return ((reg^0xff) & (1<<bit));
}
uint8_t bit_is_set(uint8_t reg, uint8_t bit)
{
	return (reg & (1<<bit));
}


int main(int c, char** v)
{
	PIND = (uint8_t)0b10111111;
	PORTD = (uint8_t)0;
	printf("PIND: %d \n",PIND);
	printf("PORTD: %d \n",PORTD);
	CharMenu* charmenu = new_CharMenu(charmenu);
	uint8_t r = charmenu->button_read();
	printf("button_read: %d \n",r);
	return 0;
}
