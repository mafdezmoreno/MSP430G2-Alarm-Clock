#ifndef ALARM_H_
#define ALARM_H_

#include "timeDate.h"

struct aTime
{
    bool active;
    timeType time;
};

class alarm
{
public:
    alarm::alarm(const timeType *cTime, const unsigned *weekDay);
    void setAlarm(unsigned weekDay, timeType alarmT);
    aTime getAlarmStatus(unsigned weekDay);
    bool alarmTimeNow();
    void stopCurrentAlarm();
    void clearAlarm(unsigned weekDay);
    void clearAllAlarms();

private:
    bool alarmState;
    aTime weekDaysAlarms[7];
    const timeType * currentTime;
    const unsigned * currentWeekDay;
};

#endif /* ALARM_H_ */
