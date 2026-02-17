#include <WiFi.h>
#include "Config.h"
#include "WifiManager.h"

unsigned long lastReconnectAttempt = 0;

void connectWiFi() {
    Serial.println();
    Serial.print("Conectando em: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);
}

void setupWiFi() {
    connectWiFi();
}

void checkWiFiConnection() {
    if (WiFi.status() != WL_CONNECTED) {
        unsigned long now = millis();
        if (now - lastReconnectAttempt > 5000) {
            Serial.println("Reconectando WiFi...");
            connectWiFi();
            lastReconnectAttempt = now;
        }
    }
}
