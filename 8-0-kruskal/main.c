//	 Labs: 8-0-kruskal
// Author: Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include "kruskal.h"


int main(int argc, char *argv[] )
{
	int N = -1, M = -1;
	struct Edge *edges;

	FILE *fIn = fopen(IN_FILE, "r");
	FILE *fOut = fopen(OUT_FILE, "w");
	if (NULL == fIn || NULL == fOut)
	{
		fprintf(stderr, ERROR_FILE);
		return (0);
	}

	if (read_first_values(fIn, &N, &M) || !((edges = (struct Edge *)calloc(M, sizeof(struct Edge)))) || get_edges(edges, M, N, fIn))
	{
		fclose(fIn);
		fclose(fOut);
		return (0);
	}

	if ((M < (N - 1)) || search_tree(edges, M, N, fOut)) fprintf(stdout, ERROR_TREE);

	free(edges);
	fclose(fIn);
	fclose(fOut);

	return (0);
}
