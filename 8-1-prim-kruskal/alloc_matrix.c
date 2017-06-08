//	 Labs: 8-1-prim-kruskal
// Author: Dimonchik0036

#define ERROR(stream, str) { fprintf(stream, str); return NULL; }


#include <stdio.h>
#include <stdlib.h>
#include "prim.h"


int** alloc_matrix(int size)
{
	int **matrix = (int **)malloc(size * sizeof(int));
	if (!matrix) ERROR(stderr, ERROR_MEM);


	for (int i = 0; i < size; ++i)
	{
		matrix[i] = calloc(size, sizeof(int));
		if (!matrix[i]) ERROR(stderr, ERROR_MEM);
	}

	return matrix;
}
