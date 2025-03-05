#ifndef DEVICE_HANDLERS_H
#define DEVICE_HANDLERS_H
#include <Arduino.h>
#include <Arduino.h>
#include <EEPROM.h>

void deviceActivated();
void deviceChangeWifiCredentials(const String& message);
#endif
