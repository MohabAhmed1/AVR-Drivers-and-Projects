/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:HAL             ******************/
/****************    SWC:Servo             ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "DIO_interface.h"
#include "Servo_config.h"
#include "Servo_interface.h"
#include "Servo_private.h"

void Servo_voidInit(void)
{
	Timer1_voidInit();
	Timer1_voidSetICR(SERVO_ICR);
}
u8 Servo_u8SetAngle(u8 Copy_u8Angle)
{

	u8 Local_u8ErrorState=OK;
	u16 Local_u16ServoOCR;
	if(Copy_u8Angle>=0 && Copy_u8Angle<=180)
	{
		Local_u16ServoOCR=ADC_s32Map(Copy_u8Angle,0,180,750,2500);
		Timer1_voidSetOCR(Local_u16ServoOCR);
	}
	else
	{
		Local_u8ErrorState=NOK;
	}
	return Local_u8ErrorState;
}
