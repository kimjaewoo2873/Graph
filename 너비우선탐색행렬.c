#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10

typedef int element;

typedef struct QueueType {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void queue_init(QueueType* q) {
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) {
	return (q->front == q->rear);
}

int is_full(QueueType* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType* q, element item) {
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;	
	q->queue[q->rear] = item;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

#define MAX_VERTICES 50
typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int visited[MAX_VERTICES];

void graph_init(GraphType* g) {
	for (int r = 0; r < MAX_VERTICES; r++)
		for (int c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
	g->n = 0;
}

void insert_vertex(GraphType* g,int v) {
	if (((g->n) + 1 > MAX_VERTICES)) {
		fprintf(stderr, "그래프: 정점 개수 초과");
		return;
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void bfs_mat(GraphType* g, int v) {
	int w;
	QueueType q;

	queue_init(&q);
	visited[v] = TRUE; // 시작 정점 방문
	printf("%d 방문 -> ", v);
	enqueue(&q, v); // 시작 정점 큐에 저장
	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에서 정점 추출
		for (w = 0; w < g->n; w++) // 추줄한 정점의 인접 정점 탐색
			if (g->adj_mat[v][w] && !visited[w]) { // v에 인접정점이 있다면, 텀색중인 w정점에 방문하지 않았더라면
				visited[w] = TRUE;
				printf("%d 방문 -> ", w);
				enqueue(&q, w); // 방문한 정점을 큐에 저장
			}
	}
}

int main(void) {
	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);
	for (int i = 0; i < 6; i++)
		insert_vertex(g, i);
	insert_edge(g, 0, 2);
	insert_edge(g, 2, 1);
	insert_edge(g, 2, 3);
	insert_edge(g, 0, 4);
	insert_edge(g, 4, 5);
	insert_edge(g, 1, 5);

	bfs_mat(g, 0);
	free(g);
}


