/*
 * Atmega16_SPI.h
 *
 * Created: 5/3/2021 8:43:42 AM
 *  Author: Mahmoud Abdelghany
 */ 


#ifndef ATMEGA16_SPI_H_
#define ATMEGA16_SPI_H_

#ifndef F_CPU
#define F_CPU 1000000
#endif

#define NULL_PTR ((void*)0)

#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

typedef enum
	{
		SPI_Interrupt_Enable,
		SPI_Interrupt_Disable,
	}SPI_Interrupt;
	
typedef enum 
	{
		SPI_MSB,
		SPI_LSB,
	}SPI_DataOrder;

typedef enum
	{
		SPI_ON,
		SPI_OFF,
	}SPI_State;

typedef enum
	{
		SPI_Master,
		SPI_Slave,
	}SPI_Mode;

typedef enum
	{
		SPI_Freq_By_4,
		SPI_Freq_By_16,
		SPI_Freq_By_64,
		SPI_Freq_By_128,
	}SPI_Clk_Freq;
	
typedef enum
	{
		SPI_NormalSpeed_Mode,
		SPI_DoubleSpeed_Mode,
	}SPI_SpeedMode;
	
typedef enum
	{
		SPI_ClkPol0_ClkPha0, /* Leading Edge: Sample(Rising) ,Trailing Edge: Setup(Falling) */ 
		SPI_ClkPol0_ClkPha1, /* Leading Edge: Setup(Rising) ,Trailing Edge: Sample(Falling) */ 
		SPI_ClkPol1_ClkPha0, /* Leading Edge: Sample(Falling) ,Trailing Edge: Setup(Rising) */ 
		SPI_ClkPol1_ClkPha1, /* Leading Edge: Setup(Falling) ,Trailing Edge: Sample(Rising) */ 
	}SPI_ClkMode;

typedef struct
	{
		/* Check enums to determine which option to select */
		SPI_ClkMode ClkMode;
		SPI_Clk_Freq ClkFreq;
		SPI_DataOrder DataOrder;
		SPI_Interrupt Interrupt;
		SPI_State State;
		SPI_SpeedMode SpeedMode;
		SPI_Mode Mode;
		void (*SPI_Interrupt_CallBack)(void);
	}SPI_Config;
	
	extern SPI_Config SPI_Config_0;
	
void SPI_init(void);
unsigned char SPI_Read_Write_Byte(unsigned char);
#endif /* ATMEGA16_SPI_H_ */