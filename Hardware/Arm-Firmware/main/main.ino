#include <AccelStepper.h>
#include <MultiStepper.h>

#include <Arduino.h>
#include "Stepper.h"
#include <ros.h>
#include <std_msgs/Float64.h>
#include <ob1_arm_hw_interface/armCmd.h>
#include <ob1_arm_hw_interface/armState.h>

ros::NodeHandle nh;

uint32_t rcv_cnt;
int num_joints;

ob1_arm_hw_interface::armState armState;
ros::Publisher p("/arduino/armState", &armState);

//callback function called when new arm cmd received
void armCmdCb( const ob1_arm_hw_interface::armCmd &msg){
  rcv_cnt++;
  num_joints = msg.num_joints;
  digitalWrite(13, HIGH-digitalRead(13));   // blink the led on rcv
  
  armState.msg_rcv_ctr = rcv_cnt;
  for(int i = 0; i < num_joints; i++)
  {
    armState.angle[i] = msg.angle[0];
    armState.vel[i] = msg.vel[0];
  }
  
}

ros::Subscriber<ob1_arm_hw_interface::armCmd> s("/arduino/armCmd", &armCmdCb);

ob1_arm_hw_interface::armState armState;
ros::Subscriber<ob1_arm_hw_interface::armCmd> s("/arduino/armCmd", &armCmdCb);
ros::Publisher p("/arduino/armState", &armState);

// bicep 
#define stepPin_1 3
#define dirPin_1 4
// bicep 
#define stepPin_2 5
#define dirPin_2 6
// shoulder 
#define stepPin_3 7
#define dirPin_3 8

// steps per rev:
#define STEPSPERREV 4000

void setup() {
  // set up serial jic we need to monitor anything
  Serial.begin(115200); // read
  Serial.println("initialized");
  // stepper constructor should take care of all the pin initializations
  rcv_cnt = 0;
  num_joints = 0;
  nh.initNode();
  nh.advertise(p);
  nh.subscribe(s);

  // instantiate steppers
  AccelStepper stepper_1(AccelStepper::DRIVER, stepPin_1, dirPin_1);
  AccelStepper stepper_2(AccelStepper::DRIVER, stepPin_2, dirPin_2);
  AccelStepper stepper_3(AccelStepper::DRIVER, stepPin_3, dirPin_3);

  // set parameters for the steppers
  stepper1.setMaxSpeed(200.0);
  stepper1.setAcceleration(100.0);

  stepper2.setMaxSpeed(200.0);
  stepper2.setAcceleration(100.0);

  stepper3.setMaxSpeed(200.0);
  stepper3.setAcceleration(100.0);
}

void loop() {

  p.publish( &armState );
  nh.spinOnce();
  delay(10); // purpose of delay?
  
  for(int i = 0; i < num_joints; i++){
    armState.angle[i] = 0.3;
    armState.vel[i] = 0;
  }
  
  p.publish( &armState );
  nh.spinOnce();
  delay(10);
  for(int i = 0; i < num_joints; i++){
    position_goal[i] =  armState.angle[i]
  }

// move joints based on position_goal
steppers.moveTo(position_goal);
steppers.setSpeed(50); //might need to set manually
steppers.runSpeedToPosition(); // Blocks until all are in position

}
