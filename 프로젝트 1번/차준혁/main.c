#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int** GraphList[MAX] = { NULL, }; //�� �׷����� ���� �迭 �̰� �����Ҵ��ص� �Ǳ� ��
int GraphIndex = 0;
int VertexNumList[MAX] = { 0, }; //�� �׷����� ���� ������ ���� �迭

int* visited; //visted�迭�� �� ������ �湮�ߴ����� üũ��.
int* path; //path�迭�� ��θ� �����ϴ� �迭.
int pathIndex; //path�迭�� index
int* Q; //BFS���� �� Queue
int front; //BFS���� �� index, Queue���� ���� �տ� �ִ� ���Ҹ� ����Ű�� index
int rear; //BFS���� �� index, Queue���� ���� �ڿ� �ִ� ���Ҹ� ����Ű�� index

void readMap(char fileloc[20]) {
	// "input.txt" txt���� �б�
	FILE* fp = fopen(fileloc, "r");
	if (fp == NULL) {
		printf("���� �б� ����\n");
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
				int bufferSize = strlen(buffer);
				if (bufferSize > 2) {
					for (int i = 2; i < bufferSize; i++) {
						if ((i % 2) == 1) continue; //���ۿ��� ¦��index�� ���� ��� ������ �����Ƿ�
						colIndex = (buffer[i] - '0') - 1;
						GraphList[GraphIndex - 1][rowIndex][colIndex] = 1; //���� a�� b�� ������ ����.
					}
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
	
	readMap("input.txt");
	for (int i = 0; i < GraphIndex; i++) {
		printf("�׷��� [%d]\n\n", (i + 1));
		printf("---------------------------------\n\n");
		//DFS ���� �켱 Ž��
		makeArr(i, 1);
		DFS(i, 0);
		freeArr(1);
		//BFS �ʺ� �켱 Ž��
		makeArr(i, 2);
		BFS(i, 0);
		freeArr(2);
		printf("=================================\n\n\n");
	}
	//�����Ҵ��� �޸� ����
	FreeMemory();
}