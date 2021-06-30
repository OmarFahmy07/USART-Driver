/*
 * main.c
 *
 *  Created on: Oct 8, 2020
 *      Author: Omar Fahmy
 */

/* HAL LAYER */
#include "../HAL/LCD/LCD_Interface.h"
/* LIB LAYER */
#include "../LIB/STD_TYPES.h"
/* MCAL LAYER */
#include "../MCAL/USART/USART_Interface.h"
#include "../MCAL/Global Interrupt/GI_Interface.h"
#include "../MCAL/DIO/DIO_Interface.h"

#include <util/delay.h>

u16 data;

void RX_ISR(void);

int main (void)
{
	LCD_U8Init();
	USART_U8Init();
	USART_U8EnableReceiver();
	USART_U8EnableRxInterrupt();
	USART_U8RxSetCallBack(RX_ISR);
	DIO_U8SetPinDirection(DIO_PORTD, DIO_PIN7, DIO_PIN_OUTPUT);
	GI_U8Enable();

	while (1)
	{
		LCD_U8SetPosition(LCD_FIRST_ROW, LCD_FIRST_COLUMN);
		LCD_U8SendData(data);
		LCD_U8SetPosition(LCD_SECOND_ROW, LCD_FIRST_COLUMN);
		LCD_U8SendNumber(data);
	}

	return 0;
}

void RX_ISR(void)
{
	USART_U8ReceiveData(&data);
}
