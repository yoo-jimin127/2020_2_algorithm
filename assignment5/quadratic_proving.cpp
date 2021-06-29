//20193017 YooJimin algorithm (na) # HW 5 - 4 quadratic proving source code

#include <stdio.h>
#pragma warning (disable : 4996)
#define TABLE_SIZE 13 //0~12의 13 크기의 테이블 값

int table_arr[TABLE_SIZE]; //13크기만큼의 테이블 배열

//테이블의 모든 원소를 NULL로 초기화 시키는 init 함수
void init(int table_arr[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		table_arr[i] = NULL;
	}
}

//이차원조사 함수 구현부
int quadratic_proving(int key) {
	int idx;

	for (int i = 0; i < TABLE_SIZE; i++) {
		idx = (key + (i*i)) % 13; //키 값을 받아 hi(x) = (x+(i*i)) mod 13을 적용하여 테이블 주소를 얻는 작업
		//충돌이 일어나는 횟수에 따라 i값이 0부터 테이블의 크기만큼 증가하여 해시함수에 적용됨

		if (table_arr[idx] == NULL) return idx; //해시함수를 적용한 테이블 주소(인덱스)가 배열 상에서 NULL일 때, 해당 인덱스 리턴 
	}
}

int main(void) {
	int input_arr[8] = { 10, 20, 30, 40, 33, 46, 50, 60 };
	int quadratic_idx;
	init(table_arr);//테이블 배열 초기화

	for (int i = 0; i < sizeof(input_arr) / sizeof(int); i++) {
		quadratic_idx = quadratic_proving(input_arr[i]);//input_arr의 원소를 차례로 이차원조사하여 테이블 주소를 반환받음
		table_arr[quadratic_idx] = input_arr[i];//테이블 배열의 반환받은 인덱스 주소에 input_arr[i]번째 원소를 저장함
	}

	printf("------quadratic proving result------\n");

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table_arr[i] != NULL) {//테이블 배열의 i번째 원소가 NULL이 아닌 경우 해당 테이블 주소와 원소값을 출력함
			printf("table : %d -> data : %d\n", i, table_arr[i]);
		}

		else {
			printf("table : %d -> NULL\n", i);
		}
	}

	return 0;
}