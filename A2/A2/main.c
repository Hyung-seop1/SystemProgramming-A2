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
