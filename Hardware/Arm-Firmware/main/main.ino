#include <Arduino.h>
#include "MCP23017.h"
#include "Stepper.h"
//#include <Adafruit_MCP23017.h>
//#define PULpin 10
//#define DIRpin 11
//#define ENApin 9
//int STEPSPERREV = 4000;
//long unsigned int stepthismuch = STEPSPERREV*50;
//unsigned long stepdelay = 0;
//MCP23017 mcp_pin2; // the chip corresponding to this class interrupts on arduino pin 2
//MCP23017 mcp_pin3; // the chip corresponding to this class interrupts on arduino pin 3
//MCP23017* MCP23017::mcp_instances [2] = { NULL, NULL };
//Stepper myStepper(ENApin, PULpin, DIRpin, STEPSPERREV);
//int steps = 0;

/* relic of manual setup
// bicep 
#define pulse_1 3
#define dir_1 4
// bicep 
#define pulse_2 5
#define dir_2 6
// shoulder 
#define pulse_3 7
#define dir_3 8
*/
// enable all steppers
#define enable 13
// steps per rev:
#define STEPSPERREV 4000
int PULpin[3] = {pulse_1, pulse_2, pulse_3};
int DIRpin[3] = {dir_1, dir_2, dir_3};

// make 3 stepper objects
// Stepper::Stepper(int _enable, int _pulse, int _dir, int _steps) 

Stepper mySteppers[3] = {Stepper(STEPSPERREV, enable, PULpin[0], DIRpin[0]),
                        Stepper(STEPSPERREV, enable, PULpin[1], DIRpin[1]),
                        Stepper(STEPSPERREV, enable, PULpin[2], DIRpin[2])};

void setup() {
  // set up serial jic we need to monitor anything
  Serial.begin(9600);
  Serial.println("initialized");
  // stepper constructor should take care of all the pin initializations

}

// ms time intervals for running motors (ms)
long Motor1Interval = 10;
long Motor2Interval = 10;
long Motor2Interval = 10;

void loop() {

    /*
      TODO: 
        * set up encoders --> they will be posn_actual's
        * serial input --> should change this to ask for joint positions as inputs then convert those to steps
    */

    // serial in for the 3 motor positions
    if(Serial.available()){
        std::cout << "enter posn_desired_1" << endl;
        posn_desired_1 = Serial.readStringUntil('\n');
    }

    if(Serial.available()){
        std::cout << "enter posn_desired_2" << endl;
        posn_desired_2 = Serial.readStringUntil('\n');
    }

    if(Serial.available()){
        std::cout << "enter posn_desired_3" << endl;
        posn_desired_3 = Serial.readStringUntil('\n');
    }

    std::cout << "you entered desired positions of: " << posn_desired_1 << " " << posn_desired_2 << " " << posn_desired_3 << endl;

    // attempting to have the motors move in such a way it appears simultaneous
    unsigned long currentMotor1Time = millis();
    unsigned long currentMotor2Time = millis();
    unsigned long currentMotor3Time = millis();

    if(currentMotor1Time - previousMotor1Time > Motor1Interval){
      // if more than 10 ms diff between when you last moved motor then check if it should do someting
      if(posn_desired_1 != posn_actual_1):
        //if position is not where you want it to be, step one time
        ((posn_desired_1 - posn_actual_1) > 0){
          mySteppers[0]::stepCW(1);
        }
        ((posn_desired_1 - posn_actual_1) < 0){
          mySteppers[0]::stepCCW(1);
        }
        ((posn_desired_1 - posn_actual_1) == 0){
          std::cout << "motor_1 is at desired posn" << endl;
        }
      previousMotor1Time = currentMotor1Time;
    }
  
    if(currentMotor2Time - previousMotor2Time > Motor2Interval){
      // if more than 10 ms diff between when you last moved motor then check if it should do something
      if(posn_desired_2 != posn_actual_2):
        //if position is not where you want it to be, step one time
        if(posn_desired_2 != posn_actual_2):
        //if position is not where you want it to be, step one time
        ((posn_desired_2 - posn_actual_2) > 0){
          mySteppers[0]::stepCW(1);
        }
        ((posn_desired_2 - posn_actual_2) < 0){
          mySteppers[0]::stepCCW(1);
        }
        ((posn_desired_2 - posn_actual_2) == 0){
          std::cout << "motor_2 is at desired posn" << endl;
        }
      previousMotor1Time = currentMotor1Time;
    }
    
    if(currentMotor3Time - previousMotor3Time > Motor3Interval){
      // if more than 10 ms diff between when you last moved motor then check if it should do someting
      if(posn_desired_3 != posn_actual_3):
        //if position is not where you want it to be, step one time
        if(posn_desired_3 != posn_actual_3):
        //if position is not where you want it to be, step one time
        ((posn_desired_3 - posn_actual_3) > 0){
          mySteppers[0]::stepCW(1);
        }
        ((posn_desired_3 - posn_actual_3) < 0){
          mySteppers[0]::stepCCW(1);
        }
        ((posn_desired_3 - posn_actual_3) == 0){
          std::cout << "motor_3 is at desired posn" << endl;
        }
      previousMotor1Time = currentMotor1Time;
    }
}
