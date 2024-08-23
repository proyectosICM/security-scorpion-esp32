#include "WebSocketHandlers.h"
#include "DeviceHandlers.h"
#include <EEPROM.h>

void handleWebSocketMessage(const String& message) {


  // Buscar el primer delimitador ": " para separar el identificador del mensaje
  int separatorIndex = message.indexOf(": ");
  if (separatorIndex != -1) {
    // Extraer el mensaje después del identificador
    String content = message.substring(separatorIndex + 2);

    // Verificar si el contenido es "reboot"
    if (content == "reboot") {
      Serial.println("Reiniciando dispositivo...");
      ESP.restart();  // Reiniciar el ESP32
    } else {
      // Manejar otros formatos de mensaje
      int colonIndex = content.indexOf(':');
      if (colonIndex != -1) {
        String deviceName = content.substring(0, colonIndex);
        String action = content.substring(colonIndex + 1);

        if (deviceName == getStoredDeviceName()) {
          if (action == "Activating") {
            deviceActivated();
            Serial.println("Dispositivo Accionado Remotamente");
          } else {
            Serial.println("Acción no reconocida");
          }
        } 
      } 
    }
  }
}
