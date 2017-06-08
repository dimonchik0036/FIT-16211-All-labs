//	 Labs: 5-huffman
// Author: Dimonchik0036

#include "huffman.h"

void create_tree_node(BARR_ELTYPE *bitBuf, Node *tree, size_t *fileBitPos,
                      FILE *fin)
{
	*fileBitPos %= BARR_ELBITS;
	if (get_file_bit(bitBuf, (*fileBitPos)++, fin))
	{
		tree->left = malloc_wr(sizeof(Node));

		tree->left->left = tree->left->right = NULL;
		create_tree_node(bitBuf, tree->left, fileBitPos, fin);
	}
	else
	{
		tree->ch = get_file_byte(bitBuf, *fileBitPos, fin);
		return;
	}

	tree->right = malloc_wr(sizeof(Node));

	tree->right->left = tree->right->right = NULL;

	if (get_file_bit(bitBuf, (*fileBitPos)++, fin))
	{
		tree->right->left = malloc_wr(sizeof(Node));

		tree->right->left->left = tree->right->left->right = NULL;
		tree->right->right = malloc_wr(sizeof(Node));

		tree->right->right->left = tree->right->right->right = NULL;

		create_tree_node(bitBuf, tree->right->left, fileBitPos, fin);
		create_tree_node(bitBuf, tree->right->right, fileBitPos, fin);
	}
	else tree->right->ch = get_file_byte(bitBuf, *fileBitPos, fin);
}

void trans(BARR_ELTYPE *bitBuf, size_t *fileBitPos, Node *tree, FILE *fin,
           FILE *fout, unsigned char sizeLostByte)
{
	Node *tmp = tree;
	size_t index = 0;
	unsigned char BUFFER[BUFFER_SIZE] = {0};

	*fileBitPos %= BARR_ELBITS;
	while (!feof(fin))
	{
		if (get_file_bit(bitBuf, *fileBitPos, fin) && tmp->left && tmp->right) tmp = tmp->left;
		else if (tmp->left && tmp->right) tmp = tmp->right;

		if (!tmp->left && !tmp->right)
		{
			BUFFER[index++] = tmp->ch;
			tmp = tree;

			if (128 == index)
			{
				fwrite(&BUFFER, 1, index, fout);
				index = 0;
			}
		}
		(*fileBitPos)++;
	}

	size_t i = sizeLostByte % CHAR_BIT;

	if (index > 0)
	{
		i = index - sizeLostByte;
		fwrite(&BUFFER, 1, i, fout);
	}
}

void decompres(FILE *fin, FILE *fout, unsigned char sizeLostByte)
{
	Node *tree = NULL;
	size_t fileBitPos = 0;

	BARR_ELTYPE *bitBuf = BARR_MALLOC(CHAR_BIT);
	RUN_ASSERT(bitBuf, "Can't alloc memmory for buffer bit\n", EXIT_FAILURE);

	fread(bitBuf, BARR_ELBITS / CHAR_BIT, 1, fin);
	tree = malloc_wr(sizeof(Node));

	tree->left = tree->right = NULL;
	create_tree_node(bitBuf, tree, &fileBitPos, fin);

	trans(bitBuf, &fileBitPos, tree, fin, fout, sizeLostByte);
	BARR_FREE(bitBuf);
	tree_remove(tree);
}
