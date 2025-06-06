#include "/root/tesi/encode_asn_veroh/headermqtt_nano.h"
#include "savelatency.h"
using namespace simdjson;

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

// Global coord variable
coord latest_position = {0, 0};

// Message callback function
int message_callback(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long reception_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    
    // Process with simdjson
    simdjson::ondemand::parser parser;

    try {
        // Parse the message payload
        simdjson::padded_string json_data(payload, payloadlen);   
        simdjson::ondemand::document doc = parser.iterate(json_data);     
        // Extract timestamp directly
        int64_t message_time = doc["data"]["head"]["stamp"].get_int64();
        
        long message_time = std::stol(stamp_str.substr(0, 13));
        
        // Calculate latency
        long latency = reception_time - message_time;
        log_latency(latency, "test_simdjson.txt"); // Your existing function
        
        // Extract coordinates
        double latitude = double(doc["data"]["objects"].at(0)["latitude"]);
        double longitude = double(doc["data"]["objects"].at(0)["longitude"]);
        
        // Update the global position
        latest_position.lat = (int)(latitude * 1000000 + 0.5);
        latest_position.lon = (int)(longitude * 1000000 + 0.5);
        
        // Optional: Print latency
        std::cout << "Latency: " << latency << " ms" << std::endl;
        
    } catch (const simdjson::simdjson_error& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
    }
    
    // Clean up message resources
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    
    return 1;
}

// Rest of your code remains largely the same...
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