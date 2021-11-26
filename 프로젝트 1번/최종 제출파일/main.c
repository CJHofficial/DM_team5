#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000
int GraphNum = 0; //ó�� ���� ������ ��ü �׷��� ���� ����
int GraphIndex = 0;
int*** GraphList;   //�� �׷����� ���� �迭
int* VertexNumList; //�� �׷����� �� ���� ������ ���� �迭
int* visited; //visted�迭�� �� ������ �湮�ߴ����� üũ��.
int* path; //path�迭�� ��θ� �����ϴ� �迭.
int pathIndex; //path�迭�� index
int* Q; //BFS���� �� Queue
int front; //BFS���� �� index, Queue���� ���� �տ� �ִ� ���Ҹ� ����Ű�� index
int rear; //BFS���� �� index, Queue���� ���� �ڿ� �ִ� ���Ҹ� ����Ű�� index

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

void readMap(char fileloc[50]) {
	// "input.txt" txt���� �б�
	FILE* fp = fopen(fileloc, "r");
	if (fp == NULL) {
		printf("���� �б� ����(��θ� Ȯ�����ּ���:D)\n");
	}
	else {
		//�� �پ� �б�
		char buffer[MAX] = { 0, };
		int check = 0; //������ ������ ��Ÿ���� �ٰ� ���� ��� ������ ��Ÿ���� �� �����ϴ� ����
		int rowIndex = 0;
		int colIndex = 0;
		while (fgets(buffer, sizeof(buffer), fp)) {
			//printf("%s\n", buffer);

			//���� ��� ������ ��Ÿ���� ���� ���� ��
			if (check != 0) {
				check--;

				//������Ŀ� ���� ��� ���� ä���
				char* bufferPtr = strtok(buffer, " "); //���� ���� ���� ������ ��Ÿ���Ƿ�
				bufferPtr = strtok(NULL, " "); //�ٷ� ���� �������� �Ѿ
				while (bufferPtr != NULL) {
					colIndex = atoi(bufferPtr) - 1;
					GraphList[GraphIndex - 1][rowIndex][colIndex] = 1;
					bufferPtr = strtok(NULL, " ");
				}
				rowIndex++;
				colIndex = 0;
				continue;
			}

			//���� ������ ��Ÿ���� ���� ���� ��
			int NumSize = sscanf(buffer,"%d",&check);//�׷��� ������ ����
			//printf("%d\n", check);
			//printf("%d\n", NumSize); // NumSize�� buffer���� ���� �������� ũ��(���� �ڸ����� ����.)
			VertexNumList[GraphIndex] = check;
			rowIndex = 0;
			//���� ������ŭ �׷��� ���� ��ķ� �����Ҵ��ؼ� ���� ex.GraphList[0] => ù��° �׷����� �������
			GraphList[GraphIndex] = (int**)malloc(sizeof(int) * check);
			for (int i = 0; i < check; i++) {
				GraphList[GraphIndex][i] = (int*)malloc(sizeof(int) * check);
			}

			//������� 0���� �ʱ�ȭ
			for (int i = 0; i < check; i++) {
				for (int j = 0; j < check; j++) {
					GraphList[GraphIndex][i][j] = 0;
				}
			}
			GraphIndex += 1;
		}
		//printf("��ü �׷��� ���� : %d\n\n", GraphIndex); //��ü �׷��� ���� ���

		//������� �׷����� ���
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
}

void makeArr(int Gindex, int SearchCheck) { //SearchCheck�� 1�̸� DFS, 2�̸� BFS
	visited = (int*)calloc(VertexNumList[Gindex], sizeof(int));
	path = (int*)calloc(VertexNumList[Gindex], sizeof(int));
	pathIndex = 0;
	if (SearchCheck == 2) {
		Q = (int*)calloc( VertexNumList[Gindex] + 1 , sizeof(int));
		front = -1;
		rear = -1;
	}
}

void freeArr(int SearchCheck) { 
	if (SearchCheck == 1) {
		printf("���� �켱 Ž��\n\n");
	}
	else if (SearchCheck == 2) {
		printf("�ʺ� �켱 Ž��\n\n");
		free(Q);
	}
	int	pathSize = _msize(path) / sizeof(int);
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

void DFS(int Gindex, int v) { //Gindex�� 1�̸� ù��° �׷����� ����. v�� ���� ���
	if (visited[v] == 0) {
		visited[v] = 1;
		path[pathIndex++] = v+1;
		for (int i = 0; i < VertexNumList[Gindex]; i++) { //���⼭ i�� v�� ����� ��带 �ǹ���.
			if (GraphList[Gindex][v][i] != 0 && visited[i] == 0) {
				DFS(Gindex, i);
			}
		}
		return;
	}
	else {
		return;
	}

}

void BFS(int Gindex, int v) { //Gindex�� 1�̸� ù��° �׷����� ����. v�� ���� ���
	if (visited[v] == 0) {
		visited[v] = 1;
		path[pathIndex++] = v + 1;
		Q[++rear] = v;
		while (front != rear) {
			v = Q[++front];
			for (int i = 0; i < VertexNumList[Gindex]; i++) { //���⼭ i�� v�� ����� ��带 �ǹ���.
				if (GraphList[Gindex][v][i] != 0 && visited[i] == 0) {
					visited[i] = 1;
					path[pathIndex++] = i + 1;
					if (path[_msize(path) / sizeof(int) - 1] != 0) return; //path�� �� ä������ return
					Q[++rear] = i;
				}
			}
		}
		return;
	}
	else {
		return;
	}
}

void FreeMemory() { //�����Ҵ��� �޸� ����
	for (int i = 0; i < GraphNum; i++) {
		int temp = _msize(GraphList[i]) / sizeof(int);
		//printf("%d\n", temp);
		for (int j = 0; j < temp; j++) {
			free(GraphList[i][j]);
		}
		free(GraphList[i]);
	}
	free(GraphList);
	free(VertexNumList);
}

int main() {
	int startVertex = 0; //0�� ����1�� ����.
	countGraphNum("input.txt");
	readMap("input.txt");
	for (int i = 0; i < GraphNum; i++) {
		printf("�׷��� [%d]\n\n", (i + 1));
		printf("---------------------------------\n\n");
		//DFS ���� �켱 Ž��
		makeArr(i, 1);
		DFS(i, startVertex);
		freeArr(1);
		//BFS �ʺ� �켱 Ž��
		makeArr(i, 2);
		BFS(i, startVertex);
		freeArr(2);
		printf("=================================\n\n\n");
	}
	//�����Ҵ��� �޸� ����
	FreeMemory();
}