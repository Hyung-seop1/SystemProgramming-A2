#include "encoder.h"

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
			stdOut(filename);
		}
		FILE* output = fopen(outputFile, "w");
		if (output == NULL)
		{
			printf("error opening file for reading");
			return -1;
		}
	unsigned char buffer[1024] = { 0 };
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

void stdOut(void) {
	printf("Please enter the content after you type (press Ctrl+Z to end):\n"); // CTRL+Z IN WINDOWS, CTRL+D IN LINUX, just for testing
	FILE* output = stdout;
	char buffer[1024];
	int bytes_read = 0;
	while ((bytes_read = fread(buffer, 1, sizeof(buffer), stdin)) > 0)
	{
		generateASM(buffer, output, bytes_read);
	}
}

void generateASM(char* buffer, char* output, int bytes_read)
{
	int maxSize = 0;
	int remaining_bytes = 0;
	for (int offset = 0; offset < bytes_read; offset += 16)
	{
		remaining_bytes = bytes_read - offset;
		if (remaining_bytes > 16)
		{
			maxSize = 16;
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
		fprintf(output, "\n");
	}
}