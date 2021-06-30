/*
 * USART_Interface.h
 *
 *  Created on: Oct 8, 2020
 *      Author: Omar Fahmy
 */

#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

#include "../../LIB/STD_TYPES.h"

/************************************************************************************/
/*							 FUNCTIONS PROTOTYPES								    */
/************************************************************************************/

/************************************************************************************/
/* Description: initializes USART peripheral	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8Init(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables the USART transmitter	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EnableTransmitter(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables the USART receiver		  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EnableReceiver(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables the USART transmitter	  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8DisableTransmitter(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables the USART receiver		  								    */
/* Inputs: nothing													 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8DisableReceiver(void);
/************************************************************************************/

/************************************************************************************/
/* Description: sends data through USART transmitter (9-bit data maximum)		    */
/* Inputs: data														 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8SendData(u16 LOC_U16Data);
/************************************************************************************/

/************************************************************************************/
/* Description: receives data through USART receiver							    */
/* Inputs: pointer to a variable to receive the data in				 	 		    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8ReceiveData(u16* const LOC_U16Data);
/************************************************************************************/

/************************************************************************************/
/* Description: polls on USART Transmit Complete flag				 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8TxPollingOnFlag(void);
/************************************************************************************/

/************************************************************************************/
/* Description: polls on USART Receive Complete flag				 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8RxPollingOnFlag(void);
/************************************************************************************/

/************************************************************************************/
/* Description: polls on USART Empty Data Register flag				 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EmptyDRPollingOnFlag(void);
/************************************************************************************/

/************************************************************************************/
/* Description: checks if the next character in the receive buffer had a frame		*/
/* error. Check is one if there is an error and zero if there is no error. Frame	*/
/* error must be checked before reading the data									*/
/* Inputs: pointer to a variable to receive the check value in					    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8CheckFrameError(u8* const LOC_U8Check);
/************************************************************************************/

/************************************************************************************/
/* Description: checks if a data overrun condition is detected. Check is one if		*/
/* there is an error and zero if there is no error. Data overrun error must be	    */
/* checked before reading the data													*/
/* Inputs: pointer to a variable to receive the check value in					    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8CheckDataOverrunError(u8* const LOC_U8Check);
/************************************************************************************/

/************************************************************************************/
/* Description: checks if the next character in the receive buffer had a parity		*/
/* error. Check is one if there is an error and zero if there is no error.			*/
/* Inputs: pointer to a variable to receive the check value in					    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8CheckParityError(u8* const LOC_U8Check);
/************************************************************************************/

/************************************************************************************/
/* Description: enables the Multi-processor Communication Mode.						*/
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EnableMPCMode(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables the Multi-processor Communication Mode.					*/
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8DisableMPCMode(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables USART transmit interrupt					 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EnableTxInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables USART transmit interrupt					 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8DisableTxInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables USART receive interrupt						 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EnableRxInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables USART receive interrupt					 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8DisableRxInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: enables USART Empty Data Register interrupt			 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EnableEmptyDRInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: disables USART Empty Data Register interrupt		 			    */
/* Inputs: nothing					   											    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8DisableEmptyDRInterrupt(void);
/************************************************************************************/

/************************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	    */
/* triggering the Transmit Complete interrupt.						 			    */
/* Inputs: pointer to a function that takes no arguments and returns no value	    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8TxSetCallBack( void (*ptrToFun)(void) );
/************************************************************************************/

/************************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	    */
/* triggering the Receive Complete interrupt.						 			    */
/* Inputs: pointer to a function that takes no arguments and returns no value	    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8RxSetCallBack( void (*ptrToFun)(void) );
/************************************************************************************/

/************************************************************************************/
/* Description: takes a pointer to a function that is to be executed on		  	    */
/* triggering the Empty Data Register interrupt.					 			    */
/* Inputs: pointer to a function that takes no arguments and returns no value	    */
/* Output: error checking								  						    */
/************************************************************************************/
extern u8 USART_U8EmptyDRSetCallBack( void (*ptrToFun)(void) );
/************************************************************************************/


#endif /* MCAL_USART_USART_INTERFACE_H_ */
