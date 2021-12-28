#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996)

typedef struct _TreeNode {//트리 노드 구조체
    char value;//노드의 값을 저장하는 변수
    struct _TreeNode* left;//왼쪽 자식
    struct _TreeNode* right;//오른쪽 자식
} TreeNode;

void makeNewNode(TreeNode* node, char parent, char leftChild, char rightChild)
{//노드를 추가하는 함수
    if (node == NULL) return;//node가 0일 경우 노드 추가 x

    if (node->value == parent) {//node의 value가 parent 값과 같을 때
        if (leftChild != '.') {

            node->left = (TreeNode*)malloc(sizeof(TreeNode));//왼쪽 자식의 입력값이 .이 아닌 경우, 노드의 왼쪽에 메모리를 할당해줌
            node->left->left = NULL;//노드의 왼쪽 자식의 왼쪽자식을 null으로 지정함
            node->left->right = NULL;//노드의 왼쪽 자식의 오른쪽자식을 null으로 지정함

            node->left->value = leftChild;//노드의 왼쪽 자식의 값에 입력값인 leftChild를 넣음
        }

        if (rightChild != '.') {
            node->right = (TreeNode*)malloc(sizeof(TreeNode));//오른쪽 자식의 입력값이 .이 아닌 경우, 노드의 오른쪽에 메모리를 할당해줌
            node->right->left = NULL;//노드의 오른쪽 자식의 왼쪽자식을 null으로 지정함
            node->right->right = NULL;//노드의 오른쪽 자식의 오른쪽자식을 null으로 지정함

            node->right->value = rightChild;//노드의 오른쪽 자식의 값에 입력값인 rightChild를 넣음
        }

        return;
    }

    makeNewNode(node->left, parent, leftChild, rightChild);//재귀를 통해 노드추가함수를 호출함
    makeNewNode(node->right, parent, leftChild, rightChild);
}

TreeNode* searchNode(TreeNode* node, char value)
{//노드를 탐색하는 함수
    if (node != NULL) {
        if (node->value == value) {
            return node;//노드가 null이 아닌 경우 node가 가진 value값이 인자로 받은 value와 같을 때 node를 리턴함
        }
        else {//노드가 null이 아님과 동시에 node가 가진 value 값이 인자로 받은 value와 다른 경우
            TreeNode* tempNode = searchNode(node->left, value);
            //임의의 노드인 tempNode를 선언하고 재귀를 통해 노드의 왼쪽 자식과 value를 인자로 전달함

            if (tempNode != NULL) {//임의의 노드 tempNode의 값이 null이 아닌 경우 tempNode를 리턴함
                return tempNode;
            }

            return searchNode(node->right, value);//노드의 오른쪽 자식과 값을 인자로 넘겨 재귀호출함으로서 노드의 양 자식을 탐색함
        }
    }
    return NULL;//node가 null인 경우에는 null을 리턴함
}

void treeInOrder(TreeNode* node)
{//트리를 중위 순회 방식으로 출력하는 함수
    if (node != NULL) {
        treeInOrder(node->left);//재귀를 사용해 node의 왼쪽자식을 인자로 중위순회함
        printf("%c", node->value);//node의 value 값을 출력함
        treeInOrder(node->right);//재귀를 사용해 node의 오른쪽자식을 인자로 중위순회함
    }
}

int main(void)
{
    int n;//노드의 개수를 저장하는 변수

    TreeNode* Head = (TreeNode*)malloc(sizeof(TreeNode));//헤드노드의 메모리 할당
    Head->value = 0;//헤드노드의 초기 데이터 값(value)을 0으로 초기화
    Head->left = NULL;//헤드노드의 왼쪽 자식을 null로 초기화
    Head->right = NULL;//헤드노드의 오른쪽 자식을 null로 초기화

    scanf("%d", &n);//입력창으로부터 노드의 개수를 저장하는 변수 n의 값을 입력받음
    getchar();

    for (int i = 0; i < n; i++) {//n(노드의 개수)만큼 반복적으로 값을 입력받음(부모, 왼쪽 자식, 오른쪽 자식 순)
        char parent, leftChild, rightChild;//부모노드, 왼쪽 자식, 오른쪽 자식의 값을 저장할 변수
        scanf("%c %c %c", &parent, &leftChild, &rightChild);//부모노드, 왼쪽 자식, 오른쪽 자식의 값을 입력받음
        getchar();

        if (parent == 'A') {//parent노드가 A일 때
            Head->value = parent;//헤드노드의 값은 A가 됨

            if (leftChild != '.') {//leftChild의 값이 .이 아닐 경우
                Head->left = (TreeNode*)malloc(sizeof(TreeNode));//구조체 멤버인 left의 값에 메모리 할당
                Head->left->left = NULL;
                Head->left->right = NULL;

                Head->left->value = leftChild;
            }

            if (rightChild != '.') {//rightChild의 값이 .이 아닐 경우
                Head->right = (TreeNode*)malloc(sizeof(TreeNode));//구조체 멤버인 right의 값에 메모리 할당
                Head->right->left = NULL;
                Head->right->right = NULL;

                Head->right->value = rightChild;
            }

            continue;
        }

        searchNode(Head, parent);
        if (i != 0) {
            makeNewNode(Head, parent, leftChild, rightChild);
            //반복하며 입력받은 값들을 노드추가함수의 인자로 넣으며 트리에 추가시킴
        }
    }

    treeInOrder(Head);//트리를 중위순회하는 방식으로 출력하는 함수에 Head를 인자로 넘겨 값을 출력함

    return 0;
}
