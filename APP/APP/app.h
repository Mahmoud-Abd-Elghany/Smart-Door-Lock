/*
 * app.h
 *
 * Created: 6/7/2021 1:12:38 AM
 *  Author: MAZ
 */ 


#ifndef APP_H_
#define APP_H_

#include <avr/io.h>
#include <util/delay.h>
#include "Atmega16_USART.h"
#include "FRAM_EEPROM_FM25V01.h"

#define EEPROM_SYS_PASS_ADDRESS (0x0014)
#define EEPROM_PASS_IS_SET_ADDRESS (0x0004)

 unsigned char Check_enteredPass (void);
 void Assign_sysPass(void);
 unsigned char Check_With_sysPass (void);
 void dummy_Write(void);

#endif /* APP_H_ */