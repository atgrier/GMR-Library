/*
  Locomotive.h
  Created by Alan T. Grier, 23 September 2019.
*/

#ifndef Locomotive_h
#define Locomotive_h

class Locomotive
{
private:
public:
    Locomotive(int address);
    void reverse();    // Change direction to -1
    void forward();    // Change direction to 1
    int ADDRESS;       // Positive number
    int speed = 0;     // Positive number from 0 to 255
    int direction = 1; // -1 for reverse, +1 for forward
};

#endif
