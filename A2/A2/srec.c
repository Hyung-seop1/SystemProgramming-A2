/*
 * FILE          : srec.c
 * PROJECT       : SENG2030 - SYSTEM PROGRAMMING
 * PROGRAMMER    : Hyungseop Lee (8948291) | Navtej Saini (8958194) | Elibe Deborah (8910192)
 * FIRST VERSION : 2025-02-02
 * DESCRIPTION   :
 *     This program converts a binary file into the Motorola S-Record (.srec) format.
 *     It processes the input file and generates the appropriate S-Record format,
 *     including S0 (header), S1 (data), S5 (count), and S9 (end) records.
 */

#include "encoder.h"

#define HEADER_NAME "NAV-DEB-HSL"  // Group name for the S0 header
#define MAX_DATA_BYTES 16          // Max bytes per S1 record

 /*
  * FUNCTION   : calculate_checksum
  * DESCRIPTION: This function calculates the checksum for an S-Record line by summing
  *              all the bytes in the record and taking the one's complement.
  * PARAMETERS :
  *   - count    : The total byte count of the record, including address and data.
  *   - address  : The memory address associated with the record.
  *   - data     : The pointer to the data bytes in the record.
  *   - data_len : The number of data bytes in the record.
  * RETURNS    : The computed one’s complement checksum as an unsigned char.
  */
unsigned char calculate_checksum(unsigned char count, unsigned short address, unsigned char* data, int data_len) {
    unsigned int sum = count + (address >> 8) + (address & 0xFF);
    for (int i = 0; i < data_len; i++) {
        sum += data[i];
    }
    return ~sum;  // One's complement
}

/*
 * FUNCTION   : write_srec
 * DESCRIPTION: This function reads a binary input file and writes its contents in
 *              Motorola S-Record format to the specified output file.
 *              It includes S0 (header), S1 (data), S5 (record count), and S9 (EOF) records.
 * PARAMETERS :
 *   - inputFilename  : The name of the binary input file.
 *   - outputFilename : The name of the output S-Record (.srec) file.
 * RETURNS    : VOID
 *              Outputs the formatted S-Record data to the specified output file.
 */
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