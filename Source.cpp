#include <iostream>
#include <vector>
#include <future>

void merge(int* arr, int left, int mid, int right) {
	// посчитаем количество элементов в левой и правой части
	int const nl = mid - left + 1;
	int const nr = right - mid;

	// Создадим 2 буфера для левой и правой частей соответсвенно
	int *arr_left[nl];
	int *arr_right[nr];

	for (int i = 0; i < nl; i++) {
		arr_left[i] = arr[left + i];
	}
	for (int j = 0; j < nr; j++) {
		arr_right[j] = arr[mid + 1 + j];
	}

	int i = 0, j = 0;
	int k = left;
	// Записываем в изначальный массив
	while (i < nl && j < nr) {
		if (arr_left[i] <= arr_right[j]) {
			arr[k] = arr_left[i];
			i++;
		}
		else {
			arr[k] = arr_right[j];
			j++;
		}
		k++;
	}
	// Записываем остатки 
	while (i < nl) {
		arr[k] = arr_left[i];
		i++;
		k++;
	}
	while (j < nr) {
		arr[k] = arr_right[j];
		k++;
		j++;
	}
}

void mergeSort(int* arr, int left, int right) {
	if (left >= right)
		return;
	int mid = (left + right - 1) / 2;
	// Рекурсивно сортируем левую и правую часть
	auto f = std::async(std::launch::async, [&]() {
		mergeSort(arr, left, mid);
		});
	mergeSort(arr, mid + 1, right);

	// Склеиваем обратно
	merge(arr, left, mid, right);
}

int main() {
	int arr[] = { 1,4,13,3,7,3,5,45,16 };
	mergeSort(arr, 0, 9);
	std::cout << arr;
	return 0;
}

