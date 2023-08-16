#include "lcdInterface.h"

lcdInterface::lcdInterface(timeDate *td)
{
    _td = td;
    initLCD();
    clean_lcd();
}

void lcdInterface::clean_lcd()
{
    _td->updateAll();
    time_to_lcd();
    /*
    setAddr(_x_sec, _y_sec);
    writeStringToLCD(_td->getSecond(), 2);
    setAddr(_x_min, _y_min);
    writeStringToLCD(_td->getMinute(),2 );
    writeCharToLCD(0x3a); //":"
    setAddr(_x_hour, _y_hour);
    writeStringToLCD(_td->getHour(), 2);
    writeCharToLCD(0x3a); //":"

    //nday/month/year
    setAddr(_x_nday,_y_nday);
    writeStringToLCD(_td->getNday(),2);
    writeCharToLCD(0x2f); //"/"
    writeStringToLCD(_td->getMonth(),2);
    writeCharToLCD(0x2f); //"/"
    writeStringToLCD(_td->getYear(),2);
    */
    //setAddr(0, 3);
    //writeStringToLCD("00002233445566", 20);

}

void lcdInterface::time_to_lcd()
{

    setAddr(_x_sec, _y_sec);
    writeStringToLCD(_td->getSecond(), 2);

    if (_td->getUpdateMinute())
    {
        setAddr(_x_min, _y_min);
        writeStringToLCD(_td->getMinute(), 2);
        writeCharToLCD(0x3a); //":"

        if (_td->getUpdateHour())
        {
            setAddr(_x_hour, _y_hour);
            writeStringToLCD(_td->getHour(), 2);
            writeCharToLCD(0x3a); //":"

            // The rest of values are updated daily
            if (_td->getUpdateDay())
            {

                //week
                setAddr(_x_week, _y_week);
                writeCharToLCD(0x57); //"W"
                writeCharToLCD(0x3a); //":"
                writeStringToLCD(_td->getWeek(), 2);

                //week day      
                setAddr(_x_wday, _y_wday);
                writeStringToLCD(_td->getWeekDay(), 9);

                //nday/month/year
                setAddr(_x_nday, _y_nday);
                writeStringToLCD(_td->getNday(), 2);
                writeCharToLCD(0x2f); //"/"
                writeStringToLCD(_td->getMonth(), 2);
                writeCharToLCD(0x2f); //"/"
                writeStringToLCD(_td->getYear(), 2);

                //Battery Level
                setAddr(_x_bat, _y_bat);
                writeCharToLCD(0x42); //"B"
                writeCharToLCD(0x3a); //":"
                writeStringToLCD("3", 2);

            }
        }
    }

    //if updated alarm:

    //alarm 1
    setAddr(_x_a1, _y_a1);
    writeStringToLCD("A", 1);
    setAddr(_x_a1_hour, _y_a1_hour);
    writeStringToLCD("07:00", 5);
    setAddr(_x_a1_days, _y_a1_days);
    writeStringToLCD("0000000", 7);

    //alarm 2
    setAddr(_x_a2, _y_a2);
    writeStringToLCD("A", 1);
    setAddr(_x_a2_hour, _y_a2_hour);
    writeStringToLCD("17:33", 5);
    setAddr(_x_a2_days, _y_a2_days);
    writeStringToLCD("0000000", 7);

    //if updated temperature and humidity

    //humidity
    setAddr(_x_hr, _y_hr);
    writeStringToLCD("HR41%", 5);

    //temperature
    setAddr(_x_temp, _y_temp);
    writeStringToLCD("24.3C", 5);
}


void lcdInterface::change_time()
{

    static unsigned int position = 3;
    while (_b.checkStateButtonTime())
    {
        switch (position)
        {
            case 1 :
                toggle_hour();
                break;
            case 2 :
                toggle_minute();
                break;
            case 3 :
                toggle_nday();
                break;
        }

        if (move_pos())
        {
            position++;
            clean_lcd();

            if (position > 3)
                position = 1;
            else if (position < 1)
                position = 3;
        }

        clean_lcd();
        for (unsigned long i = 5000; i > 0; i--);     // delay
    }
}

void lcdInterface::toggle_hour()
{

    if (_b.checkStateButtonIncrementValue())
        _td->incrementHour();
    else if (_b.checkStateButtonDecrementValue())
        _td->decrementHour();

    setAddr(10, 1);
    writeStringToLCD(_td->getHour(), 2);

    for (unsigned long i = 80000; i > 0; i--);     // delay

    setAddr(10, 1);
    writeCharToLCD(0x5b); //"_"
    writeCharToLCD(0x5b); //"_"

    for (unsigned long i = 20000; i > 0; i--);     // delay
}

void lcdInterface::toggle_minute()
{

    static bool toggle = true;
    setAddr(28, 1);
    if (toggle)
    {
        writeStringToLCD(_td->getMinute(), 2);
        toggle = false;
    } else
    {
        writeCharToLCD(0x5b); //"_"
        writeCharToLCD(0x5b); //"_"
        toggle = true;
    }
    for (unsigned long i = 50000; i > 0; i--);     // delay
}

void lcdInterface::toggle_nday()
{

    static bool toggle = true;
    setAddr(10, 2);
    if (toggle)
    {
        writeStringToLCD(_td->getNday(), 2);
        toggle = false;
    } else
    {
        writeCharToLCD(0x5b); //"_"
        writeCharToLCD(0x5b); //"_"
        toggle = true;
    }
    for (unsigned long i = 50000; i > 0; i--);     // delay
}

bool lcdInterface::move_pos()
{
    if (_b.checkStateButtonMovePos())
        return true;
    return false;
}
