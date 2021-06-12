/*
 * TimeDate.h
 *
 *  Created on: Jun 5, 2021
 *      Author: mafm
 */

#ifndef TIMEDATE_H_
#define TIMEDATE_H_

#include <string>

class Time_Date
{
public:
    Time_Date();
    
    //get char functions
    const char * get_year();
    const char * get_month();
    const char * get_week();
    const char * get_wday();
    const char * get_nday();
    const char * get_hour();
    const char * get_minute();
    const char * get_second();
        
    //get status functions
        bool get_update_minute();
        bool get_update_hour();
        bool get_update_day(); //used to update the rest of elements
        
    // ! MODIFIER FUNCTIONS
    // To increment values

        // Normal operation of clock (increment time every second). To be called by the interrupt function
        void increment_second();

        void increment_minute();
        void increment_hour();
        void increment_day();
        void increment_week();
        void increment_month();
        void increment_year();
        void set_time();

        void decrement_hour();

        void update_all(); //set all bools vars to true
private:

    // Register variables
        unsigned int _year;
        unsigned int _month;
        unsigned int _week;
        unsigned int _wday;
        unsigned int _nday;
        int _hour;
        unsigned int _minute;
        unsigned char _second;

    // status variables
        bool _update_minute;
        bool _update_hour;
        bool _update_day; //used to update the rest of elements

    // constants
        const char *wday[7] = { "MON", "TUE",
                                "WED", "THU",
                                "FRI", "SAT", "SUN"};
 

        const char * int_to_string(unsigned char value);

    // To update status (to refesh value on lcd)
        void update_minute();
        void update_hour();
        void update_day(); //used to update the rest of elements
};

#endif /* TIMEDATE_H_ */
