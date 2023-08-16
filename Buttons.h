#ifndef BUTTONS_H_
#define BUTTONS_H_

#include "msp430g2553.h"

class buttons
{
public:
    buttons ();
    bool checkStateButtonTime ();
    bool checkStateButtonIncrementValue ();
    bool checkStateButtonDecrementValue ();
    bool checkStateButtonMovePos ();

private:
    void initButtonChangeTime ();
    void initButtonMovePos ();
    void initButtonIncrementValue ();
    void initButtonDecrementValue ();
};

#endif /* BUTTONS_H_ */
