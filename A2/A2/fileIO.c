/*
 * FILE          : fileIO.c
 * PROJECT       : SENG2030 - SYSTEM PROGRAMMING
 * PROGRAMMER    : Hyungseop Lee (8948291) | Navtej Saini (8958194) | Elibe Deborah (8910192)
 * FIRST VERSION : 2025-02-02
 * DESCRIPTION   :
 *     This source file contains functions related to file I/O operations for encoding,
 *     such as adding file extensions, reading input from stdin, and writing output to files.
 */

#include "encoder.h"
#define MAX_DATA_BYTES 16

 /*
  * FUNCTION   : addExtension
  * DESCRIPTION: Appends the appropriate file extension to the output filename based on
  *              the selected format (SREC or ASM). If no output filename is provided,
  *              it generates a filename based on the input file name and adds the proper extension.
  * PARAMETERS :
  *   - inputFilename  : The name of the input file, used to generate the output file name.
  *   - outputFilename : Pointer to the output filename, which will be modified.
  *   - srec_format    : Flag indicating whether to append the `.srec` or `.asm` extension.
  * RETURNS    : VOID (Modifies outputFilename based on inputFilename and format).
  */
void addExtension(char* inputFilename, char** outputFilename, int srec_format) {
    if (*outputFilename == NULL) {  // If no output file indicated
        if (inputFilename != NULL) {
            size_t inputLen = strlen(inputFilename);
            *outputFilename = (char*)malloc(inputLen + (srec_format ? 5 : 4) + 1);

            strcpy(*outputFilename, inputFilename);  // copy outputFilename to inputFilename을

            if (srec_format) {
                strcat(*outputFilename, ".srec");  // if S-Record format append .srec
            }
            else {
                strcat(*outputFilename, ".asm");  // if ASM format append .asm
            }
        }
        else {
            printf("Error: No input file specified, and no output file provided.\n");
            exit(1);
        }
    }
}

/*
 * FUNCTION   : stdIn
 * DESCRIPTION: Reads content from standard input and writes it in a specified hex format to an output file.
 *              The content can be typed by the user, and the function handles the conversion of each byte
 *              into hexadecimal format and writes it to the provided file.
 * PARAMETERS :
 *   - fileName : Name of the output file where the data will be written.
 * RETURNS    : VOID (Writes hexadecimal representation of input to file).
 */
void stdIn(char* fileName) {

    FILE* file = fopen(fileName, "w");  // open output file
    if (file == NULL) {
        perror("Error opening output file");
        exit(1);
    }

    printf("Please enter the content after you type (press Ctrl+Z to end):\n"); // CTRL+Z IN WINDOWS, CTRL+D IN LINUX, just for testing

    char buffer[1024];
    int bytes_read;
    int remaining_bytes;
    while ((bytes_read = fread(buffer,1, sizeof(buffer), stdin))>0)
    {
        for (int i = 0; i < bytes_read; i += 16)
        {
            remaining_bytes = bytes_read - i;
            if(remaining_bytes>16)
                    fprintf(file, "$%02X", buffer[i]);  //Write the hex format into the file
        }
    }
    fclose(file);
}

