//algorithm 2020 (na) class hw8-1 20193017 Yoo Jimin

#include <stdio.h>
#pragma warning (disable : 4996)

#define INF 9999 //정점과 정점을 연결하는 간선이 존재하지 않을 경우 인접행렬에 저장되는 infinite 값
#define VERTEX_SIZE 7//정점의 개수

//adjacent matrix
int W[VERTEX_SIZE][VERTEX_SIZE] = {
	0, 4, INF, INF, INF, 10, INF,
	3, 0, INF, 18, INF, INF, INF,
	INF, 6, 0, INF, INF, INF, INF,
	INF, 5, 15, 0, 2, 19, 5,
	INF, INF, 12, 1, 0, INF, INF,
	INF, INF, INF, INF, INF, 0, 10,
	INF, INF, INF, 8, INF, INF, 0 };

//각 정점들 사이의 최단 거리
int D[VERTEX_SIZE][VERTEX_SIZE];

//정점 i에서 j까지 가는 최단경로의 중간에 놓여있는 정점이 최소한 하나는 있는 경우, 놓여있는 정점 중 가장 큰 인덱스
int P[VERTEX_SIZE][VERTEX_SIZE];

void simpleShortestPath(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]);
void path(int x, int y, int P[VERTEX_SIZE][VERTEX_SIZE]);

int main (void) {
	printf("------ all pairs shortest path ------\n");
	simpleShortestPath(VERTEX_SIZE, W, D, P);
	path(1, 7, P); //vertex 1부터 7까지 발생하는 모든 경우에 대해 최단경로를 알아내기 위한 path함수 호출
}

void simpleShortestPath(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]) { //모든 쌍 최단 경로 함수

	for (int i = 0; i < n; i++) {	//배열 초기화 작업
		for (int j = 0; j < n; j++) {
			D[i][j] = W[i][j];//행렬 D가 행렬 W와 같은 값을 가지도록 초기화
		}
	}

	for (int m = 1; m < n; m++) {//최대 m개의 간선을 사용하는 경우
		for (int i = 0; i < n; i++) {// i : 시작 정점
			for (int j = 0; j < n; j++) {// j : 마지막 정점
				if (D[i][j] > D[i][m] + D[m][j]) {
					D[i][j] = D[i][m] + D[m][j];
				}
			}
		}
	}

	printf("------ << 행렬 D >> ------\n");// 정점의 개수만큼 반복하여 모든 쌍 최단경로 출력
	for (int i = 0; i < VERTEX_SIZE; i++) {
		for (int j = 0; j < VERTEX_SIZE; j++) {
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void path(int x, int y, int P[VERTEX_SIZE][VERTEX_SIZE]) {
	//main함수에서 매개인자로 입력받은 경로, 배열 0부터 초기화했기에 인덱스 값 -1으로 탐색 
	if (P[x - 1][y - 1] != 0) { //경로 중간에 거치는 정점이 없을 때까지 재귀적으로 호출함
		path(x, P[x - 1][y - 1], P);
		//printf("지나가는 정점 : %d\n", P[x - 1][y - 1]); //지나가는 정점 출력
		path(P[x - 1][y - 1], y, P); //중간 지점부터 도착 지점까지 재귀호출
	}
}
