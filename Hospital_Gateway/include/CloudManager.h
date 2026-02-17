#ifndef CLOUD_MANAGER_H
#define CLOUD_MANAGER_H

// Função que envia os dados de qualquer leito para o ThingSpeak
void sendLeitoToCloud(int leitoNum, int volume, int status);

#endif