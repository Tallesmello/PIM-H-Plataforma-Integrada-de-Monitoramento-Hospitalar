#include <WiFi.h>
#include <HTTPClient.h>
#include "Config.h"
#include "CloudManager.h"

void sendLeitoToCloud(int leitoNum, int volume, int status) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        
        // Mapeamento automático de Fields:
        // Leito 1 -> Fields 1 e 2 | Leito 2 -> Fields 3 e 4
        int fieldVol = (leitoNum * 2) - 1;
        int fieldStat = leitoNum * 2;

        String url = String("http://") + TS_SERVER + "/update?api_key=" + TS_API_KEY;
        url += "&field" + String(fieldVol) + "=" + String(volume);
        url += "&field" + String(fieldStat) + "=" + String(status);

        http.begin(url);
        int httpCode = http.GET();
        
        if (httpCode > 0) {
            Serial.printf("\n[NUVEM] Dados do Leito %02d enviados! (Code: %d)\n", leitoNum, httpCode);
        }
        http.end();
    }
}