/**
 * (c) 2014-2016 Izzulmakin
 * based on makin.h (github.com/imakin/sarjiya)
 * 
 */
#ifndef CHAR_MENU_H
#define CHAR_MENU_H

#include <inttypes.h>
#include "settings.h"

#ifndef __CUSTOM_SETTINGS__
	///Menu uses 4 cm_Button, comprises Enter, Back, Previous, and Next, which defined here:
	#define CM_BUTTON_ENTER_PIN		PIND
	#define CM_BUTTON_BACK_PIN		PIND
	#define CM_BUTTON_PREV_PIN		PIND
	#define CM_BUTTON_NEXT_PIN		PIND
	#define CM_BUTTON_ENTER_PORT	PORTD
	#define CM_BUTTON_BACK_PORT		PORTD
	#define CM_BUTTON_PREV_PORT		PORTD
	#define CM_BUTTON_NEXT_PORT		PORTD
	///Enter the pin number for each of the cm_Button 
	#define CM_BUTTON_ENTER_DOWN	1 ///means Enter cm_Button is in PIND- bit 1
	#define CM_BUTTON_BACK_DOWN	2
	#define CM_BUTTON_PREV_DOWN	0
	#define CM_BUTTON_NEXT_DOWN	3
#endif

#define _set(_REG,_BIT) _REG |= (1<<_BIT) 			//set bit
#define _clear(_REG,_BIT) _REG &= ~(1<<_BIT) 		//clear bit
#define _togle(_REG,_BIT) _REG ^= (1<<_BIT)			//togle bit

#define isset(_REG,_BIT) bit_is_set(_REG,_BIT)
#define isclear(_REG,_BIT) bit_is_clear(_REG,_BIT)

/** wrap your LCD library here **/
void cm_DrawNumber(uint16_t bil, uint8_t x, uint8_t y,uint8_t _c);
//-- draw number in current cursor pos
void cm_DrawNumberCPos(uint16_t bil, uint8_t _c);
//-- Clears block with whitespace replacing
void cm_LcdDelete(uint8_t xawal, uint8_t xakhir, uint8_t _Y);
void cm_LcdInit(void);
void cm_LcdClear(void);
void cm_LcdString(uint8_t* string, uint8_t len);
void cm_LcdGotoXY(uint8_t x, uint8_t y);


uint8_t cm_ButtonEnter(void);
uint8_t cm_ButtonBack(void);
uint8_t cm_ButtonNext(void);
uint8_t cm_ButtonPrev(void);
void 	cm_ButtonWait(void);
uint8_t cm_ButtonIsPressed(void);
uint8_t cm_ButtonIsNotPressed(void);
uint8_t cm_ButtonRead(void);

void cm_PrintScroll(uint8_t sNum, uint8_t sMax);

typedef struct st_Menu tMenu;
struct st_Menu{
	void (*actFunction)(void);
	uint8_t *text; //-- should be defined in 16 characters. (padded with space if less to be 16 char)
	uint8_t cursorPos;
	uint8_t numOfSiblings; //-- num should be defined for best performance
	uint8_t numOfChildren;
	struct st_Menu *menuParent;
	struct st_Menu *menuNext; //-- next & previous sibling
	struct st_Menu *menuPrevious;
	struct st_Menu *menuChildF; //--if any, attach child in pos1 only
};
tMenu* cm_currentMenu;

void CharMenuInit(void);
void CharMenuDraw(void);

tMenu* cm_AddMenu(uint8_t *text, 
			uint8_t cursorPos, 
			uint8_t numOfSiblings,
			uint8_t numOfChildren,
			tMenu *menuParent,
			tMenu *menuNext, 
			tMenu *menuPrevious,
			tMenu *menuChildF,
			void (*actFunction)(void));


#endif

