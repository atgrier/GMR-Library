/*
  Locomotive.h
  Created by Alan T. Grier, 23 September 2019.
*/

#include "Locomotive.h"

Locomotive::Locomotive(int address)
{
    ADDRESS = address;
}

// Set locomotive's direction to -1 (reverse)
void Locomotive::reverse()
{
    direction = -1;
}

// Set locomotive's direction to 1 (forward)
void Locomotive::forward()
{
    direction = 1;
}
