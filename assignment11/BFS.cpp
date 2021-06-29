//algorithm 2020 (na) class HW 11-(2) [240] 20193017 Yoo Jimin

#include <stdio.h>
#include<malloc.h>

int W = 9; //과제 명세서 상 가중치 값
int p[6] = { 0, 20, 30, 35, 12, 3 };
int w[6] = { 0, 2, 5, 7, 3, 1 };
int n = 5;
int maxprofit; //max profit
int include[6], bestset[6]; // include 여부를 저장할 배열과 bestset 배열 저장

typedef struct _Node {
	int level;//노드의 레벨
	int profit;//해당 노드의 profit 값
	int weight;//해당 노드의 가중치 weight 값
	struct _Node* next;
}Node;

typedef struct _Queue {
	Node* front; //맨 앞
	Node* rear;
	int cnt;
}Queue;

void initialize(Queue** Q); //큐를 초기화하는 작업
void enqueue(Queue* Q, Node* v); //노드 v를 큐 Q에 삽입하는 작업을 진행하는 함수
Node* dequeue(Queue* Q); //큐에서 노드를 삭제하고 삭제한 노드를 리턴하는 함수
int empty(Queue* Q); //큐의 상태가 empty인지 확인하는 함수
void kanpsack(); //큐의 노드들을 바탕으로 상태공간트리를 구축하는 함수
float bound(Node u); //노드 u의 bound를 계산하는 작업 수행

int main(void) {
	kanpsack();
	printf("\n-----< max profit : %d >------\n", maxprofit);
}

void initialize(Queue** Q) { //큐를 초기화하는 작업
	(*Q) = (Queue*)malloc(sizeof(Queue));
	(*Q)->front = NULL;
	(*Q)->rear = NULL;
	
	(*Q)->cnt = 0;
}

void enqueue(Queue* Q, Node* v) {//노드 v를 큐 Q에 삽입하는 작업을 진행하는 함수

	Node* newNode = (Node*)malloc(sizeof(Node)); //노드생성

	//큐에 넣을 노드의 정보 복사
	newNode->level = v->level;
	newNode->profit = v->profit;
	newNode->weight = v->weight;

	newNode->next = v->next;

	if (Q->cnt == 0) { //큐의 노드 count 수가 0인 경우, 즉 비어있는(empty) 경우
		Q->front = Q->rear = newNode;
	}
	else { //큐가 비어있지 않은 경우
		Q->rear->next = newNode;//큐의 끝 노드의 다음 노드에 newNode를 삽입
		Q->rear = newNode;
	}

	Q->cnt++;//큐의 노드 수를 나타내는 변수 cnt의 값을 1 증가시켜줌
}

Node* dequeue(Queue* Q) { //큐에서 노드를 삭제하고 삭제한 노드를 리턴하는 함수

	Node* deNode = Q->front;

	if (Q->front->next == NULL) {
		Q->front = NULL;
		Q->rear = NULL;
	}
	else {
		Q->front = Q->front->next;
	}

	Q->cnt--;
	return deNode;
}

int empty(Queue* Q) {//큐의 상태가 empty인지 확인하는 함수
	if (Q->cnt == 0)//큐가 비어있는 경우 (cnt 변수 값이 0) 1을 리턴
		return 1;

	else //큐가 비어있는 경우
		return 0;
}

void kanpsack() { //큐의 노드들을 바탕으로 상태공간트리를 구축하는 함수
	Queue* Q; Node u; Node v; // 큐 Q와 노드 u, v 생성

	initialize(&Q); //큐 초기화
	v.level = 0; //노드 v의 level 값을 0으로 초기화
	v.profit = 0; //노드 v의 profit 값을 0으로 초기화
	v.weight = 0; //노드 v의 weight 값을 0으로 초기화
	maxprofit = 0; //maxprofit의 값을 0으로 초기화

	v.next = NULL; 
	u.next = NULL; //v가 루트가 되도록 하는 작업을 진행

	enqueue(Q, &v); //큐에 노드 v 삽입
	printf("------enqueue------\n");//삽입한 노드의 정보를 콘솔창에 출력
	printf("<level :%d, profit : %d, weight : %d, bound : %f> count of node : %d\n", v.level, v.profit, v.weight, bound(v), Q->cnt);

	while (!empty(Q)) {//큐가 비지 않을 때까지 반복
		Node* v = dequeue(Q);//큐에서 노드 v를 dequeue
		printf("\n------dequeue------\n");//삭제한 노드 v의 정보를 콘솔창에 출력
		printf("<level : %d, profit : %d, weight : %d> count of node : %d\n", v->level, v->profit, v->weight, Q->cnt);

		u.level = (v->level) + 1;//노드 u의 레벨은 v의 레벨에 1을 더한 값
		u.profit = (v->profit) + p[u.level];//노드 u의 profit, weight 값에 추가
		u.weight = (v->weight) + w[u.level];

		if ((u.weight <= W) && (u.profit > maxprofit)) {//maxprofit의 값이 update 되는 조건
			maxprofit = u.profit;
			printf("maxprofit : %d\n", maxprofit);//update된 maxprofit의 값 출력
		}

		if (bound(u) > maxprofit) { //maprofit보다 큰 bound 값을 가지는 노드
			enqueue(Q, &u);//u를 큐에 추가하고 u의 값을 콘솔창에 출력
			printf("------enqueue------\n");
			printf("< level : %d, profit : %d, weight : %d, bound : %f> count of node : %d\n", u.level, u.profit, u.weight, bound(u), Q->cnt);
		}

		u.profit = v->profit;
		u.weight = v->weight;

		if (bound(u) > maxprofit) { //그 다음 아이템을 가지고 있지 않은 노드 
			enqueue(Q, &u);//u를 큐에 추가하고 u의 값을 콘솔창에 출력
			printf("------enqueue------\n");
			printf("< level : %d, profit : %d, weight : %d, bound : %f> count of node : %d\n", u.level, u.profit, u.weight, bound(u), Q->cnt);
		}
	}
}

float bound(Node u) { //노드 u의 bound를 계산하는 작업 수행
	int j, k;
	int totweight;
	float result;

	if (u.weight >= W)
		return 0;//노드 u의 weight 값이 W = 9를 초과하는 경우 0을 리턴

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