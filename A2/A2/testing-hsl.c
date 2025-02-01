#include "encoder.h"

void testingSRC(char* input, char* output) {
	printf("SRC: %s \n%s", input, output);
}

void testingASM(char* input, char* output) {

    printf("ASM: %s | %s\n", input, output);

    // if "-i" is not provided...
    if (input == NULL) {
        FILE* file = fopen(output, "w");  // open output file
        if (file == NULL) {
            perror("Error opening output file");
            exit(1);
        }

        printf("Please enter the content after you type (press Ctrl+Z to end):\n"); // CTRL+Z IN WINDOWS, CTRL+D IN LINUX, just for testing

        char buffer[1024];  
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            fprintf(file, "%s", buffer); 
        }

        fclose(file);
    }

    if (input == NULL && output == NULL) {
        FILE* file = fopen(output, "w");  // open output file
        if (file == NULL) {
            perror("Error opening output file");
            exit(1);
        }

        printf("Please enter the content after you type (press Ctrl+Z to end):\n"); // CTRL+Z IN WINDOWS, CTRL+D IN LINUX, just for testing

        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            fprintf(file, "%s", buffer);
        }

        fclose(file);
    }
}
/*
* --------- DO NOT DELETE THIS !! -------------
* function for adding extensions
* 
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

            /*
            * NEED TO IMPLEMENT HERE FOR CONVERTING ASM | SREC
            */

            // Creating file that extension changed
            FILE* file = fopen(*outputFilename, "w");
            if (file == NULL) {
                perror("Error opening output file");
                exit(1);
            }
            printf("%s file created\n", *outputFilename);
            fclose(file);

        }
        else {
            printf("Error: No input file specified, and no output file provided.\n");
            exit(1);
        }
    }
}