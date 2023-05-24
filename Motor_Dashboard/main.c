#include "Bit_Math.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"

#include "DCM_interface.h"
//#include "Servo_interface.h"
#include "STEP_interface.h"
#include "CLCD_interface.h"
#include "util/delay.h"
#define ID_PASS 4
u8 LoginDashboard(void);
void MotorSelection(void);
void DC(void);
void Stepper(void);
void Servo(void);
u8 Verification;
void main(void)
{
	PORT_voidinit();
	CLCD_voidInit();
	u8 try=0;
	u8 flag;
	u8 Key;
	while(1)
	{
		/*Verification Menu*/
		Verification=LoginDashboard();
		if(Verification==OK)
		{
			CLCD_voidGoToXY(1,9);
			CLCD_voidSendString("Correct");
		}
		else
		{
			while(try<2)
			{
				CLCD_voidSendCommand(1);
				CLCD_voidGoToXY(1,11);
				CLCD_voidSendString("try");
				Verification=LoginDashboard();
				if(Verification==OK)
				{
					flag=1;
					break;
				}
				else
				{
					CLCD_voidGoToXY(1,11);
					CLCD_voidSendString("try");
				}
				try++;
			}
			if(flag!=1)
			{
				CLCD_voidGoToXY(1,11);
				CLCD_voidSendString("Wrong");
			}
			else
			{

				CLCD_voidGoToXY(1,9);
				CLCD_voidSendString("Correct");
			}
		}
		////////////////////////////////////////////////////////////////
		_delay_ms(1000);
		MotorSelection();


	}
}
u8 LoginDashboard(void)
{
	u8 Verfied_check;
	u8 Local_Key;

	/*ID*/
	u8 ID_Arr[ID_PASS];
	u8 ID_counter=0;
	CLCD_voidGoToXY(0,0);
	CLCD_voidSendString("ID:");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("Pass:");
	CLCD_voidGoToXY(0,3);
	while(ID_counter<ID_PASS)
	{
		do
		{
			Local_Key=KPD_u8GetPressedKey();
		}while(Local_Key==0xff);
		CLCD_voidWriteNumber(Local_Key);
		ID_Arr[ID_counter]=Local_Key;
		ID_counter++;
	}
	/*Password*/
	CLCD_voidGoToXY(1,5);
	u8 Pass_Arr[ID_PASS];
	u8 Pass_counter=0;
	while(Pass_counter<ID_PASS)
	{
		do
		{
			Local_Key=KPD_u8GetPressedKey();
		}while(Local_Key==0xff);
		CLCD_voidWriteNumber(Local_Key);
		Pass_Arr[Pass_counter]=Local_Key;
		Pass_counter++;
	}

	u8 Compare_counter;
	u8 Check_counter= 0;

	while(Check_counter<4)
	{
		if((ID_Arr[Check_counter])==(Pass_Arr[(ID_PASS-1)-Check_counter]))
		{
			Check_counter++;
		}
		else
		{
			break;
		}
	}
	if(Check_counter==ID_PASS)
	{
		Verfied_check=OK;
	}
	else
	{
		Verfied_check=NOK;
	}

	return Verfied_check;

}
void MotorSelection(void)
{
	u8 Local_Key;
	if(Verification==OK)
	{
		CLCD_voidSendCommand(1);
		CLCD_voidGoToXY(0,5);
		CLCD_voidSendString("Welcome");
		CLCD_voidGoToXY(1,2);
		CLCD_voidSendString("to Motor DB");
		_delay_ms(3500);

		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Choose one Motor");
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("1.DC 2.STP 3.SRV");
		do
		{
			Local_Key=KPD_u8GetPressedKey();
		}while(Local_Key==0xff);
		switch(Local_Key)
		{
		case 1:DC();break;
		case 2://Stepper();break;
		case 3://Servo();break;
		default:CLCD_voidSendCommand(1);CLCD_voidGoToXY(0,2);CLCD_voidSendString("Wrong Choice");_delay_ms(2000);CLCD_voidSendCommand(1);
		}

	}
}
void DC(void)
{
	u8 Local_Key;

	CLCD_voidSendCommand(1);
	CLCD_voidGoToXY(0,0);
	CLCD_voidSendString("Rotation Direction:");
	CLCD_voidGoToXY(1,0);
	CLCD_voidSendString("1.CW  2.CCW");
	do
	{
		Local_Key=KPD_u8GetPressedKey();
	}while(Local_Key==0xff);
	switch(Local_Key)
	{
	case 1:DCM_voidRotateClockwise();break;
	case 2:DCM_voidRotateAnticlockwise();break;
	default:CLCD_voidSendCommand(1);CLCD_voidGoToXY(0,2);CLCD_voidSendString("Wrong Choice");_delay_ms(2000);CLCD_voidSendCommand(1);

	}
}
