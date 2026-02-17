#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H
#include <Arduino.h>

void setupMQTT();
void loopMQTT();
void enviaDadosLeito(int valorSensor);

#endif