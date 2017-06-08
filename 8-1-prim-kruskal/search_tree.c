//	 Labs: 8-1-prim-kruskal
// Author: Dimonchik0036

#include <stdio.h>
#include <stdlib.h>
#include "prim.h"


static int get_min(struct Vert *resultVert, int N, int **matrix, const int i)
{
	int min = 0;

	/* The first vertex is not indexFrom the set. */
	while (0 == resultVert[min].lengthPath && min < N) min++;

	for (int j = 0; j < N; ++j)
	{
		if (matrix[i][j] > 0 && resultVert[j].lengthPath > matrix[i][j])
		{
			resultVert[j].lengthPath = matrix[i][j];
			resultVert[j].indexFrom = i;
		}

		min = (resultVert[j].lengthPath > 0 && resultVert[min].lengthPath > resultVert[j].lengthPath) ? j : min;
	}

	return min;
}

int search_tree(int **matrix, int N, FILE *fOut)
{
	int min = 0;
	int vertexCount = 1;

	struct Vert *resultVert = (struct Vert *)calloc(N, sizeof(struct Vert));
	if (!resultVert)
	{
		fprintf(stderr, ERROR_MEM);
		exit(0);
	}

	for (int i = 0; i < N; ++i)
	{
		resultVert[i].indexFrom = i;
		resultVert[i].lengthPath = INF;
	}

	/* Initializing the first item */
	int i = 0;
	resultVert[i].lengthPath = 0;
	resultVert[i].indexFrom = 0;

	while (vertexCount < N)
	{
		min = get_min(resultVert, N, matrix, i);

		if (INF == resultVert[min].lengthPath) return (-1);

		resultVert[min].lengthPath = 0;
		fprintf(fOut, "%d %d\n", resultVert[min].indexFrom + 1, min + 1);
		i = min;
		++vertexCount;
	}

	for (i = 0; i < N; ++i) if (i == resultVert[i].indexFrom && INF == resultVert[i].lengthPath) return (-1);

	free(resultVert);

	return (0);
}
