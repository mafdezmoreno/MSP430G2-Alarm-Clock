#include "lcdInterface.h"

lcdInterface::lcdInterface(timeDate *inData)
{
    data = inData;
    initLcd();
    cleanLcd();
}

void lcdInterface::cleanLcd()
{
    data->callUpdateTime();
    data->callUpdateDate();
    printAll();
}

void lcdInterface::timeToLcd()
{
    if (!data->checkUpdatedTime())
    {
        setAddr(xMin, yMin);
        writeStringToLcd(data->getMinute(), 2);
        setAddr(xMin + wide * 2, yMin);
        writeCharToLcd(0x3a); //":"
        setAddr(xHour, yHour);
        writeStringToLcd(data->getHour(), 2);
        setAddr(xHour + wide * 2, yHour);
        writeCharToLcd(0x3a); //":"
        data->setTimeOnLcdUpdated();
    }
    setAddr(xSec, ySec);
    writeStringToLcd(data->getSecond(), 2);
}

void lcdInterface::dateToLcd()
{
    if (!data->checkUpdatedDate())
    {
        //week year
        setAddr(xWeek, yWeek);
        writeCharToLcd(0x57); //"W"
        writeCharToLcd(0x3a); //":"
        setAddr(xWeek + wide * 2, yWeek);
        writeStringToLcd(data->getWeek(), 2);
        //week day
        setAddr(xWday, yWday);
        writeStringToLcd(data->getWeekDay(), 3);
        data->setDateOnLcdUpdate();
        //nday/month/year
        setAddr(xNday, yNday);
        writeStringToLcd(data->getMonthDay(), 2);
        setAddr(xNday + wide * 2, yNday);
        writeCharToLcd(0x2f); //"/"
        setAddr(xMonth, yMonth);
        writeStringToLcd(data->getMonth(), 2);
        setAddr(xMonth + wide * 2, yMonth);
        writeCharToLcd(0x2f); //"/"
        setAddr(xYear, yYear);
        writeStringToLcd(data->getYear(), 2);
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
    while (but.checkStateButtonTime())
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

        if (but.checkStateButtonMovePos())
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
        if (but.checkStateButtonIncrementValue())
            data->incrementWeek();
        else if (but.checkStateButtonDecrementValue())
            data->decrementWeek();
        toggle = false;
    } else
    {
        setAddr(xWeek + wide * 2, yWeek);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        data->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleWeekDay()
{
    static bool toggle = true;
    if (toggle)
    {
        if (but.checkStateButtonIncrementValue())
            data->incrementWeekDay();
        else if (but.checkStateButtonDecrementValue())
            data->decrementWeekDay();
        toggle = false;
    } else
    {
        setAddr(xWday, yWday);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        data->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleMonthDay()
{
    static bool toggle = true;
    if (toggle)
    {
        if (but.checkStateButtonIncrementValue())
            data->incrementMonthDay();
        else if (but.checkStateButtonDecrementValue())
            data->decrementMonthDay();
        toggle = false;
    } else
    {
        setAddr(xNday, yNday);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        data->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleMonth()
{
    static bool toggle = true;
    if (toggle)
    {
        if (but.checkStateButtonIncrementValue())
            data->incrementMonth();
        else if (but.checkStateButtonDecrementValue())
            data->decrementMonth();
        toggle = false;
    } else
    {
        setAddr(xMonth, yMonth);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        data->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleYear()
{
    static bool toggle = true;
    if (toggle)
    {
        if (but.checkStateButtonIncrementValue())
            data->incrementYear();
        else if (but.checkStateButtonDecrementValue())
            data->decrementYear();
        toggle = false;
    } else
    {
        setAddr(xYear, yYear);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        data->callUpdateDate();
    }
    delay();
    dateToLcd();
}

void lcdInterface::toggleHour()
{
    static bool toggle = true;
    if (toggle)
    {
        if (but.checkStateButtonIncrementValue())
            data->incrementHour();
        else if (but.checkStateButtonDecrementValue())
            data->decrementHour();
        toggle = false;
    } else
    {
        setAddr(xHour, yHour);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        data->callUpdateTime();
    }
    delay();
    timeToLcd();
}

void lcdInterface::toggleMinute()
{

    static bool toggle = true;
    if (toggle)
    {
        if (but.checkStateButtonIncrementValue())
            data->incrementMinute();
        else if (but.checkStateButtonDecrementValue())
            data->decrementMinute();
        toggle = false;
    } else
    {
        setAddr(xMin, yMin);
        writeCharToLcd(0x5f); //"_"
        writeCharToLcd(0x5f); //"_"
        toggle = true;
        data->callUpdateTime();
    }
    delay();
    timeToLcd();
}

void lcdInterface::delay()
{   //200 ms delay
    __delay_cycles(200000);
}
void lcdInterface::longDelay()
{   //400 ms delay
    __delay_cycles(400000);
}
