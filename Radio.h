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
  void init(float frequency);                 // Initialise radio
  bool send(char *message, uint8_t to);       // Send message
  bool receive(char *message, uint8_t *from); // Reveive message
  bool available();                           // Check messages

private:
  uint8_t _buf[RH_RF69_MAX_MESSAGE_LEN];
  uint8_t _len = sizeof(_buf);
  int _address;     // Positive number
  RH_RF69 &_driver; // Radio driver
  int _reset_pin;   // Radio reset pin
};

#endif
