#ifndef MQTT_SUBSCRIPTION_H
#define MQTT_SUBSCRIPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
#include <unistd.h>  // ✅ Required for sleep()
#include "/root/tesi/paho.mqtt.c/src/MQTTClient.h"
#include <sys/time.h>
#include <time.h>


#include <signal.h>
#include <json-c/json.h>

typedef struct {
    int lat;  // First integer
    int lon;  // Second integer
} coord;

void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos);
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);
coord start_mqtt();
//int messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
//void connection_lost(void *context, char *cause);


#endif // MQTT_SUBSCRIPTION_H
