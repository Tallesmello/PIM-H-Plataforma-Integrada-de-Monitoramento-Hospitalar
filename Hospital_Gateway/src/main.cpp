#include <Arduino.h>
#include "Config.h"
#include "WifiManager.h"
#include "MqttManager.h"

void setup() {
    Serial.begin(115200);
    
    setupWiFi(); 

    setupMQTT();

    Serial.println("\n--- GATEWAY HOSPITALAR ATIVO ---");
}

void loop() {
    // Mantém o Gateway ouvindo as mensagens
    loopMQTT();
}