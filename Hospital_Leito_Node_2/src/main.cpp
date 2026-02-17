#include <Arduino.h>
#include "Config.h"
#include "WifiManager.h"
#include "MqttManager.h"
#include "esp_log.h"

void setup() {
    Serial.begin(115200);

    esp_log_level_set("*", ESP_LOG_NONE);

    pinMode(PIN_SENSOR_SORO, INPUT);
    pinMode(PIN_LED_ALERTA, OUTPUT);

    setupWiFi();
    setupMQTT();
}

unsigned long lastSend = 0;
const unsigned long intervalSend = 5000;

unsigned long lastMedAlert = 0;
const unsigned long intervalMed = 20000;

bool medAlert = false;

void loop() {

    checkWiFiConnection();
    loopMQTT();

    unsigned long now = millis();

    // envio a cada 5 segundos
    if (now - lastSend >= intervalSend) {
        lastSend = now;

        int leitura = analogRead(PIN_SENSOR_SORO);

        if (leitura < 400) {
            digitalWrite(PIN_LED_ALERTA, HIGH);
        } else {
            digitalWrite(PIN_LED_ALERTA, LOW);
        }

        enviaDadosLeito(leitura);
    }

    // simulação horário medicamento
    if (now - lastMedAlert >= intervalMed) {
        lastMedAlert = now;
        medAlert = !medAlert;
        Serial.println("Alerta de Medicamento!");
    }
}