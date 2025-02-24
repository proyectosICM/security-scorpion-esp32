#include "EepromManager.h"
#include "Config.h"

void initializeDeviceSettings() {

  // Leer el primer byte de la EEPROM para verificar si ya fue inicializada
  /*
  if (EEPROM.read(0) != 0xFF) {
    Serial.println("EEPROM ya inicializada. No se sobrescriben valores.");
    return;
  }
*/
  Serial.println("initialize");
  // Write default name
  String defaultName = NAME_DEVICE_DEFAULT;
  storeDeviceName(defaultName);

  // Write default IP
  IPAddress defaultIp = LOCAL_IP_DEFAULT;
  storeIpAddress(defaultIp);

  String defaultSSID = WIFI_SSID_DEFAULT;
  storeSSID(defaultSSID);

  String defaulPassword = WIFI_PASSWORD_DEFAULT;
  storePassword(defaulPassword);

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

  String defaultSSID = WIFI_SSID_DEFAULT;
  storeSSID(defaultSSID);

  String defaulPassword = WIFI_PASSWORD_DEFAULT;
  storePassword(defaulPassword);

  EEPROM.commit();
  Serial.println("Configuration reset to default values in EEPROM");
}

void storeDeviceName(String name) {
  if (name.length() > 49) {
    name = name.substring(0, 49);
  }

  // Escribir el nuevo nombre en la EEPROM
  for (int i = 0; i < name.length(); i++) {
    EEPROM.write(1 + i, name[i]);
  }

  // Rellenar con '\0' el resto de los 50 bytes disponibles
  for (int i = name.length(); i < 50; i++) {
    EEPROM.write(1 + i, '\0');
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

/* Unused */
void storeServerPort(uint16_t port) {
  EEPROM.write(55, port >> 8);    // Byte alto
  EEPROM.write(56, port & 0xFF);  // Byte bajo
  EEPROM.commit();
}

uint16_t getStoredServerPort() {
  uint16_t port = (EEPROM.read(55) << 8) | EEPROM.read(56);
  return port;
}
/* */

void storeSSID(String ssid) {
  if (ssid.length() > 32) {  // Limitar el tamaño del SSID
    ssid = ssid.substring(0, 32);
  }

  // Guardar cada carácter en la EEPROM
  for (int i = 0; i < ssid.length(); i++) {
    EEPROM.write(57 + i, ssid[i]);  // Guardar desde la posición 57
  }

  // Rellenar con '\0' para eliminar residuos si el SSID anterior era más largo
  for (int i = ssid.length(); i < 32; i++) {
    EEPROM.write(57 + i, '\0');
  }

  EEPROM.commit();
}

String getStoredSSID() {
  String ssid;
  for (int i = 57; i < 57 + 32; i++) {  // Leer hasta 32 caracteres
    char c = EEPROM.read(i);
    if (c == '\0') break;  // Detener si encuentra el fin de la cadena
    ssid += c;
  }
  return ssid;
}

void storePassword(String password) {
  if (password.length() > 63) {  // Limitar el tamaño de la contraseña
    password = password.substring(0, 63);
  }

  // Guardar cada carácter en la EEPROM
  for (int i = 0; i < password.length(); i++) {
    EEPROM.write(89 + i, password[i]);  // Guardar desde la posición 89
  }

  // Rellenar con '\0' si la nueva contraseña es más corta que la anterior
  for (int i = password.length(); i < 63; i++) {
    EEPROM.write(89 + i, '\0');
  }

  EEPROM.commit();
}

String getStoredPassword() {
  String password;
  for (int i = 89; i < 89 + 63; i++) {  // Leer hasta 63 caracteres
    char c = EEPROM.read(i);
    if (c == '\0') break;  // Detener si encuentra el fin de la cadena
    password += c;
  }
  return password;
}