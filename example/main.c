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

void Init(void);
void FoodPizzaSmall_cb(void);
void FoodPizzaBig_cb(void);
void FoodKebabSmall_cb(void);
void FoodKebabBig_cb(void);
void DrinkCola_cb(void);
void DrinkPepsi_cb(void);

int main(void)
{
	cm_LcdInit();
	Init();
	
	while(1)
	{
		CharMenuDraw();
	}
}


void Init(void)
{
	tMenu *menu_anchestor, *menu_1, *menu_2, *menu_11, *menu_12, *menu_13;
	CharMenuInit();
	//-- Mandatory step: set the anchestor menu
	menu_anchestor = cm_AddMenu("MAIN MENU",
								1,//-- cursor pos
								0,//-- no sibling
								2,//-- has 3 children
								0,0,0,//-- parent,next,prev menu
								0, //-- child menu set to 0 first
								0);//-- no callback function
	//-- current menu is the first shown menu: the 1st child of anchestor menu
	menu_1 = cm_AddMenu("MENU PERTAMA    ",
								1,
								1,
								3,//--has three children
								menu_anchestor,
								menu_2, //-- menu_2 has not pointed anywhere 
								0,
								menu_11,
								0);
	menu_2 = cm_AddMenu("MENU KEDUA      ",
								2,
								1,
								0,
								menu_anchestor,
								0,
								menu_1,
								0,
								0);
	menu_11 = cm_AddMenu("MENU 11         ",
								1,			//pos
								2,			//num sibling
								0,			//num children
								menu_1,		//parent
								menu_12,	//next
								0,			//prev
								0,			//1st child
								0);			//cbfunction
	menu_12 = cm_AddMenu("MENU 12         ",
								2,			//pos
								2,			//num sibling
								0,			//num children
								menu_1,		//parent
								menu_13,	//next
								menu_11,	//prev
								0,			//1st child
								0);			//cbfunction
	menu_13 = cm_AddMenu("MENU 13         ",
								3,			//pos
								2,			//num sibling
								0,			//num children
								menu_1,		//parent
								0,			//next
								menu_12,	//prev
								0,			//1st child
								0);			//cbfunction
	//-- do this after all menu has pointed to correct menu object
	menu_1->menuNext 		= menu_2;
	menu_1->menuChildF 		= menu_11;
	menu_11->menuNext 		= menu_12;
	menu_12->menuNext 		= menu_13;
	menu_13->menuPrevious 	= menu_12;
	menu_12->menuPrevious 	= menu_11;
	//-- Mandatory step: set the current menu
	cm_currentMenu = menu_1;
}

void FoodPizzaSmall_cb(void)
{
	cm_LcdClear();
	cm_LcdGotoXY(0,0);
	cm_LcdString((uint8_t*)"SMALL PIZZA",11);
	cm_LcdGotoXY(0,1);
	cm_LcdString((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	cm_ButtonWait();
}

void FoodPizzaBig_cb(void)
{
	cm_LcdClear();
	cm_LcdGotoXY(0,0);
	cm_LcdString((uint8_t*)"BIG PIZZA",9);
	cm_LcdGotoXY(0,1);
	cm_LcdString((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	cm_ButtonWait();
}
void FoodKebabBig_cb(void)
{
	cm_LcdClear();
	cm_LcdGotoXY(0,0);
	cm_LcdString((uint8_t*)"BIG KEBAB",9);
	cm_LcdGotoXY(0,1);
	cm_LcdString((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	cm_ButtonWait();
}
void FoodKebabSmall_cb(void)
{
	cm_LcdClear();
	cm_LcdGotoXY(0,0);
	cm_LcdString((uint8_t*)"SMALL KEBAB",11);
	cm_LcdGotoXY(0,1);
	cm_LcdString((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	cm_ButtonWait();
}
void DrinkCola_cb(void)
{
	cm_LcdClear();
	cm_LcdGotoXY(0,0);
	cm_LcdString((uint8_t*)"COCA-COLA",9);
	cm_LcdGotoXY(0,1);
	cm_LcdString((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	cm_ButtonWait();
}
void DrinkPepsi_cb(void)
{
	cm_LcdClear();
	cm_LcdGotoXY(0,0);
	cm_LcdString((uint8_t*)"PEPSI",5);
	cm_LcdGotoXY(0,1);
	cm_LcdString((uint8_t*)"HAS SELECTED",12);
	_delay_ms(500);
	cm_ButtonWait();
}

