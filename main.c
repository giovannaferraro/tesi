#include <utils.h>
#include "headermqtt.h"
#include "headersendcam.h"

coord c;


//QUESTO HEADER è QUELLO FINALE DA USARE NEL FILE C++: int generate_uper_string(int lat, int lon) {
int main() {
    struct timeval time;

    gettimeofday(&time, NULL);
    long time_before_submqtt = time.tv_sec * 1000 + time.tv_usec / 1000;
    //getting mqtt info
    coord i = start_mqtt();
    gettimeofday(&time, NULL);
    long time_after_submqtt = time.tv_sec * 1000 + time.tv_usec / 1000;
    printf("Tempo passato per sottoscriversi a mqtt: %.2f\n", difftime(time_after_submqtt, time_before_submqtt));

    gettimeofday(&time, NULL);
    long time_before_createcam = time.tv_sec * 1000 + time.tv_usec / 1000;
    //generating CAM asn
    CAM_t* cam = create_cam_message(i.lat, i.lon);
    //gettimeofday(&time, NULL);
    //long time_after_createcam = time.tv_sec * 1000 + time.tv_usec / 1000;
    //printf("Tempo passato per creare un cam asn: %.2f\n", difftime(time_after_createcam, time_before_createcam));


    if (!cam) {
        fprintf(stderr, "Failed to create CAM message\n");
        return 1;
    }
    
    asn_encode_to_new_buffer_result_t res = encode_cam_message(cam).r;
    char *hex_string = NULL;
    bin_to_hex(res.buffer, res.result.encoded, &hex_string);
    gettimeofday(&time, NULL);
    long afterencode = time.tv_sec * 1000 + time.tv_usec / 1000;

    printf("Tempo passato per fare encoding del cam: %.2f\n", difftime(afterencode, time_before_createcam));
    //printf("Tempo totale: %.2f\n\n\n", difftime(afterencode, time_before_submqtt));


    //int ret = send_cam(hex_string);
    //gettimeofday(&time, NULL);
    //long aftersend = time.tv_sec * 1000 + time.tv_usec / 1000;
    //printf("Tempo per create uper cam e json: %.2f\n", difftime(aftersend, time_before_createcam));
    

    free(hex_string); 

    ASN_STRUCT_FREE(asn_DEF_CAM, cam);

    return 0;
}