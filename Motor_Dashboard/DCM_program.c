/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:HAL             ******************/
/****************    SWC:DC Motors         ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#include "STD_TYPES.h"
#include "Bit_Math.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "DCM_interface.h"
#include "DCM_config.h"
#include "DCM_private.h"

void DCM_voidRotateClockwise(void)
{
	DIO_u8SetPinValue(DIO_u8PORTD,DCM_DIR1,DIO_u8PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8PORTD,DCM_DIR2,DIO_u8PIN_LOW);
}
void DCM_voidRotateAnticlockwise(void)
{
	DIO_u8SetPinValue(DIO_u8PORTD,DCM_DIR1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DCM_DIR2,DIO_u8PIN_HIGH);
}
void DCM_voidStop(void)
{
	DIO_u8SetPinValue(DIO_u8PORTD,DCM_DIR1,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,DCM_DIR2,DIO_u8PIN_LOW);
}

