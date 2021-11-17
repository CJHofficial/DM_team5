#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 100
#define MAX_QUEUE_SIZE MAX * MAX * MAX
int wp, rp;

int n, minn = INT_MAX;
int sum = 0;
int** GraphList[20] = { NULL, }; //각 그래프를 담을 배열 이거 동적할당해도 되긴 함
int GraphIndex = 0;
int VertexNumList[20] = { 0, }; //각 그래프의 정점 개수를 담을 배열

int* visited; //visted배열은 각 정점에 방문했는지를 체크함.
int* path; //path배열은 경로를 저장하는 스택.
int pathIndex; //path배열의 index
int BFSIndex; //BFS에서 쓸 index

queue<int> que;

void makeArr(int Gindex) {
	while (!que.empty()) que.pop();
	visited = (int*)calloc(VertexNumList[Gindex], sizeof(int));
	path = (int*)calloc(VertexNumList[Gindex], sizeof(int));
	//calloc은 원소를 자동으로 0으로 초기화
	//malloc는 그런게 없어서 초기화 필수
	//각 그래프의 점의 수를 크기로 visted배열, path배열 생성
	pathIndex = 0;
	BFSIndex = 1;
}

void freeArr(int SearchCheck) {
	if (SearchCheck == 1) {
		printf("깊이 우선 탐색\n\n");
	}
	int	pathSize = _msize(path) / sizeof(int);//path의 길이만큼 반복
	for (int i = 0; i < pathSize; i++) {
		printf("%d ", path[i]);
		if (i != (pathSize - 1)) {
			printf("- ");
		}
		else {
			printf("\n\n");
		}
	}
	free(visited);
	free(path);
	//calloc를 통해 heap에 동적할당 된 배열 반납
}

void DFS(int Gindex, int v) { //Gindex가 1이면 첫번째 그래프를 뜻함. v는 시작 노드
	if (visited[v] == 0) {
		visited[v] = 1;
		path[pathIndex++] = v + 1;//한번 수행될 떄마다 점을 path에 넣는 과정
		for (int i = 0; i < VertexNumList[Gindex]; i++) { //여기서 i는 v와 연결된 노드를 의미함.
			if (GraphList[Gindex][v][i] != 0 && visited[i] == 0) {//방문하지 않은 연결된 노드를 탐방
				DFS(Gindex, i);//재귀를 통해 수행
			}
		}
		return;
	}
	else {
		return;
	}

}

void BFS(int Gindex, int v) { //Gindex가 1이면 첫번째 그래프를 뜻함. v는 시작 
	printf("깊이 우선 탐색\n\n");
	cout << v + 1 << " - ";
	que.push(v);
	int it = 0;
	while (!que.empty()) {
		int node = que.front();
		que.pop();
		visited[node] = 1;
		for (int i = 0; i < VertexNumList[Gindex]; i++) {
			if (GraphList[Gindex][node][i] != 0 && visited[i] == 0) {
				it++;
				if (it < VertexNumList[Gindex]) {
					if (i == (VertexNumList[Gindex] - 1)) {
						cout << i + 1;
					}
					else {
						cout << i + 1;
					}
					if (it < VertexNumList[Gindex] - 1) {
						cout << " - ";
					}
				}
				que.push(i);
			}
		}
	}
	cout << endl;
}

void FreeMemory() { //동적할당한 메모리 해제
	for (int i = 0; i < GraphIndex; i++) {
		int temp = _msize(GraphList[i]) / sizeof(int);
		//printf("%d\n", temp);
		for (int j = 0; j < temp; j++) {
			free(GraphList[i][j]);
		}
		free(GraphList[i]);
	}
}

int main() {
	// "input.txt" txt파일 읽기
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("파일 읽기 실패\n");
	}
	else {
		//한 줄씩 읽기
		char buffer[MAX] = { 0, };
		int check = 0; //정점의 개수를 나타내는 줄과 인접 노드 정보를 나타내는 줄 구분하는 기준
		int rowIndex = 0;
		int colIndex = 0;
		while (fgets(buffer, sizeof(buffer), fp)) {

			//인접 노드 정보를 나타내는 줄을 읽을 때
			if (check != 0) {
				check--;
				//printf("%s\n", buffer);

				//인접행렬에 인접 노드 정보 채우기
				int bufferSize = strlen(buffer);
				if (bufferSize > 2) {
					for (int i = 2; i < bufferSize; i++) {
						if ((i % 2) == 1) continue; //버퍼에서 짝수index에 인접 노드 정보가 있으므로
						colIndex = (buffer[i] - '0') - 1;
						GraphList[GraphIndex - 1][rowIndex][colIndex] = 1; //정점 a와 b는 인접을 뜻함.
					}
				}
				rowIndex++;
				colIndex = 0;
				continue;
			}

			//정점 개수를 나타내는 줄을 읽을 때
			if (strlen(buffer) == 2) {
				//printf("%s\n", buffer);
				check = buffer[0] - '0'; //그래프 정점의 개수
				VertexNumList[GraphIndex] = check;
				rowIndex = 0;
				//정점 개수만큼 그래프 인접 행렬로 동적할당해서 생성 ex.GraphList[0] => 첫번째 그래프의 인접행렬
				GraphList[GraphIndex] = (int**)malloc(sizeof(int) * check);
				for (int i = 0; i < check; i++) {
					GraphList[GraphIndex][i] = (int*)malloc(sizeof(int) * check);
				}

				//인접행렬 0으로 초기화
				for (int i = 0; i < check; i++) {
					for (int j = 0; j < check; j++) {
						GraphList[GraphIndex][i][j] = 0;
					}
				}
				GraphIndex += 1;
			}



		}
		//printf("전체 그래프 개수 : %d\n\n", GraphIndex); //전체 그래프 개수 출력

		//만들어진 그래프들 출력
		/*
		for (int k = 0; k < GraphIndex; k++) {
			printf("%d   \n",VertexNumList[k]);
			for (int a = 0; a < VertexNumList[k]; a++) {
				for (int b = 0; b < VertexNumList[k]; b++) {
					printf("%d ", GraphList[k][a][b]);
				}
				printf("\n");
			}
			printf("\n");
		}
		*/

	}

	for (int i = 0; i < GraphIndex; i++) {
		printf("그래프 [%d]\n\n", (i + 1));
		printf("---------------------------------\n\n");
		//DFS 깊이 우선 탐색
		makeArr(i);
		DFS(i, 0);
		freeArr(1);
		//BFS 너비 우선 탐색
		makeArr(i);
		BFS(i, 0);
		printf("=================================\n\n\n");
	}
	//동적할당한 메모리 해제
	FreeMemory();
	fclose(fp);

	return 0;
}