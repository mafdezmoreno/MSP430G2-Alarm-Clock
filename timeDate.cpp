#include <timeDate.h>

timeDate::timeDate()
{
    second = 55;
    minute = 44;
    hour = 23;
    nDay = 22;     //day of month
    wDay = 1;      // 1 = monday, 2 = tuesday ...
    week = 24;
    month = 11;
    year = 21;

    updateAll();
}

void timeDate::updateAll()
{

    updatedMinute = true;
    updatedHour = true;
    updatedDay = true;
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

void timeDate::incrementMinute()
{
    minute++;
    if (minute >= 60)
    {
        incrementHour();
        updateHour();
        minute = 0;
    }
}

void timeDate::incrementHour()
{
    hour++;
    if (hour >= 24)
    {
        incrementDay();
        updateDay();
        hour = 0;
    }
}

void timeDate::decrementHour()
{
    hour--;
    if (hour <= 0)
    {
        //increment_day();
        //update_day();
        hour = 23;
    }
}

void timeDate::incrementDay()
{
    nDay++;
    wDay++;
    if (nDay > 30)
    {
        incrementMonth();
        nDay = 1;
    }
    if (wDay > 7)
    {
        incrementWeek();
        wDay = 1;
    }
}

void timeDate::incrementSecond()
{
    second++;
    if (second >= 60)
    {
        incrementMinute();
        updateMin();
        second = 0;
    }
}

void timeDate::incrementWeek()
{
    wDay++;
}

void timeDate::incrementMonth()
{
    month++;
}

void timeDate::incrementYear()
{
    year++;
}

// To update status
void timeDate::updateMin()
{
    updatedMinute = true;
}

void timeDate::updateHour()
{
    updatedHour = true;
}

void timeDate::updateDay()
{
    updatedDay = true;
}

// GET FUNCTIONS
// get char functions
const char *timeDate::getSecond()
{
    return intToString(second);
}

const char *timeDate::getMinute()
{
    return intToString(minute);
}

const char *timeDate::getHour()
{
    return intToString(hour);
}

const char *timeDate::getNday()
{
    return intToString(nDay);
}

const char *timeDate::getWeekDay()
{
    return weekDays[wDay];
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
bool timeDate::getUpdateMinute()
{
    if (updatedMinute)
    {
        return true;
    }
    return false;
}

bool timeDate::getUpdateHour()
{
    if (updatedHour)
    {
        return true;
    }
    return false;
}

bool timeDate::getUpdateDay()
{
    if (updatedDay)
    {
        return true;
    }
    return false;
}

void timeDate::setTime()
{

}
