/*
  Locomotive.h
  Created by Alan T. Grier, 23 September 2019.
*/

#include <arduino.h>
#include "Locomotive.h"

Locomotive::Locomotive(int address, int ledPin, RHReliableDatagram *manager)
{
    _address = address;
    _ledPin = ledPin;
    _manager = manager;
}

// Set locomotive's direction to -1 (reverse)
void Locomotive::reverse()
{
    _direction = -1;
}

// Set locomotive's direction to 1 (forward)
void Locomotive::forward()
{
    _direction = 1;
}

// Set the speed of the locomotive
void Locomotive::setSpeed(int speed)
{
    _speed = speed;
}

// Send throttle command with current speed and direction
void Locomotive::sendThrottle()
{
    char pdata[3];
    pdata[0] = 't';        // Throttle
    pdata[1] = _speed;     // Speed
    pdata[2] = _direction; // Direction
    _manager->sendto((uint8_t *)pdata, strlen(pdata) + 1, _address);
}

// Send E-Stop command
void Locomotive::sendEStop()
{
    char pdata[1];
    pdata[0] = 'e'; // E-Stop
    _manager->sendto((uint8_t *)pdata, strlen(pdata) + 1, _address);
}
