#include "buzzer.h"

buzzer::buzzer()
{
    buzActive = false;
    initBuzzerPin();
}

bool buzzer::checkActive()
{
    if (buzActive)
    {
        return true;
    }
    return false;
}

void buzzer::activeBuz()
{
    buzActive = true;
    initBuzzerPin();
}

void buzzer::deactivateBuz()
{
    buzActive = false;
    clearBuzzerPin();
}

void buzzer::initBuzzerPin()
{
    switch (BUZZER_PORT)
    {
        case 1 :
            P1DIR |= BUZZER_PIN; //output
            P1OUT &= ~BUZZER_PIN; //LOW state
            break;

        case 2  :
            P2DIR |= BUZZER_PIN;
            P2OUT &= ~BUZZER_PIN;
            break;
    }
}

void buzzer::clearBuzzerPin()
{
    switch (BUZZER_PORT)
    {
        case 1 :
            P1DIR &= ~BUZZER_PIN;
            break;

        case 2  :
            P2DIR &= ~BUZZER_PIN;
            break;
    }
}

void buzzer::makeSound()
{
    if (buzActive)
    {
        switch (BUZZER_PORT)
        {
            case 1 :
                P1OUT ^= BUZZER_PIN;
                break;

            case 2  :
                P2OUT ^= BUZZER_PIN;
                break;
        }
    }
}
bool buzzer::getBuzActive()
{
    return buzActive;
}
