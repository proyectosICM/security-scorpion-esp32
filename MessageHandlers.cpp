#include "MessageHandlers.h"
#include "WiFiConfig.h"
#include <EEPROM.h>
#include <map>
#include <functional>
#include "DeviceHandlers.h"
#include "config.h"
#include "EepromManager.h"

void handleIsConnect(WiFiClient& client) {
  Serial.println("Client connected");
  digitalWrite(LED_GREEN, HIGH);
  delay(500);
  digitalWrite(LED_GREEN, LOW);
}

void handleReboot(WiFiClient& client) {
  Serial.println("Rebooting device...");
  digitalWrite(LED_YELLOW, HIGH);
  delay(500);
  digitalWrite(LED_YELLOW, LOW);
  ESP.restart();
}

void handleGetId(WiFiClient& client) {
  String responseId = "id: " + String(ID_DEVICE);
  client.println(responseId);
  Serial.println("Message sent ID: " + responseId);
}

void handleGetName(WiFiClient& client) {
  String responseName = "nombre: " + getStoredDeviceName();
  client.println(responseName);
  Serial.println("Message sent Name: " + responseName);
}

void handleActivated(WiFiClient& client) {
  deviceActivated();
  Serial.println("Localmente");
  client.stop();
  Serial.println("Client disconnected");
}

void handleDisconnect(WiFiClient& client) {
  client.stop();
  Serial.println("Client disconnected");
}

void handleEditConfig(WiFiClient& client, String& message) {
  const String MSG_NO_CHANGES = "No changes detected";
  const String MSG_INVALID_IP = "Invalid IP";
  const String MSG_INCOMPLETE_DATA = "Incomplete data";
  const String MSG_UPDATE_SUCCESS = "Configuration updated";
  const String MSG_RESTARTING = "Restarting the device...";

  Serial.println("Configuration change detected");
  Serial.println("Configuration detected: " + message);

  String name = "";
  String ip = "";

  int nameStart = message.indexOf("setName:") + 8;
  int nameEnd = message.indexOf(';', nameStart);
  if (nameStart != -1 && nameEnd != -1) {
    name = message.substring(nameStart, nameEnd);
  }

  int ipStart = message.indexOf("setIp:") + 6;
  if (ipStart != -1) {
    ip = message.substring(ipStart);
  }

  if (name.length() > 0 && ip.length() > 0) {
    IPAddress newIp;
    if (newIp.fromString(ip)) {
      // Leer los valores actuales de EEPROM
      String currentName = getStoredDeviceName();
      IPAddress currentIp = getStoredIpAddress();

      // Comparar y almacenar solo si hay cambios
      bool updated = false;
      if (name != currentName) {
        storeDeviceName(name);
        Serial.println("Name update");
        updated = true;
      }

      if (newIp != currentIp) {
        storeIpAddress(newIp);
        Serial.println("IP update");
        updated = true;
      }

      if (updated) {
        client.println(MSG_UPDATE_SUCCESS);
        Serial.println(MSG_UPDATE_SUCCESS + ": Name=" + name + ", IP=" + ip);
        Serial.println(MSG_RESTARTING);
        delay(100);  // Asegura que el mensaje se envíe antes de reiniciar
        ESP.restart();
      } else {
        client.println(MSG_NO_CHANGES);
        Serial.println(MSG_NO_CHANGES);
      }
    } else {
      client.println(MSG_INVALID_IP);
      Serial.println(MSG_INVALID_IP + ": " + ip);
    }
  } else {
    client.println(MSG_INCOMPLETE_DATA);
    Serial.println(MSG_INCOMPLETE_DATA + " in the message: " + message);
  }

  client.stop();
}


void handleUnknown(WiFiClient& client) {
  client.println("Unknown");
  Serial.println("Unrecognized message.");
  client.stop();
  Serial.println("Client disconnected");
}



std::map<String, std::function<void(WiFiClient&)>> messageHandlers = {
  { "isConnected", handleIsConnect },
  { "reboot", handleReboot },
  { "getId", handleGetId },
  { "getName", handleGetName },
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
