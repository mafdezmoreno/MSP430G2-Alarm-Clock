/*
 * buttons.h
 *
 *  Created on: Jun 5, 2021
 *      Author: mafm
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "msp430g2553.h"

class buttons
{
public:
    buttons();
    bool check_state_button_time();
    bool check_state_button_increment_value();
    bool check_state_button_decrement_value();
    bool check_state_button_move_pos();
    
    private:
        void _init_button_change_time();
        void _init_button_move_pos();
        void _init_button_increment_value();
        void _init_button_decrement_value();
};

#endif /* BUTTONS_H_ */
