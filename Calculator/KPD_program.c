/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:HAL             ******************/
/****************    SWC:KEYPAD            ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "DIO_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"
#include "KPD_interface.h"

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8PressedKey=KPD_NO_PRESSED_KEY,Local_u8ColumnIndex,Local_u8RowIndex,Local_u8PinState;

	static u8 Local_u8KPDArr[ROW_NUMBER][COLUMN_NUMBER]=KPD_ARR_VAL;

	static u8 Local_u8KPDColumnArr[COLUMN_NUMBER]={KPD_COLUMN0_PIN,KPD_COLUMN1_PIN,KPD_COLUMN2_PIN,KPD_COLUMN3_PIN};
	static u8 Local_u8KPDRowArr[ROW_NUMBER]={KPD_ROW0_PIN,KPD_ROW1_PIN,KPD_ROW2_PIN,KPD_ROW3_PIN};


	for(Local_u8ColumnIndex=0;Local_u8ColumnIndex<COLUMN_NUMBER;Local_u8ColumnIndex++)
	{
		/*Activate the current column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIndex],DIO_u8PIN_LOW);
		for(Local_u8RowIndex=0;Local_u8RowIndex<ROW_NUMBER;Local_u8RowIndex++)
		{
			/*Read the current row*/
			DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIndex],&Local_u8PinState);
			/*Check if switch is pressed*/
			if(Local_u8PinState==DIO_u8PIN_LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowIndex][Local_u8ColumnIndex];
				/*polling busy wait to avoid the repeation of the code many times while the button is pressed*/
				while(Local_u8PinState==DIO_u8PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_PORT,Local_u8KPDRowArr[Local_u8RowIndex],&Local_u8PinState);
				}
				return Local_u8PressedKey;
			}

		}
		/*Deactivate the cuurent column*/
		DIO_u8SetPinValue(KPD_PORT,Local_u8KPDColumnArr[Local_u8ColumnIndex],DIO_u8PIN_HIGH);

	}





	return Local_u8PressedKey;
}


