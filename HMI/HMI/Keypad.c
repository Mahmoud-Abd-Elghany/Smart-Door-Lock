/*
 * Keypad.c
 *
 * Created: 5/30/2021 8:18:41 PM
 *  Author: Mahmoud Abdelghany
 */ 

#include <avr/io.h>
#include "Keypad.h"

/*Special Characters returned as ASCII Code*/
/* Used for Phone-like keypad */
/*This function returns equivalent no. to the pressed button */
static unsigned char Keypad_buttonNumber_4x3(unsigned char No){
	switch(No){
		case 10:
			return '*';
		break;
		case 11:
			return 0;
		break;
		case 12:
			return '#';
		break;
		default: 
			return No; 
		break;
	}
}

/* Used for Calculator-like keypad */
/*This function returns equivalent no. to the pressed button */
static unsigned char Keypad_buttonNumber_4x4(unsigned char No){
	switch(No){
		case 1:
			return 7;
		break;
		case 2:
			return 8;
		break;
		case 3:
			return 9;
		break;
		case 4:
			return '-';
		break;
		case 5:
			return 4;
		break;
		case 6:
			return 5;
		break;
		case 7:
			return 6;
		break;
		case 8:
			return '*';
		break;
		case 9:
			return 1;
		break;
		case 10:
			return 2;
		break;
		case 11:
			return 3;
		break;
		case 12:
			return '-';
		break;
		case 13:
			return '%';
		break;
		case 14:
			return 0;
		break;
		case 15:
			return '=';
		break;
		case 16:
			return '+';
		break;
		
	}
}

unsigned char Keypad_Pressed_Key(void){
	/* Lowest significant 4 pins : Row(Input) pins
	 * Highest significant 3 or 4 pins : Column(Float) pins */
	unsigned char col,row;
	while(1){
		for( col= 0; col < KEYPAD_COLUMNS; col++){
			KEY_PORT_DIR = (0x10<<col);
			KEY_PORT_OUT = (~(0x10<<col));
		
			for(row = 0; row < KEYPAD_ROWS; row++){
				if(!(KEY_PORT_IN & (1<< row))){ // checking if bit is low
					unsigned char Button_No = ((row*KEYPAD_COLUMNS)+col+1);
					#if (KEYPAD_COLUMNS == 3)
					return Keypad_buttonNumber_4x3(Button_No);
					#elif (KEYPAD_COLUMNS == 4)
					return Keypad_buttonNumber_4x4(Button_No);
					#endif
				}
			}
		}
	}
}