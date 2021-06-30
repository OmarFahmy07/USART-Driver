#ifndef _LCD_INTERFACE_H_
#define _LCD_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/* It is assumed in case of 8-bit mode and 4-bit mode that all data pins (DB0 ~ DB7)
 * are connected on the same port and in an ascending order. In case of 4-bit mode,
 * only DB4~DB7 are available for use.
 */


/************************************************************************************/
/*					  USEFUL MACROS AS FUNCTIONS' ARGUMENTS						    */
/************************************************************************************/

/************************************************************************************/
/*								   FUNCTION SET										*/
/************************************************************************************/
#define LCD_8BITS_1LINE_5X7FONT				0x30
#define LCD_8BITS_1LINE_5X10FONT 			0x34
#define LCD_8BITS_2LINES_5X7FONT 			0x38
#define LCD_8BITS_2LINES_5X10FONT 			0x3C
#define LCD_4BITS_1LINE_5X7FONT				0x20
#define LCD_4BITS_1LINE_5X10FONT 			0x24
#define LCD_4BITS_2LINES_5X7FONT 			0x28
#define LCD_4BITS_2LINES_5X10FONT 			0x2C
/************************************************************************************/

/************************************************************************************/
/*								DISPLAY ON/OFF CONTROL								*/
/************************************************************************************/
#define LCD_NODISPLAY_NOCURSOR_NOBLINKING	0x08
#define LCD_NODISPLAY_NOCURSOR_BLINKING		0x09
#define LCD_NODISPLAY_CURSOR_NOBLINKING		0x0A
#define LCD_NODISPLAY_CURSOR_BLINKING		0x0B
#define LCD_DISPLAY_NOCURSOR_NOBLINKING		0x0C
#define LCD_DISPLAY_NOCURSOR_BLINKING		0x0D
#define LCD_DISPLAY_CURSOR_NOBLINKING		0x0E
#define LCD_DISPLAY_CURSOR_BLINKING			0x0F
/************************************************************************************/

/************************************************************************************/
/*								CURSOR OR DISPLAY SHIFT								*/
/************************************************************************************/
#define LCD_SHIFT_CURSOR_LEFT				0x10
#define LCD_SHIFT_CURSOR_RIGHT				0x14
#define LCD_SHIFT_CURSORANDDISPLAY_LEFT		0x18
#define LCD_SHIFT_CURSORANDDISPLAY_RIGHT	0x1C
/************************************************************************************/

/************************************************************************************/
/*							  CLEAR LCD DISPLAY SCREEN								*/
/************************************************************************************/
#define LCD_CLEAR_DISPLAY 					0x01
/************************************************************************************/

/************************************************************************************/
/*									ENTRY MODE SET								    */
/************************************************************************************/
#define LCD_DECREASE_NOSHIFT				0x04
#define LCD_DECREASE_SHIFT					0x05
#define LCD_INCREASE_NOSHIFT				0x06
#define LCD_INCREASE_SHIFT					0x07
/************************************************************************************/

/************************************************************************************/
/*								 CURSOR BACK TO HOME								*/
/************************************************************************************/
#define LCD_RETURN_HOME						0x02
/************************************************************************************/

/************************************************************************************/
/*								LCD DISPLAY COLUMNS									*/
/************************************************************************************/
#define LCD_FIRST_COLUMN					0
#define LCD_SECOND_COLUMN					1
#define LCD_THIRD_COLUMN					2
#define LCD_FOURTH_COLUMN					3
#define LCD_FIFTH_COLUMN					4
#define LCD_SIXTH_COLUMN					5
#define LCD_SEVENTH_COLUMN					6
#define LCD_EIGHTH_COLUMN					7
#define LCD_NINTH_COLUMN					8
#define LCD_TENTH_COLUMN					9
#define LCD_ELEVENTH_COLUMN					10
#define LCD_TWELFTH_COLUMN					11
#define LCD_THIRTEENTH_COLUMN				12
#define LCD_FOURTEENTH_COLUMN				13
#define LCD_FIFTEENTH_COLUMN				14
#define LCD_SIXTEENTH_COLUMN				15
/************************************************************************************/

/************************************************************************************/
/*								 LCD DISPLAY ROWS									*/
/************************************************************************************/
#define LCD_FIRST_ROW						0
#define LCD_SECOND_ROW						1
/************************************************************************************/


/************************************************************************************/
/* 								FUNCTIONS PROTOTYPE					 				*/
/************************************************************************************/

/************************************************************************************/
/* Description: sends a command to the LCD					  						*/
/* Input      : command 		                                                    */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 LCD_U8SendCommand(u8 LOC_U8Command);
/************************************************************************************/

/************************************************************************************/
/* Description: sends a character data to the LCD 								    */
/* Input      : data	 		                                                    */
/* Output     : error Checking                                                      */
/************************************************************************************/
extern u8 LCD_U8SendData(u8 LOC_U8Data);
/************************************************************************************/

/************************************************************************************/
/* Description: displays a string on the LCD display panel							*/
/* Input      : array of characters	                                                */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 LCD_U8SendString (const u8 *const LOC_U8String);
/************************************************************************************/

/************************************************************************************/
/* Description: initializes the LCD configurations									*/
/* Input      : Nothing				                                                */
/* Output     : error checking                                                      */
/************************************************************************************/
extern u8 LCD_U8Init(void);

/************************************************************************************/
/* Description: displays a signed number on the LCD panel  							*/
/* Input      : Signed Number		                                                */
/* Output     : Error Checking                                                      */
/************************************************************************************/
extern u8 LCD_U8SendNumber(const f64 LOC_S64Number);
/************************************************************************************/

/************************************************************************************/
/* Description: Sets the cursor position on a specific row and column on the panel	*/
/* Input      : Row number - Column number                                          */
/* Output     : Error Checking                                                      */
/************************************************************************************/
extern u8 LCD_U8SetPosition (const u8 LOC_U8Row, const u8 LOC_U8Column);
/************************************************************************************/

/************************************************************************************/
/* Description: draws user-custom character patterns								*/
/* Input      : array containing 8 bytes of the extra character                     */
/* Output     : Error Checking                                                      */
/************************************************************************************/
extern u8 LCD_U8DrawExtraCharacter(const u8 *const LOC_U8Character);
/************************************************************************************/


#endif
