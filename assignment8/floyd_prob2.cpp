//algorithm 2020 (na) class hw8-2 20193017 Yoo Jimin

#include <stdio.h>
#pragma warning (disable : 4996)

#define INF 9999 //정점과 정점을 연결하는 간선이 존재하지 않을 경우 인접행렬에 저장되는 infinite 값
#define VERTICE_SIZE 7//정점의 개수

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

void floyd(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]);
void path(int q, int r, int P[VERTEX_SIZE][VERTEX_SIZE]);

int main() {
	int x, y;

	floyd(VERTEX_SIZE, W, D, P);

	printf("출발 정점과 도착 정점 입력 : ");
	scanf_s("%d %d", &x, &y);

	printf("\n");

	printf("최단 거리: %d\n\n", D[x][y]);

	path(x, y, P); //x 정점부터 y정점까지의 최단경로를 알아내기 위한 path함수 호출
}

void floyd(int n, int W[VERTEX_SIZE][VERTEX_SIZE], int D[VERTEX_SIZE][VERTEX_SIZE], int P[VERTEX_SIZE][VERTEX_SIZE]) { //플로이드 함수

	for (int i = 0; i < n; i++) {	//배열 초기화 작업
		for (int j = 0; j < n; j++) {
			P[i][j] = 0;//행렬 P는 전체를 0으로
			D[i][j] = W[i][j];//행렬 D는 행렬 W와 같은 값을 가지도록 초기화
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) { //정점을 거쳐서 가는 것이 더 빠른 경우
					D[i][j] = D[i][k] + D[k][j]; // 거쳐가는 배열의 가중치 값을 D 배열에 저장함
					P[i][j] = k + 1; // path를 가리키는 변수 k를 P배열의 [i][j] 인덱스에 넣어줌
				}
			}
		}
	}

	printf("------ << 행렬 D >> ------\n");
	for (int i = 0; i < VERTEX_SIZE; i++) {
		for (int j = 0; j < VERTEX_SIZE; j++) {
			printf("%d ", D[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("------ << 행렬 P >> ------\n");
	for (int i = 0; i < VERTEX_SIZE; i++) {
		for (int j = 0; j < VERTEX_SIZE; j++) {
			printf("%d ", P[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

void path(int x, int y, int P[VERTEX_SIZE][VERTEX_SIZE]) {
	//main함수에서 매개인자로 입력받은 경로, 배열 0부터 초기화했기에 인덱스 값 -1으로 탐색 
	if (P[x - 1][y - 1] != 0) { //경로 중간에 거치는 정점이 없을 때까지 재귀적으로 호출함
		path(x, P[x - 1][y - 1], P);
		printf("지나가는 정점 : %d\n", P[x - 1][y - 1]); //지나가는 정점 출력
		path(P[x - 1][y - 1], y, P); //중간 지점부터 도착 지점까지 재귀호출
	}
}

