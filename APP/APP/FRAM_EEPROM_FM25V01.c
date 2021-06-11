/*
 * FRAM_EEPROM_FM25V01.c
 *
 * Created: 5/10/2021 4:18:15 AM
 *  Author: MAZ
 */ 

#include "Atmega16_SPI.h"
#include "FRAM_EEPROM_FM25V01.h"
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000

static void CS_set(unsigned char State){
	switch(State){
		case 0:
			PORTB &= (~(1<<CS));
		break;
		case 1:
			PORTB |= (1<<CS);
		break;
	}
}

void EEPROM_init(void){
	SPI_Config SPI_Config_0 = {.ClkFreq = SPI_Freq_By_4,
								.ClkMode = SPI_ClkPol1_ClkPha1,
								.Interrupt = SPI_Interrupt_Disable,
								.SpeedMode = SPI_NormalSpeed_Mode,
								.State = SPI_ON,
								.DataOrder = SPI_MSB,
								.Mode = SPI_Master};
	SPI_init();
}

void EEPROM_writeByte(unsigned char data, unsigned short address){
		unsigned char MS_8bit_address = (address>>8);
		unsigned char LS_8bit_address = (unsigned char)address;
	// 1- Select EEPROM by Setting CS(Chip Select) to 0
		CS_set(0);
	// 2- Activating Write Latch Enable
		SPI_Read_Write_Byte(WREN_OP);
	// 3- Setting CS(Chip Select) to 1 for a while then changing it to 0 again
		CS_set(1);
		_delay_ms(2);
	// 4- Sending Write Opcode
		CS_set(0);
		SPI_Read_Write_Byte(WRITE_OP);
	// 5- Sending Address (14-bit address)(0x0000-0x3FFF)
		SPI_Read_Write_Byte(MS_8bit_address);
		SPI_Read_Write_Byte(LS_8bit_address);
	// 6- Sending Data
		SPI_Read_Write_Byte(data);
		CS_set(1);
		_delay_ms(2);
}

unsigned char EEPROM_readByte(unsigned short address){
	unsigned char ReadData = 0;
	unsigned char MS_8bit_address = (address>>8);
	unsigned char LS_8bit_address = (unsigned char)address;
	// 1- Select EEPROM by Setting CS(Chip Select) to 0
		CS_set(0);
	// 2- Sending Read Opcode
		SPI_Read_Write_Byte(READ_OP);
	// 3- Sending Address (14-bit)(0x0001-0x3FFF)
		SPI_Read_Write_Byte(MS_8bit_address);
		SPI_Read_Write_Byte(LS_8bit_address);
	// 4- Sending Dummy to Receive data
		ReadData = SPI_Read_Write_Byte(DUMMY);
		CS_set(1);
		return ReadData;
}