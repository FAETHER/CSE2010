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
#include <stdint.h>
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

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef int32_t b32;

typedef float f32;
typedef double f64;

#if !__cplusplus
#define false 0
#define true 1
#endif


double _fabs(double x)
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

typedef struct buy_t
{
	u64 Time;
	char Buyer[1024];
	double Price;
	u32 Quantity;
	u32 QBought; //how much she already ackqired
}buy_t;

typedef struct sell_t
{
	u64 Time;
	char Seller[1024];
	double Price;
	u32 Quantity;
}sell_t;

typedef struct buyerhitstack_t
{
	char Name[1024];
}buyerhitstack_t;

buyerhitstack_t BHitstack[1024]; //optional for if reversed file position, aka seller came before buyer.
buyerhitstack_t SHitstack[1024]; // terrible slow implementation, but an extra safecheck for me will never hurt
//always remember: you are retarded.
buy_t BuyOrders[1024];
sell_t SellOrders[1024];
u64 Bcount;
u64 Scount;
u64 Bhitstackcount;
u64 Shitstackcount;

int main(int argc, char* argv[])
{
	FILE* file = fopen(argv[1], "rb+");
	if(!file)
	{
		p("file not found");
		return 0;
	}

	char line[1024];
	memset(line, 0, sizeof(line)); 
	u32 len;
	u32 _len;
	u32 totl;

	while(fgets(line, sizeof(line), file))
	{
		len = fstrlen(line);

		if(strstr(line, "EnterBuyOrder"))
		{
			//p("%s", line);	
			totl = 0;
			u32 count = 0;
			while(totl < len)
			{
				_len = sstrlen(&line[totl]);
				totl += _len;

				if((totl - _len) != 0)
				{
					//p("%s", &line[totl - _len]);
					if(count == 0)
					{
						BuyOrders[Bcount].Time = atoi(&line[totl-_len]);			
						//p("Time: %d", BuyOrders[Bcount].Time);
					}
					else if(count == 1)
					{
						memcpy(&BuyOrders[Bcount].Buyer, &line[totl - _len], _len);
					//	p("Buyer: %s", BuyOrders[Bcount].Buyer);
					}
					else if(count == 2)
					{
						BuyOrders[Bcount].Price = atof(&line[totl-_len]);			
						//p("Price: %lf", BuyOrders[Bcount].Price);
					}
					else if(count == 3)
					{
						BuyOrders[Bcount].Quantity = atoi(&line[totl-_len]);			
//						p("Quantity: %d", BuyOrders[Bcount].Quantity);
					}
					count++;
				}
			}
			Bcount++;
			continue;
		}

		if(strstr(line, "EnterSellOrder"))
		{
			//p("%s", line);	
			totl = 0;
			u32 count = 0;
			while(totl < len)
			{
				_len = sstrlen(&line[totl]);
				totl += _len;

				if((totl - _len) != 0)
				{
					//p("%s", &line[totl - _len]);
					if(count == 0)
					{
						SellOrders[Scount].Time = atoi(&line[totl-_len]);			
						//p("Time: %d", SellOrders[Scount].Time);
					}
					else if(count == 1)
					{
						memcpy(&SellOrders[Scount].Seller, &line[totl - _len], _len);
					//	p("Seller: %s", SellOrders[Scount].Buyer);
					}
					else if(count == 2)
					{
						SellOrders[Scount].Price = atof(&line[totl-_len]);			
					//	p("Price: %lf", SellOrders[Scount].Price);
					}
					else if(count == 3)
					{
						SellOrders[Scount].Quantity = atoi(&line[totl-_len]);			
						//p("Quantity: %d", SellOrders[Scount].Quantity);
					}
					count++;
				}
			}
			Scount++;
			continue;
		}
	}

	b32 swapped;
	for(u32 i = 0; i < Bcount - 1; i++)
	{
		swapped = 0;
		for(u32 j = 0; j < Bcount - i -1; j++)
		{
			if(BuyOrders[j].Time > BuyOrders[j+1].Time)
			{
				buy_t tmp;
				memcpy(&tmp, &BuyOrders[j], sizeof(buy_t));
				memcpy(&BuyOrders[j], &BuyOrders[j+1], sizeof(buy_t));
				memcpy(&BuyOrders[j+1], &tmp, sizeof(buy_t));
				swapped = 1;
			}
		}
		if(!swapped)
		{
			break;
		}
	}

	for(u32 i = 0; i < Scount - 1; i++)
	{
		swapped = 0;
		for(u32 j = 0; j < Scount - i -1; j++)
		{
			if(SellOrders[j].Time > SellOrders[j+1].Time)
			{
				sell_t tmp;
				memcpy(&tmp, &SellOrders[j], sizeof(sell_t));
				memcpy(&SellOrders[j], &SellOrders[j+1], sizeof(sell_t));
				memcpy(&SellOrders[j+1], &tmp, sizeof(sell_t));
				swapped = 1;
			}
		}
		if(!swapped)
		{
			break;
		}
	}

	fseek(file, 0, SEEK_SET);
	while(fgets(line, sizeof(line), file))
	{
		len = fstrlen(line);
		if(strstr(line, "DisplayHighestBuyOrder"))
		{
			totl = 0;
			u32 count = 0;
			u64 Time;
			while(totl < len)
			{
				_len = sstrlen(&line[totl]);
				totl += _len;

				if((totl - _len) != 0)
				{
					//p("%s", &line[totl - _len]);
					if(count == 0)
					{
						Time = atoi(&line[totl-_len]);			
						//p("Time: %d", SellOrders[Scount].Time);
					}
					count++;
				}
			}
			line[len - 1] = ' ';
			line[len - 2] = ' ';
			u32 i = 0;
			while(BuyOrders[i].Quantity == 0)
			{
				i++;	
			}
			if(Time > BuyOrders[i].Time)
			{
				if(BuyOrders[i].Time > 100000)
				{
					p("%s %s %d %lf %d", line, BuyOrders[i].Buyer,
							BuyOrders[i].Time, BuyOrders[i].Price, BuyOrders[i].Quantity);
				}
				else
				{
					p("%s %s 0%d %lf %d", line, BuyOrders[i].Buyer,
							BuyOrders[i].Time, BuyOrders[i].Price, BuyOrders[i].Quantity);
				}
			}
			else
			{
				p("%s", line);
			}
			continue;
		}
		if(strstr(line, "DisplayLowestSellOrder"))
		{
			totl = 0;
			u32 count = 0;
			u64 Time;
			while(totl < len)
			{
				_len = sstrlen(&line[totl]);
				totl += _len;

				if((totl - _len) != 0)
				{
					//p("%s", &line[totl - _len]);
					if(count == 0)
					{
						Time = atoi(&line[totl-_len]);			
						//p("Time: %d", SellOrders[Scount].Time);
					}
					count++;
				}
			}

			line[len - 1] = ' ';
			line[len - 2] = ' ';
			u32 i = Scount;
			while(SellOrders[i].Quantity == 0)
			{
				i--;	
			}
			if(Time > SellOrders[i].Time)
			{
				if(SellOrders[i].Time > 100000)
				{
					p("%s %s %d %lf %d", line, SellOrders[i].Seller,
							SellOrders[i].Time, SellOrders[i].Price, SellOrders[i].Quantity);
				}
				else
				{
					p("%s %s 0%d %lf %d", line, SellOrders[i].Seller,
							SellOrders[i].Time, SellOrders[i].Price, SellOrders[i].Quantity);
				}
			}
			else
			{
				p("%s", line);
			}
			continue;
		}
		if(strstr(line, "EnterBuyOrder"))
		{
			totl = 0;
			u32 count = 0;
			while(totl < len)
			{
				_len = sstrlen(&line[totl]);
				totl += _len;

				if((totl - _len) != 0)
				{
					if(count == 1)
					{
						memcpy(&BHitstack[Bhitstackcount].Name, &line[totl - _len], _len);
						Bhitstackcount++;
					}
					count++;
				}
			}
		}

		if(strstr(line, "EnterSellOrder"))
		{
			totl = 0;
			u32 count = 0;
			while(totl < len)
			{
				_len = sstrlen(&line[totl]);
				totl += _len;

				if((totl - _len) != 0)
				{
					if(count == 1)
					{
						memcpy(&SHitstack[Shitstackcount].Name, &line[totl - _len], _len);
						Shitstackcount++;
					}
					count++;
				}
			}
		}

		p("%s", line);
		for(u32 i = 0; i < Bcount; i++)
		{
			for(u32 j = 0; j < Scount; j++)
			{
				//p("diff %lf, buy: %lf, sell: %lf", _fabs(BuyOrders[i].Price - SellOrders[j].Price), BuyOrders[i].Price, SellOrders[j].Price);

				double Price = SellOrders[j].Price;
				if(BuyOrders[i].Price > SellOrders[j].Price)
				{
					Price = (BuyOrders[i].Price + SellOrders[j].Price)/2;
					goto special_case;
				}
				if(_fabs(BuyOrders[i].Price - SellOrders[j].Price) < 0.0001 )
				{
special_case:
					if(BuyOrders[i].Quantity && SellOrders[j].Quantity)
					{
						if(strstr(line, SellOrders[j].Seller))
						{
							u32 z;
							for(z = 0; z < Bhitstackcount; z++)
							{
								if(strstr(BHitstack[z].Name, BuyOrders[i].Buyer))
								{
									goto order_pass;
								}
							}
							goto next_line;
						}
						if(strstr(line, BuyOrders[i].Buyer))
						{
							u32 z;
							for(z = 0; z < Shitstackcount; z++)
							{
								if(strstr(SHitstack[z].Name, SellOrders[j].Seller))
								{
									goto order_pass;
								}
							}
							goto next_line;
						}
						continue;
order_pass:
						p("ExecuteBuySellOrders %lf %d", Price, SellOrders[j].Quantity);
						s32 Qdiff = BuyOrders[i].Quantity - SellOrders[j].Quantity;
						//	p("%d", BuyOrders[i].Quantity);
						//	p("%d", SellOrders[j].Quantity);
						if(Qdiff < 0)
						{
							Qdiff = SellOrders[j].Quantity - BuyOrders[i].Quantity;
							SellOrders[j].Quantity = Qdiff;
							BuyOrders[i].Quantity = 0;
							ASSERT(Qdiff > 0, "Huh?");
						}
						else
						{
							BuyOrders[i].QBought = SellOrders[j].Quantity;
							BuyOrders[i].Quantity = Qdiff;
							SellOrders[j].Quantity = 0;
						}

						p("Buyer: %s, %d", BuyOrders[i].Buyer, BuyOrders[i].Quantity);
						p("Seller: %s, %d", SellOrders[j].Seller, SellOrders[j].Quantity);
						//p("diff %lf, buy: %lf, sell: %lf", _fabs(BuyOrders[i].Price - SellOrders[j].Price), BuyOrders[i].Price, SellOrders[j].Price);
					}
				}
			}
		}
next_line:;
	}
}
