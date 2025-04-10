#include "DeviceHandlers.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "Config.h"
#include "EepromManager.h"

unsigned long activationTime = 0;
bool isActivated = false;

void blinkLED(int pin, int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);  // Encender LED
    delay(delayTime);
    digitalWrite(pin, LOW);  // Apagar LED
    delay(delayTime);
  }
}

void deviceActivated() {
  Serial.println("Dispositivo Activado");
  blinkLED(LED_GREEN, 1, 2000);
  digitalWrite(LED_PIN, HIGH);
  isActivated = true;
  activationTime = millis();
}

void deviceDisabled() {
  Serial.println("Dispositivo Desactivado");
  blinkLED(LED_GREEN, 1, 2000);
  digitalWrite(LED_PIN, LOW);
  isActivated = false;
}

void checkAutoDisable() {
  if (isActivated && millis() - activationTime >= 120000) {
    deviceDisabled();
    Serial.println("⏳ Desactivado automáticamente tras 2 minutos.");
  }
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
