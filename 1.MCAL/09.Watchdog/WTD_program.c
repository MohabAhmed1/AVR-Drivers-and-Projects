/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:WatchDog          ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "WDT_config.h"
#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_register.h"

void WDT_voidSleep(void)
{
	WDTCR &=WDT_PRESCALER_MASK;
	//WDTCR|=Copy_u8SleepTime;


#if WDT_PRESCALER==_16_3_MS
		WDTCR|=_16_3_MS;
#elif WDT_PRESCALER==_32_5_MS
		WDTCR|=_32_5_MS;
#elif WDT_PRESCALER==_65_MS
		WDTCR|=_65_MS;
#elif WDT_PRESCALER==_0_13_S
		WDTCR|=_0_13_S;
#elif WDT_PRESCALER==_0_26_S
		WDTCR|=_0_26_S;
#elif WDT_PRESCALER==_0_52_S
		WDTCR|=_0_52_S;
#elif WDT_PRESCALER==_1_S
		WDTCR|=_1_S;
#elif WDT_PRESCALER==_2_1_S
		WDTCR|=_2_1_S;
#endif

}
void WDT_voidEnable(void)
{
	SET_BIT(WDTCR,WDTCR_WDE);
}
void WDT_voidDisable(void)
{
	WDTCR|=0b00011000;
	WDTCR=0;
}
