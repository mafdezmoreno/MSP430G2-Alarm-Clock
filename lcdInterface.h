#ifndef LCDINTERFACE_H_
#define LCDINTERFACE_H_

#include "buttons.h"
#include "lcd5110.h"
#include "timeDate.h"

class lcdInterface
{
public:
    lcdInterface (timeDate *inData);
    void cleanLcd ();
    void timeToLcd ();
    void dateToLcd ();
    void batteryLevelToLcd ();
    void alarm1ToLcd ();
    void alarm2ToLcd();
    void dhtToLcd ();
    void printAll ();
    void changeTime ();
    void toogleYear ();
    void toogleMonth ();
    void toogleWeek ();
    void toggleMonthDay ();
    void toggleWeekDay ();
    void toggleHour ();
    void toggleMinute ();
    bool movePos ();

private:
    timeDate *data;
    buttons but;

    static const unsigned wide = 6;

    // positions on LCD screen
    // row 0
    static const unsigned xWeek = 0;
    static const unsigned yWeek = 0;

    static const unsigned xWday = wide * 6;
    static const unsigned yWday = 0;

    static const unsigned xBat = wide * 11;
    static const unsigned yBat = 0;

    // row 1
    static const unsigned xHour = 18;
    static const unsigned yHour = 1;

    static const unsigned xMin = xHour + wide * 3;
    static const unsigned yMin = 1;

    static const unsigned xSec = xMin + wide * 3;
    static const unsigned ySec = 1;

    // row 2
    static const unsigned xNday = 18;
    static const unsigned yNday = 2;

    // row 3
    static const unsigned xA1 = 0;
    static const unsigned yA1 = 3;
    static const unsigned xA1Hour = wide + wide / 2;
    static const unsigned yA1Hour = 3;
    static const unsigned xA1Days = wide * 7;
    static const unsigned yA1Days = 3;

    // row 4
    static const unsigned xA2 = 0;
    static const unsigned yA2 = 4;
    static const unsigned xA2Hour = wide + wide / 2;
    static const unsigned yA2Hour = 4;
    static const unsigned xA2Days = wide * 7;
    static const unsigned yA2Days = 4;

    // row 5
    static const unsigned xHr = wide;
    static const unsigned yHr = 5;
    static const unsigned xTemp = wide * 8;
    static const unsigned yTemp = 5;

    void delay();
    void longDelay();
};

#endif /* LCDINTERFACE_H_ */
