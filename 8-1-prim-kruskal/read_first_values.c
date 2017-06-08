//	 Labs: 8-1-prim-kruskal
// Author: Dimonchik0036

#include <stdio.h>
#include "prim.h"


int read_first_values(FILE *in, int *N, int *M)
{
	int res = 0;

	res = fscanf_s(in, "%d%d", N, M);
	if (res < 2)
	{
		fprintf(stdout, ERROR_NUMB_LINE);
		return (-1);
	}
	if (!(MIN_NUMB_VERT <= *N && *N <= MAX_NUMB_VERT))
	{
		fprintf(stdout, ERROR_NUMB_VERT);
		return (-1);
	}
	if (!(MIN_NUMB_EDGE <= *M && *M <= (*N) * (*N + 1) / 2))
	{
		fprintf(stdout, ERROR_NUMB_EDGE);
		return (-1);
	}

	return (0);
}
