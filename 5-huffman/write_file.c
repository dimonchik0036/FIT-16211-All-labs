//	 Labs: 5-huffman
// Author: Dimonchik0036

#include "huffman.h"

void write_file(FILE *fin, FILE *fout, Symbol *alphSmb, Node *tree)
{
	unsigned char readWriteSymbol = '\0';
	BARR_ELTYPE *writeByteBuffer;

	RUN_ASSERT(writeByteBuffer = BARR_MALLOC(CHAR_BIT),"Can't alloc memory for buf\n", EXIT_FAILURE);

	fseek(fin, WIN_NEW_LINE + 1, SEEK_SET); // +1 for lostByte
	rewind(fout);
	fwrite(&readWriteSymbol, 1, 1, fout);

	BARR_CLEARARRAY(writeByteBuffer, CHAR_BIT);

	size_t posWritingBit = write_tree(fout, tree, writeByteBuffer);
	unsigned char bufferForReadSymbols[BUFFER_SIZE] = {0};

	size_t countReadSymbols;

	while ((countReadSymbols = fread(bufferForReadSymbols, 1, BUFFER_SIZE, fin)))
	{
		for (size_t index = 0; index < countReadSymbols; ++index)
		{
			readWriteSymbol = bufferForReadSymbols[index];

			for (size_t i = 0; alphSmb[readWriteSymbol].lengthCode && i < alphSmb[readWriteSymbol].lengthCode;
			     i++)
			{
				set_file_bit(writeByteBuffer, BARR_TEST(alphSmb[readWriteSymbol].code, i), posWritingBit, fout);
				posWritingBit = (posWritingBit + 1) % BARR_ELBITS;
			}
		}
	}

	Node *tmp = tree;
	unsigned char lostByte = 0;
	for (size_t i = 8 - posWritingBit; i > 0; i--)
	{
		if (tmp->right) tmp = tmp->right;
		if (!tmp->right)
		{
			lostByte++;
			tmp = tree;
		}
	}

	while (posWritingBit % BARR_ELBITS) set_file_bit(writeByteBuffer, 0, posWritingBit++, fout);

	rewind(fout);
	fwrite(&lostByte, 1, 1, fout);

	BARR_FREE(writeByteBuffer);
}
