/************************************************************/
/****************    Author:Mohab Ahmed    ******************/
/****************    Layer:MCAL            ******************/
/****************    SWC:SPI               ******************/
/****************    Version:1.00          ******************/
/************************************************************/

#include "STD_TYPES.h"
#include "Bit_Math.h"

#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"
#include "SPI_register.h"

void SPI_voidInitMaster(void)
{
	/*Select as Master*/
	SET_BIT(SPCR,SPCR_MSTR);
	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);
	 /*prescaler /16*/
	SET_BIT(SPCR,SPCR_SPR0);
	SET_BIT(SPCR,SPCR_SPR1);
	CLR_BIT(SPSR,SPSR_SPI2X);

}
void SPI_voidInitSlave(void)
{
	/*Select as Slave*/
	CLR_BIT(SPCR,SPCR_MSTR);
	/*SPI Enable*/
	SET_BIT(SPCR,SPCR_SPE);

}
u8 SPI_u8Transceive(u8 Copy_u8Data)
{
			/*Send the data*/
	SPDR=Copy_u8Data;\
	/*busy waiting until transfer complete*/
	while(GET_BIT(SPSR,SPSR_SPIF)==0);

	/*get the exchanged the received data*/
	return SPDR;

}
