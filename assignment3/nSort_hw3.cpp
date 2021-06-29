//3-(c) algorithm 2020 homework3 class(��) [240]homework3_YooJimin_20193017
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable : 4996)

#define parent_node(a) (a-1)/2;

void calc_time();////���� �ð��� �����Ͽ� ����ϴ� �Լ�
void input_copy(int size);//�Է°����� ���� �迭 ���� �Լ�
void reset_arr(int size);////����� �迭�� �ʱ�ȭ��Ű�� �Լ�
void selection_sort(int arr[], int size);//�������� �Լ�
void bubble_sort(int arr[], int size);//�������� �Լ� 
void insertion_sort(int arr[], int size);//�������� �Լ� 
void merge_sort(int arr[], int left, int right);//�������� �Լ� 
void conquer_leftRight(int arr[], int left, int mid, int right);//�κ� ���� �Լ� 
void quick_sort(int arr[], int left, int right);//������ �Լ� 
void swap(int arr[], int x, int y);//���� x�� ���� y �ٲٱ� �Լ� 
int partition(int arr[], int left, int right);//���ʰ� ���������� ������ �����ϴ� �Լ� 
void heapify(int* arr, int arr_size);//�迭�� ������ ������ִ� ����
void heap_sort(int *arr, int *size);//������ �Լ� 

int input_arr[20000];
int res_arr[20000];
int arr_size = sizeof(input_arr) / sizeof(int);
int cnt;
clock_t start, end, elapse_time;

int main(void) {

	for (int i = 0; i < arr_size; i++) {
		input_arr[i] = rand();
	}

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<selection sort>");
	input_copy(arr_size);//���ĵ��� ���� �迭�� �����Ͽ� ���纻�� ������ ���� ����
	cnt = 0;//step 5������ ����� ���� �����Լ� ȣ�� �� cnt ���� 0���� �ʱ�ȭ

	start = clock();
	selection_sort(res_arr, arr_size);
	end = clock();
	calc_time();

	reset_arr(arr_size);//���� �� ���纻 �ʱ�ȭ

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<bubble sort>");
	input_copy(arr_size);
	cnt = 0;

	start = clock();
	bubble_sort(res_arr, arr_size);
	end = clock();
	calc_time();

	reset_arr(arr_size);

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<insertion sort>");
	input_copy(arr_size);
	cnt = 0;

	start = clock();
	insertion_sort(res_arr, arr_size);
	end = clock();
	calc_time();

	reset_arr(arr_size);

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<merge sort>");
	input_copy(arr_size);
	cnt = 0;

	start = clock();
	merge_sort(res_arr, 0, arr_size - 1);
	end = clock();
	calc_time();

	reset_arr(arr_size);

	//������ �Լ� ȣ�� �� ��� ���
	printf("<heap sort>");
	input_copy(arr_size);
	cnt = 0;

	start = clock();
	for (int i = 0; i < arr_size; i++) {
		heapify(res_arr, arr_size);
		heap_sort(res_arr, &arr_size);
	}
	end = clock();
	calc_time();

	reset_arr(arr_size);

	//������ �Լ� ȣ�� �� ��� ���
	printf("<quick sort>");
	input_copy(arr_size);
	cnt = 0;
	reset_arr(arr_size);

	return 0;
}

void calc_time() {
	elapse_time = end - start;
	printf(" ����ð�: %f msec\n\n", ((double)elapse_time / CLOCKS_PER_SEC)*1000);
}

void input_copy(int arr_size) {//���ĵ��� ���� �迭�� �����ϴ� �Լ�
	for (int i = 0; i < arr_size; i++) {
		res_arr[i] = input_arr[i];
	}
}

void reset_arr(int arr_size) {//����� �迭�� �ʱ�ȭ��Ű�� �Լ�
	for (int i = 0; i < arr_size; i++) {
		res_arr[i] = 0;
	}
}

void selection_sort(int arr[], int arr_size) {//��������
	int tmp;

	for (int i = 0; i < arr_size; i++) {
		for (int j = i + 1; j < arr_size; j++) {
			if (arr[i] > arr[j]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

void bubble_sort(int arr[], int arr_size) {//��������
	int tmp;

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void insertion_sort(int arr[], int arr_size) {//��������
	int insert_element, j;
	for (int i = 1; i < arr_size; i++) {
		insert_element = arr[i];

		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > insert_element) {
				arr[j + 1] = arr[j];
			}
			else break;
		}

		arr[j + 1] = insert_element;
	}
}

void merge_sort(int arr[], int left, int right) {//��������
	int mid;

	if (left < right) {
		mid = (left + right) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		conquer_leftRight(arr, left, mid, right);
	}
}

void conquer_leftRight(int arr[], int left, int mid, int right) {
	//�������ķ� �������� ���� �κй迭�� ������ �κй迭�� �����ϱ� ���� �Լ�
	int frontIdx = left;
	int backIdx = mid + 1;

	int* mergeSort_arr = (int*)malloc((right + 1) * sizeof(int));
	int idxNum = left;

	while (frontIdx <= mid && backIdx <= right) {
		if (arr[frontIdx] <= arr[backIdx]) mergeSort_arr[idxNum] = arr[frontIdx++];
		else mergeSort_arr[idxNum] = arr[backIdx++];

		idxNum++;
	}

	if (mid < frontIdx) {
		for (int i = backIdx; i <= right; i++) {
			mergeSort_arr[idxNum] = arr[i];
			idxNum++;
		}
	}

	else {
		for (int i = frontIdx; i <= mid; i++) {
			mergeSort_arr[idxNum] = arr[i];
			idxNum++;
		}
	}

	for (int i = left; i <= right; i++) {
		arr[i] = mergeSort_arr[i];
	}

	free(mergeSort_arr);
}

void quick_sort(int arr[], int left, int right) {//������
	int pivot;

	if (left <= right) {

		pivot = partition(arr, left, right);
		quick_sort(arr, left, pivot - 1);
		quick_sort(arr, pivot + 1, right);
	}

	return;
}

void swap(int arr[], int x, int y) {//�迭�� ���� x�� y�� ��ġ�� ��ȯ���ִ� �Լ�
	int tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

int partition(int arr[], int left, int right) {//���ʰ� ���������� �����Ͽ� �����ϴ� �Լ�
	int pivot, low, high;

	pivot = arr[left];
	low = left + 1;
	high = right;

	while (low <= high) {

		while (arr[low] < pivot) low++;
		while (arr[high] > pivot) high--;

		if (low <= high) swap(arr, low, high);
	}

	swap(arr, left, high);

	return high;
}

void heapify(int* arr, int arr_size) {
	int child_node, root_node, tmp;
	for (int i = 1; i < arr_size; i++){
		child_node = i;

		do {
			root_node = (child_node - 1) / 2;
			if (arr[root_node] < arr[child_node]) {
				tmp = arr[root_node];
				arr[root_node] = arr[child_node];
				arr[child_node] = tmp;
			}

			child_node = root_node;
		} while (child_node != 0);
	}
}

void heap_sort(int *arr, int *arr_size) {//�� ����
	int tmp;
	tmp = arr[0];
	arr[0] = arr[*arr_size - 1];
	arr[*arr_size - 1] = tmp;
	--(*arr_size);
}