#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 우선순위 배열
} GraphType;

int selected[MAX_VERTICES]; // 방문 확인
int distance[MAX_VERTICES]; // 신장트리 정점 집합에서 각 정점까지의 거리를 갖는다

// 최소 dist[v] 값을 갖는 정점을 반환
int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) { // 방문하지 않은 것
			v = i; // 아래에서 거리 비교하기위해
			break;
		}
	}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) // 방문하지않고, v정점보다 거리가 작은 정점을 구한다
			v = i;
	return v;
}

void prim(GraphType* g, int s) {
	int i, u, v;
	for (u = 0; u < g->n; u++)
		distance[u] = INF; // 무한대로 초기화
	distance[s] = 0; // 처음 시작 정점 값 0
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); // 정점의 개수까지
		selected[u] = TRUE;
		if (distance[u] == INF) // 최솟값 갖는 정점까지의 거리가 무한대면 종료
			return;
		printf("정점 %d 추가\n", u);
		for (v = 0; v < g->n; v++) // Prim은 인접 정점에서 최소비용 간선을 찾는다
			if (g->weight[u][v] != INF) // 인접한 정점까지의 거리가 무한대가 아니면
				if (!selected[v] && g->weight[u][v] < distance[v]) // v정점에 방문하지 않았고, 기존의 거리보다 작다면
					distance[v] = g->weight[u][v]; // 짧은 거리로 저장
	}
}