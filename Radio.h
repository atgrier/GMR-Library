/*
    Locomotive.h
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
  void init(float frequency, uint8_t *key);                       // Initialise radio
  bool send(uint8_t *message, uint8_t length, uint8_t to);        // Send message
  bool receive(uint8_t *message, uint8_t *length, uint8_t *from); // Reveive message
  bool available();                                               // Check messages

private:
  int _address;     // Positive number
  RH_RF69 &_driver; // Radio driver
  int _reset_pin;   // Radio reset pin
};

#endif
