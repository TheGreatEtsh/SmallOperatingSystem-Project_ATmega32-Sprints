/*
 * exi_private.h
 *
 *  Created on: May 16, 2023
 *      Author: Alaa
 */

#ifndef EXI_PRIVATE_H_
#define EXI_PRIVATE_H_


/*************************************************************************************************************
 * 										Ext. int. registers addressed and bits
 ************************************************************************************************************/

#define GICR             *((volatile uint8_t_*) 0x5B)
#define GICR_INT1		 7
#define GICR_INT0		 6
#define GICR_INT2		 5

#define GIFR             *((volatile uint8_t_*) 0x5A)
#define MCUCR            *((volatile uint8_t_*) 0x55)
#define MCUCR_ISC11      3
#define MCUCR_ISC10      2
#define MCUCR_ISC01      1
#define MCUCR_ISC00      0

#define MCUCSR           *((volatile uint8_t_*) 0x54)
#define MCUCSR_ISC2		 6

/*************************************************************************************************************
 * 													Macros
 ************************************************************************************************************/

#define EXI0_SENSE_MODE_MASK		0b11111100
#define EXI1_SENSE_MODE_MASK		0b11110011
#define EXI2_SENSE_MODE_MASK		0b10111111


#endif /* EXI_PRIVATE_H_ */