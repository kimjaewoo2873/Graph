#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES]; // �θ��� �ε��� ������ �迭

void init(int n) {
	for (int i = 0; i < n; i++)
		parent[i] = -1;
}

// curr�� ���ϴ� ������ ��ȯ. ����Ŭ ���� Ȯ��
int set_find(int curr) { // ��ȯ�� 2���� ��Ʈ��尡 ���� ���տ� �����ִٸ�, ����Ŭ ����
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

void set_union(int a, int b) { // �ΰ��� �ٸ� ������ �ϳ��� ����
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2) // ���� ������ �������� �ʾ�, ����Ŭ ���� ����
		parent[root1] = root2;
}

struct Edge { // ������ ��Ÿ���� ����ü
	int start, end, weight; // Edge ����ü�� ������ �����ؼ� ����� ����
};

typedef struct GraaphType {
	int n; // ������ ����
	int nvertex; // ������ ����
	struct Edge edges[2 * MAX_VERTICES]; // ������ ���� ����
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
	int edge_accepted = 0; // ������� ���õ� ������ ��
	int uset, vset; // ���� u�� ���� v�� ���� ��ȣ
	struct Edge e; // ������ �����ϱ����� ����

	set_init(g->nvertex); 
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("ũ�罺Į �ּ� ���� Ʈ�� �˰���\n");
	int i = 0;
	while (edge_accepted < (g->nvertex - 1)) { // ������ �� < n-1
		e = g->edges[i];
		uset = set_find(e.start); // ����u�� ���� ��ȣ
		vset = set_find(e.end); // ����v�� ���� ��ȣ
		if (uset != vset) {
			printf("���� (%d, %d) %d ����\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}
