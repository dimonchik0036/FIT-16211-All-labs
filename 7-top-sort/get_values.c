//	 Labs: 7-top-sort
// Author: Dimonchik0036

#include  "top_sort.h"


void get_values(FILE *fin, FILE *fout, struct List *list, int N, int M)
{
	int from, to;

	for (int i = 0; i < M; ++i)
	{
		if (2 != fscanf_s(fin, "%d %d", &from, &to))
		{
			remove_list(list, N);
			ERROR(fout, ERROR_NUMB_LINE);
		}

		if ((1 > from || N < from) || (1 > to || N < to))
		{
			remove_list(list, N);
			ERROR(fout, ERROR_VERT);
		}

		list_add(list, from - 1, to - 1);
	}

	for (int i = 0; i < N; ++i) list[i].index = i + 1;
}
