//algorithm 2020 (na) class HW 11-(3) [240] 20193017 Yoo Jimin

#include<stdio.h>
#include<malloc.h>
#pragma warning (disable : 4996)

int W = 9; //���� ���� �� ����ġ ��
int p[6] = { 0, 20, 30, 35, 12, 3 };
int w[6] = { 0, 2, 5, 7, 3, 1 };
int n = 5;
int maxprofit; //max profit
int include[6], bestset[6]; // include ���θ� ������ �迭�� bestset �迭 ����

typedef struct Node {//node ����ü
	int level;//����� ����
	int profit;//�ش� ����� profit ��
	int weight;//�ش� ����� ����ġ weight ��
	float bound;//�ش� ����� bound ��
}Node;

typedef struct Queue_of_node {
	Node* heap[9];//��带 ����ü ����� ������ �� ����
	int cnt; //ť�� ��� ����
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

void insertNode(Queue_of_node* h, Node* v) { //��带 �����ϴ� �Լ�
	Node* newNode = (Node*)malloc(sizeof(Node)); //���ο� ��� ����

	//ť�� ������ ��� v�� level, profit, weight, bound�� �� ����
	newNode->level = v->level;
	newNode->profit = v->profit;
	newNode->weight = v->weight;
	newNode->bound = v->bound;

	int i;
	i = ++(h->cnt);

	while ((i != 1) && (newNode->bound > h->heap[i / 2]->bound)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;//i�� �ε����� ���� �θ���� ������ ���ϴ� �۾��� ����
	}
	h->heap[i] = newNode; //���� i��° �ε����� ��带 ����
}

Node* deleteMax(Queue_of_node* k) { //������ ���� ū ���� bound�� ������ ��带 �����ϰ� �����ϴ� �Լ�
	Node* item;
	Node* curr;
	int parent, child;

	item = k->heap[1]; //���� 1��° ����� ��Ʈ��带 ����
	curr = k->heap[(k->cnt)--];//���� ��带 cnt -1 ��° �ε����� ����Ű���� ��

	parent = 1;//parent���� 1��° ��带 ����Ű���� ��
	child = 2; //child�� parent�� ���� �ڽ��� ����Ű���� ��

	while (child <= k->cnt) { //child�� ���� ���� cnt ������ �۰ų� ���� �������� �ݺ��� ����
		//�ڽĳ�� �� �� ���� �ڽĳ�� ã��

		if ((child < k->cnt) && (k->heap[child]->bound) < (k->heap[child + 1]->bound)) {
			child++; //child �߿��� �� ���� child�� ���� ã��, ã�� child�� ������ �ڽ��� ��
		}

		if (curr->bound >= k->heap[child]->bound) {
			break;
		}

		k->heap[parent] = k->heap[child];//�ִ� bound ���� ������ ��带 ������ �� parent �ε����� ��尡 child�ε����� ��带 ����Ű���� ����
		parent = child;//�θ����� �ε����� �ڽĳ��� ���� ���������� ����
		child *= 2;//�ڽĳ���� �ε��� �缳��
	}

	k->heap[parent] = curr;
	return item;//������ ���(���� ū bound ���� ������ ���)�� ����
}

void initialize(Queue_of_node** k) {//���� ��� ��带 �ʱ�ȭ��Ű�� �Լ�
	(*k) = (Queue_of_node*)malloc(sizeof(Queue_of_node));
	(*k)->cnt = 0;
}

int isEmpty(Queue_of_node* Q) {//���� empty ���θ� Ȯ���ϴ� �Լ�
	if (Q->cnt == 0)//ť�� ����� ������ ��Ÿ���� ���� cnt�� ���� 0�� ��� (����ִ� ���) 1 ����
		return 1;

	else //���� ������� ���� ��� 0 ����
		return 0;
}

float bound(Node u) { //��� u�� bound ���� ����ϴ� �Լ�
	int j, k;//�ε���
	int totweight;//����ġ�� ��
	float result;//��� ��(bound)

	if (u.weight >= W)//��� u�� weight ���� W = 9�� �ʰ��ϴ� ��� 0�� ����
		return 0;

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

void kanpsack3() {//�Է°����� ���°���Ʈ���� �����ϴ� �Լ�
	Queue_of_node* PQ;//�� ����
	Node u, v;//��� u�� v ����

	initialize(&PQ);//�� �ʱ�ȭ

	v.level = 0; 
	v.profit = 0; 
	v.weight = 0; 
	v.bound = bound(v); //��� v�� level, profit, weight, bound ���� �ʱ�ȭ������
	maxprofit = 0;//�ִ� ���� 0���� �ʱ�ȭ

	insertNode(PQ, &v);//���� ��� v�� ����
	printf("\'insert\' Node <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d \n", v.level, v.profit, v.weight, v.bound, PQ->cnt);

	printf("\n");

	while (!isEmpty(PQ)) {
		Node* v = deleteMax(PQ);//������ ��� v�� ����
		printf("\n\'delete Node\' <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d\n", v->level, v->profit, v->weight, v->bound, PQ->cnt);

		if (v->bound > maxprofit) { //check if node is still
			u.level = (v->level) + 1; //������ ��������� �˻�
			u.profit = (v->profit) + p[u.level];
			u.weight = (v->weight) + w[u.level];

			if ((u.weight <= W) && (u.profit > maxprofit)) {
				maxprofit = u.profit;
				printf("maxprofit : %d\n", maxprofit);
			}

			u.bound = bound(u);

			if (bound(u) > maxprofit) {
				insertNode(PQ, &u);//���� ��� u�� �߰�
				printf("\'insert\' Node <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d \n", u.level, u.profit, u.weight, bound(u), PQ->cnt);
			}

			u.weight = v->weight;//set u to the child
			u.profit = v->profit;//that does not include
			u.bound = bound(u);//the next item

			if (bound(u) > maxprofit) { 
				insertNode(PQ, &u);//���� ��� u�� �߰�
				printf("\'insert\' Node <level :%d, profit : %d, weight : %d, bound : %f> count of node : %d \n", u.level, u.profit, u.weight, u.bound, PQ->cnt);
			}
		}
	}
}