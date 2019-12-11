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

//void merge(double* arr) {
//	int len = lenarr(arr);
//	int left = len / 2;
//	int rigth = len - left;
//	double* tmp_left_arr;
//	double* tmp_rigth_arr;
//	tmp_left_arr = new double[left];
//	tmp_rigth_arr = new double[rigth];
//}

int main()
{
	setlocale(0, "");
	srand(time(NULL));
	//cout << "N: ";
	//int N;
	//cin >> N;

	double time_ch = 0, time_bu = 0, time_sh = 0;
	//output(arr);
	//bubble(arr);
	//shake(arr);	
	ofstream out_ch;
	out_ch.open("C:\\Users\\Максим\\Desktop\\choise_data.txt");
	ofstream out_bu;
	out_ch.open("C:\\Users\\Максим\\Desktop\\bubble_data.txt");
	ofstream out_sh;
	out_ch.open("C:\\Users\\Максим\\Desktop\\shaker_data.txt");
	double n = 10;
	for (int num = 1000, cntr = 0; num <= 5000; num += 500, cntr++) {
		double* arr;
		arr = new double[num];
		for (int i = 1; i <= n; i++) {
			for (int i = 0; i < num; i++) arr[i] = double(rand()) / double(10 * rand() % 1000); time_ch += choise(arr);
			//cout << "Выбор, кол-во элементов " << N << ", затрачено времени " << choise(arr) << endl;
			for (int i = 0; i < num; i++) arr[i] = double(rand()) / double(10 * rand() % 1000); time_bu += bubble(arr);
			//cout << "Пузырек, кол-во элементов " << N << ", затрачено времени " << bubble(arr) << endl;
			for (int i = 0; i < num; i++) arr[i] = double(rand()) / double(10 * rand() % 1000); time_sh += shake(arr);
			//cout << "Шейкер, кол-во элементов " << N << ", затрачено времени " << shake(arr) << endl;
		}
		cout << "Среднее время сортировки выбором для " << num << " элементов: " << time_ch / n << endl;
		cout << "Среднее время сортировки пузырьком для " << num << " элементов: " << time_bu / n << endl;
		cout << "Среднее время сортировки шейкером для " << num << " элементов: " << time_sh / n << endl;
		out_ch << num << " " << time_ch / n << endl;
		out_bu << num << " " << time_bu / n << endl;
		out_sh << num << " " << time_sh / n << endl;
		delete[] arr;
	}
	out_ch.close(); out_bu.close(); out_sh.close();
	//output(arr);
}