/*
 * buttons.cpp
 *
 *  Created on: Jun 5, 2021
 *      Author: mak
 */

#include "buttons.h"

buttons::buttons()
{
    _init_button_increment_value();
    _init_button_decrement_value();
    _init_button_change_time();
    _init_button_move_pos();
}

void buttons::_init_button_decrement_value(){
    //1.2
    P1DIR &=~ BIT2; //set pin as input (by default it's setted as input)
    P1REN |=  BIT2; //resistor enable
    P1OUT |=  BIT2; //pull up resistor
}

void buttons::_init_button_increment_value(){
    //1.3
    P1DIR &=~ BIT3; //set pin as input (by default it's setted as input)
    P1REN |=  BIT3; //resistor enable
    P1OUT |=  BIT3; //pull up resistor
}

void buttons::_init_button_change_time(){
    //1.0
    P1DIR &=~ BIT0; //set pin as input (by default it's setted as input)
    P1REN |=  BIT0; //resistor enable
    P1OUT |=  BIT0; //pull up resistor
}

void buttons::_init_button_move_pos(){
    //2.0
    P2DIR &=~ BIT0; //set pin as input (by default it's setted as input)
    P2REN |=  BIT0; //resistor enable
    P2OUT |=  BIT0; //pull up resistor
}


bool buttons::check_state_button_increment_value(){
    //1.3
    if ((P1IN & BIT3) != BIT3){
        for(unsigned int i=50; i>0; i--);     // delay
            if ((P1IN & BIT3) != BIT3){
            return true;
            }
    }
    return false;
}

bool buttons::check_state_button_decrement_value(){
    //1.2
    if ((P1IN & BIT2) != BIT2){
        for(unsigned int i=50; i>0; i--);     // delay
            if ((P1IN & BIT2) != BIT2){
            return true;
            }
    }
    return false;
}


bool buttons::check_state_button_move_pos(){
    //2.0
    if ((P2IN & BIT0) != BIT0){
        for(unsigned int i=50; i>0; i--);     // delay
            if ((P2IN & BIT0) != BIT0){
            return true;
            }
    }
    return false;
}

bool buttons::check_state_button_time(){
    //1.0
    if ((P1IN & BIT0) != BIT0){
        for(unsigned int i=50; i>0; i--);     // delay
            if ((P1IN & BIT0) != BIT0){
            return true;
            }
    }
    return false;
}
