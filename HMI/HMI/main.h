/*
 * main.h
 *
 * Created: 6/5/2021 5:34:13 AM
 *  Author: MAZ
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "LCD.h"
#include "Keypad.h"
#include "Atmega16_USART.h"

void Send_enteredPass(void);
void Send_sysPass(void);
void Send_enteredKeys(void);



#endif /* MAIN_H_ */