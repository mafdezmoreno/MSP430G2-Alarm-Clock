#ifndef ALARM_H_
#define ALARM_H_

#include "timeDate.h"

struct aTime
{
    int active;
    timeType time;
};

class alarm
{
public:
    alarm(const timeType *cTime, const unsigned *weekDay);
    void setAlarm(unsigned weekDay, timeType alarmT);
    aTime getAlarmStatus(unsigned weekDay);
    bool alarmTimeNow();
    void stopCurrentAlarm();
    void clearAlarm(unsigned weekDay);
    void clearAllAlarms();
    void toggleAlarm(unsigned weekDay);
    const char * weekAlarmsToString();
    const char * hourToString(const unsigned * weekDay);
    const char * minuteToString(const unsigned * weekDay);

private:
    bool alarmState;
    aTime weekDaysAlarms[7];
    const timeType * currentTime;
    const unsigned * currentWeekDay;
};

#endif /* ALARM_H_ */
