#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "util/delay.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "ADC_interface.h"
#include "CLCD_interface.h"
#include "ADC_config.h"
u16 Local_u8ADCReading;
void ADCNotification(void);

void main (void)
{

	u16 Millivolt;
	u8 ErrorState;
	s32 Temp;
	PORT_voidinit();
	CLCD_voidInit();
	GIE_voidEnable();
	ADC_voidInit();

	while(1)
	{
	ADC_u8StartConversionASynch(ADC0,&Local_u8ADCReading,&ADCNotification);
DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
_delay_us(20);
DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_LOW);
_delay_us(20);

		Millivolt = (u16)((u32)Local_u8ADCReading*5000UL)/256UL;
				CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Temp:");
		Temp=Millivolt/10;

		CLCD_voidGoToXY(0,5);
		CLCD_voidWriteNumber(Local_u8ADCReading);

		_delay_ms(1000);

		if (Local_u8ADCReading>230)
			DIO_u8SetPortValue(DIO_u8PORTB,0xff);
		else if(Local_u8ADCReading<230 &&Local_u8ADCReading>=200)
			DIO_u8SetPortValue(DIO_u8PORTB,0b01111111);
		else if (Local_u8ADCReading<200 &&Local_u8ADCReading>=170)
			DIO_u8SetPortValue(DIO_u8PORTB,0b00111111);
		else if(Local_u8ADCReading<170 &&Local_u8ADCReading>=140)
			DIO_u8SetPortValue(DIO_u8PORTB,0b00011111);
		else if(Local_u8ADCReading<140 &&Local_u8ADCReading>=110)
			DIO_u8SetPortValue(DIO_u8PORTB,0b00001111);
		else if(Local_u8ADCReading<110 &&Local_u8ADCReading>=80)
			DIO_u8SetPortValue(DIO_u8PORTB,0b00000111);
		else if(Local_u8ADCReading<80 &&Local_u8ADCReading>=50)
			DIO_u8SetPortValue(DIO_u8PORTB,0b00000011);
		else if(Local_u8ADCReading<50 &&Local_u8ADCReading>=0)
			DIO_u8SetPortValue(DIO_u8PORTB,0b00000001);

		Temp=ADC_s32Map(Local_u8ADCReading,0,255,0,8);
		CLCD_voidGoToXY(1,5);
		CLCD_voidWriteNumber(Temp);
		_delay_ms(1000);
		CLCD_voidSendCommand(1);


	}
}
void ADCNotification(void)
{
	CLCD_voidGoToXY(1,5);
	CLCD_voidWriteNumber(Local_u8ADCReading);
}

