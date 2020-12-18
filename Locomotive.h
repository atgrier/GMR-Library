#ifndef Locomotive_h
#define Locomotive_h

class Locomotive
{
private:
public:
    Locomotive(int address);
    int ADDRESS;
    int speed = 0;
    int direction = 1;
};
