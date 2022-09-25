#include"STD_TYPES.h"
#include "BIT_MATH.h"
#include "INT_private.h"
#include "INT_cfg.h"
/**************************************************************************************************************/
/*******************************	External Interrupt Reserved Pins	**************************************/
/*******************************	INT_0 : Port D	, Pin 2				*************************************/
/*******************************	INT_1 : Port D	, Pin 3				************************************/
/*******************************	INT_2 : Port B	, Pin 2				***********************************/
/*********************************************************************************************************/

/*Global Pointer to function*/
void (*INT0CallBack)(void);
void (*INT1CallBack)(void);
void (*INT2CallBack)(void);

void INT_VidInit(void) /*External Interrupts Initialization*/
{

#if 	INT_0  == ON
	SET_BIT(GICR,INT0_PIE);				/*INT0 Enable - GICR*/
	/*Trigger Type Handling (See ATMEGA32 Data Sheet - External Interrupts table 35)*/
	#if 	INT0_SENSE_CONTROL == FALLING_EDGE
	SET_BIT(MCUCR,ISC01);  												 /*See page 65 in ATMEGA DATA SHEET*/
	CLR_BIT(MCUCR,ISC00);											/*Falling from 5v to 0v through switch*/
	/*Review Internal pull resistance */
	#elif 	INT0_SENSE_CONTROL == RISING_EDGE
	SET_BIT(MCUCR,ISC01);  										/*Rising from 0v to 5v through switch*/
	SET_BIT(MCUCR,ISC00);										/*Review MCU Control Register Diagram P.64*/
	#elif 	INT0_SENSE_CONTROL == ON_CHANGE
	CLR_BIT(MCUCR,ISC01);  										/*Any logical change on INT_PIN*/
	SET_BIT(MCUCR,ISC00);
	#elif 	INT0_SENSE_CONTROL == LOW_LEVEL
	CLR_BIT(MCUCR,ISC01);  									 	/*When INT_PIN in low level */
	CLR_BIT(MCUCR,ISC00);										/*NO Self Nesting*/
	#endif

#endif

	
#if 	INT_1  == ON
	SET_BIT(GICR,INT1_PIE);
	/******INT Sense Control = FALLING EDGE***********/
	#if 	INT1_SENSE_CONTROL == FALLING_EDGE
	SET_BIT(MCUCR,ISC11);  												 /*See page 65 in ATMEGA DATA SHEET*/
	CLR_BIT(MCUCR,ISC10);
	#elif 	INT1_SENSE_CONTROL == RISING_EDGE
	SET_BIT(MCUCR,ISC11);  												 /*See page 65 in ATMEGA DATA SHEET*/
	SET_BIT(MCUCR,ISC10);
	#elif 	INT1_SENSE_CONTROL == ON_CHANGE
	CLR_BIT(MCUCR,ISC11);  												 /*See page 65 in ATMEGA DATA SHEET*/
	SET_BIT(MCUCR,ISC10);
	#elif 	INT1_SENSE_CONTROL == LOW_LEVEL
	CLR_BIT(MCUCR,ISC11);  												 /*See page 65 in ATMEGA DATA SHEET*/
	CLR_BIT(MCUCR,ISC10);
	#endif
#endif

#if 	INT_2  == ON
/*There is no LOW level or Logical Change Triggering*/
/*For more info Check page 64 - External Interrupts*/
	SET_BIT(GICR,INT2_PIE);						/*INT_2 PIE enable*/

	#if 	INT2_SENSE_CONTROL == FALLING_EDGE
	CLR_BIT(MCUCSR,ISC2);  					 /*See page 65 in ATMEGA DATA SHEET*/
	#elif 	INT2_SENSE_CONTROL == RISING_EDGE
	SET_BIT(MCUCSR,ISC2);
	#endif
#endif

}

/*Call back function*/
void INT0SetCallBack(void (*ptr)(void))
{
	INT0CallBack=ptr;
}
void INT1SetCallBack(void (*ptr)(void))
{
	INT1CallBack=ptr;
}
void INT2SetCallBack(void (*ptr)(void))
{
	INT2CallBack=ptr;
}
/*INT0 ISR Function*/
void __vector_1(void)
{
	INT0CallBack();
}
void __vector_2(void)				/*INT1 ISR Function*/
{
	INT1CallBack();
}
void __vector_3(void)			/*INT2 ISR Function*/
{
	INT2CallBack();
}
