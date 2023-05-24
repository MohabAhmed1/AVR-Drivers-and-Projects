/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:SPI               ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_


#define SPDR  *((volatile u8*)0x2F)

#define SPSR  *((volatile u8*)0x2E)
#define SPSR_SPIF 	7   /*SPI interrupt flag*/
#define SPSR_SPI2X  0   /*Double SPI speed bit*/

#define SPCR  *((volatile u8*)0x2D)
#define SPCR_SPIE 	7 	/*SPI interrupt enable*/
#define SPCR_SPE 	6	/*SPI enable*/
#define SPCR_DORD 	5	/*Data order*/
#define SPCR_MSTR 	4	/*Master/Slave select*/
#define SPCR_CPOL 	3	/*Clock polarity*/
#define SPCR_CPHA 	2	/*Clock phase*/
#define SPCR_SPR1 	1	/*Clock select 1*/
#define SPCR_SPR0 	0	/*Clock select 0*/

#endif /* SPI_REGISTER_H_ */
