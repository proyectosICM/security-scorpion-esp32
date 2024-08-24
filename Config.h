#ifndef CONFIG_H
#define CONFIG_H

/*****************************/
/* Configuracion de pines */
#define RESTART_BUTTON_PIN 12

// Led para confirmar activacion
#define LED_PIN 5

// Led verde
#define LED_GREEN 7

// Led amarillo
#define LED_YELLOW 8

// Led rojo
#define LED_RED 9

/* Fin de configuracion de pines*/
/*****************************/

// Configuración de WiFi
#define WIFI_SSID "www.icm.com"
#define WIFI_PASSWORD "Dakar*2024"

// Identificación del dispositivo
#define ID_DEVICE 1L  

#define NAME_DEVICE_DEFAULT "Device-B"
#define LOCAL_IP_DEFAULT IPAddress(192, 168, 1, 100)

// Configuración de IP estática
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

/*****************************/
/* Configuración de la API */

#define API_SERVER_HOST "samloto.com"

#define API_PATH "https://"

// Puerto del servidor API
#define API_SERVER_PORT 4015

#define API_BASE_PATH API_PATH + API_SERVER_HOST + "/api/devices/"

// Ruta base de la API
#define API_BASE_PATH2 "/api/devices/"

/* Fin de Configuración de la API */
/*****************************/

#endif
