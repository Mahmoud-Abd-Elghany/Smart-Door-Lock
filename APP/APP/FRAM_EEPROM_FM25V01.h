/*
 * FRAM_EEPROM_FM25V01.h
 *
 * Created: 5/10/2021 4:18:29 AM
 *  Author: MAZ
 */ 


#ifndef FRAM_EEPROM_FM25V01_H_
#define FRAM_EEPROM_FM25V01_H_

#define WREN_OP		(0x06)
#define WRITE_OP	(0x02)
#define READ_OP		(0x03)
#define CS			(PB4)
#define DUMMY		(0xFF)

void EEPROM_init(void);
void EEPROM_writeByte(unsigned char data, unsigned short address);
unsigned char EEPROM_readByte(unsigned short address);



#endif /* FRAM_EEPROM_FM25V01_H_ */