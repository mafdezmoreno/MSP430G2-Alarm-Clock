#ifndef TIMEDATE_H_
#define TIMEDATE_H_

#include <string>

struct timeType
{
    unsigned int hour;
    unsigned int minute;
    unsigned int second;
};

class timeDate
{
public:
    timeDate();

    //get char functions
    const char *getYear();
    const char *getMonth();
    const char *getWeek();
    const char *getWeekDay();
    const char *getNday();
    const char *getHour();
    const char *getMinute();
    const char *getSecond();

    //get status functions
    bool getUpdateMinute();
    bool getUpdateHour();
    bool getUpdateDay(); //used to update the rest of elements

    // Normal operation of clock (increment time every second). To be called by the interrupt function
    void incrementSecond();
    void incrementMinute();
    void incrementHour();
    void incrementDay();
    void incrementWeek();
    void incrementMonth();
    void incrementYear();
    void setTime();
    void decrementHour();
    void updateAll(); //set all bool vars to true
private:

    unsigned int year;
    unsigned int month;
    unsigned int week;
    unsigned int wDay;
    unsigned int nDay;
    timeType currentTime;

    bool updatedMinute;
    bool updatedHour;
    bool updatedDay; //used to update the rest of elements

    const char *weekDays[7] = {"MON", "TUE",
                               "WED", "THU",
                               "FRI", "SAT", "SUN"};

    const char *intToString(unsigned char value);

    // To update status (to refresh value on lcd)
    void updateMin();
    void updateHour();
    void updateDay(); //used to update the rest of elements
};

#endif /* TIMEDATE_H_ */
