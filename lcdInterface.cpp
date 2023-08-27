#include "lcdInterface.h"

lcdInterface::lcdInterface (timeDate *inData, alarm *al, buttons * but)
{
    pButtons = but;
    timeData = inData;
    initLcd();
    cleanLcd();
    // Todo create an initialize alarm related variables
}

void lcdInterface::cleanLcd()
{
    timeData->callUpdateTime();
    timeData->callUpdateDate();
    printAll();
}

void lcdInterface::timeToLcd()
{
    if (!timeData->checkUpdatedTime())
    {
        setAddr(xMin, yMin);
        writeStringToLcd(timeData->getMinute(), 2);
        setAddr(xMin + wide * 2, yMin);
        writeCharToLcd(0x3a); //":"
        setAddr(xHour, yHour);
        writeStringToLcd(timeData->getHour(), 2);
        setAddr(xHour + wide * 2, yHour);
        writeCharToLcd(0x3a); //":"
        timeData->setTimeOnLcdUpdated();
    }
    setAddr(xSec, ySec);
    writeStringToLcd(timeData->getSecond(), 2);
}

void lcdInterface::dateToLcd()
{
    if (!timeData->checkUpdatedDate())
    {
        //week year
        setAddr(xWeek, yWeek);
        writeCharToLcd(0x57); //"W"
        writeCharToLcd(0x3a); //":"
        setAddr(xWeek + wide * 2, yWeek);
        writeStringToLcd(timeData->getWeek(), 2);
        //week day
        setAddr(xWday, yWday);
        writeStringToLcd(timeData->getWeekDay(), 3);
        timeData->setDateOnLcdUpdate();
        //nday/month/year
        setAddr(xNday, yNday);
        writeStringToLcd(timeData->getMonthDay(), 2);
        setAddr(xNday + wide * 2, yNday);
        writeCharToLcd(0x2f); //"/"
        setAddr(xMonth, yMonth);
        writeStringToLcd(timeData->getMonth(), 2);
        setAddr(xMonth + wide * 2, yMonth);
        writeCharToLcd(0x2f); //"/"
        setAddr(xYear, yYear);
        writeStringToLcd(timeData->getYear(), 2);
    }
}

void lcdInterface::batteryLevelToLcd()
{
    //Battery Level
    setAddr(xBat, yBat);
    writeCharToLcd(0x42); //"B"
    writeCharToLcd(0x3a); //":"
    writeStringToLcd("3", 2);
}

void lcdInterface::alarm1ToLcd()
{
    //alarm 1
    setAddr(xA1, yA1);
    writeStringToLcd("A", 1);
    setAddr(xA1Hour, yA1Hour);
    writeStringToLcd("07:00", 5);
    setAddr(xA1Days, yA1Days);
    writeStringToLcd("0000000", 7);
}

void lcdInterface::alarm2ToLcd()
{
    //alarm 2
    setAddr(xA2, yA2);
    writeStringToLcd("A", 1);
    setAddr(xA2Hour, yA2Hour);
    writeStringToLcd("17:33", 5);
    setAddr(xA2Days, yA2Days);
    writeStringToLcd("0000000", 7);
}

void lcdInterface::dhtToLcd()
{
    // Todo: Implement updtedDht on DHT new class
    //humidity
    setAddr(xHr, yHr);
    writeStringToLcd("HR41%", 5);
    //temperature
    setAddr(xTemp, yTemp);
    writeStringToLcd("24.3C", 5);
    //outdated = false;
}

void lcdInterface::printAll()
{
    timeToLcd();
    dateToLcd();
    alarm1ToLcd();
    alarm2ToLcd();
    batteryLevelToLcd();
    alarm1ToLcd();
    alarm2ToLcd();
    dhtToLcd();
}

