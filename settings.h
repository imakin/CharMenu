/**
 * this contains setting define used for CharMenu
 */
#ifndef CHAR_MENU_SETTINGS_H
#define CHAR_MENU_SETTINGS_H

/* you don't have to do it here, but you can:
 * wrap function for your LCD library */
/* Begin example for scienceprog's lcd_lib */
	//@ #define cm_LcdInit() LCDinit()
	//@ #define cm_LcdClear() LCDclr()
	//@ #define cm_LcdString(string,len) LCDstring(string,len)
	//@ #define cm_LcdGotoXY(x,y) LCDGotoXY(x,y)
/* End for scienceprog's lcd_lib */
/* Begin example for Arduino */
	//-- suppose you have LiquidCrystal object named lcd
	//@ #define lcdobj lcd
	//-- if you want to create LiquidCrytal object named lcd
	//@ #define cm_LcdInit() LiquidCrystal lcdobj(12, 11, 10, 5, 4, 3, 2);
	//-- or if you already created that object in other place in your code, then just do nothing
	//@ #define cm_LcdInit() ;
	//@ #define cm_LcdClear() lcdobj.clear()
	//@ #define cm_LcdString(string, len) lcdobj.write(string)
	//@ #define cm_LcdGotoXY(x,y) lcdobj.setCursor(x,y)
/* End for Arduino */


/* define/uncomment this macro if you want to use this custom settings */
//#define __CUSTOM_SETTINGS__

/*
 * Menu uses 4 cm_Button(s), 
 * comprise Enter, Back, Previous, and Next, 
 * which defined here:
 */
#define CM_BUTTON_ENTER_PIN		PIND
#define CM_BUTTON_BACK_PIN		PIND
#define CM_BUTTON_PREV_PIN		PIND
#define CM_BUTTON_NEXT_PIN		PIND
#define CM_BUTTON_ENTER_PORT	PORTD
#define CM_BUTTON_BACK_PORT		PORTD
#define CM_BUTTON_PREV_PORT		PORTD
#define CM_BUTTON_NEXT_PORT		PORTD
/*
 * Enter the pin number for each of the cm_Button 
 * means [Enter] cm_Button is in PIND- bit 1
 */
#define CM_BUTTON_ENTER_DOWN	1
#define CM_BUTTON_BACK_DOWN	2
#define CM_BUTTON_PREV_DOWN	0
#define CM_BUTTON_NEXT_DOWN	3

#endif
