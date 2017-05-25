#ifndef CHAR_MENU_SETTINGS_H
#define CHAR_MENU_SETTINGS_H


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


#endif
