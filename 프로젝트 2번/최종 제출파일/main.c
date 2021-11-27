#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
#define INF 100000

int GraphNum = 0;
int*** GraphList;
int GraphIndex = 0;
int* VertexNumList;
int* visited;
int* distance;
int** path;

void countGraphNum(char fileloc[50]) { //전체 그래프의 개수를 확인하는 함수
	FILE* fp2 = fopen(fileloc, "r");
	if (fp2 == NULL) {
		printf("파일 읽기 실패(경로를 확인해주세요:D)\n");
	}
	else {
		char buffer[MAX] = { 0, };
		int check = 0; //정점의 개수를 나타내는 줄과 인접 노드 정보를 나타내는 줄 구분하는 기준
		while (fgets(buffer, sizeof(buffer), fp2)) {
			//인접 노드 정보를 나타내는 줄을 읽을 때
			if (check != 0) {
				check--;
				continue;
			}
			//정점 개수를 나타내는 줄을 읽을 때
			int NumSize = sscanf(buffer, "%d", &check); //한 그래프의 전체 정점의 개수
			GraphNum += 1;
		}
		GraphList = (int***)malloc(sizeof(int) * GraphNum); //그래프를 담을 배열을 동적할당함. 
		VertexNumList = (int*)calloc(GraphNum, sizeof(int));//각 그래프의 정점 개수를 담을 배열을 동적할당함.
		fclose(fp2);
	}
}

void readMap2(char fileloc[50]) {
	FILE* fp = fopen(fileloc, "r");
	if (fp == NULL)
		printf("파일이 존재하지 않습니다.\n");
	else {
		char buffer[MAX] = { 0, };
		int check = 0;
		int rowIndex = 0;
		int colIndex = 0;
		int num = 0; //가중치 값

		while (fgets(buffer, sizeof(buffer), fp)) {
			if (check != 0) {
				check--;
				char* bufferPtr = strtok(buffer, " ");// " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
				bufferPtr = strtok(NULL, " ");
				while (bufferPtr != NULL) {// 자른 문자열이 나오지 않을 때까지 반복
					colIndex = atoi(bufferPtr) - 1;
					bufferPtr = strtok(NULL, " ");
					num = atoi(bufferPtr);
					bufferPtr = strtok(NULL, " ");// 다음 문자열을 잘라서 포인터를 반환

					//printf("Graph : %d, rowIndex : %d, colIndex : %d, num : %d\n", GraphIndex,rowIndex,colIndex, num);
					GraphList[GraphIndex - 1][rowIndex][colIndex] = num;
				}
				rowIndex++;
				colIndex = 0;
				continue;
			}

			//그래프의 노드 개수 출력줄.
			int Numsize = sscanf(buffer, "%d", &check); //그래프 정점의 개수
			VertexNumList[GraphIndex] = check;
			GraphList[GraphIndex] = (int**)malloc(sizeof(int*) * check);

			for (int i = 0; i < check; i++) {
				GraphList[GraphIndex][i] = (int*)malloc(sizeof(int) * check);
			}

			for (int i = 0; i < check; i++) {
				for (int j = 0; j < check; j++)
				{
					if (i == j)
						GraphList[GraphIndex][i][j] = 0;
					else
						GraphList[GraphIndex][i][j] = INF;
				}
			}
			GraphIndex += 1;
			rowIndex = 0;//rowIndex 초기화
		}
		fclose(fp);
	}//loop end
}

void makeArr(int GIndex) {
	visited = (int*)calloc(VertexNumList[GIndex], sizeof(int));
	distance = (int*)calloc(VertexNumList[GIndex], sizeof(int));
	path = (int**)calloc(VertexNumList[GIndex], sizeof(int*));
	if (path != NULL) {
	for (int i = 0; i < VertexNumList[GIndex]; i++) {
		path[i] = (int*)calloc(VertexNumList[GIndex], sizeof(int));
	}
}
}

void freeArr2() {
	for (int i = 0; i < GraphNum; i++) {
		int temp = _msize(GraphList[i]) / sizeof(int);
		for (int j = 0; j < temp; j++) {
			free(GraphList[i][j]);
		}
		free(GraphList[i]);
	}
	free(GraphList);
	free(VertexNumList);
	free(visited);
	free(distance);

	int pathSize = _msize(path) / sizeof(int);
	for (int i = 0; i < pathSize; i++) {
		free(path[i]);
	}
	free(path);

}

void Dijkstra(int GIndex) {
	for (int i = 0; i < VertexNumList[GIndex];i++) {
		distance[i] = GraphList[GIndex][0][i];
		visited[i] = 0;
		path[i][0] = 1;
		if (distance[i] < INF)
			path[i][1] = i + 1;
	}
	visited[0] = 1;

	for (int i = 0;i < VertexNumList[GIndex] - 1;i++) {
		int u = 0; int minC = INF;
		for (int j = 0; j < VertexNumList[GIndex];j++) {
			if (visited[j] == 0 && distance[j] < minC)
			{
				u = j;
				minC = distance[j];
			}
		}
		visited[u] = 1;
		for (int j = 0;j < VertexNumList[GIndex];j++) {
			if (visited[j] == 0 && distance[u] + GraphList[GIndex][u][j] < distance[j])
			{
				distance[j] = distance[u] + GraphList[GIndex][u][j];
				for (int l = 1;l < VertexNumList[GIndex];l++) {
					path[j][l] = path[u][l];
					if (path[j][l] == 0)
					{
						path[j][l] = j + 1;
						break;
					}
				}
			}
		}
	}
	printf("시작점 : 1\n");
	for (int i = 1; i < VertexNumList[GIndex];i++) {
		printf("정점 [%d]: ", i + 1);
		for (int j = 0; j < VertexNumList[GIndex];j++)
		{
			if (j == 0)
				printf("%d ", path[i][j]);
			else if (path[i][j] != 0)
				printf("- %d ", path[i][j]);
		}
		printf(", 길이 : %d\n", distance[i]);
	}
}


int main(void) {
	//"input2.txt" txt 읽어오기
	countGraphNum("input2.txt");
	readMap2("input2.txt");

	for (int i = 0; i < GraphIndex;i++) {
		printf("\n그래프 [%d]\n\n", (i + 1));
		printf("--------------------------\n\n");
		makeArr(i);
		Dijkstra(i);
	}
	freeArr2();

}