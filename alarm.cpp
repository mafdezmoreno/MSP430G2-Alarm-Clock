#include "alarm.h"

alarm::alarm(const timeType *cTime, const unsigned int *weekDay)
{
    currentTime = cTime;
    currentWeekDay = weekDay;
    clearAllAlarms();
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
        (currentTime->hour == currentStatus->time.minute))
    {
        return true;
    }
    return false;
}

void alarm::clearAlarm(unsigned weekDay)
{
    const int alarm = 0;
    const timeType timeA = {0, 0, 0};
    for (auto &weekDaysAlarm: weekDaysAlarms)
    {
        weekDaysAlarm.active = alarm;
        weekDaysAlarm.time = timeA;
    }
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