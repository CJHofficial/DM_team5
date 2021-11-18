#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100
#define INF 100000

int** GraphList[20] = { NULL, };
int GraphIndex = 0;
int VertexNumList[20] = { 0, };

int* visited;
int* distance;
int** path;
void makeArr(int GIndex) {
	visited = (int*)calloc(VertexNumList[GIndex], sizeof(int));
	distance = (int*)calloc(VertexNumList[GIndex], sizeof(int));
	path = (int**)calloc(VertexNumList[GIndex], sizeof(int*));
	for (int i = 0; i < VertexNumList[GIndex]; i++) {
		path[i] = (int*)calloc(VertexNumList[GIndex],sizeof(int));
	}
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
		printf("정점 [%d]: ", i+1);
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
	FILE* fp = fopen("input2.txt", "r");
	if (fp == NULL)
		printf("파일이 존재하지 않습니다.\n");
	else {
		char buffer[MAX] = { 0, }; 
		int check = 0;
		int rowIndex = 0;
		int colIndex = 0;
		int num = 0;

		while (fgets(buffer, sizeof(buffer), fp)) {
			if (check != 0) {
				check--;
				int bufferSize = strlen(buffer);

				if (strlen(buffer) > 2) {
					char *bufferPtr = strtok(buffer, " ");// " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환

					bufferPtr = strtok(NULL, " ");

					while (bufferPtr != NULL){// 자른 문자열이 나오지 않을 때까지 반복
							colIndex = atoi(bufferPtr) - 1;
							bufferPtr = strtok(NULL, " ");
							num = atoi(bufferPtr);
							bufferPtr = strtok(NULL, " ");// 다음 문자열을 잘라서 포인터를 반환
							
							//printf("Graph : %d, rowIndex : %d, colIndex : %d, num : %d\n", GraphIndex,rowIndex,colIndex, num);
							GraphList[GraphIndex - 1][rowIndex][colIndex] = num;
					}
					//https://dojang.io/mod/page/view.php?id=376 참조.
				}
				rowIndex++;
				colIndex = 0;
			}

			else { //노드 개수 출력줄.
				check = buffer[0] - '0';
				VertexNumList[GraphIndex] = check;
				GraphList[GraphIndex] = (int**)malloc(sizeof(int*) * check);

				for (int i = 0; i < check; i++) {
					GraphList[GraphIndex][i] = (int*)malloc(sizeof(int) * check);
				}
				
				for (int i = 0; i < check;i++) {
					for (int j = 0; j < check;j++)
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
		}//loop end
		fclose(fp);
	}

	//������� �׷��� ���
	
/*
for (int k = 0; k < GraphIndex; k++) {
			printf("%-10d   \n",VertexNumList[k]);
			for (int a = 0; a < VertexNumList[k]; a++) {
				for (int b = 0; b < VertexNumList[k]; b++) {
					printf("%d ", GraphList[k][a][b]);
				}
				printf("\n");
			}
			printf("\n");
		}
*/
	for (int i = 0; i < GraphIndex;i++) {
		printf("\n그래프 [%d]\n\n", (i + 1));
		printf("--------------------------\n\n");
		makeArr(i);
		Dijkstra(i);
	}


}