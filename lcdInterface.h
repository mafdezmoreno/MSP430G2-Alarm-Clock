#ifndef LCDINTERFACE_H_
#define LCDINTERFACE_H_

#include "buttons.h"
#include "lcd5110.h"
#include "timeDate.h"
#include "alarm.h"
#include "stdio.h"
#include "string.h"
#include "dht.h"

class lcdInterface
{
public:
    lcdInterface (timeDate *inData, alarm *al1, alarm *al2, buttons *but, dht *d);
    ~lcdInterface();
    void cleanLcd ();
    void timeToLcd ();
    void dateToLcd ();
    void batteryLevelToLcd ();
    void alarm1ToLcd (const unsigned * currentWeekDay);
    void alarm2ToLcd (const unsigned * currentWeekDay);
    void dhtToLcd ();
    void printAll ();
    void changeTime ();
    void toggleYear ();
    void toggleMonth ();
    void toggleWeek ();
    void toggleMonthDay ();
    void toggleWeekDay ();
    void toggleHour ();
    void toggleMinute ();

    void changeAlarm();
    void toggleDayAlarm1(unsigned dayToToggle);
    void toggleDayAlarm2(unsigned dayToToggle);
    void toggleHourAlarm1(unsigned dayToToggle);
    void toggleMinAlarm1(unsigned dayToToggle);
    void toggleHourAlarm2(unsigned dayToToggle);
    void toggleMinAlarm2(unsigned dayToToggle);
private:
    timeDate * timeData;
    buttons * pButtons;
    alarm * pAlarm1;
    alarm * pAlarm2;
    dht * pDht;

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
    static const unsigned xMonth = xNday + wide * 3;
    static const unsigned yMonth = 2;
    static const unsigned xYear = xMonth + wide * 3;
    static const unsigned yYear= 2;

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
