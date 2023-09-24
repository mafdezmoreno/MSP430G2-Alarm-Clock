/*
 * Based on https://github.com/bafeigum/DHT11-Library-for-MSP430/tree/master from Bryce Feigum
 */

#include "dht.h"
#include "timer.h"
#include "msp430g2553.h"

dht::dht()
{
    SET (P2OUT, BIT_DHT_VCC);       // VCC to dht (pin output)
}

const char *dht::getTemperature()
{
    char *str;
    str = new char[6]{"00.0C"};
    return str;
}

const char *dht::getHumidity()
{
    char *str;
    str = new char[6]{"HR00%"};
    return str;
}

void dht::powerOn()
{
    SET (P2DIR, BIT_DHT_VCC);
}

void dht::powerOff()
{
    CLR(P2DIR, BIT_DHT_VCC);
}
