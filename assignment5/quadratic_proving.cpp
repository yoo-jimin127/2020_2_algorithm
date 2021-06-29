//20193017 YooJimin algorithm (na) # HW 5 - 4 quadratic proving source code

#include <stdio.h>
#pragma warning (disable : 4996)
#define TABLE_SIZE 13 //0~12�� 13 ũ���� ���̺� ��

int table_arr[TABLE_SIZE]; //13ũ�⸸ŭ�� ���̺� �迭

//���̺��� ��� ���Ҹ� NULL�� �ʱ�ȭ ��Ű�� init �Լ�
void init(int table_arr[]) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		table_arr[i] = NULL;
	}
}

//���������� �Լ� ������
int quadratic_proving(int key) {
	int idx;

	for (int i = 0; i < TABLE_SIZE; i++) {
		idx = (key + (i*i)) % 13; //Ű ���� �޾� hi(x) = (x+(i*i)) mod 13�� �����Ͽ� ���̺� �ּҸ� ��� �۾�
		//�浹�� �Ͼ�� Ƚ���� ���� i���� 0���� ���̺��� ũ�⸸ŭ �����Ͽ� �ؽ��Լ��� �����

		if (table_arr[idx] == NULL) return idx; //�ؽ��Լ��� ������ ���̺� �ּ�(�ε���)�� �迭 �󿡼� NULL�� ��, �ش� �ε��� ���� 
	}
}

int main(void) {
	int input_arr[8] = { 10, 20, 30, 40, 33, 46, 50, 60 };
	int quadratic_idx;
	init(table_arr);//���̺� �迭 �ʱ�ȭ

	for (int i = 0; i < sizeof(input_arr) / sizeof(int); i++) {
		quadratic_idx = quadratic_proving(input_arr[i]);//input_arr�� ���Ҹ� ���ʷ� �����������Ͽ� ���̺� �ּҸ� ��ȯ����
		table_arr[quadratic_idx] = input_arr[i];//���̺� �迭�� ��ȯ���� �ε��� �ּҿ� input_arr[i]��° ���Ҹ� ������
	}

	printf("------quadratic proving result------\n");

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table_arr[i] != NULL) {//���̺� �迭�� i��° ���Ұ� NULL�� �ƴ� ��� �ش� ���̺� �ּҿ� ���Ұ��� �����
			printf("table : %d -> data : %d\n", i, table_arr[i]);
		}

		else {
			printf("table : %d -> NULL\n", i);
		}
	}

	return 0;
}