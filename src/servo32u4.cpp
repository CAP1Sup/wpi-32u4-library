#include <servo32u4.h>

void Servo32U4::attach(void) //MUST USE PIN 5!!
{
    pinMode(5, OUTPUT); // set pin as OUTPUT

    cli();

    // clear then set the OCR3A bits (pin 5)
    TCCR3A = 0x82; //WGM
    TCCR3B = 0x1A; //WGM + CS = 8
    ICR3 = 39999; //20ms
    OCR3A = 3000; //default to neutral 1500us

    sei();

    isAttached = true;
}

void Servo32U4::detach(void)
{
    cli();

    // clear the OCR3A bits
    TCCR3A &= 0x7f; //cancel OCR3A
    sei();

    isAttached = false;
}

void Servo32U4::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    //prescaler is 8, so 1 timer count = 0.5 us
    OCR3A = microseconds << 1; // multiplies by 2
}

uint16_t Servo32U4::setMinMaxMicroseconds(uint16_t min, uint16_t max)
{
    // swap if in the wrong place
    if(min > max) {uint16_t temp = min; min = max; max = temp;}

    usMin = min;
    usMax = max;

    return usMax - usMin; //return the range, in case the user wants to do a sanity check
}

void Servo32U4Pin6::attach(void) // For controlling a servo on pin 6; 
{
    pinMode(6, OUTPUT); // set pin as OUTPUT

    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4C = 0x09;

    sei();

    isAttached = true;
}

void Servo32U4Pin6::detach(void) // For controlling a servo on pin 6; 
{
    cli();

    // Be careful here, since Timer4 is used to manage speed controller. See Chassis::init()
    TCCR4C = 0x00;

    sei();

    isAttached = true;
}

// Resolution is 64 us; not great, but shouldn't be too contstraining
void Servo32U4Pin6::writeMicroseconds(uint16_t microseconds)
{
    if (!isAttached)
    {
        attach();
    }

    microseconds = constrain(microseconds, usMin, usMax);

    //prescaler is 8, so 1 timer count = 0.5 us
    OCR4D = microseconds >> 6; // divides by 64
}

uint16_t Servo32U4Pin6::setMinMaxMicroseconds(uint16_t min, uint16_t max)
{
    // swap if in the wrong place
    if(min > max) {uint16_t temp = min; min = max; max = temp;}

    usMin = min;
    usMax = max;

    return usMax - usMin; //return the range, in case the user wants to do a sanity check
}

