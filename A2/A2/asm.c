/*
 * FILE          : asm.c
 * PROJECT       : SENG2030 - SYSTEM PROGRAMMING
 * PROGRAMMER    : Hyungseop Lee (8948291) | Navtej Saini (8958194) | Elibe Deborah (8910192)
 * FIRST VERSION : 2025-02-02
 * DESCRIPTION   :
 *     This program is part of a system programming project that converts binary input files
 *     into either S-Record (.srec) or Assembly (.asm) output formats. It processes input
 *     files and writes their hexadecimal representation to the output file in the selected format.
 *
 *     Features:
 *     - Reads binary data from a file or standard input.
 *     - Converts the data into assembly format (`dc.b` directives).
 *     - Writes the formatted data to an output file or standard output.
 *
 *     Functions:
 *     - convertToASM() : Converts a binary file to an Assembly format.
 *     - stdOut()       : Reads input from stdin and outputs the converted ASM data.
 *     - generateASM()  : Formats binary data as Assembly `dc.b` directives and writes to output.
 */

#include "encoder.h"

#define BUFFER_SIZE 1024
#define MAX_BYTES 16


 /*
  * FUNCTION   : convertToASM
  * DESCRIPTION: This function reads a binary input file and converts its contents into an
  *              Assembly (.asm) formatted file. The output consists of `dc.b` directives
  *              containing the hexadecimal representation of the binary data.
  * PARAMETERS :
  *   - filename    : The name of the binary input file.
  *   - outputFile  : The name of the output Assembly file.
  * RETURNS    : VOID
  *              Outputs the formatted Assembly content to the specified file or standard output.
  */
void convertToASM(char* filename, char* outputFile)
{
	FILE* fp = stdin;
		if (filename)
		{
			fp = fopen(filename, "rb");

			if (filename == NULL)
			{
				printf("error opening file for reading");
				exit(-1);
			}
	    }
		if (outputFile == NULL)
		{
			stdOut();
		}
		FILE* output = fopen(outputFile, "w");
		if (output == NULL)
		{
			printf("error opening file for reading");
			return -1;
		}
	unsigned char buffer[BUFFER_SIZE] = { 0 };
	int bytes_read = 0;

	while ((bytes_read = fread(buffer,1, sizeof(buffer), fp)) > 0)
	{
		generateASM(buffer, output, bytes_read);
	}
	fclose(output);
	if (fp!= stdin)
	{
		fclose(fp);
	}
	
}

/*
 * FUNCTION   : stdOut
 * DESCRIPTION: This function reads binary data from the standard input (stdin) and writes
 *              the formatted Assembly output to the standard output (stdout).
 * PARAMETERS : None
 * RETURNS    : VOID
 *              Outputs the converted Assembly format to stdout.
 */
void stdOut(void) {
	FILE* output = stdout;
	unsigned char buffer[1024];
	int bytes_read = 0;
	while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0)
	{
		generateASM(buffer, output, bytes_read);
	}
}

/*
 * FUNCTION   : generateASM
 * DESCRIPTION: This function converts a given buffer of binary data into an Assembly
 *              `dc.b` format and writes it to the output file or standard output.
 * PARAMETERS :
 *   - buffer     : The buffer containing binary data to convert.
 *   - output     : The output stream (file or stdout) where the formatted data is written.
 *   - bytes_read : The number of bytes to process in the buffer.
 * RETURNS    : VOID
 *              Outputs formatted Assembly representation of the binary data.
 */
void generateASM(char* buffer, char* output, int bytes_read)
{
	int maxSize = 0;
	int remaining_bytes = 0;
	for (int offset = 0; offset < bytes_read; offset += MAX_BYTES)
	{
		remaining_bytes = bytes_read - offset;
		if (remaining_bytes > MAX_BYTES)
		{
			maxSize = MAX_BYTES;
		}
		else
		{
			maxSize = remaining_bytes;
		}
		fprintf(output, "dc.b\t");  //Write the hex format into the file
		for (int i = 0; i < maxSize; i++)
		{
			fprintf(output, "$%02X", buffer[offset + i]);
			if (i < maxSize - 1)
			{
				fprintf(output, ", ");
			}
		}
	}
}