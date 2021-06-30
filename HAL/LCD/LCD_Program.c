/* 		 LIB LAYER 			*/
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/BIT_MATH.h"
/* 		 HAL LAYER 			*/
#include "LCD_Configure.h"
#include "LCD_Private.h"
/* 		 MCAL LAYER 		*/
#include "../../MCAL/DIO/DIO_Interface.h"
/* 		DELAY LIBRARY 		*/
#include <util/delay.h>

/************************************************************************************/
/* 						  PRIVATE FUNCTIONS IMPLEMENTATION  						*/
/************************************************************************************/

u8 LCD_U8EnableSignal(void)
{
	/* Set Enable Signal High*/
	DIO_U8SetPinValue(ENABLE_PORT, ENABLE_PIN, DIO_PIN_HIGH);
	/* Wait for E rise time (Tr --> 20 ns) + E pulse width (Tw --> 230 ns) */
	_delay_ms(1);
	/* Set Enable Signal Low*/
	DIO_U8SetPinValue(ENABLE_PORT, ENABLE_PIN, DIO_PIN_LOW);
	/* Wait for E fall time (Tf --> 20 ns) */
	_delay_ms(1);
	return NO_ERROR;
}

u8 LCD_U8SendNibble(const u8 LOC_U8Information)
{
	/* Send higher nibble to DB4 ~ DB7 */
	for (u8 LOC_U8WritePin = DATA_INITIAL_PIN, LOC_U8InformationPin = DIO_PIN4; LOC_U8WritePin < DATA_INITIAL_PIN + FOURBITS_DATA; LOC_U8WritePin++, LOC_U8InformationPin++)
	{
		DIO_U8SetPinValue(DATA_PORT, LOC_U8WritePin, GET_BIT(LOC_U8Information, LOC_U8InformationPin));
	}
	return NO_ERROR;
}

/************************************************************************************/
/* 						  PUBLIC FUNCTIONS IMPLEMENTATION  							*/
/************************************************************************************/

u8 LCD_U8SendCommand(u8 LOC_U8Command)
{
	/* Set RS = 0 to select instruction register */
	DIO_U8SetPinValue(RS_PORT, RS_PIN, DIO_PIN_LOW);
	/* Set RW = 0 to perform a write operation */
	DIO_U8SetPinValue(RW_PORT, RW_PIN, DIO_PIN_LOW);
#if MODE == EIGHTBIT_MODE
	/* Send Command to DB0 ~ DB7 */
	DIO_U8SetPortValue(DATA_PORT, LOC_U8Command);
#elif MODE == FOURBIT_MODE
	/* Send higher nibble to DB4 ~ DB7 */
	LCD_U8SendNibble(LOC_U8Command);
#else
#error "Incorrect LCD mode"
#endif
	LCD_U8EnableSignal();
#if MODE == FOURBIT_MODE
	/* Get The Lower Nibble Ready to Be Sent */
	LOC_U8Command <<= FOURBITS_DATA;
	/* Send Lower Nibble to DB4 ~ DB7 */
	LCD_U8SendNibble(LOC_U8Command);
	LCD_U8EnableSignal();
#endif
	return NO_ERROR;
}

