//
//    FILE: dht.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.14
// PURPOSE: DHT Temperature & Humidity Sensor library for Arduino
//     URL: http://arduino.cc/playground/Main/DHTLib
//
// HISTORY:
// see dht.cpp file
//

#ifndef DHT_H
#define DHT_H
#include <Arduino.h>

#define DHT_LIB_VERSION "0.1.14"

#define DHTLIB_OK                0
#define DHTLIB_ERROR_CHECKSUM   -1
#define DHTLIB_ERROR_TIMEOUT    -2
#define DHTLIB_INVALID_VALUE    -999

#define DHTLIB_DHT11_WAKEUP     18
#define DHTLIB_DHT_WAKEUP       1

// max timeout is 100 usec.
// For a 16 Mhz proc 100 usec is 1600 clock cycles
// loops using DHTLIB_TIMEOUT use at least 4 clock cycli
// so 100 us takes max 400 loops
// so by dividing F_CPU by 40000 we "fail" as fast as possible
#define DHTLIB_TIMEOUT (F_CPU/40000)

class dht
{
public:
    // return values:
    // DHTLIB_OK
    // DHTLIB_ERROR_CHECKSUM
    // DHTLIB_ERROR_TIMEOUT
    int read11(uint32_t pin);
    int read(uint32_t pin);

    inline int read21(uint32_t pin) { return read(pin); };
    inline int read22(uint32_t pin) { return read(pin); };
    inline int read33(uint32_t pin) { return read(pin); };
    inline int read44(uint32_t pin) { return read(pin); };

    double humidity;
    double temperature;

private:
    uint32_t bits[5];  // buffer to receive data
    int _readSensor(uint32_t pin, uint32_t wakeupDelay);
};
#endif
//
// END OF FILE
//