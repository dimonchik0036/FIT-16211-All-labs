//	 Labs: 5-huffman
// Author: Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include "huffman.h"

int get_option(FILE *fin);

int main(void)
{
	FILE *fin;
	FILE *fout;

	RUN_ASSERT(fin =
		fopen(FILE_NAME_RD, "rb"), "Can't open fin. Program exit\n",
		EXIT_FAILURE);
	RUN_ASSERT(fout =
		fopen(FILE_NAME_WR, "wb"), "Can't open fout. Program exit\n",
		EXIT_FAILURE);

	switch (get_option(fin))
	{
	case COMPRES: compres(fin, fout);
		break;
	case DECOMPRES:
		{
			unsigned char sizeLostByte = '\0';
			fseek(fin, WIN_NEW_LINE + 1, SEEK_SET);
			fread(&sizeLostByte, 1, 1, fin);

			if (7 < abs(sizeLostByte))
			{
				UNRLE(fin, fout);
				break;
			}

			decompres(fin, fout, sizeLostByte);
		}
		break;
	case FILE_EMPTY:
		RUN_ASSERT(!fclose(fin), "Can't close fin. Program exit\n",
			EXIT_FAILURE);
		RUN_ASSERT(!fclose(fout), "Can't close fout. Program exit\n",
			EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	case BAD_OPT: fprintf(stderr, "Invalid option. Program exit\n");
		exit(EXIT_FAILURE);
	case BAD_FILE: fprintf(stderr, "File bad. Program exit\n");
		exit(EXIT_FAILURE);
	default: 
		exit(EXIT_FAILURE);
	}

	RUN_ASSERT(!fclose(fin), "Can't close fin. Program exit\n",
		EXIT_FAILURE);
	RUN_ASSERT(!fclose(fout), "Can't close fout. Program exit\n",
		EXIT_FAILURE);

	return 0;
}

int get_option(FILE *fin)
{
	unsigned char option;

	if (!fread(&option, 1, 1, fin)) return BAD_FILE;

	fseek(fin, WIN_NEW_LINE + 1, SEEK_SET);
	fgetc(fin);

	if (feof(fin)) return FILE_EMPTY;
	if (COMPRES_OPT == option) return COMPRES;
	if (EXPAN_OPT == option) return DECOMPRES;
	return BAD_OPT;
}