u8 LCD_U8Init(void)
{
#if RS_PORT >= DIO_PORTA && RS_PORT <= DIO_PORTD
#if RS_PIN >= DIO_PIN0 && RS_PIN <= DIO_PIN7
	/* Set RS pin as output */
	DIO_U8SetPinDirection(RS_PORT, RS_PIN, DIO_PIN_OUTPUT);
#else
#error "Incorrect RS pin"
#endif
#else
#error "Incorrect RS port"
#endif
#if RW_PORT >= DIO_PORTA && RW_PORT <= DIO_PORTD
#if RW_PIN >= DIO_PIN0 && RW_PIN <= DIO_PIN7
	/* Set RW pin as output */
	DIO_U8SetPinDirection(RW_PORT, RW_PIN, DIO_PIN_OUTPUT);
#else
#error "Incorrect RW pin"
#endif
#else
#error "Incorrect RW port"
#endif
#if ENABLE_PORT >= DIO_PORTA && ENABLE_PORT <= DIO_PORTD
#if ENABLE_PIN >= DIO_PIN0 && ENABLE_PIN <= DIO_PIN7
	/* Set Enable pin as output */
	DIO_U8SetPinDirection(ENABLE_PORT, ENABLE_PIN, DIO_PIN_OUTPUT);
#else
#error "Incorrect enable pin"
#endif
#else
#error "Incorrect enable port"
#endif
#if DATA_PORT >= DIO_PORTA && DATA_PORT <= DIO_PORTD
#if DATA_INITIAL_PIN >= DIO_PIN0 && DATA_INITIAL_PIN <= DIO_PIN7
#if MODE == EIGHTBIT_MODE
	/* Set data port as output */
	DIO_U8SetPortDirection(DATA_PORT, DIO_PORT_OUTPUT);
#elif MODE == FOURBIT_MODE
	/* Set the 4 data pins as output */
	for (u8 LOC_U8Pin = DATA_INITIAL_PIN; LOC_U8Pin < DATA_INITIAL_PIN + FOURBITS_DATA; LOC_U8Pin++)
	{
		DIO_U8SetPinDirection(DATA_PORT, LOC_U8Pin, DIO_PIN_OUTPUT);
	}
#else
#error "Incorrect LCD mode"
#endif
#else
#error "Incorrect data initial pin"
#endif
#else
#error "Incorrect data port"
#endif
	/* Wait for more than 30 ms after VDD rises to 4.5V */
	_delay_ms(50);
#if MODE == FOURBIT_MODE
	/* 4-Bit Mode Function Set Instruction */
	LCD_U8SendCommand(RETURN_HOME);
#if FUNCTION_SET_4BIT == FOURBITS_1LINE_5X7FONT || FUNCTION_SET_4BIT == FOURBITS_1LINE_5X10FONT || \
		FUNCTION_SET_4BIT == FOURBITS_2LINES_5X10FONT || FUNCTION_SET_4BIT == FOURBITS_2LINES_5X7FONT
	LCD_U8SendCommand(FUNCTION_SET_4BIT);
#else
#error "Incorrect 4-bit function set"
#endif
#elif MODE == EIGHTBIT_MODE
#if FUNCTION_SET_8BIT == EIGHTBITS_1LINE_5X7FONT || FUNCTION_SET_8BIT == EIGHTBITS_1LINE_5X10FONT || \
		FUNCTION_SET_8BIT == EIGHTBITS_2LINES_5X10FONT || FUNCTION_SET_8BIT == EIGHTBITS_2LINES_5X7FONT
	/* 8-Bit Mode Function Set Instruction */
	LCD_U8SendCommand(FUNCTION_SET_8BIT);
#else
#error "Incorrect 8-bit function set"
#endif
#else
#error "Incorrect LCD mode"
#endif
	/* Wait for more than 39 µs */
	_delay_ms(1);
#if DISPLAY_CONTROL == NODISPLAY_NOCURSOR_NOBLINKING || DISPLAY_CONTROL == NODISPLAY_NOCURSOR_BLINKING || \
		DISPLAY_CONTROL == NODISPLAY_CURSOR_NOBLINKING || DISPLAY_CONTROL == NODISPLAY_CURSOR_BLINKING || \
		DISPLAY_CONTROL == DISPLAY_NOCURSOR_NOBLINKING || DISPLAY_CONTROL == DISPLAY_NOCURSOR_BLINKING || \
		DISPLAY_CONTROL == DISPLAY_CURSOR_NOBLINKING || DISPLAY_CONTROL == DISPLAY_CURSOR_BLINKING
	/* Display ON/OFF Control Instruction */
	LCD_U8SendCommand(DISPLAY_CONTROL);
#else
#error "Incorrect display control"
#endif
	/* Wait for more than 39 µs */
	_delay_ms(1);
	/* Display Clear Instruction */
	LCD_U8SendCommand(CLEAR_DISPLAY);
	/* Wait for more than 1.53 ms */
	_delay_ms(2);
	/* Entry Mode Set Instruction */
#if ENTRY_MODE == DECREASE_NOSHIFT || ENTRY_MODE == DECREASE_SHIFT || \
		ENTRY_MODE == INCREASE_NOSHIFT	|| ENTRY_MODE == INCREASE_SHIFT
	LCD_U8SendCommand(ENTRY_MODE);
#else
#error "Incorrect entry mode"
#endif
	return NO_ERROR;
}

u8 LCD_U8SendData(u8 LOC_U8Data)
{
	/* Set RS = 1 to select data register */
	DIO_U8SetPinValue(RS_PORT, RS_PIN, DIO_PIN_HIGH);
	/* Set RW = 0 to perform a write operation */
	DIO_U8SetPinValue(RW_PORT, RW_PIN, DIO_PIN_LOW);
#if MODE == EIGHTBIT_MODE
	/* Send Data to DB0 ~ DB7 */
	DIO_U8SetPortValue(DATA_PORT, LOC_U8Data);
#elif MODE == FOURBIT_MODE
	/* Send Higher Nibble to DB4 ~ DB7 */
	LCD_U8SendNibble(LOC_U8Data);
#else
#error "Incorrect LCD mode"
#endif
	LCD_U8EnableSignal();
#if MODE == FOURBIT_MODE
	/* Get The Lower Nibble Ready to Be Sent */
	LOC_U8Data <<= FOURBITS_DATA;
	/* Send Lower Nibble to DB4 ~ DB7 */
	LCD_U8SendNibble(LOC_U8Data);
	LCD_U8EnableSignal();
#endif
	return NO_ERROR;
}

