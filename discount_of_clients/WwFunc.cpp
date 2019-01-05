#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <Windows.h>
#include "WwFile.h"
#include "WwFunc.h"
using namespace std;

void Output(Information *info, int n)
{
	cout << "*********************************************************************************************************\n";
	cout << setw(2) << right << " №п\\п\t\t" <<  "ФИО" << setw(50) << right << "Адрес" << setw(30) << right << "Скидка" << endl;
	cout << "*********************************************************************************************************\n";
	for (int i = 0; i < n; i++)
	{
		cout << setw(2) << right << i + 1;
		cout<< "\t" << info[i].peop.surname << " " << info[i].peop.name << " " << info[i].peop.otch;
		cout << "\t\t" << right << "г. " << info[i].ad.city << " ул. " << info[i].ad.street << " д. " << info[i].ad.home << " кв. " << info[i].ad.apart;
		cout << "\t\t" << right << info[i].discount << "%" << endl;
		cout << "*********************************************************************************************************\n";
	}
}

void OutputWithDisc(Information *info, int n)
{
	int a;
	int check = 0;
	cout << " Введите размер скидки :";
	cin >> a;
	system("cls");
	cout << " Клиенты, имеющие " << a << "% скидку : \n";
	for (int i = 0, count = 1; i < n; i++)
	{
		if (info[i].discount == a)
		{
			check++;
			cout << " ФИО " << count << "-ого клиента, имеющего " << a << "% скидку :\n ";
			cout << info[i].peop.surname << " " << info[i].peop.name << " " << info[i].peop.otch << endl;
			cout << " Адрес " << count << "-ого клиента, имеющего " << a << "% скидку :\n ";
			cout << "г. " << info[i].ad.city << " ул. " << info[i].ad.street << " д. " << info[i].ad.home << " кв. " << info[i].ad.apart << endl;
			count++;
		}
	}
	if (!check)
	{
		cout << " Таких клиентов нет \n";
	}
}

void Sort(Information *&info, int n)
{
	int left = 0, right = n - 1;
	int c;
	cout << " Если вы хотите отсортировать по размеру скидки, нажмите \"1\",\n Если вы хотите отсортировать по алфавиту по фамилии, нажмите \"2\" : ";
	cin >> c;
	switch (c)
	{
	case 1:
	{
		while (left < right)
		{
			int a = 0;
			for (int i = left; i < right; i++)
			{
				if (info[i].discount > info[i + 1].discount)
				{
					a++;
				}
				if (info[i].discount < info[i + 1].discount)
				{
					swap(info[i], info[i + 1]);
				}
			}
			right--;
			for (int j = right; j > left; j--)
			{
				if (info[j].discount > info[j - 1].discount)
				{
					swap(info[j], info[j - 1]);
				}
			}
			left++;
			if (a >= ((left + right) / 2))
				break;
			else
				a = 0;
		}
		break;
	}
	case 2:
	{
		while (left < right)
		{
			int a = 0;
			for (int i = left; i < right; i++)
			{
				if (info[i].peop.surname < info[i + 1].peop.surname)
				{
					a++;
				}
				int k = 0;
				while (info[i].peop.surname[k] == info[i + 1].peop.surname[k])
					k++;
				if (info[i].peop.surname[k] > info[i + 1].peop.surname[k])
				{
					swap(info[i], info[i + 1]);
				}
			}
			right--;
			for (int j = right; j > left; j--)
			{
				int k = 0;
				while (info[j].peop.surname[k] == info[j - 1].peop.surname[k])
					k++;
				if (info[j].peop.surname[k] < info[j - 1].peop.surname[k])
				{
					swap(info[j], info[j - 1]);
				}
			}
			left++;
			if (a >= ((left + right) / 2))
				break;
			else
				a = 0;
		}
		break;
	}
	default:
		cout << " Ошибка в вводе. Попробуйте еще раз \n" << endl;
	}
}

void Delete(Information *&info, int &n, int nu)
{
	int size = n - 1;
	Information *c_info = new Information[size];
	for (int i = 0, j = 1; i < n; i++)
	{
		if (i == nu)
			continue;
		else
		{
			c_info[j - 1] = info[i];
			c_info[j - 1].index = j;
			j++;
		}
	}
	n--;
	delete[] info;
	info = c_info;
}

