/*
    Radio.h
    Created by Alan T. Grier, 23 September 2019.
*/

#ifndef Radio_h
#define Radio_h

#include <Arduino.h>
#include <RH_RF69.h>

class Radio
{
public:
  Radio(int address, RH_RF69 &driver, int reset_pin);
  void init(float frequency);                               // Initialise radio
  bool send(char *message, uint8_t to);                     // Send message
  bool receive(char *message, uint8_t *from, uint8_t *len); // Reveive message
  bool available();                                         // Check messages

private:
  int _address;     // Positive number
  RH_RF69 &_driver; // Radio driver
  int _reset_pin;   // Radio reset pin
};

#endif
