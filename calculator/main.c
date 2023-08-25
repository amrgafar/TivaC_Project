/*******************************************************************************
 *                                                                             *
 * [FILE NAME]:   main.c                                                       *
 *                                                                             *
 * [AUTHOR]:      Amr Gafar                                                    *
 *                                                                             *
 * [Version]:     1.0.0                                                        *
 *                                                                             *
 * [DATE]:        21/08/2023                                                   *
 *                                                                             *
 * [DESCRIPTION]: Calculator application                                       *
 *                                                                             *
 *******************************************************************************/

#include "DIO.h"
#include "lcd.h"
#include "keypad.h"
#include "EXTI.h"
#include "dynamic_memory.h"
#include "std_types.h"
#include "bitwise_operation.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

/*******************************************************************************
 *                                Global Variables                             *
 *******************************************************************************/

/* Flag raised if invalid mathematical operation detected like division by zero */
uint8_t error_flag = 0;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Function responsible for getting the pressed key number and display it on the LCD then return the key.
 */
int display_key(void);

/*
 * Description :
 * Function responsible for checking if the pressed key is operator or digit.
 */
uint8_t is_operator(char ch);

/*
 * Description :
 * Function responsible for concatenating the digits to form the mathematical equation.
 */
void concat(struct Node**);

/*
 * Description :
 * Function responsible for solving the mathematical equation by following the precedence of arithmetic operators.
 */
int calculate(struct Node**);

/*
 * Description :
 * Function responsible for displaying the answer.
 */
void operation(struct Node**);

/*******************************************************************************
 *                              Main Function                                  *
 *******************************************************************************/
int main(void)
{
    /* Initialize the LCD driver */
    LCD_init();

    while(1)
    {
        /* Create head pointer */
        struct Node* head = NULL;

        /* Perform the mathematical operation then display the answer */
        operation(&head);

        /* Display the answer for 2 seconds */
        _delay_ms(2000);

        /* Clear the screen to let the user enter another mathematical equation */
        LCD_clearScreen();
    }
}

/*
 * Description :
 * Function responsible for getting the pressed key number and display it on the LCD then return the key.
 */
int display_key(void)
{
    int key;

    /* Get the pressed key number, if any switch pressed for more than 200 ms it will considered more than one press */
    key = KEYPAD_getPressedKey();

    if((key <= 9) && (key >= 0))
    {
        LCD_intgerToString(key);   /* display the pressed keypad switch */
    }
    else
    {
        LCD_displayCharacter(key); /* display the pressed keypad switch */
    }

    _delay_ms(200);

    return key;
}

/*
 * Description :
 * Function responsible for checking if the pressed key is operator or digit.
 */
uint8_t is_operator(char ch)
{
    /* return true if the pressed key is operator */
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

/*
 * Description :
 * Function responsible for concatenating the digits to form the mathematical equation.
 */
void concat(struct Node** head)
{
    int i = 1;
    char str1[50];
    char str2[50];
    struct Node* p = *head;

    /* Concatenate any sequence of digits found */
    while (p->next != NULL)
    {
        if(!(is_operator(p->data) || is_operator(p->next->data)))
        {
            /* Convert the digits to strings */
            ltoa(p->data,str1);
            ltoa(p->next->data,str2);

            /* Concatenate the strings */
            strcat(str1, str2);

            /* Convert the concatenated string to integer again and store it */
            p->data = atoi(str1);

            /* Delete the adjacent node */
            deleteNode(&p, p->next->data);
        }

        else
        {
            i++;
            /* If the current or the next node's data was operator, move to the next node */
            p = p->next;
        }
    }
}

/*
 * Description :
 * Function responsible for solving the mathematical equation by following the precedence of arithmetic operators.
 */
int calculate(struct Node** head)
{
    int temp = 0;

    struct Node* p2 = *head;


    while (p2 != NULL)
    {
        /* Perform the multiplication and division operations first */
        if(is_operator(p2->data))
        {
            if(p2->data == '*')
            {
                /* Multiply the two numbers and store them */
                p2->data = temp * p2->next->data;

                /* Delete the nodes that used to perform the calculation */
                deleteNode(&(*head), temp);
                deleteNode(&p2, p2->next->data);
            }

            else if(p2->data == '/')
            {
                /* Check if the second number equal zero */
                if(p2->next->data == 0)
                {
                    /* Show invalid operation message to the user */
                    LCD_clearScreen();
                    LCD_displayString("Division by 0");
                    LCD_moveCursor(1, 0);
                    LCD_displayString("InvalidOperation");

                    /* Raise the error flag */
                    error_flag = 1;

                    /* return from the function once any error detected */
                    return 0;
                }

                /* Divide the two numbers and store them */
                p2->data = temp / p2->next->data;

                /* Delete the nodes that used to perform the calculation */
                deleteNode(&(*head), temp);
                deleteNode(&p2, p2->next->data);
            }
        }
        temp = p2->data;
        p2 = p2->next;
    }

    struct Node* p3 = *head;

    while (p3 != NULL)
    {
        if(is_operator(p3->data))
        {
            if(p3->data == '+')
            {
                /* Add the two numbers and store them */
                p3->data = temp + p3->next->data;

                /* Delete the nodes that used to perform the calculation */
                deleteNode(&(*head), temp);
                deleteNode(&p3, p3->next->data);
            }

            else if(p3->data == '-')
            {
                /* Subtract the two numbers and store them */
                p3->data = temp - p3->next->data;

                /* Delete the nodes that used to perform the calculation */
                deleteNode(&(*head), temp);
                deleteNode(&p3, p3->next->data);
            }
        }
        temp = p3->data;
        p3 = p3->next;
    }

    return temp;
}

/*
 * Description :
 * Function responsible for displaying the answer.
 */
void operation(struct Node** head)
{
    int temp;
    int ans;
    uint8_t counter = 0;

    while(1)
    {
        counter++;

        /* Display the pressed key */
        temp = display_key();

        /* If the LCD is full clear it to allow the user entering more characters */
        if(counter % 32 == 0)
        {
            LCD_clearScreen();
        }

        /* If any LCD line is full except the last one, move to the next line to allow the user entering more characters */
        else if(counter % 16 == 0)
        {
            LCD_moveCursor(1, 0);
        }

        /* Stop taking input characters from the user if he entered '=' character */
        if(temp == '=')
        {
            break;
        }

        /* Insert at the end of the linked list any entered character from the user */
        insertAtEnd(head, temp);
    }

    concat(head);
    ans = calculate(head);

    if(error_flag == 0)
    {
        /* When the user enters '=' the screen will be cleared and the answer will be displayed */
        LCD_clearScreen();
        LCD_displayString("ans = ");
        LCD_intgerToString(ans);
    }

    else
    {
        error_flag = 0;
    }
}
