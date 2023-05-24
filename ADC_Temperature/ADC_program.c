/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:ADC               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "ADC_interface.h"
#include "GIE_interface.h"
#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_private.h"

static u8* ADC_pu8ChannelArr=NULL;   	/*Global variable to carry chain array*/
static u8  ADC_u8ChainSize;			 	/*Global variable to carry number of channels */
static u16* ADC_pu16ChainResultArr=NULL;/*Global variable to carry chain result*/
static u8 ADC_u8ChainConversionIndex=0;

static u8 ADC_u8ISRSource;

static u16* ADC_puReading=NULL;
static void (*ADC_pvCallBackNotificationFunc)(void)=NULL;
u8 ADC_u8BusyState=IDLE;
void ADC_voidInit(void)
{
	/*AVCC as reference voltage*/
#if ADC_REF==ADC_AREF_EXTERNAL
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_REF==ADC_AREF_INTERNAL
	CLR_BIT(ADMUX,ADMUX_REFS0);
	CLR_BIT(ADMUX,ADMUX_REFS1);
#elif ADC_REF==ADC_AREF_INTERNAL_SMALL
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#error "Wrong Voltage Reference Configuration"
#endif

#if ADC_RES==ADC_RES_EIGHT_BITS
	/*Activate the Left adjust to read the 8 bits easily*/
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif ADC_RES==ADC_RES_TEN_BITS
	/*if we resolution is 10 bits so it will be easier to be right adjust*/
	CLR_BIT(ADMUX,ADMUX_ADLAR);

#error "Wrong Resolution Configuration"
#endif



	/*Set Prescaler division*/
	ADCSRA &=ADCSRA_MASK;
#if PRESCALER==DVISION_BY_128
	ADCSRA|=DVISION_BY_128;
#elif PRESCALER==DVISION_BY_64
	ADCSRA|=DVISION_BY_64;
#elif PRESCALER==DVISION_BY_32
	ADCSRA|=DVISION_BY_32;
#elif PRESCALER==DVISION_BY_16
	ADCSRA|=DVISION_BY_16;
#elif PRESCALER==DVISION_BY_8
	ADCSRA|=DVISION_BY_8;
#elif PRESCALER==DVISION_BY_4
	ADCSRA|=DVISION_BY_4;
#elif PRESCALER==DVISION_BY_2
	ADCSRA|=DVISION_BY_2;
#endif

	/*Enable the peripheral*/
	SET_BIT(ADCSRA,ADCSRA_ADEN);
#if (ADC_AUTO_TRIGGER==ENABLE)
	/*enable auto trigger mode*/
	SET_BIT(ADCSRA,ADCSRA_ADATE);
	SFIOR&=SFIOR_MASK;
	SFIOR|=TRIGGER_SOURCE;

	/*Start conversion*/
	SET_BIT(ADCSRA,ADCSRA_ADSC);
#error "Wrong ADC trigger selection"
#endif


}
u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16 *Copy_u16Val)
{
	u32 Local_u32Counter=0;
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{
		ADC_u8BusyState=BUSY;
#if ADC_AUTO_TRIGGER==DISABLE
		/*Clear the MUX bits in ADMUX register*/
		ADMUX &=ADMUX_MASK;
		/*Set the required channel into the MUX bits*/
		ADMUX|=Copy_u8Channel;
		/*Start conversion*/
		SET_BIT(ADCSRA,ADCSRA_ADSC);
		/*polling busy waiting until the conversion flag is set  and the counter reaching timeout value*/
		while(((GET_BIT(ADCSRA,ADCSRA_ADIF))==0)&& (Local_u32Counter!=ADC_u32TIMEOUT))
		{
			Local_u32Counter++;
		}
		if(Local_u32Counter==ADC_u32TIMEOUT)
		{
			/*loop is broken bec timeout is reached*/
			Local_u8ErrorState=NOK;
		}
		else
		{
			/*loop is broken because flag is raised*/
			/*clear the conversion complete flag*/
			SET_BIT(ADCSRA,ADCSRA_ADIF);
#if ADC_RES==ADC_RES_EIGHT_BITS
			*Copy_u16Val=ADCH;

#elif ADC_RES==ADC_RES_TEN_BITS
			*Copy_u16Val=ADC;
#endif
		}
#elif ADC_AUTO_TRIGGER==ENABLE
		/*Clear the MUX bits in ADMUX register*/
		ADMUX &=ADMUX_MASK;
		/*Set the required channel into the MUX bits*/
		ADMUX|=Copy_u8Channel;
#if ADC_RES==ADC_RES_EIGHT_BITS
		*Copy_u16Val=ADCH;

#elif ADC_RES==ADC_RES_TEN_BITS
		*Copy_u16Val=ADC;
#endif
#error "Please choose to Enable or to Disable the Auto trigger mode "
#endif
		ADC_u8BusyState=IDLE;
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}
	return Local_u8ErrorState;
}
u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel,u16 *Copy_u16Val,void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(ADC_u8BusyState==IDLE)
	{
		if(Copy_u16Val==NULL ||Copy_pvNotificationFunc==NULL)
		{
			Local_u8ErrorState=NULL_POINTER;
		}
		else
		{
			/*making ADC busy until the conversion is done*/
			ADC_u8BusyState=BUSY;
			/*make ISR source single channel Asynch*/
			ADC_u8ISRSource=SINGLE_CHANNEL_ASYNCH;
			/*initialize the reading variable globally*/
			ADC_puReading=Copy_u16Val;
			/*initialize the  callback notification function globally*/
			ADC_pvCallBackNotificationFunc=Copy_pvNotificationFunc;
			/*Clear the MUX bits in ADMUX register*/
			ADMUX &=ADMUX_MASK;
			/*Set the required channel into the MUX bits*/
			ADMUX|=Copy_u8Channel;
			/*Start conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			/*ADC interrupt enable*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorState=BUSY_FUNC;
	}

	return Local_u8ErrorState;

}


u8 ADC_u8StartChainASynch(Chain_t * Copy_Chain)
{
	u8 Local_u8ErrorState=OK;
	if(Copy_Chain==NULL)
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	else
	{
		if(ADC_u8BusyState==IDLE)
		{
			/*Make ADC busy */
			ADC_u8BusyState=BUSY;

			/*ISR source chain Asynch*/
			ADC_u8ISRSource=CHAIN_ASYNCH;

			/*initialize chain channel array*/
			ADC_pu8ChannelArr=Copy_Chain->Channels;

			/*initialize Result array*/
			ADC_pu16ChainResultArr=Copy_Chain->Result;

			/*initialize Chain Size*/
			ADC_u8ChainSize=Copy_Chain->Chain_Size;

			/*initialize Notification function*/
			ADC_pvCallBackNotificationFunc=Copy_Chain->NotificationFunc;

			/*initialize current conversion index */
			ADC_u8ChainConversionIndex=0;

			/*Set the required channel (first channel)*/
			ADMUX &=ADMUX_MASK;
			ADMUX |=ADC_pu8ChannelArr[ADC_u8ChainConversionIndex];

			/*Start Conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			/*Enable the interrupt*/
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
		else
		{
			Local_u8ErrorState=BUSY_FUNC;
		}
	}
}

