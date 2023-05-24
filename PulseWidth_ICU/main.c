#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "TIMER_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "GIE_interface.h"
#include "PWM_interface.h"
#include "PWM_private.h"
#include "TIMER_private.h"
#define RES 65536
static u16 periodTicks=0;
static u16 ONTicks=0;
static u16 Overflows=0;
void ICU_SW(void);
void ICU_HW(void);
void Timer1_overflow(void);
void main (void)
{

	PORT_voidinit();
	ICU_voidInit();
	ICU_u8SetCallback(&ICU_HW);
	TIMER1_Normal_u8SetCallBack(&Timer1_overflow);
//	EXTI_voidInt0Init();
//	EXTI_u8Int0SetCallBack(&ICU);
	CLCD_voidInit();
	PWM_t pwm={FAST_PWM,NON_REVERSED_FAST_PWM,DIVIDE_BY_8};
	PWM_Timer0_voidInit(&pwm);
	Timer1_t timer1={NORMAL_MODE,PRESCALE_DIVIDE_BY_8};
	TIMER1_voidInit(&timer1);

	GIE_voidEnable();

	while(1)
	{
		while((periodTicks==0)&&(ONTicks==0));
		CLCD_voidGoToXY(0,0);
		CLCD_voidSendString("Period Ticks:");
		CLCD_voidWriteNumber(periodTicks);
		CLCD_voidGoToXY(1,0);
		CLCD_voidSendString("ON Ticks:");
		CLCD_voidWriteNumber(ONTicks);
	}
}
void ICU_SW(void)
{
	static u8 counter=0;
	counter++;
	if(counter==1)
	{
		TIMER1_voidSetTimerVal(0);
	}
	else if (counter==2)
	{
		periodTicks=TIMER1_voidGetTimer1Reading();
		EXTI_u8Int0SenseControl(FALLING_EDGE);
	}
	else if(counter==3)
	{
		ONTicks=TIMER1_voidGetTimer1Reading();
		ONTicks-=periodTicks;
		EXTI_u8IntDisable(INT0);

	}
}
void ICU_HW(void)
{
	static u16 read1,read2,read3;
	static u16 Local_u16Counter=0;
	Local_u16Counter++;
	if(Local_u16Counter==1)
	{
		read1=ICU_u16ReadICR()+(Overflows*RES);
	}
	else if (Local_u16Counter==2)
	{
		read2=ICU_u16ReadICR()+(Overflows*RES);
		periodTicks=read2-read1;
		ICU_u8SetTriggerEdge(ICU_Falling);
	}
	else if(Local_u16Counter==3)
	{
		read3=ICU_u16ReadICR()+(Overflows*RES);
		ONTicks=read3-read2;
		ICU_voidDisableInterrupt();
	}
}
void Timer1_overflow(void)
{
	Overflows++;
}
