/*
  Radio.cpp
  Created by Alan T. Grier, 23 September 2019.
*/

#include "Radio.h"

// Wrapper around RadioHead Driver
Radio::Radio(int address, RH_RF69 &driver, int reset_pin) : _driver(driver)
{
  _address = address;
  _reset_pin = reset_pin;
}

// Wrapper around RadioHead init method. Must be called AFTER Serial.begin()
void Radio::init(float frequency)
{
  Serial.flush();
  pinMode(_reset_pin, OUTPUT);
  digitalWrite(_reset_pin, LOW);
  digitalWrite(_reset_pin, HIGH);
  delay(10);
  digitalWrite(_reset_pin, LOW);
  delay(10);

  _driver.init();
  _driver.setThisAddress(_address);
  _driver.setHeaderFrom(_address);

  _driver.setFrequency(frequency);
  _driver.setTxPower(20, true);
}

// Send message of length to address
bool Radio::send(char *message, uint8_t to)
{
  _driver.setHeaderTo(to);
  return _driver.send((uint8_t *)message, strlen(message) + 1);
}

// Receive message of length from address
bool Radio::receive(char *message, uint8_t *from, uint8_t *len)
{
  if (available())
  {
    if (_driver.recv((uint8_t *)message, len))
    {
      if (from)
        *from = _driver.headerFrom();
      return true;
    }
    return false;
  }
}

// Check if messages are available
bool Radio::available()
{
  return _driver.available();
}
