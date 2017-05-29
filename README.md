CharMenu v3.0.0
========

Easy menu drawer to use with 16x2 character LCD for AVR. 


Note:
CharMenu can be used with lcd_lib.h from Scienceprog.com (GPL license).
but using other library is possible by implementing wrapper function (see demo in example)

```C
/**
 * wrap functions for LCD operation you use for library here
 * __lcd_gotoXY: to set cursor to (x,y)
 * __lcd_string: to print string to LCD
 * 
 * for example you have lcd_lib.h from scienceprog, you will find its method:
 *  LCDstring(string, len);
 *  LCDGotoXY(x,y);
 * then you have to define it 
 * 	__lcd_string(string, length) LCDstring(string,length)
 * 	__lcd_gotoXY(x, y) LCDGotoXY(x,y)
 */

#define __lcd_string(string, length)	LCDstring(string,length)
#define __lcd_gotoXY(x, y) 				LCDGotoXY(x,y)
```

What is this?
========

CharMenu is a framework to make an interface/application using simple yet widely used 16x2 charracter LCD


16x2 Char LCD is popular among embedded system, widely used in system debugging and/or for end-User display. 
Building menu and its navigation for this limited characters LCD with good __User-Experience__ is a bit hard. Therefore CharMenu propose the use of four buttons: ```[Enter]``` ```[Back]``` ```[Scroll Left]``` ```[Scroll Right]``` to navigate through the options displayed in the LCD. 

![what is it](https://cloud.githubusercontent.com/assets/6647566/5604155/a92d7be8-93dc-11e4-8a39-7c6a2ce198cf.jpg)

The two scroll button will navigate the menu to the left/right which is sibling menu.
Enter button will either enter the submenu (children menu) or execute some callback function to do.
Back button will navigate the menu to the parent's menu

For an example, there are these menu:
```
                            [MainMenu]
              [FoodMenu]------------------[DrinkMenu]
          [Pizza]---[Kebab]     [CocaCola]--[Pepsi]--[BigCola]
```
Inside the MainMenu there are two menus, to pick Food or Drink. Inside FoodMenu there are menus to pick wether to run pizza or kebab. On the image above, the ```Kebab``` menu is displayed, thus the cursor is to navigate between ```Kebab``` and ```Pizza```. Hitting Enter will execute the function callback which is binded to the ```kebab``` menu. Hitting prev/scroll left button will navigate the menu to ```Pizza``` menu, Hitting next/scroll right menu will get the cursor to the next menu which --as ```kebab``` is already the right most menu-- will jump the cursor to the left most menu: ```Pizza```. Back button will return the menu to its parent menu, the menu to pick either ```FoodMenu``` or ```DrinkMenu```.



Object Oriented C
========
This Framework is easy to use. There are 3 files: CharMenu.c, CharMenu.h, settings.h
please take a look at settings.h to configure the LCD interface

there are 2 classes used in the Framework:
CharMenu: the main class
Menu: the menu class

CharMenu has member: menu_root (type is Menu)
the menus are children of this menu_root (see example)

quick usage:
```C
#include "CharMenu.h"
CharMenu * charmenu;

void menu0_action();//example callback for menu0

int main(void)
{
	LCDinit();
	charmenu = new_CharMenu(charmenu);
	
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
			
	//The main process
	while(1)
	{
		charmenu->draw(charmenu);
	}
}

void menu0_action(void)
//example callback for menu0
{
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring((uint8_t*)"SMALL PIZZA     ",16);
	LCDGotoXY(0,1);
	LCDstring((uint8_t*)"Press any button",16);
	charmenu->button_read(charmenu);
}

```


Usage
========
See ./example/ to use lcd_lib.h LCD library
