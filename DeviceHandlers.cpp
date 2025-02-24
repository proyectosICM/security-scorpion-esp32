#include "DeviceHandlers.h"
#include <Arduino.h>
#include <EEPROM.h>
#include "Config.h"

void deviceActivated() {
  Serial.println("Dispositivo Accionado");
  digitalWrite(LED_PIN, HIGH);
  delay(5000);
  digitalWrite(LED_PIN, LOW);
}
