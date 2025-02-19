#ifndef MQTT_SUBSCRIPTION_H
#define MQTT_SUBSCRIPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mosquitto.h>
//#include <jansson.h>
//#include <json-c/json.h>
#include <sys/time.h>
#include <time.h>


typedef struct {
    int lat;  // First integer
    int lon;  // Second integer
} coord;

void on_connect(struct mosquitto *mosq, void *obj, int rc);
void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos);
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);
coord start_mqtt();

#endif // MQTT_SUBSCRIPTION_H
