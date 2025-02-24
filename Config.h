#ifndef CONFIG_H
#define CONFIG_H

/*****************************/
/* Pin Configuration */
#define RESTART_BUTTON_PIN 12

// LED to confirm activation
#define LED_PIN 5
#define LED_GREEN 7
#define LED_YELLOW 8
#define LED_RED 9

/* End of pin configuration */
/*****************************/

// Device Identification
#define ID_DEVICE 1L
#define NAME_DEVICE_DEFAULT "Device-Z"
#define LOCAL_IP_DEFAULT IPAddress(192, 168, 1, 100)
#define LOCAL_IP_DEFAULT2 IPAddress(192, 168, 0, 100)

// WiFi Configuration
#define WIFI_SSID_DEFAULT "www.icm.com"
#define WIFI_PASSWORD_DEFAULT "Dakar*2024"

#define GATEWAY IPAddress(192, 168, 1, 1)
#define GATEWAY2 IPAddress(192, 168, 0, 1)
#define SUBNET IPAddress(255, 255, 255, 0)

// DNS Servers
#define DNS1 IPAddress(8, 8, 8, 8)  // Primary DNS
#define DNS2 IPAddress(8, 8, 4, 4)  // Secundary DNS

// Local Server Port
#define LOCAL_SERVER_PORT 82

// WebSocket Configuration
#define WEBSOCKET_PATH "/ws"
#define WEBSOCKET_SERVER_HOST "samloto.com"
#define WEBSOCKET_SERVER_PORT 7094

/*****************************/
/* API Configuration */
#define API_PATH "https://"

#define API_SERVER_HOST "samloto.com"

// Puerto del Servidor API
#define API_SERVER_PORT 4015

// Convertir el número del puerto a cadena
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#define API_BASE_PATH API_PATH API_SERVER_HOST ":" TOSTRING(API_SERVER_PORT) "/api/"
#define API_DEVICES_PATH API_BASE_PATH "devices"

/* Fin de Configuración de la API */
/*****************************/

#endif
