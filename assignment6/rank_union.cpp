//algorithm 2020 (na) class HW6 20193017 [240]Yoo Jimin

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int rank[9];//각 데이터의 랭크 값을 저장하는 배열
char parent[9] = { 'a','b','c','d','e','f','g','h','i' };//parent 배열의 값 초기화
int x_idx, y_idx;

//함수 선언부
void make_set(char data);
char find_set(char x_data);
void union_set(char x_data, char y_data);

int main(void) {
	union_set('a', 'b');//(a) 집합의 첫번째 트리 b -> a

	union_set('d', 'e');//(b) 집합의 첫번째 트리 e -> d

	union_set('f', 'g');//(b) 집합의 두번째 트리 f -> g
	union_set('f', 'h');//(b) 집합의 두번째 트리 f -> h
	union_set('f', 'i');//(b) 집합의 두번째 트리 f -> i

	printf("------beginning tree set state------\n");
	//아무런 union 과정을 진행하지 않은 (a)집합과 (b)집합의 초기 상태 출력
	printf("< (a) tree set >\n");
	for (int i = 0; i < 3; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	printf("< (b) tree set >\n");
	for (int i = 3; i < 9; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	printf("------Union each tree set state------\n");
	//(a)집합과 (b)집합 각각이 union과정을 거친 상태 출력
	union_set('a', 'c');//(a)집합의 두 트리를 union
	printf("< (a) tree set >\n");
	for (int i = 0; i < 3; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	union_set('d', 'f');//(b)집합의 두 트리를 union
	printf("< (b) tree set >\n");
	for (int i = 3; i < 9; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	printf("------final result <Union by Rank>------\n");
	//(a)집합과 (b) 집합을 union 한 상태 출력
	union_set('a', 'd');//(a)집합과 (b)집합을 union
	for (int i = 0; i < 9; i++) {
		printf("%c ", parent[i]);
	}

	return 0;
}


//노드 data를 유일한 원소로 하는 집합을 만드는 make_set 함수
void make_set(char data) {
	parent[data - 97] = data;
	rank[data - 97] = 0;//유일한 원소이기에 입력받은 data의 rank는 0으로 설정
}

//노드 x_data가 속한 집합을 알아낸 뒤 노드 x_data가 포함된 트리의 루트를 리턴하는 find_set 함수
char find_set(char x_data) {
	if (parent[x_data - 97] != x_data) return find_set(parent[x_data - 97]);  //parent의 원소값과 비교하여 같지 않을 경우 find_set을 재귀호출	
	else return parent[x_data-97];
}

//노드 x_data가 속한 집합과 y_data가 속한 집합을 합치는 union_set 함수
void union_set(char x_data, char y_data) {
	x_idx = find_set(x_data);//x_data가 속한 집합을 find_set에서 찾아 x_data가 포함된 트리의 루트노드를 리턴받음
	y_idx = find_set(y_data);//y_data가 속한 집합을 find_set에서 찾아 y_data가 포함된 트리의 루트노드를 리턴받음
	
	if (rank[x_idx] > rank[y_idx]) parent[y_idx] = x_data;//x 집합의 rank가 높으면 parent y에 x 집합을 합침

	else if (rank[x_idx] < rank[y_idx]) parent[x_idx] = y_data;//y 집합의 rank가 높으면 parent x에 y 집합을 합침
	
	else if (rank[x_idx] == rank[y_idx]) {
		rank[x_idx]++;//x 집합과 y 집합의 rank가 같으면 둘 중 rank를 골라 rank+1
	}
}