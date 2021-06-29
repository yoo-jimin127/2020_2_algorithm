//3 - (b) algorithm 2020 homework3 class(나) [240]homework3_YooJimin_20193017
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable : 4996)

#define parent_node(a) (a-1)/2;

double make_randArr(double x, double y);//실수 난수 배열 생성 함수
void input_copy(int size);//입력값으로 받은 배열 복사 함수
void reset_arr(int size);////복사된 배열을 초기화시키는 함수
void selection_sort(double arr[], int size);//선택정렬 함수
void bubble_sort(double arr[], int size);//버블정렬 함수 
void insertion_sort(double arr[], int size);//삽입정렬 함수 
void merge_sort(double arr[], int left, int right);//병합정렬 함수 
void conquer_leftRight(double arr[], int left, int mid, int right);//부분 정복 함수 
void quick_sort(double arr[], int left, int right);//퀵정렬 함수 
void swap(double arr[], int x, int y);//원소 x와 원소 y 바꾸기 함수 
int partition(double arr[], int left, int right);//왼쪽과 오른쪽으로 나누어 정렬하는 함수 
void heap_sort(double arr[], int size);//힙정렬 함수 

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

	//선택정렬 함수 호출 및 결과 출력
	printf("<<selection sort>>\n");
	input_copy(arr_size);//정렬되지 않은 배열을 복사하여 복사본을 가지고 정렬 진행
	cnt = 0;//step 5까지의 출력을 위해 정렬함수 호출 전 cnt 값을 0으로 초기화
	selection_sort(res_arr, arr_size);

	printf("selection sort result : ");
	for (int i = 0; i < arr_size; i++) {
		printf("%.3f  ", res_arr[i]);
	}
	printf("\n\n");
	reset_arr(arr_size);//정렬 후 복사본 초기화

	//버블정렬 함수 호출 및 결과 출력
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

	//삽입정렬 함수 호출 및 결과 출력
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

	//병합정렬 함수 호출 및 결과 출력
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

	//퀵정렬 함수 호출 및 결과 출력
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

	//힙정렬 함수 호출 및 결과 출력
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

double make_randArr(double x, double y) {//실수 난수 배열 생성 함수
	return ((y - x) * ((double)rand() / RAND_MAX)) + x;
}

void input_copy(int arr_size) {//정렬되지 않은 배열을 복사하는 함수
	for (int i = 0; i < arr_size; i++) {
		res_arr[i] = input_arr[i];
	}
}

void reset_arr(int arr_size) {//복사된 배열을 초기화시키는 함수
	for (int i = 0; i < arr_size; i++) {
		res_arr[i] = 0;
	}
}

void selection_sort(double arr[], int arr_size) {//선택정렬
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

void bubble_sort(double arr[], int arr_size) {//버블정렬
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

void insertion_sort(double arr[], int arr_size) {//삽입정렬
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

void merge_sort(double arr[], int left, int right) {//병합정렬
	int mid;

	if (left < right) {
		mid = (left + right) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		conquer_leftRight(arr, left, mid, right);
	}
}

void conquer_leftRight(double arr[], int left, int mid, int right) {
	//병합정렬로 나누어진 왼쪽 부분배열과 오른쪽 부분배열을 병합하기 위한 함수
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

void quick_sort(double arr[], int left, int right) {//퀵정렬
	int pivot;

	if (left <= right) {

		pivot = partition(arr, left, right);
		quick_sort(arr, left, pivot - 1);
		quick_sort(arr, pivot + 1, right);
	}
}

void swap(double arr[], int x, int y) {//배열의 원소 x와 y의 위치를 교환해주는 함수
	double tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

int partition(double arr[], int left, int right) {//왼쪽과 오른쪽으로 분할하여 정렬하는 함수
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

void heap_sort(double arr[], int arr_size) {//힙정렬
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
