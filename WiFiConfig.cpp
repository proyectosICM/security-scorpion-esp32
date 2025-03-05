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
  // WIFI_SSID_DEFAULT
  // WIFI_PASSWORD_DEFAULT

  // Primer intento de conexión
  Serial.println("🔄 Intentando conectar con la primera configuración de red...");
  if (!WiFi.config(LOCAL_IP_DEFAULT, GATEWAY, SUBNET)) {
    Serial.println("⚠️ Falló la configuración de la primera IP");
  }
  /*
  WiFi.begin(WIFI_SSID_DEFAULT, WIFI_PASSWORD_DEFAULT);
  if (waitForConnection(10000)) {
    Serial.println("✅ Conexión exitosa con la primera configuración de red");
    startServer();
    return;
  }
*/
  Serial.println("\n");

  // Último intento: usar DHCP
  Serial.println("🔄 Intentando conectar usando DHCP...");
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.begin(ssid, password);
  if (waitForConnection(35000)) {  // Mayor tiempo para DHCP
    Serial.println("✅ Conexión exitosa con DHCP");
    Serial.print("🌐 IP asignada por DHCP: ");
    Serial.println(WiFi.localIP());
    String ipAsignada = WiFi.localIP().toString();
    sendIPToAPI(ipAsignada);
    Serial.print("📡 IP del Router (Gateway): ");
    Serial.println(WiFi.gatewayIP());

    startServer();
    return;
  }

  // Si ambas fallan, reinicia el dispositivo
  Serial.println("❌ No se pudo conectar a ninguna red. Reiniciando...");
  //resetToDefaultSettings();
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
  setupWebSocket(webSocket);
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
