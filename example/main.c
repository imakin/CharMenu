/* BISMILLAH			
 * An example of using CharMenu
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
CharMenu * charmenu;

void menu0_action();

int main(void)
{
	LCDinit();
	charmenu = new_CharMenu(charmenu);
	Init();
	
	while(1)
	{
		charmenu->draw(charmenu);
	}
}


void Init(void)
{
	
	Menu *menu0 = new_Menu(menu0);
	menu0->text = "MENU 0          ";
	
	Menu *menu1 = new_Menu(menu1);
	menu1->action = &menu0_action;
	menu1->text = "MENU 1          ";
	
	Menu *menu00 = new_Menu(menu00);
	menu0->add_child(
				menu0,
				menu00
			);
	menu00->text = "MENU 00         ";
	
	
	charmenu->menu_root->add_child(
				charmenu->menu_root, 
				menu0
			);
	charmenu->menu_root->add_child(
				charmenu->menu_root, 
				menu1
			);
}

void menu0_action(void)
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"SMALL PIZZA",11);
	charmenu->button_read(charmenu);
}
