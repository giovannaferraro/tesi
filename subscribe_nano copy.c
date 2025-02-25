#include "headermqtt.h"
#include "savelatency.h"
#ifdef MQTT_SUBSCRIPTION_H
#include <json-c/json.h>
#else
#error "JSON_LIB_1 not defined!"
#endif

#define ADDRESS     "tcp://127.0.0.1:1883"  // NanoMQ broker address
#define CLIENTID    "MQTTSubscriber"        // Unique client ID
#define TOPIC       "/haura/data"           // Topic to subscribe to
#define QOS         0                       // Quality of Service level
#define TIMEOUT     10000L

coord c;  // Ensure coord is defined in headermqtt.h

// Callback function to handle incoming messages
int messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    // Print the received message payload (raw bytes)
    //printf("Message received on topic '%s': %.*s\n", topicName, message->payloadlen, (char*)message->payload);
    struct timeval tv;
    gettimeofday(&tv, NULL);
    // Parse the message payload as JSON using json-c
    json_object *dizionario = json_tokener_parse((char *)message->payload);
    
    if (dizionario != NULL) {
        // Call the function to process the frame
        
        // Extract timestamp from the JSON object
        json_object *data_obj = json_object_object_get(dizionario, "data");
        json_object *head_obj = json_object_object_get(data_obj, "head");
        json_object *stamp_obj = json_object_object_get(head_obj, "stamp");
        
        // Convert stamp to float (as timestamp)
        const char *stamp_str = json_object_get_string(stamp_obj);

        //conversione da stringa a long 
        char new_str[14]; 
        strncpy(new_str, stamp_str, 13);
        new_str[13] = '\0';
        long glass_time = strtol(new_str, NULL, 10); // Assuming you want the timestamp as a float
        
        long milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;
        //printf("Current time in milliseconds: %ld\n", milliseconds);
        //printf("glass time %ld \n", glass_time);

        printf("Tempo passato da frame a obu: %.2f\n", difftime(milliseconds, glass_time));
        log_latency(difftime(milliseconds, glass_time));

        struct json_object *objects_array = json_object_object_get(data_obj, "objects");

        // Get the first object in the array (index 0)
        struct json_object *first_object = json_object_array_get_idx(objects_array, 0);

        // Extract the latitude and longitude
        struct json_object *latitude_obj = json_object_object_get(first_object, "latitude");
        struct json_object *longitude_obj = json_object_object_get(first_object, "longitude");

        // Convert latitude and longitude to double values
        double latitude = json_object_get_double(latitude_obj);
        double longitude = json_object_get_double(longitude_obj);

        c.lat = (int)(json_object_get_double(latitude_obj)*1000000 + 0.5);
        c.lon = (int)(json_object_get_double(longitude_obj)*1000000 + 0.5);

        // Print the extracted values
        //printf("Latitude: %d\n", c.lat);
        //printf("Longitude: %d\n", c.lon);

        // Free memory after use
        json_object_put(dizionario);
        MQTTClient_freeMessage(&message);
        MQTTClient_free(topicName);
        return 1;
    } else {
        printf("Failed to parse JSON message.\n");
        return 0;
    }
}

coord start_mqtt() {
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;

    // Initialize the MQTT client
    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.cleansession = 1;
    conn_opts.keepAliveInterval = 20;
    MQTTClient_setCallbacks(client, NULL, NULL, messageArrived, NULL);

    // Connect to the broker
    if (MQTTClient_connect(client, &conn_opts) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect to MQTT broker!\n");
        c.lat = 0;
        c.lon = 0;
        return c;
    }

    printf("Connected to MQTT broker at %s\n", ADDRESS);

    // Subscribe to the topic
    MQTTClient_subscribe(client, TOPIC, QOS);
    printf("Subscribed to topic: %s\n", TOPIC);

    // Keep the program running to receive messages
    //while (1) {
    //    MQTTClient_yield();  // Sleep for 1 second
    //}

    // Cleanup (not reached in this example)
    MQTTClient_disconnect(client, TIMEOUT);
    MQTTClient_destroy(&client);

    return c;
}


