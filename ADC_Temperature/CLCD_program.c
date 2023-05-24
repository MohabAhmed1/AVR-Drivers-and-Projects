/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:HAL            ******************/
/****************    SWC:LCD               ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#include "STD_TYPES.h"
#include "Bit_Math.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"
#include "CLCD_interface.h"

u8 Global_u8ReadingStyle;
void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	/*Set RS to low for command*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_LOW);
	/*Set RW to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*Set Command to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Command);
	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);


}

void CLCD_voidSendData(u8 Copy_u8Data)
{

	/*Set RS to high for data*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8PIN_HIGH);
	/*Set RW to low for write*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8PIN_LOW);
	/*Set data to data pins*/
	DIO_u8SetPortValue(CLCD_DATA_PORT,Copy_u8Data);
	/*Send enable pulse*/
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8PIN_LOW);

}

void CLCD_voidSendString(const char* Copy_pcData)
{
	u8 Local_u8Counter=0;
	while((Copy_pcData[Local_u8Counter])!='\0')
	{
		CLCD_voidSendData((Copy_pcData[Local_u8Counter]));
		Local_u8Counter++;
	}

}
void CLCD_voidInit(void)
{
	/*Wait for more than 30ms*/
	_delay_ms(40);
	/*Function set command:2 lines ,5*8 Font size*/
	CLCD_voidSendCommand(0b00111000);
	/*display on/off control:display enable,disable cursor,no blink cursor*/
	CLCD_voidSendCommand(0b00001100);
	/*Clear display*/
	CLCD_voidSendCommand(1);

}

void CLCD_voidGoToXY(u8 Copy_u8XPos, u8 Copy_u8YPos)
{
	u8 Local_u8Adress;
	if(Copy_u8XPos==0)
	{
		//locate in the first line
		Local_u8Adress=Copy_u8YPos;
	}
	else if(Copy_u8XPos==1)
	{
		//locate in the second line
		Local_u8Adress=Copy_u8YPos+0x40;
	}
	//Send bit 8 in DDRAM and then the rest bits are the address then send it .
	CLCD_voidSendCommand(Local_u8Adress+128);
}

void CLCD_voidWriteSpecialCharacter(u8 * Copy_pu8Pattern,u8 Copy_pu8PatternNumber,u8 Copy_u8XPos,u8 Copy_u8YPos)
{
	u8 Local_u8CGRAMAdress=0,Local_u8iterator;
	//getting CGRAM Address where each block consists of 8 bytes
	Local_u8CGRAMAdress=Copy_pu8PatternNumber*8;
	// send CGRAM address to save the required pattern in CGRAM
	CLCD_voidSendCommand(Local_u8CGRAMAdress+64);
	/*Writing the pattern on the CGRAM*/
	for(Local_u8iterator=0;Local_u8iterator<8;Local_u8iterator++)
	{
		CLCD_voidSendData(Copy_pu8Pattern[Local_u8iterator]);
	}
	/*go back to DDRAM to display the pattern */
	CLCD_voidGoToXY(Copy_u8XPos,Copy_u8YPos);
	//Display the pattern written on the CGRAM
	CLCD_voidSendData(Copy_pu8PatternNumber);

}

void CLCD_voidWriteNumber(u32 Copy_u32Number)//99
{
	u8 Local_u8Counter=0,Local_u8LcdNumber;
	u32 Local_u32divisible=1;
	u32 Local_u32temp=Copy_u32Number;
	if(Copy_u32Number==0)
		CLCD_voidSendData('0');
	else
	{
		while(Local_u32temp!=0) /*getting the number of the digits*/
		{
			Local_u8Counter++;
			Local_u32temp=Local_u32temp/10;

		}

		while(Local_u8Counter>1) /*getting the divisible to get each number seperately*/
		{
			Local_u8Counter--;
			Local_u32divisible*=10;
		}

		while(Local_u32divisible!=0)  /*getting each number and send it to the LCD*/
		{
			Local_u8LcdNumber=Copy_u32Number/Local_u32divisible;
			CLCD_voidSendData(Local_u8LcdNumber+'0');
			Copy_u32Number=Copy_u32Number-(Local_u8LcdNumber*Local_u32divisible);
			Local_u32divisible=Local_u32divisible/10;
		}
	}
}

