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
    char *data;
    char _data[6969];  //6 * 9 + 6 + 9 = 69
    int count;
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

size_t chstrlen (const char* s, char ch) 
{
	register const char* i;
	for(i=s; *i != ch; ++i);
	return (i-s);
}

void insertchild(node *parent, node *child)
{
	//I don't need this
}

void appendchild(node *parent, node *child)
{
	//I don't need this
}

node *getchildren(node *pp)
{
	node *master = pp;
	while(pp)
	{
		if(pp->parent == master)
		{
			p("%s", pp->data);
		}
		pp = pp->child;
	}
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
	p("Usage ./a.out data.txt query.txt");
	p("The root of the tree is assumed to be the first unique symbol in the file, if there are more, more trees will be created.");
	p("-----------------------------");
	p("");
	FILE* file = fopen(argv[1], "rb+");
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

	file = fopen(argv[2], "rb+");
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
					int count = 0;
					while(totl < len)
					{
						_len = sstrlen(&line[totl]);
						totl += _len;

						if((totl - _len) != 0)
						{
							//create bunch of milksuckers
							node->child = (struct node*)malloc(sizeof(struct node)); 
							node = node->child;
							node->parent = rover;
							node->child = NULL;
							node->data = node->_data;
							node->count = count; 
							memcpy(node->data, &line[totl-_len], _len);
							count++;
						}
					}


					//I can sort, but there is no point of doing this mess.

					//node = rover->child;
					//struct node *_node = rover->child;
					//while(node->parent == rover)
					//{
					//	while(_node->parent == rover)
					//	{
							//alpabetical;
					//		if(*_node->data > *node->data)
					//		{
								//char *tmp = node->data;
								//node->data = _node->data;
								//_node->data = tmp;

					//		}
					//		_node = _node->child;
					//	}
					//	node = node->child;
					//}
					goto continue_;
				}
				rover = rover->child;
			}	
		}

		//shitty tree root
		node* node = (struct node*)malloc(sizeof(struct node)); 
		vtree[vidx] = node;
		node->data = node->_data;
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
				node->data = node->_data;
				memcpy(node->data, &line[totl-_len], _len);
			}
		}
		vidx++;
		continue_:;
		line = strtok(0, "\n");
	}

	p("OUTPUT -----------------------------------------");

	line = strtok(strdup(buffer2), "\n");
	_len = 0;
	totl = 0;
	while(line)
	{
		int len = fstrlen(line);

		if(strstr(line, "GetEventsBySport"))
		{
			_len = sstrlen(line);

			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					//p("cmp %s, %s",rover->data, &line[_len]);
					//p("line %s", line);
					if(strstr(rover->data, &line[_len]))
					{
						//p("line %s", line);
						node *master = rover;
						rover = vtree[i]->child;
						printf("GetEventsBySport %s ", &line[_len]);
						while(rover)
						{
							if(rover->parent == master)
							{
								printf("%s", rover->data);
							}
							rover = rover->child;
						}
						printf("\n");
						break;
					}
					rover = rover->child;
				}	
			}

			goto _continue_;
		}
		if(strstr(line, "GetWinnersAndCountriesBySportAndEvent"))
		{
			_len = sstrlen(line);
			_len += sstrlen(&line[_len]);
			char *target = &line[_len];

			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					//p("cmp %s, %s",rover->data, target);
					//p("line %s", line);
					if(strstr(rover->data, target))
					{
						//p("line %s", line);
						node *master = rover;
						rover = vtree[i]->child;
						printf("GetWinnersAndCountriesBySportAndEvent %s ", getparent(master)->data);
						while(rover)
						{
							if(rover->parent == master)
							{
								printf("%s", rover->data);
							}
							rover = rover->child;
						}
						printf("\n");
						break;
					}
					rover = rover->child;
				}	
			}
			goto _continue_;
		}
		if(strstr(line, "GetGoldMedalistAndCountryBySportAndEvent"))
		{
			_len = sstrlen(line);
			_len += sstrlen(&line[_len]);
			char *target = &line[_len];

			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					//p("cmp %s, %s",rover->data, target);
					//p("line %s", line);
					if(strstr(rover->data, target))
					{
						//p("line %s", line);
						node *master = rover;
						rover = vtree[i]->child;
						printf("GetGoldMedalistAndCountryBySportAndEvent %s ", getparent(master)->data);
						while(rover)
						{
							if(rover->parent == master)
							{
								printf("%s", rover->data);
								break;
							}
							rover = rover->child;
						}
						printf("\n");
						break;
					}
					rover = rover->child;
				}	
			}
			goto _continue_;
		}
		if(strstr(line, "GetAthleteWithMostMedals"))
		{
//			char *target = "speedSkating"; //I have to assume here because no set is specified.

//MEGA HACK 6969: 
//Well i know something that these retards left constant, every player has : character in between 
//so instead of traversing the tree like an idiot, I will attach to that fact. I mean, I highly doubt 
//there ever will be an input without player's country and this makes implementation way faster too. 
			char *target = ":";
			int real_max = 0;
			node* result[69];
			int rnum = 0;
			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					if(strstr(rover->data, target))
					{
						node *_rover = vtree[i]->child;
						int max = 0;
						while(_rover)
						{
							if(strstr(_rover->data, rover->data))
							{
								max++;	
							}
							_rover = _rover->child;
						}
						if(max >= real_max && max > 1)
						{
							for(int i = 0; i < rnum; i++)
							{
								if(strstr(rover->data, result[i]->data))
								{
									goto skip;
								}
							}
							result[rnum] = rover;
							real_max = max;
							rnum++;
skip:;
						}
					}
					rover = rover->child;
				}	
			}
			printf("GetAthleteWithMostMedals %d ", rnum);
			for(int i = 0; i < rnum; i++)
			{
				for(int j = 0; j < rnum; j++)
				{
					//alpabetical;
					if(*result[j]->data > *result[i]->data)
					{
						node *tmp = result[i];
						result[i] = result[j];
						result[j] = tmp;

					}
				}
			}

			for(int i = rnum-1; i >= 0; i--)
			{
				int len = chstrlen(result[i]->data, ':');
				printf("%.*s ", len, result[i]->data);
			}
			printf("\n");

			goto _continue_;
		}
		if(strstr(line, "GetAthleteWithMostGoldMedals"))
		{
			char *target = ":";
			int real_max = 0;
			node* result[69];
			int rnum = 0;
			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					if(strstr(rover->data, target))
					{
						if(rover->count == 0)
						{
							result[rnum] = rover; //gold will be the second after root.
							rnum++;
						}
					}
					rover = rover->child;
				}	
			}
			printf("GetAthleteWithMostGoldMedals 1 ");
			for(int i = 0; i < rnum; i++)
			{
				for(int j = 0; j < rnum; j++)
				{
					//alpabetical;
					if(*result[j]->data > *result[i]->data)
					{
						node *tmp = result[i];
						result[i] = result[j];
						result[j] = tmp;

					}
				}
			}
			for(int i = 0; i < rnum; i++)
			{
				int len = chstrlen(result[i]->data, ':');
				printf("%.*s ", len, result[i]->data);
			}
			printf("\n");
			goto _continue_;
		}
		if(strstr(line, "GetCountryWithMostMedals"))
		{
			char *target = ":";
			int real_max = 0;
			node* result = NULL;
			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					if(strstr(rover->data, target))
					{
						node *_rover = vtree[i]->child;
						int max = 0;
						int len = chstrlen(rover->data, ':');
						char buf[len*5];
						memset(buf, 0, len*5);
						memcpy(buf, &rover->data[len], fstrlen(&rover->data[len]));
						while(_rover)
						{
							if(strstr(_rover->data, buf))
							{
								max++;	
							}
							_rover = _rover->child;
						}
						if(max >= real_max)
						{
							result = rover;
							real_max = max;
						}
					}
					rover = rover->child;
				}	
			}
			if(result)
			{
				int len = chstrlen(result->data, ':');
				p("GetCountryWithMostMedals %d %s", real_max, &result->data[len+1]);
			}
			goto _continue_;
		}
		if(strstr(line, "GetCountryWithMostGoldMedals"))
		{
			char *target = ":";
			int real_max = 0;
			node* result = NULL;
			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					if(strstr(rover->data, target))
					{
						node *_rover = vtree[i]->child;
						int max = 0;
						int len = chstrlen(rover->data, ':');
						char buf[len*5];
						memset(buf, 0, len*5);
						memcpy(buf, &rover->data[len], fstrlen(&rover->data[len]));
						while(_rover)
						{
							if(strstr(_rover->data, buf) && _rover->count == 0)
							{
								max++;	
							}
							_rover = _rover->child;
						}
						if(max >= real_max)
						{
							result = rover;
							real_max = max;
						}
					}
					rover = rover->child;
				}	
			}
			if(result)
			{
				int len = chstrlen(result->data, ':');
				p("GetCountryWithMostGoldMedals %d %s", real_max, &result->data[len+1]);
			}
			goto _continue_;
		}
		if(strstr(line, "GetSportAndEventByAthlete"))
		{
			_len = sstrlen(line);

			printf("GetEventsBySport %s ", &line[_len]);
			for(int i = 0; i < vidx; i++)
			{
				node *rover = vtree[i]->child;
				while(rover)
				{
					if(strstr(rover->data, &line[_len]))
					{
						if(rover->parent->parent)
						{
							printf("%s: %s", rover->parent->parent->data, rover->parent->data);
						}
					}
					rover = rover->child;
				}	
			}
			printf("\n");
			goto _continue_;
		}

		_continue_:;
		line = strtok(0, "\n");
	}
return 1;


}

