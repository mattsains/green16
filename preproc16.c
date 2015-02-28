#include "preproc.h"

int main(int argc, char *argv[])
{	
	if (argc < 3)
	{
		fprintf(stderr, "Usage: preproc16 <name.g16> <name.lst>\n");
		return 1; //close and report problem
	}

	preproc(argv[1], argv[2]);
	 
	return 0;
}


