//	 Labs: 8-0-kruskal
// Author: Dimonchik0036

#include <stdio.h>
#include <limits.h>
#include "kruskal.h"


int get_edges(struct Edge *edges, int size, const int N, FILE *fIn)
{
	int from = 0, to = 0, weight = 0;
	const int M = size;
	size = 0;

	if (0 == M && 1 != N)
	{
		fprintf(stdout, ERROR_TREE);
		return (-1);
	}

	if (0 == M && 1 == N)
	{
		fprintf(stdout, "");
		return (-1);
	}

	while (size < M)
	{
		if (3 > fscanf_s(fIn, "%d%d%d", &from, &to, &weight))
		{
			fprintf(stdout, ERROR_NUMB_LINE);
			return (-1);
		}

		if ((MIN_NUMB_VERT + 1 > from || N < from) || (1 > to || N < to))
		{
			fprintf(stdout, ERROR_VERT);
			return (-1);
		}

		if ((0 > weight) || (weight > INT_MAX))
		{
			fprintf(stdout, ERROR_LENG);
			return (-1);
		}

		edges[size].indexFrom = from;
		edges[size].indexTo = to;
		edges[size].weight = weight;
		++size;
	}

	return (0);
}
