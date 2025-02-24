#include "WiFiConfig.h"
#include "MessageHandlers.h"
#include "WebSocketEvent.h"
#include <WebSocketsClient.h>
#include <HTTPClient.h>
#include <EEPROM.h>
#include "DeviceHandlers.h"
#include "EepromManager.h"


//   IPAddress localIp = getStoredIpAddress();

WiFiServer server(LOCAL_SERVER_PORT);
WebSocketsClient webSocket;

void setupWiFi() {
  String ssid = getStoredSSID();
  String password = getStoredPassword();
  
  if (!WiFi.config(LOCAL_IP_DEFAULT, GATEWAY, SUBNET, DNS1, DNS2)) {
    Serial.println("Failed to configure static IP");
  }

  WiFi.begin(ssid, password);
  Serial.println("Connecting to the WiFi network...");

  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(100);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("Connected to the WiFi network");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.begin();
    setupWebSocket(webSocket);
  } else {
    Serial.println("Could not connect to the WiFi network");
    resetToDefaultSettings();
    Serial.println("Reiniciando a configuracion por defecto");
    delay(100);
    ESP.restart();
  }
}

WiFiServer& getServer() {
  return server;
}

void setupWebSocket(WebSocketsClient& webSocket) {
  webSocket.begin(WEBSOCKET_SERVER_HOST, WEBSOCKET_SERVER_PORT, WEBSOCKET_PATH);
  webSocket.onEvent(webSocketEvent);
  webSocket.setReconnectInterval(5000);
}

void handleWebSocket(WebSocketsClient& webSocket) {
  webSocket.loop();
}
