#pragma once
#include <wiringPi.h>

class AlphaBot {
private:
	int IN1, IN2, IN3, IN4, ENA, ENB;
public:
    AlphaBot(int in1 = 12, int in2 = 13, int ena = 6, int in3 = 20, int in4 = 21, int enb = 26) :
        IN1(in1), IN2(in2), IN3(in3), IN4(in4), ENA(ena), ENB(enb) {
        wiringPiSetupGpio();
        pinMode(IN1, OUTPUT);
        pinMode(IN2, OUTPUT);
        pinMode(IN3, OUTPUT);
        pinMode(IN4, OUTPUT);
        pinMode(ENA, OUTPUT);
        pinMode(ENB, OUTPUT);
    }
	
    void forward();
	
    void stop();
	
    void left();
	
    void right();
	
};
