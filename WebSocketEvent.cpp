#include "WebSocketEvent.h"
#include <Arduino.h>
#include "WiFiConfig.h"
#include "WebSocketHandlers.h"

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.println("Desconectado! ws");
      break;
    case WStype_CONNECTED:
      Serial.println("Conectado al servidor");
      webSocket.sendTXT("Conexion desde dispositivo ESP32!");
      break;
    case WStype_TEXT:
      //Serial.printf("Mensaje recibido (longitud %d): %s\n", length, payload);
      if (length > 0) {
        //Serial.println("Mensaje procesado correctamente.");
        // Aquí podrías llamar a funciones de WebSocketHandlers
        String message((char*)payload, length);
        handleWebSocketMessage(message);
      } else {
        Serial.println("Mensaje vacío o no procesado.");
      }
      break;
    case WStype_ERROR:
      Serial.printf("Error: %s\n", payload);
      break;
    case WStype_BIN:
      Serial.println("Mensaje binario recibido");
      break;
    default:
      Serial.println("Otro tipo de evento WebSocket");
      break;
  }
}
