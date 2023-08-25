/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   systick.h                                                    *
 *                                                                             *
 * [AUTHOR]:      Ahmed Saeed                                                  *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        24/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for systick driver                               *
 *                                                                             *
 *******************************************************************************/

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define POOLING 0
#define INTERRUPTS 1

/* Keypad mode configuration, polling or interrupts */
#define SYSTICK_MODE INTERRUPTS

#define SYSTEM_FREQUENCY 16000000

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void Systick_Init(float delay);


#endif /* SYSTICK_H_ */
