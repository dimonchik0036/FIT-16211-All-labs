//	 Labs: 8-0-kruskal
// Author: Dimonchik0036

#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"


struct Stack
{
	int indexFrom;
	int indexTo;
	struct Stack *next;
};

static void push(struct Stack **st, int from, int to)
{
	if (!st)
	{
		fprintf(stderr, "ERROR: NULL pointer(Stack)\n");
		exit(0);
	}

	struct Stack *tmp = malloc(sizeof(struct Stack));
	if (!tmp)
	{
		fprintf(stderr, "ERROR: Out of memory!\n");
		exit(0);
	}

	tmp->indexTo = to;
	tmp->indexFrom = from;
	tmp->next = *st;
	(*st) = tmp;
}

static int pop(struct Stack **st, FILE *out)
{
	struct Stack *tmp = *st;

	if (!st)
	{
		fprintf(stderr, "ERROR: NULL pointer(Stack)\n");
		exit(0);
	}

	if (!*st) return (0);

	fprintf(out, "%d %d\n", (*st)->indexFrom, (*st)->indexTo);
	(*st) = (*st)->next;
	free(tmp);

	return (1);
}

static int compare(const struct Edge *first, const struct Edge *second) { return (first->weight - second->weight); }

static int master(int *set, int index)
{
	int last = index;

	while (index != set[index]) index = set[index];

	set[last] = index;

	return (index);
}

static void colored(int *set, int N, int prev, int next) { for (int i = 0; i < N; ++i) if (set[i] == prev) set[i] = next; }

int search_tree(struct Edge *edges, int M, int N, FILE *fOut)
{
	int i;
	struct Stack *st = NULL;

	int *set = malloc(sizeof(int) * N);
	if (!set)
	{
		fprintf(stderr, ERROR_MEM);
		exit(0);
	}

	for (i = 0; i < N; ++i) set[i] = i;

	qsort(edges, M, sizeof(struct Edge), compare);

	for (i = 0; i < M; ++i)
	{
		if (master(set, edges[i].indexFrom - 1) != master(set, edges[i].indexTo - 1))
		{
			colored(set, N, set[edges[i].indexFrom - 1], master(set, edges[i].indexTo - 1));
			push(&st, edges[i].indexFrom, edges[i].indexTo);
		}
	}

	int tmp = set[0];

	for (i = 0; i < N; ++i)
	{
		master(set, i);
		if (tmp != set[i]) return (-1);
	}

	for (i = 0; i < M && pop(&st, fOut); ++i);

	free(set);

	return (0);
}
