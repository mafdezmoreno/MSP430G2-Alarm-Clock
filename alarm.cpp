#include "alarm.h"

alarm::alarm(const timeType *cTime, const unsigned int *weekDay)
{
    currentTime = cTime;
    currentWeekDay = weekDay;
    clearAllAlarms();
    alarmState = false;
}

void alarm::setAlarm(unsigned weekDay, timeType alarm)
{
    weekDaysAlarms[weekDay].active = 1;
    weekDaysAlarms[weekDay].time = alarm;
}

bool alarm::alarmTimeNow()
{
    const aTime *currentStatus = &weekDaysAlarms[*currentWeekDay];

    if (!currentStatus->active)
    {
        return false;
    }
    if ((currentTime->hour == currentStatus->time.hour) &
        (currentTime->minute == currentStatus->time.minute))
    {
        return true;
    }
    return false;
}

void alarm::clearAlarm(unsigned weekDay)
{
    const int alarm = 0;
    const timeType timeA = {0, 0, 0};
        weekDaysAlarms[weekDay].active = alarm;
        weekDaysAlarms[weekDay].time = timeA;
}

aTime alarm::getAlarmStatus(unsigned weekDay)
{
    if (weekDaysAlarms[weekDay].active)
    {
        alarmState = 1;
        return weekDaysAlarms[weekDay];
    }
    alarmState = 0;
    return {0, {0, 0, 0}};
}

void alarm::clearAllAlarms()
{
    for (unsigned i = 0; i < 7; i++)
    {
        clearAlarm(i);
    }
}

const char *alarm::weekAlarmsToString()
{
    char * s = new char[8] {"0000000"};
    for (unsigned i = 0; i < 7; i++)
    {
        if (weekDaysAlarms[i].active)
        {
            s[i] = '1';
        }
    }
    return s;
}


const char * alarm::hourToString(const unsigned * weekDay)
{
    unsigned value;
    char * str = new char[3] {"00"};
    value = weekDaysAlarms[*weekDay].time.hour;
    str[0] = value/10 + '0';
    str[1] = value%10 + '0';
    return str;
}

const char * alarm::minuteToString(const unsigned * weekDay)
{
    unsigned value;
    char * str;

    value = weekDaysAlarms[*weekDay].time.minute;
    str = new char[3] {"00"};

    str[0] = value/10 + '0';
    str[1] = value%10 + '0';

    return str;
}

void alarm::toggleActiveDeactive(unsigned int weekDay)
{
    if(weekDaysAlarms[weekDay].active)
    {
        weekDaysAlarms[weekDay].active = false;
    }
    else
    {
        weekDaysAlarms[weekDay].active = true;
    }
}

void alarm::incrementHour(const unsigned * weekDay)
{
    unsigned * pHour = &weekDaysAlarms[*weekDay].time.hour;

    (*pHour)++;
    if (*pHour > 23)
    {
        *pHour = 0;
    }
}

void alarm::decrementHour(const unsigned * weekDay)
{
    unsigned * pHour = &weekDaysAlarms[*weekDay].time.hour;

    if (*pHour == 0)
    {
        *pHour = 23;
        return;
    }
    (*pHour)--;
}

void alarm::incrementMin(const unsigned  * weekDay)
{
    unsigned * pMin = &weekDaysAlarms[*weekDay].time.minute;

    (*pMin)++;
    if (*pMin > 59)
    {
        *pMin = 0;
    }
}

void alarm::decrementMin(const unsigned  * weekDay)
{
    unsigned * pMin = &weekDaysAlarms[*weekDay].time.minute;

    if (*pMin == 0)
    {
        *pMin = 59;
        return;
    }
    (*pMin)--;
}
