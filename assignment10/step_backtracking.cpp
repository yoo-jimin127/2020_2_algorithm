#include<stdio.h>
#pragma warning (disable : 4996)

void sum_of_subset(int start, int weight, int sum); //각 부분집합의 합을 구하는 함수
int promising(int start, int weight, int sum); //노드의 유망성을 조사하는 함수

int sum_W = 52;//부분집합의 합
int W[7] = { 0,2,10,13,17,22,42 };//각 부분집합의 값
int include_node[7];//포함 노드 개수


int main(void) {

	int weight = 0;//노드의 값을 저장하는 변수
	int sum = 0;//노드의 합을 저장하는 변수

	for (int i = 1; i <= 6; i++) {
		sum += W[i];//반복문 안에서 각 부분집합의 값을 sum 값에 저장함
	}

	sum_of_subset(0, weight, sum);//탐색을 시작할 0번째 노드와 해당 노드의 값, 합을 인자로 넘겨 sum_of_subset

}


void sum_of_subset(int start, int weight, int sum) {//각 부분집합의 합을 구하는 함수

	printf("< LEVEL : %d > weight : %d / sum : %d\n", start, weight, sum);//모든 step의 합을 구하는 과정 출력

	if (promising(start, weight, sum)) { //유망성을 조사하여, 해당 노드가 유망한 경우
		if (weight == sum_W) { //weight의 값과 sum_W의 값이 같으면 정답임을 확인
			printf("\n-----<< sum of subset solution >>-----\n");

			for (int i = 1; i <= 6; i++) { //정답의 부분 집합 조합을 콘솔창에 출력
				if (include_node[i] != 0) {
					printf("%d ", include_node[i]);//i번째 노드가 0이 아닌 경우 i번째 인덱스에 저장되어 있는 include_node의 값을 출력
				}
			}
			printf("\n");
		}

		else {
			include_node[start + 1] = W[start + 1]; //W[start+1]을 포함하여
			sum_of_subset(start + 1, weight + W[start + 1], sum - W[start + 1]);//W[start+1]의 값을 더해 sum_of_subset의 인자로 넘김
			include_node[start + 1] = 0; //w[i+1]포함하지 않고
			sum_of_subset(start + 1, weight, sum - W[start + 1]);//W[start+1]의 값을 weight 값에 더하지 않은 상태로  sum_of_subset의 인자로 넘김
		}
	}
}


int promising(int start, int weight, int sum) {//해당 노드의 유망성을 검사하는 함수
	if ((weight + sum >= sum_W) && (weight == sum_W || weight + W[start + 1] <= sum_W))
		//weight에 sum을 더한 값이 sum_W보다 크거나 같고, 
		//weight가 sum_W와 같거나 weight 값에 W[start+1]을 더한 값이 
		//sum_W보다 작거나 같은 조건을 성립할 때 해당 분기문 실행
		return 1;

	else
		return 0;
}