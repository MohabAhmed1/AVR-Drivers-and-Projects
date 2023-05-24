/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:ADC               ******************/
/****************    Version:1.00          ******************/
/************************************************************/
#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_
/*Reference Selections*/
#define ADC_AREF_INTERNAL 			1
#define ADC_AREF_EXTERNAL			2
#define ADC_AREF_INTERNAL_SMALL 	3


/*left and right adjust*/
#define RIGHT_ADJUST 1
#define LEFT_ADJUST  2


/*Divison factor for decreasing the speed of the conversion*/
#define DVISION_BY_2  				1
#define DVISION_BY_4				2
#define DVISION_BY_8				3
#define DVISION_BY_16				4
#define DVISION_BY_32				5
#define DVISION_BY_64				6
#define DVISION_BY_128				7

#define ADCSRA_MASK 0b11111000

#define ADMUX_MASK  0b11100000

#define SFIOR_MASK  0b00011111


#define ADC_RES_EIGHT_BITS 1
#define ADC_RES_TEN_BITS   2

#define FREE_RUNNING 	   0
#define ANALOG_COMPARATOR  1
#define EXTERNAL_INTERRUPT 2

#define ENABLE    1
#define DISABLE   2

#define IDLE 0
#define BUSY 1
#define CHAIN 2

#define SINGLE_CHANNEL_ASYNCH  0
#define CHAIN_ASYNCH 		   1

#endif /* ADC_PRIVATE_H_ */
