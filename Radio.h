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
    Radio(int address, RHGenericDriver* driver);
    bool send(uint8_t* message, uint8_t length, uint8_t to); // Send message
    bool receive(uint8_t* message, uint8_t* length, uint8_t* from, uint8_t* to,
                 uint8_t* id, uint8_t* flags); // Reveive message

private:
    int _address; // Positive number
    RHGenericDriver* _driver; // Radio driver
};

#endif
