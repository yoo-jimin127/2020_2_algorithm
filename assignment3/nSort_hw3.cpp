//3-(c) algorithm 2020 homework3 class(나) [240]homework3_YooJimin_20193017
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning (disable : 4996)

#define parent_node(a) (a-1)/2;

void calc_time();////수행 시간을 측정하여 출력하는 함수
void input_copy(int size);//입력값으로 받은 배열 복사 함수
void reset_arr(int size);////복사된 배열을 초기화시키는 함수
void selection_sort(int arr[], int size);//선택정렬 함수
void bubble_sort(int arr[], int size);//버블정렬 함수 
void insertion_sort(int arr[], int size);//삽입정렬 함수 
void merge_sort(int arr[], int left, int right);//병합정렬 함수 
void conquer_leftRight(int arr[], int left, int mid, int right);//부분 정복 함수 
void quick_sort(int arr[], int left, int right);//퀵정렬 함수 
void swap(int arr[], int x, int y);//원소 x와 원소 y 바꾸기 함수 
int partition(int arr[], int left, int right);//왼쪽과 오른쪽으로 나누어 정렬하는 함수 
void heapify(int* arr, int arr_size);//배열을 힙으로 만들어주는 과정
void heap_sort(int *arr, int *size);//힙정렬 함수 

int input_arr[20000];
int res_arr[20000];
int arr_size = sizeof(input_arr) / sizeof(int);
int cnt;
clock_t start, end, elapse_time;

int main(void) {

	for (int i = 0; i < arr_size; i++) {
		input_arr[i] = rand();
	}

	//선택정렬 함수 호출 및 결과 출력
	printf("<selection sort>");
	input_copy(arr_size);//정렬되지 않은 배열을 복사하여 복사본을 가지고 정렬 진행
	cnt = 0;//step 5까지의 출력을 위해 정렬함수 호출 전 cnt 값을 0으로 초기화

	start = clock();
	selection_sort(res_arr, arr_size);
	end = clock();
	calc_time();

	reset_arr(arr_size);//정렬 후 복사본 초기화

	//버블정렬 함수 호출 및 결과 출력
	printf("<bubble sort>");
	input_copy(arr_size);
	cnt = 0;

	start = clock();
	bubble_sort(res_arr, arr_size);
	end = clock();
	calc_time();

	reset_arr(arr_size);

	//삽입정렬 함수 호출 및 결과 출력
	printf("<insertion sort>");
	input_copy(arr_size);
	cnt = 0;

	start = clock();
	insertion_sort(res_arr, arr_size);
	end = clock();
	calc_time();

	reset_arr(arr_size);

	//병합정렬 함수 호출 및 결과 출력
	printf("<merge sort>");
	input_copy(arr_size);
	cnt = 0;

	start = clock();
	merge_sort(res_arr, 0, arr_size - 1);
	end = clock();
	calc_time();

	reset_arr(arr_size);

	//힙정렬 함수 호출 및 결과 출력
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

	//퀵정렬 함수 호출 및 결과 출력
	printf("<quick sort>");
	input_copy(arr_size);
	cnt = 0;
	reset_arr(arr_size);

	return 0;
}

void calc_time() {
	elapse_time = end - start;
	printf(" 실행시간: %f msec\n\n", ((double)elapse_time / CLOCKS_PER_SEC)*1000);
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

void selection_sort(int arr[], int arr_size) {//선택정렬
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

void bubble_sort(int arr[], int arr_size) {//버블정렬
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

void insertion_sort(int arr[], int arr_size) {//삽입정렬
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

void merge_sort(int arr[], int left, int right) {//병합정렬
	int mid;

	if (left < right) {
		mid = (left + right) / 2;

		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		conquer_leftRight(arr, left, mid, right);
	}
}

void conquer_leftRight(int arr[], int left, int mid, int right) {
	//병합정렬로 나누어진 왼쪽 부분배열과 오른쪽 부분배열을 병합하기 위한 함수
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

void quick_sort(int arr[], int left, int right) {//퀵정렬
	int pivot;

	if (left <= right) {

		pivot = partition(arr, left, right);
		quick_sort(arr, left, pivot - 1);
		quick_sort(arr, pivot + 1, right);
	}

	return;
}

void swap(int arr[], int x, int y) {//배열의 원소 x와 y의 위치를 교환해주는 함수
	int tmp = arr[x];
	arr[x] = arr[y];
	arr[y] = tmp;
}

int partition(int arr[], int left, int right) {//왼쪽과 오른쪽으로 분할하여 정렬하는 함수
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

void heap_sort(int *arr, int *arr_size) {//힙 생성
	int tmp;
	tmp = arr[0];
	arr[0] = arr[*arr_size - 1];
	arr[*arr_size - 1] = tmp;
	--(*arr_size);
}