#include "encoder.h"

int main(int argc, char* argv[]) {
    char* inputFilename = NULL;
    char* outputFilename = NULL;
    int srec_format = 0; // Flag for S-Record format

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
        else if (argc == 1) {
            // If there is no argument
            // Default format(ASM), no action needed
        }
        else {
            printf("Usage: encodeInput -iInputFile -oOutputFile -srec -h\n");
            return 1;
        }
    }

    // If no ouput file is provided add extenstion 
    addExtension(inputFilename, &outputFilename, srec_format);

    // Perform conversion based on the selected format
    if (srec_format) {
        testingSRC(inputFilename, outputFilename); // S-Record format conversion
    }
    else {
        if (inputFilename == NULL && outputFilename == NULL) {
            // add function here for converting ASM
        }
        testingASM(inputFilename, outputFilename); // ASM format conversion
    }

    return 0;
}
