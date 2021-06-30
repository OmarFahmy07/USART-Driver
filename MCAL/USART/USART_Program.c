/*
 * USART_Program.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Omar Fahmy
 */

/* LIB LAYER */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"
/* MCAL LAYER */
#include "USART_Configure.h"
#include "USART_Private.h"

/* Global Pointers to Functions for Calling Back */
void (*GLOB_VidTxPtrCallBack)(void) = NULL;
void (*GLOB_VidRxPtrCallBack)(void) = NULL;
void (*GLOB_VidEmptyDRPtrCallBack)(void) = NULL;

/************************************************************************************/
/*						PUBLIC FUNCTIONS IMPLEMENTATION								*/
/************************************************************************************/

u8 USART_U8Init(void)
{
	u8 LOC_U8UCSRCValue = CLEAR;
	u16 LOC_U16UBRR;
#if MODE == SYNCHRONOUS
	SET_BIT(LOC_U8UCSRCValue, UMSEL);
	/* UBRR Equation */
	LOC_U16UBRR = ( CLOCK_FREQUENCY / ( 2.0 * BAUD_RATE ) ) - 1;
#if CLOCK_POLARITY == CHANGE_AT_RISING_SAMPLE_AT_FALLING
	/* Do nothing, bits are already cleared */
#elif CLOCK_POLARITY == SAMPLE_AT_RISING_CHANGE_AT_FALLING
	SET_BIT(LOC_U8UCSRCValue, UCPOL);
#else
#error "Invalid USART clock polarity configuration"
#endif
#elif MODE == ASYNCHRONOUS
	/* UBRR Equation */
	LOC_U16UBRR = ( CLOCK_FREQUENCY / ( 16.0 * BAUD_RATE ) ) - 1;
#elif MODE == ASYNCHRONOUS_DOUBLE_SPEED
	/* UBRR Equation */
	LOC_U16UBRR = ( CLOCK_FREQUENCY / ( 8.0 * BAUD_RATE ) ) - 1;
	SET_BIT(UCSRA_REGISTER, U2X);
#else
#error "Invalid USART mode of operation configuration"
#endif
#if PARITY_CHECK == DISABLE_PARITY
	/* Do nothing, bits are already cleared */
#elif PARITY_CHECK == EVEN_PARITY
	SET_BIT(LOC_U8UCSRCValue, UPM1);
#elif PARITY_CHECK == ODD_PARITY
	SET_BIT(LOC_U8UCSRCValue, UPM1);
	SET_BIT(LOC_U8UCSRCValue, UPM0);
#else
#error "Invalid USART parity check configuration"
#endif
#if STOP_BITS == ONE_STOP_BIT
	/* Do nothing, bit is already cleared */
#elif STOP_BITS == TWO_STOP_BITS
	SET_BIT(LOC_U8UCSRCValue, USBS);
#else
#error "Invalid USART stop bits configuration"
#endif
#if DATA_BITS == FIVE_BITS
	/* Do nothing, bits are already cleared */
#elif DATA_BITS == SIX_BITS
	SET_BIT(LOC_U8UCSRCValue, UCSZ0);
#elif DATA_BITS == SEVEN_BITS
	SET_BIT(LOC_U8UCSRCValue, UCSZ1);
#elif DATA_BITS == EIGHT_BITS
	SET_BIT(LOC_U8UCSRCValue, UCSZ1);
	SET_BIT(LOC_U8UCSRCValue, UCSZ0);
#elif DATA_BITS == NINE_BITS
	SET_BIT(LOC_U8UCSRCValue, UCSZ2);
	SET_BIT(LOC_U8UCSRCValue, UCSZ1);
	SET_BIT(LOC_U8UCSRCValue, UCSZ0);
#else
#error "Invalid USART data bits configuration"
#endif
	/* Write to UCSRC register */
	SET_BIT(LOC_U8UCSRCValue, URSEL);
	UCSRC_REGISTER = LOC_U8UCSRCValue;
	/* Write to UBRRH and UBRRL register */
	UBRRL_REGISTER = LOC_U16UBRR;
	LOC_U16UBRR >>= SHIFT_BY_EIGHT;
	CLR_BIT(LOC_U16UBRR, BIT_SEVEN);
	CLR_BIT(LOC_U16UBRR, BIT_SIX);
	CLR_BIT(LOC_U16UBRR, BIT_FIVE);
	CLR_BIT(LOC_U16UBRR, BIT_FOUR);
	UBRRH_REGISTER = LOC_U16UBRR;
	return NO_ERROR;
}

u8 USART_U8EnableTransmitter(void)
{
	SET_BIT(UCSRB_REGISTER, TXEN);
	return NO_ERROR;
}

u8 USART_U8EnableReceiver(void)
{
	SET_BIT(UCSRB_REGISTER, RXEN);
	return NO_ERROR;
}

u8 USART_U8DisableTransmitter(void)
{
	CLR_BIT(UCSRB_REGISTER, TXEN);
	return NO_ERROR;
}

u8 USART_U8DisableReceiver(void)
{
	CLR_BIT(UCSRB_REGISTER, RXEN);
	return NO_ERROR;
}

u8 USART_U8RxPollingOnFlag(void)
{
	while ( !GET_BIT(UCSRA_REGISTER, RXC) );
	/* RXC Flag is not cleared by writing one to its bit, it is only cleared by reading
	 * the data in the receive buffer.
	 */
	return NO_ERROR;
}

u8 USART_U8TxPollingOnFlag(void)
{
	while ( !GET_BIT(UCSRA_REGISTER, TXC) );
	SET_BIT(UCSRA_REGISTER, TXC);
	return NO_ERROR;
}

