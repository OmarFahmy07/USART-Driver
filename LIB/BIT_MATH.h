/*
 * BIT_MATH.h
 *
 *  Created on: July 11, 2020
 *      Author: Omar Fahmy
 */

#ifndef _BIT_MATH_H_
#define _BIT_MATH_H_

/************************************************************************************/
/*								BIT MANIPULATION									*/
/************************************************************************************/

/* Sets bit number bit_num in variable var to 1 								   	*/
#define SET_BIT(var, bit_num) var |= (1 << bit_num)

/* Sets bit number bit_num in variable var to 0 									*/
#define CLR_BIT(var, bit_num) var &= ~(1 << bit_num)

/* Toggles bit number bit_num in variable var 										*/
#define TOG_BIT(var, bit_num) var ^= (1 << bit_num)

/* Returns bit number bit_num in variable var 										*/
#define GET_BIT(var, bit_num) ( 1 & (var >> bit_num) )

/* Writes bit number bit_num in variable var with the value val 					*/
#define WRITE_BIT(var, bit_num, val) var = (var & (~(1 << bit_num))) | (val << bit_num)


#endif
