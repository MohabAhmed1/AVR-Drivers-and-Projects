#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "DIO_interface.h"
#include "LED_interface.h"
#include "LED_config.h"
#include "LED_private.h"

u8 LED_u8TurnON(u8 Copy_u8Port,u8 Copy_u8Pin,u8 ConnType)
{
	u8 Local_u8ErrorState=0;

	if(Copy_u8Pin<=7)
	{
		if(ConnType==SOURCE)
		{

		DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_HIGH);
		}
		else if(ConnType==SINK)
		{
			DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_LOW);
		}
	}
	else
	{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;

}

u8 LED_u8TurnOFF(u8 Copy_u8Port,u8 Copy_u8Pin,u8 ConnType)
{
	u8 Local_u8ErrorState=0;

	if(Copy_u8Pin<=7)
	{
		if(ConnType==SOURCE)
		{
		DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_LOW);
		}
		else if(ConnType==SINK)
		{
			DIO_u8SetPinValue(Copy_u8Port,Copy_u8Pin,DIO_u8PIN_HIGH);
		}
	}
	else
	{
		Local_u8ErrorState=1;
	}
	return Local_u8ErrorState;

}
