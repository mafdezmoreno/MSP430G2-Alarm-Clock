#include "buzzer.h"

buzzer::buzzer()
{
    buzActive = false;
    initBuzzerPin();
}

int buzzer::checkActive()
{
    if (buzActive)
    {
        return 1;
    }
    return 0;
}

void buzzer::activeBuz()
{
    buzActive = 1;
    initBuzzerPin();
}

void buzzer::deactivateBuz()
{
    buzActive = 0;
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
