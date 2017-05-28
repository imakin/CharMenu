#include "mock.h"

uint8_t CHARMENU_BUTTON_ENTER_PIN;
uint8_t CHARMENU_BUTTON_ENTER_PORT;

LCD lcd;

uint8_t bit_is_clear(uint8_t reg, uint8_t bit)
{
	return ((reg^0xff) & (1<<bit));
}
uint8_t bit_is_set(uint8_t reg, uint8_t bit)
{
	return (reg & (1<<bit));
}


void LCDstring(uint8_t *string, uint8_t length)
{
	uint8_t i = 0;
	//initialization
	if (lcd.x>15)
		lcd.x = 0;
	if (lcd.y>1)
		lcd.y = 0;
	if (lcd.data_0==NULL || lcd.data_1==NULL){
		lcd.data_0 = malloc(sizeof(uint8_t)*17);//last index for null char
		lcd.data_1 = malloc(sizeof(uint8_t)*17);//last index for null char
		for (i=0;i<16;i++)
		{
			lcd.data_0[i] = 32;//" "
			lcd.data_1[i] = 32;//" "
		}
	}
	if (lcd.data_1==NULL){
		lcd.data_1[16]=0;
	}
	
	for (i=0;i<length; i++)
	{
		if (lcd.x<16)
		{
			if (lcd.y==0)
			{
				lcd.data_0[lcd.x] = string[i];
			}
			else if (lcd.y==1)
			{
				lcd.data_1[lcd.x] = string[i];
			}
		}
		else if (lcd.y==0)
		{
			lcd.x = 0;
			lcd.y = 1;
			lcd.data_1[lcd.x] = string[i];
		}
		lcd.x++;
	}
	LCDprint();
	
}
void LCDprint()
{
	printf("LCD:\n");
	printf("%s\n%s\n",lcd.data_0, lcd.data_1);
}

void LCDGotoXY(uint8_t x, uint8_t y)
{
	lcd.x = x;
	lcd.y = y;
}
