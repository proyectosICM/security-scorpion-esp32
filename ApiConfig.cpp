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

    String apiEndpoint = "https://samloto.com:4015/api/devices/" + String(ID_DEVICE);
    http.begin(apiEndpoint);
    http.setTimeout(5000);

    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);

      int apiId = doc["id"];
      String apiNameDevice = doc["nameDevice"];
      String apiIpLocal = doc["ipLocal"];

      String currentNameDevice = getStoredDeviceName();
      IPAddress currentIpLocal = getStoredIpAddress();

      IPAddress apiIp;
      apiIp.fromString(apiIpLocal);

      if (apiId != EEPROM.read(0) || apiNameDevice != currentNameDevice || apiIp != currentIpLocal) {
        // Actualizar EEPROM con nuevos valores del API
        EEPROM.write(0, apiId);
        storeDeviceName(apiNameDevice);
        storeIpAddress(apiIp);

        Serial.println("Configuración actualizada desde el API. Reiniciando...");

        // Reiniciar dispositivo para aplicar la nueva configuración
        ESP.restart();
      } else {
        Serial.println("Configuración del dispositivo está actualizada.");
      }
    } else {
      Serial.println("Error al obtener datos del API. Continuando con la operación normal.");
    }

    http.end();  // Cerrar conexión HTTP
  } else {
    Serial.println("No hay conexión WiFi. Continuando con la operación normal.");
  }
}
