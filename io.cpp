#include "io.h"

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

lcdLight::lcdLight()
{
    enable();
    resetCounter();
}

void lcdLight::off()
{
    P2OUT |= DISPLAY_LED_BIT;
}

void lcdLight::on()
{
    P2OUT &= ~DISPLAY_LED_BIT;
}

void lcdLight::countDown()
{
    if (counter == 0)
    {
        return;
    }
    if (counter == 1)
    {
        off();
    }
    counter--;
}

void lcdLight::resetCounter()
{
    on();
    counter = 10; // 10 iterations (1 per sec)
}

void lcdLight::enable()
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

void lcdLight::disable()
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