#include "buttons.h"

buttons::buttons()
{
    initTime();
    initIncrement();
    initMove();
    initDecrement();
    initAlarm();
}

void buttons::initTime()
{
    P_DIR_TIME &= ~BIT_TIME;
    P_REN_TIME |= BIT_TIME;
    P_OUT_TIME |= BIT_TIME;
}

bool buttons::buttonTime()
{
    return ((P_IN_TIME & BIT_TIME) != BIT_TIME);
}

void buttons::initIncrement()
{
    P_DIR_INCREMENT &= ~BIT_INCREMENT;
    P_REN_INCREMENT |= BIT_INCREMENT;
    P_OUT_INCREMENT |= BIT_INCREMENT;
}

bool buttons::buttonIncrement()
{   // 1.3
    return ((P_IN_INCREMENT & BIT_INCREMENT) != BIT_INCREMENT);
}

void buttons::initMove()
{
    P_DIR_MOVE &= ~BIT_MOVE;
    P_REN_MOVE |= BIT_MOVE;
    P_OUT_MOVE |= BIT_MOVE;
}

bool buttons::buttonMove()
{
    return ((P_IN_MOVE & BIT_MOVE) != BIT_MOVE);
}

void buttons::initDecrement()
{
    P_DIR_DECREMENT &= ~BIT_DECREMENT;
    P_REN_DECREMENT |= BIT_DECREMENT;
    P_OUT_DECREMENT |= BIT_DECREMENT;
}

bool buttons::buttonDecrement()
{
    return ((P_IN_DECREMENT & BIT_DECREMENT) != BIT_DECREMENT);
}

void buttons::initAlarm()
{
    P_DIR_ALARM &= ~BIT_ALARM;
    P_REN_ALARM |= BIT_ALARM;
    P_OUT_ALARM |= BIT_ALARM;
}

bool buttons::buttonAlarm()
{
    return ((P_IN_ALARM & BIT_ALARM) != BIT_ALARM);
}

bool buttons::checkTime()
{
    if (buttonTime())
    {
        delay();
        if (buttonTime())
        {
            return true;
        }
    }
    return false;
}

bool buttons::checkIncrement()
{
    if (buttonIncrement())
    {
        delay();
        if (buttonIncrement())
        {
            return true;
        }
    }
    return false;
}


bool buttons::checkMove()
{
    if (buttonMove())
    {
        delay();
        if (buttonMove())
        {
            return true;
        }
    }
    return false;
}

bool buttons::checkDecrement()
{
    if (buttonDecrement())
    {
        delay();
        if (buttonDecrement())
        {
            return true;
        }
    }
    return false;
}

bool buttons::checkAlarm()
{
    if (buttonAlarm())
    {
        delay();
        if (buttonAlarm())
        {
            return true;
        }
    }
    return false;
}

/// Checks all buttons at once and returns a number in some in pressed
/// It does a double check after a small delay to remove noise
/// \return 0 for no button pushed.
/// \return 1 for increment
/// \return 2 for decrement
/// \return 4 for time change
/// \return 8 for alarm set
/// \return 16 for move to other field
unsigned buttons::getSignalButton()
{
    unsigned signal = 0;
    if(buttonIncrement())
    {
        signal += 1;
    }
    if (buttonDecrement())
    {
        signal += 2;
    }
    if (buttonTime())
    {
        signal += 4;
    }
    if (buttonAlarm())
    {
        signal += 8;
    }
    if (buttonMove())
    {
        signal += 16;
    }

    delay();

    if(signal == 1 && buttonIncrement())
    {
        return signal;
    }
    else if(signal == 2 && buttonDecrement())
    {
        return signal;
    }
    else if(signal == 4 && buttonTime())
    {
        return signal;
    }
    else if(signal == 8 && buttonAlarm())
    {
        return signal;
    }
    else if(signal == 16 && buttonMove())
    {
        return signal;
    }
    return 0; // no signal
}

void buttons::delay()
{
    __delay_cycles( 1000 );     // 1ms
}

void buttons::longDelay()
{
    __delay_cycles( 100000 ); // 100ms
}
