//algorithm 2020 (na) class hw7 traveling salesperson problem
#include <stdio.h>
#pragma warning (disable : 4996)

int adj_matrix[10][10]; // 그래프에 대한 인접행렬
int visited[10]; // 방문한 정점을 체크하는 배열
int vertex; // 정점(vertex)의 개수를 저장할 변수
int min = 9999999999; //정점 순회의 최소 비용을 저장할 변수

void input_vertex();
void DFS(int start, int tmp, int sum, int cnt);
void TSP();
int travel_vertex(int vert);
void printPath(int vert);
void printWeightSum();

int main(void) {
	input_vertex(); //행렬 입력

	TSP(); //최단경로 가중치 합 계산

	printWeightSum();//최단경로와 최소비용 출력

	return 0;
}

// TSP에서 각각의 vertex와 가중치를 입력하는 input함수
void input_vertex() {

	printf("정점의 개수 입력 : ");
	scanf("%d", &vertex); // 방문할 vertex의 개수 입력

	printf("\n");

	printf("인접행렬(가중치 포함 방향 그래프) 입력: \n");

	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			scanf("%d", &adj_matrix[i][j]);
			//정점의 개수만큼 반복되어 그래프에 대한 초기상태의 인접행렬을 입력받음
		}
	}
}

//정점의 개수만큼 DFS를 호출해 최단경로를 찾아내는 함수
void TSP() {
	for (int i = 0; i < vertex; i++) { //i번째 정점에서 시작하는 경우 해당 정점을 기준으로 탐색 시작
		DFS(i, i, 0, 0);//DFS 호출
	}
}

// 깊이우선탐색을 사용해 정점을 탐색하는 함수
void DFS(int start, int tmp, int sum, int cnt) {

	// v1부터 시작하여 모든 정점의 탐색을 마친 뒤 다시 v1으로 돌아온 경우
	if (cnt == vertex && start == tmp) {
		if (min > sum) // min(최단경로)보다 sum의 비용이 더 작을 때 sum에 min 값을 할당
			min = sum;
		return;
	}

	for (int j = 0; j < vertex; j++) {

		// 해당 정점에 visited함수 값이 0이며 동시에 인접행렬의 가중치가 있을 때
		if (!visited[tmp] && adj_matrix[tmp][j] > 0) {
			visited[tmp] = true; //visited함수에 '방문함' 표시
			sum = sum + adj_matrix[tmp][j]; // 인접행렬의 비용을 최단경로를 저장하는 변수 sum에 더함

			if (sum <= min) { // sum <= min 일 경우 깊이우선탐색
				DFS(start, j, sum, cnt + 1); // 재귀호출을 통해 DFS 호출
			}

			visited[tmp] = false; // 재귀로 인해 방문 표시를 다시 초기화
			sum = sum - adj_matrix[tmp][j]; // sum 초기화
		}

		//인접행렬이 0인 경우(해당 정점과 연결되어 있지 않을 때 or 시작점과 끝점이 같을 때
		if (adj_matrix[tmp][j] == 0) {
			continue;
		}
	}
}

// 탐색 중 min일 때 정점 저장하는 함수
int travel_vertex(int vert) {
	int count, min_vertex = 999, tmp = 0;
	int minimum = 999;

	for (count = 0; count < vertex; count++) { //해당 정점에서 시작
		if ((adj_matrix[vert][count] != 0) && (visited[count] == 0)) { //인접행렬에 가중치가 있는 동시에 방문하지 않은 정점

			if (adj_matrix[vert][count] < minimum) { // 인접행렬의 가중치가 최소값보다 작은 경우
				minimum = adj_matrix[count][0] + adj_matrix[vert][count]; // minimum에 해당 인접행렬 가중치 값 할당
			}

			tmp = adj_matrix[vert][count];//인접행렬의 가중치 값을 임의의 변수 tmp에 저장
			min_vertex = count;
		}
	}

	if (minimum != 999) { //최소비용 비교를 위해 min값에 tmp를 더함
		min = min + tmp;
	}

	return min_vertex; //최소비용을 가지는 정점을 반환함
}


// 경로 출력하는 함수
void printPath(int vert) {
	int minimum_vertex; //최소 비용에서의 정점
	visited[vert] = 1; //방문 기록을 표시함

	printf("%d -> ", vert + 1);//정점 출력
	//printf("mininum cost : %d\n", min);

	minimum_vertex = travel_vertex(vert); // 탐색 중 반환한 정점을  minimum vertex에 할당

	if (minimum_vertex == 999) {//시작점으로 돌아온 경우

		minimum_vertex = 0;//최소비용에서의 정점 값을 0으로 초기화
		printf(" %d", minimum_vertex + 1);
		min = min + adj_matrix[vert][minimum_vertex];
		return;
	}

	printPath(minimum_vertex); // 재귀호출을 통해 최소비용을 가지는 모든 정점 순회
}

void printWeightSum() {//가중치 합의 최소 값을 구하는 함수
	printf("가중치 합의 최소 값 : %d", min); //최소비용 출력

	printf("\n");

	//최소비용일 때의 경로 출력
	printf("최적 일주 경로 : ");
	printPath(0);
	printf("\n");
}