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

void Menu(int &num, Information *&, int &, char &, int &);

int main()
{
	system("chcp 1251");
	int n = 0, ind = 0;
	char q;
	system("cls");
	Information *info = new Information[n];
	Action number = num1;
	int num = number;
	FileIn_Index(info, n, ind);
	do
	{
		Menu(num, info, n, q, ind);
		if (q != 43)
		{
			cout << "\n ���� �� ������ �������� ���������, ������� \"+\",\n ���� ������ ����������, ������� ����� ������ ������ \n";
			cin >> q;
		}
	} while (q != 43);
	delete[] info;
	return 0;
}

void Menu(int &num, Information *&info, int &n, char &q, int &ind)
{
	cout << " ������� \"1\", ����� ������ ������.\n";
	cout << " ������� \"2\", ����� ������� ��������.\n";
	cout << " ������� \"3\", ����� ������� �������� � ������������ �������.\n";
	cout << " ������� \"4\", ����� ������� ������������� ������.\n";
	cout << " ������� \"5\", ����� ������� ���� \n";
	cout << " ������� \"6\", ����� ��������������� ���� \n";
	cout << " ������� \"7\", ����� ������� ���� �� ������� �� ������� \n";
	cout << " ������� \"8\", ����� ��������� ���������� ��������� \n";
	cout << " ������� \"9\", ����� �������� ��� ��������� �������� \n";
	cout << " ������� \"10\", ����� ����� �� ��������� \n";
	cin >> num;
	switch (num)
	{
	case (num1):
	{
		Expend(info, n, ind);
		FileExpend(info, n);
		FileOut_Index(info, n);
		Output(info, n);
		break;
	}
	case (num2):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			Output(info, n);
			FileOut(info, n);
		}
		break;
	}
	case (num3):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			OutputWithDisc(info, n);
			FileOut(info, n);
		}
		break;
	}
	case (num4):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			Sort(info, n);
			Output(info, n);
			FileOut(info, n);
			FileOut_Index(info, n);
		}
		break;
	}
	case (num5):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			int nu;
			cout << " ������� ����� ����, ������� ������ ������� : ";
			cin >> nu;
			nu--;
			Delete(info, n, nu);
			FileOut(info, n);
			FileOut_Index(info, n);
			Output(info, n);
		}
		break;
	}
	case(num6):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			Correct(info, n);
			FileOut(info, n);
			Output(info, n);
		}
		break;
	}
	case(num7):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			int disc, change;
			cout << " ������� ������ : \n";
			cin >> disc;
			cout << " ���� ������ ������� ����� � ������� �������, ������� \"1\". \n";
			cout << " ���� ������ ������� ����� � ������� �������, ������� \"2\". \n";
			cin >> change;
			switch (change)
			{
			case 1:
			{
				for (int i = 0; i < n; i++)
				{
					if (info[i].discount < disc)
					{
						Delete(info, n, i);
						i--;
					}
				}
				break;
			}
			case 2:
			{
				for (int i = 0; i < n; i++)
				{
					if (info[i].discount > disc)
					{
						Delete(info, n, i);
						i--;
					}
				}
				break;
			}
			default:
			{
				cout << " ������ � �����! \n";
			}
			}
			FileOut(info, n);
			FileOut_Index(info, n);
			Output(info, n);
		}
		break;
	}
	case(num8):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			int amt = 0;
			char str[20];
			cout << " ������� ������ : \n";
			cin >> str;
			char num[3];
			char *p;
			for (int i = 0; i < n; i++)
			{
				p = _itoa(info[i].discount, num, 10);
				if(!strcmp(str,p))
				{
					if (strstr(str, p))
					{
						amt++;
					}
				}
				amt += Count(info[i], str);
			}
			cout << " ���������� ���������� : " << amt << endl;
		}
		break;
	}
	case(num9):
	{
		if (n == 0)
			cout << " ������ ����! \n";
		else
		{
			char str[20];
			cout << " ������� ������, ������� ������ �������� : \n";
			cin >> str;
			char c_str[20];
			cout << " ������� ������, �� ������� ������ �������� : \n";
			cin >> c_str;
			for (int i = 0; i < n; i++)
			{
				Change(info[i], str, c_str);
			}
			FileOut(info, n);
			Output(info, n);
		}
		break;
	}
	case (num10):
	{
		q = '+';
		break;
	}
	default:
		cout << " ������ � �����. ���������� ��� ��� \n" << endl;
	}
}