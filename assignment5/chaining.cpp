//20193017 YooJimin algorithm (na) # HW 5 - 5 chaining source code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
#define TABLE_SIZE 13
#define h(x) (x % TABLE_SIZE)//해시 함수: h(x) = x mod 13 (TABLE_SIZE == 13)

//구조체 선언부
typedef struct Chain {
	struct Chain* next; //체인의 다음 노드를 가리키는 포인터
	int value;//노드에 저장되는 데이터 값
}Chain;

//함수 정의부(insertChain, connectChain function)
Chain* insertChain(Chain* table, int input, int input_size);
Chain* connectChain(Chain* table, int table_idx, int value);

//데이터 삽입 함수
Chain* insertChain(Chain* table, int input, int input_size) {
	int data;

	table = connectChain(table, input % 13, input_size);//해시테이블에 입력 원소 삽입 작업을 하는 함수 호출
	return table;
}

//체이닝을 이용해 각 원소를 추가하며 노드를 연결해나가는 함수
Chain* connectChain(Chain* table, int table_idx, int value) {
	Chain* newChain;
	Chain* currChain;

	newChain = (Chain*)malloc(sizeof(Chain));//새로운 노드의 메모리 동적할당
	newChain->value = value;//새 노드의 value값을 입력받은 원소로 채우고
	newChain->next = NULL;//새 노드의 next는 NULL로 초기화

	if (table[table_idx].next == NULL) {//인자로 받은 인덱스 주소의 next 노드가 NULL이라면 인덱스의 next에 새 노드 추가 
		table[table_idx].next = newChain;

		return table;
	}

	currChain = table[table_idx].next;//현재 노드를 인자로 받은 인덱스 주소의 next를 가리키도록 설정

	while (currChain->next != NULL) {//현재 노드의 next가 NULL이 아닐 때까지 curr = curr+1 작업 반복
		currChain = currChain->next;
	}

	currChain->next = newChain;//curr체인의 next가 NULL이어서 반복문을 탈출하면 curr체인의 next에 새 노드를 지정한다.

	return table;
}

int main(void) {
	Chain* table, *curr;
	int hashTable, value;
	int choice, search;

	int input_arr[8] = { 10, 20, 30, 40, 33, 46, 50, 60 };

	//테이블의 메모리 동적할당
	table = (Chain*)malloc(TABLE_SIZE * sizeof(Chain));

	//테이블의 헤더 초기화
	for (int i = 0; i < TABLE_SIZE; i++) {
		table[i].next = NULL;
	}

	for (int i = 0; i < sizeof(input_arr) / sizeof(int); i++) {
		insertChain(table, input_arr[i], input_arr[i]);//데이터 삽입 함수에 input_arr의 원소를 하나씩 추가하는 작업
	}

	printf("------chaining result------\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i].next == NULL) {
			printf("table %d : NULL\n", i);
			continue;
		}

		curr = table[i].next;//curr포인터로 해시테이블의 i번째 주소의 next를 가리킴

		printf("table %d data ", i);

		while (curr != NULL) {
			printf("-> %d ", curr->value);//curr노드가 NULL이 아닌 경우 해당 해시테이블의 value를 출력함
			curr = curr->next;//데이터를 출력한 뒤 curr=curr+1을 반복하여 모든 테이블 주소를 순회함
		}
		printf("\n");
	}

	return 0;
}