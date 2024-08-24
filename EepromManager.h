#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

void initializeDeviceSettings();
void resetToDefaultSettings();

String getStoredDeviceName();
IPAddress getStoredIpAddress();

void storeDeviceName(String name);
void storeIpAddress(IPAddress ip);

#endif
