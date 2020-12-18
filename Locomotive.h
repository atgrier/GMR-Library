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
    int ADDRESS;
    int speed = 0;
    int direction = 1;
};

#endif
