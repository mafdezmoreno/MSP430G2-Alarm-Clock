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

    void set_alarm(int weekDay, timeType alarmT);

    int get_alarm_state();

    int check_alarm_time(int week_day);

private:
    bool alarm_state;
    aTime week_days_alarms[7];
    timeType *current_time;

    void clear_alarms();
};

#endif /* ALARM_H_ */
