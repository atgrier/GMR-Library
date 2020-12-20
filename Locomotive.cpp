/*
  Locomotive.h
  Created by Alan T. Grier, 23 September 2019.
*/

#include "Locomotive.h"

Locomotive::Locomotive(int address)
{
    ADDRESS = address;
}

void Locomotive::reverse()
{
  direction = -1;
}

void Locomotive::forward()
{
  direction = 1;
}
