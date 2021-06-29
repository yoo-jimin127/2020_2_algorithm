#include<stdio.h>
#include<time.h>
#include<stdlib.h>


int W[7] = { 0,2,10,13,17,22,42 };//�� �κ������� ��
int sum_W = 52;//�κ������� �� 

int estimate_sumofsubset(int n); //Monte Carlo �˰������� ����ð��� ȿ������ �����ϴ� �Լ�
int promising(int start, int weight, int sum); //����� �������� Ȯ���ϱ� ���� �Լ�

int main(void) {
	printf("����� �� ������ ����ġ�� ��-> %u", estimate_sumofsubset(6)); //�κ� ������ ������ 6�� ���ڷ� �ѱ�

	return 0;
}


int estimate_sumofsubset(int n) {//Monte Carlo �˰������� ����ð��� ȿ������ �����ϴ� �Լ�

	int select, cnt_m1, cnt_m2;
	int weight = 0; 
	int total = 106; 
	int sumW = 52; 
	int totalNodes = 0;
	int numAns = 0; //ã�� �ַ���� ����
	int ans_node = 0; //ã�� �ַ���� ��� ���� ����ġ ��

	int m = 1; //�Ѹ��� ������ �ڽ� 2��
	int t = 2; //����� child node
	int i = 0;
	int mprod = 1;
	int numnodes = 1;
	int answerNum = 0;

	srand(time(NULL));

	while (numAns != 2) { //��� �� 2������ ã�������� �ݺ�

		while (m != 0 && i != (n + 1)) { //������ �ڽ��� ������ 0���� �ƴҶ����� �ݺ�
			mprod = mprod * m;
			numnodes = numnodes + mprod * t;
			m = 0;
			if (promising(i, weight, total)) {
				if (weight == sumW) { //answer�� ���
					answerNum = 1;
				}

				else { //solution�� �ƴ� ���
					cnt_m1 = promising(i + 1, weight + W[i + 1], total - W[i + 1]); //����� �ڽ� ������ �˻�
					cnt_m2 = promising(i + 1, weight, total - W[i + 1]); //����� �ڽ� ������ �˻�
					m = cnt_m1 + cnt_m2; // m = v�� ������ �ڽ��� ��

					if (m == 2) { //������ �ڽĳ�� �� �������� ������
						i++;
						select = ((rand() % 2) ? W[0] : W[i]); //0�� w[i]�߿� �����ϰ� ������
						weight += select;
						total -= W[i];
					}

					else if (m == 1) { //������ �ڽĳ�� 1���� ��� ������ ��� ����
						i++;

						if (cnt_m1 == 1) {
							weight += W[i];
							total -= W[i];
						}

						else {
							total -= W[i];
						}
					}
				}
			}
		}
		printf("number of nodes : %u / weight : %d\n", numnodes, weight);
		totalNodes += numnodes; //numnodes�� ��

		if (answerNum == 1 && numnodes != ans_node) { //W=52�̸� ������ �߰��� ���հ� �ٸ� ������ ���
			numAns++; //ã�� ���� ������ ������Ŵ
			answerNum = 0;
			ans_node += numnodes; //���Ӱ� �߰��� ������ ������
		}

		
		i = 0;
		mprod = 1;
		numnodes = 1;
		m = 1;
		weight = 0;
		total = 106;//�ʱ�ȭ �۾�
	}

	return totalNodes; //numnodes�� ���� ������ ���� totalNodes�� ����(����� �� ���� ����ġ���� ��)
}

int promising(int start, int weight, int sum) {// ����� �������� Ȯ���ϱ� ���� �Լ�
	if ((weight + sum >= sum_W) && (weight == sum_W || weight + W[start + 1] <= sum_W))
		return 1; //�ش� ��尡 ������ ��� 1�� ��ȯ

	else
		return 0; //�ش� ��尡 �������� ���� ��� 0�� ��ȯ
}