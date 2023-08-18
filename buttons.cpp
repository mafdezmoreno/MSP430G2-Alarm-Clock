#include "buttons.h"

buttons::buttons()
{
    initButtonIncrementValue();
    initButtonDecrementValue();
    initButtonChangeTime();
    initButtonMovePos();
}

void buttons::initButtonDecrementValue()
{
    P1DIR &= ~BIT2;
    P1REN |= BIT2;
    P1OUT |= BIT2;
}

void buttons::initButtonIncrementValue()
{
    P1DIR &= ~BIT3;
    P1REN |= BIT3;
    P1OUT |= BIT3;
}

void buttons::initButtonChangeTime()
{
    //1.0
    P1DIR &= ~BIT0;
    P1REN |= BIT0;
    P1OUT |= BIT0;
}

void buttons::initButtonMovePos()
{
    P2DIR &= ~BIT0;
    P2REN |= BIT0;
    P2OUT |= BIT0;
}

bool buttons::buttonIncrementValueOn()
{
    return ((P1IN & BIT3) != BIT3);
}

bool buttons::checkStateButtonIncrementValue()
{
    if (buttonIncrementValueOn())
    {
        delay();
        if (buttonIncrementValueOn())
        {
            return true;
        }
    }
    return false;
}



bool buttons::buttonDecrementValueOn()
{
    return ((P1IN & BIT2) != BIT2);
}


bool buttons::checkStateButtonDecrementValue()
{
    //1.2
    if (buttonDecrementValueOn())
    {
        delay();
        if (buttonDecrementValueOn())
        {
            return true;
        }
    }
    return false;
}


bool buttons::checkStateButtonMovePos()
{
    //2.0
    if ((P2IN & BIT0) != BIT0)
    {
        delay();
        if ((P2IN & BIT0) != BIT0)
        {
            return true;
        }
    }
    return false;
}

bool buttons::checkStateButtonTime()
{
    //1.0
    if ((P1IN & BIT0) != BIT0)
    {
        delay();
        if ((P1IN & BIT0) != BIT0)
        {
            return true;
        }
    }
    return false;
}

void buttons::delay()
{
    __delay_cycles( 1000 );     // 1ms
}

void buttons::longDelay()
{
    __delay_cycles( 100000 ); // 100ms
}
