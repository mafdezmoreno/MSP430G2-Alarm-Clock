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

    _td->update_all();
    time_to_lcd();
    /*
    setAddr(_x_sec, _y_sec);
    writeStringToLCD(_td->get_second(), 2);
    setAddr(_x_min, _y_min);
    writeStringToLCD(_td->get_minute(),2 );
    writeCharToLCD(0x3a); //":"
    setAddr(_x_hour, _y_hour);
    writeStringToLCD(_td->get_hour(), 2);
    writeCharToLCD(0x3a); //":"

    //nday/month/year
    setAddr(_x_nday,_y_nday);
    writeStringToLCD(_td->get_nday(),2);
    writeCharToLCD(0x2f); //"/"
    writeStringToLCD(_td->get_month(),2);
    writeCharToLCD(0x2f); //"/"
    writeStringToLCD(_td->get_year(),2);
    */
    //setAddr(0, 3);
    //writeStringToLCD("00002233445566", 20);

}

void Lcd_Interface::time_to_lcd(){

    setAddr(_x_sec, _y_sec);
    writeStringToLCD(_td->get_second(),2);
     
    if(_td->get_update_minute()){
        setAddr(_x_min, _y_min);
        writeStringToLCD(_td->get_minute(),2);
        writeCharToLCD(0x3a); //":"

        if(_td->get_update_hour()){
            setAddr(_x_hour, _y_hour);
            writeStringToLCD(_td->get_hour(),2);
            writeCharToLCD(0x3a); //":"

            // The rest of values are updated daily
            if(_td->get_update_day()){
   
                //week
                setAddr(_x_week, _y_week);
                writeCharToLCD(0x57); //"W"
                writeCharToLCD(0x3a); //":"
                writeStringToLCD(_td->get_week(),2);

                //week day      
                setAddr(_x_wday, _y_wday);
                writeStringToLCD(_td->get_wday(),9);

                //nday/month/year
                setAddr(_x_nday,_y_nday);
                writeStringToLCD(_td->get_nday(),2);
                writeCharToLCD(0x2f); //"/"
                writeStringToLCD(_td->get_month(),2);
                writeCharToLCD(0x2f); //"/"
                writeStringToLCD(_td->get_year(),2);

                //Battery Level
                setAddr(_x_bat, _y_bat);
                writeCharToLCD(0x42); //"B"
                writeCharToLCD(0x3a); //":"
                writeStringToLCD("3",2);

            }
        }
    }

    //if updated alarm:
        
        //alarm 1
        setAddr(_x_a1, _y_a1);
        writeStringToLCD("A",1);
        setAddr(_x_a1_hour, _y_a1_hour);
        writeStringToLCD("07:00",5);
        setAddr(_x_a1_days, _y_a1_days);
        writeStringToLCD("0000000",7);

        //alarm 2
        setAddr(_x_a2, _y_a2);
        writeStringToLCD("A",1);
        setAddr(_x_a2_hour, _y_a2_hour);
        writeStringToLCD("17:33",5);
        setAddr(_x_a2_days, _y_a2_days);
        writeStringToLCD("0000000",7);

    //if updated temperature and humidity

        //humidity
        setAddr(_x_hr, _y_hr);
        writeStringToLCD("HR41%",5);

        //temperature
        setAddr(_x_temp, _y_temp);
        writeStringToLCD("24.3C",5);
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