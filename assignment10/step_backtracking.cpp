#include<stdio.h>
#pragma warning (disable : 4996)

void sum_of_subset(int start, int weight, int sum); //�� �κ������� ���� ���ϴ� �Լ�
int promising(int start, int weight, int sum); //����� �������� �����ϴ� �Լ�

int sum_W = 52;//�κ������� ��
int W[7] = { 0,2,10,13,17,22,42 };//�� �κ������� ��
int include_node[7];//���� ��� ����


int main(void) {

	int weight = 0;//����� ���� �����ϴ� ����
	int sum = 0;//����� ���� �����ϴ� ����

	for (int i = 1; i <= 6; i++) {
		sum += W[i];//�ݺ��� �ȿ��� �� �κ������� ���� sum ���� ������
	}

	sum_of_subset(0, weight, sum);//Ž���� ������ 0��° ���� �ش� ����� ��, ���� ���ڷ� �Ѱ� sum_of_subset

}


void sum_of_subset(int start, int weight, int sum) {//�� �κ������� ���� ���ϴ� �Լ�

	printf("< LEVEL : %d > weight : %d / sum : %d\n", start, weight, sum);//��� step�� ���� ���ϴ� ���� ���

	if (promising(start, weight, sum)) { //�������� �����Ͽ�, �ش� ��尡 ������ ���
		if (weight == sum_W) { //weight�� ���� sum_W�� ���� ������ �������� Ȯ��
			printf("\n-----<< sum of subset solution >>-----\n");

			for (int i = 1; i <= 6; i++) { //������ �κ� ���� ������ �ܼ�â�� ���
				if (include_node[i] != 0) {
					printf("%d ", include_node[i]);//i��° ��尡 0�� �ƴ� ��� i��° �ε����� ����Ǿ� �ִ� include_node�� ���� ���
				}
			}
			printf("\n");
		}

		else {
			include_node[start + 1] = W[start + 1]; //W[start+1]�� �����Ͽ�
			sum_of_subset(start + 1, weight + W[start + 1], sum - W[start + 1]);//W[start+1]�� ���� ���� sum_of_subset�� ���ڷ� �ѱ�
			include_node[start + 1] = 0; //w[i+1]�������� �ʰ�
			sum_of_subset(start + 1, weight, sum - W[start + 1]);//W[start+1]�� ���� weight ���� ������ ���� ���·�  sum_of_subset�� ���ڷ� �ѱ�
		}
	}
}


int promising(int start, int weight, int sum) {//�ش� ����� �������� �˻��ϴ� �Լ�
	if ((weight + sum >= sum_W) && (weight == sum_W || weight + W[start + 1] <= sum_W))
		//weight�� sum�� ���� ���� sum_W���� ũ�ų� ����, 
		//weight�� sum_W�� ���ų� weight ���� W[start+1]�� ���� ���� 
		//sum_W���� �۰ų� ���� ������ ������ �� �ش� �б⹮ ����
		return 1;

	else
		return 0;
}