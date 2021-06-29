//algorithm 2020 class (na) HW9 [240]Yoo Jimin_20193017
#include <stdio.h> 
#pragma warining (disable : 4996)

#define INF 999 //���� �� ������ �������� ���� ��� ����Ǵ� infinity�� ��
#define VERTEX_SIZE 8 //������ ����

typedef struct Edge {
	int v1;
	int v2;
};

Edge edge[VERTEX_SIZE - 1];

//�׷����� ������� �Է�
int W[VERTEX_SIZE][VERTEX_SIZE] = {
	0, 11, 9, 8, INF, INF, INF, INF,
	11, 0, 3, INF, 8, 8, INF, INF,
	9, 3, 0, 15, INF, 12, 1, INF,
	8, INF, 15, 0, INF, INF, 10, INF,
	INF, 8, INF, INF, 0, 7, INF, 4,
	INF, 8, 12, INF, 7, 0, INF, 5,
	INF, INF, 1, 10, INF, INF, 0, 2,
	INF, INF, INF, INF, 4, 5, 2, 0
};

void prim(int start); //prim algorithm���� Minimum Spanning Tree ���ϴ� �Լ�
int IsVertex(int vertex[], int a); //Ư�� vertex���� Ȯ���ϴ� �Լ�

void main(void) {
	printf("----Minimum Spanning Tree By <Prim algorithm>----\n\n");
	printf("�ּ� ���� Ʈ���� ����� ����\n\n");
	prim(2);
	for (int i = 0; i < VERTEX_SIZE - 1; i++)
		printf("(v%d , v%d) is selected\n", edge[i].v1 + 1, edge[i].v2 + 1);
}

//prim �˰������� �ּ� ���� Ʈ���� ���ϴ� �Լ�
void prim(int start) {
	int vertex[VERTEX_SIZE] = { 0, };
	int p, q, adjacent, index1 = 0, index2 = 0;

	vertex[index1++] = start; //v1�� ���������� �����Ͽ� ���� �˰��� ����
	while (index1 < VERTEX_SIZE) { //index1�� ���� ������ ���� ũ��� �������� ������ �ݺ�
		adjacent = INF;//������ ���� �� ���� ���� ����� ������ �� , �񱳸� ���� �ʱⰪ�� INF ������ ����

		for (int i = 0; i < index1; i++) {
			p = vertex[i]; //vertex�� 0���� �ʱ�ȭ��Ŵ

			for (int j = 0; j < VERTEX_SIZE; j++) {//��������� j�� v���� ���� ���� q�� ����
				q = W[j][p];

				if (q > 0 && q < INF && !IsVertex(vertex, j)) {
					//��������� q ���� 0 �̻��� ���ÿ� INF ������ �۰�, vertex j�� �ƴ� ���

					if (q < adjacent) { //q�� ������ ������ �߿��� ���� ���� ����� ������ adjacent���� ���� ��
						adjacent = q; //q ���� adjacent�� ����
						edge[index2].v1 = p; //v�� j ������ ���� ����
						edge[index2].v2 = j; //v�� j ������ ���� ����
					}
				}
			}
		}

		vertex[index1++] = edge[index2].v2; //������ ���� �ε����� ������ ���� �� �� �������� �̵���Ŵ
		index2++; //index +1�Ͽ� ���� ���� ��ȸ�ϵ��� ó��
	}
}

//�ش������� Ȯ���ϴ� �Լ�
int IsVertex(int vertex[], int tmp) {
	for (int i = 0; i < VERTEX_SIZE; i++) //0���� �迭�� ũ�⸸ŭ �˻�
		if (vertex[i] == tmp) //�ش� ������ ��� ���ϰ����� 1 ����
			return 1;

	return 0; //�ش� ������ �ƴ� ��� ���ϰ����� 0 ����
}