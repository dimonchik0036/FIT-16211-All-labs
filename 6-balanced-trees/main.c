//	 Labs: 6-balanced-trees
// Author: Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "avltree.h"
#include <stdlib.h>


int main(int argc, char *argv[])
{
	FILE *fIn = fopen("in.txt", "rt");
	FILE *fOut = fopen("out.txt", "wt");
	if (fIn == NULL || fOut == NULL) { return EXIT_FAILURE; }

	AvlTreeNode *tree = NULL;

	int n = 0;
	int cur = 0;

	fscanf(fIn, "%d", &n);

	while (n--)
	{
		fscanf(fIn, "%d", &cur);
		tree = avltree_insert(tree, cur);
	}

	fprintf(fOut, "%d\n", avltree_height(tree));

	avltree_free(tree);

	return 0;
}
