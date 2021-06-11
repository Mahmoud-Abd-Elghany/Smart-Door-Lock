/*
 * USART.h
 *
 * Created: 4/23/2021 1:16:33 PM
 *  Author: MAZ
 */ 


#ifndef USART_H_
#define USART_H_

/*Should be defined from uC configuration file*/
#ifndef F_CPU
#define F_CPU 1000000
#endif

#define NULL_PTR ((void*)0)

typedef enum
	{
		USART_SingleProcessor, 
		USART_MultiProcessor,
	}USART_CommunicationMode;
	
typedef enum
	{
		USART_Async_NormalSpeed,
		USART_Async_DoubleSpeed,
		USART_Sync,
	}USART_OperationMode;

typedef enum
	{
		USART_Disable,
		USART_Tx_Enable,
		USART_Rx_Enable,
		USART_Tx_Rx_Enable,
	}USART_EnableMode;

typedef enum
	{
		USART_Interrupt_Disable,
		USART_RxComp_Enable,
		USART_TxComp_Enable,
		USART_UDREmpty_Enable,
		USART_RxComp_TxComp_Enable,
		USART_RxComp_UDREmpty_Enable,
		USART_TxComp_UDREmpty_Enable,
		USART_RxComp_TxComp_UDREmpty_Enable,
	}USART_InterruptEnable;

typedef enum
	{
		USART_5bit,
		USART_6bit,
		USART_7bit,
		USART_8bit,
		USART_9bit,
	}USART_DataFrame;
	
typedef enum
	{
		USART_ParityDisable_1Stopbit,
		USART_ParityDisable_2StopBit,
		USART_ParityEven_1StopBit,
		USART_ParityEven_2StopBit,
		USART_ParityOdd_1StopBit,
		USART_ParityOdd_2StopBit,
	}USART_CheckFrame;

typedef enum
	{
		USART_Sample_Falling,
		USART_Sample_Rising,
	}USART_ClockPolarity;
	
typedef enum
	{
		USART_Parity_Error,
		USART_DataOverrun_Error,
		USART_Frame_Error,
	}USART_ErrorType;

typedef struct 
	{
		/* Check enums to determine which option to select */
		USART_EnableMode EnableMode;
		USART_CommunicationMode CommunicationMode;
		USART_OperationMode OperationMode;
		USART_InterruptEnable InterruptEnable;
		USART_DataFrame DataFrame;
		USART_CheckFrame CheckFrame;
		USART_ClockPolarity ClockPolarity; //Only in Sync Mode
		USART_ErrorType ErrorType;
		/* Assign the Function (to be Called) by RXC Interrupt to this pointer */
		void (*RxComp_Interrupt_CallBack)(void);
		/* Assign the Function (to be Called) by TXC Interrupt to this pointer */
		void (*TxComp_Interrupt_CallBack)(void);
		/* Assign the Function (to be Called) by UDRE Interrupt to this pointer */
		void (*UDREmpty_Interrupt_CallBack)(void);
		unsigned long BaudRate;
	}USART_Config;

extern USART_Config USART_config_0;

void USART_init(void);
void USART_sendByte_Polling(unsigned short);
unsigned short USART_recieveByte_Polling(void);


#endif /* USART_H_ */