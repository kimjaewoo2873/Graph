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
		fprintf(stderr, "그래프: 정점 초과 오류");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = start;
	node->link = g->adj_list[end];
	g->adj_list[end] = node;
	/* 무방향 그래프일 경우 반대 방향 간선도 추가
	node->vertex = end;
	node->link = g->adj_list[start];
	g->adj_list[start] = node;
	*/
}

void dfs_list(GraphType* g, int v) {
	GraphNode* w;
	visited[v] = TRUE; // 정점 v에 방문 표시
	printf("정점 %d -> ", v);

	for (w = g->adj_list[v]; w; w = w->link) { // v의 인접정점 방문하기
		if (!visited[w->vertex]) { // 정점 w가 방문되지 않았을 경우
			dfs_list(g, w->vertex); // 정점 w에서 DFS 새로 시작
		}
	}
}