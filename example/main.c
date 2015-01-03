/* BISMILLAH			
 * An example of using CharMenu
 * CharMenu was released under LGPL license copyright (c) 2014-2015 Izzulmakin
 * lcd_lib was released under GPL license copyright(c) scienceprog 
*/
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include "lcd_lib.h"
#include <avr/eeprom.h>
#include "CharMenu.h"

#define STATE_MENU				0
#define STATE_FOOD_MENU			1
#define STATE_FOOD_PIZZA_MENU	2
#define STATE_FOOD_PIZZA_SMALL	3
#define STATE_FOOD_PIZZA_BIG	4
#define STATE_FOOD_KEBAB_MENU	5
#define STATE_FOOD_KEBAB_SMALL	6
#define STATE_FOOD_KEBAB_BIG	7
#define STATE_DRINK_MENU		8
#define STATE_DRINK_COLA		9
#define STATE_DRINK_PEPSI		10	

void init(void);
void FoodPizzaSmall_cb(void);
void FoodPizzaBig_cb(void);
void FoodKebabSmall_cb(void);
void FoodKebabBig_cb(void);
void DrinkCola_cb(void);
void DrinkPepsi_cb(void);

int main(void)
{
	LCDinit();
	LCDGotoXY(0,0);
	LCDstring("HAHA",4);
	LCDGotoXY(0,1);
	LCDprogressBar(7,40,16);
	_delay_ms(2000);
	Init();
	CharMenuInit();
	gCursor = 1;
	gState = STATE_MENU;
	
	while(1)
	{
		CharMenuDraw();
	}
}


void Init(void)
{
	MenuMain[STATE_FOOD_MENU].cursorNum = 1;
	MenuMain[STATE_FOOD_MENU].menuText = (uint8_t*)"Food            ";
	MenuMain[STATE_FOOD_MENU].numOfChildren = 2;
	MenuMain[STATE_FOOD_MENU].parentIndex = STATE_MENU;
	
	MenuMain[STATE_FOOD_PIZZA_MENU].cursorNum = 1;
	MenuMain[STATE_FOOD_PIZZA_MENU].menuText = (uint8_t*)"Pizza           ";
	MenuMain[STATE_FOOD_PIZZA_MENU].numOfChildren = 2;
	MenuMain[STATE_FOOD_PIZZA_MENU].parentIndex = STATE_FOOD_MENU;
	
	MenuMain[STATE_FOOD_PIZZA_SMALL].cursorNum = 1;
	MenuMain[STATE_FOOD_PIZZA_SMALL].menuText = (uint8_t*)"Pizza Small     ";
	MenuMain[STATE_FOOD_PIZZA_SMALL].numOfChildren = 0;
	MenuMain[STATE_FOOD_PIZZA_SMALL].parentIndex = STATE_FOOD_PIZZA_MENU;
	MenuMain[STATE_FOOD_PIZZA_SMALL].actFunction = &FoodPizzaSmall_cb;
	
	MenuMain[STATE_FOOD_PIZZA_BIG].cursorNum = 2;
	MenuMain[STATE_FOOD_PIZZA_BIG].menuText = (uint8_t*)"Pizza Big       ";
	MenuMain[STATE_FOOD_PIZZA_BIG].numOfChildren = 0;
	MenuMain[STATE_FOOD_PIZZA_BIG].parentIndex = STATE_FOOD_PIZZA_MENU;
	MenuMain[STATE_FOOD_PIZZA_BIG].actFunction = &FoodPizzaBig_cb;
	
	
	MenuMain[STATE_FOOD_KEBAB_MENU].cursorNum = 2;
	MenuMain[STATE_FOOD_KEBAB_MENU].menuText = (uint8_t*)"Kebab           ";
	MenuMain[STATE_FOOD_KEBAB_MENU].numOfChildren = 2;
	MenuMain[STATE_FOOD_KEBAB_MENU].parentIndex = STATE_FOOD_MENU;
	
	MenuMain[STATE_FOOD_KEBAB_SMALL].cursorNum = 1;
	MenuMain[STATE_FOOD_KEBAB_SMALL].menuText = (uint8_t*)"Kebab Small     ";
	MenuMain[STATE_FOOD_KEBAB_SMALL].numOfChildren = 0;
	MenuMain[STATE_FOOD_KEBAB_SMALL].parentIndex = STATE_FOOD_KEBAB_MENU;
	MenuMain[STATE_FOOD_KEBAB_SMALL].actFunction = &FoodKebabSmall_cb;
	
	MenuMain[STATE_FOOD_KEBAB_BIG].cursorNum = 2;
	MenuMain[STATE_FOOD_KEBAB_BIG].menuText = (uint8_t*)"Kebab Big       ";
	MenuMain[STATE_FOOD_KEBAB_BIG].numOfChildren = 0;
	MenuMain[STATE_FOOD_KEBAB_BIG].parentIndex = STATE_FOOD_KEBAB_MENU;
	MenuMain[STATE_FOOD_KEBAB_BIG].actFunction = &FoodKebabBig_cb;
	
	
	MenuMain[STATE_DRINK_MENU].cursorNum = 2;
	MenuMain[STATE_DRINK_MENU].menuText = (uint8_t*)"Drink           ";
	MenuMain[STATE_DRINK_MENU].numOfChildren = 2;
	MenuMain[STATE_DRINK_MENU].parentIndex = STATE_MENU;
	
	MenuMain[STATE_DRINK_COLA].cursorNum = 1;
	MenuMain[STATE_DRINK_COLA].menuText = (uint8_t*)"Cola            ";
	MenuMain[STATE_DRINK_COLA].numOfChildren = 0;
	MenuMain[STATE_DRINK_COLA].parentIndex = STATE_DRINK_MENU;
	MenuMain[STATE_DRINK_COLA].actFunction = &DrinkCola_cb;
	
	MenuMain[STATE_DRINK_PEPSI].cursorNum = 2;
	MenuMain[STATE_DRINK_PEPSI].menuText = (uint8_t*)"Pepsi           ";
	MenuMain[STATE_DRINK_PEPSI].numOfChildren = 0;
	MenuMain[STATE_DRINK_PEPSI].parentIndex = STATE_DRINK_MENU;
	MenuMain[STATE_DRINK_PEPSI].actFunction = &DrinkPepsi_cb;
	
	
}


void FoodPizzaSmall_cb(void)
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"SMALL PIZZA",11);
	LCDGotoXY(0,1);
	LCDstring((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	ButtonWait();
}

void FoodPizzaBig_cb(void)
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"BIG PIZZA",9);
	LCDGotoXY(0,1);
	LCDstring((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	ButtonWait();
}
void FoodKebabBig_cb(void)
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"BIG KEBAB",9);
	LCDGotoXY(0,1);
	LCDstring((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	ButtonWait();
}
void FoodKebabSmall_cb(void)
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"SMALL KEBAB",11);
	LCDGotoXY(0,1);
	LCDstring((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	ButtonWait();
}
void DrinkCola_cb(void)
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"COCA-COLA",9);
	LCDGotoXY(0,1);
	LCDstring((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	ButtonWait();
}
void DrinkPepsi_cb(void)
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"PEPSI",5);
	LCDGotoXY(0,1);
	LCDstring((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	ButtonWait();
}

