#ifndef Struct
#define Struct

struct People
{
	char name[15];
	char surname[15];
	char otch[20];
};

struct Adress
{
	char city[15];
	char street[15];
	char home[7];
	char apart[5];
};

struct Information
{
	People peop;
	Adress ad;
	unsigned change : 1;
	int discount;
	int index;
};

enum Action {num1 = 1, num2, num3, num4, num5, num6, num7, num8, num9, num10};

#endif