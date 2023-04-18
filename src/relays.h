#ifndef RELAYS_H
#define RELAYS_H

#include <Arduino.h>

class Relays
{
public:
  const int RELAY_PIN1 = 15;
  const int RELAY_PIN2 = 14;
  const int RELAY_PIN3 = 4;
  const int RELAY_PIN4 = 13;

  Relays();
  void init();
  void setRelays(uint8_t relayStateChar);
};

#endif