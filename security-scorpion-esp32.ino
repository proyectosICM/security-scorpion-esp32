#include <WebSocketsClient.h>

#include <WiFiClient.h>
#include "WiFiConfig.h"
#include "MessageHandlers.h"


void setup() {
  Serial.begin(115200);
    setupWiFi();
}

void loop() {
  // Manejar la comunicación por WebSocket
  webSocket.loop();

  // Manejar la comunicación local por WiFi
  handleClient();
}