void lcdInterface::changeTime()
{
    static unsigned int position = 1;
    while (pButtons->checkTime())
    {
        switch (position)
        {
            case 1 :
                toggleWeek();
                break;
            case 2 :
                toggleWeekDay();
                break;
            case 3 :
                toggleHour();
                break;
            case 4 :
                toggleMinute();
                break;
            case 5 :
                toggleMonthDay();
                break;
            case 6 :
                toggleMonth();
                break;
            case 7 :
                toggleYear();
                break;
        }

        if (pButtons->checkMove())
        {
            position++;
            if (position > 7)
                position = 1;
            else if (position < 1)
                position = 7;
            longDelay();
        }
        delay();
    }
}

void lcdInterface::toggleWeek()
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
            timeData->incrementWeek();
        else if (pButtons->checkDecrement())
            timeData->decrementWeek();
        toggle = false;
    } else
    {
        setAddr(xWeek + wide * 2, yWeek);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        timeData->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleWeekDay()
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
            timeData->incrementWeekDay();
        else if (pButtons->checkDecrement())
            timeData->decrementWeekDay();
        toggle = false;
    } else
    {
        setAddr(xWday, yWday);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        timeData->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleMonthDay()
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
            timeData->incrementMonthDay();
        else if (pButtons->checkDecrement())
            timeData->decrementMonthDay();
        toggle = false;
    } else
    {
        setAddr(xNday, yNday);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        timeData->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleMonth()
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
            timeData->incrementMonth();
        else if (pButtons->checkDecrement())
            timeData->decrementMonth();
        toggle = false;
    } else
    {
        setAddr(xMonth, yMonth);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        timeData->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleYear()
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
            timeData->incrementYear();
        else if (pButtons->checkDecrement())
            timeData->decrementYear();
        toggle = false;
    } else
    {
        setAddr(xYear, yYear);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        timeData->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleHour()
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
            timeData->incrementHour();
        else if (pButtons->checkDecrement())
            timeData->decrementHour();
        toggle = false;
    } else
    {
        setAddr(xHour, yHour);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        timeData->callUpdateTime();
    }
    delay();
    timeToLcd();
}

void lcdInterface::toggleMinute()
{

    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
            timeData->incrementMinute();
        else if (pButtons->checkDecrement())
            timeData->decrementMinute();
        toggle = false;
    } else
    {
        setAddr(xMin, yMin);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        timeData->callUpdateTime();
    }
    delay();
    timeToLcd();
}

void lcdInterface::changeAlarm()
{
    // Control-Sequence to change alarm
    // Button 1 (checkStateButtonMovePos()) long push to activate change mode.
    // Button 2 to move between fields (days of week)
    // Button 3 to increment alarm hour (of current day)
    // Button 3 to increment alarm min (of current day)
    // Button 2 long push to set alarm (of current day) and break loop

    static unsigned int position = 1;
    while (pButtons->checkMove()) // Inverted button with change time
    {
        switch (position)
        {
            case 1 :
                toggleAlarm1Monday();
                break;
            case 2 :
                toggleAlarm1Tuesday();
                break;
            /*
            case 3 :
                toggleAlarm1Wednesday();
                break;
            case 4 :
                toggleAlarm1Tuersday();
                break;
            case 5 :
                toggleAlarm1Friday();
                break;
            case 6 :
                toggleAlarm1Saturday();
                break;
            case 7 :
                toggleAlarm1Sunday();
                break;
            case 8 :
                toggleAlarm2Monday();
                break;
            case 9 :
                toggleAlarm2Tuesday();
                break;
            case 10 :
                toggleAlarm2Wednesday();
                break;
            case 11:
                toggleAlarm2Tuersday();
                break;
            case 12 :
                toggleAlarm2Friday();
                break;
            case 13:
                toggleAlarm2Saturday();
                break;
            case 14:
                toggleAlarm2Sunday();
                break;
            */
        }

        if (pButtons->checkTime())
        {
            position++;
            if (position > 14)
                position = 1;
            else if (position < 1)
                position = 7;
            longDelay();
        }
        delay();
    }
}

void lcdInterface::toggleAlarm1Monday()
{

}

void lcdInterface::toggleAlarm1Tuesday()
{

}

void lcdInterface::delay()
{   //200 ms delay
    __delay_cycles(200000);
}
void lcdInterface::longDelay()
{   //400 ms delay
    __delay_cycles(400000);
}


