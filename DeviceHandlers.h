#ifndef DEVICE_HANDLERS_H
#define DEVICE_HANDLERS_H
#include <Arduino.h>
#include <Arduino.h>
#include <EEPROM.h>

void blinkLED(int pin, int times, int delayTime);
void deviceActivated();
void deviceDisabled();
void checkAutoDisable();
void deviceChangeWifiCredentials(const String& message);
#endif
