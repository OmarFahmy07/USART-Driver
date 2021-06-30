/*
 * DIO_Program.h
 *
 *  Created on: Aug 2, 2020
 *      Author: Omar Fahmy
 */

/* 		LIB LAYER 		*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/BIT_MATH.h"

/* 		MCAL LAYER 		*/
#include "DIO_Private.h"

/* Arrays of pointers that point to the three DIO registers */
u8* const directionRegisters [NUMBER_OF_PORTS] = {DDRA_REGISTER, DDRB_REGISTER, DDRC_REGISTER, DDRD_REGISTER};
u8* const writeRegisters [NUMBER_OF_PORTS] = {PORTA_REGISTER, PORTB_REGISTER, PORTC_REGISTER, PORTD_REGISTER};
volatile u8* const readRegisters [NUMBER_OF_PORTS] = {PINA_REGISTER, PINB_REGISTER, PINC_REGISTER, PIND_REGISTER};


/***********************************************************************************/
/* 							PUBLIC FUNCTIONS IMPLEMENTATION						   */
/***********************************************************************************/

u8 DIO_U8SetPortDirection (const u8 LOC_U8Port, const u8 LOC_U8Direction)
{
	if (LOC_U8Port <= PORTD)
	{
		if (LOC_U8Direction == PORT_INPUT)
		{
			*directionRegisters[LOC_U8Port] = PORT_INPUT;
			return NO_ERROR;
		}
		else if (LOC_U8Direction == PORT_OUTPUT)
		{
			*directionRegisters[LOC_U8Port] = PORT_OUTPUT;
			return NO_ERROR;
		}
		else
		{
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8SetPinDirection (const u8 LOC_U8Port, const u8 LOC_U8Pin, const u8 LOC_U8Direction)
{
	if (LOC_U8Port <= PORTD && LOC_U8Pin <= PIN7)
	{
		if (LOC_U8Direction == PIN_INPUT)
		{
			CLR_BIT( *directionRegisters[LOC_U8Port], LOC_U8Pin );
			return NO_ERROR;
		}
		else if (LOC_U8Direction == PIN_OUTPUT)
		{
			SET_BIT( *directionRegisters[LOC_U8Port], LOC_U8Pin );
			return NO_ERROR;
		}
		else
		{
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8SetPortValue (const u8 LOC_U8Port, const u8 LOC_U8Value)
{
	if (LOC_U8Port <= PORTD)
	{
		*writeRegisters[LOC_U8Port] = LOC_U8Value;
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8SetPinValue (const u8 LOC_U8Port, const u8 LOC_U8Pin, const u8 LOC_U8Value)
{
	if (LOC_U8Port <= PORTD && LOC_U8Pin <= PIN7)
	{
		if (LOC_U8Value == PIN_HIGH)
		{
			SET_BIT(*writeRegisters[LOC_U8Port], LOC_U8Pin);
			return NO_ERROR;
		}
		else if (LOC_U8Value == PIN_LOW)
		{
			CLR_BIT(*writeRegisters[LOC_U8Port], LOC_U8Pin);
			return NO_ERROR;
		}
		else
		{
			return ERROR;
		}
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8TogglePin (const u8 LOC_U8Port, const u8 LOC_U8Pin)
{
	if (LOC_U8Port <= PORTD && LOC_U8Pin <= PIN7)
	{
		TOG_BIT(*writeRegisters[LOC_U8Port], LOC_U8Pin);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8TogglePort (const u8 LOC_U8Port)
{
	if (LOC_U8Port <= PORTD)
	{
		*writeRegisters[LOC_U8Port] = ~(*writeRegisters[LOC_U8Port]);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8GetPinValue (const u8 LOC_U8Port, const u8 LOC_U8Pin, u8* const LOC_U8Value)
{
	if (LOC_U8Port <= PORTD && LOC_U8Pin <= PIN7 && LOC_U8Value != NULL)
	{
		*LOC_U8Value = GET_BIT(*readRegisters[LOC_U8Port], LOC_U8Pin);
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 DIO_U8GetPortValue (const u8 LOC_U8Port, u8* const LOC_U8Value)
{
	if (LOC_U8Port <= PORTD && LOC_U8Value != NULL)
	{
		*LOC_U8Value = *readRegisters[LOC_U8Port];
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}
