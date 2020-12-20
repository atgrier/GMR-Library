/*
  Locomotive.h
  Created by Alan T. Grier, 23 September 2019.
*/

#ifndef Locomotive_h
#define Locomotive_h

#include <RHReliableDataGram.h>

class Locomotive
{
public:
    Locomotive(int address, int ledPin, RHReliableDatagram *manager);
    void reverse();           // Change direction to -1
    void forward();           // Change direction to 1
    void setSpeed(int speed); // Set the speed of the locomotive
    void sendThrottle();      // Send throttle command with current speed and direction
    void sendEStop();         // Send E-Stop command
    int speed() { return _speed; }
    int direction() { return _direction; }
    int ledPin() { return _ledPin; }

private:
    int _speed = 0;               // Positive number from 0 to 255
    int _direction = 1;           // -1 for reverse, +1 for forward
    int _address;                 // Positive number
    int _ledPin;                  // Arudino PIN of status LED
    RHReliableDatagram *_manager; // Radio manager
};

#endif
