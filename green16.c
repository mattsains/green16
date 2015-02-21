#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>

#define PROGRAM_START 0x1 //0 used to halt
#define PC registers[0xc] 

//registers
int16_t registers[16];

//memory
int16_t memory[65536];

int main()
{
	//init registers
	registers[0x0] = 0; //const 0    
	registers[0x9] = -1; //const -1
	registers[0xD] = 2048; //stack arbitrarily at 2048
	registers[0xB] = 2048; //stack grows towards higher addresses
	registers[0xc] = PROGRAM_START; //program counter will start at PROGRAM_START

	bool running = true;

	FILE *fp;
	fp = fopen("program.lst", "r");

	if (fp == NULL){
		fprintf(stderr, "Error opening input file\n");
		exit(1); //close and report problem
	}
	
	//memory is read in from the start - must leave first line open
	//it's a good place to put a title
	uint16_t mempos = 0;
	char line[200];
	while (fgets(line, sizeof(line), fp))
	{
		sscanf(line, "%x ",  &memory[mempos]) ;
		mempos++;
	}		

	while(running)
	{
		uint16_t instruction = memory[PC];
		
		uint8_t opcode = instruction >> 12;
		uint8_t regX = (instruction & 0x0f00) >> 8;
		uint8_t regY = (instruction & 0x00f0) >> 4;
		uint8_t regZ = (instruction & 0x000f);   

		uint8_t pcInc = 1;
		bool niw = regY == 0xf || regZ == 0xf || regX == 0xf; 

		if (niw) 
		{
			pcInc = 2;			
			//only need to copy this if it might be used
			registers[0xF] = memory[PC + 1];			
		}
		else
			pcInc = 1;
		
		switch(opcode)
		{			
		case 0x0 : //add
			registers[regX] = registers[regY] + registers[regZ];
			PC+= pcInc;
			break;
		case 0x1 : //sub
			registers[regX] = registers[regY] - registers[regZ];
			PC+= pcInc;
			break;
		case 0x2 : //mul
			registers[regX] = registers[regY] * registers[regZ];
			PC+= pcInc;
			break;
		case 0x3 : //div
			registers[regX] = registers[regY] / registers[regZ];
			PC+= pcInc;
			break;
		case 0x4 : //shl
			registers[regX] = registers[regY] << registers[regZ];
			PC+= pcInc;
			break;
		case 0x5 : //sar
			registers[regX] = registers[regY] >> registers[regZ]; //TODO: check that this is an arithemetic shift
			PC+= pcInc;			
			break;
		case 0x6 : //ld
			registers[regX] = memory[(uint16_t)(registers[regY]+registers[regZ])];
			PC+= pcInc;
			break;
		case 0x7 : //st
			memory[(uint16_t)(registers[regY]+registers[regZ])] = registers[regX];
			PC+= pcInc;
			break; 
		case 0x8 : //xor
			registers[regX] = registers[regY] ^ registers[regZ];
			PC+= pcInc;
			break;
		case 0x9 : //or
			registers[regX] = registers[regY] | registers[regZ];
			PC+= pcInc;
			break;
		case 0xa : //and
			registers[regX] = registers[regY] & registers[regZ];
			PC+= pcInc;
			break;
		case 0xb : //bnz
			if (registers[regX] != 0)
			{
				registers[0xB] = PC; //Return address
				PC = (uint16_t)(registers[regY]+registers[regZ]);				
			}
			else
				PC+= pcInc;
			break;
		case 0xc : //lt
			registers[regX] = registers[regY] < registers[regZ];
			PC+= pcInc;
			break;
		case 0xd : //le
			registers[regX] = registers[regY] <= registers[regZ];
			PC+= pcInc;
			break;
		case 0xe : //eq			
			registers[regX] = registers[regY] <= registers[regZ];
			PC+= pcInc;
			break;
		case 0xf : //esc (print for now)
			printf("%d\n", memory[(uint16_t)(registers[regY]+registers[regZ])]);
			PC += pcInc;			
			break;
		}

		if (PC == 0)
			running = false;
	}
	
    return 0;
}



