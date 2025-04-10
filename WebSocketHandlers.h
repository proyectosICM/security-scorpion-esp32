#ifndef WEBSOCKETHANDLERS_H
#define WEBSOCKETHANDLERS_H

#include <WebSocketsServer.h>
#include <Arduino.h>

//extern WebSocketsServer webSocketServer;
void handleWebSocketMessage(const String& message);
void handleActivate(const String& param);
void handleDisable(const String& param);
#endif
