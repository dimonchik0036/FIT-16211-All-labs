//	 Labs: 8-1-prim-kruskal
// Author: Dimonchik0036

#include <stdlib.h>
#include "prim.h"


void free_matrix(int **matrix, int N)
{
	for (int i = 0; i < N; ++i) free(matrix[i]);
	free(matrix);
}
