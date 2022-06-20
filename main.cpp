#include "mbed.h"
#include "bbcar.h"
#include <cmath>

#define CENTER_BASE 1500
BufferedSerial pc(USBTX, USBRX);

Ticker encoder_ticker;
PwmOut pin5(D10), pin6(D11);
BusInOut qti(D4, D5, D6, D7);
DigitalIn encoder(D13);
DigitalInOut pin10(D12);

int pattern;
parallax_ping  pin(pin10);
volatile int steps;
volatile int last;

void encoder_control() {
   int value = encoder;
   if (!last && value) steps++;
   last = value;
}

void servo_control(int speed) {
    if (speed > 200)       speed = 200;
    else if (speed < -200) speed = -200;
    pin5 = (CENTER_BASE + speed)/20000.0f;
    pin6 = (CENTER_BASE + speed)/20000.0f;
}

int main()
{
    float width, width1, width2;
    float distance = (float)pin;

    steps = 0;
    last = 0;
    pc.set_baud(9600);
    while ((float)pin<100) {
        servo_control(20);
        ThisThread::sleep_for(100ms);
    }
    width1 = steps;

    steps = 0;
    last = 0;
    while((float)pin<100) {
        servo_control(-20);
        ThisThread::sleep_for(100ms);
    }
    width2 = steps;

    width = (sin(width1/6.25) + sin(width2/6.25))*distance;

    printf("the width is %f", width);
}