u8 USART_U8EmptyDRPollingOnFlag(void)
{
	while ( !GET_BIT(UCSRA_REGISTER, UDRE) );
	/* UDRE Flag is not cleared by writing one to its bit, it is only cleared when
	 * there is data present in the UDR register and is not yet shifted to the
	 * Data Shift Register.
	 */
	return NO_ERROR;
}

u8 USART_U8SendData(u16 LOC_U16Data)
{
	USART_U8EmptyDRPollingOnFlag();
#if DATA_BITS == FIVE_BITS
	CLR_BIT(LOC_U16Data, BIT_SEVEN);
	CLR_BIT(LOC_U16Data, BIT_SIX);
	CLR_BIT(LOC_U16Data, BIT_FIVE);
	UDR_REGISTER = LOC_U16Data;
#elif DATA_BITS == SIX_BITS
	CLR_BIT(LOC_U16Data, BIT_SEVEN);
	CLR_BIT(LOC_U16Data, BIT_SIX);
	UDR_REGISTER = LOC_U16Data;
#elif DATA_BITS == SEVEN_BITS
	CLR_BIT(LOC_U16Data, BIT_SEVEN);
	UDR_REGISTER = LOC_U16Data;
#elif DATA_BITS == EIGHT_BITS
	UDR_REGISTER = LOC_U16Data;
#elif DATA_BITS == NINE_BITS
	u8 LOC_U8Temp = LOC_U16Data;
	LOC_U16Data >>= SHIFT_BY_EIGHT;
	WRITE_BIT(UCSRB_REGISTER, TXB8, GET_BIT(LOC_U16Data, BIT_ZERO));
	UDR_REGISTER = LOC_U8Temp;
#else
#error "Invalid data bits for USART configuration"
#endif
	return NO_ERROR;
}

u8 USART_U8ReceiveData(u16* const LOC_U16Data)
{
	if (LOC_U16Data != NULL)
	{
		USART_U8RxPollingOnFlag();
#if DATA_BITS == NINE_BITS
		*LOC_U16Data = GET_BIT(UCSRB_REGISTER, RXB8);
		*LOC_U16Data <<= SHIFT_BY_EIGHT;
		*( (u8*) LOC_U16Data) = UDR_REGISTER;
#elif DATA_BITS == FIVE_BITS || DATA_BITS == SIX_BITS || DATA_BITS == SEVEN_BITS \
		|| DATA_BITS == EIGHT_BITS
		*LOC_U16Data = UDR_REGISTER;
#else
#error "Invalid data bits for USART configuration"
#endif
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 USART_U8CheckFrameError(u8* const LOC_U8Check)
{
	if (LOC_U8Check != NULL)
	{
		*LOC_U8Check = GET_BIT(UCSRA_REGISTER, FE);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 USART_U8CheckDataOverrunError(u8* const LOC_U8Check)
{
	if (LOC_U8Check != NULL)
	{
		*LOC_U8Check = GET_BIT(UCSRA_REGISTER, DOR);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 USART_U8CheckParityError(u8* const LOC_U8Check)
{
	if (LOC_U8Check != NULL)
	{
		*LOC_U8Check = GET_BIT(UCSRA_REGISTER, PE);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 USART_U8EnableMPCMode(void)
{
	SET_BIT(UCSRA_REGISTER, MPCM);
	return NO_ERROR;
}

u8 USART_U8DisableMPCMode(void)
{
	CLR_BIT(UCSRA_REGISTER, MPCM);
	return NO_ERROR;
}


u8 USART_U8EnableTxInterrupt(void)
{
	SET_BIT(UCSRB_REGISTER, TXCIE);
	return NO_ERROR;
}

u8 USART_U8DisableTxInterrupt(void)
{
	CLR_BIT(UCSRB_REGISTER, TXCIE);
	return NO_ERROR;
}

u8 USART_U8EnableRxInterrupt(void)
{
	SET_BIT(UCSRB_REGISTER, RXCIE);
	return NO_ERROR;
}

u8 USART_U8DisableRxInterrupt(void)
{
	CLR_BIT(UCSRB_REGISTER, RXCIE);
	return NO_ERROR;
}

u8 USART_U8EnableEmptyDRInterrupt(void)
{
	SET_BIT(UCSRB_REGISTER, UDRIE);
	return NO_ERROR;
}

u8 USART_U8DisableEmptyDRInterrupt(void)
{
	CLR_BIT(UCSRB_REGISTER, UDRIE);
	return NO_ERROR;
}

u8 USART_U8TxSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidTxPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 USART_U8RxSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidRxPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}

}

u8 USART_U8EmptyDRSetCallBack( void (*ptrToFun)(void) )
{
	if (ptrToFun != NULL)
	{
		GLOB_VidEmptyDRPtrCallBack = ptrToFun;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}

}

/************************************************************************************/
/*						PRIVATE FUNCTIONS IMPLEMENTATION							*/
/************************************************************************************/
void __vector_13(void)
{
	if (GLOB_VidRxPtrCallBack != NULL)
	{
		(*GLOB_VidRxPtrCallBack)();
	}
}

void __vector_14(void)
{
	if (GLOB_VidEmptyDRPtrCallBack != NULL)
	{
		(*GLOB_VidEmptyDRPtrCallBack)();
	}
}

void __vector_15(void)
{
	if (GLOB_VidTxPtrCallBack != NULL)
	{
		(*GLOB_VidTxPtrCallBack)();
	}
}
