#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder {
    public:
        Encoder(int, int, long);
        void readPulse();
        long getAngle();
        
    private:
        int A;
        int B;
        long pulsesperrev;

        char tick;
        char tickB;
        long countTick;
        char prevTick;
        float angle;

        void updateAngle();

};

#endif
