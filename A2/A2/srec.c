#include "encoder.h"

void srecFunction(char* fileName) {
    // Check if file exists
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        // If file doesn't exist
        printf("No file found: %s\n", fileName);
    }
    else {
        // If file exists, close it
        fclose(file);
        // Add ".srec" extension if it doesn't already have it
        if (strstr(fileName, ".srec") == NULL) {
            strcat(fileName, ".srec");
        }

        // Create the new file with the ".srec" extension
        file = fopen(fileName, "w");
        if (file == NULL) {
            // Error opening the file
            printf("Can't open or create file: %s\n", fileName);
            return;
        }
        else {
            // If file opens successfully, you can write to it here
            printf("New file created: %s\n", fileName);
        }

        // Close the file
        fclose(file);
    }
}
