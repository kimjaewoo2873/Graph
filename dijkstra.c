#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES]; // �� �������� �ٸ����������� ����ġ ����
}GraphType;

int distance[MAX_VERTICES]; // �� ���������� ���� ª�� �˷��� �Ÿ��� ����
int found[MAX_VERTICES]; // ������ ���� ǥ�� / 1: �湮, 0: x

int choose(int distance[], int n, int found[]) { // �ִܰ�� ���� ã��
	int i, min, minpos;
	min = INT_MAX; // ���Ѵ�� �ʱ�ȭ
	minpos = -1; // ���� �ε��� ������ ����
	for(i = 0; i < n; i++) // ���� ª���Ÿ��� ������ ã�� �ε��� ����
		if (distance[i] < min && !found[i]) { 
			min = distance[i]; // distance�迭�� ����� ���� ���ϱ�����
			minpos = i; // �ε����� ����
		}
	return minpos; // ���� ª�� �Ÿ��� ���� ������ȣ ��ȯ
}

void print_status(GraphType* g) {
	static int step = 1;
	printf("STEP %d: ", step++);
	printf("distance: ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
	int i, u, w;
	for (i = 0; i < g->n; i++) {
		distance[i] = g->weight[start][i]; // ���� �������� �Ÿ� �ʱ�ȭ
		found[i] = FALSE; 
	}
	found[start] = TRUE;
	distance[start] = 0; // ���� ������ ���ΰŸ� "0"
	for (i = 0; i < g->n - 1; i++) {
		print_status(g);
		u = choose(distance, g->n, found); // �ִܰ�� ���� ã��
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w]) // �湮�� �������� �Ÿ��� �ʿ����
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
}
