#include "lcdInterface.h"

lcdInterface::lcdInterface (timeDate *inData, alarm *al1, buttons * but)
{
    pButtons = but;
    timeData = inData;
    pAlarm1 = al1;
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
    const char *pSecond;
    pSecond = timeData->getSecond();

    if (!timeData->checkUpdatedTime())
    {
        const char *pHour;
        const char *pMin;
        char tempStr[7];

        pHour = timeData -> getHour();
        pMin = timeData->getMinute();

        strcpy(tempStr, pHour);
        strcat(tempStr, ":");
        strcat(tempStr, pMin);
        strcat(tempStr, ":");

        setAddr(xHour, yHour);

        writeStringToLcd(tempStr, 6);
        timeData->setTimeOnLcdUpdated();

        delete[] pMin;
        delete[] pHour;
    }
    setAddr(xSec, ySec);
    writeStringToLcd(pSecond, 2);
    delete[] pSecond;
}

void lcdInterface::dateToLcd()
{
    if (!timeData->checkUpdatedDate())
    {
        const char *pWeek;
        const char *pDay;
        const char *pMonth;
        const char *pYear;
        char tempWeek[5];
        char tempDate[9];

        pWeek = timeData ->getWeek();
        pDay = timeData -> getMonthDay();
        pMonth = timeData -> getMonth();
        pYear = timeData -> getYear();

        strcpy(tempWeek, "W:");
        strcat(tempWeek, pWeek);
        setAddr(xWeek, yWeek);
        writeStringToLcd(tempWeek, 4);

        setAddr(xWday, yWday);
        writeStringToLcd(timeData->getWeekDay(), 3);
        timeData->setDateOnLcdUpdate();

        strcpy(tempDate, pDay);
        strcat(tempDate, "/");
        strcat(tempDate, pMonth);
        strcat(tempDate, "/");
        strcat(tempDate, pYear);
        setAddr(xNday, yNday);
        writeStringToLcd(tempDate, 11);

        delete[] pWeek;
        delete[] pDay;
        delete[] pMonth;
        delete[] pYear;
    }
}

void lcdInterface::batteryLevelToLcd()
{
    char temp[4];
    const char * pBat;

    strcpy(temp, "B:");
    strcat(temp, "2");     // TODO: Implement battery level read
    setAddr(xBat, yBat);
    writeStringToLcd(temp,3);
}

void lcdInterface::alarm1ToLcd(const unsigned * currentWeekDay)
{
    const char * pHour;
    const char * pMin;
    const char * pAlarms;
    char temp[6];

    setAddr(xA1, yA1);
    writeStringToLcd("A", 1);

    setAddr(xA1Hour, yA1Hour);
    pHour = pAlarm1->hourToString(currentWeekDay);
    strcpy(temp, pHour);
    strcat(temp, ":");
    pMin = pAlarm1->minuteToString(currentWeekDay);
    strcat(temp, pMin);
    writeStringToLcd(temp, 5);

    setAddr(xA1Days, yA1Days);
    pAlarms = pAlarm1->weekAlarmsToString();
    writeStringToLcd(pAlarms, 7);

    delete[] pHour;
    delete[] pMin;
    delete[] pAlarms;
}

void lcdInterface::alarm2ToLcd(const unsigned * currentWeekDay)
{
    const char * pHour;
    const char * pMin;
    const char * pAlarms;
    char temp[6];

    setAddr(xA2, yA2);
    writeStringToLcd("A", 1);

    setAddr(xA2Hour, yA2Hour);
    pHour = pAlarm2->hourToString(currentWeekDay);
    strcpy(temp, pHour);
    strcat(temp, ":");
    pMin = pAlarm2->minuteToString(currentWeekDay);
    strcat(temp, pMin);
    writeStringToLcd(temp, 5);

    setAddr(xA2Days, yA2Days);
    pAlarms = pAlarm2->weekAlarmsToString();
    writeStringToLcd(pAlarms, 7);

    delete[] pHour;
    delete[] pMin;
    delete[] pAlarms;
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
    alarm1ToLcd(timeData->getCurrentWeekDay());
    alarm2ToLcd(timeData->getCurrentWeekDay());
    batteryLevelToLcd();
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
    }
    timeData->callUpdateDate();
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
    }
    timeData->callUpdateDate();
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
    }
    timeData->callUpdateDate();
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
    }
    timeData->callUpdateDate();
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
    }
    timeData->callUpdateDate();
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

    static unsigned positionDayAlarm = 0;
    static unsigned positionHourMin = 0;

    while (pButtons->checkAlarm())
    {
        if (positionDayAlarm < 7)
        {
            if (positionHourMin == 0)
            {
                toggleHourAlarm1(positionDayAlarm);
            }
            else if (positionHourMin == 1)
            {
                toggleMinAlarm1(positionDayAlarm);
            }
            else
            {
                toggleDayAlarm1(positionDayAlarm);
            }
            delay();
            alarm1ToLcd(&positionDayAlarm);
        }
        else{
            unsigned tempDay = positionDayAlarm - 7;
            if (positionHourMin == 0)
            {
                toggleHourAlarm2(tempDay);
            }
            else if (positionHourMin == 1)
            {
                toggleMinAlarm2(tempDay);
            }
            else
            {
                toggleDayAlarm2(tempDay);
            }
            delay();
            alarm2ToLcd(&tempDay);
        }

        if (pButtons->checkMove())
        {
            positionDayAlarm++;
            if (positionDayAlarm > 13)
                positionDayAlarm = 0;
            longDelay();
        }

        if (pButtons->checkTime())
        {
            positionHourMin++;
            if (positionHourMin > 2)
                positionHourMin = 0;
            longDelay();
        }
        delay();
    }
}

