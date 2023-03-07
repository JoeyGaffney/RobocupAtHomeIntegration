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
// Stepper.Stepper(int _enable, int _pulse, int _dir, int _steps) 

Stepper mySteppers[3] = {Stepper(enable, PULpin[0], DIRpin[0], STEPSPERREV),
                         Stepper(enable, PULpin[1], DIRpin[1], STEPSPERREV),
                         Stepper(enable, PULpin[2], DIRpin[2], STEPSPERREV)};

void setup() {
  // set up serial jic we need to monitor anything
  Serial.begin(115200); // read
  Serial.println("initialized");
  // stepper constructor should take care of all the pin initializations

}

void loop() {

    /*
      TODO: 
        * set up encoders --> they will be posn_actual's
        * serial input --> input a nx6 array of joint angles (degrees)
        *   currently this is produced by the input_sim.py script
        *   one at a time (they are all one degree at a time)
    */

byte trans_array[6];
int position_goal[6];
int position_measured[6];
double f; // tempvar for the byte -> float conversion

// populate goal
if(Serial.available() >= 6){
  for(int i = 0; i < 7; i++){
    // float x = static_cast<float>(Serial.read()); // read digit from serial, and covert it to a double
    trans_array[i] = (Serial.read());//x;
    memcpy( &f, trans_array, 8 );
    position_goal[i] = f;
  }

}

/*
Write serial to send current joint positions
*/


    if(position_goal[0] != position_measured[0]){
      //if position is not where you want it to be, step one time
      if((position_goal[0] - position_measured[0]) > 0){
        mySteppers[0].stepCW(1);
      }
      if((position_goal[0] - position_measured[0]) < 0){
        mySteppers[0].stepCCW(1);
      }
      if((position_goal[0] - position_measured[0]) == 0){
        Serial.println("motor_1 is in desired posn");
      }
    }
    if(position_goal[1] != position_measured[1]){
      //if position is not where you want it to be, step one time
      if((position_goal[1] - position_measured[1]) > 0){
        mySteppers[1].stepCW(1);
      }
      if((position_goal[1] - position_measured[1]) < 0){
        mySteppers[1].stepCCW(1);
      }
      if((position_goal[1] - position_measured[1]) == 0){
        Serial.println("motor_2 is in desired posn");
      }
    }
    
    if(position_goal[2] != position_measured[2]){
      //if position is not where you want it to be, step one time
      if((position_goal[2] - position_measured[2]) > 0){
        mySteppers[2].stepCW(1);
      }
      if((position_goal[2] - position_measured[2]) < 0){
        mySteppers[2].stepCCW(1);
      }
      if((position_goal[2] - position_measured[2]) == 0){
        Serial.println("motor_3 is in desired posn");
      }
    }

// send new joint positions
Serial.write(analogRead(A0));
}
