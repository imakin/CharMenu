#include "CharMenu.h"
#include <stdio.h>

#ifdef LINUX_TEST
	uint8_t PIND;
	uint8_t PORTD;
#endif

void CharMenu__button_wait()
{
	printf("sdposd%d",PIND);
	/** Let the system pause and wait for any cm_Button to be pressed */
	while (
		bit_is_set(CHARMENU_BUTTON_ENTER_PIN,CHARMENU_BUTTON_ENTER_DOWN) &&
		bit_is_set(CHARMENU_BUTTON_BACK_PIN, CHARMENU_BUTTON_BACK_DOWN) &&
		bit_is_set(CHARMENU_BUTTON_NEXT_PIN, CHARMENU_BUTTON_NEXT_DOWN) &&
		bit_is_set(CHARMENU_BUTTON_PREV_PIN, CHARMENU_BUTTON_PREV_DOWN)
	);
}

uint8_t CharMenu__button_read()
{
	/** Wait for any Button to be pressed and return which Button is pressed 
	 * Warning: delay is removed, when using, manually put delay after function called
	 * example:
	 *		charmenu->button_read();
	 * 		_delay_ms(100);
	 * */
	uint8_t output;
	CharMenu__button_wait();
	if (bit_is_clear(CHARMENU_BUTTON_ENTER_PIN,CHARMENU_BUTTON_ENTER_DOWN))
		output = CHARMENU_BUTTON_ENTER_DOWN;
	else if (bit_is_clear(CHARMENU_BUTTON_BACK_PIN,CHARMENU_BUTTON_BACK_DOWN))
		output = CHARMENU_BUTTON_BACK_DOWN;
	else if (bit_is_clear(CHARMENU_BUTTON_NEXT_PIN,CHARMENU_BUTTON_NEXT_DOWN))
		output = CHARMENU_BUTTON_NEXT_DOWN;
	else 
		output = CHARMENU_BUTTON_PREV_DOWN;
	return (output);
}

uint8_t CharMenu__button_is_pressed(uint8_t button)
{
	return 0;
}
