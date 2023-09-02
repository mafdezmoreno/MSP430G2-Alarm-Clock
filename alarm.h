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
    bool alarmTimeNow();
    void clearAlarm(unsigned weekDay);
    void clearAllAlarms();
    void toggleActivateDeactivate(unsigned weekDay);
    const char * weekAlarmsToString();
    const char * hourToString(const unsigned * weekDay);
    const char * minuteToString(const unsigned * weekDay);
    void incrementHour(const unsigned * weekDay);
    void decrementHour(const unsigned * weekDay);
    void incrementMin(const unsigned  * weekDay);
    void decrementMin(const unsigned  * weekDay);

private:
    aTime weekDaysAlarms[7];
    const timeType * currentTime;
    const unsigned * currentWeekDay;
};

#endif /* ALARM_H_ */
