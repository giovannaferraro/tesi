#include "headermqtt.h"
#include "savelatency.h"
#ifdef MQTT_SUBSCRIPTION_H
#include <json-c/json.h>
#else
#error "JSON_LIB_1 not defined!"
#endif

coord c;
size_t i = 0;
char str1[25];

// Callback function for when connected to the broker
void on_connect(struct mosquitto *mosq, void *obj, int rc) {
    printf("Connected with result code %d\n", rc);
    if (rc == 0) {
        mosquitto_subscribe(mosq, NULL, "/haura/data", 2);
    } else {
        fprintf(stderr, "Failed to connect to broker. Error code: %d\n", rc);
    }
}

void on_subscribe(struct mosquitto *mosq, void *obj, int mid, int qos_count, const int *granted_qos) {
    printf("Subscribed to topic\n");
}

// Callback function for when a message is received on the subscribed topic
void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message) {
    //printf("Received message on topic %s: %s\n", message->topic, (char *)message->payload);
    
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // Parse the JSON data from the payload
    json_object *dizionario = json_tokener_parse((char *)message->payload);
    
    if (dizionario != NULL) {
        // Call the function to process the frame
        
        // Extract timestamp from the JSON object
        json_object *data_obj = json_object_object_get(dizionario, "data");
        json_object *head_obj = json_object_object_get(data_obj, "head");
        json_object *n_obj = json_object_object_get(data_obj, "nObjects");
        json_object *frameid = json_object_object_get(head_obj, "frameId");
        json_object *stamp_obj = json_object_object_get(head_obj, "stamp");

        ///////////////////////////////////////////////////////////////////////////////////////
        struct timeval pre;
        gettimeofday(&pre, NULL);
        struct json_object *objects_array = json_object_object_get(data_obj, "objects");

        // Get the first object in the array (index 0)
        struct json_object *first_object = json_object_array_get_idx(objects_array, 0);

        // Extract the latitude and longitude
        struct json_object *latitude_obj = json_object_object_get(first_object, "latitude");
        struct json_object *longitude_obj = json_object_object_get(first_object, "longitude");
        double latitude = json_object_get_double(latitude_obj);
        double longitude = json_object_get_double(longitude_obj);

        c.lat = (int)(json_object_get_double(latitude_obj)*1000000 + 0.5);
        c.lon = (int)(json_object_get_double(longitude_obj)*1000000 + 0.5);

        char new_str[14]; 
        const char *stamp_str = json_object_get_string(stamp_obj);
        strncpy(new_str, stamp_str, 13);
        new_str[13] = '\0';
        long glass_time = strtol(new_str, NULL, 10); // Assuming you want the timestamp as a float
        log_glasstime(glass_time, "glasstime1.txt");

        long milliseconds = tv.tv_sec * 1000 + tv.tv_usec / 1000;


        struct timeval post;
        gettimeofday(&post, NULL);
        long ms_pre = pre.tv_sec * 1000 + pre.tv_usec / 1000;
        long ms_post = post.tv_sec * 1000 + post.tv_usec / 1000;
        
        printf("tempo impiegato per estrarre lat lon calcolare glass time: %.10f\n", difftime(ms_post, ms_pre));
        ////////////////////////////////////////////////////////////////////////////////////
        
        // Convert stamp to float (as timestamp)
        
        const char *frame_str = json_object_get_string(frameid);

        double nobj = json_object_get_double(n_obj);
        printf("Tempo passato da frame a obu: %.2f e n obj %f and SIZE %d\n\n", difftime(milliseconds, glass_time), nobj, message->payloadlen);
        strcpy(str1, frame_str);
        strcat(str1, "7.txt");
        log_latency(difftime(milliseconds, glass_time), message->payloadlen, str1);
        memset(str1, '\0', sizeof(str1));
        json_object_put(dizionario);
    } else {
        printf("Failed to parse JSON message.\n");
        return;
    }
}

coord start_mqtt() {
    mosquitto_lib_init(); 
    
    // Create a new Mosquitto client
    struct mosquitto *mosq = mosquitto_new(NULL, true, NULL);

    if (!mosq) {
        fprintf(stderr, "Failed to create Mosquitto instance.\n");
        c.lat = 0;
        c.lon = 0;
        return c;
    }
    
    // Set callbacks
    mosquitto_connect_callback_set(mosq, on_connect);
    mosquitto_subscribe_callback_set(mosq, on_subscribe);
    mosquitto_message_callback_set(mosq, on_message);
    
    // Connect to the broker
    if (mosquitto_connect(mosq, "127.0.0.1", 1883, 10) != MOSQ_ERR_SUCCESS) {
        fprintf(stderr, "Unable to connect to broker.\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return c;
    }

    mosquitto_loop_start(mosq);

    pause();

    // To stop it cleanly before exiting:
    mosquitto_loop_stop(mosq, true);
    mosquitto_disconnect(mosq);  // Disconnect from the broker
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return c;
}