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

void countGraphNum(char fileloc[50]) { //��ü �׷����� ������ Ȯ���ϴ� �Լ�
	FILE* fp2 = fopen(fileloc, "r");
	if (fp2 == NULL) {
		printf("���� �б� ����(��θ� Ȯ�����ּ���:D)\n");
	}
	else {
		char buffer[MAX] = { 0, };
		int check = 0; //������ ������ ��Ÿ���� �ٰ� ���� ��� ������ ��Ÿ���� �� �����ϴ� ����
		while (fgets(buffer, sizeof(buffer), fp2)) {
			//���� ��� ������ ��Ÿ���� ���� ���� ��
			if (check != 0) {
				check--;
				continue;
			}
			//���� ������ ��Ÿ���� ���� ���� ��
			int NumSize = sscanf(buffer, "%d", &check); //�� �׷����� ��ü ������ ����
			GraphNum += 1;
		}
		GraphList = (int***)malloc(sizeof(int) * GraphNum); //�׷����� ���� �迭�� �����Ҵ���. 
		VertexNumList = (int*)calloc(GraphNum, sizeof(int));//�� �׷����� ���� ������ ���� �迭�� �����Ҵ���.
	}
	fclose(fp2);
}

void readMap2(char fileloc[50]) {
	FILE* fp = fopen(fileloc, "r");
	if (fp == NULL)
		printf("������ �������� �ʽ��ϴ�.\n");
	else {
		char buffer[MAX] = { 0, };
		int check = 0;
		int rowIndex = 0;
		int colIndex = 0;
		int num = 0; //����ġ ��

		while (fgets(buffer, sizeof(buffer), fp)) {
			if (check != 0) {
				check--;
				char* bufferPtr = strtok(buffer, " ");// " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
				bufferPtr = strtok(NULL, " ");
				while (bufferPtr != NULL) {// �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
					colIndex = atoi(bufferPtr) - 1;
					bufferPtr = strtok(NULL, " ");
					num = atoi(bufferPtr);
					bufferPtr = strtok(NULL, " ");// ���� ���ڿ��� �߶� �����͸� ��ȯ

					//printf("Graph : %d, rowIndex : %d, colIndex : %d, num : %d\n", GraphIndex,rowIndex,colIndex, num);
					GraphList[GraphIndex - 1][rowIndex][colIndex] = num;
				}
				rowIndex++;
				colIndex = 0;
				continue;
			}

			//�׷����� ��� ���� �����.
			int Numsize = sscanf(buffer, "%d", &check); //�׷��� ������ ����
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
			rowIndex = 0;//rowIndex �ʱ�ȭ
		}
	}//loop end

	fclose(fp);
}

void makeArr(int GIndex) {
	visited = (int*)calloc(VertexNumList[GIndex], sizeof(int));
	distance = (int*)calloc(VertexNumList[GIndex], sizeof(int));
	path = (int**)calloc(VertexNumList[GIndex], sizeof(int*));
	for (int i = 0; i < VertexNumList[GIndex]; i++) {
		path[i] = (int*)calloc(VertexNumList[GIndex], sizeof(int));
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
	for (int i = 0; i < VertexNumList[GIndex]; i++) {
		distance[i] = GraphList[GIndex][0][i];
		visited[i] = 0;
		path[i][0] = 1;
		if (distance[i] < INF)
			path[i][1] = i + 1;
	}
	visited[0] = 1;

	for (int i = 0; i < VertexNumList[GIndex] - 1; i++) {
		int u = 0; int minC = INF;
		for (int j = 0; j < VertexNumList[GIndex]; j++) {
			if (visited[j] == 0 && distance[j] < minC)
			{
				u = j;
				minC = distance[j];
			}
		}
		visited[u] = 1;
		for (int j = 0; j < VertexNumList[GIndex]; j++) {
			if (visited[j] == 0 && distance[u] + GraphList[GIndex][u][j] < distance[j])
			{
				distance[j] = distance[u] + GraphList[GIndex][u][j];
				for (int l = 1; l < VertexNumList[GIndex]; l++) {
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
	printf("������ : 1\n");
	for (int i = 1; i < VertexNumList[GIndex]; i++) {
		printf("���� [%d]: ", i + 1);
		for (int j = 0; j < VertexNumList[GIndex]; j++)
		{
			if (j == 0)
				printf("%d ", path[i][j]);
			else if (path[i][j] != 0)
				printf("- %d ", path[i][j]);
		}
		printf(", ���� : %d\n", distance[i]);
	}
}


int main(void) {
	//"input2.txt" txt �о����
	countGraphNum("input2.txt");
	readMap2("input2.txt");

	for (int i = 0; i < GraphIndex; i++) {
		printf("\n�׷��� [%d]\n\n", (i + 1));
		printf("--------------------------\n\n");
		makeArr(i);
		Dijkstra(i);
	}
	freeArr2();

}