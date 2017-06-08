//	 Labs: 7-top-sort
// Author: Dimonchik0036

#include "top_sort.h"


void read_first_values(FILE *fin, FILE *fout, int *N, int *M)
{
	if (fscanf_s(fin, "%d %d", N, M) < 2) ERROR(fout, ERROR_NUMB_LINE);

	if (!(0 <= *N && *N <= 1000)) ERROR(fout, ERROR_NUMB_VERT);
	if (!(0 <= *M && *M <= (*N) * ((*N) + 1) / 2)) ERROR(fout, ERROR_NUMB_EDG);
}
