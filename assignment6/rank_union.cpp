//algorithm 2020 (na) class HW6 20193017 [240]Yoo Jimin

#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int rank[9];//�� �������� ��ũ ���� �����ϴ� �迭
char parent[9] = { 'a','b','c','d','e','f','g','h','i' };//parent �迭�� �� �ʱ�ȭ
int x_idx, y_idx;

//�Լ� �����
void make_set(char data);
char find_set(char x_data);
void union_set(char x_data, char y_data);

int main(void) {
	union_set('a', 'b');//(a) ������ ù��° Ʈ�� b -> a

	union_set('d', 'e');//(b) ������ ù��° Ʈ�� e -> d

	union_set('f', 'g');//(b) ������ �ι�° Ʈ�� f -> g
	union_set('f', 'h');//(b) ������ �ι�° Ʈ�� f -> h
	union_set('f', 'i');//(b) ������ �ι�° Ʈ�� f -> i

	printf("------beginning tree set state------\n");
	//�ƹ��� union ������ �������� ���� (a)���հ� (b)������ �ʱ� ���� ���
	printf("< (a) tree set >\n");
	for (int i = 0; i < 3; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	printf("< (b) tree set >\n");
	for (int i = 3; i < 9; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	printf("------Union each tree set state------\n");
	//(a)���հ� (b)���� ������ union������ ��ģ ���� ���
	union_set('a', 'c');//(a)������ �� Ʈ���� union
	printf("< (a) tree set >\n");
	for (int i = 0; i < 3; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	union_set('d', 'f');//(b)������ �� Ʈ���� union
	printf("< (b) tree set >\n");
	for (int i = 3; i < 9; i++) {
		printf("%c ", parent[i]);
	}
	printf("\n");

	printf("------final result <Union by Rank>------\n");
	//(a)���հ� (b) ������ union �� ���� ���
	union_set('a', 'd');//(a)���հ� (b)������ union
	for (int i = 0; i < 9; i++) {
		printf("%c ", parent[i]);
	}

	return 0;
}


//��� data�� ������ ���ҷ� �ϴ� ������ ����� make_set �Լ�
void make_set(char data) {
	parent[data - 97] = data;
	rank[data - 97] = 0;//������ �����̱⿡ �Է¹��� data�� rank�� 0���� ����
}

//��� x_data�� ���� ������ �˾Ƴ� �� ��� x_data�� ���Ե� Ʈ���� ��Ʈ�� �����ϴ� find_set �Լ�
char find_set(char x_data) {
	if (parent[x_data - 97] != x_data) return find_set(parent[x_data - 97]);  //parent�� ���Ұ��� ���Ͽ� ���� ���� ��� find_set�� ���ȣ��	
	else return parent[x_data-97];
}

//��� x_data�� ���� ���հ� y_data�� ���� ������ ��ġ�� union_set �Լ�
void union_set(char x_data, char y_data) {
	x_idx = find_set(x_data);//x_data�� ���� ������ find_set���� ã�� x_data�� ���Ե� Ʈ���� ��Ʈ��带 ���Ϲ���
	y_idx = find_set(y_data);//y_data�� ���� ������ find_set���� ã�� y_data�� ���Ե� Ʈ���� ��Ʈ��带 ���Ϲ���
	
	if (rank[x_idx] > rank[y_idx]) parent[y_idx] = x_data;//x ������ rank�� ������ parent y�� x ������ ��ħ

	else if (rank[x_idx] < rank[y_idx]) parent[x_idx] = y_data;//y ������ rank�� ������ parent x�� y ������ ��ħ
	
	else if (rank[x_idx] == rank[y_idx]) {
		rank[x_idx]++;//x ���հ� y ������ rank�� ������ �� �� rank�� ��� rank+1
	}
}