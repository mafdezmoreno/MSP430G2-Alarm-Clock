#ifndef LCDINTERFACE_H_
#define LCDINTERFACE_H_

#include "buttons.h"
#include "lcd5110.h"
#include "timeDate.h"

class lcdInterface
{
public:
    lcdInterface (timeDate *td);
    void clean_lcd ();
    void time_to_lcd ();
    void change_time ();
    void toggle_hour ();
    void toggle_nday ();
    void toggle_minute ();
    bool move_pos ();

private:
    timeDate *_td;
    buttons _b;

    static const unsigned _wide = 6;

    // positions on LCD screen
    // row 0
    static const unsigned _x_week = 0;
    static const unsigned _y_week = 0;

    static const unsigned _x_wday = _wide * 6;
    static const unsigned _y_wday = 0;

    static const unsigned _x_bat = _wide * 11;
    static const unsigned _y_bat = 0;

    // row 1
    static const unsigned _x_hour = 18;
    static const unsigned _y_hour = 1;

    static const unsigned _x_min = _x_hour + _wide * 3;
    static const unsigned _y_min = 1;

    static const unsigned _x_sec = _x_min + _wide * 3;
    static const unsigned _y_sec = 1;

    // row 2
    static const unsigned _x_nday = 18;
    static const unsigned _y_nday = 2;

    // row 3
    static const unsigned _x_a1 = 0;
    static const unsigned _y_a1 = 3;
    static const unsigned _x_a1_hour = _wide + _wide / 2;
    static const unsigned _y_a1_hour = 3;
    static const unsigned _x_a1_days = _wide * 7;
    static const unsigned _y_a1_days = 3;

    // row 4
    static const unsigned _x_a2 = 0;
    static const unsigned _y_a2 = 4;
    static const unsigned _x_a2_hour = _wide + _wide / 2;
    static const unsigned _y_a2_hour = 4;
    static const unsigned _x_a2_days = _wide * 7;
    static const unsigned _y_a2_days = 4;

    // row 5
    static const unsigned _x_hr = _wide;
    static const unsigned _y_hr = 5;
    static const unsigned _x_temp = _wide * 8;
    static const unsigned _y_temp = 5;
};

#endif /* LCDINTERFACE_H_ */
