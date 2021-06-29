//algorithm 2020 (na) class hw8-1 20193017 Yoo Jimin

#include <stdio.h>
#pragma warning (disable : 4996)

#define INF 9999 //������ ������ �����ϴ� ������ �������� ���� ��� ������Ŀ� ����Ǵ� infinite ��
#define VERTEX_SIZE 7//������ ����

//adjacent matrix
int W[VERTEX_SIZE][VERTEX_SIZE] = {
	0, 4, INF, INF, INF, 10, INF,
	3, 0, INF, 18, INF, INF, INF,
	INF, 6, 0, INF, INF, INF, INF,
	INF, 5, 15, 0, 2, 19, 5,
	INF, INF, 12, 1, 0, INF, INF,
	INF, INF, INF, INF, INF, 0, 10,
	INF, INF, INF, 8, INF, INF, 0 };

//�� ������ ������ �ִ� �Ÿ�
int D[VERTEX_SIZE][VERTEX_SIZE];

//���� i���� j���� ���� �ִܰ���� �߰��� �����ִ� ������ �ּ��� �ϳ��� �ִ� ���, �����ִ� ���� �� ���� ū �ε���
int P[VERTEX_SIZE][VERTEX_SIZE];

void simpleShortestPath(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]);
void path(int x, int y, int P[VERTEX_SIZE][VERTEX_SIZE]);

int main (void) {
	printf("------ all pairs shortest path ------\n");
	simpleShortestPath(VERTEX_SIZE, W, D, P);
	path(1, 7, P); //vertex 1���� 7���� �߻��ϴ� ��� ��쿡 ���� �ִܰ�θ� �˾Ƴ��� ���� path�Լ� ȣ��
}

void simpleShortestPath(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]) { //��� �� �ִ� ��� �Լ�

	for (int i = 0; i < n; i++) {	//�迭 �ʱ�ȭ �۾�
		for (int j = 0; j < n; j++) {
			D[i][j] = W[i][j];//��� D�� ��� W�� ���� ���� �������� �ʱ�ȭ
		}
	}

	for (int m = 1; m < n; m++) {//�ִ� m���� ������ ����ϴ� ���
		for (int i = 0; i < n; i++) {// i : ���� ����
			for (int j = 0; j < n; j++) {// j : ������ ����
				if (D[i][j] > D[i][m] + D[m][j]) {
					D[i][j] = D[i][m] + D[m][j];
				}
			}
		}
	}

	printf("------ << ��� D >> ------\n");// ������ ������ŭ �ݺ��Ͽ� ��� �� �ִܰ�� ���
	for (int i = 0; i < VERTEX_SIZE; i++) {
		for (int j = 0; j < VERTEX_SIZE; j++) {
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void path(int x, int y, int P[VERTEX_SIZE][VERTEX_SIZE]) {
	//main�Լ����� �Ű����ڷ� �Է¹��� ���, �迭 0���� �ʱ�ȭ�߱⿡ �ε��� �� -1���� Ž�� 
	if (P[x - 1][y - 1] != 0) { //��� �߰��� ��ġ�� ������ ���� ������ ��������� ȣ����
		path(x, P[x - 1][y - 1], P);
		//printf("�������� ���� : %d\n", P[x - 1][y - 1]); //�������� ���� ���
		path(P[x - 1][y - 1], y, P); //�߰� �������� ���� �������� ���ȣ��
	}
}
