#include <iostream>
#include <ctime>
#include <cstdlib>
#include <malloc.h>
using namespace std;

int lenarr(int* arr) {
	int len = _msize(arr) / sizeof(int);
	return len;
}

void output(int* arr) {
	int len = lenarr(arr);
	for (int i = 0; i < len; i++) cout << arr[i] << " ";
	cout << endl;
}

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

double choise(int* arr) {
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

double bubble(int* arr) {
	int len = lenarr(arr);
	clock_t start_time = clock();
	for (int i = 0; i < len - 1; i++) {
		for (int j = 0; j < len - i - 1; j++) { if (arr[j] < arr[j + 1]) swap(arr[j], arr[j + 1]); }
	}
	clock_t stop_time = clock();
	double result = double(stop_time - start_time) / CLOCKS_PER_SEC;
	return result;
}

double shake(int* arr) {
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

void merge(int* arr) {
	int len = lenarr(arr);
	int left = len / 2;
	int rigth = len - left;
	int* tmp_left_arr;
	int* tmp_rigth_arr;
	tmp_left_arr = new int[left];
	tmp_rigth_arr = new int[rigth];
	
}

int main()
{
	setlocale(0, "");
	srand(time(NULL));
	cout << "N: ";
	int N;
	cin >> N;
	int* arr;
	arr = new int[N];
	for (int i = 0; i < N; i++) arr[i] = rand();
	//output(arr);
	//bubble(arr);
	//shake(arr);	
	cout << "Выбор, кол-во элементов " << N << ", затрачено времени " << choise(arr) << endl;
	for (int i = 0; i < N; i++) arr[i] = rand();
	cout << "Пузырек, кол-во элементов " << N << ", затрачено времени " << bubble(arr) << endl;
	for (int i = 0; i < N; i++) arr[i] = rand();
	cout << "Шейкер, кол-во элементов " << N << ", затрачено времени " << shake(arr) << endl;
	//output(arr);
}