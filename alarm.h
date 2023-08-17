#ifndef ALARM_H_
#define ALARM_H_

#include "timeDate.h"

struct aTime
{
    int active;
    timeType timeT;
};

class alarm
{
public:
    explicit alarm(timeType *currentTime);
    void setAlarm(int weekDay, timeType alarmT);
    int getAlarmState();
    int checkAlarmTime(int weekDay);

private:
    bool alarmState;
    aTime weekDaysAlarms[7];
    timeType *currentTime;

    void clearAlarms();
};

#endif /* ALARM_H_ */
