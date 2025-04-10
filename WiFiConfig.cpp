#include "WiFiConfig.h"
#include "MessageHandlers.h"
#include "WebSocketEvent.h"
#include <WebSocketsClient.h>
#include <HTTPClient.h>
#include <EEPROM.h>
#include "DeviceHandlers.h"
#include "EepromManager.h"

WiFiServer server(LOCAL_SERVER_PORT);
WebSocketsClient webSocketClient;

void setupWiFi() {
  String ssid = getStoredSSID();
  String password = getStoredPassword();
  Serial.println("\n");

  // Último intento: usar DHCP
  Serial.println("🔄 Intentando conectar usando DHCP...");
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.begin(ssid, password);
  if (waitForConnection(35000)) {  // Mayor tiempo para DHCP
    Serial.println("✅ Conexión exitosa con DHCP");

    Serial.print("📶 Conectado a la red: ");
    Serial.println(WiFi.SSID());

    Serial.print("🌐 IP asignada por DHCP: ");
    Serial.println(WiFi.localIP());

    String ipAsignada = WiFi.localIP().toString();
    sendIPToAPI(ipAsignada);

    Serial.print("📡 IP del Router (Gateway): ");
    Serial.println(WiFi.gatewayIP());
    blinkLED(LED_GREEN, 3, 500);
    startServer();
    return;
  }

  // Si ambas fallan, reinicia el dispositivo
  Serial.println("❌ No se pudo conectar a ninguna red. Reiniciando...");
  blinkLED(LED_RED, 3, 500);
  //digitalWrite(LED_RED, HIGH);
  resetToDefaultSettings();
  delay(100);
  ESP.restart();
}

// Función auxiliar para esperar conexión con un tiempo límite
bool waitForConnection(unsigned long timeout) {
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
    delay(100);
    Serial.print(".");
  }
  return WiFi.status() == WL_CONNECTED;
}

// Inicia el servidor y WebSocket si la conexión es exitosa
void startServer() {
  Serial.println("\n📡 Conectado a la red WiFi");
  Serial.print("🌐 IP Address: ");
  Serial.println(WiFi.localIP());

  server.begin();
  setupWebSocket(webSocketClient);
}

WiFiServer& getServer() {
  return server;
}

void setupWebSocket(WebSocketsClient& webSocketClient) {
  webSocketClient.begin(WEBSOCKET_SERVER_HOST, WEBSOCKET_SERVER_PORT, WEBSOCKET_PATH);
  webSocketClient.onEvent(webSocketEvent);
  webSocketClient.setReconnectInterval(5000);
}

void handleWebSocket(WebSocketsClient& webSocketClient) {
  webSocketClient.loop();
}
