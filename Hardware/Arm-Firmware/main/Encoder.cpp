#include "Encoder.h"

Encoder::Encoder(int _A, int _B, long _resolution) {
    A = _A;
    B = _B;
    pulsesperrev = _resolution;

    tick = 0;
    tickB = 0;
    countTick = 0.0;
    prevTick = 0;
    angle = 0.0;

    pinMode(A, INPUT);
    pinMode(B, INPUT);

}

void Encoder::readPulse() {
    tick = digitalRead(A);
    tickB = digitalRead(B);
    
    if(tick != prevTick) {
        if(tick != tickB) {
            countTick = countTick + tick;
            prevTick = tick;
        } else {
            countTick = countTick - tick;
            prevTick = tick;
        }
        updateAngle();
        // Serial.print(angle);
        // Serial.println(countTick);
    }
    
}

long Encoder::getAngle() {
    return angle;
}

void Encoder::updateAngle() {
    angle = 360.0 * countTick / pulsesperrev;
    Serial.println(angle, 5);
}
