/*
 * CharMenu provides four buttons in a simple 16x2 charracter LCD 
 * 4 buttons: Enter, Back, Next, Previous
 * API provided:
 * 	Button interfacing
 * 	Menu management & instant easy but performance oriented menu for low RAM & clock ATMEGA16/32
 * Buttons are Pull-Up, LOW means pressed
 */
#ifndef CHAR_MENU_H
#define CHAR_MENU_H

#ifdef TEST_LINUX
	#include "mock.h"
#else
	#include <avr/io.h>
#endif
#include "settings.h"
#include <stdio.h>//snprintf

#define _set(_REG,_BIT) _REG |= (1<<_BIT) 			//set bit
#define _clear(_REG,_BIT) _REG &= ~(1<<_BIT) 		//clear bit
#define _togle(_REG,_BIT) _REG ^= (1<<_BIT)			//togle bit







/* Menu class */
typedef struct Menu_st Menu;
struct Menu_st{
	void (*action)(void);
	uint8_t *text; //-- should be defined in 16 characters. (padded with space to be 16 char)
	Menu *parent;//its parent menu
	Menu *next; //its sibling next item
	Menu *prev; //its sibling prev item
	Menu *child_tail;//its youngest/rightmost child
	Menu *child_head;//its oldest/leftmost child
	uint8_t pos;//for faster processing, store pos, the position this menu among its siblings
	uint8_t children;//total number of children
	
	void (*add_child)(Menu *self, Menu *child);
	
	void (*destroy)(Menu *self);
};

void Menu__add_child(Menu*,Menu*);
void Menu__destroy(Menu*);

/**
 * instantiate Menu object 
 * usages: Menu *my_menu = new_Menu(my_menu);
 */
#define new_Menu(self) \
	malloc(sizeof(Menu)); \
	self->destroy = &Menu__destroy; \
	self->add_child = &Menu__add_child; \
	self->action = NULL; \
	self->next = NULL; \
	self->prev = NULL; \
	self->parent = NULL; \
	self->children = 0;\
	self->child_head = NULL;\
	self->child_tail = NULL;







/* CharMenu main class */
typedef struct CharMenu_st CharMenu;
struct CharMenu_st {
	void 	(*button_wait)(CharMenu *self);
	uint8_t (*button_is_pressed)(CharMenu *self, uint8_t which);
	uint8_t (*button_read)(CharMenu *self);
	Menu * menu_root;
	Menu * current_menu;
	void	(*draw)(CharMenu *self);//main process
	void (*lcd_number)(CharMenu *self, uint8_t number, uint8_t pad);
	void (*print_scroll)(CharMenu *self, uint8_t pos, uint8_t scale);
	void (*init)(CharMenu *self);
};

void	CharMenu__init(CharMenu *self);
void	CharMenu__button_wait(CharMenu *self);
uint8_t	CharMenu__button_is_pressed(CharMenu *self, uint8_t which);
uint8_t	CharMenu__button_read(CharMenu *self);
void	CharMenu__draw(CharMenu *self);
void	CharMenu__lcd_number(CharMenu *self, uint8_t number, uint8_t pad);
void	CharMenu__print_scroll(CharMenu *self, uint8_t pos, uint8_t scale);

/**
 * instantiate CharMenu object <br/>
 * usages: CharMenu *my_charmenu = new_CharMenu(my_charmenu)
 */
#define new_CharMenu(self) \
	malloc(sizeof(CharMenu)); \
	self->init = &CharMenu__init;\
	self->init(self);






#endif
