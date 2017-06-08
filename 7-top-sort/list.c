//	 Labs: 7-top-sort
// Author: Dimonchik0036

#include "top_sort.h"

struct List* list_create(int N)
{
	struct List *list = calloc(N, sizeof(struct List));
	if (!list)
	{
		fprintf(stderr, "Memory error!\n");
		exit(EXIT_FAILURE);
	}

	return list;
}

void list_add(struct List *list, int indexFrom, int indexTo)
{
	if (!(list[indexFrom].first))
	{
		struct Node *first = malloc(sizeof(struct Node));
		if (!first)
		{
			fprintf(stderr, "Memory error!\n");
			exit(0);
		}

		first->link = &list[indexTo];
		first->next = NULL;

		list[indexFrom].first = first;

		return;
	}

	struct Node *first = malloc(sizeof(struct Node));
	if (!first)
	{
		fprintf(stderr, "Memory error!\n");
		exit(0);
	}

	first->link = &list[indexTo];
	first->next = list[indexFrom].first;

	list[indexFrom].first = first;
}

static void remove_node(struct Node *node)
{
	if (!node) return;

	remove_node(node->next);
	free(node);
}

void remove_list(struct List *list, int N)
{
	if (!list)	return;

	for (int i = 0; i < N; ++i) remove_node(list[i].first);

	free(list);
}
