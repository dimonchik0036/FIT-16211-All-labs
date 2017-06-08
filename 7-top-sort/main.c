//	 Labs: 7-top-sort
// Author: Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS


#include "top_sort.h"


int main(int argc, char *argv[])
{
	int N = -1, M = -1;

	FILE *fin = fopen(INPUT_FILE, "r");
	FILE *fout = fopen(OUTPUT_FILE, "w");
	if (!fin || !fout) ERROR(stderr, "Error file\n");

	read_first_values(fin, fout, &N, &M);

	struct List *list = list_create(N);
	
	get_values(fin, fout, list, N, M);

	if (top_sort(list, N, fout))
	{
		remove_list(list, N);
		ERROR(fout, ERROR_CYCLE);
	}

	remove_list(list, N);
	fclose(fin);
	fclose(fout);

	return 0;
}
