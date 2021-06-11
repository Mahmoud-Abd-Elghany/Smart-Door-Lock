/*
 * LCD.c
 *
 * Created: 6/1/2021 9:18:50 PM
 *  Author: Mahmoud Abdelghany
 */ 

#include "LCD.h"

void LCD_init(){
	#if (LCD_PORT_UPPER_LOWER == UPPER)
	LCD_PORT_DIR |= (0xF0); // changing upper 4 pins to output pins
	#else
	LCD_PORT_DIR |= (0x0F); // changing lower 4 pins to output pins
	#endif
	_delay_ms(20);
	LCD_Send_Command(LCD_4BIT_MODE); // Initialize 4-bit mode
	LCD_Send_Command(LCD_4BIT_2LINES_MODE); //Initialize 16x2 mode
	LCD_Send_Command(LCD_DISPLAY_ON_CURSOR_ON);
	LCD_Send_Command(LCD_CLEAR_SCREEN); //Clearing screen
}

void LCD_Send_Command(unsigned char cmd){
	LCD_PORT_DIR |= (1<<RS_PIN) | (1<<ENABLE_PIN) | (1<<R_W_PIN); //Setting Enable, R/W and Register Select pins to output
	LCD_PORT_OUT &= (~(1<<RS_PIN)) & (~(1<<R_W_PIN));
	
	#if (LCD_PORT_UPPER_LOWER == UPPER)
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0x0F) | (cmd & 0xF0);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	_delay_ms(1);
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0x0F) | (cmd<<4);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	#else
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0xF0) | (cmd>>4);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	_delay_ms(1);
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0xF0) | (cmd & 0x0F);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	#endif
}

void LCD_Display_Character(unsigned char Char){
	if((Char >=0) && (Char<=9)){
		Char = Char + '0';
	}
	LCD_PORT_DIR |= (1<<RS_PIN) | (1<<ENABLE_PIN) | (1<<R_W_PIN); //Setting Enable, R/W and Register Select pins to output
	_delay_ms(1);
	LCD_PORT_OUT &= (~(1<<R_W_PIN));
	LCD_PORT_OUT |= (1<<RS_PIN);
	
	#if (LCD_PORT_UPPER_LOWER == UPPER)
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0x0F) | (Char & 0xF0);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	_delay_ms(1);
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0x0F) | (Char<<4);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	#else
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0xF0) | (Char>>4);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	_delay_ms(1);
	LCD_PORT_OUT |= (1<<ENABLE_PIN);
	LCD_PORT_OUT = (LCD_PORT_OUT & 0xF0) | (Char & 0x0F);
	LCD_PORT_OUT &= (~(1<<ENABLE_PIN));
	#endif
}

void LCD_Display_String(unsigned char *str){
	signed char i = 0;
	while(str[i] != '\0'){
		LCD_Display_Character(str[i]);
		i++;
	}
}