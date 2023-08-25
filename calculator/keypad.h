/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   keypad.h                                                     *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                   *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        21/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for Keypad driver                                *
 *                                                                             *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define POOLING 0
#define INTERRUPTS 1

/* Keypad mode configuration, polling or interrupts */
#define KEYPAD_MODE POOLING

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_PORT_ID                    PORTB_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Get the Keypad pressed button.
 */
uint8_t KEYPAD_getPressedKey(void);

/*
 * Description :
 * Handle the interrupted column.
 */
void EXTI_PORTBHandler(void);

#endif /* KEYPAD_H_ */
