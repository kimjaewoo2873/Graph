#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define TRUE 1
#define FALSE 0

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
} GraphType;

int visited[MAX_VERTICES];

void init(GraphType* g) {
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++)
		g->adj_list[i] = NULL;
}

void insert_vertex(GraphType* g, int v) {
	if (((g->n) + 1 > MAX_VERTICES)) {
		fprintf(stderr, "�׷���: ���� �ʰ� ����");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = start;
	node->link = g->adj_list[end];
	g->adj_list[end] = node;
	/* ������ �׷����� ��� �ݴ� ���� ������ �߰�
	node->vertex = end;
	node->link = g->adj_list[start];
	g->adj_list[start] = node;
	*/
}

void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE; // ���� v�� �湮 ǥ��
	printf("���� %d -> ", v);

	for (w = g->adj_list[v]; w; w = w->link) { // v�� �������� �湮�ϱ�
		if (!visited[w->vertex]) { // ���� w�� �湮���� �ʾ��� ���
			dfs_list(g, w->vertex); // ���� w���� DFS ���� ����
		}
	}
}