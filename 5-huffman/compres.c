//	 Labs: 5-huffman
// Author: Dimonchik0036

#include "huffman.h"

void compres(FILE *fin, FILE *fout)
{
	unsigned char RLEsmb = '\0';

	Node *tree = malloc_wr(sizeof(Node));

	size_t *frequencyAlphSymbols = get_prob_tree(&tree, fin);

	if ((RLEsmb = is_RLE(frequencyAlphSymbols)))
	{
		RLE(fout, frequencyAlphSymbols[RLEsmb], RLEsmb);
		free(frequencyAlphSymbols);
		return;
	}

	Symbol *alphabetSymbols = calloc(1, sizeof(Symbol) * ALPH_SIZE);
	RUN_ASSERT(alphabetSymbols,"Problem with calloc. Program exit.\n", EXIT_FAILURE);

	BARR_ELTYPE tmpSmbCode[MAX_CODE_BITS] = {0};

	fill_tree_code(tree, alphabetSymbols, tmpSmbCode, 0);
	free(frequencyAlphSymbols);

	write_file(fin, fout, alphabetSymbols, tree);
	tree_remove(tree);
}
