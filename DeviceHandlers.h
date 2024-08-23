#ifndef DEVICE_HANDLERS_H
#define DEVICE_HANDLERS_H
#include <Arduino.h>
#include <Arduino.h>
#include <EEPROM.h>

void deviceActivated();
void initializeDeviceSettings(); 
void resetToDefaultSettings();
String getStoredDeviceName();
IPAddress getStoredIpAddress();
void storeDeviceName(String name);
void storeIpAddress(IPAddress ip);
#endif
