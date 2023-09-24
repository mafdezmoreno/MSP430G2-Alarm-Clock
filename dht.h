#ifndef ALARM_CLOCK_MSP430_DHT_H
#define ALARM_CLOCK_MSP430_DHT_H

/*
 * Based on https://github.com/bafeigum/DHT11-Library-for-MSP430/tree/master from Bryce Feigum
 * Changes:
 * * Improved with encapsulations.
 * * Included functions and methods to use timer 0 or timer 1.
 */

#include "timer.h"

#define DHT_PIN BIT3
#define BIT_DHT_VCC BIT2

#define TST(x,y)	(x & (y))
#define SET(x,y)	(x|= (y))
#define CLR(x,y)	(x &= ~(y))

#define DHT_TIMER1

class dht
{
public:
    dht();
    bool readDht();
    const char * getHumidity();
    const char * getTemperature();

private:
    unsigned char tempDigits[3];
    unsigned char humiDigits[2];

    void readData(unsigned char * data);
    void startSignal();
    bool checkResponse();
    bool checkChecksum(unsigned char * tmp);
    bool checkDigits(const unsigned char * digits);
    void saveDigits(const unsigned char * digits);
    unsigned char * getDigits(unsigned char * tmpData);
    bool analyzeResponse(unsigned char * tmpData);

    void powerOn();
    void powerOff();
};

#endif /* ALARM_CLOCK_MSP430_DHT_H */
