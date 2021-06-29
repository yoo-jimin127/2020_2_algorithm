//algorithm 2020 (na) class HW 11-(1) [240] 20193017 Yoo Jimin

#include<stdio.h>
#pragma warning (disable : 4996)

int W = 9; //과제 명세서 상 가중치 값
int profit[6] = {0, 20, 30, 35, 12, 3};
int weight[6] = {0, 2, 5, 7, 3, 1};
int maxprofit; //max profit
int include[6], bestset[6]; // include 여부를 저장할 배열과 bestset 배열 저장

int promising(int i, int prof, int weig, int maxprofit) { //노드의 유망성을 확인하는 함수
	if (weig >= W) //입력받은 가중치의 값이 W의 값보다 큰 경우 0을 리턴
		return 0;

	else { // weig < W
		int totweight = weig; //totweight의 값을 입력받은 가중치 weig의 값으로 초기화
		float bound = prof; //bound의 값을 입력받은 이익 prof의 값으로 초기화
		int j = i + 1;//i가 0부터 시작하는데, profit과 weight 배열의 값이 1번째 인덱스부터 들어있으므로 i+1의 값을 j에 입력

		while (j <= 5 && totweight + weight[j] <= W) { //j의 인덱스는 1~5까지 접근 가능 -> j <= 5
			totweight = totweight + weight[j]; //totweigh의 값에 weight 배열의 j번째 인덱스 값 삽입
			bound = bound + profit[j]; //bound의 값에 profit 배열의 j번째 인덱스 값 삽입
			j++; //다음 인덱스 순회
		}

		int k = j;
		if (k <= 5) bound = bound + (W - totweight) * (profit[k] / weight[k]); // k값을 순회하며 bound 값 계산
		return bound > maxprofit;
	}
}


//knapsack problem을 풀기위해 상태공간트리를 구축하는 함수
void knapsack(int i, int prof, int weig) {

	if (weig <= W && prof > maxprofit) { //best so far
		maxprofit = prof;
		printf("maxprofit : %d\n", maxprofit);

		//item의 포함여부 출력
		for (int j = 0; j <= 6; j++) {
			bestset[j] = include[j]; //의사코드 상 bestset = include

			if (j != 0 && bestset[j] == 1) {
				printf("[%d]: \"YES\"\n", j); //j가 0이 아니고, bestset의 j번째 인덱스가 1인 경우 YES를 콘솔창에 출력
			}

			else if (j != 0 && bestset[j] == 0) {
				printf("[%d]: \"NO\"\n", j); // j가 0이 아니고, bestset의 j번째 인덱스가 0인 경우 NO를 콘솔창에 출력
			}

		}
		printf("\n");
	}

	if (promising(i, prof, weig, maxprofit)) {
		include[i + 1] = 1; //w[i+1]을 포함하도록
		knapsack(i + 1, prof + profit[i + 1], weig + weight[i + 1]); //i+1번째 인덱스의 유망성 검사
		include[i + 1] = 0; //w[i+1]포함하지 않도록
		knapsack(i + 1, prof, weig); //i+1번째 인덱스를 포함하지 않으므로 입력받은 인자 그대로를 knapsack에 넘김
	}
}

int main(void) {
	knapsack(0, 0, 0); //i번째 인덱스에 이익 0과 가중치 0을 인자로 넘겨 상태공간트리 구축 시작
	printf("-----< max profit : %d>-----\n", maxprofit);

	return 0;
}