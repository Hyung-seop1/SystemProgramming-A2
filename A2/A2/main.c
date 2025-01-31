#include "encoder.h"


int main(int argc, char* argv[]) {

	// If Command is "-h" display usage statement and exit the program
	if (argc == 2 && strcmp(argv[1], "-h") == 0) {
		printf("Usage: encodeInput [-iinputFile] [-ooutputFile] [-srec | -asm]\n");
		return 0;
	}

	return 0;
}

