#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <malloc/malloc.h>

#define MAX 100

int n, minn = INT_MAX;
int sum = 0;
int** GraphList[20] = { NULL, }; //각 그래프를 담을 배열 이거 동적할당해도 되긴 함
int GraphIndex = 0;
int VertexNumList[20] = { 0, }; //각 그래프의 정점 개수를 담을 배열

int* visited; //visted배열은 각 정점에 방문했는지를 체크함.
int* path; //path배열은 경로를 저장하는 배열.
int pathIndex; //path배열의 index
int BFSIndex; //BFS에서 쓸 index

void makeArr(int Gindex) { 
	visited = (int*)calloc(VertexNumList[Gindex], sizeof(int));
	path = (int*)calloc(VertexNumList[Gindex], sizeof(int));
	pathIndex = 0;
	BFSIndex = 1;
}

void freeArr(int SearchCheck) {
	if (SearchCheck == 1) {
		printf("깊이 우선 탐색\n\n");
	}
	else if (SearchCheck == 2) {
		printf("너비 우선 탐색\n\n");
	}
	int	pathSize = malloc_size(path)/sizeof(int);//_msize
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
}

//이 코드는 Mac OS에서 작성했습니다.

void BFS(int Gindex, int v) { //Gindex가 1이면 첫번째 그래프를 뜻함. v는 시작 노드
	if (path[malloc_size(path) / sizeof(int) - 1] != 0) return;//윈도우에서는 _msize. 모든 노드 방문을 원할 시, 이 구문 주석처리.

	if (visited[v] == 0) {//연결노드 탐색 및 경로에 추가.
		visited[v] = 1;
		for (int i = 0; i < VertexNumList[Gindex]; i++) { //여기서 i는 v와 연결된 노드를 의미함.
			if (GraphList[Gindex][v][i] != 0) {
				int isIndexInPath = 0; // path에 값이 없는 경우 0/ 존재하는 경우 1.
				for (int j = 0; j< VertexNumList[Gindex]; j++){ 
					if(path[j] == i+1){//path에 이미 존재하는 경우
						isIndexInPath = 1;
						break;
					}
				}
				if(isIndexInPath == 0){//path에 존재하지 않는 경우 path에 추가.
					path[++pathIndex] = i + 1;
				}
			}
		}
	}

	if(BFSIndex < VertexNumList[Gindex])
		BFS(Gindex, path[BFSIndex++]-1);
	return;
}

void FreeMemory() { //동적할당한 메모리 해제
	for (int i = 0; i < GraphIndex; i++) {
		int temp = malloc_size(GraphList[i]) / sizeof(int);//_msize
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
		char buffer[MAX] = {0, };
		int check = 0; //정점의 개수를 나타내는 줄과 인접 노드 정보를 나타내는 줄 구분하는 기준
		int rowIndex = 0;
		int colIndex = 0;

		while (fgets(buffer, sizeof(buffer), fp)) {

			//인접 노드 정보를 나타내는 줄을 읽을 때
			if (check != 0) {
				check--;
				int bufferSize = strlen(buffer);

				if (strlen(buffer) > 2) {
					char *bufferPtr = strtok(buffer, " ");// " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환

					bufferPtr = strtok(NULL, " ");

					while (bufferPtr != NULL){// 자른 문자열이 나오지 않을 때까지 반복
							colIndex = atoi(bufferPtr) - 1;
							bufferPtr = strtok(NULL, " ");// 다음 문자열을 잘라서 포인터를 반환
							
							//printf("Graph : %d, rowIndex : %d, colIndex : %d, num : %d\n", GraphIndex,rowIndex,colIndex, num);
							GraphList[GraphIndex - 1][rowIndex][colIndex] = 1;
					}
					//https://dojang.io/mod/page/view.php?id=376 참조.
				}
                
				rowIndex++;
				colIndex = 0;
			}

			else  { //if (strlen(buffer) == 2)
				//printf("%s\n", buffer);
				check = buffer[0] - '0';
				VertexNumList[GraphIndex] = check;
				GraphList[GraphIndex] = (int**)malloc(sizeof(int*) * check);
				rowIndex = 0;

				//정점 개수만큼 그래프 동적할당해서 생성
				for (int i = 0; i < check; i++) {
					GraphList[GraphIndex][i] = (int*)malloc(sizeof(int) * check);
				}
				
				for (int i = 0; i < check;i++) {
					for (int j = 0; j < check;j++)
					{
						GraphList[GraphIndex][i][j] = 0;
					}
				}
				GraphIndex += 1;
				
			}
		}//loop end
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
	fclose(fp); 

	
	for (int i = 0; i < GraphIndex; i++) {
			printf("그래프 [%d]\n\n", (i + 1));
		printf("---------------------------------\n\n");
		//BFS 너비 우선 탐색
		makeArr(i);
		path[0] = 1;
		BFS(i, 0);
		freeArr(2);
		printf("=================================\n\n\n");
	}
	//동적할당한 메모리 해제
	//FreeMemory();
}
