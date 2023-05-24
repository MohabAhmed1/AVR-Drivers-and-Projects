/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:ADC               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*Analog channel selections*/

// Single ended Input
#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7
//Differential Input
#define ADC0P_ADC0N_TEN 			8
#define ADC1P_ADC0N_TEN 			9
#define ADC0P_ADC0N_TWO_HUNDERED    10
#define ADC1P_ADC0N_TWO_HUNDERED    11
#define ADC2P_ADC2N_TEN 			12
#define ADC3P_ADC2N_TEN				13
#define ADC2P_ADC2N_TWO_HUNDERED 	14
#define ADC3P_ADC2N_TWO_HUNDERED    15
#define ADC0P_ADC1N_ONE				16
#define ADC1P_ADC1N_ONE				17
#define ADC2P_ADC1N_ONE				18
#define ADC3P_ADC1N_ONE				19
#define ADC4P_ADC1N_ONE				20
#define ADC5P_ADC1N_ONE				21
#define ADC6P_ADC1N_ONE				22
#define ADC7P_ADC1N_ONE				23
#define ADC0P_ADC2N_ONE				24
#define ADC1P_ADC2N_ONE				25
#define ADC2P_ADC2N_ONE				26
#define ADC3P_ADC2N_ONE				27
#define ADC4P_ADC2N_ONE				28


typedef struct
{
	u8 *Channels;
	u16 *Result;
	u8 Chain_Size;
	void (*NotificationFunc)(void);

}Chain_t;

void ADC_voidInit(void);

u8 ADC_u8StartConversionSynch(u8 Copy_u8Channel,u16 *Copy_u16Val);

u8 ADC_u8StartConversionASynch(u8 Copy_u8Channel,u16 *Copy_u16Val, void(*Copy_pvNotificationFunc)(void));

s32 ADC_s32Map(s32 InputVal,s32 Min1,s32 Max1,s32 Min2,s32 Max2);

u8 ADC_u8StartChainASynch(Chain_t * Copy_Chain);


#endif /* ADC_INTERFACE_H_ */
