#include "headermqtt.h"
#include "savelatency.h"
#ifdef MQTT_SUBSCRIPTION_H
#include <json-c/json.h>
#else
#error "JSON_LIB_1 not defined!"
#endif

#define ADDRESS     "tcp://127.0.0.1:1883"
#define CLIENTID    "HighPerformanceMQTTSubscriber"
#define TOPIC       "/haura/data"
#define QOS         0
#define TIMEOUT     10000L

// Flag to indicate when to stop the client
volatile int running = 1;

// Signal handler to gracefully terminate
void handle_signal(int sig) {
    running = 0;
}

// Global coord variable to store the latest position
coord latest_position = {0, 0};

// Message callback function
int message_callback(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long reception_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    
    // Process the message as quickly as possible
    json_object *root = json_tokener_parse((char*)message->payload);
    if (root == NULL) {
        MQTTClient_freeMessage(&message);
        MQTTClient_free(topicName);
        return 0;
    }

    // Fast path extraction - only get what we need
    json_object *data_obj = NULL;
    json_object *head_obj = NULL;
    json_object *stamp_obj = NULL;
    json_object *objects_array = NULL;
    json_object *first_object = NULL;
    json_object *latitude_obj = NULL;
    json_object *longitude_obj = NULL;
    
    if (!json_object_object_get_ex(root, "data", &data_obj)) goto cleanup;
    if (!json_object_object_get_ex(data_obj, "head", &head_obj)) goto cleanup;
    if (!json_object_object_get_ex(head_obj, "stamp", &stamp_obj)) goto cleanup;
    if (!json_object_object_get_ex(data_obj, "objects", &objects_array)) goto cleanup;
    
    // Get timestamp
    const char *stamp_str = json_object_get_string(stamp_obj);
    char timestamp_str[14]; 
    strncpy(timestamp_str, stamp_str, 13);
    timestamp_str[13] = '\0';
    long message_time = strtol(timestamp_str, NULL, 10);
    
    // Calculate latency
    long latency = reception_time - message_time;
    log_latency(latency);
    
    // Get first object if available
    first_object = json_object_array_get_idx(objects_array, 0);
    
    if (json_object_object_get_ex(first_object, "latitude", &latitude_obj) &&
        json_object_object_get_ex(first_object, "longitude", &longitude_obj)) {
        
        // Update the global position
        latest_position.lat = (int)(json_object_get_double(latitude_obj) * 1000000 + 0.5);
        latest_position.lon = (int)(json_object_get_double(longitude_obj) * 1000000 + 0.5);
        
        // Optional: Print processing stats (can be disabled for max performance)
        printf("Latency: %ld ms\n", latency);
    }
    
    return 1;
cleanup:
    // Clean up
    json_object_put(root);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
}

// Connection lost callback
void connection_lost(void *context, char *cause) {
    printf("Connection lost. Cause: %s\n", cause ? cause : "Unknown");
    // You might want to attempt reconnection here
}

int main() {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;
    
    // Set up signal handlers for graceful termination
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    
    // Configure connection options for high performance
    conn_opts.keepAliveInterval = 20;       // Shorter interval
    conn_opts.cleansession = 1;             // Clean session for faster startup
    conn_opts.connectTimeout = 5;           // Fast connect timeout
    
    // Create MQTT client
    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID, 
                               MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to create client, return code: %d\n", rc);
        return 1;
    }
    
    // Set callbacks
    if ((rc = MQTTClient_setCallbacks(client, NULL, connection_lost, message_callback, NULL)) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to set callbacks, return code: %d\n", rc);
        MQTTClient_destroy(&client);
        return 1;
    }
    
    // Connect to broker
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to connect, return code: %d\n", rc);
        MQTTClient_destroy(&client);
        return 1;
    }
    
    // Subscribe to topic
    if ((rc = MQTTClient_subscribe(client, TOPIC, QOS)) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to subscribe, return code: %d\n", rc);
        MQTTClient_disconnect(client, TIMEOUT);
        MQTTClient_destroy(&client);
        return 1;
    }
    
    printf("Subscribed to %s, receiving messages at maximum speed\n", TOPIC);
    
    // Use direct receive approach for maximum speed
    while (running) {
        MQTTClient_message* message = NULL;
        char* topicName = NULL;
        int topicLen;
        
        // Zero timeout for non-blocking operation
        rc = MQTTClient_receive(client, &topicName, &topicLen, &message, 0);
        
        if (rc == MQTTCLIENT_SUCCESS && message != NULL) {
            // Process message
            message_callback(NULL, topicName, topicLen, message);
        }
        
        // CPU-efficient busy waiting - bare minimum delay to prevent 100% CPU usage
        // Remove this line for absolute maximum speed at the cost of CPU usage
        struct timespec ts = {0, 100000}; // 0.1ms - adjust based on your system
        nanosleep(&ts, NULL);
    }
    
    // Clean disconnection
    MQTTClient_unsubscribe(client, TOPIC);
    MQTTClient_disconnect(client, TIMEOUT);
    MQTTClient_destroy(&client);
    return 1;
}