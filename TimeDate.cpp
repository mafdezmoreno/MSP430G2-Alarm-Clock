/*
 * TimeDate.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: mafm
 */

#include <TimeDate.h>

Time_Date::Time_Date()
{
    _second = 55;
    _minute = 44;
    _hour = 23;
    _nday = 22;     //day of month
    _wday = 1;      // 1 = monday, 2 = tuesday ...
    _week = 24;
    _month = 11;
    _year = 21;

    update_all();
}

void Time_Date::update_all(){
    
    _update_minute = true;
    _update_hour = true;
    _update_day = true;
}

const char * Time_Date::int_to_string(unsigned char value){

    std::string s = std::to_string(value);
    if (value <10)
        s = "0" + s;
    return s.c_str();
}

// ! MODIFIER FUNCTIONS
// To increment values

void Time_Date::increment_minute(){
    _minute++;
    if (_minute >= 60){
        increment_hour();
        update_hour();
        _minute = 0;
    }
}

void Time_Date::increment_hour(){
    _hour++;
    if (_hour >= 24){
        increment_day();
        update_day();
        _hour = 0;
    }
}

void Time_Date::decrement_hour(){
    _hour--;
    if (_hour <= 0){
        //increment_day();
        //update_day();
        _hour = 23;
    }
}

void Time_Date::increment_day(){
    _nday++;
    _wday++;
    if (_nday > 30){
        increment_month();
        _nday = 1;
    }
    if(_wday > 7){
        increment_week();
        _wday = 1;
    }
}

void Time_Date::increment_second(){
    _second++;
    if (_second >= 60){
        increment_minute();
        update_minute();
        _second = 0;
    }
}
void Time_Date::increment_week(){
    _wday++;
}
void Time_Date::increment_month(){
    _wday++;
}
void Time_Date::increment_year(){
    _wday++;
}

// To update status
void Time_Date::update_minute(){
    _update_minute = true;
}
void Time_Date::update_hour(){
    _update_hour = true;
}
void Time_Date::update_day(){
    _update_day = true;
}

// GET FUNCTIONS
// get char functions
const char * Time_Date::get_second(){
    return int_to_string(_second);
}
const char * Time_Date::get_minute(){
    return int_to_string(_minute);
}
const char * Time_Date::get_hour(){
    return int_to_string(_hour);
}
const char * Time_Date::get_nday(){
    return int_to_string(_nday);
}
const char * Time_Date::get_wday(){
    //return int_to_string(_wday);
    return wday[_wday];
}
const char * Time_Date::get_week(){
    return int_to_string(_week);
}
const char * Time_Date::get_month(){
    return int_to_string(_month);
}
const char * Time_Date::get_year(){
    return int_to_string(_year);
}

// get status functions
bool Time_Date::get_update_minute(){
    if (_update_minute){
        _update_minute = false;
        return true;
    }
    return false;
}

bool Time_Date::get_update_hour(){
    if (_update_hour){
        _update_hour = false;
        return true;
    }
    return false;
}

bool Time_Date::get_update_day(){
    if (_update_day){
        _update_day = false;
        return true;
    }
    return false;
}
