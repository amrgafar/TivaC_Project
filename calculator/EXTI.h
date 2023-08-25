/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   EXTI.h                                                       *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        21/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for external interrupts driver                   *
 *                                                                             *
 *******************************************************************************/

#ifndef EXTI_H_
#define EXTI_H_

#include"std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
    BOTH_EDGES,FALLING_EDGE,RISING_EDGE,LEVEL
}Interrupt_Type;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the mode of external interrupt.
 */
void EXTI_Config(uint8_t port,uint8_t pin,Interrupt_Type mode);

/*
 * Description :
 * returns true if interrupt detected.
 */
uint8_t EXTI_BitHandler( uint8_t port, uint8_t pin);

/*
 * Description :
 * clears the detected interrupt to start to check again on interrupts.
 */
void EXTI_ClearBitHandler( uint8_t port, uint8_t pin);



#endif /* EXTI_H_ */
