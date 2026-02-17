#include <Arduino.h>
#include "Config.h"
#include "WifiManager.h"
#include "MqttManager.h"

void setup() {
    Serial.begin(115200);
    pinMode(PIN_SENSOR_SORO, INPUT);
    pinMode(PIN_LED_ALERTA, OUTPUT);

    setupWiFi();
    setupMQTT();
}

void loop() {
    loopMQTT();

    int leitura = analogRead(PIN_SENSOR_SORO);

    if (leitura < 400) { // Aproximadamente 10%
        digitalWrite(PIN_LED_ALERTA, HIGH);
    } else {
        digitalWrite(PIN_LED_ALERTA, LOW);
    }

    enviaDadosLeito(leitura);

    delay(5000);
}