#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

FILE *fpr;
FILE *fpw;

int main(int argc, char *argv[])
{	
	if (argc < 3)
	{
		fprintf(stderr, "Usage: preproc16 <name.g16> <name.lst>\n");
		return 1; //close and report problem
	}

	fpr = fopen(argv[1], "r");
	fpw = fopen(argv[2], "w");

	if (fpr == NULL){
		fprintf(stderr, "Error opening input file\n");
		return 1; //close and report problem
	}

	const char * commands[] = {"add", "sub", "mul", "div", "shl", "shr", "ld", "st", "xor", "or", "and", "bnz", "lt", "le", "eq", "esc"};
	char line[20] = ""; 
	char scommand[20] = "";
	uint8_t icommand = 0;
	bool isnumber = false;
	int number = 0;	
	int x = 0;
	int y = 0;
	int z = 0;
	while (fgets(line, sizeof(line), fpr))
	{
		isnumber =  sscanf(line, "%d", &number ) ;
		if (isnumber)
		{
		   	fprintf(fpw, "0x%04x\n", number);
		}
		else
		{
			sscanf(line, "%s%x%x%x" , scommand, &x, &y, &z);
			int i;
			for (i = 0; i < 16; i++) {
				if (strcmp(commands[i], scommand) == 0)
				{
					icommand = i;
					break;					
				}					
			}			
			fprintf(fpw, "0x%x%x%x%x %s", icommand, x, y, z, line);
		}		
	}
	fclose(fpr);
	fclose(fpw);
    return 0;
}


