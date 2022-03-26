/*
 * Activity 02 -- Staying on track
 *
 * Line following with speed control. Pauses at an intersection and waits for a turn command.
 */ 

#include <Arduino.h>
#include <wpi-32u4-lib.h>

#include <IRdecoder.h>
#include <ir_codes.h>

#include <Chassis.h>

// Include Servo32u4 library
#include <Servo32u4.h>

// Declare a chassis object with nominal dimensions
// In practice, adjust the parameters: wheel diam, encoder counts, wheel track
Chassis chassis(7.0, 1440, 14.9);

// Declare a servos object
// This example allows servos on both pins 5 and 6 
Servo32U4 servo5;
Servo32U4Pin6 servo6;


// Setup the IR receiver/decoder object
const uint8_t IR_DETECTOR_PIN = 0;
IRDecoder decoder(IR_DETECTOR_PIN);

// Helper function for debugging
#define LED_PIN 13
void setLED(bool value)
{
  Serial.println("setLED()");
  digitalWrite(LED_PIN, value);
}

// Define the states
enum ROBOT_STATE {ROBOT_IDLE, ROBOT_SERVO_TEST};
ROBOT_STATE robotState = ROBOT_IDLE;

// A helper function to stop the motors
void idle(void)
{
  Serial.println("idle()");
  setLED(LOW);

  //stop motors 
  chassis.idle();

  //set state to idle
  robotState = ROBOT_IDLE;
}

// Function for adjusting servos
void adjustServo(uint8_t pin, uint16 uSeconds)
{
  if(robotState = ROBOT_SERVO_TEST)
  {
    if(pin == 5) servo5.writeMicroseconds(uSeconds);
    else if(pin == 6) servo6.writeMicroseconds(uSeconds);
    else Serial.println("Illegal servo pin!");
  }
}

// Handles a key press on the IR remote
void handleKeyPress(int16_t keyPress)
{
  Serial.println("Key: " + String(keyPress));

  //ENTER_SAVE idles, regardless of state -- E-stop
  if(keyPress == ENTER_SAVE) idle(); 

  switch(robotState)
  {
    case ROBOT_IDLE:
      if(keyPress == VOLplus)  //VOL+ increases speed
      {
        adjustServo(5, 2000);
        adjustServo(6, 2000);
      }

      if(keyPress == VOLminus)  //VOL- decreases speed
      {
        adjustServo(5, 1000);
        adjustServo(6, 1000);
      }

      break;

     default:
      break;
  }
}

/*
 * This is the standard setup function that is called when the board is rebooted
 * It is used to initialize anything that needs to be done once.
 */
void setup() 
{
  // This will initialize the Serial at a baud rate of 115200 for prints
  // Be sure to set your Serial Monitor appropriately
  Serial.begin(115200);

  // initialize the chassis (which also initializes the motors)
  chassis.init();
  idle();

  // these can be undone for the student to adjust
  chassis.setMotorPIDcoeffs(5, 0.5);

  // Setup the servo 
  servo5.attach();
  servo6.attach();

  // initialize the IR decoder
  decoder.init();

  Serial.println("/setup()");
}

/*
 * The main loop for the program. The loop function is repeatedly called
 * after setup() is complete.
 */
void loop()
{
  // Check for a key press on the remote
  int16_t keyPress = decoder.getKeyCode();
  if(keyPress >= 0) handleKeyPress(keyPress);

  // A basic state machine
  switch(robotState)
  {
    default:
      break;
  }
}
