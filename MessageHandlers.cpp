#include "MessageHandlers.h"
#include "WiFiConfig.h"
#include <EEPROM.h>
#include <map>
#include <functional>
#include "DeviceHandlers.h"
#include "config.h"


void handleIsConnect(WiFiClient& client) {
  Serial.println("Cliente conectado");
  digitalWrite(LED_GREEN, HIGH);
  delay(500);
  digitalWrite(LED_GREEN, LOW);
}

void handleGetName(WiFiClient& client) {
  // Enviar nombre
  String responseName = "nombre: " + getStoredDeviceName();
  client.println(responseName);
  Serial.println("Mensaje enviado Nombre: " + responseName);
}

void handleGetId(WiFiClient& client) {
  // Enviar ID
  String responseId = "id: " + String(ID_DEVICE);
  client.println(responseId);
  Serial.println("Mensaje enviado ID: " + responseId);
}


void handleActivated(WiFiClient& client) {
  deviceActivated();
  Serial.println("Dispositivo Accionado Localmente");
  client.stop();
  Serial.println("Cliente desconectado");
}

void handleDisconnect(WiFiClient& client) {
  client.stop();
  Serial.println("Cliente desconectado");
}

void handleEditConfig(WiFiClient& client, String& message) {
  Serial.println("Sea detectado un cambio de configuracion");
  Serial.println("Configuracion detectada: " + message);

  // Extraer los parámetros del mensaje
  String name = "";
  String ip = "";

  int nameStart = message.indexOf("setName:") + 8;  // +8 para pasar "setName:"
  int nameEnd = message.indexOf(';', nameStart);
  if (nameStart != -1 && nameEnd != -1) {
    name = message.substring(nameStart, nameEnd);
  }

  int ipStart = message.indexOf("setIp:") + 6;  // +6 para pasar "setIp:"
  if (ipStart != -1) {
    ip = message.substring(ipStart);
  }

  // Verificar que ambos valores estén presentes
  if (name.length() > 0 && ip.length() > 0) {
    // Convertir la IP en IPAddress
    IPAddress newIp;
    if (newIp.fromString(ip)) {
      // Almacenar el nuevo nombre y IP en la EEPROM
      storeDeviceName(name);
      storeIpAddress(newIp);

      // Confirmar la actualización
      client.println("Configuración actualizada");
      Serial.println("Configuración actualizada: Nombre=" + name + ", IP=" + ip);

      // Reiniciar el ESP32 después de la actualización
      //client.println("Reiniciando el dispositivo...");
      Serial.println("Reiniciando el dispositivo...");
      delay(100);     // Pequeño retraso para asegurar que el mensaje sea enviado antes de reiniciar
      ESP.restart();  // Reinicia el ESP32
    } else {
      client.println("IP no válida");
      Serial.println("IP no válida: " + ip);
    }
  } else {
    client.println("Datos incompletos");
    Serial.println("Datos incompletos en el mensaje: " + message);
  }

  client.stop();
}


void handleUnknown(WiFiClient& client) {
  client.println("Unknown");
  Serial.println("Mensaje no reconocido.");
  Serial.println("Mensaje enviado: Unknown ");
  client.stop();
  Serial.println("Cliente desconectado");
}



std::map<String, std::function<void(WiFiClient&)>> messageHandlers = {
  { "isConnected", handleIsConnect },
  { "getName", handleGetName },
  { "getId", handleGetId },
  { "activate", handleActivated },
  { "disconnect", handleDisconnect }
};

void handleClient() {
  WiFiClient client = getServer().available();
  if (client) {
    Serial.println("Cliente conectado");

    while (client.connected()) {
      if (client.available()) {
        String message = client.readStringUntil('\n');
        message.trim();

        if (message.startsWith("editConfig")) {
          handleEditConfig(client, message);
        } else {
          auto handler = messageHandlers.find(message);
          if (handler != messageHandlers.end()) {
            handler->second(client);
          } else {
            handleUnknown(client);
          }
        }
      }
    }
  }
}
