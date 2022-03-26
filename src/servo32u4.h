#pragma once

#include <Arduino.h>

/** \class Servo32U4
 * \brief A servo class to control a servo on pin 5.
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

/** \class Servo32U4Pin6
 * \brief A servo class to control a servo on pin 6.
 * 
 * Servo32U4Pin6 uses output compare on Timer4 to control the pulse to the servo. 
 * _In Chassis::init(),
 * The 8-bit Timer4 is set up with a pre-scaler of 1024, TOP of 249 + 1 => 16 ms interval.
 * 
 * YOU MUST CALL Chasssis::init() IN setup() FOR THIS TO WORK, 
 * AND YOU MUST CALL Chassis::init() BEFORE YOU CALL attach()
 * 
 * OCR4D controls the pulse on pin 6 -- THIS SERVO MUST BE ON PIN 6! 
 * 
 * Defaults to a range of 1000 - 2000 us, but can be customized.
 * 
 * Note that because we're using an 8-bit timer, resolution is only 64 us.
 */
class Servo32U4Pin6
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