u8 LCD_U8SendString (const u8 *const LOC_U8String)
{
	if (LOC_U8String != NULL)
	{
		/* Send The String Character By Character */
		for (u8 LOC_U8Index = 0; LOC_U8String[LOC_U8Index] != '\0'; LOC_U8Index++)
		{
			LCD_U8SendData(LOC_U8String[LOC_U8Index]);
		}

		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

u8 LCD_U8SendNumber(f64 LOC_F64Number)
{
#if FLOAT_NUMBERS_ACCURACY >= MIN_ACCURACY && FLOAT_NUMBERS_ACCURACY <= MAX_ACCURACY
	f64 LOC_F64Temp = LOC_F64Number;
	u32 LOC_U32IntegerPart, LOC_U32Reverse = 0;
	u8 LOC_U8Point = 0, LOC_U8NegativeFlag = 0;
	/* If the number is negative, take its absolute value and fire a flag */
	if (LOC_F64Number < 0)
	{
		LOC_F64Number *= -1; /* Absolute value (positive value) */
		LOC_F64Temp = LOC_F64Number; /* Update the temporary variable */
		LOC_U8NegativeFlag = 1; /* Fire a negative flag */
	}

	/* Count how many numbers before the decimal point */
	while (LOC_F64Temp >= 1)
	{
		LOC_U8Point++;
		LOC_F64Temp /= 10;
	}

	LOC_F64Temp = LOC_F64Number;

	/* Determine how many digits to display based on the accuracy */
	for (u8 LOC_U8Counter = 0; LOC_U8Counter < FLOAT_NUMBERS_ACCURACY; LOC_U8Counter++)
	{
		LOC_F64Temp *= 10;
	}

	LOC_U32IntegerPart = LOC_F64Temp;

	/* Reverse the number */
	while (LOC_U32IntegerPart != 0)
	{
		LOC_U32Reverse = LOC_U32Reverse * 10 + LOC_U32IntegerPart % 10;
		LOC_U32IntegerPart /= 10;
	}

	LOC_F64Temp = 0;

	/* If the negative flag was fired, display a negative sign */
	if (LOC_U8NegativeFlag == 1)
	{
		LCD_U8SendData('-');
	}

	/* Print the whole number, digit by digit */
	while (LOC_U32Reverse != 0)
	{
		if (LOC_F64Temp == LOC_U8Point)
		{
			LCD_U8SendData('.');
		}
		else
		{
			LCD_U8SendData(LOC_U32Reverse % 10 + '0');
			LOC_U32Reverse /= 10;
		}
		LOC_F64Temp++;
	}

	LOC_U32IntegerPart = LOC_F64Number;
	/* If the number was equal to zero or had zeroes at the end with no fractional
	 * part, then print it them!
	 */
	if ( ( LOC_F64Number - LOC_U32IntegerPart == 0) || \
		 ( LOC_F64Number > 0 && LOC_F64Number < 1 && FLOAT_NUMBERS_ACCURACY == 0 ) || \
		 ( LOC_U32IntegerPart % 10 == 0 && FLOAT_NUMBERS_ACCURACY == 0 ) )
	{
		if (LOC_U32IntegerPart % 10 == 0)
		{
			/* Print 0 at least one time in case the number was equal to zero */
			do
			{
				LCD_U8SendData('0');
				LOC_U32IntegerPart /= 10;
			}while(LOC_U32IntegerPart % 10 == 0 && LOC_U32IntegerPart != 0);
		}
	}

	return NO_ERROR;
#else
#error "Incorrect floating numbers accuracy"
#endif
}

u8 LCD_U8SetPosition (const u8 LOC_U8Row, const u8 LOC_U8Column)
{
	if (LOC_U8Column <= SIXTEENTH_COLUMN)
	{
		if (LOC_U8Row == FIRST_ROW)
		{
			/* Set the address counter to a specific DDRAM address (first row) */
			LCD_U8SendCommand(DDRAM_ADDRESS_DB7 + FIRST_ROW_INITIAL_ADDRESS + LOC_U8Column);
			return NO_ERROR;
		}
		else if (LOC_U8Row == SECOND_ROW)
		{
			/* Set the address counter to a specific DDRAM address (second row) */
			LCD_U8SendCommand(DDRAM_ADDRESS_DB7 + SECOND_ROW_INITIAL_ADDRESS + LOC_U8Column);
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

u8 LCD_U8DrawExtraCharacter(const u8 *const LOC_U8Character)
{
	if (LOC_U8Character != NULL)
	{
		/* Position in the CGRAM */
		static u8 LOC_U8Position = FIRST_CGRAM_ADDRESS;
		if (LOC_U8Position <= LAST_CGRAM_ADDRESS)
		{
			/* Set the address counter at the current available spot in CGRAM */
			LCD_U8SendCommand(CGRAM_ADDRESS_DB6 + LOC_U8Position);

			/* Draw the extra character */
			for (u8 LOC_U8Index = 0; LOC_U8Index < EXTRACHAR_NO_OF_BYTES; LOC_U8Index++)
			{
				LCD_U8SendData( LOC_U8Character[LOC_U8Index] );
			}

			/* Go to the next available spot in CGRAM */
			LOC_U8Position += NEXT_CGRAM_ADDRESS;
		}
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}
