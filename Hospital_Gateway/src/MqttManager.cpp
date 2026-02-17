#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Config.h"
#include "MqttManager.h"
#include "CloudManager.h"

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    // Usar StaticJsonDocument é bom, mas vamos garantir que ele limpe a memória
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, payload, length);
    
    if (error) {
        Serial.println("\n[ERRO] Falha ao ler JSON!");
        return;
    }

    // Extração segura de valores (evita crash se o campo não existir)
    const char* id = doc["leito_id"] | "DESCONHECIDO";
    int vol = doc["volume_perc"] | 0;
    const char* stat_txt = doc["status"] | "INDETERMINADO";
    
    // Lógica de conversão de status
    int stat_num = 0;
    if (strcmp(stat_txt, "NORMAL") == 0) stat_num = 2;
    else if (strcmp(stat_txt, "ATENCAO") == 0) stat_num = 1;

    // Extrai o número do leito (ex: LEITO_01 -> 1)
    int numLeito = (strlen(id) >= 7) ? atoi(&id[6]) : 0;

    // --- LOG DE RECEBIMENTO ---
    Serial.println("\n=======================================");
    Serial.printf("[MQTT RECV] ID: %s | Vol: %d%% | Status: %s\n", id, vol, stat_txt);
    
    if (numLeito >= 1 && numLeito <= 2) {
        Serial.print("[CLOUD] Enviando para nuvem...");
        
        // Chamada da sua função original
        sendLeitoToCloud(numLeito, vol, stat_num); 
        
        // A mensagem de sucesso do seu CloudManager aparecerá aqui embaixo
    } else {
        Serial.printf("[AVISO] Leito %d fora da faixa de envio (1-2).\n", numLeito);
    }
    Serial.println("=======================================");
}

void reconnect() {
    static unsigned long lastAttempt = 0;
    unsigned long now = millis();

    if (!client.connected()) {
        if (now - lastAttempt > 5000) {
            lastAttempt = now;

            // Só imprime o status se não estiver no meio de um recebimento
            Serial.print("\n[MQTT] Tentando conexão... ");

            String clientId = "Hosp_GW_" + String(random(0xffff), HEX);

            if (client.connect(clientId.c_str())) {
                Serial.println("CONECTADO!");
                client.subscribe(TOPIC_SUBSCRIBE);
            } else {
                Serial.printf("FALHOU (rc=%d). Nova tentativa em 5s.\n", client.state());
            }
        }
    }
}

void setupMQTT() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setKeepAlive(60); // Mantém a conexão ativa por mais tempo
    client.setBufferSize(512); // Aumenta o buffer para JSONs maiores se necessário
    client.setCallback(callback);
}

void loopMQTT() {
    // Garante que o MQTT tente reconectar antes de processar o loop
    if (!client.connected()) {
        reconnect();
    }
    client.loop();
}