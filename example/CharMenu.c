/**
 * (c) 2014-2016 Izzulmakin
 * based on makin.h (github.com/imakin/sarjiya)
 * 
 */
#include "CharMenu.h"
#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include "lcd_lib.h"
#include <util/delay.h>


void cm_DrawNumber(uint16_t bil, uint8_t x, uint8_t y,uint8_t _c)
{
	uint8_t pjg;
	char lcdchar[30];
			cm_LcdGotoXY(x,y);
			if (_c!=0)
			{
				
				for (uint8_t i=1; i<=_c; i++)
				{
					cm_LcdString((uint8_t*)" ",1);
				}
				cm_LcdGotoXY(x,y);
			}
			snprintf(lcdchar,15, "%d",bil);
			pjg = strlen(lcdchar);
			cm_LcdString((uint8_t*)lcdchar,pjg);
	
}
///
void cm_DrawNumberCPos(uint16_t bil, uint8_t _c)
{
	uint8_t pjg;
	char lcdchar[30];
	if (_c!=0)
	{
		
		for (uint8_t i=1; i<=_c; i++)
		{
			cm_LcdString((uint8_t*)" ",1);
		}
	}
	snprintf(lcdchar,15, "%d",bil);
	pjg = strlen(lcdchar);
	cm_LcdString((uint8_t*)lcdchar,pjg);
	
}

///Clears block with whitespace replacing
void cm_LcdDelete(uint8_t xawal, uint8_t xakhir, uint8_t _Y)
{
	cm_LcdGotoXY(xawal,_Y);
	for (uint8_t i=xawal;i<=xakhir;i++)
	{
		cm_LcdString((uint8_t*)" ",1);
	}
}

/**  return is it true that particular cm_Button is pressed (Enter, Back, Next, Prev)*/
uint8_t cm_ButtonEnter()
{
	return isclear(CM_BUTTON_ENTER_PIN,CM_BUTTON_ENTER_DOWN);
}
uint8_t cm_ButtonBack()
{
	return isclear(CM_BUTTON_BACK_PIN,CM_BUTTON_BACK_DOWN);
}
uint8_t cm_ButtonNext()
{
	return isclear(CM_BUTTON_NEXT_PIN,CM_BUTTON_NEXT_DOWN);
}
uint8_t cm_ButtonPrev()
{
	return isclear(CM_BUTTON_PREV_PIN,CM_BUTTON_PREV_DOWN);
}



void cm_ButtonWait()
{
	/** Let the system pause and wait for any cm_Button to be pressed */
	while (isset(CM_BUTTON_ENTER_PIN,CM_BUTTON_ENTER_DOWN) && isset(CM_BUTTON_BACK_PIN,CM_BUTTON_BACK_DOWN) && isset(CM_BUTTON_NEXT_PIN,CM_BUTTON_NEXT_DOWN) && isset(CM_BUTTON_PREV_PIN,CM_BUTTON_PREV_DOWN));
}
uint8_t cm_ButtonIsPressed()
{
	/** Check if there are (any) cm_Button pressed */
	return (isclear(CM_BUTTON_ENTER_PIN,CM_BUTTON_ENTER_DOWN) || isclear(CM_BUTTON_BACK_PIN,CM_BUTTON_BACK_DOWN) || isclear(CM_BUTTON_NEXT_PIN,CM_BUTTON_NEXT_DOWN) || isclear(CM_BUTTON_PREV_PIN,CM_BUTTON_PREV_DOWN));
}
uint8_t cm_ButtonIsNotPressed()
{
	/** Check if all cm_Button is currently not pressed */
	return (isset(CM_BUTTON_ENTER_PIN,CM_BUTTON_ENTER_DOWN) || isset(CM_BUTTON_BACK_PIN,CM_BUTTON_BACK_DOWN) || isset(CM_BUTTON_NEXT_PIN,CM_BUTTON_NEXT_DOWN) || isset(CM_BUTTON_PREV_PIN,CM_BUTTON_PREV_DOWN));
}
uint8_t cm_ButtonRead()
{
	/** Wait for any cm_Button to be pressed and return which cm_Button is pressed */
	uint8_t output;
	cm_ButtonWait();
	if (isclear(CM_BUTTON_ENTER_PIN,CM_BUTTON_ENTER_DOWN))
		output = CM_BUTTON_ENTER_DOWN;
	else if (isclear(CM_BUTTON_BACK_PIN,CM_BUTTON_BACK_DOWN))
		output = CM_BUTTON_BACK_DOWN;
	else if (isclear(CM_BUTTON_NEXT_PIN,CM_BUTTON_NEXT_DOWN))
		output = CM_BUTTON_NEXT_DOWN;
	else 
		output = CM_BUTTON_PREV_DOWN;
	_delay_ms(100);
	return (output);
}

