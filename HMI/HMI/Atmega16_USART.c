/*
 * USART.c
 *
 * Created: 4/23/2021 1:02:42 PM
 * Author : MAZ
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Atmega16_USART.h"


USART_Config USART_config_0 = {.CheckFrame = USART_ParityDisable_1Stopbit,
								.BaudRate = 9600,
								.ClockPolarity = USART_Sample_Falling,
								.CommunicationMode = USART_SingleProcessor,
								.DataFrame = USART_8bit,
								.EnableMode = USART_Tx_Rx_Enable,
								.InterruptEnable = USART_Interrupt_Disable,
								.OperationMode= USART_Async_DoubleSpeed,
								.RxComp_Interrupt_CallBack = NULL_PTR,
								.TxComp_Interrupt_CallBack = NULL_PTR,
								.UDREmpty_Interrupt_CallBack = NULL_PTR};
	
ISR(USART_RXC_vect){
	if(USART_config_0.RxComp_Interrupt_CallBack != NULL_PTR)
	{
		USART_config_0.RxComp_Interrupt_CallBack();
	}
	else{
		//Handling Error Function
	}
}

ISR(USART_TXC_vect){
	if(USART_config_0.TxComp_Interrupt_CallBack != NULL_PTR)
	{
		USART_config_0.TxComp_Interrupt_CallBack();
	}
	else{
		//Handling Error Function
	}
}

ISR(USART_UDRE_vect){
	if(USART_config_0.UDREmpty_Interrupt_CallBack != NULL_PTR)
	{
		USART_config_0.UDREmpty_Interrupt_CallBack();
	}
	else{
		//Handling Error Function
	}
}

void USART_init(void){
	char UCSRA_temp = 0;
	char UCSRB_temp = 0;
	char UCSRC_temp = 0;
	float BaudRate = 0; //Value to be put in UBRR register
	
	switch (USART_config_0.EnableMode)
	{
		case USART_Disable:
		break;
		case USART_Rx_Enable:
			UCSRB_temp |= (1<<RXEN); //Rx Pin enable
		break;
		case USART_Tx_Enable:
			UCSRB_temp |= (1<<TXEN); //Tx Pin enable
		break;
		case USART_Tx_Rx_Enable:
			UCSRB_temp = UCSRB_temp | (1<<TXEN) | (1<<RXEN);
		break;
		default:
		break;
	}
	
	switch (USART_config_0.OperationMode)
	{
		case USART_Async_NormalSpeed:
			BaudRate = ((float)F_CPU/(16.0*(USART_config_0.BaudRate)))-1 + 0.5; //(float)/(float) to get float Output
		break;
		case USART_Async_DoubleSpeed:
			UCSRA_temp |= (1<<U2X);
			BaudRate = (((float)F_CPU)/(8.0*(USART_config_0.BaudRate)))-1 + 0.5; // +0.5 to get approx. value when masked to non float
		break;
		case USART_Sync:
			UCSRC_temp |= (1<<UMSEL);
			BaudRate = ((float)F_CPU/(2.0*(USART_config_0.BaudRate)))-1 + 0.5;
			
			switch(USART_config_0.ClockPolarity)
			{
				case USART_Sample_Falling:
				break;
				case USART_Sample_Rising:
					UCSRC_temp |= (1<<UCPOL);
				break;
			}
		break;
		default:
		break;
	}
	
	switch (USART_config_0.CommunicationMode)
	{
		case USART_SingleProcessor:
		break;
		case USART_MultiProcessor:
			UCSRA_temp |= (1<<MPCM);
		break;
	}
	
	switch(USART_config_0.InterruptEnable)
	{
		case USART_Interrupt_Disable:
		break;
		case USART_RxComp_Enable:
			UCSRB_temp |= (1<<RXCIE);
		break;
		case USART_TxComp_Enable:
			UCSRB_temp |= (1<<TXCIE);
		break;
		case USART_UDREmpty_Enable:
			UCSRB_temp |= (1<<UDRIE);
		break;
		case USART_RxComp_TxComp_Enable:
			UCSRB_temp |= (1<<RXCIE) | (1<<TXCIE);
		break;
		case USART_RxComp_UDREmpty_Enable:
			UCSRB_temp |= (1<<RXCIE) | (1<<UDRIE);
		break;
		case USART_TxComp_UDREmpty_Enable:
			UCSRB_temp |= (1<<TXCIE) | (1<<UDRIE);
		break;
		case USART_RxComp_TxComp_UDREmpty_Enable:
			UCSRB_temp |= (1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE);
		break;
		default:
		break;
	}
	
	switch (USART_config_0.DataFrame)
	{
		case USART_5bit:
		break;
		case USART_6bit:
			UCSRC_temp |= (1<<UCSZ0); 
		break;
		case USART_7bit:
			UCSRC_temp |= (1<<UCSZ1); 
		break;
		case USART_8bit:
			UCSRC_temp |= (1<<UCSZ0) | (1<<UCSZ1); 
		break;
		case USART_9bit:
			UCSRB_temp |= (1<<UCSZ2);
			UCSRC_temp |= (1<<UCSZ0) | (1<<UCSZ1);
		break;
		default:
		break;
	}
	
	switch(USART_config_0.CheckFrame)
	{
		case USART_ParityDisable_1Stopbit:
		break;
		case USART_ParityDisable_2StopBit:
			UCSRC_temp |= (1<<USBS);
		break;
		case USART_ParityEven_1StopBit:
			UCSRC_temp |= (1<<UPM1);
		break;
		case USART_ParityEven_2StopBit:
			UCSRC_temp |= (1<<USBS) | (1<<UPM1);
		break;
		case USART_ParityOdd_1StopBit:
			UCSRC_temp |= (1<<UPM0) | (1<<UPM1);
		break;
		case USART_ParityOdd_2StopBit:
			UCSRC_temp |= (1<<USBS) | (1<<UPM0) | (1<<UPM1);
		break;
		default:
		break;	
	}
	
	UBRRH = ((unsigned short)BaudRate) >> 8;
	UBRRL = ((unsigned char)BaudRate);
	UCSRA = UCSRA_temp;
	UCSRC_temp |= (1<<URSEL); //Accessing UCSRC
	UCSRC = UCSRC_temp;
	UCSRB = UCSRB_temp;
}

void USART_sendByte_Polling(unsigned short byte){
	while((UCSRA & (1<<UDRE)) == 0 ){} // Polling until UDR is empty
	if(USART_config_0.DataFrame == USART_9bit){
		UCSRB &= (~(0x01)); //Clearing 9th bit
		UCSRB |= ( (byte>>8) <<TXB8); // adding 9th bit 
	}
	UDR = (unsigned char) byte;
	
}

unsigned short USART_recieveByte_Polling(void){
	while((UCSRA & (1<<RXC)) == 0){} //Polling until there is unread data
	unsigned short Data = 0;
	/* Error Checking */
	if((UCSRA & ((1<<FE) | (1<<DOR) | (1<<PE))) == 1)
	{
		//Error Handling: Handle the error as you wish
		if(UCSRA & (1<<FE)){
			USART_config_0.ErrorType = USART_Frame_Error;
		}
		else if(UCSRA & (1<<DOR)){
			USART_config_0.ErrorType = USART_DataOverrun_Error;
		}
		else{
			USART_config_0.ErrorType = USART_Parity_Error;
		}
	}
	
	if(USART_config_0.DataFrame == USART_9bit)
	{
		Data |= (RXB8 << 8) | UDR;
	}
	else{
		Data = UDR;
	}
	return Data;
}


