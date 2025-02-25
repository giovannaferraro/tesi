#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
