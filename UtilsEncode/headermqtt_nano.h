#ifndef MQTT_SUBSCRIPTION_H
#define MQTT_SUBSCRIPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // ✅ Required for sleep()
#include "/root/tesi/paho.mqtt.c/src/MQTTClient.h"
#include <sys/time.h>
#include <time.h>
#include <signal.h>
//#include <json-c/json.h>

typedef struct {
    int lat;  // First integer
    int lon;  // Second integer
} coord;

coord start_mqtt();
int message_callback(void *context, char *topicName, int topicLen, MQTTClient_message *message);
void connection_lost(void *context, char *cause);


#endif // MQTT_SUBSCRIPTION_H
