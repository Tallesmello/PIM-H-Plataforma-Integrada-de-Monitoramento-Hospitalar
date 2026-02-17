#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

// --- Configurações de Rede ---
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

// --- Configurações MQTT ---
#define MQTT_SERVER "broker.emqx.io"
#define MQTT_PORT 1883
// O '+' permite ouvir hospital/leito/01, hospital/leito/02, etc.
#define TOPIC_SUBSCRIBE "hospital/leito/+/dados" 

// --- Configurações ThingSpeak ---
#define TS_SERVER "api.thingspeak.com"
#define TS_API_KEY "ZAEJ7JQ5OX47XATW"

#endif