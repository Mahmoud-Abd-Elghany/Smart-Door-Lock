/*
 * Keypad.h
 *
 * Created: 5/30/2021 8:18:53 PM
 *  Author: Mahmoud Abdelghany
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include <util/delay.h>


// PORT Configuration
#define KEY_PORT_DIR DDRA
#define KEY_PORT_OUT PORTA
#define KEY_PORT_IN PINA

// No. of Rows and Columns
#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 3

unsigned char Keypad_Pressed_Key(void);

#endif /* KEYPAD_H_ */