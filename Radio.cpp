/*
  Radio.cpp
  Created by Alan T. Grier, 23 September 2019.
*/

#include "Radio.h"

// Wrapper around RadioHead Driver
Radio::Radio(int address, RH_RF69 &driver, int reset_pin):_driver(driver)
{
  _address = address;
  _reset_pin = reset_pin;
}

// Wrapper around RadioHead init method. Must be called AFTER Serial.begin()
void Radio::init(float frequency, uint8_t *key)
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
  _driver.setEncryptionKey(key);
}

// Send message of length to address
bool Radio::send(uint8_t *message, uint8_t length, uint8_t to)
{
  _driver.setHeaderTo(to);
  return _driver.send(message, length);
}

// Receive message of length from address
bool Radio::receive(uint8_t *message, uint8_t *length, uint8_t *from)
{
  if (_driver.recv(message, length))
  {
    if (from)
      *from = _driver.headerFrom();
    return true;
  }
  return false;
}

// Check if messages are available
bool Radio::available()
{
  return _driver.available();
}
