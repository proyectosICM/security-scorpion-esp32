#include "DeviceHandlers.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "Config.h"
#include "EepromManager.h"

void deviceActivated() {
  Serial.println("Dispositivo Accionado");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);
  digitalWrite(LED_PIN, LOW);
}

void deviceChangeWifiCredentials(const String& message) {
  int separatorIndex = message.indexOf(":");

  if (separatorIndex == -1) {
    Serial.println("❌ Formato incorrecto, se esperaba 'SSID:Password'");
    return;
  }

  String ssid = message.substring(0, separatorIndex);
  String password = message.substring(separatorIndex + 1);

  ssid.trim();
  password.trim();

  Serial.println("SSID: " + ssid);
  Serial.println("PASSWORD: " + password);

  storeSSID(ssid);
  storePassword(password);

  Serial.println("✅ Credenciales guardadas en EEPROM. Reiniciando...");
  delay(1000);

  ESP.restart();
}
