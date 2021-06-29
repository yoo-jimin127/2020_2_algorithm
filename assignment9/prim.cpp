//algorithm 2020 class (na) HW9 [240]Yoo Jimin_20193017
#include <stdio.h> 
#pragma warining (disable : 4996)

#define INF 999 //정점 간 간선이 존재하지 않을 경우 저장되는 infinity한 값
#define VERTEX_SIZE 8 //정점의 개수

typedef struct Edge {
	int v1;
	int v2;
};

Edge edge[VERTEX_SIZE - 1];

//그래프의 인접행렬 입력
int W[VERTEX_SIZE][VERTEX_SIZE] = {
	0, 11, 9, 8, INF, INF, INF, INF,
	11, 0, 3, INF, 8, 8, INF, INF,
	9, 3, 0, 15, INF, 12, 1, INF,
	8, INF, 15, 0, INF, INF, 10, INF,
	INF, 8, INF, INF, 0, 7, INF, 4,
	INF, 8, 12, INF, 7, 0, INF, 5,
	INF, INF, 1, 10, INF, INF, 0, 2,
	INF, INF, INF, INF, 4, 5, 2, 0
};

void prim(int start); //prim algorithm으로 Minimum Spanning Tree 구하는 함수
int IsVertex(int vertex[], int a); //특정 vertex인지 확인하는 함수

void main(void) {
	printf("----Minimum Spanning Tree By <Prim algorithm>----\n\n");
	printf("최소 신장 트리를 만드는 과정\n\n");
	prim(2);
	for (int i = 0; i < VERTEX_SIZE - 1; i++)
		printf("(v%d , v%d) is selected\n", edge[i].v1 + 1, edge[i].v2 + 1);
}

//prim 알고리즘으로 최소 신장 트리를 구하는 함수
void prim(int start) {
	int vertex[VERTEX_SIZE] = { 0, };
	int p, q, adjacent, index1 = 0, index2 = 0;

	vertex[index1++] = start; //v1을 시작점으로 설정하여 프림 알고리즘 수행
	while (index1 < VERTEX_SIZE) { //index1의 값이 정점의 개수 크기와 같아지기 전까지 반복
		adjacent = INF;//인접한 정점 중 가장 적은 비용을 가지는 값 , 비교를 위해 초기값을 INF 값으로 설정

		for (int i = 0; i < index1; i++) {
			p = vertex[i]; //vertex를 0으로 초기화시킴

			for (int j = 0; j < VERTEX_SIZE; j++) {//인접행렬의 j행 v열일 때의 값을 q로 설정
				q = W[j][p];

				if (q > 0 && q < INF && !IsVertex(vertex, j)) {
					//인접행렬의 q 값이 0 이상인 동시에 INF 값보다 작고, vertex j가 아닌 경우

					if (q < adjacent) { //q가 인접한 정점들 중에서 가장 적은 비용을 가지는 adjacent보다 작을 때
						adjacent = q; //q 값을 adjacent에 저장
						edge[index2].v1 = p; //v와 j 사이의 간선 생성
						edge[index2].v2 = j; //v와 j 사이의 간선 생성
					}
				}
			}
		}

		vertex[index1++] = edge[index2].v2; //정점의 다음 인덱스를 생성한 간선 중 한 정점으로 이동시킴
		index2++; //index +1하여 다음 정점 순회하도록 처리
	}
}

//해당정점을 확인하는 함수
int IsVertex(int vertex[], int tmp) {
	for (int i = 0; i < VERTEX_SIZE; i++) //0부터 배열의 크기만큼 검색
		if (vertex[i] == tmp) //해당 정점인 경우 리턴값으로 1 전달
			return 1;

	return 0; //해당 정점이 아닌 경우 리턴값으로 0 전달
}