#include <WiFi.h>
#include "Config.h"
#include "wifiManager.h"

void setupWiFi() {
    delay(10);
    Serial.println();
    Serial.print("Conectando em: ");
    Serial.println(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi Conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}