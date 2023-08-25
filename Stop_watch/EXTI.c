/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   EXTI.c                                                       *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        24/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: source file for external interrupts driver                   *
 *                                                                             *
 *******************************************************************************/

#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "EXTI.h"
#include "DIO.h"


/*
 * Description :
 * Setup the mode of external interrupt.
 */
void EXTI_Config(uint8_t port,uint8_t pin,Interrupt_Type mode)
{
    if(port == PORTF_ID)
    {
        SET_BIT(NVIC_EN0_R,30);
    }

    else
    {
        SET_BIT(NVIC_EN0_R,port);
    }

    switch(port)
    {
        case PORTA_ID:
            SET_BIT(GPIO_PORTA_IM_R,pin);

            if(mode == LEVEL)
            {
                SET_BIT(GPIO_PORTA_IS_R,pin);
            }

            else if(mode == BOTH_EDGES)
            {
                CLEAR_BIT(GPIO_PORTA_IS_R,pin);
                SET_BIT(GPIO_PORTA_IBE_R,pin);
            }

            else if(mode == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTA_IS_R,pin);
                CLEAR_BIT(GPIO_PORTA_IEV_R,pin);

            }

            else if(mode == RISING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTA_IS_R,pin);
                SET_BIT(GPIO_PORTA_IEV_R,pin);
            }

            break;
        case PORTB_ID:
            SET_BIT(GPIO_PORTB_IM_R,pin);

            if(mode == LEVEL)
            {
                SET_BIT(GPIO_PORTB_IS_R,pin);
            }

            else if(mode == BOTH_EDGES)
            {
                CLEAR_BIT(GPIO_PORTB_IS_R,pin);
                SET_BIT(GPIO_PORTB_IBE_R,pin);
            }

            else if(mode == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTB_IS_R,pin);
                CLEAR_BIT(GPIO_PORTB_IEV_R,pin);

            }
            else if(mode == RISING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTB_IS_R,pin);
                SET_BIT(GPIO_PORTB_IEV_R,pin);
            }

            break;
        case PORTC_ID:
            SET_BIT(GPIO_PORTC_IM_R,pin);

            if(mode == LEVEL)
            {
                SET_BIT(GPIO_PORTC_IS_R,pin);
            }

            else if(mode == BOTH_EDGES)
            {
                CLEAR_BIT(GPIO_PORTC_IS_R,pin);
                SET_BIT(GPIO_PORTC_IBE_R,pin);
            }

            else if(mode == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTC_IS_R,pin);
                CLEAR_BIT(GPIO_PORTC_IEV_R,pin);

            }

            else if(mode == RISING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTC_IS_R,pin);
                SET_BIT(GPIO_PORTC_IEV_R,pin);
            }

            break;
        case PORTD_ID:
            SET_BIT(GPIO_PORTD_IM_R,pin);

            if(mode == LEVEL)
            {
                SET_BIT(GPIO_PORTD_IS_R,pin);
            }

            else if(mode == BOTH_EDGES)
            {
                CLEAR_BIT(GPIO_PORTD_IS_R,pin);
                SET_BIT(GPIO_PORTD_IBE_R,pin);
            }

            else if(mode == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTD_IS_R,pin);
                CLEAR_BIT(GPIO_PORTD_IEV_R,pin);

            }

            else if(mode == RISING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTD_IS_R,pin);
                SET_BIT(GPIO_PORTD_IEV_R,pin);
            }

            break;
        case PORTE_ID:
            SET_BIT(GPIO_PORTE_IM_R,pin);

            if(mode == LEVEL)
            {
                SET_BIT(GPIO_PORTE_IS_R,pin);
            }

            else if(mode == BOTH_EDGES)
            {
                CLEAR_BIT(GPIO_PORTE_IS_R,pin);
                SET_BIT(GPIO_PORTE_IBE_R,pin);
            }

            else if(mode == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTE_IS_R,pin);
                CLEAR_BIT(GPIO_PORTE_IEV_R,pin);
            }

            else if(mode == RISING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTE_IS_R,pin);
                SET_BIT(GPIO_PORTE_IEV_R,pin);
            }

            break;
        case PORTF_ID:
            SET_BIT(GPIO_PORTF_IM_R,pin);

            if(mode == LEVEL)
            {
                SET_BIT(GPIO_PORTF_IS_R,pin);
            }

            else if(mode == BOTH_EDGES)
            {
                CLEAR_BIT(GPIO_PORTF_IS_R,pin);
                SET_BIT(GPIO_PORTF_IBE_R,pin);
            }

            else if(mode == FALLING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTF_IS_R,pin);
                CLEAR_BIT(GPIO_PORTF_IEV_R,pin);

            }

            else if(mode == RISING_EDGE)
            {
                CLEAR_BIT(GPIO_PORTF_IS_R,pin);
                SET_BIT(GPIO_PORTF_IEV_R,pin);
            }

            break;
    }


}

/*
 * Description :
 * returns true if interrupt detected.
 */
uint8_t EXTI_BitHandler( uint8_t port, uint8_t pin)
{
    uint8_t data=0;

    switch (port)
    {
        case PORTA_ID:
            data = GET_BIT(GPIO_PORTA_MIS_R,pin);
            break;

        case PORTB_ID:
            data = GET_BIT(GPIO_PORTB_MIS_R,pin);
            break;

        case PORTC_ID:
            data = GET_BIT(GPIO_PORTC_MIS_R,pin);
            break;

        case PORTD_ID:
            data = GET_BIT(GPIO_PORTD_MIS_R,pin);
            break;

        case PORTE_ID:
            data = GET_BIT(GPIO_PORTE_MIS_R,pin);
            break;

        case PORTF_ID:
            data = GET_BIT(GPIO_PORTF_MIS_R,pin);
            break;

        default:
            break;
    }

    return data;
}

/*
 * Description :
 * clears the detected interrupt to start to check again on interrupts.
 */
void EXTI_ClearBitHandler(uint8_t port,uint8_t pin)
{
    switch (port)
    {
        case PORTA_ID:
            SET_BIT(GPIO_PORTA_ICR_R,pin);
            break;

        case PORTB_ID:
            SET_BIT(GPIO_PORTB_ICR_R,pin);
            break;

        case PORTC_ID:
            SET_BIT(GPIO_PORTC_ICR_R,pin);
            break;

        case PORTD_ID:
            SET_BIT(GPIO_PORTD_ICR_R,pin);
            break;

        case PORTE_ID:
            SET_BIT(GPIO_PORTE_ICR_R,pin);
            break;

        case PORTF_ID:
            SET_BIT(GPIO_PORTF_ICR_R,pin);
            break;

        default:
            break;
    }
}





