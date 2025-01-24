#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; // 각 정점에서 다른정점까지의 가중치 저장
}GraphType;

int distance[MAX_VERTICES]; // 각 정점까지의 가장 짧은 알려진 거리를 저장
int found[MAX_VERTICES]; // 벙문한 정점 표시 / 1: 방문, 0: x

int choose(int distance[], int n, int found[]) { // 최단경로 정점 찾기
	int i, min, minpos;
	min = INT_MAX; // 무한대로 초기화
	minpos = -1; // 정점 인덱스 저정할 변수
	for(i = 0; i < n; i++) // 가장 짧은거리의 정점을 찾아 인덱스 저장
		if (distance[i] < min && !found[i]) { 
			min = distance[i]; // distance배열에 저장된 값들 비교하기위해
			minpos = i; // 인덱스값 저장
		}
	return minpos; // 가장 짧은 거리를 갖는 정점번호 반환
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
		distance[i] = g->weight[start][i]; // 시작 정점부터 거리 초기화
		found[i] = FALSE; 
	}
	found[start] = TRUE;
	distance[start] = 0; // 시작 정점은 본인거리 "0"
	for (i = 0; i < g->n - 1; i++) { // 총n개의 정점 중, 시작정점은 처리했으므로 n-1개만 처리하면된다
		print_status(g);
		u = choose(distance, g->n, found); // 최단경로 정점 찾기
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w]) // 방문한 정점들의 거리는 필요없음
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
}
