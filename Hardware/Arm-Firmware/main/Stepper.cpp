#include "Stepper.h"

// Potentially useful example of Non-Blocking Stepper motor driver
// https://github.com/reven/Unistep2/blob/master/src/Unistep2.cpp
// I'd reccommend starting by implementing the stepper motor functionality
// as blocking functions since this is easier

Stepper::Stepper(int _enable, int _pulse, int _dir, int _steps) {
    Serial.println("made it to stepper constructor");
    enable = _enable;
    pulse = _pulse;
    dir = _dir;
    stepsperrev = _steps;
    currentStep = 0;
    pinMode(enable, OUTPUT);
    pinMode(pulse, OUTPUT);
    pinMode(dir, OUTPUT);

    
}

void Stepper::connectMCP() {
    MCP23017::mcp_instances[0] -> mcpPinMode(enable, OUTPUT);
    MCP23017::mcp_instances[0] -> mcpPinMode(pulse, OUTPUT);
    MCP23017::mcp_instances[0] -> mcpPinMode(dir, OUTPUT);
}

void Stepper::enableMotor() {
    //digitalWrite(enable, HIGH);
    MCP23017::mcp_instances[0] -> mcpWrite(enable, HIGH);
    //Serial.println("Enabled motor.");
}

void Stepper::disableMotor() {
    //digitalWrite(enable, LOW);
    MCP23017::mcp_instances[0] -> mcpWrite(enable, LOW);
}

// Speed should be angular speed in degrees/s
// stepdelay = time in microseconds seconds taken to travel two steps?
void Stepper::setSpeed(int speed) {
    stepdelay = 2;
    //stepdelay =  (360 * 1000000 / (2 * (unsigned long) speed * (unsigned long) stepsperrev));
    // Serial.print("step delay: ");
    // Serial.println(stepdelay);
    // Serial.print("steps: ");
    // Serial.println(stepsperrev);
    // Serial.print("speed: ");
    // Serial.println(speed);

}

void Stepper::moveToAngle(int angle) {
    unsigned long int steps = stepsperrev * angle / 360;
    if (steps > currentStep) {
        stepCW(steps - currentStep);
    } else {
        stepCCW(currentStep - steps);
    }
    currentStep = steps;
}

void Stepper::step(unsigned long int steps) {
    unsigned long lastStepTime = 0;
    unsigned long int pulses = steps * 2;
    while(pulses > 0) {
        unsigned long time = micros();
        if (time - lastStepTime >= stepdelay) {
            lastStepTime = time;
            pulses--;
            if(pulses % 2 == 0) {
                MCP23017::mcp_instances[0] -> mcpWrite(pulse, HIGH);
            } else {
                MCP23017::mcp_instances[0] -> mcpWrite(pulse, LOW);
            }
        }
    }
    //Serial.print("Finished stepping.");
}

void Stepper::stepCW(unsigned long int steps) {
    MCP23017::mcp_instances[0] -> mcpWrite(dir, HIGH);
    step(steps);
}

void Stepper::stepCCW(unsigned long int steps) {
    MCP23017::mcp_instances[0] -> mcpWrite(dir, LOW);
    step(steps);
}

void Stepper::test() {
    MCP23017::mcp_instances[0] -> mcpWrite(pulse, HIGH);
    Serial.println("in test.");
    delay(1000);
    MCP23017::mcp_instances[0] -> mcpWrite(pulse, LOW);
    delay(1000);
    stepCW(600);
}