///
/// \param dayToToggle Day of the week to activate/deactivate alarm. Monday = 0

void lcdInterface::toggleDayAlarm1(unsigned dayToToggle)
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement() ||
           pButtons->checkDecrement())
            pAlarm1->toggleActivateDeactivate(dayToToggle);
        toggle = false;
    } else
    {
        setAddr(xA1Days + wide * dayToToggle, yA1Days);
        writeCharToLcd(0x5f); //"_"
        toggle = true;
    }
}

void lcdInterface::toggleDayAlarm2(unsigned dayToToggle)
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement() ||
            pButtons->checkDecrement())
            pAlarm2->toggleActivateDeactivate(dayToToggle);
        toggle = false;
    } else
    {
        setAddr(xA2Days + wide * dayToToggle, yA2Days);
        writeCharToLcd(0x5f); //"_"
        toggle = true;
    }
}

void lcdInterface::toggleHourAlarm1(unsigned dayToToggle)
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
        {
            pAlarm1->incrementHour(&dayToToggle);
        }
        else if (pButtons -> checkDecrement())
        {
            pAlarm1->decrementHour(&dayToToggle);
        }

        toggle = false;
    }
    else
    {
        setAddr(xA1Hour, yA1Hour);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        setAddr(xA1Days + wide * dayToToggle, yA1Days);
        writeCharToLcd(0x5f); //"_"
        toggle = true;
    }
}

void lcdInterface::toggleHourAlarm2(unsigned dayToToggle)
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
        {
            pAlarm2->incrementHour(&dayToToggle);
        }
        else if (pButtons -> checkDecrement())
        {
            pAlarm2->decrementHour(&dayToToggle);
        }

        toggle = false;
    }
    else
    {
        setAddr(xA2Hour, yA2Hour);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        setAddr(xA2Days + wide * dayToToggle, yA2Days);
        writeCharToLcd(0x5f); //"_"
        toggle = true;
    }
}

void lcdInterface::toggleMinAlarm1(unsigned dayToToggle)
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
        {
            pAlarm1->incrementMin(&dayToToggle);
        }
        else if (pButtons -> checkDecrement())
        {
            pAlarm1->decrementMin(&dayToToggle);
        }

        toggle = false;
    }
    else
    {
        setAddr(xA1Hour + wide * 3, yA1Hour);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        setAddr(xA1Days + wide * dayToToggle, yA1Days);
        writeCharToLcd(0x5f); //"_"
        toggle = true;
    }
}

void lcdInterface::toggleMinAlarm2(unsigned dayToToggle)
{
    static bool toggle = true;
    if (toggle)
    {
        if (pButtons->checkIncrement())
        {
            pAlarm2->incrementMin(&dayToToggle);
        }
        else if (pButtons -> checkDecrement())
        {
            pAlarm2->decrementMin(&dayToToggle);
        }

        toggle = false;
    }
    else
    {
        setAddr(xA2Hour + wide * 3, yA2Hour);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        setAddr(xA2Days + wide * dayToToggle, yA2Days);
        writeCharToLcd(0x5f); //"_"
        toggle = true;
    }
}

void lcdInterface::delay()
{   //200 ms delay
    __delay_cycles(200000);
}
void lcdInterface::longDelay()
{   //400 ms delay
    __delay_cycles(400000);
}


