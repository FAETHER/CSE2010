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
#include <stdarg.h>
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

size_t sstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i != ' '; ++i);
	return (i-s);
}

size_t bsstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i != ' '; --i);
	return (s-i);
}

typedef struct sellers
{
	char* name;
	float scost;
	float mffs;
	struct sellers* next;
}sellers;

typedef struct prod
{
	char* name;
	float price;
	int quan;
	sellers* seller;
	struct prod* next;
}prod;


int main(int argc, char* argv[])
{
  /*
    description of declared variables, with meaningful names
   */
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


	sellers* shead = (sellers*) malloc(sizeof(sellers));
	memset(shead, 0, sizeof(sellers));
	sellers* srv = shead;
	srv->next = NULL;

	prod* phead = (prod*) malloc(sizeof(prod));
	memset(phead, 0, sizeof(prod));
	prod* prv = phead;
	prv->next = NULL;

	char* line = strtok(strdup(buffer), "\n");
	while(line)
	{
		//p("%s", line);
		int len = fstrlen(line);
		if(strstr(line, "SetShippingCost") != NULL)
		{
			srv->name = (char*) malloc(len);
			int start = sstrlen(line)+1;
			int end = sstrlen(&line[start]);
			memcpy(srv->name, &line[start], end);

			srv->scost = atof(&line[start+end]);
			end = bsstrlen(&line[len]);
			srv->mffs = atof(&line[len-end]);
			p("SetShippingCost %s %.1f %.1f", srv->name, srv->scost, srv->mffs);
			srv->next = (sellers*) malloc(sizeof(sellers));
			memset(srv->next, 0, sizeof(sellers));
			srv = srv->next;
		}

		if(strstr(line, "SetProductPrice") != NULL)
		{
			prv->name = (char*) malloc(len);
			int start = sstrlen(line)+1;
			int end = sstrlen(&line[start]);
			memcpy(prv->name, &line[start], end);

			int _end = sstrlen(&line[start+end+1]);
			sellers* _srv = shead;
			while(_srv->name)
			{
				if(strncmp(_srv->name, &line[start+end+1], _end) == 0)
				{
					prv->seller = _srv;
					break;
				}
				_srv = _srv->next;
			}
			ASSERT(prv->seller, "failed to find seller for item...");
			end = bsstrlen(&line[len]);
			prv->price = atof(&line[len-end]);

			p("SetProductPrice %s %s %.1f", prv->name, prv->seller->name, prv->price);
			prv->next = (prod*) malloc(sizeof(prod));
			memset(prv->next, 0, sizeof(prod));
			prv = prv->next;
		}
		if(strstr(line, "IncreaseInventory") != NULL)
		{
			int start = sstrlen(line)+1;
			int end = sstrlen(&line[start]);
			prod* _prv = phead;
			while(_prv->name)
			{
				if(strncmp(_prv->name, &line[start], end) == 0)
				{
					int _end = sstrlen(&line[start+end+1]);
					if(strncmp(_prv->seller->name, &line[start+end+1], _end) == 0)
					{
						_end = bsstrlen(&line[len]);
						int num = atoi(&line[len-_end]);
						_prv->quan += num;
						p("IncreaseInventory %s %s %d %d", _prv->name, _prv->seller->name, num, _prv->quan);
					}
				}
				_prv = _prv->next;
			}

		}
		if(strstr(line, "CustomerPurchase") != NULL)
		{
			int start = sstrlen(line)+1;
			int end = sstrlen(&line[start]);
			prod* _prv = phead;
			while(_prv->name)
			{
				if(strncmp(_prv->name, &line[start], end) == 0)
				{
					int _end = sstrlen(&line[start+end+1]);
					if(strncmp(_prv->seller->name, &line[start+end+1], _end) == 0)
					{
						_end = bsstrlen(&line[len]);
						int num = atoi(&line[len-_end]);
						if(_prv->quan - num < 0)
						{
							p("CustomerPurchase %s %s %d check your supply, retard", _prv->name, _prv->seller->name, num);
						}
						else
						{
							_prv->quan -= num;
							p("CustomerPurchase %s %s %d %d", _prv->name, _prv->seller->name, num, _prv->quan);
						}
					}
				}
				_prv = _prv->next;
			}
		}
		if(strstr(line, "DisplaySellerList") != NULL)
		{
			int start = sstrlen(line)+1;
			int end = strlen(&line[start]);
			prod* _prv = phead;
			char* prev = NULL;
			while(_prv->name)
			{
				if(strncmp(_prv->name, &line[start], end) == 0)
				{
					float totalc;
					if(prev)
					{
						if(strcmp(_prv->name, prev) == 0)
						{
							goto skip_head;
						}
					}
					p("DisplaySellerList %s", _prv->name);
					p("    seller  productPrice  shippingCost  totalCost");
skip_head:;
					printf("   %s", _prv->seller->name);
					printf("        %.2f", _prv->price);
					if(_prv->price >= _prv->seller->mffs)
					{
						printf("          0.00");
						totalc = _prv->price;
					}
					else
					{
						printf("          %.2f", _prv->seller->scost);
						totalc = _prv->price + _prv->seller->scost;
					}
					printf("     %.2f\n", totalc);
					prev = _prv->name;
				}
				_prv = _prv->next;
			}
		}
		line = strtok(0, "\n");
	}


  /*
    description of each "block" (about 5 lines of instructions)
   */
  
}

