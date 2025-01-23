#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // 부모노드 인덱스 저장할 배열

void init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

// curr가 속하는 집합을 반환. 사이클 형성 확인
int set_find(int curr) { // 반환한 2개의 루트노드가 같은 집합에 속해있다면, 사이클 생성
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

void set_union(int a, int b) { // 두개의 다른 집합을 하나로 병합
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2) // 같은 집합을 병합하지 않아, 사이클 형성 방지
		parent[root1] = root2;
}

struct Edge { // 간선을 나타내는 구조체
	int start, end, weight; // Edge 구조체에 변수를 선언해서 멤버에 접근
};

typedef struct GraphType {
	int n; // 간선의 개수
	int nvertex; // 정점의 개수
	struct Edge edges[2 * MAX_VERTICES]; // 간선의 정보 저장
} GraphType;

void graph_init(GraphType* g) {
	g->n = g->nvertex = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int weight) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = weight;
}

int compare(const void* a, const void* b) { // qsort()
	struct Edge* x = (struct Edge* )a;
	struct Edge* y = (struct Edge* )b;
	return (x->weight - y->weight);
}

void kruskal(GraphType* g) {
	int edge_accepted = 0; // 현재까지 선택된 간선의 수
	int uset, vset; // 정점 u와 정점 v의 집합 번호
	struct Edge e; // 간선에 접근하기위한 변수

	set_init(g->nvertex); 
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘\n");
	int i = 0;
	while (edge_accepted < (g->nvertex - 1)) { // 간선의 수 < n-1
		e = g->edges[i];
		uset = set_find(e.start); // 정점u의 집합 번호
		vset = set_find(e.end); // 정점v의 집합 번호
		if (uset != vset) {
			printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}
