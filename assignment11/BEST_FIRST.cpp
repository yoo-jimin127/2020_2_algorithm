//algorithm 2020 (na) class HW 11-(3) [240] 20193017 Yoo Jimin

#include<stdio.h>
#include<malloc.h>
#pragma warning (disable : 4996)

int W = 9; //과제 명세서 상 가중치 값
int p[6] = { 0, 20, 30, 35, 12, 3 };
int w[6] = { 0, 2, 5, 7, 3, 1 };
int n = 5;
int maxprofit; //max profit
int include[6], bestset[6]; // include 여부를 저장할 배열과 bestset 배열 저장

typedef struct Node {//node 구조체
	int level;//노드의 레벨
	int profit;//해당 노드의 profit 값
	int weight;//해당 노드의 가중치 weight 값
	float bound;//해당 노드의 bound 값
}Node;

typedef struct Queue_of_node {
	Node* heap[9];//노드를 구조체 멤버로 가지는 힙 생성
	int cnt; //큐의 노드 개수
}Queue_of_node;

void insertNode(Queue_of_node* h, Node* v);
Node* deleteMax(Queue_of_node* k);
void initialize(Queue_of_node** k);
int isEmpty(Queue_of_node* Q);
void kanpsack3();
float bound(Node u);

int main(void) {
	kanpsack3();
	printf("\n------< maxprofit : %d >------\n", maxprofit);

	return 0;
}

void insertNode(Queue_of_node* h, Node* v) { //노드를 삽입하는 함수
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드 생성

	//큐에 삽입할 노드 v의 level, profit, weight, bound의 값 저장
	newNode->level = v->level;
	newNode->profit = v->profit;
	newNode->weight = v->weight;
	newNode->bound = v->bound;

	int i;
	i = ++(h->cnt);

	while ((i != 1) && (newNode->bound > h->heap[i / 2]->bound)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;//i의 인덱스를 높여 부모노드로 접근해 비교하는 작업을 수행
	}
	h->heap[i] = newNode; //힙의 i번째 인덱스에 노드를 삽입
}

Node* deleteMax(Queue_of_node* k) { //힙에서 가장 큰 값의 bound를 가지는 노드를 삭제하고 리턴하는 함수
	Node* item;
	Node* curr;
	int parent, child;

	item = k->heap[1]; //힙의 1번째 노드인 루트노드를 삭제
	curr = k->heap[(k->cnt)--];//현재 노드를 cnt -1 번째 인덱스를 가리키도록 함

	parent = 1;//parent노드는 1번째 노드를 가리키도록 함
	child = 2; //child는 parent의 왼쪽 자식을 가리키도록 함

	while (child <= k->cnt) { //child의 값이 힙의 cnt 값보다 작거나 같을 때까지만 반복문 진행
		//자식노드 중 더 작은 자식노드 찾음

		if ((child < k->cnt) && (k->heap[child]->bound) < (k->heap[child + 1]->bound)) {
			child++; //child 중에서 더 작은 child의 값을 찾아, 찾은 child가 오른쪽 자식이 됨
		}

		if (curr->bound >= k->heap[child]->bound) {
			break;
		}

		k->heap[parent] = k->heap[child];//최대 bound 값을 가지는 노드를 삭제한 뒤 parent 인덱스의 노드가 child인덱스의 노드를 가리키도록 설정
		parent = child;//부모노드의 인덱스를 자식노드로 따라 내려가도록 설정
		child *= 2;//자식노드의 인덱스 재설정
	}

	k->heap[parent] = curr;
	return item;//삭제한 노드(가장 큰 bound 값을 가지는 노드)를 리턴
}

void initialize(Queue_of_node** k) {//힙의 모든 노드를 초기화시키는 함수
	(*k) = (Queue_of_node*)malloc(sizeof(Queue_of_node));
	(*k)->cnt = 0;
}

int isEmpty(Queue_of_node* Q) {//힙의 empty 여부를 확인하는 함수
	if (Q->cnt == 0)//큐의 노드의 개수를 나타내는 변수 cnt의 값이 0인 경우 (비어있는 경우) 1 리턴
		return 1;

	else //힙이 비어있지 않은 경우 0 리턴
		return 0;
}

float bound(Node u) { //노드 u의 bound 값을 계산하는 함수
	int j, k;//인덱스
	int totweight;//가중치의 합
	float result;//결과 값(bound)

	if (u.weight >= W)//노드 u의 weight 값이 W = 9를 초과하는 경우 0을 리턴
		return 0;

	else {
		result = u.profit;//result 값에 u 노드의 profit 값을 저장
		totweight = u.weight;//totweight 값에 u 노드의 weight 값을 저장
		j = u.level + 1;//u의 다음 노드를 순회

		while (j <= n && totweight + w[j] <= W) {
			result = result + p[j];//j번째 인덱스의 profit과 weight를 result와 totweight에 더해줌
			totweight = totweight + w[j];
			j++;
		}

		k = j;

		if (k <= n) {
			result = result + (W - totweight) * (p[k] / w[k]); //result 값의 누적
		}
		return result;
	}
}

void kanpsack3() {//입력값으로 상태공간트리를 생성하는 함수
	Queue_of_node* PQ;//힙 생성
	Node u, v;//노드 u와 v 생성

	initialize(&PQ);//힙 초기화

	v.level = 0; 
	v.profit = 0; 
	v.weight = 0; 
	v.bound = bound(v); //노드 v의 level, profit, weight, bound 값을 초기화시켜줌
	maxprofit = 0;//최대 이익 0으로 초기화

	insertNode(PQ, &v);//힙에 노드 v를 삽입
	printf("\'insert\' Node <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d \n", v.level, v.profit, v.weight, v.bound, PQ->cnt);

	printf("\n");

	while (!isEmpty(PQ)) {
		Node* v = deleteMax(PQ);//힙에서 노드 v를 삭제
		printf("\n\'delete Node\' <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d\n", v->level, v->profit, v->weight, v->bound, PQ->cnt);

		if (v->bound > maxprofit) { //check if node is still
			u.level = (v->level) + 1; //유망한 노드인지를 검사
			u.profit = (v->profit) + p[u.level];
			u.weight = (v->weight) + w[u.level];

			if ((u.weight <= W) && (u.profit > maxprofit)) {
				maxprofit = u.profit;
				printf("maxprofit : %d\n", maxprofit);
			}

			u.bound = bound(u);

			if (bound(u) > maxprofit) {
				insertNode(PQ, &u);//힙에 노드 u를 추가
				printf("\'insert\' Node <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d \n", u.level, u.profit, u.weight, bound(u), PQ->cnt);
			}

			u.weight = v->weight;//set u to the child
			u.profit = v->profit;//that does not include
			u.bound = bound(u);//the next item

			if (bound(u) > maxprofit) { 
				insertNode(PQ, &u);//힙에 노드 u를 추가
				printf("\'insert\' Node <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d \n", u.level, u.profit, u.weight, u.bound, PQ->cnt);
			}
		}
	}
}