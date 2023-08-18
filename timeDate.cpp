#include "timeDate.h"

timeDate::timeDate()
{
    currentTime.second = 55;
    currentTime.minute = 44;
    currentTime.hour = 23;
    monthDay = 22;     //day of month
    weekDay = 1;      // 1 = monday, 2 = tuesday ...
    week = 24;
    month = 11;
    year = 21;
    updatedTimeOnLcd = false;
    updatedDateOnLcd = false;
}

const char *timeDate::intToString(unsigned char value)
{

    std::string s = std::to_string(value);
    if (value < 10)
        s = "0" + s;
    return s.c_str();
}

// ! MODIFIER FUNCTIONS
// To increment values

void timeDate::incrementYear()
{
    year++;
    if (year > 2999)
    {
        year = 2000;
    }
}

void timeDate::decrementYear()
{
    if (year == 2000)
    {
        year = 2999;
        return;
    }
    year--;
}

void timeDate::incrementMonth()
{
    month++;
    if (month > 12)
    {
        incrementYear();
        month = 0;
        week = 0;
    }
}

void timeDate::decrementMonth()
{
    if (month == 0)
    {
        month = 12;
        return;
    }
    month--;
}

void timeDate::incrementWeek()
{
    updatedDateOnLcd = false;
    week++;
}

void timeDate::decrementWeek()
{
    if (week == 0)
    {
        week = 53;
        return;
    }
    week--;
    updatedDateOnLcd = false;
}

void timeDate::incrementMonthDay()
{

    monthDay++;
    if (monthDay > 31)
    {
        // ToDo: Incremented based in current month days (comparat
        incrementMonth();
        monthDay = 1;
    }
    updatedDateOnLcd = false;
}

void timeDate::decrementMonthDay()
{
    if (monthDay == 0)
    {
        monthDay = 32;
    }
    monthDay--;
    updatedDateOnLcd = false;
}

void timeDate::incrementWeekDay()
{
    weekDay++;
    if (weekDay > 6)
    {
        incrementWeek();
        weekDay = 0;
    }
    updatedDateOnLcd = false;
}

void timeDate::decrementWeekDay()
{
    if (weekDay == 0)
    {
        weekDay = 6;
        return;
    }
    weekDay--;
    updatedDateOnLcd = false;
}

void timeDate::incrementHour()
{
    currentTime.hour++;
    updatedTimeOnLcd = false;
    if (currentTime.hour > 23)
    {
        incrementMonthDay();
        incrementWeek();
        currentTime.hour = 0;
    }
}

void timeDate::decrementHour()
{
    if (currentTime.hour == 0)
    {
        currentTime.hour = 23;
        return;
    }
    currentTime.hour--;
    updatedTimeOnLcd = false;
}

void timeDate::incrementMinute()
{
    currentTime.minute++;
    updatedTimeOnLcd = false;
    if (currentTime.minute > 59)
    {
        incrementHour();
        currentTime.minute = 0;
    }
}

void timeDate::decrementMinute()
{
    if (currentTime.minute == 0)
    {
        currentTime.minute = 59;
        return;
    }
    currentTime.minute--;
    updatedTimeOnLcd = false;
}

void timeDate::incrementSecond()
{
    currentTime.second++;
    if (currentTime.second >= 60)
    {
        incrementMinute();
        currentTime.second = 0;
    }
}

// GET FUNCTIONS
// get char functions
const char *timeDate::getSecond()
{
    return intToString(currentTime.second);
}

const char *timeDate::getMinute()
{
    return intToString(currentTime.minute);
}

const char *timeDate::getHour()
{
    return intToString(currentTime.hour);
}

const char *timeDate::getMonthDay()
{
    return intToString(monthDay);
}

const char *timeDate::getWeekDay()
{
    return weekDays[weekDay];
}

const char *timeDate::getWeek()
{
    return intToString(week);
}

const char *timeDate::getMonth()
{
    return intToString(month);
}

const char *timeDate::getYear()
{
    return intToString(year);
}

// get status functions
bool timeDate::checkUpdatedTime()
{
    return updatedTimeOnLcd;
}

bool timeDate::checkUpdatedDate()
{
    return updatedDateOnLcd;
}

//set status functions
bool timeDate::setTimeOnLcdUpdated()
{
    updatedTimeOnLcd = true;
}
bool timeDate::setDateOnLcdUpdate()
{
    updatedDateOnLcd = true;
}

void timeDate::callUpdateDate()
{
    updatedDateOnLcd = false;
}

void timeDate::callUpdateTime()
{
    updatedTimeOnLcd = false;
}
