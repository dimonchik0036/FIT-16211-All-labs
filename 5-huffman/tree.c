//	 Labs: 5-huffman
// Author: Dimonchik0036

#include <stdlib.h>
#include "huffman.h"

typedef struct List
{
	struct List *next;
	struct Node *node;
	unsigned int key;
} List;

static List* list_create()
{
	List *root = malloc_wr(sizeof(List));
	*root = (List){NULL, NULL, 0};
	return root;
}

static void list_node_insert(List *root, Node *node, unsigned int value)
{
	List *leaf = malloc_wr(sizeof(List));
	leaf->key = value;
	leaf->node = node;

	while (root->next && root->next->key < value) root = root->next;

	leaf->next = root->next;
	root->next = leaf;
}

static void list_node_remove(List *root)
{
	List *tmp = root->next;

	root->next = tmp->next;
	free(tmp);
}

static void list_remove(List *root)
{
	while (root->next) list_node_remove(root);
	free(root);
}

size_t* get_prob_tree(Node **tree, FILE *fin)
{
	int countReadSymbols = 0;
	int smbFromFile = 0;

	fseek(fin, WIN_NEW_LINE + 1, SEEK_SET);
	size_t *frequencyAlphSymbols = calloc(ALPH_SIZE, sizeof(size_t));

	RUN_ASSERT(frequencyAlphSymbols, "Can't alloc memory for alph\n", EXIT_FAILURE)

	while ((smbFromFile = getc(fin)) != EOF)
	{
		frequencyAlphSymbols[smbFromFile]++;
		countReadSymbols++;
	}

	if (1 == countReadSymbols) return frequencyAlphSymbols;

	List *smbList = list_create();
	Node *tmpNode;
	size_t listLen = 0;

	for (int i = 0; i < ALPH_SIZE; i++)
	{
		if (frequencyAlphSymbols[i])
		{
			tmpNode = malloc_wr(sizeof(Node));
			*tmpNode = (Node){i, NULL, NULL};
			list_node_insert(smbList, tmpNode, frequencyAlphSymbols[i]);
			listLen++;
		}
	}

	while (1 != listLen)
	{
		tmpNode = malloc_wr(sizeof(Node));
		tmpNode->left = smbList->next->node;
		tmpNode->right = smbList->next->next->node;
		list_node_insert(smbList, tmpNode,
		                 smbList->next->key + smbList->next->next->key);
		list_node_remove(smbList);
		list_node_remove(smbList);
		--listLen;
	}

	*tree = smbList->next->node;
	list_remove(smbList);

	return frequencyAlphSymbols;
}

void tree_remove(Node *tree)
{
	if (tree)
	{
		if (tree->right) tree_remove(tree->right);
		if (tree->left) tree_remove(tree->left);
		free(tree);
	}
}
