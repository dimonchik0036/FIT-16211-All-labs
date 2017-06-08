//	 Labs: 5-huffman
// Author: Dimonchik0036

#include "huffman.h"

void fill_tree_code(Node *tree, Symbol *alphSmb,
                    BARR_ELTYPE tmpSmbCode[MAX_CODE_BITS], size_t deep)
{
	if (!(tree->right || tree->left))
	{
		alphSmb[tree->ch].lengthCode = deep ? deep : 1;
		memcpy(alphSmb[tree->ch].code, tmpSmbCode, MAX_CODE_BITS);
	}
	else
	{
		if (tree->left)
		{
			BARR_SET(tmpSmbCode, deep);
			fill_tree_code(tree->left, alphSmb, tmpSmbCode, deep + 1);
		}

		if (tree->right)
		{
			BARR_CLEAR(tmpSmbCode, deep);
			fill_tree_code(tree->right, alphSmb, tmpSmbCode, deep + 1);
		}
	}
}

unsigned int write_tree(FILE *fout, Node *tree, BARR_ELTYPE *bufForSmbCode)
{
	static unsigned int posWritingBit = 0;

	if (tree->left)
	{
		set_file_bit(bufForSmbCode, 1, posWritingBit++, fout);
		write_tree(fout, tree->left, bufForSmbCode);
	}

	if (tree->right) write_tree(fout, tree->right, bufForSmbCode);

	if (!(tree->right || tree->left))
	{
		set_file_bit(bufForSmbCode, 0, posWritingBit++, fout);
		for (char i = 7; i >= 0; i--) set_file_bit(bufForSmbCode, BARR_TEST(&(tree->ch), i), posWritingBit++, fout);
	}
	return posWritingBit;
}
