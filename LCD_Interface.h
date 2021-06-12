/*
 * lcdinterface.h
 *
 *  Created on: Jun 5, 2021
 *      Author: mafm
 */

#ifndef LCDINTERFACE_H_
#define LCDINTERFACE_H_

#include "LCD_5110.h"
#include "TimeDate.h"
#include "Buttons.h"

class Lcd_Interface
{
    public:
        Lcd_Interface(Time_Date * td);    
        void clean_lcd();
        void time_to_lcd();
        void change_time();
        void toggle_hour();
        void toggle_nday();
        void toggle_minute();
        bool move_pos();

    private:
        Time_Date * _td;
        buttons _b;
};

#endif /* LCDINTERFACE_H_ */
