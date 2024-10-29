#include "WebSocketEvent.h"
#include <Arduino.h>
#include "WiFiConfig.h"
#include "WebSocketHandlers.h"
#include "DeviceHandlers.h"

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Disconnected! ws");
      break;
    case WStype_CONNECTED:
      Serial.println("Connected to the server");
      webSocket.sendTXT("Connection from ESP32 device!");
      break;
    case WStype_TEXT:
      //Serial.printf("Message received (longitud %d): %s\n", length, payload);
      if (length > 0) {
        //Serial.println("Message processed successfully.");
        String message((char*)payload, length);
        handleWebSocketMessage(message);
      } else {
        Serial.println("Empty or unprocessed message");
      }
      break;
    case WStype_ERROR:
      Serial.printf("Error: %s\n", payload);
      break;
    case WStype_BIN:
      Serial.println("Binary message received");
      break;
    default:
      Serial.println("Other WebSocket event type");
      break;
  }
}
