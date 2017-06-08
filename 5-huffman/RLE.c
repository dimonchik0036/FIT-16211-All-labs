//	 Labs: 5-huffman
// Author: Dimonchik0036

#include "huffman.h"

unsigned char is_RLE(size_t *alphVal)
{
	unsigned char symbols = 0;
	int countSmbs = 0;
	for (int i = 0; i < ALPH_SIZE; i++)
	{
		if (alphVal[i])
		{
			symbols = i;
			countSmbs++;
		}

		if (countSmbs > 1) return 0;
	}

	return symbols;
}

void RLE(FILE *fout, size_t smbFrequency, unsigned char RLEsmb)
{
	fputc(128, fout);
	fwrite(&smbFrequency, sizeof(size_t), 1, fout);
	fputc(RLEsmb, fout);
}

void UNRLE(FILE *fin, FILE *fout)
{
	size_t smbFrequency;
	unsigned char RLEsmb;

	fread(&smbFrequency, sizeof(size_t), 1, fin);
	fread(&RLEsmb, 1, 1, fin);

	for (; smbFrequency > 0; smbFrequency--) fwrite(&RLEsmb, 1, 1, fout);
}
