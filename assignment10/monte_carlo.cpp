#include<stdio.h>
#include<time.h>
#include<stdlib.h>


int W[7] = { 0,2,10,13,17,22,42 };//각 부분집합의 값
int sum_W = 52;//부분집합의 합 

int estimate_sumofsubset(int n); //Monte Carlo 알고리즘으로 수행시간의 효율성을 추정하는 함수
int promising(int start, int weight, int sum); //노드의 유망성을 확인하기 위한 함수

int main(void) {
	printf("노드의 총 개수의 추정치의 합-> %u", estimate_sumofsubset(6)); //부분 집합의 개수인 6을 인자로 넘김

	return 0;
}


int estimate_sumofsubset(int n) {//Monte Carlo 알고리즘으로 수행시간의 효율성을 추정하는 함수

	int select, cnt_m1, cnt_m2;
	int weight = 0; 
	int total = 106; 
	int sumW = 52; 
	int totalNodes = 0;
	int numAns = 0; //찾은 솔루션의 개수
	int ans_node = 0; //찾은 솔루션의 노드 개수 추정치 값

	int m = 1; //뿌리의 유망한 자식 2개
	int t = 2; //노드의 child node
	int i = 0;
	int mprod = 1;
	int numnodes = 1;
	int answerNum = 0;

	srand(time(NULL));

	while (numAns != 2) { //모든 해 2가지를 찾을때까지 반복

		while (m != 0 && i != (n + 1)) { //유망한 자식의 개수가 0개가 아닐때까지 반복
			mprod = mprod * m;
			numnodes = numnodes + mprod * t;
			m = 0;
			if (promising(i, weight, total)) {
				if (weight == sumW) { //answer인 경우
					answerNum = 1;
				}

				else { //solution이 아닌 경우
					cnt_m1 = promising(i + 1, weight + W[i + 1], total - W[i + 1]); //노드의 자식 유망성 검사
					cnt_m2 = promising(i + 1, weight, total - W[i + 1]); //노드의 자식 유망성 검사
					m = cnt_m1 + cnt_m2; // m = v의 유망한 자식의 수

					if (m == 2) { //유망한 자식노드 중 랜덤으로 선택함
						i++;
						select = ((rand() % 2) ? W[0] : W[i]); //0과 w[i]중에 랜덤하게 선택함
						weight += select;
						total -= W[i];
					}

					else if (m == 1) { //유망한 자식노드 1개인 경우 유망한 노드 선택
						i++;

						if (cnt_m1 == 1) {
							weight += W[i];
							total -= W[i];
						}

						else {
							total -= W[i];
						}
					}
				}
			}
		}
		printf("number of nodes : %u / weight : %d\n", numnodes, weight);
		totalNodes += numnodes; //numnodes의 합

		if (answerNum == 1 && numnodes != ans_node) { //W=52이며 이전에 발견한 조합과 다른 조합인 경우
			numAns++; //찾은 답의 개수를 증가시킴
			answerNum = 0;
			ans_node += numnodes; //새롭게 발견한 조합을 저장함
		}

		
		i = 0;
		mprod = 1;
		numnodes = 1;
		m = 1;
		weight = 0;
		total = 106;//초기화 작업
	}

	return totalNodes; //numnodes의 합을 저장한 변수 totalNodes를 리턴(노드의 총 개수 추정치들의 합)
}

int promising(int start, int weight, int sum) {// 노드의 유망성을 확인하기 위한 함수
	if ((weight + sum >= sum_W) && (weight == sum_W || weight + W[start + 1] <= sum_W))
		return 1; //해당 노드가 유망한 경우 1을 반환

	else
		return 0; //해당 노드가 유망하지 않은 경우 0을 반환
}