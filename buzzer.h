
#ifndef BUZZER_H_
#define BUZZER_H_

#include "msp430g2452.h"
#include "clockTimer.h"
#define BUZZER_PORT 2
#define BUZZER_PIN BIT1

class buzzer
{
public:
    buzzer(clockTimer * cT);
    bool checkActive();
    void activeBuz();
    void deactivateBuz();
    void makeSound();
    bool getBuzActive();

private:
    clockTimer * pCt;
    bool buzActive;
    void initBuzzerPin();
    void clearBuzzerPin();

};

#endif /* BUZZER_H_ */
