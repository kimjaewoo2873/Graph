#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES]; // �켱���� �迭
} GraphType;

int selected[MAX_VERTICES]; // �湮 Ȯ��
int distance[MAX_VERTICES]; // ����Ʈ�� ���� ���տ��� �� ���������� �Ÿ��� ���´�

// �ּ� dist[v] ���� ���� ������ ��ȯ
int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) { // �湮���� ���� ��
			v = i; // �Ʒ����� �Ÿ� ���ϱ�����
			break;
		}
	}
	for (i = 0; i < n; i++)
		if (!selected[i] && (distance[i] < distance[v])) // �湮�����ʰ�, v�������� �Ÿ��� ���� ������ ���Ѵ�
			v = i;
	return v;
}

void prim(GraphType* g, int s) {
	int i, u, v;
	for (u = 0; u < g->n; u++)
		distance[u] = INF; // ���Ѵ�� �ʱ�ȭ
	distance[s] = 0; // ó�� ���� ���� �� 0
	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n); // ������ ��������
		selected[u] = TRUE;
		if (distance[u] == INF) // �ּڰ� ���� ���������� �Ÿ��� ���Ѵ�� ����
			return;
		printf("���� %d �߰�\n", u);
		for (v = 0; v < g->n; v++) // Prim�� ���� �������� �ּҺ�� ������ ã�´�
			if (g->weight[u][v] != INF) // ������ ���������� �Ÿ��� ���Ѵ밡 �ƴϸ�
				if (!selected[v] && g->weight[u][v] < distance[v]) // v������ �湮���� �ʾҰ�, ������ �Ÿ����� �۴ٸ�
					distance[v] = g->weight[u][v]; // ª�� �Ÿ��� ����
	}
}