/*
 * GI_Program.c
 *
 *  Created on: Sep 14, 2020
 *      Author: Omar Fahmy
 */

/* LIB LAYER */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/COMMON_MACROS.h"
#include "../../LIB/STD_TYPES.h"
/* MCAL LAYER */
#include "GI_Private.h"


u8 GI_U8Enable(void)
{
	SET_BIT(SREG, I);
	return NO_ERROR;
}

u8 GI_U8Disable(void)
{
	CLR_BIT(SREG, I);
	return NO_ERROR;
}
