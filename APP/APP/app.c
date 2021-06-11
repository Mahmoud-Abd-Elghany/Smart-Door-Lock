/*
 * APP.c
 *
 * Created: 6/7/2021 1:05:18 AM
 * Author : MAZ
 */ 

#include "app.h"

unsigned char Pass_is_Set;

int main(void)
{
	USART_init();
	EEPROM_init();
	dummy_Write();
	Pass_is_Set = EEPROM_readByte(EEPROM_PASS_IS_SET_ADDRESS); //0x0004 address used for the variable which declare password is set or not
	USART_sendByte_Polling(Pass_is_Set);
    while (1)
    {
		if(Pass_is_Set){
			Check_enteredPass();
		}
		else{
			Assign_sysPass();
		}
    }
}

unsigned char Check_enteredPass (void){
	unsigned char Pass_check = 0; // Variable to count the number of successful compares happened
	unsigned char Reset_check = 0;
	unsigned char key;
	for (char i = 0; i < 4; i++){
		key = USART_recieveByte_Polling();
		if(key == EEPROM_readByte((EEPROM_SYS_PASS_ADDRESS+i))) // Receiving Password and comparing it with saved one in the EEPROM
		{
			Pass_check++;
		}
		else if(key == '*'){
			Reset_check ++;
		}
	}
	
	if(Pass_check == 4){
		USART_sendByte_Polling(1); //Sending 1 if Pass is Right
	}
	
	else if(Reset_check == 4){
		USART_sendByte_Polling(2); //Sending 2 For password reseting command
		unsigned char Response = Check_With_sysPass(); 
		if(Response){
			USART_sendByte_Polling(Response);
			Assign_sysPass();
		}
		else{
			USART_sendByte_Polling(Response);
		}
	}
	else{
		USART_sendByte_Polling(0); //Sending 0 if Pass is Wrong
	}
}

/* 
* Used for write protection error
* should be used before every Write Operation or Write loop operation
*/
 void dummy_Write(void){
	EEPROM_writeByte(0x00, 0x0000);
}

void Assign_sysPass(void){
		dummy_Write();
		unsigned char key;
		for (unsigned char i = 0; i < 4; i++){
			key = USART_recieveByte_Polling();
			EEPROM_writeByte(key, (EEPROM_SYS_PASS_ADDRESS+i));
		}
		Pass_is_Set = 1;
		EEPROM_writeByte(Pass_is_Set, EEPROM_PASS_IS_SET_ADDRESS);
}

unsigned char Check_With_sysPass (void){
		unsigned char Pass_check = 0; // Variable to count the number of successful compares happened
		unsigned char key;
		for (char i = 0; i < 4; i++){
			key = USART_recieveByte_Polling();
			if(key == EEPROM_readByte((EEPROM_SYS_PASS_ADDRESS+i))) // Receiving Password and comparing it with saved one in the EEPROM
			{
				Pass_check++;
			}
		}
		return (Pass_check == 4);
}