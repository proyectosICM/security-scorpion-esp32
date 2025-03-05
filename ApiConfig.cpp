#include "ApiConfig.h"
#include "DeviceHandlers.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <EEPROM.h>
#include <WiFi.h>
#include "Config.h"
#include "EepromManager.h"

void updateDeviceConfig() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String apiEndpoint = String(API_DEVICES_PATH) + "/" + String(ID_DEVICE);

    http.begin(apiEndpoint);
    http.setTimeout(5000);

    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.println("❌ Error deserializing JSON: " + String(error.c_str()));
        return;
      }

      int apiId = doc["id"];
      String apiNameDevice = doc["nameDevice"];
      String apiIpLocal = doc["ipLocal"];

      String currentNameDevice = getStoredDeviceName();
      IPAddress currentIpLocal = getStoredIpAddress();

      IPAddress apiIp;
      apiIp.fromString(apiIpLocal);

      if (apiId != EEPROM.read(0) || apiNameDevice != currentNameDevice || apiIp != currentIpLocal) {
        // Update EEPROM with new values from the API
        EEPROM.write(0, apiId);
        storeDeviceName(apiNameDevice);
        storeIpAddress(apiIp);

        Serial.println("🔄 Configuration updated from the API. Restarting...");

        Serial.println("📌 Nombre de dispositivo actualizado: " + apiNameDevice);
        Serial.println("🌐 IP: " + apiIp);
        ESP.restart();
      } else {
        Serial.println("✅ Device configuration is up to date.");
      }
    } else {
      Serial.println("⚠️ Error retrieving data from the API. Continuing with normal operation.");
    }
    http.end();
  } else {
    Serial.println("📶❌No WiFi connection. Continuing with normal operation.");
  }
}

void sendIPToAPI(String ip) {
  HTTPClient http;

  // Construcción de la URL con el ID del dispositivo en la ruta
  String url = String(API_DEVICES_PATH) + "/register-ip/" + String(ID_DEVICE);

  Serial.print("🌍 Enviando IP a la API: ");
  Serial.println(url);

  http.begin(url);
  http.addHeader("Content-Type", "application/json");

  // El payload ahora solo enviará la IP, ya que el ID está en la URL
  String payload = "{\"ipLocal\": \"" + ip + "\"}";

  int httpResponseCode = http.PUT(payload);

  if (httpResponseCode > 0) {
    Serial.print("✅ Respuesta de la API: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("❌ Error al enviar la IP: ");
    Serial.println(http.errorToString(httpResponseCode).c_str());
  }

  http.end();
}
