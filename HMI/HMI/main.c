/*
 * HMI.c
 *
 * Created: 6/1/2021 7:17:10 PM
 * Author : MAZ
 */ 

#include "main.h"
unsigned char Password_is_set;


int main(void)
{
	USART_init();
	LCD_init();
	Password_is_set = USART_recieveByte_Polling();
    while (1)
	{
		if(Password_is_set){
			Send_enteredPass();
			_delay_ms(800);
			LCD_Send_Command(LCD_CLEAR_SCREEN);
		}
		else{
			Send_sysPass();
			_delay_ms(800);
			LCD_Send_Command(LCD_CLEAR_SCREEN);
		}
				
	}
}

/* Comparing Entered password with System password */
void Send_enteredPass(void){
	LCD_Display_String("Password:");
	LCD_Send_Command(LCD_GOTO_2ND_ROW);
	Send_enteredKeys();
	LCD_Send_Command(LCD_CLEAR_SCREEN);
	unsigned char Password_State = USART_recieveByte_Polling();
	switch(Password_State){
		case 0:
		LCD_Display_String("Access Rejected");
		break;
		case 1:
		LCD_Display_String("Access Granted");
		break;
		/* Resetting Password */ 
		case 2:
		LCD_Display_String("Reset Password?");
		LCD_Send_Command(LCD_GOTO_2ND_ROW);
		LCD_Display_String("1:Yes   2:No");
		unsigned char Answer = Keypad_Pressed_Key();
		_delay_ms(400);
		switch(Answer){
			unsigned char Response;
			case 1:
				LCD_Send_Command(LCD_CLEAR_SCREEN);
				LCD_Display_String("Old Password:");
				LCD_Send_Command(LCD_GOTO_2ND_ROW);
				Send_enteredKeys();
				Response = USART_recieveByte_Polling();
				if(Response){
					LCD_Send_Command(LCD_CLEAR_SCREEN);
					LCD_Display_String("New Password:");
					LCD_Send_Command(LCD_GOTO_2ND_ROW);
					Send_enteredKeys();
				}
				else{
					LCD_Send_Command(LCD_CLEAR_SCREEN);
					LCD_Display_String("Wrong Password");
					LCD_Send_Command(LCD_CLEAR_SCREEN);
				}
			break;
			default:
			LCD_Send_Command(LCD_CLEAR_SCREEN);
			LCD_Display_String("Ok");
			_delay_ms(500);
			break;
		}
	}
}

void Send_sysPass(void){
	LCD_Display_String("Assign New");
	LCD_Send_Command(LCD_GOTO_2ND_ROW);
	LCD_Display_String("Password:");
	Send_enteredKeys();
	Password_is_set = 1;
}

void Send_enteredKeys(void){
	unsigned char key;
	for (unsigned char i = 0; i < 4; i++){
		key = Keypad_Pressed_Key();
		USART_sendByte_Polling(key);
		LCD_Display_Character(key);
		_delay_ms(400);
	}
}