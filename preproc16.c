#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

FILE *fp;

int main(int argc, char *argv[])
{	
	if (argc < 3)
	{
		fprintf(stderr, "Usage: preproc16 <name.g16> <name.lst>\n");
		return 1; //close and report problem
	}

	fp = fopen(argv[1], "r");

	if (fp == NULL){
		fprintf(stderr, "Error opening input file\n");
		return 1; //close and report problem
	}

	char commands[16][3] = {"add", "sub", "mul", "div", "shl", "shr", "ld", "st", "xor", "or", "and", "bnz", "lt", "le", "eq", "esc"};
	char line[200]; //is this init to empty?
	bool isnumber = false;
	int16_t number;	
	uint8_t x;
	uint8_t y;
	uint8_t z;
	while (fgets(line, sizeof(line), fp))
	{
		int a = sscanf(line, "%x ",  &memory[mempos]) ;	
	}

	fclose(fp);
    return 0;
}


