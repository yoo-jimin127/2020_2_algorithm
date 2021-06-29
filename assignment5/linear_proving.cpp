//20193017 YooJimin algorithm (na) # HW 5 - 3 linear proving source code
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

//�������� �Լ� ������
int linear_proving(int key) {
	int idx, i=0;

	for (int i = 0; i < TABLE_SIZE; i++) {
		idx = (key+i) % 13; //Ű ���� �޾� h(x) = x mod 13�� �����Ͽ� ���̺� �ּҸ� ��� �۾�

		if (table_arr[idx] == NULL) return idx;//���̺�迭�� idx �ּ��� ���Ұ� ���� ��� �ش� �ε��� ����
	}
}

int main(void) {
	int input_arr[8] = { 10, 20, 30, 40, 33, 46, 50, 60 };
	int linear_idx;
	init(table_arr);//���̺� �迭�� ���Ҹ� �ʱ�ȭ������

	for (int i = 0; i < sizeof(input_arr) / sizeof(int); i++) {
		linear_idx = linear_proving(input_arr[i]);//input_arr�� ���Ҹ� ���ʷ� ���������Ͽ� ���̺� �ּҸ� ��ȯ����
		table_arr[linear_idx] = input_arr[i];//���̺� �迭�� ��ȯ���� �ε��� �ּҿ� input_arr[i]��° ���Ҹ� ������
	}

	printf("-------linear proving result------\n");

	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table_arr[i] != NULL) {//���̺� �迭�� i��° ���Ұ� NULL�� �ƴ� ��� �ش� ���̺� �ּҿ� ���Ұ��� �����
			printf("table : %d -> data : %d\n", i, table_arr[i]);
		}
		else printf("table : %d -> NULL\n", i);
	}

	return 0;
}