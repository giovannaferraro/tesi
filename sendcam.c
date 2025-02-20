//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <openssl/sha.h>
//#include <jansson.h>
//#include <curl/curl.h>

#include "headersendcam.h"
#ifdef FILE2_H
#include <jansson.h>
#else
#error "JSON_LIB_1 not defined!"
#endif

#define USERNAME "root"
#define PASSWORD "v2x"

// SHA-256 hash function
char* calculate_sha256(const char* input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, input, strlen(input));
    SHA256_Final(hash, &sha256_ctx);

    // Convert the hash to a hexadecimal string
    char* hash_string = malloc(SHA256_DIGEST_LENGTH * 2 + 1);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(&hash_string[i * 2], "%02x", hash[i]);
    }

    return hash_string;
}

int send_cam(char* UPER) 
{
    // Initialize variables
    const char* messageID = "2";
    const char* timestamp = "Thu Mar 11 17:21:11 CET 2024";
    const char* messageBodyFormat = "UPER";
    const char* messageType = "CAM";
    const char* messageDirection = "Upstream";
    int repetitionDuration = 600;
    int repetitionInterval = 1000;
    const char* messageBody = UPER;
    
    // Calculate hash
    char* hash = calculate_sha256(messageBody);

    // Create JSON object
    json_t* root = json_object();
    json_object_set_new(root, "messageId", json_string(messageID));
    json_object_set_new(root, "timestamp", json_string(timestamp));
    json_object_set_new(root, "hash", json_string(hash));
    json_object_set_new(root, "messageBodyFormat", json_string(messageBodyFormat));
    json_object_set_new(root, "messageType", json_string(messageType));
    json_object_set_new(root, "messageDirection", json_string(messageDirection));
    json_object_set_new(root, "repetitionDuration", json_integer(repetitionDuration));
    json_object_set_new(root, "repetitionInterval", json_integer(repetitionInterval));
    json_object_set_new(root, "messageBody", json_string(messageBody));

    // Convert JSON object to string
    char* json_str = json_dumps(root, 0);

    // Setup the HTTP client using libcurl
    CURL *curl;
    CURLcode res;

    const char* ip_address = "192.168.12.122";  // Replace with actual IP address

    // Initialize curl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set up HTTP POST request
        char url[256];
        snprintf(url, sizeof(url), "http://%s/proxy/msg", ip_address);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_USERPWD, USERNAME ":" PASSWORD);


        //struct curl_slist *headers = NULL;
        //headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set the URL, HTTP headers, and POST data
        //curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_str);

        // Set Basic Authentication
        

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "Curl request failed: %s\n", curl_easy_strerror(res));
        } else {
            // Get HTTP response code and print the response
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("Response status: %ld\n", response_code);
        }

        // Clean up
        curl_easy_cleanup(curl);
        //curl_slist_free_all(headers);
    }
    
    //Clean up JSON and hash
    json_decref(root);
    free(json_str);
    free(hash);

    // Clean up curl globally
    curl_global_cleanup();

    return 0;
}
