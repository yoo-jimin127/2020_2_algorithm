//algorithm 2020 class (na) HW9 [240]Yoo Jimin_20193017

#include <stdio.h>
#define VERTEX_SIZE 8
#define MAX 100 //힙의 최대 크기

int parent_node[VERTEX_SIZE]; //vertex의 부모 노드
int num[VERTEX_SIZE]; //집합의 크기

typedef struct _Element{//element 구조체
	int v; //vertex v
	int u; //vertex u
	int weight; //정점과 정점 사이에 할당된 가중치 값
}Element;


typedef struct _Heap{//힙 구조체
	Element heap[MAX];//MAX값만큼의 구조체 배열인 heap 생성
	int heap_size;
}Heap; //힙의 데이터타입

void reset_heap(_Heap* h);
void insert_element(Heap* h, Element item);
Element delete_element(Heap* h);
void reset_set(void);
int Find(int v);
void Union(int v1, int v2);
void insert_edge(Heap* h, int v, int u, int weig);
int kruskal(int n);

int main(void) {
	printf("----Minimum Spnning Tree By <Kruskal algorithm>----\n\n");
	printf("최소 신장 트리를 만드는 과정(두 정점 사이의 간선 가중치 출력)\n");
	printf("\n");
	kruskal(14); // 현재 간선의 개수를 kruskal 함수의 인자로 전달
}

//힙을 초기화시키는 함수
void reset_heap(_Heap* h) {
	h->heap_size = 0;
}

//힙에 구조체 Element를 추가하는 함수
void insert_element(Heap* h, Element item) {
	int i = ++(h->heap_size);

	//트리를 순회하며 부모노드와 값 비교
	while (i != 1 && item.weight < h->heap[i / 2].weight) { //i가 루트노드가 아닌 동시에 입력받은 element의 weight값이 i의 부모노드의 weight값보다 작은 경우 위로 올라감
		h->heap[i] = h->heap[i / 2]; //현재노드인 i번째 노드를 부모노드로 설정
		i = i/2; //현재노드의 인덱스를 부모노드의 인덱스로 설정
	}

	h->heap[i] = item; //더 순회할 곳이 없으면 while문을 빠져나와 현재의 인덱스 위치에 item 삽입
}

//힙에 간선을 추가하는 함수
void insert_edge(Heap* h, int v, int u, int weig) {
	Element node;
	node.v = v;//인자로 입력받은 정점 v와 u, 해당 두 정점 사이의 가중치 값을 구조체 변수 node 값에 저장
	node.u = u;
	node.weight = weig;

	insert_element(h, node);//간선을 추가했다면 정점을 추가하는 insert_element 함수에 힙의 주소값과 구조체 변수 node를 인자로 넘김
}

//힙에서 삽입된 Element 구조체를 삭제하는 함수
Element delete_element(Heap* h) {
	Element data, tmp;
	int parent_node, child_node;
	parent_node = 1;//루트노드를 첫 실행에서의 부모노드로 설정
	child_node = 2;//루트노드(1)의 왼쪽 자식인 2번째 인덱스에 위치한 노드를 child node 로 설정

	data = h->heap[parent_node]; //반환할 루트노드의 값을 data에 저장
	tmp = h->heap[(h->heap_size)--]; //마지막 노드의 값를 tmp에 저장하고, 힙의 사이즈를 저장하는 변수 heap_size의 크기를 1 감소

	while (child_node <= h->heap_size) { //child node가 힙 사이즈 이하일 때까지 반복

		//child node 사이의 가중치 값 비교
		if ((child_node < h->heap_size) && (h->heap[child_node].weight) > h->heap[child_node + 1].weight)
			child_node++;

		if (tmp.weight <= h->heap[child_node].weight) //tmp의 가중치가 더 작은 경우 반복문 탈출
			break;

		h->heap[parent_node] = h->heap[child_node];
		parent_node = child_node;
		child_node *= 2; //다음에 위치한 child node로 이동
	}

	h->heap[parent_node] = tmp;
	return data;
}

//집합을 초기화하는 함수
void reset_set(void) {
	for (int i = 0; i < VERTEX_SIZE; i++) {
		parent_node[i] = -1; //부모노드 배열을 -1로 초기화 시킴
		num[i] = 1; //정점의 개수만큼 존재하는 집합의 크기 배열을 1로 초기화 시킴
	}
}

// vertex가 포함된 집합을 찾는 함수
int Find(int v) {
	int i, p, tmp;

	for (i = v; (p = parent_node[i]) >= 0; i = p); //루트 노드의 위치까지 반복하여
	tmp = i; //루트노드의 정보를 tmp에 저장함

	for (i = v; (p = parent_node[i]) >= 0; i = p)
		parent_node[i] = tmp; //집합의 속한 모든 원소의 parent node 값을 루트노드로 저장

	return tmp; //루트노드 반환
}


//집합을 합치는 함수
void Union(int v1, int v2) {

	//각 집합의 노드의 개수를 비교
	if (num[v1] < num[v2]) { //v2가 더 크면
		parent_node[v1] = v2; //v1의 부모 노드를 v2로 설정
		num[v1] += num[v2]; //v1의 크기를 v2 값에 더해줌
	}

	else {//v1이 더 크면
		parent_node[v2] = v1;//v2의 부모 노드를 v1으로 설정
		num[v2] += num[v1];//v2의 크기를 v1 값에 더해줌
	}
}

//kruskal 알고리즘을 사용해 최소 신장 트리를 구하는 함수
int kruskal(int n) {
	Element e; //힙의 요소
	Heap h; //minimum spanning tree
	int edge_cnt = 0, sum = 0;
	int setU, setV; //정점 u와 정점 v의 집합의 번호

	reset_heap(&h);//힙과 집합을 초기화하는 작업
	reset_set();

	//힙에에 모든 간선 삽입(간선이 삽입되면 insert_edge 함수에서 자동으로 insert_element 함수를 호출함
	insert_edge(&h, 1, 2, 11);
	insert_edge(&h, 1, 3, 9);
	insert_edge(&h, 1, 4, 8);
	insert_edge(&h, 2, 3, 3);
	insert_edge(&h, 2, 5, 8);
	insert_edge(&h, 2, 6, 8);
	insert_edge(&h, 3, 4, 15);
	insert_edge(&h, 3, 6, 12);
	insert_edge(&h, 3, 7, 1);
	insert_edge(&h, 4, 7, 10);
	insert_edge(&h, 5, 6, 7);
	insert_edge(&h, 5, 8, 4);
	insert_edge(&h, 6, 8, 5);
	insert_edge(&h, 7, 8, 2);//본 문제에 존재하는 14개의 간선에 대한 정보 삽입 완료


	while (edge_cnt < n - 1) { //간선의 개수가 인자로 입력받은 n-1이 되기까지 반복
		e = delete_element(&h); //최소의 가중치를 가지는 간선 획득
		setU = Find(e.u); //정점 u의 집합 번호
		setV = Find(e.v); //정점 v의 집합 번호

		if (setU != setV) { //두 집합이 서로 다른 집합에 속하는 경우
			printf("(v%d , v%d) is selected, weight : %d\n", e.u, e.v, e.weight);
			sum += e.weight;
			edge_cnt++; //간선을 하나 추가하여
			Union(setU, setV); //setU와 setV Union
		}
	}

	return 0;
}