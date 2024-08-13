#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebSocketsClient.h>
#include "Config.h"

extern WebSocketsClient webSocket; // Declaración externa

void setupWiFi();
WiFiServer& getServer();
void setupWebSocket(WebSocketsClient& webSocket);
void handleWebSocket(WebSocketsClient& webSocket);

#endif
