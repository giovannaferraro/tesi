#include "headermqtt.h"
#ifdef MQTT_SUBSCRIPTION_H
#include <json-c/json.h>
#else
#error "JSON_LIB_1 not defined!"
#endif

#define MQTT_HOST "127.0.0.1"
#define MQTT_PORT 1883
#define MQTT_TOPIC "/haura/data"

coord c;
int i = 0;

void log_latency(float latency) {
    // Open file in append mode
    FILE *file = fopen("latency_data_2.txt", "a");
    
    // Check if the file opened successfully
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the float value to the file with 3 decimal precision
    fprintf(file, "%.3f\n", latency);

    // Close the file
    fclose(file);
}

// Callback function for when connected to the broker
void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    if (rc == 0) {
        printf("Connected to broker\n");
        mosquitto_subscribe(mosq, NULL, MQTT_TOPIC, 0);
    } else {
        fprintf(stderr, "Connection failed: %d\n", rc);
    }
}

// Callback function for when a message is received
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // Parse JSON
    json_object *root = json_tokener_parse((char *)message->payload);
    if (!root) {
        fprintf(stderr, "JSON parsing failed\n");
        return;
    }

    json_object *data = json_object_object_get(root, "data");
    json_object *head = json_object_object_get(data, "head");
    json_object *stamp = json_object_object_get(head, "stamp");

    // Convert timestamp from JSON
    const char *stamp_str = json_object_get_string(stamp);
    char new_str[14]; 
    strncpy(new_str, stamp_str, 13);
    new_str[13] = '\0';
    long glass_time = strtol(new_str, NULL, 10);

    long current_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;  // Current time in milliseconds

    printf("T1 - T0 = da frame a mqtts: %.6f\n", difftime(current_time, glass_time));
    log_latency(difftime(current_time, glass_time));
    i += 1;

    // Extract coordinates
    json_object *objects = json_object_object_get(data, "objects");
    if (json_object_array_length(objects) > 0) {
        json_object *first_obj = json_object_array_get_idx(objects, 0);
        json_object *lat_obj = json_object_object_get(first_obj, "latitude");
        json_object *lon_obj = json_object_object_get(first_obj, "longitude");

        c.lat = (int)(json_object_get_double(lat_obj) * 1000000 + 0.5);
        c.lon = (int)(json_object_get_double(lon_obj) * 1000000 + 0.5);
        printf("Latitude: %d\n", c.lat);
        printf("Longitude: %d\n", c.lon);
    }

    json_object_put(root);  // Free JSON object
    if (i==500){
        i=0;
        mosquitto_disconnect(mosq);
    }
    
}

//Start the MQTT client
coord start_mqtt() {
    mosquitto_lib_init();
    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Mosquitto initialization failed\n");
        c.lat = 0;
        c.lon = 0;
        return c;
    }

    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_message_callback_set(mosq, on_message);

    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "MQTT connection failed\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return c;
    }

    mosquitto_loop_forever(mosq, -1, 1);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return c;
}
