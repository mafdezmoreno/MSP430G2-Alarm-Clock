#include "alarm.h"

alarm::alarm(timeType * time)
{
    currentTime = time;
    clearAllAlarms ();
}

void alarm::setAlarm(unsigned weekDay, timeType alarm)
{
    weekDaysAlarms[weekDay].active = 1;
    weekDaysAlarms[weekDay].time = alarm;
}

bool alarm::getCurrentAlarmState()
{
    return alarmState;
}

void alarm::clearAlarm(unsigned weekDay)
{
    const int alarm = 0;
    const timeType timeA = {0, 0, 0};
    for (auto & weekDaysAlarm : weekDaysAlarms)
    {
        weekDaysAlarm.active = alarm;
        weekDaysAlarm.time = timeA;
    }
}

aTime alarm::checkAlarmTime(unsigned weekDay)
{
    if (weekDaysAlarms[weekDay].active)
    {
        // Todo: Implement check alarm time
        // Now it's only implemented check day (for test purposes)
        alarmState = 1;
        return weekDaysAlarms[weekDay];
    }
    alarmState = 0;
    return {0, {0,0,0}};
}

void alarm::clearAllAlarms()
{
    for (unsigned i = 0; i < 7; i++)
    {
        clearAlarm(i);
    }
}