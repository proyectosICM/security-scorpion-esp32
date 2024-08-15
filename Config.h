#ifndef CONFIG_H
#define CONFIG_H

// Configuración de WiFi
#define WIFI_SSID "www.icm.com"
#define WIFI_PASSWORD "Dakar*2024"

// Identificación del dispositivo
#define ID_DEVICE 1
#define NAME_DEVICE "Device-A" // Nombre Original del dispositivo

// Configuración de IP estática
#define LOCAL_IP IPAddress(192, 168, 1, 100)
#define GATEWAY IPAddress(192, 168, 1, 1)
#define SUBNET IPAddress(255, 255, 255, 0)

// Servidores DNS
#define DNS1 IPAddress(8, 8, 8, 8)  // DNS primario
#define DNS2 IPAddress(8, 8, 4, 4)  // DNS secundario

// Puerto del servidor local
#define LOCAL_SERVER_PORT 82

// Configuración del WebSocket
#define WEBSOCKET_PATH "/ws"
#define WEBSOCKET_SERVER_HOST "samloto.com"
#define WEBSOCKET_SERVER_PORT 7094

#endif
