#define _CRT_SECURE_NO_WARNINGS

#define INF UINT_MAX
#define MAX_NODES 5000


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int input_handling(FILE *fin, int low_limit, int upper_limit, char *error_msg)
{
	int temp = 0;

	fscanf(fin, "%d", &temp);

	if ((temp < low_limit) || (upper_limit < temp))
	{
		puts(error_msg);
		exit(0);
	}

	return temp;
}

int compare(unsigned dist[], unsigned overflow[], unsigned node1, unsigned node2, unsigned node1_addition)
{
	if (overflow[node1] < overflow[node2]) return -1;
	if (overflow[node1] > overflow[node2]) return 1;

	if (dist[node1] + node1_addition < dist[node2]) return -1;
	if (dist[node1] + node1_addition > dist[node2]) return 1;

	return 0;
}

int main(int argc, char *argv[])
{
	FILE *fin = fopen("in.txt", "rt");
	FILE *fout = fopen("out.txt", "wt");
	if (fin == NULL || fout == NULL) { return EXIT_FAILURE; }

	int N = input_handling(fin, 0, MAX_NODES, "bad number of vertices\n");
	int S = input_handling(fin, 1, N, "bad vertex\n");
	S--;

	int F = input_handling(fin, 1, N, "bad vertex\n");
	F--;

	int M = input_handling(fin, 0, N * (N + 1) / 2, "bad number of edges\n");

	/* Таблица сммежности */
	unsigned int **matrix = (unsigned int**)malloc(N * sizeof(unsigned int*));
	for (int i = 0; i < N; i++)
	{
		matrix[i] = (unsigned int*)malloc(N * sizeof(unsigned int));

		for (int j = 0; j < N; ++j) matrix[i][j] = INF;
	}

	bool used[MAX_NODES]; // Пройденые вершины
	int parent[MAX_NODES]; // Предки вершин
	unsigned distance[MAX_NODES]; // Расстояние от начальной вершины
	unsigned overflow[MAX_NODES]; // Количество INT_MAX

	/* Инициализация начальными значениями*/
	for (int i = 0; i < N; i++)
	{
		used[i] = false;
		distance[i] = (i == S) ? (0) : (INF);
		overflow[i] = 0;
		parent[i] = -1;
	}

	/* Заполнение матрицы смежности */
	for (int i = 0; i < M; ++i)
	{
		int v1 = input_handling(fin, 1, N, "bad vertex\n") - 1;
		int v2 = input_handling(fin, 1, N, "bad vertex\n") - 1;
		unsigned len = input_handling(fin, 0, INT_MAX, "bad length\n");

		matrix[v1][v2] = len;
		matrix[v2][v1] = len;
	}

	for (int i = 0; i < N; ++i)
	{
		/* Поиск вершины, которая наименее удалена от начальной вершины */
		int v = -1;

		for (int j = 0; j < N; ++j) if (!used[j] && (v == -1 || distance[j] < distance[v])) v = j;

		if (distance[v] == INF) break;

		used[v] = true;

		/* Релаксирование соседей */
		for (int j = 0; j < N; ++j)
		{
			if (matrix[v][j] == INF) continue;

			int to = j;
			int len = matrix[v][to];

			if (compare(distance, overflow, v, to, len) == -1)
			{
				distance[to] = distance[v] + len;
				overflow[to] = overflow[v];

				while (distance[to] > INT_MAX)
				{
					++overflow[to];
					distance[to] -= INT_MAX;
				}

				parent[to] = v;
			}
		}
	}

	/* Первая строка вывода */
	for (int i = 0; i < N; ++i)
	{
		if (distance[i] == INF) fprintf(fout, "oo ");
		else if (overflow[i]) fprintf(fout, "INT_MAX+ ");
		else fprintf(fout, "%d ", distance[i]);
	}
	fprintf(fout, "\n");

	unsigned overflow_count = 0;
	if (overflow[F])
	{
		for (int i = 0; i < N; ++i)
		{
			if (matrix[F][i] != INF && distance[i] + matrix[F][i] > INT_MAX) ++overflow_count;

			if (overflow_count >= 2) break;
		}
	}

	/* Вторая строка вывода */
	if (S == F) fprintf(fout, "%d\n", S + 1);
	else if (parent[F] == -1) fprintf(fout, "no path\n");
	else if (overflow[F] && overflow_count >= 2) fprintf(fout, "overflow\n");
	else
	{
		for (int path_node = F; path_node != S; path_node = parent[path_node]) fprintf(fout, "%d ", path_node + 1);

		fprintf(fout, "%d\n", S + 1);
	}

	for (int i = 0; i < N; ++i) free(matrix[i]);

	free(matrix);

	return 0;
}
