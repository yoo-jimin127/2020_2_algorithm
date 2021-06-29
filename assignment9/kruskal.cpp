//algorithm 2020 class (na) HW9 [240]Yoo Jimin_20193017

#include <stdio.h>
#define VERTEX_SIZE 8
#define MAX 100 //���� �ִ� ũ��

int parent_node[VERTEX_SIZE]; //vertex�� �θ� ���
int num[VERTEX_SIZE]; //������ ũ��

typedef struct _Element{//element ����ü
	int v; //vertex v
	int u; //vertex u
	int weight; //������ ���� ���̿� �Ҵ�� ����ġ ��
}Element;


typedef struct _Heap{//�� ����ü
	Element heap[MAX];//MAX����ŭ�� ����ü �迭�� heap ����
	int heap_size;
}Heap; //���� ������Ÿ��

void reset_heap(_Heap* h);
void insert_element(Heap* h, Element item);
Element delete_element(Heap* h);
void reset_set(void);
int Find(int v);
void Union(int v1, int v2);
void insert_edge(Heap* h, int v, int u, int weig);
int kruskal(int n);

int main(void) {
	printf("----Minimum Spnning Tree By <Kruskal algorithm>----\n\n");
	printf("�ּ� ���� Ʈ���� ����� ����(�� ���� ������ ���� ����ġ ���)\n");
	printf("\n");
	kruskal(14); // ���� ������ ������ kruskal �Լ��� ���ڷ� ����
}

//���� �ʱ�ȭ��Ű�� �Լ�
void reset_heap(_Heap* h) {
	h->heap_size = 0;
}

//���� ����ü Element�� �߰��ϴ� �Լ�
void insert_element(Heap* h, Element item) {
	int i = ++(h->heap_size);

	//Ʈ���� ��ȸ�ϸ� �θ���� �� ��
	while (i != 1 && item.weight < h->heap[i / 2].weight) { //i�� ��Ʈ��尡 �ƴ� ���ÿ� �Է¹��� element�� weight���� i�� �θ����� weight������ ���� ��� ���� �ö�
		h->heap[i] = h->heap[i / 2]; //�������� i��° ��带 �θ���� ����
		i = i/2; //�������� �ε����� �θ����� �ε����� ����
	}

	h->heap[i] = item; //�� ��ȸ�� ���� ������ while���� �������� ������ �ε��� ��ġ�� item ����
}

//���� ������ �߰��ϴ� �Լ�
void insert_edge(Heap* h, int v, int u, int weig) {
	Element node;
	node.v = v;//���ڷ� �Է¹��� ���� v�� u, �ش� �� ���� ������ ����ġ ���� ����ü ���� node ���� ����
	node.u = u;
	node.weight = weig;

	insert_element(h, node);//������ �߰��ߴٸ� ������ �߰��ϴ� insert_element �Լ��� ���� �ּҰ��� ����ü ���� node�� ���ڷ� �ѱ�
}

//������ ���Ե� Element ����ü�� �����ϴ� �Լ�
Element delete_element(Heap* h) {
	Element data, tmp;
	int parent_node, child_node;
	parent_node = 1;//��Ʈ��带 ù ���࿡���� �θ���� ����
	child_node = 2;//��Ʈ���(1)�� ���� �ڽ��� 2��° �ε����� ��ġ�� ��带 child node �� ����

	data = h->heap[parent_node]; //��ȯ�� ��Ʈ����� ���� data�� ����
	tmp = h->heap[(h->heap_size)--]; //������ ����� ���� tmp�� �����ϰ�, ���� ����� �����ϴ� ���� heap_size�� ũ�⸦ 1 ����

	while (child_node <= h->heap_size) { //child node�� �� ������ ������ ������ �ݺ�

		//child node ������ ����ġ �� ��
		if ((child_node < h->heap_size) && (h->heap[child_node].weight) > h->heap[child_node + 1].weight)
			child_node++;

		if (tmp.weight <= h->heap[child_node].weight) //tmp�� ����ġ�� �� ���� ��� �ݺ��� Ż��
			break;

		h->heap[parent_node] = h->heap[child_node];
		parent_node = child_node;
		child_node *= 2; //������ ��ġ�� child node�� �̵�
	}

	h->heap[parent_node] = tmp;
	return data;
}

