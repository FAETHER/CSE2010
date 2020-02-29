/*

Author: Kyryl Melekhin
  Email kmelekhin2019@my.fit.edu
  Course: Data Structures
  Section: 14a

  Description of this file:

HW3


 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <float.h>
/*
  At the top of each function, describe the function, parameter(s), and return value (if any)
 */

#define DEBUG

#ifdef DEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) \
		{ \
			printf("%s \n", message);\
			printf("Assertion %s failed in, %s line: %d \n", #condition, __FILE__, __LINE__);\
			char buf[10];					\
			fgets(buf, 10, stdin); \
			exit(1); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message)
#endif

typedef struct node
{
    struct node* parent; 
    struct node* child;
    char data[6969];  //6 * 9 + 6 + 9 = 69
}node;

float _fabs(float x)
{
	if (x < 0)
		x = -x;
	return(x);
}

char ctolower(char str)
{
        if(str >=65 && str<=90)
        {
            str = str + 32;
        }
	return str;
}

int p(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\n");
    fflush(stderr);
}

size_t fstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i; ++i);
	return (i-s);
}

int sstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i != ' '; ++i)
	{
		if(!*i || *i == '\n')
		{
			return (i-s)+1;
		}
	}
	return (i-s)+1;
}

size_t bsstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i != ' '; --i);
	return (s-i);
}

void insertchild(node *parent, node *child)
{
	
}

void appendchild(node *parent, node *child)
{
	
}

node *getchildren(node *p)
{
	
}

node *getparent(node *p)
{
	if(p->parent)
	{
		return p->parent; 
	}
	return NULL;
}

void eat_shit_and_die()
{
	//You deserve this, eat shit and die.
	while(1)
	{
		volatile void *p = malloc(6969);
		*(char*)(p) = 1;
		*(char*)(p+6969) = 1; //touch the tables to ensure paging.
	}
}

int main(int argc, char* argv[])
{
  /*
    description of declared variables, with meaningful names
   */
	p("Usage ./a.out queryfile.txt datafile.txt");
	p("The root of the tree is assumed to be the first unique symbol in the file, if there are more, more trees will be created.");
	p("-----------------------------");
	p("");
	FILE* file = fopen(argv[2], "rb+");
	if(!file)
	{
		p("file not found");
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char buffer[length];
	memset(buffer, 0, length);
	size_t rc = fread(buffer, 1, length, file);
	fclose(file);

	file = fopen(argv[1], "rb+");
	if(!file)
	{
		p("file not found");
		return 0;
	}

	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	char buffer2[length];
	memset(buffer2, 0, length);
	rc = fread(buffer2, 1, length, file);
	fclose(file);

	char* line = strtok(strdup(buffer), "\n");
	int _len = 0;
	int totl = 0;
	node *vtree[69];
	int vidx = 0;
	while(line)
	{
		int len = fstrlen(line);
		_len = sstrlen(line);

		for(int i = 0; i < vidx; i++)
		{
			node *rover = vtree[i]->child;
			while(rover)
			{
				//p("cmp %s, ",rover->data);
				//p("line %s", line);
				if(strncmp(line, rover->data, _len-1) == 0)
				{
					p("Linking %s", line);

					node* node = rover;
					//all the way back
					while(node->child)
					{
						node = node->child;
					}

					totl = 0;
					while(totl < len)
					{
						_len = sstrlen(&line[totl]);
						totl += _len;

						if((totl - _len) != 0)
						{
							//create bunch of shit children
							node->child = (struct node*)malloc(sizeof(struct node)); 
							node = node->child;
							node->parent = rover;
							node->child = NULL;
							memcpy(node->data, &line[totl-_len], _len);
						}
					}
					goto continue_;
				}
				rover = rover->child;
			}	
		}

		//shitty tree root
		node* node = (struct node*)malloc(sizeof(struct node)); 
		vtree[vidx] = node;
		memcpy(node->data, line, _len);
		p("Info: Using %s as root", node->data);
		node->child = NULL;
		node->parent = NULL;

		totl = 0;
		while(totl < len)
		{
			_len = sstrlen(&line[totl]);
			totl += _len;

			if((totl - _len) != 0)
			{
				//create bunch of shit children
				node->child = (struct node*)malloc(sizeof(struct node)); 
				node = node->child;
				node->parent = vtree[vidx];
				node->child = NULL;
				memcpy(node->data, &line[totl-_len], _len);
			}
		}
		vidx++;
		continue_:;
		line = strtok(0, "\n");
	}

	line = strtok(strdup(buffer2), "\n");
	_len = 0;
	totl = 0;
	while(line)
	{
		int len = fstrlen(line);
		_len = sstrlen(line);

		if(strstr(line, "GetEventsBySport"))
		{
			goto _continue_;
		}
		if(strstr(line, "GetWinnersAndCountriesBySportAndEvent"))
		{

			goto _continue_;
		}
		if(strstr(line, "GetGoldMedalistAndCountryBySportAndEvent"))
		{

			goto _continue_;
		}
		if(strstr(line, "GetAthleteWithMostGoldMedals"))
		{

			goto _continue_;
		}
		if(strstr(line, "GetAthleteWithMostMedals"))
		{

			goto _continue_;
		}
		if(strstr(line, "GetCountryWithMostMedals"))
		{

			goto _continue_;
		}
		if(strstr(line, "GetCountryWithMostGoldMedals"))
		{

			goto _continue_;
		}
		if(strstr(line, "GetSportAndEventByAthlete"))
		{

			goto _continue_;
		}

		_continue_:;
		line = strtok(0, "\n");
	}
return 1;


}

