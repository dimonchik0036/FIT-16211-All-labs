//	 Labs: 6-balanced-trees
// Author: Dimonchik0036

#include "avltree.h"
#include <stdlib.h>


AvlTreeNode* avltree_node_new(int key)
{
	AvlTreeNode *n = (AvlTreeNode *)malloc(sizeof(AvlTreeNode));

	n->key = key;
	n->height = 1;
	n->left = n->right = NULL;

	return n;
}

void avltree_free(AvlTreeNode *tree)
{
	if (tree == NULL) return;

	avltree_free(tree->left);
	avltree_free(tree->right);

	free(tree);
}

AvlTreeNode* avltree_insert(AvlTreeNode *node, int k)
{
	if (!node) return avltree_node_new(k);

	if (k < node->key) node->left = avltree_insert(node->left, k);
	else node->right = avltree_insert(node->right, k);

	return avltree_balance(node);
}

AvlTreeNode* avltree_rotateright(AvlTreeNode *node)
{
	AvlTreeNode *q = node->left;
	node->left = q->right;
	q->right = node;

	avltree_height_fix(node);
	avltree_height_fix(q);

	return q;
}

AvlTreeNode* avltree_rotateleft(AvlTreeNode *node)
{
	AvlTreeNode *tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;

	avltree_height_fix(node);
	avltree_height_fix(tmp);

	return tmp;
}

AvlTreeNode* avltree_balance(AvlTreeNode *node)
{
	avltree_height_fix(node);

	if (avltree_balance_difference(node) == 2)
	{
		if (avltree_balance_difference(node->right) < 0) node->right = avltree_rotateright(node->right);

		return avltree_rotateleft(node);
	}

	if (avltree_balance_difference(node) == -2)
	{
		if (avltree_balance_difference(node->left) > 0) node->left = avltree_rotateleft(node->left);

		return avltree_rotateright(node);
	}

	return node;
}

int avltree_balance_difference(AvlTreeNode *node) { return avltree_height(node->right) - avltree_height(node->left); }

unsigned char avltree_height(AvlTreeNode *node) { return (node) ? (node->height) : (0); }

void avltree_height_fix(AvlTreeNode *node)
{
	unsigned char hl = avltree_height(node->left);
	unsigned char hr = avltree_height(node->right);

	node->height = ((hl > hr) ? (hl) : (hr)) + 1;
}
