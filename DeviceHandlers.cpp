#include "DeviceHandlers.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "Config.h"

void deviceActivated() {
  Serial.println("Dash");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);
  digitalWrite(LED_PIN, LOW);
}

void initializeDeviceSettings() {

  // Escribir nombre por defecto
  String defaultName = NAME_DEVICE_DEFAULT;
  storeDeviceName(defaultName);

  // Escribir IP por defecto
  IPAddress defaultIp = LOCAL_IP_DEFAULT;
  storeIpAddress(defaultIp);

  EEPROM.commit();
  Serial.println("Configuración por defecto guardada en EEPROM");
}

void resetToDefaultSettings() {
  // Escribir nombre por defecto
  String defaultName = NAME_DEVICE_DEFAULT;
  storeDeviceName(defaultName);

  // Escribir IP por defecto
  IPAddress defaultIp = LOCAL_IP_DEFAULT;
  storeIpAddress(defaultIp);

  EEPROM.commit();
  Serial.println("Configuración restablecida a valores por defecto en EEPROM");
}

String getStoredDeviceName() {
  String deviceName;
  for (int i = 1; i < 51; i++) {
    char c = EEPROM.read(i);
    if (c == '\0') break;
    deviceName += c;
  }
  return deviceName;
}

IPAddress getStoredIpAddress() {
  IPAddress ip;
  ip[0] = EEPROM.read(51);
  ip[1] = EEPROM.read(52);
  ip[2] = EEPROM.read(53);
  ip[3] = EEPROM.read(54);
  return ip;
}

void storeDeviceName(String name) {
  for (int i = 0; i < name.length(); i++) {
    EEPROM.write(1 + i, name[i]);
  }
  EEPROM.write(1 + name.length(), '\0');  // End string
  EEPROM.commit();
}

void storeIpAddress(IPAddress ip) {
  EEPROM.write(51, ip[0]);
  EEPROM.write(52, ip[1]);
  EEPROM.write(53, ip[2]);
  EEPROM.write(54, ip[3]);
  EEPROM.commit();
}
