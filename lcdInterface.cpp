#include "lcdInterface.h"

lcdInterface::lcdInterface(timeDate *inData)
{
    data = inData;
    initLCD();
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
    setAddr(xSec, ySec);
    writeStringToLCD(data->getSecond(), 2);

    if (!data->checkUpdatedTime())
    {
        setAddr(xMin, yMin);
        writeStringToLCD(data->getMinute(), 2);
        writeCharToLCD(0x3a); //":"
        setAddr(xHour, yHour);
        writeStringToLCD(data->getHour(), 2);
        writeCharToLCD(0x3a); //":"
        data->setTimeOnLcdUpdated();
    }
}

void lcdInterface::dateToLcd()
{
    if (!data->checkUpdatedDate())
    {
        //nday/month/year
        setAddr(xNday, yNday);
        writeStringToLCD(data->getMonthDay(), 2);
        writeCharToLCD(0x2f); //"/"
        writeStringToLCD(data->getMonth(), 2);
        writeCharToLCD(0x2f); //"/"
        writeStringToLCD(data->getYear(), 2);
        //week year
        setAddr(xWeek, yWeek);
        writeCharToLCD(0x57); //"W"
        writeCharToLCD(0x3a); //":"
        writeStringToLCD(data->getWeek(), 2);
        //week day
        setAddr(xWday, yWday);
        writeStringToLCD(data->getWeekDay(), 3);
        data->setDateOnLcdUpdate();
    }
}

void lcdInterface::batteryLevelToLcd()
{
    //Battery Level
    setAddr(xBat, yBat);
    writeCharToLCD(0x42); //"B"
    writeCharToLCD(0x3a); //":"
    writeStringToLCD("3", 2);
}

void lcdInterface::alarm1ToLcd()
{
    //alarm 1
    setAddr(xA1, yA1);
    writeStringToLCD("A", 1);
    setAddr(xA1Hour, yA1Hour);
    writeStringToLCD("07:00", 5);
    setAddr(xA1Days, yA1Days);
    writeStringToLCD("0000000", 7);
}

void lcdInterface::alarm2ToLcd()
{
    //alarm 2
    setAddr(xA2, yA2);
    writeStringToLCD("A", 1);
    setAddr(xA2Hour, yA2Hour);
    writeStringToLCD("17:33", 5);
    setAddr(xA2Days, yA2Days);
    writeStringToLCD("0000000", 7);
}

void lcdInterface::dhtToLcd()
{
    // Todo: Implement updtedDht on DHT new class
    //humidity
    setAddr(xHr, yHr);
    writeStringToLCD("HR41%", 5);
    //temperature
    setAddr(xTemp, yTemp);
    writeStringToLCD("24.3C", 5);
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
    static unsigned int position = 3;
    while (but.checkStateButtonTime())
    {
        switch (position)
        {
            case 1 :
                toggleHour();
                break;
            case 2 :
                toggleMinute();
                break;
            case 3 :
                toggleMonthDay();
                break;
        }

        if (but.checkStateButtonMovePos())
        {
            position++;
            if (position > 3)
                position = 1;
            else if (position < 1)
                position = 3;
        }
        delay();
    }
    //printAll();
//    if (updatedDate)
//    {   // To remove "_" lines
//        data->callUpdateDate();
//        delay();
//        dateToLcd();
//        delay();
//    }
}

void lcdInterface::toggleWeekDay()
{

    static bool toggle = true;
    setAddr(xWday, yWday);

    if (but.checkStateButtonIncrementValue())
        data->incrementWeekDay();
    else if (but.checkStateButtonDecrementValue())
        data->decrementWeekDay();

    if (toggle)
    {
        writeStringToLCD(data->getWeekDay(), 3);
        toggle = false;
    } else
    {
        writeCharToLCD(0x5f); //"_"
        writeCharToLCD(0x5f); //"_"
        writeCharToLCD(0x5f); //"_"
        toggle = true;
    }
    delay();
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
        delay();
        dateToLcd();
        toggle = false;
    } else
    {
        setAddr(xNday, yNday);
        writeCharToLCD(0x5f); //"_"
        writeCharToLCD(0x5f); //"_"
        toggle = true;
        data->callUpdateDate();
    }
    longDelay();
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
        delay();
        //writeStringToLCD(data->getHour(), 2);
        toggle = false;
    } else
    {
        setAddr(xHour, yHour);
        writeCharToLCD(0x5f); //"_"
        writeCharToLCD(0x5f); //"_"
        toggle = true;
        data->callUpdateTime();
    }
    delay();
}

void lcdInterface::toggleMinute()
{

    static bool toggle = true;
    setAddr(xMin, yMin);
    if (toggle)
    {
        writeStringToLCD(data->getMinute(), 2);
        toggle = false;
    } else
    {
        writeCharToLCD(0x5f); //"_"
        writeCharToLCD(0x5f); //"_"
        toggle = true;
    }
    delay();
}

void lcdInterface::delay()
{   //200 ms delay
    __delay_cycles(200000);
}
void lcdInterface::longDelay()
{   //400 ms delay
    __delay_cycles(400000);
}
