//algorithm 2020 (na) class hw7 traveling salesperson problem
#include <stdio.h>
#pragma warning (disable : 4996)

int adj_matrix[10][10]; // �׷����� ���� �������
int visited[10]; // �湮�� ������ üũ�ϴ� �迭
int vertex; // ����(vertex)�� ������ ������ ����
int min = 9999999999; //���� ��ȸ�� �ּ� ����� ������ ����

void input_vertex();
void DFS(int start, int tmp, int sum, int cnt);
void TSP();
int travel_vertex(int vert);
void printPath(int vert);
void printWeightSum();

int main(void) {
	input_vertex(); //��� �Է�

	TSP(); //�ִܰ�� ����ġ �� ���

	printWeightSum();//�ִܰ�ο� �ּҺ�� ���

	return 0;
}

// TSP���� ������ vertex�� ����ġ�� �Է��ϴ� input�Լ�
void input_vertex() {

	printf("������ ���� �Է� : ");
	scanf("%d", &vertex); // �湮�� vertex�� ���� �Է�

	printf("\n");

	printf("�������(����ġ ���� ���� �׷���) �Է�: \n");

	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			scanf("%d", &adj_matrix[i][j]);
			//������ ������ŭ �ݺ��Ǿ� �׷����� ���� �ʱ������ ��������� �Է¹���
		}
	}
}

//������ ������ŭ DFS�� ȣ���� �ִܰ�θ� ã�Ƴ��� �Լ�
void TSP() {
	for (int i = 0; i < vertex; i++) { //i��° �������� �����ϴ� ��� �ش� ������ �������� Ž�� ����
		DFS(i, i, 0, 0);//DFS ȣ��
	}
}

// ���̿켱Ž���� ����� ������ Ž���ϴ� �Լ�
void DFS(int start, int tmp, int sum, int cnt) {

	// v1���� �����Ͽ� ��� ������ Ž���� ��ģ �� �ٽ� v1���� ���ƿ� ���
	if (cnt == vertex && start == tmp) {
		if (min > sum) // min(�ִܰ��)���� sum�� ����� �� ���� �� sum�� min ���� �Ҵ�
			min = sum;
		return;
	}

	for (int j = 0; j < vertex; j++) {

		// �ش� ������ visited�Լ� ���� 0�̸� ���ÿ� ��������� ����ġ�� ���� ��
		if (!visited[tmp] && adj_matrix[tmp][j] > 0) {
			visited[tmp] = true; //visited�Լ��� '�湮��' ǥ��
			sum = sum + adj_matrix[tmp][j]; // ��������� ����� �ִܰ�θ� �����ϴ� ���� sum�� ����

			if (sum <= min) { // sum <= min �� ��� ���̿켱Ž��
				DFS(start, j, sum, cnt + 1); // ���ȣ���� ���� DFS ȣ��
			}

			visited[tmp] = false; // ��ͷ� ���� �湮 ǥ�ø� �ٽ� �ʱ�ȭ
			sum = sum - adj_matrix[tmp][j]; // sum �ʱ�ȭ
		}

		//��������� 0�� ���(�ش� ������ ����Ǿ� ���� ���� �� or �������� ������ ���� ��
		if (adj_matrix[tmp][j] == 0) {
			continue;
		}
	}
}

// Ž�� �� min�� �� ���� �����ϴ� �Լ�
int travel_vertex(int vert) {
	int count, min_vertex = 999, tmp = 0;
	int minimum = 999;

	for (count = 0; count < vertex; count++) { //�ش� �������� ����
		if ((adj_matrix[vert][count] != 0) && (visited[count] == 0)) { //������Ŀ� ����ġ�� �ִ� ���ÿ� �湮���� ���� ����

			if (adj_matrix[vert][count] < minimum) { // ��������� ����ġ�� �ּҰ����� ���� ���
				minimum = adj_matrix[count][0] + adj_matrix[vert][count]; // minimum�� �ش� ������� ����ġ �� �Ҵ�
			}

			tmp = adj_matrix[vert][count];//��������� ����ġ ���� ������ ���� tmp�� ����
			min_vertex = count;
		}
	}

	if (minimum != 999) { //�ּҺ�� �񱳸� ���� min���� tmp�� ����
		min = min + tmp;
	}

	return min_vertex; //�ּҺ���� ������ ������ ��ȯ��
}


// ��� ����ϴ� �Լ�
void printPath(int vert) {
	int minimum_vertex; //�ּ� ��뿡���� ����
	visited[vert] = 1; //�湮 ����� ǥ����

	printf("%d -> ", vert + 1);//���� ���
	//printf("mininum cost : %d\n", min);

	minimum_vertex = travel_vertex(vert); // Ž�� �� ��ȯ�� ������  minimum vertex�� �Ҵ�

	if (minimum_vertex == 999) {//���������� ���ƿ� ���

		minimum_vertex = 0;//�ּҺ�뿡���� ���� ���� 0���� �ʱ�ȭ
		printf(" %d", minimum_vertex + 1);
		min = min + adj_matrix[vert][minimum_vertex];
		return;
	}

	printPath(minimum_vertex); // ���ȣ���� ���� �ּҺ���� ������ ��� ���� ��ȸ
}

void printWeightSum() {//����ġ ���� �ּ� ���� ���ϴ� �Լ�
	printf("����ġ ���� �ּ� �� : %d", min); //�ּҺ�� ���

	printf("\n");

	//�ּҺ���� ���� ��� ���
	printf("���� ���� ��� : ");
	printPath(0);
	printf("\n");
}