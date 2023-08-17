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
    explicit alarm(timeType *currentTime);
    void setAlarm(unsigned weekDay, timeType alarmT);
    aTime getAlarmState(unsigned weekDay);
    bool getCurrentAlarmState();
    aTime checkAlarmTime(unsigned weekDay);
    void clearAlarm(unsigned weekDay);
    void clearAllAlarms();

private:
    bool alarmState;
    aTime weekDaysAlarms[7];
    timeType *currentTime;

};

#endif /* ALARM_H_ */
