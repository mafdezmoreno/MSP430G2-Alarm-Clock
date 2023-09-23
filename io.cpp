#include "io.h"

void enableDisplayLed()
{
    switch (DISPLAY_LED_PORT)
    {  //Set as output
        case 1 :
            P1DIR |= DISPLAY_LED_BIT;
            break;
        case 2 :
            P2DIR |= DISPLAY_LED_BIT;
            break;
    }
}

void disableDisplayLed()
{
    switch (DISPLAY_LED_PORT)
    {
        case 1 :
            P1DIR &= ~DISPLAY_LED_BIT;
            break;
        case 2  :
            P2DIR &= ~DISPLAY_LED_BIT;
            break;
    }
}

void displayLedOff()
{
    P2OUT |= DISPLAY_LED_BIT;
}

void displayLedOn()
{
    P2OUT &= ~DISPLAY_LED_BIT;
}

void enableLed()
{
    P2DIR |= LED_BIT;
}

void disableLed()
{
    P2DIR &= ~LED_BIT;
}

void ledOn()
{
    P2OUT |= LED_BIT;

}

void ledOff()
{
    P2OUT &= ~LED_BIT;
}

void toggleLed()
{
    switch (LED_PORT)
    {
        case 1 :
            P1OUT ^= LED_BIT;
            break;

        case 2  :
            P2OUT ^= LED_BIT;
            break;
    }
}