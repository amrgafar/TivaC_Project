/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   keypad.c                                                     *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        21/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: source file for Keypad driver                                *
 *                                                                             *
 *******************************************************************************/

#include "keypad.h"
#include "DIO.h"
#include "EXTI.h"
#include "bitwise_operation.h"
#include "tm4c123gh6pm.h"

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/
uint8_t col;
uint8_t interrupt_flag = 0;

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

/*
 * Function responsible for mapping the switch number in the keypad to
 */
static uint8_t KEYPAD_4x4_adjustKeyNumber(uint8_t button_number);

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

#if KEYPAD_MODE == POOLING
/*
 * Description :
 * Get the Keypad pressed button.
 */
uint8_t KEYPAD_getPressedKey(void)
{
    uint8_t col,row;
    uint8_t keypad_port_value = 0;
    while(1)
    {
        for(col=0;col<KEYPAD_NUM_COLS;col++) /* loop for columns */
        {
            /*
             * Each time setup the direction for all keypad port as input pins,
             * except this column will be output pin
             */
            DIO_Init(KEYPAD_PORT_ID,PIN0_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,PIN1_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,PIN2_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,PIN3_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,PIN4_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,PIN5_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,PIN6_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,PIN7_ID,PIN_INPUT_PULL_UP);
            DIO_Init(KEYPAD_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col,PIN_OUTPUT_PULL_DOWN);

#if(KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
            /* Clear the column output pin and set the rest pins value */
            keypad_port_value = ~(1<<(KEYPAD_FIRST_COL_PIN_ID+col));
#else
            /* Set the column output pin and clear the rest pins value */
            keypad_port_value = (1<<(KEYPAD_FIRST_COLUMN_PIN_ID+col));
#endif
            DIO_WritePort(KEYPAD_PORT_ID,keypad_port_value);

            for(row=0;row<KEYPAD_NUM_ROWS;row++) /* loop for rows */
            {
                /* Check if the switch is pressed in this row */
                if(DIO_ReadPin(KEYPAD_PORT_ID,row+KEYPAD_FIRST_ROW_PIN_ID) == KEYPAD_BUTTON_PRESSED)
                {

                    return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);

                }
            }
        }
    }
}

void EXTI_PORTBHandler(void)
{

}

#elif KEYPAD_MODE == INTERRUPTS
/*
 * Description :
 * Get the Keypad pressed button.
 */
uint8_t KEYPAD_getPressedKey(void)
{
    uint8_t row;

    DIO_Init(KEYPAD_PORT_ID,PIN0_ID,PIN_INPUT_PULL_DOWN);
    DIO_Init(KEYPAD_PORT_ID,PIN1_ID,PIN_INPUT_PULL_DOWN);
    DIO_Init(KEYPAD_PORT_ID,PIN2_ID,PIN_INPUT_PULL_DOWN);
    DIO_Init(KEYPAD_PORT_ID,PIN3_ID,PIN_INPUT_PULL_DOWN);
    DIO_Init(KEYPAD_PORT_ID,PIN4_ID,PIN_INPUT_PULL_UP);
    DIO_Init(KEYPAD_PORT_ID,PIN5_ID,PIN_INPUT_PULL_UP);
    DIO_Init(KEYPAD_PORT_ID,PIN6_ID,PIN_INPUT_PULL_UP);
    DIO_Init(KEYPAD_PORT_ID,PIN7_ID,PIN_INPUT_PULL_UP);

    /* interrupts configuration */
    EXTI_Config(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID,FALLING_EDGE);
    EXTI_Config(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1,FALLING_EDGE);
    EXTI_Config(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2,FALLING_EDGE);
    EXTI_Config(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3,FALLING_EDGE);

    while(1)
    {
        for(row = 0; row < KEYPAD_NUM_ROWS; row++) /* loop for rows */
        {
            /* Set/Clear the row output pin */
            DIO_Init(KEYPAD_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_OUTPUT_PULL_UP);
            DIO_WritePin(KEYPAD_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row,KEYPAD_BUTTON_PRESSED);

            /* Check if the switch is pressed in this row */
            if(interrupt_flag == 1)
            {
                interrupt_flag = 0;

                DIO_WritePin(KEYPAD_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row,KEYPAD_BUTTON_RELEASED);
                DIO_Init(KEYPAD_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT_PULL_DOWN);

                return KEYPAD_4x4_adjustKeyNumber((row*KEYPAD_NUM_COLS)+col+1);

            }

            DIO_WritePin(KEYPAD_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row,KEYPAD_BUTTON_RELEASED);
            DIO_Init(KEYPAD_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,PIN_INPUT_PULL_DOWN);

            _delay_ms(10);
        }
        _delay_ms(10);
    }
}

/*
 * Description :
 * Handle the interrupted column.
 */
void EXTI_PORTBHandler(void)
{
    if(EXTI_BitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID))
    {
        col = 0;
        interrupt_flag = 1;
        EXTI_ClearBitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID);
    }
    else if(EXTI_BitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1))
    {
        col = 1;
        interrupt_flag = 1;
        EXTI_ClearBitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+1);
    }
    else if(EXTI_BitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2))
    {
        col = 2;
        interrupt_flag = 1;
        EXTI_ClearBitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+2);
    }
    else if(EXTI_BitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3))
    {
        col = 3;
        interrupt_flag = 1;
        EXTI_ClearBitHandler(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID+3);
    }
}
#endif

/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */
static uint8_t KEYPAD_4x4_adjustKeyNumber(uint8_t button_number)
{
    uint8_t keypad_button = 0;

    switch(button_number)
    {
        case 1: keypad_button = 1;
                break;
        case 2: keypad_button = 4;
                break;
        case 3: keypad_button = 7;
                break;
        case 4: keypad_button = '.';
                break;
        case 5: keypad_button = 2;
                break;
        case 6: keypad_button = 5;
                break;
        case 7: keypad_button = 8;
                break;
        case 8: keypad_button = 0;
                break;
        case 9: keypad_button = 3;
                break;
        case 10: keypad_button = 6;
                break;
        case 11: keypad_button = 9;
                break;
        case 12: keypad_button = '='; /* ASCII Code of '=' */
                break;
        case 13: keypad_button = '+'; /* ASCII Code of '+' */
                break;
        case 14: keypad_button = '-';/* ASCII Code of '-' */
                break;
        case 15: keypad_button = '*'; /* ASCII Code of '*' */
                break;
        case 16: keypad_button = '/'; /* ASCII Code of '/' */
                break;
        default: keypad_button = button_number;
                break;
    }
    return keypad_button;
}


