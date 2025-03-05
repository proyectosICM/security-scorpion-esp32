#ifndef WIFICONFIG_H
#define WIFICONFIG_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WebSocketsClient.h>
#include "Config.h"

extern WebSocketsClient webSocket;

void setupWiFi();
WiFiServer& getServer();
void setupWebSocket(WebSocketsClient& webSocket);
void handleWebSocket(WebSocketsClient& webSocket);
bool waitForConnection(unsigned long timeout);
void sendIPToAPI(String ip);
void startServer();
#endif
