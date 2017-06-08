//	 Labs: 7-top-sort
// Author: Dimonchik0036

#include "top_sort.h"

static int DFS(struct List *list, int *res, int *resInd);

int top_sort(struct List *list, int N, FILE *fout)
{
	int resInd = 0;
	int *res = (int *)malloc(N * sizeof(int));

	/* Красим вершины */
	for (int i = 0; i < N; ++i)
	{
		if ((2 != list[i].color) && (1 == list[i].color || DFS(&list[i], res, &resInd)))
		{
			free(res);
			return 1;
		}
	}

	/* Выводим результат */
	for (int i = 0; i < N; ++i) fprintf(fout, "%d ", res[N - i - 1]);

	free(res);

	return 0;
}

/* Если попали в серую вершину (1), значит обнаружен цикл */
static int DFS(struct List *list, int *res, int *resInd)
{
	if (1 == list->color) return 1;
	if (2 == list->color) return 0;
	list->color = 1;

	struct Node *tmp = list->first;
	while (tmp)
	{
		if (DFS(tmp->link, res, resInd)) return 1;
		tmp = tmp->next;
	}

	list->color = 2;
	res[*resInd] = list->index; // Добавляем вершину в буффер вывода
	(*resInd)++;

	return 0;
}
