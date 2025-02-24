#ifndef EEPROM_MANAGER_H
#define EEPROM_MANAGER_H

#include <Arduino.h>
#include <EEPROM.h>

void initializeDeviceSettings();
void resetToDefaultSettings();

String getStoredDeviceName();
IPAddress getStoredIpAddress();
String getStoredSSID();
String getStoredPassword();

void storeDeviceName(String name);
void storeIpAddress(IPAddress ip);
void storeSSID(String ssid); 
void storePassword(String password);

#endif
