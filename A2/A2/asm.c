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
		FILE* output = fopen(outputFile, "w");
		if (output == NULL)
		{
			printf("error opening file for reading");
			return -1;
		}
	unsigned char buffer[1024] = { 0 };
	int bytes_read = 0;
	int remaining_bytes = 0;
	int maxSize = 0;

	while ((bytes_read = fread(buffer,1, sizeof(buffer), fp)) > 0)
	{
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
				fprintf(output, "$%02X", buffer[offset +i]);
				if (i < maxSize - 1)
				{
					fprintf(output, ", ");
				}
			}
			fprintf(output, "\n");
		}
	}
	
	if (fp!= stdin)
	{
		fclose(fp);
	}
	fclose(output);
	
}