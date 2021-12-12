# wpi-32u4-library

Version: 3.0.0<br/>
Release date: 2021-12-12<br/>
Forked from [www.pololu.com](https://www.pololu.com/)

## Summary

This is a C++ library for the Arduino IDE that helps access the on-board hardware of the [Romi 32U4 Control Board](https://www.pololu.com/product/3544).

The Romi 32U4 Control Board turns the Romi chassis into a programmable, Arduino-compatible robot.  It has an integrated AVR ATmega32U4 microcontroller, motor drivers, encoders, buzzer, buttons, and an LSM6DS33 accelerometer and gyro.

This library includes code for accessing the LSM6DS33, forked from the separate [LSM6 library](https://github.com/pololu/lsm6-arduino).

## Installing the library (platformio)

Add the following lines to your platformio.ini file:

~~~{.cpp}
lib_deps = 
     Wire
     wpi-32u4-library
~~~

You're done.

(You may or may not need to add Wire -- it can't hurt if you do.)

## Classes and functions

The main classes and functions provided by the library are listed below:

* Romi32U4ButtonA
* Romi32U4ButtonB
* Romi32U4ButtonC
* ~~Romi32U4Buzzer~~
* Romi32U4Encoders
* ~~Romi32U4LCD~~
* Romi32U4Motors
* ledRed()
* ledGreen()
* ledYellow()
* usbPowerPresent()
* readBatteryMillivolts()

## Component libraries

This library also includes copies of several other Arduino libraries inside it which are used to help implement the classes and functions above.

* [FastGPIO](https://github.com/pololu/fastgpio-arduino)
* ~~[PololuBuzzer]~~(https://github.com/pololu/pololu-buzzer-arduino)
* ~~[PololuHD44780]~~(https://github.com/pololu/pololu-hd44780-arduino)
* [Pushbutton](https://github.com/pololu/pushbutton-arduino)
* [QTRSensors](https://github.com/pololu/qtr-sensors-arduino)
* [USBPause](https://github.com/pololu/usb-pause-arduino)

You can use these libraries in your sketch automatically without any extra installation steps and without needing to add any extra `#include` lines to your sketch.

You should avoid adding extra `#include` lines such as `#include <Pushbutton.h>` because then the Arduino IDE might try to use the standalone Pushbutton library (if you previously installed it), and it would conflict with the copy of the Pushbutton code included in this library. 

## Documentation

Documentation found at https://wpiroboticsengineering.github.io/wpi-32u4-library/index.html. We are working on updating documentation for the changes to the forked Pololu library. The biggest change is to the motor class, where

~~~{.cpp}
Romi32U4Motors::setSpeeds()
~~~

has been changed to 

~~~{.cpp}
Romi32U4Motors::setEfforts()
~~~

since that better represents the behavior of that function.

Some other library files (LCD, buzzer) have been removed, since they conflict with some of the changes in the background (mostly to timers).

## Version history

* 2.6.0 (2021-04-04): Added in a library and example for the IR Positionn sensor from DF Robot. Also includes improvements to some libraries. Now includes a Timer class for software timers.
* 2.5.0 (2021-01-30): Previous versions add IR remote with interrupts handled automatically (so long as you use either an external interrupt pin or PCINT). IMU updates.
* 2.1.0 (2020-09-06): Primary release for WPI courses.
* 1.0.2 (2017-07-17): Fixed a bug that caused errors for the right encoder to be reported as errors for the left encoder.
* 1.0.1 (2017-02-23):
  * Changed the internal `Romi32U4Motors::maxSpeed` variable to be an `int16_t` so it can be compared to other `int16_t` variables without warnings.
  * Fixed the InterialSensors and Demo examples to not use a compass.
  * Fixed some comments.
* 1.0.0 (2017-02-06): Original release.
