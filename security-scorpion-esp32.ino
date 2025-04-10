#include "WiFiConfig.h"
#include "ApiConfig.h"
#include "MessageHandlers.h"
#include "DeviceHandlers.h"
#include "EepromManager.h"

void setup() {
  Serial.begin(115200);

  // Initialize EEPROM and set default values if necessary
  EEPROM.begin(512);
  if (EEPROM.read(0) == 255) {
    initializeDeviceSettings();
  }

  pinMode(RESTART_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  setupWiFi();
  updateDeviceConfig();
  //webSocket.onEvent(webSocketEvent);
}

void loop() {
  handleClient();
  handleWebSocket(webSocketClient);
  checkAutoDisable();
}