void Expend(Information *&info, int &n, int &ind)
{
	ind++;
	Information *c_info = new Information[n + 1];
	for (int i = 0; i < n; i++)
	{
		c_info[i] = info[i];
	}
	c_info[n].index = ind;
	cout << " Введите фамилию, имя и отчество клиента : ";
	cin >> c_info[n].peop.surname >> c_info[n].peop.name >> c_info[n].peop.otch;
	cout << " Введите город, улицу, дом и квартиру клиента : ";
	cin >> c_info[n].ad.city >> c_info[n].ad.street >> c_info[n].ad.home >> c_info[n].ad.apart;
	cout << " Если у этого клиента есть скидка введите 1, если нет введите 0 : ";
	int flag;
	cin >> flag;
	c_info[n].change = flag;
	if (c_info[n].change == 1)
	{
		cout << " Введите размер скидки клиента в процентах : ";
		cin >> c_info[n].discount;
	}
	else
		c_info[n].discount = 0;
	n++;
	delete[] info;
	info = c_info;
}

void Correct(Information *info, int n)
{
	int i;
	bool count = 0;
	while (!count)
	{
		cout << " Введите номер поля, который хотите изменить : \n";
		cin >> i;
		i--;
		if (i <= n - 1)
		{
			cout << " Введите фамилию, имя и отчество клиента : ";
			cin >> info[i].peop.surname >> info[i].peop.name >> info[i].peop.otch;
			cout << " Введите город, улицу, дом и квартиру клиента : ";
			cin >> info[i].ad.city >> info[i].ad.street >> info[i].ad.home >> info[i].ad.apart;
			cout << " Если у этого клиента есть скидка введите 1, если нет введите 0 : ";
			int flag;
			cin >> flag;
			info[i].change = flag;
			if (info[i].change == 1)
			{
				cout << " Введите размер скидки клиента в процентах : ";
				cin >> info[i].discount;
			}
			else
				info[i].discount = 0;
			count = 1;
		}
		else
			cout << " Ошибка в вводе, повторите операцию еще раз \n";
	}
}

int Count(Information info, char *str)
{
	int count = 0;
	if (!strcmp(info.peop.name, str))
	{
		if (strstr(info.peop.name, str))
			count++;
	}
	if (!strcmp(info.peop.surname, str))
	{
		if (strstr(info.peop.surname, str))
			count++;
	}
	if (!strcmp(info.peop.otch, str))
	{
		if (strstr(info.peop.otch, str))
			count++;
	}
	if (!strcmp(info.ad.city, str))
	{
		if (strstr(info.ad.city, str))
			count++;
	}
	if (!strcmp(info.ad.street, str))
	{
		if (strstr(info.ad.street, str))
			count++;
	}
	if (!strcmp(info.ad.home, str))
	{
		if (strstr(info.ad.home, str))
			count++;
	}
	if (!strcmp(info.ad.apart, str))
	{
		if (strstr(info.ad.apart, str))
			count++;
	}
	return count;
}

void Change(Information &info, char *str, char *c_str)
{
	if (!strcmp(info.peop.name, str))
	{
		if (strstr(info.peop.name, str))
			strcpy(info.peop.name, c_str);
	}
	if (!strcmp(info.peop.surname, str))
	{
		if (strstr(info.peop.surname, str))
			strcpy(info.peop.surname, c_str);
	}
	if (!strcmp(info.peop.otch, str))
	{
		if (strstr(info.peop.otch, str))
			strcpy(info.peop.otch, c_str);
	}
	if (!strcmp(info.ad.city, str))
	{
		if (strstr(info.ad.city, str))
			strcpy(info.ad.city, c_str);
	}
	if (!strcmp(info.ad.street, str))
	{
		if (strstr(info.ad.street, str))
			strcpy(info.ad.street, c_str);
	}
	if (!strcmp(info.ad.home, str))
	{
		if (strstr(info.ad.home, str))
			strcpy(info.ad.home, c_str);
	}
	if (!strcmp(info.ad.apart, str))
	{
		if (strstr(info.ad.apart, str))
			strcpy(info.ad.apart, c_str);
	}
}