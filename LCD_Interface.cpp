/*
 * lcdinterface.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: mafm
 */

#include "LCD_Interface.h"

Lcd_Interface::Lcd_Interface(Time_Date * td)
{
    _td = td;
    initLCD();
    clean_lcd();
}


void Lcd_Interface::clean_lcd(){
    setAddr(46, 1);
    writeStringToLCD(_td->get_second(), 2);
    setAddr(28, 1);
    writeStringToLCD(_td->get_minute(),2 );
    writeCharToLCD(0x3a); //":"
    setAddr(10, 1);
    writeStringToLCD(_td->get_hour(), 2);
    writeCharToLCD(0x3a); //":"

    setAddr(10, 2);
    writeStringToLCD(_td->get_nday(), 2);

}

void Lcd_Interface::time_to_lcd(){

    setAddr(46, 1);
    writeStringToLCD(_td->get_second(),2);
     
    if(_td->get_update_minute()){
        setAddr(28, 1);
        writeStringToLCD(_td->get_minute(),2);

        if(_td->get_update_hour()){
            setAddr(10, 1);
            writeStringToLCD(_td->get_hour(),2);

            if(_td->get_update_day()){
                setAddr(10, 2);
                writeStringToLCD(_td->get_nday(),2);
                writeCharToLCD(0x2f); //"/"
                setAddr(10, 3);
                writeCharToLCD(0x57); //"W"
                writeStringToLCD(_td->get_week(),2);
                
                
                if(_td->get_update_week()){
                    setAddr(35, 3);
                    writeStringToLCD(_td->get_wday(),9);
                }
                if(_td->get_update_month_year()){
 
                    setAddr(28, 2);
                    writeStringToLCD(_td->get_month(),2);
                    writeCharToLCD(0x2f); //"/"
                    writeStringToLCD(_td->get_year(),2);

                }
            }
        }
    }
}


void Lcd_Interface::change_time(){
    
    static unsigned int position = 3;
    while(_b.check_state_button_time()){

        switch(position) {
            case 1 :
                toggle_hour();
                break;
            case 2 :
                toggle_minute();
                break;
            case 3 :
                toggle_nday();
                break;
        }

        if (move_pos()){
            position++;
            clean_lcd();

            if (position >3)
                position = 1;
            else if (position <1)
                position = 3; 
        }

        clean_lcd();
        for(unsigned long i=5000; i>0; i--);     // delay
    }
}

void Lcd_Interface::toggle_hour(){
    
    if (_b.check_state_button_increment_value())
        _td->increment_hour();
    else if (_b.check_state_button_decrement_value())
        _td->decrement_hour();

    setAddr(10, 1);
    writeStringToLCD(_td->get_hour(), 2);
    
    for(unsigned long i=80000; i>0; i--);     // delay
    
    setAddr(10, 1);
    writeCharToLCD(0x5b); //"_"
    writeCharToLCD(0x5b); //"_"

    for(unsigned long i=20000; i>0; i--);     // delay
}

void Lcd_Interface::toggle_minute(){
    
    static bool toggle = true;
    setAddr(28, 1);
    if (toggle){
        writeStringToLCD(_td->get_minute(), 2);
        toggle = false;
    }
    else {
        writeCharToLCD(0x5b); //"_"
        writeCharToLCD(0x5b); //"_"
        toggle = true;
    }
    for(unsigned long i=50000; i>0; i--);     // delay
}

void Lcd_Interface::toggle_nday(){
    
    static bool toggle = true;
    setAddr(10, 2);
    if (toggle){
        writeStringToLCD(_td->get_nday(), 2);
        toggle = false;
    }
    else {
        writeCharToLCD(0x5b); //"_"
        writeCharToLCD(0x5b); //"_"
        toggle = true;
    }
    for(unsigned long i=50000; i>0; i--);     // delay
}

bool Lcd_Interface::move_pos(){
    if (_b.check_state_button_move_pos())
        return true;
    return false;
}