#include "WebSocketHandlers.h"
#include "DeviceHandlers.h"
#include "Config.h"
#include <EEPROM.h>
#include <map>
#include <functional>
#include "EepromManager.h"
#include <WiFiConfig.h>

bool isValidId(const String& idString, long& receivedID) {
  receivedID = idString.toInt();
  return (receivedID != 0 || idString == "0");
}

void handleRebootGlobal(const String& param) {
  if (param == "all") {
    Serial.println("Restarting device globally...");
    digitalWrite(LED_YELLOW, HIGH);
    delay(500);
    digitalWrite(LED_YELLOW, LOW);
    ESP.restart();
  } else {
    Serial.println("Invalid parameter for global reboot: " + param);
  }
}

void handleRebootById(const String& idString) {
  long receivedID = idString.toInt();
  if (!isValidId(idString, receivedID)) {
    Serial.println("Received invalid ID: " + idString);
    return;
  }
  if (receivedID == ID_DEVICE) {
    Serial.println("ID match, rebooting device...");
    digitalWrite(LED_YELLOW, HIGH);
    delay(500);
    digitalWrite(LED_YELLOW, LOW);
    ESP.restart();
  }
}

void handleActivate(const String& idString) {
  long receivedID = idString.toInt();

  if (!isValidId(idString, receivedID)) {
    Serial.println("Received invalid ID: " + idString);
    return;
  }

  if (receivedID == ID_DEVICE) {
    deviceActivated();
    Serial.println("Device activated remotely.");

    String response = "ac:" + String(ID_DEVICE) + ":activated:successfully";
    webSocketClient.sendTXT(response);
  }
}

void handleDisable(const String& idString) {
  long receivedID = idString.toInt();

  if (!isValidId(idString, receivedID)) {
    Serial.println("Received invalid ID: " + idString);
    return;
  }

  if (receivedID == ID_DEVICE) {
    deviceDisabled();
    Serial.println("Device disabled remotely.");

    String response = "ac:" + String(ID_DEVICE) + ":disabled:successfully";
    webSocketClient.sendTXT(response);
  }
}


void handleUnknownCommand(const String& message) {
  Serial.println("Unrecognized message: " + message);
}

void handleChangeWifiCredentials(const String& message) {
  deviceChangeWifiCredentials(message);
}

void handleDeaultValues(const String& message) {
  initializeDeviceSettings();
  ESP.restart();
}

// Tabla de comandos para WebSocket
std::map<String, std::function<void(const String&)>> wsCommandHandlers = {
  { "reboot-g", [](const String& params) {
     handleRebootGlobal(params);
   } },
  { "reboot", [](const String& params) {
     handleRebootById(params);
   } },
  { "activate", [](const String& params) {
     handleActivate(params);
   } },
  { "deactivate", [](const String& params) {
     handleDisable(params);
   } },
  { "cwc", [](const String& params) {
     handleChangeWifiCredentials(params);
   } },
  { "dfv", [](const String& params) {
     handleDeaultValues(params);
   } }
};

// Función principal de manejo de mensajes
void handleWebSocketMessage(const String& message) {
  Serial.println("Received message: " + message);

  int separatorIndex = message.indexOf(": ");
  if (separatorIndex != -1) {
    String command = message.substring(separatorIndex + 2);
    String commandType;
    int commandSeparatorIndex = command.indexOf(":");

    if (commandSeparatorIndex != -1) {
      commandType = command.substring(0, commandSeparatorIndex);
      String content = command.substring(commandSeparatorIndex + 1);
      content.trim();  // Solo trima el contenido si es necesario
      Serial.println("Extracted command: " + commandType + ", content: " + content);

      // Buscar el comando en la tabla
      auto handler = wsCommandHandlers.find(commandType);
      if (handler != wsCommandHandlers.end()) {
        handler->second(content);
      } else {
        handleUnknownCommand(message);
      }
    } else {
      Serial.println("Invalid command format.");
    }
  } else {
    Serial.println("Invalid message format.");
  }
}
