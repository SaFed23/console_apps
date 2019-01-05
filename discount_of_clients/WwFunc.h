#include"Struct.h"
#ifndef WwFunc
#define WwFunc

void Output(Information *, int);
void OutputWithDisc(Information *, int);
void Sort(Information *&, int);
void Delete(Information *&, int &, int);
void Expend(Information *&, int &, int &);
void Correct(Information *, int);
int Count(Information, char *);
void Change(Information &, char *, char *);

#endif