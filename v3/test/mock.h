#ifndef MOCK_H
#define MOCK_H

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include "settings.h"

extern uint8_t CHARMENU_BUTTON_ENTER_PIN;
extern uint8_t CHARMENU_BUTTON_ENTER_PORT;
#define TESTPORT CHARMENU_BUTTON_ENTER_PORT
#define TESTPIN CHARMENU_BUTTON_ENTER_PIN

uint8_t bit_is_clear(uint8_t reg, uint8_t bit);
uint8_t bit_is_set(uint8_t reg, uint8_t bit);

void LCDstring(uint8_t *string, uint8_t length);
void LCDGotoXY(uint8_t x, uint8_t y);
void LCDprint();
//simulation of LCD
typedef struct LCD_st LCD;
struct LCD_st {
	uint8_t *data_0;//top part of LCD 
	uint8_t *data_1;//bottom part of LCD
	uint8_t x;//cursor x (0 to 16)
	uint8_t y;//cursor y (top/bottom)
};
extern LCD lcd;

#define assertEqual(a,b) if (a!=b) {printf("assertEqual error, not equal\n"); exit (1);}

#endif
