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
Stepper mySteppers[3] = {Stepper(STEPSPERREV, enable, pulse_1, dir_1),
                        Stepper(STEPSPERREV, enable, pulse_2, dir_2),
                        Stepper(STEPSPERREV, enable, pulse_3, dir_3)};

//void setup() {
//  Serial.begin(9600);
//  pinMode(LED_BUILTIN, OUTPUT);
//  pinMode(7, OUTPUT);
//  pinMode (2, INPUT_PULLUP); // arduino interrupt pin
//  pinMode (3, INPUT_PULLUP); // arduino interrupt pin
//  mcp_pin2.start(2); // start instance of MCP23017
//  mcp_pin3.start(3); // start instance of MCP23017
//  myStepper.connectMCP();
//  myStepper.enableMotor();
//  myStepper.setSpeed(200);
//}

void setup() {
  Serial.begin(9600);
  pinMode(pulse_1, OUTPUT);
  pinMode(dir_1, OUTPUT);
  pinMode(pulse_2, OUTPUT);
  pinMode(dir_2, OUTPUT);
  pinMode(pulse_2, OUTPUT);
  pinMode(dir_2, OUTPUT);
  pinMode(enable, OUTPUT);
  
  digitalWrite(enable_1, HIGH); //just set all the motors to on
  Serial.println("initialized");

}

// ms time intervals for running motors (ms)
long Motor1Interval = 10;
long Motor2Interval = 10;
long Motor2Interval = 10;

void step(unsigned long int steps, int pulse_pin, bool dir_pin) {
    unsigned long lastStepTime = 0;
    unsigned long int pulses = steps * 2;
    
    while(pulses > 0) {
        unsigned long time = micros();
        if (time - lastStepTime >= 2) {
            lastStepTime = time;
            pulses--;
            if(pulses % 2 == 0) {
                digitalWrite(pulse_pin, HIGH);
            } else {
                digitalWrite(pulse_pin, LOW);
            }
        }
    }
    Serial.println("Finished stepping.");
}

void loop() {

    // attempting to have the motors move in such a way it appears simultaneous
    unsigned long currentMotor1Time = millis();
    unsigned long currentMotor2Time = millis();
    unsigned long currentMotor3Time = millis();
  
    if(currentMotor1Time - previousMotor1Time > Motor1Interval){
      // if more than 10 ms diff between when you last moved motor then check if it should do someting
      if(posn_desired_1 != posn_actual_1):
        //if position is not where you want it to be, step one time
        
      previousMotor1Time = currentMotor1Time;
    }
  
    if(currentMotor2Time - previousMotor2Time > Motor2Interval){
      // if more than 10 ms diff between when you last moved motor then check if it should do someting
      if(posn_desired_1 != posn_actual_1):
        //if position is not where you want it to be, step one time
      previousMotor1Time = currentMotor1Time;
    }
    
    if(currentMotor3Time - previousMotor3Time > Motor3Interval){
      // if more than 10 ms diff between when you last moved motor then check if it should do someting
      if(posn_desired_1 != posn_actual_1):
        //if position is not where you want it to be, step one time
      previousMotor1Time = currentMotor1Time;
    }
}
