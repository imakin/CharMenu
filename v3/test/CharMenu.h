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

#include <inttypes.h>
#include "settings.h"

#define _set(_REG,_BIT) _REG |= (1<<_BIT) 			//set bit
#define _clear(_REG,_BIT) _REG &= ~(1<<_BIT) 		//clear bit
#define _togle(_REG,_BIT) _REG ^= (1<<_BIT)			//togle bit

#ifdef LINUX_TEST
	extern uint8_t PIND;
	extern uint8_t PORTD;
#endif

#ifndef __CUSTOM_SETTINGS__
	///Menu uses 4 cm_Button, comprises Enter, Back, Previous, and Next, which defined here:
	#define CHARMENU_BUTTON_ENTER_PIN	PIND
	#define CHARMENU_BUTTON_BACK_PIN	PIND
	#define CHARMENU_BUTTON_PREV_PIN	PIND
	#define CHARMENU_BUTTON_NEXT_PIN	PIND
	#define CHARMENU_BUTTON_ENTER_PORT	PORTD
	#define CHARMENU_BUTTON_BACK_PORT	PORTD
	#define CHARMENU_BUTTON_PREV_PORT	PORTD
	#define CHARMENU_BUTTON_NEXT_PORT	PORTD
	///Enter the pin number for each of the cm_Button 
	#define CHARMENU_BUTTON_ENTER_DOWN	1 ///means Enter button is in PIND-bit 1
	#define CHARMENU_BUTTON_BACK_DOWN	2
	#define CHARMENU_BUTTON_PREV_DOWN	0
	#define CHARMENU_BUTTON_NEXT_DOWN	3
#endif


/* CharMenu main class */
typedef struct CharMenu_st CharMenu;
struct CharMenu_st {
	void 	(*button_wait)(void);
	uint8_t (*button_is_pressed)(uint8_t);
	uint8_t (*button_read)(void);
};

void	CharMenu__button_wait(void);
uint8_t	CharMenu__button_is_pressed(uint8_t);
uint8_t	CharMenu__button_read(void);

/**
 * instantiate CharMenu object <br/>
 * usages: CharMenu *my_charmenu = new_CharMenu(my_charmenu)
 */
#define new_CharMenu(self) \
	malloc(sizeof(CharMenu)); \
	self->button_wait = &CharMenu__button_wait;\
	self->button_is_pressed = &CharMenu__button_is_pressed;\
	self->button_read = &CharMenu__button_read;




/* Menu class */
typedef struct Menu_st Menu;
struct Menu_st{
	void (*actFunction)(void);
	uint8_t *text; //-- should be defined in 16 characters. (padded with space to be 16 char)
	Menu *parent;
	Menu *next; //its sibling next item
	Menu *prev; //its sibling prev item
	Menu **children;
	
	void (*children_add)(Menu *child);
};

void Menu__children_add(Menu*);

/**
 * instantiate Menu object 
 * usages: Menu *my_menu = new_Menu(my_menu);
 */
#define new_Menu(self) \
	malloc(sizeof(Menu)); \
	self->children_add = &Menu__children_add; \
	self->actFunction = 0; \
	self->next = 0; \
	self->prev = 0; \
	self->parent = 0; \
	self->children = 0;




#endif
