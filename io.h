#ifndef IO_H_
#define IO_H_

#include "msp430g2553.h"

#define DISPLAY_LED_PORT 2
#define DISPLAY_LED_BIT BIT5

#define LED_PORT 2
#define LED_BIT BIT4

void enableDisplayLed();
void disableDisplayLed();
void displayLedOff();
void displayLedOn();
void enableLed();
void disableLed();
void ledOff();
void ledOn();
void toggleLed();

#endif /* IO_H_ */
