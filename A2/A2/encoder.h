/*
 * FILE          : encoder.h
 * PROJECT       : SENG2030 - SYSTEM PROGRAMMING
 * PROGRAMMER    : Hyungseop Lee (8948291) | Navtej Saini (8958194) | Elibe Deborah (8910192)
 * FIRST VERSION : 2025-02-02
 * DESCRIPTION   :
 *     This header file contains function prototypes and necessary includes for
 *     encoding binary files into S-Record (.srec) or Assembly (.asm) formats.
 *     It defines utility functions for file processing, checksum calculation, and
 *     format-specific conversions.
 */

#ifndef ENCODER_H
#define ENCODER_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

// Function Prototypes
unsigned char calculate_checksum(unsigned char count, unsigned short address, unsigned char* data, int data_len);
void write_srec(const char* inputFilename, const char* outputFilename);
void addExtension(char* inputFilename, char** outputFilename, int srec_format);
void stdIn(char* fileName);
void stdOut(void);
void convertToASM(char* filename, char* outputFile);
void generateASM(char* buffer, char* output, int bytes_read);

#endif // ENCODER_H