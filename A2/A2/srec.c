#include "encoder.h"

#define HEADER_NAME "NAV-DEB-HSL"  // Group name for the S0 header
#define MAX_DATA_BYTES 16          // Max bytes per S1 record



// Function to calculate checksum
unsigned char calculate_checksum(unsigned char count, unsigned short address, unsigned char* data, int data_len) {
    unsigned int sum = count + (address >> 8) + (address & 0xFF);
    for (int i = 0; i < data_len; i++) {
        sum += data[i];
    }
    return ~sum;  // One's complement
}



void write_srec(const char* inputFilename, const char* outputFilename) {
    FILE* inputFile = fopen(inputFilename, "rb");
    if (!inputFile) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    FILE* outputFile = fopen(outputFilename, "w");
    if (!outputFile) {
        perror("Error opening output file");
        fclose(inputFile);
        exit(EXIT_FAILURE);
    }

    // Write S0 header record
    unsigned char headerData[16] = { 0 };
    strncpy((char*)headerData, HEADER_NAME, 16);
    unsigned char s0_checksum = calculate_checksum(3 + strlen(HEADER_NAME), 0x0000, headerData, strlen(HEADER_NAME));
    fprintf(outputFile, "S0%02X0000", (unsigned)(3 + strlen(HEADER_NAME)));
    for (int i = 0; i < strlen(HEADER_NAME); i++) {
        fprintf(outputFile, "%02X", headerData[i]);
    }
    fprintf(outputFile, "%02X\n", s0_checksum);

    // Write S1 records
    unsigned char dataBuffer[MAX_DATA_BYTES];
    unsigned short address = 0;
    int bytesRead, s1Count = 0;

    while ((bytesRead = fread(dataBuffer, 1, MAX_DATA_BYTES, inputFile)) > 0) {
        unsigned char s1_checksum = calculate_checksum(3 + bytesRead, address, dataBuffer, bytesRead);
        fprintf(outputFile, "S1%02X%04X", (unsigned)(3 + bytesRead), address);
        for (int i = 0; i < bytesRead; i++) {
            fprintf(outputFile, "%02X", dataBuffer[i]);
        }
        fprintf(outputFile, "%02X\n", s1_checksum);
        address += MAX_DATA_BYTES;
        s1Count++;
    }

    // Write S5 record
    unsigned char s5_checksum = calculate_checksum(3, s1Count, NULL, 0);
    fprintf(outputFile, "S503%04X%02X\n", s1Count, s5_checksum);

    // Write S9 record (end of file)
    unsigned char s9_checksum = calculate_checksum(3, 0x0000, NULL, 0);
    fprintf(outputFile, "S9030000%02X\n", s9_checksum);

    fclose(inputFile);
    fclose(outputFile);
}