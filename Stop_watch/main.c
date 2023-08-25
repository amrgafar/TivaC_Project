/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   main.c                                                       *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        24/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: Stop watch application                                       *
 *                                                                             *
 *******************************************************************************/

#include "tm4c123gh6pm.h"
#include "DIO.h"
#include "lcd.h"
#include "EXTI.h"
#include "systick.h"
#include "std_types.h"
#include "bitwise_operation.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* variable used to store the previous count of seconds */
signed char previous_seconds = -1;

/* flag used to reload systick timer and to increament the number of seconds */
unsigned char count_flag = 0;

/* flag used to manage the transition between pause and continue states */
unsigned char status_flag = 1;

/* variables to hold the clock time */
unsigned char seconds_count = 0;
unsigned char minutes_count = 0;
unsigned char hours_count = 0;

/*
 * Description :
 * systick handler used to increment the clock
 */
void SysTick_Handler(void);

/*
 * Description :
 * portF handler used to pause and continue incrementing the stop watch using two switches
 */
void Switchs_Handler(void);

/*
 * Description :
 * function responsible for incrementing the stop watch and displaying the result.
 */
void stop_watch(void);

int main(void)
{
    /* Initialize the LCD driver */
    LCD_init();

    /* Initialize the systick driver */
    Systick_Init(1);

    /* Initialize the two switches in portF */
    DIO_Init(PORTF_ID, PIN0_ID, PIN_INPUT_PULL_UP);
    DIO_Init(PORTF_ID, PIN4_ID, PIN_INPUT_PULL_UP);

    /* interrupts configuration */
    EXTI_Config(PORTF_ID, PIN0_ID,FALLING_EDGE);
    EXTI_Config(PORTF_ID, PIN4_ID,FALLING_EDGE);

    while(1)
    {
        stop_watch();
    }
}

void SysTick_Handler(void)
{
    count_flag = 1;
}

void Switchs_Handler(void)
{
    if(GET_BIT(GPIO_PORTF_DATA_R,0) == 0)
    {
        status_flag = 0;
        EXTI_ClearBitHandler(PORTF_ID,PIN0_ID);
    }

    else if(GET_BIT(GPIO_PORTF_DATA_R,4) == 0)
    {
        status_flag = 1;
        EXTI_ClearBitHandler(PORTF_ID,PIN4_ID);
    }
}

void stop_watch(void)
{
    if(status_flag == 1)
    {
        if(count_flag == 1)
        {
            Systick_Init(1);

            previous_seconds = seconds_count;

            //enter here every one second
            //increment seconds count
            seconds_count++;

            if(seconds_count == 60)
            {
                seconds_count = 0;
                minutes_count++;
            }
            if(minutes_count == 60)
            {
                minutes_count = 0;
                hours_count++;
            }
            if(hours_count == 24)
            {
                hours_count = 0;
            }

            // reset the flag again
            count_flag = 0;
        }

        else
        {
            char time[10] = " ";
            char hours[3];
            char minutes[3];
            char seconds[3];
            char zero[2] = "0";
            char var[2] = ":";

            if(hours_count < 10)
            {
                strcat(time,zero);
                ltoa(hours_count,hours);
                strcat(time,hours);
            }

            else
            {
                ltoa(hours_count,hours);
                strcat(time,hours);
            }

            strcat(time,var);

            if(minutes_count < 10)
            {
                strcat(time,zero);
                ltoa(minutes_count,minutes);
                strcat(time,minutes);
            }

            else
            {
                ltoa(minutes_count,minutes);
                strcat(time,minutes);
            }

            strcat(time,var);

            if(seconds_count < 10)
            {
                strcat(time,zero);
                ltoa(seconds_count,seconds);
                strcat(time,seconds);
            }

            else
            {
                ltoa(seconds_count,seconds);
                strcat(time,seconds);
            }

            if(previous_seconds != seconds_count)
            {
                previous_seconds = seconds_count;

                /* clear the screen after any change */
                LCD_clearScreen();

                /* display the new time */
                LCD_displayString(time);
            }
        }
    }
}

