#include <Arduino.h>
#include "Config.h"
#include "WifiManager.h"
#include "MqttManager.h"
#include "esp_log.h"

void setup() {
   
    Serial.begin(115200);
    
    esp_log_level_set("*", ESP_LOG_NONE);
   
    setupWiFi(); 
    setupMQTT();

    Serial.println("\n--- GATEWAY HOSPITALAR ATIVO ---");
}

void loop() {
    // Mantém o Gateway ouvindo as mensagens
    loopMQTT();
    checkWiFiConnection();
}