tMenu* cm_AddMenu(uint8_t* text, 
			uint8_t cursorPos, 
			uint8_t numOfSiblings,//-- please predefine these for best performance
			uint8_t numOfChildren,//-- please predefine these for best performance
			tMenu* menuParent,
			tMenu* menuNext,
			tMenu* menuPrevious,
			tMenu* menuChildF,//-- optional can be set to 0, will be updated when child menu added
			void (*actFunction)(void))
{
	//--- add menu function, if no pointer is meant to be attached put 0 to it
	tMenu* newMenu = malloc(sizeof(tMenu));
	newMenu->text = text;
	newMenu->cursorPos = cursorPos;
	newMenu->numOfSiblings = numOfSiblings;
	newMenu->numOfChildren = numOfChildren;
	newMenu->menuParent = menuParent;
	newMenu->menuNext = menuNext;
	newMenu->menuPrevious = menuPrevious;
	newMenu->menuChildF = menuChildF;
	newMenu->actFunction = actFunction;
	if (cursorPos==1 && menuParent!=0)
	{
		newMenu->menuParent->menuChildF = newMenu;
	}
	return newMenu;
}

void CharMenuInit()
{
	CM_BUTTON_ENTER_PORT |= (1<<CM_BUTTON_ENTER_DOWN);
	CM_BUTTON_BACK_PORT |= (1<<CM_BUTTON_BACK_DOWN);
	CM_BUTTON_NEXT_PORT |= (1<<CM_BUTTON_NEXT_DOWN);
	CM_BUTTON_PREV_PORT |= (1<<CM_BUTTON_PREV_DOWN);
}


void CharMenuDraw()
{
	/**
	 * draw current menu, & listen Button press
	 */
	cm_LcdGotoXY(0,0);
	cm_LcdString(cm_currentMenu->text, 16);
	cm_PrintScroll(cm_currentMenu->cursorPos, 1+cm_currentMenu->numOfSiblings);
	uint8_t action = cm_ButtonRead();
	switch (action) {
		case CM_BUTTON_ENTER_DOWN:
			//-- typically either child menu or actFunction should be defined
			if (cm_currentMenu->actFunction!=0)
			{
				cm_currentMenu->actFunction();
				cm_currentMenu = cm_currentMenu->menuParent;
			}
			if (cm_currentMenu->menuChildF!=0)
			{
				cm_currentMenu = cm_currentMenu->menuChildF;
			}
			break;
		case CM_BUTTON_NEXT_DOWN:
			if (cm_currentMenu->menuNext!=0)
				cm_currentMenu = cm_currentMenu->menuNext;
			else//--rotate to left most sibling
				while(cm_currentMenu->menuPrevious!=0)
					cm_currentMenu = cm_currentMenu->menuPrevious;
			break;
		case CM_BUTTON_PREV_DOWN:
			if (cm_currentMenu->menuPrevious!=0)
				cm_currentMenu = cm_currentMenu->menuPrevious;
			else//--rotate to right most sibling
				while(cm_currentMenu->menuNext!=0)
					cm_currentMenu = cm_currentMenu->menuNext;
			
			break;
		case CM_BUTTON_BACK_DOWN:
			if (cm_currentMenu->menuParent!=0)
				cm_currentMenu = cm_currentMenu->menuParent;
			break;
	}
	return;
}


void cm_PrintScroll(uint8_t sNum, uint8_t sMax)
{
	cm_LcdGotoXY(0,1);
	//~ LCDprogressBar(sNum, sMax,16);
	//~ return;
	uint8_t progress=sNum; uint8_t maxprogress=sMax; uint8_t length=16;
	uint8_t i;
	uint16_t pixelprogress;
	uint8_t c;
	uint8_t progresswidth = length/maxprogress;
	pixelprogress = ((progress*(length*PROGRESSPIXELS_PER_CHAR))/maxprogress)/2;
	
	// print exactly "length" characters
	for(i=0; i<length; i++)
	{
		if (
			(
				((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)+progresswidth)>(pixelprogress-progresswidth)
			)
			&&
			(
				((i*(uint16_t)PROGRESSPIXELS_PER_CHAR)+progresswidth)<(pixelprogress+progresswidth)
			)
		)
		{
			c = 5;
		}
		else
		{
			c = 0;
		}
		// write character to display
		LCDsendChar(c);
	}
	return;
}
