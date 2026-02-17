#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "MqttManager.h"
#include "CloudManager.h"

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    StaticJsonDocument<256> doc;
    deserializeJson(doc, payload, length);

    const char* id = doc["leito_id"]; 
    int vol = doc["volume_perc"];
    const char* stat_txt = doc["status"];

    // Converte status texto para número (0, 1 ou 2)
    int stat_num = (strcmp(stat_txt, "NORMAL") == 0) ? 2 : (strcmp(stat_txt, "ATENCAO") == 0 ? 1 : 0);

    // Extrai o número do leito (ex: de "LEITO_01" pega o número 1)
    int numLeito = atoi(&id[6]); 

    // EXIBIÇÃO EM BLOCOS NO TERMINAL
    Serial.println("\n");
    Serial.printf("  DADOS RECEBIDOS: %s ", id);
    Serial.printf("  VOLUME: %d%% ", vol);
    Serial.printf("  STATUS: %s ", stat_txt);
    Serial.println("\n");

    // Envia para a nuvem se for leito 1 ou 2 (limite do seu painel atual)
    if (numLeito >= 1 && numLeito <= 2) {
        sendLeitoToCloud(numLeito, vol, stat_num);
    }
}

void setupMQTT() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(callback);
}

void loopMQTT() {
    while (!client.connected()) {
        // Gera um ID aleatório para evitar quedas de conexão no Broker público
        String clientId = "Hosp_GW_" + String(random(0xffff), HEX);
        Serial.print("[MQTT] Conectando como: "); Serial.println(clientId);
        
        if (client.connect(clientId.c_str())) {
            Serial.println("[MQTT] Conectado com sucesso!");
            client.subscribe(TOPIC_SUBSCRIBE);
        } else {
            Serial.print("[MQTT] Erro: "); Serial.println(client.state());
            delay(5000);
        }
    }
    client.loop();
}