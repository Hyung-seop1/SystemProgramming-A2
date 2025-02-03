/*
 * FILE          : main.c
 * PROJECT       : SENG2030 - SYSTEM PROGRAMMING
 * PROGRAMMER    : Hyungseop Lee (8948291) | Navtej Saini (8958194) | Elibe Deborah (8910192)
 * FIRST VERSION : 2025-02-02
 * DESCRIPTION   :
 *     This program is a Linux utility called "encodeInput" that converts binary
 *     input files into either S-Record (.srec) or Assembly (.asm) output files.
 *     It processes command-line arguments to determine the input file, output
 *     file, and desired format. If no arguments are provided, the program
 *     defaults to standard output handling.
 *
 *     Command-line options:
 *     - `-i<InputFile>`  : Specifies the input binary file.
 *     - `-o<OutputFile>` : Specifies the output file name.
 *     - `-srec`          : Converts the input file to S-Record format.
 *     - `-h`             : Displays usage information.
 *
 *     If the output file name is not provided, an appropriate extension is
 *     automatically added based on the selected format.
 *
 *     The program calls appropriate conversion functions (`write_srec` or
 *     `convertToASM`) depending on the specified format. If no valid input
 *     file is provided for S-Record conversion, an error message is displayed.
 */

#include "encoder.h"

int main(int argc, char* argv[]) {
    char* inputFilename = NULL;
    char* outputFilename = NULL;
    int srec_format = 0; // Flag for S-Record format
    int noArgument = 0;

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-h", 2) == 0) {
            // Print usage statement
            printf("Usage: encodeInput -iInputFile -oOutputFile -srec -h\n");
            return 0;
        }
        else if (strncmp(argv[i], "-i", 2) == 0) {
            inputFilename = argv[i] + 2;  // Skip the "-i" part
        }
        else if (strncmp(argv[i], "-o", 2) == 0) {
            outputFilename = argv[i] + 2; // Skip the "-o" part
        }
        else if (strncmp(argv[i], "-srec", 5) == 0) {
            srec_format = 1;  // Set SREC format flag
        }
        else {
            printf("Usage: encodeInput -iInputFile -oOutputFile -srec -h\n");
            return 1;
        }
    }

    // If no arguments are provided, call stdOut function
    if (argc == 1) {  // No command-line arguments except the program name
        stdOut();
    }
    else {
        // If no ouput file is provided add extenstion 
        //addExtension(inputFilename, &outputFilename, srec_format);

        // Perform conversion based on the selected format
        if (srec_format) {
            if (inputFilename) {
                // Automatically set output file to "<input>.srec" if not given
                if (!outputFilename) {
                    size_t len = strlen(inputFilename);
                    outputFilename = (char*)malloc(len + 6);
                    strcpy(outputFilename, inputFilename);
                    strcat(outputFilename, ".srec");
                }
                write_srec(inputFilename, outputFilename);
                //printf("S-Record file generated: %s\n", outputFilename);
            }
            else {
                printf("Please enter the content after you type (press Ctrl+Z to end):\n");
                write_srec(NULL, NULL);  // Process stdin and display output
            }
        }

        else {
            convertToASM(inputFilename, outputFilename); // ASM format conversion
        }
    }
    
    return 0;
}
