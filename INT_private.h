#ifndef  INT_PRIVATE_H_
#define INT_PRIVATE_H_

/*Memory Location of used Registers*/
/*Volatile Feature not mandatory*/
#define MCUCR 							*((volatile u8*)0x55)
#define MCUCSR 						*((volatile u8*)0x54)
#define GICR								*((volatile u8*)0x5B)
#define 	ON 							1
#define 	OFF							0
/*USED Bits in each Register*/
/*First: MCUCSR Register (1 bit only)*/
#define 	ISC2 						6				/*INT2 bit Sense Control*/
/*First: MCUCR Register (4 bits only)*/
/*Trigger Type Control*/
/*INT1*/
#define 	ISC11						3 				/*INT1 Highest bit Sense Control*/
#define 	ISC10						2				/*INT1 Lowest bit Sense Control*/
/*INT0*/
#define 	ISC01						1				/*INT0 Highest bit Sense Control*/
#define 	ISC00						0				/*INT0 Lowest bit Sense Control*/
/*GICR Bits*/
#define 	INT2_PIE 					5				/*INT2 Peripheral Interrupt Enable*/
#define 	INT1_PIE					7				/*INT1 Peripheral Interrupt Enable*/
#define 	INT0_PIE 					6				/*INT0 Peripheral Interrupt Enable*/

/*External Interrupts Handlers respectively*/
void __vector_1(void)       		__attribute__((signal));			/*Private section*/
void __vector_2(void)       		__attribute__((signal));			/*Private section*/
void __vector_3(void)       		__attribute__((signal));			/*Private section*/

#endif
