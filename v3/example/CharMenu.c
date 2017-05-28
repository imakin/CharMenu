#include "CharMenu.h"


/**
 * Main process for the CharMenu framework.
 * this process will show menus and listen to any button pressed, 
 * and execute each menu selected
 */
void CharMenu__draw(CharMenu *self)
{
	if (self->current_menu==NULL)
	{
		self->current_menu = self->menu_root->child_head;
	}
	__lcd_gotoXY(0,0);
	__lcd_string(self->current_menu->text,16);
	self->print_scroll(
				self,
				self->current_menu->pos,
				self->current_menu->parent->children
			);
	uint8_t action = self->button_read(self);
	switch(action) {
		case CHARMENU_BUTTON_ENTER_DOWN:
			//Each Menu should have either action or having children
			if (self->current_menu->action!=NULL)
			{
				self->current_menu->action();//Execution here (will be blocking)
			}
			else if (self->current_menu->child_head!=NULL)
			{
				self->current_menu = self->current_menu->child_head;
			}
		break;
		case CHARMENU_BUTTON_NEXT_DOWN:
			if (self->current_menu->next!=NULL)
			{
				self->current_menu = self->current_menu->next;
			}
			else
			{
				//rotate to the oldest sibling
				while (self->current_menu->prev!=NULL)
					self->current_menu = self->current_menu->prev;
			}
		break;
		case CHARMENU_BUTTON_PREV_DOWN:
			if (self->current_menu->prev!=NULL)
			{
				self->current_menu = self->current_menu->prev;
			}
			else
			{
				//rotate to the youngest sibling
				while (self->current_menu->next!=NULL)
					self->current_menu = self->current_menu->next;
			}
		break;
		case CHARMENU_BUTTON_BACK_DOWN:
			if (self->current_menu->parent!=NULL)
			{
				self->current_menu = self->current_menu->parent;
			}
		break;
	}
	return;
}


void CharMenu__init(CharMenu *self)
{
	
	self->button_wait = &CharMenu__button_wait;
	self->button_is_pressed = &CharMenu__button_is_pressed;
	self->button_read = &CharMenu__button_read;
	self->draw = &CharMenu__draw;
	self->lcd_number = &CharMenu__lcd_number;
	self->print_scroll = &CharMenu__print_scroll;
	self->current_menu = NULL;
	self->menu_root = new_Menu(self->menu_root);
	
	self->menu_root->text = "ENTER]     [BACK";
	
	CHARMENU_BUTTON_BACK_PORT |= (1<<CHARMENU_BUTTON_BACK_DOWN);
	CHARMENU_BUTTON_ENTER_PORT |= (1<<CHARMENU_BUTTON_ENTER_DOWN);
	CHARMENU_BUTTON_NEXT_PORT |= (1<<CHARMENU_BUTTON_NEXT_DOWN);
	CHARMENU_BUTTON_PREV_PORT |= (1<<CHARMENU_BUTTON_PREV_DOWN);
}

/** Wait for any Button to be pressed */
void CharMenu__button_wait(CharMenu *self)
{
	/** Let the system pause and wait for any cm_Button to be pressed */
	while (
		bit_is_set(CHARMENU_BUTTON_ENTER_PIN,CHARMENU_BUTTON_ENTER_DOWN) &&
		bit_is_set(CHARMENU_BUTTON_BACK_PIN, CHARMENU_BUTTON_BACK_DOWN) &&
		bit_is_set(CHARMENU_BUTTON_NEXT_PIN, CHARMENU_BUTTON_NEXT_DOWN) &&
		bit_is_set(CHARMENU_BUTTON_PREV_PIN, CHARMENU_BUTTON_PREV_DOWN)
	);
}

/** Wait for any Button to be pressed and return which Button is pressed 
 * Warning: delay is removed, when using, manually put delay after function called
 * this is important to give the time the User release the button before any next instruction executed,
 * example:
 *		charmenu->button_read(charmenu);
 * 		_delay_ms(100);
 * */
uint8_t CharMenu__button_read(CharMenu *self)
{
	uint8_t output;
	self->button_wait(self);
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

uint8_t CharMenu__button_is_pressed(CharMenu *self, uint8_t button)
{
	return 0;
}

/**
 * print number to LCD current position,
 * @param number: the number to be printed
 * @param pad: the space reserved for the number.
 * 		for example:
 * 		 pad=4, number= 30
 * 			print "  30"
 * 		 pad=2, number= 30
 * 			print "30"
 * 		 pad=4, number= 2384
 * 			print "2384"
 * 		 pad=4, number= 9
 * 			print "   9"
 */
void CharMenu__lcd_number(CharMenu *self, uint8_t number, uint8_t pad)
{
	uint8_t len;
	char lcdchar[20];
	uint8_t i;
	len = snprintf(lcdchar,15, "%d", number);
	for (i=0;i<pad-len;i++)
	{
		__lcd_string((uint8_t*)" ",1);
	}
	__lcd_string((uint8_t *)lcdchar,len);
}


/**
 * print scroll bar to the bottom part of LCD
 * @param pos: is the position of the scroll
 * @param scale: is the length of the scroll
 */
void CharMenu__print_scroll(CharMenu *self, uint8_t pos, uint8_t scale)
{
	const uint8_t pixels_per_char = 6;
	uint8_t max_chars = 9;
	if (scale<max_chars)
		max_chars = scale; //scroll is only small
	
	uint8_t i;
	uint8_t c[1]; //the character 
	__lcd_gotoXY(0,1);
	for (i=0;i<max_chars;i++)
	{
		if (i==(pos*max_chars/scale))
			c[0] = (uint8_t)124;//"|"
		else
			c[0] = (uint8_t)45;//"-"
		__lcd_string(c, 1);
	}
	__lcd_gotoXY(9,1);
	self->lcd_number(self, pos+1, 3);
	__lcd_string("/",1);
	self->lcd_number(self, scale,3);
	return;
}





void Menu__destroy(Menu *self)
{
	free(self);
}


void Menu__add_child(Menu* self,Menu* child)
{
	/**
	 * add child to self as its child_tail
	 */
	child->parent = self;
	child->pos = self->children;
	if (self->child_tail==NULL)
	{
		//self has no any child yet
		self->child_head = child;
		self->child_tail = child;
		self->children = 1;
	}
	else
	{
		//append child to self's children
		self->child_tail->next = child;
		child->prev = self->child_tail;
		self->child_tail = child;
		self->children += 1;
	}
}

