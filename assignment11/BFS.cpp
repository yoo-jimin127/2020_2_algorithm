//algorithm 2020 (na) class HW 11-(2) [240] 20193017 Yoo Jimin

#include <stdio.h>
#include<malloc.h>

int W = 9; //���� ���� �� ����ġ ��
int p[6] = { 0, 20, 30, 35, 12, 3 };
int w[6] = { 0, 2, 5, 7, 3, 1 };
int n = 5;
int maxprofit; //max profit
int include[6], bestset[6]; // include ���θ� ������ �迭�� bestset �迭 ����

typedef struct _Node {
	int level;//����� ����
	int profit;//�ش� ����� profit ��
	int weight;//�ش� ����� ����ġ weight ��
	struct _Node* next;
}Node;

typedef struct _Queue {
	Node* front; //�� ��
	Node* rear;
	int cnt;
}Queue;

void initialize(Queue** Q); //ť�� �ʱ�ȭ�ϴ� �۾�
void enqueue(Queue* Q, Node* v); //��� v�� ť Q�� �����ϴ� �۾��� �����ϴ� �Լ�
Node* dequeue(Queue* Q); //ť���� ��带 �����ϰ� ������ ��带 �����ϴ� �Լ�
int empty(Queue* Q); //ť�� ���°� empty���� Ȯ���ϴ� �Լ�
void kanpsack(); //ť�� ������ �������� ���°���Ʈ���� �����ϴ� �Լ�
float bound(Node u); //��� u�� bound�� ����ϴ� �۾� ����

int main(void) {
	kanpsack();
	printf("\n-----< max profit : %d >------\n", maxprofit);
}

void initialize(Queue** Q) { //ť�� �ʱ�ȭ�ϴ� �۾�
	(*Q) = (Queue*)malloc(sizeof(Queue));
	(*Q)->front = NULL;
	(*Q)->rear = NULL;
	
	(*Q)->cnt = 0;
}

void enqueue(Queue* Q, Node* v) {//��� v�� ť Q�� �����ϴ� �۾��� �����ϴ� �Լ�

	Node* newNode = (Node*)malloc(sizeof(Node)); //������

	//ť�� ���� ����� ���� ����
	newNode->level = v->level;
	newNode->profit = v->profit;
	newNode->weight = v->weight;

	newNode->next = v->next;

	if (Q->cnt == 0) { //ť�� ��� count ���� 0�� ���, �� ����ִ�(empty) ���
		Q->front = Q->rear = newNode;
	}
	else { //ť�� ������� ���� ���
		Q->rear->next = newNode;//ť�� �� ����� ���� ��忡 newNode�� ����
		Q->rear = newNode;
	}

	Q->cnt++;//ť�� ��� ���� ��Ÿ���� ���� cnt�� ���� 1 ����������
}

Node* dequeue(Queue* Q) { //ť���� ��带 �����ϰ� ������ ��带 �����ϴ� �Լ�

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

int empty(Queue* Q) {//ť�� ���°� empty���� Ȯ���ϴ� �Լ�
	if (Q->cnt == 0)//ť�� ����ִ� ��� (cnt ���� ���� 0) 1�� ����
		return 1;

	else //ť�� ����ִ� ���
		return 0;
}

void kanpsack() { //ť�� ������ �������� ���°���Ʈ���� �����ϴ� �Լ�
	Queue* Q; Node u; Node v; // ť Q�� ��� u, v ����

	initialize(&Q); //ť �ʱ�ȭ
	v.level = 0; //��� v�� level ���� 0���� �ʱ�ȭ
	v.profit = 0; //��� v�� profit ���� 0���� �ʱ�ȭ
	v.weight = 0; //��� v�� weight ���� 0���� �ʱ�ȭ
	maxprofit = 0; //maxprofit�� ���� 0���� �ʱ�ȭ

	v.next = NULL; 
	u.next = NULL; //v�� ��Ʈ�� �ǵ��� �ϴ� �۾��� ����

	enqueue(Q, &v); //ť�� ��� v ����
	printf("------enqueue------\n");//������ ����� ������ �ܼ�â�� ���
	printf("<level :%d, profit : %d, weight : %d, bound : %f> count of node : %d\n", v.level, v.profit, v.weight, bound(v), Q->cnt);

	while (!empty(Q)) {//ť�� ���� ���� ������ �ݺ�
		Node* v = dequeue(Q);//ť���� ��� v�� dequeue
		printf("\n------dequeue------\n");//������ ��� v�� ������ �ܼ�â�� ���
		printf("<level : %d, profit : %d, weight : %d> count of node : %d\n", v->level, v->profit, v->weight, Q->cnt);

		u.level = (v->level) + 1;//��� u�� ������ v�� ������ 1�� ���� ��
		u.profit = (v->profit) + p[u.level];//��� u�� profit, weight ���� �߰�
		u.weight = (v->weight) + w[u.level];

		if ((u.weight <= W) && (u.profit > maxprofit)) {//maxprofit�� ���� update �Ǵ� ����
			maxprofit = u.profit;
			printf("maxprofit : %d\n", maxprofit);//update�� maxprofit�� �� ���
		}

		if (bound(u) > maxprofit) { //maprofit���� ū bound ���� ������ ���
			enqueue(Q, &u);//u�� ť�� �߰��ϰ� u�� ���� �ܼ�â�� ���
			printf("------enqueue------\n");
			printf("< level : %d, profit : %d, weight : %d, bound : %f> count of node : %d\n", u.level, u.profit, u.weight, bound(u), Q->cnt);
		}

		u.profit = v->profit;
		u.weight = v->weight;

		if (bound(u) > maxprofit) { //�� ���� �������� ������ ���� ���� ��� 
			enqueue(Q, &u);//u�� ť�� �߰��ϰ� u�� ���� �ܼ�â�� ���
			printf("------enqueue------\n");
			printf("< level : %d, profit : %d, weight : %d, bound : %f> count of node : %d\n", u.level, u.profit, u.weight, bound(u), Q->cnt);
		}
	}
}

float bound(Node u) { //��� u�� bound�� ����ϴ� �۾� ����
	int j, k;
	int totweight;
	float result;

	if (u.weight >= W)
		return 0;//��� u�� weight ���� W = 9�� �ʰ��ϴ� ��� 0�� ����

	else {
		result = u.profit;//result ���� u ����� profit ���� ����
		totweight = u.weight;//totweight ���� u ����� weight ���� ����
		j = u.level + 1;//u�� ���� ��带 ��ȸ

		while (j <= n && totweight + w[j] <= W) {
			result = result + p[j];//j��° �ε����� profit�� weight�� result�� totweight�� ������
			totweight = totweight + w[j];
			j++;
		}

		k = j;

		if (k <= n) {
			result = result + (W - totweight) * (p[k] / w[k]); //result ���� ����
		}
		return result;
	}
}