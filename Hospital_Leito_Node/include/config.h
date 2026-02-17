#ifndef CONFIG_H
#define CONFIG_H

// --- Identificação do Leito ---
#define LEITO_ID "LEITO_01" 

// --- WiFi ---
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""

// --- MQTT Broker (HiveMQ Público) ---
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_PORT 1883
#define TOPIC_PUBLISH "hospital/leito/01/dados"

// --- Hardware ---
#define PIN_SENSOR_SORO 34  // Potenciômetro
#define PIN_LED_ALERTA 2    // LED da placa

#endif