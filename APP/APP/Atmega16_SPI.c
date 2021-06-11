/*
 * Atmega16_SPI.c
 *
 * Created: 5/3/2021 8:43:23 AM
 *  Author: Mahmoud Abdelghany
 */ 

#include "Atmega16_SPI.h"
#include <avr/io.h>
#include <avr/interrupt.h>

ISR (SPI_STC_vect){
	if(SPI_Config_0.SPI_Interrupt_CallBack != NULL_PTR){
		SPI_Config_0.SPI_Interrupt_CallBack();
	}
	else{
		/* Error Handling */
	}
}

SPI_Config SPI_Config_0 = {0,
							.SPI_Interrupt_CallBack = NULL_PTR};


void SPI_init(void){
	switch (SPI_Config_0.DataOrder)
	{
		case SPI_LSB:
			SPCR |= (1<<DORD);
		break;
		case SPI_MSB:
		break; 
	}
	
	switch (SPI_Config_0.Interrupt)
	{
		case SPI_Interrupt_Enable:
			SPCR |= (1<<SPIE);
		break;
		case SPI_Interrupt_Disable:
		break;
	}
	
	switch (SPI_Config_0.SpeedMode)
	{
		case SPI_NormalSpeed_Mode:
		break;
		case SPI_DoubleSpeed_Mode:
		 SPSR |= (1<<SPI2X);
		break;
	}
	
	switch (SPI_Config_0.ClkFreq)
	{
		case SPI_Freq_By_4:
		break;
		case SPI_Freq_By_16:
		SPCR |= (1<<SPR0);
		break;
		case SPI_Freq_By_64:
		SPCR |= (1<<SPR1);
		break;
		case SPI_Freq_By_128:
		SPCR |= (1<<SPR0) | (1<<SPR1);
		break;
	}
	
	switch(SPI_Config_0.Mode)
	{
		case SPI_Master:
		SPCR |= (1<<MSTR);
		DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SS);
		break;
		case SPI_Slave:
		break;
	}
	
	switch (SPI_Config_0.ClkMode)
	   /* 
		* Note: Using SPI mode 3 or 2, Clk IDLE STATE is High
		* in some uC we must change the default state of the pin to HIGH
		* so we set the CLK pin to HIGH
		*/
	{
		case SPI_ClkPol0_ClkPha0:
		SPCR &= (~(1<<CPHA)) & (~(1<<CPOL));
		break;
		case SPI_ClkPol0_ClkPha1:
		SPCR |= (1<<CPHA);
		break;
		case SPI_ClkPol1_ClkPha0:
		SPCR |= (1<<CPOL);
		PORTB |= (1<< PB7);
		break;
		case SPI_ClkPol1_ClkPha1:
		SPCR |= (1<<CPOL) | (1<<CPHA);
		PORTB |= (1<< PB7);
		break;
	}
	
	switch (SPI_Config_0.State)
	{
		case SPI_ON:
		SPCR |= (1<<SPE);
		break;
		case SPI_OFF:
		break;
	}
}

unsigned char SPI_Read_Write_Byte(unsigned char byte)
{
	SPDR = byte;
	while ((SPSR & (1<<SPIF)) == 0){}
	return SPDR;
}