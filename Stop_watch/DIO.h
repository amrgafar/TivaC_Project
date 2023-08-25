/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   DIO.h                                                        *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        24/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: header file for DIO driver                                   *
 *                                                                             *
 *******************************************************************************/

#ifndef DIO_H_
#define DIO_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define NUM_OF_PORTS           6

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3
#define PORTE_ID               4
#define PORTF_ID               5


#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
typedef enum
{
    PIN_INPUT_PULL_UP,PIN_INPUT_PULL_DOWN,PIN_OUTPUT_PULL_UP,PIN_OUTPUT_PULL_DOWN
}GPIO_PinDirectionType;

typedef enum
{
    PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description :
 * Setup the direction of the required pin input/output.
 */
void DIO_Init(uint8_t port, uint8_t pin, GPIO_PinDirectionType direction);

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void DIO_WritePin(uint8_t port, uint8_t pin, uint8_t value);

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 */
uint8_t DIO_ReadPin(uint8_t port, uint8_t pin);

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 */
void DIO_WritePort(uint8_t port_num, uint8_t value);

/*
 * Description :
 * delay in milli seconds.
 */
void _delay_ms(uint32_t n);

#endif /* DIO_H_ */
