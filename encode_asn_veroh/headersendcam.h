#ifndef FILE2_H
#define FILE2_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>
//#include <jansson.h>
#include <curl/curl.h>

char* calculate_sha256(const char* input);
int send_cam(char* UPER);

#endif