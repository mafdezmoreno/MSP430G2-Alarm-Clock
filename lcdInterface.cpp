#include "lcdInterface.h"

lcdInterface::lcdInterface(timeDate *inData)
{
    data = inData;
    initLCD();
    cleanLcd();
}

void lcdInterface::cleanLcd()
{
    data->updateAll();
    timeToLcd();
}

void lcdInterface::timeToLcd()
{
    //    if(!outdated){
    //        return;
    //    }
    setAddr(xSec, ySec);
    writeStringToLCD(data->getSecond(), 2);

    if (data->getUpdateMinute())
    {
        setAddr(xMin, yMin);
        writeStringToLCD(data->getMinute(), 2);
        writeCharToLCD(0x3a); //":"

        if (data->getUpdateHour())
        {
            setAddr(xHour, yHour);
            writeStringToLCD(data->getHour(), 2);
            writeCharToLCD(0x3a); //":"

            // The rest of values are updated daily
            if (data->getUpdateDay())
            {

                //week
                setAddr(xWeek, yWeek);
                writeCharToLCD(0x57); //"W"
                writeCharToLCD(0x3a); //":"
                writeStringToLCD(data->getWeek(), 2);

                //week day      
                setAddr(xWday, yWday);
                writeStringToLCD(data->getWeekDay(), 9);

                //nday/month/year
                setAddr(xNday, yNday);
                writeStringToLCD(data->getNday(), 2);
                writeCharToLCD(0x2f); //"/"
                writeStringToLCD(data->getMonth(), 2);
                writeCharToLCD(0x2f); //"/"
                writeStringToLCD(data->getYear(), 2);

                //Battery Level
                setAddr(xBat, yBat);
                writeCharToLCD(0x42); //"B"
                writeCharToLCD(0x3a); //":"
                writeStringToLCD("3", 2);

            }
        }
    }

    //if updated alarm:

    //alarm 1
    setAddr(xA1, yA1);
    writeStringToLCD("A", 1);
    setAddr(xA1Hour, yA1Hour);
    writeStringToLCD("07:00", 5);
    setAddr(xA1Days, yA1Days);
    writeStringToLCD("0000000", 7);

    //alarm 2
    setAddr(xA2, yA2);
    writeStringToLCD("A", 1);
    setAddr(xA2Hour, yA2Hour);
    writeStringToLCD("17:33", 5);
    setAddr(xA2Days, yA2Days);
    writeStringToLCD("0000000", 7);

    //if updated temperature and humidity

    //humidity
    setAddr(xHr, yHr);
    writeStringToLCD("HR41%", 5);

    //temperature
    setAddr(xTemp, yTemp);
    writeStringToLCD("24.3C", 5);

    outdated = false;
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
                toggleNday();
                break;
        }

        if (movePos())
        {
            position++;
            cleanLcd();

            if (position > 3)
                position = 1;
            else if (position < 1)
                position = 3;
        }

        cleanLcd();
        for (unsigned long i = 5000; i > 0; i--);     // delay
    }
}

void lcdInterface::toggleHour()
{

    if (but.checkStateButtonIncrementValue())
        data->incrementHour();
    else if (but.checkStateButtonDecrementValue())
        data->decrementHour();

    setAddr(10, 1);
    writeStringToLCD(data->getHour(), 2);

    for (unsigned long i = 80000; i > 0; i--);     // delay

    setAddr(10, 1);
    writeCharToLCD(0x5b); //"_"
    writeCharToLCD(0x5b); //"_"

    for (unsigned long i = 20000; i > 0; i--);     // delay
}

void lcdInterface::toggleMinute()
{

    static bool toggle = true;
    setAddr(28, 1);
    if (toggle)
    {
        writeStringToLCD(data->getMinute(), 2);
        toggle = false;
    } else
    {
        writeCharToLCD(0x5b); //"_"
        writeCharToLCD(0x5b); //"_"
        toggle = true;
    }
    for (unsigned long i = 50000; i > 0; i--);     // delay
}

void lcdInterface::toggleNday()
{

    static bool toggle = true;
    setAddr(10, 2);
    if (toggle)
    {
        writeStringToLCD(data->getNday(), 2);
        toggle = false;
    } else
    {
        writeCharToLCD(0x5b); //"_"
        writeCharToLCD(0x5b); //"_"
        toggle = true;
    }
    for (unsigned long i = 50000; i > 0; i--);     // delay
}

bool lcdInterface::movePos()
{
    if (but.checkStateButtonMovePos())
        return true;
    return false;
}

void lcdInterface::callUpdate()
{
    outdated = true;
}
