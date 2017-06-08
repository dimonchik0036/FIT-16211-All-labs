//	 Labs: 8-1-prim-kruskal
// Author: Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include "prim.h"


int main(void)
{
	int N = -1, M = -1;
	int **matrix;

	FILE *fIn = fopen(IN_FILE, "r");
	FILE *fOut = fopen(OUT_FILE, "w");
	if (!fIn || !fOut)
	{
		fprintf(stderr, ERROR_FILE);
		return (0);
	}

	if (read_first_values(fIn, &N, &M) || !((matrix = alloc_matrix(N))) || get_edges(matrix, M, N, fIn))
	{
		fclose(fIn);
		fclose(fOut);
		return (0);
	}

	if ((M < (N - 1)) || search_tree(matrix, N, fOut)) fprintf(stdout, ERROR_TREE);

	free_matrix(matrix, N);
	fclose(fIn);
	fclose(fOut);

	return (0);
}
