#include <Arduino.h>
#include "Stepper.h"

// bicep 
#define pulse_1 3
#define dir_1 4
// bicep 
#define pulse_2 5
#define dir_2 6
// shoulder 
#define pulse_3 7
#define dir_3 8

// enable all steppers
#define enable 13
// steps per rev:
#define STEPSPERREV 4000
int PULpin[3] = {pulse_1, pulse_2, pulse_3};
int DIRpin[3] = {dir_1, dir_2, dir_3};

// make 3 stepper objects
// Stepper::Stepper(int _enable, int _pulse, int _dir, int _steps) 

Stepper mySteppers[3] = {Stepper(enable, PULpin[0], DIRpin[0], STEPSPERREV,),
                         Stepper(enable, PULpin[1], DIRpin[1], STEPSPERREV,),
                         Stepper(enable, PULpin[2], DIRpin[2], STEPSPERREV,)};

void setup() {
  // set up serial jic we need to monitor anything
  Serial.begin(9600);
  Serial.println("initialized");
  // stepper constructor should take care of all the pin initializations

}

void loop() {

    /*
      TODO: 
        * set up encoders --> they will be posn_actual's
        * serial input --> input a nx6 array of joint angles (degrees)
        *   currently this is a CSV containing a bunch of joint angles to go through 
        *   one at a time (they are all one degree at a time)
    */

/*
Read Serial
*/

while (!Serial.available());
x = Serial.read

int position_d[6] = [];
int position_measured[6] = [];


    if(position_d[0] != position_measured[0]):
      //if position is not where you want it to be, step one time
      ((position_d[0] - position_measured[0]) > 0){
        mySteppers[0]::stepCW(1);
      }
      ((position_d[0] - position_measured[0]) < 0){
        mySteppers[0]::stepCCW(1);
      }
      ((position_d[0] - position_measured[0]) == 0){
        std::cout << "motor_1 is at desired posn" << endl;
      }
  
    if(position_d[1] != position_measured[1]):
      //if position is not where you want it to be, step one time
      if(position_d[1] != position_measured[1]):
      //if position is not where you want it to be, step one time
      ((position_d[1] - position_measured[1]) > 0){
        mySteppers[1]::stepCW(1);
      }
      ((position_d[1] - position_measured[1]) < 0){
        mySteppers[1]::stepCCW(1);
      }
      ((position_d[1] - position_measured[1]) == 0){
        std::cout << "motor_2 is at desired posn" << endl;
      }
    
    if(position_d[2] != position_measured[2]):
      //if position is not where you want it to be, step one time
      if(position_d[2] != position_measured[2]):
      //if position is not where you want it to be, step one time
      ((position_d[2] - position_measured[2]) > 0){
        mySteppers[2]::stepCW(1);
      }
      ((position_d[2] - position_measured[2]) < 0){
        mySteppers[2]::stepCCW(1);
      }
      ((position_d[2] - position_measured[2]) == 0){
        std::cout << "motor_3 is at desired posn" << endl;
      }
}
