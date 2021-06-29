//20193017 YooJimin algorithm (na) # HW 5 - 5 chaining source code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable : 4996)
#define TABLE_SIZE 13
#define h(x) (x % TABLE_SIZE)//�ؽ� �Լ�: h(x) = x mod 13 (TABLE_SIZE == 13)

//����ü �����
typedef struct Chain {
	struct Chain* next; //ü���� ���� ��带 ����Ű�� ������
	int value;//��忡 ����Ǵ� ������ ��
}Chain;

//�Լ� ���Ǻ�(insertChain, connectChain function)
Chain* insertChain(Chain* table, int input, int input_size);
Chain* connectChain(Chain* table, int table_idx, int value);

//������ ���� �Լ�
Chain* insertChain(Chain* table, int input, int input_size) {
	int data;

	table = connectChain(table, input % 13, input_size);//�ؽ����̺� �Է� ���� ���� �۾��� �ϴ� �Լ� ȣ��
	return table;
}

//ü�̴��� �̿��� �� ���Ҹ� �߰��ϸ� ��带 �����س����� �Լ�
Chain* connectChain(Chain* table, int table_idx, int value) {
	Chain* newChain;
	Chain* currChain;

	newChain = (Chain*)malloc(sizeof(Chain));//���ο� ����� �޸� �����Ҵ�
	newChain->value = value;//�� ����� value���� �Է¹��� ���ҷ� ä���
	newChain->next = NULL;//�� ����� next�� NULL�� �ʱ�ȭ

	if (table[table_idx].next == NULL) {//���ڷ� ���� �ε��� �ּ��� next ��尡 NULL�̶�� �ε����� next�� �� ��� �߰� 
		table[table_idx].next = newChain;

		return table;
	}

	currChain = table[table_idx].next;//���� ��带 ���ڷ� ���� �ε��� �ּ��� next�� ����Ű���� ����

	while (currChain->next != NULL) {//���� ����� next�� NULL�� �ƴ� ������ curr = curr+1 �۾� �ݺ�
		currChain = currChain->next;
	}

	currChain->next = newChain;//currü���� next�� NULL�̾ �ݺ����� Ż���ϸ� currü���� next�� �� ��带 �����Ѵ�.

	return table;
}

int main(void) {
	Chain* table, *curr;
	int hashTable, value;
	int choice, search;

	int input_arr[8] = { 10, 20, 30, 40, 33, 46, 50, 60 };

	//���̺��� �޸� �����Ҵ�
	table = (Chain*)malloc(TABLE_SIZE * sizeof(Chain));

	//���̺��� ��� �ʱ�ȭ
	for (int i = 0; i < TABLE_SIZE; i++) {
		table[i].next = NULL;
	}

	for (int i = 0; i < sizeof(input_arr) / sizeof(int); i++) {
		insertChain(table, input_arr[i], input_arr[i]);//������ ���� �Լ��� input_arr�� ���Ҹ� �ϳ��� �߰��ϴ� �۾�
	}

	printf("------chaining result------\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (table[i].next == NULL) {
			printf("table %d : NULL\n", i);
			continue;
		}

		curr = table[i].next;//curr�����ͷ� �ؽ����̺��� i��° �ּ��� next�� ����Ŵ

		printf("table %d data ", i);

		while (curr != NULL) {
			printf("-> %d ", curr->value);//curr��尡 NULL�� �ƴ� ��� �ش� �ؽ����̺��� value�� �����
			curr = curr->next;//�����͸� ����� �� curr=curr+1�� �ݺ��Ͽ� ��� ���̺� �ּҸ� ��ȸ��
		}
		printf("\n");
	}

	return 0;
}