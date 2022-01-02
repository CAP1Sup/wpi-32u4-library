#pragma once

#include <Arduino.h>

/** \class A servo class to control a servo on pin 5.
 * 
 * Servo32U4 uses output compare on Timer3 to control the pulse to the servo. 
 * The 16-bit Timer3 is set up with a pre-scaler of 8, TOP of 39999 + 1 => 20 ms interval.
 * 
 * OCR3A controls the pulse on pin 5 -- THE SERVO MUST BE ON PIN 5! 
 * 
 * Defaults to a range of 1000 - 2000 us, but can be customized.
 */
class Servo32U4
{
private:
    uint16_t usMin = 1000;
    uint16_t usMax = 2000;

    uint8_t feedbackPin = -1;
    bool isAttached = false;

public:
    void attach(void);
    void detach(void);
    void writeMicroseconds(uint16_t microseconds);
    uint16_t setMinMaxMicroseconds(uint16_t min, uint16_t max);
};
