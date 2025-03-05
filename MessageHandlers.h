#ifndef MESSAGEHANDLERS_H
#define MESSAGEHANDLERS_H

#include <WiFi.h>
#include <WiFiClient.h>
#include <map>
#include <functional>
#include "Config.h"

void handleClient();
void handleIsConnect(WiFiClient& client);
void handleDisconnect(WiFiClient& client);
void handleRestart(WiFiClient& client);
void handleGetName(WiFiClient& client);
void handleActivated(WiFiClient& client);
void handleEditConfig(WiFiClient& client, String& message);
void handleUnknown(WiFiClient& client);

#endif
