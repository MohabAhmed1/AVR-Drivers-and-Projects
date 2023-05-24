#include "STD_TYPES.h"
#include "Bit_Math.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "KPD_interface.h"
#include "CLCD_interface.h"
u16 Key;
u8 Global_u8ArrowCounter=0;
u8 Global_u8FirstLineCounter=0;
u16 Global_u16FirstNumber=0;
u16 Global_u16SecondNumber=0;
u8 Global_u8OperatorCounter=0;
u16 Global_u16FloatPart=0;
u8 DivideFlag=0;
u8 ErrorFlag=0;
char Global_Operators[4]={'+','-','*','/'};
u16 Global_u16Result;
char Operators;
u8 NumberOfOperators=0;
u8 Two_Operators[2];
void FirstCalculator(u8 Key);
void SecondCalculator(u8 Key);


void FirstNumber(u8 Key);
void Operator(u8 Key);
void SecondNumber(u8 Key);

void FirstNumberSC(u8 Key);
void OperatorSC(u8 Key);
void SecondNumberSC(u8 Key);



void main(void)
{

	PORT_voidinit();
	CLCD_voidInit();
	while(1)
	{

		do
		{
			Key=KPD_u8GetPressedKey();

		}while(Key==0xff);

		//	FirstCalculator(Key);
		SecondCalculator(Key);

	}
}
/*
void FirstCalculator(u8 Key)
{
	if(Key==4)
	{
		CLCD_voidSendCommand(1);
		Global_u8ArrowCounter=0;
		Global_u8FirstLineCounter=0;
		Global_u16FirstNumber=0;
		Global_u16SecondNumber=0;
		Global_u8OperatorCounter=0;
		Global_u16FloatPart=0;
	}

	else
	{
		FirstNumber(Key);
		Key=KPD_u8GetPressedKey();
		Operator(Key);
		Key=KPD_u8GetPressedKey();
		SecondNumber(Key);
		Global_u8FirstLineCounter++;

		CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
		CLCD_voidSendData('=');
		Global_u8ArrowCounter+=2;
		CLCD_voidGoToXY(1,Global_u8ArrowCounter-2);
		CLCD_voidSendData(' ');
		CLCD_voidGoToXY(1,Global_u8ArrowCounter);
		CLCD_voidSendData('^');
		switch (Global_u8OperatorCounter)
		{
		case 0:
			Global_u16Result=Global_u16FirstNumber+Global_u16SecondNumber;break;
		case 1:
			if(Global_u16SecondNumber<Global_u16FirstNumber)
			{
				Global_u16Result=Global_u16FirstNumber-Global_u16SecondNumber;
			}
			else
			{
				Global_u16Result=Global_u16SecondNumber-Global_u16FirstNumber;

				Global_u8FirstLineCounter++;
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidSendData('-');
			}
			break;
		case 2:
			Global_u16Result=Global_u16FirstNumber*Global_u16SecondNumber;break;
		case 3:
			if(Global_u16SecondNumber!=0)
			{
				Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
			}
			else
			{
				Global_u8FirstLineCounter++;
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidSendString("Error");
			}
			if(Global_u16FirstNumber%Global_u16SecondNumber!=0)
			{
				Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
				switch (Global_u16SecondNumber)
				{
				case 2:Global_u16FloatPart=(Global_u16FirstNumber*500)%1000;break;
				case 3:	Global_u16FloatPart=(Global_u16FirstNumber*333)%1000;break;
				case 4:Global_u16FloatPart=(Global_u16FirstNumber*250)%1000;break;
				case 5:	Global_u16FloatPart=(Global_u16FirstNumber*200)%1000;break;
				case 6:	Global_u16FloatPart=(Global_u16FirstNumber*166)%1000;break;
				case 7:Global_u16FloatPart=(Global_u16FirstNumber*143)%1000;break;
				case 8:Global_u16FloatPart=(Global_u16FirstNumber*125)%1000;break;
				case 9:Global_u16FloatPart=(Global_u16FirstNumber*111)%1000;break;
				default:break;
				}
			}
			break;
		default:
			Global_u8FirstLineCounter++;
			CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
			CLCD_voidSendString("Error");
		}
		if((Global_u16FirstNumber%Global_u16SecondNumber!=0)&&Global_u8OperatorCounter==3)
		{
			Global_u8FirstLineCounter++;
			CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
			CLCD_voidWriteNumber(Global_u16Result);
			Global_u8FirstLineCounter++;
			CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
			CLCD_voidSendData('.');
			Global_u8FirstLineCounter++;
			CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
			CLCD_voidWriteNumber(Global_u16FloatPart);
		}
		else
		{
			Global_u8FirstLineCounter++;
			CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
			CLCD_voidWriteNumber(Global_u16Result);

		}
	}
}
void FirstNumber(u8 Local_Key)
{
	CLCD_voidGoToXY(1,Global_u8ArrowCounter);
	CLCD_voidSendData('^');
	CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
	CLCD_voidWriteNumber(Global_u16FirstNumber);


	while(Local_Key!=3)
	{

		Local_Key=KPD_u8GetPressedKey();

		if(Local_Key==1)
		{
			Global_u16FirstNumber++;
			if(Global_u16FirstNumber<9)
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidWriteNumber(Global_u16FirstNumber);
			}
			else
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				Global_u16FirstNumber=9;
				CLCD_voidWriteNumber(Global_u16FirstNumber);
			}
		}
		else if(Local_Key==2)
		{
			Global_u16FirstNumber--;
			if(Global_u16FirstNumber<0)
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				Global_u16FirstNumber=0;
				CLCD_voidWriteNumber(Global_u16FirstNumber);
			}
			else
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidWriteNumber(Global_u16FirstNumber);
			}
		}
		else
		{
			CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
			CLCD_voidWriteNumber(Global_u16FirstNumber);
		}
	}
}
void Operator(u8 Local_Key)
{
	Global_u8ArrowCounter++;
	Global_u8FirstLineCounter++;
	CLCD_voidGoToXY(1,Global_u8ArrowCounter-1);
	CLCD_voidSendData(' ');
	CLCD_voidGoToXY(1,Global_u8ArrowCounter);
	CLCD_voidSendData('^');
	CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
	CLCD_voidSendData(Global_Operators[Global_u8OperatorCounter]);
	while(Local_Key!=3)
	{
		Local_Key=KPD_u8GetPressedKey();



		if(Local_Key==1)
		{
			Global_u8OperatorCounter++;
			if(Global_u8OperatorCounter<=3)
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidSendData(Global_Operators[Global_u8OperatorCounter]);
			}
			else
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				Global_u8OperatorCounter=3;
				CLCD_voidSendData(Global_Operators[Global_u8OperatorCounter]);
			}
		}
		else if(Local_Key==2)
		{
			Global_u8OperatorCounter--;
			if(Global_u8OperatorCounter<0)
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				Global_u8OperatorCounter=0;
				CLCD_voidSendData(Global_Operators[Global_u8OperatorCounter]);
			}
			else
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidSendData(Global_Operators[Global_u8OperatorCounter]);
			}


		}
	}
}
void SecondNumber(u8 Local_Key)
{
	if(Global_u8OperatorCounter==3)
	{
		Global_u16SecondNumber=1;
	}
	Global_u8ArrowCounter++;
	Global_u8FirstLineCounter++;
	CLCD_voidGoToXY(1,Global_u8ArrowCounter-1);
	CLCD_voidSendData(' ');
	CLCD_voidGoToXY(1,Global_u8ArrowCounter);
	CLCD_voidSendData('^');
	CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
	CLCD_voidWriteNumber(Global_u16SecondNumber);


	while(Local_Key!=3)
	{

		Local_Key=KPD_u8GetPressedKey();


		if(Local_Key==1)
		{
			Global_u16SecondNumber++;
			if(Global_u16SecondNumber<9)
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidWriteNumber(Global_u16SecondNumber);
			}
			else
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				Global_u16SecondNumber=9;
				CLCD_voidWriteNumber(Global_u16SecondNumber);
			}
		}
		else if(Local_Key==2)
		{
			Global_u16SecondNumber--;
			if((Global_u8OperatorCounter==3)&&(Global_u16SecondNumber<=1))
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				Global_u16SecondNumber=1;
				CLCD_voidWriteNumber(Global_u16SecondNumber);
			}
			else
			{
				CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
				CLCD_voidWriteNumber(Global_u16SecondNumber);
			}
		}
	}
}*/
void SecondCalculator(u8 Key)
{


	FirstNumberSC(Key);
	do
	{
		Key=KPD_u8GetPressedKey();
	}while(Key==0xff);
	OperatorSC(Key);

	do
	{
		Key=KPD_u8GetPressedKey();
	}while(Key==0xff);
	SecondNumberSC(Key);
	CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
	CLCD_voidSendData('=');
	if(NumberOfOperators<=2)
	{
		if(NumberOfOperators==1)
		{
			switch (Two_Operators[0])
			{
			case '+':
				Global_u8FirstLineCounter++;
				Global_u16Result=Global_u16FirstNumber+Global_u16SecondNumber;break;
			case '-':
				Global_u8FirstLineCounter++;
				if(Global_u16FirstNumber>Global_u16SecondNumber)
				{

					Global_u16Result=Global_u16FirstNumber-Global_u16SecondNumber;
				}
				else
				{
					CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
					CLCD_voidSendData('-');
					Global_u16Result=Global_u16SecondNumber-Global_u16FirstNumber;
					Global_u8FirstLineCounter++;
				}
				break;
			case '*':
				Global_u8FirstLineCounter++;
				Global_u16Result=Global_u16FirstNumber*Global_u16SecondNumber;break;
			case '/':
				if(Global_u16SecondNumber==0)
				{
					CLCD_voidGoToXY(0,Global_u8FirstLineCounter+1);
					CLCD_voidSendString("Error");
					ErrorFlag=1;
				}
				else
				{
					if(Global_u16FirstNumber%Global_u16SecondNumber==0)
					{
						Global_u8FirstLineCounter++;
						Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
					}
					else
					{
						if(Global_u16SecondNumber<=9)
						{
							DivideFlag=1;
							Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
							switch (Global_u16SecondNumber)
							{
							case 2:Global_u16FloatPart=(Global_u16FirstNumber*500)%1000;break;
							case 3:	Global_u16FloatPart=(Global_u16FirstNumber*333)%1000;break;
							case 4:Global_u16FloatPart=(Global_u16FirstNumber*250)%1000;break;
							case 5:	Global_u16FloatPart=(Global_u16FirstNumber*200)%1000;break;
							case 6:	Global_u16FloatPart=(Global_u16FirstNumber*166)%1000;break;
							case 7:Global_u16FloatPart=(Global_u16FirstNumber*143)%1000;break;
							case 8:Global_u16FloatPart=(Global_u16FirstNumber*125)%1000;break;
							case 9:Global_u16FloatPart=(Global_u16FirstNumber*111)%1000;break;
							default:break;
							}
						}
						else if(Global_u16SecondNumber>9)
						{
							DivideFlag=1;
							Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
							Global_u16FloatPart=(((f32)Global_u16FirstNumber/(f32)Global_u16SecondNumber)-(f32)Global_u16Result)*1000.0;
						}
					}
				}break;
			default: break;
			}
		}
		else if(NumberOfOperators==2)
		{
			if(Two_Operators[0]==Two_Operators[1])
			{
				switch (Two_Operators[0])
				{
				case '+':
					Global_u8FirstLineCounter++;
					Global_u16Result=Global_u16FirstNumber+Global_u16SecondNumber;break;
				case '-':
					Global_u8FirstLineCounter++;
					if(Global_u16FirstNumber>Global_u16SecondNumber)
					{
						Global_u16Result=Global_u16FirstNumber-Global_u16SecondNumber;
					}
					else
					{
						CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
						CLCD_voidSendData('-');
						Global_u16Result=Global_u16SecondNumber-Global_u16FirstNumber;
						Global_u8FirstLineCounter++;
					}
					break;
				case '*':
					Global_u8FirstLineCounter++;
					Global_u16Result=Global_u16FirstNumber*Global_u16SecondNumber;break;
				case '/':
					if(Global_u16SecondNumber==0)
					{
						CLCD_voidGoToXY(0,Global_u8FirstLineCounter+1);
						CLCD_voidSendString("Error");
						ErrorFlag=1;
					}
					else
					{
						if(Global_u16FirstNumber%Global_u16SecondNumber==0)
						{
							Global_u8FirstLineCounter++;
							Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
						}
						else
						{
							if(Global_u16SecondNumber<=9)
							{
								DivideFlag=1;
								Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
								switch (Global_u16SecondNumber)
								{
								case 2:Global_u16FloatPart=(Global_u16FirstNumber*500)%1000;break;
								case 3:	Global_u16FloatPart=(Global_u16FirstNumber*333)%1000;break;
								case 4:Global_u16FloatPart=(Global_u16FirstNumber*250)%1000;break;
								case 5:	Global_u16FloatPart=(Global_u16FirstNumber*200)%1000;break;
								case 6:	Global_u16FloatPart=(Global_u16FirstNumber*166)%1000;break;
								case 7:Global_u16FloatPart=(Global_u16FirstNumber*143)%1000;break;
								case 8:Global_u16FloatPart=(Global_u16FirstNumber*125)%1000;break;
								case 9:Global_u16FloatPart=(Global_u16FirstNumber*111)%1000;break;
								default:break;
								}
							}
							else if(Global_u16SecondNumber>9)
							{
								DivideFlag=1;
								Global_u16Result=Global_u16FirstNumber/Global_u16SecondNumber;
								Global_u16FloatPart=(((f32)Global_u16FirstNumber/(f32)Global_u16SecondNumber)-(f32)Global_u16Result)*1000.0;
							}
						}
					}
					break;
				default: break;

				}
			}
			else if(Two_Operators[0]!=Two_Operators[1])
			{
				if((Two_Operators[0]=='+'&&Two_Operators[1]=='-')||(Two_Operators[0]=='-'&&Two_Operators[1]=='+'))
				{
					Global_u8FirstLineCounter++;
					if(Global_u16FirstNumber>Global_u16SecondNumber)
					{
						Global_u16Result=Global_u16FirstNumber-Global_u16SecondNumber;
					}
					else
					{
						CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
						CLCD_voidSendData('-');
						Global_u16Result=Global_u16SecondNumber-Global_u16FirstNumber;
						Global_u8FirstLineCounter++;
					}
				}
				else
				{
					CLCD_voidGoToXY(0,Global_u8FirstLineCounter+1);
					CLCD_voidSendString("Error");
					ErrorFlag=1;

				}
			}

		}
	}
	if(DivideFlag==1)
	{

		Global_u8FirstLineCounter++;
		CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
		CLCD_voidWriteNumber(Global_u16Result);
		if(Global_u16FirstNumber/Global_u16SecondNumber>=10&&Global_u16FirstNumber/Global_u16SecondNumber<100)
		{
			Global_u8FirstLineCounter++;
		}
		else if(Global_u16FirstNumber/Global_u16SecondNumber>=100&&Global_u16FirstNumber/Global_u16SecondNumber<1000)
		{
			Global_u8FirstLineCounter+=2;
		}
		else if(Global_u16FirstNumber/Global_u16SecondNumber>=1000)
		{
			Global_u8FirstLineCounter+=3;
		}
		Global_u8FirstLineCounter++;
		CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
		CLCD_voidSendData('.');
		Global_u8FirstLineCounter++;
		CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
		CLCD_voidWriteNumber(Global_u16FloatPart);


	}
	else if(ErrorFlag==0)
	{
		CLCD_voidGoToXY(0,Global_u8FirstLineCounter);
		CLCD_voidWriteNumber(Global_u16Result);
	}
}
void FirstNumberSC(u8 Key)
{
	Global_u16FirstNumber=Key;
	CLCD_voidWriteNumber(Key);
	Global_u8FirstLineCounter++;
	while(Key!=10||Key!=11||Key!=12||Key!=13)
	{
		do{
			Key=KPD_u8GetPressedKey();
		}while(Key==0xff);
		if(Key==10||Key==11||Key==12||Key==13)
			break;
		Global_u8FirstLineCounter++;
		Global_u16FirstNumber=(Global_u16FirstNumber*10)+Key;
		CLCD_voidWriteNumber(Key);


	}
}
void OperatorSC(u8 Key)
{
	switch (Key)
	{
	case 10:CLCD_voidSendData('+');Two_Operators[NumberOfOperators]='+';NumberOfOperators++;break;
	case 11:CLCD_voidSendData('-');Two_Operators[NumberOfOperators]='-';NumberOfOperators++;break;
	case 12:CLCD_voidSendData('*');Two_Operators[NumberOfOperators]='*';NumberOfOperators++;break;
	case 13:CLCD_voidSendData('/');Two_Operators[NumberOfOperators]='/';NumberOfOperators++;break;
	default:break;
	}
	Global_u8FirstLineCounter++;
	Key=10;
	while(Key==10||Key==11||Key==12||Key==13)
	{
		do{
			Key=KPD_u8GetPressedKey();
		}while(Key==0xff);
		if(NumberOfOperators<2)
		{
			switch (Key)
			{
			case 10:
				CLCD_voidSendData('+');
				Two_Operators[NumberOfOperators]='+';
				Global_u8FirstLineCounter++;
				NumberOfOperators++;break;
			case 11:
				CLCD_voidSendData('-');
				Two_Operators[NumberOfOperators]='-';
				Global_u8FirstLineCounter++;
				NumberOfOperators++;break;
			case 12:
				CLCD_voidSendData('*');
				Two_Operators[NumberOfOperators]='*';
				Global_u8FirstLineCounter++;
				NumberOfOperators++;break;
			case 13:
				CLCD_voidSendData('/');
				Two_Operators[NumberOfOperators]='/';
				Global_u8FirstLineCounter++;
				NumberOfOperators++;break;
			default:break;
			}
		}
		else
			break;
	}
}
void SecondNumberSC(u8 Key)
{

	Global_u16SecondNumber=Key;
	CLCD_voidWriteNumber(Key);
	Global_u8FirstLineCounter++;
	while(Key!=15)
	{
		do{
			Key=KPD_u8GetPressedKey();
		}while(Key==0xff);
		if(Key==15)
			break;
		Global_u8FirstLineCounter++;
		Global_u16SecondNumber=(Global_u16SecondNumber*10)+Key;
		CLCD_voidWriteNumber(Key);


	}

}
