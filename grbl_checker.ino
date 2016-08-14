/*
 # grbl_checker https://github.com/faultylee/grbl_checker
   Simple Arduino sketch to check [Grbl](https://github.com/grbl/grbl) external connections to assist troubleshooting

 ## What is checked

   - Limit switches(todo)
   - Probe(todo)
   - Reset/Abort(todo)
   - Feed hold(todo)
   - Cycle Start/Resume(todo)
   - Coolant Enable(todo)
   - Stepper Direction(todo)
   - Step pulse(todo)
   - Spindle Enable/PWM(todo)
   - Spindle Direction(todo)

   Refer to [Connecting-Grbl](https://github.com/grbl/grbl/wiki/Connecting-Grbl) for connection details
   MIT License
 */
#include "Arduino.h"

//Uncomment the following if you're using
//  version >= 0.9j
//  OR Variable Spindle on version < 0.9j
//#define VARIABLE_SPINDLE

//Uncomment the following if you configured grbl to invert your limit input
//  Pull up will be disabled and you'll need to have external pull down
//#define LIMIT_INVERT

//Taken from https://github.com/grbl/grbl/blob/master/grbl/cpu_map/cpu_map_atmega328p.h
#define X_LIMIT_BIT     9//1  // Uno Digital Pin 9
#define Y_LIMIT_BIT     10//2  // Uno Digital Pin 10
#ifdef VARIABLE_SPINDLE // Z Limit pin and spindle enabled swapped to access hardware PWM on Pin 11.
  #define Z_LIMIT_BIT   12//4 // Uno Digital Pin 12
#else
  #define Z_LIMIT_BIT   11//3  // Uno Digital Pin 11
#endif
#define RESET_BIT        14//A0//0  // Uno Analog Pin 0
#define FEED_HOLD_BIT    15//A1//1  // Uno Analog Pin 1
#define CYCLE_START_BIT  16//A2//2  // Uno Analog Pin 2
#define PROBE_BIT        19//A5//5  // Uno Analog Pin 5

void setup() {
    Serial.begin(115200);
#ifdef  LIMIT_INVERT
    pinMode(X_LIMIT_BIT, INPUT);
    pinMode(Y_LIMIT_BIT, INPUT);
    pinMode(Z_LIMIT_BIT, INPUT);
#else
    pinMode(X_LIMIT_BIT, INPUT_PULLUP);
    pinMode(Y_LIMIT_BIT, INPUT_PULLUP);
    pinMode(Z_LIMIT_BIT, INPUT_PULLUP);
#endif
    pinMode(RESET_BIT, INPUT_PULLUP);
    pinMode(FEED_HOLD_BIT, INPUT_PULLUP);
    pinMode(CYCLE_START_BIT, INPUT_PULLUP);
    pinMode(PROBE_BIT, INPUT_PULLUP);
}

void loop() {
    Serial.print("LIMIT: ");
    Serial.print("X:" + String(digitalRead(X_LIMIT_BIT) == 1 ? "+ " : "- "));
    Serial.print("Y:" + String(digitalRead(Y_LIMIT_BIT) == 1 ? "+ " : "- "));
    Serial.print("Z:" + String(digitalRead(Z_LIMIT_BIT) == 1 ? "+ " : "- "));
    Serial.print("Reset:" + String(digitalRead(RESET_BIT) == 1 ? "+ " : "- "));
    Serial.print("Hold:" + String(digitalRead(FEED_HOLD_BIT) == 1 ? "+ " : "- "));
    Serial.print("Cycle:" + String(digitalRead(CYCLE_START_BIT) == 1 ? "+ " : "- "));
    Serial.print("Probe:" + String(digitalRead(PROBE_BIT) == 1 ? "+ " : "- "));
    Serial.println();
    //Send CR to reuse line, easier on the eye
    //Serial.write(13);//Doesn't work in Arduino Serial Monitor
    delay(100);
}
