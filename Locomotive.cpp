/*
  Locomotive.cpp
  Created by Alan T. Grier, 23 September 2019.
*/

#include "Locomotive.h"

LocomotiveReceiver::LocomotiveReceiver(int address, TwoPinMotor *motor, Lighting *light_cab, Radio *radio)
{
  _address = address;
  _motor = motor;
  _light_cab = light_cab;
  _radio = radio;
  _light_cab->On();
}

bool LocomotiveReceiver::parseRadio()
{
  char command;
  uint8_t from;
  if (_radio->receive(&command, &from))
  {
    //Serial.print("got request from : 0x");
    //Serial.print(from, HEX);
    //Serial.print(": ");
    // Serial.println(len);
    // Serial.println((char*)buf);
    parseCommand(&command);
  }
}

void LocomotiveReceiver::parseCommand(char *command)
{
  switch (command[0])
  {
  case 'e': // E-Stop
    _motor->disable(true);
    break;

  case 't': // Throttle
    throttle(command);
    break;

  case 'f': // Function
    function(command);
    break;
  }
}

void LocomotiveReceiver::shutDown(bool endless)
{
  _motor->disable(true);
  _light_cab->Off();
  while (endless)
    ;
}

void LocomotiveReceiver::throttle(char *command)
{
  int spd = (int)command[1];
  int dir = (int)command[2] == 1 ? 1 : -1;

  if (spd == -1)
    _motor->disable(true);
  else
    _motor->setSpeed(spd * dir);
}

void LocomotiveReceiver::function(char *command)
{
  0;
}

// Class containing methods to address the locomotive
LocomotiveController::LocomotiveController(int address, int ledPin, Radio *radio)
{
  _address = address;
  _ledPin = ledPin;
  pinMode(_ledPin, OUTPUT);
  _radio = radio;
}

// Set locomotive's direction to -1 (reverse)
void LocomotiveController::reverse()
{
  _direction = -1;
}

// Set locomotive's direction to 1 (forward)
void LocomotiveController::forward()
{
  _direction = 1;
}

// Set the speed of the locomotive
void LocomotiveController::setSpeed(int speed)
{
  _speed = speed;
}

// Send throttle command with current speed and direction
void LocomotiveController::sendThrottle()
{
  char pdata[3];
  pdata[0] = 't';                     // Throttle
  pdata[1] = _speed;                  // Speed
  pdata[2] = _direction == 1 ? 1 : 0; // Direction
  // Serial.print(pdata[0]);
  // Serial.print((int)pdata[1]);
  // Serial.println((int)pdata[2]);
  _radio->send(pdata, _address);
}

// Send E-Stop command
void LocomotiveController::sendEStop()
{
  char pdata[1];
  pdata[0] = 'e'; // E-Stop
  _radio->send(pdata, _address);
}

// Class for managing multiple locomotives controlled by a single physical controller
Controller::Controller(int led0, int led1, int max_speed, int num_locomotives,
                       LocomotiveController *locomotives)
{
  _locomotives = locomotives;
  _num_locomotives = num_locomotives;
  _led0 = led0;
  _led1 = led1;
  pinMode(_led0, OUTPUT);
  pinMode(_led1, OUTPUT);
  _maxSpeed = max_speed;
}

// Set the currently selected locomotive
void Controller::setCurrent(int current_train)
{
  _current = current_train;
}

// Send throttle commands to all locomotives
void Controller::sendThrottles()
{
  for (int i = 0; i < _num_locomotives; i++)
    _locomotives[i].sendThrottle();
}

// E-Stop all locomotives
void Controller::eStopAll()
{
  for (int i = 0; i < _num_locomotives; i++)
  {
    digitalWrite(_locomotives[i].ledPin(), LOW);
    _locomotives[i].setSpeed(0);
    _locomotives[i].forward();
  }

  for (int i = 0; i < 5; i++)
    for (int j = 0; j < _num_locomotives; j++)
      _locomotives[j].sendEStop();
}

// Set the curent locomotive's speed and direction, using the FORWARDS/REVERSE states
void Controller::setSpeed(int speed, int direction)
{
  _locomotives[_current].setSpeed(speed);
  if (direction == FORWARDS)
    _locomotives[_current].forward();
  else
    _locomotives[_current].reverse();
}

// Set indicator LED
void Controller::indicatorLED(int state, int previous = -1)
{
  if (state == FORWARDS)
  {
    digitalWrite(_led1, LOW);
    analogWrite(_led0, map(_current_speed(), 0, _maxSpeed, 0, 255));
    digitalWrite(_current_led(), (_current_speed() == _maxSpeed) ? HIGH : LOW);
  }

  else if (state == REVERSE)
  {
    digitalWrite(_led0, LOW);
    analogWrite(_led1, map(_current_speed(), 0, _maxSpeed, 0, 255));
    digitalWrite(_current_led(), (_current_speed() == _maxSpeed) ? HIGH : LOW);
  }

  else if (state == STOP)
  {
    digitalWrite(_led0, LOW);
    digitalWrite(_led1, LOW);
    digitalWrite(_current_led(), LOW);
  }

  else if (state == IDLE)
  {
    digitalWrite(_led0, LOW);
    digitalWrite(_led1, LOW);
  }

  else if (state == WARNING)
  {
    digitalWrite(_led0, HIGH);
    digitalWrite(_led1, HIGH);
  }

  else if (state == RUNNING)
  {
    if (previous == -1 || _locomotives[previous].speed() == 0)
      return;
    digitalWrite(_current_led(), HIGH);
  }

  else if (state == THROTTLE)
  {
    if (_current_dir() == -1)
      indicatorLED(REVERSE);
    else
      indicatorLED(FORWARDS);
  }
}
