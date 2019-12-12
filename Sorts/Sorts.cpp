#include <iostream>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
#include <fstream>
using namespace std;

int lenarr(double* arr) {
	int len = _msize(arr) / sizeof(double);
	return len;
}

void output(double* arr) {
	int len = lenarr(arr);
	for (int i = 0; i < len; i++) cout << arr[i] << " ";
	cout << endl;
}

void swap(double& a, double& b) {
	double tmp = a;
	a = b;
	b = tmp;
}

double choise(double* arr) {
	int len = lenarr(arr);
	clock_t start_time = clock();
	int max;
	for (int i = 0; i < len; i++) {
		max = 0;
		for (int j = 0; j < len - i; j++) if (arr[j] > arr[max]) max = j;
		swap(arr[max], arr[len - i - 1]);
	}
	clock_t stop_time = clock();
	double result = double(stop_time - start_time) / CLOCKS_PER_SEC;
	return result;
}

double bubble(double* arr) {
	int len = lenarr(arr);
	clock_t start_time = clock();
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) { if (arr[j] < arr[j + 1]) swap(arr[j], arr[j + 1]); }
	}
	clock_t stop_time = clock();
	double result = double(stop_time - start_time) / CLOCKS_PER_SEC;
	return result;
}

double shake(double* arr) {
	int len = lenarr(arr);
	clock_t start_time = clock();
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) if (arr[j] < arr[j + 1]) swap(arr[j], arr[j + 1]);
		for (int j = len - i - 2; j > i; j--) if (arr[j] < arr[j - 1]) swap(arr[j], arr[j - 1]);
	}
	clock_t stop_time = clock();
	double result = double(stop_time - start_time) / CLOCKS_PER_SEC;
	return result;
}

double shake1(double* mas)
{
	int size = lenarr(mas);
	double start_time = clock();
	int L = 1, R = size - 1;
	while (L <= R)
	{
		for (int i = R; i >= L; i--)
		{
			if (mas[i - 1] > mas[i])
			{
				double x = mas[i];
				mas[i] = mas[i - 1];
				mas[i - 1] = x;
			}
		}
		L++;

		for (int i = L; i <= R; i++)
		{
			if (mas[i - 1] > mas[i])
			{
				double x = mas[i];
				mas[i] = mas[i - 1];
				mas[i - 1] = x;
			}
		}
		R--;
	}

	double end_time = clock();
	double time = (end_time - start_time) / CLOCKS_PER_SEC;
	return time;
}

double merge(double* mas)
{
	int size = lenarr(mas);
	double start_time = clock();
	int step = 1;  
	int* temp = new int[size]; 
	while (step < size)  
	{
		int index = 0;    
		int l = 0;      
		int m = l + step;  
		int r = l + step * 2;  
		do
		{
			m = m < size ? m : size;  
			r = r < size ? r : size;
			int i1 = l, i2 = m; 
			for (; i1 < m && i2 < r; ) 
			{
				if (mas[i1] < mas[i2]) { temp[index++] = mas[i1++]; } 
				else { temp[index++] = mas[i2++]; }
			}
			while (i1 < m) temp[index++] = mas[i1++]; 
			while (i2 < r) temp[index++] = mas[i2++]; 
			l += step * 2; 
			m += step * 2;
			r += step * 2;
		} while (l < size); 
		for (int i = 0; i < size; i++) 
			mas[i] = temp[i];
		step *= 2; 
	}
	double end_time = clock(); 
	double time = (end_time - start_time) / CLOCKS_PER_SEC;
	return time;
}

int main()
{
	setlocale(0, "");
	srand(time(NULL));
	double time_ch = 0, time_bu = 0, time_sh = 0, time_me = 0;
	ofstream out;
	out.open("Text.txt");
	double n = 10;
	for (int num = 50000, cntr = 0; num <= 200000; num += 50000, cntr++) {
		double* arr;
		arr = new double[num];
		double* arr1;
		for (int i = 1; i <= n; i++) {
			for (int i = 0; i < num; i++) arr[i] = double(rand()) / double(10 * rand() % 1000); time_ch += choise(arr);
			for (int i = 0; i < num; i++) arr[i] = double(rand()) / double(10 * rand() % 1000); time_bu += bubble(arr);
			for (int i = 0; i < num; i++) arr[i] = double(rand()) / double(10 * rand() % 1000); time_sh += shake1(arr);
			for (int i = 0; i < num; i++) arr[i] = double(rand()) / double(10 * rand() % 1000); time_me += merge(arr);
		}
		cout << "Среднее время сортировки выбором для " << num << " элементов: " << time_ch / n << endl;
		cout << "Среднее время сортировки пузырьком для " << num << " элементов: " << time_bu / n << endl;
		cout << "Среднее время сортировки шейкером для " << num << " элементов: " << time_sh / n << endl;
		cout << "Среднее время сортировки слиянием для " << num << " элементов: " << time_me / n << endl;
		out << num << " " << time_ch / n << " " << time_bu / n << " " << time_sh / n << " " << time_me / n << endl;
		delete[] arr;
	}
	out.close();
}