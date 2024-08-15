#include "WebSocketHandlers.h"
#include "Config.h"
#include "DeviceHandlers.h"

void handleWebSocketMessage(const String& message) {
    // Buscar el separador ": "
    int separatorIndex = message.indexOf(": ");
    if (separatorIndex != -1) {
        // Extraer el contenido después del separador
        String content = message.substring(separatorIndex + 2); // +2 para saltar ": "
        int colonIndex = content.indexOf(':');
        if (colonIndex != -1) {
            String deviceName = content.substring(0, colonIndex);
            String action = content.substring(colonIndex + 1);

            // Comparar el nombre del dispositivo
            if (deviceName == NAME_DEVICE) {
                if (action == "Activating") {
                    deviceActivated();
                    Serial.println("Dispositivo Accionado Remotamente");
                } else {
                    Serial.println("Acción no reconocida");
                }
            }
        }
    } else {
        Serial.println("Formato de mensaje no reconocido");
    }
}
