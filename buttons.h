#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "msp430g2553.h"

#define P_DIR_TIME      P1DIR
#define P_REN_TIME      P1REN
#define P_OUT_TIME      P1OUT
#define P_IN_TIME       P1IN
#define BIT_TIME        BIT0

#define P_DIR_INCREMENT P1DIR
#define P_REN_INCREMENT P1REN
#define P_OUT_INCREMENT P1OUT
#define P_IN_INCREMENT  P1IN
#define BIT_INCREMENT   BIT1

#define P_DIR_MOVE      P1DIR
#define P_REN_MOVE      P1REN
#define P_OUT_MOVE      P1OUT
#define P_IN_MOVE       P1IN
#define BIT_MOVE        BIT2

#define P_DIR_DECREMENT P1DIR
#define P_REN_DECREMENT P1REN
#define P_OUT_DECREMENT P1OUT
#define P_IN_DECREMENT  P1IN
#define BIT_DECREMENT   BIT3

#define P_DIR_ALARM     P2DIR
#define P_REN_ALARM     P2REN
#define P_OUT_ALARM     P2OUT
#define P_IN_ALARM      P2IN
#define BIT_ALARM       BIT0

class buttons
{
public:
    buttons();
    bool checkTime();
    bool checkIncrement();
    bool checkMove();
    bool checkDecrement();
    bool checkAlarm();
    unsigned getSignalButton();
    static void initMove();

private:
    static void initTime();
    static bool buttonTime();
    static void initIncrement();
    static bool buttonIncrement();
    static bool buttonMove();
    static void initDecrement();
    static bool buttonDecrement();
    static void initAlarm();
    static bool buttonAlarm();

    void delay();
    void longDelay();
};

#endif /* BUTTONS_H_ */
