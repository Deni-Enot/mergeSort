#include <iostream>
#include <vector>
#include <future>

void merge(int* arr, int left, int mid, int right) {
	// ��������� ���������� ��������� � ����� � ������ �����
	int const nl = mid - left + 1;
	int const nr = right - mid;

	// �������� 2 ������ ��� ����� � ������ ������ �������������
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
	// ���������� � ����������� ������
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
	// ���������� ������� 
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
	// ���������� ��������� ����� � ������ �����
	auto f = std::async(std::launch::async, [&]() {
		mergeSort(arr, left, mid);
		});
	mergeSort(arr, mid + 1, right);

	// ��������� �������
	merge(arr, left, mid, right);
}

int main() {
	int arr[] = { 1,4,13,3,7,3,5,45,16 };
	mergeSort(arr, 0, 9);
	std::cout << arr;
	return 0;
}

