#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES];

void printA(GraphType* g) {
	int i, j;
	printf("====================================");
	for (i = 0; i < g->n; i++) {
		for (j = 0; j < g->n; j++) {
			if (A[i][j] == INF)
				printf(" * ");
			else
				printf("%3d ", A[i][j]);
		}
		printf("\n");
	}
	printf("====================================");
}

void floyd(GraphType* g) {
	int i, j, k;
	for (i = 0; i < g->n; i++)
		for (j = 0; j < g->n; j++)
			A[i][j] = g->weight[i][j]; // 초기화
	printA(g);
	 
	for (k = 0; k < g->n; k++) { // k를 거쳐가는 것과 비교한다
		for (i = 0; i < g->n; i++) { // 출발 정점
			for (j = 0; j < g->n; j++) { // 도착 정점
				if (A[i][k] + A[k][j] < A[i][j])  // i->k->j 와 i->j 비교
					A[i][j] = A[i][k] + A[k][j];  // 거쳐가는게 더 작으면 바꾼다
			}
		}
		printA(g);
	}
}