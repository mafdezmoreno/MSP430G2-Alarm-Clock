#include <timeDate.h>

timeDate::timeDate()
{
    currentTime.second = 55;
    currentTime.minute = 44;
    currentTime.hour = 23;
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
    currentTime.minute++;
    if (currentTime.minute >= 60)
    {
        incrementHour();
        updateHour();
        currentTime.minute = 0;
    }
}

void timeDate::incrementHour()
{
    currentTime.hour++;
    if (currentTime.hour >= 24)
    {
        incrementDay();
        updateDay();
        currentTime.hour = 0;
    }
}

void timeDate::decrementHour()
{
    currentTime.hour--;
    if (currentTime.hour <= 0)
    {
        //increment_day();
        //update_day();
        currentTime.hour = 23;
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
    currentTime.second++;
    if (currentTime.second >= 60)
    {
        incrementMinute();
        updateMin();
        currentTime.second = 0;
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
    return updatedMinute;
}

bool timeDate::getUpdateHour()
{
    return updatedHour;
}

bool timeDate::getUpdateDay()
{
    return updatedDay;
}

void timeDate::setTime()
{

}
