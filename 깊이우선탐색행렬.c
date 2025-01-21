#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct GraphType {
	int n;
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // �����迭�� ǥ��
} GraphType;

int visited[MAX_VERTICES]; // ���� �湮 Ȯ�� �迭

void init(GraphType* g) {
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}

// ���� ���� ����
void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ���� ���� �ʰ�");
		return;
	}
	g->n++;
}

// ���� ���� ����
void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

// ���� ��ķ� ǥ���� �׷����� ���� ���� �켱 Ž��
void dfs_mat(GraphType* g, int v) {
	int w;
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	printf("���� %d -> ", v);
	for (w = 0; w < g->n; w++)
		if (g->adj_mat[v][w] && !visited[w]) // v�������� w������ ����Ǿ��ְ�, w������ �湮���� �ʾ�����
			dfs_mat(g, w); // ���� w���� dfs �ٽ� ����
}


