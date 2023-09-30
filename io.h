#ifndef IO_H_
#define IO_H_

#include "msp430g2553.h"

#define DISPLAY_LED_PORT 2
#define DISPLAY_LED_BIT BIT5

#define LED_PORT 2
#define LED_BIT BIT4

void ledOff();
void ledOn();
void toggleLed();
void enableLed();

class lcdLight
{
public:
    lcdLight();
    void off();
    void on();
    void countDown();
    void resetCounter();
private:
    unsigned counter;
    void enable();
    void disable();
};

#endif /* IO_H_ */
