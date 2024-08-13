#include "MessageHandlers.h"
#include "WiFiConfig.h"
#include <map>
#include <functional>
#include "Config.h"

void handleIsConnect(WiFiClient& client) {
    Serial.println("Cliente conectado");
}

void handleGetName(WiFiClient& client) {
    String response = String("nombre: ") + NAME_DEVICE;
    client.println(response);
    Serial.println("Mensaje enviado: nombre: " + response);
}

void handleActivated(WiFiClient& client) {
    Serial.println("Dispositivo Accionado");
    client.stop();
}

void handleDisconnect(WiFiClient& client) {
    client.stop();
    Serial.println("Cliente desconectado");
}

void handleUnknown(WiFiClient& client) {
    Serial.println("Mensaje no reconocido.");
}

std::map<String, std::function<void(WiFiClient&)>> messageHandlers = {
    { "isConnected", handleIsConnect },
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

                Serial.print("Mensaje recibido: ");
                Serial.println(message);

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