s32 ADC_s32Map(s32 InputVal,s32 Min1,s32 Max1,s32 Min2,s32 Max2)
{
	s32 Local_s32Range2Diff,Local_s32Range1Diff,Local_s32Output;
	Local_s32Range2Diff=Max2-Min2;
	Local_s32Range1Diff=Max1-Min1;
	Local_s32Output=(((InputVal-Min1)*Local_s32Range2Diff)/Local_s32Range1Diff)+Min2;
	return Local_s32Output;

}


/*
u8 ADC_StartChainConversion(ADC_Chain_t *Chain )
{
	ADC_u8ChainID=Chain->Chain_ID;
	ADC_u8ChainSize=Chain->Chain_Size;
	ADC_u8Index=ADC_u8ChainSize;
	ADC_16ResultArr=Chain->Arr;
	ADC_u8BusyState=CHAIN;
	ADC_pvCallBackNotificationFunc=Chain->NotificationFunc;
	u8 Local_u8ErrorStatus=OK;

	if(ADC_pvCallBackNotificationFunc!=NULL)
	{
		if(ADC_u8ChainID==0)
		{
			ADMUX &=ADMUX_MASK;
			SET_BIT(ADCSRA,ADCSRA_ADSC);
			SET_BIT(ADCSRA,ADCSRA_ADIE);
		}
	}
	else
	{
		Local_u8ErrorStatus=NULL_POINTER;
	}
	return Local_u8ErrorStatus;
}
 */
void __vector_16 (void) __attribute__((signal));
void __vector_16 (void)
{


	if(ADC_u8ISRSource==SINGLE_CHANNEL_ASYNCH)
	{
		/*Read ADC result*/
#if ADC_RES==ADC_RES_EIGHT_BITS
		*ADC_puReading=ADCH;

#elif ADC_RES==ADC_RES_TEN_BITS
		*ADC_puReading=ADC;
#endif
		ADC_u8BusyState=IDLE;
		/*Invoke the callback notification function*/
		ADC_pvCallBackNotificationFunc();
		/*clear interrupt enable*/
		CLR_BIT(ADCSRA,ADCSRA_ADIE);
	}
	else if(ADC_u8ISRSource==CHAIN_ASYNCH)
	{
		/*read the current conversion*/
#if ADC_RES==ADC_RES_EIGHT_BITS
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex]=ADCH;
#elif ADC_RES==ADC_RES_TEN_BITS
		ADC_pu16ChainResultArr[ADC_u8ChainConversionIndex]=ADC;
#endif
		/*Increment chain index*/
		ADC_u8ChainConversionIndex++;

		/*check if the chain is finished or not */
		if(ADC_u8ChainConversionIndex==ADC_u8ChainSize)
		{
			/*chain is finished*/

			/*making the ADC idle again*/
			ADC_u8BusyState==IDLE;

			/*invoke callback notification function*/
			ADC_pvCallBackNotificationFunc();
			/*Disable the ADC conversion complete interrupt*/
			CLR_BIT(ADCSRA,ADCSRA_ADIE);
		}

		else
		{
			/*chain is not finished*/
			/*Set the new required channel*/
			ADMUX &=ADMUX_MASK;
			ADMUX|=ADC_pu8ChannelArr[ADC_u8ChainConversionIndex];
			/*Start the new conversion*/
			SET_BIT(ADCSRA,ADCSRA_ADSC);
		}
	}
}

