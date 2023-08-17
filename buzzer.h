
#ifndef BUZZER_H_
#define BUZZER_H_

#include "msp430g2452.h"
#define BUZZER_PORT 2
#define BUZZER_PIN BIT1

class buzzer
{
public:
    buzzer();
    int checkActive();
    void activeBuz();
    void deactivateBuz();
    void makeSound();
    bool getBuzActive();

private:
    bool buzActive;
    void initBuzzerPin();
    void clearBuzzerPin();

};

#endif /* BUZZER_H_ */
