/*
 * To test compilation of CharMenu using gcc for linux 
 */
#include "CharMenu.h"
#include "mock.h"
#include <stdio.h>

void print_buttons();
void print_menus(Menu *root);
void print_menus_level(Menu *root, uint8_t level);


int main(int c, char** v)
{
	uint8_t i;
	CharMenu* charmenu = new_CharMenu(charmenu);
	TESTPORT = (uint8_t)0b1111;
	
	//Testing button
	TESTPIN = (uint8_t)0b1101;
	for (i=0;i<4;i++)
	{
		TESTPIN = (uint8_t)((1<<i)^0x0f);
		uint8_t r = charmenu->button_read(charmenu);
		printf("button_read: %d \n",r);
		assertEqual(r,i);
	}
	
	
	//testing menu management
	Menu *menu0 = new_Menu(menu0);
	menu0->text = "Menu 0          ";
	Menu *menu1 = new_Menu(menu1);
	menu1->text = "Menu 1          ";
	Menu *menu2 = new_Menu(menu2);
	menu2->text = "Menu 2          ";
	
	Menu *menu00 = new_Menu(menu00);
	menu00->text = "Menu 00         ";
	Menu *menu01 = new_Menu(menu01);
	menu01->text = "Menu 01         ";
	menu0->add_child(menu0, menu00);
	menu0->add_child(menu0, menu01);
	
	Menu *menu10 = new_Menu(menu10);
	menu10->text = "Menu 10         ";
	Menu *menu11 = new_Menu(menu11);
	menu11->text = "Menu 11         ";
	menu1->add_child(menu1, menu10);
	menu1->add_child(menu1, menu11);
	
	
	Menu *menu110 = new_Menu(menu110);
	menu110->text = "Menu 110        ";
	menu11->add_child(menu11, menu110);
	
	charmenu->menu_root->add_child(charmenu->menu_root, menu0);
	charmenu->menu_root->add_child(charmenu->menu_root, menu1);
	charmenu->menu_root->add_child(charmenu->menu_root, menu2);
	
	printf("children: %d\n", charmenu->menu_root->children);
	print_menus(charmenu->menu_root);
	//Scroll test
	
	__lcd_gotoXY(13,1);
	charmenu->lcd_number(charmenu, 300, 3);
	printf("%s",lcd.data_1);
	fflush(stdout);
	
	printf("testing scroll\n");
	i = 1;
	for (i=0;i<0x0FE;i++)
	{
		charmenu->print_scroll(charmenu, i,0x0FE);
		//~ printf("%d [%d]",lcd.x,lcd.y);
		//~ printf("%s [%d]",lcd.data_1,i);
		fflush(stdout);//print immediately without waiting for the loop to be done
		system("sleep 0.025");
		//~ printf("\33[2K\r");
		
	}
	
	charmenu->draw(charmenu);
	return 0;
}



void print_buttons()
{
	printf("TESTPIN: %d \n",TESTPIN);
	printf("TESTPORT: %d \n",TESTPORT);
}

void print_menus(Menu *root)
{
	print_menus_level(root, 0);
}
void print_menus_level(Menu *root, uint8_t level)
{
	uint8_t i=0;
	if (root->text!=NULL)
	{
		for (i=0;i<level;i++)
			printf("  ");
		printf("%s\n", root->text);
	}
	if (root->children>0)
	{
		Menu *child;
		child = root->child_head;
		while (child!=NULL)
		{
			print_menus_level(child, level+1);
			child = child->next;
		}
	}
}
