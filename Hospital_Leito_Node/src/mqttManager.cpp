#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "MqttManager.h"
extern bool medAlert;


WiFiClient espClient;
PubSubClient client(espClient);


void reconnect() {
    if (!client.connected()) {
        Serial.print("Tentando conexão MQTT...");

        String clientId = String(LEITO_ID) + "-" + String(random(0xffff), HEX);

        if (client.connect(clientId.c_str())) {
            Serial.println("Conectado!");
        } else {
            Serial.print("Falha, rc=");
            Serial.println(client.state());
        }
    }
}

void setupMQTT() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loopMQTT() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}

void enviaDadosLeito(int valorSensor) {
    int porcentagem = map(valorSensor, 0, 4095, 0, 100);
    
    String status = "NORMAL";
    if(porcentagem < 10) status = "ALERTA";
    else if(porcentagem < 30) status = "ATENCAO";

    StaticJsonDocument<256> doc;
    doc["leito_id"] = LEITO_ID;
    doc["volume_perc"] = porcentagem;
    doc["status"] = status;
    doc["med_alert"] = medAlert;


    char buffer[256];
    serializeJson(doc, buffer);

    client.publish(TOPIC_PUBLISH, buffer);
    
    Serial.print("JSON Enviado: ");
    Serial.println(buffer);
}