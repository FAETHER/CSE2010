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

size_t fstrlen (const char* s) 
{
	register const char* i;
	for(i=s; *i; ++i);
	return (i-s);
}

void p(const char *format, ...)
{
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	va_list args;
	va_start(args, format);
	vsprintf(&buf[0], format, args);
	va_end(args);

	int len = fstrlen(buf);
	if(buf[len] == '\n')
	{
		buf[len] = '\0';
	}
	if(buf[len-1] == '\n')
	{
		buf[len-1] = '\0';
	}
	puts(buf);
	fflush(stdout);
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

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "rb+");
	if(!file)
	{
		p("file not found");
		return 0;
	}

	char str[1024];
	memset(str, 0, sizeof(str)); 
	int len;

	while(fgets(str, sizeof(str), file))
	{
		p("%s", str);	
	}
}
