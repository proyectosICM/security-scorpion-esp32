#include "EepromManager.h"
#include "Config.h"

void initializeDeviceSettings() {
  // Write default name
  String defaultName = NAME_DEVICE_DEFAULT;
  storeDeviceName(defaultName);

  // Write default IP
  IPAddress defaultIp = LOCAL_IP_DEFAULT;
  storeIpAddress(defaultIp);

  EEPROM.write(0, 0);
  EEPROM.commit();

  Serial.println("Default configuration saved in EEPROM");
}

void resetToDefaultSettings() {
  // Write default name
  String defaultName = NAME_DEVICE_DEFAULT;
  storeDeviceName(defaultName);

  // Write default IP
  IPAddress defaultIp = LOCAL_IP_DEFAULT;
  storeIpAddress(defaultIp);

  EEPROM.commit();
  Serial.println("Configuration reset to default values in EEPROM");
}

void storeDeviceName(String name) {
  if (name.length() > 49) {
    name = name.substring(0, 49);
  }

  for (int i = 0; i < name.length(); i++) {
    EEPROM.write(1 + i, name[i]);
  }

  EEPROM.write(1 + name.length(), '\0');
  EEPROM.commit();
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

void storeIpAddress(IPAddress ip) {
  EEPROM.write(51, ip[0]);
  EEPROM.write(52, ip[1]);
  EEPROM.write(53, ip[2]);
  EEPROM.write(54, ip[3]);
  EEPROM.commit();
}

IPAddress getStoredIpAddress() {
  IPAddress ip;
  ip[0] = EEPROM.read(51);
  ip[1] = EEPROM.read(52);
  ip[2] = EEPROM.read(53);
  ip[3] = EEPROM.read(54);
  return ip;
}
