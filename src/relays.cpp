#include "relays.h"

Relays::Relays() {}

void Relays::init()
{
  pinMode(this->RELAY_PIN1, OUTPUT);
  pinMode(this->RELAY_PIN2, OUTPUT);
  pinMode(this->RELAY_PIN3, OUTPUT);
  pinMode(this->RELAY_PIN4, OUTPUT);

  digitalWrite(this->RELAY_PIN1, LOW);
  digitalWrite(this->RELAY_PIN2, LOW);
  digitalWrite(this->RELAY_PIN3, LOW);
  digitalWrite(this->RELAY_PIN4, LOW);
}

void Relays::setRelays(uint8_t relayStateChar) /// relayStateChar -> 0b10110000 (first 4 digits of the char are important)
{
  uint8_t downlinkRelayState = relayStateChar & 0b11110000; /// this will set the relays states properly, in the user's desired state

  // Update the state of all the relays based on the downlink value
  digitalWrite(this->RELAY_PIN1, (downlinkRelayState & 0b10000000) != 0);
  digitalWrite(this->RELAY_PIN2, (downlinkRelayState & 0b01000000) != 0);
  digitalWrite(this->RELAY_PIN3, (downlinkRelayState & 0b00100000) != 0);
  digitalWrite(this->RELAY_PIN4, (downlinkRelayState & 0b00010000) != 0);
}

void Relays::printRelaysState(uint8_t & currChar)
{
  String binaryStr = String(currChar, BIN);
  for (int i = 0; i < 8 - binaryStr.length(); i++)
  {
    Serial.print("0");
  }
  for (int i = 0; i < binaryStr.length(); i++)
  {
    Serial.print(binaryStr[i]);
  }
  Serial.println();
}