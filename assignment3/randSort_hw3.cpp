//3 - (b) algorithm 2020 homework3 class(��) [240]homework3_YooJimin_20193017
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable : 4996)

#define parent_node(a) (a-1)/2;

double make_randArr(double x, double y);//�Ǽ� ���� �迭 ���� �Լ�
void input_copy(int size);//�Է°����� ���� �迭 ���� �Լ�
void reset_arr(int size);////����� �迭�� �ʱ�ȭ��Ű�� �Լ�
void selection_sort(double arr[], int size);//�������� �Լ�
void bubble_sort(double arr[], int size);//�������� �Լ� 
void insertion_sort(double arr[], int size);//�������� �Լ� 
void merge_sort(double arr[], int left, int right);//�������� �Լ� 
void conquer_leftRight(double arr[], int left, int mid, int right);//�κ� ���� �Լ� 
void quick_sort(double arr[], int left, int right);//������ �Լ� 
void swap(double arr[], int x, int y);//���� x�� ���� y �ٲٱ� �Լ� 
int partition(double arr[], int left, int right);//���ʰ� ���������� ������ �����ϴ� �Լ� 
void heap_sort(double arr[], int size);//������ �Լ� 

double input_arr[8];
double res_arr[8];
int arr_size = sizeof(input_arr) / sizeof(double);
int cnt;
double rand_element, d1, d2;

int main(void) {

	for (int i = 0; i < arr_size; i++) {
		rand_element = make_randArr(d1, d2);
		d1 = -1;
		d2 = 1;

		input_arr[i] = rand_element;
	}

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<<selection sort>>\n");
	input_copy(arr_size);//���ĵ��� ���� �迭�� �����Ͽ� ���纻�� ������ ���� ����
	cnt = 0;//step 5������ ����� ���� �����Լ� ȣ�� �� cnt ���� 0���� �ʱ�ȭ
	selection_sort(res_arr, arr_size);

	printf("selection sort result : ");
	for (int i = 0; i < arr_size; i++) {
		printf("%.3f  ", res_arr[i]);
	}
	printf("\n\n");
	reset_arr(arr_size);//���� �� ���纻 �ʱ�ȭ

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<<bubble sort>>\n");
	input_copy(arr_size);
	cnt = 0;
	bubble_sort(res_arr, arr_size);

	printf("bubble sort result : ");
	for (int i = 0; i < arr_size; i++) {
		printf("%.3f  ", res_arr[i]);
	}
	printf("\n\n");
	reset_arr(arr_size);

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<<insertion sort>>\n");
	input_copy(arr_size);
	cnt = 0;
	insertion_sort(res_arr, arr_size);

	printf("insertion sort result : ");
	for (int i = 0; i < arr_size; i++) {
		printf("%.3f  ", res_arr[i]);
	}
	printf("\n\n");
	reset_arr(arr_size);

	//�������� �Լ� ȣ�� �� ��� ���
	printf("<<merge sort>>\n");
	input_copy(arr_size);
	cnt = 0;
	merge_sort(res_arr, 0, arr_size - 1);

	printf("merge sort result : ");
	for (int i = 0; i < arr_size; i++) {
		printf("%.3f  ", res_arr[i]);
	}
	printf("\n\n");
	reset_arr(arr_size);

	//������ �Լ� ȣ�� �� ��� ���
	printf("<<quick sort>>\n");
	input_copy(arr_size);
	cnt = 0;
	quick_sort(res_arr, 0, arr_size - 1);

	printf("quick sort result : ");
	for (int i = 0; i < arr_size; i++) {
		printf("%.3f  ", res_arr[i]);
	}
	printf("\n\n");
	reset_arr(arr_size);

	//������ �Լ� ȣ�� �� ��� ���
	printf("<<heap sort>>\n");
	input_copy(arr_size);
	cnt = 0;
	heap_sort(res_arr, arr_size);
	double temp;

	for (int i = arr_size - 1; i >= 0; i--) {
		temp = res_arr[i];
		res_arr[i] = res_arr[0];
		res_arr[0] = temp;

		heap_sort(res_arr, i);
	}

	printf("heap sort result : ");
	for (int i = 0; i < arr_size; i++) {
		printf("%.3f  ", res_arr[i]);
	}
	printf("\n\n");
	reset_arr(arr_size);

	return 0;
}

double make_randArr(double x, double y) {//�Ǽ� ���� �迭 ���� �Լ�
	return ((y - x) * ((double)rand() / RAND_MAX)) + x;
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

void selection_sort(double arr[], int arr_size) {//��������
	double tmp;

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

void bubble_sort(double arr[], int arr_size) {//��������
	double tmp;

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

void insertion_sort(double arr[], int arr_size) {//��������
	double insert_element;
	int j;

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

void merge_sort(double arr[], int left, int right) {//��������
	int mid;

	if (left < right) {
		mid = (left + right) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		conquer_leftRight(arr, left, mid, right);
	}
}

void conquer_leftRight(double arr[], int left, int mid, int right) {
	//�������ķ� �������� ���� �κй迭�� ������ �κй迭�� �����ϱ� ���� �Լ�
	int frontIdx = left;
	int backIdx = mid + 1;

	double* mergeSort_arr = (double*)malloc((right + 1) * sizeof(double));
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

void quick_sort(double arr[], int left, int right) {//������
	int pivot;

	if (left <= right) {

		pivot = partition(arr, left, right);
		quick_sort(arr, left, pivot - 1);
		quick_sort(arr, pivot + 1, right);
	}
}

void swap(double arr[], int x, int y) {//�迭�� ���� x�� y�� ��ġ�� ��ȯ���ִ� �Լ�
	double tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

int partition(double arr[], int left, int right) {//���ʰ� ���������� �����Ͽ� �����ϴ� �Լ�
	int low, high;
	double pivot;

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

void heap_sort(double arr[], int arr_size) {//������
	int child_node, root_node;
	double tmp;

	for (int i = 1; i < arr_size; i++) {
		child_node = i;

		while (child_node > 0) {
			root_node = parent_node(child_node);

			if (arr[child_node] > arr[root_node]) {
				tmp = arr[root_node];
				arr[root_node] = arr[child_node];
				arr[child_node] = tmp;
			}

			child_node = root_node;
		}
	}
}
