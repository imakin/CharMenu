/**
 * (c) 2014-2015 Izzulmakin
 * made from 23 Dec 2014 based on makin.h (github.com/imakin/sarjiya)
 * released under LGPL license, derivative works are bind to use LGPL license
 * 
 * this library require lcd_lib.h v2.0 - Scienceprog.com - Copyright (C) 2007 - GPL license
 */
#ifndef CHAR_MENU_H
#define CHAR_MENU_H

#include <inttypes.h>
///Menu uses 4 button, comprises Enter, Back, Previous, and Next, which defined here:
#define BUTTON_ENTER_PIN	PINC
#define BUTTON_BACK_PIN		PINC
#define BUTTON_PREV_PIN		PINC
#define BUTTON_NEXT_PIN		PINC
#define BUTTON_ENTER_PORT	PORTC
#define BUTTON_BACK_PORT	PORTC
#define BUTTON_PREV_PORT	PORTC
#define BUTTON_NEXT_PORT	PORTC
///Enter the pin number for each of the button 
#define BUTTON_ENTER_DOWN	1 ///means Enter button is in PINC- bit 1
#define BUTTON_BACK_DOWN	2
#define BUTTON_PREV_DOWN	0
#define BUTTON_NEXT_DOWN	3

///MainMenu is reserved struct variable that role as prime Menu,
///Total number of children defined here:
#define MAIN_MENU_NUMBER_OF_CHILDREN	2
///For optimum performance, total number of menus should be defined
#define TOTAL_MENU	11


#define _set(_REG,_BIT) _REG |= (1<<_BIT) 			//set bit
#define _clear(_REG,_BIT) _REG &= ~(1<<_BIT) 		//clear bit
#define _togle(_REG,_BIT) _REG ^= (1<<_BIT)			//togle bit

#define isset(_REG,_BIT) bit_is_set(_REG,_BIT)
#define isclear(_REG,_BIT) bit_is_clear(_REG,_BIT)

///
void DrawNumber(uint16_t bil, uint8_t x, uint8_t y,uint8_t _c);
///
void DrawNumberCPos(uint16_t bil, uint8_t _c);
///Clears block with whitespace replacing
void LcdDelete(uint8_t xawal, uint8_t xakhir, uint8_t _Y);


uint8_t ButtonEnter(void);
uint8_t ButtonBack(void);
uint8_t ButtonNext(void);
uint8_t ButtonPrev(void);
void 	ButtonWait(void);
uint8_t ButtonIsPressed(void);
uint8_t ButtonIsNotPressed(void);
uint8_t ButtonRead(void);

uint16_t gState;
uint8_t gCursor;
uint8_t gScrollMax;


uint8_t GetCursor(uint16_t numstate);
uint8_t GetParent(uint16_t numstate);
uint8_t GetChild(uint8_t parent, uint8_t childid);
void ReStrainScroll(void);
void PrintScroll(uint8_t sNum, uint8_t sMax);
#define GetParentCursor(_ns)	GetCursor(GetParent(_ns))

typedef struct st_Menu tMenu;
struct st_Menu{
	uint16_t cursorNum;
	uint8_t* menuText; ///should be defined in 16 characters.
	uint8_t numOfChildren;
	uint8_t parentIndex;///index differs from ID
	void (*actFunction)(void);
};

tMenu MenuMain[TOTAL_MENU];
void CharMenuInit(void);
void CharMenuRelink(void);
void CharMenuDraw(void);
#endif

