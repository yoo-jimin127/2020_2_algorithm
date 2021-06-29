//algorithm 2020 (na) class HW 11-(1) [240] 20193017 Yoo Jimin

#include<stdio.h>
#pragma warning (disable : 4996)

int W = 9; //���� ���� �� ����ġ ��
int profit[6] = {0, 20, 30, 35, 12, 3};
int weight[6] = {0, 2, 5, 7, 3, 1};
int maxprofit; //max profit
int include[6], bestset[6]; // include ���θ� ������ �迭�� bestset �迭 ����

int promising(int i, int prof, int weig, int maxprofit) { //����� �������� Ȯ���ϴ� �Լ�
	if (weig >= W) //�Է¹��� ����ġ�� ���� W�� ������ ū ��� 0�� ����
		return 0;

	else { // weig < W
		int totweight = weig; //totweight�� ���� �Է¹��� ����ġ weig�� ������ �ʱ�ȭ
		float bound = prof; //bound�� ���� �Է¹��� ���� prof�� ������ �ʱ�ȭ
		int j = i + 1;//i�� 0���� �����ϴµ�, profit�� weight �迭�� ���� 1��° �ε������� ��������Ƿ� i+1�� ���� j�� �Է�

		while (j <= 5 && totweight + weight[j] <= W) { //j�� �ε����� 1~5���� ���� ���� -> j <= 5
			totweight = totweight + weight[j]; //totweigh�� ���� weight �迭�� j��° �ε��� �� ����
			bound = bound + profit[j]; //bound�� ���� profit �迭�� j��° �ε��� �� ����
			j++; //���� �ε��� ��ȸ
		}

		int k = j;
		if (k <= 5) bound = bound + (W - totweight) * (profit[k] / weight[k]); // k���� ��ȸ�ϸ� bound �� ���
		return bound > maxprofit;
	}
}


//knapsack problem�� Ǯ������ ���°���Ʈ���� �����ϴ� �Լ�
void knapsack(int i, int prof, int weig) {

	if (weig <= W && prof > maxprofit) { //best so far
		maxprofit = prof;
		printf("maxprofit : %d\n", maxprofit);

		//item�� ���Կ��� ���
		for (int j = 0; j <= 6; j++) {
			bestset[j] = include[j]; //�ǻ��ڵ� �� bestset = include

			if (j != 0 && bestset[j] == 1) {
				printf("[%d]: \"YES\"\n", j); //j�� 0�� �ƴϰ�, bestset�� j��° �ε����� 1�� ��� YES�� �ܼ�â�� ���
			}

			else if (j != 0 && bestset[j] == 0) {
				printf("[%d]: \"NO\"\n", j); // j�� 0�� �ƴϰ�, bestset�� j��° �ε����� 0�� ��� NO�� �ܼ�â�� ���
			}

		}
		printf("\n");
	}

	if (promising(i, prof, weig, maxprofit)) {
		include[i + 1] = 1; //w[i+1]�� �����ϵ���
		knapsack(i + 1, prof + profit[i + 1], weig + weight[i + 1]); //i+1��° �ε����� ������ �˻�
		include[i + 1] = 0; //w[i+1]�������� �ʵ���
		knapsack(i + 1, prof, weig); //i+1��° �ε����� �������� �����Ƿ� �Է¹��� ���� �״�θ� knapsack�� �ѱ�
	}
}

int main(void) {
	knapsack(0, 0, 0); //i��° �ε����� ���� 0�� ����ġ 0�� ���ڷ� �Ѱ� ���°���Ʈ�� ���� ����
	printf("-----< max profit : %d>-----\n", maxprofit);

	return 0;
}