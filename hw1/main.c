/*

Author: Kyryl Melekhin
  Email kmelekhin2019@my.fit.edu
  Course: Data Structures
  Section: 14a

  Description of this file:

HW1


 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
  At the top of each function, describe the function, parameter(s), and return value (if any)
 */

typedef struct sellers
{
	char* name;
	struct sellers* next;
}sellers;

sellers* shead;

int main(int argc, char* argv[])
{
  /*
    description of declared variables, with meaningful names
   */
	FILE* file = fopen(argv[1], "rb+");
	if(!file)
	{
		printf("file not found\n");
		return 0;
	}

  
	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char buffer[length];
	size_t rc = fread(buffer, 1, length, file);
	fclose(file);


	char* line = strtok(strdup(buffer), "\n");
	while(line)
	{
		printf("%s\n", line);
		int len = strlen(line);
		if(strncmp(line, "SetShippingCost", 10) == 0)
		{
			shead = (sellers*) malloc(sizeof(sellers));
			shead->name = (char*) malloc(len);
		}

		line = strtok(0, "\n");
	}


  /*
    description of each "block" (about 5 lines of instructions)
   */
  
}

