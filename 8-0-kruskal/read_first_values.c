//	 Labs: 8-0-kruskal
// Author: Dimonchik0036

#include <stdio.h>
#include "kruskal.h"


int read_first_values(FILE *fIn, int *N, int *M)
{
	int res = 0;

	res = fscanf_s(fIn, "%d%d", N, M);
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
