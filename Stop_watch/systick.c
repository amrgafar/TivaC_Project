/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   systick.h                                                    *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        24/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for systick driver                               *
 *                                                                             *
 *******************************************************************************/

#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "systick.h"

void Systick_Init(float delay)
{
    NVIC_ST_RELOAD_R = (SYSTEM_FREQUENCY) - 1;
#if SYSTICK_MODE == POOLING
    NVIC_ST_CTRL_R = 5;
#elif SYSTICK_MODE == INTERRUPTS
    NVIC_ST_CTRL_R = 7;
#endif
    NVIC_ST_CURRENT_R = 0;
}




