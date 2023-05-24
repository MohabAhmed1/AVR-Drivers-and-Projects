/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:HAL             ******************/
/****************    SWC:Stepper Motor     ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "DIO_interface.h"
#include "STEP_config.h"
#include "STEP_interface.h"
#include "STEP_private.h"
#include "util/delay.h"

void STEP_u16SetAngleAntiClockwise(u16 Copy_u16Angle)
{
	u16 Local_u16Steps=0;
	Local_u16Steps=(Copy_u16Angle/0.175)/4;
	for(Local_u16Steps;Local_u16Steps>0;Local_u16Steps--)
	{
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_LOW);
		_delay_ms(2);
	}
}

void STEP_u16SetAngleClockwise(u16 Copy_u16Angle)
{
	u16 Local_u16Steps=0;
	Local_u16Steps=(Copy_u16Angle/0.175)/4;
	for(Local_u16Steps;Local_u16Steps>0;Local_u16Steps--)
	{
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_LOW);
		_delay_ms(2);

		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_LOW);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_HIGH);
		_delay_ms(2);

	}

}
void STEP_voidStop(void)
{
	DIO_u8SetPinValue(DIO_u8PORTD,STEP_BLUE,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,STEP_PINK,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,STEP_YELLOW,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTD,STEP_ORANGE,DIO_u8PIN_LOW);
}


