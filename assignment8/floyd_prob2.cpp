//algorithm 2020 (na) class hw8-2 20193017 Yoo Jimin

#include <stdio.h>
#pragma warning (disable : 4996)

#define INF 9999 //������ ������ �����ϴ� ������ �������� ���� ��� ������Ŀ� ����Ǵ� infinite ��
#define VERTICE_SIZE 7//������ ����

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

void floyd(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]);
void path(int q, int r, int P[VERTEX_SIZE][VERTEX_SIZE]);

int main() {
	int x, y;

	floyd(VERTEX_SIZE, W, D, P);

	printf("��� ������ ���� ���� �Է� : ");
	scanf_s("%d %d", &x, &y);

	printf("\n");

	printf("�ִ� �Ÿ�: %d\n\n", D[x][y]);

	path(x, y, P); //x �������� y���������� �ִܰ�θ� �˾Ƴ��� ���� path�Լ� ȣ��
}

void floyd(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]) { //�÷��̵� �Լ�

	for (int i = 0; i < n; i++) {	//�迭 �ʱ�ȭ �۾�
		for (int j = 0; j < n; j++) {
			P[i][j] = 0;//��� P�� ��ü�� 0����
			D[i][j] = W[i][j];//��� D�� ��� W�� ���� ���� �������� �ʱ�ȭ
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) { //������ ���ļ� ���� ���� �� ���� ���
					D[i][j] = D[i][k] + D[k][j]; // ���İ��� �迭�� ����ġ ���� D �迭�� ������
					P[i][j] = k + 1; // path�� ����Ű�� ���� k�� P�迭�� [i][j] �ε����� �־���
				}
			}
		}
	}

	printf("------ << ��� D >> ------\n");
	for (int i = 0; i < VERTEX_SIZE; i++) {
		for (int j = 0; j < VERTEX_SIZE; j++) {
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("------ << ��� P >> ------\n");
	for (int i = 0; i < VERTEX_SIZE; i++) {
		for (int j = 0; j < VERTEX_SIZE; j++) {
			printf("%d ", P[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void path(int x, int y, int P[VERTEX_SIZE][VERTEX_SIZE]) {
	//main�Լ����� �Ű����ڷ� �Է¹��� ���, �迭 0���� �ʱ�ȭ�߱⿡ �ε��� �� -1���� Ž�� 
	if (P[x - 1][y - 1] != 0) { //��� �߰��� ��ġ�� ������ ���� ������ ��������� ȣ����
		path(x, P[x - 1][y - 1], P);
		printf("�������� ���� : %d\n", P[x - 1][y - 1]); //�������� ���� ���
		path(P[x - 1][y - 1], y, P); //�߰� �������� ���� �������� ���ȣ��
	}
}

