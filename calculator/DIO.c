/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   DIO.c                                                        *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        21/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: source file for DIO driver                                   *
 *                                                                             *
 *******************************************************************************/

#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "DIO.h"

/*
 * Description :
 * Setup the direction of the required pin input/output.
 */
void DIO_Init(uint8_t port, uint8_t pin, GPIO_PinDirectionType direction)
{
    switch(port)
    {
        case PORTA_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R,0);
            while((SYSCTL_PRGPIO_R &(1<<0))==0);
            GPIO_PORTA_LOCK_R=0X4C4F434B;
            SET_BIT(GPIO_PORTA_CR_R,pin);

            if(direction == 0)
            {
                CLEAR_BIT(GPIO_PORTA_DIR_R,pin);
                SET_BIT(GPIO_PORTA_PUR_R,pin);
                SET_BIT(GPIO_PORTA_DEN_R,pin);
            }

            else if(direction == 1)
            {
                CLEAR_BIT(GPIO_PORTA_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTA_PUR_R,pin);
                SET_BIT(GPIO_PORTA_DEN_R,pin);
            }

            else if(direction == 2)
            {
                SET_BIT(GPIO_PORTA_DIR_R,pin);
                SET_BIT(GPIO_PORTA_PUR_R,pin);
                SET_BIT(GPIO_PORTA_DEN_R,pin);
            }

            else if(direction == 3)
            {
                SET_BIT(GPIO_PORTA_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTA_PUR_R,pin);
                SET_BIT(GPIO_PORTA_DEN_R,pin);
            }

            break;

        case PORTB_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R,1);
            while((SYSCTL_PRGPIO_R &(1<<1))==0);
            GPIO_PORTB_LOCK_R=0X4C4F434B;
            SET_BIT(GPIO_PORTB_CR_R,pin);

            if(direction == 0)
            {
                CLEAR_BIT(GPIO_PORTB_DIR_R,pin);
                SET_BIT(GPIO_PORTB_PUR_R,pin);
                SET_BIT(GPIO_PORTB_DEN_R,pin);
            }

            else if(direction == 1)
            {
                CLEAR_BIT(GPIO_PORTB_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTB_PUR_R,pin);
                SET_BIT(GPIO_PORTB_DEN_R,pin);
            }

            else if(direction == 2)
            {
                SET_BIT(GPIO_PORTB_DIR_R,pin);
                SET_BIT(GPIO_PORTB_PUR_R,pin);
                SET_BIT(GPIO_PORTB_DEN_R,pin);
            }

            else if(direction == 3)
            {
                SET_BIT(GPIO_PORTB_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTB_PUR_R,pin);
                SET_BIT(GPIO_PORTB_DEN_R,pin);
            }

            break;

        case PORTC_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R,2);
            while((SYSCTL_PRGPIO_R &(1<<2))==0);
            GPIO_PORTC_LOCK_R=0X4C4F434B;
            SET_BIT(GPIO_PORTC_CR_R,pin);

            if(direction == 0)
            {
                CLEAR_BIT(GPIO_PORTC_DIR_R,pin);
                SET_BIT(GPIO_PORTC_PUR_R,pin);
                SET_BIT(GPIO_PORTC_DEN_R,pin);
            }

            else if(direction == 1)
            {
                CLEAR_BIT(GPIO_PORTC_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTC_PUR_R,pin);
                SET_BIT(GPIO_PORTC_DEN_R,pin);
            }

            else if(direction == 2)
            {
                SET_BIT(GPIO_PORTC_DIR_R,pin);
                SET_BIT(GPIO_PORTC_PUR_R,pin);
                SET_BIT(GPIO_PORTC_DEN_R,pin);
            }

            else if(direction == 3)
            {
                SET_BIT(GPIO_PORTC_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTC_PUR_R,pin);
                SET_BIT(GPIO_PORTC_DEN_R,pin);
            }

            break;

        case PORTD_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R,3);
            while((SYSCTL_PRGPIO_R &(1<<3))==0);
            GPIO_PORTD_LOCK_R=0X4C4F434B;
            SET_BIT(GPIO_PORTD_CR_R,pin);

            if(direction == 0)
            {
                CLEAR_BIT(GPIO_PORTD_DIR_R,pin);
                SET_BIT(GPIO_PORTD_PUR_R,pin);
                SET_BIT(GPIO_PORTD_DEN_R,pin);
            }

            else if(direction == 1)
            {
                CLEAR_BIT(GPIO_PORTD_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTD_PUR_R,pin);
                SET_BIT(GPIO_PORTD_DEN_R,pin);
            }

            else if(direction == 2)
            {
                SET_BIT(GPIO_PORTD_DIR_R,pin);
                SET_BIT(GPIO_PORTD_PUR_R,pin);
                SET_BIT(GPIO_PORTD_DEN_R,pin);
            }

            else if(direction == 3)
            {
                SET_BIT(GPIO_PORTD_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTD_PUR_R,pin);
                SET_BIT(GPIO_PORTD_DEN_R,pin);
            }

            break;

        case PORTE_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R,4);
            while((SYSCTL_PRGPIO_R &(1<<4))==0);
            GPIO_PORTE_LOCK_R=0X4C4F434B;
            SET_BIT(GPIO_PORTE_CR_R,pin);

            if(direction == 0)
            {
                CLEAR_BIT(GPIO_PORTE_DIR_R,pin);
                SET_BIT(GPIO_PORTE_PUR_R,pin);
                SET_BIT(GPIO_PORTE_DEN_R,pin);
            }

            else if(direction == 1)
            {
                CLEAR_BIT(GPIO_PORTE_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTE_PUR_R,pin);
                SET_BIT(GPIO_PORTE_DEN_R,pin);
            }

            else if(direction == 2)
            {
                SET_BIT(GPIO_PORTE_DIR_R,pin);
                SET_BIT(GPIO_PORTE_PUR_R,pin);
                SET_BIT(GPIO_PORTE_DEN_R,pin);
            }

            else if(direction == 3)
            {
                SET_BIT(GPIO_PORTE_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTE_PUR_R,pin);
                SET_BIT(GPIO_PORTE_DEN_R,pin);
            }

            break;

        case PORTF_ID:
            SET_BIT(SYSCTL_RCGCGPIO_R,5);
            while((SYSCTL_PRGPIO_R &(1<<5))==0);
            GPIO_PORTF_LOCK_R=0X4C4F434B;
            SET_BIT(GPIO_PORTF_CR_R,pin);

            if(direction == 0)
            {
                CLEAR_BIT(GPIO_PORTF_DIR_R,pin);
                SET_BIT(GPIO_PORTF_PUR_R,pin);
                SET_BIT(GPIO_PORTF_DEN_R,pin);
            }

            else if(direction == 1)
            {
                CLEAR_BIT(GPIO_PORTF_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTF_PUR_R,pin);
                SET_BIT(GPIO_PORTF_DEN_R,pin);
            }

            else if(direction == 2)
            {
                SET_BIT(GPIO_PORTF_DIR_R,pin);
                SET_BIT(GPIO_PORTF_PUR_R,pin);
                SET_BIT(GPIO_PORTF_DEN_R,pin);
            }

            else if(direction == 3)
            {
                SET_BIT(GPIO_PORTF_DIR_R,pin);
                CLEAR_BIT(GPIO_PORTF_PUR_R,pin);
                SET_BIT(GPIO_PORTF_DEN_R,pin);
            }

            break;
    }
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void DIO_WritePin(uint8_t port, uint8_t pin, uint8_t value)
{
    switch(port)
        {
            case PORTA_ID:
                if(value == 0)
                {
                    CLEAR_BIT(GPIO_PORTA_DATA_R,pin);
                }

                else if(value == 1)
                {
                    SET_BIT(GPIO_PORTA_DATA_R,pin);
                }

                break;

            case PORTB_ID:
                if(value == 0)
                {
                    CLEAR_BIT(GPIO_PORTB_DATA_R,pin);
                }

                else if(value == 1)
                {
                    SET_BIT(GPIO_PORTB_DATA_R,pin);
                }

                break;

            case PORTC_ID:
                if(value == 0)
                {
                    CLEAR_BIT(GPIO_PORTC_DATA_R,pin);
                }

                else if(value == 1)
                {
                    SET_BIT(GPIO_PORTC_DATA_R,pin);
                }

                break;

            case PORTD_ID:
                if(value == 0)
                {
                    CLEAR_BIT(GPIO_PORTD_DATA_R,pin);
                }

                else if(value == 1)
                {
                    SET_BIT(GPIO_PORTD_DATA_R,pin);
                }

                break;

            case PORTE_ID:
                if(value == 0)
                {
                    CLEAR_BIT(GPIO_PORTE_DATA_R,pin);
                }

                else if(value == 1)
                {
                    SET_BIT(GPIO_PORTE_DATA_R,pin);
                }

                break;

            case PORTF_ID:
                if(value == 0)
                {
                    CLEAR_BIT(GPIO_PORTF_DATA_R,pin);
                }

                else if(value == 1)
                {
                    SET_BIT(GPIO_PORTF_DATA_R,pin);
                }

                break;
        }
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 */
uint8_t DIO_ReadPin(uint8_t port, uint8_t pin)
{
    uint8_t value;

    switch(port)
    {
        case PORTA_ID:
            value = GET_BIT(GPIO_PORTA_DATA_R,pin);
            break;

        case PORTB_ID:
            value = GET_BIT(GPIO_PORTB_DATA_R,pin);
            break;

        case PORTC_ID:
            value = GET_BIT(GPIO_PORTC_DATA_R,pin);
            break;

        case PORTD_ID:
            value = GET_BIT(GPIO_PORTD_DATA_R,pin);
            break;

        case PORTE_ID:
            value = GET_BIT(GPIO_PORTE_DATA_R,pin);
            break;

        case PORTF_ID:
            value = GET_BIT(GPIO_PORTF_DATA_R,pin);
            break;
    }

    return value;
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 */
void DIO_WritePort(uint8_t port, uint8_t value)
{
    switch(port)
    {
        case PORTA_ID:
            GPIO_PORTA_DATA_R = value;
            break;

        case PORTB_ID:
            GPIO_PORTB_DATA_R = value;
            break;

        case PORTC_ID:
            GPIO_PORTC_DATA_R = value;
            break;

        case PORTD_ID:
            GPIO_PORTD_DATA_R = value;
            break;

        case PORTE_ID:
            GPIO_PORTE_DATA_R = value;
            break;

        case PORTF_ID:
            GPIO_PORTF_DATA_R = value;
            break;
    }
}

/*
 * Description :
 * delay in milli seconds.
 */
void _delay_ms(uint32_t n)
{
    uint32_t i,j;

    for(i=0; i<n ; i++)
        for(j=0;j<3180;j++)
        {}
}

