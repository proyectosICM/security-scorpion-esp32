#include "WiFiConfig.h"
#include "MessageHandlers.h"
#include "Config.h"
#include "WebSocketEvent.h"
#include <WebSocketsClient.h>

WiFiServer server(LOCAL_SERVER_PORT);
WebSocketsClient webSocket;  // Definición de webSocket

void setupWiFi() {
    if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, DNS1, DNS2)) {
        Serial.println("Fallo en la configuración de la IP estática");
    }

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.println("Conectando a la red WiFi...");

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
        delay(100);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("Conectado a la red WiFi");
        Serial.print("Dirección IP: ");
        Serial.println(WiFi.localIP());

        server.begin();

        setupWebSocket(webSocket);
    } else {
        Serial.println("No se pudo conectar a la red WiFi");
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