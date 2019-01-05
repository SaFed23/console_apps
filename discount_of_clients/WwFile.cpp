#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <locale>
#include <Windows.h>
#include "WwFile.h"
#include "WwFunc.h"
using namespace std;

void FileOut(Information *info, int n)
{
	ofstream fout("Data.txt");
	if (fout.is_open())
	{
		for (int i = 0; i < n; i++)
		{
			fout << info[i].peop.surname << " " << info[i].peop.name << " " << info[i].peop.otch << " ";
			fout << info[i].ad.city << " " << info[i].ad.street << " " << info[i].ad.home << " " << info[i].ad.apart << " ";
			fout << info[i].discount << " " << endl;
		}
	}
	else
		cout << " Ошибка! Файл для вывода не открылся! ";
	fout.close();
}

void FileIn(Information *&info, int &n, int &ind)
{
	ifstream fin("Data.txt");
	if (fin.is_open())
	{
		if (!fin.eof())
		{
			char str[300];
			int size = 0;
			while (fin.getline(str, 300))
				size++;
			fin.close();
			n = size;
			Information *c_info = new Information[n];
			ifstream fin("Data.txt");
			for (int i = 0; i < n; i++, ind++)
			{
				c_info[i].index = ind;
				fin >> c_info[i].peop.surname >> c_info[i].peop.name >> c_info[i].peop.otch;
				fin >> c_info[i].ad.city >> c_info[i].ad.street >> c_info[i].ad.home >> c_info[i].ad.apart;
				fin >> c_info[i].discount;
			}
			delete[] info;
			info = c_info;
		}
		else
			cout << " Ошибка! Файл для вывода не открылся! ";
	}
	fin.close();
}

void FileExpend(Information *info, int n)
{
	ofstream fout("Data.txt", ios::app);
	if (fout.is_open())
	{
		fout << info[n - 1].peop.surname << " " << info[n - 1].peop.name << " " << info[n - 1].peop.otch << " ";
		fout << info[n - 1].ad.city << " " << info[n - 1].ad.street << " " << info[n - 1].ad.home << " " << info[n - 1].ad.apart << " ";
		fout << info[n - 1].discount << " " << endl;
	}
	else
		cout << " Ошибка! Файл для вывода не открылся! ";
	fout.close();
}

void FileOut_Index(Information *info, int n)
{
	ofstream fout("Index.bin", ios::binary | ios::out);
	if (fout.is_open())
	{
		for (int i = 0; i < n; i++)
		{
			fout.write((char*)&info[i].index, sizeof(info[i].index));
		}
	}
	else
		cout << " Ошибка! Файл для вывода не открылся! ";
	fout.close();
}

void FileIn_Index(Information *&info, int &n, int &ind)
{
	ifstream fin_count("Data.txt");
	if (fin_count.is_open())
	{
		if (!fin_count.eof())
		{
			char str[300];
			int size = 0;
			while (fin_count.getline(str, 300))
				size++;
			n = size;
		}
	}
	fin_count.close();
	int *A = new int[n];
	ifstream fin_ind("Index.bin", ios::binary);
	if (fin_ind.is_open())
	{
		if (!fin_ind.eof())
		{
			for (int i = 0; i < n; i++)
			{
				fin_ind.read((char*)&A[i], sizeof(int));
			}
		}
	}
	fin_ind.close();
	Information *c_info = new Information[n];
	ifstream fin("Data.txt");
	for (int i = 0; i < n; i++)
	{
		fin >> c_info[i].peop.surname >> c_info[i].peop.name >> c_info[i].peop.otch;
		fin >> c_info[i].ad.city >> c_info[i].ad.street >> c_info[i].ad.home >> c_info[i].ad.apart;
		fin >> c_info[i].discount;
	}
	delete[] info;
	info = c_info;
	fin.close();
	int ind_max = A[0];
	for (int i = 0; i < n; i++)
	{
		if (A[i] > ind_max)
			ind_max = A[i];
		for (int j = 0; j < n; j++)
		{
			if (A[i] - 1 == j)
			{
				info[j].index = A[i];
				swap(info[i], info[j]);
				i++;
			}
		}
	}
	ind = ind_max;
}