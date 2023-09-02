#ifndef TIMEDATE_H_
#define TIMEDATE_H_

#include <string>

struct timeType
{
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};

struct dateType
{
    //Todo
};

class timeDate
{
public:
    explicit timeDate(bool * signalIncrementMin);
    ~timeDate();

    //get char functions
    const char *getYear();
    const char *getMonth();
    const char *getWeek();
    const char *getWeekDay();
    const char *getMonthDay();
    const char *getHour();
    const char *getMinute();
    const char *getSecond();

    //get status functions
    bool checkUpdatedDate() const;
    bool checkUpdatedTime() const;

    //set status functions
    bool setTimeOnLcdUpdated();
    bool setDateOnLcdUpdate();

    // Normal operation of clock (increment time every second). To be called by the interrupt function
    void incrementYear();
    void incrementMonth();
    void incrementWeek();
    void incrementMonthDay();
    void incrementWeekDay();
    void incrementHour();
    void incrementMinute();
    void incrementSecond();
    void decrementYear();
    void decrementMonth();
    void decrementWeek();
    void decrementMonthDay();
    void decrementWeekDay();
    void decrementHour();
    void decrementMinute();

    // To update status (to refresh value on lcd)
    void callUpdateTime();
    void callUpdateDate(); //used to update the rest of elements

    const timeType * getCurrentTime();
    const unsigned * getCurrentWeekDay();

private:

    unsigned int year;
    unsigned int month;
    unsigned int week;
    unsigned int * weekDay;
    unsigned int monthDay;
    timeType * currentTime;

    bool updatedTimeOnLcd;
    bool updatedDateOnLcd;
    bool * incrementedMin;

    const char *weekDays[7] = {"MON", "TUE",
                               "WED", "THU",
                               "FRI", "SAT", "SUN"};

    const char *intToString(unsigned value);
};

#endif /* TIMEDATE_H_ */