//������ �ʱ�ȭ�ϴ� �Լ�
void reset_set(void) {
	for (int i = 0; i < VERTEX_SIZE; i++) {
		parent_node[i] = -1; //�θ��� �迭�� -1�� �ʱ�ȭ ��Ŵ
		num[i] = 1; //������ ������ŭ �����ϴ� ������ ũ�� �迭�� 1�� �ʱ�ȭ ��Ŵ
	}
}

// vertex�� ���Ե� ������ ã�� �Լ�
int Find(int v) {
	int i, p, tmp;

	for (i = v; (p = parent_node[i]) >= 0; i = p); //��Ʈ ����� ��ġ���� �ݺ��Ͽ�
	tmp = i; //��Ʈ����� ������ tmp�� ������

	for (i = v; (p = parent_node[i]) >= 0; i = p)
		parent_node[i] = tmp; //������ ���� ��� ������ parent node ���� ��Ʈ���� ����

	return tmp; //��Ʈ��� ��ȯ
}


//������ ��ġ�� �Լ�
void Union(int v1, int v2) {

	//�� ������ ����� ������ ��
	if (num[v1] < num[v2]) { //v2�� �� ũ��
		parent_node[v1] = v2; //v1�� �θ� ��带 v2�� ����
		num[v1] += num[v2]; //v1�� ũ�⸦ v2 ���� ������
	}

	else {//v1�� �� ũ��
		parent_node[v2] = v1;//v2�� �θ� ��带 v1���� ����
		num[v2] += num[v1];//v2�� ũ�⸦ v1 ���� ������
	}
}

//kruskal �˰����� ����� �ּ� ���� Ʈ���� ���ϴ� �Լ�
int kruskal(int n) {
	Element e; //���� ���
	Heap h; //minimum spanning tree
	int edge_cnt = 0, sum = 0;
	int setU, setV; //���� u�� ���� v�� ������ ��ȣ

	reset_heap(&h);//���� ������ �ʱ�ȭ�ϴ� �۾�
	reset_set();

	//������ ��� ���� ����(������ ���ԵǸ� insert_edge �Լ����� �ڵ����� insert_element �Լ��� ȣ����
	insert_edge(&h, 1, 2, 11);
	insert_edge(&h, 1, 3, 9);
	insert_edge(&h, 1, 4, 8);
	insert_edge(&h, 2, 3, 3);
	insert_edge(&h, 2, 5, 8);
	insert_edge(&h, 2, 6, 8);
	insert_edge(&h, 3, 4, 15);
	insert_edge(&h, 3, 6, 12);
	insert_edge(&h, 3, 7, 1);
	insert_edge(&h, 4, 7, 10);
	insert_edge(&h, 5, 6, 7);
	insert_edge(&h, 5, 8, 4);
	insert_edge(&h, 6, 8, 5);
	insert_edge(&h, 7, 8, 2);//�� ������ �����ϴ� 14���� ������ ���� ���� ���� �Ϸ�


	while (edge_cnt < n - 1) { //������ ������ ���ڷ� �Է¹��� n-1�� �Ǳ���� �ݺ�
		e = delete_element(&h); //�ּ��� ����ġ�� ������ ���� ȹ��
		setU = Find(e.u); //���� u�� ���� ��ȣ
		setV = Find(e.v); //���� v�� ���� ��ȣ

		if (setU != setV) { //�� ������ ���� �ٸ� ���տ� ���ϴ� ���
			printf("(v%d , v%d) is selected, weight : %d\n", e.u, e.v, e.weight);
			sum += e.weight;
			edge_cnt++; //������ �ϳ� �߰��Ͽ�
			Union(setU, setV); //setU�� setV Union
		}
	}

	return 0;
}