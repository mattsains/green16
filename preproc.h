#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int preproc(char infilename[], char outfilename[])
{
	FILE *fpr;
	FILE *fpw;

	//char infile[infilec];	
	//char outfile[outfilec];

	fpr = fopen(infilename, "r");
	fpw = fopen(outfilename, "w");

	if (fpr == NULL){
		fprintf(stderr, "Error opening input file\n");
		return 1; //close and report problem
	}
	
	const char * commands[] = {"add", "sub", "mul", "div", "shl", "shr", "ld", "st", "xor", "or", "and", "bnz", "lt", "le", "eq", "esc"};
	char line[20] = ""; 
	char scommand[20] = "";
	int icommand = 0;
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
}
