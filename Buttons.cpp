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

bool buttons::checkStateButtonIncrementValue()
{
    if ((P1IN & BIT3) != BIT3)
    {
        for (unsigned int i = 50; i > 0; i--);     // delay
        if ((P1IN & BIT3) != BIT3)
        {
            return true;
        }
    }
    return false;
}

bool buttons::checkStateButtonDecrementValue()
{
    //1.2
    if ((P1IN & BIT2) != BIT2)
    {
        for (unsigned int i = 50; i > 0; i--);     // delay
        if ((P1IN & BIT2) != BIT2)
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
        for (unsigned int i = 50; i > 0; i--);     // delay
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
        for (unsigned int i = 50; i > 0; i--);     // delay
        if ((P1IN & BIT0) != BIT0)
        {
            return true;
        }
    }
    return false;
}
