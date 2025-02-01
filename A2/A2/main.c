#include "encoder.h"

int main(int argc, char* argv[]) {
    char* inputFilename = NULL;
    char* outputFilename = NULL;
    int srec_format = 0; // Flag for S-Record format

    // Parse command-line arguments
    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "-h", 2) == 0) {
            // Print usage statement
            printf("Usage: encodeInput -iInputFile -oOutputFile -srec|-asm -h\n");
            return 0;
        }
        else if (strncmp(argv[i], "-i", 2) == 0) {
            // Extract input filename
            inputFilename = argv[i] + 2;  // Skip the "-i" part
            srecFunction(inputFilename);  // Check and process the input file
        }
        else if (strncmp(argv[i], "-o", 2) == 0) {
            outputFilename = argv[i] + 2; // Skip the "-o" part and get the filename
        }
        else if (strncmp(argv[i], "-srec", 5) == 0) {
            srec_format = 1;  // Set SREC format flag
        }
        else if (strncmp(argv[i], "-asm", 4) == 0) {
            // Default format, no action needed
        }
        else {
            printf("Usage: encodeInput -iInputFile -oOutputFile -srec|-asm -h\n");
            return 1;
        }
    }

    return 0;
}
