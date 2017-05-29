#ifndef CHAR_MENU_SETTINGS_H
#define CHAR_MENU_SETTINGS_H



///Menu uses 4 cm_Button, comprises Enter, Back, Previous, and Next, which defined here:
// see AVR atmega registers: PORT, PIN, and DDR
#define CHARMENU_BUTTON_ENTER_PIN	PIND
#define CHARMENU_BUTTON_BACK_PIN	PIND
#define CHARMENU_BUTTON_PREV_PIN	PIND
#define CHARMENU_BUTTON_NEXT_PIN	PIND

#define CHARMENU_BUTTON_ENTER_PORT	PORTD
#define CHARMENU_BUTTON_BACK_PORT	PORTD
#define CHARMENU_BUTTON_PREV_PORT	PORTD
#define CHARMENU_BUTTON_NEXT_PORT	PORTD

#define CHARMENU_BUTTON_ENTER_DDR	DDRD
#define CHARMENU_BUTTON_BACK_DDR	DDRD
#define CHARMENU_BUTTON_PREV_DDR	DDRD
#define CHARMENU_BUTTON_NEXT_DDR	DDRD
///Enter the pin number for each of the BUTTON (Pull-UP)
#define CHARMENU_BUTTON_ENTER_DOWN	1 ///means Enter button is in PIND-bit 1
#define CHARMENU_BUTTON_BACK_DOWN	2
#define CHARMENU_BUTTON_PREV_DOWN	0
#define CHARMENU_BUTTON_NEXT_DOWN	3

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

#endif
