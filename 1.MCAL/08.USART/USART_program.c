#include "STD_TYPES.h"
#include "Bit_Math.h"
#include "USART_interface.h"
#include "USART_private.h"
#include "USART_register.h"
#include "USART_config.h"


static u8 Data_u8Sent;
static void (*TX_pvCallBackNotificationFunc)(void)=NULL;
static u8* Data_u8Receive =NULL;
static void (*RX_pvCallBackNotificationFunc)(void)=NULL;

void USART_voidInit(void)
{
	u8 Local_u8RegisterSelect;

#if CHAR_SIZE==8
	SET_BIT(Local_u8RegisterSelect,UCSRC_URSEL);
	SET_BIT(Local_u8RegisterSelect,UCSRC_UCSZ1);
	SET_BIT(Local_u8RegisterSelect,UCSRC_UCSZ0);
#elif CHAR_SIZE==7
	SET_BIT(Local_u8RegisterSelect,UCSRC_URSEL);
	SET_BIT(Local_u8RegisterSelect,UCSRC_UCSZ1);
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UCSZ0);
#elif CHAR_SIZE==6
	SET_BIT(Local_u8RegisterSelect,UCSRC_URSEL);
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UCSZ1);
	SET_BIT(Local_u8RegisterSelect,UCSRC_UCSZ0);
#elif CHAR_SIZE==5
	SET_BIT(Local_u8RegisterSelect,UCSRC_URSEL);
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UCSZ1);
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UCSZ0);
#endif
#if STOP_BIT==1

	CLR_BIT(Local_u8RegisterSelect,UCSRC_USBS); //1 stop bit
#elif STOP_BIT==2
	SET_BIT(Local_u8RegisterSelect,UCSRC_USBS);
#endif

#if PARITY==DISABLE
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UPM0); // disable parity
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UPM1);
#elif PARITY==ENABLE
#if PARITY_MODE==EVEN_PARITY
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UPM0); //EVEN parity
	SET_BIT(Local_u8RegisterSelect,UCSRC_UPM1);
#elif PARITY_MODE==ODD_PARITY
	SET_BIT(Local_u8RegisterSelect,UCSRC_UPM0); //ODD parity
	SET_BIT(Local_u8RegisterSelect,UCSRC_UPM1);
#endif
#endif
#if USART_SYNCH_METHOD==ASYNCH
	CLR_BIT(Local_u8RegisterSelect,UCSRC_UMSEL); //Asynchronus
#elif USART_SYNCH_METHOD==SYNCH
	SET_BIT(Local_u8RegisterSelect,UCSRC_UMSEL); //Synchronus
#endif

	UCSRC=Local_u8RegisterSelect;


	/*Baud rate*/
	CLR_BIT(UCSRA,UCSRA_U2X);
	UBRRL=((unsigned int)(FREQ/(16*BAUD_RATE)))-1;


#if TX==ENABLE
	SET_BIT(UCSRB,UCSRB_TXEN); //enable to transmit
#elif TX==DISABLE
	CLR_BIT(UCSRB,UCSRB_TXEN);
#endif
#if RX==ENABLE
	SET_BIT(UCSRB,UCSRB_RXEN); //enable to receive
#elif RX==DISABLE
	CLR_BIT(UCSRB,UCSRB_RXEN);
#endif
}

u8 USART_u8SendAsync(u8 Copy_pu8Data,void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pu8Data==NULL||Copy_pvNotificationFunc==NULL)
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	else
	{
		Data_u8Sent=Copy_pu8Data;
		TX_pvCallBackNotificationFunc=Copy_pvNotificationFunc;
		SET_BIT(UCSRB,UCSRB_UDRIE);
	}
	return Local_u8ErrorState;
}
u8 USART_u8ReceiveAsync(u8 *Copy_pu8Data,void(*Copy_pvNotificationFunc)(void))
{
	u8 Local_u8ErrorState=OK;
	if(Copy_pu8Data==NULL||Copy_pvNotificationFunc==NULL)
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	else
	{
		Data_u8Receive=Copy_pu8Data;
		RX_pvCallBackNotificationFunc=Copy_pvNotificationFunc;
		SET_BIT(UCSRB,UCSRB_RXCIE);
	}
	return Local_u8ErrorState;
}
void USART_voidSendSync(u8 Copy_u8Data)
{
	while(GET_BIT(UCSRA,UCSRA_UDRE)==0);  //WAIT UNTIL TRANSNIT BUFFER IS EMPTY
	UDR=Copy_u8Data;

}
u8 USART_u8ReceiveSync(void)
{
	while(GET_BIT(UCSRA,UCSRA_RXC)==0);
	return UDR;
}

/*TX ISR */
void __vector_14 (void) __attribute__((signal));
void __vector_14 (void)
{
	UDR=Data_u8Sent;
	TX_pvCallBackNotificationFunc();
	CLR_BIT(UCSRB,UCSRB_UDRIE);

}
/*RX ISR*/
void __vector_13 (void) __attribute__((signal));
void __vector_13 (void)
{
	*Data_u8Receive=UDR;
	RX_pvCallBackNotificationFunc();
	CLR_BIT(UCSRB,UCSRB_RXCIE);

}
