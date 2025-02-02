#ifndef ENCODER_H
#define ENCODER_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

// Function Prototypes
unsigned char calculate_checksum(unsigned char count, unsigned short address, unsigned char* data, int data_len);
void write_srec(const char* inputFilename, const char* outputFilename);
void testingSRC(char* input, char* output);
void testingASM(char* input, char* output);
void addExtension(char* inputFilename, char** outputFilename, int srec_format);
void stdIn(char* fileName);
void stdOut(void);
void convertToASM(char* filename, char* outputFile);

#endif // ENCODER_H