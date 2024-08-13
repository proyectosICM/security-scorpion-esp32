#ifndef CONFIG_H
#define CONFIG_H

// Configuración de WiFi
#define WIFI_SSID "www.icm.com"
#define WIFI_PASSWORD "Dakar*2024"

// Configuración de IP estática
#define LOCAL_IP IPAddress(192, 168, 1, 186)
#define GATEWAY IPAddress(192, 168, 1, 1)
#define SUBNET IPAddress(255, 255, 255, 0)

// DNS servers
#define DNS1 IPAddress(8, 8, 8, 8)  // DNS primario
#define DNS2 IPAddress(8, 8, 4, 4)  // DNS secundario

// Puerto del servidor
#define LOCAL_SERVER_PORT 82

// Puerto del servidor WebSocket
#define WEBSOCKET_SERVER_PORT 7094

// Dirección IP o nombre de host del servidor WebSocket
#define WEBSOCKET_SERVER_HOST "samloto.com"

// Ruta del WebSocket
#define WEBSOCKET_PATH "/ws"

#define ID_DEVICE 1

// Nombre del dispositivo
#define NAME_DEVICE "Device-A"

#endif
