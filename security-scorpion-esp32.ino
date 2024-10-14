#include "WiFiConfig.h"
#include "ApiConfig.h"
#include "MessageHandlers.h"
#include "DeviceHandlers.h"
#include "EepromManager.h"

void setup() {
  Serial.begin(115200);

  // Iniciar EEPROM y configurar valores por defecto si es necesario
  EEPROM.begin(512);
  if (EEPROM.read(0) == 255) {
    initializeDeviceSettings();
  }

  pinMode(RESTART_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  setupWiFi();
  updateDeviceConfig();
}

void loop() {
  handleClient();
  handleWeb1Socket(webSocket);
}
